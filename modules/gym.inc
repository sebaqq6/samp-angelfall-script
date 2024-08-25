//USTAWIENIA DODAWANIA SILY
#define GYM_SERIA_LAWECZKA 20
#define GYM_SERIA_HANTLE 20
#define GYM_SERIA_BIEZNIA 150
#define GYM_SERIA_ROWERYK 150
new sgym_bieznia[MAX_PLAYERS] = 0;
new sgym_roweryk[MAX_PLAYERS] = 0;
new sgym_laweczka[MAX_PLAYERS] = 0;
new sgym_hantle[MAX_PLAYERS] = 0;
stock static Float://bieznia
run_machine_pos[ ][ ] =
{
    {-2464.4597,-2494.7634,2309.2158,191.7384},
    {-2466.6619,-2495.2275,2309.2158,192.6784}
};
//BIKE
stock static Float://roweryk
bike_pos[ ][ ] =
{
    {-2468.8706,-2497.0342,2309.2158,9.6900}
};
//Bench
stock static Float://lawczeka pos
bench_pos[ ][ ] =
{
    {-2468.5847,-2490.6121,2309.2158,18.1267},
    {-2466.9106,-2490.1147,2309.2158,15.3067},
    {-2465.1162,-2489.7817,2309.2158,13.7399},
    {-2463.3052,-2489.1736,2309.2158,12.1733},
    {-2461.4434,-2488.7988,2309.2158,15.3066},
    {-2459.4839,-2488.3242,2309.2158,14.6799}
};
stock static Float://pozycja sztangi duzej
barbell_pos[ ][ ] =
{
    {-2469.429931, -2489.179931, 2309.120117, 90.000000, 14.000000, 90.000000},
    {-2467.689941, -2488.739990, 2309.120117, 90.000000, 14.000000, 90.000000},
    {-2465.929931, -2488.300048, 2309.120117, 90.000000, 14.000000, 90.000000},
    {-2464.120117, -2487.850097, 2309.120117, 90.000000, 14.000000, 90.000000},
    {-2462.280029, -2487.389892, 2309.120117, 90.000000, 14.000000, 90.000000},
    {-2460.320068, -2486.899902, 2309.120117, 90.000000, 14.000000, 90.000000}
};
stock static Float://mata
dumb_pos[ ][ ] =
{
    {-2460.8057,-2494.4175,2309.3037,193.6184}
};
stock static Float://prawa hantla
dumb_bell_right_pos[ ][ ] =
{
    {-2460.060058, -2495.070068, 2308.379882, 90.000000, 13.399999, 90.000000}
};
stock static Float://lewa hantla
dumb_bell_left_pos[ ][ ] =
{
    {-2461.129882, -2495.330078, 2308.389892, 450.000000, 16.799999, 90.000000}
};
//BOOLS
//____TREAM____
new bool:TREAM_IN_USE[sizeof run_machine_pos]=false;
new TREAM_TIME_RUN[MAX_PLAYERS];
new PLAYER_CURRECT_TREAD[MAX_PLAYERS],
bool:PLAYER_INTREAM[MAX_PLAYERS]=false;
//____BIKE___
new bool:BIKE_IN_USE[sizeof bike_pos]=false;
new BIKE_TIME_RUN[MAX_PLAYERS];
new PLAYER_CURRECT_BIKE[MAX_PLAYERS],
bool:PLAYER_INBIKE[MAX_PLAYERS]=false;
//___BENCH___
new bool:BENCH_IN_USE[sizeof bench_pos]=false;
new PLAYER_CURRECT_BENCH[MAX_PLAYERS],
bool:PLAYER_INBENCH[MAX_PLAYERS]=false;
//___DUMB_BELL___
new bool:DUMB_IN_USE[sizeof bench_pos]=false;
new PLAYER_CURRECT_DUMB[MAX_PLAYERS],
bool:PLAYER_INDUMB[MAX_PLAYERS]=false;
//Gobale
new barbell_objects[sizeof barbell_pos];
new dumbell_right_objects[sizeof dumb_bell_right_pos];
new dumbell_left_objects[sizeof dumb_bell_left_pos];
//TEXTDRAWS
//________TREAD____________________
new PLAYER_TREAM_DIS_COUNT[MAX_PLAYERS];
//________BIKE_____________________
new PLAYER_BIKE_DIS_COUNT[MAX_PLAYERS];
//_______BENCH___________________
new PLAYER_BENCH_COUNT[MAX_PLAYERS];
//________DUMB_BELL_____________
new PLAYER_DUMB_COUNT[MAX_PLAYERS];
//--------------------------------------------------------
stock Init_Gym()
{
    //SPRZĘTY:
    //ławeczki:
    CreateObject(2629, -2468.879882, -2489.530029, 2308.209960, 0.000000, 0.000000, 13.899999);
    CreateObject(2629, -2467.149902, -2489.100097, 2308.209960, 0.000000, 0.000000, 13.899999);
    CreateObject(2629, -2465.379882, -2488.659912, 2308.209960, 0.000000, 0.000000, 13.899999);
    CreateObject(2629, -2463.570068, -2488.209960, 2308.209960, 0.000000, 0.000000, 13.899999);
    CreateObject(2629, -2461.729980, -2487.750000, 2308.209960, 0.000000, 0.000000, 13.899999);
    CreateObject(2629, -2459.770019, -2487.260009, 2308.209960, 0.000000, 0.000000, 13.899999);
    //maty
    CreateObject(2631, -2460.570068, -2495.149902, 2308.250000, 0.000000, 0.000000, 13.600000);
    //rowery
    CreateObject(2630, -2468.449951, -2496.540039, 2308.209960, 0.000000, 0.000000, -166.800003);
    //bieżnie
    CreateObject(2627, -2464.179931, -2495.929931, 2308.189941, 0.000000, 0.000000, -166.300003);
    CreateObject(2627, -2466.320068, -2496.449951, 2308.189941, 0.000000, 0.000000, -166.300003);
    //Ruchome
    for(new o; o != sizeof (barbell_pos); o++)
    {
        barbell_objects[o] = CreateObject(2913, barbell_pos[ o ][ 0 ], barbell_pos[ o ][ 1 ], barbell_pos[ o ][ 2 ], barbell_pos[ o ][ 3 ], barbell_pos[ o ][ 4 ], barbell_pos[ o ][ 5 ] );
    }
    for(new o; o != sizeof (dumb_bell_right_pos); o++)
    {
        dumbell_right_objects[o] = CreateObject(3071, dumb_bell_right_pos[o][0],dumb_bell_right_pos[o][1],dumb_bell_right_pos[o][2],dumb_bell_right_pos[o][3],dumb_bell_right_pos[o][4],dumb_bell_right_pos[o][5]);
    }
    for(new o; o != sizeof (dumbell_left_objects); o++)
    {    
        dumbell_left_objects[o] = CreateObject(3072, dumb_bell_left_pos[o][0],dumb_bell_left_pos[o][1],dumb_bell_left_pos[o][2],dumb_bell_left_pos[o][3],dumb_bell_left_pos[o][4],dumb_bell_left_pos[o][5]);
    }
    //3dtexty
    for(new o; o != sizeof (bike_pos); o++)
    {
        CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Rowerek"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, bike_pos[o][0],bike_pos[o][1], bike_pos[o][2], 5.0);
    }
    for(new o; o != sizeof (dumb_pos); o++)
    {
        CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Hantle"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, dumb_pos[o][0], dumb_pos[o][1], dumb_pos[o][2], 5.0);
    }
    for(new o; o != sizeof (bench_pos); o++)
    {
        CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Ławeczka"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, bench_pos[o][0], bench_pos[o][1], bench_pos[o][2], 5.0);
    }
    for(new o; o != sizeof (run_machine_pos); o++)
    {
        CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Bieżnia"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, run_machine_pos[o][0], run_machine_pos[o][1], run_machine_pos[o][2], 5.0);
    }
    return 1;
}
stock gym_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    //schodzenie na sprzęciorów
    if((newkeys & KEY_SECONDARY_ATTACK ) && !(oldkeys & KEY_SECONDARY_ATTACK ))
    {
        if(PLAYER_INTREAM[playerid] == true)
        {
            if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
            GetOffTread(playerid); 
            return 1;
        }
        if(PLAYER_INBIKE[playerid] == true)
        {
            if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
            GetOffBIKE(playerid);
            return 1;
        }
        if(PLAYER_INBENCH[playerid] == true)
        {
            if(Spam(playerid, SPAM_GYMKEY, 11)) return 1;
            GetOffBENCH(playerid);
            return 1;
        }
        if(PLAYER_INDUMB[playerid] == true)
        {
            if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
            PutDownDUMB(playerid);
            return 1;
        }
    }
    //wchodzenie na sprzęcior
    if((newkeys & KEY_SECONDARY_ATTACK ) && !( oldkeys & KEY_SECONDARY_ATTACK ))
    {
        for( new o; o != sizeof run_machine_pos; o ++ )
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, run_machine_pos[ o ][ 0 ], run_machine_pos[ o ][ 1 ], run_machine_pos[ o ][ 2 ] ) )
            {
                if(TREAM_IN_USE[o]==false && PLAYER_INTREAM[playerid]==false)
                {
                    if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
                    if(Spam(playerid, SPAM_GYMKEY, 5)) return 1;
                    PLAYER_INTREAM[playerid]=true;
                    TREAM_IN_USE[o]=true;
                    PLAYER_CURRECT_TREAD[playerid]=o;
                    PLAYER_TREAM_DIS_COUNT[playerid]=0;
                    sgym_bieznia[playerid] = 0;
                    SetPlayerPos( playerid, run_machine_pos[ o ][ 0 ], run_machine_pos[ o ][ 1 ]+0.2, run_machine_pos[ o ][ 2 ] );
                    SetPlayerFacingAngle( playerid, run_machine_pos[ o ][ 3 ] );
                    TogglePlayerControllable( playerid, 0 );
                    ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_geton", 1, 0, 0, 0, 1, 0, 1 );
                    SetTimerEx( "TREAM_START", 2000, false, "d", playerid);
                    //SetPlayerCameraPos( playerid, run_machine_pos[ o ][ 0 ] -3, run_machine_pos[ o ][ 1 ] +3, run_machine_pos[ o ][ 2 ] + 0.5 );
                    //SetPlayerCameraLookAt( playerid, run_machine_pos[ o ][ 0 ], run_machine_pos[ o ][ 1 ], run_machine_pos[ o ][ 2 ]);
                }
                else
                {
                    GameTextForPlayer(playerid,"!", 5000, 4);
                }
            }
        }
        for( new b; b != sizeof bike_pos; b ++ )
        {
            if( IsPlayerInRangeOfPoint( playerid, 1.0, bike_pos[ b ][ 0 ], bike_pos[ b ][ 1 ], bike_pos[ b ][ 2 ] ) )
            {
                if(BIKE_IN_USE[b]==false && PLAYER_INBIKE[playerid]==false)
                {
                    if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
                    if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
                    //Bool Here
                    BIKE_IN_USE[b]=true;
                    PLAYER_INBIKE[playerid]=true;
                    PLAYER_CURRECT_BIKE[playerid]=b;
                    //clearn values
                    PLAYER_BIKE_DIS_COUNT[playerid]=0;
                    sgym_roweryk[playerid] = 0;
                    //SetPlayerPos
                    SetPlayerPos( playerid, bike_pos[ b ][ 0 ], bike_pos[ b ][ 1 ], bike_pos[ b ][ 2 ] );
                    SetPlayerFacingAngle( playerid, bike_pos[ b ][ 3 ] );
                    TogglePlayerControllable( playerid, 0 );
                    ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_geton", 1, 0, 0, 0, 1, 0, 1 );
                    //Set Timer
                    SetTimerEx( "BIKE_START", 2000, false, "d", playerid);
                    //SetPlayerCameraPos( playerid, bike_pos[ b ][ 0 ] +1, bike_pos[ b ][ 1 ] -1, bike_pos[ b ][ 2 ] + 0.5 );
                   // SetPlayerCameraLookAt( playerid, bike_pos[ b ][ 0 ], bike_pos[ b ][ 1 ], bike_pos[ b ][ 2 ]+0.5);
                }
                else
                {
                    GameTextForPlayer(playerid,"!", 5000, 4);
                }
            }
        }
        for (new g; g != sizeof bench_pos; g ++)
        {
            if( IsPlayerInRangeOfPoint( playerid, 1.0, bench_pos[ g ][ 0 ], bench_pos[ g ][ 1 ], bench_pos[ g ][ 2 ] ) )
            {
                if(BENCH_IN_USE[g]==false && PLAYER_INBENCH[playerid]==false)
                {
                    if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
                    if(Spam(playerid, SPAM_GYMKEY, 8)) return 1;
                    BENCH_IN_USE[g]=true;
                    PLAYER_INBENCH[playerid]=true;
                    PLAYER_CURRECT_BENCH[playerid]=g;
                    //clearn values
                    PLAYER_BENCH_COUNT[playerid]=0;
                    sgym_laweczka[playerid] = 0;
                    //SET POS NOW
                    TogglePlayerControllable( playerid, 0 );
                    SetPlayerPos( playerid, bench_pos[ g ][ 0 ], bench_pos[ g ][ 1 ], bench_pos[ g ][ 2 ] );
                    SetPlayerFacingAngle( playerid, bench_pos[ g ][ 3 ] );
                    ApplyAnimation( playerid, "benchpress", "gym_bp_geton", 1, 0, 0, 0, 1, 0, 1 );
                    SetTimerEx( "BENCH_START", 3800, 0, "dd", playerid, g);
                    //SetPlayerCameraPos( playerid, bench_pos[ g ][ 0 ]-1.5, bench_pos[ g ][ 1 ]+1.5, bench_pos[ g ][ 2 ] + 0.5 );
                    //SetPlayerCameraLookAt( playerid, bench_pos[ g ][ 0 ], bench_pos[ g ][ 1 ], bench_pos[ g ][ 2 ]);
                }
                else
                {
                    GameTextForPlayer(playerid,"!", 5000, 4);
                }
            }
        }
        for (new d; d != sizeof dumb_pos; d ++)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.5, dumb_pos[ d ][ 0 ], dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]))
            {
                if(DUMB_IN_USE[d]==false && PLAYER_INDUMB[playerid]==false)
                {
                    if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet na ~g~hali targowej~w~ badz u ~g~innego gracza~w~.", LN_RED);
                    if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
                    DUMB_IN_USE[d]=true;
                    PLAYER_INDUMB[playerid]=true;
                    PLAYER_CURRECT_DUMB[playerid]=d;
                    //clearn values
                    PLAYER_DUMB_COUNT[playerid]=0;
                    sgym_hantle[playerid] = 0;
                    //SET POS NOW
                    TogglePlayerControllable( playerid, 0 );
                    SetPlayerPos(playerid, dumb_pos[ d ][ 0 ], dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]);
                    SetPlayerFacingAngle( playerid, dumb_pos[ d ][ 3 ] );
                    ApplyAnimation( playerid, "Freeweights", "gym_free_pickup", 1, 0, 0, 0, 1, 0, 1 );
                    SetTimerEx( "DUMB_START", 2000, 0, "d", playerid);
                    //SetPlayerCameraPos( playerid, dumb_pos[ d ][ 0 ]+2.3, dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]+0.3 );
                    //SetPlayerCameraLookAt( playerid, dumb_pos[ d ][ 0 ], dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]+0.5);
                }
            }
        }
    }
    return 1;
}

