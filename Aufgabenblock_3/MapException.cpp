#include "MapException.h"
#include "ExceptionString.h"
#include <string>


MapException::MapException()
{
}


MapException::~MapException() throw()
{
}

MapException::MapException(std::string ss) : ExceptionString(ss)
{
}