//********************************************************************************************INICJACJA U¯YCIA PRZEDMIOTU
stock UseItem(playerid, itemid)
{
	switch(itemid)
	{
		case 1..46://BRONIE
		{
			if(eq_select[playerid][s_used])
			{
				mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
				mysql_query(MySQL, mQuery, false);
				LeftNotifyShow(playerid, "Sukces!", "Bron schowana!");
				LoadUsedWeapons(playerid);
			}
			else if(IsAnyWeaponUsed(playerid) < 2)
			{
				if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu.", LN_RED);
				new temp_giveweap;
				//***************na kategorie
				switch(GetWeaponCategory(itemid))
				{
					case 1..3:
					{
						temp_giveweap = WeapSkill(playerid, 1);
					}
					case 4:
					{
						temp_giveweap = WeapSkill(playerid, 3);
					}
					case 6:
					{
						temp_giveweap = WeapSkill(playerid, 12);
					}
					case 7:
					{
						temp_giveweap = WeapSkill(playerid, 14);
					}
					case 8:
					{
						temp_giveweap = WeapSkill(playerid, 16);
					}
				}
				//***************na bronie
				switch(itemid)
				{
					case 4:
					{
						temp_giveweap = 1;
					}
					case 28, 32:
					{
						temp_giveweap = WeapSkill(playerid, 2);
					}
					case 29:
					{
						temp_giveweap = WeapSkill(playerid, 4);
					}
				}
				if(temp_giveweap)
				{
					if(GiveWeapon(playerid, itemid))
					{
						mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
						mysql_query(MySQL, mQuery, false);
						format(temp_string, 128, "Wyciagnales: ~y~%s~w~.", ItemName[itemid]);
						LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
						LoadUsedWeapons(playerid);
					}
					else
					{
						LeftNotifyShow(playerid, "error", "Slot tej broni jest ~r~zajety~w~ przez inna bron.");
					}
				}
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Mozesz miec w uzyciu max ~r~2~w~ bronie!");
			}
		}
		case 47..52://AMUNICJA
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 53://DREWNO
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu.", LN_RED);
			if(InRangeOfMyCampfire(playerid))
			{
				Dialog_Show(playerid, DREWNOAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), ""COL_WHITE"1. "COL_GREEN"Rozpal ognisko"COL_GREY" (Koszt: 5 drewna)\n"COL_WHITE"2. "COL_BLUE"Do³ó¿ drewna do ogniska"COL_GREY" (Koszt: 1 drewna - ognisko pali siê o minutê d³u¿ej)", "Wybierz", "Wróæ");
			}
			else
			{
				Dialog_Show(playerid, DREWNOAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), ""COL_WHITE"1. "COL_GREEN"Rozpal ognisko"COL_GREY" (Koszt: 5 drewna)", "Wybierz", "Wróæ");
			}
		}
		case 54://PUSTY KANISTER
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu.", LN_RED);
			if(IsRangeOfDistributor(playerid))
			{
				TogglePlayerControllable(playerid, false);
				StartCombineMode(playerid, 7);
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzupelnic ~y~kanister~w~ musisz znajdowac sie przy sprawnym dystrybutorze.");
			}
		}
		case 55://PE£NY KANISTER
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu.", LN_RED);
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
				Dialog_Show(playerid, REFUEL, DIALOG_STYLE_TABLIST_HEADERS, "Który pojazd chcesz zatankowaæ?", list_veh, "Wybierz", "Anuluj");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzupelnic paliwo, musisz sie znajdowac przy ~r~zgaszonym, niezatankwanym do pelna ~y~pojezdzie~w~.");
			}
		}
		case 56://ODCZYNNIK CHEMICZNY
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 57://¯ELAZO
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 58..65://AMUNICJA
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 66://BATONIK PROTEINOWY
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada: '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 25);
			GivePlayerHP(playerid, 20);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 67..68:
		{
			if(eq_select[playerid][s_used])
			{
				mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
				mysql_query(MySQL, mQuery, false);
				LeftNotifyShow(playerid, "Sukces!", "Karnet wylaczony z uzytku!");
				LoadKarnetData(playerid);
			}
			else
			{
				mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND  (`itemid`='67' OR `itemid`='68')  AND `used`='1';", gracz[playerid][UID]);
				new Cache:getquery = mysql_query(MySQL, mQuery);
				mq_getdata();
				cache_delete(getquery);
				if(rekordy)
				{
					LeftNotifyShow(playerid, "error", "Mozesz miec tylko ~r~jeden~w~ uzyty karnet.");
				}
				else
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(MySQL, mQuery, false);
					LoadKarnetData(playerid, 1);
				}
			}
		}
		case 69..73:
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 74:
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu.", LN_RED);
			new list_veh[1024];
			format(list_veh, 1024, "UID\tNazwa pojazdu");
			new detected_vehs;
			for(new v; v < WORLD_VEHICLES; v++)
			{
				if(pojazd[v][v_id])
				{
					if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
					{
						format(list_veh, 1024, "%s\n"COL_BLACK"%d\t"COL_EASY"%s", list_veh, v, GetVehicleName(pojazd[v][v_model]));
						detected_vehs++;
					}
				}
			}
			if(detected_vehs)
			{
				Dialog_Show(playerid, TOOLVEHSEL, DIALOG_STYLE_TABLIST_HEADERS, "Na którym pojeŸdzie chcesz u¿yæ narzêdzi?", list_veh, "Wybierz", "Anuluj");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzyc narzedzi, musisz sie znajdowac przy ~y~pojezdzie~w~.");
			}
		}
		case 75://konserwa rybna
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 17);
			GivePlayerHP(playerid, 3);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 76..77://Zgnile jablko/banan
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 10);
			TakePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 78://Skazone mieso
		{
			new cowner;
			if(InRangeOfAnyCampfire(playerid, cowner))
			{
				SetPVarInt(playerid, "food_uid", eq_select[playerid][s_id]);
				SetPVarInt(playerid, "food_itemid", itemid);
				StartCombineMode(playerid, 11);
			}
			else
			{
				format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
				format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				FeedPlayer(playerid, 20);
				TakePlayerHP(playerid, 5);
				RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
			}
		}
		case 79://Upieczone mieso
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 30);
			GivePlayerHP(playerid, 10);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 80://Skazona ryba
		{
			new cowner;
			if(InRangeOfAnyCampfire(playerid, cowner))
			{
				SetPVarInt(playerid, "food_uid", eq_select[playerid][s_id]);
				SetPVarInt(playerid, "food_itemid", itemid);
				StartCombineMode(playerid, 11);
			}
			else
			{
				format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
				format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				FeedPlayer(playerid, 20);
				TakePlayerHP(playerid, 5);
				RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
			}
		}
		case 81://upieczona rybna
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 40);
			GivePlayerHP(playerid, 20);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 82:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 25);
			GivePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 83://zgni³a pomarancza
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 10);
			TakePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 84..86:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 20);
			GivePlayerHP(playerid, 3);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 87:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 15);
			GivePlayerHP(playerid, 3);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 88:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 5);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 89..90:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 25);
			GivePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 91:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 5);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 92:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 30);
			GivePlayerHP(playerid, 10);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 93:
		{
			format(temp_string, 128, "Zjedzono: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me zjada '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			FeedPlayer(playerid, 20);
			GivePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 94:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 10);
			TakePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 95:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 30);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 96:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 25);
			GivePlayerHP(playerid, 2);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 97:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 30);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 98:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 40);
			GivePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 99:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 100);
			GivePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 100:
		{
			LeftNotifyShow(playerid, "info", "~b~Zeton~w~ to waluta. Przedmiot zuzywa sie automatycznie.", _, 5);
		}
		case 101..102:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			DrinkPlayer(playerid, 25);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 103:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			SetPlayerDrunkLevel (playerid, 3000);
			DrinkPlayer(playerid, 30);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 104:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			SetPlayerDrunkLevel (playerid, 4000);
			DrinkPlayer(playerid, 40);
			GivePlayerHP(playerid, 1);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 105:
		{
			format(temp_string, 128, "Wypito: ~y~%s~w~.", ItemName[itemid]);
			LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5);
			format(temp_string, 128, "/me pije '%s'.", ItemName[itemid]);
			PC_EmulateCommand(playerid, temp_string);
			SetPlayerDrunkLevel (playerid, 5000);
			DrinkPlayer(playerid, 30);
			GivePlayerHP(playerid, 5);
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
		}
		case 106..114:
		{
			new temp_usemed;
			switch(itemid)
			{
				case 106: temp_usemed = MedSkill(playerid, 1);
				case 107: temp_usemed = MedSkill(playerid, 2);
				case 111: temp_usemed = MedSkill(playerid, 3);
				case 108: temp_usemed = MedSkill(playerid, 4);
				default: temp_usemed = MedSkill(playerid, 5);
			}
			if(temp_usemed) RemoteUseItem(playerid, itemid, eq_select[playerid][s_id]);
		}
		case 115..119:
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 120:
		{
			new tool_str[1024];
			format(tool_str, 1024, "Czynnoœæ");
			new temp_useweaptool;
			//kategoria
			switch(GetWeaponCategory(gracz[playerid][actual_weapon]))
			{
				case 0:
				{
					LeftNotifyShow(playerid, "error", "Musisz ~r~miec w reku bron~w~, na ktorej chcesz ~g~uzyc~w~ tych narzedzi.");
					temp_useweaptool = 0;
				}
				case 1:
				{
					temp_useweaptool = WeapSkill(playerid, 5);
				}
				case 2:
				{
					temp_useweaptool = WeapSkill(playerid, 6);
				}
				case 3:
				{
					temp_useweaptool = WeapSkill(playerid, 7);
				}
				case 4:
				{
					temp_useweaptool = WeapSkill(playerid, 8);
				}
				case 6:
				{
					temp_useweaptool = WeapSkill(playerid, 13);
				}
				case 7:
				{
					temp_useweaptool = WeapSkill(playerid, 15);
				}
				case 8:
				{
					temp_useweaptool = WeapSkill(playerid, 17);
				}
			}
			//na bronie.
			switch(gracz[playerid][actual_weapon])
			{
				case 28:
				{
					temp_useweaptool = WeapSkill(playerid, 9);
				}
				case 32:
				{
					temp_useweaptool = WeapSkill(playerid, 10);
				}
				case 29:
				{
					temp_useweaptool = WeapSkill(playerid, 11);
				}
			}
			if(temp_useweaptool)
			{
				format(tool_str, 1024, "%s\n"COL_WHITE"1."COL_GREEN" Napraw "COL_GREY"%s", tool_str, ItemName[gracz[playerid][actual_weapon]]);
				Dialog_Show(playerid, TOOLWEAPACTION, DIALOG_STYLE_TABLIST_HEADERS, "Co chcesz zrobiæ?", tool_str, "Wybierz", "Anuluj");
			}
		}
		case 122:
		{
			new str_med[1024];
			format(str_med, 1024, ""COL_WHITE"1."COL_PURPLE" Ulecz 5HP");
			format(str_med, 1024, "%s\n"COL_WHITE"2."COL_PURPLE" Ulecz 10HP", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"3."COL_PURPLE" Ulecz 20HP", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"4."COL_PURPLE" Ulecz 80HP", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"5."COL_PURPLE" Stwórz: Syrop Haps 10", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"6."COL_PURPLE" Stwórz: Syrop Haps 25", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"7."COL_PURPLE" Stwórz: Syrop Haps 50", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"8."COL_PURPLE" Stwórz: Syrop AntiRad 10", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"9."COL_PURPLE" Stwórz: Syrop AntiRad 25", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"10."COL_PURPLE" Stwórz: Syrop AntiRad 50", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"11."COL_PURPLE" Stwórz: Syrop na wytrzymalosc", str_med);
			format(str_med, 1024, "%s\n"COL_WHITE"12."COL_PURPLE" WybudŸ gracza z BW", str_med);
			Dialog_Show(playerid, MEDYKTOOL, DIALOG_STYLE_LIST, "Co chcesz zrobiæ?", str_med, "Wybierz", "Anuluj");
		}
		case 123..132:
		{
			LeftNotifyShow(playerid, "error", "Ten przedmiot uzywa sie automatycznie!");
		}
		case 133:
		{
			new str_kr[512];
			format(str_kr, 512, "Opcja\tStatus");
			if(eq_select[playerid][s_used]) format(str_kr, 512, "%s\n"COL_GREEN"W³¹cz"COL_GREY"/"COL_ORANGE"Wy³¹cz\t"COL_GREEN"W³¹czona", str_kr);
			else format(str_kr, 512, "%s\n"COL_GREEN"W³¹cz"COL_GREY"/"COL_ORANGE"Wy³¹cz\t"COL_RED"Wy³¹czona", str_kr);
			format(str_kr, 512, "%s\n"COL_GREY"Czêstotliwoœæ\t"COL_YELLOW"%d"COL_GREY" MHz", str_kr, gracz[playerid][KRMHZ]);
			Dialog_Show(playerid, KROTKOFALOWKA, DIALOG_STYLE_TABLIST_HEADERS, ""COL_BLUE"»"COL_GREY" Krótkofalówka", str_kr, "Wybierz", "Anuluj");
		}
		case 144:
		{
			new str_clock[64];
			format(str_clock, 64, "~w~%02d~g~:~w~00", serwer[godzina]);
			GameTextForPlayer(playerid, str_clock, 3000, 1);
			format(temp_string, 128, "/me spogl¹da na zegarek.");
			PC_EmulateCommand(playerid, temp_string);
		}
		case 147://licznik geigera
		{
			if(eq_select[playerid][s_used])
			{
				mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
				mysql_query(MySQL, mQuery, false);
				LeftNotifyShow(playerid, "Sukces!", "~y~Licznik Geigera~w~ zostal ~r~wylaczony~w~.");
				LoadUsedGeiger(playerid);
			}
			else
			{
				mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
				mysql_query(MySQL, mQuery, false);
				LeftNotifyShow(playerid, "Sukces!", "~y~Licznik Geigera~w~ zostal ~g~wlaczony~w~.");
				LoadUsedGeiger(playerid);
			}
		}
		case 148:
		{
			LeftNotifyShow(playerid, "Sukces!", "~y~Mapa ~g~odkryta~w~! Mozesz obejrzec ja pod ESC.");
			GangZoneHideForPlayer(playerid, serwer[gz_hidemap]);
			format(temp_string, 128, "/me spogl¹da na mapê.");
			PC_EmulateCommand(playerid, temp_string);
		}
		case 149:
		{
			LeftNotifyShow(playerid, "Sukces!", "~y~Minimapa ~g~odkryta~w~!");
			format(temp_string, 128, "/me spogl¹da na kompas.");
			PC_EmulateCommand(playerid, temp_string);
			ShowMinimap(playerid);
		}
		case 150:
		{
			new str_gps[512];
			format(str_gps, 512, "Opcja\tStatus");
			if(eq_select[playerid][s_used]) format(str_gps, 512, "%s\n"COL_GREEN"W³¹cz"COL_GREY"/"COL_ORANGE"Wy³¹cz\t"COL_GREEN"W³¹czona", str_gps);
			else format(str_gps, 512, "%s\n"COL_GREEN"W³¹cz"COL_GREY"/"COL_ORANGE"Wy³¹cz\t"COL_RED"Wy³¹czona", str_gps);
			format(str_gps, 512, "%s\n"COL_GREY"Czêstotliwoœæ\t"COL_YELLOW"%d"COL_GREY" Hz", str_gps, gracz[playerid][gps_hz]);
			Dialog_Show(playerid, GPS, DIALOG_STYLE_TABLIST_HEADERS, ""COL_BLUE"»"COL_GREY" GPS", str_gps, "Wybierz", "Anuluj");
		}
		case 151:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				GivePlayerHP(playerid, 10);
			}
		}
		case 152:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				GivePlayerHP(playerid, 25);
			}
		}
		case 153:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				GivePlayerHP(playerid, 50);
			}
		}
		case 154:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Napromieniowanie ~g~zredukowano~w~!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				gracz[playerid][rads] -= 10;
				NormalizeRads(playerid);
				mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
				mq_send("QRadsUpdate");
			}
		}
		case 155:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Napromieniowanie ~g~zredukowano~w~!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				gracz[playerid][rads] -= 25;
				NormalizeRads(playerid);
				mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
				mq_send("QRadsUpdate");
			}
		}
		case 156:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Napromieniowanie ~g~zredukowano~w~!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				gracz[playerid][rads] -= 50;
				NormalizeRads(playerid);
				mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[playerid][rads], gracz[playerid][UID]);
				mq_send("QRadsUpdate");
			}
		}
		case 157:
		{
			if(RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Twoja postac nie bedzie sie meczyla przez 10 minut!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				gracz[playerid][stamina_boost] = serwer[time_timestamp]+60*10;
			}	
		}
		case 158:
		{
			SetPVarInt(playerid, "UzylUbranie", 1);
			WybierzSkin(playerid);
		}
		case 159:
		{
			StartFish(playerid);
		}
		case 160..163://bandana
		{
			if(eq_select[playerid][s_used])
			{
				new str_akc[512];
				format(str_akc, 512, ""COL_WHITE"1. "COL_RED"Przestañ u¿ywaæ");
				format(str_akc, 512, "%s\n"COL_WHITE"2. "COL_EASY"Edytuj", str_akc);
				format(str_akc, 512, "%s\n"COL_WHITE"3. "COL_GREEN"Zresetuj pozycje", str_akc);
				Dialog_Show(playerid, BANDANACONF, DIALOG_STYLE_LIST, ""COL_BLUE"»"COL_GREY" Bandana", str_akc, "Wybierz", "Anuluj");
			}
			else
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, BANDANA_SLOT))
				{
					LeftNotifyShow(playerid, "error", "Mozna miec tylko ~r~jedna~w~ bandane w uzyciu.");
				}
				else 
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(MySQL, mQuery, false);
					LeftNotifyShow(playerid, "Sukces!", "Bandana ~g~nalozona~w~!");
					LoadUsedAccessories(playerid);
				}
			}
		}
		case 164..189://okulary
		{
			if(eq_select[playerid][s_used])
			{
				new str_akc[512];
				format(str_akc, 512, ""COL_WHITE"1. "COL_RED"Przestañ u¿ywaæ");
				format(str_akc, 512, "%s\n"COL_WHITE"2. "COL_EASY"Edytuj", str_akc);
				format(str_akc, 512, "%s\n"COL_WHITE"3. "COL_GREEN"Zresetuj pozycje", str_akc);
				Dialog_Show(playerid, OKULARYCONF, DIALOG_STYLE_LIST, ""COL_BLUE"»"COL_GREY" Okulary", str_akc, "Wybierz", "Anuluj");
			}
			else
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, OKULARY_SLOT))
				{
					LeftNotifyShow(playerid, "error", "Mozna miec tylko ~r~jedne~w~ okulary w uzyciu.");
				}
				else 
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(MySQL, mQuery, false);
					LeftNotifyShow(playerid, "Sukces!", "Okulary ~g~nalozone~w~!");
					LoadUsedAccessories(playerid);
				}
			}
		}
		case 190..202://czapki
		{
			if(eq_select[playerid][s_used])
			{
				new str_akc[512];
				format(str_akc, 512, ""COL_WHITE"1. "COL_RED"Przestañ u¿ywaæ");
				format(str_akc, 512, "%s\n"COL_WHITE"2. "COL_EASY"Edytuj", str_akc);
				format(str_akc, 512, "%s\n"COL_WHITE"3. "COL_GREEN"Zresetuj pozycje", str_akc);
				Dialog_Show(playerid, CZAPKACONF, DIALOG_STYLE_LIST, ""COL_BLUE"»"COL_GREY" Czapka", str_akc, "Wybierz", "Anuluj");
			}
			else
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, CZAPKA_SLOT))
				{
					LeftNotifyShow(playerid, "error", "Mozna miec tylko ~r~jedna~w~ czapke w uzyciu.");
				}
				else 
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(MySQL, mQuery, false);
					LeftNotifyShow(playerid, "Sukces!", "Czapka ~g~nalozona~w~!");
					LoadUsedAccessories(playerid);
				}
			}
		}
		default:
		{
			LeftNotifyShow(playerid, "error", "Tego przedmiotu ~r~nie da sie uzyc~w~. Bardzo mozliwe, ze mozesz go sprzedac na ~y~hali targowej~w~.");
		}
	}
	return 1;
}
//*************************************************************************************************************************************************************************REMOTE ITEM
stock UseRemoteItem(playerid, targetid, itemid, itemuid)
{
	switch(itemid)
	{
		case 106:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Krwawienie ~g~zatrzymane~w~!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				StopBlooding(targetid);
				GivePlayerHP(targetid, 1);
			}
		}
		case 107:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				StopBlooding(targetid);
				GivePlayerHP(targetid, 30);
			}
		}
		case 108:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				StopBlooding(targetid);
				GivePlayerHP(targetid, 50);
			}
		}
		case 109:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Napromieniowanie ~g~zredukowano~w~!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				gracz[targetid][rads] -= 20;
				NormalizeRads(targetid);
				mq_format("UPDATE `Konta` SET `rads`='%d' WHERE `id`='%d';", gracz[targetid][rads], gracz[targetid][UID]);
				mq_send("QRadsUpdate");
			}
		}
		case 110:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				GivePlayerHP(targetid, 100);
				FeedPlayer(targetid, 100);
				DrinkPlayer(targetid, 100);
			}
		}
		case 111:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Krwawienie ~g~zatrzymane~w~!", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				StopBlooding(targetid);
				GivePlayerHP(targetid, 2);
			}
		}
		case 112:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Przywrocono HP.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				GivePlayerHP(targetid, 100);
			}   
		}
		case 113:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Przez najblizsza godzine, postac nie bedzie krwawila.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				StopBlooding(targetid);
				gracz[targetid][time_antiblood] = serwer[time_timestamp]+(60*60);
				mq_format("UPDATE `Konta` SET `time_antiblood`='%d' WHERE `id`='%d';", gracz[targetid][time_antiblood], gracz[targetid][UID]);
				mq_send("QAntiBlood");
			}   
		}
		case 114:
		{
			if(RemoveItemFromPlayerEx(playerid, itemuid, 1))
			{
				format(temp_string, 128, "Uzyto: ~y~%s~w~. Przez najblizsze 2 godziny, postac nie bedzie krwawila.", ItemName[itemid]);
				LeftNotifyShow(playerid, "Sukces!", temp_string, _, 5); 
				if(targetid != playerid) format(temp_string, 128, "/me u¿ywa '%s' na postaci '%s'.", ItemName[itemid], nick(targetid));
				else format(temp_string, 128, "/me u¿ywa '%s'.", ItemName[itemid]);
				PC_EmulateCommand(playerid, temp_string);
				StopBlooding(targetid);
				gracz[targetid][time_antiblood] = serwer[time_timestamp]+(60*60)*2;
				mq_format("UPDATE `Konta` SET `time_antiblood`='%d' WHERE `id`='%d';", gracz[targetid][time_antiblood], gracz[targetid][UID]);
				mq_send("QAntiBlood");
			}   
		}
	}
	return 1;
}
//********************************************************************************************************************************************************£ADOWANIE U¯YWANYCH PRZEDMIOTÓW
stock LoadUsedItems(playerid)
{
	LoadUsedWeapons(playerid);
	LoadKarnetData(playerid);
	LoadUsedKrotkofalowka(playerid);
	LoadUsedGeiger(playerid);
	LoadUsedGPS(playerid);
	LoadUsedAccessories(playerid);
	SyncZetony(playerid);
	return 1;
}
//********************************************************************************************************************************************************SKRYPTY ROZWIJAJ¥CE
//BROÑ
stock LoadUsedWeapons(playerid)
{
	RemovePlayerAttachedObject(playerid, 9);
	RemovePlayerAttachedObject(playerid, 8);
	mq_format("SELECT `itemid`,`cdn`,`cdn_max` FROM `przedmioty` WHERE `userid` = '%d' AND (`itemid`>='1' AND `itemid`<='46') AND `used`='1';", gracz[playerid][UID]);
	mq_send("QLoadUsedWeap", "d", playerid);
	return 1;
}

