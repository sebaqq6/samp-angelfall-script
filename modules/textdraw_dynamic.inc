new Text:black_screen;
new Text:HideMap;
new Text:HideMap1;
new Text:HideMap2;
new Text:td_shoot0;
new Text:td_shoot1;
new Text:td_exp_box;
new Text:td_exp_title;
new PlayerText:napisy[MAX_PLAYERS];
new PlayerText:td_exp_content[MAX_PLAYERS];
new PlayerText:td_exp_levelup[MAX_PLAYERS];
new PlayerText:td_leftann_title[MAX_PLAYERS];
new PlayerText:td_leftann_content[MAX_PLAYERS];
new PlayerText:td_leftann_ball[MAX_PLAYERS];
new PlayerText:td_leftann_icon[MAX_PLAYERS];
new PlayerText:td_panorama0[MAX_PLAYERS];
new PlayerText:td_panorama1[MAX_PLAYERS];

new PlayerText:tdCombine0[MAX_PLAYERS];
new PlayerText:tdCombine1[MAX_PLAYERS];
new PlayerText:tdCombine2[MAX_PLAYERS];
new PlayerText:tdCombine3[MAX_PLAYERS];
new PlayerText:tdCombine4[MAX_PLAYERS];
new PlayerText:tdCombine5[MAX_PLAYERS];
new PlayerText:tdCombine6[MAX_PLAYERS];
new PlayerText:tdCombine7[MAX_PLAYERS];
new PlayerText:tdCombine8[MAX_PLAYERS];

new PlayerText:tdVehHUD0[MAX_PLAYERS];
new PlayerText:tdVehHUD1[MAX_PLAYERS];
new PlayerText:tdVehHUD2[MAX_PLAYERS];
new PlayerText:tdVehHUD3[MAX_PLAYERS];
new PlayerText:tdVehHUD4[MAX_PLAYERS];
new PlayerText:tdVehHUD5[MAX_PLAYERS];
new PlayerText:tdVehHUD6[MAX_PLAYERS];
new PlayerText:tdVehHUD7[MAX_PLAYERS];
new PlayerText:tdVehHUD8[MAX_PLAYERS];
new PlayerText:tdVehHUD9[MAX_PLAYERS];
new PlayerText:tdVehHUD10[MAX_PLAYERS];
new PlayerText:tdVehHUD11[MAX_PLAYERS];
new PlayerText:tdVehHUD12[MAX_PLAYERS];
new PlayerText:tdVehHUD13[MAX_PLAYERS];
new PlayerText:tdVehHUD14[MAX_PLAYERS];

new PlayerText:geiger_model[MAX_PLAYERS];
new PlayerText:td_geiger0[MAX_PLAYERS];
new PlayerText:td_geiger1[MAX_PLAYERS];
new PlayerText:td_geiger2[MAX_PLAYERS];
new PlayerText:td_geiger3[MAX_PLAYERS];
new PlayerText:td_geiger4[MAX_PLAYERS];
new PlayerText:td_geiger5[MAX_PLAYERS];
new PlayerText:td_geiger6[MAX_PLAYERS];
new PlayerText:td_geiger7[MAX_PLAYERS];

new PlayerText:td_topcenter[MAX_PLAYERS];

new PlayerBar:fuel_bar[MAX_PLAYERS];
new PlayerBar:temp_bar[MAX_PLAYERS];


