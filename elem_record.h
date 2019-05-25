#pragma once
//template <class T>
#include <string>
using namespace std;


class record {
public:
	
	int amount;
	char symbol;
	record()
	{
		symbol=0;
		amount=0;
	}
	
	~record() {
	}
	/*friend istream& operator >> (istream &s, record &ptIn)
	{
		cout << "ID: ";
		cin >> ptIn.id;
		cout << "X: ";
		cin >> ptIn.x;
		cout << "Y: ";
		cin >> ptIn.y;
		return s;
	}
	*/
	friend ostream& operator << (ostream &s, const record &recOut)
	{
		s << "\nsymbol: " << recOut.symbol << " \namount: " << recOut.amount <<" \n";
		return s;
	}
};