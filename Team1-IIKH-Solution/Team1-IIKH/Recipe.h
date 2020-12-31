#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "Database.h"

// stores recipe's name, description, ingredients, time
// and performs action related to recipe and it's member.
class Recipe {
private:
	// Recipe's Name
	std::string name;
	// Recipe's Description
	std::string description;
	// Recipe's Ingredients: it is set of ingredient(we use "string" for ingredient)
	std::set<std::string> ingredients;
	// Recipe's Expected Time it takes to cook. 
	int time;
	
public:
	// CTOR: name(str), description(str), time(int), ingredients(Vector)
	Recipe(std::string & n, std::string & d, int t, std::vector<std::string> i) :
		name(n), description(d), time(t), ingredients() {
		// insert all ingredient to ingredients set
		for (std::string s : i)
			ingredients.insert(s);
	};
	
	/* GET */
	// get Recipe name
	const std::string & getName() const { return name; }
	// get Recipe description
	const std::string & getDescription() const { return description; }
	// get Recipe ingredients
	const std::set<std::string> & getIngredients() const { return ingredients; }
	// get Recipe time
	int getTime() const { return time; }

	/* SET */
	// sets Recipe name
	void setName(std::string & n) { name = n; }
	// sets Recipe description
	void setDescription(std::string & d) { description = d; }
	// sets Recipe time
	void setTime(int t) { time = t; }

	/* Functions */
	// insert Recipe ingredient to ingredients set. and returns second stored value
	bool addIngredient(std::string & n) { return ingredients.insert(n).second; }
	// remove Recipe ingredient to ingredients set. and returns second stored value
	bool removeIngredient(std::string & n) { return ingredients.erase(n) == 1; }
	// find if there is ingredient
	bool searchIngredient(std::string & n) { return ingredients.find(n) != ingredients.end(); }

	// print Recipe data
	void print() {
		std::cout << " >> Recipe Name : " << name << std::endl;
		std::cout << " >> Ingredients : " << std::endl;
		for (std::string s : ingredients)
			std::cout << "  - " << s << std::endl;
		std::cout << " >> Cooking Time(min) : " << time << std::endl;
		std::cout << " >> Direction(How To Cook)"<< std::endl << "  - " << description << std::endl;
		std::cout << "----------------------------------------------------"<<std::endl;

	}
};

// database manager for Recipe
// performs file I/O operations, db items printing
class RecipeDB : public DataBase<std::string, Recipe> {
private:

public:
	// CTOR
	RecipeDB();
	// DTOR
	~RecipeDB() { _save(); };

	// select item by given date and print 
	void _show(std::string key) {
		this->_select(key).print();
	}

	// show all items in DB
	void _showAll() {
		for (std::pair<std::string, Recipe> s : db)
			s.second.print();
	}

	// save to local
	void _save();

	// search [contained substring is also searched]
	std::vector<std::string> _search(std::string && name) {
		std::vector<std::string> res = {};
		for (auto record : db)
			if (record.first.find(name) != std::string::npos)
				res.push_back(record.first);
		return res;
	}
};