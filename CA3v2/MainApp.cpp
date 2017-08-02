// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// MainApp.cpp
// ================================

#include "DLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "Player.h"
#include "Room.h"
#include "App.h"
#include "Item.h"

#include <sstream>
#include <string>
#include <ctype.h>
#include <ostream>
#include <cstring>
#include<fstream>

//Functions Called
void setUp();
void printTime(string txt);
void loadGame();
void playGame(LStack<Creature>* stack);
bool Fight(LQueue<Weapon>* pack, LStack<Creature>* stack);
void EnterRoom(string room, DLinkedList<Item>* pack);
void addToPack(string key, DLinkedList<Item>* pack);
void removeFromPack(string key, DLinkedList<Item>* pack);
bool SearchPack(string key, DLinkedList<Item>* pack);
void printPack(DLinkedList<Item>* pack);
void printWeapons(LQueue<Weapon>* weaponPack);
void switchWeapon(LQueue<Weapon>* weaponPack);

//Global Variables
string txtSpacer ="================================================================================";
string garbage;
Player thePlyr;
Room theRoom;
//Global Containers
vector<Room> Rooms;
vector<App> Apps;
vector<Item> Items;
vector<Weapon> Weapons;
//Global Objects
App gameApp;
Item theItem;
Creature theEnemy;
Weapon gameWeapon;
Function t;
Random rn;

