stock Init_Apartamenty()
{
	CreatePickup(19524, 1, POS_K1OUT);//1 klasa
	CreatePickup(1272, 1, POS_K2OUT);//2 klasa
	CreateDynamic3DTextLabel(""COL_RED"> "COL_GREEN"Apartament klasa: "COL_ORANGE"I "COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, POS_K1OUT, 10.0, _, _,  1);
	CreateDynamic3DTextLabel(""COL_RED"> "COL_GREEN"Apartament klasa: "COL_ORANGE"II"COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, POS_K2OUT, 10.0, _, _,  1);
	CreatePickup(19524, 1, POS_K1IN, -1);//1 klasa
	CreatePickup(1272, 1, POS_K2IN, -1);//2 klasa
	CreateDynamic3DTextLabel(""COL_RED"> "COL_CYAN" WYJŚCIE "COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, POS_K1IN, 10.0, _, _,  1);
	CreateDynamic3DTextLabel(""COL_RED"> "COL_CYAN" WYJŚCIE "COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, POS_K2IN, 10.0, _, _,  1);
	CreatePickup(1277, 1, POS_K1MENU, -1);//1 klasa
	CreatePickup(1277, 1, POS_K2MENU, -1);//2 klasa
	CreateDynamic3DTextLabel(""COL_RED"> "COL_CYAN" Zarządzanie "COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, POS_K1MENU, 10.0, _, _,  1);
	CreateDynamic3DTextLabel(""COL_RED"> "COL_CYAN" Zarządzanie "COL_RED" <\n"COL_EASY"["COL_LIME"Użycie: klawisz H"COL_EASY"]", -1, POS_K2MENU, 10.0, _, _,  1);
	mq_format("SELECT * FROM `apartamenty` WHERE `expire`<'%d';", serwer[time_timestamp]);
	mq_send("QApartamentyDel");
	return 1;
}

forward QApartamentyDel();
public QApartamentyDel()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new userid;
		while(i < rekordy)
		{
			userid = cache_get_field_content_int(i, "userid");
			mq_format("DELETE FROM `apartamenty` WHERE `userid`='%d';", userid);
			mq_send("QADel");
			mq_format("DELETE FROM `items_apartament` WHERE `userid`='%d';", userid);
			mq_send("QADel");
			printf("[APARTAMENT]Usuwam apartament dla gracza UID: %d", userid);
			i++; 
		}
	}
	return 1;
}


stock ApartamentEnter(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1OUT))
	{
		mq_format("SELECT * FROM `apartamenty` WHERE `userid`='%d' AND `klasa`='1' LIMIT 0,1;", gracz[playerid][UID]);
		mq_send("QSzukajApartamentu", "d", playerid);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2OUT))
	{
		mq_format("SELECT * FROM `apartamenty` WHERE `userid`='%d' AND `klasa`='2' LIMIT 0,1;", gracz[playerid][UID]);
		mq_send("QSzukajApartamentu", "d", playerid);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2IN))
	{
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, POS_K2OUT);
		SetApartamentID(playerid, 0);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1IN))
	{
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, POS_K1OUT);
		SetApartamentID(playerid, 0);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1MENU))
	{
		mq_format("SELECT * FROM `apartamenty` WHERE `id`='%d' AND `userid`='%d' AND `klasa`='1' LIMIT 0,1;", gracz[playerid][apid], gracz[playerid][UID]);
		mq_send("QZarzadzajApartament", "d", playerid);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2MENU))
	{
		mq_format("SELECT * FROM `apartamenty` WHERE `id`='%d' AND `userid`='%d' AND `klasa`='2' LIMIT 0,1;", gracz[playerid][apid], gracz[playerid][UID]);
		mq_send("QZarzadzajApartament", "d", playerid);
	}
	return 1;
}

