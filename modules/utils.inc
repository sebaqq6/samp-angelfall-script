SendClientMessage(playerid, color, message[])
{
	ov_SendClientMessage(playerid, color, message);
	if(gracz[playerid][loggedin])
	{
		new formtxt[255];
		format(formtxt, 255, "{%06x}%s", color >>> 8, message);
		mysql_escape_string(formtxt, formtxt);
		mq_format("INSERT INTO `chat_log` (`uid`,`chat`,`time`) VALUES ('%d','%s',CURRENT_TIMESTAMP);", gracz[playerid][UID], formtxt);
		mq_send("SendChatQuery");
	}
	return 1;
}

stock nick(p, escape = false)
{
	new n[24];
	GetPlayerName(p, n, 24);
	if(escape) mysql_escape_string(n, n);
	return n;
}

stock playerip(p, escape = false)
{
	new n[24];
	GetPlayerIp(p, n, 24);
	if(escape) mysql_escape_string(n, n);
	return n;
}

native gpci(playerid, serial [], len);
stock serial(p, escape = false)
{
	new n[64];
	gpci(p,  n, 64);
	if(escape) mysql_escape_string(n, n);
	return n;
}

stock KickEx(playerid, reason[])
{
	printf("|KICK| %s | Reason: %s", nick(playerid), reason);
	return SetTimerEx("KickExRun", 30, false, "d", playerid);
}
forward KickExRun(playerid); 
public  KickExRun(playerid) return Kick(playerid);


