// ================================
// CA3 - Data Structures for Games
// Author: Tadhg Deeney
// GamesDev Year 2
// Range.h
// ================================

#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <iostream>
#include <Windows.h>
using namespace std;

//Defines a range [mLow, mHigh]
struct Range
{
	int mLow;
	int mHigh;
};
struct Random
{
	int getRandomRange(Range r)
	{
		return r.mLow + rand() % ((r.mHigh + 1) - r.mLow);
	}
	int getRandom(int low, int high)
	{
		return low + rand() % ((high+1) - low);
	}
};
struct Function
{
	void printTime(string txt)
	{
		bool newline = false;
		for(unsigned int x=0;x<txt.length();x++)
		{
			if(x > 70 && txt.at(x) == ' ' && newline == false)
			{
				txt.at(x) = '\n';
				newline = true;
			}
			cout << txt.at(x);
			Sleep(50);
		}
		cout<<endl;
	}
};

#endif //UTILITY_H