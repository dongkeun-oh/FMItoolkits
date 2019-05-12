cmake_minimum_required(VERSION 1.8.12)

option(FMU_USE_STATIC_RUNTIME "Whether to link the model code against a static C(++) runtime library" ON)

if(APPLE)
  set(CMAKE_C_COMPILER "gcc-7")
  set(CMAKE_CXX_COMPILER "g++-7")
elseif(WIN32)
  if(MSVC)
    set(CMAKE_TOOLCHAIN_FILE "D:/Users/spinhalf.MICROWAVE/Work/vcpkg/scripts/buildsystems/vcpkg.cmake" )
    if(FMU_USE_STATIC_RUNTIME)
      set(VCPKG_TARGET_TRIPLET "x64-windows-static")
    else()
      set(VCPKG_TARGET_TRIPLET "x64-windows")
    endif()   
  endif()
endif()

project(test-cppfmu)

# ==============================================================================
# Detect platform & Set variables
# ==============================================================================

if("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
  set(extCmakeOpt "-DCMAKE_C_COMPILER=gcc-7" "-DCMAKE_CXX_COMPILER=g++-7")
  set(os "darwin")
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
  set(os "linux")
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
  set(os "win")
else()
  message(FATAL_ERROR "Unknown or unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()
math(EXPR wordSize 8*${CMAKE_SIZEOF_VOID_P})
set(fmuPlatform "${os}${wordSize}")

# ==============================================================================
# Set compiler/platform specific settings
# ==============================================================================

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options("-std=c++1y" "-Wall" "-Wextra" "-Werror")
  if(FMU_USE_STATIC_RUNTIME)
    add_compile_options("-static")
  endif()
elseif(MSVC)
  foreach(lang "C" "CXX")
    foreach(config "DEBUG" "MINSIZEREL" "RELEASE" "RELWITHDEBINFO")
      set(flagVar "CMAKE_${lang}_FLAGS_${config}")
      if(FMU_USE_STATIC_RUNTIME)
        string(REPLACE "/MD" "/MT" ${flagVar} ${${flagVar}})
      endif()
      # Treat warnings as errors and disable warning C4996
      set(${flagVar} "${${flagVar}} /WX /wd4996")
    endforeach()
  endforeach()
endif()

if(UNIX)
  # Remove the "lib" prefix on the generated .so files
  set(CMAKE_SHARED_MODULE_PREFIX )
endif() 

# ==============================================================================
# Set Dependences
# ==============================================================================

set(binDir "${CMAKE_SOURCE_DIR}/bin")
set(srcDir "${CMAKE_SOURCE_DIR}/src")
set(uuidDir "${srcDir}/fmu-uuids")
set(FMI_VERSION "1.0")

#fmu-uuid
include(ExternalProject)
set(fmuUuidDir "${CMAKE_SOURCE_DIR}/external/fmu-uuid")
ExternalProject_Add(fmu-uuid
  #   GIT_REPOSITORY "https://github.com/viproma/fmu-uuid.git"
  DOWNLOAD_COMMAND ""
  CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}" "${extCmakeOpt}"
  SOURCE_DIR "${fmuUuidDir}"
  )
set(fmuUuidCommand "${binDir}/fmu-uuid")

# ==============================================================================
# FMUs
# ==============================================================================

# Creat targets

if(FMI_VERSION MATCHES "2.0")
  # CPPFMU2
  file(GLOB cppfmu "${CMAKE_SOURCE_DIR}/../cppfmu2/*.?pp")  
  set(fmuIncludeDirs
    "${CMAKE_SOURCE_DIR}/../cppfmu2/fmi2"
    "${CMAKE_SOURCE_DIR}/../cppfmu2"
    "${uuidDir}"
    )
  set(fmuDir "fmu20")
  add_definitions(-D_FMI2)
elseif(FMI_VERSION MATCHES "1.0")
  # CPPFMU
  file(GLOB cppfmu "${CMAKE_SOURCE_DIR}/../cppfmu/*.?pp")
  set(fmuIncludeDirs
    "${CMAKE_SOURCE_DIR}/../cppfmu/fmi"
    "${CMAKE_SOURCE_DIR}/../cppfmu"
    "${uuidDir}"
    )
  set(fmuDir "fmu10")
  add_definitions(-D_FMI1)
else()
  message(FATAL_ERROR "Unknown or unsupported FMI vserion: ${FMI_VERSION}")
endif()
  
set(FMU_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/${fmuDir}" CACHE PATH "Where to put the generated FMU contents")

# Prepare names for FMU output directories.
if(CMAKE_CONFIGURATION_TYPES)
    set(fmuFullOutputDir "${FMU_OUTPUT_DIR}/$<CONFIGURATION>")
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "release")
    endif()
    set(fmuFullOutputDir "${FMU_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}")
endif()

set(fmuList "sine" "cpipe")

foreach(fmu IN LISTS fmuList)
  set(dlTarget "${fmu}")
  set(uuidTarget "${fmu}_uuid")
  set(fmuTarget "${fmu}_fmu")
  set(sourceDir "${srcDir}/${fmuDir}/${fmu}")
  set(outputDir "${fmuFullOutputDir}/${fmu}")
  set(binariesDir "${outputDir}/binaries/${fmuPlatform}")
  set(sourceModelDescription "${sourceDir}/modelDescription.xml")
  # Target to generate UUID
  set(outputModelDescription "${uuidDir}/${fmu}-modelDescription.xml")
  set(outputUuidHeader "${uuidDir}/${fmu}-fmu-uuid.h")
  add_custom_command(
    OUTPUT "${outputModelDescription}" "${outputUuidHeader}"
    COMMAND
    "${CMAKE_COMMAND}" "-E" "make_directory" "${uuidDir}"
    COMMAND
    "${fmuUuidCommand}"
    "${sourceModelDescription}"
    "@FMU_UUID@"
    "${outputModelDescription}"
    "${outputUuidHeader}"
    "FMU_UUID"
    DEPENDS "${sourceModelDescription}"
    VERBATIM
    )
  add_custom_target(${uuidTarget}
    DEPENDS fmu-uuid "${outputModelDescription}" "${outputUuidHeader}"
    )
  # Target to build dynamic library
  add_library(${dlTarget} MODULE
    "${sourceDir}/${fmu}.cpp"
    "${cppfmu}"
    "${sourceModelDescription}")
  if (os MATCHES "darwin")
    set_target_properties(${dlTarget}
      PROPERTIES PREFIX ""
      SUFFIX ".dylib"
      ) 
  elseif (os MATCHES "win")
    set_target_properties(${dlTarget}
      PROPERTIES PREFIX ""
      SUFFIX ".dll"
      ) 
  endif()
  # Boost dependence
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${dlTarget} ${Boost_LIBRARIES})
  if(FMU_USE_STATIC_RUNTIME)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_RUNTIME ON)
  else()
	set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_STATIC_RUNTIME OFF)
  endif() 
  set(Boost_USE_MULTITHREADED ON)  
  if(MINGW)
    target_link_libraries(${dlTarget} boost_system-mt)
	target_link_libraries(${dlTarget} boost_filesystem-mt)
    target_link_libraries(${dlTarget} ws2_32)
  else()
    find_package(Boost REQUIRED COMPONENTS system filesystem)
  endif()
  set_target_properties(${dlTarget} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${fmuPlatform}")
  add_dependencies(${dlTarget} ${uuidTarget})
  if ("${dlTarget}" STREQUAL "cpipe")
     set(_cpipe_coreDir "${sourceDir}/_cpipe_core")
     ExternalProject_Add(_cpipe_core
     DOWNLOAD_COMMAND ""
     CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}"
     SOURCE_DIR "${_cpipe_coreDir}"
  )
