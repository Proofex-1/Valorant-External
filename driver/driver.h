#include "check.h"
#include "Func.h"
#include "../sdk/xor.h"

uintptr_t lexemvevirtualaddy;

#define readioctlnewscarlet CTL_CODE(FILE_DEVICE_UNKNOWN, 0x762A, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_bascarlet CTL_CODE(FILE_DEVICE_UNKNOWN, 0X824F, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


typedef struct _exemreadwrite {
	INT32 lexemveprocess_id;
	ULONGLONG lexemveaddress;
	ULONGLONG lexemvebuffer;
	ULONGLONG lexemvesize;
	BOOLEAN lexemvewrite;
} rw, * prw;


typedef struct _ba {
	INT32 lexemveprocess_id;
	ULONGLONG* lexemveaddress;
} ba, * pba;


typedef struct _SYSTEM_BIGPOOL_ENTRY
{
	union {
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	};
	ULONG_PTR SizeInBytes;
	union {
		UCHAR Tag[4];
		ULONG TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, * PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION {
	ULONG Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[ANYSIZE_ARRAY];
} SYSTEM_BIGPOOL_INFORMATION, * PSYSTEM_BIGPOOL_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBigPoolInformation = 0x42
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI* pNtQuerySystemInformation)(
	IN _SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID                   SystemInformation,
	IN ULONG                    SystemInformationLength,
	OUT PULONG                  ReturnLength
	);

__forceinline auto query_bigpools() -> PSYSTEM_BIGPOOL_INFORMATION
{
	static const pNtQuerySystemInformation NtQuerySystemInformation =
		(pNtQuerySystemInformation)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQuerySystemInformation");

	DWORD length = 0;
	DWORD size = 0;
	LPVOID heap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0);
	heap = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, heap, 0xFF);
	NTSTATUS ntLastStatus = NtQuerySystemInformation(SystemBigPoolInformation, heap, 0x30, &length);
	heap = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, heap, length + 0x1F);
	size = length;
	ntLastStatus = NtQuerySystemInformation(SystemBigPoolInformation, heap, size, &length);

	return reinterpret_cast<PSYSTEM_BIGPOOL_INFORMATION>(heap);
}
__forceinline auto get_guarded() -> uintptr_t
{
	auto pool_information = query_bigpools();
	uintptr_t guarded = 0;

	if (pool_information)
	{
		auto count = pool_information->Count;
		for (auto i = 0ul; i < count; i++)
		{
			SYSTEM_BIGPOOL_ENTRY* allocation_entry = &pool_information->AllocatedInfo[i];
			const auto virtual_address = (PVOID)((uintptr_t)allocation_entry->VirtualAddress & ~1ull);
			if (allocation_entry->NonPaged && allocation_entry->SizeInBytes == 0x200000)
				if (guarded == 0 && allocation_entry->TagUlong == 'TnoC')
					guarded = reinterpret_cast<uintptr_t>(virtual_address);
		}
	}

	return guarded;
}

namespace lexemvemem {
	HANDLE lexemvedriver_handle;
	INT32 lexemveprocess_id;

	bool lexemvefind_driver() {
		lexemvedriver_handle = CreateFileW(_(L"\\\\.\\\StudioDevice"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (!lexemvedriver_handle || (lexemvedriver_handle == INVALID_HANDLE_VALUE))
			return false;

		return true;
	}

	INT32 lexemvefind_process(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					lexemveprocess_id = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);
		return lexemveprocess_id;
	}

	uintptr_t lexemvefind_image() {
		uintptr_t image_address = { NULL };
		_ba arguments = { NULL };

		arguments.lexemveprocess_id = lexemveprocess_id;
		arguments.lexemveaddress = (ULONGLONG*)&image_address;

		DeviceIoControl(lexemvedriver_handle, code_bascarlet, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

		return image_address;
	}

	void lexemvewrite_physical(PVOID address, PVOID buffer, DWORD size) {
		_exemreadwrite arguments = { 0 };

		arguments.lexemveaddress = (ULONGLONG)address;
		arguments.lexemvebuffer = (ULONGLONG)buffer;
		arguments.lexemvesize = size;
		arguments.lexemveprocess_id = lexemveprocess_id;
		arguments.lexemvewrite = TRUE;

		DeviceIoControl(lexemvedriver_handle, readioctlnewscarlet, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void lexemveread_physical(PVOID address, PVOID buffer, DWORD size) {
		_exemreadwrite arguments = { 0 };

		arguments.lexemveaddress = (ULONGLONG)address;
		arguments.lexemvebuffer = (ULONGLONG)buffer;
		arguments.lexemvesize = size;
		arguments.lexemveprocess_id = lexemveprocess_id;
		arguments.lexemvewrite = FALSE;

		DeviceIoControl(lexemvedriver_handle, readioctlnewscarlet, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

}

template <typename T>
T lexemveread2(uint64_t address) {
	T buffer{ };
	lexemvemem::lexemveread_physical((PVOID)address, &buffer, sizeof(T));
	if (check::is_guarded(buffer))
	{
		buffer = check::validate_pointer(buffer);
	}

	return buffer;
}

template <typename T>
T lexemveread(uint64_t address) {
	T buffer{ };
	lexemvemem::lexemveread_physical((PVOID)address, &buffer, sizeof(T));

	return buffer;
}

template <typename T>
T lxmvwrte(uint64_t address, T buffer) {

	lexemvemem::lexemvewrite_physical((PVOID)address, &buffer, sizeof(T));
	return buffer;
}