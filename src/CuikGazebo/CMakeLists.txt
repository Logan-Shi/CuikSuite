
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikAtlas/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)

IF(xml)
  ADD_EXECUTABLE(cuikworld2sdf cuikworld2sdf.cpp)

  TARGET_LINK_LIBRARIES(cuikworld2sdf ${xml})
  TARGET_LINK_LIBRARIES(cuikworld2sdf cuik-common) 
  TARGET_LINK_LIBRARIES(cuikworld2sdf cuikatlas-common)
  TARGET_LINK_LIBRARIES(cuikworld2sdf cuikworld-common) 
  TARGET_LINK_LIBRARIES(cuikworld2sdf cuikplot-common)

  INSTALL(TARGETS cuikworld2sdf
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF(xml)
