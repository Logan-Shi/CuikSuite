INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBabel/include)

IF(babel)
  ADD_EXECUTABLE(cuikbabelenergy energy.cpp)
  TARGET_LINK_LIBRARIES(cuikbabelenergy  ${babel}) 

  ADD_LIBRARY(cuikbabel SHARED babel.cpp)
  SET_TARGET_PROPERTIES(cuikbabel PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR}) 
  SET_TARGET_PROPERTIES(cuikbabel PROPERTIES MACOSX_RPATH TRUE)
  TARGET_LINK_LIBRARIES(cuikbabel cuik-common ${babel})

  FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
  INSTALL(FILES ${includes} DESTINATION include/CuikSuite)

  INSTALL(TARGETS cuikbabelenergy cuikbabel
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
ENDIF(babel)

