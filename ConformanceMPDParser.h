//
// Created by Kamaldeep Tumkur on 31/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H
#define DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H

#include <libxml++/libxml++.h>
#include <cstdlib>

namespace conformance::parser {
    using namespace xmlpp;

    class ConformanceMPDParser {
    private:
        xmlpp::DomParser *dparser_; // = new xmlpp::DomParser();
//        xmlpp::Document xmldocument;
//        xmlpp::Node rootnode;

        bool validate_document_ = true;
        bool throw_messages_ = true;
        bool have_default_attrs_ = true;
        // What is the purpose of substituting entities in the XML DOM tree?

        const std::string &xmldata_;

    public:
        ConformanceMPDParser(const std::string &xmlData) : xmldata_(xmlData) {};

        void ConformanceMPDParserWithFile(const std::string &xmlfile, bool validate, bool throwmsg, bool haveattrs) {
            dparser_ = new xmlpp::DomParser(xmlfile);

            validate_document_ = validate;
            dparser_->set_validate(validate);

            throw_messages_ = throwmsg;
            dparser_->set_throw_messages(throwmsg);

            have_default_attrs_ = haveattrs;
            dparser_->set_include_default_attributes(haveattrs);
        }

        xmlpp::DomParser *parser() { return dparser_; }

        void validateDocument(bool validate) {
            validate_document_ = validate;
            dparser_->set_validate(validate);
        }

        void parserThrowMessages(bool throwmsg) {
            throw_messages_ = throwmsg;
            dparser_->set_throw_messages(throwmsg);
        }

        void parserWithDefaultAttributes(bool haveAttrs) {
            have_default_attrs_ = haveAttrs;
            dparser_->set_include_default_attributes(haveAttrs);
        }

        void parseXMLContents();

        const std::string &xmlData() { return xmldata_; }
        bool parserWithDefaultAttributes() { return have_default_attrs_; }
        bool parserThrowMessages() { return throw_messages_; }
        bool validateDocument() { return validate_document_; }

        ~ConformanceMPDParser() = default;

    };
}

#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDPARSER_H
