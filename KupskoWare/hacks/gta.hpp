#pragma once
#include <map>

#include "hacks.hpp"

uintptr_t GTAmodule;
GTAsettings settings;

/*
	todo: remake pretty much everything below to support other gta games
*/

std::map<int, int> radio_stations =
{
	{0, 10}, // off
	{1, 8}, // wave 103
	{2, 7}, // emotion 89.3
	{3, 6}, // espantoso
	{4, 5}, // vcpr
	{5, 4}, // vrock
	{6, 3}, // fever 105
	{7, 2}, // kchat
	{8, 1}, // flash fm
	{9, 0} // wildstyle
};

const char* radio_items[] =
{
	"off",
	"wave 103",
	"emotion 89.3",
	"espantoso",
	"vcpr",
	"vrock",
	"fever 105",
	"kchat",
	"flash fm",
	"wildstyle"
};

std::vector<int> weapons =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	15,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33
};

const char* slot_items[] =
{
	"unarmed",
	"melee",
	"throwables",
	"pistols",
	"shotguns",
	"sub-machine guns",
	"rifles",
	"heavy weapons",
	"sniper rifles",
	"this slot next to minigun lol"
};

const char* weapon_items[] =
{
	"none",
	"brass knuckles",
	"screwdriver",
	"golf club",
	"nightstick",
	"knife",
	"baseball bat",
	"hammer",
	"meat cleaver",
	"machete",
	"katana",
	"chainsaw",
	"grenades",
	"remote grenades",
	"molotov",
	"pistol",
	".357",
	"shotgun",
	"spas12",
	"stubby shotgun",
	"tec9",
	"uz-1",
	"mac",
	"mp",
	"m4",
	"kruger",
	"sniper rifle",
	".308 sniper",
	"rocket launcher",
	"flame thrower",
	"m60",
	"minigun"
};