stock Init_TextDrawGlobalDynamic()
{
	HideMap = TextDrawCreate(27.625000, 335.083251, "LD_POOL:ball");
	TextDrawLetterSize(HideMap, 0.000000, 0.000000);
	TextDrawTextSize(HideMap, 118.125000, 92.749992);
	TextDrawAlignment(HideMap, 1);
	TextDrawColor(HideMap, 255);
	TextDrawSetShadow(HideMap, 0);
	TextDrawSetOutline(HideMap, 0);
	TextDrawFont(HideMap, 4);

	HideMap1 = TextDrawCreate(23.500000, 340.674987, "hud:radarRingPlane");
	TextDrawLetterSize(HideMap1, 0.000000, 0.000000);
	TextDrawTextSize(HideMap1, 126.625000, 89.774963);
	TextDrawAlignment(HideMap1, 1);
	TextDrawColor(HideMap1, COLOR_HUD);
	TextDrawSetShadow(HideMap1, 0);
	TextDrawSetOutline(HideMap1, 0);
	TextDrawFont(HideMap1, 4);

	HideMap2 = TextDrawCreate(35.625000, 389.083282, "Brak danych o pozycji.");
	TextDrawLetterSize(HideMap2, 0.263750, 0.969998);
	TextDrawAlignment(HideMap2, 1);
	TextDrawColor(HideMap2, COLOR_HUD);
	TextDrawSetShadow(HideMap2, 0);
	TextDrawSetOutline(HideMap2, 1);
	TextDrawBackgroundColor(HideMap2, 51);
	TextDrawFont(HideMap2, 1);

	td_shoot0 = TextDrawCreate(324.000000, 170.187500, "~l~/___~r~\\~n~~n~~r~\\___~l~/");
	TextDrawLetterSize(td_shoot0, 0.416499, 0.615625);
	TextDrawAlignment(td_shoot0, 1);
	TextDrawColor(td_shoot0, -2147483393);
	TextDrawSetShadow(td_shoot0, 0);
	TextDrawSetOutline(td_shoot0, 0);
	TextDrawBackgroundColor(td_shoot0, 51);
	TextDrawFont(td_shoot0, 1);
	TextDrawSetProportional(td_shoot0, 1);

	td_shoot1 = TextDrawCreate(324.000000, 170.187500, "~r~/___~l~\\~n~~n~~l~\\___~r~/");
	TextDrawLetterSize(td_shoot1, 0.416499, 0.615625);
	TextDrawAlignment(td_shoot1, 1);
	TextDrawColor(td_shoot1, -2147483393);
	TextDrawSetShadow(td_shoot1, 0);
	TextDrawSetOutline(td_shoot1, 0);
	TextDrawBackgroundColor(td_shoot1, 51);
	TextDrawFont(td_shoot1, 1);
	TextDrawSetProportional(td_shoot1, 1);

	td_exp_box = TextDrawCreate(138.000000, 306.875000, "usebox");
	TextDrawLetterSize(td_exp_box, 0.000000, 2.580555);
	TextDrawTextSize(td_exp_box, 32.000000, 0.000000);
	TextDrawAlignment(td_exp_box, 1);
	TextDrawColor(td_exp_box, 0);
	TextDrawUseBox(td_exp_box, true);
	TextDrawBoxColor(td_exp_box, 102);
	TextDrawSetShadow(td_exp_box, 0);
	TextDrawSetOutline(td_exp_box, 0);
	TextDrawFont(td_exp_box, 0);

	td_exp_title = TextDrawCreate(33.500000, 296.625000, "EXP");
	TextDrawLetterSize(td_exp_title, 0.449999, 1.600000);
	TextDrawAlignment(td_exp_title, 1);
	TextDrawColor(td_exp_title, -2147450625);
	TextDrawSetShadow(td_exp_title, 0);
	TextDrawSetOutline(td_exp_title, 1);
	TextDrawBackgroundColor(td_exp_title, 51);
	TextDrawFont(td_exp_title, 0);
	TextDrawSetProportional(td_exp_title, 1);

	black_screen = TextDrawCreate(-220.000000, -203.437500, "LD_SPAC:white");
	TextDrawLetterSize(black_screen, 0.000000, 0.000000);
	TextDrawTextSize(black_screen, 1005.000000, 741.125000);
	TextDrawAlignment(black_screen, 1);
	TextDrawColor(black_screen, 255);
	TextDrawSetShadow(black_screen, 0);
	TextDrawSetOutline(black_screen, 0);
	TextDrawFont(black_screen, 4);
	return 1;
}

