#define MAX_BAZ 10
enum baza_info
{
	bool:b_active,
	b_owner,
	b_price,
	b_gate_id,
	b_gate_model,
	Float:b_gate_close[6],
	Float:b_gate_open[6],
	b_area_id,
	Text3D:b_label,
	Float:b_magazyn[3],
	Float:b_pickup[3]
};

new baza[MAX_BAZ][baza_info];
new baza_allowedObjects[] = 
{
	925, 944, 1431, 931, 1362, 943, 1665, 1494, 1499, 941, 1755, 1767, 2063, 1800, 1801, 1812, 1778, 2514, 2518, 19915, 11496, 1483, 1458, 1482, 1452, 3403, 17074, 3415, 19303, 19429, 19436,
	19922,19996,11727,11730,2526,3425,2811,1735,1729,2096,2343,1437,1472,1426,3860,765,766,885,2561,2558,19585,19587,19918,19903,19900,19899,19848,19843,19815,19817,19893,11690,11712,19170,1755,
	2066,2067,2007,2000,2419,2463,2737,2610,1749,2812,2813,2815,3280,19087,2061,2060,2064,2690,1654,18609,19277,2011,2251,2254,3813,2589,2590,2484,3632,2669,964,2358,
	3461, 12957, 3252, 19392, 19386, 19444, 19398, 19356, 19363, 19371, 3279, 16093, 16638
};
//dane baz:
#include "modules/bazy_grup/baza_chilliad_0.inc"
#include "modules/bazy_grup/baza_bob_1.inc"

stock Init_BazyGrup()
{
	//ładowanie baz:
	baza_chilliad_0();
	baza_bob_1();

	//przypisanie grup do baz:
	mq_format("SELECT * FROM `Grupy` WHERE `baza_expire`>'%d';", serwer[time_timestamp]);
	mq_send("QLoadBaseGroup");
	return 1;
}

forward QLoadBaseGroup();
public QLoadBaseGroup()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new gid;
		new baza_id;
		while(i < rekordy)
		{
			gid = cache_get_field_content_int(i, "id");
			baza_id = cache_get_field_content_int(i, "baza");
			if(baza[baza_id][b_active]) baza[baza_id][b_owner] = gid;
			i++; 
		}
	}
	//przygotowanie bramy, pickupów itd baz:
	new str[512];
	for(new b; b < MAX_BAZ; b++)
	{

		if(!baza[b][b_active]) continue;
		if(baza[b][b_gate_model]) baza[b][b_gate_id] = CreateDynamicObject(baza[b][b_gate_model], baza[b][b_gate_close][0], baza[b][b_gate_close][1], baza[b][b_gate_close][2], baza[b][b_gate_close][3], baza[b][b_gate_close][4], baza[b][b_gate_close][5]);
		CreateDynamicPickup(1254, 1, baza[b][b_pickup][0], baza[b][b_pickup][1], baza[b][b_pickup][2]);
		CreateDynamicPickup(1277, 1, baza[b][b_magazyn][0], baza[b][b_magazyn][1], baza[b][b_magazyn][2]);
		CreateDynamic3DTextLabel(""COL_RED"> "COL_CYAN" Magazyn "COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, baza[b][b_magazyn][0], baza[b][b_magazyn][1], baza[b][b_magazyn][2], 10.0, _, _,  1);
		if(baza[b][b_owner]) format(str, 512, ""COL_RED"["COL_WHITE"Baza grupowa(id: %d) - "COL_RED"Zajęta"COL_RED"]\n"COL_EASY"["COL_LIME"Użycie:"COL_WHITE" /baza"COL_EASY"]", b);
		else 
		{
			DeleteObjectFromBase(b);
			format(str, 512, ""COL_RED"["COL_WHITE"Baza grupowa(id: %d) - "COL_GREEN"Wolna"COL_RED"]\n"COL_EASY"["COL_LIME"Użycie:"COL_WHITE" /baza"COL_EASY"]", b);
			mq_format("DELETE FROM `items_bazy` WHERE `baseid`='%d';", b);
			mq_send("QDeleteItems");
		}
		baza[b][b_label] = CreateDynamic3DTextLabel(str, -1, baza[b][b_pickup][0], baza[b][b_pickup][1], baza[b][b_pickup][2], 10.0);
		CreateDynamicMapIcon(baza[b][b_pickup][0], baza[b][b_pickup][1], baza[b][b_pickup][2], 8, -1, _, _, _, 9000.0, MAPICON_GLOBAL);
	}
	return 1;
}

