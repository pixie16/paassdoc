set(PaassCoreSources Display.cpp hribf_buffers.cpp poll2_socket.cpp )

if (${CURSES_FOUND})
	list(APPEND PaassCoreSources CTerminal.cpp)
endif()

add_library(PaassCoreObjects OBJECT ${PaassCoreSources})

add_library(PaassCoreStatic STATIC $<TARGET_OBJECTS:PaassCoreObjects>)

if (${CURSES_FOUND})
	target_link_libraries(PaassCoreStatic ${CURSES_LIBRARIES})
endif()

if(BUILD_SHARED_LIBS)
	add_library(PaassCore SHARED $<TARGET_OBJECTS:PaassCoreObjects>)
	if (${CURSES_FOUND})
		target_link_libraries(PaassCore ${CURSES_LIBRARIES})
	endif()
	install(TARGETS PaassCore DESTINATION lib)
endif(BUILD_SHARED_LIBS)