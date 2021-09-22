SET(CUIK_PLAN_DIR ${CMAKE_SOURCE_DIR}/src/CuikAtlas)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikAtlas/include)

ADD_LIBRARY(cuikatlas-common SHARED  scpolytope.c cpolytope.c chart.c
                                    atlas.c ${btree} rrt.c atlasrrt.c
				    samples.c averages.c dynamics.c sa.c)

SET_TARGET_PROPERTIES(cuikatlas-common PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR})
SET_TARGET_PROPERTIES(cuikatlas-common PROPERTIES MACOSX_RPATH TRUE)

TARGET_LINK_LIBRARIES(cuikatlas-common cuikworld-common)

IF (cuik_kdtree)
  TARGET_LINK_LIBRARIES(cuikatlas-common ${cuik_kdtree})
ENDIF(cuik_kdtree)

IF (mpnn)
  TARGET_LINK_LIBRARIES(cuikatlas-common ${mpnn})
ENDIF(mpnn)

ADD_EXECUTABLE(cuikatlas cuikatlas.c)
TARGET_LINK_LIBRARIES(cuikatlas cuikatlas-common)

# FIND_LIBRARY(efence efence)
# IF(efence)
#  MESSAGE("-- Found efence: ${efence}")
#  TARGET_LINK_LIBRARIES(cuikatlas ${efence})
#ELSE(efence)
#  MESSAGE("-- efence is missing")
#ENDIF(efence)

ADD_EXECUTABLE(cuikrrterror cuikrrterror.c)
TARGET_LINK_LIBRARIES(cuikrrterror cuikatlas-common)

ADD_EXECUTABLE(cuikccrrt cuikccrrt.c)
TARGET_LINK_LIBRARIES(cuikccrrt cuikatlas-common)

ADD_EXECUTABLE(cuikcctrrt cuikcctrrt.c)
TARGET_LINK_LIBRARIES(cuikcctrrt cuikatlas-common)

ADD_EXECUTABLE(cuikcbirrt cuikcbirrt.c)
TARGET_LINK_LIBRARIES(cuikcbirrt cuikatlas-common)

ADD_EXECUTABLE(cuikkinorrt cuikkinorrt.c)
TARGET_LINK_LIBRARIES(cuikkinorrt cuikatlas-common)

ADD_EXECUTABLE(cuikkinoest cuikkinoest.c)
TARGET_LINK_LIBRARIES(cuikkinoest cuikatlas-common)

ADD_EXECUTABLE(cuikrrtstar cuikrrtstar.c)
TARGET_LINK_LIBRARIES(cuikrrtstar cuikatlas-common)

ADD_EXECUTABLE(cuikatlasrrt cuikatlasrrt.c)
TARGET_LINK_LIBRARIES(cuikatlasrrt cuikatlas-common)

ADD_EXECUTABLE(cuikatlastrrt cuikatlastrrt.c)
TARGET_LINK_LIBRARIES(cuikatlastrrt cuikatlas-common)

ADD_EXECUTABLE(cuiksimulate cuiksimulate.c)
TARGET_LINK_LIBRARIES(cuiksimulate cuikatlas-common)

ADD_EXECUTABLE(cuikatlasrrtstar cuikatlasrrtstar.c)
TARGET_LINK_LIBRARIES(cuikatlasrrtstar cuikatlas-common)

ADD_EXECUTABLE(cuikatlasAstar cuikatlasAstar.c)
TARGET_LINK_LIBRARIES(cuikatlasAstar cuikatlas-common)

ADD_EXECUTABLE(cuikatlasGBF cuikatlasGBF.c)
TARGET_LINK_LIBRARIES(cuikatlasGBF cuikatlas-common)

ADD_EXECUTABLE(cuikplotatlas cuikplotatlas.c)
TARGET_LINK_LIBRARIES(cuikplotatlas cuikatlas-common)

ADD_EXECUTABLE(cuikatlasvolume cuikatlasvolume.c)
TARGET_LINK_LIBRARIES(cuikatlasvolume cuikatlas-common)

ADD_EXECUTABLE(cuikplotpath cuikplotpath.c)
TARGET_LINK_LIBRARIES(cuikplotpath cuikatlas-common)

