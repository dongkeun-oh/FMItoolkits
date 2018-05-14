/* Copyright 2018 National Fusion Reseach Institude (NFRI, Republic of Korea)
 * This file is updated by D. K. Oh, and the original code is cppfmu developed
 * by L. T. Kyllingstad with SINTEF Ocean, MPL 2.0 Copyright 2016-2017.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#ifndef CPPFMU2_COMMON_HPP
#define CPPFMU2_COMMON_HPP

#include <cstddef>      // std::size_t
#include <functional>   // std::function
#include <memory>       // std::shared_ptr, std::unique_ptr
#include <new>          // std::bad_alloc
#include <stdexcept>    // std::runtime_error
#include <string>       // std::basic_string, std::char_traits
#include <utility>      // std::forward


extern "C"
{
#include <fmi2Functions.h>
}


// CPPFMU_NOEXCEPT evaluates to 'noexcept' on compilers that support it.
#if (__cplusplus >= 201103L) || (defined(_MSC_VER) && _MSC_VER >= 1900)
#   define CPPFMU_NOEXCEPT noexcept
#else
#   define CPPFMU_NOEXCEPT
#endif

// ---------------------------------------------------------------------------
// Function calls allowed state masks for both Model-exchange and Co-simulation
// ---------------------------------------------------------------------------
#define MASK_fmi2GetTypesPlatform       static_cast<ModelState>(modelStartAndEnd | modelInstantiated | modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete | modelStepInProgress | modelStepFailed | modelStepCanceled \
                                        | modelTerminated | modelError)
#define MASK_fmi2GetVersion              MASK_fmi2GetTypesPlatform
#define MASK_fmi2SetDebugLogging        static_cast<ModelState>(modelInstantiated | modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete | modelStepInProgress | modelStepFailed | modelStepCanceled \
                                        | modelTerminated | modelError)
#define MASK_fmi2Instantiate             (modelStartAndEnd)
#define MASK_fmi2FreeInstance           static_cast<ModelState>(modelInstantiated | modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete | modelStepFailed | modelStepCanceled \
                                        | modelTerminated | modelError)
#define MASK_fmi2SetupExperiment         modelInstantiated
#define MASK_fmi2EnterInitializationMode modelInstantiated
#define MASK_fmi2ExitInitializationMode  modelInitializationMode
#define MASK_fmi2Terminate              static_cast<ModelState>(modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete | modelStepFailed)
#define MASK_fmi2Reset                   MASK_fmi2FreeInstance
#define MASK_fmi2GetReal                static_cast<ModelState>(modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete | modelStepFailed | modelStepCanceled \
                                        | modelTerminated | modelError)
#define MASK_fmi2GetInteger              MASK_fmi2GetReal
#define MASK_fmi2GetBoolean              MASK_fmi2GetReal
#define MASK_fmi2GetString               MASK_fmi2GetReal
#define MASK_fmi2SetReal                static_cast<ModelState>(modelInstantiated | modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete)
#define MASK_fmi2SetInteger             static_cast<ModelState>(modelInstantiated | modelInitializationMode \
                                        | modelEventMode \
                                        | modelStepComplete)
#define MASK_fmi2SetBoolean              MASK_fmi2SetInteger
#define MASK_fmi2SetString               MASK_fmi2SetInteger
#define MASK_fmi2GetFMUstate             MASK_fmi2FreeInstance
#define MASK_fmi2SetFMUstate             MASK_fmi2FreeInstance
#define MASK_fmi2FreeFMUstate            MASK_fmi2FreeInstance
#define MASK_fmi2SerializedFMUstateSize  MASK_fmi2FreeInstance
#define MASK_fmi2SerializeFMUstate       MASK_fmi2FreeInstance
#define MASK_fmi2DeSerializeFMUstate     MASK_fmi2FreeInstance
#define MASK_fmi2GetDirectionalDerivative static_cast<ModelState>(modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelStepComplete | modelStepFailed | modelStepCanceled \
                                        | modelTerminated | modelError)

// ---------------------------------------------------------------------------
// Function calls allowed state masks for Model-exchange
// ---------------------------------------------------------------------------
#define MASK_fmi2EnterEventMode          static_cast<ModelState>(modelEventMode | modelContinuousTimeMode)
#define MASK_fmi2NewDiscreteStates       modelEventMode
#define MASK_fmi2EnterContinuousTimeMode modelEventMode
#define MASK_fmi2CompletedIntegratorStep modelContinuousTimeMode
#define MASK_fmi2SetTime                 static_cast<ModelState>(modelEventMode | modelContinuousTimeMode)
#define MASK_fmi2SetContinuousStates     modelContinuousTimeMode
#define MASK_fmi2GetEventIndicators      static_cast<ModelState>(modelInitializationMode \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelTerminated | modelError)
#define MASK_fmi2GetContinuousStates     MASK_fmi2GetEventIndicators
#define MASK_fmi2GetDerivatives          static_cast<ModelState>(modelEventMode | modelContinuousTimeMode \
                                        | modelTerminated | modelError)
#define MASK_fmi2GetNominalsOfContinuousStates static_cast<ModelState>( modelInstantiated \
                                        | modelEventMode | modelContinuousTimeMode \
                                        | modelTerminated | modelError)

// ---------------------------------------------------------------------------
// Function calls allowed state masks for Co-simulation
// ---------------------------------------------------------------------------
#define MASK_fmi2SetRealInputDerivatives static_cast<ModelState>(modelInstantiated | modelInitializationMode \
                                        | modelStepComplete)
#define MASK_fmi2GetRealOutputDerivatives static_cast<ModelState>(modelStepComplete | modelStepFailed | modelStepCanceled \
                                        | modelTerminated | modelError)
#define MASK_fmi2DoStep                  modelStepComplete
#define MASK_fmi2CancelStep              modelStepInProgress
#define MASK_fmi2GetStatus               static_cast<ModelState>(modelStepComplete | modelStepInProgress | modelStepFailed \
                                        | modelTerminated)
#define MASK_fmi2GetRealStatus           MASK_fmi2GetStatus
#define MASK_fmi2GetIntegerStatus        MASK_fmi2GetStatus
#define MASK_fmi2GetBooleanStatus        MASK_fmi2GetStatus
#define MASK_fmi2GetStringStatus         MASK_fmi2GetStatus

enum ModelState {
    modelStartAndEnd        = 1<<0,
    modelInstantiated       = 1<<1,
    modelInitializationMode = 1<<2,

    // ME states
    modelEventMode          = 1<<3,
    modelContinuousTimeMode = 1<<4,
    // CS states
    modelStepComplete       = 1<<5,
    modelStepInProgress     = 1<<6,
    modelStepFailed         = 1<<7,
    modelStepCanceled       = 1<<8,

    modelTerminated         = 1<<9,
    modelError              = 1<<10,
    modelFatal              = 1<<11
};

enum logCategoryIndx {LOG_ALL=0, LOG_ERROR, LOG_FMI_CALL, LOG_EVENT};

namespace cppfmu
{

// ============================================================================
// ERROR HANDLING
// ============================================================================


/* Exception class that signals "fatal error", i.e. an error which means that
 * not only is the current model instance invalid, but all other instances of
 * the same model too.
 */