stock IsPlayerInGym(playerid)
{
    if(InRange(playerid, 50.0, -2466.6572,-2493.2800,2309.2158)) return 1;
    return 0;
}


forward BIKE_START(playerid);
public BIKE_START(playerid)
{
    ApplyAnimation( playerid, "GYMNASIUM", "bike_start", 1, 1, 0, 0, 1, 0, 1);
    StartCombineMode(playerid, 4);
    SetTimerEx("BIKE_CHECK", 900, false, "d", playerid);
}
forward TREAM_START(playerid);
public TREAM_START(playerid)
{
    ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_sprint", 1, 1, 0, 0, 1, 0, 1);
    TREAM_TIME_RUN[playerid] = serwer[time_timestamp]+8;
    StartCombineMode(playerid, 3);
    SetTimerEx("TREAM_CHECK", 500, false, "d", playerid);
}
forward BENCH_START(playerid,OBJ_INDEX);
public BENCH_START(playerid,OBJ_INDEX)
{
    SetPlayerAttachedObject(playerid, GYM_ATTACH_INDEX1, 2913, 6);
    DestroyObject(barbell_objects[OBJ_INDEX]);
    StartCombineMode(playerid, 1);
}

forward DUMB_START(playerid);
public DUMB_START(playerid)
{
    SetPlayerAttachedObject(playerid,GYM_ATTACH_INDEX2, 3072, 5);//left hand
    SetPlayerAttachedObject(playerid,GYM_ATTACH_INDEX3, 3071, 6);//right hand
    DestroyObject(dumbell_right_objects[PLAYER_CURRECT_DUMB[playerid]]);
    DestroyObject(dumbell_left_objects[PLAYER_CURRECT_DUMB[playerid]]);
    StartCombineMode(playerid, 2);
}


