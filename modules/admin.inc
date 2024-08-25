stock Interwencja(adminid, targetid, time, kara[], reason[])
{
	serwer[interwencja_time] = gettime()+15;
	format(temp_string, 512, "~p~%s~b~~w~(~y~%d~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", kara, time, nick(targetid), gracz[adminid][master_nick], reason);
	SetInterwencjaTD(temp_string);
	TextDrawShowForAll(interwencja_td);
	return 1;
}
stock Hide_Interwencja()
{
	if(serwer[interwencja_time] > gettime()) return 1;
	SetInterwencjaTD("_");
	TextDrawHideForAll(interwencja_td);
	return 1;
}
//************************************************************************************************************************************KOMENDY
CMD:acmd(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new adminacmd[2000];
	strcat(adminacmd,""COL_RED"`"COL_EASY" - Czat adminów. "COL_GREEN"(poziomy: 1,2,3)\n");
	strcat(adminacmd,""COL_RED"/aduty"COL_EASY" - Zmiana statusu służby "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/o"COL_EASY" - Czat globalny "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/kick"COL_EASY" - Wyrzucanie gracza z serwera. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/fixplayer"COL_EASY" - Naprawa gracza(przesuwa gracza przed siebie). "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/goto"COL_EASY" - Teleportujesz się do gracza "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/get"COL_EASY" - Teleportujesz do siebie gracza "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/mute"COL_EASY" - Uciszanie gracza "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/unbw"COL_EASY" - Zdejmujesz BW "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/ip"COL_EASY" - Sprawdzanie IP gracza. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/block"COL_EASY" - Blokada postaci. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/ban"COL_EASY" - Banujesz gracza na określony czas(dni) "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/feed"COL_EASY" - Karamisz i poisz gracza "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/sethp"COL_EASY" - Ustawiasz HP "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/setweather"COL_EASY" - Ustawiesz pogodę "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"/settime"COL_EASY" - Ustawiasz godzine "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"/setvw"COL_EASY" - Ustawiasz dla gracza VirtualWorld "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"/getveh"COL_EASY" - Teleportujesz pojazd do siebie (np. jak sie zbuguje w teksturach) "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/spec"COL_EASY" - Specujesz gracza ("COL_RED"wpisz swoje ID aby zastopować specowanie"COL_EASY") (opcja także dostępna pod TAB) "COL_GREEN"(poziomy: 1,2,3) \n");
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	/*strcat(adminacmd,""COL_RED"/givegg"COL_EASY" - Nadajesz punkty GoodGame za dobrą grę RP(nie szaleć!). "COL_GREEN"(poziomy: 2,3)\n");
	strcat(adminacmd,""COL_RED"/slap"COL_EASY" - Podpicie gracza do góry + zabranie 2pkt HP. "COL_GREEN"(poziomy: 2) \n");
	strcat(adminacmd,""COL_RED"/aj"COL_EASY" - Wsadzanie gracza do AdminJail "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/spec"COL_EASY" - Obserwacja gracza. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/toggleooc"COL_EASY" - Odblokowanie/Zablokowanie globalnego czatu (/o) dla wszystkich. "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"@"COL_EASY" - Czat adminów. "COL_GREEN"(poziomy: 1,2,3)\n");*/
	ShowPlayerDialog(playerid,84520,DIALOG_STYLE_MSGBOX, "Komendy Ekipy", adminacmd, "Czaje","");
	return 1;
} 

CMD:aduty(playerid, params[])
{
	if(!gracz[playerid][AdminLevel]) return 0;
	if(gracz[playerid][admin_duty])
	{
		gracz[playerid][admin_duty] = 0;
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "[A] "COL_RED"Zszedłeś z admin duty!");
	}
	else
	{
		gracz[playerid][admin_duty] = gracz[playerid][AdminLevel];
		format(temp_string, 256, "[A] "COL_GREEN"Zalogowałeś"COL_WHITE" się na "COL_GREEN"["COL_RED"%d"COL_GREEN"]"COL_WHITE" poziom uprawnień. Lista dostępnych komend: "COL_RED"/acmd"COL_WHITE".", gracz[playerid][admin_duty]);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, temp_string);
	}
	return 1;
}

