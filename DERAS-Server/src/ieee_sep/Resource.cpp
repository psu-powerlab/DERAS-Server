///////////////////////////////////////////////////////////
//  Resource.cpp
//  Implementation of the Class Resource
//  Created on:      13-Apr-2020 2:51:40 PM
//  Original author: svanausdall
///////////////////////////////////////////////////////////

#include "ieee_sep/Resource.h"


Resource::Resource(const std::string& uri)
: href(uri), xmlns("urn:ieee:std:2030.5:ns")
{

}



Resource::~Resource(){

}
