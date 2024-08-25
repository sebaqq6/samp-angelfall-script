stock ListItems(playerid)
{
	for(new eq_select_info:r; r < eq_select_info; r++)
	{
		eq_select[playerid][r] = 0;
	}
	if(gracz[playerid][BWTime]) return MessageGUI(playerid,"Informacja","Jesteœ ciê¿ko ranny - nie mo¿esz przegl¹daæ/u¿ywaæ przedmiotów.","OK","");
	if(InCombineMode(playerid)) return MessageGUI(playerid,"Informacja","Jesteœ w trybie kombinacji - nie mo¿esz przegl¹daæ/u¿ywaæ przedmiotów.","OK","");
	SyncAmmoToEQ(playerid);
	SyncWeaponCDNToEQ(playerid);
	SyncZetony(playerid);
	//mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d' ORDER BY `used` DESC, `id` ASC;", gracz[playerid][UID]);
	mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d';", gracz[playerid][UID]);
	mq_send("ShowItemsDB", "d", playerid);
	return 1;
}

new list_items[4000];
forward ShowItemsDB(playerid);
public ShowItemsDB(playerid)
{
	if(gracz[playerid][BWTime]) return MessageGUI(playerid,"Informacja","Jesteœ ciê¿ko ranny - nie mo¿esz przegl¹daæ/u¿ywaæ przedmiotów.","OK","");
	if(InCombineMode(playerid)) return MessageGUI(playerid,"Informacja","Jesteœ w trybie kombinacji - nie mo¿esz przegl¹daæ/u¿ywaæ przedmiotów.","OK","");
	new t_id, t_itemid, t_count, t_cdn, t_cdn_max, t_used;
	mq_getdata();
	if(rekordy)
	{
		new i;
		format(list_items, 4000, "UID\tNazwa przedmiotu\tIloœæ\tKondycja");
		while(i < rekordy)
		{
			t_id = cache_get_field_content_int(i, "id");
			t_itemid = cache_get_field_content_int(i, "itemid");
			t_count = cache_get_field_content_int(i, "count");
			t_cdn = cache_get_field_content_int(i, "cdn");
			t_cdn_max = cache_get_field_content_int(i, "cdn_max");
			t_used = cache_get_field_content_int(i, "used");
			if(t_count > 0) 
			{
				if(t_used)
				{
					format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_GREEN"[%s]\t"COL_DBLUE"%d\t%s", list_items, t_id, ItemName[t_itemid], t_count, eq_cdn_bar(procent(t_cdn, t_cdn_max)));
				}
				else
				{
					if(t_itemid == 100) format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_CYAN"%s\t"COL_DBLUE"%d\t%s", list_items, t_id, ItemName[t_itemid], t_count, eq_cdn_bar(procent(t_cdn, t_cdn_max)));
					else format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_EASY"%s\t"COL_DBLUE"%d\t%s", list_items, t_id, ItemName[t_itemid], t_count, eq_cdn_bar(procent(t_cdn, t_cdn_max)));
				}
			}
			i++;
		}
		new titlestr[110];
		format(titlestr, 110, ""COL_WHITE"Ekwipunek - ["COL_BLUE"Zu¿yte sloty: "COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE"]", rekordy, GetPlayerEQSize(playerid));
		Dialog_Show(playerid, EKWIPUNEK, DIALOG_STYLE_TABLIST_HEADERS, titlestr, list_items, "Wybierz", "Anuluj");
	}
	else
	{
		MessageGUI(playerid,"Informacja","Twój ekwipunek jest pusty!","OK","");
	}
	return 1;
}


