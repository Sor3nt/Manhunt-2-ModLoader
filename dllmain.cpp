/*
	ModLoader by Sor3nt - DIXMOR-HOSPITAL.COM
*/
#include <string>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <algorithm>
#include "calling.h"
#include "MemoryMgr.h"
#include <filesystem>;
namespace fs = std::experimental::filesystem;

std::string activeMod = "";

void __fastcall SelectMod() {
	std::string path = "mods/";

	int index = 1;

	
	std::cout << "                         www.dixmor-hospital.com presents" << std::endl;
	std::cout << "                                 _                    _     ____  " << std::endl;
	std::cout << "            /\\/\\    __ _  _ __  | |__   _   _  _ __  | |_  |___ \\ " << std::endl;
	std::cout << "           /    \\  / _` || '_ \\ | '_ \\ | | | || '_ \\ | __|   __) |" << std::endl;
	std::cout << "          / /\\/\\ \\| (_| || | | || | | || |_| || | | || |_   / __/ " << std::endl;
	std::cout << "          \\/    \\/ \\__,_||_| |_||_| |_| \\__,_||_| |_| \\__| |_____|" << std::endl;

	std::cout << "" << std::endl;
	std::cout << "   _.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._.~\"~._" << std::endl;
	std::cout << "                           _    __                     _             " << std::endl;
	std::cout << "         /\\/\\    ___    __| |  / /    ___    __ _   __| |  ___  _ __ " << std::endl;
	std::cout << "        /    \\  / _ \\  / _` | / /    / _ \\  / _` | / _` | / _ \\| '__|" << std::endl;
	std::cout << "       / /\\/\\ \\| (_) || (_| |/ /___ | (_) || (_| || (_| ||  __/| |   " << std::endl;
	std::cout << "       \\/    \\/ \\___/  \\__,_|\\____/  \\___/  \\__,_| \\__,_| \\___||_| by Sor3nt" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;


	std::cout << "Please select a Mod" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "[0] Regular game" << std::endl;
	for (const auto& entry : fs::directory_iterator(path)) {
		std::cout << "[" << index << "] " << entry.path().filename().string() << std::endl;
		index++;
	}

	if (index == 1) {

		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "No Mods found! Please place the mods inside \"mods/\" folder." << std::endl;
		std::cout << "" << std::endl;
		return;

	}

	index--;

	int selectedMod = -1;

	do {
		std::cout << "" << std::endl;
		std::cout << "Load mod id: " << std::endl;
		std::cin >> selectedMod;
	} while (selectedMod < 0 || selectedMod > index);


	index = 1;

	for (const auto& entry2 : fs::directory_iterator(path)) {
		if (index == selectedMod) activeMod = entry2.path().filename().string();
		index++;
	}
}

int __cdecl WrapReadBinary(char* filename) {

	if (activeMod == "") {
		return ((int(__cdecl*)(char*))0x53BCC0)(filename);
	}
	
	std::string modFilename = filename;
	
	std::string modFile = "mods/";
	modFile.append(activeMod.c_str());
	modFile.append("/");
	modFile.append(modFilename);


	// is the wanted file in our mod folder ?
	std::ifstream f(modFile.c_str());
	if (f.good()) {

		//copy the string to char*
		filename = new char[modFile.length() + 1];
		strcpy(filename, modFile.c_str());;
	}
	
	return ((int(__cdecl*)(char*))0x53BCC0)(filename);
}

FILE __cdecl Wrap2ReadBinary(char* filename, char* mode) {

	if (activeMod == "") {
		return ((FILE(__cdecl*)(char*, char*, int))0x61B338)(filename, mode, 64);
	}

	std::string modFilename = filename;

	std::string modFile = "mods/";
	modFile.append(activeMod.c_str());
	modFile.append("/");
	modFile.append(modFilename);


	// is the wanted file in our mod folder ?
	std::ifstream f(modFile.c_str());
	if (f.good()) {

		//copy the string to char*
		filename = new char[modFile.length() + 1];
		strcpy(filename, modFile.c_str());;
	}

	return ((FILE(__cdecl*)(char*, char*, int))0x61B338)(filename, mode, 64);
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		SelectMod();

		if (activeMod == "") {
			std::cout << "Boot regular game." << std::endl;
		}
		else {
			std::cout << "Boot Mod: " << activeMod << std::endl;
		}

		// Hook another readBinary call
		Memory::VP::InjectHook(0x57B2E5, Wrap2ReadBinary, PATCH_CALL);

		// Hook the readBinary call
		Memory::VP::InjectHook(0x418A1E, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4B0842, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4C3A7C, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4C7F68, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4C8D87, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CCD10, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CD186, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CD245, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CFEB7, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4E9029, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4EBB04, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x53BD0B, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x53CC17, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x53EA07, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x56AEE9, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x56E550, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x583EC4, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x586249, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x5BC856, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x5BC86B, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x5DEA76, WrapReadBinary, PATCH_CALL);


	}
}


