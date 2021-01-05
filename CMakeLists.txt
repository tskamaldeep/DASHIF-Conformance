cmake_minimum_required(VERSION 3.17)
project(DASHIF_Conformance VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(BUILD_SHARED_LIBS True)

#add_library(DASHIF_Conformance SHARED library.cpp library.h ConformanceErrorLevels.cpp ConformanceErrorLevels.h ConformanceException.cpp ConformanceException.h ConformanceExceptionTypes.h ConformanceConstraints.cpp ConformanceConstraints.h ConformanceTestTimer.cpp ConformanceTestTimer.h ConformanceMPDCheckSequence.cpp ConformanceMPDCheckSequence.h ConformanceMPDParser.cpp ConformanceMPDParser.h tests/testConformanceException.cpp tests/testConformanceException.h tests/catchinit.cpp external-includes/ tests/addTimestampDetails.cpp)
add_library(DASHIF_Conformance STATIC library.cpp library.h ConformanceExceptionTypes.h ConformanceErrorLevels.h ConformanceErrorLevels.cpp ConformanceException.cpp ConformanceException.h ConformanceConstraints.cpp ConformanceConstraints.h ConformanceTestTimer.cpp ConformanceTestTimer.h ConformanceMPDCheckSequence.cpp ConformanceMPDCheckSequence.h ConformanceMPDParser.cpp ConformanceMPDParser.h ConformanceMPDDataModel.cpp ConformanceMPDDataModel.h)

# Add the include directory locations
#target_include_directories(DASHIF_Conformance PUBLIC /usr/local/lib/libxml++-5.0/include/ /usr/local/include/libxml++-5.0/)
target_include_directories(DASHIF_Conformance PUBLIC /usr/local/lib/libxml++-5.0/include/ /usr/local/include/libxml++-5.0/)
target_include_directories(DASHIF_Conformance PUBLIC /usr/local/Cellar/glibmm/2.64.5/include/glibmm-2.4 /usr/local/Cellar/glibmm/2.64.5/lib/glibmm-2.4/include /usr/local/Cellar/glib/2.66.4/include /usr/local/Cellar/glib/2.66.4/include/glib-2.0 /usr/local/Cellar/glib/2.66.4/lib/glib-2.0/include)

#Try only include_directories.
include_directories(/usr/local/include/libxml++-5.0/)
include_directories(/usr/local/lib/libxml++-5.0/include/)
include_directories(/usr/local/Cellar/glibmm/2.64.5/include/glibmm-2.4)
include_directories(/usr/local/Cellar/glibmm/2.64.5/lib/glibmm-2.4/include)
include_directories(/usr/local/Cellar/glib/2.66.4/include)
include_directories(/usr/local/Cellar/glib/2.66.4/include/glib-2.0)
include_directories(/usr/local/Cellar/glib/2.66.4/lib/glib-2.0/include)

#Link lib directories
link_directories(/usr/local/lib/)
link_directories(/usr/local/Cellar/glibmm/2.64.5/lib/)
link_directories(/usr/local/Cellar/glib/2.66.4/lib/)

# Add the shared dependency library
target_link_libraries(DASHIF_Conformance SHARED /usr/local/lib/libxml++-5.0.dylib)
target_link_libraries(DASHIF_Conformance SHARED libglib-2.0.dylib)
target_link_libraries(DASHIF_Conformance SHARED libglibmm-2.4.dylib)


add_executable(library library.cpp)