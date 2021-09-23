#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include<windows.h>
#include <iomanip>
#include <cstdlib> // ������� �����
#include < sstream>  // ��� � ������
using namespace std;

class Schot
{
public:
	int ocenka;
	int kolvoOtvetov;
	int vsegoVoprosov;

	Schot(int oc, int kO, int vV) : ocenka(oc), kolvoOtvetov(kO), vsegoVoprosov(vV) {}
};

class User
{
public:
	string login;
	string password;
	string name;
	int type;
};

class Question
{
public:
	string quest;
	vector<string> answers;
	int corrAnsw;

	Question(string que, vector<string> ans, int corr) :quest(que), answers(ans), corrAnsw(corr) {}

	void print(int admin = 0)
	{
		cout << quest << endl;
		cout << "------------------------------" << endl;
		int i = 1;
		for (auto& v : answers)
		{
			cout << i << ". " << v << endl;
			i++;
		}
		if (admin != 1)
		{
			cout << endl << "5. ��������� � �����" << endl;
		}
		cout << "------------------------------" << endl;
	}
};

class Test
{
public:
	int testNumber;
	int queAmount;
	string testName;
	list<Question> testList;
	Schot OTVETU{ 0, 0, 0 };
	User user;

	Test() {};
	Test(int tNum, int qAm, string tNam, list<Question> tList, Schot otv) :testNumber(tNum), queAmount(qAm), testName(tNam), testList(tList), OTVETU(otv){}

	void lookCategory() // ����� ���������
	{
		system("cls");
		cout << "���������" << endl;
		cout << "--------------------------" << endl;
		ifstream in6("CategoryList.txt");
		string strr;
		while (getline(in6, strr))
		{
			int v = atoi(strr.c_str());
			getline(in6, strr);

			cout << v << ". " << strr << endl;
		}
	}

	int chooseCategory()  // ���������� ����� ���������
	{
		cout << endl << "�������� ���������" << endl;
		int d;
		cin >> d;
		ifstream in7("CategoryList.txt");
		string strr;
		while (getline(in7, strr))
		{
			int v = atoi(strr.c_str());
			getline(in7, strr);
			if (d == v)
			{
				return v;
			}
		}
	}

	void lookCategoryTests(int num)  // ����� ������ �� ���������
	{
		system("cls");
		stringstream ss;
		string nom;
		ss << num;     // ������� ���� � ������
		ss >> nom;
		cout << "����� � ���������" << endl;
		cout << "--------------------------" << endl;
		ifstream in8(nom + "Category.txt"); 
		string strr, strrr;
		while (getline(in8, strr))
		{
			int v = atoi(strr.c_str());
			getline(in8, strr);
			getline(in8, strrr);
			int c = atoi(strrr.c_str());
			cout << v << ". " << strr << " ���� ����� - " << c << endl;
		}
	}

	int chooseCategoryTest(int num)  // ����� ����� �� ���������
	{
		stringstream ss;
		string nom;
		ss << num;     
		ss >> nom;
		cout << endl << "�������� ���� � ��������� " << endl;
		int d;
		cin >> d;
		ifstream in9(nom + "Category.txt");
		string strr, strrr;
		while (getline(in9, strr))
		{
			int v = atoi(strr.c_str());
			getline(in9, strr);
			getline(in9, strrr);
			int c = atoi(strrr.c_str());
			if (d == v)
			{
				return c;
			}
		}
	}

	int chooseAdminTest()  // ����� ������ �����
	{
		cout << endl;
		cout << "�������� ���� " << endl;
		int d;
		cin >> d;
		ifstream in11("TestList.txt");
		string strr, strrr;
		while (getline(in11, strr))
		{
			int v = atoi(strr.c_str());
			getline(in11, strr);
			if (d == v)
			{
				return v;
			}
		}
	}

