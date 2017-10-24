#include "ParseException.h"
#include "ExceptionString.h"
#include <string>

ParseException::ParseException()
{
}

ParseException::ParseException(std::string ss) : ExceptionString(ss) 
{
}
ParseException::~ParseException() throw () 
{
}
