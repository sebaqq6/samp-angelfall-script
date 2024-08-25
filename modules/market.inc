stock Market_Init()
{
	NewActor(1,-1952.7751,-1586.1406,2306.4160,99.4640); // warzywko
	NewActor(5,-1951.6041,-1593.3352,2306.4111,88.8105); // miesko
	NewActor(179,-1949.5541,-1600.3796,2306.4160,102.2604); // bronie
	NewActor(95,-1958.4794,-1598.2561,2306.4160,272.6918); // skup zlomu
	NewActor(13,-1956.0336,-1607.9657,2306.4160,285.8287); // ubranka
	NewActor(70,-1946.8700,-1611.4316,2306.4111,52.4165); // medykanty
	NewActor(190,-1952.7871,-1616.8455,2306.3613,344.7359); // daily item
	CreatePickup(1314, 1, -1955.4775,-1586.9419,2306.4160); // pickup warzywko
	CreatePickup(1314, 1, -1954.2454,-1593.2649,2306.4160); // pickup miesko
	CreatePickup(1314, 1, -1951.8801,-1600.9913,2306.4160); // pickup bron
	CreatePickup(1314, 1, -1949.1616,-1610.1881,2306.4160); // pickup medykanty
	CreatePickup(1314, 1, -1953.7632,-1607.4365,2306.4160); // pickup urbanka
	CreatePickup(1314, 1, -1956.0128,-1597.4810,2306.4160); // pickup zlom
	CreatePickup(1314, 1, -1952.0747,-1614.7474,2306.4160); // pickup daily item
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Luis"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1955.4775,-1586.9419,2306.4160, 10.0);
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Andrew"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1954.2454,-1593.2649,2306.4160, 10.0);
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Emmet"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1951.8801,-1600.9913,2306.4160, 10.0);
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Rudolf"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1949.1616,-1610.1881,2306.4160, 10.0);
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Rachel"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1953.7632,-1607.4365,2306.4160, 10.0);
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Chuck"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1956.0128,-1597.4810,2306.4160, 10.0);
	CreateDynamic3DTextLabel(""COL_RED"["COL_GREEN"Ashley"COL_RED"]\n"COL_EASY"["COL_LIME"U¿ycie: klawisz H"COL_EASY"]", -1, -1952.0747,-1614.7474,2306.4160, 10.0);
	return 1;
}

//0. itemid, 1. ilosc, 2. cena, 3. akcja(0 - kup | 1 - sprzedaj)
new Luis[][4] =
{
	{76, 10, 8, 1},
	{77, 10, 8, 1},
	{101, 1, 10, 0},
	{102, 1, 10, 0}
};

new Andrew[][4] =
{
	{78, 10, 10, 1},
	{79, 1, 5, 0},
	{79, 1, 4, 1},
	{80, 10, 13, 1},
	{81, 1, 10, 0},
	{81, 1, 3, 1}
};

new Emmet[][4] =
{
	{22, 1, 170, 0},
	{33, 1, 200, 0},
	{24, 1, 350, 0},
	{25, 1, 380, 0},
	{26, 1, 340, 0},
	{29, 1, 450, 0},
	{30, 1, 700, 0},
	//ammo
	{47, 20, 30, 0},
	{62, 20, 50, 0},
	{50, 8, 50, 0},
	{49, 20, 50, 0},
	{48, 20, 50, 0},
	{61, 20, 70, 0},
	{58, 30, 70, 0},
	{60, 30, 70, 0}
};
//0. itemid, 1. ilosc, 2. cena, 3. akcja(0 - kup | 1 - sprzedaj)
new Rudolf[][4] =
{
	{106, 1, 15, 0},
	{107, 1, 50, 0},
	{109, 1, 50, 0},
	{113, 1, 50, 0}
};

new Rachel[][4] =
{
	{158, 1, 100, 0}
};

new Chuck[][4] =
{
	{137, 30, 10, 1},
	{137, 50, 25, 1},
	{137, 200, 110, 1},
	{137, 300, 230, 1},
	{137, 350, 310, 1},
	{135, 20, 5, 1},
	{135, 50, 20, 1}
};
//0. itemid, 1. ilosc, 2. cena, 3. akcja(0 - kup | 1 - sprzedaj)
new Ashley[][4] =
{
	{136, 1, 10, 1},
	{67, 1, 60, 0},
	{133, 1, 50, 0},
	{144, 1, 30, 0},
	{147, 1, 80, 0},
	{148, 1, 110, 0},
	{149, 1, 160, 0},
	{150, 1, 200, 0}
};

