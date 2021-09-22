INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBio/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBabel/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikAtlas/include)

IF(babel)
  ADD_LIBRARY(cuikbioworld SHARED bioworld.c)
  SET_TARGET_PROPERTIES(cuikbioworld PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
  SET_TARGET_PROPERTIES(cuikbioworld PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikbioworld cuik-common cuikworld-common  cuikatlas-common cuikbabel)
 
  ADD_EXECUTABLE(cuikpdb2world cuikpdb2world.c)
  TARGET_LINK_LIBRARIES(cuikpdb2world cuikbioworld)

  ADD_EXECUTABLE(cuikenergy cuikenergy.c)  
  TARGET_LINK_LIBRARIES(cuikenergy cuikbioworld) 

  ADD_EXECUTABLE(cuikrmse cuikrmse.c)  
  TARGET_LINK_LIBRARIES(cuikrmse cuikbioworld) 

  ADD_EXECUTABLE(cuiksample2pdb cuiksample2pdb.c)  
  TARGET_LINK_LIBRARIES(cuiksample2pdb cuikbioworld) 

  ADD_EXECUTABLE(cuikpdb2sample cuikpdb2sample.c)  
  TARGET_LINK_LIBRARIES(cuikpdb2sample cuikbioworld) 

  ADD_EXECUTABLE(cuikatoms2samples cuikatoms2samples.c)  
  TARGET_LINK_LIBRARIES(cuikatoms2samples cuikbioworld) 

  ADD_EXECUTABLE(cuikbioatlastrrt cuikbioatlastrrt.c)  
  TARGET_LINK_LIBRARIES(cuikbioatlastrrt cuikbioworld) 

  ADD_EXECUTABLE(cuikbiominimize cuikbiominimize.c)  
  TARGET_LINK_LIBRARIES(cuikbiominimize cuikbioworld) 

  INSTALL(TARGETS cuikbioworld cuikpdb2world cuikenergy cuikrmse cuiksample2pdb cuikpdb2sample cuikatoms2samples cuikbioatlastrrt cuikbiominimize
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF(babel)

ADD_EXECUTABLE(cuiksamples2atoms cuiksamples2atoms.c)  
TARGET_LINK_LIBRARIES(cuiksamples2atoms cuikworld-common) 

ADD_EXECUTABLE(cuiksamples2rgroups cuiksamples2rgroups.c)  
TARGET_LINK_LIBRARIES(cuiksamples2rgroups cuikworld-common) 

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${includes} DESTINATION include/CuikSuite)

INSTALL(TARGETS cuiksamples2atoms cuiksamples2rgroups
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
