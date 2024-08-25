stock const
Float:BallSpawn[3] = {2706.9944, -1802.1829, 422.8372},
Float:Corners[4][3] =
{
    {2677.1453, -1748.0548, 422.8372},
    {2736.6797, -1747.9595, 422.8372},
    {2736.7180, -1856.2570, 422.8372},
    {2677.3398, -1856.5066, 422.8372}
};
new
Ball = -1,
pLastTick[MAX_PLAYERS],
BallHolder = -1,
PlayerText:pPowerTD[MAX_PLAYERS],
Text:PowerTD[2];
stock Init_Football()
{
    SetTimer("PowerBar", 50, true);
    CreateBall();
    fb_LoadCollisions();
    fb_LoadTextDraws();
    new sterowanie[1024];
    format(sterowanie, 1024, ""COL_EASY"["COL_LIME"STEROWANIE"COL_EASY"]"COL_WHITE"");
    format(sterowanie, 1024, "%s\n"COL_GREEN"LALT"COL_EASY" - Wrzuta", sterowanie);
    format(sterowanie, 1024, "%s\n"COL_GREEN"ENTER/F"COL_EASY" - Strzał", sterowanie);
    format(sterowanie, 1024, "%s\n"COL_GREEN"LPM"COL_EASY" - Przyjęcie", sterowanie);
    format(sterowanie, 1024, "%s\n"COL_GREEN"PPM"COL_EASY" - Podanie", sterowanie);
    CreateDynamic3DTextLabel(sterowanie, -1, 2676.2441,-1746.9526,422.8280, 10.0);
    return 1;
}
stock CreateBall()
{
    if(Ball != -1) return 0;
    Ball = CreateObject(2114, BallSpawn[0], BallSpawn[1], BallSpawn[2] - 0.875, 0, 0, 0, 100.0);
    SetObjectMaterial(Ball, 0, 14534, "ab_woozieA", "ab_wuzimirror", 0);
    PHY_InitObject(Ball, 2114, 1.0, 0.152039);
    PHY_RollObject(Ball);
    PHY_SetObjectFriction(Ball, 7.0);
    PHY_SetObjectAirResistance(Ball, 0.2);
    PHY_SetObjectGravity(Ball, 10.0);
    PHY_SetObjectZBound(Ball, _, _, 0.8);
    PHY_ToggleObjectPlayerColls(Ball, 1, 0.4, 1.3);
    return 1;
}
stock DestroyBall()
{
    PHY_DeleteObject(Ball);
    DestroyObject(Ball);
    Ball = -1;
}
stock GetBallPos(&Float:x, &Float:y, &Float:z)
{
    if(BallHolder != -1)
    {
        new
        Float:angle;
        GetPlayerPos(BallHolder, x, y, z);
        GetPlayerFacingAngle(BallHolder, angle);
        x += 0.6 * floatsin(-angle, degrees);
        y += 0.6 * floatcos(-angle, degrees);
        z -= 0.875;
    }
    else
    {
        GetObjectPos(Ball, x, y, z);
    }
    return 1;
}
stock RecreateBall()
{
    DestroyBall();
    CreateBall();
    BallHolder = -1;
    return 1;
}

stock fb_LoadCollisions()
{
    // Field
    PHY_CreateArea(2669.03, -1864.08, 2745.12, -1740.54, _, _, 500.0);
    // Goal
    PHY_CreateWall(2711.87, -1857.30, 2711.87, -1862.75, 0.5, _, 425.87);
    PHY_CreateWall(2711.87, -1862.75, 2701.92, -1862.75, 0.5, _, 425.87);
    PHY_CreateWall(2701.92, -1862.75, 2701.92, -1857.30, 0.5, _, 425.87);
    // Poprzeczka
    PHY_CreateWall(2701.92, -1857.30, 2711.87, -1857.30, _, 425.87 - 0.1, 425.87 + 0.1);
    // Pole
    PHY_CreateCylinder(2711.87, -1857.30, 0.3, _, _, 425.87);
    PHY_CreateCylinder(2701.92, -1857.30, 0.3, _, _, 425.87);
    // Goal
    PHY_CreateWall(2701.92, -1747.10, 2701.92, -1741.60, 0.5, _, 425.87);
    PHY_CreateWall(2701.92, -1741.60, 2711.89, -1741.60, 0.5, _, 425.87);
    PHY_CreateWall(2711.89, -1741.60, 2711.89, -1747.10, 0.5, _, 425.87);
    // Poprzeczka
    PHY_CreateWall(2711.89, -1747.10, 2701.92, -1747.10, _, 425.87 - 0.1, 425.87 + 0.1);
    // Pole
    PHY_CreateCylinder(2701.92, -1747.10, 0.3, _, _, 425.87);
    PHY_CreateCylinder(2711.89, -1747.10, 0.3, _, _, 425.87);
    //słupy przy ścianach
    PHY_CreateCylinder(2744.5193, -1840.2107, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2744.3826,-1815.0947, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2744.5232,-1790.2849, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2744.6116,-1765.2544, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2669.7029,-1765.1370, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2669.8381,-1790.2809, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2669.6665,-1815.1140, 1.5, _, _, 500.0);
    PHY_CreateCylinder(2669.7180,-1840.0453, 1.5, _, _, 500.0);
    return 1;
}

