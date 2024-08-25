//MAKRO
#define InRange IsPlayerInRangeOfPoint
#define chrtoupper(%1) (((%1) > 0x60 && (%1) <= 0x7A) ? ((%1) ^ 0x20) : (%1))//powiekszanie pierwszej litery
//DIALOGI
#define INFO_DIALOG 111
//Attach SLOT------------------------------------
//siłka: 0,1
#define GYM_ATTACH_INDEX1 (0)
#define GYM_ATTACH_INDEX2 (1)
#define GYM_ATTACH_INDEX3 (0)
//bandana :
#define BANDANA_SLOT 2
//#wędka: 3
//okulary: 4
#define OKULARY_SLOT 4
//#zombie corpse: 5
#define CZAPKA_SLOT 6
//#plecak: 7
//bronie: 8,9
//#LIMITY
#undef MAX_OBJECTS
#define MAX_OBJECTS 15000//maxymalna ilość obiektów 
#define MAX_DOORS 100
#define MAX_SPAMID 5//Maxymalna ilość spam ID
#define MAX_ACTOR 50
#define MAX_QUESTS 10
//APARTAMENTY
#define POS_K1OUT -2570.6946,-2138.6738,2317.1760
#define POS_K1IN -2559.4336,-2171.3862,2317.1760
#define POS_K2OUT -2570.6248,-2139.2727,2311.3760
#define POS_K2IN -2559.4910,-2171.3521,2301.8955
#define POS_K1MENU -2559.4675,-2183.3293,2317.5159
#define POS_K2MENU -2560.5088,-2174.0781,2301.8960
//MSELECTION EXTRAID
#define MSEL_GOBJECTS 1
//WINDA W KRYPCIE
#define WINDAID ObjectInfo[11062][oObject]
//POJAZDY
#define WORLD_VEHICLES 15
#define WORLDV_UELEKT 5000
#define WORLDV_ZASIL 5000
#define WORLDV_SMAR 2500
#define WORLDV_CHLOD 3500
#define WORLDV_KORB 5000
#define WORLDV_DDISTANCE 5.0
#define MAX_VEHICLEHP 2000.0
//DEFINICJE SPAMU
#define SPAM_CHAT 0
#define SPAM_CMD 1
#define SPAM_PM 2
#define SPAM_GYMKEY 3
//DEFINICJE LEFTNOTIFY
#define LN_RED 0
#define LN_GREEN 1
#define LN_YELLOW 2
#define LN_GREY 3
#define LN_BLUE 4
//szybkostrzelnosc dla antycbug
#define CBUG_INTERVAL_DEAGLE    700
#define CBUG_INTERVAL_SHOTGUN   1000
#define CBUG_INTERVAL_COMBATSG  340
#define CBUG_INTERVAL_COUNTRY   850
#define CBUG_INTERVAL_SNIPER    850
//kolorki
#define COL_EASY           "{FFF1AF}"
#define COL_WHITE          "{FFFFFF}"
#define COL_BLACK          "{000000}"
#define COL_BROWN          "{6E2500}"
#define COL_GREY           "{C3C3C3}"
#define COL_RED            "{F81414}"
#define COL_YELLOW         "{F3FF02}"
#define COL_ORANGE         "{FFAF00}"
#define COL_LIME           "{B7FF00}"
#define COL_CYAN           "{00FFEE}"
#define COL_BLUE           "{00C0FF}"
#define COL_GREEN          "{009933}"
#define COL_DBLUE          "{333399}"
#define COL_PURPLE 	"{ca00d6}"
#define COLOR_INFO 0x12ADDAFF
#define BEZOWY 0xFFFFADAA
#define BIALY 0xFFFFFFAA
#define BORDOWY 0x99001FAA
#define COLOR_DIS_RED 0xFF0000FF
#define BRAZOWY 0x997A00AA
#define CIEMNY_ZIELONY 0x336633AA
#define CZARNY 0x000000AA
#define CZERWONY 0xFF0000AA
#define FIOLETOWY 0x9E3DFFAA
#define COLOR_PURPLE 0x9E3DFFAA
#define NIEBIESKI 0x0000FFAA
#define POMARANCZOWY 0xFF8000AA
#define ROZOWY 0xFF66CCAA
#define SZARY 0xB0B0B0AA
#define ZIELONY 0x00CC00AA
#define ZOLTY 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_FIOLET 0x8000FFFF
#define COLOR_LIGHTBLUE 0x6DC5F3FF
#define COLOR_LIGHTYELLOW 0xFAEAA9FF
#define COLOR_LIGHTGREEN 0x00FF00FF
#define COLOR_LIGHTCOLOR_WHITE 0xF7A26FFF
#define COLOR_LIGHTRED 0xFF0000FF
#define COLOR_RED 0xFF2F2FFF
#define COLOR_GREEN 0x33AA33AA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_YELLOW2 0xFFFF00FF
#define COLOR_COLOR_WHITE 0xFF9900AA
#define COLOR_DARKCOLOR_WHITE 0xFF9900AA
#define COLOR_BLUE 0xFF9900AA
#define COLOR_SYSTEM 0xEFEFF7AA
#define COLOR_PINK 0xFF66FFAA
#define SPAWN_DELAY 3000
#define COLOR_KOMENDA 0xC83322FF
#define COLOR_GRAD1 0xC83322FF
#define COLOR_WIADOMOSC 0x00FF00FF
#define COLOR_BLACK 0x000000FF
#define COLOR_ADMIN 0xFF0000AA
#define COLOR_GD 0x1C86EE
#define AQUAGREEN   	0x03D687FF
#define COLOR_ORANGE 0xFF8000FF
#define COLOR_BLACK 0x000000FF