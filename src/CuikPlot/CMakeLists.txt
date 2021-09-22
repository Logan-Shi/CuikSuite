# Tell CMake to build a shared library from sources
	     
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot/include)


ADD_EXECUTABLE(cuikplot plot2D.c cuikplot.c)

TARGET_LINK_LIBRARIES(cuikplot cuik-common)
TARGET_LINK_LIBRARIES(cuikplot m)

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${includes} DESTINATION include/CuikSuite)

INSTALL(TARGETS cuikplot
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
