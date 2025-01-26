#pragma once
#include "../memory.hpp"
#include "../ui.hpp"

inline bool GTAstatus = false;

struct GTAsettings
{
	bool bGod = false;
	bool bNoclip = false;
	bool bUnlimitedAmmo = false;

	bool bSetWanted1 = false;
	bool bSetWanted2 = false;
	int iWanted = 0;

	bool bSetWeapon = false;
	int iSlotSelected = 0;
	int iWeaponSelected = 0;

	bool bImmortalEngine = false;
	bool bDeloreanMode = false;

	bool bForceStation = false;
	int iStationSelected = 0;

	bool bAddMoney = false;
	int iMoneyValue = 0;

	bool bSetTime1 = false;
	bool bSetTime2 = false;
	int iTime[2] = { 0, 0 };
};

class GtaOffsets
{
public:
	//global ig
	//uintptr_t game_version = 0x3FFFE40; //char c[10]
	uintptr_t money =				0;
	uintptr_t local_player =		0;
	uintptr_t time =				0; //+0x1 for hours
	uintptr_t active_entity =		0;
	uintptr_t play_track =			0;

	//on foot
	DWORD32 player_state =			0;
	DWORD32 player_health =			0;
	DWORD32 player_armor =			0;
	DWORD32 player_weapon =			0;
	DWORD32 player_active_slot =	0;
	DWORD32 player_rotation =		0;
	DWORD32 player_x =				0;
	DWORD32 player_y =				0;
	DWORD32 player_z =				0;

	//in car
	DWORD32 engine_health =			0;
	DWORD32 engine_gear =			0; //dunno wtf this is
	DWORD32 car_horn =				0;
	DWORD32 car_wheels_shit =		0;
	DWORD32 car_idk_delorean =		0;

	GtaOffsets(const char* process_name)
	{
		if (!strcmp(process_name, "ViceCity.exe"))
		{
			this->money =				0x5247B80;
			this->local_player =		0x545DE38;
			this->time =				0x4F83DF6;
			this->active_entity =		0x4E2A4D0;
			this->play_track =			0x4E250F4;

			this->player_state =		0x394;
			this->player_health =		0x4E4;
			this->player_armor =		0x4E8;
			this->player_weapon =		0x5E8;
			this->player_active_slot =	0x8B8;
			this->player_rotation =		0x508;
			this->player_x =			0x38;
			this->player_y =			0x3C;
			this->player_z =			0x40;

			this->engine_health =		0x320;
			this->engine_gear =			0x324;
			this->car_horn =			0x36C;
			this->car_wheels_shit =		0x6C0;
			this->car_idk_delorean =	0x6E3;
		}
		else if (!strcmp(process_name, "LibertyCity.exe"))
		{
			//todo
		}
		else if (!strcmp(process_name, "SanAndreas.exe"))
		{
			//todo
		}
	}
};

namespace gta
{
	bool Init(const char* process_name);
	void MainLoop();
	void Ui();
}