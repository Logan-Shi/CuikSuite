INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include)

ADD_EXECUTABLE(cuiknewton cuiknewton.c)
TARGET_LINK_LIBRARIES(cuiknewton cuik-common)

ADD_EXECUTABLE(cuikgradient cuikgradient.c)
TARGET_LINK_LIBRARIES(cuikgradient cuik-common)

INSTALL(TARGETS cuiknewton
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
