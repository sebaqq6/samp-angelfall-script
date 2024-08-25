#pragma dynamic 30000
//**************SKRYPT POSTAPO BY SEBAQQ6****************************
#define VER "AF 1.6 (build: %d)"
//********************INCLUDE******************************
#include "qqbuild.inc"
#include "includes/a_samp.inc"
#include "includes/a_mysql.inc"
#include "includes/OPA.inc"
#include "includes/easyDialog.inc"
#include "includes/playerprogress.inc"
#include "includes/streamer.inc"
#include "includes/sscanf2.inc"
#include "includes/Pawn.CMD.inc"
#include "includes/FCNPC.inc"
#include "includes/fader.inc"
#include "includes/mapandreas.inc"
#include "includes/colandreas.inc"
#include "includes/physics.inc"
#include "includes/merrandom.inc"
#include "includes/mSelection.inc"
//********************MODU£Y*****************************
#include "modules/define.inc"//Definicje.
#include "modules/ram.inc"//Szufladki dla danych na których pracuje skrypt
#include "modules/auth.inc"//Baza danych/Autoryzacja u¿ytkownika
#include "modules/utils.inc"//Przydatne funkcje
#include "modules/textdraw.inc"//Textdrawy
#include "modules/items.inc"//Przedmioty
#include "modules/admin.inc"//Komendy admina
#include "modules/chat.inc"//Obs³uga czatu
#include "modules/inventory.inc"//System ekwipunku
#include "modules/item_probably.inc"//Modu³ odpowiadajacy za prawdopodobienistwo stworzenia przedmiotu na mapie.
#include "modules/loot.inc"//Modu³ odpowiedzialny za rozrzut przedmiotów na mapie
#include "modules/useitem.inc"//U¿ycie przedmiotu
#include "modules/player.inc"//Operacje na graczu
#include "modules/keys.inc"//Obs³uga klawiszy
#include "modules/damage.inc"//Obs³uga DMG/HP
#include "modules/removebuiliding.inc"//Modu³ usuwaj¹cy obiekty GTA SA
#include "modules/objects.inc"//Modu³ odpowiadaj¹cy za obiekty 
#include "modules/krypta.inc"//Modu³ odpowiadaj¹cy za funckjonowanie krypty
#include "modules/football.inc"//Pi³ka no¿na
#include "modules/doors.inc"//Obs³uga wejœæ
#include "modules/ognisko.inc"//System ogniska
#include "modules/nick_label.inc"//Modu³ odpowiadaj¹cy6 za nicki nad g³owami graczy
#include "modules/exp.inc"//Modu³ odpowiadaj¹cy za doœwiadczenie w grze
#include "modules/zombie.inc"//Modu³ odpowiadaj¹cy za szwêdaczy
#include "modules/commands.inc"//Wszystkie inne komendy, które nie mog¹ znaleŸæ siê w danym module
#include "modules/fadelabels.inc"//Modu³ odpowiadaj¹cy za zanikaj¹ce 3d texty
#include "modules/gym.inc"//Modu³ obs³ugujacy si³ownie.
#include "modules/combine_mode.inc"//Modu³ obs³ugujacy tryb kombinacji.
#include "modules/vehicle.inc"//Modu³ obs³ugujacy pojazdy.
#include "modules/group.inc"//Modu³ obs³ugujacy grupy.
#include "modules/sms.inc"//Modu³ obs³uguj¹cy mikrop³atnoœci.
#include "modules/market.inc"//Modu³ obs³uguj¹cy halê targow¹.
#include "modules/apartamenty.inc"//Modu³ obs³uguj¹cy apartamenty.
#include "modules/bazy.inc"//Modu³ obs³uguj¹cy bazy grup.
#include "modules/zone.inc"//Modu³ obs³uguj¹cy strefy.
//#include "modules/quest.inc"//Modu³ obs³uguj¹cy questy - INCOMPLETE
//*******************BRUDNOPIS***************************
/*
- Admin Jail 
- awanse na czacie globalnym
- osi¹gniecia - pierwszy raz zrobi³eœ taki 

- soundtrack przywróc
- Strefy (gangzone)
- grupy dostoswaæ
- bazy dodaæ
- nowa krypta
- opisy
- dla admina cmd na dodawanie itemków
- komenda na szeptanie
*/
//*********************SKRYPT*****************************
main(){}
//new pick_prezent;
public OnGameModeInit()
{
	format(serwer[wersja], 64, VER, QQBUILD);//generowanie wersji
	print("****************SKRYPT POSTAPO LOAD****************");
	print("POSTAPO system is begin load... - Coded by sebaqq6");
	print("Copyright  2016/17");
	print("Skrypt postapokalipsy dla projektu Angel Fall");
	printf(">> Wersja: %s", serwer[wersja]);
	print("****************SKRYPT POSTAPO LOAD****************");
	AddPlayerClass(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	LimitPlayerMarkerRadius(9999.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	//UsePlayerPedAnims();
	serwer[pogoda] = 20;
	serwer[godzina] = 6;
	SetWorldTime(serwer[godzina]);
	SetTimer("world_control", 1000*60*7, 1);//zmiana pogody/czasu+
	serwer[soundtrack_timer] = gettime()+60*7;
	ServerUpdate();
	SetTimer("ServerUpdate", 1000, 1);
	SendRconCommand("mapname Whetstone/Back O' Beyond");
	PasekDol("Angel Fall - angelfall.pl");
	SetGameModeText(serwer[wersja]);
	ShowNameTags(0);
	for(new a; a < MAX_ACTOR; a++)
	{
		actor[a][actor_id] = INVALID_ACTOR_ID;
	}
	ConnectDB();
	Init_TextDrawGlobal();
	Streamer_TickRate(30);
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 777);
	Init_Objects();
	Init_Football();
	Krypta_Init();
	Krypta_Close();
	Init_Doors();
	FadeInit();
	Init_Zombie();
	Init_Gym();
	Init_Vehicles();
	Init_Groups();
	Market_Init();
	LoadSkins();
	Init_Apartamenty();
	Init_Zones();
	//Init_Quest();
	serwer[gz_hidemap] = GangZoneCreate(-2966.18, -2931.147, 81.74512, -513.8265);
	serwer[game_field] = CreateDynamicPolygon(game_field_data);
	CreateDynamic3DTextLabel("***sprawny dystrybutor***\n"COL_WHITE"(("COL_EASY"/tankuj lub u¿yj kanistra"COL_WHITE"))", 0x765898FF, -1607.9446,-2717.4119,48.5391, 3.0);
	CreateDynamic3DTextLabel("***sprawny dystrybutor***\n"COL_WHITE"(("COL_EASY"/tankuj lub u¿yj kanistra"COL_WHITE"))", 0x765898FF, -11.9189,-2522.2725,36.6555, 3.0);
	CreateDynamic3DTextLabel(""COL_RED"(("COL_EASY"Naprawdê, poœwiêæ chwilê na "COL_GREEN"/pomoc"COL_LIME" -> "COL_GREEN"Opis rozgrywki"COL_EASY"\n"COL_EASY"Bêdzie Ci ³atwiej zacz¹æ grê."COL_RED"))", 0x765898FF, -2350.1819,-1632.1136,2310.4917, 5.0, _, _, 1);
	CreateDynamic3DTextLabel(""COL_RED"(("COL_ORANGE"ChodŸ na "COL_CYAN"C"COL_ORANGE" aby generowaæ najmniejszy ha³as.\nSpowoduje to, ¿e szwêdacze nie bêd¹ Ciê s³yszeæ,"COL_RED"))", 0x765898FF, -1995.1685,-1594.2118,87.3582, 10.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -1365.1147,-2000.5859,1.8554, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -1506.7386,-2312.7712,1.8554, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -1520.9185,-2223.4324,2.4344, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -2701.3765,-2197.5000,1.2692, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -1643.8407,-1682.8496,1.6915, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -1241.6897,-2526.8713,1.6894, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -1803.0276,-2766.0796,1.4611, 6.0);
	CreateDynamic3DTextLabel("***molo***\n"COL_WHITE"(("COL_EASY"/wedkuj lub u¿yj wêdki"COL_WHITE"))", 0x765898FF, -381.9236,-1852.0017,1.9192, 6.0);
	CreateDynamicMapIcon(-1365.1147,-2000.5859,1.8554, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-1506.7386,-2312.7712,1.8554, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-1520.9185,-2223.4324,2.4344, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-2701.3765,-2197.5000,1.2692, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-1643.8407,-1682.8496,1.6915, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-1241.6897,-2526.8713,1.6894, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-1803.0276,-2766.0796,1.4611, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo
	CreateDynamicMapIcon(-381.9236,-1852.0017,1.9192, 9, -1, _, _, _, 1000.0, MAPICON_GLOBAL);//molo

	CreateDynamicMapIcon(-1999.7366, -1558.9781, 87.9436, 31, -1, _, _, _, 9000.0, MAPICON_GLOBAL);//krypta
	//prezenty
	//pick_prezent = CreatePickup(19056, 1, -1969.0687,-1608.3618,88.5833);
	//czyszczenie przedmiotów z count == 0
	DelZeroItems();
	ImportItems();
	print("****************POSTAPO SUCCESS LOAD****************");
	return 1;
}

public OnGameModeExit()
{
	FadeExit();
	print("****************SKRYPT POSTAPO UNLOAD****************");
	new dd, gg, mm, ss;
	SecToTime(serwer[uptime], dd, gg, mm, ss);
	printf("UPTIME: %d dni, %d godzin, %d minut, %d sekund",   dd, gg, mm, ss);
	print("****************SKRYPT POSTAPO UNLOAD****************");
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	/*if(pickupid == pick_prezent)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, 6)) RemovePlayerAttachedObject(playerid, 6);
		else SetPlayerAttachedObject(playerid, 6, 19065, 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);
		if(!gracz[playerid][prezent])
		{
			gracz[playerid][prezent] = 1;
			GiveExp(playerid, 150);
			new info_prezent[1000];
			mq_format("UPDATE `Konta` SET `prezent`='1' WHERE `id`='%d';", gracz[playerid][UID]);
			mq_send("QPrezentUpdate");
			strcat(info_prezent, ""COL_GREY"Dostajesz od nas w prezencie {8100db}+150 EXP"COL_GREY"!");
			strcat(info_prezent, "\n"COL_GREY"Wszystkiego dobrego z okazji nadchodz¹cych œwi¹t ¿yczy Ekipa {f12f2f}Angel Fall"COL_GREY"!");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"» "COL_GREEN"Prezent otrzymany!", info_prezent, "Zamknij", "");
		}
	}*/
	return 1;
}


CMD:autorzy(playerid, params[])
{
	new autorzy[512];
	strcat(autorzy,""COL_GREY"Programista PAWN(& C++), w³aœciciel projektu, prowadz¹cy:"COL_RED" sebaqq6 \n");
	strcat(autorzy,""COL_GREY"Programista PHP, wspó³w³aœciciel projektu, admin techniczny:"COL_RED" czerwony03 \n");
	strcat(autorzy,""COL_GREY"Obiekter, wspó³w³aœciciel projektu, pomoc przy mechanice rozgrywki:"COL_RED" Requeim\n");
	strcat(autorzy,""COL_GREY"Credtis:"COL_BLUE" Julia, iDAKU, Policjant, Jase\n");
	strcat(autorzy,""COL_GREY"Nasze oficjalne forum : "COL_LIME"http://forum.angelfall.pl\n");
	strcat(autorzy,""COL_GREEN"\t\t\t\t\t\t\t\t\tMi³ej gry! :)\n");
	MessageGUIEx(playerid, "Osoby, które zaanga¿owa³y siê w projekt AngelFall", autorzy);
	return 1;
}

forward ServerUpdate();
public ServerUpdate()
{
	serwer[time_timestamp] = gettime(serwer[time_hour], serwer[time_minute], serwer[time_second]);
	serwer[uptime]++;
	Process_ServerRestart();
	Process_Vehicle();
	Process_FadeLabel();
	Hide_Interwencja();
	Process_ReLootMap(0);
	Process_Actor();
	Process_PasekDol();
	Process_PoolPlayerSize();
	Process_KryptaGate();
	Process_KryptaWinda();
	//mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `count`='0';", t_id);
	//mq_send("QDelZeroItems");
	if(serwer[soundtrack_timer] < serwer[time_timestamp])
	{
		switch(serwer[soundtrackid])
		{
			case 0:
			{
				serwer[soundtrackid] = 1;
			}
			case 1:
			{
				serwer[soundtrackid] = 2;
			}
			case 2:
			{
				serwer[soundtrackid] = 0;
			}
		}
		serwer[soundtrack_timer] = serwer[time_timestamp]+60*7;
		for(new p = PlayerPoolSize(); p != -1; p--)
		{
			Process_SoundTrack(p);
		}
	}
	/*if(serwer[playerboisko_time] > serwer[time_timestamp])
	{
		PHY_Enabled = true;
	}
	else
	{
		PHY_Enabled = false;
	}*/
	
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		OneSecondUpdate(p);
	}
	return 1;
}

forward world_control();
public world_control()
{
	serwer[godzina]++;
	if(serwer[godzina] == 23)
	{
		serwer[godzina] = 0;
		serwer[dzien_tygodnia]++;
		if(serwer[dzien_tygodnia] == 7)
		{
			serwer[dzien_tygodnia] = 0;
		}
		TextDrawSetString(td_hud8, DzienTygodnia(serwer[dzien_tygodnia]));
	}
	RandomWeather();
	return 1;
}

stock Process_PoolPlayerSize()
{
	static temp_pool;
	temp_pool = 0;
	for(new p; p < MAX_PLAYERS; p++)
	{
		if(IsPlayerNPC(p)) continue;
		if(IsPlayerConnected(p)) temp_pool = p;
	}
	serwer[playerPoolSize] = temp_pool;
	return 1;
}


stock RandomWeather()
{
	serwer[r_weather]++;
	switch(serwer[godzina])
	{
		case 1..6: return serwer[pogoda] = 44;
		case 7: return serwer[pogoda] = 20;
		case 20: return serwer[pogoda] = 0;
		case 21: return serwer[pogoda] = 0;
	}
	if(serwer[r_weather] >= 9)
	{
		serwer[r_weather] = 0;
		serwer[n_weather]++;
		if(serwer[n_weather] == 6)
		{
			serwer[n_weather] = 0;
		}
		switch(serwer[n_weather])
		{
			case 0:
			{
				serwer[pogoda] = 20;
			}
			case 1:
			{
				serwer[pogoda] = 9;
			}
			case 3:
			{
				serwer[pogoda] = 20;
			}
			case 4:
			{
				serwer[pogoda] = 20;
			}
			case 5:
			{
				serwer[pogoda] = 9;
			}
		}
	}
	return 1;
}

public OnDynamicObjectMoved(objectid)
{
	OnKryptaGateMoved(objectid);
	return 1;
}


stock LoadSkins()
{
	k_skinbialy = LoadModelSelectionMenu("k_skinbialy.txt");
	m_skinbialy = LoadModelSelectionMenu("m_skinbialy.txt");
	k_skinzolty = LoadModelSelectionMenu("k_skinzolty.txt");
	m_skinzolty = LoadModelSelectionMenu("m_skinzolty.txt");
	k_skinczarny = LoadModelSelectionMenu("k_skinczarny.txt");
	m_skinczarny = LoadModelSelectionMenu("m_skinczarny.txt");
	return 1;
}

stock Process_PasekDol()
{
	if(serwer[downbar_time] > serwer[time_timestamp]) return 1;
	serwer[downbar_time] = serwer[time_timestamp]+60;
	switch(serwer[downbar_query])
	{
		case 0:
		{
			PasekDol("Angel Fall - angelfall.pl");
			serwer[downbar_query] = 1;
		}
		case 1:
		{
			PasekDol("Chodzenie na C sprawia, ze szwedacze Cie nie slysza.");
			serwer[downbar_query] = 2;
		}
		case 2:
		{
			PasekDol("Podczas walki, warto zmieniac swoje polozenie. Stojac w miejscu, stajemy sie latwym celem.");
			serwer[downbar_query] = 3;
		}
		case 3:
		{
			PasekDol("Zalecamy uzywac bezpiecznego opuszczania serwera: ~r~/qs~w~.");
			serwer[downbar_query] = 4;
		}
		case 4:
		{
			PasekDol("Widzisz gracza lamiacego zasady? Zreportuj go ~y~/report~w~");
			serwer[downbar_query] = 5;
		}
		case 5:
		{
			PasekDol("Zapraszamy na nasz serwer glosowy TS3: ~g~ts.angelfall.pl");
			serwer[downbar_query] = 6;
		}
		case 6:
		{
			PasekDol("Chodzac na C regeneruje sie nam kondycja.");
			serwer[downbar_query] = 7;
		}
		case 7:
		{
			PasekDol("Za eksplorowanie mapy zdobywamy doswiadczenie.");
			serwer[downbar_query] = 8;
		}
		case 8:
		{
			PasekDol("Walka wrecz z szwedaczem jest bardzo niebezpieczna!");
			serwer[downbar_query] = 9;
		}
		case 9:
		{
			PasekDol("Puszki i zlom mozesz sprzedac na hali targowej.");
			serwer[downbar_query] = 10;
		}
		default:
		{
			serwer[downbar_query] = 0;
		}
	}
	return 1;
}

stock Process_ServerRestart()
{
	if(serwer[cooldown_restart] > 0)
	{
		serwer[cooldown_restart]--;
		if(serwer[cooldown_restart] == 45)
		{
			SendClientMessageToAll(-1, ""COL_RED"-|{fb9800} Serwer zostanie zrestartowany za "COL_WHITE"45{fb9800} sekund... "COL_RED"|-");
		}
		else if(serwer[cooldown_restart] == 30)
		{
			SendClientMessageToAll(-1, ""COL_RED"-|{fb9800} Serwer zostanie zrestartowany za "COL_WHITE"30{fb9800} sekund... "COL_RED"|-");
		}
		else if(serwer[cooldown_restart] == 15)
		{
			SendClientMessageToAll(-1, ""COL_RED"-|{fb9800} Serwer zostanie zrestartowany za "COL_WHITE"15{fb9800} sekund... "COL_RED"|-");
		}
		else if(serwer[cooldown_restart] <= 5 && serwer[cooldown_restart])
		{
			SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Serwer zostanie zrestartowany za "COL_WHITE"%d{fb9800} sekund... "COL_RED"|-", serwer[cooldown_restart]);
		}
		else if(serwer[cooldown_restart] == 0)
		{
			SendClientMessageToAll(-1, ""COL_RED"-|{fb9800} Serwer zostaje zrestartowany... "COL_RED"|-");
			printf("[SERVER_RESTART]Wysylam zadanie restartu serwera...");
			HTTP(0, HTTP_GET, "ip.angelfall.pl/angelfall/api/SecuredAwesomeApiScript1337.php?key=TBHYpgfmGmjDqWDmpG99qTF8FfwNyz&app=restart&ins=1", "", "RServerRestart");
		}
	}
	else if(serwer[time_hour] == 3 && serwer[time_minute] == 0)
	{
		printf("[SERVER_RESTART]Rozpoczynam procedure nocnego restartu serwera...");
		serwer[cooldown_restart] = 65;
		SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Za "COL_WHITE"%d{fb9800} sekund nast¹pi restart serwera. Powód: "COL_WHITE"Jest godzina: %02d:%02d{fb9800} "COL_RED"|-", serwer[cooldown_restart], serwer[time_hour], serwer[time_minute]);
	}
	return 1;
}

stock Process_Actor()
{
	if(actor_refresh_time > serwer[time_timestamp]) return 1;
	actor_refresh_time = serwer[time_timestamp]+30;
	for(new a; a < MAX_ACTOR; a++)
	{
		if(IsValidActor(actor[a][actor_id])) 
		{
			SetActorPos(actor[a][actor_id], actor[a][X], actor[a][Y], actor[a][Z]);
			SetActorFacingAngle(actor[a][actor_id], actor[a][R]);
		}
	}
	return 1;
}

stock FreeActorID()
{
	for(new a; a < MAX_ACTOR; a++)
	{
		if(actor[a][actor_id] == INVALID_ACTOR_ID) return a;
	}
	printf("[LIMIT]Limit aktorow przekroczony!!!");
	return MAX_ACTOR;
}

stock NewActor(amodelid, Float:aX, Float:aY, Float:aZ, Float:aRotation)
{
	new faid = FreeActorID();
	actor[faid][actor_id] = CreateActor(amodelid, aX, aY, aZ, aRotation);
	actor[faid][X] = aX;
	actor[faid][Y] = aY;
	actor[faid][Z] = aZ;
	actor[faid][R] = aRotation;
	printf("[ACTOR]Stworzono aktora ID: %d", faid);
	return faid;
}
//**************************************************************************************************************************************************POLIGON
CMD:getvw(playerid, params[])
{
	SendClientMessageEx(playerid, -1, "%d", GetPlayerVirtualWorld(playerid));
	return 1;
}

CMD:tdoff(playerid, params[])
{
	for(new i; i < MAX_PLAYER_TEXT_DRAWS; i++)
	{
		PlayerTextDrawHide(playerid, PlayerText:i);
		PlayerTextDrawDestroy(playerid, PlayerText:i);
	}
	for(new x; x < MAX_TEXT_DRAWS; x++)
	{
		TextDrawHideForPlayer(playerid, Text:x);
	}
	return 1;
}

/*CMD:timetest(playerid, params[])
{
	world_control();
	SendClientMessage(playerid, -1, "timetest");
	return 1;
}

CMD:jetpack(playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	return 1;
}

CMD:krypta(playerid, params[])
{
	SetPlayerPos(playerid, -2342.2224,-1635.1975,2316.0486);
	return 1;
}

CMD:boisko(playerid, params[])
{
	SetPlayerPos(playerid, 2706.7092,-1839.0684,422.8209);
	return 1;
}

CMD:car(playerid, params[])
{
	new carid, k[2];
	if(sscanf(params,"ddd", carid, k[0], k[1])) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /car [carid] [k1] [k2] [pozycje x,y,z]");
	if(carid < 400 || carid > 611) return 1;
	new vid = CreateVehicle(carid, gracz[playerid][PosX]+3, gracz[playerid][PosY]+3, gracz[playerid][PosZ], 0, k[0], k[1], 1000);
	SetVehicleParamsEx(vid, 1, 1, 0, 0, 0, 0, 0);
	SendClientMessage(playerid, -1, ""COL_RED"GOTOWE"COL_WHITE"!");
	return 1;
}



CMD:pooltest(playerid, params[])
{
	SendClientMessageEx(playerid, -1, "Pool: %d", PlayerPoolSize());
	return 1;
}
CMD:showmm(playerid, params[])
{
	ShowMinimap(playerid);
	return 1;
}

CMD:vipcheck(playerid, params[])
{
	SendClientMessage(playerid, -1, "sprawdzam");
	if(isvip(playerid)) SendClientMessage(playerid, -1, "jesteœ vipem");
	return 1;
}

CMD:itemls(playerid, params[])
{
	new Float:lsPos[3];
	lsPos[0] = 2078.5173;//oœ X
	lsPos[1] = -2486.1628;
	lsPos[2] = 13.5469;
	for(new x; x < MAX_ITEMS; x++)
	{
		if(ObjectItem[x] == -1) continue;
		CreateItemForWorld(x, 1, 2000, 2000, lsPos[0], lsPos[1], lsPos[2], 0, 0);
		lsPos[0] -= 1.5;//oœ X
	}
	SendClientMessage(playerid, -1, "Done");
	return 1;
}*/

/*CMD:importbackup(playerid, params[])
{
	SendClientMessage(playerid, -1, "Rozpoczynam importowanie...");
	new File:handle = fopen("obiekty_backup.txt", io_read);
	new buf[512];
	new counter;
	new id, model, idgrupa, uid, World, InteriorEx;
	new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
	new mmat;
	while(fread(handle, buf)) 
	{
		if(sscanf(buf, "p<|>ddddddffffffd", id, model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz, mmat)) return printf("fatalny b³¹d kurwa!!!!!!");
		mq_format("INSERT INTO `samp_prp`.`Obiekty` (`id`, `model`, `idgrupa`, `uid`, `World`, `InteriorEx`, `x`, `y`, `z`, `rx`, `ry`, `rz`, `mmat`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d');", id, model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz, mmat);
		mq_send("QImportObjects");
		counter++;
	}
	fclose(handle);
	SendClientMessageEx(playerid, -1, "Import zakonczony(%d rekordów)...", counter);
	return 1;
}
*/


stock ImportItems()
{
	mysql_query(MySQL, "TRUNCATE `ItemInfo`;", false);
	for(new x; x < MAX_ITEMS; x++)
	{
		mq_format("INSERT INTO `ItemInfo` (`uid`,`name`) VALUES ('%d','%s');", x, ItemName[x]);
		mq_send("ImportItems");
	}
	return 1;
}
