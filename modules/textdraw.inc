#define COLOR_HUD 0x646464FF
#include "modules/textdraw_static.inc"
#include "modules/textdraw_dynamic.inc"


stock Init_TextDrawGlobal()
{
	Init_TextDrawGlobalDynamic();
	Init_TextDrawGlobalStatic();
	return 1;
}

stock Init_TextDrawPlayer(playerid)
{
	Init_TextDrawPlayerStatic(playerid);
	Init_TextDrawPlayerDynamic(playerid);
	fb_LoadPlayerTextDraws(playerid);
	return 1;
}

stock ShowHud(playerid)
{
	format(temp_string, 128, "%s", nick(playerid));
	PlayerTextDrawSetString(playerid, td_player_hud0[playerid], temp_string);
	format(temp_string, 128, "%01dh, %01dm, %01ds", gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][PSek]);
	PlayerTextDrawSetString(playerid, td_player_hud2[playerid], temp_string);
	TextDrawShowForPlayer(playerid, td_hud0);
	TextDrawShowForPlayer(playerid, td_hud1);
	TextDrawShowForPlayer(playerid, td_hud2);
	TextDrawShowForPlayer(playerid, td_hud3);
	TextDrawShowForPlayer(playerid, td_hud4);
	TextDrawShowForPlayer(playerid, td_hud5);
	TextDrawShowForPlayer(playerid, td_hud6);
	TextDrawShowForPlayer(playerid, td_hud7);
	TextDrawShowForPlayer(playerid, td_hud8);
	TextDrawShowForPlayer(playerid, td_hud9);
	TextDrawShowForPlayer(playerid, td_hud10);
	TextDrawShowForPlayer(playerid, td_hud11);
	TextDrawShowForPlayer(playerid, td_hud12);
	TextDrawShowForPlayer(playerid, td_hud13);
	TextDrawShowForPlayer(playerid, td_hud14);
	TextDrawShowForPlayer(playerid, td_hud15);
	TextDrawShowForPlayer(playerid, td_hud16);
	TextDrawShowForPlayer(playerid, td_hud17);
	TextDrawShowForPlayer(playerid, td_hud18);
	TextDrawShowForPlayer(playerid, td_hud19);
	TextDrawShowForPlayer(playerid, td_hud20);
	TextDrawShowForPlayer(playerid, td_hud21);
	TextDrawShowForPlayer(playerid, td_hud22);
	TextDrawShowForPlayer(playerid, td_hud23);
	TextDrawShowForPlayer(playerid, td_hud24);
	TextDrawShowForPlayer(playerid, td_hud25);
	TextDrawShowForPlayer(playerid, td_hud26);
	TextDrawShowForPlayer(playerid, td_hud27);
	TextDrawShowForPlayer(playerid, model_hud1);
	TextDrawShowForPlayer(playerid, model_hud2);
	TextDrawShowForPlayer(playerid, model_hud3);
	TextDrawShowForPlayer(playerid, model_hud4);
	TextDrawShowForPlayer(playerid, model_hud5);
	TextDrawShowForPlayer(playerid, model_hud6);
	TextDrawShowForPlayer(playerid, model_hud7);
	TextDrawShowForPlayer(playerid, model_hud8);
	HideMinimap(playerid);
	if(GetPlayerWeapon(playerid))
	{
		PlayerTextDrawSetPreviewModel(playerid, weapon_model[playerid], GetPlayerWeapon(playerid));
		PlayerTextDrawShow(playerid, weapon_model[playerid]);
	}
	else
	{
		PlayerTextDrawShow(playerid, td_fist[playerid]);
	}
	PlayerTextDrawShow(playerid, td_player_hud0[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud1[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud2[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud3[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud4[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud5[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud6[playerid]);
	PlayerTextDrawShow(playerid, td_player_hud7[playerid]);
	PlayerTextDrawShow(playerid, td_halas0[playerid]);
	ShowPlayerProgressBar(playerid, hp_bar[playerid]);
	ShowPlayerProgressBar(playerid, cdn_bar[playerid]);
	ShowPlayerProgressBar(playerid, glod_bar[playerid]);
	ShowPlayerProgressBar(playerid, prag_bar[playerid]);
	ShowPlayerProgressBar(playerid, rad_bar[playerid]);
	return 1;
}

//Dolny pasek
stock PasekDol(tekst[])
{
	format(serwer[pasek_dol], 256, tekst);
	TextDrawSetString(td_hud24, serwer[pasek_dol]);
	return 1;
}

stock Process_RefreshHud(playerid)
{
	format(temp_string, 128, "%01dh, %01dm, %01ds", gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][PSek]);
	PlayerTextDrawSetString(playerid, td_player_hud2[playerid], temp_string);
	gracz[playerid][hud_showexp]++;
	if(gracz[playerid][hud_showexp] < 5)
	{
		format(temp_string, 128, "Poziom: ~y~%d", gracz[playerid][level]);
	}
	else
	{
		Process_Exp(playerid);
		format(temp_string, 128, "~p~EXP: ~g~%d~p~/~r~%d", gracz[playerid][exp], gracz[playerid][need_exp]);
		if(gracz[playerid][hud_showexp] > 9)
		{
			gracz[playerid][hud_showexp] = 0;
		}
	}
	PlayerTextDrawSetString(playerid, td_player_hud3[playerid], temp_string);
	format(temp_string, 128, "%05d", gracz[playerid][gold]);
	PlayerTextDrawSetString(playerid, td_player_hud6[playerid], temp_string);
	format(temp_string, 128, "%05d", gracz[playerid][zetony]);
	PlayerTextDrawSetString(playerid, td_player_hud5[playerid], temp_string);
	if(gracz[playerid][OrgID])
	{
		format(temp_string, 128, "%s", gracz[playerid][group_tag]);
		PlayerTextDrawSetString(playerid, td_player_hud4[playerid], temp_string);
	}
	else
	{
		format(temp_string, 128, "BRAK GRUPY");
		PlayerTextDrawSetString(playerid, td_player_hud4[playerid], temp_string);
	}
	return 1;
}

stock RefreshAmmo(playerid)
{
	if(gracz[playerid][actual_weapon])
	{
		format(temp_string, 64, "~y~%d ~w~- ~p~CDN:  %d%%", ammo[playerid][gracz[playerid][actual_weapon]], procent(w_cdn[playerid][gracz[playerid][actual_weapon]], w_cdn_max[playerid][gracz[playerid][actual_weapon]]));
		PlayerTextDrawSetString(playerid, td_player_hud1[playerid], temp_string);
		PlayerTextDrawShow(playerid, td_player_hud1[playerid]);
	}
	else
	{
		PlayerTextDrawSetString(playerid, td_player_hud1[playerid], "_");
		PlayerTextDrawShow(playerid, td_player_hud1[playerid]);
	}
	return 1;
}

stock SetBarHP(playerid, hp) return SetPlayerProgressBarValue(playerid, hp_bar[playerid], float(hp));
stock SetBarCDN(playerid, cdn) return SetPlayerProgressBarValue(playerid, cdn_bar[playerid], float(cdn));
stock SetBarGlod(playerid, glod) return SetPlayerProgressBarValue(playerid, glod_bar[playerid], float(glod));
stock SetBarPragn(playerid, pragnienie) return SetPlayerProgressBarValue(playerid, prag_bar[playerid], float(pragnienie));
stock SetBarRads(playerid, rad) return SetPlayerProgressBarValue(playerid, rad_bar[playerid], float(rad));
stock SetTempStatus(playerid, temp_value[]) return PlayerTextDrawSetString(playerid, td_player_hud7[playerid], temp_value);

stock SetInterwencjaTD(tekst[]) return TextDrawSetString(interwencja_td, tekst);

stock NapisySet(playerid, napis[]) 
{
	PlayerTextDrawSetString(playerid, napisy[playerid], napis);
	PlayerTextDrawShow(playerid, napisy[playerid]);
	return 1;
}

stock HideMinimap(playerid)
{
	TextDrawShowForPlayer(playerid, HideMap);
	TextDrawShowForPlayer(playerid, HideMap1);
	TextDrawShowForPlayer(playerid, HideMap2);
	return 1;
}

stock ShowMinimap(playerid)
{
	TextDrawHideForPlayer(playerid, HideMap);
	TextDrawHideForPlayer(playerid, HideMap1);
	TextDrawHideForPlayer(playerid, HideMap2);
	return 1;
}

stock ShowTDShoot(playerid)
{
	if(gracz[playerid][td_shoot_type])
	{
		TextDrawHideForPlayer(playerid, td_shoot1);
		TextDrawShowForPlayer(playerid, td_shoot0);
		gracz[playerid][td_shoot_type] = false;
	}
	else
	{
		TextDrawHideForPlayer(playerid, td_shoot0);
		TextDrawShowForPlayer(playerid, td_shoot1);
		gracz[playerid][td_shoot_type] = true;
	}
	gracz[playerid][shoot_td_time] = serwer[time_timestamp]+1; 
	return 1;
}

stock Process_TDShoot(playerid)
{
	if(gracz[playerid][shoot_td_time] != 0)
	{
		if(gracz[playerid][shoot_td_time] < serwer[time_timestamp])
		{
			TextDrawHideForPlayer(playerid, td_shoot0);
			TextDrawHideForPlayer(playerid, td_shoot1);
			gracz[playerid][shoot_td_time] = 0;
		}
	}
	return 1;
}

stock ShowExpWindow(playerid, exp_val = 1, exp_val_premium = 0)
{
	TextDrawShowForPlayer(playerid, td_exp_box);
	TextDrawShowForPlayer(playerid, td_exp_title);
	new str[128];
	if(exp_val_premium > 0)
	{
		format(str, 128, "~p~EXP: ~w~+%d~y~ (+%d)~n~~g~%d~p~/~r~%d", exp_val, exp_val_premium, gracz[playerid][exp], gracz[playerid][need_exp]);
	}
	else
	{
		format(str, 128, "~p~EXP: ~w~+%d~n~~g~%d~p~/~r~%d", exp_val, gracz[playerid][exp], gracz[playerid][need_exp]);
	}
	PlayerTextDrawSetString(playerid, td_exp_content[playerid], str);
	PlayerTextDrawShow(playerid, td_exp_content[playerid]);
	gracz[playerid][time_expwindow] = serwer[time_timestamp]+7;
	return 1;
}

stock Process_ExpWindow(playerid)
{
	if(gracz[playerid][time_expwindow] != 0)
	{
		if(gracz[playerid][time_expwindow] < serwer[time_timestamp])
		{
			gracz[playerid][time_expwindow] = 0;
			TextDrawHideForPlayer(playerid, td_exp_box);
			TextDrawHideForPlayer(playerid, td_exp_title);
			PlayerTextDrawHide(playerid, td_exp_levelup[playerid]);
			PlayerTextDrawHide(playerid, td_exp_content[playerid]);
			PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}



stock LeftNotifyShow(playerid, title[], content[], type = LN_GREY, time = 5)
{
	switch(type)
	{
		case LN_RED://red//error/misja
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], -2147483393);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -2147483393);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "!");
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		case LN_GREEN://green//info/sukcesy
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], 8388863);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], 8388863);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 1);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "i");
			PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
		}
		case LN_YELLOW://yellow
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], -65281);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -65281);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
		}
		case LN_GREY://grey/ogólno dostepny
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], -2139062017);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -2139062017);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "!");
			PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		}
		case LN_BLUE:
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], 0x09a4d1FF);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], 0x09a4d1FF);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "!");
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
	}
	new str[512];
	format(str, 512, "%s", title);
	PlayerTextDrawSetString(playerid,  td_leftann_title[playerid], str);
	format(str, 512, "~n~%s", content);
	PlayerTextDrawSetString(playerid,  td_leftann_content[playerid], str);
	PlayerTextDrawShow(playerid, td_leftann_title[playerid]);
	PlayerTextDrawShow(playerid, td_leftann_content[playerid]);
	PlayerTextDrawShow(playerid, td_leftann_ball[playerid]);
	PlayerTextDrawShow(playerid, td_leftann_icon[playerid]);
	if(time) gracz[playerid][time_leftnotify] = serwer[time_timestamp]+time;	
	else gracz[playerid][time_leftnotify] = 0;
	return 1;
}

