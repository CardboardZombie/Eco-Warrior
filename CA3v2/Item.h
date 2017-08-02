// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Item.h
// ================================
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <ostream>
#include <cstring>
#include <fstream>

using namespace std;

class Item
{
public:
	string Name;
	string Desc;

	Item()
	{
		Name = "Apple";
		Desc = "Something to Eat on your Journey";
	}
	Item(string name, string dsc)
	{
		Name = name;
		Desc = dsc;
	}
	Item load(ifstream& itemFile);
	void print();
};
#endif //ITEM_H