class FatalError : public std::runtime_error
{
public:
    FatalError(const char* msg) CPPFMU_NOEXCEPT : std::runtime_error{msg} { }
};


// ============================================================================
// MEMORY MANAGEMENT
// ============================================================================


/* A wrapper class for the FMI memory allocation and deallocation functions.
 * Alloc() and Free() simply forward to the functions provided by the
 * simulation environment.
 */
class Memory
{
public:
    explicit Memory(const fmi2CallbackFunctions& callbackFunctions)
        : m_alloc{callbackFunctions.allocateMemory}
        , m_free{callbackFunctions.freeMemory}
    {
    }

    // Allocates memory for 'nObj' objects of size 'size'.
    void* Alloc(std::size_t nObj, std::size_t size) CPPFMU_NOEXCEPT
    {
        return m_alloc(nObj, size);
    }

    // Frees the memory pointed to by 'ptr'.
    void Free(void* ptr) CPPFMU_NOEXCEPT
    {
        m_free(ptr);
    }

    bool operator==(const Memory& rhs) const CPPFMU_NOEXCEPT
    {
        return m_alloc == rhs.m_alloc && m_free == rhs.m_free;
    }

    bool operator!=(const Memory& rhs) const CPPFMU_NOEXCEPT
    {
        return !operator==(rhs);
    }

private:
    fmi2CallbackAllocateMemory m_alloc;
    fmi2CallbackFreeMemory m_free;
};


