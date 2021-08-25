#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include<windows.h>
#include <iomanip>
using namespace std;


class Question
{
public:
	string quest;
	vector<string> answers;
	int corrAnsw;

	Question(string que, vector<string> ans, int corr) :quest(que), answers(ans), corrAnsw(corr) {}

	void print()
	{
		cout << quest << endl;
		int i = 1;
		for (auto& v : answers)
		{
			cout << i << ". " << v << endl;
			i++;
		}
	}
};

class Test
{
public:
	int testNumber;
	int queAmount;
	string testName;
	list<Question> testList;

	Test() {};
	Test(int tNum, int qAm, string tNam, list<Question> tList) :testNumber(tNum), queAmount(qAm), testName(tNam), testList(tList) {}

	void prepareTest(int nummer)
	{
		ifstream in("1.txt");   // ?? nummer.txt ??
		string str;

		getline(in, str);
		testNumber = stoi(str);
		getline(in, str);
		queAmount = stoi(str);
		getline(in, str);
		testName = str;

		// ���������� �����

		for (int i = 0; i < queAmount; i++)     // ���� �� ���-�� ��������
		{
			string a[5];

			for (int j = 0; j < 5; j++)         // ���� �� �������
			{
				getline(in, a[j]);
			}
			vector<string> vec;
			vec.push_back(a[1]);
			vec.push_back(a[2]);
			vec.push_back(a[3]);
			int b = stoi(a[4]);
			Question q(a[0], vec, b);

			testList.push_back(q);             // ���������� ������� � ���� �����

		}

	}

	int doTest(int nummer)
	{
		prepareTest(nummer);
		int schet = 0, n, m;
		for (int i = 0; i < queAmount; i++)
		{
			system("cls");
			cout << testName << endl;
			cout << "-------------------------" << endl;

			testList.front().print();
			m = testList.front().corrAnsw;
			int m = i + 1;
			cin >> n;
			if (n == m)
			{
				cout << endl << "���������" << endl;
				schet++;
				cout << schet << "/" << m << endl;
				Sleep(3000);
			}
			else
			{
				cout << endl << "�� ���������" << endl;
				cout << schet << "/" << m << endl;
				Sleep(3000);
			}
			testList.pop_front();
		}
		system("cls");
		cout << "��� ��������� ���������� " << schet << "/" << queAmount << endl;
		Sleep(5000);
		return schet;

	}

	void saveResult(int schet)
	{
		ofstream out("result.txt", ios::app);  //??
		if (out.is_open())
		{
			out << testNumber << " " << schet << " " << "done" << " " << "all" << endl; //
		}
		out.close();
	}

	void lookResult()
	{
		system("cls");
		ifstream in("result.txt");
		string sstr;
		cout << "��� ��������" << endl;
		cout << "����� ����� - " << "������ - " << "������� - " << "����� - " << endl;
		while (in)
		{
			getline(in, sstr);
			cout << sstr << endl;
		}
		Sleep(5000);
	}

	void beginTest()
	{
		system("cls");
		cout << "������� ����� �����" << endl;
		int l;
		cin >> l;
		ifstream in("TestList.txt");
		string strr;
		int v;
		while (in)
		{
			getline(in, strr);
			v = stoi(strr);
			if (l == v)
			{
				int z = doTest(l);
				saveResult(z);
				break;
			}
		}
		cout << endl << "������ ����� �� ����������" << endl;
		Sleep(3000);
	}

	void enter()
	{};

	void menu()
	{
		setlocale(LC_ALL, "");
		enter();
		do
		{
			system("cls");
			cout << "1. ������ ����" << endl;
			cout << "2. ���������� ����" << endl;
			cout << "3. ����������� ����������" << endl;
			cout << "4. ������� ������������" << endl;
			cout << "5. �����" << endl;
			int g;
			cin >> g;
			switch (g)
			{
			case 1: beginTest();
				break;
			case 2:
				break;
			case 3: lookResult();
				break;
			case 4:
				break;
			case 5: exit(0);
				break;
			default: break;
			}

		} while (true);
	}
};




