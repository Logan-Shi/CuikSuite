INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikAtlas/include)


ADD_EXECUTABLE(cuiksample cuiksample.c)
TARGET_LINK_LIBRARIES(cuiksample cuik-common)

ADD_EXECUTABLE(cuiksols2samples cuiksols2samples.c)
TARGET_LINK_LIBRARIES(cuiksols2samples cuik-common)
TARGET_LINK_LIBRARIES(cuiksols2samples cuikworld-common)

ADD_EXECUTABLE(cuiksamples2sols cuiksamples2sols.c)
TARGET_LINK_LIBRARIES(cuiksamples2sols cuik-common)
TARGET_LINK_LIBRARIES(cuiksamples2sols cuikworld-common)
TARGET_LINK_LIBRARIES(cuiksamples2sols cuikatlas-common)

ADD_EXECUTABLE(cuikjoints2links cuikjoints2links.c) 
TARGET_LINK_LIBRARIES(cuikjoints2links cuik-common)
TARGET_LINK_LIBRARIES(cuikjoints2links cuikworld-common)

ADD_EXECUTABLE(cuiklinks2joints cuiklinks2joints.c)
TARGET_LINK_LIBRARIES(cuiklinks2joints cuik-common)
TARGET_LINK_LIBRARIES(cuiklinks2joints cuikworld-common)

ADD_EXECUTABLE(cuikerror cuikerror.c)
TARGET_LINK_LIBRARIES(cuikerror cuik-common)
TARGET_LINK_LIBRARIES(cuikerror cuikworld-common) 
TARGET_LINK_LIBRARIES(cuikerror cuikatlas-common)

INSTALL(TARGETS cuiksample cuiksols2samples cuiksamples2sols
		             cuikjoints2links cuiklinks2joints
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
