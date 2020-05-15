#ifndef XERCESXML_H
#define XERCESXML_H
#include <string>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "DOMTreeErrorReporter.hpp"
#include <xercesc/util/OutOfMemoryException.hpp>

class XercesXml
{
    public:
        XercesXml();
        virtual ~XercesXml();
        void Test();
        bool validate(std::string xml);

    private:
        XercesDOMParser* parser_;
        DOMTreeErrorReporter* error_handler_;
};

#endif // XERCESXML_H
