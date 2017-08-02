// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Weapon.h
// ================================
#ifndef WEAPON_H
#define WEAPON_H

#include "Utility.h"
#include <string>
#include <iostream>
#include <ostream>
#include <cstring>
#include <fstream>
using namespace std;

class Weapon
{
public:
	string Name;
	Range DamageRange;

	Weapon()
	{
		Name="";
		DamageRange.mLow = 1;
		DamageRange.mHigh = 2;
	}
	Weapon(string name, int dLow, int dHigh)
	{
		Name= name;
		DamageRange.mLow = dLow;
		DamageRange.mHigh = dHigh;
	}
	Weapon load(ifstream& weaponFile);
	void print();
};

#endif //WEAPON_H