forward QLoadUsedWeap(playerid);
public QLoadUsedWeap(playerid)
{
	SetPlayerArmedWeapon(playerid, 0);
	ResetPlayerWeapons(playerid);
	for(new a; a < 50; a++)
	{
		weapon[playerid][a] = false; 
	}
	RemovePlayerAttachedObject(playerid, 9);
	RemovePlayerAttachedObject(playerid, 8);
	new t_itemid;
	mq_getdata();
	if(rekordy)
	{
		new i;
		while(i < rekordy)
		{
			t_itemid = cache_get_field_content_int(i, "itemid");
			weapon[playerid][t_itemid] = true;
			GivePlayerWeapon(playerid, t_itemid, 99999);
			Process_ArmedWeapon(playerid);
			w_cdn[playerid][t_itemid] = cache_get_field_content_int(i, "cdn");
			w_cdn_max[playerid][t_itemid] = cache_get_field_content_int(i, "cdn_max");
			i++;
		}
	}
	RefreshAmmo(playerid);
	return 1;
}
stock Process_ArmedWeapon(playerid)
{
	new weaponid[8],weaponammo[8];
	GetPlayerWeaponData(playerid,1,weaponid[1],weaponammo[1]);
	GetPlayerWeaponData(playerid,2,weaponid[2],weaponammo[2]);
	GetPlayerWeaponData(playerid,3,weaponid[3],weaponammo[3]);
	GetPlayerWeaponData(playerid,4,weaponid[4],weaponammo[4]);
	GetPlayerWeaponData(playerid,5,weaponid[5],weaponammo[5]);
	GetPlayerWeaponData(playerid,6,weaponid[6],weaponammo[6]);
	RemovePlayerAttachedObject(playerid, 9);
	RemovePlayerAttachedObject(playerid, 8);
	if(weaponid[1])
	{
		if(gracz[playerid][actual_weapon] != weaponid[1])
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,GetArmedFreeSlot(playerid)))
			{
				SetPlayerAttachedObject(playerid,GetArmedFreeSlot(playerid),GetWeaponModel(weaponid[1]),11, 0.101998, -0.062999, 0.064998, -58.399902 ,105.900009, 151.399993, 1.000000, 1.000000, 1.000000);
			}
		}
	}
	if(weaponid[2])
	{
		if(gracz[playerid][actual_weapon] != weaponid[2])
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,GetArmedFreeSlot(playerid)))
			{
				SetPlayerAttachedObject(playerid,GetArmedFreeSlot(playerid),GetWeaponModel(weaponid[2]),8, -0.109999, -0.021999, 0.090999, -90.100006 ,0.000000, -8.999998, 1.000000, 1.000000, 1.000000);
			}
		}
	}
	if(weaponid[3])
	{
		if(gracz[playerid][actual_weapon] != weaponid[3])
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,GetArmedFreeSlot(playerid)))
			{
				SetPlayerAttachedObject(playerid,GetArmedFreeSlot(playerid),GetWeaponModel(weaponid[3]),1, 0.330999, -0.228999, 0.099000, -172.599945 ,-143.199966, 3.199999, 1.000000, 1.000000, 1.000000);
			}
		}
	}
	if(weaponid[4])
	{
		if(gracz[playerid][actual_weapon] != weaponid[4])
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,GetArmedFreeSlot(playerid)))
			{
				SetPlayerAttachedObject(playerid,GetArmedFreeSlot(playerid),GetWeaponModel(weaponid[4]),7, -0.013999, 0.005999, -0.075000, -80.400100 ,-10.000000, 5.499998, 1.000000, 1.000000, 1.000000);
			}
		}
	}
	if(weaponid[5])
	{
		if(gracz[playerid][actual_weapon] != weaponid[5])
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,GetArmedFreeSlot(playerid)))
			{
				SetPlayerAttachedObject(playerid,GetArmedFreeSlot(playerid),GetWeaponModel(weaponid[5]),1, 0.367999, -0.272998, -0.038998, -7.699995 ,206.000000, 3.199999, 1.000000, 1.000000, 1.000000);
			}
		}
	}
	if(weaponid[6])
	{
		if(gracz[playerid][actual_weapon] != weaponid[6])
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,GetArmedFreeSlot(playerid)))
			{
				SetPlayerAttachedObject(playerid,GetArmedFreeSlot(playerid),GetWeaponModel(weaponid[6]),1, 0.320000, -0.228000, 0.098999, -178.500030 ,-143.800018, 0.000000, 1.000000, 1.000000, 1.000000);
			}
		}
	}
	return 1;
}

