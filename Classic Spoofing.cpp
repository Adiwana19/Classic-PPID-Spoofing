// Classic Spoofing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <tlhelp32.h>

DWORD GetPidByName(const wchar_t* pName) {
	PROCESSENTRY32 pEntry;
	HANDLE snapshot;

	pEntry.dwSize = sizeof(PROCESSENTRY32);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &pEntry) == TRUE) {
		while (Process32Next(snapshot, &pEntry) == TRUE) {
			if (_wcsicmp(pEntry.szExeFile, pName) == 0) {
				return pEntry.th32ProcessID;
				
			}
		}
	}
	CloseHandle(snapshot);
}


int main()
{
	PROCESS_INFORMATION info;
	const wchar_t* name = L"explorer.exe";
	DWORD id = GetPidByName(name);
;	SIZE_T lpsize = 0;
	InitializeProcThreadAttributeList(NULL, 1, 0, &lpsize);
	LPPROC_THREAD_ATTRIBUTE_LIST thread = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, lpsize);
	InitializeProcThreadAttributeList(thread, 1, 0, &lpsize);
	HANDLE proc =  OpenProcess(PROCESS_ALL_ACCESS, false, id);
	UpdateProcThreadAttribute(thread, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &proc, sizeof(HANDLE), NULL, NULL);
	Sleep(20000);
	printf("implant ID: %d | explorer ID: %d\n", GetCurrentProcessId(), id);
	DeleteProcThreadAttributeList(thread);
	CloseHandle(proc);

	return 0;
   
}