stock DUMB_UP(playerid)
{
    switch(random( 2 ))
    {
        case 0: ApplyAnimation( playerid, "freeweights", "gym_free_A", 1, 0, 0, 0, 1, 0, 1 );
        case 1: ApplyAnimation( playerid, "freeweights", "gym_free_B", 1, 0, 0, 0, 1, 0, 1 );
    }
}

stock DUMB_DOWN(playerid)
{
    ApplyAnimation( playerid, "freeweights", "gym_free_down", 1, 0, 0, 0, 1, 0, 1 );
    PLAYER_DUMB_COUNT[playerid]++;
    sgym_hantle[playerid]++;
    Process_SeriaToSila(playerid);
    new str[64];
    format(str, 64, "Ilosc powtorzen: ~y~%d~n~~g~Wzrost sily za: ~y~%d", PLAYER_DUMB_COUNT[playerid], GYM_SERIA_HANTLE-sgym_hantle[playerid]);
    CombineTD_Left(playerid, str);
}

stock BENCH_UP(playerid)
{
    switch(random(2))
    {
        case 0: ApplyAnimation( playerid, "benchpress", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1 );
        case 1: ApplyAnimation( playerid, "benchpress", "gym_bp_up_B", 1, 0, 0, 0, 1, 0, 1 );
    }
}

