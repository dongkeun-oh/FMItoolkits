/* Copyright 2018 National Fusion Reseach Institude (NFRI, Republic of Korea)
 * This file is updated by D. K. Oh, and the original code is cppfmu developed
 * by L. T. Kyllingstad with SINTEF Ocean, MPL 2.0 Copyright 2016-2017.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#include <exception>
#include <limits>
#include <iostream>

#include "cppfmu2.hpp"


namespace
{
    // A struct that holds all the data for one model instance.
    struct Component
    {
        Component(
            fmi2String instanceName,
            const fmi2CallbackFunctions *callbackFunctions,
            fmi2Boolean loggingOn)
            : memory{*callbackFunctions}
	    , logCategories{std::make_shared<cppfmu::LogCategories>(loggingOn)}	      
            , debugLoggingEnabled{std::make_shared<bool>(loggingOn == fmi2True)}
            , logger{callbackFunctions->componentEnvironment, cppfmu::CopyString(memory, instanceName), callbackFunctions, logCategories, debugLoggingEnabled}
            , lastSuccessfulTime{std::numeric_limits<fmi2Real>::quiet_NaN()}
        {
        }
        // General
        cppfmu::Memory memory;
        std::shared_ptr<cppfmu::LogCategories> logCategories;
        std::shared_ptr<bool> debugLoggingEnabled;
        cppfmu::Logger logger;

        // FMU instance for Model Excahnge or Co-simulation
        cppfmu::UniquePtr<cppfmu::Instance> instance;
        fmi2Real lastSuccessfulTime;
        // Checking the state of FMU instane
        template<typename... Args>
        void checkInstance(const ModelState expectedState, const char *func, const char *msg, Args&&... args) {
	  const std::string logstr("Calling ");
	  logger.Log(fmi2OK, LOG_FMI_CALL, (logstr + func + msg).c_str(), std::forward<Args>(args)...);
	  if (!(instance->modelState() & expectedState)) {
	    instance->modelState() = modelError;
	    throw std::logic_error(std::string(func) + " - Illegal call sequence.");
	  }
        }
        void checkInstance(const ModelState expectedState, const char *func) {
	  logger.Log(fmi2OK, LOG_FMI_CALL, "Calling %s", func);
	  if (!(instance->modelState() & expectedState)) {
	    instance->modelState() = modelError;
	    throw std::logic_error(std::string(func) + " - Illegal call sequence.");
	  }
        }
    };

}


extern "C"
{
// ---------------------------------------------------------------------------
// FMI 2.0 functions 
// ---------------------------------------------------------------------------
// * Model Exchange is not implemented yet ...

FMI2_Export fmi2Component fmi2Instantiate(
    fmi2String  instanceName,
    fmi2Type  fmuType,
    fmi2String  fmuGUID,
    fmi2String  fmuLocation,
    const fmi2CallbackFunctions *functions,
    fmi2Boolean visible,
    fmi2Boolean loggingOn)
{
    try {
        auto component = cppfmu::AllocateUnique<Component>(cppfmu::Memory{*functions},
							    instanceName,
							    functions,
                                                            loggingOn);
        component->instance = Cppfmu2Instantiate(instanceName,
						 fmuType,
						 fmuGUID,
						 fmuLocation,
						 visible,
						 loggingOn,
						 component->memory,
						 component->logger);
        component->logger.Log(fmi2OK, LOG_FMI_CALL,"Calling fmi2Instantiate: GUID =%s", fmuGUID);
        component->instance->modelState() = modelInstantiated;
	return component.release();
    } catch (const cppfmu::FatalError& e) {
        functions->logger(nullptr, instanceName, fmi2Fatal, "FATAL: %s", e.what());
        return nullptr;
    } catch (const std::exception& e) {
        functions->logger(nullptr, instanceName, fmi2Error, "ERROR: %s", e.what());
        return nullptr;
    }
}


FMI2_Export void fmi2FreeInstance(fmi2Component c)
{
    const auto component = reinterpret_cast<Component*>(c);
    // The Component object was allocated using cppfmu::AllocateUnique(),
    // which uses cppfmu::New() internally, so we use cppfmu::Delete() to
    // release it again.
    try {
      component->checkInstance(MASK_fmi2FreeInstance, "fmi2FreeInstance");
     } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
	return;
     } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
     }
    cppfmu::Delete(component->memory, component);
}

  
FMI2_Export fmi2Status fmi2SetupExperiment(fmi2Component c,
					 fmi2Boolean toleranceDefined,
					 fmi2Real tolerance,
					 fmi2Real startTime,
					 fmi2Boolean stopTimeDefined,
					 fmi2Real stopTime)
{
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2SetupExperiment, "fmi2SetupExperiment",
			    ": toleranceDefined=%d tolerance=%g", toleranceDefined, tolerance);
      //
      component->instance->Initialize(toleranceDefined, tolerance,
				   startTime, stopTimeDefined, stopTime);
      //
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2EnterInitializationMode(fmi2Component c) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2EnterInitializationMode, "fmi2EnterInitializationMode");
    component->instance->modelState() = modelInitializationMode;
    return fmi2OK;
  } catch (const cppfmu::FatalError& e) {
    component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
      return fmi2Fatal;
  } catch (const std::exception& e) {
    component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
      return fmi2Error;
  }
}


FMI2_Export fmi2Status fmi2ExitInitializationMode(fmi2Component c) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2ExitInitializationMode, "fmi2ExitInitializationMode");
    //
    if (component->instance->isDirtyValues() !=0) {
      component->instance->Update();
      component->instance->isDirtyValues() = 1;
    }
    //
    if (component->instance->modelType() == fmi2ModelExchange)
      component->instance->modelState() = modelEventMode;
    else
      component->instance->modelState() = modelStepComplete;
    return fmi2OK;
  } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s" ,e.what());
      return fmi2Fatal;
  } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
      return fmi2Error;
  }
}


FMI2_Export fmi2Status fmi2Terminate(fmi2Component c) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2Terminate, "fmi2Terminate");
      component->instance->modelState() = modelTerminated;
      //
      component->instance->Terminate();
      //
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2Reset(fmi2Component c) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2Reset, "fmi2Reset");
      //
      component->instance->Reset();
      //
      component->instance->modelState() = modelInstantiated;
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }    
}
  
// ---------------------------------------------------------------------------
// FMI functions: class methods not depending of a specific model instance
// ---------------------------------------------------------------------------
  
FMI2_Export const char* fmi2GetTypesPlatform() { return fmi2TypesPlatform; }


FMI2_Export const char* fmi2GetVersion() { return fmi2Version; }
  
// ---------------------------------------------------------------------------
// FMI functions: logging control, setters and getters for Real, Integer,
// Boolean, String
// ---------------------------------------------------------------------------  

FMI2_Export fmi2Status fmi2SetDebugLogging(fmi2Component c,
					   fmi2Boolean loggingOn,
					   size_t nCategories,
					   const fmi2String categories[]) {
    const auto component = reinterpret_cast<Component*>(c);
    size_t ii;
    try {
      component->checkInstance(MASK_fmi2SetDebugLogging, "fmi2SetDebugLogging");

      if (nCategories == 0)
	component->logger.resetLogCategories(loggingOn);
      else {
	component->logger.resetLogCategories(fmi2False);
        std::cout << nCategories <<" ***\n";
	for(ii =0; ii < nCategories; ii++){
	  component->logger.Log(fmi2OK, LOG_ERROR, "test %s", categories[ii] );
	  component->logger.selectLogCategories(categories[ii]);}
      }
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }  

}
  

FMI2_Export fmi2Status fmi2GetReal (fmi2Component c,
			const fmi2ValueReference vr[],
			size_t nvr, fmi2Real value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {      
      component->checkInstance(MASK_fmi2GetReal, "fmi2GetReal");
      if (nvr > 0 && component->instance->isDirtyValues()) {
	component->instance->Update();
	component->instance->isDirtyValues() = 0;
      }
      //
      component->instance->GetReal(vr, nvr, value);
      //
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2GetInteger(fmi2Component c,
				      const fmi2ValueReference vr[],
				      size_t nvr, fmi2Integer value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2GetInteger, "fmi2GetInteger");
      if (nvr > 0 && component->instance->isDirtyValues()) {
	component->instance->Update();
	component->instance->isDirtyValues() = 0;
      }
      //
      component->instance->GetInteger(vr, nvr, value);
      //
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }    
}


FMI2_Export fmi2Status fmi2GetBoolean(fmi2Component c,
				      const fmi2ValueReference vr[],
				      size_t nvr, fmi2Boolean value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2GetBoolean, "fmi2GetBoolean");
      if (nvr > 0 && component->instance->isDirtyValues()) {
	component->instance->Update();
	component->instance->isDirtyValues() = 0;
      }
      //
      component->instance->GetBoolean(vr, nvr, value);
      //
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }    
}


FMI2_Export fmi2Status fmi2GetString (fmi2Component c,
				      const fmi2ValueReference vr[],
				      size_t nvr, fmi2String value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2GetString, "fmi2GetString");
      if (nvr > 0 && component->instance->isDirtyValues()) {
	component->instance->Update();
	component->instance->isDirtyValues() = 0;
      }
      //
      component->instance->GetString(vr, nvr, value);
      //
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }     
}


FMI2_Export fmi2Status fmi2SetReal (fmi2Component c,
				    const fmi2ValueReference vr[],
				    size_t nvr, const fmi2Real value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2SetReal, "fmi2SetReal");
      //
      component->instance->SetReal(vr, nvr, value);
      //
      component->instance->isDirtyValues() = 1;
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2SetInteger(fmi2Component c,
				      const fmi2ValueReference vr[],
				      size_t nvr, const fmi2Integer value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2SetInteger, "fmi2SetInteger");
      //
      component->instance->SetInteger(vr, nvr, value);
      //
      component->instance->isDirtyValues() = 1;
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }  
}


FMI2_Export fmi2Status fmi2SetBoolean(fmi2Component c,
				      const fmi2ValueReference vr[],
				      size_t nvr, const fmi2Boolean value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2SetBoolean, "fmi2SetBoolean");
      //
      component->instance->SetBoolean(vr, nvr, value);
      //
      component->instance->isDirtyValues() = 1;
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
      component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
      component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }    
}


FMI2_Export fmi2Status fmi2SetString (fmi2Component c,
				      const fmi2ValueReference vr[],
				      size_t nvr, const fmi2String value[]) {
    const auto component = reinterpret_cast<Component*>(c);
    try {
      component->checkInstance(MASK_fmi2SetString, "fmi2SetString");
      //
      component->instance->SetString(vr, nvr, value);
      //
      component->instance->isDirtyValues() = 0;
      return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }     
}


FMI2_Export fmi2Status fmi2GetFMUstate (fmi2Component c, fmi2FMUstate* /*FMUstate*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetFMUstate, "fmi2GetFMUstate");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2GetFMUstate");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2SetFMUstate (fmi2Component c, fmi2FMUstate /*FMUstate*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2SetFMUstate, "fmi2SetFMUstate");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2SetFMUstate");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* /*FMUstate*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2FreeFMUstate, "fmi2FreeFMUstate");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2FreeFMUstate");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}

  
FMI2_Export fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate /*FMUstate*/, size_t* /*size*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2SerializedFMUstateSize, "fmi2SerializedFMUstateSize");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2SerializedFMUstateSize");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2SerializeFMUstate (fmi2Component c, fmi2FMUstate /*FMUstate*/, fmi2Byte /*serializedState*/[], size_t /*size*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2SerializeFMUstate, "fmi2SerializedFMUstate");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2SerializeFMUstate");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2DeSerializeFMUstate (fmi2Component c, const fmi2Byte /*serializedState*/[], size_t /*size*/, fmi2FMUstate* /*FMUstate*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2DeSerializeFMUstate, "fmi2DeSerializedFMUstate");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2DeSerializeFMUstate");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2GetDirectionalDerivative(fmi2Component c, const fmi2ValueReference /*vUnknown_ref*/[], size_t /*nUnknown*/,
						    const fmi2ValueReference /*vKnown_ref*/[] , size_t /*nKnown*/,
						    const fmi2Real /*dvKnown*/[], fmi2Real /*dvUnknown*/[]) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetDirectionalDerivative, "fmi2GetDirectionalDerivative");
    component->logger.Log(fmi2Error, LOG_ERROR, "%s: Function not implemented.", "fmi2GetDirectionalDerivative");
    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


