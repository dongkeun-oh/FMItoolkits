/* Copyright 2018 National Fusion Reseach Institude (NFRI, Republic of Korea)
 * This file is updated by D. K. Oh, and the original code is cppfmu developed
 * by L. T. Kyllingstad with SINTEF Ocean, MPL 2.0 Copyright 2016-2017.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#include "cppfmu2.hpp"

#include <stdexcept>


namespace cppfmu
{

// =============================================================================
// FMI 2.0 Instance
// =============================================================================


void Instance::Initialize(fmi2Boolean /* toleranceDefined*/,
			  fmi2Real /* tolerance*/,
			  fmi2Real /*tStart*/,
			  fmi2Boolean /*stopTimeDefined*/,
			  fmi2Real /*tStop*/)
{
    // Do nothing
}


void Instance::Terminate()
{
    // Do nothing
}


void Instance::Reset()
{
    // Do nothing
}

  
void Instance::Update()
{
    // Do nothing
}  

  
void Instance::SetReal(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    const fmi2Real /*value*/[])
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to set nonexistent variable");
    }
}


void Instance::SetInteger(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    const fmi2Integer /*value*/[])
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to set nonexistent variable");
    }
}


void Instance::SetBoolean(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    const fmi2Boolean /*value*/[])
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to set nonexistent variable");
    }
}


void Instance::SetString(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    const fmi2String /*value*/[])
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to set nonexistent variable");
    }
}


void Instance::GetReal(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    fmi2Real /*value*/[]) const
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to get nonexistent variable");
    }
}


void Instance::GetInteger(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    fmi2Integer /*value*/[]) const
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to get nonexistent variable");
    }
}


void Instance::GetBoolean(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    fmi2Boolean /*value*/[]) const
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to set nonexistent variable");
    }
}


void Instance::GetString(
    const fmi2ValueReference /*vr*/[],
    std::size_t nvr,
    fmi2String /*value*/[]) const
{
    if (nvr != 0) {
        throw std::logic_error("Attempted to set nonexistent variable");
    }
}


bool Instance::DoStep(fmi2Real /*currentCommunicationPoint*/,
		      fmi2Real /*communicationStepSize*/,
		      fmi2Boolean /*noSetFMUStatePriorToCurrentPoint*/,
		      fmi2Real& /*endOfStep*/)
{
    throw std::logic_error("DoStep is not implemented.");
}

  
void Instance::SetRealInputDerivatives(const fmi2ValueReference /*vr*/[],
				       std::size_t nvr,
				       const fmi2Integer /*order*/[],
				       const fmi2Real /*value*/[])
{
  if (nvr != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}
  
void Instance::GetRealOutputDerivatives(const fmi2ValueReference /*vr*/[],
					std::size_t nvr,
					const fmi2Integer /*order*/[],
					fmi2Real /*value*/[]) const {
  if (nvr != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}
  
  
void Instance::SetContinousStates(const fmi2Real /*x*/[],
			std::size_t nx)
{
  if (nx != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}

  
void Instance::GetDerivatives(fmi2Real /*derivatives*/[],
		    std::size_t nx) const
{
    if (nx != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}

  
void Instance::GetContinousStates(fmi2Real /*states*/[],
			std::size_t nx) const
{
    if (nx != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}

  
void Instance::GetEventIndicaotrs(fmi2Real /*eventIndicators*/[],
			size_t ni) const
{
    if (ni != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}

  
void Instance::GetNomalsOfContinuousStates(fmi2Real /*x_nominal*/[],
				 size_t nx) const
{
    if (nx != 0) {
    throw std::logic_error("Attempted to set nonexistent variable");
  }
}

Instance::~Instance() CPPFMU_NOEXCEPT
{
    // Do nothing
}


} // namespace
