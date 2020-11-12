#pragma once

//Utd = Up to date
//Strong = Held across updates

namespace Patterns
{
    const char* GameManager = "48 8B 0D ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 41 BB"; //Utd *Strong*
    const char* ProfileManager = "48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 45 31 E4"; //Utd *strong*
    const char* RoundManager = "48 8B 05 ? ? ? ? 83 B8 ? ? ? ? ? 0F 95 C1"; //Utd *Strong*
    const char* GlowManager = "48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 89 F2 E8 ? ? ? ? 48 85 C0 74 ?"; //Utd *Strong*
    const char* NetworkManager = "8B 34 25 ? ? ? ? 89 F0 48 83 C4 20"; //Broken
    const char* FovManager = "48 8B 0D ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 0F 2E 35 ? ? ? ? F3 0F 10 70 ? 76 ? F3 0F 5C FE"; //Utd *Strong*
    const char* UnlockAll = "34 01 41 88 46 51"; //Utd *Strong*
    const char* PingThroughWalls = "80 F1 01 88 0C"; //Utd *Strong*
    const char* RunAndShoot1 = "80 B9 ? ? ? ? ? 74 15 E8"; //Utd *Strong*
    const char* RunAndShoot2 = "80 B9 ? ? ? ? ? 0F 84 ? ? ? ? 48 89 F1 31"; //Utd *Strong*
    const char* SpottedEsp = "80 BE ? ? ? ? ? 0F 85 ? ? ? ? EB 83"; //Utd
    const char* VtMarker = "48 8D 05 ? ? ? ? 48 89 01 48 8D 05 ? ? ? ? 48 89 41 30 48 8B 0D ? ? ? ?"; //Utd
    const char* Recoil = "80 B8 ? ? ? ? ? 66 0F EF C9"; //Utd *Strong*
    const char* Silent = "0F 28 97 ? ? ? ? 0F 28 87"; //Utd *Strong*
    const char* SpoofSpectate = "48 8B 05 ? ? ? ? 80 78 5D"; //Utd *Strong*
    const char* Thickness = "48 8B 05 ?? ?? ?? ?? C6 40 50"; //Utd
}