// ---------------------------------------------------------------------------
// Functions for FMI 2.0 for Co-Simulation
// ---------------------------------------------------------------------------
// #ifdef FMI_COSIMULATION
 
/* Simulating the slave */
 
FMI2_Export fmi2Status fmi2SetRealInputDerivatives(fmi2Component c,
						     const fmi2ValueReference vr[],
						     std::size_t nvr,
						     const fmi2Integer order[],
						     const fmi2Real value[]) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2SetRealInputDerivatives, "fmi2SetRealInputDerivatives", ": nvr= %d", nvr);
    //
    component->instance->SetRealInputDerivatives(vr, nvr, order, value);
    //
    return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2GetRealOutputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
                                      const fmi2Integer order[], fmi2Real value[]) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetRealOutputDerivatives, "fmi2GetRealOutputDerivatives", ": nvr= %d", nvr);
    //
    component->instance->GetRealOutputDerivatives(vr, nvr, order, value);
    //
    return fmi2OK;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2CancelStep(fmi2Component c) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2CancelStep, "fmi2CancelStep", ": Can be called when fmi2DoStep returned fmi2Pending.\nThis is not the case.");
    // component->instance->modelState() = modelStepCanceled;

    return fmi2Error;
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}


FMI2_Export fmi2Status fmi2DoStep(fmi2Component c,
				  fmi2Real currentCommunicationPoint,
				  fmi2Real communicationStepSize,
				  fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2DoStep, "fmi2DoStep", 
        ": currentCommunicationPoint = %g, communicationStepSize = %g, noSetFMUStatePriorToCurrentPoint = fmi2%s",
			     currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint ? "True" : "False");
    double endTime = currentCommunicationPoint;
    const auto ok = component->instance->DoStep(
            currentCommunicationPoint,
            communicationStepSize,
            noSetFMUStatePriorToCurrentPoint,
            endTime);
    if (ok) {
      component->lastSuccessfulTime =
	currentCommunicationPoint + communicationStepSize;
      return fmi2OK; }
    else {
      component->lastSuccessfulTime = endTime;
      return fmi2Discard; }
    } catch (const cppfmu::FatalError& e) {
        component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
        return fmi2Fatal;
    } catch (const std::exception& e) {
        component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
        return fmi2Error;
    }
}

  
const char *statusKind[4] = {"fmi2DoStepStatus","fmi2PendingStatus","fmi2LastSuccessfulTime", "fmi2Terminated"};
const char *statusReturn[4] = {"fmi2Pending","fmi2Pending","fmi2Discard", "fmi2Discard"};
  
