/* Copyright 2018 National Fusion Reseach Institude (NFRI, Republic of Korea)
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include <cmath>
#include <cstring>
#include <cppfmu_cs.hpp>
#include <boost/process.hpp>

#include "cpipe-fmu-uuid.h"

namespace bproc = boost::process;

enum
{
    // inputs and parameters
    VR_IN_pi    = 0,
    VR_IN_po    = 1,
    VR_IN_hi    = 2,
    VR_IN_ho    = 3,    
    VR_INPUT_COUNT = 4,
	VR_INPUT_TOTAL = 6,

    // outputs
    VR_OUT_mdoti    = 4,
    VR_OUT_mdoto    = 5,
    VR_OUT_hi    = 6,
    VR_OUT_ho    = 7,
    VR_OUT_deltai = 8,
    VR_OUT_deltao = 9,
    VR_OUTPUT_COUNT = 6,
	VR_OUTPUT_TOTAL = 7,
    
    // total number of variables
    VR_COUNT = 10,
    
    // strings
    VSTR_COUNT = 2,
    };


class CpipeInstance : public cppfmu::SlaveInstance
{
public:
    CpipeInstance()
          {
        CpipeInstance::Reset();
    }

private:
    void SetReal(
        const fmiValueReference vr[],
        std::size_t nvr,
        const fmiReal value[])
        override
    {
        if (nvr != VR_INPUT_COUNT)
                throw std::out_of_range{"Value reference out of range"};	  
        for (std::size_t i = 0; i < nvr; ++i) {
            if (vr[i] >= VR_INPUT_COUNT) 
                throw std::out_of_range{"Value reference out of range"};
            m_input[vr[i]] = value[i];
	    }
	}

    void GetReal(
        const fmiValueReference vr[],
        std::size_t nvr,
        fmiReal value[])
        const override
    {

      for (std::size_t i = 0; i < nvr; ++i) 
	    if (vr[i] >= VR_INPUT_COUNT && vr[i] < VR_COUNT) 
	       value[i] = m_output[vr[i]-VR_INPUT_COUNT];
	    else 
	       throw std::out_of_range{"Value reference out of range"};		
    }

    void SetString(
	const fmiValueReference vr[],
        std::size_t nvr,
        const fmiString value[])
        override
    {
      for (std::size_t i = 0; i < nvr; ++i)
	    switch( vr[i]) {
	    case 0: m_cpipe_input = std::make_unique<std::string>(value[i]);
	            break;
	    case 1: m_cpipe_workdir = std::make_unique<std::string>(value[i]);
	            break;
	    default: throw std::out_of_range{"Value reference out of range"};
	  }
    }
  
    void GetString(
	const fmiValueReference vr[],
        std::size_t nvr,
        fmiString value[])
        const override
    {
        for (std::size_t i = 0; i < nvr; ++i)  
	    switch( vr[i]) {
	    case 0: value[i] = m_cpipe_input->c_str();
	            break;
	    case 1: value[i] = m_cpipe_workdir->c_str();
	            break;
	    default: throw std::out_of_range{"Value reference out of range"};
	  }
    }

    void Initialize(
        fmiReal tStart,
        fmiBoolean /*stopTimeDefined*/,
        fmiReal /*tStop*/)
        override
    {		
        m_time = tStart;
        m_initialized = fmiFalse;		
 
        _launch_cpipe_core();
		_init_cpipe();
    }

    void Terminate()
        override
    {
		m_input[VR_INPUT_COUNT] = -1.0;
	    m_input[VR_INPUT_COUNT+1] = 0.0; 
        opipe_stream.write(reinterpret_cast<char *>(m_input), sizeof(double)*VR_INPUT_TOTAL)<< std::flush;
        if (cpipe_core != nullptr) cpipe_core->wait();
    }
  
    bool DoStep(
        fmiReal currentCommunicationPoint,
        fmiReal communicationStepSize,
        fmiBoolean /*newStep*/,
        fmiReal& /*endOfStep*/)
        override
    { 		
        _dostep_cpipe(currentCommunicationPoint, communicationStepSize);
		
        return true;
    }

    void Reset() override
    {
        m_time = 0.0;
		m_initialized = fmiFalse;
        for (auto& v : m_input) v = 0.0;
        for (auto& v : m_output) v = 0.0;	

        if (cpipe_core != nullptr) cpipe_core->terminate();
     }
	
    void _launch_cpipe_core(void) {
       std::string exe_core("_cpipe_core");
       cpipe_core = std::make_unique<bproc::child>( bproc::search_path(exe_core), bproc::std_out > ipipe_stream, bproc::std_in < opipe_stream);    
       return;
    }

    void _init_cpipe(void) {
       int status;
       bool ok = false;
       
	   if (m_initialized == fmiFalse) {
	      opipe_stream << m_cpipe_input->c_str() << std::endl;  //sending input file name	       
	      opipe_stream << m_cpipe_workdir->c_str() << std::endl;  //sending work directory name	       		  
	      ok = true&&ipipe_stream.read(reinterpret_cast<char *>(&status), sizeof(int));
	      if (status != 0 || !ok) {
		     _clear_buffer();
		     std::string errMsg;
		     switch(status) {
			    case (-1) : errMsg = "IO Error";
                    break;
			    case (-3): errMsg = "already initialized";
                    break;
			    case (2) : errMsg = "wrong input data";
                    break;
			    default : errMsg = "something unknown";
                    break;
			  }
		     throw std::runtime_error("Error in Init : " + errMsg);
		  }
		  else 
			 m_initialized = fmiTrue;
	   }
	}

	void _dostep_cpipe(double time, double timestep) {
       bool ok = false;
	   
	   if (m_initialized == fmiTrue) {
	      m_input[VR_INPUT_COUNT] = time;
	      m_input[VR_INPUT_COUNT+1] = timestep;
	      opipe_stream.write(reinterpret_cast<char *>(m_input), sizeof(double)*VR_INPUT_TOTAL)<< std::flush;
	      ok = true&&ipipe_stream.read(reinterpret_cast<char *>(m_output), sizeof(double)*VR_OUTPUT_TOTAL);
	      if (m_output[VR_OUTPUT_COUNT] != 0.0 || !ok) {
		     if (cpipe_core != nullptr) cpipe_core->terminate();
	         throw std::runtime_error("Error in DoStep");
		   }   
	      else 
		     m_time = time + timestep;
	   }
	}
	
    inline void _clear_buffer(void) {
       char ch;
	   while (ipipe_stream.rdbuf()->in_avail()) ipipe_stream.get(ch); //clear input stream buffer 
    }
    
    fmiBoolean m_initialized;
    fmiReal m_time;
    fmiReal m_input[VR_INPUT_TOTAL], m_output[VR_OUTPUT_TOTAL];	
    std::unique_ptr<std::string> m_cpipe_input, m_cpipe_workdir;
    std::unique_ptr<bproc::child> cpipe_core;
    bproc::ipstream  ipipe_stream;
    bproc::opstream  opipe_stream;
};


cppfmu::UniquePtr<cppfmu::SlaveInstance> CppfmuInstantiateSlave(
    fmiString  /*instanceName*/,
    fmiString  fmuGUID,
    fmiString  /*fmuLocation*/,
    fmiString  /*mimeType*/,
    fmiReal    /*timeout*/,
    fmiBoolean /*visible*/,
    fmiBoolean /*interactive*/,
    cppfmu::Memory memory,
    cppfmu::Logger /*logger*/)
{
    if (std::strcmp(fmuGUID, FMU_UUID) != 0) {
        throw std::runtime_error("FMU GUID mismatch");
    }
    return cppfmu::AllocateUnique<CpipeInstance>(memory);
}
