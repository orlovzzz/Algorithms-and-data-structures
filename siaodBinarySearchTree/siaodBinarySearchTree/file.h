#ifndef _FILE__H
#define _FILE__H
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "HashTable.h"
#include "BinaryTree.h"
#include "RedBlack.h"
using namespace std;


class File {
public:
	fstream f;
	HashTable* obj;
	BinaryTree* tree;
	Node* node;
	RedBlackTree* rbTree;
	RBNode* RBNode;

	void addInFile(int n, bool flag) { // ���������� � ���� n �������
		if (flag) {
			f.open("D:/plusi/siaodHash/siaodSearchTree/products.txt", ios::out);
			for (int i = 0; i < n; i++) {
				int x = 100000 + rand() % 999999;
				string s;
				int count = 1;//5 + (rand() % 6);
				for (int j = 0; j < count; j++) {
					s += 'A' + rand() % 26;
				}
				if (i == (n - 1)) {
					f << s << ", " << x;
				}
				else {
					f << s << ", " << x << "\n";
				}
			}
		}
		else { // �������� ����� ��� ���������� ��������
			f.open("D:/plusi/siaodHash/siaodSearchTree/products.txt", ios::app);
			for (int i = 0; i < n; i++) {
				int x = 100000 + rand() % 999999;
				string s;
				int count = 5 + (rand() % 6);
				for (int j = 0; j < count; j++) {
					s += 'A' + rand() % 26;
				}

				f << "\n"; int pos = f.tellg();
				f << s << ", " << x;
				cout << "\n\n\n" << x << "\n\n\n";
				node = tree->treeRoot;
				tree->addNode(s, x, pos, node);
				rbTree->addNode(s, x, pos);
				obj->addInHashTable(s, x, pos);
			}
		}
		f.close();
	}

	void readFromFile() { // ������ ������ �� ����� � ���-�������, �������� � ������-������ �������
		string line, name = "", n = ""; int code, file_position, count = 0; bool flag = false;
		obj = new HashTable();
		f.open("D:/plusi/siaodHash/siaodSearchTree/products.txt", ios::in);
		if (f.is_open()) {
			while (!f.eof()) {
				file_position = f.tellg();
				getline(f, line);
				getNameAndCode(name, n, line);
				n.erase(0, 1);
				try {
					code = stoi(n);
					if (!flag) {
						rbTree = new RedBlackTree(name, code, file_position);
						tree = new BinaryTree();
						tree->createRoot(name, code, file_position, 0);
						flag = true;
					}
					else {
						node = tree->treeRoot;
						tree->createTree(name, code, file_position, node);
						rbTree->addNode(name, code, file_position);
					}
					if (count > obj->hash.size() * 0.75) {
						obj->reHash();
						count = 0;
					}
					obj->addInHashTable(name, code, file_position);
					count++;
				}
				catch (...) {}
				name = ""; n = "";
			}
		}
		f.close();
	}

	void getNameAndCode(string& name, string& n, string line) { // ��������� ����� � ���� �� �����
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

	void printTable() { // ����� ���-�������
		obj->printTable();
	}

	void printTree() { // ����� ��������� ������
		tree->printTree(tree->treeRoot, 0);
	}

	void deleteNode(int code) { // �������� �������� ��������� ������
		tree->deleteNode(code);
	}

	void addNode() { // ���������� ��������
		addInFile(1, false);
	}

	void printRBTree() { // ����� �� ������
		rbTree->printRBTree(rbTree->root, 0);
	}

	void deleteFromFile(int code) { // �������� ������ �� ���-�������, ��������� ������, �� ������ � �����
		obj->deleteFromTable(code);
		tree->deleteNode(code);
		rbTree->remove(code);
		f.open("D:/plusi/siaodHash/siaodSearchTree/products.txt", ios::out);
		for (int i = 0; i < obj->hash.size(); i++) {
			if (obj->hash[i]) {
				Product* p = obj->hash[i]->first;
				while (p) {
					int file_position = f.tellp();
					p->setFilePosition(file_position);
					f << p->name << ", " << p->code << "\n";
					p = p->next;
				}
			}
		}
		f.close();
	}

	int searchByBinaryTree(int code) { // ����� ������ ������ �������� ��������� ������
		return tree->search(code, tree->treeRoot)->file_position;
	}

	int searchByRBTree(int code) { // ����� ������ ������ �������� �� ������
		return rbTree->search(rbTree->root, code)->file_position;
	}

	int searchByHashTable(int code) {
		return obj->search(code);
	}
};

#endif