//***********************************************************************************************************************************CONFIG
#define ZMB_UPDATERATE 50 //co ile MS ma wykonywać się Zombie_Kolejka(czym mniejsza liczba tym szybciej)(domyślnie: 50)
#define ZMB_COUNTONE 15 //ile botów ma aktualizować za każdą kolejką(domyślnie: 30)
#define RESPAWN_TIME 60000//MS po ilu zombiak wraca do świata żywych
//***********************************************************************************************************************************CONFIG END
new Float:SpawnZombie[][] = 
{
	{-1767.6453,-1711.9976},
	{-1666.3484,-1761.4525},
	{-1686.4460,-1863.8662},
	{-1880.4098,-1771.7605},
	{-1860.1469,-1681.9728},
	{-2218.1863,-2150.4805},
	{-2408.9861,-2168.9419},
	{-2410.5840,-2404.7793},
	{-2559.1809,-2430.1689},
	{-2345.2759,-2666.6321},
	{-2486.5151,-2635.9070},
	{-2694.8235,-2332.1667},
	{-2673.9519,-2611.2131},
	{-2555.7036,-2787.9656},
	{-1981.7379,-2807.6233},
	{-2246.2842,-2584.2422},
	{-2132.2700,-2719.5283},
	{-1865.0427,-2649.1555},
	{-1535.7449,-2740.0891},
	{-1396.0776,-2902.1968},
	{-1260.0468,-2714.9131},
	{-1471.5516,-2610.3652},
	{-1336.0066,-2481.6899},
	{-1661.3647,-2545.3667},
	{-1285.3502,-2388.7190},
	{-1304.4954,-2170.5107},
	{-1233.0347,-2119.7888},
	{-1367.7574,-2117.3601},
	{-1631.8269,-1991.5515},
	{-1686.0404,-2175.6750},
	{-1908.8644,-2093.9758},
	{-1950.7815,-2368.3843},
	{-2758.3179,-2008.0881},
	{-2942.6714,-1715.9872},
	{-2919.3311,-1453.3877},
	{-2899.5642,-1254.3953},
	{-2218.2102,-1124.9043},
	{-2544.7097,-958.1459},
	{-2147.6565,-1962.3899},
	{-2491.0837,-1899.0962},
	{-2798.7607,-1747.3954},
	{-2755.4595,-1431.1116},
	{-2523.9905,-1123.5533},
	{-2565.4580,-1481.3831},
	{-2342.0251,-1608.1067},
	{-1991.1066,-1552.5657},
	//new
	{-2555.2200,-2570.6963},
	{-2443.6785,-2677.8101},
	{-2211.6362,-2758.8240},
	{-2000.7261,-2739.3406},
	{-1900.0540,-2702.6558},
	{-1601.9254,-2769.2949},
	{-1473.8021,-2859.4961},
	{-1301.3181,-2882.9895},
	{-1337.0118,-2765.8884},
	{-1424.8593,-2726.4268},
	{-1545.0548,-2637.4521},
	{-1724.8397,-2559.6184},
	{-1856.9203,-2452.0305},
	{-1964.2076,-2463.5513},
	{-2299.5308,-2450.7026},
	{-2084.8494,-2013.4943},
	{-2020.5959,-1836.4395},
	{-1752.3561,-1807.3585},
	{-2316.5037,-1094.0649},
	{-2529.5388,-925.8294},
	{-1618.1913,-1864.4454},
	{-1469.4768,-1911.1893},
	{-1691.1818,-1896.4484},
	{-1862.8640,-1921.9307},
	{-1954.3011,-1942.7589},
	{-1975.3269,-2031.6207},
	{-1738.0607,-1986.3513},
	{-1699.6300,-2096.9763},
	{-1977.7947,-2209.0112},
	{-1804.7987,-2214.3684},
	{-1738.5425,-2300.0220},
	{-1865.7727,-2374.8652},
	{-1763.5645,-2442.8250},
	{-1592.9891,-2487.3821},
	{-1376.3475,-2461.3628},
	{-1222.5645,-2638.9841}
};

enum z_system_info
{
	miejsce_spawnu = 0,
	bool:spacer,
	q_loop_start,
	q_last_bot,
	bool:q_restart,
	maxnpc
};


