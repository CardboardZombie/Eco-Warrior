#include "Weapon.h"
using namespace std;

Weapon Weapon::load(ifstream& weaponFile)
{
	string garbage, name;
	int dLow, dHigh;
	Weapon temp;

	weaponFile>>garbage;
	getline(weaponFile, name);
	weaponFile>>garbage>>dLow;
	weaponFile>>garbage>>dHigh;

	temp = Weapon(name, dLow, dHigh);
	return temp;
}
void Weapon::print()
{
	
	cout<<"\nName:\t\t "<<Name<<endl;
	cout<<"Damage Range:\t  "<<DamageRange.mLow<<"-"<<DamageRange.mHigh<<endl;
	
}