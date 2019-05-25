#pragma once
#include <assert.h>
#include "Shanson_Fano.h"
#include"list_funcs.h"

#include <string>
#include "list_funcs.h"
#include "StendhalTree.h"
#include "elem_record.h"

#include "Shanson_Tree.h"
using namespace std;
template<class T>

void ordinary_test() {
	List <record> *symbol_list = new List <record>;
	string input = "qwertyuiop[Zxcvbnm, l; 'zxcvbnm,.";
	string expected_enc_str = "0111101110011010110001011010100100101000001110011000101001001111111011011100101110101001100000011000101000000010000011111111011011100101110101001000000";
	List<bool> expected_encoded;
	List<bool> real_encoded;

	for (int i = 0; i < expected_enc_str.length(); i++) { //putting expected encoding in list
		if (expected_enc_str.at(i) == '1')
			expected_encoded.push_back(1);
		else
			expected_encoded.push_back(0);
	}

	Shanson_Fano<T> *shanson = new Shanson_Fano<T>(symbol_list, input);
	shanson->start();
	real_encoded = shanson->enc_fin;
	assert(real_encoded.get_size() == expected_encoded.get_size());
	for (int i = 0; i < expected_enc_str.length(); i++) 
		assert(real_encoded.at(i) == expected_encoded.at(i)); //checking if real encoding is identical with expected
	assert(shanson->dec_fin == shanson->input); //checking if decoded string is identical with original
	return;
	
}
template<class T>

void all_symbs_are_different_test() {
	List <record> *symbol_list = new List <record>;
	string input = "qwertyuiopasdfghjklzxcvbnm";
	string expected_enc_str = "1111111011110011011100111000101110101101001001110010100011000001110110101100010101001010000011001010010000011000100000100000";
	List<bool> expected_encoded;
	List<bool> real_encoded;

	for (int i = 0; i < expected_enc_str.length(); i++) { //putting expected encoding in list
		if (expected_enc_str.at(i) == '1')
			expected_encoded.push_back(1);
		else
			expected_encoded.push_back(0);
	}

	Shanson_Fano<T> *shanson = new Shanson_Fano<T>(symbol_list, input);
	shanson->start();
	real_encoded = shanson->enc_fin;
	assert(real_encoded.get_size() == expected_encoded.get_size());
	for (int i = 0; i < expected_enc_str.length(); i++)  //checking if real encoding is identical with expected
		assert(real_encoded.at(i) == expected_encoded.at(i));
	assert(shanson->dec_fin == shanson->input); //checking if decoded string is identical with original
	return;

}
template<class T>

void a_lot_of_similar_symbs_test() {
	List <record> *symbol_list = new List <record>;
	string input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	string expected_enc_str = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	List<bool> expected_encoded;
	List<bool> real_encoded;

	for (int i = 0; i < expected_enc_str.length(); i++) { //putting expected encoding in list
		if (expected_enc_str.at(i) == '1')
			expected_encoded.push_back(1);
		else
			expected_encoded.push_back(0);
	}

	Shanson_Fano<T> *shanson = new Shanson_Fano<T>(symbol_list, input);
	shanson->start();
	real_encoded = shanson->enc_fin;
	assert(real_encoded.get_size() == expected_encoded.get_size());
	for (int i = 0; i < expected_enc_str.length(); i++) //checking if real encoding is identical with expected
		assert(real_encoded.at(i) == expected_encoded.at(i));
	assert(shanson->dec_fin == shanson->input); //checking if decoded string is identical with original
	return;

}
template<class T>
void test_all() {
	ordinary_test<T>();
	all_symbs_are_different_test<T>();
	a_lot_of_similar_symbs_test<T>();
	cout << "\n\ntest - ordinary string - succeed\n";
	cout << "all_symbs_are_different_test - succeed\n";
	cout << "a_lot_of_similar_symbs_test - succeed\n\n";
	return;
}