stock Init_Objects()
{
	new custom_object;
	//flint conuty - usunięcie pól
	custom_object = CreateDynamicObject(17122, -211.95309, -1543.38281, 4.4920, 0.00000, 0.00000, 0.00000, _, _, _, 700.0, 700.0);
	SetDynamicObjectMaterial(custom_object, 0, 17122, "cuntwlandse", "grasstype4");
	custom_object = CreateDynamicObject(17119, -226.96091, -1253.90625, 7.95920, 0.00000, 0.00000, 0.00000, _, _, _, 700.0, 700.0);
	SetDynamicObjectMaterial(custom_object, 0, 17119, "cuntwlandse", "grasstype4");
	custom_object = CreateDynamicObject(17123, -511.45309, -1312.02344, 24.06780, 0.00000, 0.00000, 0.00000, _, _, _, 700.0, 700.0);
	SetDynamicObjectMaterial(custom_object, 0, 17123, "cuntwlandse", "grasstype4");
	LoadObjectsFromDB();
	return 1;
}
//Funkcja odpowiedzialna za tworzenie obiektów
stock Object(mmm, Float:koX, Float:koY, Float:koZ, Float:korX, Float:korY, Float:korZ, oworldid = 0, ointeriorid = 0)
{
	static render_value = 300;
	static priority = 0;
	//CreateDynamicObject(omodelid, oX, oY, oZ, orX, orY, orZ, -1, -1, -1, 300, 300, -1, 0);
	if(mmm == 4058 || mmm == 19545 || mmm == 19543)//grunty w miasteczku
	{
		render_value = 600;
		priority = 1;
	}
	else if(mmm == 11442 || mmm == 11458 || mmm == 3866 || mmm == 13367 || mmm == 3887 || mmm == 11088 || mmm == 19486 || mmm == 11428 || mmm == 11011)//budynki w miasteczku
	{
		render_value = 300;
		priority = 1;
	}
	else if(mmm == 874 || mmm == 852)//trawa i gruzy
	{
		render_value = 130;
	}
	else if(mmm == 790 || mmm == 791 || mmm == 734)//drzewa
	{
		priority = 2;
		render_value = 370;
		//printf("CreateObject(%d, %f, %f, %f, %f, %f, %f);", mmm, koX, koY, koZ, korX, korY, korZ);
	}
	else if(mmm == 10795 || mmm == 10794 || mmm == 9587  || mmm == 9586 || mmm == 9585 || mmm == 9584 || mmm == 3571)//statki i kontenery
	{
		priority = 1;
		render_value = 500;
	}
	else if(mmm == 19340 || mmm == 3574 || mmm == 3620 || mmm == 3624)//port przy miasteczku
	{
		priority = 2;
		render_value = 400;
	}
	else if(mmm == 19843)//blachy krypty
	{
		render_value = 100;
	}
	else if(mmm == 5291 || mmm == 13591 || mmm == 18248 || mmm == 4571 || mmm == 19486)//złomowisko
	{
		priority = 1;
		render_value = 450;
	}
	else if(mmm == 3594)//wraki
	{
		priority = 1;
		render_value = 500;
	}
	else if(mmm == 3244)//słupy
	{
		priority = 1;
		render_value = 500;
	}
	else if(mmm == 12847 || mmm == 7269)//baza załadunkowa, flint county
	{
		priority = 1;
		render_value = 500;
	}
	else if(mmm == 6928 || mmm == 10843 || mmm == 3502)//elektrownia flint county
	{
		priority = 1;
		render_value = 500;
	}
	else if(mmm == 3279)//wojskowe wieżyczki
	{
		priority = 1;
		render_value = 500;
	}
	else if(koZ > 1400.0)
	{
		priority = 0;
		render_value = 500;
	}
	/*if(GetDistanceBetweenPoints(koX, koY, koZ, -2466.6572,-2493.2800,2309.2158) < 50.0)//wyciągacz obiektów
	{
		if(mmm == 2629 || mmm == 2913 || mmm == 2631 || mmm == 3071 || mmm == 3072 || mmm == 2630 || mmm == 2627)
		{
			printf("CreateObject(%d, %f, %f, %f, %f, %f, %f);", mmm, koX, koY, koZ, korX, korY, korZ);
		}
	}*/
	oworldid = -1;
	ointeriorid = -1;
	if(koZ < 1000.0) CA_CreateObject(mmm, koX, koY, koZ, korX, korY, korZ);
	return CreateDynamicObject(mmm, koX, koY, koZ, korX, korY, korZ, oworldid, ointeriorid, -1, render_value, render_value, -1, priority);
}
//*********************************************************************************************************SYSTEM DYNAMICZNYCH OBIEKTÓW
//CALLBACK ODPOWIEDZIALNY ZA EDYCJE
public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new uid = PlayerEditObject[playerid];
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	//Aktualizowanie zmiennych
	if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	{
		// Przypisywanie pozycji obiektu
		if(PlayerEditObject[playerid])
		{
			if(gracz[playerid][MapperLvl] == 1 && IsPlayerInBaseArea(playerid) && IsPointInBaseArea(playerid, x, y, z) && ObjectInfo[uid][oGrupa] == gracz[playerid][OrgID])
			{
				// Przenieś obiekt na pozycję
				SetDynamicObjectPos(objectid, x, y, z);
				SetDynamicObjectRot(objectid, rx, ry, rz);
				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = x;
				ObjectInfo[uid][oY] = y;
				ObjectInfo[uid][oZ] = z;
				ObjectInfo[uid][oRX] = rx;
				ObjectInfo[uid][oRY] = ry;
				ObjectInfo[uid][oRZ] = rz;
				// Zapisywanie obiektu
				SaveObject(uid);
				// Zakończ edycję obiektu
				PlayerEditObject[playerid] = 0;
				// Wyślij informację dla gracza
				LeftNotifyShow(playerid, "Sukces!", "Obiekt zostal ~g~zapisany~w~.", LN_GREEN);
			}
			else if(gracz[playerid][MapperLvl] == 2 && ObjectInfo[uid][oOwner] == GetPlayerUID(playerid))
			{
				// Przenieś obiekt na pozycję
				SetDynamicObjectPos(objectid, x, y, z);
				SetDynamicObjectRot(objectid, rx, ry, rz);
				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = x;
				ObjectInfo[uid][oY] = y;
				ObjectInfo[uid][oZ] = z;
				ObjectInfo[uid][oRX] = rx;
				ObjectInfo[uid][oRY] = ry;
				ObjectInfo[uid][oRZ] = rz;
				// Zapisywanie obiektu
				SaveObject(uid);
				// Zakończ edycję obiektu
				PlayerEditObject[playerid] = 0;
				// Wyślij informację dla gracza
				LeftNotifyShow(playerid, "Sukces!", "Obiekt zostal ~g~zapisany~w~.", LN_GREEN);
			}
			else if(gracz[playerid][MapperLvl] == 3)
			{
				// Przenieś obiekt na pozycję
				SetDynamicObjectPos(objectid, x, y, z);
				SetDynamicObjectRot(objectid, rx, ry, rz);
				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = x;
				ObjectInfo[uid][oY] = y;
				ObjectInfo[uid][oZ] = z;
				ObjectInfo[uid][oRX] = rx;
				ObjectInfo[uid][oRY] = ry;
				ObjectInfo[uid][oRZ] = rz;
				// Zapisywanie obiektu
				SaveObject(uid);
				// Zakończ edycję obiektu
				PlayerEditObject[playerid] = 0;
				// Wyślij informację dla gracza
				LeftNotifyShow(playerid, "Sukces!", "Obiekt zostal ~g~zapisany~w~.", LN_GREEN);
			}
			else
			{
				DeleteObject(uid);
				Error(playerid, "Możesz budować tylko na terenie bazy.");
				PlayerEditObject[playerid] = 0;
			}
		}
	}
	return 1;
}
public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	new searchid = GetObjectIndex(objectid);
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!searchid) return Error(playerid, "Tego obiektu nie da się edytować.");
	if(ObjectInfo[searchid][oBlock] == 1) return Error(playerid, "Ten obiekt jest zablokowany. Nie możesz go edytować.");
	if(gracz[playerid][MapperLvl] == 1 && IsPlayerInBaseArea(playerid) && IsPointInBaseArea(playerid, x, y, z) && ObjectInfo[searchid][oGrupa] == gracz[playerid][OrgID])
	{
		PlayerEditObject[playerid] = searchid;
		EditDynamicObject(playerid, objectid);
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | Grupa UID: %d"COL_RED"))", GetPlayerForumName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], ObjectInfo[searchid][oGrupa]);
	}
	else if(gracz[playerid][MapperLvl] == 2 && ObjectInfo[searchid][oOwner] == GetPlayerUID(playerid))
	{
		PlayerEditObject[playerid] = searchid;
		EditDynamicObject(playerid, objectid);
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | Grupa UID: %d"COL_RED"))", GetPlayerForumName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], ObjectInfo[searchid][oGrupa]);
	}
	else if(gracz[playerid][MapperLvl] == 3)
	{
		PlayerEditObject[playerid] = searchid;
		EditDynamicObject(playerid, objectid);
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | Grupa UID: %d"COL_RED"))", GetPlayerForumName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], ObjectInfo[searchid][oGrupa]);
	}
	else
	{
		PlayerEditObject[playerid] = 0;
		Error(playerid, "Brak uprawnień.");
	}
	return 1;
}
//ładowanie obiektów z bazy
stock LoadObjectsFromDB()
{
	mysql_pquery(MySQL, "SELECT * FROM `Obiekty`", "LoadObjectDataReceived","");
	return 1;
}
forward LoadObjectDataReceived();
public LoadObjectDataReceived()
{
	if(cache_get_row_count() > MAX_OBJECTS) printf("[ERROR][OBJECTS] Limit obiektow w gamemode jest zbyt maly.");
	new rows, fields;
	cache_get_data(rows, fields);
	new i;
	new File:handle = fopen("obiekty_backup.txt", io_write);
	new backup_str[512];
	if(rows)
	{
		while(i<cache_get_row_count())
		{
			new id = cache_get_field_content_int(i, "id", MySQL);
			ObjectInfo[id][oUID] = id;
			ObjectInfo[id][oModel]=cache_get_field_content_int(i, "model", MySQL);
			ObjectInfo[id][oGrupa]=cache_get_field_content_int(i, "idgrupa", MySQL);
			ObjectInfo[id][oOwner]=cache_get_field_content_int(i, "uid", MySQL);
			ObjectInfo[id][oVW]=cache_get_field_content_int(i, "World", MySQL);
			ObjectInfo[id][oInt]=cache_get_field_content_int(i, "InteriorEx", MySQL);
			ObjectInfo[id][oX]=cache_get_field_content_float(i, "x", MySQL);
			ObjectInfo[id][oY]=cache_get_field_content_float(i, "y", MySQL);
			ObjectInfo[id][oZ]=cache_get_field_content_float(i, "z", MySQL);
			ObjectInfo[id][oRX]=cache_get_field_content_float(i, "rx", MySQL);
			ObjectInfo[id][oRY]=cache_get_field_content_float(i, "ry", MySQL);
			ObjectInfo[id][oRZ]=cache_get_field_content_float(i, "rz", MySQL);
			ObjectInfo[id][oMMAT]=cache_get_field_content_int(i, "mmat", MySQL);
			ObjectInfo[id][oBlock]=cache_get_field_content_int(i, "block", MySQL);

			ObjectInfo[id][oObject] = Object(ObjectInfo[id][oModel], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oVW], ObjectInfo[id][oInt]);
			if(GetDistanceBetweenPoints(ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], 2706.9819,-1802.2231,422.8280) < 400.0)
			{
			ObjectInfo[id][oMMAT] = 0;
			ObjectInfo[id][oVW]= 5000;
			ObjectInfo[id][oInt]= 10;
			//format(backup_str, 512, "%d|%d|%d|%d|%d|%d|%f|%f|%f|%f|%f|%f|%d\r\n", ObjectInfo[id][oUID], ObjectInfo[id][oModel], ObjectInfo[id][oGrupa], ObjectInfo[id][oOwner], ObjectInfo[id][oVW], ObjectInfo[id][oInt], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oMMAT]);
			format(backup_str, 512, "INSERT INTO `Obiekty` (`model`, `idgrupa`, `uid`, `World`, `InteriorEx`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES ('%d', '%d', '%d', '%d', '%d', '%0.5f', '%0.5f', '%0.5f', '%0.5f', '%0.5f', '%0.5f');", ObjectInfo[id][oModel], ObjectInfo[id][oGrupa], ObjectInfo[id][oOwner], ObjectInfo[id][oVW], ObjectInfo[id][oInt], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ]);
			fwrite(handle, backup_str);
			}
			i++;
		}
	}
	fclose(handle);
	printf("[LOAD] Wczytano %d obiektów z bazy danych.", i);
	LoadTexture();
	return 1;
}
//Ładowanie tekstur z bazy danych
stock LoadTexture()
{
	mysql_tquery(MySQL, "SELECT * FROM `Obiekty_textury`","LoadTextureDataReceived","");
	return 1;
}
forward LoadTextureDataReceived();
public LoadTextureDataReceived()
{
	new rows, fields;
	cache_get_data(rows, fields);
	new i;
	if(rows)
	{
		while(i<cache_get_row_count())
		{
			new object, index, materialcolor, modelid, txdname[32], texturename[32];
			object=cache_get_field_content_int(i, "object", MySQL);
			index=cache_get_field_content_int(i, "index", MySQL);
			materialcolor=cache_get_field_content_int(i, "materialcolor", MySQL);
			modelid=cache_get_field_content_int(i, "modelid", MySQL);
			cache_get_field_content(i, "txdname", txdname);
			cache_get_field_content(i, "texturename", texturename);
			if(ObjectInfo[object][oUID] && ObjectInfo[object][oMMAT] == 1)
			{
				SetDynamicObjectMaterial(ObjectInfo[object][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
			}
			i++;
		}
	}
	printf("[LOAD] Wczytano %d [material]tekstur z bazy danych.", i);
	LoadMaterialText();
	return 1;
}
//Ładowanie przerabiania obiektów na napisy...
stock LoadMaterialText()
{
	mysql_tquery(MySQL, "SELECT * FROM `Obiekty_text`","LoadMaterialTextDataReceived","");
	return 1;
}
forward LoadMaterialTextDataReceived();
public LoadMaterialTextDataReceived()
{
	new rows, fields;
	cache_get_data(rows, fields);
	new i;
	if(rows)
	{
		while(i<cache_get_row_count())
		{
			new object, index, matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];
			object=cache_get_field_content_int(i, "object", MySQL);
			index=cache_get_field_content_int(i, "index", MySQL);
			matsize=cache_get_field_content_int(i, "matsize", MySQL);
			fontsize=cache_get_field_content_int(i, "fontsize", MySQL);
			bold=cache_get_field_content_int(i, "bold", MySQL);
			fontcolor=cache_get_field_content_int(i, "color_font", MySQL);
			backcolor=cache_get_field_content_int(i, "color_back", MySQL);
			align=cache_get_field_content_int(i, "align", MySQL);
			cache_get_field_content(i, "fontface", fontface);
			cache_get_field_content(i, "text", text);
			if(ObjectInfo[object][oUID] && ObjectInfo[object][oMMAT] == 1)
			{
				new color_font = ShiftRGBAToABGR(fontcolor);
				new color_back = ShiftRGBAToABGR(backcolor);
				SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
			}
			i++;
		}
	}
	printf("[LOAD] Wczytano %d [text]tekstur z bazy danych.", i);
	printf("[OBJECTS]Wszystkich obiektow na serwerze jest: %d sztuk!", CountDynamicObjects());
	return 1;
}
stock EscapeMMAT(name[])
{
	for(new i = 0; name[i] != 0; i++)
	{
		if(name[i] == '|') name[i] = '\n';
	}
}
stock AddObject(model, idgrupa, uid, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Cache:result;
	mq_format("SELECT id FROM (SELECT 1 AS id) q1 WHERE NOT EXISTS (SELECT 1 FROM  Obiekty WHERE  id = 1) UNION ALL SELECT * FROM (SELECT  id + 1 FROM Obiekty t WHERE  NOT EXISTS (SELECT  1 FROM Obiekty ti WHERE ti.id = t.id +1) ORDER BY id LIMIT 1) q2 ORDER BY id LIMIT 1;");
	result = mysql_query(MySQL, mQuery);
	new id = cache_get_field_content_int(0, "id");
	cache_delete(result);
	mq_format("INSERT INTO `samp_prp`.`Obiekty` (`id`, `model`, `idgrupa`, `uid`, `World`, `InteriorEx`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f');", id, model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz);
	mysql_query(MySQL, mQuery, false);
	ObjectInfo[id][oUID] = id;
	ObjectInfo[id][oModel] = model;
	ObjectInfo[id][oX] = x;
	ObjectInfo[id][oY] = y;
	ObjectInfo[id][oZ] = z;
	ObjectInfo[id][oRX] = rx;
	ObjectInfo[id][oRY] = ry;
	ObjectInfo[id][oRZ] = rz;
	ObjectInfo[id][oInt] = InteriorEx;
	ObjectInfo[id][oVW] = World;
	ObjectInfo[id][oGrupa] = idgrupa;
	ObjectInfo[id][oOwner] = uid;
	ObjectInfo[id][oObject] = CreateDynamicObject(ObjectInfo[id][oModel], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oVW], ObjectInfo[id][oInt], -1, 400.0,400.0);
	return id;
}
stock SaveObject(id)
{
	new query[1024];
	mysql_format(MySQL,query, sizeof(query), "UPDATE `Obiekty` SET `model` = '%d', `x` = '%f', `y` = '%f', `z` = '%f', `rx` = '%f', `ry` = '%f', `rz` = '%f', `InteriorEx` = '%d', `World` = '%d', `idgrupa` = '%d', `uid` = '%d', `mmat` = '%d' WHERE `id` = '%d'",
	ObjectInfo[id][oModel],
	ObjectInfo[id][oX],
	ObjectInfo[id][oY],
	ObjectInfo[id][oZ],
	ObjectInfo[id][oRX],
	ObjectInfo[id][oRY],
	ObjectInfo[id][oRZ],
	ObjectInfo[id][oInt],
	ObjectInfo[id][oVW],
	ObjectInfo[id][oGrupa],
	ObjectInfo[id][oOwner],
	ObjectInfo[id][oMMAT],
	id);
	mysql_tquery(MySQL,query,"SendQuery","");
	return 1;
}
stock DeleteObject(id)
{
	new query[564];
	mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty` WHERE `id` = '%d'", id);
	mysql_tquery(MySQL,query,"SendQuery","");
	mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty_text` WHERE `object` = '%d'", id);
	mysql_tquery(MySQL,query,"SendQuery","");
	mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty_textury` WHERE `object` = '%d'", id);
	mysql_tquery(MySQL,query,"SendQuery","");
	ObjectInfo[id][oUID] = 0;
	ObjectInfo[id][oModel] = 0;
	ObjectInfo[id][oX] = 0;
	ObjectInfo[id][oY] = 0;
	ObjectInfo[id][oZ] = 0;
	ObjectInfo[id][oRX] = 0;
	ObjectInfo[id][oRY] = 0;
	ObjectInfo[id][oRZ] = 0;
	ObjectInfo[id][oInt] = 0;
	ObjectInfo[id][oVW] = 0;
	ObjectInfo[id][oGrupa] = 0;
	ObjectInfo[id][oOwner] = 0;
	ObjectInfo[id][oMMAT] = 0;
	DestroyDynamicObject(ObjectInfo[id][oObject]);
	return 1;
}
stock GetObjectID(uid)
{
	new list = 0;
	//ForeachEx(i, MAX_OBJECTS)
	for(new i; i < MAX_OBJECTS; i++)
	{
		if(ObjectInfo[i][oUID] == uid)
		{
			list = i;
			break;
		}
	}
	return list;
}
stock IsOwnerObject(playerid, objectid)
{
	new wynik;
	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oObject]) == objectid)
		{
			//wynik = 1;//debug value
			if(gracz[playerid][UID] == ObjectInfo[i][oOwner]) wynik = 1;
			//if(PlayerGang[playerid] == ObjectInfo[i][oGrupa]) wynik = 2;
			break;
		}
	}
	return wynik;
}
stock GetObjectIndex( objectid )
{
	new uid = 0;
	//ForeachEx(i, MAX_OBJECTS)
	for(new i; i < MAX_OBJECTS; i++)
	{
		if(ObjectInfo[i][oObject] == objectid)
		{
			uid = i;
			break;
		}
	}
	return uid;
}
stock GetDynamicObjectModelID(objectid)
{
	return Streamer_GetIntData(0,objectid,E_STREAMER_MODEL_ID);
}
stock CountObjectsFromDB()
{
	new Cache:result = mysql_query(MySQL, "SELECT * FROM `Obiekty`");
	new count=cache_num_rows();
	cache_delete(result);
	return count;
}
stock CountObjectsCreatedByPlayer(playerid)
{
	new wynik,query[256];
	format(query,256,"SELECT `uid` FROM `Obiekty` WHERE `uid`='%d';",GetPlayerUID(playerid));
	new Cache:result = mysql_query(MySQL,query);
	wynik=cache_num_rows();
	cache_delete(result);
	return wynik;
}
stock GetObjectCreatedPerGroup(playerid)
{
    new wynik,query[256];
    format(query,256,"SELECT `idgrupa` FROM `Obiekty` WHERE `idgrupa`='%d';", gracz[playerid][OrgID]);
    new Cache:result = mysql_query(MySQL,query);
    wynik=cache_num_rows();
    cache_delete(result);
    return wynik;
}

stock GetMapperPremGroup(playerid)
{
	new wynik;
	if((gracz[playerid][ViceSzefORG] || gracz[playerid][SzefORG]) && gracz[playerid][MapperLvl] == 0) wynik = 1;
	else wynik = gracz[playerid][MapperLvl];
	return wynik;
}
//********************************************************************************************************************************KOMENDY DYNAMICZNEGO SYSTEMU OBIEKTÓW
CMD:mduty(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(gracz[playerid][MapperLvl] == 0)
	{
		gracz[playerid][MapperLvl] = 2;
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "[M] "COL_GREEN"Zalogowałeś"COL_WHITE" się na Mapper Duty.");
	}
	else
	{
		gracz[playerid][MapperLvl] = 0;
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "[M] "COL_RED"Wylogowałeś"COL_WHITE" się na Mapper Duty.");
	}
	return 1;
}

new mmc_objects[] =
{
	3594, 12957, 2673, 2674, 2675, 2676, 851, 874, 1458, 1457, 18726, 18748, 853, 2905, 2906, 2907, 2908, 1362, 944, 18862, 734, 766, 1349, 19294, 16327, 18690, 1327, 693, 19972, 790, 791,
	3593, 2060, 3632, 3633, 1812, 1771, 19944, 3566, 3875, 3578, 873, 639
};

CMD:mmc(playerid, params[])
{
	if(gracz[playerid][MapperLvl] < 2) return Error(playerid, "Brak uprawnień.");
	ShowModelSelectionMenuEx(playerid, mmc_objects, sizeof(mmc_objects), "Obiekty postapo", MSEL_GOBJECTS, _, _, 30.0);

	return 1;
}

CMD:mtool(playerid, params[])
{
	if(gracz[playerid][MapperLvl] < 2) return Error(playerid, "Brak uprawnień.");
	new str_mtool[1024];
	strcat(str_mtool, ""COL_RED"» "COL_GREY"Odsłoń mapę i minimapę\n");
	strcat(str_mtool, ""COL_RED"» "COL_GREY"Ustaw sobie dzień i ładną pogodę\n");
	strcat(str_mtool, ""COL_RED"» "COL_GREY"Ustaw sobie noc i ładną pogodę\n");
	strcat(str_mtool, ""COL_RED"» "COL_GREY"Ustaw oryginalną pogodę\n");
	strcat(str_mtool, ""COL_RED"» "COL_GREY"Jetpack\n");
	Dialog_Show(playerid, MTOOL, DIALOG_STYLE_LIST, ""COL_RED"» "COL_BLUE"Narzędzia mappera", str_mtool, "Wybierz", "Anuluj");
	return 1;
}

Dialog:MTOOL(playerid, response, listitem, inputtext[])
{
	if(gracz[playerid][MapperLvl] < 2) return Error(playerid, "Brak uprawnień.");
	if(!response) return 1;
	SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Wybrano "COL_GREY"%s"COL_RED"))", inputtext);
	switch(listitem)
	{
		case 0:
		{
			UseItem(playerid, 148);
			UseItem(playerid, 149);
		}
		case 1:
		{
			gracz[playerid][mapper_weather] = 1;
		}
		case 2:
		{
			gracz[playerid][mapper_weather] = 2;
		}
		case 3:
		{
			gracz[playerid][mapper_weather] = 0;
		}
		case 4:
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
		}
	}
	return 1;
}

CMD:mc(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!gracz[playerid][MapperLvl]) return Error(playerid, "Brak uprawnień.");
	if(PlayerEditObject[playerid]) return Error(playerid, "W tej chwili edytujesz inny obiekt.");
	if(CountObjectsFromDB() >= MAX_OBJECTS) return Error(playerid, "Limit obiektów na serwerze przekroczony!");
	new model;
	if(sscanf(params, "d", model)) return SendClientMessage(playerid, -1, "UŻYJ: /mc [idobiektu]");
	if(model < 616) return Error(playerid, "Błędny model.");
	if(!BaseObjectIsAllowed(model) && gracz[playerid][MapperLvl] == 1) return Error(playerid, "Dostępne obiekty grup znajdziesz pod "COL_BLUE"/gmc");
	new vw = GetPlayerVirtualWorld(playerid);
	new interior = GetPlayerInterior(playerid);
	new Float:Pos[3]; // Definiowanie pozycji
	// Przypisywanie pozycji
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	if(gracz[playerid][MapperLvl] >= 2)
	{
		//if(CountObjectsCreatedByPlayer(playerid) >= 500) return SendClientMessage(playerid, -1, "Przekroczona ilość stworzonych obiektów(300) dla Ciebie!");
		// Tworzenie obiektu
		new uid = AddObject(model, 0 - gracz[playerid][MapperLvl], gracz[playerid][UID], vw, interior, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);
		// Definiowanie zmiennych
		PlayerEditObject[playerid] = uid;
		EditDynamicObject(playerid, ObjectInfo[uid][oObject]);///
		// Informacja o komendach dla gracza
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Stworzono obiekt: %d | To twój: %d obiekt | UID: %d"COL_RED"))", model, CountObjectsCreatedByPlayer(playerid), PlayerEditObject[playerid]);
		SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
		// Aktualizowanie pozycji
		Streamer_Update(playerid);
	}
	else if(gracz[playerid][MapperLvl] == 1 && IsPlayerInBaseArea(playerid))
	{
		if(GetObjectCreatedPerGroup(playerid) >= 100) return Error(playerid, "Limit obiektów przekroczony (100 max).");
		// Tworzenie obiektu
		new uid = AddObject(model, gracz[playerid][OrgID], GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);
		// Definiowanie zmiennych
		PlayerEditObject[playerid] = uid;
		EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
		// Informacja o komendach dla gracza
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Stworzono obiekt: %d | "COL_RED"%d"COL_GREY"/"COL_GREEN"500"COL_EASY" obiekt | UID: %d"COL_RED"))", model, GetObjectCreatedPerGroup(playerid), PlayerEditObject[playerid]);
		SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
		// Aktualizowanie pozycji
		Streamer_Update(playerid);
	}
	else
	{
		Error(playerid, "Możesz budować tylko na terenie bazy.");
	}
	return 1;
}
CMD:msel(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!gracz[playerid][MapperLvl]) return Error(playerid, "Brak uprawnień.");
	if(PlayerEditObject[playerid]) return Error(playerid, "W tej chwili edytujesz inny obiekt.");
	SelectObject(playerid);
	return 1;
}
CMD:mdel(playerid, params[])
{
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	// Pobieranie ID obiektu
	// Usuwanie obiektu
	DeleteObject(PlayerEditObject[playerid]);
	// Informowanie gracza
	LeftNotifyShow(playerid, "Sukces!", "Obiekt ~r~usuniety~w~.", LN_RED);
	// Zerowanie zmiennych
	CancelEdit(playerid);
	PlayerEditObject[playerid] = 0;
	return 1;
}
CMD:mcopy(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(CountObjectsFromDB() > MAX_OBJECTS) return Error(playerid, "Limit obiektów na serwerze przekroczony!");
	new objectid = PlayerEditObject[playerid];
	new vw = GetPlayerVirtualWorld(playerid); // Definiowanie świata
	new interior = GetPlayerInterior(playerid); // Definiowanie interior
	new Float:Pos[3]; // Definiowanie pozycji
	new Float:Rot[3]; // Definiowanie pozycji
	GetDynamicObjectRot(ObjectInfo[objectid][oObject], Rot[0], Rot[1], Rot[2]);
	GetDynamicObjectPos(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
	new uid;
	if(gracz[playerid][MapperLvl] >= 2)
	{
		uid = AddObject(ObjectInfo[objectid][oModel], 0 - gracz[playerid][MapperLvl], GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
	}
	else
	{
		uid = AddObject(ObjectInfo[objectid][oModel], gracz[playerid][OrgID], GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
	}
	GetDynamicObjectPos(ObjectInfo[uid][oObject], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ]);
	GetDynamicObjectRot(ObjectInfo[uid][oObject], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ]);
	OnPlayerEditDynamicObject(playerid, ObjectInfo[uid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ]);
	EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
	PlayerEditObject[playerid] = uid;
	LeftNotifyShow(playerid, "Sukces!", "Obiekt ~g~skopiowany~w~.", LN_GREEN);
	Streamer_Update(playerid);
	return 1;
}


CMD:mrx(playerid, params[])
{
	new Float: pos;
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(sscanf(params, "f", pos))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mrx [rotacja X]");
		return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		ObjectInfo[objectid][oRX] = ObjectInfo[objectid][oRX]+pos;
		SetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		//
		GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
		OnPlayerEditDynamicObject(playerid, ObjectInfo[objectid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]\
		, ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
		PlayerEditObject[playerid] = objectid;
		//
		Streamer_Update(playerid);
		// Informowanie gracza
		LeftNotifyShow(playerid, "Sukces!", "Rotacja obiektu ~g~zmieniona~w~.", LN_GREEN);
	}
	return 1;
}
CMD:mry(playerid, params[])
{
	new Float: pos;
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(sscanf(params, "f", pos))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mry [rotacja Y]");
		return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		ObjectInfo[objectid][oRY] = ObjectInfo[objectid][oRY]+pos;
		SetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		//
		GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
		OnPlayerEditDynamicObject(playerid, ObjectInfo[objectid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]\
		, ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
		PlayerEditObject[playerid] = objectid;
		//
		Streamer_Update(playerid);
		// Informowanie gracza
		LeftNotifyShow(playerid, "Sukces!", "Rotacja obiektu ~g~zmieniona~w~.", LN_GREEN);
	}
	return 1;
}
CMD:mrz(playerid, params[])
{
	new Float: pos;
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(sscanf(params, "f", pos))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mrz [rotacja Z]");
		return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		ObjectInfo[objectid][oRZ] = ObjectInfo[objectid][oRZ]+pos;
		SetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		//
		GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
		OnPlayerEditDynamicObject(playerid, ObjectInfo[objectid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]\
		, ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
		PlayerEditObject[playerid] = objectid;
		//
		Streamer_Update(playerid);
		// Informowanie gracza
		LeftNotifyShow(playerid, "Sukces!", "Rotacja obiektu ~g~zmieniona~w~.", LN_GREEN);
	}
	return 1;
}
CMD:mmat(playerid, params[])
{
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	new index, type, comm1[256];
	new query[1024];
	if(sscanf(params, "ddS()[256]", index, type, comm1))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mmat [index (0 - 15) [0 - tekstura / 1 - napis] [parametry]");
		return 1;
	}
	else
	{
		if(index < 0 || index > 15)
		{
			SendClientMessage(playerid, -1, "Maxymalny index to 15 a minimalny to 0 - ustaw poprawny index.");
			return 1;
		}
		if(type != 0 && type != 1)
		{
			SendClientMessage(playerid, -1, "Typ nie jest prawidłowy. 0 - tekstura / 1 - napis - Ustaw poprawny typ.");
			return 1;
		}
		if(type) // Napis
		{
			new object = PlayerEditObject[playerid];
			new matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];
			if(sscanf(comm1, "dddxxds[32]s[64]", matsize, fontsize, bold, fontcolor, backcolor, align, fontface, text))
			{
				SendClientMessage(playerid, -1, "UŻYJ: /mmat [index (0 - 5)] 1 [matsize] [fontsize] [bold] [fontcolor] [backcolor] [align] [font] [text]");
				return 1;
			}
			else
			{
				new color_font = ShiftRGBAToABGR(fontcolor);
				new color_back = ShiftRGBAToABGR(backcolor);
				EscapeMMAT(text);
				SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
				ObjectInfo[object][oMMAT] = 1;
				SaveObject(ObjectInfo[object][oUID]);
				mysql_escape_string(fontface, fontface);
				mysql_escape_string(text, text);
				mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty_text` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(MySQL,query,"SendQuery","");
				mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty_textury` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(MySQL,query,"SendQuery","");
				mysql_format(MySQL,query, sizeof(query), "INSERT INTO `Obiekty_text` VALUES (NULL, '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, matsize, fontsize, bold, color_font, color_back, align, fontface, text);
				mysql_tquery(MySQL,query,"SendQuery","");
				LeftNotifyShow(playerid, "Sukces!", "Tekstura ~g~nalozona~w~.", LN_GREEN);
			}
		}
		else // Tekstura
		{
			new object = PlayerEditObject[playerid];
			new modelid, txdname[32], texturename[32], materialcolor;
			if(sscanf(comm1, "xds[32]s[32]", materialcolor, modelid, txdname, texturename))
			{
				SendClientMessage(playerid, -1, "UŻYJ: /mmat [index (0 - 5)] 0 [materialcolor] [modelid] [txdname] [texturename]");
				return 1;
			}
			else
			{
				SetDynamicObjectMaterial(ObjectInfo[object][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
				ObjectInfo[object][oMMAT] = 1;
				SaveObject(ObjectInfo[object][oUID]);
				mysql_escape_string(txdname, txdname);
				mysql_escape_string(texturename, texturename);
				mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty_textury` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(MySQL,query,"SendQuery","");
				mysql_format(MySQL,query, sizeof(query), "DELETE FROM `Obiekty_text` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(MySQL,query,"SendQuery","");
				mysql_format(MySQL,query, sizeof(query), "INSERT INTO `Obiekty_textury` VALUES (NULL,'%d', '%d', '%d', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, ShiftRGBAToABGR(materialcolor), modelid, txdname, texturename);
				mysql_tquery(MySQL,query,"SendQuery","");
				LeftNotifyShow(playerid, "Sukces!", "Tekstura ~g~nalozona~w~.", LN_GREEN);
			}
		}
	}
	return 1;
}
