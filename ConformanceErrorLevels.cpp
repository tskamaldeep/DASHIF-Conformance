//
// Created by Kamaldeep Tumkur on 26/08/20.
//

#include <iostream>
#include "ConformanceErrorLevels.h"
#include "ConformanceConstraints.h"

using namespace std;
using namespace conformance::exception;
using namespace conformance::constraints;

void ConformanceErrorLevels::initializeConformanceMaps() {
    // Method commenting
    std::map<ConformanceErrorTypes, const std::size_t> *cerrmap = this->conformanceErrorMap();
    std::map<ErrorColorCode, const std::size_t> *ccodemap = this->colorcodeErrorMap();
    std::map<ConformanceEnforcementTypes, const std::size_t> *enforcementserrmap = this->enforcementsErrorMap();

    // Conformance error mapping
    cerrmap->insert(std::pair<ConformanceErrorTypes, const std::size_t> (ConformanceErrorTypes::FATAL, conformance::exception::hashnum(DASHIF_CONFORMANCE_FATAL)));
    cerrmap->insert(std::pair<ConformanceErrorTypes, const std::size_t> (ConformanceErrorTypes::ERROR, conformance::exception::hashnum(DASHIF_CONFORMANCE_ERROR)));
    cerrmap->insert(std::pair<ConformanceErrorTypes, const std::size_t> (ConformanceErrorTypes::WARNING, conformance::exception::hashnum(DASHIF_CONFORMANCE_WARNING)));
    cerrmap->insert(std::pair<ConformanceErrorTypes, const std::size_t> (ConformanceErrorTypes::DEBUG, conformance::exception::hashnum(DASHIF_CONFORMANCE_DEBUG)));
    cerrmap->insert(std::pair<ConformanceErrorTypes, const std::size_t> (ConformanceErrorTypes::INFO, conformance::exception::hashnum(DASHIF_CONFORMANCE_INFO)));
    cerrmap->insert(std::pair<ConformanceErrorTypes, const std::size_t> (ConformanceErrorTypes::VERBOSE, conformance::exception::hashnum(DASHIF_CONFORMANCE_VERBOSE)));

    // Colorcode error mapping
    ccodemap->insert(std::pair<ErrorColorCode, const std::size_t> (ErrorColorCode::RED, conformance::exception::hashnum(DASHIF_CONFORMANCE_FATAL)));
    ccodemap->insert(std::pair<ErrorColorCode, const std::size_t> (ErrorColorCode::AMBER, conformance::exception::hashnum(DASHIF_CONFORMANCE_ERROR)));
    ccodemap->insert(std::pair<ErrorColorCode, const std::size_t> (ErrorColorCode::YELLOW, conformance::exception::hashnum(DASHIF_CONFORMANCE_WARNING)));
    ccodemap->insert(std::pair<ErrorColorCode, const std::size_t> (ErrorColorCode::GRAY, conformance::exception::hashnum(DASHIF_CONFORMANCE_DEBUG)));
    ccodemap->insert(std::pair<ErrorColorCode, const std::size_t> (ErrorColorCode::WHITE, conformance::exception::hashnum(DASHIF_CONFORMANCE_INFO)));
    ccodemap->insert(std::pair<ErrorColorCode, const std::size_t> (ErrorColorCode::GREEN, conformance::exception::hashnum(DASHIF_CONFORMANCE_VERBOSE)));

    // Enforcements error mapping
    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::MUST, conformance::exception::hashnum(DASHIF_CONFORMANCE_FATAL)));
    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::MUST_NOT, conformance::exception::hashnum(DASHIF_CONFORMANCE_FATAL)));

    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::REQUIRED, conformance::exception::hashnum(DASHIF_CONFORMANCE_FATAL)));

    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::SHALL, conformance::exception::hashnum(DASHIF_CONFORMANCE_ERROR)));
    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::SHALL_NOT, conformance::exception::hashnum(DASHIF_CONFORMANCE_ERROR)));

    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::SHOULD, conformance::exception::hashnum(DASHIF_CONFORMANCE_WARNING)));
    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::SHOULD_NOT, conformance::exception::hashnum(DASHIF_CONFORMANCE_WARNING)));

    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::MAY, conformance::exception::hashnum(DASHIF_CONFORMANCE_DEBUG)));
    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::MAY_NOT, conformance::exception::hashnum(DASHIF_CONFORMANCE_DEBUG)));

    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::RECOMMENDED, conformance::exception::hashnum(DASHIF_CONFORMANCE_DEBUG)));

    enforcementserrmap->insert(std::pair<ConformanceEnforcementTypes, const std::size_t> (ConformanceEnforcementTypes::OPTIONAL, conformance::exception::hashnum(DASHIF_CONFORMANCE_INFO)));

}

