#ifndef _HASHTABLE__H
#define _HASHTABLE__H
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "list.h"
#include "file.h"
using namespace std;

class HashTable {
public:
	vector <list*> hash = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
	int srcount = 0;

	void addInHashTable(string name, int code, int file_position) {
		if (hash[hashF(code, hash.size())]) {
			hash[hashF(code, hash.size())]->push_back(name, code, file_position);
		}
		else {
			hash[hashF(code, hash.size())] = new list();
			hash[hashF(code, hash.size())]->push_back(name, code, file_position);
		}
	}

	int hashF(int n, int hash) {
		return n % hash;
	}

	void reHash() {
		vector <list*> THash = { hash.begin(), hash.end() };
		hash.resize(hash.size() * 2);
		for (int i = 0; i < THash.size(); i++) {
			hash[i] = nullptr;
		}
		for (int i = 0; i < THash.size(); i++) {
			if (THash[i]) {
				Product* p = THash[i]->first;
				while (p) {
					if (hash[hashF(p->code, hash.size())]) {
						hash[hashF(p->code, hash.size())]->push_back(p->name, p->code, p->fileposition);
					}
					else {
						hash[hashF(p->code, hash.size())] = new list();
						hash[hashF(p->code, hash.size())]->push_back(p->name, p->code, p->fileposition);
					}
					p = p->next;
				}
			}
		}
	}

	void printTable() {
		cout << "Key:" << "\t\t" << "Value:" << "\n\n";
		for (int i = 0; i < hash.size(); i++) {
			if (hash[i]) {
				hash[i]->print(i);
				cout << "\n";
			}
		}
	}

	void deleteFromTable(int code) {
		hash[hashF(code, hash.size())]->remove(code);
	}

	int search(int code) {
		return hash[hashF(code, hash.size())]->search(code, srcount);
	}
};

#endif