stock SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
	static
	args,
	str[256];
	/*
	*  Custom function that uses #emit to format variables into a string.
	*  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 3)
	{
		format(str, 256, "%s", text);
		SendClientMessage(playerid, color, str);
	}
	else
	{
		while (--args >= 3)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 256
		#emit PUSH.C str
		#emit PUSH.S 8
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		SendClientMessage(playerid, color, str);
		#emit RETN
	}
	return 1;
}


stock SendClientMessageToAllEx(color, const text[], {Float, _}:...)
{
	static
	args,
	str[256];
	/*
	*  Custom function that uses #emit to format variables into a string.
	*  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 2)
	{
		SendClientMessageToAll(color, text);
	}
	else
	{
		while (--args >= 2)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 256
		#emit PUSH.C str
		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		SendClientMessageToAll(color, str);
		#emit RETN
	}
	return 1;
}


stock udb_hash(buf[]) 
{
	new length=strlen(buf);
	new s1 = 1;
	new s2 = 0;
	new n;
	for (n=0; n<length; n++)
	{
		s1 = (s1 + buf[n]) % 65521;
		s2 = (s2 + s1)     % 65521;
	}
	return (s2 << 16) + s1;
}


stock GetVehicleName(model)
{
	new name[32];
	switch(model)
	{
		case 400: format(name,32,"Landstalker");
		case 401: format(name,32,"Bravura");
		case 402: format(name,32,"Buffalo");
		case 403: format(name,32,"Linerunner");
		case 404: format(name,32,"Perenniel");
		case 405: format(name,32,"Sentinel");
		case 406: format(name,32,"Dumper");
		case 407: format(name,32,"Firetruck");
		case 408: format(name,32,"Trashmaster");
		case 409: format(name,32,"Stretch");
		case 410: format(name,32,"Manana");
		case 411: format(name,32,"Infernus");
		case 412: format(name,32,"Voodoo");
		case 413: format(name,32,"Pony");
		case 414: format(name,32,"Mule");
		case 415: format(name,32,"Cheetah");
		case 416: format(name,32,"Ambulance");
		case 417: format(name,32,"Leviathan");
		case 418: format(name,32,"Moonbeam");
		case 419: format(name,32,"Esperanto");
		case 420: format(name,32,"Taxi");
		case 421: format(name,32,"Washington");
		case 422: format(name,32,"Bobcat");
		case 423: format(name,32,"Mr Whoopee");
		case 424: format(name,32,"BF Injection");
		case 425: format(name,32,"Hunter");
		case 426: format(name,32,"Premier");
		case 427: format(name,32,"Enforcer");
		case 428: format(name,32,"Securicar");
		case 429: format(name,32,"Banshee");
		case 430: format(name,32,"Predator");
		case 431: format(name,32,"Bus");
		case 432: format(name,32,"Rhino");
		case 433: format(name,32,"Barracks");
		case 434: format(name,32,"Hotknife");
		case 435: format(name,32,"Article Trailer");
		case 436: format(name,32,"Previon");
		case 437: format(name,32,"Coach");
		case 438: format(name,32,"Cabbie");
		case 439: format(name,32,"Stallion");
		case 440: format(name,32,"Rumpo");
		case 441: format(name,32,"RC Bandit");
		case 442: format(name,32,"Romero");
		case 443: format(name,32,"Packer");
		case 444: format(name,32,"Monster");
		case 445: format(name,32,"Admiral");
		case 446: format(name,32,"Squallo");
		case 447: format(name,32,"Seasparrow");
		case 448: format(name,32,"Pizzaboy");
		case 449: format(name,32,"Tram");
		case 450: format(name,32,"Article Trailer 2");
		case 451: format(name,32,"Turismo");
		case 452: format(name,32,"Speeder");
		case 453: format(name,32,"Reefer");
		case 454: format(name,32,"Tropic");
		case 455: format(name,32,"Flatbed");
		case 456: format(name,32,"Yankee");
		case 457: format(name,32,"Caddy");
		case 458: format(name,32,"Solair");
		case 459: format(name,32,"Berkley's RC Van");
		case 460: format(name,32,"Skimmer");
		case 461: format(name,32,"PCJ-600");
		case 462: format(name,32,"Faggio");
		case 463: format(name,32,"Freeway");
		case 464: format(name,32,"RC Baron");
		case 465: format(name,32,"RC Raider");
		case 466: format(name,32,"Glendale");
		case 467: format(name,32,"Oceanic");
		case 468: format(name,32,"Sanchez");
		case 469: format(name,32,"Sparrow");
		case 470: format(name,32,"Patriot");
		case 471: format(name,32,"Quad");
		case 472: format(name,32,"Coastguard");
		case 473: format(name,32,"Dinghy");
		case 474: format(name,32,"Hermes");
		case 475: format(name,32,"Sabre");
		case 476: format(name,32,"Rustler");
		case 477: format(name,32,"ZR-350");
		case 478: format(name,32,"Walton");
		case 479: format(name,32,"Regina");
		case 480: format(name,32,"Comet");
		case 481: format(name,32,"BMX");
		case 482: format(name,32,"Burrito");
		case 483: format(name,32,"Camper");
		case 484: format(name,32,"Marquis");
		case 485: format(name,32,"Baggage");
		case 486: format(name,32,"Dozer");
		case 487: format(name,32,"Maverick");
		case 488: format(name,32,"SAN News Maverick");
		case 489: format(name,32,"Rancher");
		case 490: format(name,32,"FBI Rancher");
		case 491: format(name,32,"Virgo");
		case 492: format(name,32,"Greenwood");
		case 493: format(name,32,"Jetmax");
		case 494: format(name,32,"Hotring Racer");
		case 495: format(name,32,"Sandking");
		case 496: format(name,32,"Blista Compact");
		case 497: format(name,32,"Police Maverick");
		case 498: format(name,32,"Boxville");
		case 499: format(name,32,"Benson");
		case 500: format(name,32,"Mesa");
		case 501: format(name,32,"RC Goblin");
		case 502: format(name,32,"Hotring Racer");
		case 503: format(name,32,"Hotring Racer");
		case 504: format(name,32,"Bloodring Banger");
		case 505: format(name,32,"Rancher");
		case 506: format(name,32,"Super GT");
		case 507: format(name,32,"Elegant");
		case 508: format(name,32,"Journey");
		case 509: format(name,32,"Bike");
		case 510: format(name,32,"Mountain Bike");
		case 511: format(name,32,"Beagle");
		case 512: format(name,32,"Cropduster");
		case 513: format(name,32,"Stuntplane");
		case 514: format(name,32,"Tanker");
		case 515: format(name,32,"Roadtrain");
		case 516: format(name,32,"Nebula");
		case 517: format(name,32,"Majestic");
		case 518: format(name,32,"Buccaneer");
		case 519: format(name,32,"Shamal");
		case 520: format(name,32,"Hydra");
		case 521: format(name,32,"FCR-900");
		case 522: format(name,32,"NRG-500");
		case 523: format(name,32,"HPV1000");
		case 524: format(name,32,"Cement Truck");
		case 525: format(name,32,"Towtruck");
		case 526: format(name,32,"Fortune");
		case 527: format(name,32,"Cadrona");
		case 528: format(name,32,"FBI Truck");
		case 529: format(name,32,"Willard");
		case 530: format(name,32,"Forklift");
		case 531: format(name,32,"Tractor");
		case 532: format(name,32,"Combine Harvester");
		case 533: format(name,32,"Feltzer");
		case 534: format(name,32,"Remington");
		case 535: format(name,32,"Slamvan");
		case 536: format(name,32,"Blade");
		case 537: format(name,32,"Freight");
		case 538: format(name,32,"Brownstreak");
		case 539: format(name,32,"Vortex");
		case 540: format(name,32,"Vincent");
		case 541: format(name,32,"Bullet");
		case 542: format(name,32,"Clover");
		case 543: format(name,32,"Sadler");
		case 544: format(name,32,"Firetruck LA");
		case 545: format(name,32,"Hustler");
		case 546: format(name,32,"Intruder");
		case 547: format(name,32,"Primo");
		case 548: format(name,32,"Cargobob");
		case 549: format(name,32,"Tampa");
		case 550: format(name,32,"Sunrise");
		case 551: format(name,32,"Merit");
		case 552: format(name,32,"Utility Van");
		case 553: format(name,32,"Nevada");
		case 554: format(name,32,"Yosemite");
		case 555: format(name,32,"Windsor");
		case 556: format(name,32,"Monster A");
		case 557: format(name,32,"Monster B");
		case 558: format(name,32,"Uranus");
		case 559: format(name,32,"Jester");
		case 560: format(name,32,"Sultan");
		case 561: format(name,32,"Stratum");
		case 562: format(name,32,"Elegy");
		case 563: format(name,32,"Raindance");
		case 564: format(name,32,"RC Tiger");
		case 565: format(name,32,"Flash");
		case 566: format(name,32,"Tahoma");
		case 567: format(name,32,"Savanna");
		case 568: format(name,32,"Bandito");
		case 569: format(name,32,"Freight Flat Trailer");
		case 570: format(name,32,"Streak Trailer");
		case 571: format(name,32,"Kart");
		case 572: format(name,32,"Mower");
		case 573: format(name,32,"Dune");
		case 574: format(name,32,"Sweeper");
		case 575: format(name,32,"Broadway");
		case 576: format(name,32,"Tornado");
		case 577: format(name,32,"AT400");
		case 578: format(name,32,"DFT-30");
		case 579: format(name,32,"Huntley");
		case 580: format(name,32,"Stafford");
		case 581: format(name,32,"BF-400");
		case 582: format(name,32,"Newsvan");
		case 583: format(name,32,"Tug");
		case 584: format(name,32,"Petrol Trailer");
		case 585: format(name,32,"Emperor");
		case 586: format(name,32,"Wayfarer");
		case 587: format(name,32,"Euros");
		case 588: format(name,32,"Hotdog");
		case 589: format(name,32,"Club");
		case 590: format(name,32,"Freight Box Trailer");
		case 591: format(name,32,"Article Trailer 3");
		case 592: format(name,32,"Andromada");
		case 593: format(name,32,"Dodo");
		case 594: format(name,32,"RC Cam");
		case 595: format(name,32,"Launch");
		case 596: format(name,32,"Police Car (LSPD)");
		case 597: format(name,32,"Police Car (SFPD)");
		case 598: format(name,32,"Police Car (LVPD)");
		case 599: format(name,32,"Police Ranger");
		case 600: format(name,32,"Picador");
		case 601: format(name,32,"S.W.A.T.");
		case 602: format(name,32,"Alpha");
		case 603: format(name,32,"Phoenix");
		case 604: format(name,32,"Glendale Shit");
		case 605: format(name,32,"Sadler Shit");
		case 606: format(name,32,"Baggage Trailer A");
		case 607: format(name,32,"Baggage Trailer B");
		case 608: format(name,32,"Tug Stairs Trailer");
		case 609: format(name,32,"Boxville");
		case 610: format(name,32,"Farm Trailer");
		case 611: format(name,32,"Utility Trailer");
	}
	return name;
}

stock SaveInPlayerLog(playerid, txt[])
{
	mq_format("INSERT INTO `chat_log` (`uid`,`chat`,`time`) VALUES ('%d','%e',CURRENT_TIMESTAMP);",GetPlayerUID(playerid),txt);
	mq_send("SendChatQuery");
	return 1;
}

stock GetPlayerUID(playerid) return gracz[playerid][UID];

stock DzienTygodnia(day)
{
	new str_dzien[16];
	switch(day)
	{
		case 0: format(str_dzien, 16, "poniedzialek");
		case 1: format(str_dzien, 16, "wtorek");
		case 2: format(str_dzien, 16, "sroda");
		case 3: format(str_dzien, 16, "czwartek");
		case 4: format(str_dzien, 16, "piatek");
		case 5: format(str_dzien, 16, "sobota");
		case 6: format(str_dzien, 16, "niedziela");
	}
	return str_dzien;
}


stock SecToTime(seconds, &days, &hours, &minutes, &secc)
{
	while(seconds > 59)
	{
		seconds -= 60;
		minutes++;
	}
	while(minutes > 59)
	{
		minutes -= 60;
		hours++;
	}
	while(hours > 23)
	{
		hours -= 24;
		days++;
	}
	secc = seconds;
	return 1;
}

//System hałasu
/*GetPlayerSpeed(playerid):
5 = chodzenie
13 = Chodzenie na kucaka.
19 Bieg.
*/
new Float:ST[4][MAX_PLAYERS];
stock GetDzwiek(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && EngineStatus(GetPlayerVehicleID(playerid))) return 20;
	GetPlayerVelocity(playerid,ST[0][playerid],ST[1][playerid],ST[2][playerid]);
	ST[3][playerid] = floatsqroot(floatpower(floatabs(ST[0][playerid]), 2.0) + floatpower(floatabs(ST[1][playerid]), 2.0) + floatpower(floatabs(ST[2][playerid]), 2.0)) * 179.28625;
	return floatround(ST[3][playerid]);
}
new Float:STP[4][MAX_VEHICLES];
stock GetVehSpeed(vehicleid)
{
	GetVehicleVelocity(vehicleid,STP[0][vehicleid],STP[1][vehicleid],STP[2][vehicleid]);
	STP[3][vehicleid] = floatsqroot(floatpower(floatabs(STP[0][vehicleid]), 2.0) + floatpower(floatabs(STP[1][vehicleid]), 2.0) + floatpower(floatabs(STP[2][vehicleid]), 2.0)) * 179.28625;
	return floatround(STP[3][vehicleid]);
}

