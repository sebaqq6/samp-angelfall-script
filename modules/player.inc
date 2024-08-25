///******************************CALLBACKI GRACZA*************************************************
//**********************************************************************************************************CONNECT/DISCONNECT
public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(playerid > 49) 
	{
		Error(playerid, "Serwer jest pe³ny!");
		Kick(playerid);
		return 1;
	}
	for(new player_stats:r; r < player_stats; r++)//czyszczenie zmiennych
	{
		gracz[playerid][r] = 0;
	}
	for(new a; a < 50; a++)
	{
		ammo[playerid][a] = 0; 
		weapon[playerid][a] = false; 
		w_cdn[playerid][a] = 0; 
		w_cdn_max[playerid][a] = 0; 
	}
	for(new i; i < MAX_PLAYERS; i++)
	{
		givenDamage[playerid][i] = false;
	}
	SetPVarInt(playerid, "PProces", serwer[time_timestamp]+3);
	SetPVarInt(playerid, "GProces", serwer[time_timestamp]+3);
	FadePlayerConnect(playerid);
	Init_TextDrawPlayer(playerid);
	SetPVarInt(playerid, "RePM", -1);
	RemoveBuilding(playerid);
	ShowPanorama(playerid);
	SendClientMessage(playerid, -1, ""COL_WHITE"((Polecamy wy³¹czyæ komunikaty 'Audio Stream: [URL]' za pomoc¹ komendy: "COL_GREEN"/audiomsg"COL_WHITE"))");
	SendClientMessage(playerid, -1, "(("COL_GREEN"Dostosuj g³oœnoœæ soundtracku"COL_WHITE", wchodz¹c w ustawienia dŸwiêkowe GTA SA(g³oœnoœæ radia).))");
	PlayAudioStreamForPlayer(playerid, "http:/127.0.0.1/sound/track/logon.mp3");
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(IsPlayerNPC(playerid)) return 1;
	FadePlayerDisconnect(playerid);
	Disconnect(playerid);
	return 1;
}

stock Disconnect(playerid, reason = 1)
{
	if(!gracz[playerid][loggedin]) return 1;
	gracz[playerid][spawned] = false;
	gracz[playerid][loggedin] = false;
	OnPlayerExitVehicle(playerid, GetPlayerVehicleID(playerid));
	Gym_Disconnect(playerid);
	StopCombineMode(playerid);
	Process_PoolPlayerSize();
	DestroyLabelNick(playerid);
	SyncAmmoToEQ(playerid);
	SyncWeaponCDNToEQ(playerid);
	if(gracz[playerid][anty_leave_time] > serwer[time_timestamp]) DropItems(playerid, 1);
	EndLoginHistory(playerid);
	if(PlayerEditObject[playerid])
	{
		DeleteObject(PlayerEditObject[playerid]);
		CancelEdit(playerid);
		PlayerEditObject[playerid] = 0;
		Streamer_Update(playerid);
	}
	if(ognisko[playerid][o_status])
	{
		ognisko[playerid][o_status] = 1;//gaszenie ogniska
		Process_Campfire(playerid);//gaszenie ogniska
	}
	new str_leave[128];
	if(reason == 0) format(str_leave, 128, "~w~%s~r~ opuscil~w~ gre. (Timeout)", nick(playerid));
	else format(str_leave, 128, "~w~%s~r~ opuscil~w~ gre.", nick(playerid));
	if(serwer[downbar_query]) serwer[downbar_query]--;
	serwer[downbar_time] = serwer[time_timestamp]+5;
	PasekDol(str_leave);
	printf("[PLAYER]Gracz %s wylogowal sie poprawnie.", nick(playerid));
	return 1;
}
//**************************************************************************************************************************SPAWN/DEATH
public OnPlayerSpawn(playerid)
{
	if(!gracz[playerid][loggedin])
	{
		CheckS0beit(playerid);
		return 1;
	}
	gracz[playerid][god_check] = 0;
	Process_PoolPlayerSize();
	printf("[PLAYER]Gracz %s zespawnowal sie. IP: %s", nick(playerid), playerip(playerid));
	gracz[playerid][spawned] = true;
	if(gracz[playerid][first_spawn])
	{ 
		TogglePlayerControllable(playerid, false);
	}
	LoadUsedItems(playerid);
	Process_BW(playerid);
	SetGoodSkillLevel(playerid);
	SetPlayerAttachedObject(playerid, 7, 19559, 1, 0.107000, -0.044000, -0.000999, 0.000000 ,90.500007, 0.000000, 1.000000, 1.000000, 1.000000);
	return 1;
}
public OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(GetPVarInt(playerid, "SetFullHP"))
	{
		gracz[playerid][HP] = 100;
		SetPVarInt(playerid, "SetFullHP", 0);
	}
	gracz[playerid][god_check] = 0;
	if(SpawnProtect(playerid)) return 1;
	new bool:fakekill_detect;
	Process_PoolPlayerSize();
	if(killerid == INVALID_PLAYER_ID || playerid == killerid)
	{
		fakekill_detect = false;
	}
	else if(givenDamage[playerid][killerid])
	{
		givenDamage[playerid][killerid] = false;
		fakekill_detect = false;
	}
	else
	{
		fakekill_detect = true;
	}
	//***************************************************************************************************GDY GRACZ UMRZE
	if(!fakekill_detect)//AntyFakeKill
	{
		printf("[PLAYER]Gracz %s umarl[killerid: %d|reason: %d]. IP: %s", nick(playerid), killerid, reason, playerip(playerid));
		gracz[playerid][spawned] = false;
		if(IsPlayerInRangeOfPoint(playerid, 10.0, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
		{
			GetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
		}
		if(PlayerEditObject[playerid])
		{
			DeleteObject(PlayerEditObject[playerid]);
			CancelEdit(playerid);
			PlayerEditObject[playerid] = 0;
			Streamer_Update(playerid);
		}
		GangZoneHideForPlayer(playerid, serwer[gz_hidemap]);
		GangZoneShowForPlayer(playerid, serwer[gz_hidemap], 0x646464FF);
		HideMinimap(playerid);
		Dialog_Close(playerid);
		if(isvip(playerid)) ActivateBW(playerid, 1);
		else ActivateBW(playerid, 2);
		SetPlayerHP(playerid, 100);
		if(gracz[playerid][PGodz] >= 3) DropItems(playerid);
		SyncZetony(playerid);
		HideVehicleHUD(playerid);
		StopCombineMode(playerid);
		if(killerid != INVALID_PLAYER_ID)
		{
			GiveExp(killerid, 3, true, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			gracz[killerid][KillHumans]++;
			mq_format("UPDATE `Konta` SET `KillHumans`='%d' WHERE `id`='%d';", gracz[killerid][KillHumans], gracz[killerid][UID]);
			mq_send("QKillHumans");
		}
	}
	return 1;
}
//************************************************************************************************************************Aktualizacja gracza
public OnPlayerUpdate(playerid)
{
	if(!gracz[playerid][loggedin]) return 1;
	if(IsPlayerNPC(playerid)) return 1;
	Process_Halas(playerid);
	speedcap_OnPlayerUpdate(playerid);
	GetPlayerKeys(playerid, gracz[playerid][key_keyid], gracz[playerid][key_updown], gracz[playerid][key_leftright]);
	if(gracz[playerid][key_leftright] == 128 || gracz[playerid][key_leftright] == -128)
	{
		combine_OnPlayerKeyStateChange(playerid, gracz[playerid][key_leftright], 1);
	}
	else if(gracz[playerid][key_updown] == 128 || gracz[playerid][key_updown] == -128)
	{
		combine_OnPlayerKeyStateChange(playerid, gracz[playerid][key_updown], 0);
	}
	//speed test
	/*new test[65];
	format(test, 65, "speed: %d", GetSpeedXY(playerid));
	GameTextForPlayer(playerid, test, 1000, 5);*/
	//system AFK
	gracz[playerid][afk_control_timestamp] = serwer[time_timestamp]+5;
	gracz[playerid][afk_control_hour] = serwer[time_hour];
	gracz[playerid][afk_control_minute] = serwer[time_minute];
	//zapis pozycji
	if(gracz[playerid][spawned] && gracz[playerid][sec_online] > 5)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 200.0, 0.0, 0.0, 0.0) && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		{
			GetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			SetSpawnInfo(playerid, 0, gracz[playerid][Skin], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], 0.0, 0, 0, 0, 0, 0, 0);
		}
	}
	if(GetPlayerWeapon(playerid) != gracz[playerid][actual_weapon])
	{
		gracz[playerid][actual_weapon] = GetPlayerWeapon(playerid);
		Process_ArmedWeapon(playerid);
		if(gracz[playerid][actual_weapon])
		{
			PlayerTextDrawHide(playerid, td_fist[playerid]);
			PlayerTextDrawSetPreviewModel(playerid, weapon_model[playerid], GetWeaponModel(gracz[playerid][actual_weapon]));
			PlayerTextDrawShow(playerid, weapon_model[playerid]);
			RefreshAmmo(playerid);
		}
		else
		{
			PlayerTextDrawHide(playerid, weapon_model[playerid]);
			PlayerTextDrawShow(playerid, td_fist[playerid]);
			PlayerTextDrawSetString(playerid, td_player_hud1[playerid], "_");
			PlayerTextDrawShow(playerid, td_player_hud1[playerid]);
		}
	}
	/*if(gracz[playerid][actual_vehicleid] != GetPlayerVehicleID(playerid))
	{
		gracz[playerid][actual_vehicleid] = GetPlayerVehicleID(playerid);
		if(gracz[playerid][vehicleid_change] > GetTickCount() && = )
		{
			if(!gracz[playerid][AdminLevel]) Ban_Time(-1, playerid, "Vehicle teleport hack.", 1095);
			gracz[playerid][vehicleid_change] = GetTickCount()+500;
			return 0;
		}
		gracz[playerid][vehicleid_change] = GetTickCount()+500;
	}*/
	return 1;
}
//*********************************************************************************************************************Strzelanie
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(!gracz[playerid][loggedin]) return 0;
	static interval;
	interval = 0;
	switch (weaponid)
	{
		case 24: interval = CBUG_INTERVAL_DEAGLE;
		case 25: interval = CBUG_INTERVAL_SHOTGUN;
		case 27: interval = CBUG_INTERVAL_COMBATSG;
		case 33: interval = CBUG_INTERVAL_COUNTRY;
		case 34: interval = CBUG_INTERVAL_SNIPER;
	}
	if(interval > 0)
	{            
		if(GetTickCount() - gracz[playerid][cbug_tick] < interval && GetTickCount() - gracz[playerid][cbug_tick] >= 0)
		{                              
			SetPlayerArmedWeapon(playerid, 0);
			Error(playerid, "Wykryto C-BUG! Strza³ nie zosta³ zsynchronizowany.");
			SetTimerEx("UnFreeze", 1000, false, "d", playerid);
			TogglePlayerControllable(playerid, false);
			return 0;
		}
		gracz[playerid][cbug_tick] = GetTickCount();
	}
	if(ammo[playerid][weaponid] && w_cdn[playerid][weaponid] && !gracz[playerid][in_krypta])
	{
		ammo[playerid][weaponid]--;
		w_cdn[playerid][weaponid]--;
		gracz[playerid][shoot_halas] = true;
		RefreshAmmo(playerid);
		ShakePlayerCamera(playerid);
	}
	else
	{
		SetPlayerArmedWeapon(playerid, 0);
		if(!w_cdn[playerid][weaponid])  LeftNotifyShow(playerid, "error", "Bron jest ~r~uszkodzona~w~.", LN_RED);
		if(!ammo[playerid][weaponid])  LeftNotifyShow(playerid, "error", "~r~Brak amunicji~w~.", LN_RED);
		return 0;
	}
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z)
{
	return 1;
}

