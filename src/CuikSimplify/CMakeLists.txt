INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include)

ADD_EXECUTABLE(cuiksimplify cuiksimplify.c)
TARGET_LINK_LIBRARIES(cuiksimplify cuik-common)

ADD_EXECUTABLE(cuikunsimplify cuikunsimplify.c)
TARGET_LINK_LIBRARIES(cuikunsimplify cuik-common)

ADD_EXECUTABLE(cuikatan2 cuikatan2.c)
TARGET_LINK_LIBRARIES(cuikatan2 cuik-common)

ADD_EXECUTABLE(cuikmerge cuikmerge.c)
TARGET_LINK_LIBRARIES(cuikmerge cuik-common)

ADD_EXECUTABLE(cuikmergeboxes cuikmergeboxes.c)
TARGET_LINK_LIBRARIES(cuikmergeboxes cuik-common)

INSTALL(TARGETS cuiksimplify cuikunsimplify cuikatan2 cuikmerge cuikmergeboxes
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