ConformanceErrorLevels::ConformanceErrorLevels() {
    this->initializeConformanceMaps();
}

ConformanceErrorLevels::ConformanceErrorLevels(ConformanceEnforcementTypes errorLevel) {
    // Add check for init error level in the given types.
    try {
        ConformanceErrorLevels();
        this->setDefaultEnforcementErrorLevel(errorLevel);
    }
    // TODO: Test the exception construction below.
    catch (ConformanceException &e) {
        EXCDETAIL *details;
        std::string excName = e.exceptionName();
        details = e.exceptionDetails();
        EXCDETAIL::iterator *detailsIter = new EXCDETAIL::iterator();
        for (auto const& [stringname, excdescs] :  *details) {
            for (auto const& [excname, descstrs] : excdescs) {
                cout << descstrs.begin() << " " << descstrs.end() << " " << descstrs.size() << endl;
            }
        }

        cout << e.what() << endl;
    }
}

ConformanceErrorTypes ConformanceErrorLevels::errorLevelForConformanceEnforcementType(ConformanceEnforcementTypes errtype) {

    ConformanceErrorTypes etype = DEFAULT_DASHIF_CONFORMANCE_ERROR_LEVEL;
    std::map<ConformanceEnforcementTypes, const std::size_t> *enfmap = this->enforcementsErrorMap();
    const std::size_t errlevelhash = enfmap->operator[](errtype);

    for (auto const& [etype, ehash] : *(this->conformanceErrorMap())) {
        if (static_cast<const size_t>(ehash) == errlevelhash) {
            return static_cast<ConformanceErrorTypes>(etype);
        }
    }

    return etype;
}

ErrorColorCode ConformanceErrorLevels::errorColorCodeForConformanceErrorType(ConformanceErrorTypes errtype) {

    ErrorColorCode retcode = DEFAULT_DASHIF_CONFORMANCE_ERROR_COLOR_CODE;
    std::map<ConformanceErrorTypes, const size_t> *errmap = this->conformanceErrorMap();
    const std::size_t errlevelhash = errmap->operator[](errtype);

    for (auto const& [retcode, errhash] : *(this->colorcodeErrorMap())) {
        if (errhash == errtype) {
            return static_cast<ErrorColorCode>(retcode);
        }
    }

    return retcode;
}

// Set the default error level only for display purposes.
void ConformanceErrorLevels::setDefaultConformanceErrorLevel(ConformanceErrorTypes errorLevel) {
    // TODO: Any additional settings?
    DEFAULT_DASHIF_CONFORMANCE_ERROR_LEVEL = errorLevel;
}

// Set the default enforcement error level for the detail deployed in the check iteration.
void ConformanceErrorLevels::setDefaultEnforcementErrorLevel(ConformanceEnforcementTypes level) {

    DEFAULT_DASHIF_CONFORMANCE_MIN_ENFORCEMENT_LEVEL = level;

    // Also set the corresponding conformance error level, used for display purposes.
    setDefaultConformanceErrorLevel(this->errorLevelForConformanceEnforcementType(level));
}