void main()
{
	cout<<txtSpacer<<txtSpacer<<endl;
	cout<<"\t\t\t ________  _______   _______\n"; 
	cout<<"\t\t\t(  ____  \(  ____ \\(  ___  )\n";
	cout<<"\t\t\t| (    \\/| (    \\/| (   ) |\n";
	cout<<"\t\t\t| (__     | |       | |   | |\n";
	cout<<"\t\t\t|  __)    | |       | |   | |\n";
	cout<<"\t\t\t| (       | |       | |   | |\n";
	cout<<"\t\t\t| (____/\ | (____/\ | (___) |\n";
	cout<<"\t\t\t\_______/ \_______/ (_______)\n\n";
	cout<<"\t           ______  _______  _______   _________ _______  ________\n";
	cout<<"\t|\\     /|( ___  )(  ____ )(  ____  )\\__   __/(  ___  )(  ____  )\n";
	cout<<"\t| )   ( || (   ) || (    )| | (    )|     ) (   | (   ) || (    )|\n";
	cout<<"\t| | _ | || (___) || (____)| | (____)|     | |   | |   | || (____)|\n";
	cout<<"\t| |( )| ||  ___  ||     __) |     __)     | |   | |   | ||     __)\n";
	cout<<"\t| || || || (   ) || (\\ (   | (\\  (      | |   | |   | || (\\ (   \n";
	cout<<"\t| () () || )   ( || ) \\ \\_| ) \\  \\____) (___| (___) || ) \\ \\_\n";
	cout<<"\t(_______)|/    \\||/   \\__/|/   \\__/\\_______/(_______)|/   \\__/\n\n";
	cout<<txtSpacer;
	//The Game is Loaded and from there it is Played until the Loop has been completed
	loadGame();
	cin.ignore();
	cin.ignore();
}
void setUp()
{
/* ===================================================================================================================================
	The SetUp() Function Details the BackStory & How To Play using the Commands Given to help the Player navigate through the Game
 ====================================================================================================================================*/
	system("cls");
	t.printTime("\n\n\t\t\t\tSTORYLINE: INTRO");
	cout<<txtSpacer<<endl;
	cout<<"Welcome To Eco Warrior!! This game invites you, "<<thePlyr.getName()<<", to learn about"<<endl;
	cout<<"Saving Energy in your own home (While taking on some mean baddies too!)\n\n"<<endl;
	t.printTime("You hear a noise from outside your Room...");
	t.printTime("It sounds like your home has been infested by Energy Pests:");
	cout<<"\nVampires suck away all the Energy in the room feeding and growing.\n"<<endl;
	cout<<"Ghosts have been known to appear when an infestation occurs to spook people."<<endl;
	cout<<"The Energy Trolls don't really gain from the Energy they steal,"<<endl;
	cout<<"but they love watching you squirm knowing that they are costing you"<<endl;
	cout<<"tonnes of Money!!"<<endl;
	t.printTime("Take them out.");
	cout<<"\nYour Mission is to stop all creatures from wasting Energy in your home."<<endl;
	cout<<"Accomplish this by turning off an Electronic Appliance in each Room in the House and defeating each creature in Combat."<<endl;
	t.printTime("Are you ready? You better be...Gather your wits and become the last hope to Save Energy in your Home!");
	system("PAUSE");
	system("cls");
	t.printTime("\n\n\t\t\t\tHOW TO PLAY!!!");
	cout<<txtSpacer<<endl;
	t.printTime("Explore all the Rooms and be sure to Turn off as many Appliances as you can.");
	t.printTime("Take Items that will help you defeat Enemies you may Encounter.");
	t.printTime("Commands:\n");
	t.printTime("\"Show Commands\"\n\"Check Gameboy/Room/Pack/Weapons\"\n\"Quit Game\"\n\"Kill [Name of Appliance]\"");
	t.printTime("\"Take [Name of Object]\"\n\"Enter [Name of Room]\"\n\"Take [Name of Weapon]\"\n\"Switch Weapons\"");
	cout<<txtSpacer<<endl;
	system("Pause");
}
void loadGame()
{
	/* ===================================================================================================================================
		The loadGame function Loads in the Player or creates a new Player and sets it to the Main Player. 
		It also loads in a Number of other Objects from their txt files. 
		I had to load everything that wasn't owned by the player to a vector because I couldn't get my Array class working so I 
		have a few vectors storing the Items, Apps & Weapons. Had I more time I could have possibly added them to Stacks and Queued
		Arrays as I knew how many I was putting in the Game.
		The Creature class was loaded and added to a LinkedList Stack. I thought this was for the best as I could call each Enemy
		and Remove it from the Top of the Container once the Player had fought them. I had intended the Fights to be a linear sequence
		so the Stack List suited me as I wasn't sure how many Enemies the Player would face in Total but this allowed room for it to 
		Grow. The ListStack was a pointer so I had to feed it through the playGame function to access it later on.
 ====================================================================================================================================*/
	LStack<Creature>* eStack = new LStack<Creature>;
	string garbage;
	//Load in the Player
	do
	{
		thePlyr = thePlyr.loadPoint();
	}while(thePlyr.getName() == "");

	//Load in the Rooms
	int numOfRooms = 0;
	ifstream inRoomFile("Room.txt");
	if(inRoomFile)
	{
		inRoomFile>>garbage>>numOfRooms;
		for(int i = 0; i < numOfRooms; i++)
		{
			theRoom = theRoom.load(inRoomFile);
			//Add to Container
			Rooms.push_back(theRoom);
		}
	}
	inRoomFile.close();//Closes the File I/O
	string pos;
	pos = thePlyr.getPosition();
	//Set the Player's Position If Loaded in from somewhere else in the Game
	for(int i = 0; i < Rooms.size(); i++)
	{
		if(pos == Rooms[i].getName())
		{
			theRoom = Rooms[i];
			break;
		}
	}

	//Load in the Items
	int numOfItems;
	ifstream itemFile("Item.txt");
	if(itemFile)//Opened File I/O Successfully
	{
		itemFile>>garbage>>numOfItems;
		for(int i = 0; i < numOfItems; i++)
		{
			theItem = theItem.load(itemFile);
			//Add to Container
			Items.push_back(theItem);
		}
	}
	itemFile.close();

	//Load Apps
	int numOfApps;
	ifstream inAppFile("App.txt");
	if(inAppFile)
	{
		inAppFile>>garbage>>numOfApps;
		for(int i = 0; i < numOfApps; i++)
		{
			gameApp = gameApp.load(inAppFile);
			Apps.push_back(gameApp);
		}
	}
	inAppFile.close();
	
	//Load in Weapons
	int noWeapons;
	ifstream weaponFile("Weapon.txt");
	if(weaponFile)
	{
		weaponFile>>garbage>>noWeapons;
		for(int i = 0; i < noWeapons; i++)
		{
			gameWeapon = gameWeapon.load(weaponFile);
			Weapons.push_back(gameWeapon);
		}
	}
	weaponFile.close();

	//Load Enemies
	int noEnemies;
	ifstream inFile("Creature.txt");
	if(inFile)
	{
		inFile>>garbage>>noEnemies;
		for(int i = 0; i < noEnemies; i++)
		{
			//Last In First Out -Stack Container
			theEnemy = theEnemy.load(inFile);
			eStack->Push(theEnemy);
		}
	}
	inFile.close();
	//Sets the 1st Enemy to the Top of the Stack
	theEnemy = eStack->Top();
	if(thePlyr.getMoney() == 0)//If the player is new display the set up
		setUp();
	playGame(eStack);
}
void playGame(LStack<Creature>* stack)
{
	/* ====================================================================================================================================
		Here in the playGame function I set up the Players containers allowing the Game to read an Item, App or Weapon from a vector
		and place it into the players inventorys ie. playerPack & WeaponQueue.
		The primary function of playGame is to set up the loop that allows the player to play a step in the game continously until
		one of the arguments to end the loop are met.
		Through this loop the Player can Enter various other rooms, Take Items & Weapons, Check Stats, Turn off Apps, Switch Weapons..
		The plyrPack is the DLL for the Item class so that the Player can interact with and store Items within the Rooms
		Because the Player is constantly removing and adding new Items the list does not have a definitive size making an Array
		less efficient in terms of speed and memory. The DLL allows me to start from the end of the list and search backwards
		for a specific Item that the Player has just picked up.
		The QueuedList is used for the Weapons because while I wanted the Player to be able to use different Weapons I wanted an 
		inventory of them to be used sequentially. Using the Switch Weapons command the Player can switch between their Weapon and
		the First Weapon added to the inventory ie. the First Weapon the Picked Up will be the First Popped off the Queue.
		I used a Linked List for this Container because again, its size could vary and I felt that an Array would let prove to
		be less efficient here aswell.
 ====================================================================================================================================*/
	DLinkedList<Item>* plyrPack = new DLinkedList<Item>;
	LQueue<Weapon>* weaponPack = new LQueue<Weapon>;
	string command;
	string input;
	string newName;
	bool gameOvr = false;
	string commandList[6] = {"Enter", "Take", "Check", "Kill", "Switch", "Show"};
	cout<<"Good Luck with your quest, Eco-Warrior "<<thePlyr.getName()<<".\nTo find out more \"Check Room\""<<endl;
	do//game stays in this loop until the player has won
	{
		input = "";
		cout<< "\n\nWhat's Next?\n>";
		cin >> command;
		getline(cin, input);
		input.erase(0,1);

		if(command == commandList[0])
		{
			EnterRoom(input, plyrPack);
		}
		else if(command == commandList[1])
		{
			if(" "+input == theRoom.getItem())
			{
				for(int i = 0; i < Items.size(); i++)
				{
					if(" "+input == Items[i].Name)
					{
						plyrPack->Append(Items[i]);
						t.printTime("It was added to your pack!");
						theRoom.setItem("Already Taken");
						break;
					}
				}
			}
			else if(" "+input == theRoom.getWeapon())
			{
				cout<<thePlyr.getName()<<" Lifted the"<<theRoom.getWeapon()<<endl;
				for(int i = 0; i < Weapons.size(); i++)
				{
					if(" "+input == Weapons[i].Name)
					{
						if(stack->Length() > 0)
							gameOvr = Fight(weaponPack, stack);
						weaponPack->Enqueue(Weapons[i]);
						t.printTime("The"+Weapons[i].Name+" was added to the Weapons!");
						theRoom.setWeapon("Already Taken");
						if(stack->Length() > 0)
							gameOvr = Fight(weaponPack, stack);
						break;
					}
				}
			}
			else
				cout<<"Invalid Object"<<endl;
		}
		else if(command == commandList[2] && input == "Gameboy")
		{
			if(SearchPack(" Batteries", plyrPack))
			{
				thePlyr.turnOnGameboy();
				removeFromPack("Batteries", plyrPack);
			}
			else
				cout<<"It Needs Batteries!"<<endl;
		}
		else if(command == commandList[2] && input == "Room")
		{
			theRoom.print();
		}
		else if(command == commandList[2] && input == "Pack")
		{
			printPack(plyrPack);
		}
		else if(command == commandList[2] && input == "Weapons")
		{
			printWeapons(weaponPack);
		}
		else if(command == commandList[3])
		{
			if(" "+input == theRoom.getApp())
			{
				for(int i = 0; i < Apps.size(); i++)
				{
					if(" "+input == Apps[i].Name)
					{
						gameApp = Apps[i];
						cout<<endl;
						gameApp.state = thePlyr.flipSwitch(gameApp);
						cout<<endl;
						if(!gameApp.state)
							theRoom.setItem("Already Turned Off");
						break;
					}
				}
			}
		}
		else if(command == commandList[4] && input == "Weapons")
		{
			switchWeapon(weaponPack);
		}
		else if(command == commandList[5] && input == "Commands")
		{
			cout<<txtSpacer<< "\n\t\t\t\tCOMMANDS:\n"<<txtSpacer<<endl;
			for(int i = 0; i < 5; i++)
			{
				cout << commandList[i] << "\n";
			}
			cout<<txtSpacer<<endl;
		}
		else if(command == "Quit")
		{
			break;
		}
		else
			cout << "Invalid Command" << endl;
		if(SearchPack(" Energy Bulb", plyrPack))
		{
			gameOvr = true;
			t.printTime("******************************************************************");
			cout<<"\nCongratulations you have discovered an easier way to Save Energy!!\n\n"<<endl;
			t.printTime("******************************************************************");
			break;
		}
		if(gameOvr)
			break;
		cout<<endl;
		system("Pause");
		system("cls");
	}while(command != "Quit" || !gameOvr);
	thePlyr.endGame();

}
void EnterRoom(string key, DLinkedList<Item>* pack)
{
	/* ====================================================================================================================================
		This function allows me to switch between Rooms and set the Players position to a new one for when the Game is Saved.
		It also prints out an error message if the room cannot be accessed
 ====================================================================================================================================*/
	for(int i = 0; i < Rooms.size(); i++)
	{
		if(key == Rooms[i].getName())
		{
			if((SearchPack(Rooms[i].getKeyObj(), pack) == true) || (Rooms[i].getKeyObj() == " None"))
			{
				for(int j = 0; j < theRoom.ExitList().size(); j++)
				{
					if(key == theRoom.ExitList()[j])
					{
						thePlyr.setPosition(key);
						t.printTime("\n\nYou Entered the " + thePlyr.getPosition());
						theRoom = Rooms[i];
						if(thePlyr.getPosition() == "Kitchen")
							removeFromPack("Fire Extinguisher", pack);
						break;
					}
				}
			}
			else
				t.printTime("You need a" + Rooms[i].getKeyObj() + " to Enter this Room.\n");
		}
	}
}
/* ====================================================================================================================================
	These Next set of functions I had to call in This class because I was running very short on time and I needed to be able to access
	the List Iterators allowing me To Cycle through the various Lists. Had I more Time I may have been able to find a more efficient
	place to put these functions but for the moment they work by feeding in the pointer for the Lists and modifying it from 
	another location
 ====================================================================================================================================*/
