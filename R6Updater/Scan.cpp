#include "Scan.h"

Scan::Scan()
{

}

Scan::Scan(HANDLE hProc, MODULEENTRY32 modEntry)
{
    this->hProc = hProc;
    this->modEntry = modEntry;
}

char* Scan::ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
{
    intptr_t patternLen = strlen(mask);

    for (int i = 0; i < size; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }
    return nullptr;
}

char* Scan::ScanEx(char* pattern, char* mask, char* begin, intptr_t size, HANDLE hProc)
{
    char* match{ nullptr };
    SIZE_T bytesRead;
    DWORD oldprotect;
    char* buffer{ nullptr };
    MEMORY_BASIC_INFORMATION mbi;
    mbi.RegionSize = 0x1000;//

    VirtualQueryEx(hProc, (LPCVOID)begin, &mbi, sizeof(mbi));

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQueryEx(hProc, curr, &mbi, sizeof(mbi))) continue;
        if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

        delete[] buffer;
        buffer = new char[mbi.RegionSize];

        if (VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
        {
            ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
            VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

            char* internalAddr = ScanBasic(pattern, mask, buffer, (intptr_t)bytesRead);

            if (internalAddr != nullptr)
            {
                match = curr + (internalAddr - buffer);
                break;
            }
        }
    }
    delete[] buffer;
    return match;
}

char* Scan::ScanModEx(char* pattern, char* mask, MODULEENTRY32& modEntry, HANDLE hProc)
{
    return Scan::ScanEx(pattern, mask, (char*)modEntry.modBaseAddr, modEntry.modBaseSize, hProc);
}

void Scan::Parse(const char* combo, char* pattern, char* mask)
{
    char lastChar = ' ';
    unsigned int j = 0;

    for (unsigned int i = 0; i < strlen(combo); i++)
    {
        if ((combo[i] == '?' || combo[i] == '*') && (lastChar != '?' && lastChar != '*'))
        {
            pattern[j] = mask[j] = '?';
            j++;
        }

        else if (isspace(lastChar))
        {
            pattern[j] = lastChar = (char)strtol(&combo[i], 0, 16);
            mask[j] = 'x';
            j++;
        }
        lastChar = combo[i];
    }
    pattern[j] = mask[j] = '\0';
}

uintptr_t Scan::PatternScan(const char* combopattern)
{
    char pattern[100]{};
    char mask[100]{};
    Scan::Parse(combopattern, pattern, mask);
    return (uintptr_t)Scan::ScanModEx(pattern, mask, modEntry, hProc);
}