	void prepareTest(int nummer)  // ���������� ����� �����
	{
		stringstream ss;
		string nom;
		ss << nummer;
		ss >> nom;

		ifstream in(nom + ".txt");
		string str;

		getline(in, str);
		testNumber = atoi(str.c_str());
		getline(in, str);
		queAmount = atoi(str.c_str());
		OTVETU.vsegoVoprosov = queAmount;
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

	

	void printAllTests()  // ����� ���� �������� ������
	{
		system("cls");
		cout << "������ ���� ������" << endl;
		cout << "------------------------------" << endl;
		ifstream in5("TestList.txt");
		string strr;
		while (getline(in5, strr))
		{
			int v = atoi(strr.c_str());    ///// ������� �� ������� � ���
			getline(in5, strr);

			cout << v << ". " << strr << endl;
		}
	}

	Schot doTest(int nummer)  // ��� ����
	{
		prepareTest(nummer);
		OTVETU.ocenka = 0;
		int yourAnswer, correctAnswer, m;
		for (int i = 0; i < queAmount; i++)
		{
			system("cls");
			cout << testName << endl;
			m = i + 1;
			cout << "------------------------------" << endl;
			cout << "������ ����� " << m << endl;
			cout << "------------------------------" << endl;

			testList.front().print();
			correctAnswer = testList.front().corrAnsw;
			
			cin >> yourAnswer;
			
			if (yourAnswer < 4)
			{
				if (yourAnswer == correctAnswer)
				{
					cout << endl << "���������" << endl;
					OTVETU.ocenka++;
					OTVETU.kolvoOtvetov = m;
					cout << OTVETU.ocenka << "/" << OTVETU.kolvoOtvetov << endl;
					cout << "4. �����" << endl;
					int z;
					cin >> z;
				}
				else
				{
					cout << endl << "�� ���������" << endl;
					OTVETU.kolvoOtvetov = m;
					cout << OTVETU.ocenka << "/" << OTVETU.kolvoOtvetov << endl;
					cout << "4. �����" << endl;
					int z;
					cin >> z;
				}
			}
			else
			{
				if (yourAnswer == 5)
				{
					break;
				}
			}
			testList.pop_front();
		}
		system("cls");
		cout << "��� ��������� ���������� " << OTVETU.ocenka << "/" << OTVETU.vsegoVoprosov << endl;
		return OTVETU;

	}

	void lookAdminTest(int nummer)  // �������� ����� �������
	{
		prepareTest(nummer);
		system("cls");
		int correctAnswer, m;
		cout << testName << endl;
		for (int i = 0; i < queAmount; i++)
		{
			cout << endl;
			m = i + 1;
			cout << "------------------------------" << endl;
			cout << "������ ����� " << m << endl;
			cout << "------------------------------" << endl;

			testList.front().print(1);
			correctAnswer = testList.front().corrAnsw;
			cout << "���������� ����� - " << correctAnswer << endl;

			testList.pop_front();
		}
	}

	void saveResult(Schot otv)  // ���������� ������
	{
		ofstream out(user.login + "result.txt", ios::app);  
		if (out.is_open())
		{
			out << testNumber << endl;
			out << otv.ocenka << endl;
			out << otv.kolvoOtvetov << endl;
			out << otv.vsegoVoprosov << endl; 
		}
		out.close();
	}

	void lookResult() // �������� ������� ����� ������
	{
		system("cls");
		ifstream in(user.login + "result.txt");
		string sstr;
		cout << user.name << endl;
		while (getline(in, sstr))
		{
			cout << "����� ����� - " << sstr;

			getline(in, sstr);
			cout << ", ������ - " << sstr;

			getline(in, sstr);
			cout << ", ��������� - " << sstr;

			getline(in, sstr);
			cout << " �� " << sstr;

			cout << endl;
		}
		int z;
		cout << "1. �����" << endl;
		cin >> z;
	}

	void beginTest()  // ������ �����
	{
		system("cls");
		lookCategory();
		int cat = chooseCategory();
		lookCategoryTests(cat);
		int tes = chooseCategoryTest(cat);

		ifstream in("TestList.txt");
		string strr;
		int v;
		while (in)
		{
			getline(in, strr);
			v = atoi(strr.c_str());
			getline(in, strr);
			if (tes == v)
			{
				Schot otvet = doTest(tes);
				saveResult(otvet);
				break;
			}
		}
		if (tes != v)
		{
			cout << endl << "������ ����� �� ����������" << endl;
		}
		int z;
		cout << "1. �����" << endl;
		cin >> z;
	}

	void continueTest()  // ���������� �� ����������� ���� // ??
	{
		system("cls");
		ifstream in(user.login + "result.txt");
		string sstr;
		vector<string> vect;
		int sdel, iz, ocen, nomTest;
		string sdelano, izz, ocenka, nomerTesta;
		cout << user.name << endl;
		while (getline(in, sstr))
		{
			cout << "����� ����� - " << sstr;
			nomTest = atoi(sstr.c_str());
			nomerTesta = sstr;

			getline(in, sstr);
			cout << ", ������ - " << sstr;
			ocen = atoi(sstr.c_str());
			ocenka = sstr;

			getline(in, sstr);
			cout << ", ��������� - " << sstr;
			sdel = atoi(sstr.c_str());
			sdelano = sstr;

			getline(in, sstr);
			cout << " �� " << sstr;
			iz = atoi(sstr.c_str());
			izz = sstr;
			 
			cout << endl;

			if (sdel == iz)
			{
				vect.push_back(nomerTesta);
				vect.push_back(ocenka);
				vect.push_back(sdelano);
				vect.push_back(izz);
			}

			if (sdel < iz)
				break;
		}

		prepareTest(nomTest);

		OTVETU.ocenka = ocen;
		OTVETU.kolvoOtvetov = sdel;
		OTVETU.vsegoVoprosov = iz;
		int yourAnswer, correctAnswer, m;

		for (int q = 0; q < sdel; q++)
		{
			testList.pop_front();
		}

		for (int i = sdel; i < queAmount; i++)
		{
			system("cls");

			cout << testName << endl;
			m = i + 1;
			cout << "------------------------------" << endl;
			cout << "������ ����� " << m << endl;
			cout << "------------------------------" << endl;

			testList.front().print();
			correctAnswer = testList.front().corrAnsw;

			cin >> yourAnswer;

			if (yourAnswer < 4)
			{
				if (yourAnswer == correctAnswer)
				{
					cout << endl << "���������" << endl;
					OTVETU.ocenka++;
					OTVETU.kolvoOtvetov = m;
					cout << OTVETU.ocenka << "/" << OTVETU.kolvoOtvetov << endl;
					cout << "4. �����" << endl;
					int z;
					cin >> z;
				}
				else
				{
					cout << endl << "�� ���������" << endl;
					OTVETU.kolvoOtvetov = m;
					cout << OTVETU.ocenka << "/" << OTVETU.kolvoOtvetov << endl;
					cout << "4. �����" << endl;
					int z;
					cin >> z;
				}
			}
			else
			{
				if (yourAnswer == 5)
				{
					break;
				}
			}
			testList.pop_front();
		}
		system("cls");
		cout << "��� ��������� ���������� " << OTVETU.ocenka << "/" << OTVETU.vsegoVoprosov << endl;
		

		vect.push_back(nomerTesta);
		stringstream ss;
		string nom;
		ss << OTVETU.ocenka;    
		ss >> nom;
		vect.push_back(nom);
		ss << OTVETU.kolvoOtvetov;    
		ss >> nom;
		vect.push_back(nom);
		ss << OTVETU.vsegoVoprosov;    
		ss >> nom;
		vect.push_back(nom);

		
		while (getline(in, sstr))
		{
			nomerTesta = sstr;

			getline(in, sstr);
			ocenka = sstr;

			getline(in, sstr);
			sdelano = sstr;

			getline(in, sstr);
			izz = sstr;

		    vect.push_back(nomerTesta);
			vect.push_back(ocenka);
			vect.push_back(sdelano);
			vect.push_back(izz);
		}

		ofstream ofs;
		ofs.open(user.login + "result.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream out(user.login + "result.txt", ios::app);
		if (out.is_open())
		{
			for (auto& v : vect)
			{
				out << v << endl;
			}
		}
		out.close();
		
		cout << "1. �����" << endl;
		int z;
		cin >> z;
	}

	void userMenu()  // ���� ������������
	{
		setlocale(LC_ALL, "");
		int gg = 1;
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
			case 2: continueTest();
				break;
			case 3: lookResult();
				break;
			case 4: gg = 4;
				break;
			case 5: exit(0);
				break;
			default: break;
			}
		} while(gg != 4);

		

	}

