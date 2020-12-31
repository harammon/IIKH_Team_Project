#pragma once
#include <set>
#include <string>
#include <iostream>

#include "Database.h"
#include "Recipe.h"

// stores a lot of RecipeNames
class Meal {
private:
	// set, sorts recipes in alphabetical order
	std::set<std::string> recipeNames;

public:
	// CTOR: saves Recipe vector[argument] into RecipeNames set[class member]
	Meal(std::vector<std::string> r) {
		for (std::string s : r)
			recipeNames.insert(s);
	}

	// return current recipes
	auto & getRecipes() { return recipeNames; }
	// add new recipe into Recipes set[class member]
	void addRecipes(std::string & n) { recipeNames.insert(n);}
	// if the recipe target[argument] is in the recipes, return 1, else return 0
	bool searchRecipes(std::string & target) {return recipeNames.find(target) != recipeNames.end();}
	// delete target recipe from Recipes set[class member]
	void deleteRecipes(std::string & target) { recipeNames.erase(target); }

	// print all recipes
	void print() {
		std::cout << std::endl;
		for (std::string recipe : recipeNames) {
			std::cout <<" - "<< recipe << std::endl;
		}
		std::cout<<std::endl;
	}

	// returns plan instance to string
	std::string toString() const {
		std::string res = { '"' };
		for (auto value : recipeNames)
			res += value + ',';
		res[res.size() - 1] = '"';

		// In case of Empty Meal => should push one more "
		if (res.size() == 1) {
			res += '"';
		}

		return res;
	}
};


class Date {
private:
	// variables for Date
	int year, month, day;

public:
	// CTOR
	Date(int y, int m, int d) :
		year(y), month(m), day(d) {	};
	
	Date(const char * d) { sscanf_s(d, "%04d%02d%02d", &year, &month, &day); };

	// date ordering standard
	friend bool operator<(const Date & first, const Date & second) {
		if (first.year < second.year) return true;
		if (first.year > second.year) return false;
		if (first.month < second.month) return true;
		if (first.month > second.month) return false;
		if (first.day < second.day) return true;
		return false;
	}

	// returns Date instance to string
	std::string toString() const {
		char buf[9];
		sprintf_s(buf, "%04d%02d%02d", year, month, day);
		return std::string(buf);
	}

	// return dateString into .c format string
	const char * c_str() const {
		return toString().c_str();
	}
};

// stores Meals(Breakfast, Lunch, Dinner) which is daily meal plan
class Plan {
private:
	// Plan name
	std::string name;

	// Plan has three meal instance
	Meal Breakfast, Lunch, Dinner;

public:
	// CTOR name date mealVector
	Plan(std::string & n, std::vector<Meal> m) :
		name(n), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]) {};
	
	/* GET */
	// get Plan name
	const std::string & getName() const { return name; }
	// get Breakfast Meal
	const Meal & getBreakfast() { return Breakfast; }
	// get Lunch Meal
	const Meal & getLunch() { return Lunch; }
	// get Dinner Meal
	const Meal & getDinner() { return Dinner; }

	/* SET */
	// set Plan name
	void setName(std::string & _name) { name = _name; }
	// set Breakfast Meal
	void setBreakfast(Meal & b) { Breakfast = b; }
	// set Lunch Meal
	void setLunch(Meal & l) { Lunch = l; }
	// set Dinner Meal
	void setDinner(Meal & d) { Dinner = d; }

	// prints all meal plan
	void print() {
		std::cout << " Plan Name	: " << name<<std::endl;
		std::cout << " >> Breakfast"; Breakfast.print(); std::cout ;
		std::cout << " >> Lunch"; Lunch.print(); std::cout;
		std::cout << " >> Dinner"; Dinner.print(); std::cout;
		std::cout << "----------------------------------------------------" << std::endl;
	}
};

// database manager for Plan(name + 3 meal)
// performs file I/O operations, db items printing
class PlanDB : public DataBase<Date, Plan> {
private:
	  
public:
	// CTOR
	PlanDB();
	// DTOR
	~PlanDB() { _save(); };

	// select item by given date and print 
	void _show(Date key) {
		this->_select(key).print();
	}

	// show all items in DB
	void _showAll() {
		for (auto p : db) {
			p.second.print();
		}
	}
	// save into local
	void _save();
};