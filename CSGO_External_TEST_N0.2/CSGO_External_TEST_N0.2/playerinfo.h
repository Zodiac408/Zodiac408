#pragma once
#include<windows.h>
#include"Math.h"


struct ClientEngine
{
	DWORD clientM;
	DWORD engineM;
}ce;

struct LocalPlayer
{
												//Type	Int
	//A
	int ArmorValue;

	//C
	int CrosshairID;

	//F
	int Fov;
	int Flags;
	int FlashDuration;

	//H
	int Health;

	//T
	int TeamID;
	//N
	int Nohands;
	
	//S
	
											//Type Float
	//F
	float Fired;															//read as int           m_iShotsFired
	float speed;

	   										//Type Bool
	//B
	bool BDormant;

	//H
	bool HasHelmet;
	bool HasDefuser;
		
	//I
	bool IsAlive;
	bool IsScoped;
	bool InReload;
	bool IsSpotted;
	bool IsDefusing;
	bool Is_c4_owner;

	//L
	DWORD LocalPlayer;
	
											//Type Vector2
	//A
	Vector2 AimPunchAngle;

	//C
	Vector2 ClientState_ViewAngles;
	Vector2 NewViewAngles;
	Vector2 OldAimPunch;
	

											//Type Vector3
	//P
	Vector3 Pos;

}Linfo;


struct Entity
{
	//DWORD
	DWORD Entity;
											//Type Int
	//A
	int ArmorValue;

	//H
	int Health;

	//T
	int TeamID;
	
	
											//Type Bool

	//B
	bool BDormant;
	bool BombPlanted;
	
	//H
	bool HasDefuser;
	bool HasHelmet;

	//I
	bool IsAlive;
	bool IsScoped;
	bool InReload;
	bool IsSpotted;
	bool IsDefusing;
	bool Is_c4_owner;
	

											//Type Vector 2
	//A
	Vector2 aimPunchAngle;

	//C
	Vector2 ClientState_ViewAngles;
											//Type Vector 3
	//P
	Vector3 Pos;


}Einfo;


struct ClientState
{
	DWORD clientState;
	Vector2 ViewAngles; // clientstate + this

}clientS;
struct misc
{
	bool couldhop;
	bool BombPlanted;
}Misc;