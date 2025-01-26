#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

class Memory
{
private:
	HANDLE hProcess = NULL;
public:
	DWORD32 iPid = NULL;
	const char* szProcessName = "None";

	void GetProcessHandle(const char* process_name)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do 
		{
			if (!_stricmp(process_name, entry.szExeFile)) 
			{
				CloseHandle(snapshot);

				iPid = entry.th32ProcessID;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, iPid);
				szProcessName = process_name;
			}
		} while (Process32Next(snapshot, &entry));
	}

	uintptr_t GetModuleAddress(const char* module_name)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, iPid);

		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do 
		{
			if (!_stricmp(module_name, entry.szModule)) 
			{
				CloseHandle(snapshot);
				return (uintptr_t)entry.modBaseAddr;
			}
		} while (Module32Next(snapshot, &entry));

		CloseHandle(snapshot);
		return NULL;
	}

	template <typename t>
	t Read(uintptr_t address)
	{
		t ret;

		ReadProcessMemory(hProcess, (LPVOID)address, &ret, sizeof(ret), NULL);

		return ret;
	}

	template <typename t>
	void Write(uintptr_t address, t value)
	{
		WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), NULL);
	}

	bool IsProcessAlive()
	{
		if (hProcess)
		{
			DWORD ret = NULL;
			GetExitCodeProcess(hProcess, &ret);

			if (ret != STILL_ACTIVE)
			{
				hProcess = NULL;
				iPid = NULL;
				szProcessName = "None";

				return false;
			}
			return true;
		}
		return false;
	}
};

inline Memory memory;