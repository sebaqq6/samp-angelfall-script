stock Init_Vehicles()
{
	mq_format("SELECT * FROM `pojazdy`;");
	mq_send("LoadVehFromDB");
	ManualVehicleEngineAndLights();
	return 1;
}

forward LoadVehFromDB();
public LoadVehFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new fid;
		while(i < rekordy)
		{
			fid = GetVehicleFreeID();
			pojazd[fid][v_id] = cache_get_field_content_int(i, "id");
			pojazd[fid][v_model] = cache_get_field_content_int(i, "model");

			pojazd[fid][v_X] = cache_get_field_content_float(i, "X");
			pojazd[fid][v_Y] = cache_get_field_content_float(i, "Y");
			pojazd[fid][v_Z] = cache_get_field_content_float(i, "Z");
			pojazd[fid][v_R] = cache_get_field_content_float(i, "R");

			pojazd[fid][v_temp_X] = cache_get_field_content_float(i, "temp_X");
			pojazd[fid][v_temp_Y] = cache_get_field_content_float(i, "temp_Y");
			pojazd[fid][v_temp_Z] = cache_get_field_content_float(i, "temp_Z");
			pojazd[fid][v_temp_R] = cache_get_field_content_float(i, "temp_R");

			pojazd[fid][v_uZasilania] = cache_get_field_content_int(i, "uZasilania");
			pojazd[fid][v_uSmarowania] = cache_get_field_content_int(i, "uSmarowania");
			pojazd[fid][v_uChlodzenia] = cache_get_field_content_int(i, "uChlodzenia");
			pojazd[fid][v_uElektryczny] = cache_get_field_content_int(i, "uElektryczny");
			pojazd[fid][v_uKorbowy] = cache_get_field_content_int(i, "uKorbowy");
			pojazd[fid][v_paliwo] = cache_get_field_content_int(i, "paliwo");
			pojazd[fid][v_color] = cache_get_field_content_int(i, "color");
			cache_get_field_content(i, "combine", pojazd[fid][v_combine], MySQL, 32);

			pojazd[fid][v_vehicleid] = CreateVehicle(pojazd[fid][v_model], pojazd[fid][v_temp_X], pojazd[fid][v_temp_Y], pojazd[fid][v_temp_Z], pojazd[fid][v_temp_R], pojazd[fid][v_color], pojazd[fid][v_color], -1);
			ToggleEngine(fid, 0);
			i++;
		}
		printf("[LOAD]Zaladowano %d pojazdow.", i);
	}
	return 1;
}

stock GetVehicleFreeID()
{
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(!pojazd[v][v_id]) return v;
	}
	return 0;
}



CMD:vehdebug(playerid, params[])
{
	if(gracz[playerid][AdminLevel] < 4) return 0;
	new zmienna, wartosc;
	if(sscanf(params,"dd", zmienna, wartosc)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /vehdebug [zmiennaid] [wartosc]");
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
		{
			switch(zmienna)
			{
				case 0:
				{
					pojazd[v][v_uZasilania] = wartosc;
				}
				case 1:
				{
					pojazd[v][v_uSmarowania] = wartosc;
				}
				case 2:
				{
					pojazd[v][v_uChlodzenia] = wartosc;
				}
				case 3:
				{
					pojazd[v][v_uElektryczny] = wartosc;
				}
				case 4:
				{
					pojazd[v][v_uKorbowy] = wartosc;
				}
				case 5:
				{
					pojazd[v][v_paliwo] = wartosc;
				}
				case 999:
				{
					pojazd[v][v_uZasilania] = wartosc;
					pojazd[v][v_uSmarowania] = wartosc;
					pojazd[v][v_uChlodzenia] = wartosc;
					pojazd[v][v_uElektryczny] = wartosc;
					pojazd[v][v_uKorbowy] = wartosc;
					pojazd[v][v_paliwo] = wartosc;
				}
			}
		}
	}
	return 1;
}

