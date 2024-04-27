// Copyright 2010 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <mutex>
#include <vector>

#include "Common/CommonPaths.h"
#include "Common/FileUtil.h"
#include "Common/Logging/Log.h"
#include "Common/Thread.h"

#include "Core/ConfigManager.h"
#include "Core/GeckoCode.h"
#include "Core/HW/Memmap.h"
#include "Core/NetPlayProto.h"
#include "Core/PowerPC/PowerPC.h"

#include <iostream>

namespace Gecko
{

static const u32 INSTALLER_BASE_ADDRESS = 0x80001800;
static const u32 INSTALLER_END_ADDRESS = 0x80003000;

// return true if a code exists
bool GeckoCode::Exist(u32 address, u32 data) const
{
	for (const CodeData& code : codes)
	{
		if (code.address == address && code.data == data)
			return true;
	}

	return false;
}

// return true if the code is identical
bool GeckoCode::Compare(const GeckoCode& compare) const
{
	if (codes.size() != compare.codes.size())
		return false;

	unsigned int exist = 0;

	for (const CodeData& code : codes)
	{
		if (compare.Exist(code.address, code.data))
			exist++;
	}

	return exist == codes.size();
}

static bool code_handler_installed = false;
// the currently active codes
static std::vector<GeckoCode> active_codes;
static std::mutex active_codes_lock;

//static bool IsEnabledMeleeCode(const GeckoCode& code)
//{
//    if(SConfig::GetInstance().bMeleeForceWidescreen && code.name == "Widescreen 16:9")
//        return true;
//        
//    if(NetPlay::IsNetPlayRunning() && SConfig::GetInstance().iLagReductionCode != MELEE_LAG_REDUCTION_CODE_UNSET)
//    {
//        if(SConfig::GetInstance().iLagReductionCode == MELEE_LAG_REDUCTION_CODE_NORMAL)
//            return code.name.find("Normal Lag Reduction") != std::string::npos;
//
//        if(SConfig::GetInstance().iLagReductionCode == MELEE_LAG_REDUCTION_CODE_PERFORMANCE)
//            return code.name.find("Performance Lag Reduction") != std::string::npos;
//    }
//
//    return false;
//}

//static bool IsDisabledMeleeCode(const GeckoCode& code)
//{
//    if(NetPlay::IsNetPlayRunning() && SConfig::GetInstance().iLagReductionCode != MELEE_LAG_REDUCTION_CODE_UNSET)
//    {
//        if(SConfig::GetInstance().iLagReductionCode == MELEE_LAG_REDUCTION_CODE_NORMAL)
//            return code.name.find("Performance Lag Reduction") != std::string::npos;
//
//        if(SConfig::GetInstance().iLagReductionCode == MELEE_LAG_REDUCTION_CODE_PERFORMANCE)
//            return code.name.find("Normal Lag Reduction") != std::string::npos;
//    }
//
//    return false;
//}

////have we already set the right gekko code
//static bool KAR_Netplay_AlreadyHaveTheCorrectGekkoCodeEnabled = false;
//
//#define KAR_NETPLAY_GEKKO_CODE_INJECTOR_FULL_SCREEN_NAME_ARRAY_COUNT 4
//
////the local full screen gekko code names
//static const char
//    *KAR_NETPLAY_LOCAL_FULL_SCREEN_GEKKO_CODE_NAMES[KAR_NETPLAY_GEKKO_CODE_INJECTOR_FULL_SCREEN_NAME_ARRAY_COUNT] = {
//
//};
//
////the online full screen gekko code names
//static const char
//    *KAR_NETPLAY_ONLINE_FULL_SCREEN_GEKKO_CODE_NAMES[KAR_NETPLAY_GEKKO_CODE_INJECTOR_FULL_SCREEN_NAME_ARRAY_COUNT] = {
//        "P1 Fullscreen", "P2 Fullscreen", "P3 Fullscreen", "P4 Fullscreen"};
//
////enables the desired Full screen gekko code
//static bool KAR_HackPack_ValidateGekkoCode_CorrectFullScreenCode(const GeckoCode &code)
//{
//	if (!NetPlay::IsNetPlayRunning())
//		return false;
//
//	const char *gc = code.name.c_str();
//
//	//validates that only one of the eight is active
//	for (uint32_t i = 0; i < KAR_NETPLAY_GEKKO_CODE_INJECTOR_FULL_SCREEN_NAME_ARRAY_COUNT; ++i)
//	{
//		if (!strcmp(KAR_NETPLAY_ONLINE_FULL_SCREEN_GEKKO_CODE_NAMES[i], gc))
//		{
//			//if we have already chosen the code to use, reject this one
//			if (KAR_Netplay_AlreadyHaveTheCorrectGekkoCodeEnabled)
//				return false;
//
//			//if we have no check it and enable it
//			if (i == SConfig::GetInstance().KAR_Netplay_GCPort)
//			{
//				KAR_Netplay_AlreadyHaveTheCorrectGekkoCodeEnabled = true;
//				return true;
//			}
//		}
//	}
//
//	//let it through if it isn't a full screen code
//	return true;
//}

void SetActiveCodes(const std::vector<GeckoCode>& gcodes)
{
	std::lock_guard<std::mutex> lk(active_codes_lock);

	active_codes.clear();
	//active_codes.reserve(100);

	// add enabled codes
	for (const GeckoCode& gecko_code : gcodes)
	{        
		if (gecko_code.enabled)// && KAR_HackPack_ValidateGekkoCode_CorrectFullScreenCode(gecko_code))// && !IsDisabledMeleeCode(gecko_code)) || IsEnabledMeleeCode(gecko_code))
		{
			// TODO: apply modifiers
			// TODO: don't need description or creator string, just takin up memory
			active_codes.push_back(gecko_code);
		}
	}

	GeckoCode code;

	//auto injects the ini files containing Core content

	//test with flashy menu
	CodeData codeData;

	//""
	//""
	//std::istringstream ss("C23FAC58 00000002");
	//ss >> std::hex >> codeData.address >> codeData.data;
	//code.codes.emplace_back(codeData);
	//
	//ss = std::istringstream("80060004 5400083E");
	//ss >> std::hex >> codeData.address >> codeData.data;
	//code.codes.emplace_back(codeData);
	//
	//ss = std::istringstream("90060004 00000000");
	//ss >> std::hex >> codeData.address >> codeData.data;
	//code.codes.emplace_back(codeData);
	//
	//code.enabled = true;
	//active_codes.push_back(code);

	//"C23FAC58 00000002" >> std::hex >> 
	//"80060004 5400083E"
	//"90060004 00000000"
	
	//GeckoCode::Code c = code.codes.emplace_back(GeckoCode::Code());
	//std::hex >>  .address >> code.data;
	//
	

	//if mods are enabled, load their Gekko codes as well

	code_handler_installed = false;
}

static bool InstallCodeHandler()
{
	std::string data;
	std::string _rCodeHandlerFilename = File::GetSysDirectory() + GECKO_CODE_HANDLER;
	if (!File::ReadFileToString(_rCodeHandlerFilename, data))
	{
		NOTICE_LOG(ACTIONREPLAY, "Could not enable cheats because codehandler.bin was missing.");
		return false;
	}

	u8 mmioAddr = 0xCC;

	if (SConfig::GetInstance().bWii)
	{
		mmioAddr = 0xCD;
	}

	// Install code handler
	for (size_t i = 0, e = data.length(); i < e; ++i)
		PowerPC::HostWrite_U8(data[i], (u32)(INSTALLER_BASE_ADDRESS + i));

	// Patch the code handler to the system starting up
	for (unsigned int h = 0; h < data.length(); h += 4)
	{
		// Patch MMIO address
		if (PowerPC::HostRead_U32(INSTALLER_BASE_ADDRESS + h) == (0x3f000000u | ((mmioAddr ^ 1) << 8)))
		{
			NOTICE_LOG(ACTIONREPLAY, "Patching MMIO access at %08x", INSTALLER_BASE_ADDRESS + h);
			PowerPC::HostWrite_U32(0x3f000000u | mmioAddr << 8, INSTALLER_BASE_ADDRESS + h);
		}
	}

	u32 codelist_base_address = INSTALLER_BASE_ADDRESS + (u32)data.length() - 8;
	u32 codelist_end_address = INSTALLER_END_ADDRESS;

	if(SConfig::GetInstance().m_gameType == GAMETYPE_MELEE_NTSC)
	{
		// Move Gecko code handler to the tournament mode region
		codelist_base_address = 0x801910E0;
		codelist_end_address = 0x8019AF4C;
		PowerPC::HostWrite_U32(0x3DE08019, 0x80001f58);
		PowerPC::HostWrite_U32(0x61EF10E0, 0x80001f5C);

		// Here we are replacing a line in the codehandler with a blr.
		// The reason for this is that this is the section of the codehandler
		// that attempts to read/write commands for the USB Gecko. These calls
		// were sometimes interfering with the Slippi EXI calls and causing
		// the game to loop infinitely in EXISync.
		PowerPC::HostWrite_U32(0x4E800020, 0x80001D6C);
	}

	// Write a magic value to 'gameid' (codehandleronly does not actually read this).
	PowerPC::HostWrite_U32(0xd01f1bad, INSTALLER_BASE_ADDRESS);

	// Create GCT in memory
	PowerPC::HostWrite_U32(0x00d0c0de, codelist_base_address);
	PowerPC::HostWrite_U32(0x00d0c0de, codelist_base_address + 4);

	std::lock_guard<std::mutex> lk(active_codes_lock);

	//applies the codes
	//SetActiveCodes({});

	int i = 0;

	for (const GeckoCode& active_code : active_codes)
	{
		if (active_code.enabled)// &&
		   // KAR_HackPack_ValidateGekkoCode_CorrectFullScreenCode(active_code)) // && !IsDisabledMeleeCode(active_code)) || IsEnabledMeleeCode(active_code))
		{
			for (const CodeData& code : active_code.codes)
			{
				// Make sure we have enough memory to hold the code list
				if ((codelist_base_address + 24 + i) < codelist_end_address)
				{
					PowerPC::HostWrite_U32(code.address, codelist_base_address + 8 + i);
					PowerPC::HostWrite_U32(code.data, codelist_base_address + 12 + i);
					i += 8;
				}
			}
		}
	}

	PowerPC::HostWrite_U32(0xff000000, codelist_base_address + 8 + i);
	PowerPC::HostWrite_U32(0x00000000, codelist_base_address + 12 + i);

	// Turn on codes
	PowerPC::HostWrite_U8(1, INSTALLER_BASE_ADDRESS + 7);

	// Invalidate the icache and any asm codes
	for (unsigned int j = 0; j < (INSTALLER_END_ADDRESS - INSTALLER_BASE_ADDRESS); j += 32)
	{
		PowerPC::ppcState.iCache.Invalidate(INSTALLER_BASE_ADDRESS + j);
	}
	for (unsigned int k = codelist_base_address; k < codelist_end_address; k += 32)
	{
		PowerPC::ppcState.iCache.Invalidate(k);
	}
	return true;
}

void RunCodeHandler()
{
	if (SConfig::GetInstance().bEnableCheats && active_codes.size() > 0)
	{
		if (!code_handler_installed || PowerPC::HostRead_U32(INSTALLER_BASE_ADDRESS) - 0xd01f1bad > 5)
			code_handler_installed = InstallCodeHandler();

		if (!code_handler_installed)
		{
			// A warning was already issued.
			return;
		}

		if (PC == LR)
		{
			u32 oldLR = LR;
			PowerPC::CoreMode oldMode = PowerPC::GetMode();

			PC = INSTALLER_BASE_ADDRESS + 0xA8;
			LR = 0;

			// Execute the code handler in interpreter mode to track when it exits
			PowerPC::SetMode(PowerPC::MODE_INTERPRETER);

			while (PC != 0)
				PowerPC::SingleStep();

			PowerPC::SetMode(oldMode);
			PC = LR = oldLR;
		}
	}
}

} // namespace Gecko
