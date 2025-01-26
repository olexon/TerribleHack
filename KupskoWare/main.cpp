#include <iostream>
#include <thread>

#include "ui.hpp"
#include "hacks/hacks.hpp"

int main()
{
	std::thread overlay(ui::run);
	std::unique_ptr<std::thread> game = nullptr;

	std::printf("menu key: insert\n");
	std::printf("looking for games\n");

	while (true)
	{
		if (!memory.iPid)
		{
			if (gta::Init("ViceCity.exe") || gta::Init("LibertyCity.exe") || gta::Init("SanAndreas.exe"))
			{
				game = std::make_unique<std::thread>(gta::MainLoop);
			}
		}
		else
		{
			if (!memory.IsProcessAlive())
			{
				if (game)
				{
					game->detach();
					game.reset();
				}

				std::printf("process died, looking for games\n");
			}
		}
		Sleep(1000);
	};

	overlay.detach();
}