forward QSzukajApartamentu(playerid);
public QSzukajApartamentu(playerid)
{
	mq_getdata();
	new str_content[1024];
	if(rekordy)
	{
		format(str_content, 1024, "{1b300e}» "COL_GREY"Wejdź do swojego aparamentu "COL_LIME"[NR: "COL_RED"%d"COL_LIME"]", cache_get_field_content_int(0, "id"));
		strcat(str_content, "\n{630e70}» "COL_GREY"Wejdź do danego apartamentu");
		Dialog_Show(playerid, APARTMENUX, DIALOG_STYLE_LIST, "{1c5755} »"COL_GREY" Co chcesz zrobić?", str_content, "Wybierz", "Anuluj");
	}
	else
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1OUT)) strcat(str_content, "{1b300e}» "COL_GREY"Kup swój apartament klasy: "COL_ORANGE"I"COL_GREY" za "COL_CYAN"300 żetonów");
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2OUT)) strcat(str_content, "{1b300e}» "COL_GREY"Kup swój apartament klasy: "COL_ORANGE"II"COL_GREY" za "COL_CYAN"100 żetonów");
		strcat(str_content, "\n{630e70}» "COL_GREY"Wejdź do danego apartamentu");
		Dialog_Show(playerid, APARTMENUY, DIALOG_STYLE_LIST, "{1c5755} »"COL_GREY" Co chcesz zrobić?", str_content, "Wybierz", "Anuluj");
	}
	return 1;
}

Dialog:APARTMENUX(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("SELECT * FROM `apartamenty` WHERE `userid`='%d' LIMIT 0,1;", gracz[playerid][UID]);
			mq_send("QEnterMyApartament", "d", playerid);
		}
		case 1:
		{
			Dialog_Show(playerid, APARTENTER, DIALOG_STYLE_INPUT, "{1c5755} »"COL_GREY" Podaj NR apartamentu", "Podaj numer apartamentu, do którego chcesz się dostać:", "Wejdz", "Anuluj");
		}
	}
	return 1;
}


Dialog:APARTMENUY(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			//Error(playerid, "W tej chwili zablokowane jest kupowanie apartamentów.");
			mq_format("SELECT * FROM `apartamenty` WHERE `userid`='%d' LIMIT 0,1;", gracz[playerid][UID]);
			mq_send("QTryBuyAp", "d", playerid);

		}
		case 1:
		{
			Dialog_Show(playerid, APARTENTER, DIALOG_STYLE_INPUT, "{1c5755} »"COL_GREY" Podaj NR apartamentu", "Podaj numer apartamentu, do którego chcesz się dostać:", "Wejdz", "Anuluj");
		}
	}
	return 1;
}

forward QTryBuyAp(playerid);
public QTryBuyAp(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		Error(playerid, "Można mieć tylko jeden apartament.");
	}
	else
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1OUT)) 
		{
			mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='100' AND `count`>='300';", gracz[playerid][UID]);
			mq_send("QBuyAp1", "d", playerid);
		}
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2OUT))
		{
			mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='100' AND `count`>='100';", gracz[playerid][UID]);
			mq_send("QBuyAp2", "d", playerid);
		}
	}
	return 1;
}

forward QBuyAp1(playerid);
public QBuyAp1(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new calc_expire = serwer[time_timestamp]+((60*60)*24)*20;
		if(RemoveItemFromPlayer(playerid, 100, 300))
		{
			mq_format("INSERT INTO `apartamenty` (`userid`, `klasa`, `expire`) VALUES ('%d', '1', '%d');", gracz[playerid][UID], calc_expire);
			mq_send("QBuyApComplete");
			LeftNotifyShow(playerid, "Sukces!", "Zakupiles ~y~apartament~w~ pierwszej klasy.", LN_GREEN);
		}
	}
	else
	{
		Error(playerid, "Za mało żetonów.");
	}
	return 1;
}

forward QBuyAp2(playerid);
public QBuyAp2(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new calc_expire = serwer[time_timestamp]+((60*60)*24)*20;
		if(RemoveItemFromPlayer(playerid, 100, 100))
		{
			mq_format("INSERT INTO `apartamenty` (`userid`, `klasa`, `expire`) VALUES ('%d', '2', '%d');", gracz[playerid][UID], calc_expire);
			mq_send("QBuyApComplete");
			LeftNotifyShow(playerid, "Sukces!", "Zakupiles ~y~apartament~w~ drugiej klasy.", LN_GREEN);
		}
	}
	else
	{
		Error(playerid, "Za mało żetonów.");
	}
	return 1;
}

