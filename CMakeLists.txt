# Pre-requisites about cmake itself
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0005 NEW) 
  cmake_policy(SET CMP0003 NEW) 
  cmake_policy(SET CMP0012 NEW) 
endif(COMMAND cmake_policy)

# ---------------------------------------------------------------------------

# User settings to configure the CuikSuite package

# CuikSuite compiling options: Set to 'on' or to 'off' to select the components of the suite to be compiled
# The more the off's the less the dependencies but also the less the functionalities provided by the suite.
# When all options are set to off you still will need a simplex library (Clp), flex, bison, some numerical libraries
# (lapck and cblas or gls). This is the minimum set of dependencies for the CuikSuite.
# The default is to compile with all the extra functionalities (and extra dependencies).
# Set CuikSuite_on_grid to on to compile only the cuik solver (with the minim set of dependencies).
#
OPTION(CuikSuite_on_grid "To compile only the cuik solver for execution in a grid" off)
OPTION(CuikSuite_Parallel_Cluster "Multi-core parallel execution via MPI." on)

# The options below are not used if CuikSuite_on_grid is 'on'
IF (CuikSuite_on_grid)

  IF (NOT CuikSuite_Parallel_Cluster)
    MESSAGE(FATAL_ERROR "MPI (CuikSuite_Parallel_Cluster) must be ON to execute cuik on a cluster")
  ENDIF (NOT CuikSuite_Parallel_Cluster)
  IF (CuikSite_Parallel_SharedMem)
    MESSAGE(FATAL_ERROR "OpenMP (CuikSite_Parallel_SharedMem) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSite_Parallel_SharedMem)
  IF (CuikSuite_kdtree)
    MESSAGE(FATAL_ERROR "Kdtree (CuikSuite_kdtree) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_kdtree) 
  IF (CuikSuite_Import3dModels)
    MESSAGE(FATAL_ERROR "Assimp import (CuikSuite_Import3dModels) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_Import3dModels)
  IF (CuikSuite_Bio)
    MESSAGE(FATAL_ERROR "Bio (CuikSuite_Bio) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_Bio) 
  IF (CuikSuite_ROS)
    MESSAGE(FATAL_ERROR "ROS (CuikSuite_ROS) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_AlternativeCD) 
  IF (CuikSuite_AlternativeCD)
    MESSAGE(FATAL_ERROR "Collision detection (CuikSuite_AlternativeCD) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_AlternativeCD) 
  IF (CuikSuite_GUI)
    MESSAGE(FATAL_ERROR "Graphical interface (CuikSuite_GUI) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_GUI) 
  IF (CuikSuite_Doc)
    MESSAGE(FATAL_ERROR "Documentation (CuikSuite_Doc) must be OFF to execute cuik on a cluster")
  ENDIF (CuikSuite_Doc)
  
ELSE (CuikSuite_on_grid)

  OPTION(CuikSite_Parallel_SharedMem "Single-machine parallel execution via OpenMP." on)
  OPTION(CuikSuite_kdtree                    "Kd-tree nearest-neighbour for path planning." on)
  OPTION(CuikSuite_Import3dModels    "3D model import via assymp." on)
  OPTION(CuikSuite_Bio                         "To manipulate molecular information via OpenMP" on)
  OPTION(CuikSuite_ROS                       "To imort URDF (ROS) files via tinyxml2." on)
  OPTION(CuikSuite_AlternativeCD        "To integrate additional collision detection engines (vcollide, pqp, fcl, rigidCLL, bullet)" on)
  OPTION(CuikSuite_GUI                        "To compile the CuikSuite GUI"  on)
  OPTION(CuikSuite_Doc                       "To include the commands to generate the documentation" on)
  
ENDIF (CuikSuite_on_grid)

# ---------------------------------------------------------------------------

  # Debug level
  # Moreover, if DEBUG>0 executable include debug information (and the larger the more the information printed).
  # Note that some modules have their own debug flag (e.g., DEBUG_RANDOM, ATLAS_VERBOSE, ATLASRRT_VERBOSE,
  # RRT_VERBOSE,  DEBUG_HandC). They are set in terms of the DEBUG flag, but they can be
  # activated separately if necessary.
  #
  # Note that numerical libraries (e.g. BLAS) introduce some randomness in the evaluation of
  # floating point expressions due to the rounding and the random order of additions (see
  # https://bebop.cs.berkeley.edu/reproblas for more details). Thus, for DEBUG larger than 1
  # BLAS is not used to enhance replicability.
  
    SET(DEBUG 0)

# ---------------------------------------------------------------------------
# Nothing to be set beyond this point

# this avoid the use of clang in Mac OS X (must be set before the PROJECT)
# clang does not support OMP
SET(CMAKE_CXX_COMPILER g++-9)
SET(CMAKE_C_COMPILER gcc-9)

# The project name and the type of project
PROJECT(cuiksuite C CXX)

# rpath
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH ${CMPAKE_CURRENT_SOURCE_DIR}/lib)
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# where to store executable and libraries
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# non-standard cmake modules are stored in share directory
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/share)

# Information about the software package defined in the project
SET(VERSION_MAJOR 3)
SET(VERSION_MINOR 1)
SET(VERSION_PATCH 0)
SET(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "DEBUG")
ENDIF(NOT CMAKE_BUILD_TYPE)

MESSAGE("Building a ${CMAKE_BUILD_TYPE} version")

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  SET(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Wno-implicit-fallthrough -Wno-sign-compare -Wno-unused-parameter -Wno-deprecated-declarations -Wno-self-assign-overloaded -Wno-unknown-pragmas -Wno-unused-function -fPIC ")
  SET(CMAKE_C_FLAGS_RELEASE "-O3 -fPIC") 
  SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Wno-implicit-fallthrough -Wno-sign-compare -Wno-unused-parameter -Wno-deprecated-copy -Wno-class-memaccess -Wno-deprecated-declarations -Wno-self-assign-overloaded -Wno-unknown-pragmas -Wno-unused-function -fPIC")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC")
ELSE( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  SET(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Wno-implicit-fallthrough -Wno-sign-compare -Wno-unused-parameter -Wno-deprecated-declarations -Wno-self-assign-overloaded -Wno-unknown-pragmas -Wno-unused-function ")
  SET(CMAKE_C_FLAGS_RELEASE "-O3") 
  SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-deprecated-copy -Wno-class-memaccess -Wno-deprecated-declarations -Wno-self-assign-overloaded -Wno-unknown-pragmas -Wno-unused-function ")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")

# include/libs for software installed via macports
IF(APPLE)
  INCLUDE_DIRECTORIES(/opt/local/include) 
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib) 
ENDIF(APPLE)

# to avoid problems with shared ojects in mac os x (this accepts
# the global, uninitialized definitions used by bison and flex
SET(CMAKE_C_FLAGS "-fno-common ${CMAKE_C_FLAGS}")

# Install instructions for the default parameter file
INSTALL(FILES share/CuikSuite/default.param DESTINATION share/CuikSuite)

# Current folder. Necessary to define filenames. 
# Install folder. Necessary to find the default param file after make install
IF(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} LESS 5)
  ADD_DEFINITIONS(-D_CUIK_SUITE_MAIN_DIR="\\"${CMAKE_SOURCE_DIR}\\"")
  ADD_DEFINITIONS(-D_PARAM_PREFIX="\\"${CMAKE_INSTALL_PREFIX}\\"")
ELSE(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} LESS 5)
  ADD_DEFINITIONS(-D_CUIK_SUITE_MAIN_DIR=\"${CMAKE_SOURCE_DIR}\")
  ADD_DEFINITIONS(-D_PARAM_PREFIX=\"${CMAKE_INSTALL_PREFIX}\")
ENDIF(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} LESS 5)


# External programs used in the CuikSuite compilation
FIND_PROGRAM(bison bison)
IF(bison)
  MESSAGE("-- Found Bison: ${bison}")
ELSE(bison)
  MESSAGE("-- Bison is missing")
ENDIF(bison)

FIND_PROGRAM(flex flex)
IF(flex)
  MESSAGE("-- Found Flex: ${flex}")
ELSE(flex)
  MESSAGE("-- Flex is missing")
ENDIF(flex)

# General compilation flags
ADD_DEFINITIONS(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_DEBUG=${DEBUG})

#################################################
#################################################

# Find libraries used in different parts of the CuikSuite


###########
# Check which simplex library is available (some simplex library is always required)
# Available simplex engines
#  The COmputational INfrastructure for Operations Research Solver (http://www.coin-or.org/)
     SET(CLP 0)
#  The GNU linear programming toolkit (http://www.gnu.org/software/glpk/)
     SET(GLPK 1)
#  Lp solve http://sourceforge.net/projects/lpsolve
     SET(LP_SOLVE 2) 
#  Gurobi linear solver http://www.gurobi.com
     SET(GUROBI 3)

# default simplex engine = not found
SET(SIMPLEX_ENGINE 4)
  
# We search from them in order for the better option to the worst.
FIND_LIBRARY(clp_simplex Clp)
IF(clp_simplex)
  FIND_LIBRARY(coin_utils CoinUtils)
  IF(NOT coin_utils)
    MESSAGE("-- CoinUtils library missing (but clp found?)")
  ENDIF(NOT coin_utils)
  MESSAGE("-- Found Simplex library: ${clp_simplex}, ${coin_utils}")
  SET(SIMPLEX_ENGINE ${CLP}) 
  FIND_PATH(simplex_includes coin/Clp_C_Interface.h)
ELSE(clp_simplex)
  FIND_LIBRARY(gurobi_simplex gurobi60)
  IF(gurobi_simplex)
    MESSAGE("-- Found Gurobi library: ${gurobi_simplex}")
    SET(SIMPLEX_ENGINE ${GUROBI}) 
    FIND_PATH(simplex_includes gurobi_c.h)
  ELSE(gurobi_simplex)
    FIND_LIBRARY(glpx_simplex glpk)
    IF(glpx_simplex)
      MESSAGE("-- Found Simplex: ${glpx_simplex}")
      SET(SIMPLEX_ENGINE ${GLPK}) 
      FIND_PATH(simplex_includes glpk.h)
    ELSE(glpx_simplex)
      FIND_LIBRARY(lps_simplex lpsolve)
      IF(lps_simplex)
        MESSAGE("-- Found Simplex ${lps_simplex}")
        SET(SIMPLEX_ENGINE ${LP_SOLVE}) 
        FIND_PATH(simplex_includes lp_solve/lp_lib.h)
      ELSE(lps_simplex)
        MESSAGE(FATAL_ERROR "-- Simplex library is missing")
      ENDIF(lps_simplex)
    ENDIF(glpx_simplex)
  ENDIF(gurobi_simplex) 
ENDIF(clp_simplex)

IF(simplex_includes)
  MESSAGE("-- Found Simplex includes: ${simplex_includes}")
  INCLUDE_DIRECTORIES(${simplex_includes})
ELSE(simplex_includes)
  MESSAGE(FATAL_ERROR "-- Simplex includes missing")
ENDIF(simplex_includes)

ADD_DEFINITIONS(-D_LP_SOLVE=${LP_SOLVE} -D_GLPK=${GLPK} -D_CLP=${CLP} -D_GUROBI=${GUROBI} -D_SIMPLEX_ENGINE=${SIMPLEX_ENGINE})

IF (CuikSuite_on_grid)
  # In our grid we have a mix of 32 and 64 bits installations. The side effect is that
  # we can not rely on system libraries. We can only use the libraries we compiled
  # in 32 bits and that are shared for all the machines in the grid. GSL is one of such
  # libraries (not blas o lapack)
  # This may be different in your grid.
  
  IF(${DEBUG} GREATER 1)
    MESSAGE(FATAL_ERROR "The DEBUG flag must be set to 0 or 1 to execute cuik on a cluster")
  ENDIF(${DEBUG} GREATER 1)

  FIND_LIBRARY(gsl gsl)
  IF(gsl)
    MESSAGE("-- Found GSL library: ${gsl}")
    FIND_PATH(gsl_includes gsl/gsl_linalg.h)
    MESSAGE("-- Found GSL includes: ${gsl_includes}")
    INCLUDE_DIRECTORIES(${gsl_includes})
    ADD_DEFINITIONS(-D_GSL)
    IF(${DEBUG} LESS 2)
      ADD_DEFINITIONS(-DHAVE_INLINE -DGSL_RANGE_CHECK_OFF)
    ENDIF(${DEBUG} LESS 2)
  ELSE(gsl)
    MESSAGE(FATAL_ERROR "-- GSL library is missing") 
  ENDIF(gsl)
      
  FIND_LIBRARY(gslcblas gslcblas)
  IF(gslcblas)
    MESSAGE("-- Found CBLAS library: ${gslcblas}")
    FIND_PATH(gslcblas_includes gsl/gsl_cblas.h)
    IF(gslcblas_includes)
      MESSAGE("-- Found CBLAS includes: ${gslcblas_includes}")
      INCLUDE_DIRECTORIES(${gslcblas_includes})
      ADD_DEFINITIONS(-D_CBLAS -D_GSL_CBLAS)
    ELSE(gslcblas_includes)
      MESSAGE("-- CBLAS includes missing")
    ENDIF(gslcblas_includes)
  ELSE(gslcblas)
    MESSAGE("-- CBLAS library is missing. Using naive numerical libraries.")
  ENDIF(gslcblas)
      
ELSE (CuikSuite_on_grid)
  ###########
  # Numerical libraries (some numerical library are always required)
  # In Mac OS X the library is libclapack
  # In Linux it is liblapacke
  # They provide the same service (C interface to lapack) but
  # the interface is different, we need to compile slightly different
  # code (different sets of defines)

  FIND_LIBRARY(clapack clapack)
  IF(clapack)
    MESSAGE("-- Found CLAPACK library: ${clapack}")
     FIND_PATH(clapack_includes clapack.h HINT /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/ /Library//Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/)
     MESSAGE("-- Found CLAPACK includes: ${clapack_includes}")
     INCLUDE_DIRECTORIES(${clapack_includes})
     ADD_DEFINITIONS(-D_LAPACK)
  ELSE(clapack)
     FIND_LIBRARY(clapacke lapacke)
     IF(clapacke)
       MESSAGE("-- Found LAPACKE library: ${clapacke}")
       FIND_PATH(clapacke_includes lapacke.h)
       MESSAGE("-- Found LAPACKE includes: ${clapacke_includes}")
       INCLUDE_DIRECTORIES(${clapacke_includes})
       ADD_DEFINITIONS(-D_LAPACK -D_LAPACKE)
     ELSE(clapacke)
       # If we do not have access to a lapack library. Try GSL
       # it is slower but may be easier to install.
       MESSAGE("-- CLAPACK library missing. Searching for GSL")
       FIND_LIBRARY(gsl gsl)
       IF(gsl)
         MESSAGE("-- Found GSL library: ${gsl}")
         FIND_PATH(gsl_includes gsl/gsl_linalg.h)
         MESSAGE("-- Found GSL includes: ${gsl_includes}")
         INCLUDE_DIRECTORIES(${gsl_includes})
         ADD_DEFINITIONS(-D_GSL)
         IF(${DEBUG} LESS 2)
           ADD_DEFINITIONS(-DHAVE_INLINE -DGSL_RANGE_CHECK_OFF)
         ENDIF(${DEBUG} LESS 2)
       ELSE(gsl)
         MESSAGE(FATAL_ERROR "-- Lapack/gsl library is missing") 
       ENDIF(gsl)
    ENDIF(clapacke)
   ENDIF(clapack)

  # In debug mode (larger than 1)
  IF(${DEBUG} LESS 2)
   # In Mac OS X the libaray is called libcblas
   # In Linux libblas
   FIND_LIBRARY(cblas cblas)
     IF(cblas)
       MESSAGE("-- Found CBLAS library: ${cblas}")
     ELSE(cblas)
       FIND_LIBRARY(blas blas)
       IF (blas)
        MESSAGE("-- Found CBLAS library: ${blas}")
       ENDIF(blas)
     ENDIF(cblas)
     IF(cblas OR blas)
       # the include file is the same in both linux and Mac OS X
       FIND_PATH(cblas_includes cblas.h HINT /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/ /Library//Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/)
       IF(cblas_includes)
         MESSAGE("-- Found CBLAS includes: ${cblas_includes}")
         INCLUDE_DIRECTORIES(${cblas_includes})
         ADD_DEFINITIONS(-D_CBLAS)
       ELSE(cblas_includes)
         MESSAGE("-- CBLAS includes missing")
       ENDIF(cblas_includes)
     ELSE(cblas OR blas)
       # If neither libcblas o libblas are installed
       # try with libgslcblas
       FIND_LIBRARY(gslcblas gslcblas)
       IF(gslcblas)
         MESSAGE("-- Found CBLAS library: ${gslcblas}")
         FIND_PATH(gslcblas_includes gsl/gsl_cblas.h)
         IF(gslcblas_includes)
           MESSAGE("-- Found CBLAS includes: ${gslcblas_includes}")
           INCLUDE_DIRECTORIES(${gslcblas_includes})
           ADD_DEFINITIONS(-D_CBLAS -D_GSL_CBLAS)
         ELSE(gslcblas_includes)
           MESSAGE("-- CBLAS includes missing")
         ENDIF(gslcblas_includes)
       ELSE(gslcblas)
         MESSAGE("-- CBLAS library is missing. Using naive numerical libraries.")
       ENDIF(gslcblas)
     ENDIF(cblas OR blas)
   ELSE(${DEBUG} LESS 2)
     MESSAGE("-- CBLAS not used to facilitate replicability in DEBUG mode. Using naive numerical libraries.") 
   ENDIF(${DEBUG} LESS 2)


ENDIF(CuikSuite_on_grid)


 ########### 
  # expokit libraries (computation of matrix exponential)
  FIND_LIBRARY(expokit expokit)
  IF (expokit)
     MESSAGE("-- Found EXPOKIT library: ${expokit}")
     ADD_DEFINITIONS(-D_EXPOKIT)
  ELSE(expokit)
     MESSAGE("-- EXPOKIT library is missing")
  ENDIF(expokit)


###########
# Parallel execution in different machines, i.e. non-shared memory (for the cuik command only)
IF(CuikSuite_Parallel_Cluster)
  FIND_LIBRARY(mpi mpi HINTS /opt/local/lib/openmpi-gcc48 /opt/local/lib/openmpi-devel-gcc5 /opt/local/lib/openmpi-mp)
  IF(mpi)
    MESSAGE("-- Found MPI library: ${mpi}")

    FIND_PATH(mpi_includes mpi/mpi.h)
    IF(NOT mpi_includes)
      FIND_PATH(mpi_includes mpi.h HINTS /opt/local/include/openmpi-devel-gcc5)
    ENDIF(NOT mpi_includes)

    # just in case it is installed via mac ports
    IF(NOT mpi_includes)
      FIND_PATH(mpi_includes openmpi-gcc48/mpi.h)
    ENDIF(NOT mpi_includes)
    IF(NOT mpi_includes)
      FIND_PATH(mpi_includes openmpi-mp/mpi.h)
    ENDIF(NOT mpi_includes)

    IF(mpi_includes)
      MESSAGE("-- Found MPI includes: ${mpi_includes}")
      INCLUDE_DIRECTORIES(${mpi_includes}) 
      SET(USE_MPI 1)
      SET(CMAKE_C_COMPILER "mpicc")
    ELSE(mpi_includes) 
      MESSAGE("-- MPI includes not available??. Compiling in single machine mode.")
      SET(USE_MPI 0) 
      SET(CMAKE_C_COMPILER "gcc")
    ENDIF(mpi_includes)
  ELSE(mpi)
    MESSAGE("-- MPI library not available. Compiling in single machine mode.")
    SET(USE_MPI 0)
    SET(CMAKE_C_COMPILER "gcc")
  ENDIF(mpi)
ELSE(CuikSuite_Parallel_Cluster)
  MESSAGE("-- Compiling without MPI ")
  SET(USE_MPI 0) 
ENDIF(CuikSuite_Parallel_Cluster)

ADD_DEFINITIONS(-D_USE_MPI=${USE_MPI})

# From this point, the libraries for other parts of the suite beyond the basic cuik solver
IF (NOT CuikSuite_on_grid)

  ###########
  # Parallel execution in the same machine (cuikatlas,cuikatlasA*,cuikrrt*,cuikatlasrrt*,cuiksmoothpath)
   IF(CuikSite_Parallel_SharedMem)
   #IF(APPLE)
   # FIND_PACKAGE(OPENMP)
   #ELSE(APPLE) 
    FIND_PACKAGE(OpenMP)
   #ENDIF(APPLE)
    IF (OPENMP_FOUND)
      MESSAGE("-- Found OpenMP:  ${OpenMP_C_FLAGS}")
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ELSE(OPENMP_FOUND)
      MESSAGE("-- OpenMP missing")
    ENDIF(OPENMP_FOUND)
   ELSE(CuikSite_Parallel_SharedMem)
    MESSAGE("-- Compiling without OpenMP")
   ENDIF(CuikSite_Parallel_SharedMem)


  ###########
  # kd-tree search and sample
   IF(CuikSuite_kdtree)
    FIND_LIBRARY(cuik_kdtree cuik-kdtree)
    IF (cuik_kdtree)
      FIND_PATH(cuik_kdtree_includes cuik-kdtree/cuik-kdtree.h)
      IF (cuik_kdtree_includes)
        MESSAGE("-- Found Cuik-kdtree library: ${cuik_kdtree}")
        MESSAGE("-- Found Cuik-kdtree includes: ${cuik_kdtree_includes}") 
        INCLUDE_DIRECTORIES(${cuik_kdtree_includes}) 
         SET(btree btree.c)
        ADD_DEFINITIONS(-D_KDTREE=1)
      ELSE (cuik_kdtree_includes)
         MESSAGE("-- Cuik-kdtree includes not found. Kd-tree searches (path planning) won't be used.") 
         ADD_DEFINITIONS(-D_KDTREE=0)
      ENDIF(cuik_kdtree_includes)
     ELSE(cuik_kdtree)
       FIND_LIBRARY(mpnn DNN)
       IF (mpnn) 
         FIND_PATH(mpnn_includes DNN/ANN_C.h) 
         IF (mpnn_includes)
            MESSAGE("-- Found MPNN library: ${mpnn}")
           MESSAGE("-- Found MPNN includes: ${mpnn_includes}")
            INCLUDE_DIRECTORIES(${mpnn_includes})
            SET(btree btree.c)
            ADD_DEFINITIONS(-D_KDTREE=2)
         ELSE(mpnn_includes) 
            MESSAGE("-- A wrong version of MPNN library detected. Kd-tree searches (path planning) won't be used.") 
            ADD_DEFINITIONS(-D_KDTREE=0)
         ENDIF(mpnn_includes)
       ELSE(dnn)
          MESSAGE("-- cuik-kdtree/MPNN libraries are missing. Kd-tree searches (path planning) won't be used.") 
          ADD_DEFINITIONS(-D_KDTREE=0)
       ENDIF(mpnn)
     ENDIF(cuik_kdtree)
   ELSE(CuikSuite_kdtree)
     MESSAGE("-- Compiling without Kd-tree") 
     ADD_DEFINITIONS(-D_KDTREE=0)
   ENDIF(CuikSuite_kdtree)


  ###########
  # 3d model import
  IF(CuikSuite_Import3dModels)
    FIND_LIBRARY(assimp assimp)
    IF(assimp)
      FIND_PATH(assimp_includes assimp/scene.h)
      IF(assimp_includes) 
        MESSAGE("-- Found Assimp library: ${assimp}")
        MESSAGE("-- Found Assimp includes: ${assimp_includes}") 
        INCLUDE_DIRECTORIES(${assimp_includes})
        ADD_DEFINITIONS(-D_ASSIMP=1)
      ELSE(assimp_includes)
        MESSAGE("-- Assimp includes not found. Only OFF and STL file will be read.") 
        ADD_DEFINITIONS(-D_ASSIMP=0)
      ENDIF(assimp_includes)
    ELSE(assimp)
      MESSAGE("-- Assimp library is missing. Only OFF and STL file will be read.") 
      ADD_DEFINITIONS(-D_ASSIMP=0)
    ENDIF(assimp)
  ELSE(CuikSuite_Import3dModels)
    MESSAGE("-- Compiling without the assimp 3d import library") 
    ADD_DEFINITIONS(-D_ASSIMP=0)
  ENDIF(CuikSuite_Import3dModels)


  ###########
  # To manipulate molecular information
  IF(CuikSuite_Bio)
    FIND_LIBRARY(babel openbabel)
    IF (babel)
      MESSAGE("-- Found OpenBabel library: ${babel}")
      FIND_PATH(babel_includes openbabel3)
      MESSAGE("-- Found OpenBabel includes: ${babel_includes}/openbabel3")
      INCLUDE_DIRECTORIES(${babel_includes}/openbabel3) 
    ELSE(babel)
      MESSAGE("-- OpenBabel library missing. libcuikbabel, cuikpdb2world, cuikenergy, cuikrmse, cuiksample2pdb, cuikpdb2sample, cuikatoms2samples, cuikbioatlastrrt, and cuikbiominimize won't be generated")
    ENDIF(babel)
  ELSE(CuikSuite_Bio)
    MESSAGE("-- Compiling without the molecular applications") 
  ENDIF(CuikSuite_Bio)


  ###########
  # To parse xml files (in particular urdf ROS files).
  IF(CuikSuite_ROS)
    FIND_LIBRARY(xml tinyxml2)
    IF(xml)
      MESSAGE("-- Found Tinyxml2 library: ${xml}")
      FIND_PATH(xml_includes tinyxml2.h)
      MESSAGE("-- Found Tinyxml2 includes: ${xml_includes}")
      INCLUDE_DIRECTORIES(${xml_includes})
    ELSE(xml)
      MESSAGE("-- Tinyxml2 library missing. cuikurdf2world won't be generated")
    ENDIF(xml)
  ELSE(CuikSuite_ROS)
    MESSAGE("-- Compiling without the ROS/URDF interface") 
  ENDIF(CuikSuite_ROS)


  ########### 
  # Collision detection libraries (always required)
  FIND_LIBRARY(solid solid)
  IF (solid)
     MESSAGE("-- Found SOLID library: ${solid}")
     FIND_PATH(solid_includes solid/SOLID.h)
     MESSAGE("-- Found SOLID includes: ${solid_includes}")
     INCLUDE_DIRECTORIES(${solid_includes})
     ADD_DEFINITIONS(-D_HAVE_SOLID)
  ELSE(solid)
     MESSAGE("-- SOLID library is missing")
  ENDIF(solid)


  ###########
  IF(CuikSuite_AlternativeCD)
    FIND_LIBRARY(vcollide VCollide)
    IF (vcollide)
       MESSAGE("-- Found VCollide library: ${vcollide}")
       FIND_PATH(vcollide_includes VCollide.H)
       MESSAGE("-- Found VCollide includes: ${vcollide_includes}")
       INCLUDE_DIRECTORIES(${vcollide_includes})
    
       # Vcollide requires rapid
       FIND_LIBRARY(rapid RAPID)
       IF (rapid)
          MESSAGE("-- Found RAPID library: ${rapid}")
          ADD_DEFINITIONS(-D_HAVE_VCOLLIDE) 
       ELSE(rapid)
          MESSAGE("-- RAPID library is missing")
       ENDIF(rapid)
  
    ELSE(vcollide)
       MESSAGE("-- VCollide library is missing")
    ENDIF(vcollide)
  
    ###########
    FIND_LIBRARY(pqp PQP)
    IF (pqp)
       MESSAGE("-- Found PQP library: ${pqp}")
       FIND_PATH(pqp_includes PQP/PQP.h)
       MESSAGE("-- Found PQP includes: ${pqp_includes}")
       INCLUDE_DIRECTORIES(${pqp_includes})
       ADD_DEFINITIONS(-D_HAVE_PQP)
    ELSE(pqp)
       MESSAGE("-- PQP library is missing")
    ENDIF(pqp)
  
    ###########
    FIND_LIBRARY(fcl fcl)
    IF (fcl)
       MESSAGE("-- Found FCL library: ${fcl}")
       FIND_LIBRARY(ccd ccd)
       IF (ccd)
         MESSAGE("-- Found CCD library: ${ccd}")
       ELSE(ccd) 
         MESSAGE("-- CCD library is missing")
       ENDIF(ccd)
    ELSE (fcl)
       MESSAGE("-- FCL library is missing")
    ENDIF (fcl)
  
    FIND_LIBRARY(bs boost_system-mt)
    IF (NOT bs)
      FIND_LIBRARY(bs boost_system)
    ENDIF (NOT bs)
    IF (bs)
       MESSAGE("-- Found Boost system library: ${bs}")
    ENDIF(bs)
  
    IF (fcl AND ccd AND bs)
       FIND_PATH(fcl_includes fcl/config.h)
       MESSAGE("-- Found FCL includes: ${fcl_includes}")
       INCLUDE_DIRECTORIES(${fcl_includes})
       ADD_DEFINITIONS(-D_HAVE_FCL)
       FIND_PATH(eigen_includes Eigen/Dense HINTS /usr/include/eigen3 /usr/local/include/eigen3)
       MESSAGE("-- Found eigen includes: ${eigen_includes}")
       INCLUDE_DIRECTORIES(${eigen_includes})

       SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=gnu++11")
       SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=gnu++11")
  
    ELSE(fcl AND ccd AND bs)
       MESSAGE("-- FCL, CCD or boost system libraries are missing")
    ENDIF(fcl AND ccd AND bs)
  
    ###########
    FIND_LIBRARY(bullet BulletCollision)
    FIND_LIBRARY(bulletLin LinearMath)
    IF (bullet AND bulletLin)
       MESSAGE("-- Found BULLET library: ${bullet} ${bulletLin}")
       FIND_PATH(bullet_includes btBulletCollisionCommon.h HINTS /usr/include/bullet /usr/local/include/bullet /opt/local/include/bullet)
       MESSAGE("-- Found BULLET includes: ${bullet_includes}")
       INCLUDE_DIRECTORIES(${bullet_includes})
       ADD_DEFINITIONS(-D_HAVE_BULLET)
       
       FIND_LIBRARY(hacd HACD)
       IF (hacd) 
         MESSAGE("-- Found HACD library: ${hacd}") 
         ADD_DEFINITIONS(-D_HAVE_HACD)
       ELSE(hacd) 
         MESSAGE("-- HACD library is missing")
       ENDIF(hacd)
       
    ELSE(bullet AND bulletLin) 
       MESSAGE("-- BULLET library is missing")
    ENDIF(bullet AND bulletLin) 
  
    ###########
    FIND_LIBRARY(rigidCLL RigidCLL)
    IF (rigidCLL)
       MESSAGE("-- Found RigidCLL library: ${rigidCLL}")
       FIND_PATH(rigidCLL_includes RigidCLL.h)
       MESSAGE("-- Found RigidCLL includes: ${rigidCLL_includes}")
       INCLUDE_DIRECTORIES(${rigidCLL_includes})
       ADD_DEFINITIONS(-D_HAVE_RIGIDCLL)
    ELSE(rigidCLL)
       MESSAGE("-- RigidCLL library is missing")
    ENDIF(rigidCLL)

  ELSE(CuikSuite_AlternativeCD)
    MESSAGE("-- Compiling without the alternative collision detection engines (vcollide,pqp,fcl,bullet,rigidCLL)") 
  ENDIF(CuikSuite_AlternativeCD)


  ###########
  # GUI libraries
  IF(CuikSuite_GUI)
    FIND_LIBRARY(glib glib-2.0)
    IF (glib)
      MESSAGE("-- Found glib library: ${glib}")
    ELSE(glib)
      MESSAGE("-- glib library missing")
    ENDIF (glib)

    FIND_LIBRARY(gtk gtk-x11-2.0)
    IF(NOT gtk)
      FIND_LIBRARY(gtk gtk-quartz-2.0)
    ENDIF(NOT gtk)
  
    IF (gtk)
      MESSAGE("-- Found gtk library: ${gtk}")
    ELSE(gtk)
      MESSAGE("-- gtk library missing")
    ENDIF (gtk)

    FIND_LIBRARY(gdk gdk-x11-2.0)
    IF(NOT gdk)
      FIND_LIBRARY(gdk gdk-quartz-2.0)
    ENDIF(NOT gdk)

    IF (gdk)
      MESSAGE("-- Found gdk library: ${gdk}")
    ELSE(gdk)
      MESSAGE("-- gdk library missing")
    ENDIF (gdk)

    IF (glib AND gtk AND gdk)
      
      FIND_LIBRARY(gobject gobject-2.0)
      FIND_LIBRARY(atk atk-1.0)
      FIND_LIBRARY(gdk_pixbuf gdk_pixbuf-2.0)
      IF (gobject AND atk AND gdk_pixbuf)
        MESSAGE("-- Found Gtk auxiliary libs: ${gobject}, ${atk}, ${gdk_pixbuf}")
      ELSE(gobject AND atk AND gdk_pixbuf)
        MESSAGE("-- Gtk auxiliary libraries missing (gobject, atk, gdk_pixbuf)")
      ENDIF(gobject AND atk AND gdk_pixbuf)
  
      IF(APPLE)
        # macports
        INCLUDE_DIRECTORIES(/opt/local/include/gtk-2.0)
        INCLUDE_DIRECTORIES(/opt/local/include/glib-2.0)
        INCLUDE_DIRECTORIES(/opt/local/include/glib-2.0/include)
        INCLUDE_DIRECTORIES(/opt/local/lib/glib-2.0/include)
        INCLUDE_DIRECTORIES(/opt/local/lib/gtk-2.0/include)
        INCLUDE_DIRECTORIES(/opt/local/include/gdk-2.0/gdk)
        INCLUDE_DIRECTORIES(/opt/local/include/cairo)
        INCLUDE_DIRECTORIES(/opt/local/include/pango-1.0)
        INCLUDE_DIRECTORIES(/opt/local/include/atk-1.0) 
        INCLUDE_DIRECTORIES(/opt/local/include/gdk-pixbuf-2.0) 
        INCLUDE_DIRECTORIES(/opt/local/include/harfbuzz)

        # homebrew
        INCLUDE_DIRECTORIES(/usr/local/include/gtk-2.0)
        INCLUDE_DIRECTORIES(/usr/local/include/glib-2.0)
        INCLUDE_DIRECTORIES(/usr/local/include/glib-2.0/include)
        INCLUDE_DIRECTORIES(/usr/local/lib/glib-2.0/include)
        INCLUDE_DIRECTORIES(/usr/local/lib/gtk-2.0/include)
        INCLUDE_DIRECTORIES(/usr/local/include/gdk-2.0/gdk)
        INCLUDE_DIRECTORIES(/usr/local/include/cairo)
        INCLUDE_DIRECTORIES(/usr/local/include/pango-1.0)
        INCLUDE_DIRECTORIES(/usr/local/include/atk-1.0) 
        INCLUDE_DIRECTORIES(/usr/local/include/gdk-pixbuf-2.0) 
        INCLUDE_DIRECTORIES(/usr/local/include/harfbuzz)
      ELSE(APPLE)
        # assuming linux
        INCLUDE_DIRECTORIES(/usr/lib/x86_64-linux-gnu/glib-2.0/include)
        INCLUDE_DIRECTORIES(/usr/lib/i386-linux-gnu/glib-2.0/include) 
        INCLUDE_DIRECTORIES(/usr/lib/x86_64-linux-gnu/gtk-2.0/include)
        INCLUDE_DIRECTORIES(/usr/lib/i386-linux-gnu/gtk-2.0/include)
        INCLUDE_DIRECTORIES(/usr/include/gdk-pixbuf-2.0)
        INCLUDE_DIRECTORIES(/usr/include/gtk-2.0)
        INCLUDE_DIRECTORIES(/usr/include/glib-2.0)
        INCLUDE_DIRECTORIES(/usr/include/glib-2.0/include)
        INCLUDE_DIRECTORIES(/usr/lib/glib-2.0/include)
        INCLUDE_DIRECTORIES(/usr/lib/gtk-2.0/include)
        INCLUDE_DIRECTORIES(/usr/include/gdk-2.0/gdk)
        INCLUDE_DIRECTORIES(/usr/include/cairo)
        INCLUDE_DIRECTORIES(/usr/include/pango-1.0)
        INCLUDE_DIRECTORIES(/usr/include/atk-1.0) 
        INCLUDE_DIRECTORIES(/usr/include/harfbuzz)
      ENDIF(APPLE)
    ELSE (glib AND gtk AND gdk)
      MESSAGE("-- Compiling without the CuikSuite GUI (glib, gtk or gdk missing)") 
    ENDIF  (glib AND gtk AND gdk) 
  ELSE(CuikSuite_GUI)
    MESSAGE("-- Compiling without the CuikSuite GUI") 
  ENDIF(CuikSuite_GUI)
  
  ###########
  # include/libs for locally installed sofware
  IF(UNIX OR APPLE)
    INCLUDE_DIRECTORIES(/usr/local/include)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
  ENDIF(UNIX OR APPLE) 

  ###########
  # documentation commands
  IF(CuikSuite_Doc)
    FIND_PACKAGE(Doxygen)
    IF(DOXYGEN_FOUND)
      MESSAGE("-- Found Doxygen: ${DOXYGEN_EXECUTABLE}")
      ADD_CUSTOM_TARGET (doc cd ..\;${DOXYGEN_EXECUTABLE} doc/doxygen.conf\;cp doc/style/menu.js doc/html)
    ENDIF(DOXYGEN_FOUND)
  ELSE(CuikSuite_Doc)
    MESSAGE("-- Compiling without the documentation generation commands") 
  ENDIF(CuikSuite_Doc)

  INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt DESTINATION share/doc/CuikSuite)
  INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/license.txt DESTINATION share/doc/CuikSuite)

  ###########
  # Instruction to generate debian packages
  SET(CPACK_PACKAGE_NAME ${PROJECT_NAME})
  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CuikSuite, the motion analysis library.")
  SET(CPACK_PACKAGE_DESCRIPTION "The CuikSuite, a motion analysis library developed by the KRD group at IRI.")
  SET(CPACK_PACKAGE_VENDOR "The Kinematics and Robot Design group at IRI")
  SET(CPACK_PACKAGE_CONTACT "Josep M Porta <porta@iri.upc.edu>")
  SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
  SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
  SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/license.txt")
  SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
  SET(CPACK_STRIP_FILES TRUE)
  # deb packages
  SET(CPACK_GENERATOR "DEB")
  SET(CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}")
  SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://www.iri.upc.edu/cuik")
  FIND_PROGRAM(DPKG_PROGRAM dpkg)
  IF(DPKG_PROGRAM)
    EXECUTE_PROCESS(
      COMMAND ${DPKG_PROGRAM} --print-architecture
      OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_DEBIAN_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")  
  ELSE(DPKG_PROGRAM)
    SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_DEBIAN_PACKAGE_VERSION}_${CMAKE_SYSTEM_NAME}")
  ENDIF(DPKG_PROGRAM)

  SET(CPACK_DEBIAN_PACKAGE_SECTION "Science")

  SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS "xfig, geomview, tcsh")
  SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
 
  INCLUDE(CPack)

# end of the extra libraries (not used for the basic cuik solver)
ENDIF(NOT CuikSuite_on_grid)

# ----------------------------
# Tell CMake to process the sub-directories 
ADD_SUBDIRECTORY(src)
# ----------------------------

ADD_CUSTOM_TARGET (distclean @echo cleaning cmake files)

# install, uninstall commands

IF (UNIX OR APPLE)  
  ADD_CUSTOM_COMMAND(
    COMMENT "distribution clean"
    COMMAND make ARGS clean
    COMMAND rm ARGS -rf ${CMAKE_SOURCE_DIR}/build/*
    TARGET  distclean
  )
ELSE(UNIX OR APPLE)
  ADD_CUSTOM_COMMAND(
    COMMENT "distclean only implemented in Unix/Apple"
    TARGET  distclean
  )
ENDIF(UNIX OR APPLE)

ADD_CUSTOM_TARGET (uninstall @echo uninstall package)

IF (UNIX OR APPLE)
  ADD_CUSTOM_COMMAND(
    COMMENT "uninstall package"
    COMMAND xargs ARGS rm < install_manifest.txt
    TARGET  uninstall
  )
ELSE(UNIX OR APPLE)
  ADD_CUSTOM_COMMAND(
    COMMENT "uninstall only implemented in Unix/Apple"
    TARGET  uninstall
  )
ENDIF(UNIX OR APPLE)
