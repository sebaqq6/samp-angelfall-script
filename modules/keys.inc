#define HOLDING(%0) ((newkeys & (%0)) == (%0))
#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define PRESSING(%0,%1) (%0 & (%1))
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(!gracz[playerid][loggedin]) return 1;
	FISHSYS_OnPlayerKeyStateChange(playerid, newkeys);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	if(IsPlayerInBoisko(playerid)) football_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	if(IsPlayerInGym(playerid)) gym_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	if(PRESSED(KEY_YES))//otwieranie eq
	{
		ShowYMenu(playerid);
	}
	else if(PRESSED(KEY_NO))//podnoszenie przedmiotów
	{
		PickItemForPlayer(playerid);
	}
	else if(PRESSED(KEY_CTRL_BACK))
	{
		MagazynShow(playerid);
		ApartamentEnter(playerid);
		market_Enter(playerid);
		//Key_QuestActor(playerid);
	}
	else if(PRESSED(128))//prawy przycisk myszy
	{
		if(gracz[playerid][actual_weapon] && !IsPlayerInAnyVehicle(playerid))
		{
			if(!ammo[playerid][gracz[playerid][actual_weapon]] || !w_cdn[playerid][gracz[playerid][actual_weapon]] || gracz[playerid][in_krypta])
			{
				if(!w_cdn[playerid][gracz[playerid][actual_weapon]])  LeftNotifyShow(playerid, "error", "Bron jest ~r~uszkodzona~w~.", LN_RED);
				if(!ammo[playerid][gracz[playerid][actual_weapon]] && gracz[playerid][actual_weapon] > 15)  LeftNotifyShow(playerid, "error", "~r~Brak amunicji~w~.", LN_RED);
				SetPlayerArmedWeapon(playerid, 0);
			}
		}
	}
	else if(PRESSED(KEY_JUMP))
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			if(gracz[playerid][MapperLvl] >= 2) return 1;
			if(gettime() - GetPVarInt(playerid, "Podskoczyl") < 1) return 1;
			if(gracz[playerid][kondycja] >= 5)
			{
				SetPVarInt(playerid, "Podskoczyl", gettime());
				gracz[playerid][kondycja] -= 5;
				Process_Kondycja(playerid);
			}
			else
			{
				SetPVarInt(playerid, "Podskoczyl", gettime());
				gracz[playerid][kondycja] = 0;
				Process_Kondycja(playerid);
			}
		}
	}
	else if(PRESSED(KEY_SECONDARY_ATTACK))
	{
		if(!_PlayerTeleporting[playerid] && !gracz[playerid][first_spawn] && !gracz[playerid][BWTime]) EnterDoor(playerid);
	}
	return 1;
}
