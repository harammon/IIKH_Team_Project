#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"
#include "Exception.h"
#include "Greeter.h"

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	/********** Variables **********/
	PlanDB planDB;
	RecipeDB recipeDB;
	std::vector<std::string> menu;
	Greeter greeter(menu, recipeDB, planDB);
	/*******************************/

	while (true)
	{
		// clear screen
		system("CLS");
		// print the menu for IIKH
		greeter.printMenu();
		// select menu and update the screen to selected menu
		greeter.selectMenu();

		// waits for user to continue
		system("pause");
		
	}
	return 0;

}