Dialog:EKWIPUNEK(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SyncEQToAmmo(playerid);
		return 1;
	}
	mq_format("SELECT * FROM `przedmioty` WHERE `id`='%d' LIMIT 0,1;", strval(inputtext));
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	eq_select[playerid][s_id] = cache_get_field_content_int(0, "id");
	eq_select[playerid][s_itemid] = cache_get_field_content_int(0, "itemid");
	eq_select[playerid][s_count] = cache_get_field_content_int(0, "count");
	eq_select[playerid][s_cdn] = cache_get_field_content_int(0, "cdn");
	eq_select[playerid][s_cdn_max] = cache_get_field_content_int(0, "cdn_max");
	eq_select[playerid][s_used] = cache_get_field_content_int(0, "used");
	cache_delete(itemquery);
	if(eq_select[playerid][s_used])
	{
		//tego ifa trzeba na funkcje..
		if(ItemCanConfig(eq_select[playerid][s_itemid])) Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), ""COL_WHITE"1. "COL_ORANGE"Konfiguruj", "Wybierz", "Wróæ");
		else Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), ""COL_WHITE"1. "COL_RED"Przestañ u¿ywaæ", "Wybierz", "Wróæ");
	}
	else
	{
		new range_szafka;
		if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1MENU))
		{
			mq_format("SELECT * FROM `apartamenty` WHERE `id`='%d' AND `userid`='%d' AND `klasa`='1' LIMIT 0,1;", gracz[playerid][apid], gracz[playerid][UID]);
			itemquery = mysql_query(MySQL, mQuery);
			if(cache_get_row_count())
			{
				range_szafka = 1;
			}
			cache_delete(itemquery);
		}
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2MENU))
		{
			mq_format("SELECT * FROM `apartamenty` WHERE `id`='%d' AND `userid`='%d' AND `klasa`='2' LIMIT 0,1;", gracz[playerid][apid], gracz[playerid][UID]);
			itemquery = mysql_query(MySQL, mQuery);
			if(cache_get_row_count())
			{
				range_szafka = 1;
			}
			cache_delete(itemquery);
		}
		if(range_szafka) Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), "1. "COL_GREEN"U¿yj\n"COL_WHITE"2. "COL_RED"Wyrzuæ\n"COL_WHITE"3. "COL_RED"Zniszcz\n"COL_WHITE"4. "COL_CYAN"Schowaj do szafki", "Wybierz", "Wróæ");
		else if(IsPlayerRangeOfMagazine(playerid)) Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), "1. "COL_GREEN"U¿yj\n"COL_WHITE"2. "COL_RED"Wyrzuæ\n"COL_WHITE"3. "COL_RED"Zniszcz\n"COL_WHITE"4. "COL_CYAN"Schowaj do magazynu", "Wybierz", "Wróæ");
		else Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), "1. "COL_GREEN"U¿yj\n"COL_WHITE"2. "COL_RED"Wyrzuæ\n"COL_WHITE"3. "COL_RED"Zniszcz", "Wybierz", "Wróæ");
	}
	
	return 1;
}

