INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikSilhouette/include)

ADD_EXECUTABLE(cuiksilhouette cuiksilhouette.c cp.c)

TARGET_LINK_LIBRARIES(cuiksilhouette cuik-common)

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${includes} DESTINATION include/CuikSuite)

INSTALL(TARGETS cuiksilhouette
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