stock ShakePlayerCamera(playerid)
{
	if(gracz[playerid][tick_shakecamera] < GetTickCount())
	{
		CreateExplosionForPlayer(playerid, gracz[playerid][PosX]+random(8), gracz[playerid][PosY]+random(6), gracz[playerid][PosZ]-85, 5, 0.01);
		gracz[playerid][tick_shakecamera] = GetTickCount()+200; 
	}
	return 1;
}
//*********************************************************************************************************************STATECHANGE
public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(!gracz[playerid][loggedin]) return 1;
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
	{
		LeftNotifyShow(playerid, "info", "Aby ~g~odpalic~w~/~r~zgasic~w~ silnik, wcisnij ~y~lewy ALT~w~ lub ~y~LPM~w~.", _, 10);

	}
	else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
	{
		HideVehicleHUD(playerid);
		StopCombineMode(playerid);
	}
	return 1;
}
//*********************************************************************************************************ON PLAYER CLICK PLAYER
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(gracz[playerid][admin_duty])
	{
		if(playerid != clickedplayerid)
		{
			TogglePlayerSpectating(playerid, true);
			if(IsPlayerInAnyVehicle(clickedplayerid)) PlayerSpectateVehicle(playerid, GetPlayerVehicleID(clickedplayerid));
			else PlayerSpectatePlayer(playerid, clickedplayerid);
			SendClientMessageEx(playerid, -1, "Specujesz: "COL_LIME"%s ("COL_WHITE"%d"COL_LIME")", nick(clickedplayerid), clickedplayerid);
		}
		else
		{
			TogglePlayerSpectating(playerid, false);
		}
	}
	return 1;
}
//**********************************************************************************************************************************EDYCJA AKCESORII
public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	new i = index;
	if(response)
	{
		LeftNotifyShow(playerid, "info", "Pozycja akcesorii ~g~zapisana~w~!");
		ao[playerid][index][ao_x] = fOffsetX;
		ao[playerid][index][ao_y] = fOffsetY;
		ao[playerid][index][ao_z] = fOffsetZ;
		ao[playerid][index][ao_rx] = fRotX;
		ao[playerid][index][ao_ry] = fRotY;
		ao[playerid][index][ao_rz] = fRotZ;
		ao[playerid][index][ao_sx] = fScaleX;
		ao[playerid][index][ao_sy] = fScaleY;
		ao[playerid][index][ao_sz] = fScaleZ;
		mq_format("UPDATE `akcesoria` SET `ao_x`='%f', `ao_y`='%f', `ao_z`='%f', `ao_rx`='%f', `ao_ry`='%f', `ao_rz`='%f', `ao_sx`='%f', `ao_sy`='%f', `ao_sz`='%f' WHERE `userid`='%d' AND `type`='%d';", ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz], gracz[playerid][UID], ao[playerid][i][ao_typ]);
		mq_send("QUpdateAkcesoria");
	}
	else
	{
		LeftNotifyShow(playerid, "info", "Ustawienie pozycji akcesorii ~r~anulowane~w~!");
		SetPlayerAttachedObject(playerid, index, modelid, boneid, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
	}
	return 1;
}
//************************SYSTEMY****************************************************************************************************************************************
//***************************************************************************************TIMER GRACZA
forward OneSecondUpdate(i);
public OneSecondUpdate(i)
{
	if(!IsPlayerConnected(i)) return 1;
	if(IsPlayerNPC(i)) return 1;
	Process_PlayerMarker(i);
	if(!gracz[i][spawned]) return 1;
	if(!gracz[i][loggedin]) return 1;
	gracz[i][shoot_halas] = false;
	TimeOnServer(i);
	Process_RefreshHud(i);
	Process_BW(i);
	Process_SavePlayer(i);
	Process_CheckHP(i);
	Process_Kondycja(i);
	Process_Blooding(i);
	Process_Weather(i);
	Process_Campfire(i);
	Process_NickLabel(i);
	Process_WeaponCheck(i);
	Process_FlyHack(i);
	Process_GlodPragnienie(i);
	Process_ExpWindow(i);
	Process_TDShoot(i);
	Process_LeftNotify(i);
	Process_CombineMode(i);
	Process_KryptaProtect(i);
	Process_PlayerVehicle(i);
	Process_Rads(i);
	Process_GameField(i);
	Process_Temperatura(i);
	Process_TextSP(i);
	Process_ExpForExplore(i);
	return 1;
}
//******************************************************************************************Cykliczne zapisywanie statystyk
stock Process_SavePlayer(playerid)
{
	if(gracz[playerid][first_spawn]) return 1;
	if(gracz[playerid][time_savedata] > serwer[time_timestamp]) return 1;
	gracz[playerid][time_savedata] = serwer[time_timestamp]+5;
	mq_format("UPDATE `Konta` SET `PosX`='%f', `PosY`='%f', `PosZ`='%f', `HP`='%d', `LastOnline`='%d' WHERE `id`='%d';", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][HP], serwer[time_timestamp], gracz[playerid][UID]);
	mq_send("QSavePlayer");
	return 1;
}
//*****************************************************************************************SYSTEM BW
stock ActivateBW(playerid, minuty)
{
	if(gracz[playerid][admin_duty]) return 1;
	if(SpawnProtect(playerid) || gracz[playerid][MapperLvl] >= 2) return 1;
	gracz[playerid][BWTime] = 60*minuty;
	new str[256];
	format(str, 256, ""COL_DBLUE"[AINFO]"COL_RED"%s(%d)"COL_WHITE" dostal BW.", nick(playerid), playerid);
	SaveInPlayerLog(playerid, str);
	return 1;
}
stock DeactivateBW(playerid)
{
	GiveSpawnProtect(playerid, 15);
	gracz[playerid][BWTime] = 0;
	SetPVarInt(playerid, "BWAnimPreload", 0);
	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid);
	LeftNotifyShow(playerid, "info", "Twoja ~y~postac~w~ doszla~n~do siebie.");
	SetCameraBehindPlayer(playerid);
	mq_format("UPDATE `Konta` SET `BWTime`='%d' WHERE `id`='%d';", gracz[playerid][BWTime], gracz[playerid][UID]);
	mq_send("QBWTime");
	StopBlooding(playerid);
	return 1;
}
stock Process_BW(playerid)
{
	if(!gracz[playerid][BWTime]) return 1;
	new superstring[128];
	gracz[playerid][BWTime]--;
	gracz[playerid][HP] = 100;
	gracz[playerid][god_check] = 0;
	format(superstring,128,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~b~nieprzytomny:~n~~g~pozostalo %d sekund.", gracz[playerid][BWTime]);
	GameTextForPlayer(playerid, superstring, 1000, 3);
	mq_format("UPDATE `Konta` SET `BWTime`='%d' WHERE `id`='%d';", gracz[playerid][BWTime], gracz[playerid][UID]);
	mq_send("QBWTime");
	if(GetPVarInt(playerid, "BWAnimPreload") < 3)
	{
		SetPVarInt(playerid, "BWAnimPreload", GetPVarInt(playerid, "BWAnimPreload")+1);
		TogglePlayerControllable(playerid, 0);
		ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 1, 1, 1, 0, 1);
		ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 1, 1, 1, 0, 1);
		SetPlayerCameraPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]+5);
		SetPlayerCameraLookAt(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
	}
	if(gracz[playerid][BWTime] <= 1) DeactivateBW(playerid);
	return 1;
}
//*******************************************************************************************************Licznik przegranych godzin
stock TimeOnServer(playerid)
{
	gracz[playerid][sec_online]++;
	switch(gracz[playerid][sec_online])
	{
		case 600:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~10 minut~w~. Od teraz bedziesz dostawal ~g~+1~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 1;
		}
		case 1200:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~20 minut~w~. Od teraz bedziesz dostawal ~g~+2~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 2;
		}
		case 1800:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~30 minut~w~. Od teraz bedziesz dostawal ~g~+3~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 3;
		}
		case 2400:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~40 minut~w~. Od teraz bedziesz dostawal ~g~+4~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 4;
		}
		case 3000:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~50 minut~w~. Od teraz bedziesz dostawal ~g~+5~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 5;
		}
		case 3600:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~60 minut~w~. Od teraz bedziesz dostawal ~g~+9~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 9;
		}
		case 7200:
		{
			LeftNotifyShow(playerid, "EXP", "Przebywasz na serwerze juz ~y~2 godziny~w~. Od teraz bedziesz dostawal ~g~+20~w~ wiecej ~p~EXP~w~!", LN_YELLOW);
			gracz[playerid][exp_boost] = 20;
		}
	}
	if(IsPlayerAFK(playerid)) return 1;
	gracz[playerid][PSek]++;
	new bool:query_send;
	if(gracz[playerid][PSek] > 59)
	{
		gracz[playerid][PMin]++;
		gracz[playerid][PSek]=0;
		mq_format("UPDATE `Konta` SET `PGodz`='%d', `PMin`='%d', `PSek`='%d' WHERE `id`='%d';", gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][PSek], gracz[playerid][UID]);
		mq_send("QPlayedTimeM");
		query_send = true;
	}
	if(gracz[playerid][PMin] > 59)
	{
		gracz[playerid][PMin]=0;
		gracz[playerid][PGodz]++;
		mq_format("UPDATE `Konta` SET `PGodz`='%d', `PMin`='%d', `PSek`='%d' WHERE `id`='%d';", gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][PSek], gracz[playerid][UID]);
		mq_send("QPlayedTimeH");
		query_send = true;
	}
	SetPlayerScore(playerid, gracz[playerid][level]);
	if(!query_send)
	{
		mq_format("UPDATE `Konta` SET `PSek`='%d' WHERE `id`='%d';", gracz[playerid][PSek], gracz[playerid][UID]);
		mq_send("QPlayedTimeS");
	}
	return 1;
}
//***********************************************************************************************************System ha³asu
forward GetHalas(playerid);
public GetHalas(playerid) return gracz[playerid][gen_halas]+1;

