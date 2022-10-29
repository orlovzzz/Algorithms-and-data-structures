#include <iostream>
using namespace std;

struct Node {
	double n;
    int floor;
	Node* right;
	Node* left;
};

int getHeight(Node* tNode) {
    Node* p = tNode;
    int count = 0;
    while (p->left) {
        p = p->left;
        count++;
    }
    return count;
}

void create(int n, Node*& tNode, int floor)
{
    if (n > 0)
    {
        int a = rand() % 1000 + 1;
        cout << "a = " << a << "\n";
        tNode = new Node();
        tNode->n = a;
        tNode->floor = floor++;
        tNode->left = tNode->right = NULL;
        int nl = n / 2;
        int nr = n - nl - 1;
        create(nl, tNode->left, floor);
        create(nr, tNode->right, floor);
    }
}

void printTree(Node* tNode) {
    if (tNode->left) {
        printTree(tNode->left);
    }
    for (int i = 0; i < tNode->floor; i++) {
        cout << "\t";
    }
    cout << tNode->n << "\n";
    if (tNode->right) {
        cout << "\n";
        printTree(tNode->right);
    }
}

void printReverseTree(Node* tNode) {
    if (tNode->right) {
        printReverseTree(tNode->right);
    }
    for (int i = 0; i < tNode->floor; i++) {
        cout << "\t";
    }
    cout << tNode->n << "\n";
    if (tNode->left) {
        cout << "\n";
        printReverseTree(tNode->left);
    }
}

void avgSum(Node* tNode, double& avgsum, int& count) {
    if (tNode) {
        avgSum(tNode->left, avgsum, count);
        avgsum += tNode->n;
        count++;
        avgSum(tNode->right, avgsum, count);
    }
}

void deleteTree(Node*& tNode) {
    if (tNode->left) deleteTree(tNode->left);
    if (tNode->right) deleteTree(tNode->right);
    delete tNode;
}

int main() {
    srand(time(0));
	setlocale(0, "");
    Node* root;
	int n; cout << "¬ведите количество узлов: "; cin >> n;
    create(n, root, 0);
    int height = getHeight(root);
    cout << "Left  to Right\n";
    printTree(root);
    cout << "\n\nRight to Left\n\n";
    printReverseTree(root);
    double avgsum = 0; int count = 0;
    avgSum(root->left, avgsum, count);
    cout << "\n\nAverage sum left tree = " << avgsum / count << "\n";
    avgSum(root->left, avgsum, count);
    avgSum(root->right, avgsum = 0, count = 0);
    cout << "\n\nAverage sum right tree = " << avgsum / count << "\n";
    deleteTree(root);
    return 0;
}