stock Init_TextDrawPlayerDynamic(playerid)
{

	napisy[playerid] = CreatePlayerTextDraw(playerid, 320.500000, 336.437500, "_");
	PlayerTextDrawLetterSize(playerid, napisy[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, napisy[playerid], 2);
	PlayerTextDrawColor(playerid, napisy[playerid], -1);
	PlayerTextDrawSetShadow(playerid, napisy[playerid], 0);
	PlayerTextDrawSetOutline(playerid, napisy[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, napisy[playerid], 51);
	PlayerTextDrawFont(playerid, napisy[playerid], 1);
	PlayerTextDrawSetProportional(playerid, napisy[playerid], 1);

	td_exp_content[playerid] = CreatePlayerTextDraw(playerid, 85.500000, 313.687500, "~p~EXP: ~w~+0~y~(+0)~n~~g~0~p~/~r~0");
	PlayerTextDrawLetterSize(playerid, td_exp_content[playerid], 0.207499, 0.755625);
	PlayerTextDrawAlignment(playerid, td_exp_content[playerid], 2);
	PlayerTextDrawColor(playerid, td_exp_content[playerid], -2147450625);
	PlayerTextDrawSetShadow(playerid, td_exp_content[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_exp_content[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_exp_content[playerid], 51);
	PlayerTextDrawFont(playerid, td_exp_content[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_exp_content[playerid], 1);

	td_leftann_title[playerid] = CreatePlayerTextDraw(playerid, 18.000000, 206.937500, "Misja");
	PlayerTextDrawLetterSize(playerid, td_leftann_title[playerid], 0.440499, 1.573750);
	PlayerTextDrawAlignment(playerid, td_leftann_title[playerid], 1);
	PlayerTextDrawColor(playerid, td_leftann_title[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, td_leftann_title[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_leftann_title[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_leftann_title[playerid], 51);
	PlayerTextDrawFont(playerid, td_leftann_title[playerid], 0);
	PlayerTextDrawSetProportional(playerid, td_leftann_title[playerid], 1);

	td_leftann_content[playerid] = CreatePlayerTextDraw(playerid, 10.500000, 217.875000, "~n~NONE");
	PlayerTextDrawLetterSize(playerid, td_leftann_content[playerid], 0.219999, 0.865000);
	PlayerTextDrawTextSize(playerid, td_leftann_content[playerid], 127.500000, -63.437500);
	PlayerTextDrawAlignment(playerid, td_leftann_content[playerid], 1);
	PlayerTextDrawColor(playerid, td_leftann_content[playerid], -1);
	PlayerTextDrawUseBox(playerid, td_leftann_content[playerid], true);
	PlayerTextDrawBoxColor(playerid, td_leftann_content[playerid], 80);
	PlayerTextDrawSetShadow(playerid, td_leftann_content[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_leftann_content[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_leftann_content[playerid], 48);
	PlayerTextDrawFont(playerid, td_leftann_content[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_leftann_content[playerid], 1);

	
	td_exp_levelup[playerid] = CreatePlayerTextDraw(playerid, 85.500000, 311.062500, "LEVEL UP!");
	PlayerTextDrawLetterSize(playerid, td_exp_levelup[playerid], 0.585999, 2.020000);
	PlayerTextDrawAlignment(playerid, td_exp_levelup[playerid], 2);
	PlayerTextDrawColor(playerid, td_exp_levelup[playerid], 16711935);
	PlayerTextDrawSetShadow(playerid, td_exp_levelup[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_exp_levelup[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_exp_levelup[playerid], 51);
	PlayerTextDrawFont(playerid, td_exp_levelup[playerid], 3);
	PlayerTextDrawSetProportional(playerid, td_exp_levelup[playerid], 1);

	td_leftann_ball[playerid] = CreatePlayerTextDraw(playerid, 1.000000, 210.875000, "LD_POOL:ball");
	PlayerTextDrawLetterSize(playerid, td_leftann_ball[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, td_leftann_ball[playerid], 15.000000, 11.375000);
	PlayerTextDrawAlignment(playerid, td_leftann_ball[playerid], 1);
	PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, td_leftann_ball[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_leftann_ball[playerid], 0);
	PlayerTextDrawFont(playerid, td_leftann_ball[playerid], 4);

	td_leftann_icon[playerid] = CreatePlayerTextDraw(playerid, 6.500000, 210.437500, "!");
	PlayerTextDrawLetterSize(playerid, td_leftann_icon[playerid], 0.434500, 1.258749);
	PlayerTextDrawAlignment(playerid, td_leftann_icon[playerid], 1);
	PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_leftann_icon[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_leftann_icon[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_leftann_icon[playerid], 51);
	PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_leftann_icon[playerid], 1);

	td_panorama0[playerid] = CreatePlayerTextDraw(playerid, 645.444458, 452.666625, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, td_panorama0[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, td_panorama0[playerid], -650.333312, -115.037017);
	PlayerTextDrawAlignment(playerid, td_panorama0[playerid], 1);
	PlayerTextDrawColor(playerid, td_panorama0[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_panorama0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_panorama0[playerid], 0);
	PlayerTextDrawFont(playerid, td_panorama0[playerid], 4);
	
	td_panorama1[playerid] = CreatePlayerTextDraw(playerid, 645.444458, 115.629631, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, td_panorama1[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, td_panorama1[playerid], -650.444458, -115.629631);
	PlayerTextDrawAlignment(playerid, td_panorama1[playerid], 1);
	PlayerTextDrawColor(playerid, td_panorama1[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_panorama1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_panorama1[playerid], 0);
	PlayerTextDrawFont(playerid, td_panorama1[playerid], 4);

	/*td_panorama1[playerid] = CreatePlayerTextDraw(playerid, -255.000000, 311.000000, "Header2");
	PlayerTextDrawBackgroundColor(playerid, td_panorama1[playerid], 0);
	PlayerTextDrawFont(playerid, td_panorama1[playerid], 5);
	PlayerTextDrawLetterSize(playerid, td_panorama1[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, td_panorama1[playerid], 255);
	PlayerTextDrawSetOutline(playerid, td_panorama1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, td_panorama1[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_panorama1[playerid], 1);
	PlayerTextDrawTextSize(playerid, td_panorama1[playerid], 1141.000000, 197.000000);
	PlayerTextDrawSetPreviewModel(playerid, td_panorama1[playerid], 2189);
	PlayerTextDrawSetPreviewRot(playerid, td_panorama1[playerid], 90.000000, 0.000000, 180.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, td_panorama1[playerid], 0);

	td_panorama0[playerid] = CreatePlayerTextDraw(playerid, -255.000000, -60.000000, "Header1");
	PlayerTextDrawBackgroundColor(playerid, td_panorama0[playerid], 0);
	PlayerTextDrawFont(playerid, td_panorama0[playerid], 5);
	PlayerTextDrawLetterSize(playerid, td_panorama0[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, td_panorama0[playerid], 255);
	PlayerTextDrawSetOutline(playerid, td_panorama0[playerid], 0);
	PlayerTextDrawSetProportional(playerid, td_panorama0[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_panorama0[playerid], 1);
	PlayerTextDrawTextSize(playerid, td_panorama0[playerid], 1141.000000, 197.000000);
	PlayerTextDrawSetPreviewModel(playerid, td_panorama0[playerid], 2189);
	PlayerTextDrawSetPreviewRot(playerid, td_panorama0[playerid], 90.000000, 0.000000, 180.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, td_panorama0[playerid], 0);*/


	tdCombine0[playerid] = CreatePlayerTextDraw(playerid, 439.000000, 317.812500, "boxaction");
	PlayerTextDrawLetterSize(playerid, tdCombine0[playerid], 0.000000, 7.154166);
	PlayerTextDrawTextSize(playerid, tdCombine0[playerid], 198.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, tdCombine0[playerid], 1);
	PlayerTextDrawColor(playerid, tdCombine0[playerid], 0);
	PlayerTextDrawUseBox(playerid, tdCombine0[playerid], true);
	PlayerTextDrawBoxColor(playerid, tdCombine0[playerid], 102);
	PlayerTextDrawSetShadow(playerid, tdCombine0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine0[playerid], 0);
	PlayerTextDrawFont(playerid, tdCombine0[playerid], 0);

	tdCombine1[playerid] = CreatePlayerTextDraw(playerid, 319.000000, 307.562500, "laweczka");
	PlayerTextDrawLetterSize(playerid, tdCombine1[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, tdCombine1[playerid], 2);
	PlayerTextDrawColor(playerid, tdCombine1[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdCombine1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine1[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine1[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine1[playerid], 2);
	PlayerTextDrawSetProportional(playerid, tdCombine1[playerid], 1);

	tdCombine2[playerid] = CreatePlayerTextDraw(playerid, 317.000000, 372.750000, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
	PlayerTextDrawLetterSize(playerid, tdCombine2[playerid], 0.169500, 0.930625);
	PlayerTextDrawAlignment(playerid, tdCombine2[playerid], 2);
	PlayerTextDrawColor(playerid, tdCombine2[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdCombine2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine2[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine2[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdCombine2[playerid], 1);

	tdCombine3[playerid] = CreatePlayerTextDraw(playerid, 202.500000, 322.437500, "Ilosc powtorzen: ~y~10");
	PlayerTextDrawLetterSize(playerid, tdCombine3[playerid], 0.218000, 0.970001);
	PlayerTextDrawAlignment(playerid, tdCombine3[playerid], 1);
	PlayerTextDrawColor(playerid, tdCombine3[playerid], -1);
	PlayerTextDrawSetShadow(playerid, tdCombine3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine3[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine3[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdCombine3[playerid], 1);

	tdCombine4[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 323.000000, "Ilosc blednych kombinacji: ~g~0~w~/~r~3");
	PlayerTextDrawLetterSize(playerid, tdCombine4[playerid], 0.218000, 0.970001);
	PlayerTextDrawAlignment(playerid, tdCombine4[playerid], 3);
	PlayerTextDrawColor(playerid, tdCombine4[playerid], -1);
	PlayerTextDrawSetShadow(playerid, tdCombine4[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine4[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine4[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine4[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdCombine4[playerid], 1);

	tdCombine5[playerid] = CreatePlayerTextDraw(playerid, 378.000000, 349.312500, "boxkombinacja");
	PlayerTextDrawLetterSize(playerid, tdCombine5[playerid], 0.000000, 1.768055);
	PlayerTextDrawTextSize(playerid, tdCombine5[playerid], 254.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, tdCombine5[playerid], 1);
	PlayerTextDrawColor(playerid, tdCombine5[playerid], 0);
	PlayerTextDrawUseBox(playerid, tdCombine5[playerid], true);
	PlayerTextDrawBoxColor(playerid, tdCombine5[playerid], 102);
	PlayerTextDrawSetShadow(playerid, tdCombine5[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine5[playerid], 0);
	PlayerTextDrawFont(playerid, tdCombine5[playerid], 0);

	tdCombine6[playerid] = CreatePlayerTextDraw(playerid, 316.500000, 340.375000, "kombinacja");
	PlayerTextDrawLetterSize(playerid, tdCombine6[playerid], 0.212500, 0.755624);
	PlayerTextDrawAlignment(playerid, tdCombine6[playerid], 2);
	PlayerTextDrawColor(playerid, tdCombine6[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdCombine6[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine6[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine6[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine6[playerid], 3);
	PlayerTextDrawSetProportional(playerid, tdCombine6[playerid], 1);

	tdCombine7[playerid] = CreatePlayerTextDraw(playerid, 258.500000, 348.250000, "~d~~u~~<~~>~~<~~u~");
	PlayerTextDrawLetterSize(playerid, tdCombine7[playerid], 0.769499, 1.687500);
	PlayerTextDrawAlignment(playerid, tdCombine7[playerid], 1);
	PlayerTextDrawColor(playerid, tdCombine7[playerid], -1);
	PlayerTextDrawSetShadow(playerid, tdCombine7[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine7[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine7[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine7[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdCombine7[playerid], 1);

	tdCombine8[playerid] = CreatePlayerTextDraw(playerid, 387.000000, 352.187500, "~g~0~w~/~r~6");
	PlayerTextDrawLetterSize(playerid, tdCombine8[playerid], 0.387500, 1.074999);
	PlayerTextDrawAlignment(playerid, tdCombine8[playerid], 1);
	PlayerTextDrawColor(playerid, tdCombine8[playerid], -1);
	PlayerTextDrawSetShadow(playerid, tdCombine8[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdCombine8[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdCombine8[playerid], 51);
	PlayerTextDrawFont(playerid, tdCombine8[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdCombine8[playerid], 1);

	tdVehHUD0[playerid] = CreatePlayerTextDraw(playerid, 281.500000, 356.750000, "usebox");
	PlayerTextDrawLetterSize(playerid, tdVehHUD0[playerid], 0.000000, 6.427777);
	PlayerTextDrawTextSize(playerid, tdVehHUD0[playerid], 138.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, tdVehHUD0[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD0[playerid], 0);
	PlayerTextDrawUseBox(playerid, tdVehHUD0[playerid], true);
	PlayerTextDrawBoxColor(playerid, tdVehHUD0[playerid], 102);
	PlayerTextDrawSetShadow(playerid, tdVehHUD0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD0[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD0[playerid], 0);

	tdVehHUD1[playerid] = CreatePlayerTextDraw(playerid, 192.000000, 355.250000, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD1[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD1[playerid], 1.500000, 61.250000);
	PlayerTextDrawAlignment(playerid, tdVehHUD1[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD1[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD1[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD1[playerid], 4);

	tdVehHUD2[playerid] = CreatePlayerTextDraw(playerid, 193.000000, 363.687500, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD2[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD2[playerid], 86.500000, 1.312500);
	PlayerTextDrawAlignment(playerid, tdVehHUD2[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD2[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD2[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD2[playerid], 4);

	tdVehHUD3[playerid] = CreatePlayerTextDraw(playerid, 236.000000, 354.812500, "nazwa pojazdu");
	PlayerTextDrawLetterSize(playerid, tdVehHUD3[playerid], 0.301999, 0.891250);
	PlayerTextDrawAlignment(playerid, tdVehHUD3[playerid], 2);
	PlayerTextDrawColor(playerid, tdVehHUD3[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD3[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdVehHUD3[playerid], 51);
	PlayerTextDrawFont(playerid, tdVehHUD3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdVehHUD3[playerid], 1);

	tdVehHUD4[playerid] = CreatePlayerTextDraw(playerid, 193.000000, 382.187500, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD4[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD4[playerid], 86.500000, 1.312500);
	PlayerTextDrawAlignment(playerid, tdVehHUD4[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD4[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD4[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD4[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD4[playerid], 4);

	tdVehHUD5[playerid] = CreatePlayerTextDraw(playerid, 236.500000, 367.062500, "233 km/h");
	PlayerTextDrawLetterSize(playerid, tdVehHUD5[playerid], 0.349498, 1.389999);
	PlayerTextDrawAlignment(playerid, tdVehHUD5[playerid], 2);
	PlayerTextDrawColor(playerid, tdVehHUD5[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD5[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD5[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, tdVehHUD5[playerid], 51);
	PlayerTextDrawFont(playerid, tdVehHUD5[playerid], 3);
	PlayerTextDrawSetProportional(playerid, tdVehHUD5[playerid], 1);

	tdVehHUD6[playerid] = CreatePlayerTextDraw(playerid, 193.000000, 398.937500, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD6[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD6[playerid], 86.500000, 1.312500);
	PlayerTextDrawAlignment(playerid, tdVehHUD6[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD6[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD6[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD6[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD6[playerid], 4);

	tdVehHUD7[playerid] = CreatePlayerTextDraw(playerid, 209.000000, 382.500000, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD7[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD7[playerid], 1.500000, 33.687500);
	PlayerTextDrawAlignment(playerid, tdVehHUD7[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD7[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, tdVehHUD7[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD7[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD7[playerid], 4);

	tdVehHUD8[playerid] = CreatePlayerTextDraw(playerid, 197.000000, 399.437500, ".");
	PlayerTextDrawLetterSize(playerid, tdVehHUD8[playerid], 0.806000, 1.967500);
	PlayerTextDrawAlignment(playerid, tdVehHUD8[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD8[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, tdVehHUD8[playerid], 1);
	PlayerTextDrawSetOutline(playerid, tdVehHUD8[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, tdVehHUD8[playerid], 51);
	PlayerTextDrawFont(playerid, tdVehHUD8[playerid], 1);
	PlayerTextDrawSetProportional(playerid, tdVehHUD8[playerid], 1);

	tdVehHUD9[playerid] = CreatePlayerTextDraw(playerid, 202.500000, 403.375000, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD9[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD9[playerid], -2.000000, 7.875000);
	PlayerTextDrawAlignment(playerid, tdVehHUD9[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD9[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, tdVehHUD9[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD9[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD9[playerid], 4);

	tdVehHUD10[playerid] = CreatePlayerTextDraw(playerid, 202.500000, 404.250000, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD10[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD10[playerid], 3.500000, 0.875000);
	PlayerTextDrawAlignment(playerid, tdVehHUD10[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD10[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, tdVehHUD10[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD10[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD10[playerid], 4);

	tdVehHUD11[playerid] = CreatePlayerTextDraw(playerid, 202.500000, 406.125000, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD11[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD11[playerid], 3.500000, 0.875000);
	PlayerTextDrawAlignment(playerid, tdVehHUD11[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD11[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, tdVehHUD11[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD11[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD11[playerid], 4);

	tdVehHUD12[playerid] = CreatePlayerTextDraw(playerid, 202.500000, 408.437500, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, tdVehHUD12[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD12[playerid], 3.500000, 0.875000);
	PlayerTextDrawAlignment(playerid, tdVehHUD12[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD12[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, tdVehHUD12[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD12[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD12[playerid], 4);

	tdVehHUD13[playerid] = CreatePlayerTextDraw(playerid, 194.000000, 385.437500, "hud:radar_centre");
	PlayerTextDrawLetterSize(playerid, tdVehHUD13[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, tdVehHUD13[playerid], 15.000000, 11.375000);
	PlayerTextDrawAlignment(playerid, tdVehHUD13[playerid], 1);
	PlayerTextDrawColor(playerid, tdVehHUD13[playerid], -1);
	PlayerTextDrawSetShadow(playerid, tdVehHUD13[playerid], 0);
	PlayerTextDrawSetOutline(playerid, tdVehHUD13[playerid], 0);
	PlayerTextDrawFont(playerid, tdVehHUD13[playerid], 4);

	tdVehHUD14[playerid] = CreatePlayerTextDraw(playerid,126.000000, 355.000000, "vhud_model");
	PlayerTextDrawBackgroundColor(playerid,tdVehHUD14[playerid], 0x00000000);
	PlayerTextDrawFont(playerid,tdVehHUD14[playerid], 5);
	PlayerTextDrawLetterSize(playerid,tdVehHUD14[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,tdVehHUD14[playerid], -1);
	PlayerTextDrawSetOutline(playerid,tdVehHUD14[playerid], 0);
	PlayerTextDrawSetProportional(playerid,tdVehHUD14[playerid], 1);
	PlayerTextDrawSetShadow(playerid,tdVehHUD14[playerid], 1);
	PlayerTextDrawUseBox(playerid,tdVehHUD14[playerid], 1);
	PlayerTextDrawBoxColor(playerid,tdVehHUD14[playerid], -255);
	PlayerTextDrawTextSize(playerid,tdVehHUD14[playerid], 71.000000, 55.000000);
	PlayerTextDrawSetPreviewModel(playerid, tdVehHUD14[playerid], 406);
	PlayerTextDrawSetPreviewRot(playerid, tdVehHUD14[playerid], 340.000000, 0.000000, 30.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,tdVehHUD14[playerid], 0);

	geiger_model[playerid] = CreatePlayerTextDraw(playerid,466.000000, 290.000000, "geigera_model");
	PlayerTextDrawBackgroundColor(playerid,geiger_model[playerid], 0x00000000);
	PlayerTextDrawFont(playerid,geiger_model[playerid], 5);
	PlayerTextDrawLetterSize(playerid,geiger_model[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,geiger_model[playerid], -1);
	PlayerTextDrawSetOutline(playerid,geiger_model[playerid], 0);
	PlayerTextDrawSetProportional(playerid,geiger_model[playerid], 1);
	PlayerTextDrawSetShadow(playerid,geiger_model[playerid], 1);
	PlayerTextDrawUseBox(playerid,geiger_model[playerid], 1);
	PlayerTextDrawBoxColor(playerid,geiger_model[playerid], 0);
	PlayerTextDrawTextSize(playerid,geiger_model[playerid], 224.000000, 161.000000);
	PlayerTextDrawSetPreviewModel(playerid, geiger_model[playerid], 18875);
	PlayerTextDrawSetPreviewRot(playerid, geiger_model[playerid], 260.000000, 0.000000, 180.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,geiger_model[playerid], 0);

	td_geiger0[playerid] = CreatePlayerTextDraw(playerid, 581.000000, 339.500000, "GEIGER_RADS");
	PlayerTextDrawLetterSize(playerid, td_geiger0[playerid], 0.251999, 0.834375);
	PlayerTextDrawTextSize(playerid, td_geiger0[playerid], 307.000000, 62.562500);
	PlayerTextDrawAlignment(playerid, td_geiger0[playerid], 2);
	PlayerTextDrawColor(playerid, td_geiger0[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_geiger0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger0[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_geiger0[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger0[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_geiger0[playerid], 1);

	td_geiger1[playerid] = CreatePlayerTextDraw(playerid, 544.500000, 340.812500, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, td_geiger1[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, td_geiger1[playerid], 68.500000, 5.250000);
	PlayerTextDrawAlignment(playerid, td_geiger1[playerid], 1);
	PlayerTextDrawColor(playerid, td_geiger1[playerid], 1566923519);
	PlayerTextDrawSetShadow(playerid, td_geiger1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger1[playerid], 0);
	PlayerTextDrawFont(playerid, td_geiger1[playerid], 4);

	td_geiger2[playerid] = CreatePlayerTextDraw(playerid, 579.500000, 351.750000, "urems/hr");
	PlayerTextDrawLetterSize(playerid, td_geiger2[playerid], 0.208499, 0.935000);
	PlayerTextDrawAlignment(playerid, td_geiger2[playerid], 1);
	PlayerTextDrawColor(playerid, td_geiger2[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_geiger2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger2[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_geiger2[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_geiger2[playerid], 1);

	td_geiger3[playerid] = CreatePlayerTextDraw(playerid, 579.500000, 353.625000, "l");
	PlayerTextDrawLetterSize(playerid, td_geiger3[playerid], 0.208999, 0.891250);
	PlayerTextDrawAlignment(playerid, td_geiger3[playerid], 1);
	PlayerTextDrawColor(playerid, td_geiger3[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_geiger3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger3[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_geiger3[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_geiger3[playerid], 1);

	td_geiger4[playerid] = CreatePlayerTextDraw(playerid, 545.000000, 354.375000, "888");
	PlayerTextDrawLetterSize(playerid, td_geiger4[playerid], 0.363000, 1.499375);
	PlayerTextDrawAlignment(playerid, td_geiger4[playerid], 1);
	PlayerTextDrawColor(playerid, td_geiger4[playerid], 1516591816);
	PlayerTextDrawSetShadow(playerid, td_geiger4[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger4[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_geiger4[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger4[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_geiger4[playerid], 1);

	td_geiger5[playerid] = CreatePlayerTextDraw(playerid, 575.000000, 354.500000, "13");
	PlayerTextDrawLetterSize(playerid, td_geiger5[playerid], 0.363000, 1.499375);
	PlayerTextDrawAlignment(playerid, td_geiger5[playerid], 3);
	PlayerTextDrawColor(playerid, td_geiger5[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_geiger5[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger5[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_geiger5[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger5[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_geiger5[playerid], 1);

	td_geiger6[playerid] = CreatePlayerTextDraw(playerid, 585.000000, 388.500000, "Status:");
	PlayerTextDrawLetterSize(playerid, td_geiger6[playerid], 0.189999, 0.851874);
	PlayerTextDrawAlignment(playerid, td_geiger6[playerid], 1);
	PlayerTextDrawColor(playerid, td_geiger6[playerid], 255);
	PlayerTextDrawSetShadow(playerid, td_geiger6[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger6[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_geiger6[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger6[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_geiger6[playerid], 1);

	td_geiger7[playerid] = CreatePlayerTextDraw(playerid, 609.000000, 384.562500, "-");
	PlayerTextDrawLetterSize(playerid, td_geiger7[playerid], 1.383000, 1.683125);
	PlayerTextDrawAlignment(playerid, td_geiger7[playerid], 1);
	PlayerTextDrawColor(playerid, td_geiger7[playerid], 16711935);
	PlayerTextDrawSetShadow(playerid, td_geiger7[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_geiger7[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_geiger7[playerid], 51);
	PlayerTextDrawFont(playerid, td_geiger7[playerid], 0);
	PlayerTextDrawSetProportional(playerid, td_geiger7[playerid], 1);

	td_topcenter[playerid] = CreatePlayerTextDraw(playerid, 325.000000, 5.687500, "SPAWN PROTECT~n~~b~5s");
	PlayerTextDrawLetterSize(playerid, td_topcenter[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, td_topcenter[playerid], 2);
	PlayerTextDrawColor(playerid, td_topcenter[playerid], 8388863);
	PlayerTextDrawSetShadow(playerid, td_topcenter[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_topcenter[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_topcenter[playerid], 51);
	PlayerTextDrawFont(playerid, td_topcenter[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_topcenter[playerid], 1);

	fuel_bar[playerid] = CreatePlayerProgressBar(playerid, 217.00, 389.00, 55.50, 3.20, 0xFFFFFFFF, 1000.0);
	temp_bar[playerid] = CreatePlayerProgressBar(playerid, 217.00, 406.00, 55.50, 3.20, 0x1f9c5aFF, 100.0);
	return 1;
}

