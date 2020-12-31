#include <fstream>
#include <sstream>
#include "CSVParser.h"

CSVParser * CSVParser::instance = nullptr;
bool CSVParser::IsAllocated = false;

std::vector<std::vector<std::string>> CSVParser::read(std::string && name) {
	std::ifstream file(name, std::ios::in);
	std::string line, value = {};
	std::vector<std::vector<std::string>> result = {};
	std::vector<std::string> record = {};
	bool IsDblDot = true;

	// 파일이 없는 경우 새로 생성 후 열기
	if (!file.is_open()) {
		std::vector<std::string> empty;
		write(std::string(name), empty);
		return result;
	}

	while (!file.eof()) {
		std::getline(file, line);
		if (line.size() < 1) continue;
		for (char c : line) {
			switch (c) {
			case ',':
				if (IsDblDot) {
					record.push_back(value);
					value.erase();
				}
				else value += c;
				break;
			case '"':
				IsDblDot = !IsDblDot;
				break;
			default:
				value += c;
			}
		}
		record.push_back(value);
		result.push_back(record);
		value.erase();
		record.clear();
	}
	return result;
}

void CSVParser::write(std::string && name, std::vector<std::string> & value) {
	std::ofstream file(name, std::ios::out | std::ios::trunc);
	for (auto line : value) {
		file << line << std::endl;
	}
}

std::vector<std::string> split(std::string & str)
{
	std::stringstream string(str);
	std::string temp;
	std::vector<std::string> result;
	while (!string.eof()) {
		std::getline(string, temp, ',');
		result.push_back(temp);
	}
	return result;
}