	void addTest() // �������� ����� ���� �������
	{
		system("cls");
		cout << "������� �������� �����" << endl;
		string tName;
		cin >> tName;
		cout << "������� ���-�� ��������" << endl;
		int tVopr;
		cin >> tVopr;

		ifstream in10("TestList.txt");
		string strr;
		int v;
		while (getline(in10, strr))
		{
			v = atoi(strr.c_str());
			getline(in10, strr);
		}

		v++;

		ofstream out("TestList.txt", ios::app);  
		if (out.is_open())
		{
			out << endl;
			out << v << endl;
			out << tName;
		}
		out.close();

		stringstream ss;
		string nom, vop;
		ss << v;     
		ss >> nom;
	
		string questParts;
		int trueAns;

		ofstream out1(nom + ".txt", ios::app);
		if (out1.is_open())
		{
			out1 << v << endl;
			out1 << tVopr << endl;
			out1 << tName << endl;
			for (int h = 0; h < tVopr; h++)
			{
				cout << "������� ������" << endl;
				cin.ignore();
				getline(cin, questParts);
				out1 << questParts << endl;

				cout << "������� ����� 1." << endl;
				
				getline(cin, questParts);
				out1 << questParts << endl;

				cout << "������� ����� 2." << endl;
				
				getline(cin, questParts);
				out1 << questParts << endl;

				cout << "������� ����� 3." << endl;
				
				getline(cin, questParts);
				out1 << questParts << endl;

				cout << "������� ����� ����������� ������" << endl;
				cin >> trueAns;
				out1 << trueAns << endl;
			}
		}
		out1.close();

		for (int i = 0; i < tVopr; i++)
		{

		}
	}

