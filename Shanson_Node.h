#pragma once
#include "list_funcs.h"
#include "StendhalTree.h"
#include "elem_record.h"
#include "Shanson_Fano.h"
#include "Shanson_Tree.h"

class Shanson_Tree;

class Shanson_Node
{
	
private:
	friend Shanson_Tree;
	List<record> *loc_symbols;
	size_t length;
	bool code_ofElement;

	Shanson_Node * left;
	Shanson_Node * right;
	Shanson_Node * parent;
public:
	Shanson_Node();
	Shanson_Node(List<record> *);
	~Shanson_Node();

	void create_head();
};
Shanson_Node::Shanson_Node() {
}
Shanson_Node::Shanson_Node(List<record> *symbols) {
	this->loc_symbols = symbols;
	length = loc_symbols->get_size();
}
Shanson_Node::~Shanson_Node()
{
}
void Shanson_Node::create_head() {

	record *symb_to_sort = new record[length];
	for (size_t i = 0; i < length; i++) {
		symb_to_sort[i] = loc_symbols->at(i);
	}
	for (size_t i = 0; i < length - 1; i++) {
		for (size_t j = 0; j < length - 1 - i; j++) {
			if (symb_to_sort[j].amount < symb_to_sort[j + 1].amount) {
				std::swap(symb_to_sort[j], symb_to_sort[j + 1]);
			}
		}
	}
	for (size_t i = 0; i < length; i++) {
		std::cout << symb_to_sort[i] << " ";
	}
}