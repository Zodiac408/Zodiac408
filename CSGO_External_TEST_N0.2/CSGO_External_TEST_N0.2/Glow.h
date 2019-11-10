#pragma once
#include<windows.h>
#include"offsets.h"
#include"playerinfo.h"
#include"Memory.h"
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

struct var
{
	DWORD  glowObject;
	int glowIndx;
}Gvar;

struct ClrRender
{
	BYTE red, green, blue;
};

struct Bright
{
	ClrRender clrEnemy;
	ClrRender clrTeam;
}Br;

struct GlowStruct
{
	BYTE base[4];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buffer[16];
	bool renderWhenOccluded;
	bool renderWhenUnOccluded;
	bool fullBloom;
	BYTE buffer1[5];
	int glowStyle;
};

GlowStruct SetGlowColor(GlowStruct Glow, DWORD entity)
{
	Einfo.IsDefusing =	mem.rpm<bool>(entity + m_bIsDefusing);
	if (Einfo.IsDefusing == true)
	{
		Glow.red = 1.0f;
		Glow.green = 1.0f;
		Glow.blue = 1.0f;
	}
	else
	{
		Einfo.Health = mem.rpm<int>(entity + m_iHealth);
		Glow.red = Einfo.Health * -0.01 + 1;
		Glow.green = Einfo.Health * 0.01;
		Glow.glowStyle = 0;
	}
	
	Glow.alpha = 0.8f;//2 all white//normal = 1
	Glow.renderWhenOccluded = true;
	Glow.renderWhenUnOccluded = false;
	return Glow;
}

void SetTeamGlow(DWORD entity, int glowIndex)
{
	GlowStruct TGlow;
	TGlow = mem.rpm<GlowStruct>(Gvar.glowObject + (glowIndex * 0x38));

	TGlow.blue = 1.0f;
	TGlow.alpha = 1.0f;
	TGlow.renderWhenOccluded = true;
	TGlow.renderWhenUnOccluded = false;
	mem.wpm<GlowStruct>(Gvar.glowObject + (glowIndex * 0x38), TGlow);
}

void SetEnemyGlow(DWORD entity, int glowIndex)
{
	GlowStruct EGlow;
	EGlow = mem.rpm<GlowStruct>(Gvar.glowObject + (glowIndex * 0x38));
	EGlow = SetGlowColor(EGlow, entity);
	mem.wpm<GlowStruct>(Gvar.glowObject + (glowIndex * 0x38), EGlow);
}

void MutiColourForBoth(int LocalTeam,  int EntityTeam)
{
	Gvar.glowObject =mem.rpm<DWORD>(ce.clientM + dwGlowObjectManager);
	
	Gvar.glowIndx = mem.rpm<int>(Einfo.Entity + m_iGlowIndex);

	if (LocalTeam == EntityTeam)
		{
		mem.wpm<ClrRender>(Einfo.Entity + m_clrRender, Br.clrTeam);
			SetTeamGlow(Einfo.Entity, Gvar.glowIndx);
		}
		else
		{
			mem.wpm<ClrRender>(Einfo.Entity + m_clrRender,Br.clrEnemy);
			SetEnemyGlow(Einfo.Entity,Gvar.glowIndx);
		}
}

void SetBrightness()
{
	Br.clrTeam.red = 0;
	Br.clrTeam.blue = 255;
	Br.clrTeam.green = 0;

	Br.clrEnemy.red = 255;
	Br.clrEnemy.blue = 0;
	Br.clrEnemy.green = 0;

	float brightness = 1.0f;

	int ptr = mem.rpm<int>(ce.engineM + model_ambient_min);
	int xorptr = *(int*)&brightness ^ ptr;
	mem.wpm<int>(ce.engineM + model_ambient_min, xorptr);
}
