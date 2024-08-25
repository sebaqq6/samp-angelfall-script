/*
minimum 3 osoby do przejmowania terenu danej grupy
gdy obca grupa znajdzie sie w tej samej iloœci jest pauzowane przejmowanie
przejmowanie trwa przez 30 minut (tyle musi znajdowaæ sie grupa na danym terenie)
*/


#define MAX_ZONES 20

enum strefa_info
{
	//db
	st_id,
	st_typ,
	st_owner,
	Float:st_minx,
	Float:st_miny,
	Float:st_maxx,
	Float:st_maxy,
	st_name[64],
	//local
	st_areaid,
	st_gzid,
	//przejmowanie
	st_groupid,
	st_gpeople,
	st_taketime
};


new strefa[MAX_ZONES][strefa_info];


stock Init_Zones()
{
	mq_format("SELECT * FROM `strefy`;");
	mq_send("LoadZonesFromDB");
	return 1;
}

forward LoadZonesFromDB();
public LoadZonesFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new fid; 
		while(i < rekordy)
		{
			fid = GetFreeZoneID();
			strefa[fid][st_id] = cache_get_field_content_int(i, "id");
			strefa[fid][st_typ] = cache_get_field_content_int(i, "typ");
			strefa[fid][st_owner] = cache_get_field_content_int(i, "owner");
			strefa[fid][st_minx] = cache_get_field_content_int(i, "minx");
			strefa[fid][st_miny] = cache_get_field_content_int(i, "miny");
			strefa[fid][st_maxx] = cache_get_field_content_int(i, "maxx");
			strefa[fid][st_maxy] = cache_get_field_content_int(i, "maxy");
			cache_get_field_content(i, "name", strefa[fid][st_name], MySQL, 64);

			strefa[fid][st_areaid] = CreateDynamicCuboid(strefa[fid][st_minx], strefa[fid][st_miny], -100.0, strefa[fid][st_maxx], strefa[fid][st_maxy], 1400.0);
			if(strefa[fid][st_typ]) strefa[fid][st_gzid] = GangZoneCreate(strefa[fid][st_minx], strefa[fid][st_miny], strefa[fid][st_maxx], strefa[fid][st_maxy]);
			
			i++;
		}
		printf("[LOAD]Zaladowano %d stref.", i);
	}
	return 1;
}

stock GetFreeZoneID()
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(!strefa[s][st_id]) return s;
	}
	return 0;
}

stock ShowZones(playerid)
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(strefa[s][st_id])
		{
			switch(strefa[s][st_typ])
			{
				case 1: GangZoneShowForPlayer(playerid, strefa[s][st_gzid], 0xFF0000AA);//red zone pvp on
				case 2: GangZoneShowForPlayer(playerid, strefa[s][st_gzid], 0x0000FFAA);//Strefa do przejmowania przez grupy
			}
		}
	}
	return 1;
}

stock GetPlayerZoneType(playerid)
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(!strefa[s][st_id]) continue;
		if(IsPlayerInDynamicArea(playerid, strefa[s][st_areaid])) return strefa[s][st_typ];
	}
	return -1;
}


public OnPlayerEnterDynamicArea(playerid, areaid)
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(!strefa[s][st_id]) continue;
		if(strefa[s][st_areaid] == areaid)
		{
			SendClientMessageEx(playerid, 0xFF0000FF, "(({AA0000}Wszedles/as do strefy: {FFFFFF}%s{AA0000}.{FF0000}))", strefa[s][st_name]);
			switch(strefa[s][st_typ])
			{
				case 1:
				{
					LeftNotifyShow(playerid, "Uwaga!", "Wszedles/as do ~r~czerwonej strefy~w~! Strzelaniny na tym terenie sa na porzadku dziennym. Kazdy gracz moze Cie tutaj ~r~postrzelic~w~, ~r~okrasc~w~ bez koniecznosci odgrywania ~p~/me~w~ i ~p~/do~w~.", LN_RED, 20) ;
				}
				case 2:
				{
					LeftNotifyShow(playerid, "Uwaga!", "Wszedles/as do ~b~niebieskiej strefy~w~! Wszelkie strzelaniny oraz okradanie na tej strefie ~r~musza zostac odegrane~w~ za pomoca komend ~p~/me ~w~i ~p~/do~w~.", LN_RED, 20) ;
				}
			}
		}
	}
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(!strefa[s][st_id]) continue;
		if(strefa[s][st_areaid] == areaid)
		{
			SendClientMessageEx(playerid, 0xFF0000FF, "(({00AA00}Opusciles/as strefe: {FFFFFF}%s{00AA00}.{FF0000}))", strefa[s][st_name]);
			switch(strefa[s][st_typ])
			{
				case 1:
				{
					LeftNotifyShow(playerid, "info", "Opusciles/as ~r~czerwona strefe~w~! Od teraz wszelkie konfrontacje sa skryptowo ~r~zablokowane~w~.", LN_GREEN, 15) ;
				}
				case 2:
				{
					LeftNotifyShow(playerid, "info", "Opusciles/as ~b~niebieska strefe~w~! Od teraz wszelkie konfrontacje sa skryptowo ~r~zablokowane~w~.", LN_GREEN, 15) ;
				}
			}
		}
	}
	return 1;
}


