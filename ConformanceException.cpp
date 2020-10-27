//
// Created by Kamaldeep Tumkur on 26/08/20.
//

#include "ConformanceException.h"
#include <iostream>
#include <ctime>

using namespace std;
using namespace conformance::exception;

std::string ConformanceException::addTimestampDetailsToException() {

    // Add a placeholder to conform to the format.
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
        return descLong;
    }
    catch (std::exception &e) {
        // This is an exception formed at the time of constructing a throwable exception.
        cout << "Error in the ConformanceException module\n" \
 << "Error at: %s\n, __func__" \
 << "Error Description: %s, e.what()" \
 << endl;
        return descLong;
    }
}

ConformanceException::ConformanceException() noexcept {
    // Build the exception description.
    exceptionname_ = genericexceptionname;

    // GenericException init.
    // Short and Long Descriptions. Any stacktraces.
    EXCSTRS genericArr = {genericexceptionstrshort, genericexceptionstrlong};
    EXCDESC *genericexcDesc = new EXCDESC();
    genericexcDesc->insert(EXCSTRPAIR(genericexceptionname, genericArr));
    EXCDETAIL *details = static_cast<EXCDETAIL *>(this->exceptionDetails());
    // std::pair<const std::size_t, std::map<const std::string, std::array<std::string, 2>>> spair = EXCDESCPAIR(genericexceptionhash, *genericexcDesc);

    details->insert(EXCDESCPAIR(genericexceptionhash, *genericexcDesc));

    // IOException init.
    EXCSTRS ioexceptionArr = {ioexceptionstrshort, ioexceptionstrlong};
    EXCDESC *ioexcDesc = new EXCDESC();
    ioexcDesc->insert(EXCSTRPAIR(ioexceptionname, ioexceptionArr));

    details->insert(EXCDESCPAIR(ioexceptionhash, *ioexcDesc));

    // NetworkException init.
    EXCSTRS networkexceptionArr = {networkexceptionstrshort, networkexceptionstrlong};
    EXCDESC *networkexcDesc = new EXCDESC();
    networkexcDesc->insert(EXCSTRPAIR(networkexceptionname, networkexceptionArr));

    details->insert(EXCDESCPAIR(networkexceptionhash, *networkexcDesc));

    // MediaException init.
    EXCSTRS mediaexceptionArr = {mediaexceptionstrshort, mediaexceptionstrlong};
    EXCDESC *mediaexcDesc = new EXCDESC();
    mediaexcDesc->insert(EXCSTRPAIR(mediaexceptionname, mediaexceptionArr));

    details->insert(EXCDESCPAIR(mediaexceptionhash, *mediaexcDesc));

    // BufferException init.
    EXCSTRS bufferexceptionArr = {bufferexceptionstrshort, bufferexceptionstrlong};
    EXCDESC *bufferexcDesc = new EXCDESC();
    bufferexcDesc->insert(EXCSTRPAIR(bufferexceptionname, bufferexceptionArr));

    details->insert(EXCDESCPAIR(bufferexceptionhash, *bufferexcDesc));

    // SecurityException init.
    EXCSTRS securityexceptionArr = {securityexceptionstrshort, securityexceptionstrlong};
    EXCDESC *securityexcDesc = new EXCDESC();
    securityexcDesc->insert(EXCSTRPAIR(securityexceptionname, securityexceptionArr));

    details->insert(EXCDESCPAIR(securityexceptionhash, *securityexcDesc));
}

[[nodiscard]] EXCSTRS ConformanceException::exceptionDescription(const std::size_t exckey) const {
    EXCSTRS descstrings = {"", ""};

    try {

        EXCDETAIL *details = this->exceptionDetails();
        // Iterate
        // Absence of the exchash in the details would signal an invalid hash provided as input.
        for (auto const&[deschash, descstrings] : *details) {
            if (deschash == exckey) {
//                EXCSTRS outputstr = descstrings;
            }
        }

        return descstrings;
    }
    catch (ConformanceException &e) {
        cerr << "DASH-IF Conformance Exception: " << e.what() << endl;
        return descstrings;
    }
    catch (std::exception &e) {
        cerr << "Platform Exception: " << e.what() << endl;
        return descstrings;
    }
}

