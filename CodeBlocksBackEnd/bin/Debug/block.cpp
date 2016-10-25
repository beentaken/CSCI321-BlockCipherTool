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
		dynamic_bitset<> result2 = CustomXOR(result1, resultKey);
		returnval.erase(returnval.begin(), returnval.end());
		for (int i = 0; i < initial.length(); i++) {
			dynamic_bitset<> tmp;
			for (int l = 0; l < 8; l++) {
				tmp.push_back(result2[result2.size() - l - 1]);
			}
			unsigned long temp = tmp.to_ulong();
			unsigned char ctemp = (unsigned char)temp;
			returnval.insert(returnval.begin(), ctemp);
			dynamic_bitset<> rtemp = result2;
			rtemp.resize(result2.size() - 8);
			for (int l = 0; l < rtemp.size(); l++) {
				rtemp[rtemp.size() - l - 1] = result2[result2.size() - l - 1];
			}
			result2 = rtemp;
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
		unsigned long * array7 = new unsigned long[8];
		array7[0] = 0;
		array7[1] = 1;
		array7[2] = 2;
		array7[3] = 3;
		array7[4] = 4;
		array7[5] = 5;
		array7[6] = 6;
		array7[7] = 7;
		dynamic_bitset<> result7 = PBoxOneToOne(array7, result0, 8);
		delete [] array7;
		dynamic_bitset<> result8 = CustomXOR(result7, resultKey);
		returnval.erase(returnval.begin(), returnval.end());
		for (int i = 0; i < initial.length(); i++) {
			dynamic_bitset<> tmp;
			for (int l = 0; l < 8; l++) {
				tmp.push_back(result8[result8.size() - l - 1]);
			}
			unsigned long temp = tmp.to_ulong();
			unsigned char ctemp = (unsigned char)temp;
			returnval.insert(returnval.begin(), ctemp);
			dynamic_bitset<> rtemp = result8;
			rtemp.resize(result8.size() - 8);
			for (int l = 0; l < rtemp.size(); l++) {
				rtemp[rtemp.size() - l - 1] = result8[result8.size() - l - 1];
			}
			result8 = rtemp;
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
		unsigned long * array13 = new unsigned long[8];
		array13[0] = 0;
		array13[1] = 1;
		array13[2] = 2;
		array13[3] = 3;
		array13[4] = 4;
		array13[5] = 5;
		array13[6] = 6;
		array13[7] = 7;
		dynamic_bitset<> result13 = PBoxOneToOne(array13, result0, 8);
		delete [] array13;
		dynamic_bitset<> temporaryres13 = result13;
		for (int i = 0; i < 1; i++) {
			dynamic_bitset<> tmp;
			for (int l = 0; l < 8; l++) {
				tmp.push_back(temporaryres13[temporaryres13.size() - l - 1]);
			}
			unsigned long temp = tmp.to_ulong();
			unsigned char ctemp = (unsigned char)temp;
			returnval[counter].insert(returnval[counter].begin(), ctemp);
			dynamic_bitset<> rtemp = temporaryres13;
			rtemp.resize(temporaryres13.size() - 8);
			for (int l = 0; l < rtemp.size(); l++) {
				rtemp[rtemp.size() - l - 1] = temporaryres13[temporaryres13.size() - l - 1];
			}
			temporaryres13 = rtemp;
		}
		counter++;

	return returnval;
}
