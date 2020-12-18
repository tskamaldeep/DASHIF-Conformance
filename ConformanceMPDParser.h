//
// Created by Kamaldeep Tumkur on 31/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H
#define DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H

#include <libxml++/libxml++.h>
#include <cstdlib>

namespace conformance::parser {

    class ConformanceMPDParser {
    private:
        xmlpp::DomParser dparser;
//        xmlpp::Document xmldocument;
//        xmlpp::Node rootnode;

        bool validate_document_ = true;
        bool throw_messages_ = true;
        bool have_default_attrs_ = true;
        // What is the purpose of substituting entities in the XML DOM tree?

        const std::string &xmldata_;

    public:
        ConformanceMPDParser(const std::string &xmlData) : xmldata_(xmlData) {};

        ConformanceMPDParser(const std::string &xmlData, bool validate, bool throwmsg, bool haveattrs) : xmldata_(xmlData),
        validate_document_(validate), throw_messages_(throwmsg), have_default_attrs_(haveattrs) {
//            dparser.set_validate(validate);
//            dparser.set_throw_messages(throwmsg);
//            dparser.set_include_default_attributes(haveattrs);
        }

        xmlpp::DomParser *DOMParser() { return &dparser; }

        void validateDocument(bool validate) {
            validate_document_ = validate;
            dparser.set_validate(validate);
        }

        void parserThrowMessages(bool throwmsg) {
            throw_messages_ = throwmsg;
            dparser.set_throw_messages(throwmsg);
        }

        void parserWithDefaultAttributes(bool haveAttrs) {
            have_default_attrs_ = haveAttrs;
            dparser.set_include_default_attributes(haveAttrs);
        }

        void parseXMLContents();

        const std::string xmlData() { return xmldata_; }
        bool parserWithDefaultAttributes() { return have_default_attrs_; }
        bool parserThrowMessages() { return throw_messages_; }
        bool validateDocument() { return validate_document_; }

        ~ConformanceMPDParser() = default;

    };
}

#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H
