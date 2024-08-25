forward QuestStart(playerid, questid);
forward QuestEnd(playerid, questid);

#define QCOL_A "{7e0a5c}"

stock Init_Quest()
{
	//NewQuest(1, -1995.1685,-1594.2118,87.3582, 0.0, "Noah", 50, 100, 75, "Znajdz na mapie 50 zniszczonych pudelek i przynies dla Noah.");
	return 1;
}

stock NewQuest(amodelid, Float:aX, Float:aY, Float:aZ, Float:aRotation, name[], qexp, qitem, qitem_count, qopis[])
{
	new qid = FreeQuestID();
	quest[qid][q_actor] = NewActor(amodelid, aX, aY, aZ, aRotation);
	format(quest[qid][q_actor_name], 30, "%s", name);
	CreateDynamic3DTextLabel(quest[qid][q_actor_name], -1, aX, aY, aZ+1.0, 3.0);
	CreateDynamicMapIcon(aX, aY, aZ, 58, -1, _, _, _, 500.0, MAPICON_GLOBAL);//molo
	quest[qid][q_nagroda_exp] = qexp;
	quest[qid][q_nagroda_item] = qitem;
	quest[qid][q_nagroda_item_count] = qitem_count;
	format(quest[qid][q_opis], 256, "%s", qopis);
	quest[qid][q_active] = true;
	return qid;
}

stock FreeQuestID()
{
	for(new q = 1; q < MAX_QUESTS; q++)
	{
		if(!quest[q][q_active]) return q;
	}
	return MAX_QUESTS;
}

stock Key_QuestActor(playerid)
{
	new aid;
	for(new q; q < MAX_QUESTS; q++)
	{
		if(!quest[q][q_active]) continue;
		aid = quest[q][q_actor];
		if(IsPlayerInRangeOfPoint(playerid, 3.0, actor[aid][X], actor[aid][Y], actor[aid][Z]))
		{
			mq_format("SELECT * FROM `daily_quest` WHERE `userid`='%d' AND `questid`='%d' LIMIT 0,1;", gracz[playerid][UID], q);
			mq_send("QCheckDailyQuest", "dd", playerid, q);
			return 1;
		}
	}
	return 0;
}

forward QCheckDailyQuest(playerid, questid);
public QCheckDailyQuest(playerid, questid)
{
	mq_getdata();
	if(rekordy)
	{
		ActorTalk(playerid, quest[questid][q_actor_name], ""COL_GREY"Przykro mi, podj¹³eœ siê ju¿ dzisiejszego zadania. "COL_GREEN"Wróæ jutro"COL_GREY" po nastêpne...");
	}
	else
	{
		new actual_quest = IsPlayerQuest(playerid);
		if(actual_quest == questid)
		{
			QuestEnd(playerid, questid);
			//LeftNotifyShow(playerid, "error", "Nie wykonales misji. Wroc kiedy to zrobisz.", LN_RED);
		}
		else if(actual_quest)
		{
			LeftNotifyShow(playerid, "error", "Mozesz tylko jedno zadanie wykonywac na w tym samym momencie.", LN_RED);
		}
		else
		{
			QuestStart(playerid, questid);
		}
	}
	return 1;
}

stock ActorTalk(playerid, aName[], content[])
{
	new str_header[128];
	format(str_header, 128, "{0362a2}» "COL_CYAN"%s"COL_GREY" mówi:", aName);
	Dialog_Show(playerid, QTALK, DIALOG_STYLE_MSGBOX, str_header, content, "Okej", "Wyjdz");
	return 1;
}

public QuestStart(playerid, questid)
{
	gracz[playerid][q_id] = questid;
	gracz[playerid][q_step] = 0;
	new str_talk[2048];
	//                             strcat(str_talk, " \n");
	switch(questid)
	{
		case 1:
		{
			strcat(str_talk, ""COL_GREY"Czeœæ jestem "QCOL_A"Noah"COL_GREY", jak zapewne zd¹¿y³eœ/aœ zauwa¿yæ próbujemy prowadziæ normalne ¿ycie. \n");
			strcat(str_talk, ""COL_GREY"Nie odda tego jak ¿yliœmy przed Apokalips¹, ale choæ odrobinê chcemy to odzwierciedliæ. \n");
			strcat(str_talk, ""COL_GREY"W krypcie mieszkaj¹ doroœli jak i dzieci. Dzieci siê nudz¹, a doroœli pracuj¹ do póŸnych godzin. \n");
			strcat(str_talk, ""COL_GREY"Przyda³oby siê jakoœ zaj¹æ tymi ma³ymi brzd¹cami, prawda? Haha... \n");
			strcat(str_talk, ""COL_GREY"Kojarzysz pewnie masê zniszczonych pude³ek, s¹ one z tektury która jest idealnym pochodnym \n");
			strcat(str_talk, ""COL_GREY"materia³em od papieru, walaj¹ siê one wszedzie, a nikt tego nie chce zbieraæ. Czas to zmieniæ! \n");
			strcat(str_talk, ""COL_GREY"Dzieci wkoñcu bêd¹ mia³y na czym sobie rysowaæ, a doroœli pisaæ pamiêtniki czy nawet próbowaæ \n");
			strcat(str_talk, ""COL_GREY"swoich si³ w literaturze. \n");
		}
	}
	strcat(str_talk, " \n");
	strcat(str_talk, " \n"); 
	format(str_talk, 2048, "%s{09a4d1}» "COL_RED"Zadanie {09a4d1}«\n"COL_GREY" %s\n", str_talk, quest[questid][q_opis]);
	strcat(str_talk, " \n"); 
	strcat(str_talk,"{09a4d1}» "COL_GREEN"Nagroda {09a4d1}«\n");
	if(quest[questid][q_nagroda_exp]) format(str_talk, 2048, "%s{f85818}»"COL_GREEN" +{6f3e9c}%d EXP\n", str_talk, quest[questid][q_nagroda_exp]);
	if(quest[questid][q_nagroda_item]) format(str_talk, 2048, "%s{f85818}»{ffa500} %d sztuk"COL_GREY" przedmiotu:{a5a971} %s\n", str_talk, quest[questid][q_nagroda_item_count], ItemName[quest[questid][q_nagroda_item]]);
	ActorTalk(playerid, quest[questid][q_actor_name], str_talk);
	return 1;
}

Dialog:QTALK(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][q_id] && !gracz[playerid][q_step])
	{
		gracz[playerid][q_step] = 1;
		LeftNotifyShow(playerid, "Misja", "Zadanie zostalo ~g~przyjete~w~! Miejsce ukonczenia questa masz zaznaczone na mapie ~y~czerwona flaga~w~.", LN_GREEN, 10);
	}
	return 1;
}

stock IsPlayerQuest(playerid)
{
	if(gracz[playerid][q_id]  && gracz[playerid][q_step]) return gracz[playerid][q_id];
	return 0;
}

public QuestEnd(playerid, questid)
{
	switch(questid)
	{
		case 1:
		{
			
		}
	}
	return 1;
}