stock Process_Halas(playerid)
{
	static halas_temp;
	halas_temp = GetDzwiek(playerid);
	if(halas_temp > 20 || gracz[playerid][shoot_halas])
	{
		halas_temp = 20;
	}
	if(IsPlayerCrouch(playerid) && halas_temp != 0)
	{
		halas_temp = 1;
	}
	if(gracz[playerid][MapperLvl] >= 2 || gracz[playerid][admin_duty])
	{
		halas_temp = 0;
	}
	gracz[playerid][gen_halas] = halas_temp;
	if(halas_temp && halas_temp < 5)
	{
		PlayerTextDrawShow(playerid, td_halas1[playerid]);
		PlayerTextDrawHide(playerid, td_halas2[playerid]);
		PlayerTextDrawHide(playerid, td_halas3[playerid]);
		PlayerTextDrawHide(playerid, td_halas4[playerid]);
	}
	else if(halas_temp > 5 && halas_temp < 10)
	{
		PlayerTextDrawShow(playerid, td_halas1[playerid]);
		PlayerTextDrawShow(playerid, td_halas2[playerid]);
		PlayerTextDrawHide(playerid, td_halas3[playerid]);
		PlayerTextDrawHide(playerid, td_halas4[playerid]);
	}
	else if(halas_temp > 10 && halas_temp < 15)
	{
		PlayerTextDrawShow(playerid, td_halas1[playerid]);
		PlayerTextDrawShow(playerid, td_halas2[playerid]);
		PlayerTextDrawShow(playerid, td_halas3[playerid]);
		PlayerTextDrawHide(playerid, td_halas4[playerid]);
	}
	else if(halas_temp > 15 && halas_temp <= 20)
	{
		PlayerTextDrawShow(playerid, td_halas1[playerid]);
		PlayerTextDrawShow(playerid, td_halas2[playerid]);
		PlayerTextDrawShow(playerid, td_halas3[playerid]);
		PlayerTextDrawShow(playerid, td_halas4[playerid]);
	}
	else
	{
		PlayerTextDrawHide(playerid, td_halas1[playerid]);
		PlayerTextDrawHide(playerid, td_halas2[playerid]);
		PlayerTextDrawHide(playerid, td_halas3[playerid]);
		PlayerTextDrawHide(playerid, td_halas4[playerid]);
	}
	return 1;
}
//******************************************************************************************************************SYSTEM KONDYCJI
stock Process_Kondycja(playerid)//1 sekunda
{
	if(gracz[playerid][kondycja_reftime] > GetTickCount()) return 1;
	if(IsPlayerInBoisko(playerid)) return 1;
	if(gracz[playerid][MapperLvl] >= 2) return 1;
	if(GetPlayerSpecialAction(playerid) == 2) return 1;
	if(gracz[playerid][admin_duty]) return 1;
	if(PlayerEditObject[playerid]) return 1;
	if(gracz[playerid][in_krypta] && !IsPlayerInGym(playerid)) return 1;
	gracz[playerid][kondycja_reftime] = GetTickCount()+200;
	if(GetPlayerSpeed(playerid) >= 20.0 && !IsPlayerCrouch(playerid))
	{
		gracz[playerid][kondycja] -= StrenghtCDN(playerid);
	}
	else if(GetPlayerSpeed(playerid) >= 13.0 && !IsPlayerCrouch(playerid))
	{
		gracz[playerid][kondycja] -= 1;
	}
	else
	{
		gracz[playerid][kondycja] += 4;
	}
	if(gracz[playerid][kondycja] > 100)
	{
		gracz[playerid][kondycja] = 100;
	}
	else if(gracz[playerid][kondycja] < 0)
	{
		gracz[playerid][kondycja] = 0;
	}
	if(gracz[playerid][stamina_boost] > serwer[time_timestamp])
	{
		gracz[playerid][kondycja] += 30;
	}
	if(gracz[playerid][kondycja] < 1)
	{
		if(IsPlayerInGym(playerid)) return 1;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		gracz[playerid][kondycja] = 1;
		SetTimerEx("ZdejmijFreezaKondycji_STEP1", 700, 0, "d", playerid);
		ApplyAnimation(playerid, "FAT", "IDLE_TIRED", 4.1, 1, 1, 1, 1, 1, 1);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~KONDYCJA!",1000,5);
	}
	SetBarCDN(playerid, gracz[playerid][kondycja]);
	return 1;
}
forward ZdejmijFreezaKondycji_STEP1(playerid);
public ZdejmijFreezaKondycji_STEP1(playerid)
{
	TogglePlayerControllable(playerid, 0);
	ApplyAnimation(playerid, "FAT", "IDLE_TIRED", 4.1, 1, 1, 1, 1, 1, 1);
	SetTimerEx("ZdejmijFreezaKondycji_STEP2", 2400, 0, "d", playerid);
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~ODPOCZYWASZ...",2400,5);
	return 1;
}
forward ZdejmijFreezaKondycji_STEP2(playerid);
public ZdejmijFreezaKondycji_STEP2(playerid)
{
	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid);
	SetPlayerSkin(playerid, GetPlayerSkin(playerid));
	return 1;
}
//******************************************************************************************************************SYSTEM POGODY
stock Process_Weather(playerid)
{
	if(gracz[playerid][mapper_weather] == 1) 
	{
		SetPlayerTime(playerid, 12, 0);
		SetPlayerWeather(playerid, 0);
	}
	else if(gracz[playerid][mapper_weather] == 2)
	{
		SetPlayerTime(playerid, 0, 0);
		SetPlayerWeather(playerid, 0);
	}
	if(IsPlayerInBoisko(playerid))
	{
		gracz[playerid][in_interior] = true;
		gracz[playerid][in_krypta] = true;
		if(!gracz[playerid][mapper_weather]) SetPlayerTime(playerid, 20, 0);
		if(!gracz[playerid][mapper_weather]) SetPlayerWeather(playerid, 0);
		SetPlayerInterior(playerid, 1);
		if(serwer[playerboisko_time] < gettime())
		{
			serwer[playerboisko_time] = gettime()+30;
		}
	}
	else if(gracz[playerid][PosZ] > 1500.0)
	{
		gracz[playerid][in_interior] = true;
		if(!gracz[playerid][mapper_weather]) SetPlayerTime(playerid, 15, 0);
		if(!gracz[playerid][mapper_weather]) SetPlayerWeather(playerid, 0);
		SetPlayerInterior(playerid, 0);
	}
	else
	{
		switch(serwer[godzina])
		{
			case 1..6:
			{
				if(!gracz[playerid][mapper_weather]) SetPlayerTime(playerid, 6, 0);
			}
			default:
			{
				if(!gracz[playerid][mapper_weather]) SetPlayerTime(playerid, serwer[godzina], 0);
			}
		}
		gracz[playerid][in_interior] = false;
		gracz[playerid][in_krypta] = false;
		SetPlayerInterior(playerid, 0);
		if(!gracz[playerid][mapper_weather]) SetPlayerWeather(playerid, serwer[pogoda]);
	}
	return 1;
}
//****************************************************************************************************************OBS£UGA FADE
public OnFadeComplete(playerid, beforehold)
{
	if(beforehold)
	{
		if(gracz[playerid][first_spawn])
		{
			gracz[playerid][first_spawn] = false;
			SetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			if(!gracz[playerid][BWTime] && !gracz[playerid][WebReg]) TogglePlayerControllable(playerid, true);
		}
	}
	return 1;
}
//****************************************************************************************************************ANTY WEAPON hack 
stock Process_WeaponCheck(playerid)
{
	if(gracz[playerid][AdminLevel] > 1) return 1;
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && gracz[playerid][MapperLvl] < 2)
	{
		Ban_Time(-1, playerid, "Jetpack.", 1095);
		return 1;
	}
	if(gracz[playerid][actual_weapon] == 0) return 1;
	if(gracz[playerid][actual_weapon] == 46) return 1;
	if(!weapon[playerid][gracz[playerid][actual_weapon]])
	{
		if(GetPVarInt(playerid, "WeaponWarn") >= 3)
		{
			Ban_Time(-1, playerid, "Weapon Hack.", 1095);
		}
		ResetPlayerWeapons(playerid);
		LoadUsedWeapons(playerid);
		SetPVarInt(playerid, "WeaponWarn", GetPVarInt(playerid, "WeaponWarn")+1);
	}
	else SetPVarInt(playerid, "WeaponWarn", 0);
	if(gracz[playerid][actual_weapon] && IsPlayerInAnyVehicle(playerid))
	{
		SetPlayerArmedWeapon(playerid, 0);
	}
	return 1;
}
//******************************************************************************************************************Anty AIRBRK
public OnPlayerAirbreak(playerid)
{
	if(gracz[playerid][MapperLvl] >= 2) return 1;
	if(gracz[playerid][AdminLevel] >= 1) return 1;
	Ban_Time(-1, playerid, "AirBrk.", 1095);
	return 1;
}
//********************************************************************************************************************anty fly hack
stock Process_FlyHack(playerid)
{
	if(gracz[playerid][AdminLevel] > 1) return 1;
	if(gracz[playerid][PosZ] > 1.0 && GetSpeedXY(playerid) > 100)
	{
		new a_index = GetPlayerAnimationIndex(playerid);
		if((a_index == 1544 || a_index == 1538) || (gracz[playerid][actual_weapon] != 46 && (a_index == 959 || a_index == 373)))
		{
			Ban_Time(-1, playerid, "FlyHack.", 1095);
		}
	}
	return 1;
}
//**********************************************************************************************************************historia logowania
stock StartLoginHistory(playerid)
{
	gracz[playerid][loginhistory_start] = serwer[time_timestamp];
	gracz[playerid][loginhistory_end] = serwer[time_timestamp];
	return 1;
}
stock EndLoginHistory(playerid)
{
	gracz[playerid][loginhistory_end] = serwer[time_timestamp];
	mq_format("INSERT INTO `HistoriaLogowania` (`uid`, `login`, `logout`) VALUES ('%d', FROM_UNIXTIME('%d'), FROM_UNIXTIME('%d'));", gracz[playerid][UID], gracz[playerid][loginhistory_start], gracz[playerid][loginhistory_end]);
	mq_send("QLoginHistory");
	return 1;
}
//*********************************************************************************************************************markery graczy
stock Process_PlayerMarker(playerid)//m - drugi gracz
{
	for(new m = PlayerPoolSize(); m != -1; m--)
	{
		if(gracz[m][loggedin])
		{
			if(gracz[playerid][OrgID] == gracz[m][OrgID] && gracz[playerid][OrgID] && gracz[m][OrgID])//gps grup
			{
				if(isvip(m)) SetPlayerMarkerForPlayer(playerid, m, 0xB0B200FF);//VIP, widoczny
				else SetPlayerMarkerForPlayer(playerid, m, 0x00B403FF);//zielony - cz³onek grupy
			}
			else if(gracz[playerid][gps_hz] == gracz[m][gps_hz] && gracz[playerid][gps] && gracz[m][gps])//gps przedmiot
			{
				if(isvip(m)) SetPlayerMarkerForPlayer(playerid, m, 0xB0B200FF);//VIP, widoczny
				else SetPlayerMarkerForPlayer(playerid, m, 0x727272FF);//siwy, widoczny
			}
			else//zmienianie na niewidzialnoœæ
			{
				if(isvip(m)) SetPlayerMarkerForPlayer(playerid, m, 0xB0B20000);//VIP
				else SetPlayerMarkerForPlayer(playerid, m, 0x72727200);//siwy
			}
		}
		else
		{
			SetPlayerMarkerForPlayer(playerid, m, 0x00000000);//czarny
		}
	}
	return 1;
}
//****************************************************************************************************************************g³ód/pragnienie
stock Process_GlodPragnienie(playerid)
{
	if(gracz[playerid][admin_duty]) return 1;
	if(gracz[playerid][MapperLvl]) return 1;
		//g³ód
	if(GetPVarInt(playerid, "GProces") < serwer[time_timestamp])
	{
		SetPVarInt(playerid, "GProces", serwer[time_timestamp]+10*60);
		gracz[playerid][Glod] -= RandomEx(1, 3);
		if(gracz[playerid][Glod] > 100)
		{
			gracz[playerid][Glod] = 100;
		}
		else if(gracz[playerid][Glod] < 0)
		{
			gracz[playerid][Glod] = 0;
		}
		if(gracz[playerid][Glod] < 10)
		{
			SendClientMessage(playerid, -1, "(("COL_RED"Jesteœ g³odny! Zjedz coœ, inaczej stracisz przytomnoœæ!"COL_WHITE"))");
			TakePlayerHP(playerid, 5);
		}
		SetBarGlod(playerid, gracz[playerid][Glod]);
		mq_format("UPDATE `Konta` SET `Glod`='%d' WHERE `id`='%d';", gracz[playerid][Glod], gracz[playerid][UID]);
		mq_send("QGlod");
	}
		//pragnienie
	if(GetPVarInt(playerid, "PProces") < serwer[time_timestamp])
	{
		SetPVarInt(playerid, "PProces", serwer[time_timestamp]+8*60);
		gracz[playerid][Pragn] -= RandomEx(1, 3);
		if(gracz[playerid][Pragn] > 100)
		{
			gracz[playerid][Pragn] = 100;
		}
		else if(gracz[playerid][Pragn] < 0)
		{
			gracz[playerid][Pragn] = 0;
		}
		if(gracz[playerid][Pragn] < 10)
		{
			SendClientMessage(playerid, -1, "(("COL_RED"Jesteœ spragniony! Wypij coœ, inaczej stracisz przytomnoœæ!"COL_WHITE"))");
			TakePlayerHP(playerid, 5);
		}
		SetBarPragn(playerid, gracz[playerid][Pragn]);
		mq_format("UPDATE `Konta` SET `Pragn`='%d' WHERE `id`='%d';", gracz[playerid][Pragn], gracz[playerid][UID]);
		mq_send("QPragn");
	}
	return 1;
}