stock GetArmedFreeSlot(playerid)
{
	new wynik;
	if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) wynik = 8;
	else wynik = 9;
	return wynik;
}


//PUSTY KANISTER
stock IsRangeOfDistributor(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -1607.9446,-2717.4119,48.5391)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -11.9189,-2522.2725,36.6555)) return 1;
	return 0;
}
//PE£NY KANISTER
Dialog:REFUEL(playerid, response, listitem, inputtext[])
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
				StartCombineMode(playerid, 8);
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
//OGNISKO
Dialog:DREWNOAKCJA(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	switch(listitem)
	{
		case 0:
		{
			if(eq_select[playerid][s_count] < 5) return LeftNotifyShow(playerid, "error", "Potrzebujesz ~r~5 sztuk~w~.");
			if(gracz[playerid][in_interior]) return LeftNotifyShow(playerid, "error", "~r~Zakazuje sie~w~ rozpalania ogniska w interiorach.");
			new ownerid;
			if(InRangeOfAnyCampfire(playerid, ownerid)) return LeftNotifyShow(playerid, "error", "~r~W poblizu jest juz jedno ognisko.");
			if(CreateCampfire(playerid))
			{
				RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 5);
				LeftNotifyShow(playerid, "Sukces!", "Trwa ~y~rozpalanie ogniska~w~! Oddalenie sie spowoduje ze ognisko sie ~r~nie rozpali~w~.");
				ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
			}
			else
			{
				Dialog_Show(playerid, OGNISKOZNISZCZ, DIALOG_STYLE_MSGBOX, ""COL_WHITE"Czy chcesz "COL_RED"zniszczyæ"COL_WHITE" swoje poprzednie ognisko?", "System wykry³, ¿e na mapie jest ju¿ jedno stworzone przez Ciebie ognisko.\n"COL_YELLOW"Czy chcesz je zniszczyæ by móc rozpaliæ nowe?", "Tak", "Nie");
			}
		}
		case 1:
		{
			new ownerid;
			if(InRangeOfAnyCampfire(playerid, ownerid))
			{
				//SendClientMessageEx(playerid, -1, "DEBUG: Owner: %s", nick(ownerid));
				new add_campfire = ognisko[ownerid][o_status]+60;
				if(add_campfire < 299)
				{
					if(eq_select[playerid][s_count] < 1) return LeftNotifyShow(playerid, "error", "Potrzebujesz ~r~1 sztuki~w~.");
					RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 1);
					ognisko[ownerid][o_status] = add_campfire;
					if(ownerid != playerid)
					{
						SendClientMessage(playerid, -1, "(("COL_RED"Uwaga!"COL_EASY" Do³o¿y³eœ drewna do cudzego ogniska. Pamiêtaj, ¿e w³aœciciel mo¿e je zniszczyæ."COL_WHITE"))");
					}
					LeftNotifyShow(playerid, "Sukces!", "~g~Dolozono~w~ drewna do ogniska. Ognisko bedzie sie palic o ~g~minute dluzej~w~.");
					ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
				}
				else
				{
					LeftNotifyShow(playerid, "error", "Nie mozna podlozyc do ogniska wiecej drewna w tej chwili. ~g~Odczekaj~w~ jak troche sie wypali.");
				}
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Musisz byc w poblizu ~y~ogniska~w~.");
			}
		}
	}
	return 1;
}

