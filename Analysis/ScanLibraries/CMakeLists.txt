#Install include directories to support the shared library.
if(BUILD_SHARED_LIBS)
  install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})
endif(BUILD_SHARED_LIBS)

if(BUILD_UNITTESTS)
    add_subdirectory(tests)
endif(BUILD_UNITTESTS)

add_subdirectory(source)