stock LeftNotifyHide(playerid)
{
	PlayerTextDrawHide(playerid, td_leftann_title[playerid]);
	PlayerTextDrawHide(playerid, td_leftann_content[playerid]);
	PlayerTextDrawHide(playerid, td_leftann_ball[playerid]);
	PlayerTextDrawHide(playerid, td_leftann_icon[playerid]);	
	return 1;
}

stock Process_LeftNotify(playerid)
{
	if(gracz[playerid][time_leftnotify] != 0)
	{
		if(gracz[playerid][time_leftnotify] < serwer[time_timestamp])
		{
			gracz[playerid][time_leftnotify] = 0;
			LeftNotifyHide(playerid);
			//if(IsPlayerQuest(playerid)) LeftNotifyShow(playerid, "Misja", quest[gracz[playerid][q_id]][q_opis], LN_BLUE, 0);
		}
	}
	return 1;
}

stock ShowPanorama(playerid)
{
	PlayerTextDrawShow(playerid, td_panorama0[playerid]);
	PlayerTextDrawShow(playerid, td_panorama1[playerid]);
	return 1;
}

stock HidePanorama(playerid)
{
	PlayerTextDrawHide(playerid, td_panorama0[playerid]);
	PlayerTextDrawHide(playerid, td_panorama1[playerid]);
	return 1;
}

