//
// Created by Kamaldeep Tumkur on 12/09/20.
//

#include "testConformanceException.h"

using namespace conformance::exception;

TEST_CASE("set of allowed exceptions", "[conformanceexceptions]") {

    GIVEN("The description limit with conformance exceptions.") {
        std::size_t short_desc_limit = EXCEPTION_STR_CHAR_LIMIT_SHORT;
        std::size_t detail_desc_limit = EXCEPTION_STR_CHAR_LIMIT_LONG;

        REQUIRE (short_desc_limit == 1024);
        REQUIRE (detail_desc_limit == 65535);
    }

    GIVEN("Instance of the ConformanceException in the description setter.") {
        ConformanceException exc = ConformanceException();

        EXCSTRS descStrings = exc.exceptionDescription(genericexceptionhash);
        std::string descShort = descStrings[0];
        std::string descLong = descStrings[1];

        REQUIRE(descShort.size() <= EXCEPTION_STR_CHAR_LIMIT_SHORT);
        REQUIRE(descLong.size() <= EXCEPTION_STR_CHAR_LIMIT_LONG);

        WHEN ("There is a description setter used on the exception class.")

        descShort = "Testing the size of a short description using the catch framework." \
        "Exception reported is a generic type of ConformanceException.";

        descLong = "In file included from /Users/tskamaldeep/CLionProjects/DASHIF-Conformance/ConformanceMPDCheckSequence.cpp:5:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/iostream:38:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/ios:216:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/__locale:15:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/string:500:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/string_view:176:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/__string:56:\n" \
                                       "In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/algorithm:644:\n" \
                                       "/Library/Developer/CommandLineTools/usr/include/c++/v1/memory:1825:31: error: no matching constructor" \
                                       "for initialization of 'std::__1::pair<const unsigned long, std::__1::list<conformance::constraints::ConstraintEntity *," \
                                       "std::__1::allocator<conformance::constraints::ConstraintEntity *> > >'\n";

        exc.exceptionStrShort(genericexceptionhash, descShort);
        exc.exceptionStrLong(genericexceptionhash, descLong);

        THEN ("The characters limit as well should be within bounds.")

        REQUIRE(descShort.size() <= EXCEPTION_STR_CHAR_LIMIT_SHORT);
        REQUIRE(descLong.size() <= EXCEPTION_STR_CHAR_LIMIT_LONG);
    }

    GIVEN ("IOException type construction should be tested.") {
        ConformanceException ioexc = ConformanceException(ioexceptionhash);
        EXCSTRS iodescstrings = ioexc.exceptionDescription(ioexceptionhash);

        ConformanceException netexc = ConformanceException(networkexceptionhash);
        EXCSTRS netdescstrings = netexc.exceptionDescription(networkexceptionhash);

        std::string iodescName = ioexc.exceptionName();
        std::string iodescShort = iodescstrings[0];
        std::string iodescLong = iodescstrings[1];

        std::string netdescName = netexc.exceptionName();
        std::string netdescShort = netdescstrings[0];
        std::string netdescLong = netdescstrings[1];

        THEN("Validate the instantiated object with preset properties.")

        REQUIRE(typeid(iodescName).hash_code() == typeid(ioexceptionname).hash_code());
        REQUIRE(typeid(iodescShort).hash_code() == typeid(ioexceptionstrshort).hash_code());
        REQUIRE(typeid(iodescLong).hash_code() == typeid(ioexceptionstrlong).hash_code());

        REQUIRE(typeid(netdescName).hash_code() == typeid(networkexceptionname).hash_code());
        REQUIRE(typeid(netdescShort).hash_code() == typeid(networkexceptionstrshort).hash_code());
        REQUIRE(typeid(netdescLong).hash_code() == typeid(networkexceptionstrlong).hash_code());
    }

}