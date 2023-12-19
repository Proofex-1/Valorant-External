#include "blabla/include.h"
#include "driver/driver.h"
#include "sdk/cheats.h"
#include "auth/auth.hpp"
#include "blabla/skStr.h"
#include "blabla/download.h"
#include <locale>
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <winerror.h>
#include <ntstatus.h>
#include <bcrypt.h>
#include <wininet.h>
#include <xstring>
#include <vector>
#include <fstream>
#include <chrono>
#include <codecvt>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "protect.h"
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "libcurl.lib")

#pragma optimize("", off)

using namespace KeyAuth;
std::string name = "orospu çocuğu cracklemeyecenki";
std::string ownerid = "orospu çocuğu cracklemeyecenki";
std::string secret = "orospu çocuğu cracklemeyecenki";
std::string version = "orospu çocuğu cracklemeyecenki";
std::string url = skCrypt("orospu çocuğu cracklemeyecenki").decrypt();

api KeyAuthApp(name, ownerid, secret, version, url);

using namespace std;
namespace fs = std::filesystem;
void vmdedect()
{
    if (IsProcessRunning(XorStr(L"joeboxcontrol.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();
         
        detect("joeboxcontrol");
    }
    else	if (IsProcessRunning(XorStr(L"joeboxserver.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("joeboxserver");
    }
    else	if (IsProcessRunning(XorStr(L"VMSrvc.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("VMSrvc");
    }
    else	if (IsProcessRunning(XorStr(L"VMUSrvc.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("VMUSrvc");
    }
    else	if (IsProcessRunning(XorStr(L"xenservice.exe").c_str()))
    {
        BlueScreen();
        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("xenservice");
    }
    else	if (IsProcessRunning(XorStr(L"VBoxControl.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("VBoxControl");
    }
    else	if (IsProcessRunning(XorStr(L"vboxtray.exe").c_str()))
    {
        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vboxtray");
    }
    else	if (IsProcessRunning(XorStr(L"vboxservice.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vboxservice");
    }
    else	if (IsProcessRunning(XorStr(L"vmtoolsd.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vmtoolsd");
    }
    else	if (IsProcessRunning(XorStr(L"vmwaretray.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vmwaretray");
    }
    else	if (IsProcessRunning(XorStr(L"vmwareuser.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vmwareuser");
    }
    else	if (IsProcessRunning(XorStr(L"VGAuthService.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("VGAuthService");
    }
    else	if (IsProcessRunning(XorStr(L"vmacthlp.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vmacthlp");
    }
    else	if (IsProcessRunning(XorStr(L"qemu-ga.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("qemu-ga");
    }
    else	if (IsProcessRunning(XorStr(L"vdagent.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vdagent");
    }
    else	if (IsProcessRunning(XorStr(L"vdservice.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vdservice");
    }
    else	if (IsProcessRunning(XorStr(L"prl_cc.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("prl_cc");
    }
    else	if (IsProcessRunning(XorStr(L"prl_tools.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");

        BlueScreen();

        detect("prl_tools");
    }
    else	if (IsProcessRunning(XorStr(L"vdagent.exe").c_str()))
    {
        BlueScreen();

        KeyAuthApp.ban("Oc Cracklemeye çalışıyor bide hahhahaha");
        BlueScreen();

        detect("vdagent");
    }
}


std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), " %d/%m/%y", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10);

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}


DWORD GetProcessID(const std::wstring processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}


auto get_process_wnd(uint32_t pid) -> HWND
{
    std::pair<HWND, uint32_t> params = { 0, pid };
    BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
        uint32_t processId = 0;

        if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
            SetLastError((uint32_t)-1);
            pParams->first = hwnd;
            return FALSE;
        }

        return TRUE;

        }, (LPARAM)&params);

    if (!bResult && GetLastError() == -1 && params.first)
        return params.first;

    return NULL;
}
string hwidcheck = DownloadString(XorStr("https://raw.githubusercontent.com/amliva/valo-auth/main/keys.txt"));


std::string generateRandomName(int length) {
    std::string name;
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < length; ++i) {
        int index = rand() % (sizeof(charset) - 1);
        name += charset[index];
    }

    return name;
}


std::string GetHWID() {
    std::wstring hwidW;
    HW_PROFILE_INFO hwProfileInfo;

    if (GetCurrentHwProfile(&hwProfileInfo) != 0) {
        hwidW = hwProfileInfo.szHwProfileGuid;
    }

    std::wstring::size_type startPos = hwidW.find_first_of(L"{");
    std::wstring::size_type endPos = hwidW.find_first_of(L"}");

    if (startPos != std::wstring::npos && endPos != std::wstring::npos && startPos < endPos) {
        hwidW = hwidW.substr(startPos + 1, endPos - startPos - 1);
    }

    std::string hwid(hwidW.begin(), hwidW.end());
    return hwid;
}

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);
size_t wclbcks(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}


void Hwd(std::string& hwid) {

    hwid = GetHWID();
}
std::string intToString(int value) {
    return std::to_string(value);
}
std::string encrypt(const std::string& input, const std::string& key)
{
    std::string output = input;
    for (size_t i = 0; i < input.length(); ++i)
    {
        output[i] = input[i] ^ key[i % key.length()];
    }
    return output;
}

std::string decrypt(const std::string& input, const std::string& key)
{
    std::string output = input;
    size_t length = input.length();
    size_t keyLength = key.length();

    for (size_t i = 0; i < length; ++i) {
        output[i] = input[i] ^ key[i % keyLength];
    }

    return output;
}



void cheat()
{

    std::string keyyyyyy = "0123456789";

    lexemvemmap_driver();

    std::string activecheat = "[+] Cheat active menu off/on key : Insert.";
    std::string notfounddrver = "[-] Driver not found. Exiting..";
    std::string ntfoundgame = "[-] Please open the program while in game..";

    std::string encryptedactv = encrypt(activecheat, keyyyyyy);
    std::string encryptedntfnddv = encrypt(notfounddrver, keyyyyyy);
    std::string encryptedntfondgme = encrypt(ntfoundgame, keyyyyyy);

    if (lexemvemem::lexemvefind_driver()) {
         system("cls");
    }
    else {
        system("cls");
        system("color c");
        for (char& c : notfounddrver) {
            std::cout << c;
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Her karakterin arasında 50 milisaniye bekleyin
        }
        Sleep(3000);
        exit(0);
    }

    if (lexemvemem::lexemvefind_process(L"VALORANT-Win64-Shipping.exe")) {
        lexemvevirtualaddy = get_guarded();
        check::guard = lexemvevirtualaddy;
        base = lexemvemem::lexemvefind_image();
        system("cls");
        for (char& c : activecheat) {
            std::cout << c;
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Her karakterin arasında 50 milisaniye bekleyin
        }

        LAGMMEEE::LASTRTC();

    }
    else {
        system("cls");
        system("color c");
        for (char& c : ntfoundgame) {
            std::cout << c;
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Her karakterin arasında 50 milisaniye bekleyin
        }
        Sleep(2000);
        exit(0);
    }
}

bool SetClipboard(const std::string& data) {

    auto size = data.size() + 1;
    auto pGlobal = GlobalAlloc(GMEM_MOVEABLE, size);

    if (!pGlobal) {

        return false;
    }

    OpenClipboard(0);
    EmptyClipboard();

    auto pLock = GlobalLock(pGlobal);

    if (!pLock) {
        CloseClipboard();
        return false;
    }

    CopyMemory(pLock, data.c_str(), size);

    GlobalUnlock(pGlobal);

    SetClipboardData(CF_TEXT, pGlobal);

    CloseClipboard();

    GlobalFree(pGlobal);

    return true;
}

int main(HWND, UINT, WPARAM, LPARAM);

int main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    GlobalAddAtomA("qwertyssddsjdfkjd");
    std::string randomName = RandomString(50);
    SetConsoleTitleA(randomName.c_str());
    Sleep(1500);
    std::string hwid;
    Protecion();
    BOOL result;
    if (GlobalFindAtomA("qwertyssddsjdfkjd") == 0)
    {
        exit(0);
    }
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &result); //Get a handle to our current process and send our result to the our boolean.
    if (result || result == 1) //Check to see if our result is true.
    {
        exit(0);
    }
    SetLastError(0); //Set last error to 0 so it won't conflict with our check.
    OutputDebugStringA("Using a debugger?"); //Send a little message to the debugger.
    if (GetLastError() != 0) //If the message passed without error (Meaning it was sent to the debugger)
    {
        exit(0);
    }


    std::string grsbsrz = "HWID is not found in system exiting...";
    std::string grsbsrl = "HWID found opening..";

    Hwd(hwid);
    std::cout << "\nYour hwid for login: " << hwid << std::endl;
    SetClipboard(hwid);
    std::cout << "\nHWID copied.";
    Sleep(3500);
    std::cout << "\nHWID checking..." << std::endl;
    Sleep(1500);
    Protecion();

    if (GlobalFindAtomA("qwertyssddsjdfkjd") == 0)
    {
        exit(0);
    }

    CheckRemoteDebuggerPresent(GetCurrentProcess(), &result); //Get a handle to our current process and send our result to the our boolean.
    if (result || result == 1) //Check to see if our result is true.
    {
        exit(0);
    }

    SetLastError(0); //Set last error to 0 so it won't conflict with our check.
    OutputDebugStringA("Using a debugger?"); //Send a little message to the debugger.
    if (GetLastError() != 0) //If the message passed without error (Meaning it was sent to the debugger)
    {
        exit(0);
    }
    if (hwidcheck.find("1.5") != std::string::npos)
    {
        if (hwidcheck.find(hwid) != std::string::npos)
        {
            int choice;
            system("cls");
            system("color e");
            std::cout << grsbsrl;
            Sleep(3000);
            system("cls");
            std::cout << "[1] cheat\n";
            std::cout << "[2] spoof\n";
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                Sleep(2000);
                cheat();
            }
            break;

        }
        else
        {
            system("cls");
            system("color c");
            std::cout << grsbsrz;
            Sleep(3000);
            exit(0);
        }
    }
    else
    {
        system("cls");
        system("color c");
        std::cout << "Please update the program.";
        Sleep(2000);
        exit(0);
    }
    
}



#pragma optimize("", on)