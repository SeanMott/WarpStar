#pragma once

#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

namespace Slippi {
	const uint8_t EVENT_PAYLOAD_SIZES = 0x35;
	const uint8_t EVENT_GAME_INIT = 0x36;
	const uint8_t EVENT_PRE_FRAME_UPDATE = 0x37;
	const uint8_t EVENT_POST_FRAME_UPDATE = 0x38;
	const uint8_t EVENT_GAME_END = 0x39;

	const uint8_t GAME_INFO_HEADER_SIZE = 78;
	const uint8_t UCF_TOGGLE_SIZE = 8;
	const int32_t GAME_FIRST_FRAME = -123;
	const uint8_t GAME_SHEIK_INTERNAL_ID = 0x7;
	const uint8_t GAME_SHEIK_EXTERNAL_ID = 0x13;

	static uint8_t* data;

	typedef struct {
		// Every player update has its own rng seed because it might change in between players
		uint32_t randomSeed;

		uint8_t internalCharacterId;
		uint16_t animation;
		float locationX;
		float locationY;
		float facingDirection;
		uint8_t stocks;
		float percent;
		float shieldSize;
		uint8_t lastMoveHitId;
		uint8_t comboCount;
		uint8_t lastHitBy;

		//Controller information
		float joystickX;
		float joystickY;
		float cstickX;
		float cstickY;
		float trigger;
		uint32_t buttons; //This will include multiple "buttons" pressed on special buttons. For example I think pressing z sets 3 bits

		//This is extra controller information
		uint16_t physicalButtons; //A better representation of what a player is actually pressing
		float lTrigger;
		float rTrigger;

		uint8_t joystickXRaw;
	} PlayerFrameData;

	typedef struct {
		int32_t frame;
		std::unordered_map<uint8_t, PlayerFrameData> players;
		std::unordered_map<uint8_t, PlayerFrameData> followers;
	} FrameData;

	typedef struct {
		//Static data
		uint8_t characterId;
		uint8_t characterColor;
		uint8_t playerType;
		uint8_t controllerPort;
	} PlayerSettings;

	typedef struct {
		uint16_t stage; //Stage ID
		uint32_t randomSeed;
		std::array<uint32_t, GAME_INFO_HEADER_SIZE> header;
		std::array<uint32_t, UCF_TOGGLE_SIZE> ucfToggles;
		std::unordered_map<uint8_t, PlayerSettings> players;
	} GameSettings;

	typedef struct {
		std::array<uint8_t, 4> version;
		std::unordered_map<int32_t, FrameData> frameData;
		GameSettings settings;

		int32_t frameCount; // Current/last frame count

		//From OnGameEnd event
		uint8_t winCondition;
	} Game;

	static std::unordered_map<uint8_t, uint32_t> asmEvents = {
		{ EVENT_GAME_INIT, 320 },
		{ EVENT_PRE_FRAME_UPDATE, 58 },
		{ EVENT_POST_FRAME_UPDATE, 33 },
		{ EVENT_GAME_END, 1 }
	};

	class SlippiGame
	{
	public:
		static SlippiGame* FromFile(std::string path);
		bool DoesFrameExist(int32_t frame);
		FrameData* GetFrame(int32_t frame);
		GameSettings* GetSettings();
		bool DoesPlayerExist(int8_t port);
	private:
		Game* game;

		static SlippiGame* processFile(uint8_t* fileContents, uint64_t fileSize);
	};
}