stock GetSpeedXY(playerid)
{
	GetPlayerVelocity(playerid,ST[0][playerid],ST[1][playerid],ST[2][playerid]);
	ST[3][playerid] = floatsqroot(floatpower(floatabs(ST[0][playerid]), 2.0) + floatpower(floatabs(ST[1][playerid]), 2.0)) * 179.28625;
	return floatround(ST[3][playerid]);
}

stock IsPlayerCrouch(playerid)
{
	if(GetPlayerAnimationIndex(playerid) == 1159) return 1;
	return 0;
}

stock MessageGUI(playerid,firstmessage[],secondmessage[],button1[],button2[])
{
	return ShowPlayerDialog(playerid,146,DIALOG_STYLE_MSGBOX,firstmessage,secondmessage,button1,button2);
}

stock MessageGUIEx(playerid, tytul[],  info[])
{
	MessageGUI(playerid, tytul, info, "Zamknij", "");
	return 1;
}




stock GetWeaponModel(weaponid)
{
	switch(weaponid)
	{
		case 1:
		return 331;
		case 2..8:
		return weaponid+331;
		case 9:
		return 341;
		case 10..15:
		return weaponid+311;
		case 16..18:
		return weaponid+326;
		case 22..29:
		return weaponid+324;
		case 30,31:
		return weaponid+325;
		case 32:
		return 372;
		case 33..45:
		return weaponid+324;
		case 46:
		return 371;
	}
	return 0;
}

