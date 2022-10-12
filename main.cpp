#include <iostream>
#include <string>
using namespace std;

class BitOperation {
public:

	void Operator1() { // ���������� 1 � 3-�, 5-�, 11-� ����
		block(1);
		int n = 0x5D2;
		cout << "����� 5D2 � 2 - ���� �� : \n";
		toBin(n);
		int mask = 0x828;
		cout << "����� 5D2 ����� ��������� 1 � 3-�, 11-� � 5-� ��� � 2-���� �������:\n";
		n |= mask;
		toBin(n);
		block();
	}
	
	void Operator2() { // ���������� 0 � 4-� ������� �����
		block(2);
		int n;
		cout << "������� ����� n: "; cin >> n;
		cout << "����� " << n << " � 2 - ���� ��: \n";
		toBin(n);
		int mask = 0xFFFFFFF0;
		cout << "����� " << n << " ����� ��������� ������ ������� ���� � 0: \n";
		n &= mask;
		toBin(n);
		block();
	}

	void Operator3() { // �������� ����� �� 128
		block(3);
		int n;
		cout << "������� ����� n: "; cin >> n;
		cout << "����� " << n << " � 2 - ���� ��: \n";
		toBin(n);
		cout << "����� " << n << " ����� ��������� �� ����� 128: \n";
		n <<= 7; // 128 = pow(2, 7)
		toBin(n);
		block();
	}

	void Operator4() { // ��������� ����� �� 128
		block(4);
		int n;
		cout << "������� ����� n: "; cin >> n;
		cout << "����� " << n << " � 2 - ���� ��: \n";
		toBin(n);
		cout << "����� " << n << " ����� ��������� �� ����� 128: \n";
		n >>= 7; // 128 = pow(2, 7)
		toBin(n);
		block();
	}

	void Operator5() { // ���������� n-� ��� � 1, ��������� ����� � 1 � ������� ����
		block(5);
		int mask = 0x8000000, num, bit; // ����� � 1 � ������� ����
		cout << mask;
		toBin(mask);
		cout << "������� ����� n: "; cin >> num;
		cout << "����� " << num << " � 2 - ���� ��: \n";
		toBin(num);
		cout << "\n" << "������� ���, ������� ����� ���������� � 1: "; cin >> bit;
		mask = (mask >>= 27) <<= bit;
		cout << "\n����� " << num << " ����� ������������ ������� � " << bit << "-� ���: \n";
		num |= mask;
		toBin(num);
		block();
	}

	void toBin(long n) { // ����� ����� � �������� ������� ���������
		string s = "";
		while (n > 0) {
			s += to_string(n % 2);
			n /= 2;
		}
		for (int i = s.size() - 1; i >= 0; i--) cout << s[i] << " ";
		cout << "\n";
	}
	void block(int n) { // ������������� ����� ��� ������������� �������
		cout << "������� �" << n;
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