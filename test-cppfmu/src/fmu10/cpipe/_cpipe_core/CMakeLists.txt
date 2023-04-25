cmake_minimum_required(VERSION 2.8.12)

enable_language(Fortran)
enable_language(C)

GET_FILENAME_COMPONENT(Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} 
NAME)
MESSAGE("Fortran_COMPILER_NAME: " ${Fortran_COMPILER_NAME})

if(WIN32)
   set(destDir "$ENV{HOMEPATH}/bin")
else()
   set(destDir "$ENV{HOME}/bin")
endif()

if(MINGW)
  set(CMAKE_C_FLAGS "${CMAKED_C_FLAGS} -DMINGW")
endif()

if (Fortran_COMPILER_NAME MATCHES "gfortran.*")
  # gfortran
  set (CMAKE_Fortran_FLAGS_RELEASE "${FOPTs} -funroll-all-loops -fno-f2c -O3")
  set (CMAKE_Fortran_FLAGS_DEBUG   "${FOPTs} -fno-f2c -O0 -g")
elseif (Fortran_COMPILER_NAME MATCHES "ifort.*")
  # ifort (untested)
  set (CMAKE_Fortran_FLAGS_RELEASE "${FOPTs} -f77rtl -O3")
  set (CMAKE_Fortran_FLAGS_DEBUG   "${FOPTs} -f77rtl -O0 -g")
elseif (Fortran_COMPILER_NAME MATCHES "g77")
  # g77
  set (CMAKE_Fortran_FLAGS_RELEASE "${FOPTs} -funroll-all-loops -fno-f2c -O3 -m32")
  set (CMAKE_Fortran_FLAGS_DEBUG   "${FOPTs} -fno-f2c -O0 -g -m32")
else (Fortran_COMPILER_NAME MATCHES "gfortran.*")
  message ("CMAKE_Fortran_COMPILER full path: " ${CMAKE_Fortran_COMPILER})
  message ("Fortran compiler: " ${Fortran_COMPILER_NAME})
  message ("No optimized Fortran compiler flags are known, we just try -O2...")
  set (CMAKE_Fortran_FLAGS_RELEASE "${FOPTs} -O2")
  set (CMAKE_Fortran_FLAGS_DEBUG   "${FOPTs} -O0 -g")
endif (Fortran_COMPILER_NAME MATCHES "gfortran.*")

project(_cpipe_core Fortran)
#file(GLOB _cpipe_core_fsrc "${CMAKE_SOURCE_DIR}/*.f")
#file(GLOB _cpipe_core_csrc "/*.c")
set(src ${CMAKE_SOURCE_DIR})
add_executable(_cpipe_core "${src}/cpipe_core.f" 
                           "${src}/solstep.f" "${src}/setmat.f"
                           "${src}/heprop.f" "${src}/util.f" 
						   "${src}/fio.f" "${src}/cio.c") 
add_executable(cpipe_test "${src}/cpipe_test.f" 
                          "${src}/solstep.f" "${src}/setmat.f"
                          "${src}/heprop.f" "${src}/fio.f")         

target_include_directories(_cpipe_core PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(cpipe_test PRIVATE ${CMAKE_SOURCE_DIR})
if (APPLE)
  target_link_libraries(_cpipe_core lapack)
  target_link_libraries(cpipe_test lapack)
else()
  target_link_libraries(_cpipe_core openblas)
  target_link_libraries(cpipe_test openblas)
endif()
set_target_properties(_cpipe_core PROPERTIES LINKER_LANGUAGE Fortran)
set_target_properties(cpipe_test PROPERTIES LINKER_LANGUAGE Fortran)

add_custom_command(OUTPUT testin
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${src}/test.in" "${destDir}"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${src}/test1.in" "${destDir}"
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${src}/test2.in" "${destDir}"
    DEPENDS _cpipe_core
    VERBATIM)   
set_property(SOURCE testin PROPERTY SYMBOLIC TRUE)
add_custom_target(copy_testin ALL DEPENDS testin)
  
install(TARGETS "_cpipe_core" RUNTIME DESTINATION ${destDir})
install(TARGETS "cpipe_test" RUNTIME DESTINATION ${destDir})