	void adminTest() // ����� ���� ������, ����� � ����� � ������ ������
	{
		printAllTests();
		int b = chooseAdminTest();
		lookAdminTest(b);
		cout << endl;
		cout << "1. �����" << endl;;
		int m; 
		cin >> m;
		
	}

	void printAllUsers() // ����� ������� ���� �������������
	{
		system("cls");
		cout << "������ ���� �������������" << endl;
		cout << "------------------------------" << endl;
		ifstream in12("users.txt");
		string strr;
		int sum = 0;
		while (getline(in12, strr))
		{
			sum++;
			cout << sum << ". " << strr << endl;
		}
	}

	string chooseAdminUsers() // ���������� ����� ������������ ��� ������. ���������
	{
		cout << endl;
		cout << "�������� ������������ ��� ���������� ���������" << endl;
		int d, sum = 0;
		cin >> d;
		ifstream in13("users.txt");
		string strr;
		while (getline(in13, strr))
		{
			sum++;
			if (d == sum)
			{
				return strr;
			}
		}
	}

	int chooseAdminUsersDelete() // ���������� ����� ������������ ��� ������. ��������
	{
		cout << "�������� ������������ ��� ��������" << endl;
		int d, sum = 0;
		cin >> d;
		ifstream in13("users.txt");
		string strr;
		while (getline(in13, strr))
		{
			sum++;
			if (d == sum)
			{
				return sum;
			}
		}
	}
	
