// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Room.h
// ================================
#ifndef ROOM_H
#define ROOM_H

#include "Weapon.h"
#include "Item.h"
#include "App.h"

#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <cstring>
#include <fstream>
using namespace std;

class Room
{
public:
	//Constructor
	Room()
	{
		Name = "Bedroom";
		Desc = "Nothing";//Room Description
		key = "None";
		weaponName = "";
		appName= "";
		itemName = "";
		NumOfExits = 1;//Number of Attached Rooms
		Exits;
	}
	Room(const string& name, const string& desc, const string& keyObj, string wName,
		string aName, string iName, int noOfExits, vector<string> newExits)
	{
		Name = name;
		Desc = desc;//Room Description
		key = keyObj;
		weaponName = wName;
		appName = aName;
		itemName = iName;
		NumOfExits = noOfExits;//Number of Attached Rooms
		Exits = newExits;
	}

	//Methods
	string getName()
	{
		return Name;
	}
	string getDesc()
	{
		return Desc;
	}
	string getKeyObj()
	{
		return key;
	}
	string getWeapon()
	{
		return weaponName;
	}
	string getItem()
	{
		return itemName;
	}
	string getApp()
	{
		return appName;
	}
	int getNumOfExits()
	{
		return NumOfExits;
	}
	vector<string> ExitList()
	{
		return Exits;
	}
	void setApp(string str)
	{
		appName = str;
	}
	void setWeapon(string str)
	{
		weaponName = str;
	}
	void setItem(string str)
	{
		itemName = str;
	}
	void addExits(string exit)
	{
		Exits.push_back(exit);
	}
	void clearExits()
	{
		Exits.clear();
	}
	void print();//prints the details of the room
	Room load(ifstream& inRoomFile);//used for loading rooms from a file

private:
	//Data members
	string Name;
	string Desc;//Room Description
	string key;
	string weaponName;
	string appName;
	string itemName;
	int NumOfExits;//Number of Attached Rooms
	vector<string> Exits;
};
#endif