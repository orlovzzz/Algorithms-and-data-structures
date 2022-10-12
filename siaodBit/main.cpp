#include <iostream>
#include <string>
using namespace std;

class BitOperation {
public:

	void Operator1() { // установить 1 в 3-й, 5-й, 11-й биты
		block(1);
		int n = 0x5D2;
		cout << "Число 5D2 в 2 - чной СС : \n";
		toBin(n);
		int mask = 0x828;
		cout << "Число 5D2 после установки 1 в 3-й, 11-й и 5-й бит в 2-чной системе:\n";
		n |= mask;
		toBin(n);
		block();
	}
	
	void Operator2() { // установить 0 в 4-х младших битах
		block(2);
		int n;
		cout << "Введите число n: "; cin >> n;
		cout << "Число " << n << " в 2 - чной СС: \n";
		toBin(n);
		int mask = 0xFFFFFFF0;
		cout << "Число " << n << " после установки четырёх младших бита в 0: \n";
		n &= mask;
		toBin(n);
		block();
	}

	void Operator3() { // умножить число на 128
		block(3);
		int n;
		cout << "Введите число n: "; cin >> n;
		cout << "Число " << n << " в 2 - чной СС: \n";
		toBin(n);
		cout << "Число " << n << " после умножения на число 128: \n";
		n <<= 7; // 128 = pow(2, 7)
		toBin(n);
		block();
	}

	void Operator4() { // разделить число на 128
		block(4);
		int n;
		cout << "Введите число n: "; cin >> n;
		cout << "Число " << n << " в 2 - чной СС: \n";
		toBin(n);
		cout << "Число " << n << " после умножения на число 128: \n";
		n >>= 7; // 128 = pow(2, 7)
		toBin(n);
		block();
	}

	void Operator5() { // установить n-й бит в 1, используя маску с 1 в старшем бите
		block(5);
		int mask = 0x8000000, num, bit; // маска с 1 в старшем бите
		cout << mask;
		toBin(mask);
		cout << "Введите число n: "; cin >> num;
		cout << "Число " << num << " в 2 - чной СС: \n";
		toBin(num);
		cout << "\n" << "Введите бит, который нужно установить в 1: "; cin >> bit;
		mask = (mask >>= 27) <<= bit;
		cout << "\nЧисло " << num << " после установления единицы в " << bit << "-й бит: \n";
		num |= mask;
		toBin(num);
		block();
	}

	void toBin(long n) { // вывод числа в двоичной системе счисления
		string s = "";
		while (n > 0) {
			s += to_string(n % 2);
			n /= 2;
		}
		for (int i = s.size() - 1; i >= 0; i--) cout << s[i] << " ";
		cout << "\n";
	}
	void block(int n) { // перегруженный метод для разграничения заданий
		cout << "Задание №" << n;
		for (int i = 0; i < 3; i++) cout << "\n";
	}
	void block() {
		for (int i = 0; i < 3; i++) cout << "\n";
	}
};

int main() {
	setlocale(0, "");
	BitOperation *obj = new BitOperation();
	obj->Operator1();
	obj->Operator2();
	obj->Operator3();
	obj->Operator4();
	obj->Operator5();
}