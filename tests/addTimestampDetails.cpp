//
// Created by Kamaldeep Tumkur on 23/10/20.
//
#include <string>
#include <iostream>
#include <ctime>

std::string addTimestampDetailsToException() {

    // Add a placeholder to conform to the format.
    std::string descLong = "<epochmsecs> <mm-dd-yy> <hh:mm:ss TZ>";

    try {
        std::chrono::system_clock::time_point systime = std::chrono::system_clock::now();
        std::size_t epochMilliSecs = std::chrono::duration_cast<std::chrono::milliseconds>(
                systime.time_since_epoch()).count();
        std::time_t syslocaltime = std::chrono::system_clock::to_time_t(systime);
        std::tm tm = *std::localtime(&syslocaltime);

        // Form the timestamp using the formatter: seconds since epoch - mm-dd-yy hh:mm:ss:mls
        std::string epochStr = std::to_string(epochMilliSecs);
        std::string descDate = std::to_string(tm.tm_mon) + "-" + std::to_string(tm.tm_mday) + "-" + std::to_string(tm.tm_year);
        std::string descTime = std::to_string(tm.tm_hour) + ":" + std::to_string(tm.tm_min) + ":" + std::to_string(tm.tm_sec) + " " + std::string(tm.tm_zone);

        descLong = epochStr + " " + descDate + " " + descTime;
        return descLong;
    }
    catch (std::exception &e) {
        // This is an exception formed at the time of constructing a throwable exception.
        std::cout << "Error in the ConformanceException module\n" << "Error at: %s\n, __func__" << "Error Description: %s, e.what()" << std::endl;
        return descLong;
    }
}

int main(int argc, char **argv) {
    std::string descLong = addTimestampDetailsToException();
    std::cout << descLong << std::endl;
}