#We will build a separate library for each one of the third party
#libraries/codes that we are going to use. However, we'll dump them all into
#the same folder for simplicity's sake.

#Build pugixml. This software is used to parse XML files.
set(PugixmlSources pugixml.cpp)
add_library(PugixmlObjects OBJECT ${PugixmlSources})
add_library(PugixmlStatic STATIC $<TARGET_OBJECTS:PugixmlObjects>)
if(BUILD_SHARED_LIBS)
    add_library(Pugixml SHARED $<TARGET_OBJECTS:PugixmlObjects>)
    install(TARGETS Pugixml DESTINATION lib)
endif(BUILD_SHARED_LIBS)