Dialog:APARTENTER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new aid = strval(inputtext);
	if(aid <= 0) return Error(playerid, "Numer apartamentu musi być większy niż 0.");
	if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1OUT)) mq_format("SELECT * FROM `apartamenty` WHERE `id`='%d' AND `klasa`='1' LIMIT 0,1;", aid);
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2OUT)) mq_format("SELECT * FROM `apartamenty` WHERE `id`='%d' AND `klasa`='2' LIMIT 0,1;", aid);
	mq_send("QEnterOtherApartament", "d", playerid);
	return 1;
}


forward QEnterMyApartament(playerid);
public QEnterMyApartament(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new id = cache_get_field_content_int(0, "id");
		new klasa = cache_get_field_content_int(0, "klasa");
		switch(klasa)
		{
			case 1:
			{
				SetPlayerVirtualWorld(playerid, 777+id);
				SetPlayerPos(playerid, POS_K1IN);
				SetApartamentID(playerid, id);
			}
			case 2:
			{
				SetPlayerVirtualWorld(playerid, 777+id);
				SetPlayerPos(playerid, POS_K2IN);
				SetApartamentID(playerid, id);
			}
		}
	}
	else
	{
		Error(playerid, "Nie znaleziono apartamentu.");
	}
	return 1;
}

forward QEnterOtherApartament(playerid);
public QEnterOtherApartament(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new id = cache_get_field_content_int(0, "id");
		new klasa = cache_get_field_content_int(0, "klasa");
		new open = cache_get_field_content_int(0, "open");
		if(open == 0) return Error(playerid, "Ten apartament jest zamknięty.");
		switch(klasa)
		{
			case 1:
			{
				SetPlayerVirtualWorld(playerid, 777+id);
				SetPlayerPos(playerid, POS_K1IN);
				SetApartamentID(playerid, id);
			}
			case 2:
			{
				SetPlayerVirtualWorld(playerid, 777+id);
				SetPlayerPos(playerid, POS_K2IN);
				SetApartamentID(playerid, id);
			}
		}
	}
	else
	{
		Error(playerid, "Nie znaleziono apartamentu.");
	}
	return 1;
}

forward QZarzadzajApartament(playerid);
public QZarzadzajApartament(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new str_menu[1024];
		new id = cache_get_field_content_int(0, "id");
		new klasa = cache_get_field_content_int(0, "klasa");
		new open = cache_get_field_content_int(0, "open");
		new expire = cache_get_field_content_int(0, "expire");
		SetPVarInt(playerid, "atemp_klasa", klasa);
		SetPVarInt(playerid, "atemp_open", open);
		SetPVarInt(playerid, "atemp_expire", expire);
		new dd, hh, mm, ss;
		SecToTime(expire-serwer[time_timestamp], dd, hh, mm, ss);
		format(str_menu, 1024, "{1b300e}» "COL_EASY"Otwórz szafkę");
		if(open) format(str_menu, 1024, "%s\n{1b300e}» "COL_RED"Zamknij"COL_GREY" drzwi", str_menu);
		else format(str_menu, 1024, "%s\n{1b300e}» "COL_GREEN"Otwórz"COL_GREY" drzwi", str_menu);
		if(klasa == 1) format(str_menu, 1024, "%s\n{1b300e}» "COL_GREEN"Opłać "COL_CYAN" [300 żetonów] "COL_LIME"(pozostało %d dni"COL_LIME")", str_menu, dd);
		else if(klasa == 2) format(str_menu, 1024, "%s\n{1b300e}» "COL_GREEN"Opłać "COL_CYAN" [100 żetonów] "COL_LIME"(pozostało %d dni"COL_LIME")", str_menu, dd);
		format(str_menu, 1024, "%s\n{1b300e}» "COL_RED"Wyprowadź się", str_menu);
		new str_header[128];
		format(str_header, 128, "{1300f7}» "COL_GREY"Zarządzanie apartamentem NR: "COL_RED"%d", id);
		Dialog_Show(playerid, APMENU, DIALOG_STYLE_LIST, str_header, str_menu, "Wybierz", "Anuluj");
	}
	else
	{
		Error(playerid, "Brak uprawnień do zarządzania tym apartamentem.");
	}
	return 1;
}

