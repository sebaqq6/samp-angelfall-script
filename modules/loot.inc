#define MAX_WORLD_ITEMS 2000
#define DISTANCE 4.0

enum ItemEnum
{
	bool:Drop,
	ItemID,
	Item,
	Value,
	ObjectGameID,
	Text3D:Label,
	Float:X,
	Float:Y,
	Float:Z,
	icdn,
	icdn_max,
	i_vw,
	i_time_protect
};

new Przedmiot[MAX_WORLD_ITEMS][ItemEnum];

stock CreateItemForWorld(item, value, pcdn, pcdn_max, Float:itemX, Float:itemY, Float:itemZ, vw, protect_time = 10*60)
{
	if(CountItemsInWorld() >= MAX_WORLD_ITEMS-5) return 0;
	if(0 < item && item <= MAX_ITEMS - 1)
	{
		if(0 < value && value <= 999999)
		{
			for(new i = 0; i < MAX_WORLD_ITEMS; i++)
			{
				if(Przedmiot[i][Drop] == false)
				{
					new str[128];
					format(str,sizeof(str),"{8b8b8b}%s "COL_WHITE"(%d)\n%s",ItemName[item], value, eq_cdn_bar(procent(pcdn, pcdn_max)));
					Przedmiot[i][Drop]         = true;
					Przedmiot[i][icdn] 		   = pcdn;
					Przedmiot[i][icdn_max] 	   = pcdn_max;
					Przedmiot[i][ItemID]       = i;
					Przedmiot[i][Item]         = item;
					Przedmiot[i][Value]        = value;
					Przedmiot[i][ObjectGameID] = CreateDynamicObject(ObjectItem[item],itemX,itemY,itemZ-ObjectItemFloat[item][0],ObjectItemFloat[item][1],ObjectItemFloat[item][2],ObjectItemFloat[item][3], vw);
					Przedmiot[i][Label]        = CreateDynamic3DTextLabel(str,-1,itemX,itemY,itemZ-ObjectItemFloat[item][0], DISTANCE, _, _, _, vw);
					Przedmiot[i][X]            = itemX;
					Przedmiot[i][Y]            = itemY;
					Przedmiot[i][Z]            = itemZ-ObjectItemFloat[item][0];
					Przedmiot[i][i_vw]  =  vw;
					Przedmiot[i][i_time_protect] = serwer[time_timestamp]+protect_time;
					break;
				}
			}
		}
	}
	return 1;
}

stock RemoveItemFromWorld(scriptItemID)
{
	if(Przedmiot[scriptItemID][Drop] == true)
	{
		DestroyDynamicObject(Przedmiot[scriptItemID][ObjectGameID]);
		DestroyDynamic3DTextLabel(Przedmiot[scriptItemID][Label]);
		for(new ItemEnum:r; r < ItemEnum; r++)//czyszczenie zmiennych
		{
			Przedmiot[scriptItemID][r] = 0;
		}
		return 1;
	}
	return 0;
}

stock CountItemsInWorld()
{
	static wynik;
	wynik = 0;
	for(new i = 0; i < MAX_WORLD_ITEMS; i++)
	{
		if(Przedmiot[i][Drop])
		{
			wynik++;
		}
	}
	return wynik;
}

stock ClearItemsForWorld()
{
	for(new i = 0; i < MAX_WORLD_ITEMS; i++)
	{
		if(Przedmiot[i][Drop])
		{
			if(Przedmiot[i][i_time_protect] < serwer[time_timestamp])
			{
				RemoveItemFromWorld(i);
			}
		}
	}
	return 1;
}

