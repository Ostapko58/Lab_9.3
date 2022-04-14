#include<iostream>
#include<windows.h>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;


enum Pozn
{
	casual,
	comfort,
	expres
};

struct Electr
{
	string prizn;
	Pozn poznach;
	int time[2];
};
void Create(Electr* stud, const int N);
void Print(Electr* stud, const int N, string* List);
void SortPrizn(Electr* stud, const int N);
void SortTime(Electr* stud, const int N);
int* IndexSort(Electr* stud, const int N);
int Pisla(Electr* stud, const int N, int* I);
void Remove(Electr*& stud, int& N);
void Add(Electr*& stud, int& N);
void PrintIndex(Electr* stud, const int N, string* List, int* I, int no);
void Zamina(Electr* stud, const int N);
void SaveToFile(Electr* stud, const int N, const char* filename);
void LoadFromFile(Electr*& stud, int& N, const char* filename);

void Create(Electr* stud, const int N)
{
	int poznach;
	for (int i = 0; i < N; i++)
	{
		cout << " � " << i + 1 << ":" << endl;
		cin.get(); cin.sync();
		cout << " �����������: "; getline(cin, stud[i].prizn);
		do
		{
			if (stud[i].prizn.find_first_of("0 123456789", 0) != -1)
			{
				stud[i].prizn.erase(0, -1);
				cout << "�� ����� ������ �������, ���������� �����: " << endl;
				cout << " �����������: "; getline(cin, stud[i].prizn);
			}
		} while (stud[i].prizn.find_first_of("0 123456789", 0) != -1);

		cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������): ";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ������ �����, ���������� �����: " << endl;
				cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������):";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		stud[i].poznach = (Pozn)poznach;
		cout << " ��� �����������:\n������: "; cin >> stud[i].time[0];
		if (cin.fail() || stud[i].time[0] < 1 || stud[i].time[0]>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ����� ���, ���������� �����: " << endl;
				cout << " ������: "; cin >> stud[i].time[0];
			} while (cin.fail() || stud[i].time[0] < 1 || stud[i].time[0]>24);
		}
		cin.get(); cin.sync();
		cout << "�������: "; cin >> stud[i].time[1];
		if (cin.fail() || stud[i].time[1] < 1 || stud[i].time[1]>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ����� ���, ���������� �����: " << endl;
				cout << " �������: "; cin >> stud[i].time[1];
			} while (cin.fail() || stud[i].time[1] < 1 || stud[i].time[1]>60);
		}
		cout << endl;
	}
}

void Print(Electr* stud, const int N, string* List)
{
	cout << "========================================================="
		<< endl;
	cout << "| � |    �����������    |          ���          |  ���  |"
		<< endl;
	cout << "---------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(18) << left << stud[i].prizn
			<< "| " << setw(22) << left << List[stud[i].poznach];
			//<< "| " << setw(5) << right << to_string(stud[i].time)<< " |" << endl;
			cout << "| " << setw(2) <<right<< to_string(stud[i].time[0]) << ":"<<
			setw(2) <<left<< to_string(stud[i].time[1]) << " |" << endl;
	}
	cout << "========================================================="
		<< endl;
	cout << endl;
}

void SortPrizn(Electr* stud, const int N)
{
	Electr tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if (stud[i1].prizn > stud[i1 + 1].prizn)
			{
				tmp = stud[i1];
				stud[i1] = stud[i1 + 1];
				stud[i1 + 1] = tmp;
			}
}

void SortTime(Electr* stud, const int N)
{
	Electr tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((stud[i1].time[0] > stud[i1 + 1].time[0])|| (stud[i1].time[0] == stud[i1 + 1].time[0]&& stud[i1].time[1] > stud[i1 + 1].time[1]))
			{
				tmp = stud[i1];
				stud[i1] = stud[i1 + 1];
				stud[i1 + 1] = tmp;
			}
}

int* IndexSort(Electr* stud, const int N)
{
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((stud[I[j]].time[0] > stud[value].time[0]) ||
				(stud[I[j]].time[0] == stud[value].time[0] &&
					stud[I[j]].time[1] > stud[value].time[1]));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

int Pisla(Electr* stud, const int N,int *I)
{
	int tmp[2];
	cin.get(); cin.sync();
	cout << " ������ ������� ��� ���:\n������: "; cin >> tmp[0];
	if (cin.fail() || tmp[0] < 1 || tmp[0]>24)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " ������: "; cin >> tmp[0];
		} while (cin.fail() || tmp[0] < 1 || tmp[0]>24);
	}
	cin.get(); cin.sync();
	cout << "�������: "; cin >> tmp[1];
	if (cin.fail() || tmp[1] < 1 || tmp[1]>60)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " �������: "; cin >> tmp[1];
		} while (cin.fail() || tmp[1] < 1 || tmp[1]>60);
	}
	for (int i = 0; i < N; i++)
	{
		if ((stud[I[i]].time[0]>tmp[0])||(stud[I[i]].time[0]==tmp[0]&&stud[I[i]].time[1]>tmp[1]))
		{
			return I[i];
		}
	}
	return -1;
}

