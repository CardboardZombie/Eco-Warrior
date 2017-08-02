#include "Item.h"
using namespace std;


Item Item::load(ifstream& itemFile)
{
	string garbage, name, desc;
	Item temp;
	
	itemFile>>garbage;
	getline(itemFile, name);
	itemFile>>garbage;
	getline(itemFile, desc);

	temp = Item(name, desc);

	return temp;
}
//==============Print=============================
void Item::print()
{
	cout<<"\n\n\nName:\t "<<Name<<endl;
	cout<<"Hint:\t "<<Desc<<endl;
}