new Zombie_system[z_system_info];
new Zombie_skins[] = {162, 160, 200, 212, 230, 137, 181, 134, 77, 78, 79};
//new mikolajid;
enum zombieinfo
{
    Float:sx,//miejsce spawnu
    Float:sy,//miejsce spawnu
    Float:sz,//miejsce spawnu
    Float:wx,//aktualna pozycja
    Float:wy,//aktualna pozycja
    Float:wz,//aktualna pozycja
    bool:use_anim,//czy używa animacji
    autoZ_time,
    autoZ_action,
    can_spawn
};
new Zombie[MAX_PLAYERS][zombieinfo];
new zombie_connected;
//**********************************************************************************************************************************SKRYPT
stock Init_Zombie()
{
	SetTimer("Zombie_Add", 50, false);
	MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/AngelFallZ.hmap");
	FCNPC_SetUpdateRate(200);
	if(FCNPC_InitMapAndreas(MapAndreas_GetAddress()))
	{
		print("[LOAD]FCNPC zaladowal poprawnie ZMap - zombie czuja grunt pod nogami.");
	}
	else
	{
		print("[ERROR]FCNPC NIE zaladowal ZMap - zombie nie wyczuwaja ziemi.");
	}
	SetTimer("Zombie_Kolejka", 15000, false);
	Zombie_system[maxnpc] = GetServerVarAsInt("maxnpc");
	printf("[LOAD]Inicjacja zombie zakonczona! Wpuszczam %d szwedaczy...", Zombie_system[maxnpc]);
	Zombie_system[spacer] = true;
	Zombie_system[q_loop_start] = GetPlayerPoolSize();
	return 1;
}
forward Zombie_Add();
public Zombie_Add()
{         
	new name[24];
	if(zombie_connected < Zombie_system[maxnpc])
	{
		format(name, 24, "SZWEDACZ_%d", zombie_connected + 1);
		FCNPC_Create(name);
		zombie_connected++;
		SetTimer("Zombie_Add", 10, false);
	}
	return 1;
}
//REAKCJA NA GRACZA
/*public FCNPC_OnUpdate(npcid)
{
	if(FCNPC_IsStreamedForAnyone(npcid))
	{
		UpdateZombieMovement(npcid);
	}
	return 1;
}*/
forward UpdateZombieMovement(j);
public UpdateZombieMovement(j)
{
	if(FCNPC_IsDead(j)) return 1;
	if(!IsPlayerAttachedObjectSlotUsed(j, 2)) SetPlayerAttachedObject(j, 2, 2907, 1, 0.038000,0.051000,0.027000,-94.999984, -0.299995, 89.399932, 1.0, 0.739000, 1.211000);
	//if(!IsPlayerAttachedObjectSlotUsed(j, 3)) SetPlayerAttachedObject(j, 3, 19065, 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);//czpaka świąteczn
	//if(j == mikolajid) return 1;
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		FCNPC_GetPosition(j, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]);
		if(Zombie[j][wz] < 1.2)
		{
			FCNPC_SetHealth(j, FCNPC_GetHealth(j)-10.0);
		}
		//wykrywanie ogniska - start
		for(new p = GetPlayerPoolSize(); p != -1; p--)
		{
			if(ognisko[p][o_status] <= 299 && ognisko[p][o_status])
			{
				if(InRange(j, 30.0, ognisko[p][o_X], ognisko[p][o_Y], ognisko[p][o_Z])) 
				{
					Zombie_WalkAnimStop(j);
					FCNPC_Stop(j);
					return 1;
				}
			}
		}
		//wykrywanie ogniska - stop
		if(IsPlayerInRangeOfPoint(i, 9.5, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]) && IsPlayerInAnyVehicle(i))
		{
			Zombie_WalkAnimStop(j);
			FCNPC_Stop(j);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(i, 10.0, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]) && gracz[i][BWTime])
		{
			Zombie_Spaceruj(j);
			if(FCNPC_IsAttacking(j))
			{
				FCNPC_StopAttack(j);
			}
			return 1;
		}
		else if(IsPlayerInRangeOfPoint(i, 1.1, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]))
		{
			givenDamage[i][j] = true;
			Zombie_WalkAnimStop(j);
			FCNPC_MeleeAttack(j, -1);
			TakePlayerHP(i, 10);
			return 1;
		}
		else if(FCNPC_IsAttacking(j))
		{
			FCNPC_StopAttack(j);
		}
		if(IsPlayerInRangeOfPoint(i, (GetHalas(i)*2)-4.0, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]))
		{
			Zombie_WalkAnimStop(j);
			if(!NPCAntyCol(j, 4.0))
			{
				//GetPlayerPos(i, gracz[i][PosX], gracz[i][PosY], gracz[i][PosZ]);
				if(!IsPointInAnyBaseArea(gracz[i][PosX], gracz[i][PosY], gracz[i][PosZ])) FCNPC_GoToPlayer(j, i, MOVE_TYPE_RUN, MOVE_SPEED_RUN, true, 1.1, true);
				else FCNPC_Stop(j);
				//FCNPC_GoToFixZ(j, gracz[i][PosX], gracz[i][PosY], gracz[i][PosZ], MOVE_TYPE_RUN, MOVE_SPEED_RUN, true, 1.1);
			} 
			else
			{
				FCNPC_Stop(j);
			}
			Zombie[j][autoZ_time] = gettime();
		} 
		else 
		{
			if(!IsPlayerInRangeOfPoint(i, 10.0, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]))
			{
				if(Zombie_system[spacer]) Zombie_Spaceruj(j);
			}
		}
	}
	return 1;
}


