// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Player.cpp
// ================================

#include "Player.h"
using namespace std;

string header = "================================================================================";
Function timer;
Random r;

//===============================The Constructor==============================================
Player::Player()
{
	Name = "";
	Password = "";
	Accuracy = 0;
	HitPoints = 0;
	MaxHitPoints = 0;
	ExpPoints = 0;
	Level = 0;
	Money = 0;
	plyrPos = "";
	aWeapon.Name = "";
	aWeapon.DamageRange.mLow = 1;
	aWeapon.DamageRange.mHigh = 9;
	theGameBoy.Name = "the Gameboy";
	theGameBoy.StandbyMsg = "This is your Gameboy...\nWhen you find Batteries, you will be able to rest and save the game using it.";
	theGameBoy.state = 0;
}

Player::Player(const string& name, const string& pass, int acc, int xp, int lvl, int hp,
	int maxhp, int lvlUp, int money, Weapon tempWeapon, string startPos)
{
	Name = name;
	Password = pass;
	Accuracy = acc;
	HitPoints = hp;
	MaxHitPoints = maxhp;
	ExpPoints = xp;
	Level = lvl;
	LvlXp = lvlUp;
	Money = money;
	theGameBoy.Name = "the Gameboy";
	theGameBoy.StandbyMsg = "This is your Gameboy...\nWhen you find Batteries, you will be able to rest and save the game using it.";
	theGameBoy.state = false;
	aWeapon.Name = tempWeapon.Name;
	aWeapon.DamageRange.mLow = tempWeapon.DamageRange.mLow;
	aWeapon.DamageRange.mHigh = tempWeapon.DamageRange.mLow;
	plyrPos = startPos;
}
void Player::initializePlayer()
{
	int choice;
	cout<<"\n\n\t\t\t\tCREATE YOUR HERO!"<<endl;
	cout<<header<<endl;
	//Input character's name.
	timer.printTime("Erh Sorry, what was your Name again?");
	cin>>Name;
	timer.printTime("Now, Enter the Password:");
	cin>>Password;
	//Get character details.
	Accuracy = 5;
	HitPoints = 5;
	MaxHitPoints = 5;
	ExpPoints = 0;
	Level = 1;
	LvlXp = 100;
	Money = 0;
	plyrPos = "Bedroom";
	theGameBoy.Name = "the Gameboy";
	cout<<Name<<" recieved a Gameboy!"<<endl;
	theGameBoy.StandbyMsg = "This is your Gameboy...\nWhen you find Batteries, you will be able to rest and save the game using it.";
	theGameBoy.state = false;
	timer.printTime(theGameBoy.StandbyMsg);
	cout<<endl;



	do{
		timer.printTime("\nNow please select your Weapon:\n1)Lightning Rod\n2)Mjolnir \n3)The Amp\n");
		cout<<header<<endl;
		cin>>choice;

		if(choice == 1)
		{
			aWeapon.Name = "The Lightning Rod";
			aWeapon.DamageRange.mLow = 1;
			aWeapon.DamageRange.mHigh = 10;
			Accuracy += (1,10);
			MaxHitPoints += (1,10);
		}
		else if(choice == 2)
		{
			aWeapon.Name = "Mjolnir";
			aWeapon.DamageRange.mLow = 10;
			aWeapon.DamageRange.mHigh = 20;
			Accuracy += (1,5);
			MaxHitPoints += (10,20);
		}
		else if(choice == 3)
		{
			aWeapon.Name = "The Amp";
			aWeapon.DamageRange.mLow = 1;
			aWeapon.DamageRange.mHigh = 20;
			Accuracy += (10,20);
			MaxHitPoints += (1,5);
		}
		else
			cout<<"An Error Occured :("<<endl;
	}while(choice < 1 || choice > 3);
	cout<<"You have selected "<<aWeapon.Name<<"!!\n"<<header<<endl;
}
//=============================Getters==================================
void Player::lvlUp()
{
	int choice;
	if(ExpPoints >= LvlXp)
	{
		cout <<header<<"\n\nYou Gained a Level!" <<endl;

		//Increment level
		Level++;

		//Set experience points for the next level
		LvlXp += Level*Level*100;
		cout<<"You have found two items. Choose One.\n1)Sandwich\n2)Steroids"<<endl;
		cin>>choice;

		if(choice == 1)
		{
			//Increase stats randomly
			cout<<"Nom...Nom..Nom...\n\n\n"<<endl;
			Accuracy += r.getRandom(3,6);
			MaxHitPoints += r.getRandom(4,7);
			Money += 100;
		}
		else if(choice == 2)
		{
			cout<<"****Star Power****\n\n\n"<<endl;
			Accuracy += r.getRandom(4,7);
			Money += 75;
			aWeapon.DamageRange.mLow += r.getRandom(2,4);
			aWeapon.DamageRange.mHigh += r.getRandom(4,6);
		}
		else
		{
			cout<<"You chose the Apple!!"<<endl;
			Accuracy += r.getRandom(1,3);
			MaxHitPoints += r.getRandom(2,6);
			Money += 10;
			aWeapon.DamageRange.mLow += r.getRandom(1,3);
			aWeapon.DamageRange.mHigh += 3;
			
		}
		//Give player full hitpoints when they level up
		HitPoints = MaxHitPoints;
		print();
	}
}
void Player::print()
{
	cout <<header<< "\nPLAYER STATS\n"<<header<< endl;
	cout << "\n\nName:\t\t\t" << Name << endl;
	cout << "Room:\t\t\t"<<plyrPos<<endl;
	cout << "Accuracy:\t\t" << Accuracy << endl;
	cout << "HP:\t\t\t" << HitPoints << endl;
	cout << "Max HP:\t\t\t" << MaxHitPoints << endl;
	cout << "XP:\t\t\t" << ExpPoints << endl;
	cout << "XP for Next Level:\t" << LvlXp << endl;
	cout << "Level:\t\t\t" << Level << endl;
	cout << "Weapon Name:\t\t" << aWeapon.Name << endl;
	cout << "Weapon Damage:\t\t(" << aWeapon.DamageRange.mLow<< "-" << aWeapon.DamageRange.mHigh <<")\n\n"<< endl;
	cout << header<<"\n\tMONEY SAVED:\t\t$" << Money<<endl;
	cout <<header<<endl;
}
void Player::takeDamage(int damage)
{
	HitPoints -= damage;
}
void Player::turnOnGameboy()
{
	int choice;
	theGameBoy.state = true;
	timer.printTime("Batteries turned "+theGameBoy.Name+" On!!");

	do
	{
		cout<<"\nWhat next?\n1)Rest Here\n2)Save Game\n3)View Player Stats\n4)Turn Off Gameboy"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
				cout<<header<<endl;
				timer.printTime("\n"+Name+" took a break and played the Gameboy for a few hours.\n");
				cout <<"Resting...\n\n"<<header<<endl;
				HitPoints = MaxHitPoints;
				break;
		case 2:
			{
				ofstream outFile("PlayerData\\"+Name+"QuickSave.txt");
				if(outFile)
				{
					savePoint(outFile);
				}
				outFile.close();
				cout<<header<<"\n"<<header<<"\nSaved Game.\n\n"<<header<<"\n"<<header<<endl;
				break;
			}
		case 3:
				print();
				break;
		case 4:
				break;
		default:
			cout<<header<<"\n\nInvalid option! Try Again\n\n"<<header<<endl;
		}
		cout<<endl;
	}while(choice != 4);
	theGameBoy.state = false;
	timer.printTime("\nThe Batteries burned out.\nFind More to turn "+theGameBoy.Name+" back on.\n");
}


