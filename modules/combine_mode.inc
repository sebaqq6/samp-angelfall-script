#define CKEY_UP 1
#define CKEY_DOWN 2
#define CKEY_LEFT 3
#define CKEY_RIGHT 4


forward  StartCombineMode(playerid, cid);
public StartCombineMode(playerid, cid)
{
	if(combine_mode[playerid][c_id]) return 0;
	combine_mode[playerid][c_id] = cid;
	combine_mode[playerid][c_step] = 0;
	combine_mode[playerid][c_mode] = 0;
	combine_mode[playerid][c_bad] = 0;
	switch(combine_mode[playerid][c_id])
	{
		case 1:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "laweczka");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Ilosc powtorzen: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_LAWECZKA);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 2:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "hantle");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Ilosc powtorzen: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_HANTLE);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 3:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "bieznia");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Pokonany dystans: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_BIEZNIA);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 4:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "rowerek");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Pokonany dystans: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_ROWERYK);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 5://odpalanie pojazdu - niezakodowany - jawne
		{
			CombineTD_Title(playerid, "odpalanie pojazdu");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "_");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 6://odpalanie pojazdu - zakodowany - niejawne
		{
			CombineTD_Title(playerid, "odpalanie pojazdu");
			CombineTD_Tip(playerid, "~w~((Wprowadz ~y~tajna kombinacje~w~. Uzyj ~p~strzalek~w~.))");
			CombineTD_Left(playerid, "Ten pojazd jest ~r~zakodowany~w~! Uzyj ~p~strzalek~w~, aby~n~wprowadzic odpowiednia kombinacje i ~g~odpalic~w~ pojazd.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			combine_mode[playerid][c_mode] = 1;
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 7:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "uzupelnianie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~blad~w~, ~r~przerwiesz~w~ uzupelnianie.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 8:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "uzupelnianie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~blad~w~, ~r~przerwiesz~w~ uzupelnianie.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 9:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "uzywanie narzedzi");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~3 razy blad~w~, ~r~przerwiesz~w~ akcje.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "~g~0~w~/~r~10");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 10:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "tankowanie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~blad~w~, ~r~przerwiesz~w~ tankowanie.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 11:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "gotowanie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~blad~w~, ~r~przerwiesz~w~ gotowanie.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 12:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "uzywanie przedmiotu");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~blad~w~, ~r~przerwiesz~w~ akcje.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 13:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "uzywanie narzedzi");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~3 razy blad~w~, ~r~przerwiesz~w~ akcje.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "~g~0~w~/~r~10");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 14:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "ustawianie sekwencji");
			CombineTD_Tip(playerid, "((Podaj swoja sekwencje zaplonu wymagana do odpalenia pojazdu.))");
			CombineTD_Left(playerid, "Podana przez Ciebie sekwencja bedzie wymagana~n~do odpalenia pojazdu.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			combine_mode[playerid][c_mode] = 2;
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 15:
		{
			GenerateCombine(playerid, 1);
			CombineTD_Title(playerid, "ustawianie sekwencji");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Ta operacja ustawi domyslna sekwencje zaplonu.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 16:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "leczenie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~3 razy blad~w~, ~r~przerwiesz~w~ akcje.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "~g~0~w~/~r~10");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 17:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "tworzenie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~3 razy blad~w~, ~r~przerwiesz~w~ akcje.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "~g~0~w~/~r~10");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
		case 18:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "leczenie");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			CombineTD_Left(playerid, "Jesli popelnisz ~y~3 razy blad~w~, ~r~przerwiesz~w~ akcje.");
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "~g~0~w~/~r~10");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
			TogglePlayerControllable(playerid, false);
		}
	}
	return 1;
}

stock StopCombineMode(playerid)
{
	combine_mode[playerid][c_id] = 0;
	HideCombineTD(playerid);
	return 1;
}

stock InCombineMode(playerid) return combine_mode[playerid][c_id];

