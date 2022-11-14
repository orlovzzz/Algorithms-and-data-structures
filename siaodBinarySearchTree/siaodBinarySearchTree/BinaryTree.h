#ifndef __BINARYTREE_H
#define __BINARYTREE_H
#include <iostream>
using namespace std;

class Node {
public:
	int code;
	string name;
	int file_position;
	Node* right;
	Node* left;
};

class BinaryTree {
public:
	Node* treeRoot = new Node();
	int srcount = 0;

	void createRoot(string name, int code, int file_position, int floor) {
		treeRoot->code = code;
		treeRoot->name = name;
		treeRoot->file_position = file_position;
		treeRoot->left = treeRoot->right = nullptr;
	}

	void createTree(string name, int code, int file_position, Node*& root) {
		if (!root) {
			root = new Node();
			root->code = code;
			root->name = name;
			root->file_position = file_position;
			root->right = root->left = nullptr;
			return;
		}
		if (code < root->code) {
			createTree(name, code, file_position, root->left);
		}
		else {
			createTree(name, code, file_position, root->right);
		}
	}

	void addNode(string name, int code, int file_position, Node*& node) {
		if (!node) {
			node = new Node();
			node->name = name;
			node->code = code;
			node->file_position = file_position;
			node->left = node->right = nullptr;
			return;
		}
		if (code < node->code) {
			addNode(name, code, file_position, node->left);
		}
		else {
			addNode(name, code, file_position, node->right);
		}
	}

	void printTree(Node* root, int tab)
	{
		if (root)
		{
			tab++;
			printTree(root->left, tab);
			for (int i = 0; i < tab; i++) cout << "     ";
			cout << root->code << "\n";
			tab++;
			printTree(root->right, tab);
		}
	}

	Node* search(int code, Node* root) {
		if (root->code == code) {
			srcount++;
			return root;
		}
		if (code < root->code) {
			srcount++;
			search(code, root->left);
		}
		else {
			srcount++;
			search(code, root->right);
		}
	}
	
	void deleteNode(int code) {
		Node* p = treeRoot;
		Node* parent = nullptr;
		while (p && p->code != code) {
			parent = p;
			if (code < p->code) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}
		if (!p) return;
		if (!p->left) {
			if (parent && parent->left == p)
				parent->left = p->right;
			if (parent && parent->right == p)
				parent->right = p->right;
			p = nullptr;
			return;
		}
		if (!p->right)
		{
			if (parent && parent->left == p)
				parent->left = p->left;
			if (parent && parent->right == p)
				parent->right = p->left;
			p = nullptr;
			return;
		}
		Node* temp = p->right;
		while (temp->left)
			temp = temp->left;
		int x = temp->code;
		deleteNode(x);
		p->code = x;
	}

};

#endif