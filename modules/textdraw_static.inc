new Text:td_hud0;
new Text:td_hud1;
new Text:td_hud2;
new Text:td_hud3;
new Text:td_hud4;
new Text:td_hud5;
new Text:td_hud6;
new Text:td_hud7;
new Text:td_hud8;
new Text:td_hud9;
new Text:td_hud10;
new Text:td_hud11;
new Text:td_hud12;
new Text:td_hud13;
new Text:td_hud14;
new Text:td_hud15;
new Text:td_hud16;
new Text:td_hud17;
new Text:td_hud18;
new Text:td_hud19;
new Text:td_hud20;
new Text:td_hud21;
new Text:td_hud22;
new Text:td_hud23;
new Text:td_hud24;
new Text:td_hud25;
new Text:td_hud26;
new Text:td_hud27;
new Text:model_hud1;
new Text:model_hud2;
new Text:model_hud3;
new Text:model_hud4;
new Text:model_hud5;
new Text:model_hud6;
new Text:model_hud7;
new Text:model_hud8;
new Text:interwencja_td;


new PlayerText:td_player_hud0[MAX_PLAYERS];
new PlayerText:td_player_hud1[MAX_PLAYERS];
new PlayerText:td_player_hud2[MAX_PLAYERS];
new PlayerText:td_player_hud3[MAX_PLAYERS];
new PlayerText:td_player_hud4[MAX_PLAYERS];
new PlayerText:td_player_hud5[MAX_PLAYERS];
new PlayerText:td_player_hud6[MAX_PLAYERS];
new PlayerText:td_player_hud7[MAX_PLAYERS];
new PlayerText:weapon_model[MAX_PLAYERS];
new PlayerText:td_halas0[MAX_PLAYERS];
new PlayerText:td_halas1[MAX_PLAYERS];
new PlayerText:td_halas2[MAX_PLAYERS];
new PlayerText:td_halas3[MAX_PLAYERS];
new PlayerText:td_halas4[MAX_PLAYERS];
new PlayerText:td_fist[MAX_PLAYERS];


new PlayerBar:hp_bar[MAX_PLAYERS];
new PlayerBar:cdn_bar[MAX_PLAYERS];
new PlayerBar:glod_bar[MAX_PLAYERS];
new PlayerBar:prag_bar[MAX_PLAYERS];
new PlayerBar:rad_bar[MAX_PLAYERS];

