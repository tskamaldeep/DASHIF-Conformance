cmake_minimum_required(VERSION 3.17)
project(DASHIF_Conformance VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(BUILD_SHARED_LIBS True)

link_directories(/usr/local/Cellar/libxml++3/3.2.2/lib)
link_directories(/usr/local/Cellar/glibmm/2.64.4/lib)

#add_library(DASHIF_Conformance SHARED library.cpp library.h ConformanceErrorLevels.cpp ConformanceErrorLevels.h ConformanceException.cpp ConformanceException.h ConformanceExceptionTypes.h ConformanceConstraints.cpp ConformanceConstraints.h ConformanceTestTimer.cpp ConformanceTestTimer.h ConformanceMPDCheckSequence.cpp ConformanceMPDCheckSequence.h ConformanceMPDParser.cpp ConformanceMPDParser.h tests/testConformanceException.cpp tests/testConformanceException.h tests/catchinit.cpp external-includes/ tests/addTimestampDetails.cpp)
add_library(DASHIF_Conformance STATIC library.cpp library.h ConformanceExceptionTypes.h ConformanceErrorLevels.h ConformanceErrorLevels.cpp ConformanceException.cpp ConformanceException.h ConformanceConstraints.cpp ConformanceConstraints.h ConformanceTestTimer.cpp ConformanceTestTimer.h ConformanceMPDCheckSequence.cpp ConformanceMPDCheckSequence.h ConformanceMPDParser.cpp ConformanceMPDParser.h)

# Add the shared dependency library
# target_link_libraries(libDASHIF_Conformance.a SHARED libxml++-3.0.dylib)

# Add the include directory locations
target_include_directories(DASHIF_Conformance PUBLIC /usr/local/Cellar/libxml++3/3.2.2/include/libxml++-3.0 /usr/local/Cellar/libxml++3/3.2.2/lib/libxml++-3.0/include)

target_include_directories(DASHIF_Conformance PUBLIC /usr/local/Cellar/glibmm/2.64.4/include/glibmm-2.4 /usr/local/Cellar/glibmm/2.64.4/lib/glibmm-2.4/include /usr/local/Cellar/glib/2.66.2_1/include /usr/local/Cellar/glib/2.66.2_1/include/glib-2.0 /usr/local/Cellar/glib/2.66.2_1/lib/glib-2.0/include)