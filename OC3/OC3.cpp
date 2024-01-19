#include "Header.h"
using namespace std;



int main()
{
	coutUptoK = CreateEvent(NULL, FALSE, FALSE, NULL);
	startSum = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&cs);

	qweStruct qwe;
	cin >> qwe;
	CreateAndFillArray(qwe);
	ShowArray(qwe);

	HANDLE hWork = CreateThread(NULL, 0, Work, &qwe, NULL, NULL);
	HANDLE hSum = CreateThread(NULL, 0, Sum, &qwe, NULL, NULL);

	WaitForSingleObject(coutUptoK, INFINITE);

	ShowArrayK(qwe);
	SetEvent(startSum);

	
	EnterCriticalSection(&cs);

	//тут вывод работы sum
	cout << "Sum element result: " << qwe.sumResult << endl;

	LeaveCriticalSection(&cs);


	WaitForSingleObject(hWork, INFINITE);
	CloseHandle(hWork);
}