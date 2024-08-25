//**********DANE*************
#define sqluser "user"//your sql user
#define sqlpass "password"//your sql password
#define sqldb "database"//your sql database name
#define sqlhost "localhost"//sql host
//******MACRO**************
new MySQL;
new mQuery[1024];
#define mq_format( mysql_format(MySQL, mQuery, 1024,
#define mq_send( mysql_pquery(MySQL, mQuery,
#define mq_getdata() new rekordy, pola; cache_get_data(rekordy, pola, MySQL)

stock GetMOTD()
{
	new str_motd[2048];
	strcat(str_motd, ""COL_EASY"Projekt "COL_RED"Angel Fall"COL_EASY" jest jeszcze w fazie BETA! Prosimy wszelkie b³êdy zg³aszaæ administracji! \n");
	strcat(str_motd, "Nad czym pracujemy: \n");
	strcat(str_motd, "» Skrypt questów - 50%% \n");
	strcat(str_motd, "» Rozszerzenie terenu rozgrywki o Flint County - 10%% \n");
	strcat(str_motd, "» Akcesoria postaci - 0%% \n");
	strcat(str_motd, "» Zrzuty - 0%% \n");
	strcat(str_motd, "» Arena - 0%% \n");
	strcat(str_motd, "[lista nie jest kompletna] \n");
	return str_motd;
}

stock ShowLogin(playerid)  
{
	new motd[1024];
	format(motd, 1024, ""COL_EASY"Projekt "COL_RED"Angel Fall"COL_EASY" jest jeszcze w fazie BETA! Prosimy wszelkie b³êdy zg³aszaæ administracji!\n");
	format(motd, 1024, "%s\n", motd);
	format(temp_string, 512,  "%s"COL_WHITE"Witaj, "COL_BLUE"%s"COL_WHITE"!\n"COL_WHITE"Aby "COL_GREEN"zagraæ"COL_WHITE" musisz siê "COL_BLUE"zalogowaæ"COL_WHITE".", motd, nick(playerid));
	Dialog_Show(playerid, LOGOWANIE, DIALOG_STYLE_PASSWORD, ""COL_GREEN"»"COL_WHITE" LOGOWANIE - Angel Fall", temp_string, "Zaloguj", "Wyjdz");
	return 1;
}