stock Process_CombineMode(playerid)
{
	if(!combine_mode[playerid][c_id]) return 0;
	switch(combine_mode[playerid][c_id])
	{
		case 1:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					if(gracz[playerid][kondycja] > 30)
					{
						BENCH_UP(playerid);
						gracz[playerid][kondycja] -= 30;
						combine_mode[playerid][c_step] = 3;
					}
					else
					{
						combine_mode[playerid][c_step] = 4;
						LeftNotifyShow(playerid, "error", "~r~Zwolnij~w~ kowboju! Daj swojej postaci troche ~g~odpoczac~w~.", LN_RED);
					}
					ShowCombineTD(playerid);
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					BENCH_DOWN(playerid);
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 4;
				}
			}
			else if(combine_mode[playerid][c_step] == 3)
			{
				GenerateCombine(playerid, 2);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 2;
			}
			else if(combine_mode[playerid][c_step] == 4)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 2:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					if(gracz[playerid][kondycja] > 30)
					{
						DUMB_UP(playerid);
						gracz[playerid][kondycja] -= 30;
						combine_mode[playerid][c_step] = 3;
					}
					else
					{
						combine_mode[playerid][c_step] = 4;
						LeftNotifyShow(playerid, "error", "~r~Zwolnij~w~ kowboju! Daj swojej postaci troche ~g~odpoczac~w~.", LN_RED);
					}
					ShowCombineTD(playerid);
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					DUMB_DOWN(playerid);
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 4;
				}
			}
			else if(combine_mode[playerid][c_step] == 3)
			{
				GenerateCombine(playerid, 2);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 2;
			}
			else if(combine_mode[playerid][c_step] == 4)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 3:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					if(gracz[playerid][kondycja] > 15)
					{
						gracz[playerid][kondycja] -= 15;
						TREAM_RUN(playerid);
					}
					else
					{
						LeftNotifyShow(playerid, "error", "~r~Zwolnij~w~ kowboju! Daj swojej postaci troche ~g~odpoczac~w~.", LN_RED);
					}
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 2;
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 4:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					if(gracz[playerid][kondycja] > 15)
					{
						gracz[playerid][kondycja] -= 15;
						BIKE_RUN(playerid);
					}
					else
					{
						LeftNotifyShow(playerid, "error", "~r~Zwolnij~w~ kowboju! Daj swojej postaci troche ~g~odpoczac~w~.", LN_RED);
					}
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 2;
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 5:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					ToggleEngine(GetPVarInt(playerid, "world_vehicleid"), 1);
					StopCombineMode(playerid);
					PC_EmulateCommand(playerid, "/me uruchamia silnik.");
					LeftNotifyShow(playerid, "info", "Silnik zostal ~g~uruchomiony~w~.");
				}
			}
		}
		case 6:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					ToggleEngine(GetPVarInt(playerid, "world_vehicleid"), 1);
					StopCombineMode(playerid);
					PC_EmulateCommand(playerid, "/me uruchamia silnik.");
					LeftNotifyShow(playerid, "info", "Silnik zostal ~g~uruchomiony~w~.");
				}
			}
		}
		case 7:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad])
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ uzupelnianie ~y~kanistra~w~.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					StopCombineMode(playerid);
					TogglePlayerControllable(playerid, true);
					if(RemoveItemFromPlayer(playerid, 54, 1))
					{
						CreateItemForPlayer(playerid, 55, 1);
						PC_EmulateCommand(playerid, "/me uzupe³nia kanister.");
						LeftNotifyShow(playerid, "info", "~y~Kanister~w~ zostal ~g~uzupelniony~w~.");
					}
				}
			}
		}
		case 8:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad])
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ uzupelnianie ~y~paliwa~w~ pojezdzie.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					StopCombineMode(playerid);
					TogglePlayerControllable(playerid, true);
					new v = GetPVarInt(playerid, "world_vehrefuel");
					if(pojazd[v][v_id])
					{
						if(!pojazd[v][v_enginestatus] && pojazd[v][v_paliwo] != 1000)
						{
							if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
							{
								if(RemoveItemFromPlayer(playerid, 55, 1))
								{
									CreateItemForPlayer(playerid, 54, 1);
									new cmd_str[64];
									format(cmd_str, 64, "/me zatankowal pojazd '%s'.", GetVehicleName(pojazd[v][v_model]));
									PC_EmulateCommand(playerid, cmd_str);
									pojazd[v][v_paliwo] += 300;
									LeftNotifyShow(playerid, "info", "~y~Pojazd~w~ zostal ~g~zatankowany~w~.");
								}
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
				}
			}
		}
		case 9:
		{
			if(combine_mode[playerid][c_step])
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad] >= 3)
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ akcje.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					GenerateCombine(playerid);
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_step] < 10)
					{
						combine_mode[playerid][c_step]++;
					}
					else
					{
						StopCombineMode(playerid);
						TogglePlayerControllable(playerid, true);
						new v = GetPVarInt(playerid, "world_toolvehsel");
						if(pojazd[v][v_id])
						{
							if(!pojazd[v][v_enginestatus])
							{
								if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
								{
									switch(GetPVarInt(playerid, "world_toolvehaction"))
									{
										case 0:
										{
											new tool_str[1024];
											format(tool_str, 1024, "Uk³ad\tKondycja");
											format(tool_str, 1024, "%s\n"COL_WHITE"»"COL_BLUE" Uk³ad elektryczny\t%s", tool_str, text_bar(procent(pojazd[v][v_uElektryczny], WORLDV_UELEKT)));
											format(tool_str, 1024, "%s\n"COL_WHITE"»"COL_BLUE" Uk³ad zasilania\t%s", tool_str, text_bar(procent(pojazd[v][v_uZasilania], WORLDV_ZASIL)));
											format(tool_str, 1024, "%s\n"COL_WHITE"»"COL_BLUE" Uk³ad smarowania\t%s", tool_str, text_bar(procent(pojazd[v][v_uSmarowania], WORLDV_SMAR)));
											format(tool_str, 1024, "%s\n"COL_WHITE"»"COL_BLUE" Uk³ad ch³odzenia\t%s", tool_str, text_bar(procent(pojazd[v][v_uChlodzenia], WORLDV_CHLOD)));
											format(tool_str, 1024, "%s\n"COL_WHITE"»"COL_BLUE" Uk³ad korbowy\t%s", tool_str, text_bar(procent(pojazd[v][v_uKorbowy], WORLDV_KORB)));
											format(tool_str, 1024, "%s\n"COL_WHITE"»"COL_BLUE" Paliwo\t%s", tool_str, text_bar(procent(pojazd[v][v_paliwo], 1000)));
											ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "Wynik diagonostyki pojazdu:", tool_str, "OK", "");
											LeftNotifyShow(playerid, "Sukces!", "~y~Diagnostyka zakonczona~w~.", LN_GREEN);
										}
										case 1:
										{
											if(RemoveItemFromPlayer(playerid, 69, VehNeed_uElektryczny(pojazd[v][v_model])))
											{
												new cmd_str[128];
												format(cmd_str, 128, "/me zakoñczy³ remont uk³adu elektrycznego dla pojazdu '%s'.", GetVehicleName(pojazd[v][v_model]));
												PC_EmulateCommand(playerid, cmd_str);
												pojazd[v][v_uElektryczny] = WORLDV_UELEKT;
												LeftNotifyShow(playerid, "Sukces!", "~y~Uklad elektryczny~w~ zostal ~g~wyremontowany~w~.", LN_GREEN);
											}
										}
										case 2:
										{
											if(RemoveItemFromPlayer(playerid, 70, VehNeed_uZasilania(pojazd[v][v_model])))
											{
												new cmd_str[128];
												format(cmd_str, 128, "/me zakoñczy³ remont uk³adu zasilania dla pojazdu '%s'.", GetVehicleName(pojazd[v][v_model]));
												PC_EmulateCommand(playerid, cmd_str);
												pojazd[v][v_uZasilania] = WORLDV_ZASIL;
												LeftNotifyShow(playerid, "Sukces!", "~y~Uklad zasilania~w~ zostal ~g~wyremontowany~w~.", LN_GREEN);
											}
										}
										case 3:
										{
											if(RemoveItemFromPlayer(playerid, 71, VehNeed_uSmarowania(pojazd[v][v_model])))
											{
												new cmd_str[128];
												format(cmd_str, 128, "/me zakoñczy³ remont uk³adu smarowania dla pojazdu '%s'.", GetVehicleName(pojazd[v][v_model]));
												PC_EmulateCommand(playerid, cmd_str);
												pojazd[v][v_uSmarowania] = WORLDV_SMAR;
												LeftNotifyShow(playerid, "Sukces!", "~y~Uklad smarowania~w~ zostal ~g~wyremontowany~w~.", LN_GREEN);
											}
										}
										case 4:
										{
											if(RemoveItemFromPlayer(playerid, 72, VehNeed_uChlodzenia(pojazd[v][v_model])))
											{
												new cmd_str[128];
												format(cmd_str, 128, "/me zakoñczy³ remont uk³adu ch³odzenia dla pojazdu '%s'.", GetVehicleName(pojazd[v][v_model]));
												PC_EmulateCommand(playerid, cmd_str);
												pojazd[v][v_uChlodzenia] = WORLDV_CHLOD;
												LeftNotifyShow(playerid, "Sukces!", "~y~Uklad chlodzenia~w~ zostal ~g~wyremontowany~w~.", LN_GREEN);
											}
										}
										case 5:
										{
											if(RemoveItemFromPlayer(playerid, 73, VehNeed_uKorbowy(pojazd[v][v_model])))
											{
												new cmd_str[128];
												format(cmd_str, 128, "/me zakoñczy³ remont uk³adu korbowego dla pojazdu '%s'.", GetVehicleName(pojazd[v][v_model]));
												PC_EmulateCommand(playerid, cmd_str);
												pojazd[v][v_uKorbowy] = WORLDV_KORB;
												LeftNotifyShow(playerid, "Sukces!", "~y~Uklad korbowy~w~ zostal ~g~wyremontowany~w~.", LN_GREEN);
											}
										}
									}
								}
								else
								{
									LeftNotifyShow(playerid, "error", "Pojazd jest za daleko.");
								}
							}
							else
							{
								LeftNotifyShow(playerid, "error", "Pojazd nie ma ~r~zgaszonego~w~ silnika.");
							}
						}
					}
					new str_beside[16];
					format(str_beside, 16, "~g~%d~w~/~r~10", combine_mode[playerid][c_step]-1);
					CombineTD_Beside(playerid, str_beside);
				}
			}
		}
		case 10:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad])
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ tankowanie ~y~pojazdu~w~.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					StopCombineMode(playerid);
					TogglePlayerControllable(playerid, true);
					new v = GetPVarInt(playerid, "world_vehrefuel");
					if(pojazd[v][v_id])
					{
						if(!pojazd[v][v_enginestatus] && pojazd[v][v_paliwo] != 1000)
						{
							if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
							{
								new cmd_str[64];
								format(cmd_str, 64, "/me tankuje pojazd '%s'.", GetVehicleName(pojazd[v][v_model]));
								PC_EmulateCommand(playerid, cmd_str);
								pojazd[v][v_paliwo] = 1000;
								LeftNotifyShow(playerid, "info", "~y~Pojazd~w~ zostal ~g~zatankowany~w~.");
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
				}
			}
		}
		case 11:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad])
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ gotowanie ~y~jedzenia~w~.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					StopCombineMode(playerid);
					TogglePlayerControllable(playerid, true);
					new food_uid = GetPVarInt(playerid, "food_uid");
					new food_itemid = GetPVarInt(playerid, "food_itemid");
					switch(food_itemid)
					{
						case 78:
						{
							if(CreateItemForPlayer(playerid, 79, 1))
							{
								RemoveItemFromPlayerEx(playerid, food_uid, 1);
								new cmd_str[64];
								format(cmd_str, 64, "/me gotuje '%s'.", ItemName[food_itemid]);
								PC_EmulateCommand(playerid, cmd_str);
								LeftNotifyShow(playerid, "info", "~y~Jedzenie~w~ zostalo ~g~ugotowane~w~.");
							}
						}
						case 80:
						{
							if(CreateItemForPlayer(playerid, 81, 1))
							{
								RemoveItemFromPlayerEx(playerid, food_uid, 1);
								new cmd_str[64];
								format(cmd_str, 64, "/me gotuje '%s'.", ItemName[food_itemid]);
								PC_EmulateCommand(playerid, cmd_str);
								LeftNotifyShow(playerid, "info", "~y~Jedzenie~w~ zostalo ~g~ugotowane~w~.");
							}	
						}
					}
				}
			}
		}
		case 12:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad])
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ uzywanie przedmiotu na innym ~y~graczu~w~.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					StopCombineMode(playerid);
					TogglePlayerControllable(playerid, true);
					new remoteuseitem_itemid = GetPVarInt(playerid, "remoteuseitem_itemid");
					new remoteuseitem_itemuid = GetPVarInt(playerid, "remoteuseitem_itemuid");
					new remoteuseitem_targetid = GetPVarInt(playerid, "remoteuseitem_targetid");
					if(!gracz[remoteuseitem_targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
					if(!IsPlayerInRangeOfPoint(playerid, 3.0, gracz[remoteuseitem_targetid][PosX], gracz[remoteuseitem_targetid][PosY], gracz[remoteuseitem_targetid][PosZ])) return Error(playerid, "Ten gracz jest za daleko.");
					UseRemoteItem(playerid, remoteuseitem_targetid, remoteuseitem_itemid, remoteuseitem_itemuid);
				}
			}
		}
		case 13:
		{
			if(combine_mode[playerid][c_step])
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad] >= 3)
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ akcje.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					GenerateCombine(playerid);
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_step] < 10)
					{
						combine_mode[playerid][c_step]++;
					}
					else
					{
						StopCombineMode(playerid);
						TogglePlayerControllable(playerid, true);
						if(GetWeaponCategory(gracz[playerid][actual_weapon]) == 0) return LeftNotifyShow(playerid, "error", "Musisz ~r~miec w reku bron~w~, na ktorej chcesz ~g~uzyc~w~ tych narzedzi.");
						mq_format("UPDATE `przedmioty` SET `count`=`count`-'1' WHERE (`itemid`>='115' AND `itemid`<='119') AND `userid`='%d';", gracz[playerid][UID]);
						mq_send("QDelWeapParts");
						w_cdn[playerid][gracz[playerid][actual_weapon]] = w_cdn_max[playerid][gracz[playerid][actual_weapon]];
						SyncWeaponCDNToEQ(playerid);
						LeftNotifyShow(playerid, "Sukces!", "~y~Bron~w~ zostala ~g~wyremontowana~w~.", LN_GREEN);
						new cmd_str[64];
						format(cmd_str, 64, "/me zakoñczy³/a remont broni '%s'.", ItemName[gracz[playerid][actual_weapon]]);
						PC_EmulateCommand(playerid, cmd_str);
						RefreshAmmo(playerid);
					}
					new str_beside[16];
					format(str_beside, 16, "~g~%d~w~/~r~10", combine_mode[playerid][c_step]-1);
					CombineTD_Beside(playerid, str_beside);
				}
			}
		}
		case 14:
		{
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					combine_mode[playerid][c_mode] = 0;
					combine_mode[playerid][c_qkey] = 0;
					CombineTD_Left(playerid, "~g~Wprowadz~w~ drugi raz podana przez Ciebie kombinacje. Aby~n~zatwierdzic.");
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 2;
				}
			}
			if(combine_mode[playerid][c_step] == 2)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad])
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ ustawianie sekwencji. Wprowadzona drugi raz przez Ciebie kombinacja byla ~r~bledna~w~.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					StopCombineMode(playerid);
					TogglePlayerControllable(playerid, true);
					new v = GetPVarInt(playerid, "world_toolvehsel");
					if(pojazd[v][v_id])
					{
						if(pojazd[v][v_enginestatus])
						{
							if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
							{
								new combine_str[64];
								for(new k; k < 6; k++)
								{
									if(combine_mode[playerid][c_key][k] == CKEY_LEFT) format(combine_str, 64, "%s|lewo", combine_str);
									else if(combine_mode[playerid][c_key][k] == CKEY_RIGHT) format(combine_str, 64, "%s|prawo", combine_str);
									else if(combine_mode[playerid][c_key][k] == CKEY_UP) format(combine_str, 64, "%s|góra", combine_str);
									else if(combine_mode[playerid][c_key][k] == CKEY_DOWN) format(combine_str, 64, "%s|dó³", combine_str);
								}
								SendClientMessageEx(playerid, -1, ""COL_GREY"Teraz, aby "COL_GREEN"uruchomiæ silnik"COL_GREY", wymagana jest kombinacja: "COL_PURPLE"%s|"COL_GREY".", combine_str);
								SetVehicleCombine(v, combine_mode[playerid][c_key][0], combine_mode[playerid][c_key][1], combine_mode[playerid][c_key][2], combine_mode[playerid][c_key][3], combine_mode[playerid][c_key][4], combine_mode[playerid][c_key][5]);
							}
							else
							{
								LeftNotifyShow(playerid, "error", "Pojazd jest za daleko.");
							}
						}
						else
						{
							LeftNotifyShow(playerid, "error", "Pojazd musi miec ~h~uruchomiony~w~ silnik.");
						}
					}
				}
			}
		}
		case 15:
		{
			if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
			{
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				if(combine_mode[playerid][c_bad])
				{
					TogglePlayerControllable(playerid, true);
					StopCombineMode(playerid);
					LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ ustawianie sekwencji. Wcisnieto zly klawisz.");
				}
			}
			else//gdy kombinacja zostaje wykonana
			{
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				StopCombineMode(playerid);
				TogglePlayerControllable(playerid, true);
				new v = GetPVarInt(playerid, "world_toolvehsel");
				if(pojazd[v][v_id])
				{
					if(pojazd[v][v_enginestatus])
					{
						if(IsPlayerInRangeOfPoint(playerid, WORLDV_DDISTANCE, pojazd[v][v_temp_X], pojazd[v][v_temp_Y], pojazd[v][v_temp_Z]))
						{
							new combine_str[64];
							for(new k; k < 6; k++)
							{
								if(combine_mode[playerid][c_key][k] == CKEY_LEFT) format(combine_str, 64, "%s|lewo", combine_str);
								else if(combine_mode[playerid][c_key][k] == CKEY_RIGHT) format(combine_str, 64, "%s|prawo", combine_str);
								else if(combine_mode[playerid][c_key][k] == CKEY_UP) format(combine_str, 64, "%s|góra", combine_str);
								else if(combine_mode[playerid][c_key][k] == CKEY_DOWN) format(combine_str, 64, "%s|dó³", combine_str);
							}
							SendClientMessageEx(playerid, -1, ""COL_GREY"Teraz, aby "COL_GREEN"uruchomiæ silnik"COL_GREY", wymagana jest kombinacja: "COL_PURPLE"%s|"COL_GREY".", combine_str);
							SetVehicleCombine(v, combine_mode[playerid][c_key][0], combine_mode[playerid][c_key][1], combine_mode[playerid][c_key][2], combine_mode[playerid][c_key][3], combine_mode[playerid][c_key][4], combine_mode[playerid][c_key][5]);
						}
						else
						{
							LeftNotifyShow(playerid, "error", "Pojazd jest za daleko.");
						}
					}
					else
					{
						LeftNotifyShow(playerid, "error", "Pojazd musi miec ~h~uruchomiony~w~ silnik.");
					}
				}
			}	
		}
		case 16:
		{
			if(combine_mode[playerid][c_step])
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad] >= 3)
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ akcje.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					GenerateCombine(playerid);
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_step] < 10)
					{
						combine_mode[playerid][c_step]++;
					}
					else
					{
						StopCombineMode(playerid);
						TogglePlayerControllable(playerid, true);
						new targetid = GetPVarInt(playerid, "heal_targetid");
						if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
						if(!IsPlayerInRangeOfPoint(playerid, 3.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Ten gracz jest za daleko.");
						new str_cmd[128];
						format(str_cmd, 128, "/me leczy '%s'.", nick(targetid));
						PC_EmulateCommand(playerid, str_cmd);
						switch(GetPVarInt(playerid, "HealMode"))
						{
							case 0:
							{
								GivePlayerHP(targetid, 5);
								LeftNotifyShow(playerid, "Sukces!", "~g~Przywrocono~w~ dla gracza ~y~5~w~ HP.", LN_GREEN);
							}
							case 1:
							{
								GivePlayerHP(targetid, 10);
								LeftNotifyShow(playerid, "Sukces!", "~g~Przywrocono~w~ dla gracza ~y~10~w~ HP.", LN_GREEN);
							}
							case 2:
							{
								GivePlayerHP(targetid, 20);
								LeftNotifyShow(playerid, "Sukces!", "~g~Przywrocono~w~ dla gracza ~y~20~w~ HP.", LN_GREEN);
							}
							case 3:
							{
								GivePlayerHP(targetid, 80);
								LeftNotifyShow(playerid, "Sukces!", "~g~Przywrocono~w~ dla gracza ~y~80~w~ HP.", LN_GREEN);
							}
						}
					}
					new str_beside[16];
					format(str_beside, 16, "~g~%d~w~/~r~10", combine_mode[playerid][c_step]-1);
					CombineTD_Beside(playerid, str_beside);
				}
			}
		}
		case 17:
		{
			if(combine_mode[playerid][c_step])
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad] >= 3)
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ akcje.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					GenerateCombine(playerid);
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_step] < 10)
					{
						combine_mode[playerid][c_step]++;
					}
					else
					{
						StopCombineMode(playerid);
						TogglePlayerControllable(playerid, true);
						SyropCraft(playerid, GetPVarInt(playerid, "SyropCraft"), 0, 0);
					}
					new str_beside[16];
					format(str_beside, 16, "~g~%d~w~/~r~10", combine_mode[playerid][c_step]-1);
					CombineTD_Beside(playerid, str_beside);
				}
			}
		}
		case 18:
		{
			if(combine_mode[playerid][c_step])
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_bad] >= 3)
					{
						TogglePlayerControllable(playerid, true);
						StopCombineMode(playerid);
						LeftNotifyShow(playerid, "info", "~r~Przerwano~w~ akcje.");
					}
				}
				else//gdy kombinacja zostaje wykonana
				{
					GenerateCombine(playerid);
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
					if(combine_mode[playerid][c_step] < 10)
					{
						combine_mode[playerid][c_step]++;
					}
					else
					{
						StopCombineMode(playerid);
						TogglePlayerControllable(playerid, true);
						new targetid = GetPVarInt(playerid, "unbw_targetid");
						if(!gracz[targetid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
						if(!gracz[targetid][BWTime]) return Error(playerid, "Ten gracz nie ma BW.");
						if(!IsPlayerInRangeOfPoint(playerid, 3.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Ten gracz jest za daleko.");
						new str_cmd[128];
						format(str_cmd, 128, "/me wybudza gracza '%s'.", nick(targetid));
						PC_EmulateCommand(playerid, str_cmd);
						DeactivateBW(targetid);
					}
					new str_beside[16];
					format(str_beside, 16, "~g~%d~w~/~r~10", combine_mode[playerid][c_step]-1);
					CombineTD_Beside(playerid, str_beside);
				}
			}
		}
	}
	return 1;
}

