//****************************************************************************************************************************************CZAT G£ÓWNY
public OnPlayerText(playerid, text[])
{
	new pText[512];
	if(gracz[playerid][muted_timestamp] > serwer[time_timestamp])
	{
		format(pText, 512,  "Jesteœ uciszony. Pozosta³o: "COL_RED"%d"COL_WHITE" sekund.", gracz[playerid][muted_timestamp] - serwer[time_timestamp]);
		Error(playerid, pText);
		return 0;
	}
	if(gracz[playerid][BWTime])
	{
		Error(playerid, "Jesteœ nieprzytomny - nie mo¿esz mówiæ.");
		return 0;
	}
	text[0] = chrtoupper(text[0]);
	//ADMIN
	if(text[0] == '`' && gracz[playerid][AdminLevel])
	{
		for(new a = PlayerPoolSize(); a != -1; a--)
		{
			if(!gracz[a][loggedin]) continue;
			if(!gracz[a][AdminLevel]) continue;
			format(pText, 512, "@"COL_WHITE"(%d)"COL_RED"%s"COL_WHITE" » %s", playerid, gracz[playerid][master_nick], text[1]);
			SendClientMessage(a, 0xFF0000AA, pText);
		}
		return 0;
	}
	//GRUPOWA KRÓTKOFALÓWKA
	if(text[0] == '#' && gracz[playerid][OrgID])
	{
		if(Interpunkcja(text[1]))
		{
			format(pText, 512, "%s (krótkofalówka): %s", nick(playerid), text[1]);
		}
		else
		{
			format(pText, 512, "%s (krótkofalówka): %s.", nick(playerid), text[1]);
		}
		ProxDetector(playerid, 8.0, pText, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
		if(Interpunkcja(text[1]))
		{
			format(pText, 512, "{276288}[{00B403}%s{276288}]{088FCC}%s"COL_WHITE": %s", gracz[playerid][group_tag], nick(playerid), text[1]);
		}
		else
		{
			format(pText, 512, "{276288}[{00B403}%s{276288}]{088FCC}%s"COL_WHITE": %s.", gracz[playerid][group_tag], nick(playerid), text[1]);
		}
		for(new k = PlayerPoolSize(); k != -1; k--)
		{
			if(!gracz[k][loggedin]) continue;
			if(gracz[playerid][OrgID] != gracz[k][OrgID]) continue;
			SendMSGLamane(k, -1, pText);
		}
		return 0;
	}
	if(text[0] == '!' && gracz[playerid][krotkofala])
	{
		if(Interpunkcja(text[1]))
		{
			format(pText, 512, "%s (krótkofalówka): %s", nick(playerid), text[1]);
		}
		else
		{
			format(pText, 512, "%s (krótkofalówka): %s.", nick(playerid), text[1]);
		}
		ProxDetector(playerid, 8.0, pText, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
		if(Interpunkcja(text[1]))
		{
			format(pText, 512, "{276288}[{15940E}%d MHz{276288}]{088FCC}%s"COL_WHITE": %s", gracz[playerid][KRMHZ], nick(playerid), text[1]);
		}
		else
		{
			format(pText, 512, "{276288}[{15940E}%d MHz{276288}]{088FCC}%s"COL_WHITE": %s.", gracz[playerid][KRMHZ], nick(playerid), text[1]);
		}
		for(new k = PlayerPoolSize(); k != -1; k--)
		{
			if(!gracz[k][loggedin]) continue;
			if(!gracz[k][krotkofala] || gracz[playerid][KRMHZ] != gracz[k][KRMHZ]) continue;
			SendMSGLamane(k, -1, pText);
		}
		return 0;
	}
	if(gracz[playerid][admin_duty])
	{
		format(pText, 512, ""COL_RED"%s", text);
		ShowBubble(playerid, pText);
		format(pText, 512, ""COL_RED"%s"COL_WHITE": %s", gracz[playerid][master_nick], text);
		ProxDetector(playerid, 18.0, pText, 0xFFFFFF96, 0xFFFFFF96, 0xFFFFFF96, 0xFFFFFF96,  0xFFFFFF96);
		return 0;
	}
	//GRACZ
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	if(Interpunkcja(text))
	{
		format(pText, 512, "%s mówi: %s", nick(playerid), text);
	}
	else
	{
		format(pText, 512, "%s mówi: %s.", nick(playerid), text);
	}
	ShowBubble(playerid, text);
	ProxDetector(playerid, 18.0, pText, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
	return 0;
}

stock ShowBubble(playerid, text[])
{
	format(gracz[playerid][bubble_text], 144, "%s", text);
	gracz[playerid][bubble_timestamp] = serwer[time_timestamp]+10;
	return 1;
}
//****************************************************************************************************************************************INNE CZATY
CMD:b(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[128];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /b [wiadomoœæ]");
	format(str, sizeof(str), ""COL_GREY"(( %s (ID: %d): %s ))", gracz[playerid][master_nick], playerid, message);
	SendNearByMessage(playerid, -1, str, 5);
	return 1;
}

CMD:o(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[128];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /o [wiadomoœæ]");
	if(gracz[playerid][AdminLevel] < 1)
	{
		if(!serwer[ooc_status]) return Error(playerid, "Czat globalny jest aktualnie niedostêpny.");
	}
	message[0] = chrtoupper(message[0]);
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(gracz[i][loggedin])
		{
			format(str, 128, ""COL_WHITE"(( %s (ID: %d): %s ))", gracz[playerid][master_nick], playerid, message);
			SendMSGLamane(i, -1, str);
		}
	}
	return 1;
}

CMD:l(playerid, params[])
{
	if(gracz[playerid][BWTime])
	{
		Error(playerid, "Jesteœ nieprzytomny - nie mo¿esz mówiæ.");
		return 1;
	}
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /l [wiadomoœæ]");
	message[0] = chrtoupper(message[0]);
	format(str, sizeof(str), ""COL_GREY"%s szepcze: %s", nick(playerid), message);
	SendNearByMessage(playerid, -1, str, 2.5);
	return 1;
}

CMD:me(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /me [akcja]");
	format(str, 128, "* %s %s", nick(playerid), message);
	SendNearByMessage(playerid, 0xC2A2DAAA, str, 10);
	return 1;
}

CMD:do(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /do [akcja]");
	format(str, 128, "* %s ((%s))", message, nick(playerid));
	SendNearByMessage(playerid, 0x6082B6FF, str, 10);
	return 1;
}

CMD:k(playerid, params[])
{
	if(gracz[playerid][BWTime])
	{
		Error(playerid, "Jesteœ nieprzytomny - nie mo¿esz mówiæ.");
		return 1;
	}
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /k [wiadomoœæ]");
	message[0] = chrtoupper(message[0]);
	format(str, 128, "%s krzyczy: %s!", nick(playerid), message);
	ProxDetector(playerid, 35.0, str, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
	return 1;
}

CMD:re(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[256], str[256];
	if(GetPVarInt(playerid, "RePM") == -1) return Error(playerid, "Nie mo¿esz odpisaæ, gdy¿ nikt ostatnio do Ciebie nie napisa³ PM.");
	new targetid;
	targetid = GetPVarInt(playerid, "RePM");
	if(sscanf(params,"s[256]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /re [wiadomoœæ]");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz o takim ID nie jest po³¹czony z serwerem.");
	if(strlen(message) < 1) return Error(playerid, "Wiadomoœæ jest za krótka.");
	format(str, sizeof(str), ""COL_RED">>"COL_BLUE" %s[%d]:"COL_WHITE" %s", gracz[targetid][master_nick], targetid, message);
	SendMSGLamane(playerid, -1, str);
	format(str, sizeof(str), ""COL_GREEN"<<"COL_BLUE" %s[%d]:"COL_WHITE" %s", gracz[playerid][master_nick], playerid, message);
	SendMSGLamane(targetid, -1, str);
	SetPVarInt(targetid, "RePM", playerid);
	return 1;
}
CMD:w(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new targetid, message[256], str[256];
	if(sscanf(params,"ds[256]", targetid, message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /w [idgracza] [wiadomoœæ]");
	if(targetid == playerid) return Error(playerid, "Nie mo¿esz wys³aæ wiadomoœci do samego siebie.");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz o takim ID nie jest po³¹czony z serwerem.");
	format(str, sizeof(str), ""COL_RED">>"COL_BLUE" %s[%d]:"COL_WHITE" %s", gracz[targetid][master_nick], targetid, message);
	SendMSGLamane(playerid, -1, str);
	format(str, sizeof(str), ""COL_GREEN"<<"COL_BLUE" %s[%d]:"COL_WHITE" %s", gracz[playerid][master_nick], playerid, message);
	SendMSGLamane(targetid, -1, str);
	SetPVarInt(targetid, "RePM", playerid);
	return 1;
}
CMD:pm(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new targetid, message[256], str[256];
	if(sscanf(params,"ds[256]", targetid, message)) return SendClientMessage(playerid, -1, ""COL_GREY"U¯YJ: /pm [idgracza] [wiadomoœæ]");
	if(targetid == playerid) return Error(playerid, "Nie mo¿esz wys³aæ wiadomoœci do samego siebie.");
	if(!gracz[targetid][loggedin]) return Error(playerid, "Gracz o takim ID nie jest po³¹czony z serwerem.");
	format(str, sizeof(str), ""COL_RED">>"COL_BLUE" %s[%d]:"COL_WHITE" %s", gracz[targetid][master_nick], targetid, message);
	SendMSGLamane(playerid, -1, str);
	format(str, sizeof(str), ""COL_GREEN"<<"COL_BLUE" %s[%d]:"COL_WHITE" %s", gracz[playerid][master_nick], playerid, message);
	SendMSGLamane(targetid, -1, str);
	SetPVarInt(targetid, "RePM", playerid);
	return 1;
}