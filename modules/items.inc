
//************************************************************************************************
#define MAX_ITEMS 203
#define DEFAULT_OBJECT 1575
new ItemName[MAX_ITEMS][] =
{
    {" "}, // 0 - Występuje błąd
    {"Kastet"}, // 1
    {"Kij golfowy"}, // 2
    {"Palka policyjna"}, // 3
    {"Noz bojowy"}, // 4
    {"Kij bejsbolowy"}, // 5
    {"Lopata"}, // 6
    {"Kij bilardowy"},
    {"Katana"}, // 7
    {"Pila lancuchowa"}, // 9
    {"Fioletowy Dildo"}, // 10
    {"Duzy Bialy Vibrator"}, // 11
    {"Sredni Bialy Vibrator"}, // 12
    {"Maly Bialy Vibrator"}, // 13
    {"Kwiaty"}, // 14
    {"Laska"}, // 15
    {"Granat odlamkowy"}, // 16
    {"Granat dymny"}, // 17
    {"Koktajl Molotova"}, // 18
    {" "}, // 19
    {" "}, // 20
    {" "}, // 21
    {"Colt 45"}, // 22
    {"Colt 45 (Z tlumikiem)"}, // 23
    {"Desert Eagle"}, // 24
    {"Mossberg 500"}, // 25
    {"Sawed-off shotgun"}, // 26
    {"SPAS-12"}, // 27
    {"Mac 10 Ingram"}, // 28
    {"Hk MP5N"}, // 29
    {"AK-47"}, // 30
    {"M4 Carbine"}, // 31
    {"TEC-DC9"}, // 32
    {"Winchester M1866"}, // 33
    {"BAR-10"}, // 34
    {"RPG-7"}, // 35
    {"Wyrzutnia rakiet z autonamierzaniem"}, // 36
    {"Miotacz ognia"}, // 37
    {"M134 Minigun"}, // 38
    {"Ladunek wybuchowy"}, // 39
    {"Detonator"}, // 40
    {"Spray"}, // 41
    {"Gasnica"}, // 42
    {"Aparat fotograficzny"}, // 43
    {"Noktowizor"}, // 44
    {"Termowizor"}, // 45
    {"Spadochron"}, // 46
    {"Amunicja: Colt45"}, // 47
    {"Amunicja: Desert Eagle"}, // 48
    {"Amunicja: Mossberg 500"}, // 49
    {"Amunicja: Sawed-off shotgun"}, // 50
    {"Amunicja: SPAS-12"}, // 51
    {"Amunicja: Mac 10 Ingram"}, // 52
    {"Drewno"}, // 53
    {"Pusty kanister"}, // 54
    {"Pełny kanister"}, // 55
    {"wolny_slot_przedmiotu2"}, // 56
    {"Żelazo"}, //57
    {"Amunicja: Hk MP5N"}, //58
    {"Amunicja: TEC-DC9"}, //59
    {"Amunicja: AK-47"}, //60
    {"Amunicja: M4 Carbine"}, //61
    {"Amunicja: Winchester M1866"}, //62
    {"Amunicja: BAR-10"}, //63
    {"Amunicja: RPG-7"}, //64
    {"Amunicja: M134 Minigun"}, //65
    {"Batonik proteinowy"}, //66
    {"Karnet"},//67
    {"Karnet(nieważny)"},//68
    {"Element u.elektrycznego"},//69
    {"Element u.zasilana"},//70
    {"Element u.smarowania"},//71
    {"Element u.chlodzenia"},//72
    {"Element u.korbowego"},//73
    {"Zestaw narzedzi (Pojazd)"}, //74
    {"Konserwa rybna"},//75
    {"Zgnile jablko"},//76
    {"Zgnily banan"},//77
    {"Skazone mieso"},//78
    {"Upieczone mieso"},//79
    {"Skazona ryba"},//80
    {"Upieczone ryba"},//81
    {"Chrupki CripsyFlakes"},//82
    {"Zgnila pomarancza"},//83
    {"Jogurt truskawkowy"},//84
    {"Jogurt bananowy"},//85
    {"Jogurt waniliowy"},//86
    {"Baton"},//87
    {"Suchy wafelek"},//88
    {"Konserwa wieprzowa"},//89
    {"Konserwa warzywna"},//90
    {"Solone orzeszki"},//91
    {"Twarog niskotluszczowy"},//92
    {"Chrupki Happy-Smiley"},//93
    {"Skazona woda"},//94
    {"Woda"},//95
    {"Mleko"},//96
    {"Sprunk"},//97
    {"Apo-Cola"},//98
    {"Apo-Cola Tiger"},//99
    {"Zeton"},//100
    {"Sok jablkowy"},//101
    {"Sok pomaranczowy"},//102
    {"Whisky"},//103
    {"Anyzowy likwor"},//104
    {"Apple Jack Brandy"},//105
    {"Bandaz"},//106
    {"Apteczka"},//107
    {"Duza Apteczka"},//108
    {"Anti-Rad"},//109
    {"Morfina"},//110
    {"Bandaz elastyczny"},//111
    {"Haps"},//112
    {"AntiBlooder"},//113
    {"AntiBlooder-Quantum"},//114
    {"Element broni: Zamek"},//115
    {"Element broni: Sprezyna powrotna"},//116
    {"Element broni: Nasada lufy"},//117
    {"Element broni: Sprezyna spustu"},//118
    {"Element broni: Spust"},//119
    {"Zestaw narzedzi (Bron)"},//120
    {"wolny_slot_przedmiotu1"},//121
    {"Zestaw medyczny"},//122
    {"Mut-warzywo"},//123
    {"Korzen ksadrowy"},//124
    {"Necik piegowaty"},//125
    {"Zimnokwiat piaszczysty"},//126
    {"Krwawa Lespedoza"},//127
    {"Zmutowana Lucerna"},//128
    {"Zmutowany Krwawnik"},//129
    {"Dzika Ankrecja"},//130
    {"Xadricaria srebrzysta"},//131
    {"Kiew wodnisty"},//132
    {"Krótkofalówka"},//133
    {"Gruz"},//134
    {"Zgnieciona puszka"},//135
    {"Modul elektryczny"},//136
    {"Zlom"},//137
    {"Gumowy kalosz"},//138
    {"Zniszczone pudełko"},//139
    {"Papier toaletowy"},//140
    {"Stara deskorolka"},//141
    {"Miotla"},//142
    {"Zkorodowana patelnia"},//143
    {"Zegarek"},//144
    {"Lom"},//145
    {"Mlotek"},//146
    {"Licznik Geigera"},//147
    {"Mapa"},//148
    {"Kompas"},//149
    {"GPS"},//150
    {"Syrop Haps 10"},//151
    {"Syrop Haps 25"},//152
    {"Syrop Haps 50"},//153
    {"Syrop AntiRad 10"},//154
    {"Syrop AntiRad 25"},//155
    {"Syrop AntiRad 50"},//156
    {"Syrop na wytrzymalosc"},//157
    {"Ubranie"},//158
    {"Wedka"},//159
    {"Bandana: zielona"},//160
    {"Bandana: niebieska"}, //161
    {"Bandana: czarna"}, //162
    {"Bandana: biała"}, //163
    {"Okulary owalne: czerwone"},//164
    {"Okulary owalne: pomaranczowe"},//165
    {"Okulary owalne: zielone"},//166
    {"Okulary owalne: niebieskie"},//167
    {"Okulary owalne: rozowe"},//168
    {"Okulary owalne: ciemne"},//169
    {"Okulary ochronne: zolte"},//170
    {"Okulary ochronne: pomaranczowe"},//171
    {"Okulary ochronne: czerwone"},//172
    {"Okulary ochronne: niebieskie"},//173
    {"Okulary ochronne: zielone"},//174
    {"Okulary pilotki: czarne"},//175
    {"Okulary pilotki: niebieskie"},//176
    {"Okulary pilotki: fioletowe"},//177
    {"Okulary pilotki: rozowe"},//178
    {"Okulary pilotki: czerwone"},//179
    {"Okulary pilotki: pomaranczowe"},//180
    {"Okulary pilotki: zolte"},//181
    {"Okulary pilotki: zielone"},//182
    {"Okulary kwadratowe: siwe"},//183
    {"Okulary kwadratowe: zolte"},//184
    {"Okulary kwadratowe: czerwone"},//185
    {"Okulary kwadratowe: czarne"},//186
    {"Okulary policyjne: czarne"},//187
    {"Okulary policyjne: czerwone"},//188
    {"Okulary policyjne: niebieskie"},//189
    {"Kaszkietowka: zielona"},//190
    {"Kaszkietowka: szara"},//191
    {"Kaszkietowka: czarna"},//192
    {"Kaszkietowka: niebieska"},//193
    {"Kaszkietowka: elektryczna"},//194
    {"Czapka: czarna"},//195
    {"Czapka: szara"},//196
    {"Kapelusz: szary"},//197
    {"Kapelusz: czarny"},//198
    {"Kapelusz: niebieski"},//199
    {"Kapelusz: zielony"},//200
    {"Kapelusz: czerwony"},//201
    {"Kapelusz: zolty"}//202
};
new ObjectItem[MAX_ITEMS] =
{
    -1,          //Błąd, 0
    331,         //Kastet, 1
    333,         //Kij golfowy, 2
    334,         //Pałka policyjna, 3
    335,         //Nóż, 4
    336,         //Baseball, 5
    337,         //Łopata, 6
    338,         //Kij bilardowy, 7
    339,         //Katana, 8
    341,         //Piła mechaniczna, 9
    321,         //Fioletowy Dildo, 10
    322,         //Duży Biały Vibrator, 11
    323,         //Średni Biały Vibrator, 12
    324,         //Mały Biały Vibrator, 13
    325,         //Kwiaty, 14
    326,         //Laska, 15
    342,         //Granat odłamkowy, 16
    343,         //Granat dymny, 17
    344,         //Koktajl molotova, 18
    -1,          //Błąd, 19
    -1,          //Błąd, 20
    -1,          //Błąd, 21
    346,         //Colt 45, 22
    347,         //Colt 45 (Z tłumikiem), 23
    348,         //Desert Eagle, 24
    349,         //Shotgun, 25
    350,         //Sawnoff Shotgun, 26
    351,         //Combat Shotgun, 27
    352,         //UZI, 28
    353,         //MP5, 29
    355,         //AK-47, 30
    356,         //M4, 31
    372,         //Tec9, 32
    357,         //Karabin Klasyczny, 33
    358,         //Karabin Snajperski, 34
    359,         //Wyrzutnia rakiet, 35
    360,         //Wyrzutnia rakiet z autonamierzaniem, 36
    361,         //Miotacz ognia, 37
    362,         //Minigun, 38
    363,         //Ładunek wybuchowy, 39
    364,         //Detonator, 40
    365,         //Spray, 41
    366,         //Gaśnica, 42
    367,         //Aparat fotograficzny, 43
    368,         //Noktowizor, 44
    369,         //Termowizor, 45
    371,         //Spadochron, 46
    19995,         //Amunicja: Colt 45, 47
    19995,       //Amunicja: Desert Eagle, 48
    2037,        //Amunicja: Mossberg 500, 49
    2037,        //Amunicja: Sawed-off shotgun, 50
    2037,        //Amunicja: SPAS-12, 51
    19832,        //Amunicja: Mac 10 Ingram, 52
    19793,		 //Drewno, 53
    1650,		 //Pusty kanister, 54
    1650,		 //Pełny kanister, 55
    1668,		 //wolny_slot_przedmiotu2, 56
    19772,	 	 //Żelazo, 57
    19832, 		 //Amunicja: Hk MP5N, 58
    19832, 		 //Amunicja: TEC-DC9, 59
    19832, 		 //Amunicja: AK-47, 60
    19832,		 //Amunicja: M4 Carbine, 61
    2037,		 //Amunicja: Winchester M1866, 62
    2037,		 //Amunicja: BAR-10, 63
    2358,		 //Amunicja: RPG-7, 64
    2006,		 //Amunicja: M134 Minigun, 65
    11742,                   //Batonik proteinowy, 66
    19792,                   //Karnet, 67
    19792,                   //Karnet[nieważny], 68
    DEFAULT_OBJECT,//Element u.elektrycznego, 69
    DEFAULT_OBJECT,//Element u.zasilana, 70
    DEFAULT_OBJECT,//Element u.smarowania, 71
    DEFAULT_OBJECT,//Element u.chlodzenia, 72
    DEFAULT_OBJECT, //Element u.korbowego, 73
    19921,//Zestaw narzedzi(Pojazd), 74
    11739,//Konserwa rybna, 75
    19575,//Zgniłe jabłko, 76
    19578,//Zgnily banan, 77
    19582,//Skazone mieso, 78
    19847,//Upieczone mieso, 79
    19630,//Skazona ryba, 80
    19630,//Upieczone ryba, 81
    19561,//Chrupki CripsyFlakes, 82
    19574,//Zgnila pomarancza, 83
    1455,//Jogurt truskawkowy, 84
    1455,//Jogurt bananowy, 85
    1455,//Jogurt waniliowy, 86
    11742,//Baton, 87
    19883,//Suchy wafelek, 88
    11739,//Konserwa wieprzowa, 89
    11739,//Konserwa warzywna, 90
    11740,//Solone orzeszki, 91
    11740,//Twarog niskotluszczowy, 92
    19562,//Chrupki Happy-Smileym, 93
    19570,//Skazona woda, 94
    19570,//Woda, 95
    19569,//Mleko, 96
    1546,//Sprunk, 97
    1950,//Apo-Cola, 98
    19822,//Apo-Cola Tiger, 99
    1912,//Żeton, 100
    19564,//Sok jablkowy, 101
    19563,//Sok pomaranczowy, 102
    19823,//Whisky, 103
    19821,//Anyzowy likwor, 104
    19824,//Apple Jack Brandy, 105
    11747,//Bandaz, 106
    11736,//Apteczka, 107
    11738,//Duza Apteczka, 108
    11742,//Anti-Rad, 109
    19874,//Morfina, 110
    19873,//Bandaz elastyczny, 111
    19896,//Haps, 112
    19896,//AntiBlooder, 113
    19896,//AntiBlooder-Quantum, 114
    DEFAULT_OBJECT,//Element broni: Zamek, 115
    DEFAULT_OBJECT,//Element broni: Sprezyna powrotna, 116
    DEFAULT_OBJECT,//Element broni: Nasada lufy, 117
    DEFAULT_OBJECT,//Element broni: Sprezyna spustu, 118
    DEFAULT_OBJECT,//Element broni: Spust, 119
    19921,//Zestaw narzedzi (Bron), 120
    19921,//wolny_slot_przedmiotu1, 121
    19921,//Zestaw medyczny, 122
    675,//Mut-warzywo, 123
    815,//Korzen ksadrowy, 124
    682,//Necik piegowaty, 125
    2250,//Zimnokwiat piasczysty, 126
    678,//Krwawa Lespedoza, 127
    857,//Zmutowana Lucerna, 128
    811,//Zmutowany Krwawnik, 129
    859,//Dzika Ankrecja, 130
    2249,//Xadricaria srebrzysta, 131
    804,//Kiew wodnisty, 132
    2966,//Krótkofalówka, 133
    854,//Napromieniowany gruz, 134
    2647,//Zgnieciona puszka, 135
    18875,//Moduł elektryczny, 136
    849,//Złom, 137
    11735,//Gumowy kalosz, 138
    928,//Karton, 139        
    19873,//Papier toaletowy, 140
    19878,//Stara deskorolka, 141
    19622,//Miotla, 142
    19581,//Zkorodowana patelnia, 143        
    19041,//Zegarek, 144
    18634,//Lom, 145
    18635,//Mlotek, 146
    18875,//Licznik Geigera, 147
    3017,//Mapa, 148
    2710,//Kompas, 149
    2966,//GPS, 150
    1668,//Syrop Haps 10, 151
    1668,//Syrop Haps 25, 152
    1668,//Syrop Haps 50, 153
    1668,//Syrop AntiRad 10, 154
    1668,//Syrop AntiRad 25, 155
    1668,//Syrop AntiRad 50, 156
    1668,//Syrop na wytrzymalosc, 157
    DEFAULT_OBJECT,//Ubranie, 158
    18632,//Wędka, 159
    18913,//Bandana: zielona, 160
    18917, //Bandana niebieska, 161
    18912, //Bandana czarna, 162
    18919, //Bandana biała, 163
    19006,//Okulary owalne: czerwone, 164
    19007,//Okulary owalne: pomaranczowe, 165
    19008,//Okulary owalne: zielone, 166
    19009,//Okulary owalne: niebieskie, 167
    19010,//Okulary owalne: rozowe, 168
    19012,//Okulary owalne: ciemne, 169
    19017,//Okulary ochronne: zolte, 170
    19018,//Okulary ochronne: pomaranczowe, 171
    19019,//Okulary ochronne: czerwone, 172
    19020,//Okulary ochronne: niebieskie, 173
    19021,//Okulary ochronne: zielone, 174
    19022,//Okulary pilotki: czarne, 175
    19023,//Okulary pilotki: niebieskie, 176
    19024,//Okulary pilotki: fioletowe, 177
    19025,//Okulary pilotki: rozowe, 178
    19026,//Okulary pilotki: czerwone, 179
    19027,//Okulary pilotki: pomaranczowe, 180
    19028,//Okulary pilotki: zolte, 181
    19029,//Okulary pilotki: zielone, 182
    19030,//Okulary kwadratowe: siwe, 183
    19031,//Okulary kwadratowe: zolte, 184
    19032,//Okulary kwadratowe: czerwone, 185
    19033,//Okulary kwadratowe: czarne, 186
    19138,//Okulary policyjne: czarne, 187
    19139,//Okulary policyjne: czerwone, 188
    19140,//Okulary policyjne: niebieskie, 189
    18943,//Kaszkietowka: zielona, 190
    18942,//Kaszkietowka: szara, 191
    18941,//Kaszkietowka: czarna, 192
    18940,//Kaszkietowka: niebieska, 193
    18939,//Kaszkietowka: elektryczna, 194
    18953,//Czapka: czarna, 195
    18954,//Czapka: szara, 196
    18946,//Kapelusz: szary, 197
    18947,//Kapelusz: czarny, 198
    18948,//Kapelusz: niebieski, 199
    18949,//Kapelusz: zielony, 200
    18950,//Kapelusz: czerwony, 201
    18951 //Kapelusz: zolty, 202
};
new Float:ObjectItemFloat[MAX_ITEMS][4] =
{
    {0.0, 0.0, 0.0, 0.0}, //Błąd, 0
    {1.0, 85.0, -809.0, 0.0}, //Kastet, 1
    {1.0, 85.0, -809.0, 0.0}, //Kij golfowy, 2
    {1.0, 85.0, -809.0, 0.0}, //Pałka policyjna, 3
    {1.0, 85.0, -809.0, 0.0}, //Nóż, 4
    {1.0, 85.0, -809.0, 0.0}, //Baseball,, 5
    {1.0, 85.0, 0.0, 0.0}, //Łopata, 6
    {1.0, 85.0, -809.0, 0.0}, //Kij bilardowy, 7
    {1.0, 85.0, -809.0, 0.0}, //Katana, 8
    {1.0, 85.0, -809.0, 0.0}, //Piła mechaniczna, 9
    {1.0, 85.0, -809.0, 0.0}, //Fioletowy Dildo, 10
    {1.0, 85.0, -809.0, 0.0}, //Duży Biały Vibrator, 11
    {1.0, 85.0, -809.0, 0.0}, //Średni Biały Vibrator, 11
    {1.0, 85.0, -809.0, 0.0}, //Mały Biały Vibrator,, 13
    {1.0, 85.0, -809.0, 0.0}, //Kwiaty, 1
    {1.0, 85.0, -809.0, 0.0}, //Laska, 15
    {1.0, 85.0, -809.0, 0.0}, //Granat odłamkowy,, 16
    {1.0, 85.0, -809.0, 0.0}, //Granat dymny, 17
    {1.0, 85.0, -809.0, 0.0}, //Koktajl molotova, 18
    {0.0, 0.0, 0.0, 0.0}, //Błąd, 19
    {0.0, 0.0, 0.0, 0.0}, //Błąd, 20
    {0.0, 0.0, 0.0, 0.0}, //Błąd, 21
    {1.0, 85.0, -809.0, 0.0}, //Colt 45, 22
    {1.0, 85.0, -809.0, 0.0}, //Colt 45 (Z tłumikiem), 23
    {1.0, 85.0, -809.0, 0.0}, //Desert Eagle, 24
    {1.0, 85.0, -809.0, 0.0}, //Shotgun, 25
    {1.0, 85.0, -809.0, 0.0}, //Sawnoff Shotgun, 26
    {1.0, 85.0, -809.0, 0.0}, //Combat Shotgun, 27
    {1.0, 85.0, -809.0, 0.0}, //UZI, 28
    {1.0, 85.0, -809.0, 0.0}, //MP5, 29
    {1.0, 85.0, -809.0, 0.0}, //AK-47, 30
    {1.0, 85.0, -809.0, 0.0}, //M4, 31
    {1.0, 85.0, -809.0, 0.0}, //Tec9, 32
    {1.0, 85.0, -809.0, 0.0}, //Karabin Klasyczny, 33
    {1.0, 85.0, -809.0, 0.0}, //Karabin Snajperski, 34
    {1.0, 85.0, -809.0, 0.0}, //Wyrzutnia rakiet, 35
    {1.0, 85.0, -809.0, 0.0}, //Wyrzutnia rakiet z autonamierzaniem, 36
    {1.0, 85.0, -809.0, 0.0}, //Miotacz ognia, 37
    {1.0, 85.0, -809.0, 0.0}, //Minigun, 38
    {1.0, 85.0, -809.0, 0.0}, //Ładunek wybuchowy, 39
    {1.0, 85.0, -809.0, 0.0}, //Detonator, 40
    {1.0, 85.0, -809.0, 0.0}, //Spray, 41
    {1.0, 85.0, -809.0, 0.0}, //Gaśnica, 42
    {1.0, 85.0, -809.0, 0.0}, //Aparat fotograficzny, 43
    {1.0, 85.0, -809.0, 0.0}, //Noktowizor, 44
    {1.0, 85.0, -809.0, 0.0}, //Termowizor, 45
    {1.0, 85.0, -809.0, 0.0}, //Spadochron, 46
    {1.0, 0.0, 90.0, 0.0}, //Amunicja: Colt 45, 47
    {1.0, 0.0, 90.0, 0.0}, //Amunicja: Desert Eagle, 48
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: Mossberg 500, 49
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: Sawed-off shotgun, 50
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: SPAS-12, 51
    {1.0, 0.0, 0.0, 0.0}, //Amunicja: Mac 10 Ingram, 52
    {0.9, 0.0, 0.0, 0.0}, //Drewno, 53
    {0.7, 0.0, 0.0, 0.0}, //Pusty kanister, 54
    {0.7, 0.0, 0.0, 0.0}, //Pełny kanister, 55
    {0.8, 0.0, 0.0, 0.0}, //wolny_slot_przedmiotu2, 56
    {1.0, 0.0, 0.0, 0.0}, //Żelazo, 57
    {1.0, 0.0, 0.0, 0.0}, //Amunicja: Hk MP5N, 58
    {1.0, 0.0, 0.0, 0.0}, //Amunicja: TEC-DC9, 59
    {1.0, 0.0, 0.0, 0.0}, //Amunicja: AK-47, 60
    {1.0, 0.0, 0.0, 0.0}, //Amunicja: M4 Carbine, 61
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: Winchester M1866, 62
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: BAR-10, 63
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: RPG-7, 64
    {0.9, 0.0, 0.0, 0.0}, //Amunicja: M134 Minigun, 65
    {1.0, 0.0, 0.0, 0.0}, //Batonik proteinowy, 66
    {0.9, 0.0, 0.0, 0.0}, //Karnet, 67
    {0.9, 0.0, 0.0, 0.0}, //Karnet[nieważny], 68
    {1.0, 0.0, 0.0, 0.0},//Element u.elektrycznego, 69
    {1.0, 0.0, 0.0, 0.0},//Element u.zasilana, 70
    {1.0, 0.0, 0.0, 0.0},//Element u.smarowania, 71
    {1.0, 0.0, 0.0, 0.0},//Element u.chlodzenia, 72
    {1.0, 0.0, 0.0, 0.0},//Element u.korbowego, 73
    {0.9, 0.0, 0.0, 0.0},//Zestaw narzedzi(Pojazd), 74
    {1.0, 0.0, 0.0, 0.0},//Konserwa rybna, 75
    {0.9, 0.0, 0.0, 0.0},//Zgniłe jabłko, 76
    {0.9, 0.0, 0.0, 0.0},//Zgnily banan, 77
    {0.9, 0.0, 0.0, 0.0},//Skazone mieso, 78
    {0.9, 0.0, 0.0, 0.0},//Upieczone mieso, 79
    {0.9, 90.0, 0.0, 0.0},//Skazona ryba, 80
    {0.9, 90.0, 0.0, 0.0},//Upieczone ryba, 81
    {1.0, 0.0, 0.0, 0.0},//Chrupki CripsyFlakes, 82
    {0.9, 0.0, 0.0, 0.0},//Zgnila pomarancza, 83
    {0.9, 0.0, 0.0, 0.0},//Jogurt truskawkowy, 84
    {0.9, 0.0, 0.0, 0.0},//Jogurt bananowy, 85
    {0.9, 0.0, 0.0, 0.0},//Jogurt waniliowy, 86
    {1.0, 0.0, 0.0, 0.0},//Baton, 87
    {0.9, 0.0, 0.0, 0.0},//Suchy wafelek, 88
    {1.0, 0.0, 0.0, 0.0},//Konserwa wieprzowa, 89
    {1.0, 0.0, 0.0, 0.0},//Konserwa warzywna, 90
    {1.0, 0.0, 0.0, 0.0},//Solone orzeszki, 91
    {1.0, 0.0, 0.0, 0.0},//Twarog niskotluszczowy, 92
    {1.0, 0.0, 0.0, 0.0},//Chrupki Happy-Smileym, 93
    {1.0, 0.0, 0.0, 0.0},//Skazona woda, 94
    {1.0, 0.0, 0.0, 0.0},//Woda, 95
    {1.0, 0.0, 0.0, 0.0},//Mleko, 96
    {0.8, 0.0, 0.0, 0.0},//Sprunk, 97
    {0.8, 0.0, 0.0, 0.0},//Apo-Cola, 98
    {1.0, 0.0, 0.0, 0.0},//Apo-Cola Tiger, 99
    {1.0, 0.0, 0.0, 0.0},//Żeton, 100
    {1.0, 0.0, 0.0, 0.0},//Sok jablkowy, 101
    {1.0, 0.0, 0.0, 0.0},//Sok pomaranczowy, 102
    {1.0, 0.0, 0.0, 0.0},//Whisky, 103
    {1.0, 0.0, 0.0, 0.0},//Anyzowy likwor, 104
    {1.0, 0.0, 0.0, 0.0},//Apple Jack Brandy, 105
    {0.9, 90.0, 0.0, 0.0},////Bandaz, 106
    {0.9, 0.0, 0.0, 0.0},//Apteczka, 107
    {0.9, 0.0, 0.0, 0.0},//Duza Apteczka, 108
    {1.0, 0.0, 0.0, 0.0},//Anti-Rad, 109
    {1.0, 0.0, 0.0, 0.0},//Morfina, 110
    {0.9, 90.0, 0.0, 0.0},//Bandaz elastyczny, 111
    {0.9, 0.0, 0.0, 0.0},//Haps, 112
    {0.9, 0.0, 0.0, 0.0},//AntiBlooder, 113
    {0.9, 0.0, 0.0, 0.0},//AntiBlooder-Quantum, 114
    {1.0, 0.0, 0.0, 0.0},//Element broni: Zamek, 115
    {1.0, 0.0, 0.0, 0.0},//Element broni: Sprezyna powrotna, 116
    {1.0, 0.0, 0.0, 0.0},//Element broni: Nasada lufy, 117
    {1.0, 0.0, 0.0, 0.0},//Element broni: Sprezyna spustu, 118
    {1.0, 0.0, 0.0, 0.0},//Element broni: Spust, 119
    {0.9, 0.0, 0.0, 0.0},//Zestaw narzedzi (Bron), 120
    {0.9, 0.0, 0.0, 0.0},//wolny_slot_przedmiotu1, 121
    {0.9, 0.0, 0.0, 0.0},//Zestaw medyczny, 122
    {0.8, 0.0, 0.0, 0.0},//Mut-warzywo, 123
    {1.3, 0.0, 0.0, 0.0},//Korzen ksadrowy, 124
    {1.0, 0.0, 0.0, 0.0},//Necik piegowaty, 125
    {0.8, 0.0, 0.0, 0.0},//Zimnokwiat piasczysty, 126
    {1.0, 0.0, 0.0, 0.0},//Krwawa Lespedoza, 127
    {0.8, 0.0, 0.0, 0.0},//Zmutowana Lucerna, 128
    {0.3, 0.0, 0.0, 0.0},//Zmutowany Krwawnik, 129
    {1.0, 0.0, 0.0, 0.0},//Dzika Ankrecja, 130
    {0.6, 0.0, 0.0, 0.0},//Xadricaria srebrzysta, 131
    {0.2, 0.0, 0.0, 0.0},//Kiew wodnisty, 132
    {0.9, 0.0, 0.0, 0.0},//Krótkofalówka, 133
    {1.0, 0.0, 0.0, 0.0},//Napromieniowany gruz, 134
    {0.9, 90.0, 90.0, 0.0},//Zgnieciona puszka, 135
    {0.9, 0.0, 0.0, 0.0},//Moduł elektryczny, 136
    {1.0, 0.0, 0.0, 0.0},//Złom, 137
    {0.9, 0.0, 90.0, 0.0},//Gumowy kalosz, 138
    {0.7, 0.0, 0.0, 0.0},//Karton, 139
    {0.8, 0.0, 0.0, 0.0},//Papier toaletowy, 140
    {0.9, 0.0, 0.0, 0.0},//Stara deskorolka, 141
    {0.8, 90.0, 0.0, 0.0},//Miotla, 142
    {0.9, 0.0, 0.0, 0.0},//Zkorodowana patelnia, 143
    {0.9, 0.0, 0.0, 0.0},//Zegarek, 144
    {0.9, 0.0, 90.0, 0.0},//Lom, 145
    {1.0, 90.0, 0.0, 0.0},//Mlotek, 146
    {0.9, 0.0, 0.0, 0.0},//Licznik Geigera, 147
    {1.0, 0.0, 0.0, 0.0},//Mapa, 148
    {1.0, 0.0, 0.0, 0.0},//Kompas, 149
    {1.0, 0.0, 0.0, 0.0},//GPS, 150
    {0.8, 0.0, 0.0, 0.0},//Syrop Haps 10, 151
    {0.8, 0.0, 0.0, 0.0},//Syrop Haps 25, 152
    {0.8, 0.0, 0.0, 0.0},//Syrop Haps 50, 153
    {0.8, 0.0, 0.0, 0.0},//Syrop AntiRad 10, 154
    {0.8, 0.0, 0.0, 0.0},//Syrop AntiRad 25, 155
    {0.8, 0.0, 0.0, 0.0},//Syrop AntiRad 50, 156
    {0.8, 0.0, 0.0, 0.0},//Syrop na wytrzymalosc, 157
    {1.0, 0.0, 0.0, 0.0},//Ubranie, 158
    {1.0, 0.0, 0.0, 0.0},//Wędka, 159
    {1.0, 0.0, 0.0, 0.0},//Bandana zielona, 160
    {1.0, 0.0, 0.0, 0.0}, //Bandana niebieska, 161
    {1.0, 0.0, 0.0, 0.0}, //Bandana czarna, 162
    {1.0, 0.0, 0.0, 0.0}, //Bandana biała, 163
    {1.0, 0.0, 0.0, 0.0},//Okulary owalne: czerwone, 164
    {1.0, 0.0, 0.0, 0.0},//Okulary owalne: pomaranczowe, 165
    {1.0, 0.0, 0.0, 0.0},//Okulary owalne: zielone, 166
    {1.0, 0.0, 0.0, 0.0},//Okulary owalne: niebieskie, 167
    {1.0, 0.0, 0.0, 0.0},//Okulary owalne: rozowe, 168
    {1.0, 0.0, 0.0, 0.0},//Okulary owalne: ciemne, 169
    {1.0, 0.0, 0.0, 0.0},//Okulary ochronne: zolte, 170
    {1.0, 0.0, 0.0, 0.0},//Okulary ochronne: pomaranczowe, 171
    {1.0, 0.0, 0.0, 0.0},//Okulary ochronne: czerwone, 172
    {1.0, 0.0, 0.0, 0.0},//Okulary ochronne: niebieskie, 173
    {1.0, 0.0, 0.0, 0.0},//Okulary ochronne: zielone, 174
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: czarne, 175
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: niebieskie, 176
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: fioletowe, 177
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: rozowe, 178
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: czerwone, 179
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: pomaranczowe, 180
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: zolte, 181
    {1.0, 0.0, 0.0, 0.0},//Okulary pilotki: zielone, 182
    {1.0, 0.0, 0.0, 0.0},//Okulary kwadratowe: siwe, 183
    {1.0, 0.0, 0.0, 0.0},//Okulary kwadratowe: zolte, 184
    {1.0, 0.0, 0.0, 0.0},//Okulary kwadratowe: czerwone, 185
    {1.0, 0.0, 0.0, 0.0},//Okulary kwadratowe: czarne, 186
    {1.0, 0.0, 0.0, 0.0},//Okulary policyjne: czarne, 187
    {1.0, 0.0, 0.0, 0.0},//Okulary policyjne: czerwone, 188
    {1.0, 0.0, 0.0, 0.0},//Okulary policyjne: niebieskie, 189
    {1.0, 0.0, 0.0, 0.0},//Kaszkietowka: zielona, 190
    {1.0, 0.0, 0.0, 0.0},//Kaszkietowka: szara, 191
    {1.0, 0.0, 0.0, 0.0},//Kaszkietowka: czarna, 192
    {1.0, 0.0, 0.0, 0.0},//Kaszkietowka: niebieska, 193
    {1.0, 0.0, 0.0, 0.0},//Kaszkietowka: elektryczna, 194
    {1.0, 0.0, 0.0, 0.0},//Czapka: czarna, 195
    {1.0, 0.0, 0.0, 0.0},//Czapka: szara, 196
    {1.0, 0.0, 0.0, 0.0},//Kapelusz: szary, 197
    {1.0, 0.0, 0.0, 0.0},//Kapelusz: czarny, 198
    {1.0, 0.0, 0.0, 0.0},//Kapelusz: niebieski, 199
    {1.0, 0.0, 0.0, 0.0},//Kapelusz: zielony, 200
    {1.0, 0.0, 0.0, 0.0},//Kapelusz: czerwony, 201
    {1.0, 0.0, 0.0, 0.0}//Kapelusz: zolty, 202
};

new ItemCountOnMap[MAX_ITEMS];

stock StackedItem(item_id)//0 - nie stackujacy, 1 - stackujacy
{
    switch(item_id)
    {
        case 1..46: return 0;
        case 54..55: return 0;
        case 67..68: return 0;
        case 74: return 0;
        case 120..122: return 0;
    }
    return 1;
}

stock ItemCanConfig(item_id)//1 - konfigurowalny(w menu zamiast przestań używać jest 'konfiguruj'), 0 - niekonfigurowalny 
{
    switch(item_id)
    {
        case 133: return 1;//Krótkofalówka
        case 150: return 1;//GPS
        case 160..163: return 1;//Bandany
        case 164..189: return 1;//Okularki
        case 190..202: return 1;//Czapki
    }   
    return 0;
}