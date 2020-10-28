#include <stdint.h>
#include <stdbool.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const size_t borderpx  = 2;        /* border pixel of windows */
static const uint32_t snap      = 32;       /* snap pixel */
static const bool showbar            = true;        /* 0 means no bar */
static const bool topbar             = true;        /* 0 means bottom bar */
static const char *fonts[]          = { "Victor Mono NF:size=12" };
static const char dmenufont[]       = "Victor Mono NF:size=12";
static char normbgcolor[]           = "#282828";
static char normbordercolor[]       = "#98971a";
static char normfgcolor[]           = "#ebdbb2";
static char selfgcolor[]            = "#cc241d";
static char selbordercolor[]        = "#cc241d";
static char selbgcolor[]            = "#3c3836";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const size_t nmaster     = 1;    /* number of clients in master area */
static const bool resizehints = false;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           Arg::set_ui(1 << TAG) }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            Arg::set_ui(1 << TAG) }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      Arg::set_ui(1 << TAG) }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     Arg::set_ui(1 << TAG) }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *roficmd[] = { "rofi", "-show", "run",NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *nextlayout[] = {"xkb-switch", "-n", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	//{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	//{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
	//{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	//{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	//{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	//{ MODKEY,                       XK_Return, zoom,           {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },
	//{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	//{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_l,      slankdev_view_right,     {0} },
    { MODKEY,                       XK_h,      slankdev_view_left,      {0} },
    { MODKEY|ShiftMask|ControlMask, XK_l,      slankdev_view_right,     {0} },
    { MODKEY|ShiftMask|ControlMask, XK_h,      slankdev_view_left,      {0} },
	{ MODKEY,                       XK_p,      spawn,          Arg::set_v(dmenucmd) },
	{ MODKEY,                       XK_d,      spawn,          Arg::set_v(roficmd) },
	{ MODKEY,                       XK_t,      spawn,          Arg::set_v(termcmd) },
	//{ MODKEY,                       XK_f,      spawn,          Arg::set_v("firefox") },
	{ MODKEY,                       XK_j,      focusstack,     Arg::set_i(+1) },
	{ MODKEY,                       XK_k,      focusstack,     Arg::set_i(-1) },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  spawn,          Arg::set_v(nextlayout) },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       Arg::set_f(-0.05) },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       Arg::set_f(0.05) },
	{ MODKEY|ShiftMask,             XK_f,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_p,      quit,           {0} },
  { MODKEY|ControlMask|ShiftMask, XK_r,      quit,           {1} },
	{ MODKEY|ShiftMask,             XK_j,      slankdev_movestack,      Arg::set_i(+1) },
	{ MODKEY|ShiftMask,             XK_k,      slankdev_movestack,      Arg::set_i(-1) },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_Tab,   scratchpad_show,   {0} },
	{ MODKEY|ShiftMask,             XK_Tab,   scratchpad_hide,   {0} },
	{ MODKEY,                       XK_equal, scratchpad_remove, {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      Arg::set_v(&layouts[2]) },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          Arg::set_v(termcmd) },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