stock ShowRegister(playerid)  
{
	new motd[1024];
	format(motd, 1024, ""COL_EASY"Projekt "COL_RED"Angel Fall"COL_EASY" jest jeszcze w fazie BETA! Prosimy wszelkie b³êdy zg³aszaæ administracji!\n");
	format(motd, 1024, "%s\n", motd);
	format(temp_string, 512,  "%s"COL_WHITE"Witaj, "COL_BLUE"%s"COL_WHITE"!\n"COL_WHITE"Aby "COL_GREEN"zagraæ"COL_WHITE" musisz siê "COL_BLUE"zarejestrowaæ"COL_WHITE".", motd, nick(playerid));
	format(temp_string, 512, "%s\n"COL_WHITE"Podaj has³o"COL_RED"(Has³o musi zawieraæ od 4 do 16 znaków.)"COL_WHITE":\n", temp_string);
	Dialog_Show(playerid, REJESTRACJA, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Angel Fall", temp_string, "Dalej", "Wyjdz");
	return 1;
}


forward OnAccountLoad(playerid);
public OnAccountLoad(playerid)
{
	//***********************************************************************************************************************************
	gracz[playerid][UID] = cache_get_field_content_int(0, "id");
	gracz[playerid][KillZombies] = cache_get_field_content_int(0, "KillZombies");
	gracz[playerid][KillHumans] = cache_get_field_content_int(0, "KillHumans");
	gracz[playerid][HP] = cache_get_field_content_int(0, "HP");
	gracz[playerid][Haslo] = cache_get_field_content_int(0, "Haslo");
	gracz[playerid][Plec] = cache_get_field_content_int(0, "Plec");
	gracz[playerid][Wiek] = cache_get_field_content_int(0, "Wiek");
	gracz[playerid][Karnacja] = cache_get_field_content_int(0, "Karnacja");
	gracz[playerid][Skin] = cache_get_field_content_int(0, "Skin");
	gracz[playerid][KRMHZ] = cache_get_field_content_int(0, "KRMHZ");
	gracz[playerid][Krwawi] = cache_get_field_content_int(0, "Krwawi");
	gracz[playerid][PSek] = cache_get_field_content_int(0, "PSek");
	gracz[playerid][PMin] = cache_get_field_content_int(0, "PMin");
	gracz[playerid][PGodz] = cache_get_field_content_int(0, "PGodz");
	gracz[playerid][OrgID] = cache_get_field_content_int(0, "OrgID");
	gracz[playerid][SzefORG] = cache_get_field_content_int(0, "SzefORG");
	gracz[playerid][ViceSzefORG] = cache_get_field_content_int(0, "ViceSzefORG");
	gracz[playerid][AdminJailTime] = cache_get_field_content_int(0, "AdminJailTime");
	gracz[playerid][BOOC] = cache_get_field_content_int(0, "BOOC");
	gracz[playerid][PosX] = cache_get_field_content_float(0, "PosX");
	gracz[playerid][PosY] = cache_get_field_content_float(0, "PosY");
	gracz[playerid][PosZ] = cache_get_field_content_float(0, "PosZ");
	gracz[playerid][Glod] = cache_get_field_content_int(0, "Glod");
	gracz[playerid][Pragn] = cache_get_field_content_int(0, "Pragn");
	gracz[playerid][LaserColor] = cache_get_field_content_int(0, "LaserColor");
	gracz[playerid][Warns] = cache_get_field_content_int(0, "Warns");
	gracz[playerid][Zwiazany] = cache_get_field_content_int(0, "Zwiazany");
	gracz[playerid][LastOnline] = gettime();
	gracz[playerid][AdminLevel] = cache_get_field_content_int(0, "AdminLevel");
	gracz[playerid][WebReg] = cache_get_field_content_int(0, "WebReg");
	gracz[playerid][MapperLvl] = cache_get_field_content_int(0, "MapperLvl");
	gracz[playerid][MaxEQ] = cache_get_field_content_int(0, "MaxSlotseq");
	gracz[playerid][gold] = cache_get_field_content_int(0, "gold");
	gracz[playerid][BWTime] = cache_get_field_content_int(0, "BWTime");
	gracz[playerid][QuestID] = cache_get_field_content_int(0, "QuestID");
	gracz[playerid][QuestStatus] = cache_get_field_content_int(0, "QuestStatus");
	gracz[playerid][GGame] = cache_get_field_content_int(0, "GGame");
	gracz[playerid][muted_timestamp] = cache_get_field_content_int(0, "muted_timestamp");
	cache_get_field_content(0, "master_nick", gracz[playerid][master_nick], MySQL, 32);
	if(strlen(gracz[playerid][master_nick]) < 3) format(gracz[playerid][master_nick], 32, "%s", nick(playerid));
	gracz[playerid][exp] = cache_get_field_content_int(0, "exp");
	gracz[playerid][level] = cache_get_field_content_int(0, "level");
	if(gracz[playerid][level] == 0) gracz[playerid][level] = 1;
	gracz[playerid][sila] = cache_get_field_content_int(0, "sila");
	gracz[playerid][vip] = cache_get_field_content_int(0, "vip");
	gracz[playerid][rads] = cache_get_field_content_int(0, "rads");
	gracz[playerid][time_antiblood] = cache_get_field_content_int(0, "time_antiblood");
	gracz[playerid][gps_hz] = cache_get_field_content_int(0, "gps_hz");
	gracz[playerid][rusznikarstwo] = cache_get_field_content_int(0, "rusznikarstwo");
	gracz[playerid][motoryzacja] = cache_get_field_content_int(0, "motoryzacja");
	gracz[playerid][medycyna] = cache_get_field_content_int(0, "medycyna");
	gracz[playerid][apid] = cache_get_field_content_int(0, "apid");
	gracz[playerid][prezent] = cache_get_field_content_int(0, "prezent");
	//------------------
	if(gracz[playerid][OrgID])
	{
		mq_format("SELECT * FROM `Grupy` WHERE `id`='%d' LIMIT 0,1;", gracz[playerid][OrgID]);
		mq_send("QLoadGroupData", "d", playerid);
	}
	//***********************************************************************************************************************************
	gracz[playerid][loggedin] = true;
	gracz[playerid][kondycja] = 100;
	SetPlayerVirtualWorld(playerid, 0);
	TogglePlayerControllable(playerid, false);
	HidePanorama(playerid);
	CreateLabelNick(playerid);
	Init_tutorial(playerid);
	SetSpawnInfo(playerid, 0, gracz[playerid][Skin], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][PosR], 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, false);
	ShowZones(playerid);
	GangZoneShowForPlayer(playerid, serwer[gz_hidemap], 0x646464FF);
	SpawnPlayer(playerid);
	SyncEQToAmmo(playerid);
	SendClientMessageEx(playerid, -1, "(("COL_EASY"Zalogowano na postaæ "COL_GREEN"%s "COL_EASY"(UID: %d | Konto: "COL_BLUE"%s"COL_EASY"). Mi³ej rozgrywki!"COL_WHITE"))", nick(playerid), gracz[playerid][UID], gracz[playerid][master_nick]);
	new bool:nofade;
	if(gracz[playerid][AdminLevel])
	{
		SendClientMessageEx(playerid, -1, "(("COL_EASY"Posiadasz "COL_GREEN"["COL_RED"%d"COL_GREEN"]"COL_EASY" poziom uprawnieñ. Aby wejœæ na s³u¿bê wpisz: "COL_BLUE"/aduty"COL_WHITE"))", gracz[playerid][AdminLevel]);	
	}
	if(gracz[playerid][sobeit_detect])
	{
		if(!gracz[playerid][AdminLevel]) 
		{
			nofade = true;
			Ban_Time(-1, playerid, "Niedozwolone oprogramowanie.", 1095);
		}
		else SendClientMessage(playerid, -1, ""COL_RED"[WYKRYCIE]"COL_WHITE" Administratorze, skrypt wykry³ u Ciebie mod s0beit. Pamiêtaj, ¿eby nie u¿ywaæ go do zabawy.");
	}
	format(temp_string, 128, "~w~Witaj z powrotem~n~~b~%s", nick(playerid));
	if(!gracz[playerid][WebReg]) GameTextForPlayer(playerid, temp_string, 3000, 1);
	ShowHud(playerid);
	if(!nofade) FadeColorForPlayer(playerid, 0, 0, 0, 255, 0, 0, 0, 0, 30, 1);
	gracz[playerid][first_spawn] = true;
	SetPlayerColor(playerid, 0x00000000);
	StartLoginHistory(playerid);
	StopAudioStreamForPlayer(playerid);
	PreloadAnimations(playerid);
	new str_join[128];
	format(str_join, 128, "~w~%s~g~ dolaczyl~w~ do gry.", nick(playerid));
	if(serwer[downbar_query]) serwer[downbar_query]--;
	serwer[downbar_time] = serwer[time_timestamp]+10;
	PasekDol(str_join);
	Process_SoundTrack(playerid);
	if(gracz[playerid][apid] > 0)
	{
		SetPlayerVirtualWorld(playerid, 777+gracz[playerid][apid]);
	}
	printf("[PLAYER]Gracz %s zalogowal sie. IP: %s", nick(playerid), playerip(playerid));
	return 1;
}


