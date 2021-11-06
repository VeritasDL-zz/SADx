#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <IniFile.hpp>
extern "C"
{
	facewk* face = 0;
	bool SonicSadEnabled = true;
	bool TailsSadEnabled = true;
	bool KnucklesSadEnabled = true;
	bool AmySadEnabled = true;
	bool P2SonicSadEnabled = true;
	bool P2TailsSadEnabled = true;
	bool P2KnucklesSadEnabled = true;
	bool P2AmySadEnabled = true;
	void fixedFace(int old, int __new, int frame, int nbFrame);
	void fixedFaceP2(int old, int __new, int frame, int nbFrame);
	playerwk* playerwkptr = 0;
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		SonicSadEnabled = config->getBool("General", "SonicSadEnabled", true);
		TailsSadEnabled = config->getBool("General", "TailsSadEnabled", true);
		KnucklesSadEnabled = config->getBool("General", "KnucklesSadEnabled", true);
		AmySadEnabled = config->getBool("General", "AmySadEnabled", true);
		P2SonicSadEnabled = config->getBool("General", "P2SonicSadEnabled", true);
		P2TailsSadEnabled = config->getBool("General", "P2TailsSadEnabled", true);
		P2KnucklesSadEnabled = config->getBool("General", "P2KnucklesSadEnabled", true);
		P2AmySadEnabled = config->getBool("General", "P2AmySadEnabled", true);
	}
	__declspec(dllexport) void __cdecl OnFrame()
	{
		// Executed every running frame of SADX
		if (PlayerPtrs[0] != nullptr) 
		{
			if (SonicSadEnabled)
			{
				if (GetCharacterID(0) == Characters_Sonic)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[0];
					fixedFace(12, 1, 1, 100);//Sonic Sad face
				}
			}
			if (TailsSadEnabled)
			{
				if (GetCharacterID(0) == Characters_Tails)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[0];
					fixedFace(12, 1, 1, 100); //tails sad face?
				}
			}
			if (KnucklesSadEnabled)
			{
				if (GetCharacterID(0) == Characters_Knuckles)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[0];
					fixedFace(12, 1, 1, 100); //knuckles sad face?
				}
			}
			if (AmySadEnabled)
			{
				if (GetCharacterID(0) == Characters_Amy)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[0];
					fixedFace(12, 1, 1, 100); //amy sad face?
				}
			}
		}
		if (PlayerPtrs[1] != nullptr)
		{
			if (P2SonicSadEnabled)
			{
				if (GetCharacterID(1) == Characters_Sonic)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[1];
					fixedFaceP2(12, 1, 1, 100);//Sonic Sad face
				}
			}
			if (P2TailsSadEnabled)
			{
				if (GetCharacterID(1) == Characters_Tails)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[1];
					fixedFaceP2(12, 1, 1, 100); //tails sad face?
				}
			}
			if (P2KnucklesSadEnabled)
			{
				if (GetCharacterID(1) == Characters_Knuckles)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[1];
					fixedFaceP2(12, 1, 1, 100); //knuckles sad face?
				}
			}
			if (P2AmySadEnabled)
			{
				if (GetCharacterID(1) == Characters_Amy)
				{
					playerwkptr = (playerwk*)CharObj2Ptrs[1];
					fixedFaceP2(12, 1, 1, 100); //amy sad face?
				}
			}
		}
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}
void fixedFace(int old, int __new, int frame, int nbFrame)
{
	task* player = (task*)PlayerPtrs[0];
	int faceaddress = (int)&player->twp->ewp->face;
	faceaddress = faceaddress + 8; //Adjust address because this is 8 bytes off
	face = (facewk*)faceaddress;
	face->old = old;
	face->__new = __new;
	face->frame = frame;
	face->nbFrame = nbFrame;
}
void fixedFaceP2(int old, int __new, int frame, int nbFrame)
{
	task* player = (task*)PlayerPtrs[1];
	int faceaddress = (int)&player->twp->ewp->face;
	faceaddress = faceaddress + 8; //Adjust address because this is 8 bytes off
	face = (facewk*)faceaddress;
	face->old = old;
	face->__new = __new;
	face->frame = frame;
	face->nbFrame = nbFrame;
}