stock Process_Vehicle()
{
	static saved;
	saved = 0;
	new Float:veh_hp;
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(pojazd[v][v_id]) 
		{
			if(pojazd[v][v_paliwo] > 1000)
			{
				pojazd[v][v_paliwo] = 1000;
			}
			if(pojazd[v][v_enginestatus])
			{
				//zu¿ywanie pojazdu...
				if(pojazd[v][v_paliwo] > 1)
				{
					pojazd[v][v_paliwo] -= 1;
				}
				else
				{
					pojazd[v][v_paliwo] = 0;
				}
				if(pojazd[v][v_uZasilania])
				{
					pojazd[v][v_uZasilania] -= 1;
				}
				if(pojazd[v][v_uSmarowania])
				{
					pojazd[v][v_uSmarowania] -= 1;
				}
				if(pojazd[v][v_uChlodzenia])
				{
					pojazd[v][v_uChlodzenia] -= 1;
				}
				if(pojazd[v][v_uElektryczny])
				{
					pojazd[v][v_uElektryczny] -= 1;
				}
				if(pojazd[v][v_uKorbowy])
				{
					pojazd[v][v_uKorbowy] -= 1;
				}
				if(pojazd[v][v_temp_engine] < 100)
				{
					if(!pojazd[v][v_uChlodzenia])
					{
						pojazd[v][v_temp_engine] += 2;
					}
					else if(!pojazd[v][v_uSmarowania])
					{
						pojazd[v][v_temp_engine] += 5;
					}
					else if(!pojazd[v][v_uSmarowania] && !pojazd[v][v_uChlodzenia])
					{
						pojazd[v][v_temp_engine] += 10;
					}
					else if(pojazd[v][v_temp_engine] < 52)
					{
						pojazd[v][v_temp_engine] += 1;
					}
				}
				//gdy zasoby siê zu¿yj¹, to...
				if(!pojazd[v][v_uZasilania] || !pojazd[v][v_uElektryczny] || !pojazd[v][v_uKorbowy])
				{
					ToggleEngine(v, 0);
				}
				else if(!pojazd[v][v_paliwo])//brak paliwa
				{
					ToggleEngine(v, 0);
				}
				else if(pojazd[v][v_temp_engine] >= 100)//przegrzanie
				{
					pojazd[v][v_uKorbowy] = 0;
					ToggleEngine(v, 0);
				}
			}
			else//gdy zgaszony
			{
				if(pojazd[v][v_temp_engine])
				{
					pojazd[v][v_temp_engine] -= 1;
				}
			}
			//
			if(pojazd[v][v_idletime] < serwer[time_timestamp])
			{
				if(GetVehicleDistanceFromPoint(pojazd[v][v_vehicleid], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]) > 9.0)
				{
					SetVehiclePos(pojazd[v][v_vehicleid], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]);
					SetVehicleZAngle(pojazd[v][v_vehicleid], pojazd[v][v_temp_R]); 
				}
			}
			else
			{
				GetVehiclePos(pojazd[v][v_vehicleid], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]);
				GetVehicleZAngle(pojazd[v][v_vehicleid], pojazd[v][v_temp_R]);
			}
			//destroy detect...
			GetVehicleHealth(pojazd[v][v_vehicleid], veh_hp);
			if(pojazd[v][v_temp_Z] > 1.0)
			{
				if(veh_hp <= 655.0)
				{
					if(pojazd[v][v_autoflip] > serwer[time_timestamp])
					{
						new Float:A;
						GetVehicleZAngle(pojazd[v][v_vehicleid], A);
						SetVehicleZAngle(pojazd[v][v_vehicleid], A);
						pojazd[v][v_uZasilania] = 0;
						pojazd[v][v_uSmarowania] = 0;
						pojazd[v][v_uChlodzenia] = 0;
						pojazd[v][v_uElektryczny] = 0;
						pojazd[v][v_uKorbowy] = 0;
						ToggleEngine(v, 0);
					}
					if(veh_hp < 300.0)
					{
						pojazd[v][v_autoflip] = serwer[time_timestamp]+3;
					}
					if(pojazd[v][v_uChlodzenia] && pojazd[v][v_uSmarowania])
					{
						SetVehicleHealth(pojazd[v][v_vehicleid], 1000.0);
					}
					else
					{
						SetVehicleHealth(pojazd[v][v_vehicleid], 555.0);
					}
				}
				else if(!pojazd[v][v_uChlodzenia] || !pojazd[v][v_uSmarowania])
				{
					SetVehicleHealth(pojazd[v][v_vehicleid], 555.0);
				}
				UpdateVehicleDamageStatus(pojazd[v][v_vehicleid], 0, 0, 0, 0);
			}
			if(!IsVehicleInUse(pojazd[v][v_vehicleid]))
			{
				if(pojazd[v][v_door])
				{
					ToggleVDoors(v, 0);
				}
			}
			if(pojazdy_save_timer < serwer[time_timestamp])
			{
				new pojazd_query[1500];
				format(pojazd_query, 1500, "UPDATE `pojazdy` SET ");
				format(pojazd_query, 1500, "%s`temp_X`='%f', ", pojazd_query, pojazd[v][v_temp_X]);
				format(pojazd_query, 1500, "%s`temp_Y`='%f', ", pojazd_query, pojazd[v][v_temp_Y]);
				format(pojazd_query, 1500, "%s`temp_Z`='%f', ", pojazd_query, pojazd[v][v_temp_Z]);
				format(pojazd_query, 1500, "%s`temp_R`='%f', ", pojazd_query, pojazd[v][v_temp_R]);
				format(pojazd_query, 1500, "%s`uZasilania`='%d', ", pojazd_query, pojazd[v][v_uZasilania]);
				format(pojazd_query, 1500, "%s`uSmarowania`='%d', ", pojazd_query, pojazd[v][v_uSmarowania]);
				format(pojazd_query, 1500, "%s`uChlodzenia`='%d', ", pojazd_query, pojazd[v][v_uChlodzenia]);
				format(pojazd_query, 1500, "%s`uElektryczny`='%d', ", pojazd_query, pojazd[v][v_uElektryczny]);
				format(pojazd_query, 1500, "%s`uKorbowy`='%d', ", pojazd_query, pojazd[v][v_uKorbowy]);
				format(pojazd_query, 1500, "%s`paliwo`='%d' ", pojazd_query, pojazd[v][v_paliwo]);
				format(pojazd_query, 1500, "%sWHERE `id`='%d';", pojazd_query, pojazd[v][v_id]);
				mq_format(pojazd_query);
				mq_send("UpdateVehData");
				saved = 1;
			}
		}
	}
	if(saved == 1) pojazdy_save_timer = serwer[time_timestamp]+5;
	return 1;
}