ADD_EXECUTABLE(cuikplotforcefield cuikplotforcefield.c)
TARGET_LINK_LIBRARIES(cuikplotforcefield cuikatlas-common)

ADD_EXECUTABLE(cuiktriangulateatlas cuiktriangulateatlas.c)
TARGET_LINK_LIBRARIES(cuiktriangulateatlas cuikatlas-common)

ADD_EXECUTABLE(cuikplotrrt cuikplotrrt.c)
TARGET_LINK_LIBRARIES(cuikplotrrt cuikatlas-common)

ADD_EXECUTABLE(cuikrrtpath cuikrrtpath.c)
TARGET_LINK_LIBRARIES(cuikrrtpath cuikatlas-common)

ADD_EXECUTABLE(cuikatlascenters cuikatlascenters.c)
TARGET_LINK_LIBRARIES(cuikatlascenters cuikatlas-common)

ADD_EXECUTABLE(cuikatlas2graph cuikatlas2graph.c)
TARGET_LINK_LIBRARIES(cuikatlas2graph cuikatlas-common)

ADD_EXECUTABLE(cuiksingularcharts cuiksingularcharts.c)
TARGET_LINK_LIBRARIES(cuiksingularcharts cuikatlas-common)

ADD_EXECUTABLE(cuikrrtnodes cuikrrtnodes.c)
TARGET_LINK_LIBRARIES(cuikrrtnodes cuikatlas-common)

ADD_EXECUTABLE(cuikrrtcosts cuikrrtcosts.c)
TARGET_LINK_LIBRARIES(cuikrrtcosts cuikatlas-common)

ADD_EXECUTABLE(cuikcost cuikcost.c)
TARGET_LINK_LIBRARIES(cuikcost cuikatlas-common)

ADD_EXECUTABLE(cuikdim cuikdim.c)
TARGET_LINK_LIBRARIES(cuikdim cuikatlas-common)

ADD_EXECUTABLE(cuikplotatlasrrt cuikplotatlasrrt.c)
TARGET_LINK_LIBRARIES(cuikplotatlasrrt cuikatlas-common)

ADD_EXECUTABLE(cuiksmoothpath cuiksmoothpath.c)
TARGET_LINK_LIBRARIES(cuiksmoothpath cuikatlas-common)

ADD_EXECUTABLE(cuikrefinetrajectory cuikrefinetrajectory.c)
TARGET_LINK_LIBRARIES(cuikrefinetrajectory cuikatlas-common)

ADD_EXECUTABLE(cuikminimize cuikminimize.c)
TARGET_LINK_LIBRARIES(cuikminimize cuikatlas-common)

ADD_EXECUTABLE(cuikpathlength cuikpathlength.c)
TARGET_LINK_LIBRARIES(cuikpathlength cuikatlas-common)

ADD_EXECUTABLE(cuikpatheffort cuikpatheffort.c)
TARGET_LINK_LIBRARIES(cuikpatheffort cuikatlas-common)

ADD_EXECUTABLE(cuikME cuikME.c)
TARGET_LINK_LIBRARIES(cuikME cuikatlas-common)

ADD_EXECUTABLE(cuikxdot cuikxdot.c)
TARGET_LINK_LIBRARIES(cuikxdot cuikatlas-common)

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${includes} DESTINATION include/CuikSuite)


INSTALL(TARGETS cuikatlas-common cuikatlas cuikccrrt cuikcbirrt cuikcctrrt
		cuikkinorrt cuikkinoest cuikrrterror
		cuikatlasrrt cuiksimulate 
		cuikatlasAstar cuikatlasGBF cuikplotatlas cuikatlastrrt
		cuikplotrrt cuikrrtpath cuikatlascenters cuikrrtnodes cuikrrtcosts
		cuiktriangulateatlas cuikplotatlasrrt cuikrrtstar cuiksmoothpath
		cuikatlasrrtstar cuikatlasvolume cuikcost cuikplotpath
		cuiksingularcharts cuikrefinetrajectory cuikminimize
		cuikpathlength cuikpatheffort  cuikME cuikxdot
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
