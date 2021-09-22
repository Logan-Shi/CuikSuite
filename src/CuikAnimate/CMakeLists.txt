
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikBase/include) 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikAtlas/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikPlot3d/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikWorld/include)

ADD_EXECUTABLE(cuikanimate cuikanimate.c)   
TARGET_LINK_LIBRARIES(cuikanimate cuikworld-common)

ADD_EXECUTABLE(cuiktransform cuiktransform.c)  

TARGET_LINK_LIBRARIES(cuiktransform cuikworld-common)

IF (glib AND gtk AND gdk)  

  INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CuikAnimate/include)
  
  #cuikplay
  ADD_EXECUTABLE(cuikplay cuikplay.c cuikplay_callbacks.c
	  	 cuikplay_interface.c cuikplay_support.c) 

  TARGET_LINK_LIBRARIES(cuikplay ${glib})
  TARGET_LINK_LIBRARIES(cuikplay ${gtk})
  TARGET_LINK_LIBRARIES(cuikplay ${gdk})
  TARGET_LINK_LIBRARIES(cuikplay ${gobject})
  TARGET_LINK_LIBRARIES(cuikplay ${atk})
  TARGET_LINK_LIBRARIES(cuikplay ${gdk_pixbuf})
  
  TARGET_LINK_LIBRARIES(cuikplay cuikworld-common) 
  TARGET_LINK_LIBRARIES(cuikplay cuikatlas-common)

  #cuikmove
  ADD_EXECUTABLE(cuikmotion cuikmove.c cuikmove_callbacks.c
	  	 cuikmove_interface.c cuikplay_support.c) 

  TARGET_LINK_LIBRARIES(cuikmotion ${glib})
  TARGET_LINK_LIBRARIES(cuikmotion ${gtk})
  TARGET_LINK_LIBRARIES(cuikmotion ${gdk})
  TARGET_LINK_LIBRARIES(cuikmotion ${gobject})
  TARGET_LINK_LIBRARIES(cuikmotion ${atk})
  TARGET_LINK_LIBRARIES(cuikmotion ${gdk_pixbuf})
  
  TARGET_LINK_LIBRARIES(cuikmotion cuikworld-common)

  #cuikexplore
  ADD_EXECUTABLE(cuikexploration cuikexplore.c cuikexplore_callbacks.c
	  	 cuikexplore_interface.c cuikplay_support.c) 

  TARGET_LINK_LIBRARIES(cuikexploration ${glib})
  TARGET_LINK_LIBRARIES(cuikexploration ${gtk})
  TARGET_LINK_LIBRARIES(cuikexploration ${gdk})
  TARGET_LINK_LIBRARIES(cuikexploration ${gobject})
  TARGET_LINK_LIBRARIES(cuikexploration ${atk})
  TARGET_LINK_LIBRARIES(cuikexploration ${gdk_pixbuf})
  
  TARGET_LINK_LIBRARIES(cuikexploration cuikworld-common) 
  TARGET_LINK_LIBRARIES(cuikexploration cuikatlas-common)

  INSTALL(FILES ${includes} DESTINATION include/CuikSuite)
  INSTALL(PROGRAMS cuikplayer DESTINATION bin)
  INSTALL(PROGRAMS cuikexplore DESTINATION bin)
  INSTALL(PROGRAMS cuikmove DESTINATION bin)

  INSTALL(TARGETS cuikanimate cuikplay cuikmotion cuikexploration
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )

ENDIF(glib AND gtk AND gdk)

FILE(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

INSTALL(TARGETS cuiktransform
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
