#include <ntifs.h>
#include <windef.h>

UNICODE_STRING LHname, LHlink;

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

extern "C" NTSTATUS NTAPI IoCreateDriver(PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction);
extern "C" PVOID NTAPI PsGetProcessSectionBaseAddress(PEPROCESS Process);
extern "C" NTSTATUS NTAPI ZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, PULONG returnLength);

#define speedy_rw CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7B456, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define speedy_ba CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3C568, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define win_1803 17134
#define win_1809 17763
#define win_1903 18362
#define win_1909 18363
#define win_2004 19041
#define win_20H2 19569
#define win_21H1 20180
#define win_22H1 22000
#define win_22H2 24345
#define win_22H22 22621
#define win_222H222 19045

#define PAGE_OFFSET_SIZE 12
static const UINT64 PMASK = (~0xfull << 8) & 0xfffffffffull;

typedef struct _rw {
	INT32 process_id;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
	BOOLEAN write;
} rw, * prw;

typedef struct _ba {
	INT32 process_id;
	ULONGLONG* address;
} ba, * pba;

typedef struct _ga {
	ULONGLONG* address;
} ga, * pga;

NTSTATUS LHwrite(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_read)
{
	if (!target_address)
		return STATUS_UNSUCCESSFUL;

	PHYSICAL_ADDRESS AddrToWrite = { 0 };
	AddrToWrite.QuadPart = LONGLONG(target_address);

	PVOID pmapped_mem = MmMapIoSpaceEx(AddrToWrite, size, PAGE_READWRITE);

	if (!pmapped_mem)
		return STATUS_UNSUCCESSFUL;

	memcpy(pmapped_mem, buffer, size);

	*bytes_read = size;
	MmUnmapIoSpace(pmapped_mem, size);
	return STATUS_SUCCESS;
}

NTSTATUS LHread(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_read) {
	MM_COPY_ADDRESS to_read = { 0 };
	to_read.PhysicalAddress.QuadPart = (LONGLONG)target_address;
	return MmCopyMemory(buffer, to_read, size, MM_COPY_MEMORY_PHYSICAL, bytes_read);
}


INT32 LHget_winver() {
	RTL_OSVERSIONINFOW ver = { 0 };
	RtlGetVersion(&ver);
	switch (ver.dwBuildNumber)
	{
	case win_1803:
		return 0x0278;
		break;
	case win_1809:
		return 0x0278;
		break;
	case win_1903:
		return 0x0280;
		break;
	case win_1909:
		return 0x0280;
		break;
	case win_2004:
		return 0x0388;
		break;
	case win_20H2:
		return 0x0388;
		break;
	case win_21H1:
		return 0x0388;
		break;
	case win_22H1:
		return 0x0388;
		break;
	case win_22H2:
		return 0x0388;
		break;
	case win_22H22:
		return 0x0388;
		break;
	case win_222H222:
		return 0x0388;
		break;
	default:
		return 0x0388;
	}
}

UINT64 LHget_process_cr3(const PEPROCESS pProcess) {
	PUCHAR process = (PUCHAR)pProcess;
	ULONG_PTR process_dirbase = *(PULONG_PTR)(process + 0x28);
	if (process_dirbase == 0)
	{
		INT32 UserDirOffset = LHget_winver();
		ULONG_PTR process_userdirbase = *(PULONG_PTR)(process + UserDirOffset);
		return process_userdirbase;
	}
	return process_dirbase;
}

UINT64 LHtranslate_linear(UINT64 directoryTableBase, UINT64 virtualAddress) {
	directoryTableBase &= ~0xf;

	UINT64 pageOffset = virtualAddress & ~(~0ul << PAGE_OFFSET_SIZE);
	UINT64 pte = ((virtualAddress >> 12) & (0x1ffll));
	UINT64 pt = ((virtualAddress >> 21) & (0x1ffll));
	UINT64 pd = ((virtualAddress >> 30) & (0x1ffll));
	UINT64 pdp = ((virtualAddress >> 39) & (0x1ffll));

	SIZE_T readsize = 0;
	UINT64 pdpe = 0;
	LHread(PVOID(directoryTableBase + 8 * pdp), &pdpe, sizeof(pdpe), &readsize);
	if (~pdpe & 1)
		return 0;

	UINT64 pde = 0;
	LHread(PVOID((pdpe & PMASK) + 8 * pd), &pde, sizeof(pde), &readsize);
	if (~pde & 1)
		return 0;

	/* 1GB large page, use pde's 12-34 bits */
	if (pde & 0x80)
		return (pde & (~0ull << 42 >> 12)) + (virtualAddress & ~(~0ull << 30));

	UINT64 pteAddr = 0;
	LHread(PVOID((pde & PMASK) + 8 * pt), &pteAddr, sizeof(pteAddr), &readsize);
	if (~pteAddr & 1)
		return 0;

	/* 2MB large page */
	if (pteAddr & 0x80)
		return (pteAddr & PMASK) + (virtualAddress & ~(~0ull << 21));

	virtualAddress = 0;
	LHread(PVOID((pteAddr & PMASK) + 8 * pte), &virtualAddress, sizeof(virtualAddress), &readsize);
	virtualAddress &= PMASK;

	if (!virtualAddress)
		return 0;

	return virtualAddress + pageOffset;
}