stock BENCH_DOWN(playerid)
{
    ApplyAnimation( playerid, "benchpress", "gym_bp_down", 1, 0, 0, 0, 1, 0, 1 );
    PLAYER_BENCH_COUNT[playerid]++;
    sgym_laweczka[playerid]++;
    Process_SeriaToSila(playerid);
    new str[64];
    format(str, 64, "Ilosc powtorzen: ~y~%d~n~~g~Wzrost sily za: ~y~%d", PLAYER_BENCH_COUNT[playerid], GYM_SERIA_LAWECZKA-sgym_laweczka[playerid]);
    CombineTD_Left(playerid, str);
}

forward BIKE_CHECK(playerid);
public BIKE_CHECK(playerid)
{
    if(!PLAYER_INBIKE[playerid]) return 1;
    if(BIKE_TIME_RUN[playerid] >= serwer[time_timestamp])
    {
        ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_fast", 1, 1, 0, 0, 1, 0, 1 );
        PLAYER_BIKE_DIS_COUNT[playerid]++;
        sgym_roweryk[playerid]++;
        Process_SeriaToSila(playerid);
        new str[64];
        format(str, 64, "Pokonany dystans: ~y~%dm~n~~g~Wzrost sily za: ~y~%d", PLAYER_BIKE_DIS_COUNT[playerid], GYM_SERIA_ROWERYK-sgym_roweryk[playerid]);
        CombineTD_Left(playerid, str);
        format(str, 64, "00~r~:~w~%02d", BIKE_TIME_RUN[playerid]-serwer[time_timestamp]);
        CombineTD_Beside(playerid, str);
        SetTimerEx("BIKE_CHECK", 1000, false, "d", playerid);
    }
    else
    {
        ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_still", 1, 1, 0, 0, 1, 0, 1);
        SetTimerEx("BIKE_CHECK", 1000, false, "d", playerid);
    }
    return 1;
}

