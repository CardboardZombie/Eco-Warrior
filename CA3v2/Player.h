#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "App.h"
#include "Weapon.h"
#include "Creature.h"
#include "Utility.h"

#include <iostream>
#include <string>
#include <ostream>
#include <cstring>
#include <fstream>
using namespace std;

class Player
{
public:
	//Constructor
	Player();
	Player(const string& name,const string& pass, int acc, int xp, int lvl, int hp, 
			int maxhp, int lvlUP, int money, Weapon tempWeapon, string startPos);
	
	void initializePlayer();
	//Methods
	bool isDead()
	{
		if(HitPoints <= 0)
		{
			MaxHitPoints -= (int)(floor(MaxHitPoints*0.2));
			Accuracy -= (int)(floor(Accuracy*0.2));
			Money -= 100;
			return true;
		}
		return false;
	}
	string getName()
	{
		return Name;
	}
	string getPass()
	{
		return Password;
	}
	int getAcc()
	{
		return Accuracy;
	}
	int getHP()
	{
		return HitPoints;
	}
	int getMoney()
	{
		return Money;
	}
	int getXP()
	{
		return ExpPoints;
	}
	Weapon getWeapon()
	{
		return aWeapon;
	}
	string getPosition()
	{
		return plyrPos;
	}
	void setPosition(string pos)
	{
		plyrPos = pos;
	}
	void setHP(int hp)
	{
		HitPoints = hp;
	}
	void setName(string str)
	{
		Name = str;
	}
	void setPass(string str)
	{
		Password = str;
	}
	void setXp(int xp)
	{
		ExpPoints += xp;
	}
	void setWeapon(Weapon newWeapon)
	{
		aWeapon = newWeapon;
	}
	void addToAcc(int acc)
	{
		Accuracy+= acc;
	}
	void setCash(int c)
	{
		Money+= c;
	}
	void print();
	void lvlUp();
	void takeDamage(int damage);
	void turnOnGameboy();
	bool endBattle(int xp);
	void endGame();
	bool flipSwitch(App tempItem);
	void savePoint(ofstream& outFile);
	Player loadPoint();
	

private:
	//Data members
	string Name;
	string Password;
	int HitPoints;
	int Money;
	int ExpPoints;
	int Accuracy;
	int MaxHitPoints;
	int Level;
	int LvlXp;
	Weapon aWeapon;
	App theGameBoy;
	string plyrPos;

};
#endif