stock CreateCampfire(playerid)
{
	if(ognisko[playerid][o_status]) return 0;
	ognisko[playerid][o_X] = gracz[playerid][PosX];
	ognisko[playerid][o_Y] = gracz[playerid][PosY];
	ognisko[playerid][o_Z] = gracz[playerid][PosZ];
	ognisko[playerid][o_object][0] = CreateObject(841, ognisko[playerid][o_X], ognisko[playerid][o_Y], ognisko[playerid][o_Z]-1, 0.000, 0.000, 0.0);
	ognisko[playerid][o_object][1] = CreateObject(841, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ognisko[playerid][o_object][2] = CreateObject(841, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ognisko[playerid][o_object][3] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ognisko[playerid][o_object][4] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ognisko[playerid][o_object][5] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ognisko[playerid][o_object][6] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ognisko[playerid][o_object][7] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	AttachObjectToObject(ognisko[playerid][o_object][1], ognisko[playerid][o_object][0], 0, -0.5, 0, 0, 0, 0, 1);
	AttachObjectToObject(ognisko[playerid][o_object][2], ognisko[playerid][o_object][0], 0, -0.5, 0, 0, 0, 90, 1);
	ognisko[playerid][o_status] = 320;
	format(temp_string, 512, " "COL_EASY"["COL_RED"Ognisko"COL_EASY"]\n"COL_EASY"["COL_LIME"Status: %s"COL_EASY"] ", StatusCampfire(playerid));
	ognisko[playerid][o_label] = CreateDynamic3DTextLabel(temp_string, -1, ognisko[playerid][o_X], ognisko[playerid][o_Y], ognisko[playerid][o_Z], 5.0);
	return 1;
}

stock Process_Campfire(playerid)
{
	if(!ognisko[playerid][o_status]) return 1;
	ognisko[playerid][o_status]--;
	if(ognisko[playerid][o_status] > 299)
	{
		if(!InRange(playerid, 5.0, ognisko[playerid][o_X], ognisko[playerid][o_Y], ognisko[playerid][o_Z]))
		{
			LeftNotifyShow(playerid, "error", "Oddaliles sie od ~y~ogniska~w~ Rozpalanie zostalo ~r~przerwane~w~.");
			ognisko[playerid][o_status] = 0;
		}
	}
	else if(ognisko[playerid][o_status] == 299)
	{
		AttachObjectToObject(ognisko[playerid][o_object][3], ognisko[playerid][o_object][0], 0.5, -0.5, -2, 0, 0, 0, 1);
		AttachObjectToObject(ognisko[playerid][o_object][4], ognisko[playerid][o_object][0], -0.5, -0.5, -2, 0, 0, 0, 1);
		AttachObjectToObject(ognisko[playerid][o_object][5], ognisko[playerid][o_object][0], 0, -0.5, -2, 0, 0, 0, 1);
		AttachObjectToObject(ognisko[playerid][o_object][6], ognisko[playerid][o_object][0], 0, -0.5, -2, 0, 0, 0, 1);
		AttachObjectToObject(ognisko[playerid][o_object][7], ognisko[playerid][o_object][0], 0, -0.5, -2, 0, 0, 0, 1);
	}
	format(temp_string, 512, " "COL_EASY"["COL_RED"Ognisko"COL_EASY"]\n"COL_EASY"["COL_LIME"Status: %s"COL_EASY"] ", StatusCampfire(playerid));
	UpdateDynamic3DTextLabelText(ognisko[playerid][o_label], -1, temp_string);
	if(!ognisko[playerid][o_status])
	{
		DestroyObject(ognisko[playerid][o_object][0]);
		DestroyObject(ognisko[playerid][o_object][1]);
		DestroyObject(ognisko[playerid][o_object][2]);
		DestroyObject(ognisko[playerid][o_object][3]);
		DestroyObject(ognisko[playerid][o_object][4]);
		DestroyObject(ognisko[playerid][o_object][5]);
		DestroyObject(ognisko[playerid][o_object][6]);
		DestroyObject(ognisko[playerid][o_object][7]);
		DestroyDynamic3DTextLabel(ognisko[playerid][o_label]);
		for(new ognisko_info:r; r < ognisko_info; r++) //czyszczenie zmiennych
		{
			ognisko[playerid][r] = 0;
		}
	}
	return 1;
}

stock StatusCampfire(playerid)
{
	new wynik[64];
	switch(ognisko[playerid][o_status])
	{
		case 1..299: format(wynik, 64, ""COL_ORANGE"Wypalanie "COL_WHITE"(Pozostało %ds)", ognisko[playerid][o_status]);
		case 300..320: format(wynik, 64, ""COL_GREEN"Rozpalanie "COL_WHITE"(Pozostało %ds)", ognisko[playerid][o_status]-300);
	}
	return wynik;
}

stock InRangeOfMyCampfire(playerid)
{
	if(ognisko[playerid][o_status] <= 299 && ognisko[playerid][o_status])
	{
		if(InRange(playerid, 5.0, ognisko[playerid][o_X], ognisko[playerid][o_Y], ognisko[playerid][o_Z])) return 1;
	}
	return 0;
}

stock InRangeOfAnyCampfire(playerid, &owner)
{
	for(new p = GetPlayerPoolSize(); p != -1; p--)
	{
		if(ognisko[p][o_status] <= 299 && ognisko[p][o_status])
		{
			if(InRange(playerid, 5.0, ognisko[p][o_X], ognisko[p][o_Y], ognisko[p][o_Z])) 
			{
				owner = p;
				return 1;
			}
		}
	}
	return 0;
} 