stock FeedPlayer(playerid, val)
{
	gracz[playerid][Glod] += val;
	if(gracz[playerid][Glod] > 100)
	{
		gracz[playerid][Glod] = 100;
	}
	else if(gracz[playerid][Glod] < 0)
	{
		gracz[playerid][Glod] = 0;
	}
	ApplyAnimation(playerid,"FOOD","EAT_Burger",1.0,0,1,1,0,0);
	SetBarGlod(playerid, gracz[playerid][Glod]);
	mq_format("UPDATE `Konta` SET `Glod`='%d' WHERE `id`='%d';", gracz[playerid][Glod], gracz[playerid][UID]);
	mq_send("QGlod");
	pKrypta[playerid][pk_status] = 120;
	return 1;
}

stock DrinkPlayer(playerid, val)
{
	gracz[playerid][Pragn] += val;
	if(gracz[playerid][Pragn] > 100)
	{
		gracz[playerid][Pragn] = 100;
	}
	else if(gracz[playerid][Pragn] < 0)
	{
		gracz[playerid][Pragn] = 0;
	}
	ApplyAnimation(playerid,"VENDING","VEND_Drink2_P",1.0,0,1,1,0,0);
	SetBarPragn(playerid, gracz[playerid][Pragn]);
	mq_format("UPDATE `Konta` SET `Pragn`='%d' WHERE `id`='%d';", gracz[playerid][Pragn], gracz[playerid][UID]);
	mq_send("QPragn");
	return 1;
}
//***********************************************************************************************KRYPTA PROTECT
stock Process_KryptaProtect(playerid)
{
	
	if(IsPlayerInBoisko(playerid)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInGym(playerid)) gracz[playerid][in_krypta] = true;//si³ownia
	else if(IsPlayerInRangeOfPoint(playerid, 80.0, -1999.7366,-1558.9781,87.9436) && gracz[playerid][PosZ] < 120.0) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2344.9458,-1652.0934,2308.8259)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -1953.9146,-1598.6378,2306.4160)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2563.7761,-2127.7659,2318.1797)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2727.4834,-1772.3660,2308.8259)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2235.0435,-2041.2233,2308.8259)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2076.1985,-1598.2826,2308.8259)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2125.8914,-2420.2996,2309.2158)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2462.2852,-2492.2937,2309.2158)) gracz[playerid][in_krypta] = true;
	else if(IsPlayerInRangeOfPoint(playerid, 100.0, -2395.4392,-2735.6243,2309.2158)) gracz[playerid][in_krypta] = true;
	else
	{
		gracz[playerid][in_krypta] = false;
	}
	/*		
	if(gracz[playerid][in_krypta])
	{
		if(gracz[playerid][actual_weapon])
		{
			SetPlayerArmedWeapon(playerid, 0);
		}
	}*/
	return 1;
}
//**************************************************************************************************************RADS
new Float:rads_field[][4] =
{
	//range, x,y,z
	{1000.0, 0.0, 0.0, 0.0}
};
stock Process_Rads(playerid)
{
	if(gracz[playerid][rads_timestamp] > serwer[time_timestamp]) return 1;
	gracz[playerid][rads_timestamp] = serwer[time_timestamp]+2;
	new Float:distance;
	new int_distance;
	for(new r; r < sizeof(rads_field); r++)
	{
		if(IsPlayerInRangeOfPoint(playerid, rads_field[r][0], rads_field[r][1], rads_field[r][2], rads_field[r][3]))
		{
			distance = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], rads_field[r][1], rads_field[r][2], rads_field[r][3]);
			int_distance = floatround(distance)+8;
			gracz[playerid][geiger_rads] = 6000/int_distance;
			switch(gracz[playerid][geiger_rads])
			{
				case 250..800:
				{
					gracz[playerid][rads] += 4; 
					NormalizeRads(playerid);
					mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
					mq_send("QRadsUpdate");
				}
				case 150..249:
				{
					gracz[playerid][rads] += 3;
					NormalizeRads(playerid);
					mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
					mq_send("QRadsUpdate");
				}
				case 130..149:
				{
					gracz[playerid][rads] += 2;
					NormalizeRads(playerid);
					mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
					mq_send("QRadsUpdate");
				}
				case 100..129:
				{
					gracz[playerid][rads] += 1;
					NormalizeRads(playerid);
					mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
					mq_send("QRadsUpdate");
				}
			}
			if(gracz[playerid][geiger_rads] < 50)
			{
				gracz[playerid][geiger_rads] = MRandRange(50, 70);
			}
		}
		else
		{
			gracz[playerid][geiger_rads] = MRandRange(50, 70);
		}
	}
	NormalizeRads(playerid);
	SetBarRads(playerid, gracz[playerid][rads]);
	//akcja rads
	if(!_PlayerTeleporting[playerid])
	{
		switch(gracz[playerid][rads])
		{
			case 0..33:
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, 5)) RemovePlayerAttachedObject(playerid, 5);
			}
			case 34..66:
			{
				if(gracz[playerid][time_rads_effect] < serwer[time_timestamp])
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, 5)) RemovePlayerAttachedObject(playerid, 5);
					TakePlayerHP(playerid, 1);
					FadeColorForPlayer(playerid, 229, 231, 0, 100, 229, 231, 0, 0, 30, 1);
					gracz[playerid][time_rads_effect] = serwer[time_timestamp]+60*6;
					LeftNotifyShow(playerid, "info", "Twoja postaci ~r~cierpi~w~ na ~y~chorobe popromienna~w~!", LN_RED);
				}
			}
			case 67..100:
			{
				if(gracz[playerid][time_rads_effect] < serwer[time_timestamp])
				{
					if(!IsPlayerAttachedObjectSlotUsed(playerid, 5)) SetPlayerAttachedObject(playerid, 5, 2907, 1, 0.038000,0.051000,0.027000,-94.999984, -0.299995, 89.399932, 1.0, 0.739000, 1.211000);
					TakePlayerHP(playerid, 2);
					FadeColorForPlayer(playerid, 229, 231, 0, 255, 229, 231, 0, 0, 30, 1);
					gracz[playerid][time_rads_effect] = serwer[time_timestamp]+60*3;
					LeftNotifyShow(playerid, "info", "Twoja postaci ~r~cierpi~w~ na ~y~chorobe popromienna~w~!", LN_RED);
				}
			}
		}
	}
	return 1;
}

