//***********************STATYSTYKI GRACZA****************************
enum player_stats
{
//BAZA DANYCH
    UID,
    Name[MAX_PLAYER_NAME+1],
    KillZombies,
    KillHumans,
    HP,
    Haslo,
    Plec,
    Wiek,
    Karnacja,
    Skin,
    KRMHZ,
    Krwawi,
    PSek,
    PMin,
    PGodz,
    OrgID,
    SzefORG,
    AdminJailTime,
    BOOC,
    Float:PosX,
    Float:PosY,
    Float:PosZ,
    Float:PosR,
    Glod,
    Pragn,
    LaserColor,
    Warns,
    Zwiazany,
    LastOnline,
    AdminLevel,
    WebReg,
    f_master,
    MapperLvl,
    ForumNick[20],
    ViceSzefORG,
    MaxEQ,
    gold,
    BWTime,
    QuestID,
    QuestStatus,
    quiz,
    GGame,
    master_nick[32],
    exp,
    muted_timestamp,
    level,
    sila,
    vip,
    rads,
    time_antiblood,
    gps_hz,
    rusznikarstwo,
    motoryzacja,
    medycyna,
    apid,
//TYMCZASOWE
    spawned,
    bool:loggedin,
    gen_halas,
    actual_weapon,
    admin_duty,
    kondycja,
    kondycja_reftime,
    tick_shakecamera,
    bool:first_spawn,
    Text3D:p_label,
    p_label_string[512],
    sec_online,
    bool:sobeit_detect,
    bool:shoot_halas,
    afk_control_timestamp,
    afk_control_hour,
    afk_control_minute,
    bubble_text[144],
    bubble_timestamp,
    loginhistory_start,
    loginhistory_end,
    bool:in_interior,
    bool:in_krypta,
    time_savedata,
    time_spam[MAX_SPAMID],
    need_exp,
    time_spawnprotect,
    cbug_tick,
    shoot_td_time,
    time_expwindow,
    time_leftnotify,
    bool:td_shoot_type,
    hud_showexp,
    key_keyid,
    key_updown,
    key_leftright,
    karnet,
    vehicleid_change,
    actual_vehicleid,
    kick_antyspam,
    group_join,
    group_name[128],
    group_tag[8],
    zetony,
    rads_timestamp,
    bool:krotkofala,
    geiger,
    geiger_rads,
    geiger_tick,
    bool:geiger_led,
    gps,
    explore_world_tick,
    time_rads_effect,
    stamina_boost,
    god_check,
    prezent,
    exp_boost,
    anty_leave_time,
    mapper_weather,
    q_id,
    q_step
};

new gracz[MAX_PLAYERS][player_stats];

new ammo[MAX_PLAYERS][50];
new bool:weapon[MAX_PLAYERS][50];

new w_cdn[MAX_PLAYERS][50];
new w_cdn_max[MAX_PLAYERS][50];

enum eq_select_info
{
    s_id,
    s_itemid,
    s_count,
    s_cdn,
    s_cdn_max,
    s_used
};

new eq_select[MAX_PLAYERS][eq_select_info];
new PlayerEditObject[MAX_PLAYERS];

new bool:givenDamage[MAX_PLAYERS][MAX_PLAYERS];
//*********************SERWER*************************************
enum server_data
{
    wersja[64],
    godzina,
    pogoda,
    r_weather,
    n_weather,
    pasek_dol[256],
    dzien_tygodnia,
    interwencja_time,
    playerboisko_time,
    playerPoolSize,
    time_timestamp,
    time_hour,
    time_minute,
    time_second,
    bool:ooc_status,
    gz_hidemap,
    uptime,
    time_relootmap,
    game_field,
    downbar_time,
    downbar_query,
    cooldown_restart,
    soundtrackid,
    soundtrack_timer
};
new serwer[server_data];
new temp_string[1024];
new dmgstring[50];
new k_skinbialy = mS_INVALID_LISTID;
new m_skinbialy = mS_INVALID_LISTID;
new k_skinzolty = mS_INVALID_LISTID;
new m_skinzolty = mS_INVALID_LISTID;
new k_skinczarny = mS_INVALID_LISTID;
new m_skinczarny = mS_INVALID_LISTID;