stock combine_OnPlayerKeyStateChange(playerid, key, axis)
{
	if(!combine_mode[playerid][c_id]) return 0;
	if(combine_mode[playerid][c_key_time] > GetTickCount()) return 0;
	new qkey = combine_mode[playerid][c_qkey];
	if(qkey >= 6) return 0;
	if(axis)//lewo prawo
	{
		if(combine_mode[playerid][c_mode] == 2)
		{
			if(key == KEY_LEFT)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_LEFT;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_RIGHT)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_RIGHT;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
		}
		else
		{
			if(key == KEY_LEFT && combine_mode[playerid][c_key][qkey] == CKEY_LEFT)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_RIGHT && combine_mode[playerid][c_key][qkey] == CKEY_RIGHT)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else 
			{
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				combine_mode[playerid][c_bad]++;
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, "~r~X~r~X~r~X~r~X~r~X~r~X");
				ShowCombineTD(playerid);
			}
		}
	}
	else//góra dó³
	{
		if(combine_mode[playerid][c_mode] == 2)
		{
			if(key == KEY_UP)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_UP;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_DOWN)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_DOWN;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
		}
		else
		{
			if(key == KEY_UP && combine_mode[playerid][c_key][qkey] == CKEY_UP)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_DOWN && combine_mode[playerid][c_key][qkey] == CKEY_DOWN)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else 
			{
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				combine_mode[playerid][c_bad]++;
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, "~r~X~r~X~r~X~r~X~r~X~r~X");
				ShowCombineTD(playerid);
			}
		}
	}
	return 1;
}

