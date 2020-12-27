#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
enum Specialty { ComputerScience, Informatics, Mathematics, Physics, Work };
string specialtyStr[] = { "����'����� �����", "�����������", "�����.�� ������.","Գ���� �� ������.","������� ��������" };
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
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	char fname[100];
	cout << "��'� ����� � ���������� : "; cin >> fname;
	int N;
	cout << "������ ������� �������� N: "; cin >> N;
	double proc;
	int count_3 = 0;
	int count_4 = 0;
	int count_5 = 0;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ʳ������ ������ � ���������������� �5�, �4�, �3�:" << endl;
		cout << " [4] - ������� ��������, �� �������� � � ������ � � ���������� ������ �4� ��� �5�:" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "ʳ������ ������ � ������������� �3�:" << count_3 << endl;
			cout << "ʳ������ ������ � ������������� �4�:" << count_4 << endl;
			cout << "ʳ������ ������ � ������������� �5�:" << count_5 << endl;
			break;
		case 4:
			LineSearch_proc(fname, N, &proc);
			cout << "������� ��������, �� �������� � � ������ � � ���������� ������ �4� ��� �5�:" << endl;
			cout << proc << "%" << endl;
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
Student Create()
{
	Student p;
	int specialty;
	cin.get(); // ������� ����� ��������� � �� ����������� �������
	cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
	cout << " �������: "; cin >> p.prizv;
	cout << " ����: "; cin >> p.course;
	cout << "  ������������ (0 -����'����� ����� , 1 -�����������, 2 -�����. �� ������., 3 - Գ���� �� ������., 4 - ������� ��������): ";
	cin >> specialty;
	p.specialty = (Specialty)specialty;
	cout << "������ � ������: "; cin >> p.grades_in_physics;
	cout << "������ � ����������: "; cin >> p.grades_in_mathematics;
	p.specialty = (Specialty)specialty;
	switch (p.specialty)
	{
	case ComputerScience:
		cout << "������ � �������������  : "; cin >> p.grades_in_programming;
		break;
	case Informatics:
		cout << "������ � ��������� ������  : "; cin >> p.grades_in_numerical_methods;
		break;
	case Mathematics:
	case Physics:
	case Work:
		cout << " ������ � ��������� : "; cin >> p.grades_in_pedagogy;
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
		cout << "������� � " << i + 1 << ":" << endl;
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
	cout << "|�  |�������  |����|C�����������    |O����� � ������|O����� � ����������|O����� � �������������|O����� � ��������� ������|O����� � ���������|"
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