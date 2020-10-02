//
// Created by Kamaldeep Tumkur on 27/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEEXCEPTIONTYPES_H
#define DASHIF_CONFORMANCE_CONFORMANCEEXCEPTIONTYPES_H

#include <string>
#include <exception>
#include <map>
#include <array>

namespace conformance::exception {

#if !defined(EXCDETAIL) && !defined(EXCDESCPAIR) && !defined(EXCDESC) && !defined(EXCSTRPAIR) && !defined(EXCSTRS)
#define EXCSTRS std::array<std::string, 2>
#define EXCSTRPAIR std::pair<const std::string, EXCSTRS>
#define EXCDESC std::map<const std::string, EXCSTRS>
#define EXCDESCPAIR std::pair<const std::size_t, EXCDESC>
#define EXCDETAIL std::map<const std::size_t, EXCDESC>
#endif

    const std::string genericexceptionname = "ConformanceGenericException";
    const std::size_t genericexceptionhash = std::hash<std::string>{}(genericexceptionname);
    std::string genericexceptionstrshort = "A Generic conformance exception was observed";
    std::string genericexceptionstrlong = genericexceptionname + ": " + genericexceptionstrshort;


    const std::string ioexceptionname = "ConformanceIOException";
    const std::size_t ioexceptionhash = std::hash<std::string>{}(ioexceptionname);
    std::string ioexceptionstrshort = "An IO type conformance exception was observed";
    std::string ioexceptionstrlong = ioexceptionname + ": " + ioexceptionstrshort;

    const std::string networkexceptionname = "ConformanceNetworkException";
    const std::size_t networkexceptionhash = std::hash<std::string>{}(networkexceptionname);
    std::string networkexceptionstrshort = "A Network type conformance exception was observed";
    std::string networkexceptionstrlong = networkexceptionname + ": " + networkexceptionstrshort;

    const std::string mediaexceptionname = "ConformanceMediaException";
    const std::size_t mediaexceptionhash = std::hash<std::string>{}(mediaexceptionname);
    std::string mediaexceptionstrshort = "A media type conformance exception was observed";
    std::string mediaexceptionstrlong = mediaexceptionname + ": " + mediaexceptionstrshort;

    const std::string bufferexceptionname = "ConformanceBufferException";
    const std::size_t bufferexceptionhash = std::hash<std::string>{}(bufferexceptionname);
    std::string bufferexceptionstrshort = "A Buffer type conformance exception was observed";
    std::string bufferexceptionstrlong = bufferexceptionname + ": " + bufferexceptionstrshort;

    const std::string securityexceptionname = "ConformanceSecurityException";
    const std::size_t securityexceptionhash = std::hash<std::string>{}(securityexceptionname);
    std::string securityexceptionstrshort = "A Security type conformance exception was observed";
    std::string securityexceptionstrlong = securityexceptionname + ": " + securityexceptionstrshort;


    std::size_t hashnum(const std::string val) noexcept { return typeid(val).hash_code(); }

}

#endif //DASHIF_CONFORMANCE_CONFORMANCEEXCEPTIONTYPES_H