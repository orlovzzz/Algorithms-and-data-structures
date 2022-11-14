#ifndef __REDBLACK_H
#define __REDBLACK_H
#include <iostream>
using namespace std;

class RBNode {
public:
	int code;
	string name;
	int file_position;
	RBNode* parent;
	RBNode* right;
	RBNode* left;
	string color;


};

class RedBlackTree {
public:

	RBNode* root;
	int count = 0;
	int srcount = 0;

	RedBlackTree(string name, int code, int file_position) {
		root = new RBNode();
		root->code = code;
		root->color = "b";
		root->name = name;
		root->file_position = file_position;
		root->parent = nullptr;
	}

	void leftRotate(RBNode*& root, RBNode* x) {
		RBNode* y = x->right;
		x->right = y->left;
		if (y->left) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (!x->parent) {
			root = y;
		}
		else {
			if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(RBNode*& root, RBNode* x) {
		RBNode* y = x->left;
		x->left = y->right;
		if (x->right != NULL)
			y->right->parent = x;

		y->parent = x->parent;
		if (x->parent == NULL)
			root = y;
		else {
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void addNode(string name, int code, int file_position) {
		RBNode* x = new RBNode();
		x->name = name;
		x->code = code;
		x->file_position = file_position;
		x->color = "r";
		x->parent = x->left = x->right = nullptr;
		addNode(root, x);
	}

	void addNode(RBNode*& root, RBNode* node) {
		RBNode* x = root;
		RBNode* y = nullptr;
		while (x) {
			y = x;
			if (node->code > x->code) {
				x = x->right;
			}
			else {
				x = x->left;
			}
		}
		node->parent = y;
		if (y) {
			if (node->code > y->code) {
				y->right = node;
			}
			else {
				y->left = node;
			}
		}
		else {
			root = node;
		}
		node->color = "r";
		CheckPropertyAdd(root, node);
	}

	void CheckPropertyAdd(RBNode*& root, RBNode* node) {
		RBNode* parent;
		parent = node->parent;
		while (node != this->root && parent->color == "r") {
			RBNode* gparent = parent->parent;
			if (gparent->left == parent) {
				RBNode* uncle = gparent->right;
				if (uncle && uncle->color == "r") {
					parent->color = "b";
					uncle->color = "b";
					gparent->color = "r";
					node = gparent;
					parent = node->parent;
				}
				else {
					if (parent->right == node) {
						leftRotate(root, parent);
						count++;
						swap(node, parent);
					}
					rightRotate(root, gparent);
					count++;
					gparent->color = "r";
					parent->color = "b";
					break;
				}
			}
			else {
				RBNode* uncle = gparent->left;
				if (uncle && uncle->color == "r") {
					gparent->color = "r";
					parent->color = "b";
					uncle->color = "b";
					node = gparent;
					parent = node->parent;
				}
				else {
					if (parent->left == node) {
						rightRotate(root, parent);
						swap(parent, node);
					}
					leftRotate(root, gparent);
					parent->color = "b";
					gparent->color = "r";
					break;
				}
			}
		}
		root->color = "b";
	}

	void remove(int code)
	{
		RBNode* x = search(root, code);
		if (x)
			remove(root, x);
	}

	void remove(RBNode*& root, RBNode* node) {
		RBNode* child, * parent; string color;
		if (node->left && node->right) {
			RBNode* temp = node->right;
			while (temp->left) {
				temp = temp->left;
			}
			if (node->parent) {
				if (node->parent->left) {
					node->parent->left = temp;
				}
				else {
					node->parent->right = temp;
				}
			}
			else {
				root = temp;
			}
			child = temp->right;
			parent = temp->parent;
			color = temp->color;
			if (parent == node) {
				parent = temp;
			}
			else {
				if (child) {
					child->parent = parent;
				}
				parent->left = child;
				temp->right = node->right;
				node->right->parent = temp;
			}
			temp->parent = node->parent;
			temp->color = node->color;
			temp->left = node->left;
			node->left->parent = temp;
			if (color == "b") {
				CheckPropertyRemove(root, child, parent);
			}
			delete node;
			return;
		}
		if (node->left) {
			child = node->left;
		}
		else {
			child = node->right;
		}
		parent = node->parent;
		color = node->color;
		if (child) {
			child->parent = parent;
		}
		if (parent) {
			if (node == parent->left) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}
		else {
			this->root = child;
		}
		if (color == "b") {
			CheckPropertyRemove(root, child, parent);
		}
		node = nullptr;
	}

	void CheckPropertyRemove(RBNode*& root, RBNode* node, RBNode* parent) {
		RBNode* temp;
		while ((!node) || node->color == "b" && node != this->root) {
			if (parent->left == node) {
				temp = parent->right;
				if (temp->color == "r") {
					temp->color = "b";
					parent->color = "r";
					leftRotate(root, parent);
					temp = parent->right;
				}
				else {
					if (!temp->right || temp->right->color == "b") {
						temp->left->color = "b";
						temp->color = "r";
						rightRotate(root, temp);
						temp = parent->left;
					}
					temp->color = parent->color;
					parent->color = "b";
					temp->left->color = "b";
					rightRotate(root, parent);
					node = root;
					break;
				}
			}
			else {
				temp = parent->left;
				if (temp->color == "r") {
					temp->color = "b";
					parent->color = "r";
					rightRotate(root, parent);
					temp = parent->left;
				}
				if ((!temp->left || temp->left->color == "b") && (!temp->right || temp->right->color == "b")) {
					temp->color = "r";
					node = parent;
					parent = node->parent;
				}
				else {
					if (!temp->left || temp->left->color == "b") {
						temp->right->color = "b";
						temp->color = "r";
						leftRotate(root, temp);
						temp = parent->left;
					}
					temp->color = parent->color;
					parent->color = "b";
					temp->left->color = "b";
					rightRotate(root, parent);
					node = root;
					break;
				}
			}
		}
		if (node) {
			node->color = "b";
		}
	}

	void printRBTree(RBNode* root, int tab)
	{
		if (root)
		{
			printRBTree(root->right, tab + 1);
			for (int i = 0; i < tab; i++) cout << "     ";
			cout << root->code << " " << root->color << "\n";
			printRBTree(root->left, tab + 1);
		}
	}

	void setFilePosition(int code, int file_position) {
		search(root, code)->file_position = file_position;
	}

	RBNode* search(RBNode* node, int code) {
		if (node->code == code) {
			srcount++;
			return node;
		}
		if (code > node->code) {
			srcount++;
			search(node->right, code);
		}
		else {
			srcount++;
			search(node->left, code);
		}
	}
};

#endif