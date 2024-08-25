stock Init_Groups()
{
	mq_format("SELECT * FROM `Grupy` WHERE `expire`<'%d';", serwer[time_timestamp]);
	mq_send("QInitGroups");
	return 1;
}

forward QInitGroups();
public QInitGroups()
{
	mq_getdata();
	if(rekordy)
	{
		printf("[GRUPY]Znaleziono %d grup kwalifikujacych sie do usuniecia...", rekordy);
		new i;
		new gid;
		while(i < rekordy)
		{
			gid = cache_get_field_content_int(i, "id");
			mq_format("DELETE FROM `Grupy` WHERE `id`='%d';", gid);
			mysql_query(MySQL, mQuery, false);
			mq_format("UPDATE `Konta` SET `OrgID`='0', `SzefORG`='0', `ViceSzefORG`='0' WHERE `OrgID`='%d' OR `SzefORG`='%d' OR `ViceSzefORG`='%d';", gid, gid, gid);
			mq_send("QDelUserFromG");
			printf("[GRUPY]Usuwam grupe o ID: %d", gid);
			i++; 
		}
	}
	else
	{
		printf("[GRUPY]Nie znaleziono grup do usuniecia!");
	}
	Init_BazyGrup();
	return 1;
}

stock CreateGroup(playerid, nazwa[], tag[])
{
	mysql_escape_string(nazwa, nazwa, MySQL, 64);
	mysql_escape_string(tag, tag, MySQL, 8);
	new expire = serwer[time_timestamp]+((60*60)*24)*31;
	mq_format("INSERT INTO `Grupy` (`id`, `Nazwa`, `Skrot`, `expire`) VALUES (NULL, '%s', '%s', '%d');", nazwa, tag, expire);
	new Cache:cache_id = mysql_query(MySQL, mQuery);
	new gid = cache_insert_id();
	cache_delete(cache_id);
	format(gracz[playerid][group_name], 128, "%s", nazwa);
	format(gracz[playerid][group_tag], 8, "%s", tag);
	gracz[playerid][OrgID] = gid;
	gracz[playerid][SzefORG] = gracz[playerid][OrgID];
	gracz[playerid][ViceSzefORG] = gracz[playerid][OrgID];
	mq_format("UPDATE `Konta` SET `OrgID`='%d', `SzefORG`='%d', `ViceSzefORG`='%d' WHERE `id`='%d';", gracz[playerid][OrgID], gracz[playerid][SzefORG], gracz[playerid][ViceSzefORG], gracz[playerid][UID]);
	mq_send("QSetUserGroup");
	return gid;
}
//KOMENDY GRUP
CMD:gpanel(playerid, params[])
{
	if(Spam(playerid, SPAM_CMD, 5)) return 1;
	if(!gracz[playerid][OrgID]) return Error(playerid, "Nie nale¿ysz do grupy.");
	mq_format("SELECT * FROM `Grupy` WHERE `id`='%d';", gracz[playerid][OrgID]);
	mq_send("QGPanel", "d", playerid);
	return 1;
}