Dialog:EQAKCJA(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	switch(listitem)
	{
		case 0:
		{
			UseItem(playerid, eq_select[playerid][s_itemid]);
		}
		case 1:
		{
			if(eq_select[playerid][s_count] == 1)
			{
				dialog_EQDROP(playerid, 1, 0, "1");
			}
			else
			{
				Dialog_Show(playerid, EQDROP, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzuciæ na ziemiê?", "Wyrzuæ", "Wróæ");
			}
		}
		case 2:
		{
			Dialog_Show(playerid, EQDESTROY, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz zniszczyæ?", "Zniszcz!", "Wróæ");
		}
		case 3:
		{
			if(IsPlayerRangeOfMagazine(playerid)) Dialog_Show(playerid, EQMGSCHOWAJ, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz schowaæ do magazynu?", "Schowaj", "Wróæ");
			else Dialog_Show(playerid, EQSZSCHOWAJ, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz schowaæ do szafki?", "Schowaj", "Wróæ");
		}
	}
	return 1;
}

Dialog:EQDROP(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1 || ilosc > 5000)
	{
		Dialog_Show(playerid, EQDROP, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzuciæ na ziemiê?\n"COL_RED"B³¹d! Niepoprawna iloœæ towaru(min: 1 | max: 5000).", "Wyrzuæ", "Wróæ");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		if(CreateItemForWorld(eq_select[playerid][s_itemid], ilosc, eq_select[playerid][s_cdn], eq_select[playerid][s_cdn_max], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], GetPlayerVirtualWorld(playerid)))
		{
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], ilosc);
			ListItems(playerid);
		}
		else
		{
			MessageGUI(playerid,"Informacja","W chwili obecnej nie da sie wyrzuciæ przedmiotu na ziemiê. Powód: zbyt du¿o przedmiotów na mapie.","OK","");
		}
	}
	else
	{
		Dialog_Show(playerid, EQDROP, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzuciæ na ziemiê?\n"COL_RED"B³¹d! Brak takiej iloœci towaru.", "Wyrzuæ", "Wróæ");
	}
	return 1;
}

Dialog:EQDESTROY(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1)
	{
		Dialog_Show(playerid, EQDESTROY, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz zniszczyæ?\n"COL_RED"B³¹d! Nie wykryto wprowadzonej iloœci.", "Zniszcz!", "Wróæ");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], ilosc);
		ListItems(playerid);
	}
	else
	{
		Dialog_Show(playerid, EQDESTROY, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzuciæ na ziemiê?\n"COL_RED"B³¹d! Brak takiej iloœci towaru.", "Zniszcz!", "Wróæ");
	}
	return 1;
}

Dialog:EQSZSCHOWAJ(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1 || ilosc > 5000)
	{
		Dialog_Show(playerid, EQSZSCHOWAJ, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz schowaæ do szafki?\n"COL_RED"B³¹d! Niepoprawna iloœæ towaru(min: 1 | max: 5000).", "Wyrzuæ", "Wróæ");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		if(CreateItemForSzafka(playerid, eq_select[playerid][s_itemid], ilosc, eq_select[playerid][s_cdn], eq_select[playerid][s_cdn_max]))
		{
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], ilosc);
			ListItems(playerid);
		}
	}
	else
	{
		Dialog_Show(playerid, EQSZSCHOWAJ, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz schowaæ do szafki?\n"COL_RED"B³¹d! Brak takiej iloœci towaru.", "Wyrzuæ", "Wróæ");
	}
	return 1;
}


Dialog:EQMGSCHOWAJ(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1 || ilosc > 5000)
	{
		Dialog_Show(playerid, EQMGSCHOWAJ, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz schowaæ do magazynu?\n"COL_RED"B³¹d! Niepoprawna iloœæ towaru(min: 1 | max: 5000).", "Wyrzuæ", "Wróæ");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		if(CreateItemForMagazyn(playerid, eq_select[playerid][s_itemid], ilosc, eq_select[playerid][s_cdn], eq_select[playerid][s_cdn_max]))
		{
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], ilosc);
			ListItems(playerid);
		}
	}
	else
	{
		Dialog_Show(playerid, EQMGSCHOWAJ, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz schowaæ do magazynu?\n"COL_RED"B³¹d! Brak takiej iloœci towaru.", "Wyrzuæ", "Wróæ");
	}
	return 1;
}



stock CreateItemForPlayer(playerid, item_id, item_count, item_cdn = 100, item_cdn_max = 100)
{
	SyncAmmoToEQ(playerid);
	mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count() && StackedItem(item_id))
	{
		new t_id = cache_get_field_content_int(0, "id");
		cache_delete(itemquery);
		mq_format("UPDATE `przedmioty` SET `count`=`count`+'%d' WHERE `id`='%d';", item_count, t_id);
		mysql_query(MySQL, mQuery, false);
		SyncEQToAmmo(playerid);
		SyncZetony(playerid);
	}
	else
	{			
		cache_delete(itemquery);
		mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d';", gracz[playerid][UID]);
		itemquery = mysql_query(MySQL, mQuery);
		if(cache_get_row_count() >= GetPlayerEQSize(playerid))
		{
			cache_delete(itemquery,MySQL);
			MessageGUI(playerid,"Informacja","Brak miejsca w ekwipunku!","OK","");
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 0;
		}
		cache_delete(itemquery,MySQL);
		mq_format("INSERT INTO `przedmioty` VALUES(NULL, '%d', '%d', '%d', '%d', '%d', '0');", gracz[playerid][UID], item_id, item_count, item_cdn, item_cdn_max);
		mysql_query(MySQL, mQuery, false);
		SyncEQToAmmo(playerid);
		SyncZetony(playerid);
	}
	if(pKrypta[playerid][pk_status] == 9) pKrypta[playerid][pk_status] = 10;
	return 1;
}


stock RemoveItemFromPlayer(playerid, item_id, item_count)//wed³ug ITEMID
{
	if(item_count < 1) return 0;
	SyncAmmoToEQ(playerid);
	mq_format("SELECT `id`,`count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count())
	{
		new t_id = cache_get_field_content_int(0, "id");
		new t_count = cache_get_field_content_int(0, "count");
		if(item_count > t_count)
		{
			if(item_id == 100) MessageGUI(playerid,"Informacja",""COL_GREY"Nie posiadasz takiej iloœci "COL_CYAN"¿etonów"COL_GREY".","OK","");
			else MessageGUI(playerid,"Informacja","Nie posiadasz tyle iloœci towaru!","OK","");
			cache_delete(itemquery,MySQL);
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 0;
		} 
		else if(item_count == t_count)
		{
			mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 1;
		}
		else
		{
			mq_format("UPDATE `przedmioty` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 1;
		}
	}
	if(item_id == 100) MessageGUI(playerid,"Informacja",""COL_GREY"Nie posiadasz takiej iloœci "COL_CYAN"¿etonów"COL_GREY".","OK","");
	else MessageGUI(playerid,"Informacja","Nie posiadasz tyle iloœci towaru!","OK","");
	cache_delete(itemquery,MySQL);
	SyncEQToAmmo(playerid);	
	return 0;
}


stock RemoveItemFromPlayerEx(playerid, t_id, item_count)//wed³ug ID
{
	if(item_count < 1) return 0;
	SyncAmmoToEQ(playerid);
	mq_format("SELECT `count` FROM `przedmioty` WHERE `id`='%d' LIMIT 0,1;", t_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count())
	{
		new t_count = cache_get_field_content_int(0, "count");
		if(item_count > t_count)
		{
			MessageGUI(playerid,"Informacja","Nie posiadasz tyle iloœci towaru!","OK","");
			cache_delete(itemquery,MySQL);
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 0;
		} 
		else if(item_count == t_count)
		{
			mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 1;
		}
		else
		{
			mq_format("UPDATE `przedmioty` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			SyncEQToAmmo(playerid);
			SyncZetony(playerid);
			return 1;
		}
	}
	MessageGUI(playerid,"Informacja","Nie posiadasz tyle iloœci towaru!","OK","");
	cache_delete(itemquery,MySQL);
	SyncEQToAmmo(playerid);
	return 0;
}

stock Title_SelectItem(playerid)
{
	new titlestr[200];
	format(titlestr, 200, ""COL_WHITE"Ekwipunek - ["COL_RED"%s"COL_WHITE"]["COL_GREEN"Iloœæ: "COL_RED"%d"COL_WHITE"]", ItemName[eq_select[playerid][s_itemid]], eq_select[playerid][s_count]);
	return titlestr;
}

stock GetItemValueForPlayer(playerid, item_id)//wed³ugi itemid
{
	SyncAmmoToEQ(playerid);
	mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	new ilosc;
	if(cache_get_row_count())
	{
		ilosc = cache_get_field_content_int(0, "count");
	}
	cache_delete(itemquery,MySQL);
	return ilosc;
}

/*
stock GetItemValueForPlayerEx(playerid, t_id)//wed³ug id
{
	SyncAmmoToEQ(playerid);
	mq_format("SELECT `count` FROM `przedmioty` WHERE `id`='%d' LIMIT 0,1;", t_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	new ilosc = cache_get_row_count();
	cache_delete(itemquery,MySQL);
	return ilosc;
}
*/

/*stock GetItemCdnPlayer(playerid, item_id)
{
	mq_format("SELECT `cdn` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	new cdn;
	if(cache_get_row_count())
	{
		cdn = cache_get_field_content_int(0, "cdn");
	}
	cache_delete(itemquery,MySQL);
	return cdn;
}*/

stock RemoteUseItem(playerid, itemid, itemuid)
{
	new remote_str[256];
	format(remote_str, 256, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_GREY"WprowadŸ ID gracza, na którym chcesz u¿yæ tego przedmiotu ("COL_GREEN"Twoje ID: "COL_RED"%d"COL_GREY"):", playerid);
	Dialog_Show(playerid, ITEMREMOTE, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), remote_str, "U¿yj!", "Anuluj");
	SetPVarInt(playerid, "remoteuseitem_itemid", itemid);
	SetPVarInt(playerid, "remoteuseitem_itemuid", itemuid);
	return 1;
}

Dialog:ITEMREMOTE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = strval(inputtext);
	if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Ten gracz jest za daleko.");
	SetPVarInt(playerid, "remoteuseitem_targetid", targetid);
	StartCombineMode(playerid, 12);
	return 1;
}

stock eq_cdn_bar(cd)
{
	new bar[32];
	switch(cd)
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

stock SyncAmmoToEQ(playerid)
{
	mq_format("SELECT `id`,`itemid` FROM `przedmioty` WHERE `userid` = '%d' AND ((`itemid`>='47' AND `itemid`<='52') OR (`itemid`>='58' AND `itemid`<='65'));", gracz[playerid][UID]);
	new Cache:ammoquery = mysql_query(MySQL, mQuery);
	new rekordy = cache_get_row_count();
	if(rekordy)
	{
		new i;
		new t_itemid;
		new t_id;
		while(i < rekordy)
		{
			t_itemid = cache_get_field_content_int(i, "itemid");
			t_id = cache_get_field_content_int(i, "id");
			if(t_itemid == 47)
			{
				if(ammo[playerid][22])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][22], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 48)
			{
				if(ammo[playerid][24])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][24], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 49)
			{
				if(ammo[playerid][25])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][25], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 50)
			{
				if(ammo[playerid][26])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][26], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 51)
			{
				if(ammo[playerid][27])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][27], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 52)
			{
				if(ammo[playerid][28])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][28], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 58)
			{
				if(ammo[playerid][29])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][29], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 59)
			{
				if(ammo[playerid][32])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][32], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 60)
			{
				if(ammo[playerid][30])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][30], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 61)
			{
				if(ammo[playerid][31])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][31], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 62)
			{
				if(ammo[playerid][33])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][33], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 63)
			{
				if(ammo[playerid][34])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][34], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 64)
			{
				if(ammo[playerid][35])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][35], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			else if(t_itemid == 65)
			{
				if(ammo[playerid][38])
				{
					mq_format("UPDATE `przedmioty` SET `count`='%d' WHERE `id`='%d';", ammo[playerid][38], t_id);
					mysql_query(MySQL, mQuery, false);
				}
				else
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mysql_query(MySQL, mQuery, false);
				}
			}
			i++;
		}
	}
	cache_delete(ammoquery,MySQL);
	return 1;
}