stock PickItemForPlayer(playerid, first_time = 1)
{
	if(gracz[playerid][BWTime]) return MessageGUI(playerid,"Informacja","Jesteś ciężko ranny - nie możesz podnosić przedmiotów.","OK","");
	if(InCombineMode(playerid)) return MessageGUI(playerid,"Informacja","Jesteś w trybie kombinacji - nie możesz podnosić przedmiotów.","OK","");
	if(IsPlayerInAnyVehicle(playerid)) return MessageGUI(playerid,"Informacja","Znajdując się w pojeździe nie posiadasz możliwości podnoszenia przedmiotu!","OK","");
	new str[2000];
	new detected_items;
	format(str,sizeof(str),"UID\tNazwa\tIlość\tKondycja", str);
	for(new i = 0; i < MAX_WORLD_ITEMS; i++)
	{
		if(Przedmiot[i][i_vw] != GetPlayerVirtualWorld(playerid)) continue;
		if(InRange(playerid,DISTANCE,Przedmiot[i][X],Przedmiot[i][Y],Przedmiot[i][Z]))
		{
			detected_items++;
			format(str,sizeof(str),"%s\n"COL_BLACK"%d\t"COL_GREY"%s\t"COL_DBLUE"%d\t%s",str, i, ItemName[Przedmiot[i][Item]], Przedmiot[i][Value], eq_cdn_bar(procent(Przedmiot[i][icdn], Przedmiot[i][icdn_max])));
		}
	}
	if(detected_items > 0)
	{
		Dialog_Show(playerid, LOOT, DIALOG_STYLE_TABLIST_HEADERS,"Lista przedmiotów znajdujących się wokół ciebie:", str,"Podnieś","Anuluj");
	}
	else if(first_time)
	{
		MessageGUI(playerid,"Informacja","Wokół Ciebie nie znajduje się żaden przedmiot.","OK","");
	}
	return 1;
}

Dialog:LOOT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new w_uid = strval(inputtext);
	if(!Przedmiot[w_uid][Drop]) return MessageGUI(playerid,"Informacja","Ktoś inny podniósł ten przedmiot.","OK","");
	if(CreateItemForPlayer(playerid,Przedmiot[w_uid][Item],Przedmiot[w_uid][Value], Przedmiot[w_uid][icdn], Przedmiot[w_uid][icdn_max]))
	{
		mq_format("INSERT INTO `loot_history` (`userid`, `itemid`, `value`) VALUES ('%d', '%d', '%d');", gracz[playerid][UID], Przedmiot[w_uid][Item], Przedmiot[w_uid][Value]);
		mq_send("QLootHistory");
		RemoveItemFromWorld(w_uid);
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
		PickItemForPlayer(playerid, 0);

	}
	return 1 ;
}
//SYSTEM ROZRZUTU PRZEDMIOTÓW NA MAPIE
forward Process_ReLootMap(action);
public Process_ReLootMap(action)
{
	switch(action)
	{
		case 0:
		{
			if(serwer[time_relootmap] < serwer[time_timestamp])
			{
				serwer[time_relootmap] = serwer[time_timestamp]+60*60;//godzina
				SetTimerEx("Process_ReLootMap", 1000*30, false, "d", 1);
				SendClientMessageToAll(-1, ""COL_RED"(({510009}Za 30 sekund nastąpi respawn przedmiotów..."COL_RED"))");
			}
		}
		case 1:
		{
			ClearItemsForWorld();
			mq_format("SELECT * FROM `loots`;");
			mq_send("StartLootSystem");
		}
	}
	return 1;
}


