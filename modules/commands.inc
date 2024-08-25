//*******************************************************************************************************************************************************CMD CALLBACKS
public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	//printf("cmd: '/%s' | params: '%s' | all: '/%s %s'", cmd, params, cmd, params);
	if(!gracz[playerid][loggedin]) return 0;
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if(result == -1)
	{
		new str[127];
		format(str, 127, "Komenda "COL_ORANGE"/%s"COL_WHITE" jest niedostêpna. Dostêpne komendy:"COL_GREEN" /pomoc", cmd);
		Error(playerid, str);
		return 0;
	}
	return 1;
}
//********************************************************************************************************************************************************KOMENDY
//QUIT SAFE
CMD:qs(playerid, params[])
{
	if(!gracz[playerid][loggedin]) return Error(playerid, "Nie jesteœ zalogowany!");
	Disconnect(playerid);
	SendClientMessage(playerid, -1, "(("COL_BLUE"Za chwilê zostaniesz "COL_GREEN"bezpiecznie"COL_RED" roz³¹czony "COL_BLUE"z serwerem."COL_WHITE"))");
	SetTimerEx("KickExRun", 1000, false, "d", playerid);
	return 1;
}
//POMOC
CMD:pomoc(playerid, params[])
{
	new listhelp[1000];
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Opis rozgrywki"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Komendy czatu"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Podstawowe komendy gracza"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Komendy grup"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Komendy edytora obiektów"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Klawiszologia"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_RED"$"COL_WHITE")\t"COL_YELLOW"PREMIUM"COL_WHITE"\t("COL_RED"$"COL_WHITE")\n");
	Dialog_Show(playerid, POMOC, DIALOG_STYLE_TABLIST, ""COL_WHITE"Centrum Pomocy - "COL_GREEN"AngelFall.pl"COL_WHITE"", listhelp, "Wybierz", "Anuluj");
	return 1;
}
Dialog:POMOC(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new listcmd[3000];
	switch(listitem)
	{
		case 0:
		{
			strcat(listcmd,""COL_GREY"Witaj w œwiecie postapokalipsy {64000d}Angel Fall"COL_GREY"! \n");
			strcat(listcmd,""COL_GREY"Zdobywaj {6f3e9c}doœwiadczenie"COL_GREY" w œwiecie postapokalipsy, rywalizuj¹c z innymi graczami. \n");
			strcat(listcmd,""COL_GREY"{6f3e9c}Doœwiadczenie"COL_GREY" zdobywasz zabijaj¹c szwêdaczy (zombie), zabójstwa innych graczy oraz eksploruj¹c mapê.\n");
			strcat(listcmd,""COL_GREY"Zdobyte doœwiadczenie zamieniane jest na poziom, do 20 poziomu trwa rozwój specjalizacji dla postaci. \n");
			strcat(listcmd,""COL_GREY"{0d6400}Punkty specjalizacji"COL_GREY" mo¿esz przydzielaæ wciskaj¹c klawisz "COL_RED"Y"COL_GREY" oraz wybieraj¹c opcje {0d6400}Specjalizacje"COL_GREY" w GUI.\n");
			strcat(listcmd,""COL_GREY"Eksploruj najskrytsze zakamarki {0d644e}Whetstone"COL_GREY"/{0d644e}Back O' Beyond"COL_GREY" i znajduj {1d4a64}przedmioty"COL_GREY" koniecznie do przetrwania.\n");
			strcat(listcmd,""COL_GREY""COL_GREEN"Aby podnieœæ przedmioty"COL_GREY" le¿¹ce wokó³ Twojej postaci wciœnij klawisz "COL_RED"N"COL_GREY". \n");
			strcat(listcmd,""COL_GREY"{5db579}Handluj"COL_GREY" przedmiotami z innymi graczami b¹dŸ z sprzedawcami w {d44531}hali targowej"COL_GREY", która znajduje siê {d44531}krypcie"COL_GREY". \n");
			strcat(listcmd,""COL_GREY""COL_CYAN"¯etony"COL_GREY", czyli walutê serwerow¹ mo¿na zdobyæ tylko przez {d44531}handel na hali targowej"COL_GREY".\n");
			strcat(listcmd,""COL_GREY"{3cff00}Przez pierwsze 3 godziny"COL_GREY" rozgrywki, jeœli zginiesz to Twój ekwipunek "COL_GREEN"nie rozsypie siê na ziemiê"COL_GREY".\n");
			strcat(listcmd,""COL_GREY"Jest to czas na zapoznanie siê z serwerem, wykorzystaj go dobrze!\n");
			strcat(listcmd,""COL_GREY"Na serwerze "COL_RED"nie ma czatu globalnego"COL_GREY", jeœli chcesz mieæ kontakt z reszt¹ œwiata zaopatrz siê w "COL_RED"krótkofalówkê"COL_GREY".\n");
			strcat(listcmd,""COL_GREY"Pocz¹tki bywaj¹ trudne, dla pocz¹tkuj¹cych graczy "COL_GREY"zalecamy wydaæ pierwszy punkt w specjalizacje "COL_ORANGE"rusznikarstwo"COL_GREY" i zaopatrzyæ siê w {1d4a64}Colt 45"COL_GREY". \n");
			strcat(listcmd,""COL_GREY"Wszelkie {642500}BH/sprint"COL_RED" nie jest wskazane"COL_GREY", postaæ szybko siê mêczy. Aby "COL_GREEN"zregenerowaæ kondycjê"COL_GREY" zatrzymaj siê na chwilê b¹dŸ "COL_LIME"przejdŸ w tryb\n");
			strcat(listcmd,""COL_LIME"skradania"COL_GREY" wciskaj¹c klawisz "COL_RED"C"COL_GREY". Przechodz¹c w ten tryb "COL_GREEN"generujesz niski poziom ha³asu"COL_GREY", przez co staniesz siê "COL_GREEN"niewidoczny dla szwêdaczy"COL_GREY". \n");
			strcat(listcmd,""COL_RED"Walka ze szwêdaczami za pomoc¹ piêœci jest bardzo niebezpieczna!"COL_GREY" Dopóki nie zaopatrzysz siê w {1d4a64}broñ"COL_RED" omijaj walk z {2a5a5b}szwêdaczem"COL_GREY", "COL_LIME"przechodz¹c w tryb skradania"COL_GREY". \n");
			strcat(listcmd,""COL_GREY"{64000d}Powodzenia"COL_GREY"! \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_GREEN"» "COL_GREEN"Pomoc"COL_GREY" dotycz¹ca rozgrywki.", listcmd,"OK","");
		}
		case 1:
		{
			strcat(listcmd,""COL_GREEN"/b "COL_EASY"- Czat lokalny, bardzo bliskiego zasiêgu. \n");
			strcat(listcmd,""COL_GREEN"/do "COL_EASY"- Opisywanie akcji otoczenia wzglêdem gracza. \n");
			strcat(listcmd,""COL_GREEN"/l "COL_EASY"- Szept. \n");
			strcat(listcmd,""COL_GREEN"/me "COL_EASY"- Opisywanie akcji gracza. \n");
			strcat(listcmd,""COL_GREEN"/o "COL_EASY"- Czat globalny. "COL_RED"(zwykle pozostaje wy³¹czony) \n");
			strcat(listcmd,""COL_GREEN"/pm | /w "COL_EASY"- Prywatna wiadomoœæ. \n");
			strcat(listcmd,""COL_GREEN"/re "COL_EASY"- Odpisujesz do osoby, która ostatnio napisa³a do Ciebie na PW. \n");
			strcat(listcmd,""COL_GREEN"/k "COL_EASY"- Krzyk. \n");
			strcat(listcmd,""COL_GREEN"! "COL_EASY"- u¿ywanie krótkofalówki. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Komendy czatu", listcmd,"OK","");
		}
		case 2:
		{
			strcat(listcmd,""COL_GREEN"/autorzy "COL_EASY"- Ludzie którzy zaanga¿owali siê w powstanie projektu Angel Fall. \n");
			strcat(listcmd,""COL_GREEN"/admins "COL_EASY"- Lista Administratorów online. \n");
			//strcat(listcmd,""COL_GREEN"/animlist "COL_EASY"- Lista animacji. \n");
			strcat(listcmd,""COL_GREEN"/pomoc "COL_EASY"- Pomoc. \n");
			strcat(listcmd,""COL_GREEN"/report "COL_EASY"- Reportujesz gracza. \n");
			strcat(listcmd,""COL_GREEN"/stats "COL_EASY"- Wyœwietlanie statystyk. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Podstawowe komendy gracza", listcmd,"OK","");
		}
		case 3:
		{
			strcat(listcmd,""COL_GREEN"Komendy tylko dla Lidera/Vice Lidera grupy: \n");
			strcat(listcmd,""COL_GREEN"/ginvite "COL_EASY"- Zapraszasz gracza do swojej grupy. \n");
			strcat(listcmd,""COL_GREEN"/gkick "COL_EASY"- Wyrzucasz gracza ze swojej grupy. \n");
			strcat(listcmd,""COL_GREEN"/gsetvld "COL_EASY"- Nadajesz/Zdejmujesz V-ce Lidera grupy."COL_RED" [Tylko lider!] \n");
			strcat(listcmd,""COL_GREY"Komendy cz³onków: \n");
			strcat(listcmd,""COL_GREEN"/gmembers "COL_EASY"- Lista cz³onków ONLINE twojej grupy. \n");
			strcat(listcmd,""COL_GREEN"/gpanel "COL_EASY"- Informacje o grupie. \n");
			strcat(listcmd,""COL_GREEN"/gleave "COL_EASY"- Opuszczasz grupê. \n");
			strcat(listcmd,""COL_GREEN"/go "COL_EASY"- Otwieranie bramy bazy. \n");
			strcat(listcmd,""COL_GREEN"/gc "COL_EASY"- Otwieranie bramy bazy. \n");
			strcat(listcmd,""COL_GREEN"# "COL_EASY"- Czat grupowy. \n");
			strcat(listcmd,""COL_GREY"Obiektowanie bazy: \n");
			strcat(listcmd,""COL_GREEN"/gmc"COL_EASY"- Tworzenie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/msel "COL_EASY"- Wybieranie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mdel "COL_EASY"- Usuwanie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mcopy "COL_EASY"- Kopiowanie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mmat "COL_EASY"- Ustawianie textury/textu dla obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mrx "COL_EASY"- Ustawienie obrotu osi X obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mry "COL_EASY"- Ustawienie obrotu osi Y obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mrz "COL_EASY"- Ustawienie obrotu osi Z obiektu. \n");
			strcat(listcmd,""COL_GREY"Inne funkcje: \n");
			strcat(listcmd,""COL_GREEN"GPS "COL_EASY"- Widzisz cz³onków swojej grupy na mapie. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Komendy grup", listcmd,"OK","");
		}
		case 4:
		{
			if(gracz[playerid][MapperLvl] >= 2) 
			{
				strcat(listcmd,""COL_GREEN"/mmc "COL_EASY"- Przydatne obiekty. \n");
				strcat(listcmd,""COL_GREEN"/mtool "COL_EASY"- Narzêdzia mappera. \n");
			}
			strcat(listcmd,""COL_GREEN"/mc "COL_EASY"- Tworzenie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/msel "COL_EASY"- Wybieranie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mdel "COL_EASY"- Usuwanie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mcopy "COL_EASY"- Kopiowanie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mmat "COL_EASY"- Ustawianie textury/textu dla obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mrx "COL_EASY"- Ustawienie obrotu osi X obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mry "COL_EASY"- Ustawienie obrotu osi Y obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mrz "COL_EASY"- Ustawienie obrotu osi Z obiektu. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Komendy edytora obiektów", listcmd,"OK","");
		}
		case 5:
		{
			strcat(listcmd,""COL_GREY"Poni¿sza klawiszlogia obowi¹zuje na domyœlnych ustawieniach sterowania GTA:SA. \n");
			strcat(listcmd,""COL_GREY"Za pomoc¹ danych klawiszy, mo¿esz uruchomiæ nastêpuj¹ce funkcjonalnoœci: \n");
			strcat(listcmd,""COL_GREEN"Klawisz Y "COL_EASY"- Wyœwietlanie ekwipunku/spechakuzachu. \n");
			strcat(listcmd,""COL_GREEN"Klawisz N "COL_EASY"- Wyœwietlanie listy przedmiotów le¿¹cych wokó³ Ciebie. \n");
			strcat(listcmd,""COL_GREEN"LALT "COL_EASY"- Zarz¹dzanie pojazdem. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Klawiszologia", listcmd,"OK","");
		}
		case 6:
		{
			ShowPremiumMenu(playerid);
		}
	}
	return 1;
}

CMD:report(playerid, params[])
{
	if(gettime() - GetPVarInt(playerid, "ReportSpam") < 20) return Error(playerid, "Odczekaj trochê zanim wyœlesz kolejny report.");
	new targetid, reason[256];
	if(sscanf(params,"ds[256]", targetid, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /report [idgracza] [powód]");
	if(targetid == playerid) return Error(playerid, "Nie mo¿esz zreportowaæ siebie samego.");
	if(!gracz[playerid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	SetPVarInt(playerid, "ReportSpam", gettime());
	for(new a; a <= GetPlayerPoolSize(); a++)
	{
		if(gracz[a][loggedin] && gracz[a][AdminLevel])
		{
			SendClientMessageEx(a, 0xFF0000FF, "|REPORT| "COL_GREEN"%s[%d]"COL_WHITE" >> "COL_RED"%s[%d]"COL_WHITE" | Powód: %s", nick(playerid), playerid, nick(targetid), targetid, reason);
		}
	}
	mysql_escape_string(reason, reason, MySQL, 256);
	mq_format("INSERT INTO `player_report` (`uid`, `targetuid`, `reason`) VALUES ('%d', '%d', '%s');", gracz[playerid][UID], gracz[targetid][UID], reason);
	mq_send("REPORTQUERY");
	SendClientMessageEx(playerid, -1, "(("COL_GREEN"Report na gracza "COL_RED"%s"COL_GREEN" zosta³ wys³any! Dziêki!"COL_WHITE"))", nick(targetid));
	return 1;
}

CMD:tankuj(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie mo¿esz u¿ywaæ tej komendy bêd¹c w pojeŸdzie.");
	if(IsRangeOfDistributor(playerid))
	{
		new list_veh[1024];
		format(list_veh, 1024, "UID\tNazwa pojazdu");
		new detected_vehs;
		for(new v; v < WORLD_VEHICLES; v++)
		{
			if(pojazd[v][v_id])
			{
				if(!pojazd[v][v_enginestatus] && pojazd[v][v_paliwo] != 1000)
				{
					if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
					{
						format(list_veh, 1024, "%s\n"COL_BLACK"%d\t"COL_EASY"%s", list_veh, v, GetVehicleName(pojazd[v][v_model]));
						detected_vehs++;
					}
				}
			}
		}
		if(detected_vehs)
		{
			Dialog_Show(playerid, REFUELDIS, DIALOG_STYLE_TABLIST_HEADERS, "Który pojazd chcesz zatankowaæ?", list_veh, "Wybierz", "Anuluj");
		}
		else
		{
			LeftNotifyShow(playerid, "error", "Aby uzupelnic paliwo, musisz sie znajdowac przy ~r~zgaszonym, niezatankwanym do pelna ~y~pojezdzie~w~.");
		}
	}
	else
	{
		Error(playerid, "Musisz byæ przy sprawnym dystrybutorze.");
	}
	return 1;
}

Dialog:REFUELDIS(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new v = strval(inputtext);
	if(pojazd[v][v_id])
	{
		if(!pojazd[v][v_enginestatus] && pojazd[v][v_paliwo] != 1000)
		{
			if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
			{
				SetPVarInt(playerid, "world_vehrefuel", v);
				TogglePlayerControllable(playerid, false);
				StartCombineMode(playerid, 10);
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzupelnic paliwo w ~y~pojezdzie~w~, musisz sie przy nim znajdowac.");
			}
		}
		else
		{
			LeftNotifyShow(playerid, "error", "Pojazd nie ma ~r~zgaszonego~w~ silnika lub ~y~pojazd~w~ jest zatankowany do ~g~pelna~w~.");
		}
	}
	return 1;
}

CMD:admins(playerid, params[])
{
	new fstring[256], string[1000];
	new liczae;
	liczae = 0;
	for(new i=0; i < MAX_PLAYERS; i++)
	{
		if(gracz[i][loggedin])
		{
			if(gracz[i][admin_duty] >= 1)
			{
				if(gracz[i][admin_duty] == 1) format(fstring, sizeof(fstring),"{FFAF00}%s {B700FF}(ID:%d) {FFFFFF}- {B7FF00}Typ: {00A09E}Support{FFFFFF}\n", gracz[i][master_nick], i);
				else if(gracz[i][admin_duty] == 2) format(fstring, sizeof(fstring),"{FFAF00}%s {B700FF}(ID:%d) {FFFFFF}- {B7FF00}Typ: {0052dd}Game Master{FFFFFF}\n", gracz[i][master_nick], i);
				else if(gracz[i][admin_duty] >= 3) format(fstring, sizeof(fstring),"{FFAF00}%s {B700FF}(ID:%d) {FFFFFF}- {B7FF00}Typ: {FF0000}Administrator{FFFFFF}\n", gracz[i][master_nick], i);
				strcat(string, fstring, sizeof(string));
				liczae++;
			}
		}
	}
	if(liczae == 0)
	{
		ShowPlayerDialog(playerid,INFO_DIALOG,DIALOG_STYLE_MSGBOX,""COL_RED"»"COL_GREY" Administracja "COL_GREEN"na s³u¿bie", "{FFAF00}Brak Administracji ONLINE!","OK","");
	} 
	else
	{
		ShowPlayerDialog(playerid,INFO_DIALOG,DIALOG_STYLE_MSGBOX,""COL_RED"»"COL_GREY" Administracja "COL_GREEN"na s³u¿bie",string,"OK","");
	}
	return 1;
}

CMD:stats(playerid, params[])
{
	new str_header[128];
	new str_stats[2048];
	format(str_header, 128, "{7e6644}» "COL_GREY"Statystyki postaci:{0d644e} %s", nick(playerid));
	format(str_stats, 2048, "Statystyka\tWartoœæ");
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Nick\t"COL_EASY"%s", str_stats, nick(playerid));
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"UID postaci\t"COL_EASY"%d", str_stats, gracz[playerid][UID]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Konto master\t"COL_EASY"%s", str_stats, gracz[playerid][master_nick]);
	format(str_stats, 2048, "%s\n{6f3e9c}» "COL_GREY"Poziom\t{6f3e9c}%d", str_stats, gracz[playerid][level]);
	format(str_stats, 2048, "%s\n{6f3e9c}» "COL_GREY"Doœwiadczenie\t"COL_GREEN"%d{6f3e9c}/"COL_RED"%d", str_stats, gracz[playerid][exp], gracz[playerid][need_exp]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Zabitych szwêdaczy\t%d", str_stats, gracz[playerid][KillZombies]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Zabójstwa\t%d", str_stats, gracz[playerid][KillHumans]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Przegrano\t%02d godzin, %02d minut, %02d sekund", str_stats, gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][PSek]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_CYAN"¯etony\t"COL_GREY"%d", str_stats, gracz[playerid][zetony]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_YELLOW"¯etony premium\t"COL_GREY"%d", str_stats, gracz[playerid][gold]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Si³a\t"COL_GREEN"%d"COL_GREY"/100", str_stats, gracz[playerid][sila]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"G³ód\t"COL_GREEN"%d"COL_GREY"/100", str_stats, gracz[playerid][Glod]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Pragnienie\t"COL_GREEN"%d"COL_GREY"/100", str_stats, gracz[playerid][Pragn]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Napromieniowanie\t"COL_RED"%d"COL_GREY"/100", str_stats, gracz[playerid][rads]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Spec: "COL_ORANGE"Rusznikarstwo\t"COL_GREEN"%d"COL_GREY"/17", str_stats, gracz[playerid][rusznikarstwo]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Spec: "COL_DBLUE"Motoryzacja\t"COL_GREEN"%d"COL_GREY"/11", str_stats, gracz[playerid][motoryzacja]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Spec: "COL_BLUE"Medycyna\t"COL_GREEN"%d"COL_GREY"/17", str_stats, gracz[playerid][medycyna]);
	if(gracz[playerid][OrgID]) 
	{
		format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Grupa\t"COL_RED"["COL_GREY"%s"COL_RED"]"COL_GREY"%s", str_stats, gracz[playerid][group_tag] , gracz[playerid][group_name]);
	}
	if(isvip(playerid))
	{
		new dd, hh, mm, ss;
		SecToTime(gracz[playerid][vip]-serwer[time_timestamp], dd, hh, mm, ss);
		format(str_stats, 2048, "%s\n{77fd04}» "COL_ORANGE"Konto premium\t"COL_GREY"%02d dni, %02d godzin, %02d minut, %02d sekund", str_stats, dd, hh, mm, ss);
	}
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, str_header, str_stats,"Zamknij","");
	return 1;
}


CMD:wedkuj(playerid)
{
	mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='159' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("QStartFishing", "d", playerid);
	return 1;
}

forward QStartFishing(playerid);
public QStartFishing(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		UseItem(playerid, 159);
	}
	else
	{
		Error(playerid, "Brak wêdki w ekwipunku.");
	}
	return 1;
}