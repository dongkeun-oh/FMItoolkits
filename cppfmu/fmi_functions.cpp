/* Copyright 2016-2017, SINTEF Ocean.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <exception>
#include <limits>

#include "cppfmu_cs.hpp"


namespace
{
    // A struct that holds all the data for one model instance.
    struct Component
    {
        Component(
            fmiString instanceName,
            fmiCallbackFunctions callbackFunctions,
            fmiBoolean loggingOn)
            : memory{callbackFunctions}
            , debugLoggingEnabled{std::make_shared<bool>(loggingOn == fmiTrue)}
            , logger{this, cppfmu::CopyString(memory, instanceName), callbackFunctions, debugLoggingEnabled}
            , lastSuccessfulTime{std::numeric_limits<fmiReal>::quiet_NaN()}
        {
        }

        // General
        cppfmu::Memory memory;
        std::shared_ptr<bool> debugLoggingEnabled;
        cppfmu::Logger logger;

        // Co-simulation
        cppfmu::UniquePtr<cppfmu::SlaveInstance> instance;
        fmiReal lastSuccessfulTime;

        // Checking the state of FMU instane
        template<typename... Args>
        void checkInstance(const ModelState expectedState, const char *func, const char *msg, Args&&... args) {
	  const std::string logstr("Calling ");
	  logger.Log(fmiOK, "log", (logstr + func + msg).c_str(), std::forward<Args>(args)...);
	  if (!(instance->modelState() & expectedState)) {
	    instance->modelState() = modelError;
	    throw std::logic_error(std::string(func) + " - Illegal call sequence.");
	  }
        }
        void checkInstance(const ModelState expectedState, const char *func) {
	  logger.Log(fmiOK, "log", "Calling %s", func);
	  if (!(instance->modelState() & expectedState)) {
	    instance->modelState() = modelError;
	    throw std::logic_error(std::string(func) + " - Illegal call sequence.");
	  }
        }
    };
}


// FMI functions
extern "C"
{


DllExport const char* fmiGetTypesPlatform() { return fmiPlatform; }


DllExport const char* fmiGetVersion() { return fmiVersion; }


DllExport fmiComponent fmiInstantiateSlave(
    fmiString  instanceName,
    fmiString  fmuGUID,
    fmiString  fmuLocation,
    fmiString  mimeType,
    fmiReal    timeout,
    fmiBoolean visible,
    fmiBoolean interactive,
    fmiCallbackFunctions functions,
    fmiBoolean loggingOn)
{
    try {
        auto component = cppfmu::AllocateUnique<Component>(cppfmu::Memory{functions},
            instanceName,
            functions,
            loggingOn);
        component->instance = CppfmuInstantiateSlave(
            instanceName,
            fmuGUID,
            fmuLocation,
            mimeType,
            timeout,
            visible,
            interactive,
            component->memory,
            component->logger);
	component->logger.Log(fmiOK, "log", "Calling fmiInstantiateSlave: GUID =%s", fmuGUID);
        component->instance->modelState() = modelInstantiated;
	return component.release();
        return component.release();
    } catch (const cppfmu::FatalError& e) {
        functions.logger(nullptr, instanceName, fmiFatal, "", e.what());
        return nullptr;
    } catch (const std::exception& e) {
        functions.logger(nullptr, instanceName, fmiError, "", e.what());
        return nullptr;
    }
}


DllExport void fmiFreeSlaveInstance(fmiComponent c)
{
    const auto component = reinterpret_cast<Component*>(c);
    // The Component object was allocated using cppfmu::AllocateUnique(),
    // which uses cppfmu::New() internally, so we use cppfmu::Delete() to
    // release it again.
    try {
      component->checkInstance(modelTerminated, "fmiFreeSlaveInstance");
     } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmiFatal, "fatal", "%s", e.what());
	return;
     } catch (const std::exception& e) {
      component->logger.Log(fmiError, "error", "%s", e.what());
     }
    cppfmu::Delete(component->memory, component);
}


DllExport fmiStatus fmiInitializeSlave(
    fmiComponent c,
    fmiReal      tStart,
    fmiBoolean   stopTimeDefined,
    fmiReal      tStop)
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(modelInstantiated, "fmiInitializeSlave");
      //
      if ( component->instance->modelState() & modelInitialized) 
         component->instance->Reset();
      component->instance->Initialize(tStart, stopTimeDefined, tStop);
      //
      component->instance->modelState() = static_cast<ModelState>(modelInstantiated|modelInitialized);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiResetSlave(fmiComponent c)
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(modelInstantiated, "fmiResetSlave");
      //
      component->instance->Reset();
      //
      component->instance->modelState() = modelInstantiated;
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiTerminateSlave(fmiComponent c)
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(modelInitialized, "fmiTerminateSlave");
      //
      component->instance->Terminate();
      //
      component->instance->modelState() = modelTerminated;
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiSetDebugLogging(
    fmiComponent c,
    fmiBoolean loggingOn)
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiSetDebugLogging");
      //
      *(component->debugLoggingEnabled) = (loggingOn == fmiTrue);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }    
}


DllExport fmiStatus fmiGetReal(
    fmiComponent c,
    const fmiValueReference vr[],
    size_t nvr,
    fmiReal value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiGetReal");
      //
      component->instance->GetReal(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiGetInteger(
    fmiComponent c,
    const fmiValueReference vr[],
    size_t nvr,
    fmiInteger value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiGetInteger");
      //
      component->instance->GetInteger(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiGetBoolean(
    fmiComponent c,
    const fmiValueReference vr[],
    size_t nvr,
    fmiBoolean value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiGetBoolean");
      //
      component->instance->GetBoolean(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiGetString(
    fmiComponent c,
    const fmiValueReference vr[],
    size_t nvr,
    fmiString value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiGetString");
      //
      component->instance->GetString(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiSetReal(
    fmiComponent c,
    const fmiValueReference vr[],
    size_t nvr,
    const fmiReal value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiSetReal");
      //
      component->instance->SetReal(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiSetInteger(
    fmiComponent c,
    const fmiValueReference vr[],
    size_t nvr,
    const fmiInteger value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiSetInteger");
      //
      component->instance->SetInteger(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiSetBoolean (fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiBoolean value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiSetBoolean");
      //
      component->instance->SetBoolean(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}

  
DllExport fmiStatus fmiSetString  (fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiString  value[])
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(not_modelError, "fmiSetString");
      //
      component->instance->SetString(vr, nvr, value);
      return fmiOK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


DllExport fmiStatus fmiSetRealInputDerivatives(
    fmiComponent c,
    const  fmiValueReference vr[],
    size_t  nvr,
    const  fmiInteger order[],
    const  fmiReal value[])
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance(modelInitialized, "fmiSetRealInputDerivatives", ": nvr= %d", nvr);
     //
     component->instance->SetRealInputDerivatives(vr, nvr, order, value);
     //
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiGetRealOutputDerivatives(
    fmiComponent c,
    const   fmiValueReference vr[],
    size_t  nvr,
    const   fmiInteger order[],
    fmiReal  value[])
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance(modelInitialized, "fmiGetRealOutputDerivatives", ": nvr= %d", nvr);
     component->instance->GetRealOutputDerivatives(vr, nvr, order, value);
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiCancelStep(fmiComponent c)
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance(modelInitialized, "fmiCancelStep", ": Can be called when fmiDoStep returned fmiPending.\nThis is not the case.");
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiDoStep(
    fmiComponent c,
    fmiReal      currentCommunicationPoint,
    fmiReal      communicationStepSize,
    fmiBoolean   newStep)
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
        component->checkInstance(modelInitialized, "fmiDoStep", 
				 ": currentCommunicationPoint = %g, communicationStepSize = %g, newStep = fmi%s",
				 currentCommunicationPoint, communicationStepSize, newStep ? "True" : "False");
      
        double endTime = currentCommunicationPoint;
        const auto ok = component->instance->DoStep(
            currentCommunicationPoint,
            communicationStepSize,
            newStep,
            endTime);
        if (ok) {
            component->lastSuccessfulTime =
                currentCommunicationPoint + communicationStepSize;
            return fmiOK;
        } else {
            component->lastSuccessfulTime = endTime;
            return fmiDiscard;
        }
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmiFatal, "fatal", e.what());
        return fmiFatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmiError, "error", e.what());
        return fmiError;
    }
}


const char *statusKind[3] = {"fmiDoStepStatus","fmiPendingStatus","fmiLastSuccessfulTime"};
const char *statusReturn[3] = {"fmiPending","fmiPending","fmiDiscard"};

DllExport fmiStatus fmiGetStatus(
    fmiComponent c,
    const fmiStatusKind s,
    fmiStatus* /*value*/)
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance( static_cast<ModelState>(modelInstantiated|modelInitialized), "fmiGetStatus", ": fmiStatusKind = %s", statusKind[s]);
     component->logger.Log(fmiError, "error", "fmiGetStatus: Can be called with %s when fmiDoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiGetRealStatus(
    fmiComponent c,
    const fmiStatusKind s,
    fmiReal* /*value*/)
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance( static_cast<ModelState>(modelInstantiated|modelInitialized), "fmiGetRealStatus", ": fmiStatusKind = %s", statusKind[s]);
     component->logger.Log(fmiError, "error", "fmiGetRealStatus: Can be called with %s when fmiDoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiGetIntegerStatus(
    fmiComponent c,
    const fmiStatusKind s,
    fmiInteger* /*value*/)
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance( static_cast<ModelState>(modelInstantiated|modelInitialized), "fmiGetIntegerStatus", ": fmiStatusKind = %s", statusKind[s]);
     component->logger.Log(fmiError, "error", "fmiGetIntegerStatus: Can be called with %s when fmiDoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiGetBooleanStatus(
    fmiComponent c,
    const fmiStatusKind s,
    fmiBoolean* /*value*/)
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance( static_cast<ModelState>(modelInstantiated|modelInitialized), "fmiGetBooleanStatus", ": fmiStatusKind = %s", statusKind[s]);
     component->logger.Log(fmiError, "error", "fmiGetBooleanStatus: Can be called with %s when fmiDoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}


DllExport fmiStatus fmiGetStringStatus(
    fmiComponent c,
    const fmiStatusKind s,
    fmiString*  /*value*/)
{
   const auto component = reinterpret_cast<Component*>(c);
   try {
     component->checkInstance( static_cast<ModelState>(modelInstantiated|modelInitialized), "fmiGetStringStatus", ": fmiStatusKind = %s", statusKind[s]);
     component->logger.Log(fmiError, "error", "fmiGetStringStatus: Can be called with %s when fmiDoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
     return fmiOK;
     } catch (const cppfmu::FatalError& e) {
         component->logger.Log(fmiFatal,"fatal", e.what());
         return fmiFatal;
     } catch (const std::exception& e) {
         component->logger.Log(fmiError, "error", e.what());
         return fmiError;
     }
}

}