stock Init_TextDrawGlobalStatic()
{
	td_hud0 = TextDrawCreate(496.375000, 22.020832, "LD_SPAC:white");
	TextDrawLetterSize(td_hud0, 0.000000, 0.000000);
	TextDrawTextSize(td_hud0, 146.500000, 77.000000);
	TextDrawAlignment(td_hud0, 1);
	TextDrawColor(td_hud0, -2139062017);
	TextDrawSetShadow(td_hud0, 0);
	TextDrawSetOutline(td_hud0, 0);
	TextDrawFont(td_hud0, 4);

	td_hud1 = TextDrawCreate(499.375000, 24.770835, "LD_SPAC:white");
	TextDrawLetterSize(td_hud1, 0.000000, 0.000000);
	TextDrawTextSize(td_hud1, 156.000000, 71.750000);
	TextDrawAlignment(td_hud1, 1);
	TextDrawColor(td_hud1, 255);
	TextDrawSetShadow(td_hud1, 0);
	TextDrawSetOutline(td_hud1, 0);
	TextDrawFont(td_hud1, 4);

	td_hud2 = TextDrawCreate(570.000000, 24.500000, "LD_SPAC:white");
	TextDrawLetterSize(td_hud2, 0.000000, 0.000000);
	TextDrawTextSize(td_hud2, 2.500000, 73.500000);
	TextDrawAlignment(td_hud2, 1);
	TextDrawColor(td_hud2, -2139062017);
	TextDrawSetShadow(td_hud2, 0);
	TextDrawSetOutline(td_hud2, 0);
	TextDrawFont(td_hud2, 4);

	td_hud3 = TextDrawCreate(497.000000, 52.625000, "LD_SPAC:white");
	TextDrawLetterSize(td_hud3, 0.000000, 0.000000);
	TextDrawTextSize(td_hud3, 145.500000, 2.187500);
	TextDrawAlignment(td_hud3, 1);
	TextDrawColor(td_hud3, -2139062017);
	TextDrawSetShadow(td_hud3, 0);
	TextDrawSetOutline(td_hud3, 0);
	TextDrawFont(td_hud3, 4);

	td_hud4 = TextDrawCreate(498.500000, 32.187500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud4, 0.000000, 0.000000);
	TextDrawTextSize(td_hud4, 73.500000, 2.187500);
	TextDrawAlignment(td_hud4, 1);
	TextDrawColor(td_hud4, -2139062017);
	TextDrawSetShadow(td_hud4, 0);
	TextDrawSetOutline(td_hud4, 0);
	TextDrawFont(td_hud4, 4);

	td_hud5 = TextDrawCreate(498.500000, 62.812500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud5, 0.000000, 0.000000);
	TextDrawTextSize(td_hud5, 73.500000, 2.187500);
	TextDrawAlignment(td_hud5, 1);
	TextDrawColor(td_hud5, -2139062017);
	TextDrawSetShadow(td_hud5, 0);
	TextDrawSetOutline(td_hud5, 0);
	TextDrawFont(td_hud5, 4);

	td_hud6 = TextDrawCreate(496.500000, 73.437500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud6, 0.000000, 0.000000);
	TextDrawTextSize(td_hud6, 154.500000, 2.187500);
	TextDrawAlignment(td_hud6, 1);
	TextDrawColor(td_hud6, -2139062017);
	TextDrawSetShadow(td_hud6, 0);
	TextDrawSetOutline(td_hud6, 0);
	TextDrawFont(td_hud6, 4);

	td_hud7 = TextDrawCreate(498.500000, 82.312500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud7, 0.000000, 0.000000);
	TextDrawTextSize(td_hud7, 73.500000, 2.187500);
	TextDrawAlignment(td_hud7, 1);
	TextDrawColor(td_hud7, -2139062017);
	TextDrawSetShadow(td_hud7, 0);
	TextDrawSetOutline(td_hud7, 0);
	TextDrawFont(td_hud7, 4);

	td_hud8 = TextDrawCreate(535.000000, 84.812500, DzienTygodnia(serwer[dzien_tygodnia]));
	TextDrawLetterSize(td_hud8, 0.222498, 1.048750);
	TextDrawAlignment(td_hud8, 2);
	TextDrawColor(td_hud8, -1378294017);
	TextDrawSetShadow(td_hud8, 0);
	TextDrawSetOutline(td_hud8, 1);
	TextDrawBackgroundColor(td_hud8, 51);
	TextDrawFont(td_hud8, 2);
	TextDrawSetProportional(td_hud8, 1);

	td_hud9 = TextDrawCreate(663.000000, 149.375000, "usebox");
	TextDrawLetterSize(td_hud9, 0.000000, 17.547224);
	TextDrawTextSize(td_hud9, 598.000000, 0.000000);
	TextDrawAlignment(td_hud9, 1);
	TextDrawColor(td_hud9, 0);
	TextDrawUseBox(td_hud9, true);
	TextDrawBoxColor(td_hud9, 102);
	TextDrawSetShadow(td_hud9, 0);
	TextDrawSetOutline(td_hud9, 0);
	TextDrawFont(td_hud9, 0);

	td_hud10 = TextDrawCreate(600.000000, 147.437500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud10, 0.000000, 0.000000);
	TextDrawTextSize(td_hud10, 84.000000, 1.750000);
	TextDrawAlignment(td_hud10, 1);
	TextDrawColor(td_hud10, -2139062017);
	TextDrawSetShadow(td_hud10, 0);
	TextDrawSetOutline(td_hud10, 0);
	TextDrawFont(td_hud10, 4);

	td_hud11 = TextDrawCreate(600.000000, 155.437500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud11, 0.000000, 0.000000);
	TextDrawTextSize(td_hud11, 84.000000, 1.750000);
	TextDrawAlignment(td_hud11, 1);
	TextDrawColor(td_hud11, -2139062017);
	TextDrawSetShadow(td_hud11, 0);
	TextDrawSetOutline(td_hud11, 0);
	TextDrawFont(td_hud11, 4);

	td_hud12 = TextDrawCreate(600.000000, 187.500000, "LD_SPAC:white");
	TextDrawLetterSize(td_hud12, 0.000000, 0.000000);
	TextDrawTextSize(td_hud12, 84.000000, 1.750000);
	TextDrawAlignment(td_hud12, 1);
	TextDrawColor(td_hud12, -2139062017);
	TextDrawSetShadow(td_hud12, 0);
	TextDrawSetOutline(td_hud12, 0);
	TextDrawFont(td_hud12, 4);

	td_hud13 = TextDrawCreate(600.000000, 195.937500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud13, 0.000000, 0.000000);
	TextDrawTextSize(td_hud13, 84.000000, 1.750000);
	TextDrawAlignment(td_hud13, 1);
	TextDrawColor(td_hud13, -2139062017);
	TextDrawSetShadow(td_hud13, 0);
	TextDrawSetOutline(td_hud13, 0);
	TextDrawFont(td_hud13, 4);

	td_hud14 = TextDrawCreate(600.000000, 228.437500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud14, 0.000000, 0.000000);
	TextDrawTextSize(td_hud14, 84.000000, 1.750000);
	TextDrawAlignment(td_hud14, 1);
	TextDrawColor(td_hud14, -2139062017);
	TextDrawSetShadow(td_hud14, 0);
	TextDrawSetOutline(td_hud14, 0);
	TextDrawFont(td_hud14, 4);

	td_hud15 = TextDrawCreate(600.000000, 236.875000, "LD_SPAC:white");
	TextDrawLetterSize(td_hud15, 0.000000, 0.000000);
	TextDrawTextSize(td_hud15, 84.000000, 1.750000);
	TextDrawAlignment(td_hud15, 1);
	TextDrawColor(td_hud15, -2139062017);
	TextDrawSetShadow(td_hud15, 0);
	TextDrawSetOutline(td_hud15, 0);
	TextDrawFont(td_hud15, 4);

	td_hud16 = TextDrawCreate(600.000000, 268.062500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud16, 0.000000, 0.000000);
	TextDrawTextSize(td_hud16, 84.000000, 1.750000);
	TextDrawAlignment(td_hud16, 1);
	TextDrawColor(td_hud16, -2139062017);
	TextDrawSetShadow(td_hud16, 0);
	TextDrawSetOutline(td_hud16, 0);
	TextDrawFont(td_hud16, 4);

	td_hud17 = TextDrawCreate(600.000000, 276.062500, "LD_SPAC:white");
	TextDrawLetterSize(td_hud17, 0.000000, 0.000000);
	TextDrawTextSize(td_hud17, 84.000000, 1.750000);
	TextDrawAlignment(td_hud17, 1);
	TextDrawColor(td_hud17, -2139062017);
	TextDrawSetShadow(td_hud17, 0);
	TextDrawSetOutline(td_hud17, 0);
	TextDrawFont(td_hud17, 4);

	td_hud18 = TextDrawCreate(613.000000, 147.687500, "GLOD");
	TextDrawLetterSize(td_hud18, 0.161000, 0.926250);
	TextDrawAlignment(td_hud18, 1);
	TextDrawColor(td_hud18, -2139062017);
	TextDrawSetShadow(td_hud18, 0);
	TextDrawSetOutline(td_hud18, 1);
	TextDrawBackgroundColor(td_hud18, 51);
	TextDrawFont(td_hud18, 1);
	TextDrawSetProportional(td_hud18, 1);

	td_hud19 = TextDrawCreate(604.500000, 188.250000, "PRAGNIENIE");
	TextDrawLetterSize(td_hud19, 0.161000, 0.926250);
	TextDrawAlignment(td_hud19, 1);
	TextDrawColor(td_hud19, -2139062017);
	TextDrawSetShadow(td_hud19, 0);
	TextDrawSetOutline(td_hud19, 1);
	TextDrawBackgroundColor(td_hud19, 51);
	TextDrawFont(td_hud19, 1);
	TextDrawSetProportional(td_hud19, 1);

	td_hud20 = TextDrawCreate(601.500000, 229.062500, "TEMPERATURA");
	TextDrawLetterSize(td_hud20, 0.161000, 0.926250);
	TextDrawAlignment(td_hud20, 1);
	TextDrawColor(td_hud20, -2139062017);
	TextDrawSetShadow(td_hud20, 0);
	TextDrawSetOutline(td_hud20, 1);
	TextDrawBackgroundColor(td_hud20, 51);
	TextDrawFont(td_hud20, 1);
	TextDrawSetProportional(td_hud20, 1);

	td_hud21 = TextDrawCreate(614.000000, 268.125000, "RAD");
	TextDrawLetterSize(td_hud21, 0.161000, 0.926250);
	TextDrawAlignment(td_hud21, 1);
	TextDrawColor(td_hud21, -2139062017);
	TextDrawSetShadow(td_hud21, 0);
	TextDrawSetOutline(td_hud21, 1);
	TextDrawBackgroundColor(td_hud21, 51);
	TextDrawFont(td_hud21, 1);
	TextDrawSetProportional(td_hud21, 1);

	td_hud22 = TextDrawCreate(723.000000, 440.312500, "usebox");
	TextDrawLetterSize(td_hud22, 0.000000, 2.622221);
	TextDrawTextSize(td_hud22, -105.500000, 0.000000);
	TextDrawAlignment(td_hud22, 1);
	TextDrawColor(td_hud22, 0);
	TextDrawUseBox(td_hud22, true);
	TextDrawBoxColor(td_hud22, 102);
	TextDrawSetShadow(td_hud22, 0);
	TextDrawSetOutline(td_hud22, 0);
	TextDrawFont(td_hud22, 0);

	td_hud23 = TextDrawCreate(-40.000000, 437.791656, "LD_SPAC:white");
	TextDrawLetterSize(td_hud23, 0.000000, 0.000000);
	TextDrawTextSize(td_hud23, 693.000000, 1.750000);
	TextDrawAlignment(td_hud23, 1);
	TextDrawColor(td_hud23, -2139062017);
	TextDrawSetShadow(td_hud23, 0);
	TextDrawSetOutline(td_hud23, 0);
	TextDrawFont(td_hud23, 4);

	td_hud24 = TextDrawCreate(317.500000, 438.812500, serwer[pasek_dol]);
	TextDrawLetterSize(td_hud24, 0.347500, 0.865000);
	TextDrawAlignment(td_hud24, 2);
	TextDrawColor(td_hud24, -2139062017);
	TextDrawSetShadow(td_hud24, 0);
	TextDrawSetOutline(td_hud24, 1);
	TextDrawBackgroundColor(td_hud24, 51);
	TextDrawFont(td_hud24, 1);
	TextDrawSetProportional(td_hud24, 1);

	td_hud25 = TextDrawCreate(637.500000, 1.750000, serwer[wersja]);
	TextDrawLetterSize(td_hud25, 0.330000, 0.899999);
	TextDrawAlignment(td_hud25, 3);
	TextDrawColor(td_hud25, -2139062017);
	TextDrawSetShadow(td_hud25, -3);
	TextDrawSetOutline(td_hud25, 0);
	TextDrawBackgroundColor(td_hud25, 51);
	TextDrawFont(td_hud25, 0);
	TextDrawSetProportional(td_hud25, 1);

	td_hud26 = TextDrawCreate(633.500000, 245.875000, "o");
	TextDrawLetterSize(td_hud26, 0.236499, 0.659375);
	TextDrawAlignment(td_hud26, 1);
	TextDrawColor(td_hud26, -2139062017);
	TextDrawSetShadow(td_hud26, 0);
	TextDrawSetOutline(td_hud26, 1);
	TextDrawBackgroundColor(td_hud26, 51);
	TextDrawFont(td_hud26, 1);
	TextDrawSetProportional(td_hud26, 1);

	td_hud27 = TextDrawCreate(738.000000, 109.562500, "usebox");
	TextDrawLetterSize(td_hud27, 0.000000, 2.223611);
	TextDrawTextSize(td_hud27, 598.000000, 0.000000);
	TextDrawAlignment(td_hud27, 1);
	TextDrawColor(td_hud27, 0);
	TextDrawUseBox(td_hud27, true);
	TextDrawBoxColor(td_hud27, 102);
	TextDrawSetShadow(td_hud27, 0);
	TextDrawSetOutline(td_hud27, 0);
	TextDrawFont(td_hud27, 0);

	model_hud1 = TextDrawCreate(545.000000, 36.000000, "k_normal");
	TextDrawAlignment(model_hud1, 2);
	TextDrawBackgroundColor(model_hud1, 0x00000000);
	TextDrawFont(model_hud1, 5);
	TextDrawLetterSize(model_hud1, 0.829999, 1.799998);
	TextDrawColor(model_hud1, -1);
	TextDrawSetOutline(model_hud1, 0);
	TextDrawSetProportional(model_hud1, 1);
	TextDrawSetShadow(model_hud1, 1);
	TextDrawUseBox(model_hud1, 1);
	TextDrawBoxColor(model_hud1, 0);
	TextDrawTextSize(model_hud1, 77.000000, 52.000000);
	TextDrawSetPreviewModel(model_hud1, 1912);
	TextDrawSetPreviewRot(model_hud1, -90.000000, 0.000000, 5.000000, 2.000000);
	TextDrawSetSelectable(model_hud1, 0);

	model_hud2 = TextDrawCreate(545.000000, 58.000000, "k_premium");
	TextDrawAlignment(model_hud2, 2);
	TextDrawBackgroundColor(model_hud2, 0x00000000);
	TextDrawFont(model_hud2, 5);
	TextDrawLetterSize(model_hud2, 0.829999, 1.799998);
	TextDrawColor(model_hud2, -1);
	TextDrawSetOutline(model_hud2, 0);
	TextDrawSetProportional(model_hud2, 1);
	TextDrawSetShadow(model_hud2, 1);
	TextDrawUseBox(model_hud2, 1);
	TextDrawBoxColor(model_hud2, 0);
	TextDrawTextSize(model_hud2, 77.000000, 52.000000);
	TextDrawSetPreviewModel(model_hud2, 1907);
	TextDrawSetPreviewRot(model_hud2, -90.000000, 0.000000, 5.000000, 2.000000);
	TextDrawSetSelectable(model_hud2, 0);

	model_hud3 = TextDrawCreate(575.000000, 148.000000, "glod");
	TextDrawAlignment(model_hud3, 2);
	TextDrawBackgroundColor(model_hud3, 0x00000000);
	TextDrawFont(model_hud3, 5);
	TextDrawLetterSize(model_hud3, 0.829999, 1.799998);
	TextDrawColor(model_hud3, -1);
	TextDrawSetOutline(model_hud3, 0);
	TextDrawSetProportional(model_hud3, 1);
	TextDrawSetShadow(model_hud3, 1);
	TextDrawUseBox(model_hud3, 1);
	TextDrawBoxColor(model_hud3, -255);
	TextDrawTextSize(model_hud3, 77.000000, 52.000000);
	TextDrawSetPreviewModel(model_hud3, 19847);
	TextDrawSetPreviewRot(model_hud3, 130.000000, 130.000000, 100.000000, 2.000000);
	TextDrawSetSelectable(model_hud3, 0);

	model_hud4 = TextDrawCreate(581.000000, 185.000000, "pragnienie");
	TextDrawAlignment(model_hud4, 2);
	TextDrawBackgroundColor(model_hud4, 0x00000000);
	TextDrawFont(model_hud4, 5);
	TextDrawLetterSize(model_hud4, 0.829999, 1.799998);
	TextDrawColor(model_hud4, -1);
	TextDrawSetOutline(model_hud4, 0);
	TextDrawSetProportional(model_hud4, 1);
	TextDrawSetShadow(model_hud4, 1);
	TextDrawUseBox(model_hud4, 1);
	TextDrawBoxColor(model_hud4, 0);
	TextDrawTextSize(model_hud4, 77.000000, 52.000000);
	TextDrawSetPreviewModel(model_hud4, 19819);
	TextDrawSetPreviewRot(model_hud4, 0.000000, 0.000000, 0.000000, 2.000000);
	TextDrawSetSelectable(model_hud4, 0);

	model_hud5 = TextDrawCreate(569.000000, 226.000000, "temperatura");
	TextDrawAlignment(model_hud5, 2);
	TextDrawBackgroundColor(model_hud5, 0x00000000);
	TextDrawFont(model_hud5, 5);
	TextDrawLetterSize(model_hud5, 0.829999, 1.799998);
	TextDrawColor(model_hud5, -1);
	TextDrawSetOutline(model_hud5, 0);
	TextDrawSetProportional(model_hud5, 1);
	TextDrawSetShadow(model_hud5, 1);
	TextDrawUseBox(model_hud5, 1);
	TextDrawBoxColor(model_hud5, 0);
	TextDrawTextSize(model_hud5, 77.000000, 52.000000);
	TextDrawSetPreviewModel(model_hud5, 19797);
	TextDrawSetPreviewRot(model_hud5, 0.000000, 90.000000, 180.000000, 2.000000);
	TextDrawSetSelectable(model_hud5, 0);

	model_hud6 = TextDrawCreate(487.000000, 202.000000, "radiacja");
	TextDrawAlignment(model_hud6, 2);
	TextDrawBackgroundColor(model_hud6, 0x00000000);
	TextDrawFont(model_hud6, 5);
	TextDrawLetterSize(model_hud6, 0.829999, 1.799998);
	TextDrawColor(model_hud6, -1);
	TextDrawSetOutline(model_hud6, 0);
	TextDrawSetProportional(model_hud6, 1);
	TextDrawSetShadow(model_hud6, 1);
	TextDrawUseBox(model_hud6, 1);
	TextDrawBoxColor(model_hud6, 0);
	TextDrawTextSize(model_hud6, 227.000000, 142.000000);
	TextDrawSetPreviewModel(model_hud6, 11700);
	TextDrawSetPreviewRot(model_hud6, 0.000000, -60.000000, 180.000000, 3.000000);
	TextDrawSetSelectable(model_hud6, 0);

	model_hud7 = TextDrawCreate(487.000000, 187.000000, "radiacja");
	TextDrawAlignment(model_hud7, 2);
	TextDrawBackgroundColor(model_hud7,  0x00000000);
	TextDrawFont(model_hud7, 5);
	TextDrawLetterSize(model_hud7, 0.829999, 1.799998);
	TextDrawColor(model_hud7, -1);
	TextDrawSetOutline(model_hud7, 0);
	TextDrawSetProportional(model_hud7, 1);
	TextDrawSetShadow(model_hud7, 1);
	TextDrawUseBox(model_hud7, 1);
	TextDrawBoxColor(model_hud7, 0);
	TextDrawTextSize(model_hud7, 227.000000, 142.000000);
	TextDrawSetPreviewModel(model_hud7, 11700);
	TextDrawSetPreviewRot(model_hud7, 0.000000, -120.000000, 180.000000, 3.000000);
	TextDrawSetSelectable(model_hud7, 0);

	model_hud8 = TextDrawCreate(556.000000, 177.000000, "radiacja");
	TextDrawAlignment(model_hud8, 2);
	TextDrawBackgroundColor(model_hud8, 0x00000000);
	TextDrawFont(model_hud8, 5);
	TextDrawLetterSize(model_hud8, 0.829999, 1.799998);
	TextDrawColor(model_hud8, -1);
	TextDrawSetOutline(model_hud8, 0);
	TextDrawSetProportional(model_hud8, 1);
	TextDrawSetShadow(model_hud8, 1);
	TextDrawUseBox(model_hud8, 1);
	TextDrawBoxColor(model_hud8, 0);
	TextDrawTextSize(model_hud8, 227.000000, 142.000000);
	TextDrawSetPreviewModel(model_hud8, 11700);
	TextDrawSetPreviewRot(model_hud8, 0.000000, 120.000000, 180.000000, 3.000000);
	TextDrawSetSelectable(model_hud8, 0);

	interwencja_td = TextDrawCreate(7.500000, 93.187500, "_");
	TextDrawLetterSize(interwencja_td, 0.191999, 0.711875);
	TextDrawTextSize(interwencja_td, 133.000000, -54.687500);
	TextDrawAlignment(interwencja_td, 1);
	TextDrawColor(interwencja_td, -1);
	TextDrawUseBox(interwencja_td, true);
	TextDrawBoxColor(interwencja_td, 128);
	TextDrawSetShadow(interwencja_td, 0);
	TextDrawSetOutline(interwencja_td, 1);
	TextDrawBackgroundColor(interwencja_td, 51);
	TextDrawFont(interwencja_td, 1);
	TextDrawSetProportional(interwencja_td, 1);

	return 1;
}


