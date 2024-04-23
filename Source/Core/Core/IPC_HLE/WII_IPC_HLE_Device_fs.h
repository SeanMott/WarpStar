// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>

#include "Common/CommonTypes.h"
#include "Core/IPC_HLE/WII_IPC_HLE.h"
#include "Core/IPC_HLE/WII_IPC_HLE_Device.h"

class PointerWrap;

struct NANDStat
{
	u32 BlockSize;
	u32 FreeUserBlocks;
	u32 UsedUserBlocks;
	u32 FreeSysBlocks;
	u32 UsedSysBlocks;
	u32 Free_INodes;
	u32 Used_Inodes;
};

class CWII_IPC_HLE_Device_fs : public IWII_IPC_HLE_Device
{
public:
	CWII_IPC_HLE_Device_fs(u32 _DeviceID, const std::string& _rDeviceName);
	virtual ~CWII_IPC_HLE_Device_fs();

	void DoState(PointerWrap& p) override;

	IPCCommandResult Open(u32 _CommandAddress, u32 _Mode) override;

	IPCCommandResult IOCtl(u32 _CommandAddress) override;
	IPCCommandResult IOCtlV(u32 _CommandAddress) override;

private:
	enum
	{
		IOCTL_GET_STATS = 0x02,
		IOCTL_CREATE_DIR = 0x03,
		IOCTLV_READ_DIR = 0x04,
		IOCTL_SET_ATTR = 0x05,
		IOCTL_GET_ATTR = 0x06,
		IOCTL_DELETE_FILE = 0x07,
		IOCTL_RENAME_FILE = 0x08,
		IOCTL_CREATE_FILE = 0x09,
		IOCTLV_GETUSAGE = 0x0C,
		IOCTL_SHUTDOWN = 0x0D
	};

	IPCCommandResult GetFSReply() const;
	s32 ExecuteCommand(u32 Parameter, u32 _BufferIn, u32 _BufferInSize, u32 _BufferOut,
		u32 _BufferOutSize);
};
