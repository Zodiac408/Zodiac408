#include<iostream>
#include<windows.h>
#include"Memory.h"
#include"playerinfo.h"
#include"offsets.h"
#include"Glow.h"
#include<thread>

//void AntiFlash();
void bHoppping();
void Nohands();
void third();
void Fov();
void FakeLag();


using namespace hazedumper::netvars;
using namespace hazedumper::signatures;
using namespace std;

bool isscope()
{
	if (Linfo.IsScoped == true)
	{
		return true;
	}
	else if (Linfo.IsScoped == false)
	{
		return false;
	}
}

int main()
{
	
	SetConsoleTitle("VAC == Suck");
	system("COLOR 04");
	Attach();
	ce.clientM = getModule((char*)"client_panorama.dll");
	ce.engineM = getModule((char*)"engine.dll");
	
	//BHOP SET
	Misc.couldhop = false;
	//Set Brightness
	SetBrightness();
	   
	while (!GetAsyncKeyState(VK_F10))
	{
		
		

		//Type DWORD
		Linfo.LocalPlayer = mem.rpm<DWORD>(ce.clientM + dwLocalPlayer);
		/*DWORD clinetLocalPLayer = mem.rpm<DWORD>(ce.engineM + dwClientState_GetLocalPlayer);*/
		
		//Type Int
		/*Linfo.ArmorValue = mem.rpm<int>(Linfo.LocalPlayer + m_ArmorValue);*/
		Linfo.CrosshairID = mem.rpm<int>(Linfo.LocalPlayer + m_iCrosshairId);
		Linfo.Fov = mem.rpm<int>(Linfo.LocalPlayer + m_iFOV);

		Linfo.Flags = mem.rpm<int>(Linfo.LocalPlayer + m_fFlags);
		Linfo.Fired = mem.rpm<int>(Linfo.LocalPlayer + m_iShotsFired);
		Linfo.Health = mem.rpm<int>(Linfo.LocalPlayer + m_iHealth);
		Linfo.TeamID = mem.rpm<int>(Linfo.LocalPlayer + m_iTeamNum);
		Linfo.speed = mem.rpm<float>(Linfo.LocalPlayer + m_vecVelocity);
		Linfo.FlashDuration = mem.rpm<int>(Linfo.LocalPlayer + m_flFlashDuration);

		//Type Vector 2   
		Linfo.AimPunchAngle = mem.rpm<Vector2>(Linfo.LocalPlayer + m_aimPunchAngle);//vPunc

		////Type Vector 3 
		Linfo.Pos = mem.rpm<Vector3>(Linfo.LocalPlayer + m_vecOrigin);

		//Type  Bool 
		Linfo.BDormant = mem.rpm<bool>(Linfo.LocalPlayer + m_bDormant);
		//Linfo.HasHelmet = mem.rpm<bool>(Linfo.LocalPlayer + m_bHasHelmet);
		//Linfo.HasDefuser = mem.rpm<bool>(Linfo.LocalPlayer + m_bHasDefuser);
		Linfo.InReload = mem.rpm<bool>(Linfo.LocalPlayer + m_bInReload);
		//Linfo.Is_c4_owner = mem.rpm<bool>(Linfo.LocalPlayer + is_c4_owner);
		Linfo.IsScoped = mem.rpm<bool>(Linfo.LocalPlayer + m_bIsScoped);

		//Entity loop

	
		for (int i = 1; i < 64; i++)
		{
			Einfo.Entity = mem.rpm<DWORD>(ce.clientM + dwEntityList +  i * 0x10);
			
			//if Have Entity

			if (Einfo.Entity != NULL)
			{

				Einfo.Health = mem.rpm<int>(Einfo.Entity + m_iHealth);
				Einfo.TeamID = mem.rpm<int>(Einfo.Entity + m_iTeamNum);
				//Cheat Area!

				//Cheat 2D Rader
				mem.wpm<bool>(Einfo.Entity + m_bSpotted, true);
				
				
				//Glow
				if (GetKeyState(VK_NUMPAD0) & 1)
				{
					MutiColourForBoth(Linfo.TeamID, Einfo.TeamID);
				}
			}
		}
		
		//Cheat Area!
		bHoppping();
		Nohands();
		third();
		Fov();
		FakeLag();
		
	}
	return 0;
}



	//Cheat 
	


	
	//void AntiFlash()
	//{
	//	if (GetKeyState(VK_NUMPAD3) &1)
	//	{		
	//		{
	//			if ((Linfo.FlashDuration > 0))
	//			{
	//				mem.wpm<int>(Linfo.LocalPlayer + m_flFlashDuration, 0);
	//				std::cout << "Anti-Flash" << std::endl;
	//			}
	//		}
	//
	//	}
	//}

	void bHoppping()
	{
		if (GetKeyState(VK_NUMPAD1) & 1)
		{
			Misc.couldhop = true;
			
		}
		else 
		{
			Misc.couldhop = false;
		}

		if (GetAsyncKeyState(VK_SPACE) && Linfo.Flags & (1 << 0) && Misc.couldhop == true)
		{
			mem.wpm<BYTE>(ce.clientM + dwForceJump, 6);
		}
	}

void Nohands()
{
		if (GetKeyState(VK_NUMPAD2) & 1)
		{
			mem.wpm<int>(Linfo.LocalPlayer + n_ModelIndex, 0);
		}
		
}

void third()
{
	if (GetKeyState(VK_NUMPAD3) & 1)
	{
		mem.wpm<int>(Linfo.LocalPlayer + m_iObserverMode, 1);
	}
	else
	{
		mem.wpm<int>(Linfo.LocalPlayer + m_iObserverMode, 0);
		
	}
}

void Fov()
{
	if (GetKeyState(VK_NUMPAD4))
	{
		if (Linfo.LocalPlayer + m_iFOV != 110)
		{
			mem.wpm<int>(Linfo.LocalPlayer + m_iFOV, 110);
		}
	}
	else if (GetKeyState(VK_NUMPAD5))
	{
		if (Linfo.LocalPlayer + m_iFOV != 40)
		{
			mem.wpm<int>(Linfo.LocalPlayer + m_iFOV, 40);
		}
	}
	else if (GetKeyState(VK_NUMPAD6))
	{
		if (Linfo.LocalPlayer + m_iFOV != 10)
		{
			mem.wpm<int>(Linfo.LocalPlayer + m_iFOV, 10);
		}
	}
	else if (Linfo.IsScoped == true)
	{
		if (Linfo.LocalPlayer + m_iFOV != 90)
		{
			mem.wpm<int>(Linfo.LocalPlayer + m_iFOV, 90);
		}
	}
	else
	{
	   if (Linfo.LocalPlayer + m_iFOV != 90)
		{
		  mem.wpm<int>(Linfo.LocalPlayer + m_iFOV, 90);
		}
	}
	
}

void FakeLag()
{
	long lag = 15.625 * 9;
	byte sendpacket = mem.rpm<byte>(ce.engineM + dwbSendPackets);
	if (GetAsyncKeyState(VK_XBUTTON1))
	{
		if (sendpacket != 0)
		{

			mem.wpm<byte>(ce.engineM + dwbSendPackets, 0);
			/*	std::this_thread::sleep_for(std::chrono::milliseconds(lag));*/
			Sleep(lag);
			mem.wpm<byte>(ce.engineM + dwbSendPackets, 1);
			/*std::this_thread::sleep_for(std::chrono::milliseconds(lag));*/
			Sleep(lag);
		}
	}

	Sleep(0);

}

