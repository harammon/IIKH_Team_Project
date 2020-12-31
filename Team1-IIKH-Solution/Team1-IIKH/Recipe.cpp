#include "Recipe.h"
#include "CSVParser.h"

#include <vector>

RecipeDB::RecipeDB() {
	enum { NAME = 0, DESCRIPTION, TIME, INGREDIENT };
	auto DB = CSVParser::getInstance().read(std::string("IIKHRecipeDB.csv"));
	for (auto record : DB) {
		if (record.size() != 4) throw CSVParserException(0, "");
		this->_insert(record[NAME], Recipe(record[NAME], record[DESCRIPTION], std::atoi(record[TIME].c_str()), split(record[INGREDIENT])));
	}
}

void RecipeDB::_save() {
	std::string ingredientBuffer = {}, line = {};
	std::vector<std::string> res;
	for (auto record : db) {
		ingredientBuffer += '"';
		for (auto var : record.second.getIngredients()) {
			ingredientBuffer += var;
			ingredientBuffer += ",";
		}
		ingredientBuffer[ingredientBuffer.size() - 1] = '"';
		// In case of Empty ingredient => should push one more "
		if (ingredientBuffer.size() == 1) {
			ingredientBuffer += '"';
		}
		line = record.second.getName() + ',';
		line += record.second.getDescription() + ',';
		line += std::to_string(record.second.getTime()) + ',';
		line += ingredientBuffer;
		res.push_back(line);
		line.erase();
		ingredientBuffer.erase();
	}
	CSVParser::getInstance().write(std::string("IIKHRecipeDB.csv"), res);
}