Dialog:OGNISKOZNISZCZ(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(eq_select[playerid][s_count] < 5) return LeftNotifyShow(playerid, "error", "Potrzebujesz ~r~5 sztuk~w~.");
		if(gracz[playerid][in_interior]) return LeftNotifyShow(playerid, "error", "~r~Zakazuje sie~w~ rozpalania ogniska w interiorach.");
		if(CreateCampfire(playerid))
		{
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 5);
			LeftNotifyShow(playerid, "Sukces!", "Trwa ~y~rozpalanie ogniska~w~! Oddalenie sie spowoduje ze ognisko sie nie rozpali.");
		}
		else
		{
			ognisko[playerid][o_status] = 1;//gaszenie ogniska
			Process_Campfire(playerid);//gaszenie ogniska
			if(CreateCampfire(playerid))
			{
				RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], 5);
				LeftNotifyShow(playerid, "Sukces!", "Trwa ~y~rozpalanie ogniska~w~! Oddalenie sie spowoduje ze ognisko sie nie rozpali.");
			}
		}
	}
	return 1;
}
//KARNET
stock LoadKarnetData(playerid, showinfo = 0)
{
	mq_format("SELECT `id`,`cdn` FROM `przedmioty` WHERE `userid` = '%d' AND (`itemid`='67' OR `itemid`='68') AND `used`='1' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("QLoadKarnet", "dd", playerid, showinfo);
	return 1;
}

forward QLoadKarnet(playerid, showinfo);
public QLoadKarnet(playerid, showinfo)
{
	gracz[playerid][karnet] = 0;
	mq_getdata();
	if(rekordy)
	{
		gracz[playerid][karnet] = cache_get_field_content_int(0, "cdn");
		new str[128];
		if(gracz[playerid][karnet] > serwer[time_timestamp])
		{
			if(showinfo)
			{
				new dd, gg, hh, mm;
				SecToTime(gracz[playerid][karnet]-serwer[time_timestamp], dd, gg, hh, mm);
				format(str, 128, "~g~Uzyto~w~ karnetu na silownie. Karnet jest aktywny jeszcze przez:~y~ %02dgodz, %02dmin, %02dsek~w~.", gg, hh, mm);
				LeftNotifyShow(playerid, "Sukces!", str);
			}
		}
		else
		{
			gracz[playerid][karnet] = 0;
			new id = cache_get_field_content_int(0, "id");
			mq_format("UPDATE `przedmioty` SET `itemid`='68' WHERE `id`='%d';", id);
			mysql_query(MySQL, mQuery, false);
			if(showinfo)
			{
				format(str, 128, "~r~Uwaga~w~! Uzyty karnet jest ~r~niewazny~w~!", LN_RED);
				LeftNotifyShow(playerid, "Uwaga!", str);
			}
		}
	}
	return 1;
}

stock Karnet(playerid)
{
	if(gracz[playerid][karnet] > serwer[time_timestamp]) return 1;
	if(gracz[playerid][karnet] != 0)
	{
		LoadKarnetData(playerid);
	}
	return 0;
} 

CMD:givekarnet(playerid, params[])
{
	if(gracz[playerid][AdminLevel] < 4) return 0;
	new time = serwer[time_timestamp]+strval(params);
	CreateItemForPlayer(playerid, 67, 1, time, time);
	SendClientMessage(playerid, -1 , "OK!");
	return 1;
}
//NARZEDZIA POJAZD
Dialog:TOOLVEHSEL(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new v = strval(inputtext);
	if(pojazd[v][v_id])
	{
		if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
		{
			SetPVarInt(playerid, "world_toolvehsel", v);
			new tool_str[1024];
			format(tool_str, 1024, "Czynnoœæ\tWymagania iloœæ czêœci");
			format(tool_str, 1024, "%s\n"COL_WHITE"1."COL_PURPLE" PrzeprowadŸ diagnostykê\t"COL_ORANGE"-", tool_str);
			format(tool_str, 1024, "%s\n"COL_WHITE"2."COL_PURPLE" Remontuj uk³ad elektryczny\t"COL_ORANGE"%d czêœci", tool_str, VehNeed_uElektryczny(pojazd[v][v_model]));
			format(tool_str, 1024, "%s\n"COL_WHITE"3."COL_PURPLE" Remontuj uk³ad zasilania\t"COL_ORANGE"%d czêœci", tool_str, VehNeed_uZasilania(pojazd[v][v_model]));
			format(tool_str, 1024, "%s\n"COL_WHITE"4."COL_PURPLE" Remontuj uk³ad smarowania\t"COL_ORANGE"%d czêœci", tool_str, VehNeed_uSmarowania(pojazd[v][v_model]));
			format(tool_str, 1024, "%s\n"COL_WHITE"5."COL_PURPLE" Remontuj uk³ad ch³odzenia\t"COL_ORANGE"%d czêœci", tool_str, VehNeed_uChlodzenia(pojazd[v][v_model]));
			format(tool_str, 1024, "%s\n"COL_WHITE"6."COL_PURPLE" Remontuj uk³ad korbowy\t"COL_ORANGE"%d czêœci", tool_str, VehNeed_uKorbowy(pojazd[v][v_model]));
			format(tool_str, 1024, "%s\n"COL_WHITE"7."COL_PURPLE" Zmieñ sekwencje zap³onu (kodowanie)\t"COL_ORANGE"-", tool_str);
			format(tool_str, 1024, "%s\n"COL_WHITE"8."COL_PURPLE" Ustaw domyœln¹ sewkencje zap³onu (zdekodowanie)\t"COL_ORANGE"-", tool_str);
			Dialog_Show(playerid, TOOLVEHACTION, DIALOG_STYLE_TABLIST_HEADERS, "Co chcesz zrobiæ?", tool_str, "Wybierz", "Anuluj");
		}
		else
		{
			LeftNotifyShow(playerid, "error", "Pojazd jest za daleko.");
		}
	}
	return 1;
}

Dialog:TOOLVEHACTION(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new v = GetPVarInt(playerid, "world_toolvehsel");
	if(pojazd[v][v_id])
	{
		if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
		{
			SetPVarInt(playerid, "world_toolvehaction", listitem);
			switch(listitem)
			{
				case 0:
				{
					if(VehSkill(playerid, 4))
					{
						if(pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~r~zgaszony~w~ silnik.");
						else StartCombineMode(playerid, 9);
					}
				}
				case 1:
				{
					if(VehSkill(playerid, 5))
					{
						if(pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~r~zgaszony~w~ silnik.");
						else if(GetItemValueForPlayer(playerid, 69) < VehNeed_uElektryczny(pojazd[v][v_model])) LeftNotifyShow(playerid, "error", "Posiadasz zbyt malo czesci aby wyremontowac ten uklad.");
						else StartCombineMode(playerid, 9);
					}
				}
				case 2:
				{
					if(VehSkill(playerid, 6))
					{
						if(pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~r~zgaszony~w~ silnik.");
						else if(GetItemValueForPlayer(playerid, 70) < VehNeed_uZasilania(pojazd[v][v_model])) LeftNotifyShow(playerid, "error", "Posiadasz zbyt malo czesci aby wyremontowac ten uklad.");
						else StartCombineMode(playerid, 9);
					}
				}
				case 3:
				{
					if(VehSkill(playerid, 7))
					{
						if(pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~r~zgaszony~w~ silnik.");
						else if(GetItemValueForPlayer(playerid, 71) < VehNeed_uSmarowania(pojazd[v][v_model])) LeftNotifyShow(playerid, "error", "Posiadasz zbyt malo czesci aby wyremontowac ten uklad.");
						else StartCombineMode(playerid, 9);
					}
				}
				case 4:
				{
					if(VehSkill(playerid, 8))
					{
						if(pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~r~zgaszony~w~ silnik.");
						else if(GetItemValueForPlayer(playerid, 72) < VehNeed_uChlodzenia(pojazd[v][v_model])) LeftNotifyShow(playerid, "error", "Posiadasz zbyt malo czesci aby wyremontowac ten uklad.");
						else StartCombineMode(playerid, 9);
					}
				}
				case 5:
				{
					if(VehSkill(playerid, 9))
					{
						if(pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~r~zgaszony~w~ silnik.");
						else if(GetItemValueForPlayer(playerid, 73) < VehNeed_uKorbowy(pojazd[v][v_model])) LeftNotifyShow(playerid, "error", "Posiadasz zbyt malo czesci aby wyremontowac ten uklad.");
						else StartCombineMode(playerid, 9);
					}
				}
				case 6:
				{
					if(VehSkill(playerid, 11))
					{
						if(!pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~h~uruchomiony~w~ silnik.");
						else StartCombineMode(playerid, 14);
					}
				}
				case 7:
				{
					if(VehSkill(playerid, 11))
					{
						if(!pojazd[v][v_enginestatus]) LeftNotifyShow(playerid, "error", "Pojazd musi miec ~h~uruchomiony~w~ silnik.");
						else StartCombineMode(playerid, 15);
					}
				}
			}
		}
		else
		{
			LeftNotifyShow(playerid, "error", "Pojazd jest za daleko.");
		}
	}
	return 1;
}
//************************************************************************************************************************************************************************KRÓTKOFALÓWKA
stock LoadUsedKrotkofalowka(playerid)
{
	mq_format("SELECT `id` FROM `przedmioty` WHERE `itemid`='133' AND `userid`='%d' AND `used`='1' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("QKrotkofalowka", "d", playerid);
	return 1;
}

forward QKrotkofalowka(playerid);
public QKrotkofalowka(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		gracz[playerid][krotkofala] = true;
	}
	else
	{
		gracz[playerid][krotkofala] = false;
	}
	return 1;
}


Dialog:KROTKOFALOWKA(playerid, response, listitem, inputtext[])
{
  if(!response) return 1;
  switch(listitem)
  {
	case 0:
	{
	  if(eq_select[playerid][s_used])
	  {
		mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
		mysql_query(MySQL, mQuery, false);
		LeftNotifyShow(playerid, "Sukces!", "Krotkofalowka zostala ~r~wylaczona~w~.");    
	  }
	  else
	  {
		mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
		mysql_query(MySQL, mQuery, false);
		LeftNotifyShow(playerid, "Sukces!", "Krotkofalowka zostala ~g~wlaczona~w~.");   
	  }
	  LoadUsedKrotkofalowka(playerid);
	}
	case 1:
	{
	  new str_kr[512];
	  format(str_kr, 512, ""COL_GREY"Aktualna czêstotliwoœæ: "COL_YELLOW"%d"COL_GREY" MHz", gracz[playerid][KRMHZ]);
	  format(str_kr, 512, "%s\n"COL_GREY"(("COL_EASY"Domyœlna"COL_GREY" czêstotliwoœæ: "COL_GREEN"%d"COL_GREY" MHz))", str_kr, gracz[playerid][KRMHZ]);
	  format(str_kr, 512, "%s\n\n"COL_GREY"WprowadŸ now¹ czêstotliwoœæ("COL_GREEN"400 MHz"COL_GREY" - "COL_RED"500 MHz"COL_GREY"): ", str_kr, gracz[playerid][KRMHZ]);
	  Dialog_Show(playerid, FALOWKAMHZ, DIALOG_STYLE_INPUT, ""COL_BLUE"»"COL_GREY" Krótkofalówka", str_kr, "Ustaw", "Anuluj");  
	}
  }
  return 1;
}

Dialog:FALOWKAMHZ(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new mhz = strval(inputtext);
	switch(mhz)
	{
		case 400..500:
		{
			gracz[playerid][KRMHZ] = mhz;
			new str_kr[512];
			format(str_kr, 512, "~g~Zmieniono~w~ czestotliwosc na: ~y~%d~w~ MHz.", gracz[playerid][KRMHZ]);
			LeftNotifyShow(playerid, "Sukces!", str_kr);    
			mq_format("UPDATE `Konta` SET `KRMHZ`='%d' WHERE `id`='%d';", gracz[playerid][KRMHZ], gracz[playerid][UID]);
			mq_send("QMHzUpdate");
		}
		default:
		{
			dialog_KROTKOFALOWKA(playerid, 1, 1, "null");
			LeftNotifyShow(playerid, "error", "~y~Czestotliwosc~w~ musi sie miescic w zakresie ~g~400 MHz~w~ - ~r~500 MHz~w~.");  
		}
	}
	return 1;
}
//***********************************************************************NAPRAWA BRONI
Dialog:TOOLWEAPACTION(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	mq_format("SELECT `count`,`itemid` FROM `przedmioty` WHERE (`itemid`>='115' AND `itemid`<='119') AND `userid`='%d';", gracz[playerid][UID]);
	mq_send("QGetWeapParts", "d", playerid);
	return 1;
}

forward QGetWeapParts(playerid);
public QGetWeapParts(playerid)
{
	mq_getdata();
	new part_115, part_116, part_117, part_118, part_119;
	if(rekordy)
	{
		new i;
		while(i < rekordy)
		{
			switch(cache_get_field_content_int(i, "itemid"))
			{
				case 115:
				{
					part_115 = cache_get_field_content_int(i, "count");
				}
				case 116:
				{
					part_116 = cache_get_field_content_int(i, "count");
				}
				case 117:
				{
					part_117 = cache_get_field_content_int(i, "count");
				}
				case 118:
				{
					part_118 = cache_get_field_content_int(i, "count");
				}
				case 119:
				{
					part_119 = cache_get_field_content_int(i, "count");
				}
			}
			i++;
		}
	}
	if(GetWeaponCategory(gracz[playerid][actual_weapon]) == 0) return LeftNotifyShow(playerid, "error", "Musisz ~r~miec w reku bron~w~, na ktorej chcesz ~g~uzyc~w~ tych narzedzi.");
	if(part_115 < 1) return LeftNotifyShow(playerid, "error", "~r~Brakuje~w~ elementu broni: ~y~Zamek~w~.");
	if(part_116 < 1) return LeftNotifyShow(playerid, "error", "~r~Brakuje~w~ elementu broni: ~y~Sprezyna powrotna~w~.");
	if(part_117 < 1) return LeftNotifyShow(playerid, "error", "~r~Brakuje~w~ elementu broni: ~y~Nasada lufy~w~.");
	if(part_118 < 1) return LeftNotifyShow(playerid, "error", "~r~Brakuje~w~ elementu broni: ~y~Sprezyna spustu~w~.");
	if(part_119 < 1) return LeftNotifyShow(playerid, "error", "~r~Brakuje~w~ elementu broni: ~y~Spust~w~.");
	StartCombineMode(playerid, 13);
	return 1;
}

forward QDelWeapParts();
public QDelWeapParts()
{
	DelZeroItems();
	return 1;
}
//*************************************************************************************************************************************************************LICZNIK GEIGERA
#define GEIGER_NULL 0
#define GEIGER_ENABLE 1
#define GEIGER_DISABLE 2
#define GEIGER_WORK 3
forward Process_Geiger();
public Process_Geiger()
{
	new tick = GetTickCount();
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][geiger] == GEIGER_NULL) continue;
		switch(gracz[p][geiger])
		{
			case GEIGER_ENABLE:
			{
				gracz[p][geiger] = GEIGER_WORK;
				ShowGeigerTD(p);
			}
			case GEIGER_DISABLE:
			{
				gracz[p][geiger] = GEIGER_NULL;
				HideGeigerTD(p);
			}
			case GEIGER_WORK:
			{
				Geiger_SetUREMS(p, gracz[p][geiger_rads]);
				switch(gracz[p][geiger_rads])
				{
					case 250..800:
					{
						if(gracz[p][geiger_tick] > tick) continue;
						if(!gracz[p][geiger_led])
						{
							gracz[p][geiger_led] = true;
							Geiger_SetColorLED(p, 0xFF0000FF);
							PlayerPlaySound(p, 4203, 0.0, 0.0, 0.0);
						}
						else
						{
							gracz[p][geiger_led] = false;
							Geiger_SetColorLED(p, 0x000000FF);      
						}
						gracz[p][geiger_tick] = tick+60;
					}
					case 150..249:
					{
						if(gracz[p][geiger_tick] > tick) continue;
						if(!gracz[p][geiger_led])
						{
							gracz[p][geiger_led] = true;
							Geiger_SetColorLED(p, 0xff9a00FF);
							PlayerPlaySound(p, 4203, 0.0, 0.0, 0.0);
						}
						else
						{
							gracz[p][geiger_led] = false;
							Geiger_SetColorLED(p, 0x000000FF);      
						}
						gracz[p][geiger_tick] = tick+200;
					}
					case 130..149:
					{
						if(gracz[p][geiger_tick] > tick) continue;
						if(!gracz[p][geiger_led])
						{
							gracz[p][geiger_led] = true;
							Geiger_SetColorLED(p, 0xfdff00FF);
							PlayerPlaySound(p, 4203, 0.0, 0.0, 0.0);
						}
						else
						{
							gracz[p][geiger_led] = false;
							Geiger_SetColorLED(p, 0x000000FF);      
						}
						gracz[p][geiger_tick] = tick+400;
					}
					case 100..129:
					{
						if(gracz[p][geiger_tick] > tick) continue;
						if(!gracz[p][geiger_led])
						{
							gracz[p][geiger_led] = true;
							Geiger_SetColorLED(p, 0xd6ff00FF);
							PlayerPlaySound(p, 4203, 0.0, 0.0, 0.0);
						}
						else
						{
							gracz[p][geiger_led] = false;
							Geiger_SetColorLED(p, 0x000000FF);      
						}

						gracz[p][geiger_tick] = tick+600;
					}
					case 0..99:
					{
						if(gracz[p][geiger_tick] > tick) continue;
						if(!gracz[p][geiger_led])
						{
							gracz[p][geiger_led] = true;
							Geiger_SetColorLED(p, 0x49ff00FF);
						}
						else
						{
							gracz[p][geiger_led] = false;
							Geiger_SetColorLED(p, 0x000000FF);
						}
						gracz[p][geiger_tick] = tick+1000;
					}
				}
			}
		}
	}
	return 1;
}

stock LoadUsedGeiger(playerid)
{
	mq_format("SELECT `id` FROM `przedmioty` WHERE `itemid`='147' AND `userid`='%d' AND `used`='1' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("QGeigerLoad", "d", playerid);
	return 1;
}

forward QGeigerLoad(playerid);
public QGeigerLoad(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		gracz[playerid][geiger] = 1;
	}
	else
	{
		gracz[playerid][geiger] = 2;
	}
	return 1;
}

//GPS
Dialog:GPS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			if(eq_select[playerid][s_used])
			{
				mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
				mysql_query(MySQL, mQuery, false);
				LeftNotifyShow(playerid, "Sukces!", "GPS zostal ~r~wylaczony~w~.");    
			}
			else
			{
				mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
				mysql_query(MySQL, mQuery, false);
				LeftNotifyShow(playerid, "Sukces!", "GPS zostal ~g~wlaczony~w~.");   
			}
			LoadUsedGPS(playerid);
		}
		case 1:
		{
			new str_gps[512];
			format(str_gps, 512, ""COL_GREY"Podaj czêstotliwoœæ nadajnika.\nOsoby maj¹ce w³¹czone nadajniki i ustawion¹ t¹ sam¹ czêstotliwoœæ\nbêd¹ widoczne dla Ciebie na mapie, a Ty dla nich.");
			format(str_gps, 512, "%s\n"COL_GREY"Aktualna czêstotliwoœæ: "COL_YELLOW"%d"COL_GREY" Hz", str_gps, gracz[playerid][gps_hz]);
			format(str_gps, 512, "%s\n\n"COL_GREY"WprowadŸ now¹ czêstotliwoœæ("COL_GREEN"50 Hz"COL_GREY" - "COL_RED"1000 Hz"COL_GREY"): ", str_gps, gracz[playerid][KRMHZ]);
			Dialog_Show(playerid, GPSSET, DIALOG_STYLE_INPUT, ""COL_BLUE"»"COL_GREY" GPS", str_gps, "Ustaw", "Anuluj");  
		}
	}
	return 1;
}

Dialog:GPSSET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new gethz = strval(inputtext);
	switch(gethz)
	{
		case 50..1000:
		{
			gracz[playerid][gps_hz] = gethz;
			new str_gps[512];
			format(str_gps, 512, "~g~Zmieniono~w~ czestotliwosc na: ~y~%d~w~ Hz.", gracz[playerid][gps_hz]);
			LeftNotifyShow(playerid, "Sukces!", str_gps);    
			mq_format("UPDATE `Konta` SET `gps_hz`='%d' WHERE `id`='%d';", gracz[playerid][gps_hz], gracz[playerid][UID]);
			mq_send("QHzUpdate");
		}
		default:
		{
			dialog_GPS(playerid, 1, 1, "null");
			LeftNotifyShow(playerid, "error", "~y~Czestotliwosc~w~ musi sie miescic w zakresie ~g~50 Hz~w~ - ~r~1000 Hz~w~.");  
		}
	}
	return 1;
}

stock LoadUsedGPS(playerid)
{
	mq_format("SELECT `id` FROM `przedmioty` WHERE `itemid`='150' AND `userid`='%d' AND `used`='1' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("QGPSLoad", "d", playerid);
	return 1;
}

forward QGPSLoad(playerid);
public QGPSLoad(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		gracz[playerid][gps] = true;
	}
	else
	{
		gracz[playerid][gps] = false;
	}
	return 1;
}

Dialog:MEDYKTOOL(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new str[512];
	switch(listitem)
	{
		case 0:
		{
			if(MedSkill(playerid, 6))
			{
				SetPVarInt(playerid, "HealMode", listitem);
				format(str, 512, ""COL_GREY"WprowadŸ ID gracza którego chcesz uleczyæ ("COL_GREEN"Twoje ID: "COL_RED"%d"COL_GREY"):", playerid);
				Dialog_Show(playerid, MEDYKHEAL, DIALOG_STYLE_INPUT, ""COL_BLUE"Kogo chcesz uleczyæ?", str, "Ulecz!", "Anuluj");
			}
		}
		case 1:
		{
			if(MedSkill(playerid, 7))
			{
				SetPVarInt(playerid, "HealMode", listitem);
				format(str, 512, ""COL_GREY"WprowadŸ ID gracza którego chcesz uleczyæ ("COL_GREEN"Twoje ID: "COL_RED"%d"COL_GREY"):", playerid);
				Dialog_Show(playerid, MEDYKHEAL, DIALOG_STYLE_INPUT, ""COL_BLUE"Kogo chcesz uleczyæ?", str, "Ulecz!", "Anuluj");
			}
		}
		case 2:
		{
			if(MedSkill(playerid, 8))
			{
				SetPVarInt(playerid, "HealMode", listitem);
				format(str, 512, ""COL_GREY"WprowadŸ ID gracza którego chcesz uleczyæ ("COL_GREEN"Twoje ID: "COL_RED"%d"COL_GREY"):", playerid);
				Dialog_Show(playerid, MEDYKHEAL, DIALOG_STYLE_INPUT, ""COL_BLUE"Kogo chcesz uleczyæ?", str, "Ulecz!", "Anuluj");
			}
		}
		case 3:
		{
			if(MedSkill(playerid, 9))
			{
				SetPVarInt(playerid, "HealMode", listitem);
				format(str, 512, ""COL_GREY"WprowadŸ ID gracza którego chcesz uleczyæ ("COL_GREEN"Twoje ID: "COL_RED"%d"COL_GREY"):", playerid);
				Dialog_Show(playerid, MEDYKHEAL, DIALOG_STYLE_INPUT, ""COL_BLUE"Kogo chcesz uleczyæ?", str, "Ulecz!", "Anuluj");
			}
		}
		case 4:
		{
			if(MedSkill(playerid, 10)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 5:
		{
			if(MedSkill(playerid, 11)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 6:
		{
			if(MedSkill(playerid, 12)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 7:
		{
			if(MedSkill(playerid, 13)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 8:
		{
			if(MedSkill(playerid, 14)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 9:
		{
			if(MedSkill(playerid, 15)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 10:
		{
			if(MedSkill(playerid, 16)) SyropCraft(playerid, listitem, 0, 1);
		}
		case 11:
		{
			if(MedSkill(playerid, 17))
			{
				format(str, 512, ""COL_GREY"WprowadŸ ID gracza którego chcesz wybudziæ:", playerid);
				Dialog_Show(playerid, MEDYKUNBW, DIALOG_STYLE_INPUT, ""COL_BLUE"Kogo chcesz wybudziæ?", str, "WybudŸ!", "Anuluj");
			}
		}
	}
	return 1;
}

Dialog:MEDYKHEAL(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = strval(inputtext);
	if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Ten gracz jest za daleko.");
	SetPVarInt(playerid, "heal_targetid", targetid);
	StartCombineMode(playerid, 16);
	return 1;
}

Dialog:MEDYKUNBW(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = strval(inputtext);
	if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(!gracz[targetid][BWTime]) return Error(playerid, "Ten gracz nie ma BW.");
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Ten gracz jest za daleko.");
	SetPVarInt(playerid, "unbw_targetid", targetid);
	StartCombineMode(playerid, 18);
	return 1;
}

forward SyropCraft(playerid, syropid, step, begin_craft);
public SyropCraft(playerid, syropid, step, begin_craft)
{
	if(step == 0)
	{
		mq_format("SELECT `count`,`itemid` FROM `przedmioty` WHERE (`itemid`>='123' AND `itemid`<='132' OR `itemid`='95' OR `itemid`='96') AND `userid`='%d';", gracz[playerid][UID]);
		mq_send("SyropCraft", "dddd", playerid, syropid, 1, begin_craft);
	}
	else if(step == 1)//zasysanie materia³ów
	{
		new Woda,
		Mleko,
		Mut_warzywo,//123
		Korzen_ksadrowy,//124
		Necik_piegowaty,//125
		Zimnokwiat_piaszczysty,//126
		Krwawa_Lespedoza,//127
		Zmutowana_Lucerna,//128
		Zmutowany_Krwawnik,//129
		Dzika_Ankrecja,//130
		Xadricaria_srebrzysta,//131
		Kiew_wodnisty;//132
		mq_getdata();
		if(rekordy)
		{
			new i;
			while(i < rekordy)
			{
				switch(cache_get_field_content_int(i, "itemid"))
				{
					case 95:
					{
						Woda = cache_get_field_content_int(i, "count");
					}
					case 96:
					{
						Mleko = cache_get_field_content_int(i, "count");
					}
					case 123:
					{
						Mut_warzywo = cache_get_field_content_int(i, "count");
					}
					case 124:
					{
						Korzen_ksadrowy = cache_get_field_content_int(i, "count");
					}
					case 125:
					{
						Necik_piegowaty = cache_get_field_content_int(i, "count");
					}
					case 126:
					{
						Zimnokwiat_piaszczysty = cache_get_field_content_int(i, "count");
					}
					case 127:
					{
						Krwawa_Lespedoza = cache_get_field_content_int(i, "count");
					}
					case 128:
					{
						Zmutowana_Lucerna = cache_get_field_content_int(i, "count");
					}
					case 129:
					{
						Zmutowany_Krwawnik = cache_get_field_content_int(i, "count");
					}
					case 130:
					{
						Dzika_Ankrecja = cache_get_field_content_int(i, "count");
					}
					case 131:
					{
						Xadricaria_srebrzysta = cache_get_field_content_int(i, "count");
					}
					case 132:
					{
						Kiew_wodnisty = cache_get_field_content_int(i, "count");
					}
				}
				i++;
			}
		}
		#pragma unused Dzika_Ankrecja
		#pragma unused Korzen_ksadrowy
		switch(syropid)
		{
			case 4:
			{
				if(Mut_warzywo < 2) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~2 sztuk~w~: ~y~ Mut-warzywo~w~.");
				if(Zimnokwiat_piaszczysty < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Zimnokwiat piaszczysty~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 151, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop Haps 10~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'2' WHERE `itemid`='123' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='126' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
			case 5:
			{
				if(Mut_warzywo < 5) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~5 sztuk~w~: ~y~ Mut-warzywo~w~.");
				if(Zimnokwiat_piaszczysty < 2) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~2 sztuk~w~: ~y~Zimnokwiat piaszczysty~w~.");
				if(Necik_piegowaty < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Necik piegowaty~w~.");
				if(Woda < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Woda~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 152, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop Haps 25~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'5' WHERE `itemid`='123' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'2' WHERE `itemid`='126' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='125' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='95' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
			case 6:
			{
				if(Necik_piegowaty < 5) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~5 sztuk~w~: ~y~Necik piegowaty~w~.");
				if(Krwawa_Lespedoza < 4) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~4 sztuk~w~: ~y~Krwawa Lespedoza~w~.");
				if(Kiew_wodnisty < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Kiew wodnisty~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 153, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop Haps 50~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'5' WHERE `itemid`='125' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'4' WHERE `itemid`='127' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='132' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
			case 7:
			{
				if(Zmutowana_Lucerna < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Zmutowana Lucerna~w~.");
				if(Zmutowany_Krwawnik < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Zmutowany Krwawnik~w~.");
				if(Mleko < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Mleko~w~.");
				if(Krwawa_Lespedoza < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Krwawa Lespedoza~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 154, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop AntiRad 10~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='128' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='129' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='96' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='127' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
			case 8:
			{
				if(Zmutowana_Lucerna < 2) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~2 sztuk~w~: ~y~Zmutowana Lucerna~w~.");
				if(Zmutowany_Krwawnik < 2) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~2 sztuk~w~: ~y~Zmutowany Krwawnik~w~.");
				if(Mleko < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Mleko~w~.");
				if(Krwawa_Lespedoza < 2) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~2 sztuk~w~: ~y~Krwawa Lespedoza~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 155, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop AntiRad 25~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'2' WHERE `itemid`='128' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'2' WHERE `itemid`='129' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='96' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'2' WHERE `itemid`='127' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
			case 9:
			{
				if(Zmutowana_Lucerna < 5) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~5 sztuk~w~: ~y~Zmutowana Lucerna~w~.");
				if(Zmutowany_Krwawnik < 5) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~5 sztuk~w~: ~y~Zmutowany Krwawnik~w~.");
				if(Mleko < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Mleko~w~.");
				if(Krwawa_Lespedoza < 5) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~5 sztuk~w~: ~y~Krwawa Lespedoza~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 156, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop AntiRad 50~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'5' WHERE `itemid`='128' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'5' WHERE `itemid`='129' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='96' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'5' WHERE `itemid`='127' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
			case 10:
			{
				if(Xadricaria_srebrzysta < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Xadricaria srebrzysta~w~.");
				if(Woda < 1) return LeftNotifyShow(playerid, "error", "~r~Potrzebujesz ~g~1 sztuk~w~: ~y~Woda~w~.");
				if(!begin_craft)
				{
					if(CreateItemForPlayer(playerid, 157, 1, 2000, 2000))
					{
						LeftNotifyShow(playerid, "Sukces!", "~g~Stworzono~w~: ~y~Syrop na wytrzymalosc~w~.", LN_GREEN);
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='131' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE `itemid`='95' AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelPlayerPlants");
					}
				}
				else
				{
					SetPVarInt(playerid, "SyropCraft", syropid);
					StartCombineMode(playerid, 17);
				}
			}
		}
	}
	return 1;
}

forward QDelPlayerPlants();
public QDelPlayerPlants()
{
	DelZeroItems();
	return 1;
}
//AKCESORIA
stock LoadUsedAccessories(playerid)
{
	RemovePlayerAttachedObject(playerid, BANDANA_SLOT);
	RemovePlayerAttachedObject(playerid, OKULARY_SLOT);
	RemovePlayerAttachedObject(playerid, CZAPKA_SLOT);
	mq_format("SELECT `itemid` FROM `przedmioty` WHERE (`itemid`>='160' AND `itemid`<='202') AND `userid`='%d' AND `used`='1' LIMIT 0,3;", gracz[playerid][UID]);
	mq_send("QAkcesoria", "d", playerid);
	return 1;
}

forward QAkcesoria(playerid);
public QAkcesoria(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new t_itemid;
		while(i < rekordy)
		{
			t_itemid = cache_get_field_content_int(i, "itemid");
			AkcesoriaSet(playerid, t_itemid);
			i++;
		}
	}
	return 1;
}

stock AkcesoriaSet(playerid, item_id)
{
	//typ: 1 - bandany, 2 - okulary, 3 - czapki
	new typ;
	switch(item_id)
	{
		case 160..163: typ = 1;
		case 164..189: typ = 2;
		case 190..202: typ = 3;
	}
	mq_format("SELECT * FROM `akcesoria` WHERE `type`='%d' AND `userid`='%d' LIMIT 0,1;", typ, gracz[playerid][UID]);
	mq_send("QSetAkcesoria", "ddd", playerid, ObjectItem[item_id], typ);
	return 1;
}

forward QSetAkcesoria(playerid, model, typ);
public QSetAkcesoria(playerid, model, typ)
{
	mq_getdata();
	new aslot;
	new i;
	/*ao[playerid][aslot][ao_x] = 
	ao[playerid][aslot][ao_y] =  
	ao[playerid][aslot][ao_z] =  
	ao[playerid][aslot][ao_rx] = 
	ao[playerid][aslot][ao_ry] = 
	ao[playerid][aslot][ao_rz] = 
	ao[playerid][aslot][ao_sx] = 
	ao[playerid][aslot][ao_sy] = 
	ao[playerid][aslot][ao_sz] = 
	ao[playerid][aslot][ao_typ] = */
	switch(typ)
	{
		case 1: 
		{
			aslot = BANDANA_SLOT;
			ao[playerid][aslot][ao_x] = 0.078534;
			ao[playerid][aslot][ao_y] = 0.041857;
			ao[playerid][aslot][ao_z] = -0.001727;
			ao[playerid][aslot][ao_rx] = 268.970458;
			ao[playerid][aslot][ao_ry] = 1.533374;
			ao[playerid][aslot][ao_rz] = 269.223754;
			ao[playerid][aslot][ao_sx] = 1.0;
			ao[playerid][aslot][ao_sy] = 1.0;
			ao[playerid][aslot][ao_sz] = 1.0;
		}
		case 2:
		{
			aslot = OKULARY_SLOT;
			ao[playerid][aslot][ao_x] = 0.093999;
			ao[playerid][aslot][ao_y] = 0.036000;
			ao[playerid][aslot][ao_z] = 0.003000;
			ao[playerid][aslot][ao_rx] = 0.000000;
			ao[playerid][aslot][ao_ry] = 84.600028;
			ao[playerid][aslot][ao_rz] = 91.200012;
			ao[playerid][aslot][ao_sx] = 1.0;
			ao[playerid][aslot][ao_sy] = 1.0;
			ao[playerid][aslot][ao_sz] = 1.0;
		} 
		case 3: 
		{
			aslot = CZAPKA_SLOT;
			if(model == 18953 || model == 18954)
			{
				ao[playerid][aslot][ao_x] = 0.112000;
				ao[playerid][aslot][ao_y] = 0.019999;
				ao[playerid][aslot][ao_z] = 0.000000;
				ao[playerid][aslot][ao_rx] = 0.000000;
				ao[playerid][aslot][ao_ry] = 0.000000;
				ao[playerid][aslot][ao_rz] = 0.000000;
			}
			else if(model == 18939 || model == 18940 || model == 18941 || model == 18942 || model == 18943)
			{
				ao[playerid][aslot][ao_x] = 0.157999;
				ao[playerid][aslot][ao_y] =  0.000000;
				ao[playerid][aslot][ao_z] =  0.000000;
				ao[playerid][aslot][ao_rx] = -171.599945;
				ao[playerid][aslot][ao_ry] = 0.000000;
				ao[playerid][aslot][ao_rz] = 0.000000;
			}
			else if(18951 >= model >= 18946)//kapelusze
			{
				ao[playerid][aslot][ao_x] = 0.112000;
				ao[playerid][aslot][ao_y] = 0.019999;
				ao[playerid][aslot][ao_z] = 0.000000;
				ao[playerid][aslot][ao_rx] = 0.000000;
				ao[playerid][aslot][ao_ry] = 0.000000;
				ao[playerid][aslot][ao_rz] = 0.000000;
			}
			ao[playerid][aslot][ao_sx] = 1.0;
			ao[playerid][aslot][ao_sy] = 1.0;
			ao[playerid][aslot][ao_sz] = 1.0;
		}
	}
	ao[playerid][aslot][ao_typ] = typ;
	if(rekordy)
	{
		ao[playerid][aslot][ao_x] = cache_get_field_content_float(0, "ao_x");
		ao[playerid][aslot][ao_y] = cache_get_field_content_float(0, "ao_y");
		ao[playerid][aslot][ao_z] = cache_get_field_content_float(0, "ao_z");
		ao[playerid][aslot][ao_rx] = cache_get_field_content_float(0, "ao_rx");
		ao[playerid][aslot][ao_ry] = cache_get_field_content_float(0, "ao_ry");
		ao[playerid][aslot][ao_rz] = cache_get_field_content_float(0, "ao_rz");
		ao[playerid][aslot][ao_sx] = cache_get_field_content_float(0, "ao_sx");
		ao[playerid][aslot][ao_sy] = cache_get_field_content_float(0, "ao_sy");
		ao[playerid][aslot][ao_sz] = cache_get_field_content_float(0, "ao_sz");
		i = aslot;
		SetPlayerAttachedObject(playerid, aslot, model, 2, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
		//EditAttachedObject(playerid, i);
	}
	else 
	{
		i = aslot;
		SetPlayerAttachedObject(playerid, aslot, model, 2, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
		mq_format("INSERT INTO `akcesoria` VALUES (NULL, '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f');", gracz[playerid][UID], typ, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
		mq_send("QInsertAkcesoria");
	}
	return 1;
}

Dialog:BANDANACONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
			mysql_query(MySQL, mQuery, false);
			LeftNotifyShow(playerid, "Sukces!", "Bandana zdjeta.");
			RemovePlayerAttachedObject(playerid, BANDANA_SLOT);
		}
		case 1:
		{
			ao[playerid][BANDANA_SLOT][ao_typ] = 1;
			EditAttachedObject(playerid, BANDANA_SLOT);
		}
		case 2:
		{
			mq_format("DELETE FROM `akcesoria` WHERE `userid`='%d' AND `type`='1';", gracz[playerid][UID]);
			mq_send("QAkcesoriaReset", "d", playerid);
		}
	}
 	return 1;
}

Dialog:OKULARYCONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
			mysql_query(MySQL, mQuery, false);
			LeftNotifyShow(playerid, "Sukces!", "Okulary zdjete.");
			RemovePlayerAttachedObject(playerid, OKULARY_SLOT);
		}
		case 1:
		{
			ao[playerid][OKULARY_SLOT][ao_typ] = 2;
			EditAttachedObject(playerid, OKULARY_SLOT);
		}
		case 2:
		{
			mq_format("DELETE FROM `akcesoria` WHERE `userid`='%d' AND `type`='2';", gracz[playerid][UID]);
			mq_send("QAkcesoriaReset", "d", playerid);
		}
	}
 	return 1;
}

Dialog:CZAPKACONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
			mysql_query(MySQL, mQuery, false);
			LeftNotifyShow(playerid, "Sukces!", "Czapka zdjeta.");
			RemovePlayerAttachedObject(playerid, CZAPKA_SLOT);
		}
		case 1:
		{
			ao[playerid][CZAPKA_SLOT][ao_typ] = 3;
			EditAttachedObject(playerid, CZAPKA_SLOT);
		}
		case 2:
		{
			mq_format("DELETE FROM `akcesoria` WHERE `userid`='%d' AND `type`='3';", gracz[playerid][UID]);
			mq_send("QAkcesoriaReset", "d", playerid);
		}
	}
 	return 1;
}


forward QAkcesoriaReset(playerid);
public QAkcesoriaReset(playerid)
{
	LoadUsedAccessories(playerid);
	return 1;
}