stock Process_PlayerVehicle(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		SetPlayerSpeedCap(playerid, 1.0);
		for(new v; v < WORLD_VEHICLES; v++)
		{
			if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
			{
				if(pojazd[v][v_enginestatus])
				{
					VehHUD_VehName(playerid, GetVehicleName(pojazd[v][v_model]));
					VehHUD_Speed(playerid, GetVehSpeed(pojazd[v][v_vehicleid]));
					VehHUD_VehModel(playerid, pojazd[v][v_model], pojazd[v][v_color]);
					VehHUD_Fuel(playerid, pojazd[v][v_paliwo]);
					VehHUD_Temp(playerid, pojazd[v][v_temp_engine]);
					ShowVehicleHUD(playerid);
					GetVehiclePos(pojazd[v][v_vehicleid], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]);
					GetVehicleZAngle(pojazd[v][v_vehicleid], pojazd[v][v_temp_R]);
					pojazd[v][v_idletime] = serwer[time_timestamp]+5;
				}
				else
				{
					HideVehicleHUD(playerid);
				}
			}
		}
	}
	else
	{
		SetPlayerSpeedCap(playerid, 0.150);
	}
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(pojazd[v][v_vehicleid] == vehicleid)
		{
			if(pojazd[v][v_antyspam_destroy] > serwer[time_timestamp]) continue;
			pojazd[v][v_antyspam_destroy] = serwer[time_timestamp]+15;
			ToggleEngine(v, 0);
			ToggleVDoors(v, 0);
			DestroyVehicle(pojazd[v][v_vehicleid]);
			pojazd[v][v_temp_X] = pojazd[v][v_X];
			pojazd[v][v_temp_Y] = pojazd[v][v_Y];
			pojazd[v][v_temp_Z] = pojazd[v][v_Z];
			pojazd[v][v_temp_R] = pojazd[v][v_R];
			pojazd[v][v_uZasilania] = 0;
			pojazd[v][v_uSmarowania] = 0;
			pojazd[v][v_uChlodzenia] = 0;
			pojazd[v][v_uElektryczny] = 0;
			pojazd[v][v_uKorbowy] = 0;
			pojazd[v][v_paliwo] = 0;
			SetVehicleColor(v, 252);
			SetVehicleCombine(v, 1, 1, 1, 1, 1, 1);
			pojazd[v][v_vehicleid] = CreateVehicle(pojazd[v][v_model], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z], pojazd[v][v_temp_R], pojazd[v][v_color], pojazd[v][v_color], -1);
			break;
		}
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	HideVehicleHUD(playerid);
	StopCombineMode(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		for(new v; v < WORLD_VEHICLES; v++)
		{
			if(vehicleid == pojazd[v][v_vehicleid])
			{
				if(pojazd[v][v_door])
				{
					ToggleVDoors(v, 0);
					LeftNotifyShow(playerid, "info", "~y~Drzwi pojazdu~w~ zostaly automatycznie ~g~otwarte~w~.");
				}
			}
		}
	}
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	/*if(GetVehicleDistanceFromPoint(vehicleid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]) > 16.0)
	{
		if(!gracz[playerid][AdminLevel]) Ban_Time(-1, playerid, "Wsiadanie na odleglosc - cheat.", 1095);
	}*/
	SetPlayerArmedWeapon(playerid, 0);
	return 1;
}


