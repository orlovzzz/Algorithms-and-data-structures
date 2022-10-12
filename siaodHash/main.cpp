#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <exception>
using namespace std;

struct Product {
	string name;
	int code;
	Product* next;

	Product(string name, int code) {
		this->code = code;
		this->name = name;
		this->next = nullptr;
	}
};

struct list {
	Product* first;
	Product* last;

	list() {
		first = nullptr;
		last = nullptr;
	}

	bool is_empty() { // проверка на пустоту списка
		return first == nullptr;
	}

	void push_back(string name, int code) { // добавление узла в список
		Product* obj = new Product(name, code);
		if (is_empty()) {
			first = obj;
			last = obj;
			return;
		}
		obj->next = first;
		first = obj;
	}

	void print() { // печать списка
		Product* p = first;
		while (p) {
			cout << p->name << setw(40 - p->name.size()) << p->code << "\n";
			p = p->next;
		}
	}
	
	void remove_first() { // удаление первого узла
		if (is_empty()) return;
		Product* p = first;
		first = p->next;
		delete p;
	}

	void remove_last() { // удаление последнего узла
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

	void remove(int code) { // удаление по значению
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

	void addInFile(){ // перезапись файла без удалённого ключа
		fstream file("products.txt", ios::out);
		Product* p = first;
		while (p) {
			file << p->name << ", " << p->code << "\n";
			p = p->next;
		}
		file.close();
	}

	void addInFile(int count) { // дозапись файла без удалённого ключа
		fstream file("products.txt", ios::app);
		Product* p = first;
		while (p) {
			file << p->name << ", " << p->code << "\n";
			p = p->next;
		}
		file.close();
	}
};

int hashF(int n) { // хеш-функция
	return n % 10;
}

void getNameAndCode(string& name, string& n, string line) { // получение имени товара и номера из файла
	bool flag = false;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ',') {
			flag = true;
		}
		if (flag == false) {
			name += line[i];
		}
		if (flag == true && line[i] != ',') {
			n += line[i];
		}
	}
}

void addInHashTable(list* hashTable[10], string name, int code) { // добавление ключа в хеш-таблицу
	if (hashTable[hashF(code)]) {
		hashTable[hashF(code)]->push_back(name, code);
	}
	else {
		hashTable[hashF(code)] = new list();
		hashTable[hashF(code)]->push_back(name, code);
	}
}

void addInFile(string name, int code) { // дозапись файла при добавлении нового ключа
	fstream file("products.txt", ios::app);
	file << name << ", " << code << "\n";
	file.close();
}

int main() {
	setlocale(0, "");
	list* hashTable[10];
	for (int i = 0; i < 10; i++) {
		hashTable[i] = nullptr;
	}
	string line, name = "", n = ""; int code;
	ifstream file("products.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			getNameAndCode(name, n, line);
			n.erase(0, 1);
			try {
				code = stoi(n);
				addInHashTable(hashTable, name, code);
			}
			catch (...) {}
			name = ""; n = "";
		}
	}
	file.close();
	int command = 0, count = 0;
	while (command != 4) {
		cout << "1 - Вывод таблицы\n" << "2 - Вставить ключ в таблицу\n" << "3 - Удалить ключ из таблицы\n" << "4 - Завершить работу\n";
		cin >> command;
		switch (command) {
		case(1):
			cout << "Product:" << setw(31) << "Code:" << "\n\n";
			for (int i = 0; i < 10; i++) {
				if (hashTable[i]) {
					hashTable[i]->print();
				}
			}
			break;
		case(2):
			cout << "Введите имя и код товара.\n";
			cin >> name >> code;
			addInHashTable(hashTable, name, code);
			addInFile(name, code);
			break;
		case(3):
			cout << "Введите код товара для удаления.\n";
			cin >> code;
			for (int i = 0; i < 10; i++) {
				if (hashF(code) == i) {
					hashTable[i]->remove(code);
					break;
				}
			}
			for (int i = 0; i < 10; i++) {
				if (hashTable[i] && count == 0) {
					hashTable[i]->addInFile();
					count++;
				}
				else if (hashTable[i]) {
					hashTable[i]->addInFile(count);
				}
			}
			count = 0;
			break;
		case(4):
			break;
		default:
			break;
		}
	}
	return 0;
}