stock NormalizeRads(playerid)
{
	if(gracz[playerid][rads] > 100)
	{
		gracz[playerid][rads] = 100;
	}
	if(gracz[playerid][rads] < 0)
	{
		gracz[playerid][rads] = 0;
	}
}
//********************************************************************************************************************MODEL SELECT
public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if(GetPVarInt(playerid, "UzylUbranie"))
	{
		if(listid == k_skinbialy || listid == m_skinbialy || listid == k_skinzolty || listid == m_skinzolty || listid == k_skinczarny || listid == m_skinczarny)
		{
			if(response)
			{
				if(RemoveItemFromPlayer(playerid, 158, 1))
				{
					gracz[playerid][Skin] = modelid;
					SetPlayerSkin(playerid, gracz[playerid][Skin]);
					SetPVarInt(playerid, "UzylUbranie", 0);
					mq_format("UPDATE `Konta` SET `Skin`='%d' WHERE `id`='%d';", gracz[playerid][Skin], gracz[playerid][UID]);
					mq_send("QSkinUpdate");
				}
			}
		}
	}
	else
	{
		if(listid == k_skinbialy || listid == m_skinbialy || listid == k_skinzolty || listid == m_skinzolty || listid == k_skinczarny || listid == m_skinczarny)
		{
			if(response)
			{
				gracz[playerid][Skin] = modelid;
				Dialog_Show(playerid, REGEND, DIALOG_STYLE_MSGBOX, ""COL_RED"»"COL_WHITE" Rejestracja - Zakonczenie", ""COL_WHITE"Czy akceptujesz "COL_RED"regulamin serwera"COL_WHITE" znajduj¹cy siê na "COL_YELLOW"forum.angelfall.pl"COL_WHITE"?", "TAK", "NIE");
			}
			else
			{
				WybierzSkin(playerid);
			}
		}
	}
	return 1;
}