stock Zombie_WalkAnimStop(zombieid)
{
	if(Zombie[zombieid][use_anim])
	{
		ClearAnimations(zombieid);
		Zombie[zombieid][use_anim] = false;
	}
	return 1;
}

forward Zombie_Spaceruj(j);
public Zombie_Spaceruj(j)
{
	if(IsPlayerNPC(j))
	{
		if(gettime() - Zombie[j][autoZ_time] < 3) return 1;
		Zombie[j][autoZ_action] = MRandom(2);
		Zombie[j][autoZ_time] = gettime();
		if(Zombie[j][autoZ_action])
		{
			new Float:Xrand,Float:Yrand,Float:Zrand,Float:Angle;
			FCNPC_GetPosition(j, Zombie[j][wx], Zombie[j][wy], Zombie[j][wz]);
			new rand1=random(2),rand2=random(2);
			if(rand1==0) Xrand=Zombie[j][wx]+10+float(random(10));
			else Xrand=Zombie[j][wx]-10-float(random(10));
			if(rand2==0) Yrand=Zombie[j][wy]+10+float(random(10));
			else Yrand=Zombie[j][wy]-10-float(random(15));
			if((Xrand-Zombie[j][wx])>0&&(Yrand-Zombie[j][wy])>0) Angle=atan((Yrand-Zombie[j][wy])/(Xrand-Zombie[j][wx]));
			else Angle=atan((Yrand-Zombie[j][wy])/(Xrand-Xrand-Zombie[j][wx]))-180;
			if(!Zombie[j][use_anim])
			{
				ApplyAnimation(j,"PED","WOMAN_walkold",3.1,1,1,1,1,0,1);
				Zombie[j][use_anim] = true;
			}
			FCNPC_SetAngle(j,Angle);
			if(!IsPointInAnyBaseArea(Xrand, Yrand, Zrand)) FCNPC_GoTo(j, Xrand, Yrand, Zrand, MOVE_TYPE_WALK, MOVE_SPEED_WALK, true);
		}
		else
		{
			Zombie_WalkAnimStop(j);
			FCNPC_Stop(j);
		}
	}
	return 1;
}

stock NPCAntyCol(npcid, Float:range)
{
	for(new pd; pd < MAX_PLAYERS; pd++)
	{
		if(IsPlayerNPC(pd) && npcid > pd && !FCNPC_IsDead(pd))
		{
			if(IsPlayerInRangeOfPoint(npcid, range, Zombie[pd][wx], Zombie[pd][wy], Zombie[pd][wz])) return 1;
		}
	}
	return 0;
}

public FCNPC_OnDeath(npcid, killerid, weaponid)
{
	SetTimerEx("RespawnZ", RESPAWN_TIME, 0, "d", npcid);
	//SendClientMessageToAllEx(-1, "npcid: %d, killerid: %d, weaponid: %d", npcid, killerid, weaponid);
	if(killerid == INVALID_PLAYER_ID)
	{
		Zombie[npcid][sx] = SpawnZombie[Zombie_system[miejsce_spawnu]][0];
		Zombie[npcid][sy] = SpawnZombie[Zombie_system[miejsce_spawnu]][1];
		Zombie_system[miejsce_spawnu]++;
		if(Zombie_system[miejsce_spawnu] >= sizeof(SpawnZombie))
		{
			Zombie_system[miejsce_spawnu] = 0;
		}
	}
	else
	{
		FCNPC_GetPosition(npcid, Zombie[npcid][wx], Zombie[npcid][wy], Zombie[npcid][wz]);
		GiveExp(killerid, 1, true, Zombie[npcid][wx], Zombie[npcid][wy], Zombie[npcid][wz]);
		if(random(4) == 2)
		{
			CreateItemForWorld(78, 1, 100, 100, Zombie[npcid][wx], Zombie[npcid][wy], Zombie[npcid][wz], 0);
		}
		gracz[killerid][KillZombies]++;
		mq_format("UPDATE `Konta` SET `KillZombies`='%d' WHERE `id`='%d';", gracz[killerid][KillZombies], gracz[killerid][UID]);
		mq_send("QKillZombies");
	}
	return 1;
}

