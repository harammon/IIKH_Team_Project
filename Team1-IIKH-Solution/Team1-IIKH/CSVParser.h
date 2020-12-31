#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Exception.h"

class CSVParser {
private:
	static CSVParser * instance;
	static bool IsAllocated;
	CSVParser() {};

public:
	static CSVParser & getInstance() {
		if (IsAllocated) instance = new CSVParser();
		return *instance;
	}
	static void deleteInstance() {
		delete instance;
	}
	std::vector<std::vector<std::string>> read(std::string && name);
	void write(std::string && name, std::vector<std::string> & value);
};

std::vector<std::string> split(std::string & str);

class CSVParserException : public Exception {

public:
	CSVParserException(int e, const char * o) :
		Exception(e, o) {};
	void resolve() {
		std::cout << "CSVParser error (" << error << ") : ";
		switch (error) {
		case 0:
			std::cout << "File Column is incorrect" << std::endl;
			break;
		default:
			std::cout << "Unknown Error" << std::endl;
		}
	}
};