stock Process_TakeZone()
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(strefa[s][st_typ] != 2) continue;
		for(new g = PlayerPoolSize(); g != -1; g--)
		{
			if(!gracz[g][OrgID]) continue;
			if(IsPlayerInDynamicArea(g, strefa[s][st_areaid]))
			{
				if(!strefa[s][st_groupid])
				{
					strefa[s][st_groupid] = gracz[g][OrgID];
					strefa[s][st_gpeople] = 1;
				}
				else if(strefa[s][st_groupid] == gracz[g][OrgID] && strefa[s][st_gpeople] == 1)
				{
					strefa[s][st_gpeople]++;
				}
				else if(strefa[s][st_groupid] == gracz[g][OrgID] && strefa[s][st_gpeople] >= 3)
				{
					strefa[s][st_taketime]++;
				}
				else
				{
					strefa[s][st_taketime] = 0;
					strefa[s][st_groupid] = 0;
					strefa[s][st_gpeople] = 0;
				}
			}
		}
	}
	return 1;
}

/*







stock Process_TakeZone()
{
	mq_format("SELECT `j`.`sid`,`j`.`gid`, \
	COUNT(*) AS `count`, \
	GROUP_CONCAT(`j`.`uid` SEPARATOR ' ') AS `uids` \
	FROM ( \
	SELECT `k`.`id` AS `uid`,`k`.`Nick`,`k`.`PosX`,`k`.`PosY`,`k`.`LastOnline`, \
	`s`.`id` AS `sid`,`s`.`typ`,`s`.`owner`,`s`.`name`, \
	`g`.`id` AS `gid` \
	FROM `Konta` AS `k` \
	INNER JOIN `strefy` AS `s` \
	ON `k`.`PosX`>=`s`.`minx` \
	AND `k`.`PosX`<=`s`.`maxx` \
	AND `k`.`PosY`>=`s`.`miny` \
	AND `k`.`PosY`<=`s`.`maxy` \
	AND `s`.`typ`='2' \
	INNER JOIN `Grupy` AS `g` \
	ON `k`.`OrgID` = `g`.`id` \
	) AS `j` \
	GROUP BY `j`.`sid`,`j`.`gid`;");
	mq_send("AskDBForZoneData");
	return 1;
}

forward AskDBForZoneData();
public AskDBForZoneData()
{
	mq_getdata();
	if(rekordy)
	{
		new i;

		new sid, siddb, gid, count, uids[64];
		while(i < rekordy)
		{
			siddb = cache_get_field_content_int(i, "sid");
			gid = cache_get_field_content_int(i, "gid");
			count = cache_get_field_content_int(i, "count");
			cache_get_field_content(i, "uids", uids, 64);
			sid = ZoneDBIdToSid(siddb);

			if(count < 3) //niespelnione warunki przejmowania
			{
				for(new s; s < MAX_ZONES; s++)
				{
					if(strefa[s][przejmowanie]==gid) //grupa byla w trakcie przejmowania, ale prawdopodobnie ktos zginal i juz nie spelnia tych warunkow, wiec przerywamy imprezê
					{
						if(strefa[s][przejmowanie_time]>5*60) //wlasciciele zostali powiadomieni, wiec trzeba odwolac alarm
						{
							//scm, jupi, we fucked them in the ass
						}
						strefa[s][przejmowanie]=0;
						strefa[s][przejmowanie_time]=0;
					}
				}
				continue;
			}
			if(strefa[sid][przejmowanie]) //strefa jest przez kogos przejmowana
			{
				if(strefa[sid][przejmowanie]!= gid)//strefa jest przejmowana przez inna grupê
				{
					if(strefa[sid][st_owner]== gid)//grupa ktora znajduje sie w strefie to wlasciciele
					{
					
					}
					else //grupa ktora znajduje sie w strefie nie jest wlascicielem, i nie moze rozpoczac przejmowania, bo juz ktos to robi
					{
						//scm, inna grupa juz przejmuje ta strefe, sprobuj pozniej lub wymorduj ich
					}
				}
				else //strefa przejmowana przez aktualna grupe w pêtli, podbijamy czas itp
				{
					strefa[sid][przejmowanie_time]+=60;
					if(strefa[sid][przejmowanie_time]>30*60)
					{
						//strefa przejeta
					}
				}
			}
			else //strefa nie jest przez nikogo przejmowana
			{
				if(strefa[sid][st_owner]!=gid) //grupa nie jest wlascicielem, wiec moze rozpoczac przejmowanie
				{
					strefa[sid][przejmowanie]=gid;
					strefa[sid][przejmowanie_time]=0;
				}
			}
			
			i++;
		}
	}
	return 1;
}

ZoneDBIdToSid(dbid)
{
	for(new s; s < MAX_ZONES; s++)
	{
		if(strefa[s][st_id] == dbid)
			return strefa[s][st_id];
	}
	return -1;
}
*/