/* A class that satisfies the Allocator concept, and which can therefore be
 * used to manage memory for the standard C++ containers.
 *
 * For information about the various member functions, we refer to reference
 * material for the Allocator concept, e.g.:
 * http://en.cppreference.com/w/cpp/concept/Allocator
 */
template<typename T>
class Allocator
{
public:
    using value_type = T;

    explicit Allocator(const Memory& memory) : m_memory{memory} { }

    template<typename U>
    Allocator(const Allocator<U>& other) CPPFMU_NOEXCEPT
        : m_memory{other.m_memory}
    {
    }

    T* allocate(std::size_t n)
    {
        if (n == 0) return nullptr;
        if (auto m = m_memory.Alloc(n, sizeof(T))) {
            return reinterpret_cast<T*>(m);
        } else {
            throw std::bad_alloc();
        }
    }

    void deallocate(T* p, std::size_t n) CPPFMU_NOEXCEPT
    {
        if (n > 0) {
            m_memory.Free(p);
        }
    }

    bool operator==(const Allocator& rhs) const CPPFMU_NOEXCEPT
    {
        return m_memory == rhs.m_memory;
    }

    bool operator!=(const Allocator& rhs) const CPPFMU_NOEXCEPT
    {
        return !operator==(rhs);
    }

    // -------------------------------------------------------------------------
    // None of the following are required by C++11, yet they are, variously,
    // required by GCC and MSVC.

    template<typename U>
    struct rebind { using other = Allocator<U>; };

#if defined(__GNUC__) && (__GNUC__ < 5)
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    Allocator() : m_memory{fmi2CallbackFunctions{}} { }
#pragma GCC diagnostic pop
#endif

#ifdef _MSC_VER
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        ::new((void*) p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }
#endif

    // -------------------------------------------------------------------------

private:
    template<typename U>
    friend class Allocator;

    Memory m_memory;
};


// An alias for a string type that uses cppfmu2::Allocator to manage memory.
using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;


// Returns a String whose contents are equal to those of 'string'.
inline String CopyString(const Memory& memory, fmi2String string)
{
    return String{string, Allocator<char>{memory}};
}


/* Allocates memory for a single object of type T and runs its constructor,
 * in the style of the built-in 'new' operator.  Any arguments in 'args'
 * are forwarded to the constructor.
 */
template<typename T, typename... Args>
T* New(const Memory& memory, Args&&... args)
{
    auto alloc = Allocator<T>{memory};
    const auto ptr = std::allocator_traits<decltype(alloc)>::allocate(alloc, 1);
    try {
        std::allocator_traits<decltype(alloc)>::construct(
            alloc,
            ptr,
            std::forward<Args>(args)...);
    } catch (...) {
        std::allocator_traits<decltype(alloc)>::deallocate(alloc, ptr, 1);
        throw;
    }
    return ptr;
}


/* Destroys and deallocates memory for an object of type T, in the style of
 * the built-in 'delete' operator.
 */
template<typename T>
void Delete(const Memory& memory, T* obj) CPPFMU_NOEXCEPT
{
    auto alloc = Allocator<T>{memory};
    std::allocator_traits<decltype(alloc)>::destroy(alloc, obj);
    std::allocator_traits<decltype(alloc)>::deallocate(alloc, obj, 1);
}


/* An alias for a std::unique_ptr specialisation where the deleter is general
 * and independent of the type of the object pointed to.  This is used for the
 * return type of AllocateUnique() below.
 */
template<typename T>
using UniquePtr = std::unique_ptr<T, std::function<void(void*)>>;


