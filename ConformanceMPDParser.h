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

        const Glib::ustring &xmldata_;

    public:
        ConformanceMPDParser(const Glib::ustring &xmlData) : xmldata_(xmlData) {};

        ConformanceMPDParser(const Glib::ustring &xmlData, bool validate, bool throwmsg, bool haveattrs) : xmldata_(xmlData),
        validate_document_(validate), throw_messages_(throwmsg), have_default_attrs_(haveattrs) {}

        xmlpp::DomParser *DOMParser() { return parser_; }

        const Glib::ustring xmlData() { return xmldata_; }

        void validateDocument(bool validate) {
            validate_document_ = validate;
            parser_->set_validate(validate);
        }

        bool validateDocument() { return validate_document_; }

        void parserThrowMessages(bool throwmsg) {
            throw_messages_ = throwmsg;
            parser_->set_throw_messages(throwmsg);
        }

        bool parserThrowMessages() { return throw_messages_; }

        void parserWithDefaultAttributes(bool haveAttrs) {
            have_default_attrs_ = haveAttrs;
            parser_->set_include_default_attributes(haveAttrs);
        }

        bool parserWithDefaultAttributes() { return have_default_attrs_; }

        bool parseXML();

        ~ConformanceMPDParser() = default;
//
//
    };
//
}

#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H