stock GetGroupBaseID(groupid)
{
	if(groupid == 0) return -1;
	for(new b; b < MAX_BAZ; b++)
	{
		if(!baza[b][b_active]) continue;
		if(groupid == baza[b][b_owner]) return b;
	}
	return -1;
}

stock PickupGetBaseID(playerid)
{
	for(new b; b < MAX_BAZ; b++)
	{
		if(!baza[b][b_active]) continue;
		if(IsPlayerInRangeOfPoint(playerid, 2.0, baza[b][b_pickup][0], baza[b][b_pickup][1], baza[b][b_pickup][2])) return b;
	}
	return -1;
}

stock IsPlayerRangeOfMagazine(playerid)
{
	new groupid = gracz[playerid][OrgID];
	if(groupid)
	{
		new group_base = GetGroupBaseID(groupid);
		if(group_base != -1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, baza[group_base][b_magazyn][0], baza[group_base][b_magazyn][1], baza[group_base][b_magazyn][2])) return 1;
		}
	}
	return 0;
}

stock IsPlayerInBaseArea(playerid)
{
	new groupid = gracz[playerid][OrgID];
	if(groupid)
	{
		new group_base = GetGroupBaseID(groupid);
		if(group_base != -1)
		{
			if(IsPlayerInDynamicArea(playerid, baza[group_base][b_area_id])) return 1;
		}
	}
	return 0;
}

stock IsPointInBaseArea(playerid, Float:bX, Float:bY, Float:bZ)
{
	new groupid = gracz[playerid][OrgID];
	if(groupid)
	{
		new group_base = GetGroupBaseID(groupid);
		if(group_base != -1)
		{
			if(IsPointInDynamicArea(baza[group_base][b_area_id], bX, bY, bZ)) return 1;
		}
	}
	return 0;
}

stock IsPointInAnyBaseArea(Float:bX, Float:bY, Float:bZ)
{
	for(new b; b < MAX_BAZ; b++)
	{
		if(!baza[b][b_active]) continue;
		if(IsPointInDynamicArea(baza[b][b_area_id], bX, bY, bZ)) return 1;
	}
	return 0;
}


stock BaseObjectIsAllowed(model)
{
	for(new o; o < sizeof(baza_allowedObjects); o++)
	{
		if(baza_allowedObjects[o] == model) return 1;
	}
	return 0;
}

stock DeleteObjectFromBase(baza_id)
{
	for(new i; i < MAX_OBJECTS; i++)//usuwanie obiektów z bazy, jeśli wolna
	{
		if(ObjectInfo[i][oGrupa] <= 0) continue;
		if(IsPointInDynamicArea(baza[baza_id][b_area_id], ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]))
		{
			DeleteObject(ObjectInfo[i][oUID]);
		}
	}
	return 1;
}

stock Baza_OpenGate(baza_id)
{
	MoveDynamicObject(baza[baza_id][b_gate_id], baza[baza_id][b_gate_open][0], baza[baza_id][b_gate_open][1], baza[baza_id][b_gate_open][2], 2.0, baza[baza_id][b_gate_open][3], baza[baza_id][b_gate_open][4], baza[baza_id][b_gate_open][5]);
	return 1;
}

stock Baza_CloseGate(baza_id)
{
	MoveDynamicObject(baza[baza_id][b_gate_id], baza[baza_id][b_gate_close][0], baza[baza_id][b_gate_close][1], baza[baza_id][b_gate_close][2], 2.0, baza[baza_id][b_gate_close][3], baza[baza_id][b_gate_close][4], baza[baza_id][b_gate_close][5]);
	return 1;
}