stock ToggleEngine(world_vehicleid, toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	for(new v; v < MAX_VEHICLES; v++)
	{
		if(v == pojazd[world_vehicleid][v_vehicleid])
		{
			GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(v, toggle, lights, alarm, doors, bonnet, boot, objective);
			pojazd[world_vehicleid][v_enginestatus] = toggle;
			break;
		}
	}
	return 1;
}

stock EngineStatus(vehicleid)
{
	static engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return engine;
}

stock ToggleVDoors(world_vehicleid, toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	for(new v; v < MAX_VEHICLES; v++)
	{
		if(v == pojazd[world_vehicleid][v_vehicleid])
		{
			GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(v, engine, lights, alarm, toggle, bonnet, boot, objective);
			pojazd[world_vehicleid][v_door] = toggle;
			break;
		}
	}
	return 1;
}


stock vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_FIRE))
	{	
		for(new v; v < WORLD_VEHICLES; v++)
		{
			if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
			{
				new str_vehmenu[512];
				format(str_vehmenu, 512, ""COL_GREY"Akcja\t"COL_GREY"Status");
				if(pojazd[v][v_enginestatus]) format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_GREEN"W³¹cz"COL_WHITE"/"COL_RED"Wy³¹cz"COL_GREY" silnik\t"COL_GREEN"W³¹czony", str_vehmenu);
				else format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_GREEN"W³¹cz"COL_WHITE"/"COL_RED"Wy³¹cz"COL_GREY" silnik\t"COL_RED"Wy³¹czony", str_vehmenu);
				if(!pojazd[v][v_door]) format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij"COL_GREY" drzwi\t"COL_GREEN"Otwarte", str_vehmenu);
				else format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij"COL_GREY" drzwi\t"COL_RED"Zamkniête", str_vehmenu);
				new passangers;
				for(new p = PlayerPoolSize(); p != -1; p--)//liczenie graczy siedz¹cych w tym pojezdzie
				{
					if(p == playerid) continue;
					if(GetPlayerState(p) != PLAYER_STATE_PASSENGER) continue;
					if(IsPlayerInVehicle(p, pojazd[v][v_vehicleid]))
					{
						passangers++;
					}
				}
				format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_RED"Wykop"COL_GREY" pasa¿era z pojazdu\t"COL_LIME"%d osób", str_vehmenu, passangers);
				new combine[6];
				sscanf(pojazd[v][v_combine], "p<|>dddddd", combine[0], combine[1], combine[2], combine[3], combine[4], combine[5]);
				if(combine[0] == 1 && combine[1] == 1 && combine[2] == 1 && combine[3] == 1 && combine[4] == 1 && combine[5] == 1)
				{
					format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_GREY"Kodowanie zap³onu\t"COL_GREEN"Odkodowany", str_vehmenu);
				}
				else
				{
					format(str_vehmenu, 512, "%s\n"COL_ORANGE"» "COL_GREY"Kodowanie zap³onu\t"COL_RED"Zakodowany", str_vehmenu);
				}
				Dialog_Show(playerid, CTRLVEHICLE, DIALOG_STYLE_TABLIST_HEADERS, ""COL_BLUE"» "COL_GREY"Panel pojazdu", str_vehmenu, "Wybierz", "Anuluj");
				break;
			}
		}
	}
	return 1;
}

