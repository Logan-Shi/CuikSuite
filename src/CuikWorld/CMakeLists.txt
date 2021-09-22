
SET(CUIK_WORLD_DIR ${CMAKE_SOURCE_DIR}/src/CuikWorld)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include)

SET(sources link.c joint.c mechanism.c  polyhedron.c
	    	    environment.c cd.c sample.c world.c 
		    error_world.c  error_tensegrity.c)
		    
# Custom commands for the world parser
  # Create custom command for flex/lex (note the outputs)
  ADD_CUSTOM_COMMAND(
    OUTPUT lexreadworld.c
    COMMAND flex 
    ARGS -t -i -8 -PReadWorld ${CUIK_WORLD_DIR}/readworld.l > lexreadworld.c
    DEPENDS readworld.l)
    
  # Create custom command for bison/yacc (note the DEPENDS)
  ADD_CUSTOM_COMMAND(
    OUTPUT readworld.tab.c readworld.tab.h
    COMMAND bison
    ARGS -d -pReadWorld ${CUIK_WORLD_DIR}/readworld.y
    DEPENDS lexreadworld.c readworld.y)
 
  # Add parser.c to the list of sources
  SET(sources ${sources} lexreadworld.c)
  SET(sources ${sources} readworld.tab.c)
  SET(sources ${sources} readworld.tab.h)

# Custom commands for the parsers
  # Create custom command for flex/lex (note the outputs)
  ADD_CUSTOM_COMMAND(
    OUTPUT lexreadtensegrity.c
    COMMAND flex 
    ARGS -t -i -8 -PReadTensegrity ${CUIK_WORLD_DIR}/readtensegrity.l > lexreadtensegrity.c
    DEPENDS readtensegrity.l)
    
  # Create custom command for bison/yacc (note the DEPENDS)
  ADD_CUSTOM_COMMAND(
    OUTPUT readtensegrity.tab.c readtensegrity.tab.h
    COMMAND bison
    ARGS -d -pReadTensegrity ${CUIK_WORLD_DIR}/readtensegrity.y
    DEPENDS lexreadtensegrity.c readtensegrity.y)
    
  # Add parser.c to the list of sources
  SET(sources ${sources} lexreadtensegrity.c)
  SET(sources ${sources} readtensegrity.tab.c)
  SET(sources ${sources} readtensegrity.tab.h)
  
# To locate the tab.h files
INCLUDE_DIRECTORIES(.)

IF (vcollide AND rapid)
  ADD_LIBRARY(cuikvcollide SHARED cd_vcollide.cpp)
  SET_TARGET_PROPERTIES(cuikvcollide PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
  SET_TARGET_PROPERTIES(cuikvcollide PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikvcollide ${vcollide}) 
  TARGET_LINK_LIBRARIES(cuikvcollide ${rapid})

  TARGET_LINK_LIBRARIES(cuikvcollide cuik-common)

  INSTALL(TARGETS cuikvcollide
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF (vcollide AND rapid)

IF (pqp)
  ADD_LIBRARY(cuikpqp SHARED cd_pqp.cpp)
  SET_TARGET_PROPERTIES(cuikpqp PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
  SET_TARGET_PROPERTIES(cuikpqp PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikpqp ${pqp}) 

  TARGET_LINK_LIBRARIES(cuikpqp cuik-common) 

  INSTALL(TARGETS cuikpqp
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF (pqp)

IF (fcl AND ccd  AND bs)

  INCLUDE_DIRECTORIES(/opt/local/include/Eigen3) 
  INCLUDE_DIRECTORIES(/usr/local/include/Eigen3)
  
  ADD_LIBRARY(cuikfcl SHARED cd_fcl.cpp)
  SET_TARGET_PROPERTIES(cuikfcl PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
  SET_TARGET_PROPERTIES(cuikfcl PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikfcl ${fcl} ${ccd} ${bs})

  TARGET_LINK_LIBRARIES(cuikfcl cuik-common)
  
  INSTALL(TARGETS cuikfcl
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF (fcl AND ccd AND bs)

IF (bullet AND bulletLin)
  ADD_LIBRARY(cuikbullet SHARED cd_bullet.cpp)
  SET_TARGET_PROPERTIES(cuikbullet PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
  SET_TARGET_PROPERTIES(cuikbullet PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikbullet ${bullet} ${bulletLin})
  
  IF (hacd)
    TARGET_LINK_LIBRARIES(cuikbullet ${hacd}) 
  ENDIF (hacd)

  TARGET_LINK_LIBRARIES(cuikbullet cuik-common) 

  INSTALL(TARGETS cuikbullet
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF (bullet AND bulletLin)

IF (rigidCLL)
  ADD_LIBRARY(cuikrigidCLL SHARED cd_rigidCLL.cpp)
  SET_TARGET_PROPERTIES(cuikrigidCLL PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR})
  SET_TARGET_PROPERTIES(cuikrigidCLL PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikrigidCLL ${rigidCLL}) 

  TARGET_LINK_LIBRARIES(cuikrigidCLL cuik-common) 

  INSTALL(TARGETS cuikrigidCLL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF (rigidCLL)

ADD_LIBRARY(cuikworld-common SHARED ${sources})

SET_TARGET_PROPERTIES(cuikworld-common PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
SET_TARGET_PROPERTIES(cuikworld-common PROPERTIES MACOSX_RPATH TRUE)
#SET_TARGET_PROPERTIES(cuikworld-common PROPERTIES INSTALL_RPATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)


TARGET_LINK_LIBRARIES(cuikworld-common cuikplot-common)
TARGET_LINK_LIBRARIES(cuikworld-common cuik-common) 

IF (solid)
  TARGET_LINK_LIBRARIES(cuikworld-common ${solid})
ENDIF (solid)

IF (vcollide AND rapid )
  TARGET_LINK_LIBRARIES(cuikworld-common cuikvcollide) 
ENDIF(vcollide AND rapid)

IF (pqp)
  TARGET_LINK_LIBRARIES(cuikworld-common cuikpqp) 
ENDIF(pqp)

IF (fcl AND bs)
  TARGET_LINK_LIBRARIES(cuikworld-common cuikfcl)
ENDIF(fcl AND bs)

IF (bullet AND bulletLin) 
  TARGET_LINK_LIBRARIES(cuikworld-common cuikbullet)
ENDIF (bullet AND bulletLin)

IF (rigidCLL)
  TARGET_LINK_LIBRARIES(cuikworld-common cuikrigidCLL)
ENDIF (rigidCLL)

IF (assimp)
  TARGET_LINK_LIBRARIES(cuikworld-common ${assimp})
ENDIF(assimp)

ADD_EXECUTABLE(cuikworldaxes cuikworldaxes.c)
TARGET_LINK_LIBRARIES(cuikworldaxes cuikworld-common) 

ADD_EXECUTABLE(cuikworldforces cuikworldforces.c)
TARGET_LINK_LIBRARIES(cuikworldforces cuikworld-common)

ADD_EXECUTABLE(cuikworld2world cuikworld2world.c)
TARGET_LINK_LIBRARIES(cuikworld2world cuikworld-common) 

ADD_EXECUTABLE(cuikcollisions cuikcollisions.c)
TARGET_LINK_LIBRARIES(cuikcollisions cuikworld-common)

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${includes} DESTINATION include/CuikSuite)

INSTALL(TARGETS cuikworld-common cuikpqp cuikrigidCLL cuikvcollide cuikfcl cuikbullet cuikworldaxes cuikcollisions cuikworld2world
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
