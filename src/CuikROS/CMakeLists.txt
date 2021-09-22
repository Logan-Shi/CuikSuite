
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)

IF(xml)
  ADD_EXECUTABLE(cuikurdf2world cuikurdf2world.cpp)

  TARGET_LINK_LIBRARIES(cuikurdf2world ${xml})
  TARGET_LINK_LIBRARIES(cuikurdf2world cuik-common) 
  TARGET_LINK_LIBRARIES(cuikurdf2world cuikworld-common) 
  TARGET_LINK_LIBRARIES(cuikurdf2world cuikplot-common)

  INSTALL(TARGETS cuikurdf2world
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF(xml)