bool SearchPack(string key, DLinkedList<Item>* pack)
{
	DListIterator<Item> itr = pack->GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth())
	{
		if(itr.m_node->m_data.Name == key)
			return true;
	}
	return false;
}
void removeFromPack(string key, DLinkedList<Item>* pack)
{
	DListIterator<Item> itr = pack->GetIterator();

	for(itr.End(); itr.Valid(); itr.Back())
	{
		if(itr.m_node->m_data.Name == " "+key)
			pack->Remove(itr, false);
	}
}
void printPack(DLinkedList<Item>* pack)
{
	DListIterator<Item> itr = pack->GetIterator();
	cout<<txtSpacer<<"\n\t\t\t\tPLAYER PACK\n"<<endl;
	cout<<txtSpacer<<endl;
	for(itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.m_node->m_data.print();
		cout<<endl;
	}
	cout<<txtSpacer<<endl;
}
/* ====================================================================================================================================
	This function demonstrates How I was able to override the FIFO Queue by Removing a Weapon from the Queue and Adding 
	the old Player Weapon to the Queue. This way I am able to reverse it and use the Queue as a Container for the Weapons I have 
	already Collected.
 ====================================================================================================================================*/
void switchWeapon(LQueue<Weapon>* pack)
{
	gameWeapon = pack->Front();
	thePlyr.setWeapon(gameWeapon);
	pack->Dequeue();
}
void printWeapons(LQueue<Weapon>* pack)
{
	DListIterator<Weapon> itr = pack->GetIterator();
	cout<<txtSpacer<<"\n\t\t\t\tWEAPON STATS"<<endl;
	cout<<txtSpacer<<endl;
	for(itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.m_node->m_data.print();
		cout<<endl;
	}
	cout<<txtSpacer<<endl;
}
/* ====================================================================================================================================
	The Fight Function primarily displays the Fight Sequence between the Player and A Creature but it also shows off an understanding 
	of how the Stack works and How the Queue is used. When the Creature is defeated it is Removed from the Top of the Stack and a
	New Enemy replaces it.
	When the Player loses a Weapon is Dequeued from the Queue List and is forced to accept that Weapon is lost during this Play.
 ====================================================================================================================================*/
