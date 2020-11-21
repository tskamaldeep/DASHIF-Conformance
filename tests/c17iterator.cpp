#include <iostream>
#include <cstdlib>
#include <map>
#include <memory>
#include <iterator>
#include <string>
#include <chrono>
#include <ctime>
#include <typeinfo>

#include "../ConformanceException.h"
#include "../ConformanceConstraints.h"
#include "../ConformanceMPDCheckSequence.h"

using namespace conformance::exception;
using namespace conformance::constraints;
using namespace conformance::download;
using namespace std;

//    enum ConstraintDefEvalStatus : std::int16_t {
//        SUCCESS = 0,
//        CONDITIONAL_SUCCESS = 1,
//        FAILURE = 2,
//    };


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
    // cout << addr->begin() << " " << addr->end() << " " << addr->size() << "\n" << endl;

    bool d = true;
    std::list<int> *intlist = new std::list<int>();

    intlist->push_back(1);
    intlist->push_back(2);
    intlist->push_back(3);
    intlist->push_back(4);

    // cout << "a: " << typeid(a).name() << endl;
    // cout << "Intlist " << typeid(intlist).name() << endl;
    //cout << std::string(typeid(a).name());

    std::string descLong = "<epochmsecs> <mm-dd-yy> <hh:mm:ss TZ>";

    try {
        std::chrono::system_clock::time_point systime = std::chrono::system_clock::now();
        std::size_t epochMilliSecs = std::chrono::duration_cast<std::chrono::milliseconds>(
                systime.time_since_epoch()).count();
        std::time_t syslocaltime = std::chrono::system_clock::to_time_t(systime);
        std::tm tm = *std::localtime(&syslocaltime);

        // Form the timestamp using the formatter: seconds since epoch - mm-dd-yy hh:mm:ss:mls
        std::string epochStr = to_string(epochMilliSecs);
        std::string descDate = to_string(tm.tm_mon) + "-" + to_string(tm.tm_mday) + "-" + to_string(tm.tm_year);
        std::string descTime = to_string(tm.tm_hour) + ":" + to_string(tm.tm_min) + ":" + to_string(tm.tm_sec) + " " +
                               std::string(tm.tm_zone);

        descLong = epochStr + " " + descDate + " " + descTime;
    }
    catch (std::exception &e) {
        // This is an exception formed at the time of constructing a throwable exception.
        // cout << "Error in the ConformanceException module\n" << "Error at: %s\n, __func__" << "Error Description: %s, e.what()" << endl;
    }

    cout << "Exception Description: " << descLong << std::endl;

    conformance::constraints::ConstraintDefEvalStatus stat1 = conformance::constraints::ConstraintDefEvalStatus::SUCCESS;
    conformance::constraints::ConstraintDefEvalStatus stat2 = conformance::constraints::ConstraintDefEvalStatus::CONDITIONAL_SUCCESS;

    int16_t status = stat1 + stat2;
    ConstraintDefEvalStatus result = static_cast<ConstraintDefEvalStatus>(status);

    cout << typeid(stat1).name() << " " << typeid(stat2).name() << " " << typeid(status).name() << " " << static_cast<int16_t>(result) << endl;

    // your code goes here
    return 0;
}