forward RespawnZ(npcid);
public RespawnZ(npcid)
{
	Zombie[npcid][can_spawn] = true;
	for(new pd = 0; pd < MAX_PLAYERS; pd++)
	{
		if(!IsPlayerNPC(pd) && IsPlayerInRangeOfPoint(pd, 10, Zombie[npcid][sx], Zombie[npcid][sy], Zombie[npcid][sz]))
		{
			Zombie[npcid][can_spawn] = false;
			break;
		} 
	}
	if(Zombie[npcid][can_spawn])
	{
		FCNPC_Respawn(npcid);
		FCNPC_SetHealth(npcid, 100.0);
		FCNPC_SetPosition(npcid,  Zombie[npcid][sx], Zombie[npcid][sy], Zombie[npcid][sz]);
		FCNPC_SetSkin(npcid, Zombie_skins[random(sizeof(Zombie_skins))]);
		FCNPC_SetAngle(npcid, random(200));
		SetPlayerColor(npcid, 0xAA333300);
	}
	else
	{
		SetTimerEx("RespawnZ", RESPAWN_TIME, false, "d", npcid);
	}
	return 1;
}

public FCNPC_OnCreate(npcid)
{
	new Float:zX,Float:zY,Float:zXrand,Float:Yrand;
	zX = SpawnZombie[Zombie_system[miejsce_spawnu]][0];
	zY = SpawnZombie[Zombie_system[miejsce_spawnu]][1];
	while(IsPointInAnyBaseArea(zX, zY, 0.0))
	{
		zX = SpawnZombie[Zombie_system[miejsce_spawnu]][0];
		zY = SpawnZombie[Zombie_system[miejsce_spawnu]][1];
		Zombie_system[miejsce_spawnu]++;
		if(Zombie_system[miejsce_spawnu] >= sizeof(SpawnZombie))
		{
			Zombie_system[miejsce_spawnu] = 0;
		}
	}
	new string_podpis[32];
	format(string_podpis, 32, "{3f3f3f}SZWĘDACZ");
	CreateDynamic3DTextLabel(string_podpis, 0x99001FAA, 0.0, 0.0, 0.0, 30.0, npcid);
	new rand1=random(2),rand2=random(2);
	if(rand1==0) zXrand=zX+7+float(random(7));
	else zXrand=zX-7-float(random(7));
	if(rand2==0) Yrand=zY+7+float(random(7));
	else Yrand=zY-7-float(random(7));
	new Float:calcZ;
	MapAndreas_FindZ_For2DCoord(zXrand, Yrand, calcZ);
	Zombie[npcid][sx] = zXrand;
	Zombie[npcid][sy] = Yrand;
	Zombie[npcid][sz] = calcZ+1.0;
	FCNPC_Spawn(npcid,  Zombie_skins[random(sizeof(Zombie_skins))], zXrand, Yrand, Zombie[npcid][sz]);
    	//ApplyAnimation(npcid,"PED","WOMAN_walkold",3.1,1,1,1,1,0,1);
	ClearAnimations(npcid);
	FCNPC_SetHealth(npcid, 100.0);
	FCNPC_GoTo(npcid, zXrand+2, Yrand+3, calcZ+2, MOVE_TYPE_RUN, 1.0, true);
	SetPlayerColor(npcid, 0xAA333300);
	Zombie_system[miejsce_spawnu]++;
	if(Zombie_system[miejsce_spawnu] >= sizeof(SpawnZombie))
	{
		Zombie_system[miejsce_spawnu] = 0;
	}
	/*if(!mikolajid) mikolajid = npcid;
	FCNPC_SetPosition(mikolajid, -1967.3983,-1606.3917,88.5833);
	FCNPC_SetAngle(mikolajid, 149.4146);
	FCNPC_SetInvulnerable(mikolajid);*/
	return 1;
}