public PHY_OnObjectUpdate(objectid)
{
    if(objectid != Ball) return 1;
    new
    Float:x, Float:y, Float:z;
    GetBallPos(x, y, z);
    if(!(2669.03 < x < 2745.12 && -1864.08 < y < -1740.54))
    {
        RespawnBall();
    }
    else if(GetDistanceBetweenPoints(x, y, z, 2744.5193,-1840.2107,423.0513) < 1.5)
    {
        RespawnBall();
    }  
    else if(GetDistanceBetweenPoints(x, y, z, 2744.3826,-1815.0947,423.0513) < 1.5)
    {
        RespawnBall();
    }   
    else if(GetDistanceBetweenPoints(x, y, z, 2744.5232,-1790.2849,423.0513) < 1.5)
    {
        RespawnBall();
    }   
    else if(GetDistanceBetweenPoints(x, y, z,2744.6116,-1765.2544,423.1210) < 1.5)
    {
        RespawnBall();
    }   
    else if(GetDistanceBetweenPoints(x, y, z, 2669.7029,-1765.1370,423.1210) < 1.5)
    {
        RespawnBall();
    }   
    else if(GetDistanceBetweenPoints(x, y, z, 2669.8381,-1790.2809,423.1210) < 1.5)
    {
        RespawnBall();
    }   
    else if(GetDistanceBetweenPoints(x, y, z, 2669.6665,-1815.1140,423.1210) < 1.5)
    {
        RespawnBall();
    }   
    else if(GetDistanceBetweenPoints(x, y, z, 2669.7180,-1840.0453,423.1210) < 1.5)
    {
        RespawnBall();
    }   
    else if((2701.92 < x < 2711.87 && -1862.75 < y < -1857.30) || (2701.92 < x < 2711.89 && -1747.10 < y < -1741.60))
    {
        PHY_SetObjectZBound(Ball, _, 425.6 , 0.5);
        if(z > 425.6)
        {
            RecreateBall();
            for(new p = PlayerPoolSize(); p != -1; p--)
            {
                if(IsPlayerNPC(p)) continue;
                if(IsPlayerConnected(p))
                {
                    if(IsPlayerInBoisko(p))
                    {
                        SendClientMessage(p, -1, "(("COL_LIME"Piłka została zrespawnowana - "COL_BLUE"narożnik"COL_LIME"."COL_WHITE"))");
                    }
                }
            }
            new Float:mindist = FLOAT_INFINITY,
            Float:dist,
            closest;
            for(new i; i < sizeof Corners; i++)
            {
                dist = (x - Corners[i][0]) * (x - Corners[i][0]) + (y - Corners[i][1]) * (y - Corners[i][1]);
                if(dist < mindist)
                {
                    mindist = dist;
                    closest = i;
                }
            }
            SetObjectPos(Ball, Corners[closest][0], Corners[closest][1], Corners[closest][2]);
        }
    }
    return 1;
}

stock RespawnBall()
{
    RecreateBall();
    for(new p = PlayerPoolSize(); p != -1; p--)
    {
        if(IsPlayerNPC(p)) continue;
        if(IsPlayerConnected(p))
        {
            if(IsPlayerInBoisko(p))
            {
                SendClientMessage(p, -1, "(("COL_LIME"Piłka została zrespawnowana - "COL_BLUE"środek boiska"COL_LIME"."COL_WHITE"))");
            }
        }
    }
    return 1;
}

