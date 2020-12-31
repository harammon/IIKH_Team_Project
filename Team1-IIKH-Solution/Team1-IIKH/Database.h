#pragma once
#include <string>
#include <map>
#include <iostream>

#include "Exception.h"

// class declaration
class Date;
class DBException;

// template declaration
template<class T1, class T2>
struct IsEqual {
	enum { value = false };
};

template<class T>
struct IsEqual<T, T> {
	enum { value = true };
};

template<class _key, class _value>

// stores db map 
// and controls entire DB system
class DataBase {
protected:
	std::map<_key, _value> db;

public:
	// insert pair of key and value
	void _insert(_key k, _value v) { db.insert(std::pair<_key, _value>(k, v)); }

	_value & _select(_key k) {
		// if you do not find key (throws exception)
		if (db.find(k) == db.end()) {
			if (IsEqual<_key, std::string>::value) throw DBException(0, k.c_str());
			else if (IsEqual<_key, Date>::value) throw DBException(1, k.c_str());
			else throw DBException(2, k.c_str());
		}

		// if you find key (return value)
		return (*db.find(k)).second;
	}

	// delete pair of key and value, insert new pair of key and value
	void _update(_key k, _value v) { 
		db.erase(k);
		db.insert(std::pair<_key, _value>(k, v));
	}

	// delete pair of key and value
	void _delete(_key k) { db.erase(k); }

	// show items with given key
	virtual void _show(_key k) = 0;

	// show all items in DB
	virtual void _showAll() = 0;
	
	// save DB(items) to local
	virtual void _save() = 0;
};

// performs handles DB related error
class DBException : public Exception{
public:
	// CTOR: initializes error and option
	DBException(int e, const char * s) :
		Exception(e, s) {};
	// resolve DB Error
	void resolve() {
		// print error type
		std::cout << "DB error (" << error << ") : ";
		
		// resolve by error type
		switch (error) {
			// no searching key in RecipeDB
			case 0:
				std::cout << " >> There is no search result for Recipe(" << option << ")" << std::endl;
				break;

			// no searching key in PlanDB
			case 1:
				std::cout << " >> There is no matching result for searched Plan" << std::endl;
				break;
			
			//  unknown error
			default:
				std::cout << "unknown error" << std::endl;
		}
	}
};