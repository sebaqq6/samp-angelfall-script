#define MAX_FADE_LABELS 100
enum fade_label_data
{
	e_text[128],
	Text3D:e_lab,
	bool:e_lock,
	e_AA,
	e_speed,
	e_col_r,
	e_col_g,
	e_col_b
};

new fade_label[MAX_FADE_LABELS][fade_label_data];

stock CreateFadeLabel(playerid, col_r, col_g, col_b, text[], Float:fX, Float:fY, Float:fZ, Float:range = 100.0, speed_fade = 15)
{
	for(new s; s < MAX_FADE_LABELS; s++)
	{
		if(fade_label[s][e_lock]) continue;
		format(fade_label[s][e_text], 128, "%s", text);
		fade_label[s][e_lab] = CreateDynamic3DTextLabel(fade_label[s][e_text], ConvertToColor(col_r, col_g, col_b, fade_label[s][e_AA]), fX, fY, fZ, range, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0,  -1,  -1, playerid);
		fade_label[s][e_AA] = 255;
		fade_label[s][e_speed] = speed_fade;
		fade_label[s][e_col_r] = col_r;
		fade_label[s][e_col_g] = col_g;
		fade_label[s][e_col_b] = col_b;
		fade_label[s][e_lock] = true;
		return 1;
	}
	return 0;
}

forward Process_FadeLabel();
public Process_FadeLabel()
{
	for(new s; s < MAX_FADE_LABELS; s++)
	{
		if(!fade_label[s][e_lock]) continue;
		if(fade_label[s][e_AA] > 0)
		{
			UpdateDynamic3DTextLabelText(fade_label[s][e_lab], ConvertToColor(fade_label[s][e_col_r], fade_label[s][e_col_g], fade_label[s][e_col_b], fade_label[s][e_AA]), fade_label[s][e_text]);
			fade_label[s][e_AA] -= fade_label[s][e_speed];
		}
		else
		{
			DestroyDynamic3DTextLabel(fade_label[s][e_lab]);
			fade_label[s][e_AA] = 0;
			fade_label[s][e_lock] = false;
		}
	}
	return 1;
}