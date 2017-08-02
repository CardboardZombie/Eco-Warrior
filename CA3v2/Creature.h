// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Creature.h
// ================================

#ifndef CREATURE_H
#define CREATURE_H

#include "Weapon.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <ostream>
#include <cstring>
#include <fstream>
using namespace std;
class Player;
class Creature
{
public:
	Creature()
	{
		Name = "Dobby";
		Type = "Goblin";
		HitPoints = 5;
		Accuracy = 2;
		ExpReward = 100;
		cWeapon.Name = "a Sock";
		cWeapon.DamageRange.mLow = 5;
		cWeapon.DamageRange.mHigh = 10;
	}
	Creature(string name, string type, int hp, int acc,
		int xpReward, Weapon eWeapon)
	{
		Name = name;
		Type = type;
		HitPoints = hp;
		Accuracy = acc;
		ExpReward = xpReward;
		cWeapon.Name = eWeapon.Name;
		cWeapon.DamageRange.mLow = eWeapon.DamageRange.mLow;
		cWeapon.DamageRange.mHigh = eWeapon.DamageRange.mHigh;
	}
	bool isDead()
	{
		if(HitPoints <= 0)
			return true;
		return false;
	}
	int getXPReward()
	{
		return ExpReward;
	}
	string getName()
	{
		return Name;
	}
	string getType()
	{
		return Type;
	}
	int getHitPoints()
	{
		return HitPoints;
	}
	Weapon getWeapon()
	{
		return cWeapon;
	}
	void attack(Player& player);
	void takeDamage(int damage);
	Creature load(ifstream& inFile);
	void print();

private:
	string Name;
	string Type;
	int HitPoints;
	int Accuracy;
	int ExpReward;
	Weapon cWeapon;
};

#endif //Creature_H