set(fmuUuidCommand "${binDir}/fmu-uuid")
    add_dependencies(${dlTarget} "_cpipe_core")
  endif()
  target_compile_definitions(${dlTarget} PRIVATE
    "MODEL_IDENTIFIER=${fmu}")
  target_include_directories(${dlTarget} PRIVATE ${fmuIncludeDirs})

  # Target to generate FMU contents
  set(rule "${fmu}-fmu")
  add_custom_command(OUTPUT "${rule}"
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "make_directory" "${outputDir}/sources"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${sourceDir}" "${outputDir}/sources"
    COMMAND "${CMAKE_COMMAND}" "-E" "remove" "${outputDir}/sources/modelDescription.xml"   
    COMMAND "${CMAKE_COMMAND}" "-E" "make_directory" "${binariesDir}"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "$<TARGET_FILE:${dlTarget}>" "${binariesDir}/"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${outputModelDescription}" "${outputDir}/modelDescription.xml"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${outputUuidHeader}" "${outputDir}/sources/"
    COMMAND "${CMAKE_COMMAND}" "-E" "chdir" "${outputDir}" "zip" "-r" "${fmuFullOutputDir}/${fmu}.zip" "modelDescription.xml" "sources" "binaries"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${fmuFullOutputDir}/${fmu}.zip" "${fmuFullOutputDir}/${fmu}.fmu"
    COMMAND "${CMAKE_COMMAND}" "-E" "remove" "${fmuFullOutputDir}/${fmu}.zip"
    DEPENDS ${dlTarget} ${uuidTarget}
    VERBATIM)
  set_property(SOURCE "${rule}" PROPERTY SYMBOLIC TRUE)
  add_custom_target(${fmuTarget} ALL DEPENDS "${rule}")
endforeach()

source_group("Metadata" REGULAR_EXPRESSION "modelDescription.xml")
