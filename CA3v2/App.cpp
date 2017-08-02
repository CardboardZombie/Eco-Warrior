#include "App.h"
using namespace std;
App App::load(ifstream& inAppFile)
{
	string garbage, name, desc;
	bool power;
	App temp;

	inAppFile>>garbage;
	getline(inAppFile, name);
	inAppFile>>garbage;
	getline(inAppFile, desc);
	inAppFile>>garbage>>power;
	temp = App(name, desc, power);
	return temp;
}
//==============Print=============================
void App::print()
{
	cout<<"\n\nSource Of Wasted Energy:\n"<<Name<<StandbyMsg<<endl;
}