new Float:game_field_data[] = {
    -3028.0,-981.0,-2704.0,-950.0,-2582.0,-873.0,-2354.0,-930.0,-2194.0,-1051.0,-2040.0,-1278.0,-1926.0,-1408.0,-1773.0,-1528.0,-1588.0,-1673.0,-1421.0,-1683.0,
    -1313.0,-1751.0,-1263.0,-1924.0,-968.0,-1926.0,-715.0,-1828.0,-457.0,-1878.0,-378.0,-1838.0,-204.0,-1923.0,-148.0,-2136.0,73.0,-2468.0,116.0,-2968.0,
    -2964.0,-2992.0,-3028.0,-981.0
};
//*********************************************************************OBIEKTY
enum oinfo
{
    oUID,
    oModel,
    oObject,
    oMMAT,
    Float:oX,
    Float:oY,
    Float:oZ,
    Float:oRX,
    Float:oRY,
    Float:oRZ,
    oInt,
    oVW,
    oGrupa,
    oOwner,
    oBlock
};
new ObjectInfo[MAX_OBJECTS][oinfo];
//KRYPTA 
enum krypta_info
{
    brama_opened,
    brama_z_status,
    brama_w_status,
    brama_z,
    brama_w,
    lampka_c1,
    lampka_c2,
    lampka_c3,
    lampka_c4,
    lampka_z1,
    lampka_z2,
    lampka_z3,
    lampka_z4,
    gaz[24],
    winda_status,
    winda_lastactivestatus,
    winda_delay
};

new krypta[krypta_info];
//WEJŒCIA
enum door_info
{
    d_id,
    d_status,
    Float:d_aX,
    Float:d_aY,
    Float:d_aZ,
    Float:d_bX,
    Float:d_bY,
    Float:d_bZ,
    d_pickupA,
    d_pickupB,
    Text3D:d_labelA,
    Text3D:d_labelB
};

new door[MAX_DOORS][door_info];
//OGNISKA

enum ognisko_info
{
o_status,
Float:o_X,
Float:o_Y,
Float:o_Z,
o_object[8],
Text3D:o_label
};

new ognisko[MAX_PLAYERS][ognisko_info];

enum pKrypta_info
{
    pk_uid,
    pk_door[5],
    bool:pk_door_created,
    pk_status,
    pk_sbad
};
new pKrypta[MAX_PLAYERS][pKrypta_info];

//POJAZDY
enum pojazd_info
{
    v_id,
    v_vehicleid,
    v_model,
    Float:v_X,
    Float:v_Y,
    Float:v_Z,
    Float:v_R,
    Float:v_temp_X,
    Float:v_temp_Y,
    Float:v_temp_Z,
    Float:v_temp_R,
    v_autoflip,
    v_uZasilania,
    v_uSmarowania,
    v_uChlodzenia,
    v_uElektryczny,
    v_uKorbowy,
    v_paliwo,
    v_color,
    v_combine[32],
    v_idletime,
    v_enginestatus,
    v_temp_engine,
    v_antyspam_destroy,
    v_door
};

new pojazd[WORLD_VEHICLES][pojazd_info];
new pojazdy_save_timer;

enum combine_info
{
    c_id,
    c_step,
    c_bad,
    c_key[6],
    c_qkey,
    c_key_time,
    c_mode
};

new combine_mode[MAX_PLAYERS][combine_info];

enum actor_info
{
    actor_id,
    Float:X,
    Float:Y,
    Float:Z,
    Float:R
};

new actor[MAX_ACTOR][actor_info];
new actor_refresh_time;
/*
enum quest_info
{
    bool:q_active,
    q_actor,
    q_actor_name[30],
    q_nagroda_exp,
    q_nagroda_item,
    q_nagroda_item_count,
    q_opis[256]
};

new quest[MAX_QUESTS][quest_info];
*/

enum attached_object_data
{
    Float:ao_x,
    Float:ao_y,
    Float:ao_z,
    Float:ao_rx,
    Float:ao_ry,
    Float:ao_rz,
    Float:ao_sx,
    Float:ao_sy,
    Float:ao_sz,
    ao_typ
};
 
new ao[MAX_PLAYERS][MAX_PLAYER_ATTACHED_OBJECTS][attached_object_data];