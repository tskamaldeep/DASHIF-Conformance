#include <iostream>
#include <map>
#include <memory>
#include <iterator>
#include <string>
#include <chrono>
#include <ctime>
#include <typeinfo>

#include "ConformanceException.h"
#include "ConformanceConstraints.h"

using namespace conformance::exception;
using namespace conformance::constraints;
using namespace std;


    const std::string MPDEXT = ".mpd";
    const std::string PATHSEP = "/";
    const std::string HTTPPREFIX = "http://";
    const std::string HTTPSPREFIX = "https://";

    // Find the path components.
    // std::string murl = this->MPDURL();
    // std::size_t firstsepindex = murl.find_first_of(PATHSEP);
    // std::size_t lastsepindex = murl.find_last_of(PATHSEP);
    // std::string urlbasename = murl.substr(lastsepindex+1);
    // std::string urldirname = murl.substr(firstsepindex+1, lastsepindex);

int main() {


    //////////////////////////////////////////////////////////////////////////
    // Address of operator: Initializer list instantiation.
    //////////////////////////////////////////////////////////////////////////
    auto a = {"1", "2"};
    auto *addr = std::addressof(a);
    cout << addr->begin() << " " << addr->end() << " " << addr->size() << endl;



    // your code goes here
    return 0;
}