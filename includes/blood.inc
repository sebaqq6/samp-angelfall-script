 /************************************************
 *				Blood effect v1.1				 *
 *						                         *
 *        (c) Copyright 2014, Jstylezzz          *
 *  		This file is provided as is.         *
 *												 *
 ************************************************/
 
#if defined _jblood_included
  #endinput
#endif
#define _jblood_included

//=== NEW'S ===//
 new jb_bloodtimer[MAX_PLAYERS];
 new jb_BloodCount[MAX_PLAYERS];
 new Text:jb_BloodDraw[MAX_PLAYERS];
 new bDrawCreated[MAX_PLAYERS];

//=== FORWARDS ===//

 forward jb_getBloodColor(playerid, type);

//=== PUBLICS ===//

 public jb_getBloodColor(playerid, type)
 {
 	TextDrawHideForPlayer(playerid,jb_BloodDraw[playerid]);
 	new newhex[128],endhex;
 	if(type == 0)
 	{
 		if(jb_BloodCount[playerid] < 10)
 		{
 			format(newhex,128,"0xFF00000%d",jb_BloodCount[playerid]);
 		}
 		if(jb_BloodCount[playerid] > 10)
 		{
 			format(newhex,128,"0xFF0000%d",jb_BloodCount[playerid]);
 		}
 	}
 	if(type == 1)
 	{
 		if(jb_BloodCount[playerid] < 10)
 		{
 			format(newhex,128,"0x0000000%d",jb_BloodCount[playerid]);
 		}
 		if(jb_BloodCount[playerid] > 10)
 		{
 			format(newhex,128,"0x000000%d",jb_BloodCount[playerid]);
 		}
 	}
 	sscanf(newhex, "x", endhex);
 	TextDrawBoxColor(jb_BloodDraw[playerid],endhex);
 	jb_BloodCount[playerid]--;
 	TextDrawShowForPlayer(playerid,jb_BloodDraw[playerid]);
 	if(jb_BloodCount[playerid]== 0) {KillTimer(jb_bloodtimer[playerid]); TextDrawHideForPlayer(playerid,jb_BloodDraw[playerid]);}
 	return 1;
 }

//=== STOCKS ===//
//Type: 0 - czerwony, 1 - czarny
 stock ShowBloodScreen(playerid,Float:amount, shadetimer = 100, type = 0)
 {
 	CheckbDraw(playerid);
 	KillTimer(jb_bloodtimer[playerid]);
 	TextDrawHideForPlayer(playerid,jb_BloodDraw[playerid]);
 	jb_BloodCount[playerid] = floatround(amount);
 	new newhex[128],endhex;
 	if(type == 0)
 	{
 		if(jb_BloodCount[playerid] < 10)
 		{
 			format(newhex,128,"0xFF00000%d",jb_BloodCount[playerid]);
 		}
 		if(jb_BloodCount[playerid] > 10)
 		{
 			format(newhex,128,"0xFF0000%d",jb_BloodCount[playerid]);
 		}
 	}
 	if(type == 1)
 	{
 		if(jb_BloodCount[playerid] < 10)
 		{
 			format(newhex,128,"0x0000000%d",jb_BloodCount[playerid]);
 		}
 		if(jb_BloodCount[playerid] > 10)
 		{
 			format(newhex,128,"0x000000%d",jb_BloodCount[playerid]);
 		}
 	}
 	sscanf(newhex, "x", endhex);
 	TextDrawBoxColor(jb_BloodDraw[playerid],endhex);
 	TextDrawShowForPlayer(playerid,jb_BloodDraw[playerid]);
 	jb_bloodtimer[playerid] = SetTimerEx("jb_getBloodColor",shadetimer,1,"dd",playerid, type);
 }

stock CheckbDraw(playerid) //Check if the textdraw is created, if not, create it
{
	if(bDrawCreated[playerid] == 0)
	{
		jb_BloodDraw[playerid] = TextDrawCreate(643.000000, 1.500000, "usebox");
		TextDrawLetterSize(jb_BloodDraw[playerid], 0.000000, 49.396297);
		TextDrawTextSize(jb_BloodDraw[playerid], -2.000000, 0.000000);
		TextDrawAlignment(jb_BloodDraw[playerid], 1);
		TextDrawColor(jb_BloodDraw[playerid], 0);
		TextDrawUseBox(jb_BloodDraw[playerid], true);
		TextDrawBoxColor(jb_BloodDraw[playerid], -16777166);
		TextDrawSetShadow(jb_BloodDraw[playerid], 0);
		TextDrawSetOutline(jb_BloodDraw[playerid], 0);
		TextDrawFont(jb_BloodDraw[playerid], 0);
		bDrawCreated[playerid] = 1;
	}
}