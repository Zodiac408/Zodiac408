#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

//Attach To Process
extern bool Attach();

//Get Module
extern DWORD getModule(char* modName);

//unknow
extern std::uint32_t find(const char* proc);

//ProcessID
extern DWORD pID;

//Handle To Process
extern HANDLE hProc;

//For Process
extern HANDLE hPrcoSnapshot;
extern PROCESSENTRY32 ProcEntry32;

//For Module
extern HANDLE hModuleSnapshot;
extern MODULEENTRY32 ModuleEnrty32;

class Memory
{
public:

	//WriteProcessMemory
	template<class dataType>
	void wpm(DWORD addresToWrite, dataType ValueToWrite)
	{
		WriteProcessMemory(hProc, (LPVOID)addresToWrite, &ValueToWrite, sizeof(dataType), 0);
	}

	//ReadProcessMemory
	template<class dataType>
	dataType rpm(DWORD addresToRead)
	{
		dataType Readbuffer;
		ReadProcessMemory(hProc, (LPVOID)addresToRead, &Readbuffer, sizeof(dataType), 0);
		//We Need To Read The Memory So return the Readbuffer
		return Readbuffer;
	}

}mem;

