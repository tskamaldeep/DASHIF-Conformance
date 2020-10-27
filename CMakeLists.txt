cmake_minimum_required(VERSION 3.17)
project(DASHIF_Conformance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(DASHIF_Conformance SHARED library.cpp library.h ConformanceErrorLevels.cpp ConformanceErrorLevels.h ConformanceException.cpp ConformanceException.h ConformanceExceptionTypes.h ConformanceConstraints.cpp ConformanceConstraints.h ConformanceTestTimer.cpp ConformanceTestTimer.h ConformanceMPDCheckSequence.cpp ConformanceMPDCheckSequence.h ConformanceMPDParser.cpp ConformanceMPDParser.h tests/testConformanceException.cpp tests/testConformanceException.h tests/catchinit.cpp external-includes/ tests/addTimestampDetails.cpp)
target_link_libraries(DASHIF_Conformance libxerces-c-3.2.dylib)
