//zł, numer, żetony
new Float:sms_cennik[][3] =
{
	{0.61, 7055.0, 25.0},
	{1.23, 7136.0, 50.0},
	{3.69, 7355.0, 150.0},
	{6.15, 7555.0, 250.0},
	{7.38, 7636.0, 300.0},
	{11.07, 7936.0, 450.0},
	{17.22, 91455.0, 700.0},
	{23.37, 91955.0, 950.0},
	{30.75, 92555.0, 1250.0}
};
//cennik usług w żetonach premium:
#define CENA_VIP 450
#define CENA_GRUPA 250

stock ShowPremiumMenu(playerid)
{
	new str_menu[1000];
	strcat(str_menu, ""COL_WHITE"("COL_CYAN"SMS"COL_WHITE")\t"COL_GREY"Kup "COL_ORANGE"ż"COL_GREY"etony "COL_ORANGE"p"COL_GREY"remium"COL_WHITE"\t("COL_CYAN"SMS"COL_WHITE")\n");
	strcat(str_menu, ""COL_WHITE"("COL_RED"450 "COL_ORANGE"żp"COL_WHITE")\t"COL_GREY"Konto premium"COL_WHITE"\t("COL_RED"30 dni"COL_WHITE")\n");
	strcat(str_menu, ""COL_WHITE"("COL_RED"250 "COL_ORANGE"żp"COL_WHITE")\t"COL_GREY"Grupa"COL_WHITE"\t("COL_RED"30 dni"COL_WHITE")\n");
	new str_header[100];
	format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
	Dialog_Show(playerid, PREMIUM, DIALOG_STYLE_TABLIST, str_header, str_menu, "Wybierz", "Wróć");
	return 1;
}
//Doładowanie
Dialog:PREMIUM(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/pomoc");
	switch(listitem)
	{
		case 0:
		{
			new str_sms[2048];
			new str_header[100];
			format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
			format(str_sms, 2048, "Cena\tIlość");
			for(new s; s < sizeof(sms_cennik); s++)
			{
				format(str_sms, 2048, "%s\n"COL_GREY"» "COL_WHITE"%.02f "COL_GREY"zł\t"COL_GREEN"+"COL_GREY"%d "COL_ORANGE"żp", str_sms, sms_cennik[s][0], floatround(sms_cennik[s][2]));
			}
			Dialog_Show(playerid, BUYSMS, DIALOG_STYLE_TABLIST_HEADERS, str_header, str_sms, "Wybierz", "Wróć");
		}
		case 1://vip
		{
			new str_vip[2048];
			new str_header[100];
			format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
			format(str_vip, 2048, "%s\n"COL_GREY"Cechy konta premium:", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Wyróżniony nick pod TAB (kolor: złoty).", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Wyróżniony kolor nad skinem (kolor: złoty).", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Zmieniony domyślny status nad głową.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Bonus do siły na siłowni ("COL_GREEN"+"COL_GREY"2 punkty).", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Bonus EXP ("COL_GREEN"+"COL_GREY"3 exp).", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Skrócony czas BW (60 sekund).", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Zwiększenie slotów w ekwipunku ("COL_GREEN"+"COL_GREY"6 slotów).", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Koszt: "COL_RED"%d "COL_ORANGE"żetonów premium"COL_GREY".", str_vip, CENA_VIP);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Konto premium jest ważna przez "COL_RED"30 dni"COL_GREY".", str_vip);
			//format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"x", str_vip);
			format(str_vip, 2048, "%s\n", str_vip);
			format(str_vip, 2048, "%s\n"COL_GREY"Czy chcesz zakupić konto premium?", str_vip);
			Dialog_Show(playerid, BUYVIP, DIALOG_STYLE_MSGBOX, str_header, str_vip, "Kup!", "Wróć");
		}
		case 2://grupa
		{
			new str_cgroup[2048];
			new str_header[100];
			if(!gracz[playerid][OrgID] && !gracz[playerid][SzefORG] && !gracz[playerid][ViceSzefORG])
			{
				format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
				format(str_cgroup, 2048, ""COL_GREY"Rozpoczęto proces "COL_GREEN"tworzenia"COL_GREY" grupy...");
				format(str_cgroup, 2048, "%s\n"COL_GREY"Cechy grupy:", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"W grupie moze być max: "COL_RED"10 graczy"COL_GREY".", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Rywalizacja z innymi grupami (levelowanie)", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Darmowa krótkofalówka - czat grupowy.", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» {00B403}Darmowy GPS"COL_GREY" - widzisz na mapie gdzie znajdują się członkowie Twojej grupy.", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Możliwość dokupienia siedziby.", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Koszt: "COL_RED"%d "COL_ORANGE"żetonów premium"COL_GREY".", str_cgroup, CENA_GRUPA);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Grupa jest ważna przez "COL_RED"30 dni"COL_GREY".", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Wszelkie komendy znajdują się pod /pomoc", str_cgroup);
				format(str_cgroup, 2048, "%s\n", str_cgroup);
				format(str_cgroup, 2048, "%s\n"COL_GREY"Wprowadź pełną nazwę grupy (max: 30 znaków): ", str_cgroup);
				Dialog_Show(playerid, BUYGROUP, DIALOG_STYLE_INPUT, str_header, str_cgroup, "Dalej", "Wróć");
			}
			else if(gracz[playerid][OrgID] && !gracz[playerid][SzefORG] && !gracz[playerid][ViceSzefORG])
			{
				Error(playerid, "Musisz opuścić swoją dotychczasową grupę, by móc stworzyć swoją.");
			}
			else if(gracz[playerid][SzefORG] || gracz[playerid][ViceSzefORG])
			{
				format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
				format(str_cgroup, 2048, ""COL_GREY"Rozpoczęto proces "COL_RED"przedłużania"COL_GREY" grupy...");
				format(str_cgroup, 2048, "%s\n"COL_GREY"Cechy grupy:", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"W grupie moze być max: "COL_RED"10 graczy"COL_GREY".", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Rywalizacja z innymi grupami (levelowanie)", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Darmowa krótkofalówka grupowa - czat grupowy.", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» {00B403}Darmowy GPS"COL_GREY" - widzisz na mapie gdzie znajdują się członkowie Twojej grupy.", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Możliwość dokupienia siedziby.", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Koszt: "COL_RED"%d "COL_ORANGE"żetonów premium"COL_GREY".", str_cgroup, CENA_GRUPA);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Grupa jest ważna przez "COL_RED"30 dni"COL_GREY".", str_cgroup);
				format(str_cgroup, 2048, "%s\n{a90000}» "COL_GREY"Wszelkie komendy znajdują się pod /pomoc", str_cgroup);
				format(str_cgroup, 2048, "%s\n", str_cgroup);
				format(str_cgroup, 2048, "%s\n"COL_GREEN"Czy chcesz przedłużyć swoją grupę "COL_RED"(%s)"COL_GREEN" o 30 dni?", str_cgroup, gracz[playerid][group_name]);
				Dialog_Show(playerid, ADDEXPIREGROUP, DIALOG_STYLE_MSGBOX, str_header, str_cgroup, "TAK", "NIE");
			}
		}
	}
	return 1;
}

Dialog:BUYSMS(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	new str_smsbuy[2048];
	new str_header[100];
	format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
	format(str_smsbuy, 2048, ""COL_GREY"Zakup "COL_RED"%d"COL_GREY" sztuk "COL_ORANGE"żetonów premium"COL_GREY":", floatround(sms_cennik[listitem][2]));
	format(str_smsbuy, 2048, "%s\n{a90000}» "COL_GREY"Wyślij SMS o treści "COL_BLUE"SIM.ZETONY"COL_GREY" na numer "COL_GREEN"%d"COL_GREY".", str_smsbuy, floatround(sms_cennik[listitem][1]));
	format(str_smsbuy, 2048, "%s\n{a90000}» "COL_CYAN"Kod zwrotny wprowadź w polu poniżej.", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n"COL_GREY"Koszt SMS: "COL_RED"%.02f "COL_GREY"zł (brutto)", str_smsbuy, sms_cennik[listitem][0]);
	format(str_smsbuy, 2048, "%s\n", str_smsbuy);
	format(str_smsbuy, 2048, "%s\nAdministracja {a90000}Angel Fall"COL_GREY" nie czerpie korzyści majątkowych ze sprzedaży żetonów premium na serwerze oraz w panelu gracza {a90000}Angel Fall"COL_GREY".", str_smsbuy);
	format(str_smsbuy, 2048, "%s\nWszystkie środki są przekazywane na utrzymanie forum, serwera TS3, serwera SA:MP oraz opłacenie zakładki HOSTED.", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n"COL_GREY"Płatności obsługuje: {49cc8d}SimPay.pl"COL_GREY"\tReklamacje: {49cc8d}https://simpay.pl/reklamacje", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n{49cc8d}SimPay"COL_GREY" obsługuje wszystkie sieci, w tym: {f200e8}T-MOBILE"COL_GREY", {ff6700}ORANGE"COL_GREY", {297a00}PLUS"COL_GREY", {9f00c9}PLAY"COL_GREY", {ec0018}HEYAH"COL_GREY", {f9be02}CYFROWY POLSAT", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n"COL_GREY"Więcej informacji oraz {59e700}inne rodzaje płatności"COL_GREY" znajdziesz w panelu gracza {a90000}Angel Fall"COL_GREY".", str_smsbuy);
	Dialog_Show(playerid, BUYSMS2, DIALOG_STYLE_INPUT, str_header, str_smsbuy, "Zatwierdź", "Anuluj");
	SetPVarInt(playerid, "BuySms_Selected", listitem);
	return 1;
}

Dialog:BUYSMS2(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(strlen(inputtext) < 6) return Error(playerid, "Podany kod jest za krótki.");
	format(inputtext, 10, inputtext);
	new selected = GetPVarInt(playerid, "BuySms_Selected");
	new request[512];
	format(request, 512, "redtm.pl/api_sms.php?typ=af&sms=%d&kod=%s", floatround(sms_cennik[selected][1]), inputtext);
	SetPVarString(playerid, "Sms_Code", inputtext);
	HTTP(playerid, HTTP_GET, request, "", "ValidSMSCode");
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "{f0da00}Sprawdzanie...", "Trwa sprawdzanie... Proszę czekać...", "OK","");
	return 1;
}

forward ValidSMSCode(index, response_code, data[]);
public ValidSMSCode(index, response_code, data[])
{
	new buffer[128];
	if(response_code == 200)//success connect api
	{
		new code_data = strval(data);
		switch(code_data)
		{
			case 0:
			{
				format(buffer, sizeof(buffer), "Wewnętrzny błąd API.");
				Error(index, buffer);
				Dialog_Close(index);
			}
			case 1:
			{
				new str_successbuy[512];
				new selected = GetPVarInt(index, "BuySms_Selected");
				new add_zetony = floatround(sms_cennik[selected][2]);
				format(str_successbuy, 512, "{00b415}Sukces!");
				format(str_successbuy, 512, "%s\n"COL_GREY"Dziękujemy za dofinansowanie projektu {a90000}Angel Fall"COL_GREY"!", str_successbuy);
				format(str_successbuy, 512, "%s\n"COL_GREY"W zamian otrzymujesz "COL_GREEN"+"COL_RED"%d"COL_GREY" sztuk "COL_ORANGE"żetonów premium"COL_GREY" :)", str_successbuy, add_zetony);
				format(str_successbuy, 512, "%s\n"COL_GREY"Pozdrawiamy, ekipa {a90000}Angel Fall"COL_GREY".", str_successbuy);
				gracz[index][gold] += add_zetony;
				mq_format("UPDATE `Konta` SET `gold`='%d' WHERE `id`='%d';", gracz[index][gold], gracz[index][UID]);
				mq_send("QAddGold");
				ShowPlayerDialog(index, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "{00b415}SUKCES!!!", str_successbuy, "ZAMKNIJ","");
				printf("[ZETONY]Gracz UID: %d[%s] doladowal %d zetonow. Aktualny jego stan: %d", gracz[index][UID], nick(index), add_zetony, gracz[index][gold]);
				new sms_code[32];
				GetPVarString(index, "Sms_Code", sms_code, 32);
				mq_format("INSERT INTO `WebPremiumLog` (`web`, `type`, `uid`, `nr`, `code`, `price`) VALUES ('0', '1', '%d', '%d', '%s', '%f');", gracz[index][UID], floatround(sms_cennik[selected][1]), sms_code, sms_cennik[selected][0]);
				mq_send("QSMSLog");
			}
			case 2:
			{
				format(buffer, sizeof(buffer), "Błędny kod.");
				Error(index, buffer);
				Dialog_Close(index);
			}
			case 3..4:
			{
				format(buffer, sizeof(buffer), "Błąd zapytania.");
				Error(index, buffer);
				Dialog_Close(index);
			}
			case 5:
			{
				format(buffer, sizeof(buffer), "Kod został już wykorzystany.");
				Error(index, buffer);
				Dialog_Close(index);
			}
		}
	}
	else
	{
		format(buffer, sizeof(buffer), "Błąd połączenia API, kod błędu: %d", response_code);
		Error(index, buffer);
		Dialog_Close(index);
		format(buffer, 100, "[HTTP_DATA]: PUID: %d | %s", gracz[index][UID], data);
		print(buffer);
	}
	return 1;
}
//kupno premium

//kupno grupy
Dialog:BUYGROUP(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	if(gracz[playerid][gold] < CENA_GRUPA) return Error(playerid, "Za mało żetonów premium.");
	if(4 > strlen(inputtext) > 30)
	{
		Error(playerid, "Nazwa grupy musi mieć od 4 do 30 znaków.");
		ShowPremiumMenu(playerid);
		return 1;
	}
	if(!CheckAllowedChar(inputtext))
	{
		Error(playerid, "W nazwie grupy pojawiły się niedozwolone znaki! Używaj tylko od A do Z(bez ogonków) oraz 0-9.");
		ShowPremiumMenu(playerid);
		return 1;
	}
	new str_cgroup[2048];
	new str_header[100];
	SetPVarString(playerid, "GroupSetName", inputtext);
	format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
	format(str_cgroup, 2048, "%s\n"COL_GREY"Wprowadzona nazwa grupy: "COL_BLUE"%s", str_cgroup, inputtext);
	format(str_cgroup, 2048, "%s\n"COL_GREY"Aby zakończyć proces tworzenia grupy, musisz wprowadzić jeszcze jej skrót.", str_cgroup);
	format(str_cgroup, 2048, "%s\n"COL_GREY"Wprowadź TAG grupy(max: "COL_RED"3 znaki"COL_GREY", np: "COL_BLUE"ABC"COL_GREY"): ", str_cgroup);
	Dialog_Show(playerid, BUYGROUPEND, DIALOG_STYLE_INPUT, str_header, str_cgroup, "STWÓRZ!", "Wróć");
	return 1;
}

Dialog:BUYGROUPEND(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	if(gracz[playerid][gold] < CENA_GRUPA) return Error(playerid, "Za mało żetonów premium.");
	if(1 > strlen(inputtext) > 3)
	{
		Error(playerid, "Tag musi mieć od 1 do 3 znaków.");
		ShowPremiumMenu(playerid);
		return 1;
	}
	if(!CheckAllowedChar(inputtext))
	{
		Error(playerid, "W TAG'u grupy pojawiły się niedozwolone znaki! Używaj tylko od A do Z(bez ogonków) oraz 0-9.");
		ShowPremiumMenu(playerid);
		return 1;
	}
	if(gracz[playerid][gold] < CENA_GRUPA) return Error(playerid, "Za mało żetonów premium.");
	new str_cgroup[2048];
	new str_header[100];
	format(str_header, 100, ""COL_YELLOW"»"COL_GREEN"Stworzono grupe!", gracz[playerid][gold]);
	format(str_cgroup, 2048, ""COL_GREEN"Gratulację! "COL_GREY"Stworzyłeś swoją grupę :)");
	format(str_cgroup, 2048, "%s\n"COL_GREY"Grupa jest ważna przez 30 dni, możesz ją w każdej chwili przedłużyć używając tej samej opcji, co do tworzenia.", str_cgroup);
	new gname[30];
	GetPVarString(playerid, "GroupSetName", gname, 30);
	format(str_cgroup, 2048, "%s\n"COL_GREY"Nazwa grupy: "COL_BLUE"%s", str_cgroup, gname);
	format(str_cgroup, 2048, "%s\n"COL_GREY"TAG grupy: "COL_BLUE"%s", str_cgroup, inputtext);
	format(str_cgroup, 2048, "%s\n"COL_GREY"Wszelkie komendy dla grup znajdziesz pod "COL_RED"/pomoc"COL_GREY".", str_cgroup);
	gracz[playerid][gold] -= CENA_GRUPA;
	mq_format("UPDATE `Konta` SET `gold`='%d' WHERE `id`='%d';", gracz[playerid][gold], gracz[playerid][UID]);
	mq_send("QDelGold");
	mq_format("INSERT INTO `LogiZetonowPremium` (`uid`, `price`, `property`) VALUES ('%d', '%d', '2');", gracz[playerid][UID], CENA_GRUPA);
	mq_send("QZetonLog");
	CreateGroup(playerid, gname, inputtext);
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, str_header, str_cgroup, "ZAMKNIJ", "");
	return 1;
}

Dialog:ADDEXPIREGROUP(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	if(gracz[playerid][gold] < CENA_GRUPA) return Error(playerid, "Za mało żetonów premium.");
	new str_cgroup[2048];
	new str_header[100];
	format(str_header, 100, ""COL_YELLOW"»"COL_GREEN"Stworzono grupe!", gracz[playerid][gold]);
	format(str_cgroup, 2048, ""COL_GREEN"Gratulację! "COL_GREY"Przedłużyłeś swoją grupę o 30 dni!");
	mq_format("SELECT `expire` FROM `Grupy` WHERE `id`='%d';", gracz[playerid][SzefORG]);
	new Cache:qGetExpire = mysql_query(MySQL, mQuery);
	new actual_expire = cache_get_field_content_int(0, "expire");
	cache_delete(qGetExpire);
	new new_expire = actual_expire+((60*60)*24)*31;
	mq_format("UPDATE `Grupy` SET `expire`='%d' WHERE `id`='%d';", new_expire, gracz[playerid][SzefORG]);
	mq_send("QAddExpireGroup");
	gracz[playerid][gold] -= CENA_GRUPA;
	mq_format("UPDATE `Konta` SET `gold`='%d' WHERE `id`='%d';", gracz[playerid][gold], gracz[playerid][UID]);
	mq_send("QDelGold");
	mq_format("INSERT INTO `LogiZetonowPremium` (`uid`, `price`, `property`) VALUES ('%d', '%d', '2');", gracz[playerid][UID], CENA_GRUPA);
	mq_send("QZetonLog");
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, str_header, str_cgroup, "ZAMKNIJ", "");
	return 1;
}
//kupno vipa
Dialog:BUYVIP(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	if(gracz[playerid][gold] < CENA_VIP) return Error(playerid, "Za mało żetonów premium.");
	gracz[playerid][gold] -= CENA_VIP;
	if(isvip(playerid))
	{
		gracz[playerid][vip] = gracz[playerid][vip]+((60*60)*24)*30;
	}
	else
	{
		gracz[playerid][vip] = serwer[time_timestamp]+((60*60)*24)*30;
	}
	mq_format("UPDATE `Konta` SET `gold`='%d', `vip`='%d' WHERE `id`='%d';", gracz[playerid][gold], gracz[playerid][vip], gracz[playerid][UID]);
	mq_send("QBuyVIP");
	mq_format("INSERT INTO `LogiZetonowPremium` (`uid`, `price`, `property`) VALUES ('%d', '%d', '1');", gracz[playerid][UID], CENA_VIP);
	mq_send("QZetonLog");
	new str_successbuy[512];
	format(str_successbuy, 512, "{00b415}Sukces!");
	format(str_successbuy, 512, "%s\n"COL_GREY"Dziękujemy za zakup konta premium na projekcie {a90000}Angel Fall"COL_GREY"!", str_successbuy);
	format(str_successbuy, 512, "%s\n"COL_GREY"Twoje konto premium na tej postaci jest ważne przez "COL_RED"%d dni"COL_GREY" ("COL_LIME"czas wygaśnięcia jest pod "COL_GREEN"/stats"COL_GREY").", str_successbuy, (gracz[playerid][vip]-serwer[time_timestamp])/60/60/24);
	format(str_successbuy, 512, "%s\n"COL_GREY"Możesz w każdej chwili przedłużyć ważność konta premium używając tej samej opcji co do kupna.", str_successbuy);
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_YELLOW"»{00b415}Przyznano konto premium!", str_successbuy, "ZAMKNIJ","");
	return 1;
}