//new baza_id = GetGroupBaseID(groupid);
//if(baza_id != -1) return Error(playerid, "Twoja grupa posiada już bazę.");
CMD:baza(playerid, params[])
{
	new groupid = gracz[playerid][OrgID];
	if(!groupid) return Error(playerid, "Nie należysz do grupy.");
	if(!gracz[playerid][SzefORG]) return Error(playerid, "Musisz być liderem.");
	new pickBazaID = PickupGetBaseID(playerid);
	if(pickBazaID == -1) return Error(playerid, "W tym miejscu nie możesz użyć tej komendy.");
	new group_base = GetGroupBaseID(groupid);
	new str_baza[1024];
	new str_header[128];
	format(str_header, 128, ""COL_CYAN"»"COL_GREY" Baza grupowa "COL_RED"["COL_GREY"ID: "COL_CYAN"%d"COL_RED"]", pickBazaID);
	if(group_base == -1)
	{
		format(str_baza, 1024, ""COL_RED"» "COL_GREEN"Kup bazę"COL_GREY"["COL_YELLOW"%d "COL_CYAN"żetonów"COL_GREY"]["COL_RED"20 dni"COL_GREY"]", baza[pickBazaID][b_price]);
		format(str_baza, 1024, "%s\n"COL_RED"» "COL_GREEN"Kup bazę"COL_GREY"["COL_YELLOW"300 "COL_YELLOW"żp"COL_GREY"]["COL_RED"20 dni"COL_GREY"]", str_baza);
		Dialog_Show(playerid, BAZAMENU, DIALOG_STYLE_LIST, str_header, str_baza, "Wybierz", "Anuluj");
	}
	else if(group_base == pickBazaID) 
	{
		format(str_baza, 1024, ""COL_RED"» "COL_GREEN"Przedłuż ważność bazy"COL_GREY"["COL_YELLOW"%d "COL_CYAN"żetonów"COL_GREY"]["COL_RED"20 dni"COL_GREY"]", baza[pickBazaID][b_price]);
		format(str_baza, 1024, "%s\n"COL_RED"» "COL_GREEN"Przedłuż ważność bazy"COL_GREY"["COL_YELLOW"300 "COL_YELLOW"żp"COL_GREY"]["COL_RED"20 dni"COL_GREY"]", str_baza);
		Dialog_Show(playerid, BAZAMENU, DIALOG_STYLE_LIST, str_header, str_baza, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Twoja grupa posiada już bazę.");
	return 1;
}

Dialog:BAZAMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("SELECT * FROM `Grupy` WHERE `id`='%d' LIMIT 0,1;", gracz[playerid][OrgID]);
			mq_send("QBuyBase", "d", playerid);
		}
		case 1:
		{
			mq_format("SELECT * FROM `Grupy` WHERE `id`='%d' LIMIT 0,1;", gracz[playerid][OrgID]);
			mq_send("QBuyBaseGold", "d", playerid);
		}
	}
	return 1;
}

forward QBuyBase(playerid);
public QBuyBase(playerid)
{
	new groupid = gracz[playerid][OrgID];
	if(!groupid) return Error(playerid, "Nie należysz do grupy.");
	if(!gracz[playerid][SzefORG]) return Error(playerid, "Musisz być liderem.");
	new pickBazaID = PickupGetBaseID(playerid);
	if(pickBazaID == -1) return Error(playerid, "W tym miejscu nie możesz tego zrobić.");
	new group_base = GetGroupBaseID(groupid);
	mq_getdata();
	if(rekordy)
	{
		new baza_expire = cache_get_field_content_int(0, "baza_expire");
		new id = cache_get_field_content_int(0, "id");
		if(group_base == pickBazaID)
		{
			if(RemoveItemFromPlayer(playerid, 100, baza[pickBazaID][b_price]))
			{
				if(baza_expire > serwer[time_timestamp]) baza_expire += 60*60*24*20;
				else baza_expire = serwer[time_timestamp]+60*60*24*20;
				mq_format("UPDATE `Grupy` SET `baza_expire`='%d' WHERE `id`='%d';", baza_expire, id);
				mq_send("QBuyBaseComplete");
				LeftNotifyShow(playerid, "Sukces!", "Waznosc bazy zostala ~g~przedluzona~w~ o ~y~20 dni~w~. Aby sprawdzic czas wygasniecia bazy wpisz ~y~/gpanel~w~.", LN_GREEN, 15);
			}
		}
		else if(group_base == -1)
		{
			if(RemoveItemFromPlayer(playerid, 100, baza[pickBazaID][b_price]))
			{
				baza_expire = serwer[time_timestamp]+60*60*24*20;
				baza[pickBazaID][b_owner] = gracz[playerid][OrgID];
				mq_format("UPDATE `Grupy` SET `baza`='%d', `baza_expire`='%d' WHERE `id`='%d';", pickBazaID, baza_expire, id);
				mq_send("QBuyBaseComplete");
				LeftNotifyShow(playerid, "Sukces!", "Baza zostala ~g~zakupiona~w~ na ~y~20 dni~w~. Zawsze mozesz ja przedluzyc w ten sam sposob co zakupiles. Aby sprawdzic czas wygasniecia bazy wpisz ~y~/gpanel~w~.", LN_GREEN, 15);
				new str[512];
				format(str, 512, ""COL_RED"["COL_WHITE"Baza grupowa(id: %d) - "COL_RED"Zajęta"COL_RED"]\n"COL_EASY"["COL_LIME"Użycie:"COL_WHITE" /baza"COL_EASY"]", pickBazaID);
				UpdateDynamic3DTextLabelText(baza[pickBazaID][b_label], -1, str);
			}
		}
	}
	return 1;
}