forward StartLootSystem();
public StartLootSystem()
{
	mq_getdata();
	new count_created;
	if(rekordy)
	{
		printf("[LOOT]Wykryto %d miejsc lootu!", rekordy);
		new i;
		new Float:pos[3];
		new TYP;
		new rand_procent;
		new Float:rand_pos[2];
		static last_rand;
		new pula;
		pula = (sizeof(ItemProbably))-1;
		new different_start;
		new bool:fuck_logic;
		for(new d; d < pula; d++)
		{
			if(ItemProbably[d][0] == -1)
			{
				different_start = d;
				break;
			}
		}
		for(new r; r < MAX_ITEMS; r++)
		{
			ItemCountOnMap[r] = 0;
		}
		while(i < rekordy)
		{
			pos[0] = cache_get_field_content_float(i, "X");
			pos[1] = cache_get_field_content_float(i, "Y");
			pos[2] = cache_get_field_content_float(i, "Z");
			TYP = cache_get_field_content_int(i, "TYP");
			for(new x; x < 3; x++)
			{
				if(fuck_logic)
				{
					rand_procent = MRandRange(0, different_start);
					if(rand_procent == last_rand) rand_procent = MRandRange(0, different_start);
					fuck_logic = false;
				}
				else
				{
					rand_procent = MRandRange(different_start, pula);
					if(rand_procent == last_rand) rand_procent = MRandRange(different_start, pula);
					fuck_logic = true;
				}
				if(rand_procent == different_start) rand_procent++;
				last_rand = rand_procent;
				MRandFloatRange(0.000, 1.200, rand_pos[0]);
				MRandFloatRange(0.000, 1.200, rand_pos[1]);
				switch(MRandRange(1, 4))
				{
					case 1:
					{
						pos[0] += rand_pos[0];
						pos[1] += rand_pos[1];
					}
					case 2:
					{
						pos[0] -= rand_pos[0];
						pos[1] += rand_pos[1];
					}
					case 3:
					{
						pos[0] += rand_pos[0];
						pos[1] -= rand_pos[1];
					}
					case 4:
					{
						pos[0] -= rand_pos[0];
						pos[1] -= rand_pos[1];
					}
				}
				if(TYP == 0)//normal
				{
					if(ItemProbably[rand_procent][2] > ItemCountOnMap[ItemProbably[rand_procent][0]] || ItemProbably[rand_procent][2] == 0)
					{
						ItemCountOnMap[ItemProbably[rand_procent][0]]++;
						count_created++;
						if(ItemProbably[rand_procent][0] >= 22 && ItemProbably[rand_procent][0] <= 46) CreateItemForWorld(ItemProbably[rand_procent][0], MRandRange(1, ItemProbably[rand_procent][1]), MRandRange(10, 30), 1000, pos[0], pos[1], pos[2], 0, 0);
						else CreateItemForWorld(ItemProbably[rand_procent][0], MRandRange(1, ItemProbably[rand_procent][1]), 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					}
				}
				else if(TYP == 1)//roślina - pod wodą
				{
					count_created++;
					static plant_underwater;
					if(plant_underwater == 0) plant_underwater = 128;
					else if(plant_underwater == 128) plant_underwater = 129;
					else if(plant_underwater == 129) plant_underwater = 128;
					CreateItemForWorld(plant_underwater, 1, 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					break;
				}
				else if(TYP == 2)//roślina - góry
				{
					count_created++;
					CreateItemForWorld(131, 1, 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					break;
				}
				else if(TYP == 3)//roślina - piasek
				{
					count_created++;
					CreateItemForWorld(126, 1, 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					break;
				}
				else if(TYP == 4)//roślina - woda
				{
					count_created++;
					CreateItemForWorld(132, 1, 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					break;
				}
				else if(TYP == 5)//roślina - bagna
				{
					count_created++;
					CreateItemForWorld(124, 1, 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					break;
				}
				else if(TYP == 6)//roślina - las
				{
					static plant_forest;
					if(plant_forest == 0) plant_forest = 127;
					else if(plant_forest == 127) plant_forest = 125;
					else if(plant_forest == 125) plant_forest = 123;
					else if(plant_forest == 123) plant_forest = 130;
					else if(plant_forest == 130) plant_forest = 127;
					count_created++;
					CreateItemForWorld(plant_forest, 1, 2000, 2000, pos[0], pos[1], pos[2], 0, 0);
					break;
				}
			}
			i++;
		}
	}
	SendClientMessageToAllEx(-1, ""COL_RED"(({510009}Stworzono "COL_WHITE"%d{510009} przedmiotów na mapie. Kolejny respawn za godzinę."COL_RED"))", count_created);
	printf("[LOOT]Stworzono %d przedmiotów na mapie!", count_created);
	return 1;
}
