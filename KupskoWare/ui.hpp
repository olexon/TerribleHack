#pragma once

#define WINDOW_NAME "Terrible Overlay"

#ifdef _DEBUG
#define MENU_NAME "[DEBUG] - TerribleHack"
#else
#define MENU_NAME "[RELEASE] - TerribleHack"
#endif

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h> //include before glfw
#include <GLFW/glfw3.h>

#include "hacks/hacks.hpp"

struct MenuVars
{
	bool bMenuOpen = false;
};

struct Screen
{
	unsigned short width;
	unsigned short height;
};

namespace ui 
{
	void run();
}