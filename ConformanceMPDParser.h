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
        xmlpp::DomParser *parser_;
        xmlpp::Document *xmldocument_ = NULL;
        xmlpp::Node *rootnode_ = NULL;

        bool validate_document_ = true;
        bool throw_messages_ = true;
        bool have_default_attrs_ = true;
        // What is the purpose of substituting entities in the XML DOM tree?

        const std::string &xmldata_;

    public:
        ConformanceMPDParser(const std::string &xmlData) : xmldata_(xmlData) {};

        ConformanceMPDParser(const std::string &xmlData, bool validate, bool throwmsg, bool haveattrs) : xmldata_(xmlData),
        validate_document_(validate), throw_messages_(throwmsg), have_default_attrs_(haveattrs) {}

        xmlpp::DomParser *DOMParser() { return parser_; }

        void validateDocument(bool validate) {
            validate_document_ = validate;
            parser_->set_validate(validate);
        }

        void parserThrowMessages(bool throwmsg) {
            throw_messages_ = throwmsg;
            parser_->set_throw_messages(throwmsg);
        }

        void parserWithDefaultAttributes(bool haveAttrs) {
            have_default_attrs_ = haveAttrs;
            parser_->set_include_default_attributes(haveAttrs);
        }

        const std::string xmlData() { return xmldata_; }
        bool parserWithDefaultAttributes() { return have_default_attrs_; }
        bool parserThrowMessages() { return throw_messages_; }
        bool validateDocument() { return validate_document_; }

        bool parseXML();
        ~ConformanceMPDParser() = default;

    };
}

#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H