public OnPlayerModelSelectionEx(playerid, response, extraid, modelid)
{
	if(!response) return 1;
	if(extraid == MSEL_GOBJECTS)
	{
		new str_cmd[128];
		format(str_cmd, 128, "/mc %d", modelid);
		PC_EmulateCommand(playerid, str_cmd);
	}
	return 1;
}
//********************************************************************************************************************WYBÓR SKINU
stock WybierzSkin(playerid)
{
	switch(gracz[playerid][Plec])
	{
		case 1://men
		{
			if(gracz[playerid][Karnacja] == 1)
			{
				ShowModelSelectionMenu(playerid, m_skinbialy, "Wybor skina");
			}
			else if(gracz[playerid][Karnacja] == 2)
			{
				ShowModelSelectionMenu(playerid, m_skinzolty, "Wybor skina");
			}
			else if(gracz[playerid][Karnacja] == 3)
			{
				ShowModelSelectionMenu(playerid, m_skinczarny, "Wybor skina");
			}
		}
		case 2://kob
		{
			if(gracz[playerid][Karnacja] == 1)
			{
				ShowModelSelectionMenu(playerid, k_skinbialy, "Wybor skina");
			}
			else if(gracz[playerid][Karnacja] == 2)
			{
				ShowModelSelectionMenu(playerid, k_skinzolty, "Wybor skina");
			}
			else if(gracz[playerid][Karnacja] == 3)
			{
				ShowModelSelectionMenu(playerid, k_skinczarny, "Wybor skina");
			}
		}
	}
	return 1;
}
//************************************************************************************************************GAME FIELD
stock Process_GameField(playerid)
{
	if(gracz[playerid][MapperLvl] >= 2) return 1;
	if(!IsPlayerInDynamicArea(playerid, serwer[game_field]) && !gracz[playerid][BWTime] && !gracz[playerid][in_interior] && gracz[playerid][sec_online] > 10)
	{
		GameTextForPlayer(playerid, "~g~ZAWROC!~n~~r~TEREN SKAZONY!~n~~y~TRACISZ HP!",1000,5);
		TakePlayerHP(playerid, 1);
	}
	return 1;
}
//******************************************************************************************************TEMPERATURA
stock Process_Temperatura(playerid)
{
	if(gracz[playerid][rads] > 90)
	{
		SetTempStatus(playerid, "39.3");
	}
	else if(gracz[playerid][rads] > 50)
	{
		SetTempStatus(playerid, "38.8");
	}
	else if(gracz[playerid][rads] > 20)
	{
		SetTempStatus(playerid, "37.9");
	}
	else if(gracz[playerid][kondycja] < 20)
	{
		SetTempStatus(playerid, "36.7");
	}
	else if(gracz[playerid][PosZ] < 1.0)
	{
		SetTempStatus(playerid, "35.5");
	}
	else
	{
		SetTempStatus(playerid, "36.6");
	}
	return 1;
}
//*************************************************************************************************************SPEEDCAP
new Float:g_fSpeedCap[ MAX_PLAYERS ] = { 0.0, ... };

stock speedcap_OnPlayerUpdate(playerid)
{
	static
		s_iVehicle
	;
	
	if ( g_fSpeedCap[ playerid ] != 0.0 && GetPlayerState( playerid ) == PLAYER_STATE_DRIVER )
	{
		s_iVehicle = GetPlayerVehicleID( playerid );
		
		if ( s_iVehicle )
		{
			static
				Float:s_fX,
				Float:s_fY,
				Float:s_fZ,
				Float:s_fVX,
				Float:s_fVY,
				Float:s_fVZ
			;
			
			GetVehiclePos( s_iVehicle, s_fX, s_fY, s_fZ );
			GetVehicleVelocity( s_iVehicle, s_fVX, s_fVY, s_fVZ );
			
			if ( !IsPlayerInRangeOfPoint( playerid, g_fSpeedCap[ playerid ] + 0.05, s_fX + s_fVX, s_fY + s_fVY, s_fZ + s_fVZ ) )
			{
				static
					Float:s_fLength
				;
				
				s_fLength = floatsqroot( ( s_fVX * s_fVX ) + ( s_fVY * s_fVY ) + ( s_fVZ * s_fVZ ) );
				
				s_fVX = ( s_fVX / s_fLength ) * g_fSpeedCap[ playerid ];
				s_fVY = ( s_fVY / s_fLength ) * g_fSpeedCap[ playerid ];
				s_fVZ = ( s_fVZ / s_fLength ) * g_fSpeedCap[ playerid ];
				
				SetVehicleVelocity( s_iVehicle, s_fVX, s_fVY, s_fVZ );
			}
		}
	}
	/*else if ( g_fSpeedCap[ playerid ] != 0.0 && GetPlayerState( playerid ) == PLAYER_STATE_ONFOOT )
	{
		static
		Float:s_fX,
		Float:s_fY,
		Float:s_fZ,
		Float:s_fVX,
		Float:s_fVY,
		Float:s_fVZ,
		Float:s_temp_fVZ
		;

		GetPlayerPos(playerid, s_fX, s_fY, s_fZ );
		GetPlayerVelocity(playerid, s_fVX, s_fVY, s_fVZ );
		s_temp_fVZ = s_fVZ;
		if (!IsPlayerInRangeOfPoint( playerid, g_fSpeedCap[ playerid ] + 0.05, s_fX + s_fVX, s_fY + s_fVY, s_fZ + s_fVZ ) )
		{
			static
			Float:s_fLength
			;

			s_fLength = floatsqroot( ( s_fVX * s_fVX ) + ( s_fVY * s_fVY ) + ( s_fVZ * s_fVZ ) );

			s_fVX = ( s_fVX / s_fLength ) * g_fSpeedCap[ playerid ];
			s_fVY = ( s_fVY / s_fLength ) * g_fSpeedCap[ playerid ];
			s_fVZ = ( s_fVZ / s_fLength ) * g_fSpeedCap[ playerid ];
			SetPlayerVelocity( playerid, s_fVX, s_fVY, s_temp_fVZ);
		}
	}
	*/
	return 1;
}

stock SetPlayerSpeedCap( playerid, Float:value )
{
	if ( 0 <= playerid < sizeof( g_fSpeedCap ) )
		g_fSpeedCap[ playerid ] = value;
}

stock DisablePlayerSpeedCap( playerid )
{
	if ( 0 <= playerid < sizeof( g_fSpeedCap ) )
		g_fSpeedCap[ playerid ] = 0.0;
}
//***************************************************************************Y MENU
stock ShowYMenu(playerid)
{
	new str[512];
	format(str, 512, ""COL_BLUE"»\t"COL_GREEN"Ekwipunek\t"COL_BLUE"«");
	format(str, 512, "%s\n"COL_YELLOW"»\t"COL_EASY"Specjalizacje\t"COL_YELLOW"«", str);
	Dialog_Show(playerid, YMENU, DIALOG_STYLE_TABLIST, ""COL_RED"» "COL_GREY"Wybierz akcje:", str, "Wybierz", "Anuluj");
	return 1;
}
Dialog:YMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			ListItems(playerid);
		}
		case 1:
		{
			ShowSkillWindow(playerid);
		}
	}
	return 1;
}
//****************************************************************************************************************************************SKRYPT SPECJALIZACJI
stock WeapSkill(playerid, need)
{
	if(gracz[playerid][admin_duty]) return 1;
	if(need > gracz[playerid][rusznikarstwo])
	{
		new str[128];
		format(str, 128, "Aby wykonac ta akcje, ~r~musisz posiadac~w~ minimum ~y~%d~w~ punktow dla specjalizacji: ~g~rusznikarstwo~w~.", need);
		LeftNotifyShow(playerid, "error", str, LN_RED, 10);
		return 0;
	}
	return 1;
}  
stock VehSkill(playerid, need)
{
	if(gracz[playerid][admin_duty]) return 1;
	if(need > gracz[playerid][motoryzacja])
	{
		new str[128];
		format(str, 128, "Aby wykonac ta akcje, ~r~musisz posiadac~w~ minimum ~y~%d~w~ punktow dla specjalizacji: ~g~motoryzacja~w~.", need);
		LeftNotifyShow(playerid, "error", str, LN_RED, 10);
		return 0;
	}
	return 1;
}  
stock MedSkill(playerid, need)
{
	if(gracz[playerid][admin_duty]) return 1;
	if(need > gracz[playerid][medycyna])
	{
		new str[128];
		format(str, 128, "Aby wykonac ta akcje, ~r~musisz posiadac~w~ minimum ~y~%d~w~ punktow dla specjalizacji: ~g~medycyna~w~.", need);
		LeftNotifyShow(playerid, "error", str, LN_RED, 10);
		return 0;
	}
	return 1;
}

stock CalcFreeSkillPoints(playerid)
{
	new points;
	points = gracz[playerid][level];
	if(points > 20) points = 20;
	points -= gracz[playerid][rusznikarstwo];
	points -= gracz[playerid][motoryzacja];
	points -= gracz[playerid][medycyna];
	if(points < 0) points = 0;
	return points;
}