FMI2_Export fmi2Status fmi2GetStatus(fmi2Component c,
				     const fmi2StatusKind s,
				     fmi2Status */*value*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetStatus, "fmi2GetStatus", ": fmi2StatusKind = %s", statusKind[s]);
    component->logger.Log(fmi2Error, LOG_ERROR, "fmi2GetStatus: Can be called with %s when fmi2DoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
    return fmi2Discard;
   } catch (const cppfmu::FatalError& e) {
       component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
       return fmi2Fatal;
   } catch (const std::exception& e) {
       component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
       return fmi2Error;
   } 
}

  
FMI2_Export fmi2Status fmi2GetRealStatus(fmi2Component c,
					 const fmi2StatusKind s,
					 fmi2Real *value) {
    const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetRealStatus, "fmi2GetRealStatus", ": fmi2StatusKind = %s", statusKind[s]);
    if (s == fmi2LastSuccessfulTime) {
        *value = component->lastSuccessfulTime;
        return fmi2OK;
    } else {
        component->logger.Log(fmi2Error, LOG_ERROR, "Invalid status inquiry for fmiGetRealStatus");
        return fmi2Error;
    }
  } catch (const cppfmu::FatalError& e) {
       component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
       return fmi2Fatal;
   } catch (const std::exception& e) {
       component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
       return fmi2Error;
   } 
}

  
FMI2_Export fmi2Status fmi2GetIntegerStatus(fmi2Component c,
					    const fmi2StatusKind s,
					    fmi2Integer* /*value*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetIntegerStatus, "fmi2GetIntegerStatus", ": fmi2StatusKind = %s", statusKind[s]);
    component->logger.Log(fmi2Error, LOG_ERROR, "fmi2GetIntegerStatus: Can be called with %s when fmi2DoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
    return fmi2Discard;
   } catch (const cppfmu::FatalError& e) {
       component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
       return fmi2Fatal;
   } catch (const std::exception& e) {
       component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
       return fmi2Error;
   } 
}


FMI2_Export fmi2Status fmi2GetBooleanStatus(fmi2Component c, const fmi2StatusKind s, fmi2Boolean *value) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetBooleanStatus, "fmi2GetBooleanStatus", ": fmi2StatusKind = %s", statusKind[s]);
    if (s == fmi2Terminated) {
      *value = component->instance->terminateSimulation();
      return fmi2OK;
    } else {
      component->logger.Log(fmi2Error, LOG_ERROR, "fmi2GetStringStatus: Can be called with %s when fmi2DoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
      return fmi2Discard;
    }
   } catch (const cppfmu::FatalError& e) {
       component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
       return fmi2Fatal;
   } catch (const std::exception& e) {
       component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
       return fmi2Error;
   } 
}

  
FMI2_Export fmi2Status fmi2GetStringStatus(fmi2Component c, const fmi2StatusKind s, fmi2String* /*value*/) {
  const auto component = reinterpret_cast<Component*>(c);
  try {
    component->checkInstance(MASK_fmi2GetStringStatus, "fmi2GetStringStatus", ": fmi2StatusKind = %s", statusKind[s]);
    component->logger.Log(fmi2Error, LOG_ERROR, "fmi2GetStringStatus: Can be called with %s when fmi2DoStep returned %s.\nThis is not the case.", statusKind[s], statusReturn[s]);
    return fmi2Discard;
   } catch (const cppfmu::FatalError& e) {
       component->logger.Log(fmi2Fatal, LOG_ERROR, "FATAL: %s", e.what());
       return fmi2Fatal;
   } catch (const std::exception& e) {
       component->logger.Log(fmi2Error, LOG_ERROR, "ERROR: %s", e.what());
       return fmi2Error;
   } 
}



// ---------------------------------------------------------------------------
// Functions for FMI 2.0 for Model Exchange
// ---------------------------------------------------------------------------
//#else
/* Enter and exit the different modes */
//#endif //Model Exchange 
}
