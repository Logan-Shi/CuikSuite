# Install script for directory: /home/logan/Downloads/CuikSuite3/src/CuikBase

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
    set(CMAKE_INSTALL_CONFIG_NAME "DEBUG")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CuikSuite" TYPE FILE FILES
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/algebra.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/basic_algebra.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/boolean.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/box.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/box_heap.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/box_list.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/constants.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/csmapping.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/cuiksystem.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/defines.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/equation.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/equations.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/eqvector.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/error.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/filename.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/geom.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/heap.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/hessian.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/htransform.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/interval.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/interval_vector.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/jacobian.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/kequation.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/linear_constraint.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/list.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/mequation.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/monomial.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/nhessian.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/njacobian.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/parameters.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/random.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/readcuiksystemtypes.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/shtransform.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/simplex.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/statistics.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/trans_seq.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/variable.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/variable_set.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/variables.h"
    "/home/logan/Downloads/CuikSuite3/src/CuikBase/include/vector.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so.3.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so.3"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/logan/Downloads/CuikSuite3/lib/libcuik-common.so.3.1.0"
    "/home/logan/Downloads/CuikSuite3/lib/libcuik-common.so.3"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so.3.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so.3"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/usr/local/lib:"
           NEW_RPATH "/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so"
         RPATH "/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/logan/Downloads/CuikSuite3/lib/libcuik-common.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcuik-common.so")
    endif()
  endif()
endif()

