#include <iostream>
#include "file.h"
#include "list.h"
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
using namespace std;

int main() {
	setlocale(0, "");
	srand(time(0));
	File* obj = new File();
	obj->addInFile(1000000, 1);
	obj->readFromFile();
	cout << "1\n";
	while (true) {
		int n; cin >> n;

		auto begin = std::chrono::steady_clock::now();
		int y = obj->searchByHashTable(n);
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		std::cout << "Hash time: " << elapsed_ms.count() << " ns " << obj->obj->srcount << "\n";

		auto begin1 = std::chrono::steady_clock::now();
		y = obj->searchByBinaryTree(n);
		auto end1 = std::chrono::steady_clock::now();
		auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
		std::cout << "Binary time: " << elapsed_ms1.count() << " ns " << obj->tree->srcount << "\n";

		auto begin2 = std::chrono::steady_clock::now();
		y = obj->searchByRBTree(n);
		auto end2 = std::chrono::steady_clock::now();
		auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
		std::cout << "RB time: " << elapsed_ms2.count() << " ns " << obj->rbTree->srcount << "\n";
	}
	return 0;
}