stock SyncEQToAmmo(playerid)
{
	mq_format("SELECT `count`,`itemid` FROM `przedmioty` WHERE `userid` = '%d' AND ((`itemid`>='47' AND `itemid`<='52') OR (`itemid`>='58' AND `itemid`<='65'));", gracz[playerid][UID]);
	new Cache:ammoquery = mysql_query(MySQL, mQuery);
	new rekordy = cache_get_row_count();
	for(new a; a < 50; a++)
	{
		ammo[playerid][a] = 0; 
	}
	if(rekordy)
	{
		new i;
		new t_itemid, t_count;
		while(i < rekordy)
		{
			t_itemid = cache_get_field_content_int(i, "itemid");
			t_count = cache_get_field_content_int(i, "count");
			if(t_itemid == 47)
			{
				if(t_count)
				{
					ammo[playerid][22] = t_count;
				}
			}
			else if(t_itemid == 48)
			{
				if(t_count)
				{
					ammo[playerid][24] = t_count;
				}
			}
			else if(t_itemid == 49)
			{
				if(t_count)
				{
					ammo[playerid][25] = t_count;
				}
			}
			else if(t_itemid == 50)
			{
				if(t_count)
				{
					ammo[playerid][26] = t_count;
				}
			}
			else if(t_itemid == 51)
			{
				if(t_count)
				{
					ammo[playerid][27] = t_count;
				}
			}
			else if(t_itemid == 52)
			{
				if(t_count)
				{
					ammo[playerid][28] = t_count;
				}
			}
			else if(t_itemid == 58)
			{
				if(t_count)
				{
					ammo[playerid][29] = t_count;
				}
			}
			else if(t_itemid == 59)
			{
				if(t_count)
				{
					ammo[playerid][32] = t_count;
				}
			}
			else if(t_itemid == 60)
			{
				if(t_count)
				{
					ammo[playerid][30] = t_count;
				}
			}
			else if(t_itemid == 61)
			{
				if(t_count)
				{
					ammo[playerid][31] = t_count;
				}
			}
			else if(t_itemid == 62)
			{
				if(t_count)
				{
					ammo[playerid][33] = t_count;
				}
			}
			else if(t_itemid == 63)
			{
				if(t_count)
				{
					ammo[playerid][34] = t_count;
				}
			}
			else if(t_itemid == 64)
			{
				if(t_count)
				{
					ammo[playerid][35] = t_count;
				}
			}
			else if(t_itemid == 65)
			{
				if(t_count)
				{
					ammo[playerid][38] = t_count;
				}
			}
			i++;
		}
	}
	cache_delete(ammoquery, MySQL);
	RefreshAmmo(playerid);
	return 1;
}