forward QBuyBaseGold(playerid);
public QBuyBaseGold(playerid)
{
	new groupid = gracz[playerid][OrgID];
	if(!groupid) return Error(playerid, "Nie należysz do grupy.");
	if(!gracz[playerid][SzefORG]) return Error(playerid, "Musisz być liderem.");
	new pickBazaID = PickupGetBaseID(playerid);
	if(pickBazaID == -1) return Error(playerid, "W tym miejscu nie możesz tego zrobić.");
	new group_base = GetGroupBaseID(groupid);
	mq_getdata();
	if(rekordy)
	{
		new baza_expire = cache_get_field_content_int(0, "baza_expire");
		new id = cache_get_field_content_int(0, "id");
		if(group_base == pickBazaID)
		{
			if(gracz[playerid][gold] < 300) return Error(playerid, "Za mało żetonów premium.");
			gracz[playerid][gold] -= 300;
			mq_format("UPDATE `Konta` SET `gold`='%d' WHERE `id`='%d';", gracz[playerid][gold], gracz[playerid][UID]);
			mq_send("QBuyBaseGold");
			if(baza_expire > serwer[time_timestamp]) baza_expire += 60*60*24*20;
			else baza_expire = serwer[time_timestamp]+60*60*24*20;
			mq_format("UPDATE `Grupy` SET `baza_expire`='%d' WHERE `id`='%d';", baza_expire, id);
			mq_send("QBuyBaseComplete");
			LeftNotifyShow(playerid, "Sukces!", "Waznosc bazy zostala ~g~przedluzona~w~ o ~y~20 dni~w~. Aby sprawdzic czas wygasniecia bazy wpisz ~y~/gpanel~w~.", LN_GREEN, 15);
		}
		else if(group_base == -1)
		{
			if(gracz[playerid][gold] < 300) return Error(playerid, "Za mało żetonów premium.");
			gracz[playerid][gold] -= 300;
			mq_format("UPDATE `Konta` SET `gold`='%d' WHERE `id`='%d';", gracz[playerid][gold], gracz[playerid][UID]);
			mq_send("QBuyBaseGold");
			baza_expire = serwer[time_timestamp]+60*60*24*20;
			baza[pickBazaID][b_owner] = gracz[playerid][OrgID];
			mq_format("UPDATE `Grupy` SET `baza`='%d', `baza_expire`='%d' WHERE `id`='%d';", pickBazaID, baza_expire, id);
			mq_send("QBuyBaseComplete");
			LeftNotifyShow(playerid, "Sukces!", "Baza zostala ~g~zakupiona~w~ na ~y~20 dni~w~. Zawsze mozesz ja przedluzyc w ten sam sposob co zakupiles. Aby sprawdzic czas wygasniecia bazy wpisz ~y~/gpanel~w~.", LN_GREEN, 15);
			new str[512];
			format(str, 512, ""COL_RED"["COL_WHITE"Baza grupowa(id: %d) - "COL_RED"Zajęta"COL_RED"]\n"COL_EASY"["COL_LIME"Użycie:"COL_WHITE" /baza"COL_EASY"]", pickBazaID);
			UpdateDynamic3DTextLabelText(baza[pickBazaID][b_label], -1, str);
		}
	}
	return 1;
}

CMD:gmc(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!gracz[playerid][MapperLvl]) return Error(playerid, "Brak uprawnień.");
	ShowModelSelectionMenuEx(playerid, baza_allowedObjects, sizeof(baza_allowedObjects), "Dostepne obiekty", MSEL_GOBJECTS, _, _, 30.0);
	return 1;
}


//magazyn

stock MagazynShow(playerid)
{
	if(IsPlayerRangeOfMagazine(playerid))
	{
		if(Spam(playerid, SPAM_CMD, 2)) return 0;
		ListItemsMagazyn(playerid);
	}
	return 1;
}