CMD:kick(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, reason[128];
	if(sscanf(params,"ds[128]", targetid, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kick [targetid] [powód]");
	if(!IsPlayerConnected(targetid) || IsPlayerNPC(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	Interwencja(playerid, targetid, 0, "Wyrzucenie", reason);
	KickEx(targetid, reason);
	return 1;
}

CMD:ban(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, reason[128], days;
	if(sscanf(params,"dds[128]", targetid, days, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /ban [targetid] [dni] [powód]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	Ban_Time(playerid, targetid, reason, days);
	return 1;
}

CMD:spec(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /spec [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	OnPlayerClickPlayer(playerid, targetid, 0);
	return 1;
}

CMD:fixplayer(playerid, params[])
{
    if(gracz[playerid][admin_duty] < 1) return 0;
    new targetid;
    if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /fixplayer [idgracza] - Przesuwa gracza przed siebie(np gdy wpadnie w textury).");
    if(!IsPlayerConnected(targetid) || IsPlayerNPC(targetid)) return Error(playerid, "Gracz nie jest połączony.");
    SetPlayerInterior(targetid, 0);
    new Float:pPos[3];
    GetXYInFrontOfPlayer(targetid, pPos[0], pPos[1], 7.0);
    MapAndreas_FindZ_For2DCoord(pPos[0], pPos[1], pPos[2]);
    SetPlayerPos(targetid, pPos[0], pPos[1], pPos[2]+1.0);
    SendClientMessageEx(playerid, -1, "Naprawiłeś gracza %s. Została został on delikatnie przesunięty do przodu(przed siebie) - jeśli nie pomogło, ponów komendę.", nick(targetid));
    return 1;
}

CMD:goto(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /goto [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	SetPlayerPos(playerid, gracz[targetid][PosX]+1, gracz[targetid][PosY]+1, gracz[targetid][PosZ]);
	return 1;
}

CMD:get(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /get [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	SetPlayerPos(targetid, gracz[playerid][PosX]+1, gracz[playerid][PosY]+1, gracz[playerid][PosZ]);
	return 1;
}

CMD:unbw(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unbw [targetid]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	DeactivateBW(targetid);
	SendClientMessageEx(playerid, -1, "Zdjąłeś BW dla gracza: "COL_BLUE"%s (%d)", nick(targetid), targetid);
	return 1;
}

CMD:ip(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /ip [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	SendClientMessageEx(playerid, -1, "IP gracza: "COL_BLUE"%s (%d)"COL_WHITE" to: "COL_RED"%s", nick(targetid), targetid, playerip(targetid));
	return 1;
}

CMD:block(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, reason[128]; 
	if(sscanf(params,"ds[128]", targetid, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /block [targetid] [powód]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	SendClientMessageEx(playerid, -1, "Zablokowałeś postać: "COL_BLUE"%s"COL_EASY" (UID: %d | Konto: %s).", nick(targetid), gracz[targetid][UID], gracz[targetid][master_nick]);
	new czas = (1025*24*60*60)+gettime();
	mq_format("INSERT INTO `BanList` (`uid`, `aid`, `time`, `time_end`, `ip_on`, `ip`, `gpci_on`, `gpci`, `reason`) VALUES ('%d', '%d', '%d', '%d', '0', '%s', '0', '%s', '%s');", gracz[targetid][UID], gracz[playerid][UID],  gettime(), czas, playerip(targetid, true), serial(targetid, true), reason);
	mq_send("QBlockChar");
	Interwencja(playerid, targetid, 0, "Blokada postaci", reason);
	KickEx(targetid, reason);
	return 1;
}


CMD:setweather(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new pogodaid;
	if(sscanf(params,"d", pogodaid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setweather [pogoda]");
	serwer[pogoda] = pogodaid;
	SendClientMessageEx(playerid, -1, "Ustawiłeś ID pogody na: "COL_GREEN"%d", serwer[pogoda]);
	return 1;
}

CMD:settime(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new godzinaid;
	if(sscanf(params,"d", godzinaid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /settime [godzina]");
	switch(godzinaid)
	{
		case 0..23:
		{
			serwer[godzina] = godzinaid;
			SendClientMessageEx(playerid, -1, "Ustawiłeś czas na: "COL_GREEN"%02d:00", serwer[godzina]);
		}
		default:
		{
			Error(playerid, "Podana godzina musi się mieścić od 0 do 23.");
		}
	}
	return 1;
}

CMD:setvw(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new targetid, vw;
	if(sscanf(params,"dd", targetid, vw)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setvw [targetid] [virtualworld;domyślny == 0]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	SetPlayerVirtualWorld(targetid, vw);
	SendClientMessageEx(playerid, -1, "Zmieniłeś VW dla gracza: "COL_BLUE"%s (%d)"COL_WHITE" na: "COL_DBLUE"%d", nick(targetid), targetid, vw);
	return 1;
}

CMD:getitem(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new itemid, count, cdn, cdn_max;
	if(sscanf(params,"dddd", itemid, count, cdn, cdn_max)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /getitem [itemid] [count] [cdn] [cdn_max]");
	CreateItemForPlayer(playerid, itemid, count, cdn, cdn_max);
	SendClientMessageEx(playerid, -1, "Próba dodania: "COL_GREEN"%s"COL_EASY"[ilosc: %d]"COL_GREEN"[kondycja: %d]"COL_EASY"[kondycja max: %d]", ItemName[itemid], count, cdn, cdn_max);
	return 1;
}

CMD:setmapper(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new targetid, lvl;
	if(sscanf(params,"dd", targetid, lvl)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setmapper [targetid] [poziom]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	gracz[targetid][MapperLvl] = lvl;
	mq_format("UPDATE`Konta` SET `MapperLvl`='%d' WHERE `id`='%d';", gracz[targetid][MapperLvl], gracz[targetid][UID]);
	mq_send("QMapper");
	SendClientMessageEx(playerid, -1, "Zmieniłeś poziom mappera dla gracza: "COL_BLUE"%s (%d)"COL_WHITE" na: "COL_DBLUE"%d", nick(targetid), targetid, lvl);
	return 1;
}

CMD:mute(playerid, params[])
{
    if(gracz[playerid][admin_duty] < 1) return 0;
    new targetid, minutes, reason[128];
    if(sscanf(params,"dds[128]", targetid, minutes, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /mute [targetid] [minuty] [powód]");
    if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
    if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
    gracz[targetid][muted_timestamp] = 60*minutes+gettime();
    mq_format("UPDATE `Konta` SET `muted_timestamp`='%d' WHERE `id`='%d';", gracz[targetid][muted_timestamp], gracz[targetid][UID]);
    mq_send("QMuted");
    Interwencja(playerid, targetid, minutes, "Uciszenie", reason);
    return 1;
}

CMD:audiostream(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new link[128];
	if(sscanf(params,"s[128]", link)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /audiostream [link]");
	PlayAudioStreamForPlayer(playerid, link);
	return 1;
}

CMD:playsound(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new id;
	if(sscanf(params,"d", id)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /playsound [id]");
	PlayerPlaySound(playerid, id, 0.0, 0.0, 0.0);
	return 1;
}

CMD:feed(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /feed [targetid]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	FeedPlayer(targetid, 100);
	DrinkPlayer(targetid, 100);
	SendClientMessageEx(playerid, -1, "Nakarmiłeś i napoiłeś gracza: "COL_BLUE"%s (%d)", nick(targetid), targetid);
	return 1;
}

CMD:sethp(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid, hp;
	if(sscanf(params,"dd", targetid, hp)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /sethp [targetid] [hp]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz nie jest zalogowany.");
	SetPlayerHP(playerid, hp);
	SendClientMessageEx(playerid, -1, "Ustawiłeś dla gracza: "COL_BLUE"%s (%d)"COL_WHITE" punkty HP na: "COL_DBLUE"%d", nick(targetid), targetid, hp);
	return 1;
}


CMD:setpos(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new Float:sPos[3];
	if(sscanf(params,"fff", sPos[0], sPos[1], sPos[2])) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setpos [x] [y] [z]");
	SetPlayerPos(playerid, sPos[0], sPos[1], sPos[2]);
	return 1;
}

CMD:setloot(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new list_setloot[1000];
	strcat(list_setloot, "1. NORMAL\n");
	strcat(list_setloot, "2. ROŚLINA - pod wodą\n");
	strcat(list_setloot, "3. ROŚLINA - góry\n");
	strcat(list_setloot, "4. ROŚLINA - piasek\n");
	strcat(list_setloot, "5. ROŚLINA - woda\n");
	strcat(list_setloot, "6. ROŚLINA - bagna\n");
	strcat(list_setloot, "7. ROŚLINA - las\n");
	Dialog_Show(playerid, SETLOOT, DIALOG_STYLE_LIST, "Wybierz typ loot spawnu:", list_setloot, "Stwórz!", "Anuluj");
	return 1;
}

CMD:itemresp(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	Process_ReLootMap(1);
	SendClientMessage(playerid, -1, "GOTOWE");
	return 1;
}

CMD:restart(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new gmx_time, gmx_reason[128];
	if(sscanf(params,"ds[128]",  gmx_time, gmx_reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /restart [za ile sekund] [powód]");
	serwer[cooldown_restart] = gmx_time;
	SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Za "COL_WHITE"%d{fb9800} sekund nastąpi restart serwera. Powód: "COL_WHITE"%s{fb9800} "COL_RED"|-", serwer[cooldown_restart], gmx_reason);
	return 1;
}


Dialog:SETLOOT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"NORMAL");
			CreateFadeLabel(playerid, 255, 0, 0, "<NORMAL>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
		case 1:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"ROŚLINA - pod wodą");
			CreateFadeLabel(playerid, 0, 255, 0, "<ROŚLINA - pod wodą>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
		case 2:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"ROŚLINA - góry");
			CreateFadeLabel(playerid, 0, 255, 0, "<ROŚLINA - góry>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
		case 3:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"ROŚLINA - piasek");
			CreateFadeLabel(playerid, 0, 255, 0, "<ROŚLINA - piasek>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
		case 4:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"ROŚLINA - woda");
			CreateFadeLabel(playerid, 0, 255, 0, "<ROŚLINA - woda>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
		case 5:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"ROŚLINA - bagna");
			CreateFadeLabel(playerid, 0, 255, 0, "<ROŚLINA - bagna>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
		case 6:
		{
			SendClientMessage(playerid, -1, ">> Ustawiono loot spawn: "COL_RED"ROŚLINA - las");
			CreateFadeLabel(playerid, 0, 255, 0, "<ROŚLINA - las>", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], _, 5);
		}
	}
	mq_format("INSERT INTO `loots` (`id`, `X`, `Y`, `Z`, `TYP`) VALUES (NULL, '%f', '%f', '%f', '%d');", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], listitem);
	mq_send("QSetLoot");
	return 1;
}

CMD:getveh(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new list_veh[1024];
	format(list_veh, 1024, "UID\tNazwa pojazdu\tOdległość");
	new detected_vehs;
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(pojazd[v][v_id])
		{
			if(IsPlayerInRangeOfPoint(playerid, 100.0, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
			{
				format(list_veh, 1024, "%s\n"COL_BLACK"%d\t"COL_EASY"%s\t"COL_RED"%0.02fm", list_veh, v, GetVehicleName(pojazd[v][v_model]), GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY],gracz[playerid][PosZ],  pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]));
				detected_vehs++;
			}
		}
	}
	if(detected_vehs)
	{
		Dialog_Show(playerid, TPVEH, DIALOG_STYLE_TABLIST_HEADERS, "Który pojazd chcesz do siebie teleportować?", list_veh, "Wybierz", "Anuluj");
	}
	else
	{
		Error(playerid, "Brak pojazdów w pobliżu.");
	}
	return 1;
}
Dialog:TPVEH(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new v = strval(inputtext);
	if(pojazd[v][v_id])
	{
		if(IsPlayerInRangeOfPoint(playerid, 100.0, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
		{
			pojazd[v][v_idletime] = serwer[time_timestamp]+5;
			pojazd[v][v_temp_X] = gracz[playerid][PosX];
		 	pojazd[v][v_temp_Y] = gracz[playerid][PosY];
		 	pojazd[v][v_temp_Z] = gracz[playerid][PosZ];
		 	ToggleVDoors(v, 0);
		 	SetVehiclePos(pojazd[v][v_vehicleid], pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]);
		 	SetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]+4.0);
		 	SendClientMessage(playerid, -1, ""COL_RED"GOTOWE"COL_WHITE"!");
		}
		else
		{
			LeftNotifyShow(playerid, "error", "Pojazd jest za daleko.");
		}
	}
	return 1;
}