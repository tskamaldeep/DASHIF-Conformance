//
// Created by Kamaldeep Tumkur on 26/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEEXCEPTION_H
#define DASHIF_CONFORMANCE_CONFORMANCEEXCEPTION_H

#include "ConformanceExceptionTypes.h"

namespace conformance::exception {

#if !defined(CDEBUG)
#define CDEBUG 1
#endif

    const std::size_t EXCEPTION_STR_CHAR_LIMIT_SHORT = 1024;
    const std::size_t EXCEPTION_STR_CHAR_LIMIT_LONG = 65535;

    class ConformanceException : public std::exception {
    private:
        std::string exceptionname_;
        std::string exceptionstrshort_;
        std::string exceptionstrlong_;

        // Instantiate exception Details.
        EXCDETAIL *exceptionDetails_ = new EXCDETAIL();

        static std::string addTimestampDetailsToException();
        // void printException();

    public:
        ConformanceException() noexcept;

        ConformanceException(const std::size_t exchash) noexcept;

        ConformanceException(const ConformanceException &) noexcept;

        ConformanceException &operator=(const ConformanceException &) noexcept;

        ~ConformanceException() = default;

        const char *what() const noexcept override {
            return exceptionstrlong_.c_str();
        };

        std::string exceptionName() const {
            return exceptionname_;
        };

        [[nodiscard]] EXCSTRS exceptionDescription(const std::size_t exckey) const;

        void exceptionDescription(const std::size_t exckey, EXCDESC *desc);

        // Fix syntax/return type.
        EXCDETAIL *exceptionDetails() const {
            return exceptionDetails_;
        }

        void exceptionName(std::string &val) {
            exceptionname_ = std::move(val);
        };

        void exceptionStrShort(const std::size_t exchash, std::string &strval);

        void exceptionStrLong(const std::size_t exchash, std::string &strval);
    };
}

#endif //DASHIF_CONFORMANCE_CONFORMANCEEXCEPTION_H
