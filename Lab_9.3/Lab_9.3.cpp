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
		cout << " № " << i + 1 << ":" << endl;
		cin.get(); cin.sync();
		cout << " Призначення: "; getline(cin, stud[i].prizn);
		do
		{
			if (stud[i].prizn.find_first_of("0 123456789", 0) != -1)
			{
				stud[i].prizn.erase(0, -1);
				cout << "Ви ввели невірне прізвище, попробуйте знову: " << endl;
				cout << " Призначення: "; getline(cin, stud[i].prizn);
			}
		} while (stud[i].prizn.find_first_of("0 123456789", 0) != -1);

		cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес): ";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірне число, попробуйте знову: " << endl;
				cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес):";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		stud[i].poznach = (Pozn)poznach;
		cout << " Час відправлення:\nГодина: "; cin >> stud[i].time[0];
		if (cin.fail() || stud[i].time[0] < 1 || stud[i].time[0]>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
				cout << " Година: "; cin >> stud[i].time[0];
			} while (cin.fail() || stud[i].time[0] < 1 || stud[i].time[0]>24);
		}
		cin.get(); cin.sync();
		cout << "Хвилина: "; cin >> stud[i].time[1];
		if (cin.fail() || stud[i].time[1] < 1 || stud[i].time[1]>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
				cout << " Хвилина: "; cin >> stud[i].time[1];
			} while (cin.fail() || stud[i].time[1] < 1 || stud[i].time[1]>60);
		}
		cout << endl;
	}
}

void Print(Electr* stud, const int N, string* List)
{
	cout << "========================================================="
		<< endl;
	cout << "| № |    Призначення    |          Тип          |  Час  |"
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
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
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
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
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
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
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
	cout << " Введіть потрібен вам час:\nГодина: "; cin >> tmp[0];
	if (cin.fail() || tmp[0] < 1 || tmp[0]>24)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Година: "; cin >> tmp[0];
		} while (cin.fail() || tmp[0] < 1 || tmp[0]>24);
	}
	cin.get(); cin.sync();
	cout << "Хвилина: "; cin >> tmp[1];
	if (cin.fail() || tmp[1] < 1 || tmp[1]>60)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Хвилина: "; cin >> tmp[1];
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
	cout << "Введіть номер рядка, який ви хочете видалити: "; cin >> K;
	if (cin.fail() || K < 1 || K>N)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Введіть номер рядка, який ви хочете видалити: "; cin >> K;
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
	cout << " № " << N+1 << ":" << endl;
	cin.get(); cin.sync();
	cout << " Призначення: "; getline(cin, t[N].prizn);
	do
	{
		if (t[N].prizn.find_first_of("0 123456789", 0) != -1)
		{
			t[N].prizn.erase(0, -1);
			cout << "Ви ввели невірне прізвище, попробуйте знову: " << endl;
			cout << " Призначення: "; getline(cin, t[N].prizn);
		}
	} while (t[N].prizn.find_first_of("0 123456789", 0) != -1);
	cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес): ";
	cin >> poznach;
	if (cin.fail() || poznach < 0 || poznach>2)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірне число, попробуйте знову: " << endl;
			cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес):";
			cin >> poznach;
		} while (cin.fail() || poznach < 0 || poznach>2);
	}
	t[N].poznach = (Pozn)poznach;
	cout << t[N].poznach << endl;
	cout << " Час відправлення:\nГодина: "; cin >> t[N].time[0];
	if (cin.fail() || t[N].time[0] < 1 || t[N].time[0]>24)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Година: "; cin >> t[N].time[0];
		} while (cin.fail() || t[N].time[0] < 1 || t[N].time[0]>24);
	}
	cin.get(); cin.sync();
	cout << "Хвилина: "; cin >> t[N].time[1];
	if (cin.fail() || t[N].time[1] < 1 || t[N].time[1]>60)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Хвилина: "; cin >> t[N].time[1];
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
		cout << "Немає підходящої електрички(" << endl;
		return;
	}
	cout << "========================================================="
		<< endl;
	cout << "| № |    Призначення    |          Тип          |  Час  |"
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
	cout << "Введіть номер рядка, який ви хочете замінити: "; cin >> row;
	if (cin.fail() || row < 0 || row>N)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірне число, попробуйте знову: " << endl;
			cout << " Введіть номер рядка, який ви хочете замінити:";
			cin >> row;
		} while (cin.fail() || row < 0 || row>N);
	}
	row--;
	cout << "Введіть, який ви хочете замінити стовпчик(0-Призначення,1-Тип,2-Час): "; cin >> col;
	if (cin.fail() || col < 0 || col>2)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірне число, попробуйте знову: " << endl;
			cout << " Введіть, який ви хочете замінити стовпчик(0-Призначення,1-Тип,2-Час):";
			cin >> col;
		} while (cin.fail() || col < 0 || col>2);
	}
	cin.get(); cin.sync();
	switch (col)
	{
	case 0:
		cout << "Введіть нове місце призначення: ";

		getline(cin, stud[row].prizn);
		do
		{
			if (stud[row].prizn.find_first_of("0 123456789", 0) != -1)
			{
				stud[row].prizn.erase(0, -1);
				cout << "Ви ввели невірне прізвище, попробуйте знову: " << endl;
				cout << " Призначення: "; getline(cin, stud[row].prizn);
			}
		} while (stud[row].prizn.find_first_of("0 123456789", 0) != -1);
		break;
	case 1:
		cout << "Введіть нову позначку (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес): ";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірне число, попробуйте знову: " << endl;
				cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес):";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		stud[row].poznach = (Pozn)poznach;
		break;
	case 2:
		cout << "Введіть новий час відправлення:\nГодина: "; cin >> stud[row].time[0];
		if (cin.fail() || stud[row].time[0] < 1 || stud[row].time[0]>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
				cout << " Година: "; cin >> stud[row].time[0];
			} while (cin.fail() || stud[row].time[0] < 1 || stud[row].time[0]>24);
		}
		cin.get(); cin.sync();
		cout << "Хвилина: "; cin >> stud[row].time[1];
		if (cin.fail() || stud[row].time[1] < 1 || stud[row].time[1]>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
				cout << " Хвилина: "; cin >> stud[row].time[1];
			} while (cin.fail() || stud[row].time[1] < 1 || stud[row].time[1]>60);
		}
		break;
	}
}

