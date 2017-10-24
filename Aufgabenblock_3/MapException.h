#pragma once
#include "ExceptionString.h"

class MapException : public ExceptionString
{
public:
	MapException();
	~MapException() throw();
	MapException(std::string ss);
};