stock fb_LoadTextDraws()
{
    PowerTD[0] = TextDrawCreate(511.000000, 396.000000, "~n~~n~");
    TextDrawBackgroundColor(PowerTD[0], 255);
    TextDrawFont(PowerTD[0], 1);
    TextDrawLetterSize(PowerTD[0], 0.590000, 0.039999);
    TextDrawColor(PowerTD[0], -1);
    TextDrawSetOutline(PowerTD[0], 0);
    TextDrawSetProportional(PowerTD[0], 1);
    TextDrawSetShadow(PowerTD[0], 1);
    TextDrawUseBox(PowerTD[0], 1);
    TextDrawBoxColor(PowerTD[0], 255);
    TextDrawTextSize(PowerTD[0], 592.000000, -10.000000);
    PowerTD[1] = TextDrawCreate(512.000000, 397.000000, "~n~~n~");
    TextDrawBackgroundColor(PowerTD[1], 255);
    TextDrawFont(PowerTD[1], 1);
    TextDrawLetterSize(PowerTD[1], 0.500000, -0.099999);
    TextDrawColor(PowerTD[1], -1);
    TextDrawSetOutline(PowerTD[1], 0);
    TextDrawSetProportional(PowerTD[1], 1);
    TextDrawSetShadow(PowerTD[1], 1);
    TextDrawUseBox(PowerTD[1], 1);
    TextDrawBoxColor(PowerTD[1], 252645375);
    TextDrawTextSize(PowerTD[1], 591.000000, 0.000000);
    return 1;
}
stock fb_LoadPlayerTextDraws(playerid)
{
    pPowerTD[playerid] = CreatePlayerTextDraw(playerid, 512.000000, 397.000000, "~n~~n~");
    PlayerTextDrawBackgroundColor(playerid, pPowerTD[playerid], 255);
    PlayerTextDrawFont(playerid, pPowerTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, pPowerTD[playerid], 0.500000, -0.099999);
    PlayerTextDrawColor(playerid, pPowerTD[playerid], -1);
    PlayerTextDrawSetOutline(playerid, pPowerTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, pPowerTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, pPowerTD[playerid], 1);
    PlayerTextDrawUseBox(playerid, pPowerTD[playerid], 1);
    PlayerTextDrawBoxColor(playerid, pPowerTD[playerid], -1359019777);
    PlayerTextDrawTextSize(playerid, pPowerTD[playerid], 507.000000, 0.000000);
    PlayerTextDrawHide(playerid, pPowerTD[playerid]);
    TextDrawHideForPlayer(playerid, PowerTD[0]);
    TextDrawHideForPlayer(playerid, PowerTD[1]);
    return 1;
}
forward PowerBar();
public PowerBar()
{
    static tick;
    tick = GetTickCount();
    static dif;
    for(new i = PlayerPoolSize(); i != -1; i--)
    {
        if(IsPlayerNPC(i)) continue;
        if(!IsPlayerConnected(i)) continue;
        if(!IsPlayerInBoisko(i)) continue;
        if(pLastTick[i] == -1)
        {
            PlayerTextDrawHide(i, pPowerTD[i]);
            TextDrawHideForPlayer(i, PowerTD[0]);
            TextDrawHideForPlayer(i, PowerTD[1]);
            pLastTick[i] = 0;
        }
        else if(pLastTick[i])
        {
            dif = tick - pLastTick[i];
            if(dif > 2000)
            {
                pLastTick[i] = -1;
                continue;
            }
            else if(dif > 1000)
            dif = 2000 - dif;
            PlayerTextDrawTextSize(i, pPowerTD[i], 507.0 + ((84.0 * dif)/1000.0), 0.0);
            PlayerTextDrawShow(i, pPowerTD[i]);
            TextDrawShowForPlayer(i, PowerTD[0]);
            TextDrawShowForPlayer(i, PowerTD[1]);
        }
    }
    return 1;
}
stock football_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    new
    tick = GetTickCount(),
    dif;
    if(PRESSED(KEY_HANDBRAKE))
    pLastTick[playerid] = tick;
    else if(RELEASED(KEY_HANDBRAKE))
    {
        dif = tick - pLastTick[playerid];
        pLastTick[playerid] = -1;
        if(dif < 2000)
        {
            new
            Float:ox, Float:oy, Float:oz,
            Float:x, Float:y, Float:z;
            GetBallPos(ox, oy, oz);
            GetPlayerPos(playerid, x, y, z);
            if(IsPlayerInRangeOfPoint(playerid, 1.2, ox, oy, z) && floatabs(oz - z) < 1.8)
            {
                new
                Float:speed,
                Float:angle,
                Float:vx, Float:vy, Float:vz;
                if(dif > 1000)
                dif = 2000 - dif;
                speed = (float(dif + 400) / (1000)) * 20.0;
                if(BallHolder != -1)
                {
                    DestroyBall();
                    CreateBall();
                    SetObjectPos(Ball, ox, oy, oz);
                    BallHolder = -1;
                }
                GetPlayerFacingAngle(playerid, angle);
                vx = speed * floatsin(-angle, degrees),
                vy = speed * floatcos(-angle, degrees);
                vz = /*(newkeys & KEY_SECONDARY_ATTACK) ? (speed / 1.3) :*/ (speed / 5.2);
                /*GetPlayerCameraFrontVector(playerid, vx, vy, vz);
                vx *= speed;
                vy *= speed;
                vz *= speed * 1.2;
                if(vz < 0.0)
                vz = 0.0;*/
                PHY_SetObjectVelocity(Ball, vx, vy, vz);
                if(oz > BallSpawn[2] + (1.0 - 0.875))
                ApplyAnimation(playerid, "WAYFARER", "WF_Fwd", 4.0, 0, 0, 0, 0, 0);
                else if(dif > 300)
                ApplyAnimation(playerid, "FIGHT_D", "FightD_1", 4.1, 0, 1, 1, 0, 0);
                PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
            }
        }
    }
    if (PRESSED(KEY_WALK))
    pLastTick[playerid] = tick;
    else if (RELEASED(KEY_WALK))
    {
        dif = tick - pLastTick[playerid];
        pLastTick[playerid] = -1;
        if(dif < 2000)
        {
            new
            Float:ox, Float:oy, Float:oz,
            Float:x, Float:y, Float:z;
            GetBallPos(ox, oy, oz);
            GetPlayerPos(playerid, x, y, z);
            if(IsPlayerInRangeOfPoint(playerid, 1.2, ox, oy, z) && floatabs(oz - z) < 1.8)
            {
                new
                Float:speed,
                Float:angle,
                Float:vx, Float:vy, Float:vz;
                if(dif > 1000)
                dif = 2000 - dif;
                speed = (float(dif + 400) / (1000)) * 15.0;
                if(BallHolder != -1)
                {
                    DestroyBall();
                    CreateBall();
                    SetObjectPos(Ball, ox, oy, oz);
                    BallHolder = -1;
                }
                GetPlayerFacingAngle(playerid, angle);
                vx = speed * floatsin(-angle, degrees),
                vy = speed * floatcos(-angle, degrees);
                vz = speed / 1.3;
                PHY_SetObjectVelocity(Ball, vx, vy, vz);
                if(oz > BallSpawn[2] + (1.0 - 0.875))
                ApplyAnimation(playerid, "WAYFARER", "WF_Fwd", 4.0, 0, 0, 0, 0, 0);
                else if(dif > 300)
                ApplyAnimation(playerid, "FIGHT_D", "FightD_1", 4.1, 0, 1, 1, 0, 0);
                PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
            }
        }
    }
    if (PRESSED(KEY_SECONDARY_ATTACK))
    pLastTick[playerid] = tick;
    else if (RELEASED(KEY_SECONDARY_ATTACK))
    {
        dif = tick - pLastTick[playerid];
        pLastTick[playerid] = -1;
        if(dif < 2000)
        {
            new
            Float:ox, Float:oy, Float:oz,
            Float:x, Float:y, Float:z;
            GetBallPos(ox, oy, oz);
            GetPlayerPos(playerid, x, y, z);
            if(IsPlayerInRangeOfPoint(playerid, 1.2, ox, oy, z) && floatabs(oz - z) < 1.8)
            {
                new
                Float:speed,
                Float:angle,
                Float:vx, Float:vy, Float:vz;
                if(dif > 1000)
                dif = 2000 - dif;
                speed = (float(dif + 400) / (1000)) * 16.0;
                if(BallHolder != -1)
                {
                    DestroyBall();
                    CreateBall();
                    SetObjectPos(Ball, ox, oy, oz);
                    BallHolder = -1;
                }
                GetPlayerFacingAngle(playerid, angle);
                vx = speed * floatsin(-angle, degrees),
                vy = speed * floatcos(-angle, degrees);
                vz = speed / 2.0;
                PHY_SetObjectVelocity(Ball, vx, vy, vz);
                if(oz > BallSpawn[2] + (1.0 - 0.875))
                ApplyAnimation(playerid, "WAYFARER", "WF_Fwd", 4.0, 0, 0, 0, 0, 0);
                else if(dif > 300)
                ApplyAnimation(playerid, "FIGHT_D", "FightD_1", 4.1, 0, 1, 1, 0, 0);
                PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
            }
        }
    }
    if(PRESSED(KEY_FIRE))
    {
        new
        Float:ox, Float:oy, Float:oz,
        Float:x, Float:y, Float:z;
        GetBallPos(ox, oy, oz);
        if(BallHolder == playerid)
        {
            DestroyBall();
            CreateBall();
            SetObjectPos(Ball, ox, oy, oz);
            BallHolder = -1;
        }
        else
        {
            GetPlayerPos(playerid, x, y, z);
            if(IsPlayerInRangeOfPoint(playerid, 1.2, ox, oy, z) && oz < z && (z - oz) < 1.2)
            {
                GetObjectRot(Ball, ox, oy, oz);
                AttachObjectToPlayer(Ball, playerid, 0.0, 0.6, -0.875, ox, oy, oz);
                if(BallHolder != -1)
                PlayerPlaySound(BallHolder, 1130, 0.0, 0.0, 0.0);
                PlayerPlaySound(playerid, 1130, 0.0, 0.0, 0.0);
                BallHolder = playerid;
            }
        }
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
    }
    return 1;
}

stock IsPlayerInBoisko(playerid)
{
    if(InRange(playerid, 500.0, 2706.8354,-1802.2961,422.8372)) return 1;
    return 0;
}