stock Init_TextDrawPlayerStatic(playerid)
{
	td_player_hud0[playerid] = CreatePlayerTextDraw(playerid, 534.000000, 24.500000, "nick");
	PlayerTextDrawLetterSize(playerid, td_player_hud0[playerid], 0.177499, 0.799374);
	PlayerTextDrawAlignment(playerid, td_player_hud0[playerid], 2);
	PlayerTextDrawColor(playerid, td_player_hud0[playerid], -1378294017);
	PlayerTextDrawSetShadow(playerid, td_player_hud0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud0[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud0[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud0[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_player_hud0[playerid], 1);

	td_player_hud1[playerid] = CreatePlayerTextDraw(playerid, 573.500000, 45.937500, "_");//ammo
	PlayerTextDrawLetterSize(playerid, td_player_hud1[playerid], 0.143998, 0.729375);
	PlayerTextDrawAlignment(playerid, td_player_hud1[playerid], 1);
	PlayerTextDrawColor(playerid, td_player_hud1[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_player_hud1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud1[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud1[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud1[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_player_hud1[playerid], 1);

	td_player_hud2[playerid] = CreatePlayerTextDraw(playerid, 533.500000, 54.687500, "0h, 0m, 0s");
	PlayerTextDrawLetterSize(playerid, td_player_hud2[playerid], 0.169999, 0.904375);
	PlayerTextDrawAlignment(playerid, td_player_hud2[playerid], 2);
	PlayerTextDrawColor(playerid, td_player_hud2[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_player_hud2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud2[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud2[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud2[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_player_hud2[playerid], 1);

	td_player_hud3[playerid] = CreatePlayerTextDraw(playerid, 533.500000, 64.437500, "0h, 0m, 0s");
	PlayerTextDrawLetterSize(playerid, td_player_hud3[playerid], 0.169999, 0.904375);
	PlayerTextDrawAlignment(playerid, td_player_hud3[playerid], 2);
	PlayerTextDrawColor(playerid, td_player_hud3[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_player_hud3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud3[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud3[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud3[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_player_hud3[playerid], 1);

	td_player_hud4[playerid] = CreatePlayerTextDraw(playerid, 533.500000, 74.187500, "brak grupy");//grupa
	PlayerTextDrawLetterSize(playerid, td_player_hud4[playerid], 0.169999, 0.904375);
	PlayerTextDrawAlignment(playerid, td_player_hud4[playerid], 2);
	PlayerTextDrawColor(playerid, td_player_hud4[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_player_hud4[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud4[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud4[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud4[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_player_hud4[playerid], 1);

	td_player_hud5[playerid] = CreatePlayerTextDraw(playerid, 594.500000, 57.312500, "00000");//normal
	PlayerTextDrawLetterSize(playerid, td_player_hud5[playerid], 0.297500, 1.311249);
	PlayerTextDrawAlignment(playerid, td_player_hud5[playerid], 1);
	PlayerTextDrawColor(playerid, td_player_hud5[playerid], 16777215);
	PlayerTextDrawSetShadow(playerid, td_player_hud5[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud5[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud5[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud5[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_player_hud5[playerid], 1);

	td_player_hud6[playerid] = CreatePlayerTextDraw(playerid, 594.500000, 78.875000, "00000");//premium
	PlayerTextDrawLetterSize(playerid, td_player_hud6[playerid], 0.297500, 1.311249);
	PlayerTextDrawAlignment(playerid, td_player_hud6[playerid], 1);
	PlayerTextDrawColor(playerid, td_player_hud6[playerid], -5963521);
	PlayerTextDrawSetShadow(playerid, td_player_hud6[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud6[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud6[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud6[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_player_hud6[playerid], 1);

	td_player_hud7[playerid] = CreatePlayerTextDraw(playerid, 614.000000, 248.937500, "36.6");
	PlayerTextDrawLetterSize(playerid, td_player_hud7[playerid], 0.218500, 0.755625);
	PlayerTextDrawAlignment(playerid, td_player_hud7[playerid], 1);
	PlayerTextDrawColor(playerid, td_player_hud7[playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, td_player_hud7[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_player_hud7[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_player_hud7[playerid], 51);
	PlayerTextDrawFont(playerid, td_player_hud7[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_player_hud7[playerid], 1);

	weapon_model[playerid] = CreatePlayerTextDraw(playerid,577.000000, 13.000000, "bron");
	PlayerTextDrawAlignment(playerid,weapon_model[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,weapon_model[playerid], -255);
	PlayerTextDrawFont(playerid,weapon_model[playerid], 5);
	PlayerTextDrawLetterSize(playerid,weapon_model[playerid], 0.829999, 1.799998);
	PlayerTextDrawColor(playerid,weapon_model[playerid], -1);
	PlayerTextDrawSetOutline(playerid,weapon_model[playerid], 0);
	PlayerTextDrawSetProportional(playerid,weapon_model[playerid], 1);
	PlayerTextDrawSetShadow(playerid,weapon_model[playerid], 1);
	PlayerTextDrawUseBox(playerid,weapon_model[playerid], 1);
	PlayerTextDrawBoxColor(playerid,weapon_model[playerid], 0);
	PlayerTextDrawTextSize(playerid,weapon_model[playerid], 77.000000, 52.000000);
	PlayerTextDrawSetPreviewModel(playerid, weapon_model[playerid], 350);
	PlayerTextDrawSetPreviewRot(playerid, weapon_model[playerid], -16.000000, 0.000000, 0.000000, 2.500000);
	PlayerTextDrawSetSelectable(playerid,weapon_model[playerid], 0);

	td_halas0[playerid] = CreatePlayerTextDraw(playerid, 622.000000, 114.187500, "H");
	PlayerTextDrawLetterSize(playerid, td_halas0[playerid], 0.472999, 1.166875);
	PlayerTextDrawAlignment(playerid, td_halas0[playerid], 1);
	PlayerTextDrawColor(playerid, td_halas0[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_halas0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_halas0[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_halas0[playerid], 51);
	PlayerTextDrawFont(playerid, td_halas0[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_halas0[playerid], 1);
	
	td_halas1[playerid] = CreatePlayerTextDraw(playerid, 617.000000, 115.625000, "(");
	PlayerTextDrawLetterSize(playerid, td_halas1[playerid], 0.312499, 0.816875);
	PlayerTextDrawAlignment(playerid, td_halas1[playerid], 1);
	PlayerTextDrawColor(playerid, td_halas1[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_halas1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_halas1[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_halas1[playerid], 51);
	PlayerTextDrawFont(playerid, td_halas1[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_halas1[playerid], 1);
	
	td_halas2[playerid] = CreatePlayerTextDraw(playerid, 611.500000, 113.562500, "(");
	PlayerTextDrawLetterSize(playerid, td_halas2[playerid], 0.387999, 1.188750);
	PlayerTextDrawAlignment(playerid, td_halas2[playerid], 1);
	PlayerTextDrawColor(playerid, td_halas2[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_halas2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_halas2[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_halas2[playerid], 51);
	PlayerTextDrawFont(playerid, td_halas2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_halas2[playerid], 1);
	
	td_halas3[playerid] = CreatePlayerTextDraw(playerid, 606.500000, 110.187500, "(");
	PlayerTextDrawLetterSize(playerid, td_halas3[playerid], 0.360499, 1.739999);
	PlayerTextDrawAlignment(playerid, td_halas3[playerid], 1);
	PlayerTextDrawColor(playerid, td_halas3[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_halas3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_halas3[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_halas3[playerid], 51);
	PlayerTextDrawFont(playerid, td_halas3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_halas3[playerid], 1);
	
	td_halas4[playerid] = CreatePlayerTextDraw(playerid, 601.500000, 105.500000, "(");
	PlayerTextDrawLetterSize(playerid, td_halas4[playerid], 0.362499, 2.562500);
	PlayerTextDrawAlignment(playerid, td_halas4[playerid], 1);
	PlayerTextDrawColor(playerid, td_halas4[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_halas4[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_halas4[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, td_halas4[playerid], 51);
	PlayerTextDrawFont(playerid, td_halas4[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_halas4[playerid], 1);

	td_fist[playerid] = CreatePlayerTextDraw(playerid, 616.500000, 27.125000, "hud:fist");
	PlayerTextDrawLetterSize(playerid, td_fist[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, td_fist[playerid], -22.500000, 21.875000);
	PlayerTextDrawAlignment(playerid, td_fist[playerid], 1);
	PlayerTextDrawColor(playerid, td_fist[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_fist[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_fist[playerid], 0);
	PlayerTextDrawFont(playerid, td_fist[playerid], 4);

	hp_bar[playerid] = CreatePlayerProgressBar(playerid, 507.00, 37.00, 55.50, 3.20, -16776961, 100.0);
	cdn_bar[playerid] = CreatePlayerProgressBar(playerid, 507.00, 46.00, 55.50, 3.20, -1376714753, 100.0);
	glod_bar[playerid] = CreatePlayerProgressBar(playerid, 603.00, 183.00, 35.50, 2.19, -1768515841, 100.0);
	prag_bar[playerid] = CreatePlayerProgressBar(playerid, 603.00, 224.00, 35.50, 2.20, -1768515841, 100.0);
	rad_bar[playerid] = CreatePlayerProgressBar(playerid, 603.00, 304.00, 35.50, 2.20, -1768515841, 100.0);
	return 1;
}