forward QGPanel(playerid);
public QGPanel(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new str_header[256];
		new str_gpanel[2048];
		format(str_header, 256, ""COL_ORANGE"» "COL_WHITE"Panel grupy ["COL_BLUE"%s"COL_WHITE"]"COL_BLUE"%s", gracz[playerid][group_tag], gracz[playerid][group_name]);
		format(str_gpanel, 2048, ""COL_GREY"Nazwa grupy:\t"COL_EASY"%s", gracz[playerid][group_name]);
		format(str_gpanel, 2048, "%s\n"COL_GREY"TAG grupy:\t"COL_WHITE"["COL_ORANGE"%s"COL_WHITE"]", str_gpanel, gracz[playerid][group_tag]);
		new days_expire = (cache_get_field_content_int(0, "expire")-serwer[time_timestamp])/60/60/24;
		new baza_expire = (cache_get_field_content_int(0, "baza_expire")-serwer[time_timestamp])/60/60/24;
		if(days_expire > 4)
		{
			format(str_gpanel, 2048, "%s\n"COL_GREY"Grupa wygasa za:\t"COL_GREEN"%d dni", str_gpanel, days_expire);
		}
		else
		{
			format(str_gpanel, 2048, "%s\n"COL_GREY"Grupa wygasa za:\t"COL_RED"%d dni", str_gpanel, days_expire);
		}
		mq_format("SELECT `OrgID` FROM `Konta` WHERE `OrgID`='%d';", gracz[playerid][OrgID]);
		new Cache:cache_cache = cache_save(MySQL);
		new Cache:QGetMembers = mysql_query(MySQL, mQuery);
		new members_count = cache_get_row_count();
		cache_delete(QGetMembers);
		format(str_gpanel, 2048, "%s\n"COL_GREY"Iloœæ osób w grupie:\t"COL_RED"%d"COL_WHITE"/"COL_GREEN"10", str_gpanel, members_count);
		cache_set_active(cache_cache);
		new g_exp = cache_get_field_content_int(0, "exp");
		new g_level = 1;
		new g_calc_needexp = g_level*80;
		while(g_exp >= g_calc_needexp)
		{
			g_exp -= g_calc_needexp;
			g_level++;
			g_calc_needexp = g_level*80;
		}
		format(str_gpanel, 2048, "%s\n"COL_GREY"Poziom grupy:\t{96ff00}%d", str_gpanel, g_level);
		format(str_gpanel, 2048, "%s\n"COL_GREY"Stan EXP:\t"COL_GREEN"%d"COL_PURPLE"/"COL_RED"%d", str_gpanel, g_exp, g_calc_needexp);
		if(GetGroupBaseID(gracz[playerid][OrgID]) != -1)
		{
			if(baza_expire  > 4)
			{
				format(str_gpanel, 2048, "%s\n"COL_GREY"Baza grupy wygasa za:\t"COL_GREEN"%d dni", str_gpanel, baza_expire);
			}
			else
			{
				format(str_gpanel, 2048, "%s\n"COL_GREY"Baza grupy wygasa za:\t"COL_RED"%d dni", str_gpanel, baza_expire);
			}
		}
		Dialog_Show(playerid, GPANEL, DIALOG_STYLE_TABLIST, str_header, str_gpanel, "Wybierz", "WyjdŸ");
		cache_delete(cache_cache);
	}
	return 1;
}

Dialog:GPANEL(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 2:
		{
			if(gracz[playerid][SzefORG] || gracz[playerid][ViceSzefORG]) dialog_PREMIUM(playerid, 1, 2, "null");
		}
		case 3:
		{
			PC_EmulateCommand(playerid, "/gmembers");
		}
	}
	return 1;
}

CMD:gmembers(playerid, params[])
{
	if(!gracz[playerid][OrgID]) return Error(playerid, "Nie nale¿ysz do grupy.");
	new listgroup_str[2048];
	format(listgroup_str, 2048, "ID\tNick\tRanga\n");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][OrgID] == gracz[playerid][OrgID])
			{
				if(gracz[p][SzefORG] == gracz[playerid][OrgID]) format(listgroup_str, 2048, "%s\n"COL_BLACK"%d\t"COL_GREY"%s\t"COL_RED"Lider", listgroup_str, p, nick(p));
				else if(gracz[p][SzefORG] == gracz[playerid][OrgID]) format(listgroup_str, 2048, "%s\n"COL_BLACK"%d\t"COL_GREY"%s\t"COL_YELLOW"V-ce Lider", listgroup_str, p, nick(p));
				else format(listgroup_str, 2048, "%s\n"COL_BLACK"%d\t"COL_GREY"%s\t"COL_GREEN"Cz³onek", listgroup_str, p, nick(p));
			}
		}
	}
	Dialog_Show(playerid, GMEMBERS, DIALOG_STYLE_TABLIST_HEADERS, ""COL_GREY"Lista graczy "COL_GREEN"ONLINE"COL_GREY", nale¿¹cych do Twoje grupy", listgroup_str, "OK", "");
	return 1;
}