ConformanceException &ConformanceException::operator=(const ConformanceException &excinstance) noexcept {
    std::string excname = excinstance.exceptionName();
    const std::size_t exchash = hashnum(exceptionname_);

    ConformanceException *exc = new ConformanceException(exchash);

    // Set the exception string to be output.
    std::size_t substrlenshort = std::min(exceptionname_.size(), EXCEPTION_STR_CHAR_LIMIT_SHORT);
    std::size_t substrlenlong = std::min(exceptionname_.size(), EXCEPTION_STR_CHAR_LIMIT_LONG);
    std::string excshort = excinstance.exceptionstrshort_.substr(0, substrlenshort);
    std::string exclong = excinstance.exceptionstrlong_.substr(0, substrlenlong);

    exc->exceptionName(excname);
    exc->exceptionStrShort(exchash, excshort);
    exc->exceptionStrLong(exchash, exclong);

    return *exc;

}

ConformanceException::ConformanceException(const ConformanceException &cexcept) noexcept {
    // Call the default constructor.
    ConformanceException();


}

ConformanceException::ConformanceException(const std::size_t exchash) noexcept {
    if (exchash == ioexceptionhash) {
        exceptionname_ = ioexceptionname;
        exceptionstrshort_ = ioexceptionstrshort;
        exceptionstrlong_ = ioexceptionstrlong;

    } else if (exchash == networkexceptionhash) {
        exceptionname_ = networkexceptionname;
        exceptionstrshort_ = networkexceptionstrshort;
        exceptionstrlong_ = networkexceptionstrlong;

    } else if (exchash == mediaexceptionhash) {
        exceptionname_ = mediaexceptionname;
        exceptionstrshort_ = mediaexceptionstrshort;
        exceptionstrlong_ = mediaexceptionstrlong;

    } else if (exchash == bufferexceptionhash) {
        exceptionname_ = bufferexceptionname;
        exceptionstrshort_ = bufferexceptionstrshort;
        exceptionstrlong_ = bufferexceptionstrlong;

    } else if (exchash == securityexceptionhash) {
        exceptionname_ = securityexceptionname;
        exceptionstrshort_ = securityexceptionstrshort;
        exceptionstrlong_ = securityexceptionstrlong;

    } else {
        exceptionname_ = genericexceptionname;
        exceptionstrshort_ = genericexceptionstrshort;
        exceptionstrlong_ = genericexceptionstrlong;
    };

    // Add in Exception Details.
    this->exceptionStrShort(exchash, exceptionstrshort_);
    this->exceptionStrLong(exchash, exceptionstrlong_);

    // Construct the description object
    EXCSTRS excArr = {exceptionstrshort_, exceptionstrlong_};
    EXCDESC *excDesc = new EXCDESC();
    excDesc->insert(EXCSTRPAIR(exceptionname_, excArr));
    EXCDETAIL *details = static_cast<EXCDETAIL *>(this->exceptionDetails());
    // std::pair<const std::size_t, std::map<const std::string, std::array<std::string, 2>>> spair = EXCDESCPAIR(genericexceptionhash, *genericexcDesc);

    details->insert(EXCDESCPAIR(genericexceptionhash, *excDesc));
}

void ConformanceException::exceptionStrShort(const std::size_t exchash, std::string &strval) {

    exceptionstrshort_ = std::move(strval);

    // Now change in the exception details map.
    for (auto const&[hashval, excdesc] : *this->exceptionDetails()) {
        if (hashval == exchash) {
            EXCDESC desc = excdesc;
            EXCSTRS excstrs = desc.begin()->second;
            std::string currentDesc = excstrs[0];
            std::string newDesc = strval;
        }
    }
}

void ConformanceException::exceptionStrLong(const std::size_t exchash, [[maybe_unused]] std::string &strval) {
    // strval is usually the short form the exception string.
    // Get details of the current timestamp.
    std::string descLong = this->addTimestampDetailsToException();
    // Combine timestamp details with the short-form description of the exception.
    descLong = strval + descLong;

    exceptionstrlong_ = std::move(descLong);
    for (auto const&[hashval, excdesc] : *this->exceptionDetails()) {
        if (hashval == exchash) {
            EXCDESC desc = excdesc;

        }
    }

    // ConformanceException(exchash);

}

