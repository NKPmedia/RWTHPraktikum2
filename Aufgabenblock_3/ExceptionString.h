#pragma once
#include <exception>
#include <string>

class ExceptionString :
	public std::exception
{
public:
	ExceptionString();
	std::string s;
	ExceptionString(std::string ss);
	~ExceptionString() throw ();
	const char* what() const throw();
};

