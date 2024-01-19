#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <map>
using namespace std;

CRITICAL_SECTION cs;
HANDLE coutUptoK;
HANDLE startSum;


struct qweStruct
{
	char* arr;
	int size;
	int k;
	int sumResult;
};



istream& operator>>(istream& in, qweStruct& qwe)
{
	cout << "Enter size: ";
	cin >> qwe.size;
	cout << "Enter k: ";
	cin >> qwe.k;
	return in;
}



void CreateAndFillArray(qweStruct& qwe)
{
	srand(time(NULL));
	qwe.arr = new char[qwe.size];
	for (int i = 0; i < qwe.size; i++)
		qwe.arr[i] = rand();
}



void ShowArray(qweStruct& qwe)
{
	for (int i = 0; i < qwe.size; i++)
		cout << qwe.arr[i] << " ";
	cout << endl;
}



void ShowArrayK(qweStruct& qwe)
{
	for (int i = 0; i < qwe.k; i++)
		cout << qwe.arr[i] << " ";
	cout << endl;
}



DWORD WINAPI Work(LPVOID args)
{
	qweStruct* qwe = (qweStruct*)args;
	int il;
	cout << "Enter interval: ";
	cin >> il;
	map <char, int> ma;
	for (int i = 0; i < qwe->size; i++)
		ma[qwe->arr[i]]++;
	char* b = new char[qwe->size];
	int j = 0;

	for (int i = 0; i < qwe->size; i++)
	{
		if (ma[qwe->arr[i]] == 1)
		{
			b[j] = qwe->arr[i];
			j++;
			Sleep(il);
		}
		if (j == qwe->k)
		{
			//установить событие
			SetEvent(coutUptoK);
			cout << "Event has been set" << endl;
		}
	}
	for (int i = 0; i < qwe->size; i++)
	{
		if (ma[qwe->arr[i]] > 1)
		{
			for (int l = 0; l < ma[qwe->arr[i]]; l++)
			{
				b[j] = qwe->arr[i];
				j++;

				if (j == qwe->k)
				{
					//установить событие
					SetEvent(coutUptoK);
					cout << "Event has been set" << endl;
				}
			}
		}
	}
	qwe->arr = b;
	return 0;
}



DWORD WINAPI Sum(LPVOID args)
{
	qweStruct* qwe = (qweStruct*)args;
	EnterCriticalSection(&cs);
	WaitForSingleObject(startSum, INFINITE);



	int k1 = 0;
	for (int i = 0; i < qwe->k; i++)
		if (qwe->arr[i] >= '0' && qwe->arr[i] <= '9')
			k1++;
	qwe->sumResult = k1;

	LeaveCriticalSection(&cs);

	return 0;
}