stock market_Enter(playerid)
{
	new str_market[2048];
	format(str_market, 2048, "Nazwa przedmiotu\tIloœæ\tCena\tAkcja");
	if(IsPlayerInRangeOfPoint(playerid, 1.0, -1955.4775,-1586.9419,2306.4160)) // pickup warzywko
	{
		for(new m; m < sizeof(Luis); m++)
		{
			if(Luis[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Luis[m][0]], Luis[m][1], Luis[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Luis[m][0]], Luis[m][1], Luis[m][2]);
		}
		Dialog_Show(playerid, LUIS, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Luis", str_market, "Wybierz", "Anuluj");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, -1954.2454,-1593.2649,2306.4160)) // pickup miesko
	{
		for(new m; m < sizeof(Andrew); m++)
		{
			if(Andrew[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Andrew[m][0]], Andrew[m][1], Andrew[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Andrew[m][0]], Andrew[m][1], Andrew[m][2]);
		}
		Dialog_Show(playerid, ANDREW, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Andrew", str_market, "Wybierz", "Anuluj");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, -1951.8801,-1600.9913,2306.4160)) // pickup bron
	{
		for(new m; m < sizeof(Emmet); m++)
		{
			if(Emmet[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Emmet[m][0]], Emmet[m][1], Emmet[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Emmet[m][0]], Emmet[m][1], Emmet[m][2]);
		}
		Dialog_Show(playerid, EMMET, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Emmet", str_market, "Wybierz", "Anuluj");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, -1949.1616,-1610.1881,2306.4160)) // pickup medykanty
	{
		for(new m; m < sizeof(Rudolf); m++)
		{
			if(Rudolf[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Rudolf[m][0]], Rudolf[m][1], Rudolf[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Rudolf[m][0]], Rudolf[m][1], Rudolf[m][2]);
		}
		Dialog_Show(playerid, RUDOLF, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Rudolf", str_market, "Wybierz", "Anuluj");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, -1953.7632,-1607.4365,2306.4160)) // pickup urbanka
	{
		for(new m; m < sizeof(Rachel); m++)
		{
			if(Rachel[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Rachel[m][0]], Rachel[m][1], Rachel[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Rachel[m][0]], Rachel[m][1], Rachel[m][2]);
		}
		Dialog_Show(playerid, RACHEL, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Rachel", str_market, "Wybierz", "Anuluj");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, -1956.0128,-1597.4810,2306.4160)) // pickup zlom
	{
		for(new m; m < sizeof(Chuck); m++)
		{
			if(Chuck[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Chuck[m][0]], Chuck[m][1], Chuck[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Chuck[m][0]], Chuck[m][1], Chuck[m][2]);
		}
		Dialog_Show(playerid, CHUCK, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Chuck", str_market, "Wybierz", "Anuluj");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, -1952.0747,-1614.7474,2306.4160)) // pickup daily item
	{
		for(new m; m < sizeof(Ashley); m++)
		{
			if(Ashley[m][3]) format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_DBLUE"Sprzedaj"COL_RED"]", str_market, ItemName[Ashley[m][0]], Ashley[m][1], Ashley[m][2]);
			else format(str_market, 2048, "%s\n"COL_BROWN"» "COL_EASY"%s\t"COL_GREEN"%d "COL_GREY"sztuk\t"COL_CYAN"%d "COL_GREY"¿etonów\t"COL_RED"["COL_ORANGE"Kup"COL_RED"]", str_market, ItemName[Ashley[m][0]], Ashley[m][1], Ashley[m][2]);
		}
		Dialog_Show(playerid, ASHLEY, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"» "COL_GREY"Handel z: "COL_LIME"Ashley", str_market, "Wybierz", "Anuluj");
	}
	return 1;
}

Dialog:LUIS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Luis[listitem][3]) Market_Sell(playerid, Luis[listitem][0], Luis[listitem][1], Luis[listitem][2]);
	else Market_Buy(playerid, Luis[listitem][0], Luis[listitem][1], Luis[listitem][2]);
	return 1;
}
Dialog:ANDREW(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Andrew[listitem][3]) Market_Sell(playerid, Andrew[listitem][0], Andrew[listitem][1], Andrew[listitem][2]);
	else Market_Buy(playerid, Andrew[listitem][0], Andrew[listitem][1], Andrew[listitem][2]);
	return 1;
}
Dialog:EMMET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Emmet[listitem][3]) Market_Sell(playerid, Emmet[listitem][0], Emmet[listitem][1], Emmet[listitem][2]);
	else Market_Buy(playerid, Emmet[listitem][0], Emmet[listitem][1], Emmet[listitem][2]);
	return 1;
}
Dialog:RUDOLF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Rudolf[listitem][3]) Market_Sell(playerid, Rudolf[listitem][0], Rudolf[listitem][1], Rudolf[listitem][2]);
	else Market_Buy(playerid, Rudolf[listitem][0], Rudolf[listitem][1], Rudolf[listitem][2]);
	return 1;
}
Dialog:RACHEL(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Rachel[listitem][3]) Market_Sell(playerid, Rachel[listitem][0], Rachel[listitem][1], Rachel[listitem][2]);
	else Market_Buy(playerid, Rachel[listitem][0], Rachel[listitem][1], Rachel[listitem][2]);
	return 1;
}
Dialog:CHUCK(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Chuck[listitem][3]) Market_Sell(playerid, Chuck[listitem][0], Chuck[listitem][1], Chuck[listitem][2]);
	else Market_Buy(playerid, Chuck[listitem][0], Chuck[listitem][1], Chuck[listitem][2]);
	return 1;
}
Dialog:ASHLEY(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Ashley[listitem][3]) Market_Sell(playerid, Ashley[listitem][0], Ashley[listitem][1], Ashley[listitem][2]);
	else Market_Buy(playerid, Ashley[listitem][0], Ashley[listitem][1], Ashley[listitem][2]);
	return 1;
}

stock Market_Sell(playerid, itemid, count, price)
{
	mq_format("SELECT `id` FROM `przedmioty` WHERE `itemid`='%d' AND `count`>='%d' AND `userid`='%d' LIMIT 0,1;", itemid, count, gracz[playerid][UID]);
	mq_send("MarketSellProcess", "dddd", playerid, itemid, count, price);
	return 1;
}

forward MarketSellProcess(playerid, itemid, count, price);
public MarketSellProcess(playerid, itemid, count, price)
{
	mq_getdata();
	if(rekordy)
	{
		new id = cache_get_field_content_int(0, "id");
		if(CreateItemForPlayer(playerid, 100, price))
		{
			mq_format("UPDATE `przedmioty` SET `count`=`count`-'%d' WHERE `id`='%d'; ", count, id);
			mq_send("QMarketTransaction", "dd", playerid, 0);
			new str_sell[256];
			format(str_sell, 256, "~g~Sprzedales~y~ %s ~w~(~y~%d~w~ sztuk) za ~y~%d~w~ zetonow.", ItemName[itemid], count, price);
			LeftNotifyShow(playerid, "Sukces!", str_sell, LN_GREEN, 10);
			mq_format("INSERT INTO `targowa_history` (`userid`, `itemid`, `count`, `price`, `type`) VALUES ('%d', '%d', '%d', '%d', '2');", gracz[playerid][UID], itemid, count, price);
			mq_send("QTargowaHistory");
		}
	}
	else
	{
		LeftNotifyShow(playerid, "error", "~r~Brak~w~ wymaganej ilosci ~y~towaru~w~!", LN_RED);
	}
	return 1;
}

stock Market_Buy(playerid, itemid, count, price)
{
	mq_format("SELECT `id` FROM `przedmioty` WHERE `itemid`='100' AND `count`>='%d' AND `userid`='%d' LIMIT 0,1;", price, gracz[playerid][UID]);
	mq_send("MarketBuyProcess", "dddd", playerid, itemid, count, price);
	return 1;
}

forward MarketBuyProcess(playerid, itemid, count, price);
public MarketBuyProcess(playerid, itemid, count, price)
{
	mq_getdata();
	if(rekordy)
	{
		new id = cache_get_field_content_int(0, "id");
		
		new kond[2];
		if(itemid >= 22 && itemid <= 46)
		{
			kond[0] = 500;//actual
			kond[1] = 1000;//max
		}
		else if(itemid == 67)
		{
			new time_karnet = serwer[time_timestamp]+(60*60)*15;
			kond[0] = time_karnet;//actual
			kond[1] = time_karnet;//max
		}
		else
		{
			kond[0] = 100;//actual
			kond[1] = 100;//max
		}
		if(CreateItemForPlayer(playerid, itemid, count, kond[0], kond[1]))
		{
			mq_format("UPDATE `przedmioty` SET `count`=`count`-'%d' WHERE `id`='%d'; ", price, id);
			mq_send("QMarketTransaction", "dd", playerid, 1);
			new str_sell[256];
			format(str_sell, 256, "~g~Kupiles~y~ %s ~w~(~y~%d~w~ sztuk) za ~y~%d~w~ zetonow.", ItemName[itemid], count, price);
			LeftNotifyShow(playerid, "Sukces!", str_sell, LN_GREEN, 10);
			mq_format("INSERT INTO `targowa_history` (`userid`, `itemid`, `count`, `price`, `type`) VALUES ('%d', '%d', '%d', '%d', '1');", gracz[playerid][UID], itemid, count, price);
			mq_send("QTargowaHistory");
		}
	}
	else
	{
		LeftNotifyShow(playerid, "error", "~r~Brak~w~ wymaganej ilosci ~y~zetonow~w~!", LN_RED);
	}
	return 1;
}

forward QMarketTransaction(playerid, ref_zetony);
public QMarketTransaction(playerid, ref_zetony)
{
	DelZeroItems();
	if(ref_zetony) SyncZetony(playerid);
	return 1;
}