stock CombineTD_Title(playerid, title[])
{
	PlayerTextDrawSetString(playerid, tdCombine1[playerid], title);
	return 1;
}

stock CombineTD_Left(playerid, left[])
{
	PlayerTextDrawSetString(playerid, tdCombine3[playerid], left);
	return 1;
}

stock CombineTD_Right(playerid, right[])
{

	PlayerTextDrawSetString(playerid, tdCombine4[playerid], right);
	return 1;
}

stock CombineTD_Beside(playerid, beside[])
{
	PlayerTextDrawSetString(playerid, tdCombine8[playerid], beside);
	return 1;
}

stock CombineTD_Tip(playerid, tip[])
{
	PlayerTextDrawSetString(playerid, tdCombine2[playerid], tip);
	return 1;
}

stock CombineTD_Combine(playerid, combine[])
{
	PlayerTextDrawSetString(playerid, tdCombine7[playerid], combine);
	return 1;
}

stock ShowCombineTD(playerid)
{
	PlayerTextDrawShow(playerid, tdCombine0[playerid]);
	PlayerTextDrawShow(playerid, tdCombine1[playerid]);
	PlayerTextDrawShow(playerid, tdCombine2[playerid]);
	PlayerTextDrawShow(playerid, tdCombine3[playerid]);
	PlayerTextDrawShow(playerid, tdCombine4[playerid]);
	PlayerTextDrawShow(playerid, tdCombine5[playerid]);
	PlayerTextDrawShow(playerid, tdCombine6[playerid]);
	PlayerTextDrawShow(playerid, tdCombine7[playerid]);
	PlayerTextDrawShow(playerid, tdCombine8[playerid]);
	return 1;
}

