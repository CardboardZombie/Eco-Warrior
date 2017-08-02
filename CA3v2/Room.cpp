/* ====================================================================================================================================
	The Map Navigates by Checking The Exitlist, Checking if that Exit exists and Seting the players position to a new room adjacent 
	to the previous room using a Vector to contain it.
 ====================================================================================================================================*/
#include "Room.h"
using namespace std;
Room Room::load(ifstream& inRoomFile)
{
	Room temp;
	//Creates the Temp Variables
	string aStr, name, desc , k;
	string wData, itemData, appData;
	string noExits;
	int numExits;
	vector<string> exitPoint;
	string garbage;

	inRoomFile >> garbage>> name;//The data needed
	inRoomFile >> garbage;
	getline(inRoomFile, desc);
	inRoomFile >> garbage;
	getline(inRoomFile,wData);
	inRoomFile>>garbage;
	getline(inRoomFile, appData);
	inRoomFile >> garbage;
	getline(inRoomFile,itemData);
	inRoomFile>> garbage>> noExits;
	numExits= atoi(noExits.c_str());
	inRoomFile >> garbage;
	for(int i = 0; i < numExits; i++)
	{
		inRoomFile>>aStr;
		exitPoint.push_back(aStr);
	}
	inRoomFile >> garbage;
	getline(inRoomFile, k);

	temp = Room(name, desc, k, wData, itemData, appData, numExits, exitPoint);
	return temp;
}
//==============Print=============================
void Room::print()
{
	cout<<"================================================================================";
	cout<<"\t\t\t\tROOM STATS"<<endl;
	cout<<"================================================================================";
	cout << "Room Name:\t\t " << Name << endl;
	cout << "Description:\t\t" << Desc << endl;
	cout << "Weapon found:\t\t"<< weaponName<<endl;
	cout << "Item found:\t\t"<<itemName<<endl;
	cout << "Wasted Energy Source:\t"<<appName<<endl;
	cout << "Nearby Exits:\t\t "<<NumOfExits<<endl;
	for(int i = 0; i < NumOfExits; i++)
	{
		cout<<"\t\t\t"<<Exits[i]<<endl;
	}
	cout<<"\n================================================================================"<<endl;
}