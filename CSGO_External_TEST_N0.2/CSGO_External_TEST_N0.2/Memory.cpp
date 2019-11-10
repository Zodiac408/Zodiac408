#include"Memory.h"
#include<windows.h>
#include<TlHelp32.h>
#include"playerinfo.h"

DWORD pID = NULL;

HANDLE hProc = NULL;

HANDLE hPrcoSnapshot = NULL;
PROCESSENTRY32 ProcEntry32;

HANDLE hModuleSnapshot = NULL;
MODULEENTRY32 ModuleEnrty32;

//AttachProc
bool Attach()
{
	const char* processName = "csgo.exe";

	PROCESSENTRY32 procEntry32;
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcSnap == INVALID_HANDLE_VALUE)
		return false;

	while (Process32Next(hProcSnap, &procEntry32))
	{
		if (!strcmp(processName, procEntry32.szExeFile))
		{
			HANDLE temp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			if (temp == INVALID_HANDLE_VALUE) {
				CloseHandle(hProcSnap);
				return false;
			}

			pID = procEntry32.th32ProcessID;
			hProc = temp;
			// NUMPAD 
			std::cout << "\t\t\t\t\t\tCSGO Legit Cheat By  Zodiac     " << std::endl;
			std::cout << "\t\t\t\t\t\t\t\   Enjoy!				  " << std::endl;
			std::cout << "--------------------Join My discord And Learn Together  Link = https://discord.gg/vvmtkJ-------------------------------" << std::endl;
			std::cout << "________________________________________________________________________________________________________________________" << std::endl;
			std::cout << "[0] Glow 瑩光" << std::endl;
			std::cout << "[1] BHOP 連跳" << std::endl;
			std::cout << "[2] No Hands 沒手" << std::endl;
			std::cout << "[3] ThirdPerson View 第三人稱" << std::endl;
			std::cout << "[4] FOV = 110  角度"<< std::endl;
			std::cout << "[5] FOV = 40 角度" << std::endl;
			std::cout << "[6] FOV = 10 角度(First Scoped)" << std::endl;
			std::cout << "[xButton1] Fakelag 延遲 140ms 【要按住】" << std::endl;
			CloseHandle(hProcSnap);
			return true;
		}
	}

	CloseHandle(hProcSnap);
	return false;
}

DWORD getModule(char* modName)
{
	hModuleSnapshot = INVALID_HANDLE_VALUE;
	hModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pID);

	if (hModuleSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't Take a Snapshot of Module" << std::endl;
		CloseHandle(hModuleSnapshot);
		return 0;
	}

	ModuleEnrty32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hModuleSnapshot, &ModuleEnrty32))
	{
		if (!strcmp(modName, ModuleEnrty32.szModule))
		{
			std::cout << "Module  Found " << ModuleEnrty32.szModule << " with base address " << std::hex << (DWORD)ModuleEnrty32.modBaseAddr << std::endl;
			//Close handle to process snapshot then return base address
			CloseHandle(hModuleSnapshot);
			return (DWORD)ModuleEnrty32.modBaseAddr;
		}
	}

	while (Module32Next(hModuleSnapshot, &ModuleEnrty32))
	{
		if (!strcmp(modName, ModuleEnrty32.szModule))
		{
			std::cout << "Module Found " << ModuleEnrty32.szModule << " with base address 0x" << std::hex << std::uppercase << (DWORD)ModuleEnrty32.modBaseAddr << std::endl;
			//Close handle to process snapshot then return base address
			CloseHandle(hModuleSnapshot);
			return (DWORD)ModuleEnrty32.modBaseAddr;
		}
	}

	std::cout << "Couldn't Find " << modName << " in the ModuleSnapshot" << std::endl;
	CloseHandle(hModuleSnapshot);
	return false;
}

std::uint32_t find(const char* proc)
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	if (Process32First(snapshot, &pe)) {
		while (Process32Next(snapshot, &pe))
		{
			if (!strcmp(proc, pe.szExeFile)) {
				CloseHandle(snapshot);
				//mylog << "Found proc!\n";
				return pe.th32ProcessID;
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}