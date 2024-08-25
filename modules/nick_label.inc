stock CreateLabelNick(playerid)
{
	gracz[playerid][p_label] = CreateDynamic3DTextLabel("GRACZ", -1, 0.0, 0.0, 0.4, 5.0, playerid, INVALID_VEHICLE_ID, 1);
	return 1;
}

stock DestroyLabelNick(playerid)
{
	DestroyDynamic3DTextLabel(gracz[playerid][p_label]);
	return 1;
}

stock Process_NickLabel(playerid)
{
	if(gracz[playerid][bubble_timestamp] < serwer[time_timestamp] && gracz[playerid][bubble_timestamp] != 0)
	{
		format(gracz[playerid][bubble_text], 144, " ");
		gracz[playerid][bubble_timestamp] = 0;
	}
	if(gracz[playerid][OrgID])
	{
		if(isvip(playerid)) format(gracz[playerid][p_label_string], 512, "%s\n\n"COL_RED"[%s]{B0B200}%s "COL_WHITE"[%d]\n{4d4d4d}[Status: %s{4d4d4d}]\n<Poziom: {088DA5}%d{4d4d4d}>", gracz[playerid][bubble_text], gracz[playerid][group_tag], nick(playerid), playerid, GetPlayerStatus(playerid), gracz[playerid][level]);
		else format(gracz[playerid][p_label_string], 512, "%s\n\n"COL_RED"[%s]{a1a1a1}%s "COL_WHITE"[%d]\n{4d4d4d}[Status: %s{4d4d4d}]\n<Poziom: {088DA5}%d{4d4d4d}>", gracz[playerid][bubble_text], gracz[playerid][group_tag], nick(playerid), playerid, GetPlayerStatus(playerid), gracz[playerid][level]);
	}
	else
	{
		if(isvip(playerid)) format(gracz[playerid][p_label_string], 512, "%s\n\n{B0B200}%s "COL_WHITE"[%d]\n{4d4d4d}[Status: %s{4d4d4d}]\n<Poziom: {088DA5}%d{4d4d4d}>", gracz[playerid][bubble_text], nick(playerid), playerid, GetPlayerStatus(playerid), gracz[playerid][level]);
		else format(gracz[playerid][p_label_string], 512, "%s\n\n{a1a1a1}%s "COL_WHITE"[%d]\n{4d4d4d}[Status: %s{4d4d4d}]\n<Poziom: {088DA5}%d{4d4d4d}>", gracz[playerid][bubble_text], nick(playerid), playerid, GetPlayerStatus(playerid), gracz[playerid][level]);
	}
	UpdateDynamic3DTextLabelText(gracz[playerid][p_label], 0x20B2AAFF, gracz[playerid][p_label_string]);
	return 1;
}

stock GetPlayerStatus(playerid)
{
	new status[128];
	if(isvip(playerid)) format(status, 128, "{B0B200}VIP");
	else format(status, 128, ""COL_GREEN"OK");
	if(gracz[playerid][admin_duty])
	{
		format(status, 128, ""COL_RED"admin duty");
	}
	else if(IsPlayerAFK(playerid))
	{
		format(status, 128, ""COL_WHITE"AFK od godziny: %02d:%02d", gracz[playerid][afk_control_hour], gracz[playerid][afk_control_minute]);
	}
	else if(gracz[playerid][BWTime])
	{
		format(status, 128, ""COL_RED"nieprzytomny "COL_WHITE"(%ds)", gracz[playerid][BWTime]);
	}
	else if(SpawnProtect(playerid))
	{
		format(status, 128, ""COL_GREEN"niezniszczalny");
	}
	else if(ognisko[playerid][o_status] > 299)
	{
		format(status, 128, ""COL_ORANGE"rozpala ognisko");
	}
	else if(combine_mode[playerid][c_id])
	{
		switch(combine_mode[playerid][c_id])
		{
			case 1..4:
			{
				format(status, 128, ""COL_ORANGE"æwiczy");
			}
			case 5..6:
			{
				format(status, 128, ""COL_ORANGE"odpala pojazd");
			}
			case 7..8:
			{
				format(status, 128, ""COL_ORANGE"uzupe³nia paliwo");
			}
			case 9:
			{
				format(status, 128, ""COL_ORANGE"u¿ywa narzêdzi");
			}
			case 10:
			{
				format(status, 128, ""COL_ORANGE"tankuje");
			}
			case 11:
			{
				format(status, 128, ""COL_ORANGE"gotuje");
			}
			case 12:
			{
				format(status, 128, ""COL_ORANGE"u¿ywa przedmiotu");
			}
			case 13:
			{
				format(status, 128, ""COL_ORANGE"u¿ywa narzêdzi");
			}
			case 14:
			{
				format(status, 128, ""COL_ORANGE"koduje pojazd");
			}
			default:
			{
				format(status, 128, ""COL_ORANGE"tryb kombinacji");
			}
		}
	}
	return status;
}
