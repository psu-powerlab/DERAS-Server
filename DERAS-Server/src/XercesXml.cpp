#include <string>
#include <iostream>

#include "XercesXml.h"
#include "DOMTreeErrorReporter.hpp"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

using namespace xercesc_3_2;
using namespace xercesc;
using namespace boost::filesystem;
XercesXml::XercesXml()
{
    XMLPlatformUtils::Initialize();
    parser_ = new XercesDOMParser();

    // configure
    std::string pXSD = "/home/tylor/Dev/SEPXerces/data/sep.xsd";
    parser_->setValidationScheme(XercesDOMParser::Val_Always);
    parser_->setDoNamespaces(true);    // optional
    parser_->loadGrammar(pXSD.c_str(),Grammar::SchemaGrammarType, true);
    parser_->setValidationScheme(XercesDOMParser::Val_Always);
    parser_->setDoNamespaces(true);
    parser_->setDoSchema(true);
    parser_->useCachedGrammarInParse(true);

    error_handler_ = new DOMTreeErrorReporter();
    parser_->setErrorHandler(error_handler_);
    //XercesXml::Test();
}

XercesXml::~XercesXml()
{
    delete error_handler_;
    delete parser_;
    XMLPlatformUtils::Terminate();
}

void XercesXml::Test()
{
    try
    {
        boost::filesystem::path p("data/examples/");

        try
        {
            if (exists(p))
            {
                if (is_regular_file(p))
                    std::cout << p << " size is " << file_size(p) << '\n';

                else if (is_directory(p))
                {
                    std::cout << p << " is a directory containing:\n";

                    for (directory_entry& x : directory_iterator(p))
                    {
                        std::string file = (x.path()).string();
                        std::cout << "    " << file << '\n';
                        parser_->parse(file.c_str());
                    }
                }
                else
                    std::cout << p << " exists, but is not a regular file or directory\n";
            }
            else
                std::cout << p << " does not exist\n";
            }

        catch (const filesystem_error& ex)
        {
        std::cout << ex.what() << '\n';
        }
        //string mXML = R"(<FunctionSetAssignmentsList xsi:schemaLocation="urn:ieee:std:2030.5:ns sep.xsd" xmlns="urn:ieee:std:2030.5:ns" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" href="/fsa" subscribable="0" all="1" results="1">  <FunctionSetAssignments subscribable=\"0\" href=\"/fsa/0\">\n    <DERProgramListLink all=\"3\" href=\"/derp\"/>\n    <TimeLink href=\"/dcap/tm\"/>\n    <mRID>800200000000000000000003a1b2c3b4</mRID>\n    <description>FSAX0</description>\n  </FunctionSetAssignments>\n</FunctionSetAssignmentsList>\n)";
        //MemBufInputSource myxml_buf((const XMLByte*)mXML.c_str(), mXML.size(),"myxml (in memory)", false);
        //parser_->parse(myxml_buf);
    }
    catch (const OutOfMemoryException&)
    {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
    }
    catch (const DOMError& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
    }
}

bool XercesXml::validate(std::string xml)
{
    bool valid = true;
    try
    {
        xercesc::MemBufInputSource myxml_buf((const XMLByte*)xml.c_str(), xml.size(),
                                     "buffer", true);
        parser_->parse(myxml_buf);
    }
        catch (const OutOfMemoryException&)
    {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        valid = false;
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        valid = false;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        valid = false;
    }
    catch (const DOMError& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        valid = false;
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
        valid = false;
    }
    bool xml_valid = !error_handler_->getSawErrors();
    error_handler_->resetErrors();
    return valid && xml_valid;
}
