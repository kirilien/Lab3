// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "list_funcs.h"
#include "StendhalTree.h"
#include "elem_record.h"
#include "Shanson_Fano.h"
#include "unit_test.h"
#include <conio.h>
using namespace std;
template <class T>
void menu(List<T> *symbol_list);

int main() {
	List <record> *symbol_list=new List <record>;
	
	menu(symbol_list);
	return 0;
}
template <class T>
void menu(List<T> *symbol_list) {

	/*cout << "Choose mode:\n1)Work mode\n2)Test mode\n";
	int mode;
	cin >> mode;
	if (mode == 2) {*/
		test_all<T>();
		//_getch();
		//return;
	//}
	cout << "\nInsert string to encode\n";
	string input;
	getline(cin, input);
	Shanson_Fano<T> *shanson = new Shanson_Fano<T>(symbol_list, input);
	shanson->start();
	_getch();
	cout << "\nDo you want to open (symbol-amount) list? Y/N \n";
	char ans;
	cin >> ans;
	if (ans == 'Y')
		shanson->printing_pairs();
	_getch();
}
	/*
	cout << "Insert string to encode\n";
	string input;
	getline(cin, input);
	record temp_symb;
	Node<record> temp_node;
	bool flag = 0;
	//List<record> symbol_list;// = new List<record>;
	for (int i = 0; i < input.length(); i++) {
		temp_symb.symbol = input.at(i);
		temp_symb.amount = 1;
		for (int j = 0; j < symbol_list->get_size(); j++)
			if (symbol_list->at(j).symbol == temp_symb.symbol) {
				temp_symb.amount = symbol_list->at(j).amount + 1;
				
				symbol_list->set(j, temp_symb);
				flag = 1;
			}
		if (!flag)
			symbol_list->push_back(temp_symb);
		flag = 0;
	}
	symbol_list->print_to_console();
	Shanson_Fano<T> *shanson = new Shanson_Fano<T>(symbol_list, input);
	shanson->start();
	return;
}
*/