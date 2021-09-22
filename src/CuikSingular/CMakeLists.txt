
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include)

ADD_EXECUTABLE(cuiksingequations cuiksingequations.c)
ADD_EXECUTABLE(cuikaddjacobian cuikaddjacobian.c)
ADD_EXECUTABLE(cuikTWS cuikTWS.c)

TARGET_LINK_LIBRARIES(cuiksingequations cuikworld-common)
TARGET_LINK_LIBRARIES(cuikaddjacobian cuikworld-common)
TARGET_LINK_LIBRARIES(cuikTWS cuikworld-common)

INSTALL(TARGETS cuiksingequations cuikaddjacobian cuikTWS
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)