stock GetCombine(playerid)
{
	new combine[64];
	if(combine_mode[playerid][c_mode] == 0)
	{
		for(new c; c < 6; c++)
		{
			if(c < combine_mode[playerid][c_qkey])
			{
				format(combine, 64, "%s~g~X", combine);
			}
			else
			{
				switch(combine_mode[playerid][c_key][c])
				{
					case CKEY_LEFT:
					{
						format(combine, 64, "%s~<~", combine);
					}
					case CKEY_RIGHT:
					{
						format(combine, 64, "%s~>~", combine);
					}
					case CKEY_UP:
					{
						format(combine, 64, "%s~u~", combine);
					}
					case CKEY_DOWN:
					{
						format(combine, 64, "%s~d~", combine);
					}
				}
			}
		}
	}
	else if(combine_mode[playerid][c_mode] == 1)
	{
		for(new c; c < 6; c++)
		{
			if(c >= combine_mode[playerid][c_qkey])
			{
				format(combine, 64, "%s~p~X", combine);
			}
			else
			{
				switch(combine_mode[playerid][c_key][c])
				{
					case CKEY_LEFT:
					{
						format(combine, 64, "%s~<~", combine);
					}
					case CKEY_RIGHT:
					{
						format(combine, 64, "%s~>~", combine);
					}
					case CKEY_UP:
					{
						format(combine, 64, "%s~u~", combine);
					}
					case CKEY_DOWN:
					{
						format(combine, 64, "%s~d~", combine);
					}
				}
			}
		}
	}
	else if(combine_mode[playerid][c_mode] == 2)
	{
		for(new c; c < 6; c++)
		{
			if(c >= combine_mode[playerid][c_qkey])
			{
				format(combine, 64, "%s~y~X", combine);
			}
			else
			{
				switch(combine_mode[playerid][c_key][c])
				{
					case CKEY_LEFT:
					{
						format(combine, 64, "%s~<~", combine);
					}
					case CKEY_RIGHT:
					{
						format(combine, 64, "%s~>~", combine);
					}
					case CKEY_UP:
					{
						format(combine, 64, "%s~u~", combine);
					}
					case CKEY_DOWN:
					{
						format(combine, 64, "%s~d~", combine);
					}
				}
			}
		}
	}
	return combine;
}

stock GenerateCombine(playerid, difficulty = 4)
{
	combine_mode[playerid][c_qkey] = 0;
	if(combine_mode[playerid][c_mode] == 1) return 0;
	for(new k; k < 6; k++)
	{
		combine_mode[playerid][c_key][k] = MRandRange(1, difficulty);
	}
	return 1;
}

stock SetCombine(playerid, k1, k2, k3, k4, k5, k6)
{
	combine_mode[playerid][c_qkey] = 0;
	combine_mode[playerid][c_key][0] = k1;
	combine_mode[playerid][c_key][1] = k2;
	combine_mode[playerid][c_key][2] = k3;
	combine_mode[playerid][c_key][3] = k4;
	combine_mode[playerid][c_key][4] = k5;
	combine_mode[playerid][c_key][5] = k6;
	return 1;
}