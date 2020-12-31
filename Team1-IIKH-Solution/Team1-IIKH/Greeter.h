#pragma once
#include <iostream>
#include <string>
#include <map>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"

// class declaration
class Greeter {
private:
	RecipeDB recipeDB;
	PlanDB planDB;
	std::vector<std::string> menu;
public:
	// CTOR: vector<string> menu, RecipeDB, PlanDB
	Greeter(std::vector<std::string>& _menu, RecipeDB& _recipeDB, PlanDB& _planDB) :
		menu(_menu), recipeDB(_recipeDB), planDB(_planDB) {
		addMenu("SEARCH RECIPE");//1
		addMenu("ADD RECIPE");//2
		addMenu("DELETE RECIPE");//3
		addMenu("VIEW RECIPE");//4
		addMenu("SEARCH PLAN");//5
		addMenu("ADD PLAN");//6
		addMenu("DELETE PLAN");//7
		addMenu("VIEW PLAN");//8
		addMenu("QUIT");//9
	};

	void addMenu(std::string instruction) {
		menu.push_back(instruction);
	}

	void printMenu() {
		// print logo and menu
		std::cout << "IIIIIIIIIIIIIIIIIIIIKKKKKKKKK    KKKKKKKHHHHHHHHH     HHHHHHHHH\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nII::::::IIII::::::IIK:::::::K   K::::::KHH::::::H     H::::::HH\n  I::::I    I::::I  KK::::::K  K:::::KKK  H:::::H     H:::::H  \n  I::::I    I::::I    K:::::K K:::::K     H:::::H     H:::::H  \n  I::::I    I::::I    K::::::K:::::K      H::::::HHHHH::::::H  \n  I::::I    I::::I    K:::::::::::K       H:::::::::::::::::H  \n  I::::I    I::::I    K:::::::::::K       H:::::::::::::::::H  \n  I::::I    I::::I    K::::::K:::::K      H::::::HHHHH::::::H  \n  I::::I    I::::I    K:::::K K:::::K     H:::::H     H:::::H  \n  I::::I    I::::I  KK::::::K  K:::::KKK  H:::::H     H:::::H  \nII::::::IIII::::::IIK:::::::K   K::::::KHH::::::H     H::::::HH\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nIIIIIIIIIIIIIIIIIIIIKKKKKKKKK    KKKKKKKHHHHHHHHH     HHHHHHHHH" << std::endl;
		std::cout << std::endl;
		std::cout << " ********** Here's Menu ********** " << std::endl;
		std::cout << std::endl;

		int size = menu.size();
		for (int i = 1; i <= size; i++)
			std::cout << "  >> Enter [" << i << "] to <" << menu[i - 1] << ">" << std::endl;
	}
	// add instruction to menu (Order matters)
	void selectMenu()
	{
		int selectedNum; std::cin >> selectedNum;
		// clear screen
		system("CLS");
		// print message
		std::cout << "You've selected [" << selectedNum << "] ";
		switch (selectedNum)
		{
			case 1:
			{
				std::cout << "to search recipe" << std::endl;
				searchRecipe();
				break;
			}
			case 2:
			{
				std::cout << "to add recipe" << std::endl;
				addRecipe();
				recipeDB._save();
				break;
			}
			case 3:
			{
				std::cout << "to delete recipe" << std::endl;
				deleteRecipe();
				recipeDB._save();
				break;
			}
			case 4:
			{
				std::cout << "to view recipe" << std::endl;
				recipeDB._showAll();
				break;
			}
			case 5:
			{
				std::cout << "to search plan" << std::endl;
				searchPlan();
				break;
			}
			case 6:
			{
				std::cout << "to add plan" << std::endl;
				addPlan();
				planDB._save();
				break;
			}
			case 7:
			{
				std::cout << "to delete plan" << std::endl;
				deletePlan();
				planDB._save();
				break;
			}
			case 8:
			{
				std::cout << "to view plan" << std::endl;
				planDB._showAll();
				break;
			}
			case 9:
			{
				std::cout << "to QUIT..." << std::endl;
				planDB._save();
				recipeDB._save();
				exit(0);
				break;
			}
			default:
			{
				std::cout << "PLEASE ENTER NUMBER FROM 1 ~ " << menu.size() << std::endl;
				break;
			}
		}
	}
	// search recipe by name
	void searchRecipe()
	{
		std::cout << "Search : " << std::flush;
		std::cin.ignore();
		std::string searchM;
		std::getline(std::cin, searchM);

		// get all recipes names that has searched string
		auto recipeNames = recipeDB._search(std::string(searchM));
		// no search results
		if (recipeNames.size() == 0) {
			std::cout << " >> There is no search result for Recipe(" << searchM << ")" << std::endl;
			return;
		}// has search results
		else {
			std::cout << "There is " << recipeNames.size() << " matching result for \"" << searchM << "\"" << std::endl;
			std::cout << "====================================================" << std::endl;
			std::cout << "====================================================" << std::endl << std::endl;
		}

		for (auto recipeName : recipeNames)
		{
			try
			{
				auto recipe = recipeDB._select(recipeName);
				recipe.print();
			}
			catch (DBException & e)
			{
				e.resolve();
			}
		}
	}