void Player::endGame()
{
	Money += ExpPoints + (Level *10);
	cout <<header<<"MONEY SAVED: $" <<Money<<endl;
	cout<<header<<endl;
	if(Money >= 500)
		cout<<"Congratulations! You are an ECO-WARRIOR!!!\nYour Legend will inspire others..."<<endl;
	else
		cout<<"You have brought shame to the Eco-Warriors that came before you..."<<endl;
}
bool Player::flipSwitch(App tempApp)
{
	int choice;
	cout << tempApp.Name<<tempApp.StandbyMsg<<endl;
	cout << "1)Turn it Off?\n2)Leave it On" << endl;
	cin>>choice;

	if(choice == 1)
	{
		cout<<"You Turned "<<tempApp.Name<<" Off. (+56)"<<endl;
		Money += 56;
		ExpPoints += r.getRandom(100, 500);
		tempApp.state = 0;
		return tempApp.state;
	}
	else
	{
		cout<<"You left it On! (-103)"<<endl;
		Money -= 103;
	}
	return tempApp.state;
}
Player Player::loadPoint()
{
	string name, pass, pos, n, p;
	int acc, xp, hp, lvl, maxHp, lvlUp, cash, choice;
	Weapon weapon;
	string garbage;
	bool complete = false;
	Player temp;

	while(!complete)
	{
		cout<< "1)New Game 2)Load Game\n"<<header<<endl;
		cin >>choice;
		timer.printTime("Enter Name:\n");
		cin >> name;
		timer.printTime("Enter Password:\n");
		cin >> pass;

		ifstream inFile ("PlayerData\\"+name+"QuickSave.txt");

		if(choice ==1 && !inFile)
		{
			temp.initializePlayer();
			complete = true;
		}
		else if(inFile && choice == 2)
		{	
			while(!inFile.eof())
			{
				inFile >>garbage >> n;
				inFile >>garbage >> p;
				if(n == name && p == pass)
				{
					inFile>> garbage >> pos;
					inFile>> garbage >> acc;
					inFile>> garbage >> hp;
					inFile>> garbage >> maxHp;
					inFile>> garbage >> xp;
					inFile>> garbage >> lvlUp;
					inFile>> garbage >> lvl;
					inFile>> garbage >> cash;
					inFile>> garbage;
					getline(inFile, weapon.Name);
					weapon.Name.erase(0,1);
					inFile>> garbage >> weapon.DamageRange.mLow;
					inFile>> garbage >> weapon.DamageRange.mHigh;
					temp = Player(n, p, acc, xp, lvl, hp, maxHp, lvlUp, cash, weapon, pos);
					complete = true;
				}
				else
					cout<<"The Password is wrong."<<endl;
			}
		}
		inFile.close();
	}
	return temp;
}
void Player::savePoint(ofstream& outFile)
{
	outFile<<"Name= "<<Name<<endl;
	outFile<< "Pass= "<<Password<<endl;
	outFile<< "Position= "<<plyrPos<<endl;
	outFile<< "Accuracy= "<<Accuracy<<endl;
	outFile<< "HitPoints= "<<HitPoints<<endl;
	outFile<< "MaxHP= "<<MaxHitPoints<<endl;
	outFile<< "ExpPoints= "<<ExpPoints<<endl;
	outFile<< "NextLevel= "<<LvlXp<<endl;
	outFile<< "Level= "<<Level<<endl;
	outFile<< "Score= "<<Money<<endl;
	outFile<< "wName= "<<aWeapon.Name<<endl;
	outFile<< "WeaponLR= " << aWeapon.DamageRange.mLow<< endl;
	outFile<< "WeaponHR= " << aWeapon.DamageRange.mHigh<<endl;
	outFile<< endl;
}