	void lookAdminUser(string login) // �������� ������ ������������ � ������ ������
	{
		system("cls");
		string sstr;
		ifstream in14(login + ".txt");
		cout << "�����            - " << login << endl;
		getline(in14, sstr);
		cout << "������           - " << sstr << endl;
		getline(in14, sstr);
		cout << "���              - " << sstr << endl;
		getline(in14, sstr);
		if (sstr == "1")
		{
			cout << "��� ������������ - �����" << endl;
		}
		else
		{
			cout << "��� ������������ - ������������" << endl;
		}
		
		ifstream in13(login + "result.txt");
		while (getline(in13, sstr))
		{
			cout << "����� ����� - " << sstr;

			getline(in13, sstr);
			cout << ", ������ - " << sstr;

			getline(in13, sstr);
			cout << ", ��������� - " << sstr;

			getline(in13, sstr);
			cout << " �� " << sstr;

			cout << endl;
		}
	}

	void adminUsers() // ����� �������������, ����� � ��������
	{
		printAllUsers();
		string b = chooseAdminUsers();
		lookAdminUser(b);
		cout << endl;
		cout << "1. �����" << endl;;
		int m;
		cin >> m;

	}

	void deleteUser() // �������� ������������
	{
		printAllUsers();
		int nom = chooseAdminUsersDelete();


		vector<string> vect;

		ifstream in20("users.txt");
		string sstr;
		int sum = 0;
		while (getline(in20, sstr))
		{
			sum++;
			if (nom != sum)
			{
				vect.push_back(sstr);
			}
		}

		ofstream ofs;
		ofs.open("users.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream out("users.txt", ios::app);  
		if (out.is_open())
		{

			for (auto& v : vect)
			{
				out << v << endl;
			}
		}
		out.close();
	}

	int chooseAdminTestDelete() // ���������� ����� ����� ��� ��������
	{
		cout << endl;
		cout << "�������� ���� ��� ��������" << endl;
		int d;
		cin >> d;
		ifstream in11("TestList.txt");
		string strr, strrr;
		while (getline(in11, strr))
		{
			int v = atoi(strr.c_str());
			getline(in11, strr);
			if (d == v)
			{
				return v;
			}
		}
	}

	void deleteTest() // �������� �����
	{
		printAllTests();
		int nom = chooseAdminTestDelete();


		vector<string> vect;

		ifstream in21("TestList.txt");
		string sstr, sstrr;
		
		while (getline(in21, sstr))
		{
			int v = atoi(sstr.c_str());
			getline(in21, sstrr);

			if (nom != v)
			{
				vect.push_back(sstr);
				vect.push_back(sstrr);
			}
		}

		ofstream ofs;
		ofs.open("TestList.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream out("TestList.txt", ios::app);
		if (out.is_open())
		{

			for (auto& v : vect)
			{
				out << v << endl;
			}
		}
		out.close();
	}

	void addReadyTest() // �������� ������� ���� �� ������ ??
	{
		system("cls");
		cout << "������� ����� �����" << endl;
		cout << "(������� ����� ����� �������� �� ���������� � ������, ������ ������ ��������� !!!)" << endl;
		string nomer;
		cin >> nomer;

		ifstream in23(nomer + ".txt");
		string strg;
		getline(in23, strg);
		getline(in23, strg);
		getline(in23, strg);

		vector<string> vect;

		ifstream in22("TestList.txt");
		string sstr, sstrr;

		int number = atoi(nomer.c_str());

		while (getline(in22, sstr))
		{
			int v = atoi(sstr.c_str());
			getline(in22, sstrr);

			if (number > v)
			{
				vect.push_back(sstr);
				vect.push_back(sstrr);
			}
			if (number < v)
			{
				vect.push_back(nomer);
				vect.push_back(strg);
				vect.push_back(sstr);
				vect.push_back(sstrr);
				number = 5000;
			}
			if (number == v)  //??//
			{
				vect.push_back(sstr);
				vect.push_back(sstrr);
			}
		}

		ofstream ofs;
		ofs.open("TestList.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream out("TestList.txt", ios::app);
		if (out.is_open())
		{

			for (auto& v : vect)
			{
				out << v << endl;
			}
		}
		out.close();
		cin >> number;
	}

	void adminMenu() // ���� ������
	{
		int pp = 1;
		do
		{
			system("cls");
			cout << "1. �������� ������" << endl;
			cout << "2. �������� ����� ����" << endl;
			cout << "3. �������� ������� ���� �� ������" << endl;
			cout << "4. ������� ����" << endl;
			cout << "5. �������� �������������" << endl;
			cout << "6. ������� ������������" << endl;
			cout << "7. ������� ������������" << endl;
			cout << "8. �����" << endl;

			int g;
			cin.ignore();
			cin >> g;
			switch (g)
			{
			case 1: adminTest();
				break;
			case 2: addTest();
				break;
			case 3: addReadyTest();
				break;
			case 4: deleteTest();
				break;
			case 5: adminUsers();
				break;
			case 6: deleteUser();
				break;
			case 7: pp = 7;
				break;
			case 8: exit(0);
				break;
			default: break;
			}

		} while (pp != 7);
		
	}

	void registration() // �����������
	{
		system("cls");
		cout << "���������� ���� �����" << endl;
		string registrLog, registrPass, registrName;
		int registrType;
		cin >> registrLog;
		
		ofstream out1("users.txt", ios::app);  
		if (out1.is_open())
		{
			out1 << registrLog << endl;
		}
		out1.close();

		cout << "���������� ���� ������" << endl;
		cin >> registrPass;
		ofstream out2(registrLog + ".txt", ios::app);
		if (out2.is_open())
		{
			out2 << registrPass << endl;
		}
		out2.close();

		cout << "������� ���� ���" << endl;
		cin.ignore();
		getline(cin, registrName);
		ofstream out3(registrLog + ".txt", ios::app);
		if (out3.is_open())
		{
			out3 << registrName<< endl;
		}
		out3.close();

		cout << "������� ����� ������������: 0-������������, 1-�����" << endl;
		cin >> registrType;
		ofstream out4(registrLog + ".txt", ios::app);
		if (out4.is_open())
		{
			out4 << registrType << endl;
		}
		out4.close();

		system("cls");
		cout << "�� ������������������" << endl;
		cout << "1. �����" << endl;
		int b;
		cin >> b;
	}

	void enter() // ���� 
	{
		
		system("cls");
		cout << "������� ��� �����" << endl;
		string login;
		string userName;
		string userType;
		cin >> login;
		ifstream in("users.txt");
		string strr, log, userPass;
		while (in)
		{
			getline(in, strr);
			log = strr;
			if (login == log)
			{
				user.login = log;
				ifstream in2(log + ".txt");
				getline(in2, userPass);
				user.password = userPass;
				getline(in2, userName);
				user.name = userName;
				getline(in2, userType);
				user.type = stoi(userType);
				break;
			}
		}
		if (login != log)
		{
			cout << endl << "������ ������������ �� ����������" << endl;
			cout << endl << "1. �����������" << endl;
			cout <<         "2. �����" << endl;
			int reg;
			cin >> reg;
			switch (reg)
			{
			case 1: registration(); break;
			case 2:  break;;
			default: break;
			}
		}
		else
		{
			cout << "������������ ������" << endl;
			string password;
			cout << "������� ������" << endl;
			cin >> password;
			if (password == userPass)
			{
				if (user.type == 0)
				{
					userMenu();
				}
				else
				{
					adminMenu();
				}
			}
			else
			{
				cout << "������ �� ������" << endl;
				cout << "1. �����" << endl;
				int b;
				cin >> b;
			}
		}


	}

	void Start() // �����
	{
		while (true)
		{
			setlocale(LC_ALL, "");
			system("cls");
			cout << "1. �����" << endl;
			cout << "2. �����" << endl;
			int g;
			cin >> g;
			switch (g)
			{
			case 1: enter();
				break;
			case 2: exit(0);
				break;
			default: break;
			}
		}
	};

	
};