Dialog:APMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			ListItemsSzafka(playerid);
		}
		case 1:
		{
			if(GetPVarInt(playerid, "atemp_open")) 
			{
				mq_format("UPDATE `apartamenty` SET `open`='0' WHERE `userid`='%d';", gracz[playerid][UID]);
				LeftNotifyShow(playerid, "Sukces!", "Drzwi do Twojego apartamentu zostaly ~r~zamkniete~w~.", LN_GREEN);
			}
			else
			{
				mq_format("UPDATE `apartamenty` SET `open`='1' WHERE `userid`='%d';", gracz[playerid][UID]);
				LeftNotifyShow(playerid, "Sukces!", "Drzwi do Twojego apartamentu zostaly ~g~otwarte~w~. Jesli chcesz kogos wpuscic, podaj mu swoj numer apartamentu.", LN_GREEN);
			}
			mq_send("QUpdateOpen");
		}
		case 2:
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1MENU)) 
			{
				mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='100' AND `count`>='300';", gracz[playerid][UID]);
				mq_send("QExpireAddAp1", "d", playerid);
			}
			else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2MENU))
			{
				mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='100' AND `count`>='100';", gracz[playerid][UID]);
				mq_send("QExpireAddAp2", "d", playerid);
			}
		}
		case 3:
		{
			Dialog_Show(playerid, APWYPROWADZ, DIALOG_STYLE_INPUT, "Zatwierdź decyzję", ""COL_GREY"Jeśli się wyprowadzisz, wszystkie Twoje rzeczy w szafce przepadną!\nAby zatwierdzić, wpisz:"COL_RED" wyprowadz", "Zatwierdz", "Anuluj");
		}
	}
	return 1;
}

Dialog:APWYPROWADZ(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(!strcmp(inputtext, "wyprowadz"))
	{
		mq_format("DELETE FROM `items_apartament` WHERE `userid`='%d';", gracz[playerid][UID]);
		mq_send("QWyprowadz");
		mq_format("DELETE FROM `apartamenty` WHERE `userid`='%d';", gracz[playerid][UID]);
		mq_send("QWyprowadz");
		LeftNotifyShow(playerid, "Sukces!", "Wyprowadzono sie z apartamentu.", LN_GREEN);
		if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K2MENU))
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, POS_K2OUT);
			SetApartamentID(playerid, 0);
		}
		else if(IsPlayerInRangeOfPoint(playerid, 2.0, POS_K1MENU))
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, POS_K1OUT);
			SetApartamentID(playerid, 0);
		}
	}
	else Error(playerid, "Nie potwierdzono wyprowadzenia się.");
	return 1;
}


forward QExpireAddAp1(playerid);
public QExpireAddAp1(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new calc_expire = GetPVarInt(playerid, "atemp_expire")+((60*60)*24)*20;
		if(RemoveItemFromPlayer(playerid, 100, 300))
		{
			mq_format("UPDATE `apartamenty` SET `expire`='%d' WHERE `userid`='%d';", calc_expire, gracz[playerid][UID]);
			mq_send("QBuyApComplete");
			LeftNotifyShow(playerid, "Sukces!", "Przedluzono waznosc o 20 dni.", LN_GREEN);
		}
	}
	else
	{
		Error(playerid, "Za mało żetonów.");
	}
	return 1;
}

forward QExpireAddAp2(playerid);
public QExpireAddAp2(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new calc_expire = GetPVarInt(playerid, "atemp_expire")+((60*60)*24)*20;
		if(RemoveItemFromPlayer(playerid, 100, 100))
		{
			mq_format("UPDATE `apartamenty` SET `expire`='%d' WHERE `userid`='%d';", calc_expire, gracz[playerid][UID]);
			mq_send("QBuyApComplete");
			LeftNotifyShow(playerid, "Sukces!", "Przedluzono waznosc o 20 dni.", LN_GREEN);
		}
	}
	else
	{
		Error(playerid, "Za mało żetonów.");
	}
	return 1;
}

