#include "ExceptionString.h"



ExceptionString::ExceptionString()
{
}


ExceptionString::ExceptionString(std::string ss)
{
	this->s = ss;
}

ExceptionString::~ExceptionString()
{
}

const char* ExceptionString::what() const throw()
{
	return s.c_str();
}