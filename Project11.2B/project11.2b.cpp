#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
enum Specialty { ComputerScience, Informatics, Mathematics, Physics, Work };
string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Матем.та економ.","Фізика та інформ.","Трудове навчання" };
struct Student
{
	char prizv[50];
	unsigned course;
	Specialty specialty;
	unsigned grades_in_physics;
	unsigned grades_in_mathematics;
	union
	{
		unsigned grades_in_programming;
		unsigned grades_in_numerical_methods;
		unsigned grades_in_pedagogy;
	};
};
void Save_students_to_file(char* fname, const int N);
void Print(char* fname);
void LineSearch_count(char* fname, int* count_3, int* count_4, int* count_5);
void LineSearch_proc(char* fname, const int N, double* proc);
int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[100];
	cout << "Ім'я файлу з студентами : "; cin >> fname;
	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;
	double proc;
	int count_3 = 0;
	int count_4 = 0;
	int count_5 = 0;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - Кількість оцінок з програмуваннячий «5», «4», «3»:" << endl;
		cout << " [4] - процент студентів, які отримали і з фізики і з математики оцінки «4» або «5»:" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Save_students_to_file(fname, N);
			break;
		case 2:
			Print(fname);
			break;
		case 3:
			LineSearch_count(fname, &count_3, &count_4, &count_5);
			cout << "Кількість оцінок з програмування «3»:" << count_3 << endl;
			cout << "Кількість оцінок з програмування «4»:" << count_4 << endl;
			cout << "Кількість оцінок з програмування «5»:" << count_5 << endl;
			break;
		case 4:
			LineSearch_proc(fname, N, &proc);
			cout << "процент студентів, які отримали і з фізики і з математики оцінки «4» або «5»:" << endl;
			cout << proc << "%" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
Student Create()
{
	Student p;
	int specialty;
	cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
	cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
	cout << " прізвище: "; cin >> p.prizv;
	cout << " курс: "; cin >> p.course;
	cout << "  спеціальність (0 -Комп'ютерні науки , 1 -Інформатика, 2 -Матем. та економ., 3 - Фізика та інформ., 4 - Трудове навчання): ";
	cin >> specialty;
	p.specialty = (Specialty)specialty;
	cout << "оцінки з фізики: "; cin >> p.grades_in_physics;
	cout << "оцінки з математики: "; cin >> p.grades_in_mathematics;
	p.specialty = (Specialty)specialty;
	switch (p.specialty)
	{
	case ComputerScience:
		cout << "оцінки з програмування  : "; cin >> p.grades_in_programming;
		break;
	case Informatics:
		cout << "оцінки з чисельних методів  : "; cin >> p.grades_in_numerical_methods;
		break;
	case Mathematics:
	case Physics:
	case Work:
		cout << " оцінки з педагогіки : "; cin >> p.grades_in_pedagogy;
		break;
	}
	return p;
}
void Save_to_file(ofstream* fout, Student student)
{
	fout->write((char*)&student, sizeof(Student));
}
void Save_students_to_file(char* fname, const int N)
{
	ofstream fout;
	fout.open(fname, ios::binary);
	Student student;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		student = Create();
		Save_to_file(&fout, student);
	}
	fout.close();
}
void Print_student(int N, Student student)
{
	cout << "|" << setw(3) << left << N;
	cout << "|" << setw(10) << left << student.prizv;
	cout << "|" << setw(3) << right << student.course << " ";
	cout << "|" << setw(17) << left << specialtyStr[student.specialty];
	cout << "|" << setw(14) << right << student.grades_in_physics << " ";
	cout << "|" << setw(18) << right << student.grades_in_mathematics << " ";
	switch (student.specialty)
	{
	case ComputerScience:
		cout << "| " << setw(20) << setprecision(2) << fixed << right
			<< student.grades_in_programming << " |" << setw(27) << right << "|" << setw(20) << right << "|" << endl;
		break;
	case Informatics:
		cout << "|" << setw(23) << " |" << setw(25) << setprecision(2) << fixed << right
			<< student.grades_in_numerical_methods << " |" << setw(20) << right << "|" << endl;
		break;
	case Mathematics:
	case Physics:
	case Work:
		cout << "| " << setw(23) << "| " << setw(26) << right << "|" << " " << setw(17) << right
			<< student.grades_in_pedagogy << " |" << endl;
		break;
	}
}
void Print(char* fname)
{
	ifstream fin(fname);
	Student student;
	cout << "=================================================================================================================================================="
		<< endl;
	cout << "|№  |Прізвище  |Курс|Cпеціальність    |Oцінки з фізики|Oцінки з математики|Oцінки з програмування|Oцінки з чисельних методів|Oцінки з педагогіки|"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	int N = 1;
	while (fin.read((char*)&student, sizeof(Student)))
	{
		Print_student(N, student);
		N++;
	}
	fin.close();
	cout << "=================================================================================================================================================="
		<< endl;
	cout << endl;
}
void LineSearch_count(char* fname, int* count_3, int* count_4, int* count_5)
{
	ifstream fin(fname);
	Student student;
	while (fin.read((char*)&student, sizeof(Student)))
	{
		if (student.specialty == ComputerScience)
		{
			if (student.grades_in_programming == 3)
			{
				(*count_3)++;
			}
			else if (student.grades_in_programming == 4)
			{
				(*count_4)++;
			}
			else if (student.grades_in_programming == 5)
			{
				(*count_5)++;
			}
		}
	}
	fin.close();
}
void LineSearch_proc(char* fname, const int N, double* proc)
{
	ifstream fin(fname);
	Student student;
	int count = 0;
	while (fin.read((char*)&student, sizeof(Student)))
	{
		if ((student.grades_in_physics >= 4 && student.grades_in_physics <= 5) &&
			(student.grades_in_mathematics >= 4 && student.grades_in_mathematics <= 5))
		{
			count++;
		}
	}
	*proc =  100.0 * count / N;
}