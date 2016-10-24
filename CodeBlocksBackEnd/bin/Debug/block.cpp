#include <iostream>
#include <string>
#include <boost/dynamic_bitset.hpp>
#include "block.h"
#include "GenericFunctions.h"
using namespace std;
using namespace boost;

string Encrypt(string initial, string initialkey) {
	dynamic_bitset<> result0 (initial.length()*8);

	string * key = Keygen(initialkey);
	for (int i = 0; i < initial.length(); i++) {
		unsigned char c = initial[i];
		for (int j = 7; j >= 0 && c; j--) {
			if (c & 0x1) {
				result0.set(8*i+j);
			}
			c >>= 1;
		}
	}
	result0.resize(8);
	string returnval;
	dynamic_bitset<> result_1(key[0].length()*8);
	for (int i = 0; i < key[0].length(); i++) {
		unsigned char c = key[0][i];
		for (int j = 7; j >= 0 && c; j--) {
			if (c & 0x1) {
				result_1.set(8*i+j);
			}
			c >>= 1;
		}
	}
	result_1.resize(8);
	dynamic_bitset<> resultKey;

	for (int round = 0; round < 1; round++) {
		if (round == 0) {
			 resultKey = result_1;
		}
		unsigned long * array1 = new unsigned long[8];
		array1[0] = 0;
		array1[1] = 1;
		array1[2] = 2;
		array1[3] = 3;
		array1[4] = 4;
		array1[5] = 5;
		array1[6] = 6;
		array1[7] = 7;
		dynamic_bitset<> result1 = PBoxOneToOne(array1, result0, 8);
		delete [] array1;
		returnval.erase(returnval.begin(), returnval.end());
		for (int i = 0; i < initial.length(); i++) {
			dynamic_bitset<> tmp;
			for (int l = 0; l < 8; l++) {
				tmp.push_back(result1[result1.size() - l - 1]);
			}
			unsigned long temp = tmp.to_ulong();
			unsigned char ctemp = (unsigned char)temp;
			returnval.insert(returnval.begin(), ctemp);
			dynamic_bitset<> rtemp = result1;
			rtemp.resize(result1.size() - 8);
			for (int l = 0; l < rtemp.size(); l++) {
				rtemp[rtemp.size() - l - 1] = result1[result1.size() - l - 1];
			}
			result1 = rtemp;
		}
	}

	return returnval;
}

string Decrypt(string initial, string initialkey) {
	dynamic_bitset<> result0 (initial.length()*8);

	string * key = Keygen(initialkey);
	for (int i = 0; i < initial.length(); i++) {
		unsigned char c = initial[i];
		for (int j = 7; j >= 0 && c; j--) {
			if (c & 0x1) {
				result0.set(8*i+j);
			}
			c >>= 1;
		}
	}
	result0.resize(8);
	string returnval;
	dynamic_bitset<> result_1(key[0].length()*8);
	for (int i = 0; i < key[0].length(); i++) {
		unsigned char c = key[0][i];
		for (int j = 7; j >= 0 && c; j--) {
			if (c & 0x1) {
				result_1.set(8*i+j);
			}
			c >>= 1;
		}
	}
	result_1.resize(8);
	dynamic_bitset<> resultKey;

	for (int round = 0; round < 1; round++) {
		if (round == 0) {
			 resultKey = result_1;
		}
		unsigned long * array4 = new unsigned long[8];
		array4[0] = 0;
		array4[1] = 1;
		array4[2] = 2;
		array4[3] = 3;
		array4[4] = 4;
		array4[5] = 5;
		array4[6] = 6;
		array4[7] = 7;
		dynamic_bitset<> result4 = PBoxOneToOne(array4, result0, 8);
		delete [] array4;
		returnval.erase(returnval.begin(), returnval.end());
		for (int i = 0; i < initial.length(); i++) {
			dynamic_bitset<> tmp;
			for (int l = 0; l < 8; l++) {
				tmp.push_back(result4[result4.size() - l - 1]);
			}
			unsigned long temp = tmp.to_ulong();
			unsigned char ctemp = (unsigned char)temp;
			returnval.insert(returnval.begin(), ctemp);
			dynamic_bitset<> rtemp = result4;
			rtemp.resize(result4.size() - 8);
			for (int l = 0; l < rtemp.size(); l++) {
				rtemp[rtemp.size() - l - 1] = result4[result4.size() - l - 1];
			}
			result4 = rtemp;
		}
	}

	return returnval;
}

string* Keygen(string initial) {
	dynamic_bitset<> result0 (initial.length()*8);

	for (int i = 0; i < initial.length(); i++) {
		unsigned char c = initial[i];
		for (int j = 7; j >= 0 && c; j--) {
			if (c & 0x1) {
				result0.set(8*i+j);
			}
			c >>= 1;
		}
	}
	result0.resize(initial.length()*8);
	string * returnval = new string[1];
	int counter = 0;

	return returnval;
}
