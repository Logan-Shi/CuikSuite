# Tell CMake to build a shared library from sources

SET(CUIK_BASE_DIR  ${CMAKE_SOURCE_DIR}/src/CuikBase)

INCLUDE_DIRECTORIES(${CUIK_BASE_DIR}/include)

SET(sources  box.c constants.c error.c list.c variables.c interval_vector.c
             box_list.c csmapping.c equation.c filename.c interval.c parameters.c  
             statistics.c variable_set.c cuiksystem.c equations.c geom.c algebra.c basic_algebra.c
             linear_constraint.c monomial.c random.c variable.c vector.c simplex.c
	     heap.c box_heap.c htransform.c eqvector.c shtransform.c
             trans_seq.c mequation.c kequation.c jacobian.c hessian.c
	     nhessian.c njacobian.c)

IF (${SIMPLEX_ENGINE} EQUAL ${GUROBI})
  SET(sources ${sources} simplex_gurobi.c)
ENDIF(${SIMPLEX_ENGINE} EQUAL ${GUROBI})

IF (${SIMPLEX_ENGINE} EQUAL ${CLP})
  SET(sources ${sources} simplex_clp.c)
ENDIF(${SIMPLEX_ENGINE} EQUAL ${CLP})

IF (${SIMPLEX_ENGINE} EQUAL ${GLPK})
  SET(sources ${sources} simplex_glpk.c)
ENDIF(${SIMPLEX_ENGINE} EQUAL ${GLPK})

IF (${SIMPLEX_ENGINE} EQUAL ${LP_SOLVE})
  SET(sources ${sources} simplex_lpsolve.c)
ENDIF(${SIMPLEX_ENGINE} EQUAL ${LP_SOLVE})

# Custom commands for the parsers
  # Create custom command for flex/lex (note the outputs)
  ADD_CUSTOM_COMMAND(
    OUTPUT lexreadparameters.c
    COMMAND flex 
    ARGS -t -i -8 -PReadParameters ${CUIK_BASE_DIR}/readparameters.l > lexreadparameters.c
    DEPENDS readparameters.l)
    
  # Create custom command for bison/yacc (note the DEPENDS)
  ADD_CUSTOM_COMMAND(
    OUTPUT readparameters.tab.c readparameters.tab.h
    COMMAND bison
    ARGS -d -pReadParameters ${CUIK_BASE_DIR}/readparameters.y
    DEPENDS lexreadparameters.c readparameters.y)
    
  # Add parser.c to the list of sources
  SET(sources ${sources} lexreadparameters.c)
  SET(sources ${sources} readparameters.tab.c)
  SET(sources ${sources} readparameters.tab.h)
  
# Custom commands for the parsers
  # Create custom command for flex/lex (note the outputs)
  ADD_CUSTOM_COMMAND(
    OUTPUT lexreadcuiksystem.c
    COMMAND flex 
    ARGS -t -i -8 -PReadcuiksystem ${CUIK_BASE_DIR}/readcuiksystem.l > lexreadcuiksystem.c
    DEPENDS readcuiksystem.l)
    
  # Create custom command for bison/yacc (note the DEPENDS)
  ADD_CUSTOM_COMMAND(
    OUTPUT readcuiksystem.tab.c readcuiksystem.tab.h
    COMMAND bison
    ARGS -d -v -pReadcuiksystem ${CUIK_BASE_DIR}/readcuiksystem.y
    DEPENDS lexreadcuiksystem.c readcuiksystem.y)
    
  # Add parser.c to the list of sources
  SET(sources ${sources} lexreadcuiksystem.c)
  SET(sources ${sources} readcuiksystem.tab.c)
  SET(sources ${sources} readcuiksystem.tab.h)
  
# To locate the tab.h files
INCLUDE_DIRECTORIES(.)

#IF (mpi)
#  # This must be static to allow for MPI execution
#  MESSAGE("-- Compiling a static cuik-common library (necessary for MPI)")
#  ADD_LIBRARY(cuik-common STATIC ${sources})
#ELSE(mpi) 
  # For single processor this can be dynamic
  MESSAGE("-- Compiling a dynamic cuik-common library")
  ADD_LIBRARY(cuik-common SHARED ${sources})
  SET_TARGET_PROPERTIES(cuik-common PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR})
  SET_TARGET_PROPERTIES(cuik-common PROPERTIES MACOSX_RPATH TRUE)
#ENDIF(mpi)

#some libs used by functions in libcuik
IF(cblas)
  TARGET_LINK_LIBRARIES(cuik-common ${cblas}) 
ELSE(cblas)
  IF(blas)
    TARGET_LINK_LIBRARIES(cuik-common ${blas}) 
  ELSE(blas)
     IF(gslcblas)
       TARGET_LINK_LIBRARIES(cuik-common ${gslcblas}) 
     ENDIF(gslcblas)
  ENDIF(blas)
ENDIF(cblas)

TARGET_LINK_LIBRARIES(cuik-common ${expokit}) 

IF (${SIMPLEX_ENGINE} EQUAL ${GUROBI}) 
  TARGET_LINK_LIBRARIES(cuik-common ${gurobi_simplex}) 
ENDIF(${SIMPLEX_ENGINE} EQUAL ${GUROBI})

IF (${SIMPLEX_ENGINE} EQUAL ${CLP}) 
  TARGET_LINK_LIBRARIES(cuik-common ${clp_simplex}) 
  TARGET_LINK_LIBRARIES(cuik-common ${coin_utils})
ENDIF(${SIMPLEX_ENGINE} EQUAL ${CLP})

IF (${SIMPLEX_ENGINE} EQUAL ${GLPK})
  TARGET_LINK_LIBRARIES(cuik-common ${glpx_simplex})
ENDIF(${SIMPLEX_ENGINE} EQUAL ${GLPK})

IF (${SIMPLEX_ENGINE} EQUAL ${LP_SOLVE})
  TARGET_LINK_LIBRARIES(cuik-common ${lps_simplex})
ENDIF(${SIMPLEX_ENGINE} EQUAL ${LP_SOLVE})

TARGET_LINK_LIBRARIES(cuik-common m)

IF(clapack) 
  TARGET_LINK_LIBRARIES(cuik-common ${clapack})
ELSE(clapack) 
  IF(clapacke)
    TARGET_LINK_LIBRARIES(cuik-common ${clapacke})
  ELSE(clapacke)
    IF(gsl)  
      TARGET_LINK_LIBRARIES(cuik-common ${gsl})
    ENDIF(gsl)
  ENDIF(clapacke)
ENDIF(clapack) 

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${includes} DESTINATION include/CuikSuite)

INSTALL(TARGETS cuik-common
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