stock SyncWeaponCDNToEQ(playerid)
{ 
	mq_format("SELECT `id`,`itemid` FROM `przedmioty` WHERE `userid` = '%d' AND (`itemid`>='1' AND `itemid`<='46') AND `used`='1';", gracz[playerid][UID]);
	new Cache:cdnquery = mysql_query(MySQL, mQuery);
	new rekordy = cache_get_row_count();
	if(rekordy)
	{
		new i;
		new t_id, t_itemid;
		while(i < rekordy)
		{
			t_id = cache_get_field_content_int(i, "id");
			t_itemid = cache_get_field_content_int(i, "itemid");
			if(w_cdn_max[playerid][t_itemid])
			{
				mq_format("UPDATE `przedmioty` SET `cdn`='%d', `cdn_max`='%d' WHERE `id`='%d';", w_cdn[playerid][t_itemid], w_cdn_max[playerid][t_itemid], t_id);
				mysql_query(MySQL, mQuery, false);	
			}		
			i++;
		}
	}
	cache_delete(cdnquery, MySQL);
	return 1;
}
//
stock SyncZetony(playerid)
{
	mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='100';", gracz[playerid][UID]);
	mq_send("ZetonyUpdate", "d", playerid);
	return 1;
}
forward ZetonyUpdate(playerid);
public ZetonyUpdate(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		gracz[playerid][zetony] = cache_get_field_content_int(0, "count");
	}
	else
	{
		gracz[playerid][zetony] = 0;
	}
	return 1;
}
//usuwanie przedmiotów - wszystko cache
stock DropItems(playerid, dont_syncw = 0)
{
	for(new eq_select_info:r; r < eq_select_info; r++)
	{
		eq_select[playerid][r] = 0;
	}
	if(dont_syncw == 1)
	{
		SyncAmmoToEQ(playerid);
		SyncWeaponCDNToEQ(playerid);
	}
	mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d';", gracz[playerid][UID]);
	mq_send("InventoryDropAll", "d", playerid);
	Dialog_Close(playerid);
	return 1; 
}

