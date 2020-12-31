#pragma once
#include <string>

class Exception {
protected:
	int error;
	std::string option;

public:
	Exception(int e, const char * o) :
		error(e), option(o) {};
	virtual void resolve() = 0;
};