#pragma once
#include <exception>
#include <string>
#include "ExceptionString.h"

class ParseException : public ExceptionString
{
public:
	ParseException();
	ParseException(std::string ss);
	~ParseException() throw ();
};
