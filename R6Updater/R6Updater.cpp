//Made by Kix

#include <Windows.h>
#include <iostream>
#include "Memory.h"
#include "Scan.h"
#include "Patterns.h"

int choice = 0;

void Init();
void ScanGameManager();
void ScanProfileManager();
void ScanRoundManager();
void ScanGlowManager();
void ScanNetworkManager();
void ScanAll();

int main()
{
    std::cout << "Welcome to R6Updater by Kix\n";
    std::cout << "Choose an option and await the results!\n\n";

    OPTIONS:

    std::cout << "~~~~~~~~~~ Options ~~~~~~~~~~\n";
    std::cout << "1. All\n";
    std::cout << "2. GameManager\n";
    std::cout << "3. ProfileManager\n";
    std::cout << "4. RoundManager\n";
    std::cout << "5. GlowManager\n";
    std::cout << "6. NetworkManager\n";
    std::cout << "7. Exit\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    std::cout << "Choice: ";

    std::cin >> choice;

    switch (choice)
    {
    case 1:
        system("cls");
        Init();
        ScanAll();
        break;

    case 2:
        system("cls");
        Init();
        ScanGameManager();
        break;

    case 3:
        system("cls");
        Init();
        ScanProfileManager();
        break;

    case 4:
        system("cls");
        Init();
        ScanRoundManager();
        break;

    case 5:
        system("cls");
        Init();
        ScanGlowManager();
        break;

    case 6:
        system("cls");
        Init();
        ScanNetworkManager();
        break;

    case 7:
        system("cls");
        return 0;
        break;

    default:
        system("cls");
        std::cout << "Please enter a valid choice!\n";
        Sleep(3000);
        system("cls");
        goto OPTIONS;
        break;
    }

    AGAIN:
    
    choice = 0;

    std::cout << "\nAgain(1: Yes, 2: No)?\n\n";

    std::cout << "Choice: ";

    std::cin >> choice;

    switch (choice)
    {
    case 1:
        system("cls");
        goto OPTIONS;
        break;

    case 2:
        system("cls");
        break;

    default:
        system("cls");
        std::cout << "Please enter a valid choice!\n";
        Sleep(3000);
        system("cls");
        goto AGAIN;
        break;
    }

    CloseHandle(Memory::hProc);

    return 0;
}

void Init()
{
    Memory::pid = Memory::GetProcessId("RainbowSix.exe");

    if (Memory::pid == 0)
    {
        MessageBoxA(NULL, "Please open the game and retry", "R6Updater - Error", MB_OK);
        exit(0);
    }

    Memory::modEntry = Memory::GetModule(Memory::pid, "RainbowSix.exe");

    if (Memory::modEntry.modBaseAddr == 0 || Memory::modEntry.modBaseSize == 0)
    {
        MessageBoxA(NULL, "Error getting base address and size", "R6Updater - Error", MB_OK);
        exit(0);
    }

    Memory::hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Memory::pid);

    if (Memory::hProc == INVALID_HANDLE_VALUE)
    {
        MessageBoxA(NULL, "Error opening handle to game", "R6Updater - Error", MB_OK);
        exit(0);
    }
}

void ScanGameManager()
{
    Scan* scan = new Scan(Memory::hProc, Memory::modEntry);

    uint64_t manager = Memory::GetActualAddr((uint64_t)scan->PatternScan(Patterns::GameManager) + 0x3);

    std::cout << "GameManager    -> 0x" << std::hex << std::uppercase << manager << std::nouppercase << std::endl;

    delete scan;
}

void ScanProfileManager()
{
    Scan* scan = new Scan(Memory::hProc, Memory::modEntry);

    uint64_t manager = Memory::GetActualAddr((uint64_t)scan->PatternScan(Patterns::ProfileManager) + 0x3);

    std::cout << "ProfileManager -> 0x" << std::hex << std::uppercase << manager << std::nouppercase << std::endl;

    delete scan;
}

void ScanRoundManager()
{
    Scan* scan = new Scan(Memory::hProc, Memory::modEntry);

    uint64_t manager = Memory::GetActualAddr((uint64_t)scan->PatternScan(Patterns::RoundManager) + 0x3);

    std::cout << "RoundManager   -> 0x" << std::hex << std::uppercase << manager << std::nouppercase << std::endl;

    delete scan;
}

void ScanGlowManager()
{
    Scan* scan = new Scan(Memory::hProc, Memory::modEntry);

    uint64_t manager = Memory::GetActualAddr((uint64_t)scan->PatternScan(Patterns::GlowManager) + 0x3);

    std::cout << "GlowManager    -> 0x" << std::hex << std::uppercase << manager << std::nouppercase << std::endl;

    delete scan;
}

void ScanNetworkManager()
{
    Scan* scan = new Scan(Memory::hProc, Memory::modEntry);

    uint64_t manager = Memory::GetActualAddr((uint64_t)scan->PatternScan(Patterns::NetworkManager) + 0x3);

    std::cout << "NetworkManager -> 0x" << std::hex << std::uppercase << manager << std::nouppercase << std::endl;

    delete scan;
}

void ScanAll()
{
    ScanGameManager();
    ScanProfileManager();
    ScanRoundManager();
    ScanGlowManager();
    ScanNetworkManager();
}
