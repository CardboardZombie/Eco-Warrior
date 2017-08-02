// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Creature.cpp
// ================================
#include "Creature.h"
#include "Utility.h"
#include <iostream>
using namespace std;
//=========================Constructor==================================
Random rd;
//========================Fight Related Functions=======================
void Creature::attack(Player& player)
{
	cout << Name << " Attacks you "
		<<"with" << cWeapon.Name << endl;

	if(rd.getRandom(0,20) < Accuracy)
	{
		int damage = rd.getRandomRange(cWeapon.DamageRange);
		cout << "You are Hit!"<< endl;
		player.takeDamage(damage);
	}
	else
	{
		cout << Name << " Missed!" << endl;
	}
	cout << endl;
}
void Creature::takeDamage(int damage)
{
	HitPoints -= damage;
}
Creature Creature::load(ifstream& inFile)
{
	string garbage, name, type;
	int hp, acc, xp;
	Weapon tempWeapon;
	Creature temp;

	inFile>> garbage;
	getline(inFile, name);
	inFile>> garbage;
	getline(inFile, type);
	inFile>> garbage>>hp;
	inFile>> garbage >> acc;
	inFile>> garbage >> xp;
	inFile>> garbage;
	getline(inFile, tempWeapon.Name);
	inFile>> garbage >> tempWeapon.DamageRange.mLow;
	inFile>> garbage >> tempWeapon.DamageRange.mHigh;
	temp = Creature(name, type, hp, acc, xp, tempWeapon);

	return temp;
}
void Creature::print()
{
	cout<<"================================================================================"<<endl;
	cout<<"\t\t\t\tCREATURE STATS"<<endl;
	cout<<"================================================================================"<<endl;
	cout<<"\n\n\nName:\t\t"<<Name<<endl;
	cout<<"Type:\t\t"<<Type<<endl;
	cout<<"HP:\t\t "<<HitPoints<<endl;
	cout<<"Accuracy:\t "<<Accuracy<<endl;
	cout<<"Weapon Name:\t"<<cWeapon.Name<<endl;
	cout<<"Damage Range:\t "<<cWeapon.DamageRange.mLow<<"-"<<cWeapon.DamageRange.mHigh<<endl;
	cout<<"\n\n================================================================================"<<endl;
}
//Make sure the display Hp function is neccessary