public OnPlayerRequestClass(playerid, classid)
{
	SetSpawnInfo(playerid, 0, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

stock ConnectDB()
{
	MySQL = mysql_connect(sqlhost, sqluser, sqldb, sqlpass, 3306, true, 5);
	print("[CONNECT]Lacze z  localhost...");
	if(mysql_errno() != 0) printf("[CONNECT]BLAD POLACZENIA Z BAZA DANYCH! - EXIT..."), SendRconCommand("exit");
	else
	{ 
		printf("[CONNECT]Polaczono z baza danych.");
	}
	return 1;
}

stock AuthPlayer(playerid)
{
	mq_format("SELECT `Haslo` FROM `Konta` WHERE `Nick`='%s' LIMIT 0,1;", nick(playerid, true));
	mq_send("OnAccountCheck", "d", playerid);
	return 1;
}

forward OnAccountCheck(playerid);
public OnAccountCheck(playerid)
{
	mq_getdata();
	LoginCamera(playerid);
	Process_Weather(playerid);
	if(rekordy)
	{
		gracz[playerid][Haslo] = cache_get_field_content_int(0, "Haslo");
		ShowLogin(playerid);
		CheckBan(playerid);
	}
	else
	{
		Dialog_Show(playerid, WIAD, DIALOG_STYLE_MSGBOX, "Rejestracja - INFO", ""COL_WHITE"Witaj na "COL_GREEN"Angel Fall\n"COL_WHITE"Aby móc graæ na serwerze musisz zarejestrowaæ swoj¹ postaæ przez panel gracza:"COL_GREEN" http://game.angelfall.pl"COL_WHITE".", "OK", "");
		KickEx(playerid, "Nie znaleziono konta");
		//ShowRegister(playerid);
	}
	return 1;
}

Dialog:LOGOWANIE(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	if(!strlen(inputtext)) 
	{
		ShowLogin(playerid);
		return 1;	
	}
	new str[130];
	if(udb_hash(inputtext) == gracz[playerid][Haslo])
	{
		mq_format("SELECT * FROM `Konta` WHERE `Nick`='%s' LIMIT 0,1;", nick(playerid, true));
		mq_send("OnAccountLoad", "d", playerid);
	}
	else
	{
		SetPVarInt(playerid, "BadPass", GetPVarInt(playerid, "BadPass")+1);
		if(GetPVarInt(playerid, "BadPass") == 3) return KickEx(playerid, "3/3 bad password.");
		format(str, 130, ""COL_WHITE"Aby "COL_GREEN"zagraæ"COL_WHITE" musisz siê "COL_BLUE"zalogowaæ"COL_WHITE".\nB³êdnych prób: "COL_RED"%d/3", GetPVarInt(playerid, "BadPass"));
		Dialog_Show(playerid, LOGOWANIE, DIALOG_STYLE_PASSWORD, ""COL_GREEN"»"COL_WHITE" LOGIN - Angel Fall", str, "Zaloguj", "Wyjdz");
	}
	return 1;
}

stock CheckBan(playerid)
{
	mq_format("SELECT `BanList`.*,FROM_UNIXTIME(`BanList`.`time`) as `times`,FROM_UNIXTIME(`BanList`.`time_end`) as `time_ends`,`u1`.`Nick` AS `admin_nick`,`u2`.`Nick` AS `user_nick`,(`BanList`.`time_end`-UNIX_TIMESTAMP(CURRENT_TIMESTAMP)) as `left` FROM `BanList` LEFT OUTER JOIN `Konta` AS `u1` ON `BanList`.`aid`=`u1`.`id` LEFT OUTER JOIN `Konta` AS `u2` ON `BanList`.`uid`=`u2`.`id` WHERE `BanList`.`time_end`>UNIX_TIMESTAMP(CURRENT_TIMESTAMP) AND (`u2`.`Nick` LIKE '%s' OR  (`BanList`.`ip`='%s' AND `BanList`.`ip_on`='1') OR (`BanList`.`gpci`='%s' AND `BanList`.`gpci_on`='1'));", nick(playerid, true), playerip(playerid, true), serial(playerid, true));
	mq_send("OnBanChecked", "d", playerid);
	return 1;
}

forward OnBanChecked(playerid);
public OnBanChecked(playerid)
{
	mq_getdata();
	new b_id, b_ip[20], b_serial[50], reason[128], b_admin[20], b_user[20], b_start[32], b_end[24], left_time;
	new ip_on, gpci_on, a_id;
	new i;
	if(rekordy)
	{
		while(i < cache_get_row_count())
		{
			b_id = cache_get_field_content_int(i, "id");
			ip_on = cache_get_field_content_int(i, "ip_on");
			cache_get_field_content(i, "ip", b_ip);
			gpci_on = cache_get_field_content_int(i, "gpci_on");
			cache_get_field_content(i, "gpci", b_serial);
			cache_get_field_content(i, "reason", reason);
			a_id = cache_get_field_content_int(i, "aid");
			if(a_id)
			{
				cache_get_field_content(i, "admin_nick", b_admin);
			}
			else
			{
				format(b_admin, 20, "SYSTEM");
			}
			cache_get_field_content(i, "user_nick", b_user);
			cache_get_field_content(i, "times", b_start);
			cache_get_field_content(i, "time_ends", b_end);
			left_time = cache_get_field_content_int(i, "left");
			if(compare(nick(playerid), b_user))
			{
			 	ShowBanInfo(playerid, b_id, b_admin, b_user, b_start, b_end, reason, left_time);
			 	break;
			}
			else if(compare(playerip(playerid), b_ip) && ip_on)
			{
				ShowBanInfo(playerid, b_id, b_admin, b_user, b_start, b_end, reason, left_time);
				break;
			}
			else if(compare(serial(playerid), b_serial) && gpci_on)
			{
				ShowBanInfo(playerid, b_id, b_admin, b_user, b_start, b_end, reason, left_time);
				break;
			}
			i++;
		}
	}
	return 1;
}

stock ShowBanInfo(playerid, banid, admin[], user[], nadane[], koniec[], powod[], dokonca)
{
	const contstr = 1600;
	new title[128], content[contstr];
	format(title, 128, ""COL_GREEN"»"COL_WHITE" BAN INFO"COL_RED"[ID: %d]", banid);
	format(content, contstr, ""COL_GREY"Ban ID:\t\t"COL_RED"%d\n", banid);
	format(content, contstr, "%s"COL_GREY"Admin:\t\t"COL_RED"%s\n", content, admin);
	if(compare(user, "NULL"))
	{
		format(content, contstr, "%s"COL_GREY"Konto:\t"COL_YELLOW"Nie zarejestrowane\n", content);
	}
	else
	{
		format(content, contstr, "%s"COL_GREY"Konto:\t\t"COL_YELLOW"%s\n", content, user);
	}
	format(content, contstr, "%s"COL_GREY"IP:\t\t"COL_YELLOW"%s\n", content, playerip(playerid));
	format(content, contstr, "%s"COL_GREY"Powód:\t"COL_ORANGE"%s\n", content, powod);
	format(content, contstr, "%s"COL_GREY"Data nadania:\t"COL_BLUE"%s\n", content, nadane);
	format(content, contstr, "%s"COL_GREY"Wygasa:\t"COL_BLUE"%s\n", content, koniec);
	new day_s, hour_s, minute_s, sec_s;
	SecToTime(dokonca, day_s, hour_s, minute_s, sec_s);
	format(content, contstr, "%s"COL_GREY"Pozosta³o:\t"COL_GREEN"%dd, %dh, %dm, %ds\n", content,  day_s, hour_s, minute_s, sec_s);
	format(content, contstr, "%s"COL_GREY"Napisz apelacje na "COL_GREEN"forum.angelfall.pl\n", content); 
	format(content, contstr, "%s"COL_GREY"Jeœli chcesz apelowaæ "COL_YELLOW"wciœnij F8(screenshoot jest potrzebny!).\n", content);
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, title, content, "Zamknij", "");
	KickEx(playerid, "Aktywny ban.");
	return 1;
}

stock Ban_Time(adminid, targetid, reason[], days)
{
	if(gracz[targetid][kick_antyspam] > serwer[time_timestamp]) return 0;
	gracz[targetid][kick_antyspam] = serwer[time_timestamp]+4;
	new czas = (days*24*60*60)+gettime();
	if(adminid != -1)
	{
		mq_format("INSERT INTO `BanList` (`uid`, `aid`, `time`, `time_end`, `ip_on`, `ip`, `gpci_on`, `gpci`, `reason`) VALUES ('%d', '%d', '%d', '%d', '1', '%s', '0', '%s', '%s');", gracz[targetid][UID], gracz[adminid][UID],  gettime(), czas, playerip(targetid, true), serial(targetid, true), reason);
		Interwencja(adminid, targetid, days, "Ban", reason);
	}
	else
	{
		mq_format("INSERT INTO `BanList` (`uid`, `aid`, `time`, `time_end`, `ip_on`, `ip`, `gpci_on`, `gpci`, `reason`) VALUES ('%d', '0', '%d', '%d', '1', '%s', '0', '%s', '%s');", gracz[targetid][UID],  gettime(), czas, playerip(targetid, true), serial(targetid, true), reason);
		Interwencja(targetid, targetid, days, "Ban", reason);
	}
	mq_send("QBan");
	KickEx(targetid, reason);
	return 1;
}

stock CheckS0beit(playerid)
{
	LoginCamera(playerid, 1);
	new golf = CreateVehicle(457, 0.0, 0.0, 4.0, 0.0, 1, 1, 20);
	SetPlayerVirtualWorld(playerid, playerid+1000);
	SetVehicleVirtualWorld(golf, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(golf, 500);
	PutPlayerInVehicle(playerid, golf, 0);
	SetTimerEx("SobeitCheck_s1", 300, false, "dd", playerid, golf);
	return 1;
}

forward SobeitCheck_s1(playerid, vehid);
public SobeitCheck_s1(playerid, vehid)
{
	LoginCamera(playerid, 1);
	RemovePlayerFromVehicle(playerid);
	SetTimerEx("SobeitCheck_s2", 300, false, "dd", playerid, vehid);
	return 1;
}

forward SobeitCheck_s2(playerid, vehid);
public SobeitCheck_s2(playerid, vehid)
{
	LoginCamera(playerid, 1);
	DestroyVehicle(vehid);
	new wdata1, wdata2;
	GetPlayerWeaponData(playerid, 1, wdata1, wdata2);
	if(wdata1)
	{
		gracz[playerid][sobeit_detect] = true;
	}
	else
	{
		gracz[playerid][sobeit_detect] = false;
	}	
	SetTimerEx("SobeitCheck_s3", 100, false, "d", playerid);
	return 1;
}

forward SobeitCheck_s3(playerid);
public SobeitCheck_s3(playerid)
{
	LoginCamera(playerid, 1);
	new wdata1, wdata2;
	GetPlayerWeaponData(playerid, 1, wdata1, wdata2);
	if(wdata1)
	{
		gracz[playerid][sobeit_detect] = true;
	}
	else
	{
		gracz[playerid][sobeit_detect] = false;
	}
	TogglePlayerSpectating(playerid, true);
	ResetPlayerWeapons(playerid);
	AuthPlayer(playerid);
	return 1;
}

stock LoginCamera(playerid, mode = 0)
{
	if(mode)
	{
		SetPlayerCameraPos(playerid, -664.5156, -3093.6965, 185.4273);
		SetPlayerCameraLookAt(playerid, -665.3368, -3093.1287, 185.4473);
	}
	else
	{
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerCameraPos(playerid, -664.5156, -3093.6965, 185.4273);
		SetPlayerCameraLookAt(playerid, -665.3368, -3093.1287, 185.4473);
		const time = 1000*60*2;
		InterpolateCameraPos(playerid,-664.5156, -3093.6965, 185.4273, -2004.5593, -1629.5525, 109.4682, time, CAMERA_MOVE);
		InterpolateCameraLookAt(playerid, -665.3368, -3093.1287, 185.4473,  -2004.2999, -1628.5823, 109.0332, time, CAMERA_MOVE);
	}
	return 1;
}

public OnQueryError(errorid, error[], callback[], query[], connectionHandle)
{
	switch(errorid)
	{
		case 2013:
		{
			printf("[CONNECT]Polaczenie z baza danych utracone - blokuje serwer...");
			SendRconCommand("password blockbymysql");
			SetGameModeText("MAINTANCE");
			for(new k; k <= GetPlayerPoolSize(); k++)
			{
				if(IsPlayerConnected(k))
				{
					KickEx(k, "MAINTANCE");
				}
			}
		}
		case ER_SYNTAX_ERROR:
		{
			printf("[SKLADNIA]Blokuje serwer, blad skladni: %s", query);
			SendRconCommand("password blockbymysql");
			SetGameModeText("MAINTANCE");
			for(new k; k <= GetPlayerPoolSize(); k++)
			{
				if(IsPlayerConnected(k))
				{
					KickEx(k, "MAINTANCE");
				}
			}
		}
	}
	printf("|QERROR| eid: %d | err: %s | call: %s | query: %s", errorid, error, callback, query);
	return 1;
}

forward QLoadGroupData(playerid);
public QLoadGroupData(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		cache_get_field_content(0, "Nazwa", gracz[playerid][group_name], MySQL, 128);
		cache_get_field_content(0, "Skrot", gracz[playerid][group_tag], MySQL, 8);
	}
	return 1;
}



Dialog:REJESTRACJA(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	switch(strlen(inputtext))
	{
		case 4..16:
		{
			gracz[playerid][Haslo] = udb_hash(inputtext);
			Dialog_Show(playerid, PLEC, DIALOG_STYLE_LIST, ""COL_RED"»"COL_WHITE" Rejestracja - P³eæ postaci", ""COL_RED"»"COL_WHITE" Mê¿czyzna\n"COL_RED"»"COL_WHITE" Kobieta", "Dalej", "Wyjdz");
		}
		default:
		{
			ShowRegister(playerid);
		}
	}
	return 1;
}

Dialog:PLEC(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	if(listitem == 0)
	{
		SendClientMessage(playerid, -1, "(("COL_GREY"P³eæ postaci: "COL_GREEN"Mê¿czyzna"COL_WHITE".))");
		gracz[playerid][Plec] = 1;
		Dialog_Show(playerid, WIEK, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Wiek postaci", "Podaj wiek"COL_RED"(16-60)"COL_WHITE":", "Dalej", "Wyjdz");
	} 
	else 
	{
		SendClientMessage(playerid, -1, "(("COL_GREY"P³eæ postaci: "COL_GREEN"Kobieta"COL_WHITE".))");
		gracz[playerid][Plec] = 2;
		Dialog_Show(playerid, WIEK, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Wiek postaci", "Podaj wiek"COL_RED"(16-60)"COL_WHITE":", "Dalej", "Wyjdz");
	}
	return 1;
}

Dialog:WIEK(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	new age = strval(inputtext);

	switch(age)
	{
		case 16..60:
		{
			gracz[playerid][Wiek] = age;
			SendClientMessageEx(playerid, -1, "(("COL_GREY"Wiek Twojej postaci: "COL_GREEN"%d"COL_WHITE".))", gracz[playerid][Wiek]);
			Dialog_Show(playerid, KARNACJA, DIALOG_STYLE_LIST, ""COL_RED"»"COL_WHITE"Rejestracja - Karnacja postaci", ""COL_RED"»"COL_WHITE" Bia³a\n"COL_RED"»"COL_WHITE" ¯ó³ta\n"COL_RED"»"COL_WHITE" Czarna", "Dalej", "Wyjdz");
		}
		default:
		{
			Dialog_Show(playerid, WIEK, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Wiek postaci", "Podaj wiek"COL_RED"(16-60)"COL_WHITE":", "Dalej", "Wyjdz");
		}
	}
	return 1;
}

Dialog:KARNACJA(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	switch(listitem)
	{
		case 0:
		{
			SendClientMessageEx(playerid, -1, "(("COL_GREY"Karnacja Twojej postaci: "COL_GREEN"Bia³a"COL_WHITE".))");
			gracz[playerid][Karnacja] = 1;
			WybierzSkin(playerid);
		}
		case 1:
		{
			SendClientMessageEx(playerid, -1, "(("COL_GREY"Karnacja Twojej postaci: "COL_GREEN"¯ó³ta"COL_WHITE".))");
			gracz[playerid][Karnacja] = 2;
			WybierzSkin(playerid);
		}
		case 2:
		{
			SendClientMessageEx(playerid, -1, "(("COL_GREY"Karnacja Twojej postaci: "COL_GREEN"Czarna"COL_WHITE".))");
			gracz[playerid][Karnacja] = 3;
			WybierzSkin(playerid);
		}
	}
	return 1;
}

Dialog:REGEND(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	SendClientMessageEx(playerid, -1, "(("COL_GREY"Twoja postaæ zosta³a stworzona."COL_GREEN" Zaloguj siê"COL_GREY"!"COL_WHITE"))");
	mq_format("INSERT INTO `Konta` (`Nick`,`Plec`,`Wiek`,`Karnacja`,`Skin`,`Haslo`,`WebReg`) VALUES ('%s','%d','%d','%d','%d','%d','1');", nick(playerid, true), gracz[playerid][Plec], gracz[playerid][Wiek], gracz[playerid][Karnacja], gracz[playerid][Skin], gracz[playerid][Haslo]);
	mq_send("QueryRegisterEnd", "d", playerid);
	return 1;
}

forward QueryRegisterEnd(playerid);
public QueryRegisterEnd(playerid)
{
	ShowLogin(playerid);
	return 1;
}