Dialog:CTRLVEHICLE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			for(new v; v < WORLD_VEHICLES; v++)
			{
				if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
				{
					if(!pojazd[v][v_enginestatus])//odpalanie
					{
						if(!pojazd[v][v_paliwo]) return LeftNotifyShow(playerid, "error", "~r~Brak paliwa~w~.", LN_RED);
						if(!pojazd[v][v_uZasilania] || !pojazd[v][v_uElektryczny] || !pojazd[v][v_uKorbowy]) return LeftNotifyShow(playerid, "error", "Z tym pojazdem jest cos nie tak, powinen obejrzec go mechanik.", LN_RED);
						new combine[6];
						if(sscanf(pojazd[v][v_combine], "p<|>dddddd", combine[0], combine[1], combine[2], combine[3], combine[4], combine[5])) return Error(playerid, "B³¹d krytyczny! Nie odnaleziono kombinacji.");
						SetCombine(playerid, combine[0], combine[1], combine[2], combine[3], combine[4], combine[5]);
						SetPVarInt(playerid, "world_vehicleid", v);
						if(combine[0] == 1 && combine[1] == 1 && combine[2] == 1 && combine[3] == 1 && combine[4] == 1 && combine[5] == 1)
						{
							if(VehSkill(playerid, 1))
							{
								if(StartCombineMode(playerid, 5))
								{
									LeftNotifyShow(playerid, "info", "Pojazd ~g~nie jest zakodowany~w~. Aby ~g~uruchomic~w~ silnik wystarczy wprowadzic ~y~kombinacje~w~. W tym celu uzyj ~p~strzalek~w~ na klawiaturze.", _, 20);
								}
								else
								{
									StopCombineMode(playerid);
								}
							}
						}
						else
						{
							if(VehSkill(playerid, 10))
							{
								if(StartCombineMode(playerid, 6))
								{
									LeftNotifyShow(playerid, "info", "Pojazd jest ~r~zakodowany~w~. Aby uruchomic silnik musisz wprowadzic ~y~tajna kombinacje~w~ uzywajac ~p~strzalek~w~ na klawiaturze.", _, 20);
								}
								else
								{
									StopCombineMode(playerid);
								}
							}
						}
						break;
					}
					else//gaszenie
					{
						ToggleEngine(v, 0);
						LeftNotifyShow(playerid, "info", "Silnik zostal ~r~zgaszony~w~.");
						PC_EmulateCommand(playerid, "/me gasi silnik.");
						break;
					}
				}
			}
		}
		case 1:
		{
			if(VehSkill(playerid, 2))
			{
				for(new v; v < WORLD_VEHICLES; v++)
				{
					if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
					{
						if(pojazd[v][v_door])
						{
							ToggleVDoors(v, 0);
							LeftNotifyShow(playerid, "info", "~y~Drzwi pojazdu~w~ zostaly ~g~otwarte~w~.");
						}
						else
						{
							ToggleVDoors(v, 1);
							LeftNotifyShow(playerid, "info", "~y~Drzwi pojazdu~w~ zostaly ~r~zamkniete~w~.");
						}
						break;
					}
				}
			}
		}
		case 2:
		{
			if(VehSkill(playerid, 3))
			{
				for(new v; v < WORLD_VEHICLES; v++)
				{
					if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
					{
						new kick_passangers[512];
						format(kick_passangers, 512, "ID\tNazwa gracza");
						new any_passanger;
						for(new p = PlayerPoolSize(); p != -1; p--)
						{
							if(p == playerid) continue;
							if(GetPlayerState(p) != PLAYER_STATE_PASSENGER) continue;
							if(IsPlayerInVehicle(p, pojazd[v][v_vehicleid]))
							{
								format(kick_passangers, 512, "%s\n"COL_BLACK"%d\t"COL_GREY"%s", kick_passangers, p, nick(p));
								any_passanger++;
							}
						}
						if(any_passanger) Dialog_Show(playerid, KICKPASSG, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» Wykop"COL_GREY" gracza z pojazdu", kick_passangers, "Kopnij!", "Anuluj");
						else Dialog_Show(playerid, KICKPASSGN, DIALOG_STYLE_MSGBOX, ""COL_RED"» Wykop"COL_GREY" gracza z pojazdu", ""COL_RED"Nie wykryto"COL_GREY" pasa¿erów w Twoim pojeŸdzie.", "Zamknij", "");
						break;
					}
				}
			}
		}
		case 3:
		{
			LeftNotifyShow(playerid, "info", "Sekwencje zaplonu zmienisz za pomoca narzedzi.");
		}
	}
	return 1;
}

