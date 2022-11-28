#include <iostream>;
#include <vector>
#include <queue>;
#include <set>
using namespace std;

struct top {

	int parentNumber;
	vector <top*> child;
	int road;

	top(int parentNumber) {
		this->parentNumber = parentNumber;
	}

	top(int parentNumber, int road) {
		this->parentNumber = parentNumber;
		this->road = road;
	}

};

vector <top*> mas;

void createGraph(int n, bool flag) { // создание вершин и списка сежных вершин
	while (true) {
		int child, road, parent;
		cout << "Введите вершину, смежную вершину и путь до неё или 0 для завершения работы.\n"; cin >> parent;
		if (parent == 0) {
			break;
		}
		cin >> child >> road;
		if (!mas[parent - 1]) {
			mas[parent - 1] = new top(parent);
		}
		mas[parent - 1]->child.push_back(new top(child, road));
		mas[child - 1] = mas[parent - 1]->child[mas[parent - 1]->child.size() - 1];
		if (flag) {
			if (!mas[child - 1]) {
				mas[child - 1] = mas[parent - 1]->child[mas[parent - 1]->child.size() - 1];
			}
			mas[child - 1]->child.push_back(new top(parent, road));
		}
	}
	if (!flag) {
		for (int i = 0; i < mas.size(); i++) {
			if (!mas[i]) {
				mas[i] = new top(i + 1);
			}
		}
	}
}

void BFS(top* x) { // вывод цепочки графа с помощью метода поиска в ширину
	queue <top*> q;
	q.push(x);
	vector <bool> visited(mas.size());
	visited[x->parentNumber - 1] = true;
	cout << x->parentNumber;
	while (!q.empty()) {
		top* cur = q.front();
		q.pop();
		for (top* i : cur->child) {
			if (!visited[i->parentNumber - 1]) {
				q.push(i);
				cout << " --> " << i->parentNumber;
				visited[i->parentNumber - 1] = true;
			}
		}
	}

}

void createMas(vector <vector<int>>& road) { // создания массива путей для алгоритма Дейкстры
	for (int i = 0; i < mas.size(); i++) {
		for (int j = 0; j < mas[i]->child.size(); j++) {
			road[mas[i]->parentNumber - 1][mas[i]->child[j]->parentNumber - 1] = mas[i]->child[j]->road;
		}
	}
	for (int i = 0; i < mas.size(); i++) {
		for (int j = 0; j < mas.size(); j++) {
			if (road[i][j] == 0) {
				road[i][j] = INT_MAX;
			}
		}
	}
}

top* searchTopInList(int n) { // поиск элемента в массиве по названию его вершины
	for (top* i : mas) {
		if (i->parentNumber == n) {
			return i;
		}
	}
}

void searchMinRoad(int n, int seacrh) {  // Алгоритм Дейкстры
	vector <vector<int>> roadMatrix(mas.size());
	vector <bool> visited(mas.size());
	vector <int> minRoad(mas.size());
	set <int> topRoad;
	int temp;
	for (int i = 0; i < mas.size(); i++) {
		roadMatrix[i].resize(mas.size());
		minRoad[i] = INT_MAX;
	}
	top* obj = searchTopInList(n);
	createMas(roadMatrix);
	minRoad[obj->parentNumber - 1] = 0;
	int index = 0, x = 0;
	topRoad.insert(n);
	for (int i = 0; i < mas.size(); i++) {
		int min = INT_MAX;
		for (int j = 0; j < mas.size(); j++) {
			if (!visited[j] && minRoad[j] < min) {
				min = minRoad[j];
				index = j;
			}
		}
		x = index;
		visited[x] = true;
		for (int j = 0; j < mas.size(); j++) {
			if (!visited[j] && roadMatrix[x][j] != INT_MAX && minRoad[x] != INT_MAX && (minRoad[x] + roadMatrix[x][j] < minRoad[j])) {
				minRoad[j] = minRoad[x] + roadMatrix[x][j];
				temp = j + 1;
			}
		}
		topRoad.insert(temp);
	}

	for (int i = 0; i < mas.size(); i++) {
		if (i + 1 == seacrh) {
			cout << "Кратчайший путь из " << obj->parentNumber << " в " << i + 1 << " = " << minRoad[i] << "\n";
		}
	}
	cout << "\nПуть:\n";
	for (auto i : topRoad) {
		if (i == seacrh) {
			cout << i;
			break;
		}
		else {
			cout << i << " --> ";
		}
	}
}

int main() {
	setlocale(0, "");
	cout << "Количество вершин: "; int n, k; cin >> n; cout << "\n";
	mas.resize(n);
	cout << "Какой граф? (Or, Unor) "; string s; cin >> s;
	if (s == "Or") {
		createGraph(n, 0);
	}
	else {
		createGraph(n, 1);
	}
	cout << "\n";
	BFS(mas[0]);
	cout << "\n";
	cout << "\nВведите вершины между которыми нужно найти минимальное расстояние: "; cin >> n >> k;
	searchMinRoad(n, k);
}