stock ShowSkillWindow(playerid)
{
	new str[1500];
	new freep = CalcFreeSkillPoints(playerid);
	format(str, 1500, ""COL_GREY"Specjalizacja\t"COL_GREY"Przydzielone punkty("COL_BLUE"%d"COL_GREY"/20)\t"COL_GREEN"Dostêpne punkty: "COL_RED"%d"COL_GREY"/20", gracz[playerid][rusznikarstwo]+gracz[playerid][motoryzacja]+gracz[playerid][medycyna], freep);
	if(freep && gracz[playerid][rusznikarstwo] < 20)
	{
		format(str, 1500, "%s\n"COL_RED"» "COL_ORANGE" Rusznikarstwo\t"COL_GREEN"%d "COL_GREY"/"COL_RED"17\t"COL_YELLOW"["COL_GREEN"ulepsz"COL_YELLOW"]", str, gracz[playerid][rusznikarstwo]);
	}
	else if(gracz[playerid][rusznikarstwo] == 20) format(str, 1500, "%s\n"COL_RED"» "COL_ORANGE" Rusznikarstwo\t"COL_GREEN"%d "COL_GREY"/"COL_RED"17\t"COL_YELLOW"["COL_RED"max"COL_YELLOW"]", str, gracz[playerid][rusznikarstwo]);
	else format(str, 1500, "%s\n"COL_RED"» "COL_ORANGE" Rusznikarstwo\t"COL_GREEN"%d "COL_GREY"/"COL_RED"17\t"COL_YELLOW"["COL_RED"ulepsz"COL_YELLOW"]", str, gracz[playerid][rusznikarstwo]);
	
	if(freep && gracz[playerid][motoryzacja] < 20)
	{
		format(str, 1500, "%s\n"COL_RED"» "COL_DBLUE" Motoryzacja\t"COL_GREEN"%d "COL_GREY"/"COL_RED"11\t"COL_YELLOW"["COL_GREEN"ulepsz"COL_YELLOW"]", str, gracz[playerid][motoryzacja]);
	}
	else if(gracz[playerid][motoryzacja] == 20) format(str, 1500, "%s\n"COL_RED"» "COL_DBLUE" Motoryzacja\t"COL_GREEN"%d "COL_GREY"/"COL_RED"11\t"COL_YELLOW"["COL_RED"max"COL_YELLOW"]", str, gracz[playerid][motoryzacja]);
	else format(str, 1500, "%s\n"COL_RED"» "COL_DBLUE" Motoryzacja\t"COL_GREEN"%d "COL_GREY"/"COL_RED"11\t"COL_YELLOW"["COL_RED"ulepsz"COL_YELLOW"]", str, gracz[playerid][motoryzacja]);
	
	if(freep && gracz[playerid][medycyna] < 20)
	{
		format(str, 1500, "%s\n"COL_RED"» "COL_BLUE" Medycyna\t"COL_GREEN"%d "COL_GREY"/"COL_RED"17\t"COL_YELLOW"["COL_GREEN"ulepsz"COL_YELLOW"]", str, gracz[playerid][medycyna]);
	}
	else if(gracz[playerid][medycyna] == 20) format(str, 1500, "%s\n"COL_RED"» "COL_BLUE" Medycyna\t"COL_GREEN"%d "COL_GREY"/"COL_RED"17\t"COL_YELLOW"["COL_RED"max"COL_YELLOW"]", str, gracz[playerid][medycyna]);
	else format(str, 1500, "%s\n"COL_RED"» "COL_BLUE" Medycyna\t"COL_GREEN"%d "COL_GREY"/"COL_RED"17\t"COL_YELLOW"["COL_RED"ulepsz"COL_YELLOW"]", str, gracz[playerid][medycyna]);

	format(str, 1500, "%s\n"COL_GREY"Wiêcej:", str);
	format(str, 1500, "%s\n"COL_GREY"Szczegó³y:"COL_ORANGE" Rusznikarstwo ", str);
	format(str, 1500, "%s\n"COL_GREY"Szczegó³y:"COL_DBLUE" Motoryzacja ", str);
	format(str, 1500, "%s\n"COL_GREY"Szczegó³y:"COL_BLUE" Medycyna ", str);
	Dialog_Show(playerid, SKILLUP, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREEN"Rozwój specjalizacji", str, "Wybierz", "Anuluj");
	return 1;
}

Dialog:SKILLUP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][WebReg]) return Error(playerid, "To jeszcze nie pora na przydzielanie specjalizacji.");
	new freep = CalcFreeSkillPoints(playerid);
	switch(listitem)
	{
		case 0:
		{
			if(freep && gracz[playerid][rusznikarstwo] < 17) 
			{
				gracz[playerid][rusznikarstwo]++;
				LeftNotifyShow(playerid, "Sukces!", "~g~Rozwinieto~w~ specjalizacje: ~y~rusznikarstwo~w~.", LN_GREEN, 10);
				ShowSkillWindow(playerid);
				mq_format("UPDATE `Konta` SET `rusznikarstwo`='%d' WHERE `id`='%d';", gracz[playerid][rusznikarstwo], gracz[playerid][UID]);
				mq_send("QUpdateSkill");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "~r~Nie mozna dodac~y~ punktu~w~ dla tej specjalizacji, gdyz ~r~brak punktow~w~/~g~jest juz rozwinieta na maxa~w~.", LN_RED, 10);
			}
		}
		case 1:
		{
			if(freep && gracz[playerid][motoryzacja] < 11) 
			{
				gracz[playerid][motoryzacja]++;
				LeftNotifyShow(playerid, "Sukces!", "~g~Rozwinieto~w~ specjalizacje: ~y~motoryzacja~w~.", LN_GREEN, 10);
				ShowSkillWindow(playerid);
				mq_format("UPDATE `Konta` SET `motoryzacja`='%d' WHERE `id`='%d';;", gracz[playerid][motoryzacja], gracz[playerid][UID]);
				mq_send("QUpdateSkill");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "~r~Nie mozna dodac~y~ punktu~w~ dla tej specjalizacji, gdyz ~r~brak punktow~w~/~g~jest juz rozwinieta na maxa~w~.", LN_RED, 10);
			}
		}
		case 2:
		{
			if(freep && gracz[playerid][medycyna] < 17)
			{ 
				gracz[playerid][medycyna]++;
				LeftNotifyShow(playerid, "Sukces!", "~g~Rozwinieto~w~ specjalizacje: ~y~medycyna~w~.", LN_GREEN, 10);
				ShowSkillWindow(playerid);
				mq_format("UPDATE `Konta` SET `medycyna`='%d' WHERE `id`='%d';;", gracz[playerid][medycyna], gracz[playerid][UID]);
				mq_send("QUpdateSkill");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "~r~Nie mozna dodac~y~ punktu~w~ dla tej specjalizacji, gdyz ~r~brak punktow~w~/~g~jest juz rozwinieta na maxa~w~.", LN_RED, 10);
			}
		}
		case 4:
		{
			SpecAbout(playerid, 0);
		}
		case 5:
		{
			SpecAbout(playerid, 1);
		}
		case 6:
		{
			SpecAbout(playerid, 2);
		}
	}
	return 1;
}