stock SetApartamentID(playerid, aid)
{
	gracz[playerid][apid] = aid;
	mq_format("UPDATE `Konta` SET `apid`='%d' WHERE `id`='%d';", gracz[playerid][apid], gracz[playerid][UID]);
	mq_send("QUpdateAID");
	return 1;
}

stock ListItemsSzafka(playerid)
{
	for(new eq_select_info:r; r < eq_select_info; r++)
	{
		eq_select[playerid][r] = 0;
	}
	if(gracz[playerid][BWTime]) return MessageGUI(playerid,"Informacja","Jesteś ciężko ranny - nie możesz przeglądać/używać przedmiotów.","OK","");
	if(InCombineMode(playerid)) return MessageGUI(playerid,"Informacja","Jesteś w trybie kombinacji - nie możesz przeglądać/używać przedmiotów.","OK","");
	SyncZetony(playerid);
	//mq_format("SELECT * FROM `items_apartament` WHERE `userid`='%d' ORDER BY `used` DESC, `id` ASC;", gracz[playerid][UID]);
	mq_format("SELECT * FROM `items_apartament` WHERE `userid`='%d';", gracz[playerid][UID]);
	mq_send("ShowItemsSzafkaDB", "d", playerid);
	return 1;
}

forward ShowItemsSzafkaDB(playerid);
public ShowItemsSzafkaDB(playerid)
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
		format(titlestr, 110, ""COL_WHITE"Szafka - ["COL_BLUE"Zużyte sloty: "COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE"]", rekordy, GetSzafkaSize(playerid));
		Dialog_Show(playerid, SZAFKA, DIALOG_STYLE_TABLIST_HEADERS, titlestr, list_items, "Wybierz", "Anuluj");
	}
	else
	{
		MessageGUI(playerid,"Informacja","Twoja szafka jest pusta!","OK","");
	}
	return 1;
}


Dialog:SZAFKA(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SyncEQToAmmo(playerid);
		return 1;
	}
	mq_format("SELECT * FROM `items_apartament` WHERE `id`='%d' LIMIT 0,1;", strval(inputtext));
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	eq_select[playerid][s_id] = cache_get_field_content_int(0, "id");
	eq_select[playerid][s_itemid] = cache_get_field_content_int(0, "itemid");
	eq_select[playerid][s_count] = cache_get_field_content_int(0, "count");
	eq_select[playerid][s_cdn] = cache_get_field_content_int(0, "cdn");
	eq_select[playerid][s_cdn_max] = cache_get_field_content_int(0, "cdn_max");
	Dialog_Show(playerid, SZAKCJA, DIALOG_STYLE_LIST, TitleSzafka_SelectItem(playerid), "1. "COL_GREEN"Wyciągnij", "Wybierz", "Wróć");
	cache_delete(itemquery);
	return 1;
}