void Remove(Electr*& stud, int& N)
{
	int K;
	cout << "������ ����� �����, ���� �� ������ ��������: "; cin >> K;
	if (cin.fail() || K < 1 || K>N)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " ������ ����� �����, ���� �� ������ ��������: "; cin >> K;
		} while (cin.fail() || K < 1 || K>N);
		Electr* t = new Electr[N - 1];
		int j = 0;
		for (int i = 0; i < N; i++)
		{
			if (i != K - 1)
			{
				t[j].poznach = stud[i].poznach;
				t[j].prizn = stud[i].prizn;
				t[j].time[0] = stud[i].time[0];
				t[j].time[1] = stud[i].time[1];
				j++;
			}
		}
		delete[] stud;
		stud = t;
		N--;

	}
}
void Add(Electr*& stud, int& N)
{
	int poznach;
	Electr* t = new Electr[N+1];
	for (int i = 0; i < N; i++)
	{
		t[i].poznach = stud[i].poznach;
		t[i].prizn = stud[i].prizn;
		t[i].time[0] = stud[i].time[0];
		t[i].time[1] = stud[i].time[1];
	}
	cout << " � " << N+1 << ":" << endl;
	cin.get(); cin.sync();
	cout << " �����������: "; getline(cin, t[N].prizn);
	do
	{
		if (t[N].prizn.find_first_of("0 123456789", 0) != -1)
		{
			t[N].prizn.erase(0, -1);
			cout << "�� ����� ������ �������, ���������� �����: " << endl;
			cout << " �����������: "; getline(cin, t[N].prizn);
		}
	} while (t[N].prizn.find_first_of("0 123456789", 0) != -1);
	cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������): ";
	cin >> poznach;
	if (cin.fail() || poznach < 0 || poznach>2)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ������ �����, ���������� �����: " << endl;
			cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������):";
			cin >> poznach;
		} while (cin.fail() || poznach < 0 || poznach>2);
	}
	t[N].poznach = (Pozn)poznach;
	cout << t[N].poznach << endl;
	cout << " ��� �����������:\n������: "; cin >> t[N].time[0];
	if (cin.fail() || t[N].time[0] < 1 || t[N].time[0]>24)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " ������: "; cin >> t[N].time[0];
		} while (cin.fail() || t[N].time[0] < 1 || t[N].time[0]>24);
	}
	cin.get(); cin.sync();
	cout << "�������: "; cin >> t[N].time[1];
	if (cin.fail() || t[N].time[1] < 1 || t[N].time[1]>60)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " �������: "; cin >> t[N].time[1];
		} while (cin.fail() || t[N].time[1] < 1 || t[N].time[1]>60);
	}
	cout << endl;
	delete[] stud;
	stud = t;
	N++;
	//N = K;
}

void PrintIndex(Electr* stud, const int N, string* List,int * I,int no)
{
	int num=1;
	cout << no << endl;
	if (no==-1)
	{
		cout << "���� �������� ����������(" << endl;
		return;
	}
	cout << "========================================================="
		<< endl;
	cout << "| � |    �����������    |          ���          |  ���  |"
		<< endl;
	cout << "---------------------------------------------------------"
		<< endl;
	for (int i = no; i < N; i++)
	{
		cout << "| " << setw(1) << right << num++ << " ";
		cout << "| " << setw(18) << left << stud[I[i]].prizn
			<< "| " << setw(22) << left << List[stud[I[i]].poznach];
		cout << "| " << setw(2) << right << to_string(stud[I[i]].time[0]) << ":" <<
			setw(2) << left << to_string(stud[I[i]].time[1]) << " |" << endl;
	}
	cout << "========================================================="
		<< endl;
	cout << endl;

}