stock SpecAbout(playerid, spectype)
{
	new spec_about[2000];
	switch(spectype)
	{
		case 0://rusznikartswo
		{
			strcat(spec_about,""COL_RED"»» "COL_LIME"Przedmiot specjalizacji:"COL_RED" Zestaw narzedzi (Bron)"COL_GREY". \n");
			strcat(spec_about," \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 1"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Colt45  \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Desert Eagle \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Winchester M1866 \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Mossberg 500 \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Sawed-off shotgun \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 2"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Mac 10 Ingram \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: TEC-DC9 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 3"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: SPAS-12 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 4"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Hk MP5N \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 5"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Colt45,  \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Desert Eagle \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 6"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Winchester M1866 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 7"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Mossberg 500 \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Sawed-off shotgun \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 8"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: SPAS-12 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 9"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Mac 10 Ingram \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 10"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: TEC-DC9 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 11"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: Hk MP5N \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 12"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: AK-47 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 13"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: AK-47 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 14"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: M4 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 15"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: M4 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 16"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: BAR-10 \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 17"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Naprawa: BAR-10 \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_GREEN"» "COL_GREEN"Rusznikarstwo"COL_GREY" - Szczegó³y", spec_about,"OK","");
		}
		case 1://motoryzacja
		{
			strcat(spec_about,""COL_RED"»» "COL_LIME"Przedmiot specjalizacji:"COL_RED" Zestaw narzedzi (Pojazd)"COL_GREY". \n");
			strcat(spec_about," \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 1"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Prowadzenie niezakodowanych pojazdów \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 2"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Mo¿liwoœæ zamykania/otwierania pojazdów \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 3"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Mo¿liwoœæ wykopania gracza z pojazdu \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 4"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Diagnostyka pojazdu \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 5"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Remont uk³adu elektrycznego \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 6"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Remont uk³adu zasilania \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 7"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Remont uk³adu smarowania \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 8"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Remont uk³adu ch³odzenia \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 9"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Remont uk³adu korbowego \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 10"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Mo¿liwoœæ podjêcia próby rozkodowania pojazdu \n");
			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 11"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Kodowanie pojazdu \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_GREEN"» "COL_GREEN"Motoryzacja"COL_GREY" - Szczegó³y", spec_about,"OK","");
		}
		case 2://medycyna
		{
			strcat(spec_about,""COL_RED"»» "COL_LIME"Przedmiot specjalizacji:"COL_RED" Zestaw medyczny"COL_GREY". \n");
			strcat(spec_about," \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 1"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Banda¿ \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 2"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Apteczka \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 3"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Bandaz elastyczny \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 4"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie: Duza Apteczka \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 5"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" U¿ywanie wszytkich medykamentów \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 6"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY"Leczenie 5HP \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 7"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Leczenie 10HP \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 8"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Leczenie 20HP \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 9"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Leczenie 80HP \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 10"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop Haps 10 \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 11"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop Haps 25 \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 12"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop Haps 50 \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 13"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop AntiRad 10 \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 14"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop AntiRad 25 \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 15"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop AntiRad 50 \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 16"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Tworzenie: Syrop na wytrzymalosc \n");

			strcat(spec_about,""COL_LIME"»» "COL_DBLUE"Iloœæ punktów:"COL_RED" 17"COL_GREY": \n");
			strcat(spec_about,""COL_GREY"» "COL_EASY" Mo¿liwoœæ wybudzenia gracza (jeœli nieprzytomy) \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_GREEN"» "COL_GREEN"Medycyna"COL_GREY" - Szczegó³y", spec_about,"OK","");
		}
	}
	return 1;
}
//*********************************************************************************************************************dawanie exp za exploracje
stock Process_ExpForExplore(playerid)
{
	if(gracz[playerid][explore_world_tick] > 180)
	{
		gracz[playerid][explore_world_tick] = 0;
		GiveExp(playerid, 4);
	}
	else if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetVehSpeed(GetPlayerVehicleID(playerid))) gracz[playerid][explore_world_tick]++;
	}
	else if(GetSpeedXY(playerid)) gracz[playerid][explore_world_tick]++;
	return 1;
}
//**************************************************************************************************************soundtrack
stock Process_SoundTrack(playerid)
{
	if(!gracz[playerid][loggedin]) return 1;
	if(gracz[playerid][WebReg]) return 1;
	switch(serwer[soundtrackid])
	{
		case 0:
		{
			PlayAudioStreamForPlayer(playerid, "http://127.0.0.1/sound/track/bg1.mp3");
		}
		case 1:
		{
			PlayAudioStreamForPlayer(playerid, "http://127.0.0.1/sound/track/bg2.mp3");
		}
		case 2:
		{
			PlayAudioStreamForPlayer(playerid, "http://127.0.0.1/sound/track/bg3.mp3");
		}
	}
	return 1;
}
//**************************************************************************************************************wêdkowanie
new fishtimer[MAX_PLAYERS];
stock StartFish(playerid)
{
	if(GetPVarInt(playerid, "RateFish") != 0) return LeftNotifyShow(playerid, "error", "Musisz skonczyc aktualne wedkowanie.", LN_RED);
	if(!IsPlayerInFishingPoint(playerid)) return LeftNotifyShow(playerid, "error", "W tym miejscu ~r~nie~w~ mozesz wedkowac. Znajdz ~y~molo~w~.", LN_RED);
	RemovePlayerAttachedObject(playerid,3);
	SetPlayerAttachedObject(playerid, 3,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
	TogglePlayerControllable(playerid, 0);
	SetCameraBehindPlayer(playerid);
	SetPVarInt(playerid, "RateFish", 10);
	ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1);
	//ApplyAnimation(playerid, "SAMP", "FishingIdle", 4.1, 0, 1, 1, 1, 1);
	SetTimerEx("AnimFixer", 1000, false, "d", playerid);
	fishtimer[playerid] = SetTimerEx("ProcedureFish", 2000, true, "d", playerid);
	SetPlayerArmedWeapon(playerid, 0);
	return 1;
}
forward AnimFixer(playerid);
public AnimFixer(playerid)
{
	ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1);
	//ApplyAnimation(playerid, "SAMP", "FishingIdle", 4.1, 0, 1, 1, 1, 1);
}
stock IsPlayerInFishingPoint(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -2715.5703,-2209.6528,1.9654)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1365.1147,-2000.5859,1.8554)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1506.7386,-2312.7712,1.8554)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1520.9185,-2223.4324,2.4344)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -2701.3765,-2197.5000,1.2692)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1643.8407,-1682.8496,1.6915)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1241.6897,-2526.8713,1.6894)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1803.0276,-2766.0796,1.4611)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -381.9236,-1852.0017,1.9192 )) return 1;
	return 0;
}
forward ProcedureFish(playerid);
public ProcedureFish(playerid)
{
	if(GetPVarInt(playerid, "ClickFishGood") == 4)
	{
		KillTimer(fishtimer[playerid]);
		SetPVarInt(playerid, "RateFish", 0);
		SetPVarInt(playerid, "ClickFish", 0);
		SetPVarInt(playerid, "ClickFishGood", 0);
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0);
		TogglePlayerControllable(playerid, 1);
		RemovePlayerAttachedObject(playerid,3);
		ClearAnimations(playerid, 1);
		CreateItemForPlayer(playerid, 80, 1);
		GiveExp(playerid, 1);
		LeftNotifyShow(playerid, "Sukces!", "~g~Gratulacje!~w~ Zlowiles rybe!", LN_GREEN);
		PC_EmulateCommand(playerid, "/me z³owi³/a rybê.");
		return 1;
	}
	if(GetPVarInt(playerid, "RateFish") == 0)
	{
		KillTimer(fishtimer[playerid]);
		LeftNotifyShow(playerid, "info", "Polow ryb ~r~zakonczony~w~. Ryba ~r~nie~w~ polknela haczyka.");
		SetPVarInt(playerid, "RateFish", 0);
		SetPVarInt(playerid, "ClickFish", 0);
		SetPVarInt(playerid, "ClickFishGood", 0);
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0);
		TogglePlayerControllable(playerid, 1);
		RemovePlayerAttachedObject(playerid,3);
		ClearAnimations(playerid, 1);
		return 1;
	}
	new fstr[64];
	format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
	SetPVarInt(playerid, "ClickFish", 0);
	if(GetPVarInt(playerid, "RateFish") < 9)
	{
		switch(random(5)+1)
		{
			case 1:
			{
				SetPVarInt(playerid, "ClickFish", 1);
				format(fstr, sizeof(fstr), "~r~WCISNIJ: ~y~LPM~w~!");
				SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			}
			case 2:
			{
				SetPVarInt(playerid, "ClickFish", 0);
				format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			}
			case 3:
			{
				SetPVarInt(playerid, "ClickFish", 2);
				format(fstr, sizeof(fstr), "~r~WCISNIJ: ~y~PPM~w~!");
				SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			}
			case 4:
			{
				SetPVarInt(playerid, "ClickFish", 0);
				format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			}
		}
	}
	if(GetPVarInt(playerid, "RateFish") > 10)
	{
		format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
		SetPVarInt(playerid, "ClickFish", 0);
	}
	GameTextForPlayer(playerid, fstr,1000,5);
	SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")-1);
	return 1;
}
stock FISHSYS_OnPlayerKeyStateChange(playerid, newkeys)
{
	if(GetPVarInt(playerid, "RateFish") == 0) return 1;
	if(newkeys == KEY_FIRE)//LPM
	{
		if(GetPVarInt(playerid, "ClickFish") == 1)
		{
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", GetPVarInt(playerid, "ClickFishGood")+1);
			SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			new fstr[64];
			format(fstr, sizeof(fstr), "~g~DOBRZE! - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			GameTextForPlayer(playerid, fstr,1111,5);
		} 
		else 
		{
			KillTimer(fishtimer[playerid]);
			SetPVarInt(playerid, "RateFish", 0);
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", 0);
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0);
			RemovePlayerAttachedObject(playerid,3);
			TogglePlayerControllable(playerid, 1);
			ClearAnimations(playerid, 1);
			LeftNotifyShow(playerid, "error", "Lowienie ryb ~r~przerwane~w~. ~r~Niepoprawny~w~ przycisk wcisnales.");
		}
	}
	if(GetPVarInt(playerid, "ClickFish") == 0) return 1;
	if(newkeys == 128)//PPM
	{
		if(GetPVarInt(playerid, "ClickFish") == 2)
		{
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", GetPVarInt(playerid, "ClickFishGood")+1);
			SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			new fstr[64];
			format(fstr, sizeof(fstr), "~g~DOBRZE! - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			GameTextForPlayer(playerid, fstr,1111,5);
		} 
		else 
		{
			KillTimer(fishtimer[playerid]);
			SetPVarInt(playerid, "RateFish", 0);
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", 0);
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0);
			RemovePlayerAttachedObject(playerid,3);
			TogglePlayerControllable(playerid, 1);
			SetPVarInt(playerid, "ClickFish", 0);
			ClearAnimations(playerid, 1);
			LeftNotifyShow(playerid, "error", "Lowienie ryb ~r~przerwane~w~. ~r~Niepoprawny~w~ przycisk wcisnales.");
		}
	}
	return 1;
}
//*******************************************************************************ANTY LEAVE
stock AntyLeaverRun(playerid)
{
	if(gracz[playerid][PGodz] >= 3)
	{
		if(gracz[playerid][anty_leave_time] < serwer[time_timestamp])
		{
			LeftNotifyShow(playerid, "info", "~r~Uwaga~w~! Jestes w trakcie walki. Jesli ~y~opuscisz serwer~w~, zanim czas na gorze ekranu dobiegnie konca, Twoje ~y~przedmioty zostana rozsypane na ziemie~w~!", LN_RED, 15);
		}
		gracz[playerid][anty_leave_time] = serwer[time_timestamp]+15;
	}
	return 1;
}