bool Fight(LQueue<Weapon>* pack, LStack<Creature>* stack)
{
	int choice;
	int limit = (thePlyr.getAcc() + 5);
	bool over = false;
	cout <<txtSpacer<< "\n\nPrepare for Battle!! You have awoken a sleeping Creature!!!!\n"<<endl;
	do{

	int random = rn.getRandom(0, limit);
	cout << "\n\n1)Attack\n2)Run:"<<endl;
	cin >> choice;
	cout << endl;

	switch(choice)
	{
	case 1:
		cout << "\nYou Attack the" <<theEnemy.getType()<< " with " << thePlyr.getWeapon().Name << endl;
		if( random < thePlyr.getAcc())
		{
			int damage = rn.getRandomRange(thePlyr.getWeapon().DamageRange);
			int xp = rn.getRandom(200,400);
			thePlyr.setXp(xp);
			cout << "You Deal "<<damage<<" Damage to"<< theEnemy.getName() <<"(+"<<xp<<")"<<endl;
			thePlyr.setCash(rn.getRandom(2, 5));
			theEnemy.takeDamage(damage);
		}
		else
			cout << "You Missed!" << endl;
		cout << txtSpacer<<endl;
		break;
	case 2:
		//25% chance of being able to run
		int roll = rn.getRandom(1,4);
		if(roll == 1)
		{
			cout << "\nYou got away safely..." << endl;
			over = true;
		}
		else
			cout << "\nYou could not escape" << endl;
	}
	if(!theEnemy.isDead())
		theEnemy.attack(thePlyr);
	else
		over =true;

	cout<<txtSpacer<<endl;
	if(thePlyr.isDead())
	{
		cout<<"You were killed..."<<endl;
		over = true;
	}
	}while(!over);

	if(theEnemy.isDead())
	{
		cout << "\n\nYou Won the Battle!! (+"<< theEnemy.getXPReward() << ")" << endl;
		thePlyr.setXp(theEnemy.getXPReward());
		stack->Pop();
		thePlyr.lvlUp();
		if (stack->Length() > 0)
			theEnemy = stack->Top();
	}
	if(thePlyr.isDead())
	{
		thePlyr.setCash(-100);
		pack->Dequeue();
		return true;
	}
	return false;
}
