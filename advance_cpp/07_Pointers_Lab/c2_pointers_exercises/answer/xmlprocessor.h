#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include "xmlstubs.h"

class XMLProcessor {
public:
	XMLProcessor();
	~XMLProcessor();
protected:
    DOMParser *parser ;
    ErrorHandler* errHandler; 
    DOMDocument *doc;
    DOMElement *element;
    char*  xmlMsg; 
};

XMLProcessor::XMLProcessor()
	: parser( new DOMParser ),
	errHandler( new ErrorHandler ),
	doc( new DOMDocument ),
	element( 0 )
	{}

XMLProcessor::~XMLProcessor()
{
   if( parser )
   {   
      delete parser;
   }   
   delete errHandler;
   if (doc)
   {
      delete doc;
   }
   if (errHandler)
   {
      delete errHandler;
   }
   if (element)
   {
      delete element;
   }
   if (xmlMsg)
   {
      delete xmlMsg;
   }
}

#endif