void Zamina(Electr* stud, const int N)
{
	int row,col,poznach;
	cout << "������ ����� �����, ���� �� ������ �������: "; cin >> row;
	if (cin.fail() || row < 0 || row>N)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ������ �����, ���������� �����: " << endl;
			cout << " ������ ����� �����, ���� �� ������ �������:";
			cin >> row;
		} while (cin.fail() || row < 0 || row>N);
	}
	row--;
	cout << "������, ���� �� ������ ������� ��������(0-�����������,1-���,2-���): "; cin >> col;
	if (cin.fail() || col < 0 || col>2)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ������ �����, ���������� �����: " << endl;
			cout << " ������, ���� �� ������ ������� ��������(0-�����������,1-���,2-���):";
			cin >> col;
		} while (cin.fail() || col < 0 || col>2);
	}
	cin.get(); cin.sync();
	switch (col)
	{
	case 0:
		cout << "������ ���� ���� �����������: ";

		getline(cin, stud[row].prizn);
		do
		{
			if (stud[row].prizn.find_first_of("0 123456789", 0) != -1)
			{
				stud[row].prizn.erase(0, -1);
				cout << "�� ����� ������ �������, ���������� �����: " << endl;
				cout << " �����������: "; getline(cin, stud[row].prizn);
			}
		} while (stud[row].prizn.find_first_of("0 123456789", 0) != -1);
		break;
	case 1:
		cout << "������ ���� �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������): ";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ������ �����, ���������� �����: " << endl;
				cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������):";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		stud[row].poznach = (Pozn)poznach;
		break;
	case 2:
		cout << "������ ����� ��� �����������:\n������: "; cin >> stud[row].time[0];
		if (cin.fail() || stud[row].time[0] < 1 || stud[row].time[0]>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ����� ���, ���������� �����: " << endl;
				cout << " ������: "; cin >> stud[row].time[0];
			} while (cin.fail() || stud[row].time[0] < 1 || stud[row].time[0]>24);
		}
		cin.get(); cin.sync();
		cout << "�������: "; cin >> stud[row].time[1];
		if (cin.fail() || stud[row].time[1] < 1 || stud[row].time[1]>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ����� ���, ���������� �����: " << endl;
				cout << " �������: "; cin >> stud[row].time[1];
			} while (cin.fail() || stud[row].time[1] < 1 || stud[row].time[1]>60);
		}
		break;
	}
}

void SaveToFile(Electr* stud, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // ������� ������� ���� ������
	fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
	for (int i = 0; i < N; i++)
		fout.write((char*)&stud[i], sizeof(Electr)); // �������� �������� ������
	fout.close(); // ������� ����
}

void LoadFromFile(Electr*& stud, int& N, const char* filename)
{
	delete[] stud; // ������� �������� ���
	ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
	fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
	stud = new Electr[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		fin.read((char*)&stud[i], sizeof(Electr)); // ��������� �������� ������
	fin.close(); // ������� ����
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fileName[50];
	int ca;
	int* t;
	string List[] = 
	{
		"���������",
		"���������� ��������",
		"��������� �������"	
	};
	int N;
	//cout << "������ N: "; cin >> N;
	Electr* stud= nullptr;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ����������� �������� � ���������" << endl;
		cout << " [4] - ���������� �� �������� ����������� ��� �� ����� �����������" << endl;
		cout << " [5] - ���� �� ����� ���������� ��� �����, �� �������� ���� ��������� ����" << endl;
		cout << " [6] - �������� ��� � ����" << endl;
		cout << " [7] - ������� ��� � �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			cout << "������ N: "; cin >> N;
			stud = new Electr[N];
			Create(stud, N);
			break;
		case 2:
			Print(stud, N, List);
			break;
		case 3:
			cin.get(); cin.sync();
			int menu2;
			cout << "������� ��:" << endl << endl;
			cout << " [1] - ����������" << endl;
			cout << " [2] - ���������" << endl;
			cout << " [3] - ����������� ����������" << endl;
			cout << "������ ��������: "; cin >> menu2;
			switch (menu2)
			{
			case 1:
				Add(stud, N);
				break;
			case 2:
				Remove(stud, N);
				break;
			case 3:
				Zamina(stud, N);
				break;
			}
			break;
		case 4:
			cin.get(); cin.sync();
			int menu3;
			cout << "������� ��:" << endl << endl;
			cout << " [1] - ���������� �� ��������" << endl;
			cout << " [2] - ���������� �� �����" << endl;
			cout << "������ ��������: "; cin >> menu3;
			switch (menu3)
			{
			case 1:
				SortPrizn(stud, N);
				break;
			case 2:
				SortTime(stud, N);
				break;
			}
			break;
		case 5:
			t = IndexSort(stud, N);
			ca = Pisla(stud, N, t);
			PrintIndex(stud, N, List, t, ca);
			break;
		case 6:
			cin.get(); cin.sync();
			cout << "������ ����� �����: "; cin.getline(fileName, 49);
			SaveToFile(stud, N, fileName);
			break;
		case 7:
			cin.get(); cin.sync();
			cout << "������ ����� �����: "; cin.getline(fileName, 49);
			LoadFromFile(stud, N, fileName);
			break;
		case 0:
			break;
		default:
			cout << "�� ����������, ���������� �����" << endl;

		}
	} while (menuItem != 0);
	
	return 0;
}