stock BIKE_RUN(playerid)
{
    BIKE_TIME_RUN[playerid] = serwer[time_timestamp]+7;
}

forward TREAM_CHECK(playerid);
public TREAM_CHECK(playerid)
{
    if(!PLAYER_INTREAM[playerid]) return 1;
    if(TREAM_TIME_RUN[playerid] >= serwer[time_timestamp])
    {
        PLAYER_TREAM_DIS_COUNT[playerid]++;
        sgym_bieznia[playerid]++;
        Process_SeriaToSila(playerid);
        new str[64];
        format(str, 64, "Pokonany dystans: ~y~%dm~n~~g~Wzrost sily za: ~y~%d", PLAYER_TREAM_DIS_COUNT[playerid], GYM_SERIA_BIEZNIA-sgym_bieznia[playerid]);
        CombineTD_Left(playerid, str);
        format(str, 64, "00~r~:~w~%02d", TREAM_TIME_RUN[playerid]-serwer[time_timestamp]);
        CombineTD_Beside(playerid, str);
        SetTimerEx("TREAM_CHECK", 700, false, "d", playerid);
    }
    else
    {
        FallOffTread(playerid);
    }
    return 1;
}

stock TREAM_RUN(playerid)
{
    TREAM_TIME_RUN[playerid] = serwer[time_timestamp]+7;
}

