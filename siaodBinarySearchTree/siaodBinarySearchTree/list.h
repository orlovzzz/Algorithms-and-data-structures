#ifndef _LIST__H
#define _LIST__H
#include <iostream>
#include <iomanip>
using namespace std;

class Product {
public:
	string name;
	int code;
	Product* next;
	int fileposition;
	Product(string name, int code, int fileposition) {
		this->code = code;
		this->name = name;
		this->next = nullptr;
		this->fileposition = fileposition;
	}

	void setFilePosition(int file_position) {
		this->fileposition = file_position;
	}
};

class list {
public:
	Product* first;
	Product* last;

	list() {
		first = nullptr;
		last = nullptr;
	}

	bool is_empty() {
		return first == nullptr;
	}

	void push_back(string name, int code, int file_position) {
		Product* obj = new Product(name, code, file_position);
		if (is_empty()) {
			first = obj;
			last = obj;
			return;
		}
		obj->next = first;
		first = obj;
	}

	void print(int i) {
		cout << i;
		Product* p = first;
		while (p) {
			cout << "\t\t\t" << p->code;
			p = p->next;
		}
	}

	void remove_first() {
		if (is_empty()) return;
		Product* p = first;
		first = p->next;
		delete p;
		p = nullptr;
	}

	void remove_last() {
		if (is_empty()) return;
		if (first == last) {
			remove_first();
			return;
		}
		Product* p = first;
		while (p->next != last) p = p->next;
		p->next = nullptr;
		delete last;
		last = p;
	}

	void remove(int code) {
		if (is_empty()) return;
		if (first->code == code) {
			remove_first();
			return;
		}
		else if (last->code == code) {
			remove_last();
			return;
		}
		Product* start = first;
		Product* second = first->next;
		while (second && second->code != code) {
			second = second->next;
			start = start->next;
		}
		start->next = second->next;
		delete second;
	}

	int search(int code, int& srcount) {
		Product* p = first;
		while (p) {
			srcount++;
			if (p->code = code) {
				srcount++;
				return p->fileposition;
			}
			p = p->next;
		}
	}
};

#endif