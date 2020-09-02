#pragma once

#include <Windows.h>
#include <TlHelp32.h>

//All functions are from Guided Hacking
class Scan
{
public:
	Scan();
	Scan(HANDLE hProc, MODULEENTRY32 modEntry);
	uintptr_t PatternScan(const char* combopattern);

private:
	HANDLE hProc = 0;
	MODULEENTRY32 modEntry = { 0 };

	char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
	char* ScanEx(char* pattern, char* mask, char* begin, intptr_t size, HANDLE hProc);
	char* ScanModEx(char* pattern, char* mask, MODULEENTRY32& modEntry, HANDLE hProc);
	void Parse(const char* combo, char* pattern, char* mask);
};