stock HideCombineTD(playerid)
{
	PlayerTextDrawHide(playerid, tdCombine0[playerid]);
	PlayerTextDrawHide(playerid, tdCombine1[playerid]);
	PlayerTextDrawHide(playerid, tdCombine2[playerid]);
	PlayerTextDrawHide(playerid, tdCombine3[playerid]);
	PlayerTextDrawHide(playerid, tdCombine4[playerid]);
	PlayerTextDrawHide(playerid, tdCombine5[playerid]);
	PlayerTextDrawHide(playerid, tdCombine6[playerid]);
	PlayerTextDrawHide(playerid, tdCombine7[playerid]);
	PlayerTextDrawHide(playerid, tdCombine8[playerid]);
	return 1;
}

stock VehHUD_VehName(playerid, vehname[])
{
	new str[24];
	format(str, 24, "%s", vehname);
	PlayerTextDrawSetString(playerid, tdVehHUD3[playerid], str);
	return 1;
}

stock VehHUD_Speed(playerid, speed)
{
	new str[16];
	format(str, 16, "%03d km/h", speed);
	PlayerTextDrawSetString(playerid, tdVehHUD5[playerid], str);
	return 1;
}

new VehHUD_cache_info[MAX_PLAYERS][3];
stock VehHUD_VehModel(playerid, model, color)
{
	if(VehHUD_cache_info[playerid][0] != model)
	{
		PlayerTextDrawSetPreviewModel(playerid, tdVehHUD14[playerid], model);
		VehHUD_cache_info[playerid][0] = model;
		VehHUD_cache_info[playerid][2] = 1;
	}
	if(VehHUD_cache_info[playerid][1] != color)
	{
		PlayerTextDrawSetPreviewVehCol(playerid, tdVehHUD14[playerid], color, color);
		VehHUD_cache_info[playerid][1] = color;
		VehHUD_cache_info[playerid][2] = 1;
	}
	return 1;
}