void SaveToFile(Electr* stud, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
		fout.write((char*)&stud[i], sizeof(Electr)); // записали елементи масиву
	fout.close(); // закрили файл
}

void LoadFromFile(Electr*& stud, int& N, const char* filename)
{
	delete[] stud; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	stud = new Electr[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&stud[i], sizeof(Electr)); // прочитали елементи масиву
	fin.close(); // закрили файл
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
		"звичайний",
		"підвищеного комфорту",
		"швидкісний експрес"	
	};
	int N;
	//cout << "Введіть N: "; cin >> N;
	Electr* stud= nullptr;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - корегування розкладу з клавіатури" << endl;
		cout << " [4] - сортування за станцією призначення або за часом відправлення" << endl;
		cout << " [5] - вивід на екран інформації про поїзди, що відходять після введеного часу" << endl;
		cout << " [6] - записати дані в файл" << endl;
		cout << " [7] - зчитати дані з файлу" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			cout << "Введіть N: "; cin >> N;
			stud = new Electr[N];
			Create(stud, N);
			break;
		case 2:
			Print(stud, N, List);
			break;
		case 3:
			cin.get(); cin.sync();
			int menu2;
			cout << "Виберіть дію:" << endl << endl;
			cout << " [1] - добавлення" << endl;
			cout << " [2] - вилучення" << endl;
			cout << " [3] - редагування інформації" << endl;
			cout << "Введіть значення: "; cin >> menu2;
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
			cout << "Виберіть дію:" << endl << endl;
			cout << " [1] - сортування за станцією" << endl;
			cout << " [2] - сортування за часом" << endl;
			cout << "Введіть значення: "; cin >> menu3;
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
			cout << "Введіть назву файлу: "; cin.getline(fileName, 49);
			SaveToFile(stud, N, fileName);
			break;
		case 7:
			cin.get(); cin.sync();
			cout << "Введіть назву файлу: "; cin.getline(fileName, 49);
			LoadFromFile(stud, N, fileName);
			break;
		case 0:
			break;
		default:
			cout << "Ви помилилися, попробуйте знову" << endl;

		}
	} while (menuItem != 0);
	
	return 0;
}

