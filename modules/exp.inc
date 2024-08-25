#define EXP_SVAL 20

stock GiveExp(playerid, expval, bool:use_label = false, Float:lX = 0.0, Float:lY = 0.0, Float:lZ = 0.0)
{
	new premia;
	if(isvip(playerid)) premia += 3;
	premia += gracz[playerid][exp_boost];
	if(use_label)
	{
		new str[128];
		format(str, 128, "EXP: +%d", expval+premia);
		CreateFadeLabel(playerid, 128, 3, 123, str, lX, lY, lZ+1.0);
	}
	gracz[playerid][exp] += expval+premia;
	new getlevelup = Process_Exp(playerid);
	ShowExpWindow(playerid, expval, premia);
	if(getlevelup)
	{
		PlayerTextDrawHide(playerid, td_exp_content[playerid]);
		PlayerTextDrawShow(playerid, td_exp_levelup[playerid]); 
		new str_graty[245];
		if(gracz[playerid][level] <= 20) format(str_graty, 245, "~g~Gratulacje~w~! ~b~Awansowales~w~ na ~y~%d~w~ poziom! Wcisnij klawisz ~r~Y~w~ aby przydzielic punkt specjalizacji!", gracz[playerid][level]);
		else format(str_graty, 245, "~g~Gratulacje~w~! ~b~Awansowales~w~ na ~y~%d~w~ poziom!", gracz[playerid][level]);
		LeftNotifyShow(playerid,"Gratulacje!", str_graty, LN_GREEN, 10);
		PlayerPlaySound(playerid, 1185, 0.0, 0.0, 0.0);
		gracz[playerid][time_expwindow] = serwer[time_timestamp]+10;
	}
	else
	{
		PlayerTextDrawHide(playerid, td_exp_levelup[playerid]); 
		PlayerPlaySound(playerid, 5201, 0.0, 0.0, 0.0);
	}
	mq_format("UPDATE `Konta` SET `exp`='%d', `level`='%d' WHERE `id`='%d';", gracz[playerid][exp], gracz[playerid][level], gracz[playerid][UID]);
	mq_send("QSaveExpLvl");
	if(gracz[playerid][OrgID])
	{
		mq_format("UPDATE `Grupy` SET `exp`=`exp`+'%d' WHERE `id`='%d';", expval+premia, gracz[playerid][OrgID]);
		mq_send("QAddExpGroup");
	}
	return 1;
}

stock Process_Exp(playerid)
{
	new levelup;
	gracz[playerid][need_exp] = (gracz[playerid][level]+1)*EXP_SVAL;
	while(gracz[playerid][exp] >= gracz[playerid][need_exp])
	{
		gracz[playerid][exp] -= gracz[playerid][need_exp];
		gracz[playerid][level]++;	
		levelup = 1;
		gracz[playerid][need_exp] = (gracz[playerid][level]+1)*EXP_SVAL;
	}
	return levelup;
}



CMD:expgive(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 1;
	GiveExp(playerid, strval(params));
	return 1;
}