forward InventoryDropAll(playerid);
public InventoryDropAll(playerid)
{
	Dialog_Close(playerid);
	new t_id, t_itemid, t_count, t_cdn, t_cdn_max;
	new Float:rand_pos;
	mq_getdata();
	if(rekordy)
	{
		new i;
		while(i < rekordy)
		{
			rand_pos += 0.10;
			t_id = cache_get_field_content_int(i, "id");
			t_itemid = cache_get_field_content_int(i, "itemid");
			t_count = cache_get_field_content_int(i, "count");
			t_cdn = cache_get_field_content_int(i, "cdn");
			t_cdn_max = cache_get_field_content_int(i, "cdn_max");
			if(t_count > 0)
			{
				if(CreateItemForWorld(t_itemid, t_count, t_cdn, t_cdn_max, gracz[playerid][PosX]+rand_pos, gracz[playerid][PosY]+rand_pos, gracz[playerid][PosZ], GetPlayerVirtualWorld(playerid)))
				{
					mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
					mq_send("QDropItem");
				}
			}
			i++;
		}
	}
	return 1;
}

stock GetPlayerEQSize(playerid)
{
	new max_slots = gracz[playerid][MaxEQ];
	if(isvip(playerid)) max_slots += 6;
	if(gracz[playerid][sila] > 90) max_slots += 4;
	return max_slots;
}