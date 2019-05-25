#pragma once
#include <vector>
#include <conio.h>
#include "list_funcs.h"
#include "StendhalTree.h"
#include "elem_record.h"
#include "Shanson_Fano.h"
//#include "Shanson_Node.h"

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
	this->loc_symbols = new List<record>;
	this->length = 0;
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
	//sorting symbols with their frequences
	for (size_t i = 0; i < length - 1; i++) {
		for (size_t j = 0; j < length - 1 - i; j++) {
			if (symb_to_sort[j].amount < symb_to_sort[j + 1].amount) {
				std::swap(symb_to_sort[j], symb_to_sort[j + 1]);
			}
		}
	}
	loc_symbols->clear();
	for (size_t i = 0; i < length; i++) {
		loc_symbols->push_back(symb_to_sort[i]);
		//cout<<symb_to_sort[i];
	}
}
class Shanson_Node;
//--------------------------------------------------------------------
class Shanson_Tree
{
	
private:
	friend Shanson_Node;
	List <char> encoded_symbols;
	List <List<bool>> code;
	string message;
	void recuirsiveClear(Shanson_Node *node);
public:
	List<bool> encoded_out; //finally encoded message, for testing
	string decoded_out;//finally decoded message,
	Shanson_Node * head;
	Shanson_Tree(List<record>*, string);
	~Shanson_Tree();
	void creating_tree();
	void separation(Shanson_Node*);
	void result();

	void decoding();

};

Shanson_Tree::Shanson_Tree(List<record>* map, string input)
{
	Shanson_Node *Init_node = new Shanson_Node(map);
	this->message = input;
	this->head = Init_node;
	head->create_head();

	creating_tree();
	result();
};

void Shanson_Tree::creating_tree()
{
	separation(head);
}

void Shanson_Tree::separation(Shanson_Node *current) // recursive tree creation method
{
	//current->loc_symbols->print_to_console(); //we can print sorted list of (symbol-amount) elems here
	if (current->loc_symbols->get_size()==1)
	{
		// filling the final table
		encoded_symbols.push_back(current->loc_symbols->at(0).symbol);

		List<bool> code_list; //Shannon - Fano symbol code
		
		if (current == head)
		{
			code_list.push_front(1); //if there is alphabet of 1 symbol = set its code as 1
		}
		while (current != head)
		{                                                     
			//if there is alphabet some symbols - raise from current element to head, recording codes of every
			// recording codes of every visited node in reverse order
			code_list.push_front(current->code_ofElement);
			current = current->parent;
		}
		code.push_back(code_list);
		
		return;
	}
	else
	{
		int total = 0; // total amount calculation
		for (size_t i = 0; i < current->loc_symbols->get_size(); i++)
		{
			total += current->loc_symbols->at(i).amount;
		}

		// searching for separator
		int current_total = 0;
		size_t divider=0;
		for (size_t i = 0; i < (current->loc_symbols->get_size() - 1) && (current_total + current->loc_symbols->at(i).amount) <= (total / 2); i++)
		{
			current_total += current->loc_symbols->at(i).amount;
			divider = i;
		}

		//separating our list-node to approximately equal children
		current->left = new Shanson_Node; //to left side - all to divider, INCLUDING the divider
		current->left->code_ofElement = 1;
		current->left->parent = current;		//making left child
		for (size_t i = 0; i <= divider; i++)
		{
			//record ins = current->loc_symbols->at(i); //filling left child
			current->left->loc_symbols->push_back(current->loc_symbols->at(i));
		}

		current->right = new Shanson_Node; //to right side - all from divider
		//making left child
		current->right->code_ofElement = 0;
		current->right->parent = current;

		for (size_t i = divider + 1; i < current->loc_symbols->get_size(); i++)
		{
			current->right->loc_symbols->push_back(current->loc_symbols->at(i));
		}
		//recursive separating children
		separation(current->left);
		separation(current->right);
	}
	
}
void Shanson_Tree::result() {
	StendhalTree<char, List<bool>> *map_of_chars = new StendhalTree<char, List<bool>>();
	cout << "Table of codes of symbols\n";
	for (int i = 0; i < encoded_symbols.get_size(); i++) {
		map_of_chars->insert(encoded_symbols.at(i), code.at(i)); //filling up RB- tree with chars and codes (for fast encode/decode)
		cout << encoded_symbols.at(i) << ": ";
		for (int j = 0; j < code.at(i).get_size(); j++)
			cout << code.at(i).at(j);
		cout << endl;
	}
	cout << endl;

	cout << "Original message: " << message << "; size - " << message.length()<< "\n";
	
	size_t encode_length = 0;
	cout << "Encoded message: ";
	for (int i = 0; i < message.length(); i++) { //printing encoded message, using RB - map
		for (int j = 0; j < map_of_chars->find(message.at(i))->getValue().get_size(); j++) {
			encode_length++;
			bool temp = map_of_chars->find(message.at(i))->getValue().at(j);
			encoded_out.push_back(temp);
			cout<< temp;
		}

	}
	cout << "; size - " << encode_length << ", in bytes: " << ((encode_length % 8 == 0) ? (encode_length / 8) : ((encode_length / 8) + 1)) << "\n"; 
	int size_enc_byte = ((encode_length % 8 == 0) ? (encode_length / 8) : ((encode_length / 8) + 1));
	double comp_ratio=(double) message.length()/ size_enc_byte;
	cout << "compressed in " << comp_ratio << " times\n";
	cout << "decoded message: ";
	decoding();
//	for (i=0; i<encoded_symbols.get_size(); i++)
	//_getch();

}
void Shanson_Tree::decoding() {
	int counter = 0;
	int len_symb = 1;
	while (counter < encoded_out.get_size()) {
		bool flag = false;
		for (int i=0; i< code.get_size(); i++)
			if (code.at(i).get_size() == len_symb) {//trying to find suitable size of code 
				flag = true;
				for (int j = 0; j < code.at(i).get_size(); j++) //checking, if code from RB Tree is equal for current code
					if (code.at(i).at(j) != encoded_out.at(counter + j))
						flag = 0;
				if (flag) {
					decoded_out += encoded_symbols.at(i);//if found element, add decoded symbol to string
					counter+= code.at(i).get_size();//if found element, raise counter to quantity of symbs in code
					len_symb = 1;
				}
			}
			
		if (!flag)
			len_symb++;//if not found, exppand seeking area

	}
	cout <<decoded_out<<"\n";
}
void Shanson_Tree::recuirsiveClear(Shanson_Node *node) {
	if (node == nullptr)
		return;

	recuirsiveClear(node->left);
	recuirsiveClear(node->right);
	delete node;
	node = nullptr;
}
Shanson_Tree::~Shanson_Tree() {
	recuirsiveClear(head);
}
