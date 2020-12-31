#include "Plan.h"
#include "CSVParser.h"

PlanDB::PlanDB() {
	enum { NAME = 0, DATE, BRACKFAST, LUNCH, DINNER };
	auto DB = CSVParser::getInstance().read(std::string("IIKHPlanDB.csv"));
	for (auto record : DB) {
		if (record.size() != 5) throw CSVParserException(0, "");
		Date date(record[DATE].c_str());
		this->_insert(
			date, 
			Plan( 
				record[NAME], {
					Meal(split(record[BRACKFAST])),
					Meal(split(record[LUNCH])),
					Meal(split(record[DINNER])) 
				}
			)
		);
	}
}

void PlanDB::_save() {
	std::string line;
	std::vector<std::string> res;
	for (auto record : db) {
		line.erase();
		line += record.second.getName() + ',';
		line += record.first.toString() + ',';
		line += record.second.getBreakfast().toString() + ',';
		line += record.second.getLunch().toString() + ',';
		line += record.second.getDinner().toString();
		res.push_back(line);
	}
	CSVParser::getInstance().write(std::string("IIKHPlanDB.csv"), res);
}