/* Creates an object of type T which is managed by a std::unique_ptr.
 * The object is created using cppfmu2::New(), and when the time comes, it is
 * destroyed using cppfmu2::Delete().
 */
template<typename T, typename... Args>
UniquePtr<T> AllocateUnique(const Memory& memory, Args&&... args)
{
    return UniquePtr<T>{
        New<T>(memory, std::forward<Args>(args)...),
        [memory] (void* ptr) { Delete(memory, reinterpret_cast<T*>(ptr)); }};
}


// ============================================================================
// LOGGING
// ============================================================================


/* A class that can be used to log messages from model code.  All messages are
 * forwarded to the logging facilities provided by the simulation environment.
 */

class LogCategories {
   public:
     LogCategories(fmi2Boolean t0) { reset(t0);}
  //
     void reset(fmi2Boolean t0) {
       std::fill_n(m_select, N_OF_CATEGORIES, t0==fmi2True);
     }
     const std::string& getName(logCategoryIndx idx) {
       _checkIndex( idx);
       return m_categories[static_cast<int>(idx)];
     }
     bool select(const fmi2String s) {
       for (int ii = LOG_ALL; ii <= LOG_EVENT; ii++) 
	 if (s == m_categories[static_cast<logCategoryIndx>(ii)]) {
	   m_select[ii] = true;
	   return true;
       }
       return false;
     }
     bool& operator[](logCategoryIndx idx){
       _checkIndex( idx);
       return m_select[static_cast<int>(idx)];
     }
   private:
     static const int N_OF_CATEGORIES{4};
     const std::string m_categories[N_OF_CATEGORIES]{"logAll", "logError", "logFMICall", "logEvent"};
     bool m_select[N_OF_CATEGORIES];
     //
     void _checkIndex(logCategoryIndx idx) {
       if ( idx < LOG_ALL || idx > LOG_EVENT)
	 throw std::logic_error("LogCategories : index out of bound"); 
     }
};


class Logger
{
public:
    Logger(
        fmi2ComponentEnvironment componentEnvironment,
        String instanceName,
        const fmi2CallbackFunctions *callbackFunctions,
	std::shared_ptr<LogCategories> logCategories,
        std::shared_ptr<bool> debugLoggingEnabled)
        : m_instanceName(std::move(instanceName))
	, m_debugLoggingEnabled{debugLoggingEnabled}
	, m_logCategories{logCategories}
	, m_componentEnvironment{componentEnvironment}
	, m_fmi2Logger{callbackFunctions->logger}

    {
    }

    // Logs a message.
    template<typename... Args>
    void Log(
        fmi2Status status,
	logCategoryIndx idx,
        fmi2String message,
        Args&&... args) CPPFMU_NOEXCEPT
    {
      try {
	if ( (*m_logCategories)[idx] || (*m_logCategories)[LOG_ALL] )
	  m_fmi2Logger(
		       m_componentEnvironment,
		       m_instanceName.c_str(),
		       status,
		       m_logCategories->getName(idx).c_str(),
		       message,
		       std::forward<Args>(args)...);
      }
      catch (const std::logic_error &le) {
	Log(status, LOG_ERROR, le.what(), std::forward<Args>(args)...); 
      } 
    }

    /* Logs a debug message (if debug logging is enabled by the simulation
     * environment).
     */
    template<typename... Args>
    void DebugLog(
        fmi2Status status,
	logCategoryIndx idx,
        fmi2String message,
        Args&&... args) CPPFMU_NOEXCEPT
    {
        if (*m_debugLoggingEnabled) {
            Log(
                status,
                idx,
                message,
                std::forward<Args>(args)...);
        }
    }
  inline void resetLogCategories(fmi2Boolean b) {
    m_logCategories->reset(b);
  }
  inline void selectLogCategories(fmi2String str) {
    m_logCategories->select(str);
  }
private:
    const String m_instanceName;
    std::shared_ptr<bool> m_debugLoggingEnabled;
    std::shared_ptr<LogCategories> m_logCategories;    
    const fmi2ComponentEnvironment m_componentEnvironment;
    const fmi2CallbackLogger m_fmi2Logger;
};


} // namespace cppfmu
#endif // header guard