stock ListItemsMagazyn(playerid)
{
	new group_base = GetGroupBaseID(gracz[playerid][OrgID]);
	if(group_base == -1) return Error(playerid, "Brak uprawnień.");
	for(new eq_select_info:r; r < eq_select_info; r++)
	{
		eq_select[playerid][r] = 0;
	}
	if(gracz[playerid][BWTime]) return MessageGUI(playerid,"Informacja","Jesteś ciężko ranny - nie możesz przeglądać/używać przedmiotów.","OK","");
	if(InCombineMode(playerid)) return MessageGUI(playerid,"Informacja","Jesteś w trybie kombinacji - nie możesz przeglądać/używać przedmiotów.","OK","");
	SyncZetony(playerid);
	//mq_format("SELECT * FROM `items_bazy` WHERE `baseid`='%d' ORDER BY `used` DESC, `id` ASC;", gracz[playerid][UID]);
	mq_format("SELECT * FROM `items_bazy` WHERE `baseid`='%d';", group_base);
	mq_send("ShowItemsMagazynDB", "d", playerid);
	return 1;
}

forward ShowItemsMagazynDB(playerid);
public ShowItemsMagazynDB(playerid)
{
	if(gracz[playerid][BWTime]) return MessageGUI(playerid,"Informacja","Jesteś ciężko ranny - nie możesz przeglądać/używać przedmiotów.","OK","");
	if(InCombineMode(playerid)) return MessageGUI(playerid,"Informacja","Jesteś w trybie kombinacji - nie możesz przeglądać/używać przedmiotów.","OK","");
	new t_id, t_itemid, t_count, t_cdn, t_cdn_max;
	mq_getdata();
	if(rekordy)
	{
		new i;
		format(list_items, 4000, "UID\tNazwa przedmiotu\tIlość\tKondycja");
		while(i < rekordy)
		{
			t_id = cache_get_field_content_int(i, "id");
			t_itemid = cache_get_field_content_int(i, "itemid");
			t_count = cache_get_field_content_int(i, "count");
			t_cdn = cache_get_field_content_int(i, "cdn");
			t_cdn_max = cache_get_field_content_int(i, "cdn_max");
			if(t_count > 0) 
			{
				if(t_itemid == 100) format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_CYAN"%s\t"COL_DBLUE"%d\t%s", list_items, t_id, ItemName[t_itemid], t_count, eq_cdn_bar(procent(t_cdn, t_cdn_max)));
				else format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_EASY"%s\t"COL_DBLUE"%d\t%s", list_items, t_id, ItemName[t_itemid], t_count, eq_cdn_bar(procent(t_cdn, t_cdn_max)));
			}
			i++;
		}
		new titlestr[110];
		format(titlestr, 110, ""COL_WHITE"Magazyn - ["COL_BLUE"Zużyte sloty: "COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE"]", rekordy, GetMagazynSize());
		Dialog_Show(playerid, MAGAZYN, DIALOG_STYLE_TABLIST_HEADERS, titlestr, list_items, "Wybierz", "Anuluj");
	}
	else
	{
		MessageGUI(playerid,"Informacja","Magazyn jest pusty!","OK","");
	}
	return 1;
}


Dialog:MAGAZYN(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SyncEQToAmmo(playerid);
		return 1;
	}
	mq_format("SELECT * FROM `items_bazy` WHERE `id`='%d' LIMIT 0,1;", strval(inputtext));
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	eq_select[playerid][s_id] = cache_get_field_content_int(0, "id");
	eq_select[playerid][s_itemid] = cache_get_field_content_int(0, "itemid");
	eq_select[playerid][s_count] = cache_get_field_content_int(0, "count");
	eq_select[playerid][s_cdn] = cache_get_field_content_int(0, "cdn");
	eq_select[playerid][s_cdn_max] = cache_get_field_content_int(0, "cdn_max");
	Dialog_Show(playerid, MGAKCJA, DIALOG_STYLE_LIST, TitleMagazyn_SelectItem(playerid), "1. "COL_GREEN"Wyciągnij", "Wybierz", "Wróć");
	cache_delete(itemquery);
	return 1;
}