stock FallOffTread(playerid)
{
    StopCombineMode(playerid);
    ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_falloff", 1, 0, 0, 0, 1, 0, 1 );
    SetTimerEx( "REST_PLAYER", 2000, false, "i", playerid);
}
stock GetOffTread(playerid)
{
    ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_getoff", 1, 0, 0, 0, 1, 0, 1 );
    StopCombineMode(playerid);
    SetTimerEx( "REST_PLAYER", 3500, false, "i", playerid);
}
stock GetOffBENCH(playerid)
{
    ApplyAnimation(playerid, "benchpress", "gym_bp_getoff", 1, 0, 0, 0, 1, 0, 1 );
    StopCombineMode(playerid);
    SetTimerEx( "REST_PLAYER", 2500, false, "i", playerid);
}
stock PutDownDUMB(playerid)
{
    ApplyAnimation(playerid, "freeweights", "gym_free_putdown", 1, 0, 0, 0, 1, 0, 1 );
    StopCombineMode(playerid);
    SetTimerEx( "REST_PLAYER", 1000, false, "i", playerid);
}
stock GetOffBIKE(playerid)
{
    BIKE_TIME_RUN[playerid] = 0;
    ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_getoff", 1, 0, 0, 0, 1, 0, 1 );
    StopCombineMode(playerid);
    SetTimerEx( "REST_PLAYER", 2000, false, "i", playerid);
}

forward REST_PLAYER(playerid);
public REST_PLAYER(playerid)
{
    if(PLAYER_INTREAM[playerid]==true)
    {
        PLAYER_INTREAM[playerid]=false;
        TREAM_IN_USE[PLAYER_CURRECT_TREAD[playerid]]=false;
        REST_PLAYER_2(playerid);
    }
    if(PLAYER_INBIKE[playerid]==true)
    {
        PLAYER_INBIKE[playerid]=false;
        BIKE_IN_USE[PLAYER_CURRECT_BIKE[playerid]]=false;
        REST_PLAYER_2(playerid);
    }
    if(PLAYER_INBENCH[playerid]==true)
    {
        PLAYER_INBENCH[playerid]=false;
        BENCH_IN_USE[PLAYER_CURRECT_BENCH[playerid]]=false;
        barbell_objects[PLAYER_CURRECT_BENCH[playerid]] = CreateObject(2913, barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 0 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 1 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 2 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 3 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 4 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 5 ] );
        RemovePlayerAttachedObject( playerid, GYM_ATTACH_INDEX1 );
        SetTimerEx( "REST_PLAYER_2", 5000, false, "i", playerid);
    }
    if(PLAYER_INDUMB[playerid]==true)
    {
        PLAYER_INDUMB[playerid]=false;
        DUMB_IN_USE[PLAYER_CURRECT_DUMB[playerid]]=false;
        dumbell_right_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateObject(3071,dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][5]);
        dumbell_left_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateObject(3072,dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][5]);
        RemovePlayerAttachedObject(playerid,GYM_ATTACH_INDEX2);
        RemovePlayerAttachedObject(playerid,GYM_ATTACH_INDEX3);
        SetTimerEx( "REST_PLAYER_2", 1500, false, "i", playerid);
    }
}

