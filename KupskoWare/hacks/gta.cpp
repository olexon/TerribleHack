#include <iostream>
#include "gta.hpp"

bool gta::Init(const char* process_name)
{
	memory.GetProcessHandle(process_name);
	GTAmodule = NULL;

	if (memory.iPid != NULL)
	{
		std::printf("looking for modules\n");

		do
		{
			GTAmodule = memory.GetModuleAddress(process_name);
			Sleep(10);
		} while (!GTAmodule);

		std::printf("loaded gta [%s]\n", memory.szProcessName);

		GTAstatus = true;
		return true;
	}

	GTAstatus = false;
	return false;
}

void gta::MainLoop()
{
	GtaOffsets offsets(memory.szProcessName);

	while (GTAmodule != NULL)
	{
		uintptr_t active_entity = memory.Read<uintptr_t>(GTAmodule + offsets.active_entity); //idek how to call this but shit changes when u enter a car for example
		uintptr_t local_player = memory.Read<uintptr_t>(memory.Read<uintptr_t>(GTAmodule + offsets.local_player));

		std::vector<uintptr_t> position = 
		{ 
			active_entity + offsets.player_x,
			active_entity + offsets.player_y,
			active_entity + offsets.player_z
		};

		bool in_car = active_entity != local_player;

		if (active_entity)
		{
			if (in_car) //vehicle stuff
			{
				if (settings.bImmortalEngine)
				{
					memory.Write<float>(active_entity + offsets.engine_health, 1337.f);
				}		

				if (settings.bDeloreanMode)
				{
					memory.Write<byte>(active_entity + offsets.car_idk_delorean, 255);
				}

				if (settings.bForceStation)
				{
					int current_track = memory.Read<int>(GTAmodule + offsets.play_track);

					//tommy TOMMY WHY YOU COMING BACK??!??!?!?! [1025]

					if (current_track <= 10 && current_track != radio_stations[settings.iStationSelected])
					{
						memory.Write<int>(GTAmodule + offsets.play_track, radio_stations[settings.iStationSelected]);
					}
				}
			}

			if (settings.bAddMoney)
			{
				memory.Write<int>(GTAmodule + offsets.money, settings.iMoneyValue);
			}

			if (settings.bGod)
			{
				memory.Write<float>(local_player + offsets.player_health, 1337.f);
				memory.Write<float>(local_player + offsets.player_armor, 1337.f);
			}

			if (settings.bSetTime1 || settings.bSetTime2)
			{
				memory.Write<byte>(GTAmodule + offsets.time, settings.iTime[1]);
				memory.Write<byte>(GTAmodule + offsets.time + 0x1, settings.iTime[0]);
			}

			for (int i = 0; i < 10; i++) //loop through weapon slots
			{
				uintptr_t weapon = local_player + (offsets.player_weapon + i * 0x20); //slots are offset from eachother by 0x20

				//	0x8 = mag capacity offset
				//	0xC = ammo offset

				if (settings.bSetWeapon)
				{
					if (i == settings.iSlotSelected && weapons[settings.iWeaponSelected] != memory.Read<int>(weapon))
					{
						memory.Write<int>(weapon, weapons[settings.iWeaponSelected]); //set weapon id

						memory.Write<int>(weapon + 0x8, 1337); // mag capacity
						memory.Write<int>(weapon + 0xC, 2674); // ammo

						memory.Write<int>(local_player + offsets.player_active_slot, settings.iSlotSelected); //set as a selected slot
					}
				}

				if (settings.bUnlimitedAmmo)
				{
					memory.Write<int>(weapon + 0x8, 1337);
					memory.Write<int>(weapon + 0xC, 2674);
				}
			}

			static float fPos[3] = { 0.f, 0.f, 0.f };
			static bool bNoclipping = false;
			if (settings.bNoclip)
			{
				static const float step = 1.f;
					
				if (!bNoclipping)
				{
					for (short i = 0; i < 3; i++)
					{
						fPos[i] = memory.Read<float>(position[i]);
					}

					bNoclipping = true;
				}

				//up - down
				if (GetAsyncKeyState(VK_SPACE))
					fPos[2] += step;

				if (GetAsyncKeyState(VK_SHIFT))
					fPos[2] -= step;

				//forward - backward
				if (GetAsyncKeyState(0x57)) // W
					fPos[1] += step;

				if (GetAsyncKeyState(0x53)) // S
					fPos[1] -= step;

				//left - right
				if (GetAsyncKeyState(0x44)) // D
					fPos[0] += step;

				if (GetAsyncKeyState(0x41)) // A
					fPos[0] -= step;

				for (short i = 0; i < 3; i++)
				{
					memory.Write<float>(position[i], fPos[i]);
				}

				memory.Write<float>(local_player + offsets.player_rotation, 0.f); //force model to the north
			}
			else
			{
				bNoclipping = false;
				for (short i = 0; i < 3; i++)
				{
					fPos[i] = 0.f;
				}
			}
		}

		Sleep(10);
	}
}

void gta::Ui()
{
	if (ImGui::BeginTabBar("#main"))
	{
		if (ImGui::BeginTabItem("Player")) //player shit
		{
			ImGui::Checkbox("Unlimited Ammo", &settings.bUnlimitedAmmo);
			ImGui::Checkbox("Infinite Health", &settings.bGod);

			ImGui::Separator();

			ImGui::Spacing();
			ImGui::Text("You can click the slider while prssing ctrl");
			ImGui::Text("to enter custom values");
			ImGui::Spacing();

			ImGui::SliderInt("Money", &settings.iMoneyValue, 0, 10000000);
			settings.bAddMoney = ImGui::Button("Set Money", ImVec2(370, 30));

			ImGui::Separator();

			ImGui::Spacing();
			ImGui::Text("Will crash most of the time... rip");
			ImGui::Spacing();

			ImGui::Combo("Slot", &settings.iSlotSelected, slot_items, sizeof(slot_items) / sizeof(slot_items[0]));
			ImGui::Combo("Weapon", &settings.iWeaponSelected, weapon_items, sizeof(weapon_items) / sizeof(weapon_items[0]));
			settings.bSetWeapon = ImGui::Button("Set Weapon", ImVec2(370, 30));

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Vehicle")) //vehicle shit
		{
			ImGui::Checkbox("Immortal Engine", &settings.bImmortalEngine);
			ImGui::Checkbox("Delorean Mode", &settings.bDeloreanMode);

			ImGui::Separator();

			ImGui::Combo("Radio Station", &settings.iStationSelected, radio_items, sizeof(radio_items) / sizeof(radio_items[0]));
			ImGui::Checkbox("Force Station", &settings.bForceStation);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Misc")) //misc shit
		{
			ImGui::Text("WASD + SPACE & SHIFT");
			ImGui::Text("Controls are north relative");
			ImGui::Spacing();

			ImGui::Checkbox("Noclip", &settings.bNoclip);	
			
			ImGui::Separator();

			ImGui::SliderInt("Hour", &settings.iTime[0], 0, 23);
			ImGui::SliderInt("Minute", &settings.iTime[1], 0, 59);
			settings.bSetTime1 = ImGui::Button("Set Time", ImVec2(370, 30));
			ImGui::Checkbox("Lock Time", &settings.bSetTime2);

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}