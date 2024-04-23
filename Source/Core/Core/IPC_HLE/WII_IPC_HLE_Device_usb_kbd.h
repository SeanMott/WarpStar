// Copyright 2009 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <queue>
#include <string>

#include "Common/CommonTypes.h"
#include "Core/IPC_HLE/WII_IPC_HLE.h"
#include "Core/IPC_HLE/WII_IPC_HLE_Device.h"

class CWII_IPC_HLE_Device_usb_kbd : public IWII_IPC_HLE_Device
{
public:
	CWII_IPC_HLE_Device_usb_kbd(u32 _DeviceID, const std::string& _rDeviceName);
	virtual ~CWII_IPC_HLE_Device_usb_kbd();

	IPCCommandResult Open(u32 _CommandAddress, u32 _Mode) override;
	IPCCommandResult Close(u32 _CommandAddress, bool _bForce) override;
	IPCCommandResult Write(u32 _CommandAddress) override;
	IPCCommandResult IOCtl(u32 _CommandAddress) override;
	void Update() override;

private:
	enum
	{
		MSG_KBD_CONNECT = 0,
		MSG_KBD_DISCONNECT = 1,
		MSG_EVENT = 2
	};

#pragma pack(push, 1)
	struct SMessageData
	{
		u32 MsgType;
		u32 Unk1;
		u8 Modifiers;
		u8 Unk2;
		u8 PressedKeys[6];

		SMessageData(u32 msg_type, u8 modifiers, u8* pressed_keys);
	};
#pragma pack(pop)
	std::queue<SMessageData> m_MessageQueue;

	bool m_OldKeyBuffer[256];
	u8 m_OldModifiers;

	virtual bool IsKeyPressed(int _Key);

	// This stuff should probably die
	enum
	{
		KBD_LAYOUT_QWERTY = 0,
		KBD_LAYOUT_AZERTY = 1
	};
	int m_KeyboardLayout;
	static u8 m_KeyCodesQWERTY[256];
	static u8 m_KeyCodesAZERTY[256];
};