stock VehHUD_Fuel(playerid, fuel_val)
{
	SetPlayerProgressBarValue(playerid, fuel_bar[playerid], float(fuel_val));
	return 1;
}

stock VehHUD_Temp(playerid, temp_val)
{
	switch(temp_val)
	{
		case 0..33:
		{
			SetPlayerProgressBarColor(playerid, temp_bar[playerid], 0x1f9c5aFF);
		}
		case 34..66:
		{
			SetPlayerProgressBarColor(playerid, temp_bar[playerid], 0xebb73dFF);
		}
		case 67..100:
		{
			SetPlayerProgressBarColor(playerid, temp_bar[playerid], 0x9b300eFF);
		}
		
	}
	SetPlayerProgressBarValue(playerid, temp_bar[playerid], float(temp_val));
	return 1;
}

stock ShowVehicleHUD(playerid)
{
	PlayerTextDrawShow(playerid, tdVehHUD0[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD1[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD2[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD3[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD4[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD5[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD6[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD7[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD8[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD9[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD10[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD11[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD12[playerid]);
	PlayerTextDrawShow(playerid, tdVehHUD13[playerid]);
	if(VehHUD_cache_info[playerid][2])
	{
		PlayerTextDrawShow(playerid, tdVehHUD14[playerid]);
		VehHUD_cache_info[playerid][2] = 0;
	}
	ShowPlayerProgressBar(playerid, fuel_bar[playerid]);
	ShowPlayerProgressBar(playerid, temp_bar[playerid]);
	return 1;
}

stock HideVehicleHUD(playerid)
{
	PlayerTextDrawHide(playerid, tdVehHUD0[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD1[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD2[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD3[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD4[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD5[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD6[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD7[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD8[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD9[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD10[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD11[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD12[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD13[playerid]);
	PlayerTextDrawHide(playerid, tdVehHUD14[playerid]);
	HidePlayerProgressBar(playerid, fuel_bar[playerid]);
	HidePlayerProgressBar(playerid, temp_bar[playerid]);
	for(new r; r < 3; r++)
	{
		VehHUD_cache_info[playerid][r] = -1; 
	}
	return 1;
}
//LICZNIK GEIGERA
stock ShowGeigerTD(playerid)
{
	PlayerTextDrawShow(playerid, geiger_model[playerid]);
	PlayerTextDrawShow(playerid, td_geiger0[playerid]);
	PlayerTextDrawShow(playerid, td_geiger1[playerid]);
	PlayerTextDrawShow(playerid, td_geiger2[playerid]);
	PlayerTextDrawShow(playerid, td_geiger3[playerid]);
	PlayerTextDrawShow(playerid, td_geiger4[playerid]);
	PlayerTextDrawShow(playerid, td_geiger5[playerid]);
	PlayerTextDrawShow(playerid, td_geiger6[playerid]);
	PlayerTextDrawShow(playerid, td_geiger7[playerid]);
	return 1;
}

stock HideGeigerTD(playerid)
{
	PlayerTextDrawHide(playerid, geiger_model[playerid]);
	PlayerTextDrawHide(playerid, td_geiger0[playerid]);
	PlayerTextDrawHide(playerid, td_geiger1[playerid]);
	PlayerTextDrawHide(playerid, td_geiger2[playerid]);
	PlayerTextDrawHide(playerid, td_geiger3[playerid]);
	PlayerTextDrawHide(playerid, td_geiger4[playerid]);
	PlayerTextDrawHide(playerid, td_geiger5[playerid]);
	PlayerTextDrawHide(playerid, td_geiger6[playerid]);
	PlayerTextDrawHide(playerid, td_geiger7[playerid]);
	return 1;
}

stock Geiger_SetUREMS(playerid, urems)
{
	new urems_str[16];
	format(urems_str, 16, "%d", urems);
	PlayerTextDrawSetString(playerid, td_geiger5[playerid], urems_str);
	return 1;
}

stock Geiger_SetColorLED(playerid, color_led)
{
	PlayerTextDrawColor(playerid, td_geiger7[playerid], color_led);
	PlayerTextDrawShow(playerid, td_geiger7[playerid]);
	return 1;
}

stock TD_TopCenter(playerid, hide, str_sp[])
{
	if(hide)
	{
		PlayerTextDrawHide(playerid, td_topcenter[playerid]);
	}
	else
	{
		PlayerTextDrawSetString(playerid, td_topcenter[playerid], str_sp);
		PlayerTextDrawShow(playerid, td_topcenter[playerid]);
	}
	return 1;
}

stock Process_TextSP(playerid)
{
	new str[64];
	if(gracz[playerid][anty_leave_time] > serwer[time_timestamp])
	{
		format(str, 64, "~r~Nie opuszczaj serwera!!!~n~~y~(pozostalo: %d sekund)", gracz[playerid][anty_leave_time]-serwer[time_timestamp]);
		TD_TopCenter(playerid, 0, str);
	}
	else if(gracz[playerid][in_krypta] && !gracz[playerid][WebReg])
	{
		TD_TopCenter(playerid, 0, "~y~PvP OFF");
	}
	else if(SpawnProtect(playerid))
	{
		if(_PlayerTeleporting[playerid])
		{
			format(str, 64, "NIEZNISZCZALNY");
		}
		else if(gracz[playerid][time_spawnprotect] > serwer[time_timestamp])
		{
			new seconds = gracz[playerid][time_spawnprotect]-serwer[time_timestamp];
			format(str, 64, "NIEZNISZCZALNY~n~~b~%ds", seconds);
		}
		else
		{
			format(str, 64, "NIEZNISZCZALNY~n~~b~%ds", 30-gracz[playerid][sec_online]);
		}
		TD_TopCenter(playerid, 0, str);
	}
	else if(GetPlayerZoneType(playerid) == 1)
	{
		TD_TopCenter(playerid, 0, "~r~PvP ON~n~~y~(~r~czerwona strefa~y~)");
	}
	else if(GetPlayerZoneType(playerid) == 2)
	{
		TD_TopCenter(playerid, 0, "~r~PvG/GvG ON~n~~y~(~b~niebieska strefa~y~)");
	}
	else
	{
		TD_TopCenter(playerid, 1, "_");
	}
	return 1;
}