Dialog:MGAKCJA(playerid, response, listitem, inputtext[])
{
	new group_base = GetGroupBaseID(gracz[playerid][OrgID]);
	if(group_base == -1) return Error(playerid, "Brak uprawnień.");
	if(!response) return ListItemsMagazyn(playerid);
	switch(listitem)
	{
		case 0:
		{
			if(eq_select[playerid][s_count] == 1)
			{
				dialog_MGDROP(playerid, 1, 0, "1");
			}
			else
			{
				Dialog_Show(playerid, MGDROP, DIALOG_STYLE_INPUT, TitleMagazyn_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyciągnąć?", "Wyrzuć", "Wróć");
			}
		}
	}
	return 1;
}

Dialog:MGDROP(playerid, response, listitem, inputtext[])
{
	new group_base = GetGroupBaseID(gracz[playerid][OrgID]);
	if(group_base == -1) return Error(playerid, "Brak uprawnień.");
	if(!response) return ListItemsMagazyn(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1 || ilosc > 5000)
	{
		Dialog_Show(playerid, MGDROP, DIALOG_STYLE_INPUT, TitleMagazyn_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyciągnąć?\n"COL_RED"Błąd! Niepoprawna ilość towaru(min: 1 | max: 5000).", "Wyrzuć", "Wróć");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		if(CreateItemForPlayer(playerid, eq_select[playerid][s_itemid], ilosc, eq_select[playerid][s_cdn], eq_select[playerid][s_cdn_max]))
		{
			RemoveItemFromMagazynEx(playerid, eq_select[playerid][s_id], ilosc);
			LeftNotifyShow(playerid, "Sukces!", "Wyciagnieto przedmiot z magazynu!", LN_GREEN);
		}
	}
	else
	{
		Dialog_Show(playerid, MGDROP, DIALOG_STYLE_INPUT, TitleMagazyn_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyciągnąć?\n"COL_RED"Błąd! Brak takiej ilości towaru.", "Wyrzuć", "Wróć");
	}
	return 1;
}



stock CreateItemForMagazyn(playerid, item_id, item_count, item_cdn = 100, item_cdn_max = 100)
{
	new group_base = GetGroupBaseID(gracz[playerid][OrgID]);
	if(group_base == -1) return 0;
	mq_format("SELECT * FROM `items_bazy` WHERE `baseid`='%d' AND `itemid`='%d' LIMIT 0,1;", group_base, item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count() && StackedItem(item_id))
	{
		new t_id = cache_get_field_content_int(0, "id");
		cache_delete(itemquery);
		mq_format("UPDATE `items_bazy` SET `count`=`count`+'%d' WHERE `id`='%d';", item_count, t_id);
		mysql_query(MySQL, mQuery, false);
	}
	else
	{			
		cache_delete(itemquery);
		mq_format("SELECT * FROM `items_bazy` WHERE `baseid`='%d';", group_base);
		itemquery = mysql_query(MySQL, mQuery);
		if(cache_get_row_count() >= GetMagazynSize())
		{
			cache_delete(itemquery,MySQL);
			MessageGUI(playerid,"Informacja","Brak miejsca w magazynie!","OK","");
			return 0;
		}
		cache_delete(itemquery,MySQL);
		mq_format("INSERT INTO `items_bazy` VALUES(NULL, '%d', '%d', '%d', '%d', '%d');", group_base, item_id, item_count, item_cdn, item_cdn_max);
		mysql_query(MySQL, mQuery, false);
	}
	return 1;
}


stock RemoveItemFromMagazynEx(playerid, t_id, item_count)//według ID
{
	new group_base = GetGroupBaseID(gracz[playerid][OrgID]);
	if(group_base == -1) return 0;
	if(item_count < 1) return 0;
	mq_format("SELECT `count` FROM `items_bazy` WHERE `id`='%d' LIMIT 0,1;", t_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count())
	{
		new t_count = cache_get_field_content_int(0, "count");
		if(item_count > t_count)
		{
			MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
			cache_delete(itemquery,MySQL);
			return 0;
		} 
		else if(item_count == t_count)
		{
			mq_format("DELETE FROM `items_bazy` WHERE `id`='%d';", t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			return 1;
		}
		else
		{
			mq_format("UPDATE `items_bazy` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			return 1;
		}
	}
	MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
	cache_delete(itemquery,MySQL);
	return 0;
}

stock TitleMagazyn_SelectItem(playerid)
{
	new titlestr[200];
	format(titlestr, 200, ""COL_WHITE"Magazyn - ["COL_RED"%s"COL_WHITE"]["COL_GREEN"Ilość: "COL_RED"%d"COL_WHITE"]", ItemName[eq_select[playerid][s_itemid]], eq_select[playerid][s_count]);
	return titlestr;
}

stock GetMagazynSize()
{
	new wynik = 40;
	return wynik;
}