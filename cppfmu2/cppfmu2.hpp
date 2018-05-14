/* Copyright 2018 National Fusion Reseach Institude (NFRI, Republic of Korea)
 * This file is updated by D. K. Oh, and the original code is cppfmu developed
 * by L. T. Kyllingstad with SINTEF Ocean, MPL 2.0 Copyright 2016-2017.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#ifndef CPPFMU2_HPP
#define CPPFMU2_HPP

#include <vector>
#include "cppfmu2_common.hpp"

namespace cppfmu
{

/* ============================================================================
 * FMI 2.0 INTERFACE
 * ============================================================================
 */

/* A base class of instances for co-simulation or model exchange.
 *
 * To implement an instance, a class which publicly derives
 * from this one and override its virtual methods as required.  
 *
 * The methods map directly to the C functions defined by FMI 2.0, so the
 * documentation here is intentionally sparse.  We refer to the FMI 2.0
 * specification for detailed information.
 */

  
class Instance
{
public:  
  Instance(fmi2Type type):m_fmi2type{type},
			  m_time{0.0},
			  m_state{modelInstantiated},
			  m_eventInfo{fmi2False,fmi2False,fmi2False,fmi2False,fmi2False,0},
			  m_is_dirty_values{0}

  {
  }
  
  // Called from fmiInitialize(). Does nothing by default.
  virtual void Initialize(fmi2Boolean toleranceDefined,
			  fmi2Real tolerance,
			  fmi2Real tStart,
			  fmi2Boolean stopTimeDefined,
			  fmi2Real tStop);
  
  // Called from fmiTerminateSlave(). Does nothing by default.
  virtual void Terminate();
  
  // Called from fmiResetSlave(). Does nothing by default.
  virtual void Reset();
  // Called when update necessary (isDirtyVlaues is not 0)
  virtual void Update();
  // Called from fmiSetXxx(). Throw std::logic_error by default.
  virtual void SetReal(const fmi2ValueReference vr[],
		       std::size_t nvr,
		       const fmi2Real value[]);
  virtual void SetInteger(const fmi2ValueReference vr[],
			  std::size_t nvr,
			  const fmi2Integer value[]);
  virtual void SetBoolean(const fmi2ValueReference vr[],
			  std::size_t nvr,
			  const fmi2Boolean value[]);
  virtual void SetString(const fmi2ValueReference vr[],
			 std::size_t nvr,
			 const fmi2String value[]);

    // Called from fmiGetXxx(). Throw std::logic_error by default.
  virtual void GetReal(const fmi2ValueReference vr[],
		       std::size_t nvr,
		       fmi2Real value[]) const;
  virtual void GetInteger(const fmi2ValueReference vr[],
			  std::size_t nvr,
			  fmi2Integer value[]) const;
  virtual void GetBoolean(const fmi2ValueReference vr[],
			  std::size_t nvr,
			  fmi2Boolean value[]) const;
  virtual void GetString(const fmi2ValueReference vr[],
			 std::size_t nvr,
			 fmi2String value[]) const;
  
  // (Co-simulation) Called from fmiDoStep(). 
  virtual bool DoStep(fmi2Real currentCommunicationPoint,
		      fmi2Real communicationStepSize,
		      fmi2Boolean noSetFMUStatePriorToCurrentPoint,
		      fmi2Real& endOfStep) = 0;
  virtual void SetRealInputDerivatives(const fmi2ValueReference vr[],
				       std::size_t nvr,
				       const fmi2Integer order[],
				       const fmi2Real value[]);
  virtual void GetRealOutputDerivatives(const fmi2ValueReference vr[],
					std::size_t nvr,
					const fmi2Integer order[],
					fmi2Real value[]) const;   
  // (Model Exchange)
  virtual void SetContinousStates(const fmi2Real x[],
				  std::size_t nx);
  virtual void GetDerivatives(fmi2Real derivatives[],
			      std::size_t nx) const;
  virtual void GetContinousStates(fmi2Real states[],
				  std::size_t nx) const;
  virtual void GetEventIndicaotrs(fmi2Real eventIndicators[],
				  size_t ni) const;
  virtual void GetNomalsOfContinuousStates(fmi2Real x_nominal[],
					   size_t nx) const;
  // Members to monitor instance states
  inline fmi2Type modelType( void) {
    return m_fmi2type;
  }
  inline ModelState &modelState( void) {
    return m_state;
  }
  inline fmi2Boolean &newDiscreteStatesNeeded(void) {
    return m_eventInfo.newDiscreteStatesNeeded;
  }
  inline fmi2Boolean &terminateSimulation(void) {
    return m_eventInfo.terminateSimulation;
  }
  inline fmi2Boolean &nominalsOfContinuousStatesChanged(void) {
    return m_eventInfo.nominalsOfContinuousStatesChanged;
  }
  inline fmi2Boolean &valuesOfContinuousStatesChanged(void) {
    return m_eventInfo.valuesOfContinuousStatesChanged;
  }
  inline fmi2Boolean &nextEventTimeDefined(void) {
    return m_eventInfo.nextEventTimeDefined;
  }
  inline fmi2Real &nextEventTime(void) {
    return m_eventInfo.nextEventTime; 
  }
  inline int &isDirtyValues(void) {
    return m_is_dirty_values;
  }
  void clearEventInfo(void) {
    m_eventInfo.newDiscreteStatesNeeded = fmi2False;
    m_eventInfo.terminateSimulation = fmi2False;
    m_eventInfo.nominalsOfContinuousStatesChanged = fmi2False;
    m_eventInfo.valuesOfContinuousStatesChanged = fmi2False;
    m_eventInfo.nextEventTimeDefined = fmi2False;
    m_eventInfo.nextEventTime = 0.0;
  }
    // The instance is destroyed in fmiFreeSlaveInstance().
  virtual ~Instance() CPPFMU_NOEXCEPT;
private:
  fmi2Type m_fmi2type;
  fmi2Real m_time;
  ModelState m_state;
  fmi2EventInfo m_eventInfo;
  int m_is_dirty_values;
};

} // namespace cppfmu


/* A function which must be defined by model code, and which should create
 * and return a new instance.
 *
 * The returned instance must be managed by a std::unique_ptr with a deleter
 * of type std::function<void(void*)> that takes care of freeing the memory.
 * The simplest way to set this up is to use cppfmu2::AllocateUnique() to
 * create the slave instance.
 *
 * Most of its parameters correspond to those of fmiInstantiateSlave(),
 * except that 'functions' and 'loggingOn' have been replaced with more
 * convenient types:
 *
 *     memory = An object which the model code can use for memory management,
 *              typically in conjunction with cppfmu2::Allocator,
 *              cppfmu2::AllocateUnique(), etc.  Allocation and deallocation
 *              requests get forwarded to the simulation environment.
 *
 *     logger = An object which the model code can use to log messages (e.g.
 *              warnings or debug info).  The messages are forwarded to the
 *              simulation environment's logging facilities.
 *
 * Note that this function is declared in the global namespace.
 */
cppfmu::UniquePtr<cppfmu::Instance> Cppfmu2Instantiate(
    fmi2String  instanceName,
    fmi2Type    fmuType,
    fmi2String  fmuGUID,
    fmi2String  fmuLocation,
    fmi2Boolean visible,
    fmi2Boolean loggingOn,
    cppfmu::Memory memory,
    cppfmu::Logger logger);


#endif // header guard
