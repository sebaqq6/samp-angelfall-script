//GRACZE
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(issuerid != INVALID_PLAYER_ID)
	{
		if(gracz[issuerid][MapperLvl] >= 2) return 1;
	}
	if(IsPlayerNPC(playerid)) return 1;
	if(IsPlayerNPC(issuerid)) return 1;
	if(gracz[playerid][in_krypta]) return 1;
	if(gracz[playerid][BWTime]) return 1;
	if(gracz[playerid][MapperLvl] >= 2) return 1;
	if(gracz[playerid][admin_duty]) return 1;
	if(SpawnProtect(playerid)) return 1;
	if(_PlayerTeleporting[playerid]) return 1;
	if(IsPlayerInAnyVehicle(playerid))
	{
		SetPlayerArmedWeapon(playerid, 0);
		return 1;
	}
	if(issuerid == INVALID_PLAYER_ID)
	{
		Process_Tutorial(playerid, 13);
		TakePlayerHP(playerid, floatround(amount));
	}
	else
	{
		givenDamage[playerid][issuerid] = true;
		switch(weaponid)
		{
			case 0:
			{
				TakePlayerHP(playerid, 1+StrenghtDMG(playerid));
				AntyLeaverRun(playerid);
			}
			case 4:
			{
				TakePlayerHP(playerid, 5);
				StartRandomBlooding(playerid);
				AntyLeaverRun(playerid);
			}
			case 5:
			{
				TakePlayerHP(playerid, 5);
				AntyLeaverRun(playerid);
			}
			case 8:
			{
				TakePlayerHP(playerid, 5);
				StartRandomBlooding(playerid);
				AntyLeaverRun(playerid);
			}
			case 9:
			{
				TakePlayerHP(playerid, 3);
				StartRandomBlooding(playerid);
				AntyLeaverRun(playerid);
			}
			case 22:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 15);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 24:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 18);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 25:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 35);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 26:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 25);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 27:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 30);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 28:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 15);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 29:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 18);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 30:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 27);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 31:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 25);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 32:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 20);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 33:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 30);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
			case 34:
			{
				if(!ammo[issuerid][weaponid] || !w_cdn[issuerid][weaponid]) return 1;
				TakePlayerHP(playerid, 85);
				StartBlooding(playerid);
				ShowTDShoot(issuerid);
				AntyLeaverRun(playerid);
			}
		}
	}
	return 1;
}
//*************************************************************************************************************
//ZOMBIE
public FCNPC_OnTakeDamage(npcid, damagerid, weaponid, bodypart, Float:health_loss)
{
	if(weaponid == 0)
	{
		FCNPC_SetHealth(npcid, FCNPC_GetHealth(npcid)-5);
		if(floatround(FCNPC_GetHealth(npcid)) != 0) format(dmgstring, 50, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~w~ %dHP", floatround(FCNPC_GetHealth(npcid)));
		else format(dmgstring, 50, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~ 0HP");
		GameTextForPlayer(damagerid, dmgstring,1500,3);
	}
	else if(weaponid == 9 || weaponid == 4 || weaponid == 5)
	{
		FCNPC_SetHealth(npcid, FCNPC_GetHealth(npcid)-25);
		if(floatround(FCNPC_GetHealth(npcid)) != 0) format(dmgstring, 50, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~w~ %dHP", floatround(FCNPC_GetHealth(npcid)));
		else format(dmgstring, 50, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~ 0HP");
		GameTextForPlayer(damagerid, dmgstring,1500,3);	
	}
	else
	{
		if(ammo[damagerid][weaponid] && w_cdn[damagerid][weaponid])
		{
			BloodEffectRun(npcid);
			ShowTDShoot(damagerid);
			if(bodypart == 9) FCNPC_SetHealth(npcid, FCNPC_GetHealth(npcid)-100);
			else FCNPC_SetHealth(npcid, FCNPC_GetHealth(npcid)-10);
			if(floatround(FCNPC_GetHealth(npcid)) != 0) format(dmgstring, 50, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~w~ %dHP", floatround(FCNPC_GetHealth(npcid)));
			else format(dmgstring, 50, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~ 0HP");
			GameTextForPlayer(damagerid, dmgstring,1500,3);
			return 1;
		}
	}
	return 0;
}
//************************************************************************************************************SYSTEM HP
forward TakePlayerHP(playerid, amount);
public TakePlayerHP(playerid, amount)
{
	if(gracz[playerid][in_krypta]) return 0;
	if(gracz[playerid][BWTime]) return 0;
	if(gracz[playerid][MapperLvl] >= 2) return 0;
	if(gracz[playerid][admin_duty]) return 0;
	if(SpawnProtect(playerid)) return 0;
	if(_PlayerTeleporting[playerid]) return 0;
	if(combine_mode[playerid][c_id])
	{
		LeftNotifyShow(playerid, "error", "Otrzymano obrazenia. ~r~Przerwano~w~ akcje!", LN_RED);
		StopCombineMode(playerid);
	}
	SetPlayerHP(playerid, gracz[playerid][HP]-amount);
	FadeColorForPlayer(playerid, 255, 0, 0, amount*10+1, 255, 0, 0, 0, amount+1, 0);
	return 1;
}

stock GivePlayerHP(playerid, amount)
{
	FadeColorForPlayer(playerid, 8, 253, 0, 50, 8, 253, 0, 0, 15, 1);
	SetPlayerHP(playerid, gracz[playerid][HP]+amount);
	SetPlayerHealth(playerid, 9999);
	return 1;
}

stock SetPlayerHP(playerid, amount)
{
	if(gracz[playerid][BWTime]) return 1;
	if(gracz[playerid][MapperLvl] >= 2) return 1;
	gracz[playerid][HP] = amount;
	Process_CheckHP(playerid);
	SetPlayerHealth(playerid, 9999);
	return 1;
}

stock Process_CheckHP(playerid)
{
	if(gracz[playerid][HP] > 0)
	{
		SetPlayerHealth(playerid, 9999);
		gracz[playerid][god_check] = 0;
	}
	if(gracz[playerid][HP] > 100)
	{
		gracz[playerid][HP] = 100;
	}
	else if(gracz[playerid][HP] <= 0)
	{
		gracz[playerid][HP] = 0;
		SetPVarInt(playerid, "SetFullHP", 1);
		SetPlayerHealth(playerid, 0);
		gracz[playerid][god_check]++;
	}
	if(gracz[playerid][god_check] > 20)
	{
		gracz[playerid][god_check] = 0;
		if(SpawnProtect(playerid)) return 0;
		Interwencja(playerid, playerid, 0, "Wyrzucenie", "Niezniszczalnosc.");
		KickEx(playerid, "Niezniszczalnosc.");
	}
	SetBarHP(playerid, gracz[playerid][HP]);
	return 1;
}
//**********************************************************************************************SYSTEM KRWAWIENIA
stock StartBlooding(playerid) 
{
	if(gracz[playerid][time_antiblood] > serwer[time_timestamp]) return 1;
	if(gracz[playerid][in_krypta]) return 0;
	if(gracz[playerid][BWTime]) return 0;
	if(gracz[playerid][MapperLvl] >= 2) return 0;
	if(gracz[playerid][admin_duty]) return 0;
	if(SpawnProtect(playerid)) return 0;
	if(_PlayerTeleporting[playerid]) return 0;
	gracz[playerid][Krwawi] = 1;
	mq_format("UPDATE `Konta` SET `Krwawi`='%d' WHERE `id`='%d';", gracz[playerid][Krwawi], gracz[playerid][UID]);
	mq_send("QKrwawi");
	return 1;
}
stock StopBlooding(playerid)
{
	gracz[playerid][Krwawi] = 0;
	mq_format("UPDATE `Konta` SET `Krwawi`='%d' WHERE `id`='%d';", gracz[playerid][Krwawi], gracz[playerid][UID]);
	mq_send("QKrwawi");
	return 1;
} 
stock StartRandomBlooding(playerid) 
{
	if(random(4) == 2) gracz[playerid][Krwawi] = 1;
	return 1;
}
stock Process_Blooding(playerid)
{
	if(!gracz[playerid][Krwawi]) return 1;
	if(gracz[playerid][time_antiblood] > serwer[time_timestamp]) return 1;
	SetPVarInt(playerid, "TimeKrwawi", GetPVarInt(playerid, "TimeKrwawi")+1);
	if(GetPVarInt(playerid, "TimeKrwawi") >= 5)
	{
		SetPVarInt(playerid, "TimeKrwawi", 0);
		TakePlayerHP(playerid, 1);
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~KRWAWISZ!",1000,5);
	}
	return 1;
}