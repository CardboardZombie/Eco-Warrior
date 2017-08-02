// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// App.h
// ================================
#ifndef APP_H
#define APP_H

#include <string>
#include <iostream>
#include <ostream>
#include <cstring>
#include <fstream>

using namespace std;

class App
{
public:
	string Name;
	string StandbyMsg;
	bool state;

	App()
	{
		Name = "";
		StandbyMsg = "";
		state = 1;
	}
	App(string name, string onOff,bool power)
	{
		Name = name;
		StandbyMsg = onOff;
		state = power;
	}
	App load(ifstream& inAppFile);
	void print();
};
#endif //App_H