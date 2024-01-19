#include <iostream>
#include <Windows.h>
using namespace std;



struct MyStruct
{

	int x;
	int size;
	int* pointer;
};



void FillArray(MyStruct* arr)
{
	for (int i = 0; i < arr->size; i++)
	{
		arr->pointer[i] = rand() % 10;
	}
}



void ShowArray(MyStruct* arr)
{
	for (int i = 0; i < arr->size; i++)
	{
		cout << arr->pointer[i] << " ";
	}
	cout << endl;
}



void push_back(MyStruct* arr)
{
	int* temp = new int[arr->size + 1];
	for (int i = 0; i < arr->size; i++)
	{
		temp[i] = arr->pointer[i];
	}
	temp[arr->size] = arr->x;

	delete[] arr->pointer;
	arr->pointer = temp;
	arr->size++;
}



DWORD WINAPI WorkerFunc(LPVOID arr)
{
	cout << "WorkerThread is working" << endl;
	int count = 0;

	for (int i = 0; i < ((MyStruct*)arr)->size; i++)
	{
		if (((MyStruct*)arr)->pointer[i] == ((MyStruct*)arr)->x)
		{
			count++;
		}
	}

	push_back(((MyStruct*)arr));
	ShowArray(((MyStruct*)arr));

	cout << "number of elements equal x: " << count << endl;
	return 0;
}



DWORD WINAPI CountFunc(LPVOID n)
{
	cout << "CountThread is working" << endl;

	int OldValue = 0;
	int CurrentValue = 1;
	int temp;

	cout << "Fib:";

	for (int i = 1; i < 10; i++)
	{
		cout << CurrentValue << " ";
		temp = CurrentValue;
		CurrentValue = CurrentValue + OldValue;
		OldValue = temp;
	}
	cout << endl;
	return 0;
}



int main()
{
	srand(time(NULL));

	HANDLE hWorker;
	DWORD WorkerID;

	HANDLE hCount;
	DWORD CountID;

	MyStruct arr;

	cout << "Enter size: ";
	cin >> arr.size;

	arr.pointer = new int[arr.size];

	int suspend_time;

	cout << "Enter suspend time (in ms): ";
	cin >> suspend_time;

	FillArray(&arr);
	ShowArray(&arr);

	cout << "Enter x: ";
	cin >> arr.x;

	hWorker = CreateThread(NULL, 0, WorkerFunc, &arr, 0, &WorkerID);

	int n = 10;
	hCount = CreateThread(NULL, 0, CountFunc, (void*)n, CREATE_SUSPENDED, &CountID);

	SuspendThread(hWorker);
	cout << "Thread suspended" << endl;
	Sleep(suspend_time);
	cout << "Thread resumed" << endl;
	ResumeThread(hWorker);

	ResumeThread(hCount);

	WaitForSingleObject(hWorker, INFINITE);
	CloseHandle(hWorker);
}