Dialog:KICKPASSG(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = strval(inputtext);
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(IsPlayerInVehicle(playerid, pojazd[v][v_vehicleid]))
		{
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(p == playerid) continue;
				if(GetPlayerState(p) != PLAYER_STATE_PASSENGER) continue;
				if(IsPlayerInVehicle(p, pojazd[v][v_vehicleid]))
				{
					if(targetid == p)
					{
						RemovePlayerFromVehicle(targetid);
						LeftNotifyShow(playerid, "info", "~y~Gracz~w~ zostal ~r~wykopany~w~!", LN_GREEN);
						LeftNotifyShow(targetid, "info", "Zostales ~r~wykopany~w~ z pojazdu!", LN_RED);
						break;
					}
				}
			}
			break;
		}
	}
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(pojazd[v][v_vehicleid] == vehicleid)
		{
			if(pojazd[v][v_idletime] < serwer[time_timestamp])
			{
				if(GetVehicleDistanceFromPoint(pojazd[v][v_vehicleid], new_x, new_y, new_z) > 0.8)
				{
					SetVehiclePos(pojazd[v][v_vehicleid], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]);
					SetVehicleZAngle(pojazd[v][v_vehicleid], pojazd[v][v_temp_R]); 
					return 0;
				}
			}
			else
			{
				pojazd[v][v_temp_X] = new_x;
				pojazd[v][v_temp_Y] = new_y;
				pojazd[v][v_temp_Z] = new_z;
			}
		}
	}
	return 1;
}

stock SetVehicleCombine(world_vehicleid, c1, c2, c3, c4, c5, c6)
{
	format(pojazd[world_vehicleid][v_combine], 32, "%d|%d|%d|%d|%d|%d", c1, c2, c3, c4, c5, c6);
	mq_format("UPDATE `pojazdy` SET `combine`='%s' WHERE `id`='%d';", pojazd[world_vehicleid][v_combine], pojazd[world_vehicleid][v_id]);
	mq_send("QUpdateVehComb");
	return 1;
}

stock SetVehicleColor(world_vehicleid, color)
{
	pojazd[world_vehicleid][v_color] = color;
	ChangeVehicleColor(pojazd[world_vehicleid][v_vehicleid], pojazd[world_vehicleid][v_color], pojazd[world_vehicleid][v_color]);
	mq_format("UPDATE `pojazdy` SET `color`='%d' WHERE `id`='%d';", pojazd[world_vehicleid][v_color], pojazd[world_vehicleid][v_id]);
	mq_send("QUpdateVehColor");
	return 1;
}


stock VehicleDriverID(vehicleid)
{
    for (new i = PlayerPoolSize(); i != -1;i--)
    {
        if((IsPlayerConnected(i))&&(GetPlayerVehicleID(i)==vehicleid)&&(GetPlayerState(i)==2))  return i;
    }
    return -1;
}
stock IsVehicleInUse(vehicleid) //
{
    new vdid = VehicleDriverID(vehicleid);
    if(vdid != -1)
    {
        return 1;
    }
    return 0;
}

//VehNeed
stock VehNeed_uElektryczny(veh_model)
{
	switch(veh_model)
	{
		case 468: return 2;
		case 471: return 2;
		case 495: return 15;
		case 515: return 17;
		case 428: return 10;
		case 504: return 8;
		case 424: return 6;
		case 568: return 5;
		case 418: return 8;
		case 466: return 7;
	}
	return 5;
}

stock VehNeed_uZasilania(veh_model)
{
	switch(veh_model)
	{
		case 468: return 3;
		case 471: return 2;
		case 495: return 17;
		case 515: return 20;
		case 428: return 10;
		case 504: return 10;
		case 424: return 7;
		case 568: return 6;
		case 418: return 10;
		case 466: return 8;
	}
	return 5;
}

stock VehNeed_uSmarowania(veh_model)
{
	switch(veh_model)
	{
		case 468: return 2;
		case 471: return 2;
		case 495: return 10;
		case 515: return 8;
		case 428: return 5;
		case 504: return 8;
		case 424: return 5;
		case 568: return 4;
		case 418: return 7;
		case 466: return 6;
	}
	return 5;
}

stock VehNeed_uChlodzenia(veh_model)
{
	switch(veh_model)
	{
		case 468: return 1;
		case 471: return 1;
		case 495: return 8;
		case 515: return 10;
		case 428: return 7;
		case 504: return 7;
		case 424: return 4;
		case 568: return 3;
		case 418: return 5;
		case 466: return 5;
	}
	return 5;
}

stock VehNeed_uKorbowy(veh_model)
{
	switch(veh_model)
	{
		case 468: return 2;
		case 471: return 2;
		case 495: return 10;
		case 515: return 15;
		case 428: return 8;
		case 504: return 8;
		case 424: return 5;
		case 568: return 4;
		case 418: return 6;
		case 466: return 5;
	}
	return 5;
}