CMD:ginvite(playerid, params[])
{
	if(!gracz[playerid][SzefORG] && !gracz[playerid][ViceSzefORG]) return Error(playerid, "Brak uprawnieñ.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /invite [idgracza]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(targetid == playerid) return Error(playerid, "Nie mo¿esz zaprosic samego siebie");
	if(gracz[targetid][OrgID]) return Error(playerid, "Ten gracz nale¿y do innej grupy.");
	mq_format("SELECT `OrgID` FROM `Konta` WHERE `OrgID`='%d';", gracz[playerid][OrgID]);
	new Cache:QGetMembers = mysql_query(MySQL, mQuery);
	new members_count = cache_get_row_count();
	cache_delete(QGetMembers);
	if(members_count >= 10) return Error(playerid, "W Twojej grupie jest ju¿ maxymalna iloœæ osób.");
	gracz[targetid][group_join] = gracz[playerid][OrgID];
	format(gracz[targetid][group_name], 128, "%s", gracz[playerid][group_name]);
	format(gracz[targetid][group_tag], 8, "%s", gracz[playerid][group_tag]);
	SendClientMessageEx(playerid, -1, "((Wys³ano zaproszenie do: "COL_BLUE"%s"COL_WHITE"[%d]. Poinformuj zaproszonego aby wpisa³: "COL_RED"/gjoin %d"COL_WHITE"))", nick(targetid), targetid, gracz[targetid][group_join]);
	return 1;
}

CMD:gkick(playerid, params[])
{
	if(!gracz[playerid][SzefORG] && !gracz[playerid][ViceSzefORG]) return Error(playerid, "Brak uprawnieñ.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /gkick [idgracza]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(targetid == playerid) return Error(playerid, "Nie mo¿esz wyrzuciæ samego siebie");
	if(gracz[targetid][OrgID] != gracz[playerid][OrgID]) return Error(playerid, "Ten gracz nie nale¿y do Twojej grupy.");
	if(gracz[targetid][SzefORG]) return Error(playerid, "Ten gracz jest liderem!");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][OrgID] == gracz[targetid][OrgID] && p != targetid)
			{
				SendClientMessageEx(p, -1, "((Gracz "COL_BLUE"%s[%d]"COL_WHITE" zosta³ "COL_RED"wyrzucony"COL_WHITE" z Twojej grupy!))", nick(targetid), targetid);
			}
		}
	}
	gracz[targetid][OrgID] = 0;
	gracz[targetid][ViceSzefORG] = 0;
	mq_format("UPDATE `Konta` SET `OrgID`='%d', `ViceSzefORG`='%d' WHERE `id`='%d';", gracz[targetid][OrgID], gracz[targetid][ViceSzefORG], gracz[targetid][UID]);
	mq_send("QKickGroup");
	SendClientMessageEx(targetid, -1, "((Zosta³eœ "COL_RED"wyrzucony"COL_WHITE" z grupy "COL_PURPLE"%s"COL_WHITE".))", gracz[playerid][group_name]);
	return 1;
}

CMD:gjoin(playerid, params[])
{
	if(!gracz[playerid][group_join]) return Error(playerid, "Nie otrzyma³eœ zaproszenia.");
	new groupid;
	if(sscanf(params,"d", groupid)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /join [idgrupy]");
	if(gracz[playerid][group_join] != groupid) return Error(playerid, "Nie dosta³eœ zaproszenia od tej grupy.");
	gracz[playerid][OrgID] = gracz[playerid][group_join];
	gracz[playerid][group_join] = 0;
	SendClientMessageEx(playerid, -1, "((Do³¹czy³eœ do grupy: "COL_GREEN"[%s]"COL_RED"%s"COL_WHITE". Wszelkie komendy znajdziesz pod "COL_YELLOW"/pomoc"COL_WHITE".))", gracz[playerid][group_tag], gracz[playerid][group_name]);
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][OrgID] == gracz[playerid][OrgID] && p != playerid)
			{
				SendClientMessageEx(p, -1, "((Gracz "COL_BLUE"%s[%d]"COL_WHITE" "COL_GREEN"do³¹czy³"COL_WHITE" do Twojej grupy!))", nick(playerid), playerid);
			}
		}
	}
	mq_format("UPDATE `Konta` SET `OrgID`='%d' WHERE `id`='%d';", gracz[playerid][OrgID], gracz[playerid][UID]);
	mq_send("QJoinGroup");
	return 1;
}