	// add recipe to recipeDB
	void addRecipe()
	{
		std::cout << "Enter recipe information in [[ NAME -> DESCRIPTION -> TIME -> INGREDIENTS ]] order" << std::endl;
		std::cout << "Name			: " << std::flush;	std::cin.clear();	std::cin.ignore();	std::string name;			std::getline(std::cin, name);
		std::cout << "Direction	: " << std::flush;	std::cin.clear();						std::string description;	std::getline(std::cin, description);
		std::cout << "Cooking Time(min)	: " << std::flush;	std::cin.clear();						int time;					std::cin >> time;
		std::cout << "Ingredients (If you want to stop enter \"stop\" ) : " << std::flush;
		std::vector<std::string> ingredients;
		std::cin.ignore();

		while (true)
		{
			std::string ingredient; std::getline(std::cin, ingredient);
			if (ingredient == "stop")break;
			ingredients.push_back(ingredient);
		}

		try
		{
			Recipe* recipe = new Recipe(name, description, time, ingredients);
			recipeDB._insert(name, *recipe);
		}
		catch (DBException & e) {
			e.resolve();
		}
	}

	// add plan to planDB
	void addPlan()
	{
		std::cout << "Enter plan information in [[ YEAR -> MONTH -> DAY -> DAYNAME -> BREAKFAST -> LUNCH -> DINNER ]] order" << std::endl;
		std::cout << "Year        : " << std::flush;
		std::cin.clear();
		std::cin.ignore();
		int year;
		std::cin >> year;

		std::cout << "Month       : " << std::flush;
		std::cin.clear();
		int month;
		std::cin >> month;

		std::cout << "Day         : " << std::flush;
		std::cin.clear();
		int day;
		std::cin >> day;

		std::cout << "Plan Name	: " << std::flush;
		std::cin.clear();
		std::cin.ignore();
		std::string dayName;
		std::getline(std::cin, dayName);

		Meal breakfast = addMeal("Breakfast");
		Meal lunch = addMeal("Lunch    ");
		Meal dinner = addMeal("Dinner   ");
		planDB._insert(Date(year, month, day), Plan(dayName, { breakfast,lunch,dinner }));
	}

	// add Meal and returns Meal instance
	Meal addMeal(std::string mealName)
	{
		std::cout << mealName << " (If you want to stop enter \"stop\" ) : " << std::flush;
		std::vector<std::string> recipeList;

		while (true)
		{
			std::string recipe; std::getline(std::cin, recipe);
			if (recipe == "stop")
				break;
			recipeList.push_back(recipe);
		}
		return Meal(recipeList);
	}

	// search for plan
	void searchPlan()
	{
		std::cout << "Enter date [[ YEAR -> MONTH -> DAY]] order" << std::endl;
		std::cout << "Year        : " << std::flush;
		std::cin.clear();
		std::cin.ignore();
		int year;
		std::cin >> year;

		std::cout << "Month       : " << std::flush;
		std::cin.clear();
		int month;
		std::cin >> month;

		std::cout << "Day         : " << std::flush;
		std::cin.clear();
		int day;
		std::cin >> day;
		
		try
		{
			auto targetPlan = planDB._select(Date(year, month, day));
			targetPlan.print();
		}
		catch (DBException & e)
		{
			e.resolve();
		}
	}

	// delete plan
	void deletePlan()
	{
		std::cout << "Enter date [[ YEAR -> MONTH -> DAY]] order to delete plan" << std::endl;
		std::cout << "Year        : " << std::flush;
		std::cin.clear();
		std::cin.ignore();
		int year;
		std::cin >> year;

		std::cout << "Month       : " << std::flush;
		std::cin.clear();
		int month;
		std::cin >> month;

		std::cout << "Day         : " << std::flush;
		std::cin.clear();
		int day;
		std::cin >> day;

		// select plan
		try
		{
			auto targetPlan = planDB._select(Date(year, month, day));
		}
		catch (DBException & e)
		{
			std::cout << " >> Deletion Failed." << std::endl;
			e.resolve();
			return;
		}
		
		// if plan exists
		planDB._delete(Date(year, month, day));
		std::cout << " >> Deletion Success." << std::endl;

	}

	void deleteRecipe() {
		std::cout << "Enter recipe name which you want to delete : " << std::flush;
		std::cin.ignore();
		std::string searchM;
		std::getline(std::cin, searchM);

		// search 
		auto recipeNames = recipeDB._search(std::string(searchM));

		// no search results
		if (recipeNames.size() == 0) {
			std::cout << " >> Deletion Failed." << std::endl;
			std::cout << " >> There is no search result for Recipe(" << searchM << ")" << std::endl;
			return;
		}// has search results
		else {
			// has Entered correct
			if (searchM.compare(recipeNames[0]) == 0) {
				recipeDB._delete(searchM);
				std::cout << " >> Deletion Success." << std::endl;
			}
			else {
				std::cout << " >> Deletion Failed." << std::endl;
				std::cout << " >> There is no matching recipe for \""<<searchM<<"\""<<std::endl<<" >> Did you meant \"" << recipeNames[0] << "\"? try it again" << std::endl;
			}
		}
	}
};