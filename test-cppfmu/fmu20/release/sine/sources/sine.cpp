// Copyright 2015-2017, SINTEF Ocean.
// Distributed under the 3-Clause BSD License.
// (See accompanying file LICENCE.txt or copy at
// https://github.com/viproma/demo-fmus/raw/master/LICENCE.txt.)

#include <cmath>
#include <cstring>
#include "cppfmu2.hpp"
#include "sine-fmu-uuid.h"

enum
{
    // inputs and parameters
    VR_x    = 0,
    VR_a    = 1,
    VR_b    = 2,
    VR_w    = 3,
    VR_k    = 4,
    VR_d    = 5,
    VR_INPUT_COUNT = 6,

    // outputs
    VR_y    = 6,

    VR_COUNT = 7,
};


class SineInstance : public cppfmu::Instance
{
public:
    SineInstance():Instance{fmi2CoSimulation}
    {
        SineInstance::Reset();
    }

    void SetReal(
        const fmi2ValueReference vr[],
        std::size_t nvr,
        const fmi2Real value[])
        override
    {
        for (std::size_t i = 0; i < nvr; ++i) {
            if (vr[i] >= VR_INPUT_COUNT) {
                throw std::out_of_range{"Value reference out of range"};
            }
            m_input[vr[i]] = value[i];
        }
    }

    void GetReal(
        const fmi2ValueReference vr[],
        std::size_t nvr,
        fmi2Real value[])
        const override
    {
        for (std::size_t i = 0; i < nvr; ++i) {
            if (vr[i] == VR_y) {
                value[i] = Calculate();
            } else if (vr[i] < VR_INPUT_COUNT) {
                value[i] = m_input[vr[i]];
            } else {
                throw std::out_of_range{"Value reference out of range"};
            }
        }
    }

private:
    void Initialize(fmi2Boolean /*toleranceDefined*/,
		fmi2Real /*tolerance*/,
                    fmi2Real tStart,
                    fmi2Boolean /*stopTimeDefined*/,
                    fmi2Real /*tStop*/) override
    {
        m_time = tStart;
    }

    bool DoStep(
        fmi2Real currentCommunicationPoint,
        fmi2Real communicationStepSize,
        fmi2Boolean /*noSetFMUStatePriorToCurrentPoint*/,
        fmi2Real& /*endOfStep*/)
        override
    {
        m_time = currentCommunicationPoint + communicationStepSize;
        return true;
    }

    void Reset() override
    {
        m_time = 0.0;
        for (auto& v : m_input) v = 0.0;
        m_input[VR_b] = 1.0;
        m_input[VR_w] = 1.0;
    }

    fmi2Real Calculate() const CPPFMU_NOEXCEPT
    {
        return m_input[VR_a]
             + m_input[VR_b] * std::sin(
                    m_input[VR_w] * m_time
                  + m_input[VR_k] * m_input[VR_x]
                  + m_input[VR_d]
               );
    }

    fmi2Real m_time;
    fmi2Real m_input[VR_INPUT_COUNT];
};


cppfmu::UniquePtr<cppfmu::Instance> Cppfmu2Instantiate(
    fmi2String  /*stanceName*/,
    fmi2Type    fmuType,
    fmi2String  fmuGUID,
    fmi2String  /*fmuLocation*/,
    fmi2Boolean /*visible*/,
    fmi2Boolean /*loggingOn*/,
    cppfmu::Memory memory,
    cppfmu::Logger /*logger*/)
{
    if (std::strcmp(fmuGUID, FMU_UUID) != 0) {
        throw std::runtime_error("FMU GUID mismatch");
    }
    if (fmuType != fmi2CoSimulation) {
        throw std::runtime_error("FMU type must be co-simulation");
    }

    return cppfmu::AllocateUnique<SineInstance>(memory);
}