ULONG64 LHfind_min(INT32 g, SIZE_T f) {
	INT32 h = (INT32)f;
	ULONG64 result = 0;

	result = (((g) < (h)) ? (g) : (h));

	return result;
}

NTSTATUS LHfrw(prw x) {
	if (!x->process_id)
		return STATUS_UNSUCCESSFUL;

	PEPROCESS process = NULL;
	PsLookupProcessByProcessId((HANDLE)x->process_id, &process);
	if (!process)
		return STATUS_UNSUCCESSFUL;

	ULONGLONG process_base = LHget_process_cr3(process);
	ObDereferenceObject(process);

	SIZE_T this_offset = NULL;
	SIZE_T total_size = x->size;

	INT64 physical_address = LHtranslate_linear(process_base, (ULONG64)x->address + this_offset);
	if (!physical_address)
		return STATUS_UNSUCCESSFUL;

	ULONG64 final_size = LHfind_min(PAGE_SIZE - (physical_address & 0xFFF), total_size);
	SIZE_T bytes_trough = NULL;

	if (x->write) {
		LHwrite(PVOID(physical_address), (PVOID)((ULONG64)x->buffer + this_offset), final_size, &bytes_trough);
	}
	else {
		LHread(PVOID(physical_address), (PVOID)((ULONG64)x->buffer + this_offset), final_size, &bytes_trough);
	}

	return STATUS_SUCCESS;
}

NTSTATUS LHfba(pba x) {
	if (!x->process_id)
		return STATUS_UNSUCCESSFUL;

	PEPROCESS process = NULL;
	PsLookupProcessByProcessId((HANDLE)x->process_id, &process);
	if (!process)
		return STATUS_UNSUCCESSFUL;

	ULONGLONG image_base = (ULONGLONG)PsGetProcessSectionBaseAddress(process);
	if (!image_base)
		return STATUS_UNSUCCESSFUL;

	RtlCopyMemory(x->address, &image_base, sizeof(image_base));
	ObDereferenceObject(process);

	return STATUS_SUCCESS;
}

NTSTATUS LHio_controller(PDEVICE_OBJECT device_obj, PIRP irp) {
	UNREFERENCED_PARAMETER(device_obj);

	NTSTATUS status = { };
	ULONG bytes = { };
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG size = stack->Parameters.DeviceIoControl.InputBufferLength;

	if (code == speedy_rw) {
		if (size == sizeof(_rw)) {
			prw req = (prw)(irp->AssociatedIrp.SystemBuffer);

			status = LHfrw(req);
			bytes = sizeof(_rw);
		}
		else
		{
			status = STATUS_INFO_LENGTH_MISMATCH;
			bytes = 0;
		}
	}
	else if (code == speedy_ba) {
		if (size == sizeof(_ba)) {
			pba req = (pba)(irp->AssociatedIrp.SystemBuffer);

			status = LHfba(req);
			bytes = sizeof(_ba);
		}
		else
		{
			status = STATUS_INFO_LENGTH_MISMATCH;
			bytes = 0;
		}
	}

	irp->IoStatus.Status = status;
	irp->IoStatus.Information = bytes;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS LHunsupported_dispatch(PDEVICE_OBJECT device_obj, PIRP irp) {
	UNREFERENCED_PARAMETER(device_obj);

	irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return irp->IoStatus.Status;
}

NTSTATUS LHdispatch_handler(PDEVICE_OBJECT device_obj, PIRP irp) {
	UNREFERENCED_PARAMETER(device_obj);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

	switch (stack->MajorFunction) {
	case IRP_MJ_CREATE:
		break;
	case IRP_MJ_CLOSE:
		break;
	default:
		break;
	}

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

void LHunload_drv(PDRIVER_OBJECT drv_obj) {
	NTSTATUS status = { };

	status = IoDeleteSymbolicLink(&LHlink);

	if (!NT_SUCCESS(status))
		return;

	IoDeleteDevice(drv_obj->DeviceObject);
}

NTSTATUS LHinitialize_driver(PDRIVER_OBJECT drv_obj, PUNICODE_STRING path) {
	UNREFERENCED_PARAMETER(path);

	NTSTATUS status = { };
	PDEVICE_OBJECT device_obj = { };

	RtlInitUnicodeString(&LHname, L"\\Device\\BattlEyeServices");
	RtlInitUnicodeString(&LHlink, L"\\DosDevices\\BattlEyeServices");

	status = IoCreateDevice(drv_obj, 0, &LHname, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_obj);

	if (!NT_SUCCESS(status))
		return status;

	status = IoCreateSymbolicLink(&LHlink, &LHname);

	if (!NT_SUCCESS(status))
		return status;

	for (int i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		drv_obj->MajorFunction[i] = &LHunsupported_dispatch;

	device_obj->Flags |= DO_BUFFERED_IO;
	
	drv_obj->MajorFunction[IRP_MJ_CREATE] = &LHdispatch_handler;
	drv_obj->MajorFunction[IRP_MJ_CLOSE] = &LHdispatch_handler;
	drv_obj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = &LHio_controller;
	drv_obj->DriverUnload = &LHunload_drv;

	device_obj->Flags &= ~DO_DEVICE_INITIALIZING;

	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	return IoCreateDriver(NULL, &LHinitialize_driver);
}
