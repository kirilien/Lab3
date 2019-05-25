#pragma once
#include <iostream>
#include"list_funcs.h"

#include <string>
#include "list_funcs.h"
#include "StendhalTree.h"
#include "elem_record.h"
//#include "Shanson_Node.h"
#include "Shanson_Tree.h"


template<class T>
class Shanson_Fano {
private:
	
	//string encoding(string input);
	List<T> *symbol_list;
public:
	string input, dec_fin; //original and decoded messages
	Shanson_Fano(List<T> *symbol_list, string input);
	void start();
	List<bool> enc_fin;
	void printing_pairs();
	~Shanson_Fano();
};

template<class T>
Shanson_Fano<T>::Shanson_Fano(List<T> *symbol_list, string input) {

	//map = nullptr;
	this->symbol_list = symbol_list;
	this->input = input;
	record temp_symb;
	Node<record> temp_node;
	bool flag = 0;
	//List<record> symbol_list;// = new List<record>;
	for (int i = 0; i < input.length(); i++) {
		temp_symb.symbol = input.at(i);
		temp_symb.amount = 1;
		for (int j = 0; j < symbol_list->get_size(); j++) //counting symbols
			if (symbol_list->at(j).symbol == temp_symb.symbol) {
				temp_symb.amount = symbol_list->at(j).amount + 1;

				symbol_list->set(j, temp_symb);
				flag = 1;
			}
		if (!flag)
			symbol_list->push_back(temp_symb);
		flag = 0;
	}
	
}
template<class T>
void Shanson_Fano<T>::start() {
	//create_map(symbol_list);
	Shanson_Tree *encode_tree = new Shanson_Tree(symbol_list, input);// passing to building encoding tree
	enc_fin = encode_tree->encoded_out;
	dec_fin = encode_tree->decoded_out;
	
}
template<class T>
void Shanson_Fano<T>::printing_pairs() {
	symbol_list->print_to_console();
}

template<class T>
Shanson_Fano<T>::~Shanson_Fano(){
	symbol_list->clear();
}