//******************************************************************************************funkcja aktualizuj±ca boty <3
forward Zombie_Kolejka();
public Zombie_Kolejka()
{
	Zombie_system[q_loop_start] = Zombie_system[q_last_bot];
	for(new i = Zombie_system[q_loop_start]; i > (Zombie_system[q_loop_start]-ZMB_COUNTONE); i--)
	{
		if(IsPlayerNPC(i))
		{
			if(FCNPC_IsStreamedForAnyone(i)) UpdateZombieMovement(i);
		}
		else if(!IsPlayerNPC(i))
		{
			Zombie_system[q_restart] = true;
			break;
		}
	}
	if(!Zombie_system[q_restart])
	{ 
		Zombie_system[q_last_bot] = (Zombie_system[q_loop_start]-ZMB_COUNTONE);
	}
	else
	{
		Zombie_system[q_restart] = false;
		Zombie_system[q_last_bot] = GetPlayerPoolSize();
	}
	Process_Geiger();
	SetTimer("Zombie_Kolejka", ZMB_UPDATERATE, false);
	return 1;
}
//FIX GOTO
/*------------------
-   FCNPC_GoToFixZ 0.1
-   This Function fix Z ground of FCNPC in mostly cases
-   By Bruno da Silva @ ipsBruno
------------------------------------*/
stock FCNPC_GoToFixZ(n, Float:x, Float:y, Float:z, type = MOVE_TYPE_AUTO, Float: speed, bool: mapAndreas = true, Float:radius = 0.0, bool:getangle = true, Float: pitch = 0.1) 
{
    mapAndreas = true;
    
	static
		Float:a[3],
		Float:b[3];

	FCNPC_GetPosition(n, a[0], a[1], a[2]);

	b[0] = x, b[1] = y, b[2] = z;

	static Float:c[3];
	static Float:d[3];

	static Float:angle;

	angle = (atan2(a[0]-b[0], a[1]-b[1]))+180.0;

	if(angle > 360.0) angle -= 360.0;

	static Float: i;

	i = pitch;

	static Float: j;

	j = VectorSize(a[0]-b[0], a[1]-b[1], 0.0);

	while( i <= (j) ) {

		c[0]=a[0]+(i*floatsin(angle,degrees));
		c[1]=a[1]+(i*floatcos(angle,degrees));

		d[0]=a[0]+((i-pitch)*floatsin(angle,degrees));
		d[1]=a[1]+((i-pitch)*floatcos(angle,degrees));

		c[2] = a[2]+(i*( (a[2]-b[2]==0.0?0.0000001:a[2]-b[2])/j));
		CA_FindZ_For2DCoord(d[0],d[1],d[2]);

		i += pitch;

		if (  d[2] - c[2] > 1.0 ) { 
			mapAndreas = false;
			break;
		}

	}

	return FCNPC_GoTo( n, x, y, z,  type, speed, mapAndreas, radius, getangle);
}
//**************************************************************************************KOMENDY
/*CMD:autoz(playerid, params[])
{
	if(Zombie_system[spacer])
	{
		SendClientMessage(playerid, -1, "AutoZ zostało wyłączone.");
		Zombie_system[spacer] = false;
	}
	else
	{
		SendClientMessage(playerid, -1, "AutoZ zostało włączone.");
		Zombie_system[spacer] = true;
	}
	return 1;
}
CMD:respawnzm(playerid, params[])
{
	SendClientMessage(playerid, -1, "Wszystkie zombie wróciły na swoje miejsce spawnu.");
	for (new i = 0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerNPC(i))
		{
			RespawnZ(i);
		}
	}
	return 1;
}
CMD:gz(playerid, params[])
{
	new Float:range, ilosc, go;
	if(sscanf(params,"fdd", range, ilosc, go)) return SendClientMessage(playerid, -1, "/gz [odleglosc] [ilosc] [go]");
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	new Float:gopos[3];
	gopos[0] = pos[0];
	gopos[1] = pos[1];
	gopos[2] = pos[2];
	GetXYInFrontOfPlayer(playerid, pos[0], pos[1], range);
	new check_ilosc;
	new Float:hrandom[2];
	for (new i = 0; i<MAX_PLAYERS; i++)
	{
		if(check_ilosc==ilosc) break;
		if(IsPlayerNPC(i) && !FCNPC_IsDead(i))
		{
			FCNPC_Stop(i);
			MRandFloatRange(0.5, 37.0, hrandom[0]);
			MRandFloatRange(0.5, 37.0, hrandom[1]);
			FCNPC_SetPosition(i, pos[0]+hrandom[0], pos[1]-hrandom[1], pos[2]+1);
			if(go)
			{
				FCNPC_GoTo(i,gopos[0]+hrandom[0], gopos[1]-hrandom[1], gopos[2],MOVE_TYPE_RUN, MOVE_SPEED_RUN, true);
				ApplyAnimation(i,"PED","WOMAN_walkold",3.1,1,1,1,1,0,1);
				Zombie[i][use_anim] = true;
			}
			check_ilosc++;
		}
	}
	SendClientMessage(playerid, -1, "WYKONANO!");
	return 1;
}*/