Dialog:SZAKCJA(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItemsSzafka(playerid);
	switch(listitem)
	{
		case 0:
		{
			if(eq_select[playerid][s_count] == 1)
			{
				dialog_SZDROP(playerid, 1, 0, "1");
			}
			else
			{
				Dialog_Show(playerid, SZDROP, DIALOG_STYLE_INPUT, TitleSzafka_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyciągnąć?", "Wyrzuć", "Wróć");
			}
		}
	}
	return 1;
}

Dialog:SZDROP(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItemsSzafka(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1 || ilosc > 5000)
	{
		Dialog_Show(playerid, SZDROP, DIALOG_STYLE_INPUT, TitleSzafka_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyciągnąć?\n"COL_RED"Błąd! Niepoprawna ilość towaru(min: 1 | max: 5000).", "Wyrzuć", "Wróć");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		if(CreateItemForPlayer(playerid, eq_select[playerid][s_itemid], ilosc, eq_select[playerid][s_cdn], eq_select[playerid][s_cdn_max]))
		{
			RemoveItemFromSzafkaEx(playerid, eq_select[playerid][s_id], ilosc);
			LeftNotifyShow(playerid, "Sukces!", "Wyciagnieto przedmiot z szafki!", LN_GREEN);
		}
	}
	else
	{
		Dialog_Show(playerid, SZDROP, DIALOG_STYLE_INPUT, TitleSzafka_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyciągnąć?\n"COL_RED"Błąd! Brak takiej ilości towaru.", "Wyrzuć", "Wróć");
	}
	return 1;
}



stock CreateItemForSzafka(playerid, item_id, item_count, item_cdn = 100, item_cdn_max = 100)
{
	mq_format("SELECT * FROM `items_apartament` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count() && StackedItem(item_id))
	{
		new t_id = cache_get_field_content_int(0, "id");
		cache_delete(itemquery);
		mq_format("UPDATE `items_apartament` SET `count`=`count`+'%d' WHERE `id`='%d';", item_count, t_id);
		mysql_query(MySQL, mQuery, false);
	}
	else
	{			
		cache_delete(itemquery);
		mq_format("SELECT * FROM `items_apartament` WHERE `userid`='%d';", gracz[playerid][UID]);
		itemquery = mysql_query(MySQL, mQuery);
		if(cache_get_row_count() >= GetSzafkaSize(playerid))
		{
			cache_delete(itemquery,MySQL);
			MessageGUI(playerid,"Informacja","Brak miejsca w szafce!","OK","");
			return 0;
		}
		cache_delete(itemquery,MySQL);
		mq_format("INSERT INTO `items_apartament` VALUES(NULL, '%d', '%d', '%d', '%d', '%d');", gracz[playerid][UID], item_id, item_count, item_cdn, item_cdn_max);
		mysql_query(MySQL, mQuery, false);
	}
	return 1;
}


stock RemoveItemFromSzafka(playerid, item_id, item_count)//według ITEMID
{
	if(item_count < 1) return 0;
	mq_format("SELECT `id`,`count` FROM `items_apartament` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(MySQL, mQuery);
	if(cache_get_row_count())
	{
		new t_id = cache_get_field_content_int(0, "id");
		new t_count = cache_get_field_content_int(0, "count");
		if(item_count > t_count)
		{
			MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
			cache_delete(itemquery,MySQL);
			return 0;
		} 
		else if(item_count == t_count)
		{
			mq_format("DELETE FROM `items_apartament` WHERE `id`='%d';", t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			return 1;
		}
		else
		{
			mq_format("UPDATE `items_apartament` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			return 1;
		}
	}
	MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
	cache_delete(itemquery,MySQL);	
	return 0;
}


stock RemoveItemFromSzafkaEx(playerid, t_id, item_count)//według ID
{
	if(item_count < 1) return 0;
	mq_format("SELECT `count` FROM `items_apartament` WHERE `id`='%d' LIMIT 0,1;", t_id);
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
			mq_format("DELETE FROM `items_apartament` WHERE `id`='%d';", t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			return 1;
		}
		else
		{
			mq_format("UPDATE `items_apartament` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(MySQL, mQuery, false);
			cache_delete(itemquery,MySQL);
			return 1;
		}
	}
	MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
	cache_delete(itemquery,MySQL);
	return 0;
}

stock TitleSzafka_SelectItem(playerid)
{
	new titlestr[200];
	format(titlestr, 200, ""COL_WHITE"Szafka - ["COL_RED"%s"COL_WHITE"]["COL_GREEN"Ilość: "COL_RED"%d"COL_WHITE"]", ItemName[eq_select[playerid][s_itemid]], eq_select[playerid][s_count]);
	return titlestr;
}

stock GetSzafkaSize(playerid)
{
	new wynik;
	if(GetPVarInt(playerid, "atemp_klasa") == 1) wynik = 20;
	else if(GetPVarInt(playerid, "atemp_klasa") == 2) wynik = 10;
	return wynik;
}