stock IsAnyWeaponUsed(playerid)
{
	new wynik = 0;
	mq_format("SELECT `count` FROM `przedmioty` WHERE `userid` = '%d' AND (`itemid`>='1' AND `itemid`<='46') AND `used`='1';", gracz[playerid][UID]);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	wynik = cache_get_row_count();
	cache_delete(itemquery, MySQL);
	return wynik;
}


stock GiveWeapon(playerid, weaponid)
{
	reload_weapons(playerid);
	switch(weaponid)
	{
		case 0, 1:
		{
			if(IsWeaponSlotUsed(playerid, 0)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 2, 3, 4, 5, 6, 7, 8, 9:
		{
			if(IsWeaponSlotUsed(playerid, 1)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 22, 23, 24:
		{
			if(IsWeaponSlotUsed(playerid, 2)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 25, 26, 27:
		{
			if(IsWeaponSlotUsed(playerid, 3)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 28, 29, 32:
		{
			if(IsWeaponSlotUsed(playerid, 4)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 30, 31:
		{
			if(IsWeaponSlotUsed(playerid, 5)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 33, 34:
		{
			if(IsWeaponSlotUsed(playerid, 6)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 35, 36, 37, 38:
		{
			if(IsWeaponSlotUsed(playerid, 7)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 16, 17, 18, 39:
		{
			if(IsWeaponSlotUsed(playerid, 8)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 41, 42, 43:
		{
			if(IsWeaponSlotUsed(playerid, 9)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 10, 11, 12, 13, 14, 15:
		{
			if(IsWeaponSlotUsed(playerid, 10)) return 0;
			weapon[playerid][weaponid] = true;
		}
		case 44, 45, 46:
		{
			if(IsWeaponSlotUsed(playerid, 11)) return 0;
			weapon[playerid][weaponid] = true;
		}
	}
	reload_weapons(playerid);
	return 1;
}

stock RemoveWeapon(playerid, weaponid)
{
	if(!weapon[playerid][weaponid]) return 0;
	weapon[playerid][weaponid] = false;
	reload_weapons(playerid);
	return 1;
}

stock IsWeaponSlotUsed(playerid, slotid)
{
	new weapondata[2];
	GetPlayerWeaponData(playerid, slotid, weapondata[0], weapondata[1]);
	if(weapondata[0]) return 1;
	return 0;
}

stock reload_weapons(playerid)
{
	ResetPlayerWeapons(playerid);
	for(new w; w < 50; w++)
	{
		if(weapon[playerid][w])
		{
			GivePlayerWeapon(playerid, w, 99999);
		}
	}
	return 1;
}

stock procent(Float:value_l, Float:value_h)
{
	new Float:wynik = ((value_l / value_h) * 100.0);
	return floatround(wynik);
}

stock IsPlayerAiming(playerid) 
{
	new anim = GetPlayerAnimationIndex(playerid);
	if (((anim >= 1160) && (anim <= 1163)) || (anim == 1167) || (anim == 1365) || (anim == 1643) || (anim == 1453) || (anim == 220)) return 1;
	if(anim == 361 || anim == 363 || anim == 1331 || anim == 1449) return 1;
	if(GetPlayerWeapon(playerid) != 0)
		if(!IsPlayerInAnyVehicle(playerid))
		{
			new Keys,ud,lr;
			GetPlayerKeys(playerid,Keys,ud,lr);
			if(Keys == 128) return 1;
		}
		return 0;
	}

//Efekt bloodingu
//Obiekt: 18668
new Float:eBlood[MAX_PLAYERS][3];
new eBlood_object[MAX_PLAYERS];
new EffectBlood[MAX_PLAYERS];
stock BloodEffectRun(playerid)
{
	if(EffectBlood[playerid]) return 1;
	if(IsPlayerNPC(playerid))
	{
		FCNPC_GetPosition(playerid, eBlood[playerid][0], eBlood[playerid][1], eBlood[playerid][2]);
	}
	else
	{
		GetPlayerPos(playerid, eBlood[playerid][0], eBlood[playerid][1], eBlood[playerid][2]);
	}
	eBlood_object[playerid] = CreateObject(18668, eBlood[playerid][0], eBlood[playerid][1], eBlood[playerid][2]-2.0, 0.0, 0.0, 0.0, 300.0);
	SetTimerEx("UsunEffektKrwi", 50, false, "d", playerid);
	EffectBlood[playerid] = 1;
	return 1;
}
forward UsunEffektKrwi(playerid);
public UsunEffektKrwi(playerid)
{
	DestroyObject(eBlood_object[playerid]);
	EffectBlood[playerid] = 0;
	return 1;
}

stock RandomEx(min, max)
{
	return random(max - min) + min;
}

stock SetGoodSkillLevel(playerid)
{
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);
	return 1;
}

stock GetPlayerSpeed(playerid)
{
	if(IsPlayerInAnyVehicle(playerid)) return 0;
	new Float:STex[4];
	GetPlayerVelocity(playerid,STex[0],STex[1],STex[2]);
	STex[3] = floatsqroot(floatpower(floatabs(STex[0]), 2.0) + floatpower(floatabs(STex[1]), 2.0)) * 200.0;
	return floatround(STex[3]);
}


stock ShiftRGBAToABGR(color)
{
	new r, g, b, a;
	r = (color >>> 24);
	g = (color >>> 16 & 0xFF);
	b = (color >>> 8 & 0xFF);
	a = (color  & 0xFF);
	color = (a & 0xFF) | ((b & 0xFF) << 8) | ((g & 0xFF) << 16) | (r << 24);
	return color;
}

stock GetPlayerForumName(uid)
{
	new wynik[24],query[256];
	mysql_format(MySQL,query,256,"SELECT `master_nick` FROM `Konta` WHERE `id`='%d';",uid);
	new Cache:result = mysql_query(MySQL,query);
	if(cache_get_row_count()) cache_get_field_content(0, "master_nick", wynik,MySQL);
	else format(wynik,24,"-brak-");
	cache_delete(result);
	return wynik;
}
stock Error(playerid, string[])
{
	SendClientMessageEx(playerid, -1, "(("COL_RED"Wystąpił błąd:"COL_WHITE" %s"COL_WHITE"))", string);
	return 1;
}
stock GetXYInFrontOfPlayer(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	if(GetPlayerVehicleID(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}
stock compare(text1[], text2[], bool:ignorec = true)
{
	if(!strcmp(text1, text2, ignorec)) return 1;
	return 0;
}

forward Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2);
public Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return VectorSize(x1-x2, y1-y2, z1-z2);
}

stock SpawnProtect(playerid)
{
	if(_PlayerTeleporting[playerid]) return 1;
	if(gracz[playerid][sec_online] < 30 || gracz[playerid][time_spawnprotect] > serwer[time_timestamp]) return 1;
	return 0;
}

stock GiveSpawnProtect(playerid, seconds)
{
	gracz[playerid][time_spawnprotect] = serwer[time_timestamp]+seconds;
	return 1;
}

stock PlayerPoolSize() return serwer[playerPoolSize];

stock IsPlayerAFK(playerid)
{
	if(gracz[playerid][afk_control_timestamp] > serwer[time_timestamp]) return 0;
	return 1;
}

stock Interpunkcja(txt[])
{
	new wynik = 0;
	for(new i; i < strlen(txt); i++)
	{
		if(txt[i] == '.')
		{
			wynik++;
		}
		if(txt[i] == '?')
		{
			wynik++;
		}
		if(txt[i] == '!')
		{
			wynik++;
		}
	}
	return wynik;
}

stock ProxDetector(playerid, Float:radius, string[], col1, col2, col3, col4, col5)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	new Float:ix, Float:iy, Float:iz;
	new Float:cx, Float:cy, Float:cz;
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(!gracz[playerid][loggedin]) continue;
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
		{
			GetPlayerPos(i, ix, iy, iz);
			cx = (x - ix);
			cy = (y - iy);
			cz = (z - iz);
			if(((cx < radius/16) && (cx > -radius/16)) && ((cy < radius/16) && (cy > -radius/16)) && ((cz < radius/16) && (cz > -radius/16)))
			{
				SendMSGLamane(i,col1, string);
			}
			else if(((cx < radius/8) && (cx > -radius/8)) && ((cy < radius/8) && (cy > -radius/8)) && ((cz < radius/8) && (cz > -radius/8)))
			{
				SendMSGLamane(i,col2, string);
			}
			else if(((cx < radius/4) && (cx > -radius/4)) && ((cy < radius/4) && (cy > -radius/4)) && ((cz < radius/4) && (cz > -radius/4)))
			{
				SendMSGLamane(i,col3, string);
			}
			else if(((cx < radius/2) && (cx > -radius/2)) && ((cy < radius/2) && (cy > -radius/2)) && ((cz < radius/2) && (cz > -radius/2)))
			{
				SendMSGLamane(i,col4, string);
			}
			else if(((cx < radius) && (cx > -radius)) && ((cy < radius) && (cy > -radius)) && ((cz < radius) && (cz > -radius)))
			{
				SendMSGLamane(i,col5, string);
			}
		}
	}
	return 1;
}

#define EX_SPLITLENGTH 90
stock SendMSGLamane(playerid, color, final[])
{
	new buffer[EX_SPLITLENGTH+15];
	new len = strlen(final);
	if(len>EX_SPLITLENGTH)
	{
		new times = (len/EX_SPLITLENGTH);
		for(new i = 0; i < times+1; i++)
		{
			strdel(buffer, 0, EX_SPLITLENGTH+15);
			if(len-(i*EX_SPLITLENGTH)>EX_SPLITLENGTH)
			{
				strmid(buffer, final, EX_SPLITLENGTH*i, EX_SPLITLENGTH*(i+1));
				format(buffer, sizeof(buffer), "%s...", buffer);
			}
			else
			{
				strmid(buffer, final, EX_SPLITLENGTH*i, len);
			}
			SendClientMessage(playerid, color, buffer);
		}
	}
	else
	{
		SendClientMessage(playerid, color, final);
	}
	return 1;
}

stock SendNearByMessage(playerid, color, str[], Float:radius)
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(gracz[playerid][loggedin])
		{
			if(IsPlayerInRangeOfPoint(i, radius, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
			{
				if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i) && GetPlayerInterior(playerid) == GetPlayerInterior(i))
				{
					SendMSGLamane(i, color, str);
				}
			}
		}
	}
	return 1;
}

stock Spam(playerid, spamid = 0, time = 1)
{
	if(gracz[playerid][time_spam][spamid] > serwer[time_timestamp])
	{
		new str[100];
		format(str, 100, "(("COL_RED"Wystąpił błąd:"COL_WHITE" Odczekaj %d sekund.))", gracz[playerid][time_spam][spamid]-serwer[time_timestamp]);
		ov_SendClientMessage(playerid, -1, str);
		return 1;
	}
	gracz[playerid][time_spam][spamid] = serwer[time_timestamp]+time;
	return 0;
}

forward UnFreeze(playerid);
public UnFreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	return 1;
}

stock PreloadAnimations(playerid)
{
	static s_AnimationLibraries[][] = 
	{
		"AIRPORT",    "ATTRACTORS",   "BAR",                 "BASEBALL",
		"BD_FIRE",    "BEACH",            "BENCHPRESS",  "BF_INJECTION",
		"BIKED",          "BIKEH",        "BIKELEAP",        "BIKES",
		"BIKEV",          "BIKE_DBZ",     "BMX",             "BOMBER",
		"BOX",            "BSKTBALL",     "BUDDY",           "BUS",
		"CAMERA",         "CAR",          "CARRY",           "CAR_CHAT",
		"CASINO",         "CHAINSAW",     "CHOPPA",          "CLOTHES",
		"COACH",          "COLT45",       "COP_AMBIENT", "COP_DVBYZ",
		"CRACK",          "CRIB",         "DAM_JUMP",         "DANCING",
		"DEALER",         "DILDO",        "DODGE",            "DOZER",
		"DRIVEBYS",   "FAT",          "FIGHT_B",      "FIGHT_C",
		"FIGHT_D",    "FIGHT_E",      "FINALE",               "FINALE2",
		"FLAME",      "FLOWERS",      "FOOD",                 "FREEWEIGHTS",
		"GANGS",      "GHANDS",       "GHETTO_DB",    "GOGGLES",
		"GRAFFITI",   "GRAVEYARD",    "GRENADE",      "GYMNASIUM",
		"HAIRCUTS",   "HEIST9",       "INT_HOUSE",    "INT_OFFICE",
		"INT_SHOP",   "JST_BUISNESS", "KART",                 "KISSING",
		"KNIFE",      "LAPDAN1",              "LAPDAN2",      "LAPDAN3",
		"LOWRIDER",   "MD_CHASE",     "MD_END",               "MEDIC",
		"MISC",       "MTB",                  "MUSCULAR",     "NEVADA",
		"ON_LOOKERS", "OTB",                  "PARACHUTE",    "PARK",
		"PAULNMAC",   "PED",                  "PLAYER_DVBYS", "PLAYIDLES",
		"POLICE",     "POOL",                 "POOR",                 "PYTHON",
		"QUAD",       "QUAD_DBZ",     "RAPPING",      "RIFLE",
		"RIOT",       "ROB_BANK",     "ROCKET",               "RUSTLER",
		"RYDER",      "SCRATCHING",   "SHAMAL",               "SHOP",
		"SHOTGUN",    "SILENCED",     "SKATE",                "SMOKING",
		"SNIPER",     "SPRAYCAN",     "STRIP",                "SUNBATHE",
		"SWAT",       "SWEET",                "SWIM",                 "SWORD",
		"TANK",       "TATTOOS",              "TEC",                  "TRAIN",
		"TRUCK",      "UZI",                  "VAN",                  "VENDING",
		"VORTEX",     "WAYFARER",     "WEAPONS",      "WUZI",
		"WOP",        "GFUNK",                "RUNNINGMAN"
	};
	for(new i = 0; i < sizeof(s_AnimationLibraries); i ++)
	{
		ApplyAnimation(playerid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
	}
	return 1;
}

stock text_bar(proc)
{
	new bar[32];
	switch(proc)
	{
		case 0..9: format(bar, 32, ""COL_RED"|");
		case 10..19: format(bar, 32, ""COL_RED"||");
		case 20..29: format(bar, 32, ""COL_RED"|||");
		case 30..39: format(bar, 32, ""COL_YELLOW"||||");
		case 40..49: format(bar, 32, ""COL_YELLOW"|||||");
		case 50..59: format(bar, 32, ""COL_YELLOW"||||||");
		case 60..69: format(bar, 32, ""COL_YELLOW"|||||||");
		case 70..79: format(bar, 32, ""COL_GREEN"||||||||");
		case 80..89: format(bar, 32, ""COL_GREEN"|||||||||");
		case 90..100: format(bar, 32, ""COL_GREEN"||||||||||");
	}
	return bar;
}

new AllowedCharacters[] =
{
		"0","1","2","3","4","5","6","7","8","9",
		"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r", "s","t","u","v","w","x","y","z",
		"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
};

stock CheckAllowedChar(string[])
{
	new l=strlen(string), ll=sizeof(AllowedCharacters);
	new n;
	for(new i=0; i<l; i++)
	{
		for(n=0; n<ll; n++)
		if(string[i] == AllowedCharacters[n])
		break;
		if(n==ll)
		return false;
	}
	return true;
}


stock isvip(playerid)
{
	if(gracz[playerid][vip] > serwer[time_timestamp]) return 1;
	return 0;
}

stock GetWeaponCategory(weaponid)
{
	switch(weaponid)
	{
		case 22, 23, 24://klamki
		{
			return 1;
		}
		case 33://winchester(strzelba)
		{
			return 2;
		}
		case 25, 26://shootguny
		{
			return 3;
		}
		case 27://spas(combat)
		{
			return 4;
		}
		case 28, 29, 32://uzi, tec, mp5
		{
			return 5;
		}
		case 30://ak 47
		{
			return 6;
		}
		case 31://m4
		{
			return 7;
		}
		case 34://snajperka
		{
			return 8;
		}
	}
	return 0;
}

stock DelZeroItems()
{
	mq_format("DELETE FROM `przedmioty` WHERE `count`<='0';");
	mq_send("QDelZeroItems");
	return 1;
}