# Install script for directory: /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/examples/sunmatrix/band/test_sunmatrix_band.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.h;/usr/local/examples/sunmatrix/band/sundials_matrix.c;/usr/local/examples/sunmatrix/band/sundials_nvector.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/examples/sunmatrix/band" TYPE FILE FILES
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/test_sunmatrix_band.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.h"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_matrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_nvector.c"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/examples/sunmatrix/band/test_sunmatrix_band.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.h;/usr/local/examples/sunmatrix/band/sundials_matrix.c;/usr/local/examples/sunmatrix/band/sundials_nvector.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/examples/sunmatrix/band" TYPE FILE FILES
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/test_sunmatrix_band.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.h"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_matrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_nvector.c"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/examples/sunmatrix/band/test_sunmatrix_band.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.h;/usr/local/examples/sunmatrix/band/sundials_matrix.c;/usr/local/examples/sunmatrix/band/sundials_nvector.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/examples/sunmatrix/band" TYPE FILE FILES
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/test_sunmatrix_band.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.h"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_matrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_nvector.c"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/examples/sunmatrix/band/test_sunmatrix_band.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.c;/usr/local/examples/sunmatrix/band/test_sunmatrix.h;/usr/local/examples/sunmatrix/band/sundials_matrix.c;/usr/local/examples/sunmatrix/band/sundials_nvector.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/examples/sunmatrix/band" TYPE FILE FILES
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/test_sunmatrix_band.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../test_sunmatrix.h"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_matrix.c"
    "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/examples/sunmatrix/band/../../../src/sundials/sundials_nvector.c"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/examples/sunmatrix/band/CMakeLists.txt")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/examples/sunmatrix/band" TYPE FILE FILES "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/build/examples/sunmatrix/band/CMakeLists.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/examples/sunmatrix/band/Makefile")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/examples/sunmatrix/band" TYPE FILE RENAME "Makefile" FILES "/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/build/examples/sunmatrix/band/Makefile_ex")
endif()

