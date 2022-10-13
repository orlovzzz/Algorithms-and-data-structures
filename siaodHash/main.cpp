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
	int file_position;

	Product(string name, int code, int file_position) {
		this->code = code;
		this->name = name;
		this->next = nullptr;
		this->file_position = file_position;
	}

	void setFilePosition(int file_position) {
		this->file_position = file_position;
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

	void push_back(string name, int code, int file_position) { // добавление узла в список
		Product* obj = new Product(name, code, file_position);
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
			cout << p->name << setw(40 - p->name.size()) << p->code << setw(40) << p->file_position << "\n";
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

	int search(int code) { // поиск по ключу
		Product* p = first;
		while (p) {
			if (p->code = code) {
				return p->file_position;
			}
			p = p->next;
		}
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

void addInHashTable(list* hashTable[10], string name, int code, int file_position) { // добавление ключа в хеш-таблицу
	if (hashTable[hashF(code)]) {
		hashTable[hashF(code)]->push_back(name, code, file_position);
	}
	else {
		hashTable[hashF(code)] = new list();
		hashTable[hashF(code)]->push_back(name, code, file_position);
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
	string line, name = "", n = ""; int code, file_position;
	ifstream file("products.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			file_position = file.tellg();
			getline(file, line);
			getNameAndCode(name, n, line);
			n.erase(0, 1);
			try {
				code = stoi(n);
				addInHashTable(hashTable, name, code, file_position);
			}
			catch (...) {}
			name = ""; n = "";
		}
	}
	file.close();
	int command = 0;
	while (command != 5) {
		cout << "1 - Вывод таблицы\n" << "2 - Вставить ключ в таблицу\n" << "3 - Удалить ключ из таблицы\n" << "4 - Поиск по ключу\n" << "5 - Завершить работу\n";
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
			addInHashTable(hashTable, name, code, file_position);
			addInFile(name, code);
			break;
		case(3):
		{
			cout << "Введите код товара для удаления.\n";
			cin >> code;
			hashTable[hashF(code)]->remove(code);
			ofstream file("products.txt");
			for (int i = 0; i < 10; i++) {
				if (hashTable[i]) {
					Product* p = hashTable[i]->first;
					while (p) {
						int file_position = file.tellp();
						p->setFilePosition(file_position);
						file << p->name << ", " << p->code << "\n";
						p = p->next;
					}
				}
			}
			file.close();
			break;
		}
		case(4):
		{
			cout << "Введите ключ для поиска.\n";
			cin >> code;
			int position = hashTable[hashF(code)]->search(code);
			cout << "Ключ находится на " << position << " бите в файле.\n";
			break;
		}
		default:
			break;
		}
	}
	return 0;
}