forward REST_PLAYER_2(playerid);
public REST_PLAYER_2(playerid)
{
    ClearAnimations(playerid, 1);
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    return 1;
}

stock Gym_Disconnect(playerid)
{
    if(PLAYER_INTREAM[playerid]==true)
    {
        PLAYER_INTREAM[playerid]=false;
        TREAM_IN_USE[PLAYER_CURRECT_TREAD[playerid]]=false;
    }
    if(PLAYER_INBIKE[playerid]==true)
    {
        PLAYER_INBIKE[playerid]=false;
        BIKE_IN_USE[PLAYER_CURRECT_BIKE[playerid]]=false;
    }
    if(PLAYER_INBENCH[playerid]==true)
    {
        PLAYER_INBENCH[playerid]=false;
        BENCH_IN_USE[PLAYER_CURRECT_BENCH[playerid]]=false;
        barbell_objects[PLAYER_CURRECT_BENCH[playerid]] = CreateObject(2913, barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 0 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 1 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 2 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 3 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 4 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 5 ] );
        RemovePlayerAttachedObject( playerid, GYM_ATTACH_INDEX1);
    }
    if(PLAYER_INDUMB[playerid]==true)
    {
        PLAYER_INDUMB[playerid]=false;
        DUMB_IN_USE[PLAYER_CURRECT_DUMB[playerid]]=false;
        dumbell_right_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateObject(3071,dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][5]);
        dumbell_left_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateObject(3072,dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][5]);
        RemovePlayerAttachedObject(playerid, GYM_ATTACH_INDEX2);
        RemovePlayerAttachedObject(playerid, GYM_ATTACH_INDEX3);
    }
    ClearAnimations(playerid, 1);
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    return 1;
}

stock Process_SeriaToSila(playerid)
{
    if(sgym_bieznia[playerid] >= GYM_SERIA_BIEZNIA)
    {
        sgym_bieznia[playerid] = 0;
        if(isvip(playerid)) AddStrenght(playerid, 3);
        else AddStrenght(playerid, 1);
        GiveExp(playerid, 1);
    }
    else if(sgym_roweryk[playerid] >= GYM_SERIA_ROWERYK)
    {
        sgym_roweryk[playerid] = 0;
        if(isvip(playerid)) AddStrenght(playerid, 3);
        else AddStrenght(playerid, 1);
        GiveExp(playerid, 1);
    }
    else if(sgym_laweczka[playerid] >= GYM_SERIA_LAWECZKA)
    {
        sgym_laweczka[playerid] = 0;
        if(isvip(playerid)) AddStrenght(playerid, 3);
        else AddStrenght(playerid, 1);
        GiveExp(playerid, 1);
    }
    else if(sgym_hantle[playerid] >= GYM_SERIA_HANTLE)
    {
        sgym_hantle[playerid] = 0;
        if(isvip(playerid)) AddStrenght(playerid, 3);
        else AddStrenght(playerid, 1);
        GiveExp(playerid, 1);
    }
    return 1;
}


stock SetCombine_KarnetStr(playerid)
{
    new str[64];
    if(gracz[playerid][karnet] > serwer[time_timestamp])
    {
        new dd, gg, hh, mm;
        SecToTime(gracz[playerid][karnet]-serwer[time_timestamp], dd, gg, hh, mm);
        format(str, 64, "Karnet: ~g~%02d~w~:~g~%02d~w~:~g~%02d", gg, hh, mm);
    }
    else
    {
        format(str, 64, "Karnet: ~r~niewazny");
    }
    CombineTD_Right(playerid, str);
    return 1;
}