CMD:gleave(playerid, params[])
{
	if(!gracz[playerid][OrgID]) return Error(playerid, "Nie nale¿ysz do grupy.");
	if(gracz[playerid][SzefORG]) return Error(playerid, "Jesteœ liderem, nie mo¿esz opuœciæ grupy.");
	SendClientMessageEx(playerid, -1, "((Opuœci³eœ grupê: "COL_GREEN"[%s]"COL_RED"%s"COL_WHITE".))", gracz[playerid][group_tag], gracz[playerid][group_name]);
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][OrgID] == gracz[playerid][OrgID] && p != playerid)
			{
				SendClientMessageEx(p, -1, "((Gracz "COL_BLUE"%s[%d]"COL_WHITE" "COL_RED"opuœci³"COL_WHITE" Twoj¹ grupê!))", nick(playerid), playerid);
			}
		}
	}
	gracz[playerid][OrgID] = 0;
	gracz[playerid][ViceSzefORG] = 0;
	mq_format("UPDATE `Konta` SET `OrgID`='%d', `ViceSzefORG`='%d' WHERE `id`='%d';", gracz[playerid][OrgID], gracz[playerid][ViceSzefORG], gracz[playerid][UID]);
	mq_send("QLeaveGroup");
	return 1;
}

CMD:gsetvld(playerid, params[])
{
	if(!gracz[playerid][SzefORG]) return Error(playerid, "Brak uprawnieñ.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /gsetvld [idgracza]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(targetid == playerid) return Error(playerid, "Nie mo¿esz u¿yæ tej komendy na sobie.");
	if(gracz[targetid][OrgID] != gracz[playerid][OrgID]) return Error(playerid, "Ten gracz nie nale¿y do Twojej grupy.");
	if(gracz[targetid][SzefORG]) return Error(playerid, "Ten gracz jest liderem!");
	if(gracz[targetid][ViceSzefORG])
	{
		gracz[targetid][ViceSzefORG] = 0;
		SendClientMessageEx(playerid, -1, "(("COL_RED"Zabrano"COL_WHITE" V-ce Lidera dla gracza "COL_BLUE"%s"COL_WHITE"[%d].))", nick(targetid), targetid);
		SendClientMessageEx(targetid, -1, "((Zosta³a Tobie "COL_RED"odebrana"COL_WHITE" ranga V-ce Lidera grupy: "COL_PURPLE"%s"COL_WHITE".))", gracz[playerid][group_name]);
	}
	else
	{
		gracz[targetid][ViceSzefORG] = gracz[playerid][OrgID];
		SendClientMessageEx(playerid, -1, "(("COL_GREEN"Nadano"COL_WHITE" V-ce Lidera dla gracza "COL_BLUE"%s"COL_WHITE"[%d].))", nick(targetid), targetid);
		SendClientMessageEx(targetid, -1, "((Zosta³a Tobie "COL_GREEN"nadana"COL_WHITE" ranga V-ce Lidera grupy: "COL_PURPLE"%s"COL_WHITE".))", gracz[playerid][group_name]);
	}
	mq_format("UPDATE `Konta` SET `ViceSzefORG`='%d' WHERE `id`='%d';", gracz[targetid][ViceSzefORG], gracz[targetid][UID]);
	mq_send("QSetVLDGroup");
	return 1;
}

CMD:go(playerid, params[])
{
	new groupid = gracz[playerid][OrgID];
	if(!groupid) return Error(playerid, "Nie nale¿ysz do grupy.");
	new baza_id = GetGroupBaseID(groupid);
	if(baza_id == -1) return Error(playerid, "Twoja grupa nie posiada bazy.");
	Baza_OpenGate(baza_id);
	LeftNotifyShow(playerid, "info", "Brama bazy ~g~otwarta~w~.");
	return 1;
}

CMD:gc(playerid, params[])
{
	new groupid = gracz[playerid][OrgID];
	if(!groupid) return Error(playerid, "Nie nale¿ysz do grupy.");
	new baza_id = GetGroupBaseID(groupid);
	if(baza_id == -1) return Error(playerid, "Twoja grupa nie posiada bazy.");
	Baza_CloseGate(baza_id);
	LeftNotifyShow(playerid, "info", "Brama bazy ~r~zamknieta~w~.");
	return 1;
}