stock StrenghtDMG(playerid)
{
    switch(gracz[playerid][sila])
    {
        case 20..29: return 1;
        case 30..39: return 2;
        case 40..49: return 3;
        case 50..59: return 4;
        case 60..69: return 5;
        case 70..79: return 6;
        case 80..89: return 7;
        case 90..100: return 8;
    }
    return 0;
}


stock StrenghtCDN(playerid)
{
    switch(gracz[playerid][sila])
    {
        case 70..79: return 5;
        case 80..89: return 4;
        case 90..100: return 3;
    }
    return 6;
}

stock AddStrenght(playerid, val)
{
    if(gracz[playerid][sila] >= 100) return 0;
    new str[128];
    format(str, 128, "Rozwoj miesni ~g~wzrosl~w~ o: ~b~%d%%", val);
    LeftNotifyShow(playerid, "Miesnie", str, LN_GREEN);
    gracz[playerid][sila] += val;
    if(gracz[playerid][sila] > 100)
    {
        gracz[playerid][sila] = 100;
    }
    mq_format("UPDATE `Konta` SET `sila`='%d' WHERE `id`='%d';", gracz[playerid][sila], gracz[playerid][UID]);
    mq_send("QUpdateSila");
    return 1;
}

stock RemoveStrenght(playerid, val)
{
    if(gracz[playerid][sila] <= 0) return 0;
    new str[128];
    format(str, 128, "Rozwoj miesni ~g~zmalal~w~ o: ~b~%d%%", val);
    LeftNotifyShow(playerid, "Miesnie", str, LN_RED);
    gracz[playerid][sila] -= val;
    if(gracz[playerid][sila] < 0)
    {
        gracz[playerid][sila] = 0;
    }
    mq_format("UPDATE `Konta` SET `sila`='%d' WHERE `id`='%d';", gracz[playerid][sila], gracz[playerid][UID]);
    mq_send("QUpdateSila");
    return 1;
}
/*
CreateObject(2629, -2468.879882, -2489.530029, 2308.209960, 0.000000, 0.000000, 13.899999);//
CreateObject(2913, -2469.429931, -2489.179931, 2309.120117, 90.000000, 14.000000, 90.000000);//
CreateObject(2629, -2467.149902, -2489.100097, 2308.209960, 0.000000, 0.000000, 13.899999);//
CreateObject(2913, -2467.689941, -2488.739990, 2309.120117, 90.000000, 14.000000, 90.000000);//
CreateObject(2629, -2465.379882, -2488.659912, 2308.209960, 0.000000, 0.000000, 13.899999);//
CreateObject(2913, -2465.929931, -2488.300048, 2309.120117, 90.000000, 14.000000, 90.000000);//
CreateObject(2629, -2463.570068, -2488.209960, 2308.209960, 0.000000, 0.000000, 13.899999);//
CreateObject(2913, -2464.120117, -2487.850097, 2309.120117, 90.000000, 14.000000, 90.000000);//
CreateObject(2629, -2461.729980, -2487.750000, 2308.209960, 0.000000, 0.000000, 13.899999);//
CreateObject(2913, -2462.280029, -2487.389892, 2309.120117, 90.000000, 14.000000, 90.000000);//
CreateObject(2629, -2459.770019, -2487.260009, 2308.209960, 0.000000, 0.000000, 13.899999);//
CreateObject(2913, -2460.320068, -2486.899902, 2309.120117, 90.000000, 14.000000, 90.000000);//
CreateObject(2631, -2460.570068, -2495.149902, 2308.250000, 0.000000, 0.000000, 13.600000);//
CreateObject(3071, -2460.060058, -2495.070068, 2308.379882, 90.000000, 13.399999, 90.000000);//
CreateObject(3072, -2461.129882, -2495.330078, 2308.389892, 450.000000, 16.799999, 90.000000);//
CreateObject(2627, -2464.179931, -2495.929931, 2308.189941, 0.000000, 0.000000, -166.300003);//
CreateObject(2627, -2466.320068, -2496.449951, 2308.189941, 0.000000, 0.000000, -166.300003);//
CreateObject(2630, -2468.449951, -2496.540039, 2308.209960, 0.000000, 0.000000, -166.800003);//
*/