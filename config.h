#include <stdbool.h>
#include <stdint.h>
//#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const size_t borderpx = 2; /* border pixel of windows */
static const uint32_t snap = 32;  /* snap pixel */
static const bool showbar = true; /* 0 means no bar */
static const bool topbar = true;  /* 0 means bottom bar */
//static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char* altbarclass = "Polybar";                       /* Alternate bar class name */
static const char* alttrayname = "tray";                          /* Polybar tray instance name */
static const char* altbarcmd = "$HOME/.config/polybar/launch.sh"; /* Alternate bar launch command */
static const char* fonts[] = { "Victor Mono NF:size=12" };
static const char dmenufont[] = "Victor Mono NF:size=12";
static char normbgcolor[] = "#282828";
static char normbordercolor[] = "#98971a";
static char normfgcolor[] = "#ebdbb2";
static char selfgcolor[] = "#cc241d";
static char selbordercolor[] = "#cc241d";
static char selbgcolor[] = "#3c3836";
static char* colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel] = { selfgcolor, selbgcolor, selbordercolor },
};

/* tagging */
static const char* tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
  /* class, instance, title, tags mask, isfloating, monitor, shouldMaximize, scratchkey */
  { "Gimp", NULL, NULL, 0, 1, -1, 0, 0 },
  { "Firefox", NULL, NULL, 1 << 8, 0, -1, 0, 0 },
  { NULL, NULL, "st_scratched", 0, 1, -1, 1, 's' },
};

/* layout(s) */
static const float mfact = 0.55;       /* factor of master area size [0.05..0.95] */
static const size_t nmaster = 1;       /* number of clients in master area */
static const bool resizehints = false; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=", tile }, /* first entry is default */
  { "><>", NULL }, /* no layout function means floating behavior */
  { "[M]", monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                          \
  { MODKEY, KEY, view, Arg::set_ui(1 << TAG) },                                    \
      { MODKEY | ShiftMask, KEY, tag, Arg::set_ui(1 << TAG) },                     \
      { MODKEY | ControlMask | ShiftMask, KEY, toggletag, Arg::set_ui(1 << TAG) }, \
      { MODKEY | ControlMask, KEY, toggleview, Arg::set_ui(1 << TAG) },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                      \
  {                                                     \
    .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } \
  }

/* commands */
//static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static const char* roficmd[] = { "rofi", "-show", "run", NULL };
static const char* termcmd[] = { "st", NULL };

static const char* nextlayout[] = { "xkb-switch", "-n", NULL };

static const char* screenshot_gui[] = { "flameshot", "gui", NULL };

static const char* incbacklight[] = { "brightnessctl", "set", "5%+", NULL };
static const char* decbacklight[] = { "brightnessctl", "set", "5%-", NULL };
static const char* incvolume[] = { "pamixer", "--allow-boost", "-i", "5", NULL };
static const char* decvolume[] = { "pamixer", "--allow-boost", "-d", "5", NULL };
//static const char* mutevolume[] = { "pamixer", "-t", NULL };

/*First arg only serves to match against key in rules*/
static const char* st_scratched_cmd[] = { "s", "st", "-t", "st_scratched", NULL };

static Key keys[] = {
  /* modifier                     key        function        argument */
  //{ MODKEY,                       XK_b,      togglebar,      {0} },
  //{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  //{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  //{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  //{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  //{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  //{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  //{ MODKEY,                       XK_Return, zoom,           {0} },
  //{ MODKEY,                       XK_Tab,    view,           {0} },
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
  { MODKEY, 46, slankdev_view_right, { 0 } },
  { MODKEY | ShiftMask | ControlMask, 46, slankdev_view_right, { 0 } },
  { MODKEY | ShiftMask | ControlMask, 43, slankdev_view_left, { 0 } },
  { MODKEY, 43, slankdev_view_left, { 0 } },
  //{ MODKEY,                       33,      spawn,                   Arg::set_v(dmenucmd) },
  { MODKEY, 40, spawn, Arg::set_v(roficmd) },
  { MODKEY, 28, spawn, Arg::set_v(termcmd) },
  //{ MODKEY,                       XK_f,      spawn,                   Arg::set_v("firefox") },
  { MODKEY, 44, focusstack, Arg::set_i(+1) },
  { MODKEY, 45, focusstack, Arg::set_i(-1) },
  //{ MODKEY,                       XK_space,  setlayout,               {0} },
  { MODKEY, 65, spawn, Arg::set_v(nextlayout) },
  { MODKEY | ShiftMask, 43, setmfact, Arg::set_f(-0.05) },
  { MODKEY | ShiftMask, 46, setmfact, Arg::set_f(0.05) },
  { MODKEY | ShiftMask, 41, togglefloating, { 0 } },
  { MODKEY | ShiftMask, 24, killclient, { 0 } },
  { MODKEY | ShiftMask | ControlMask, 33, quit, { 0 } },
  { MODKEY | ControlMask | ShiftMask, 27, quit, { 1 } },
  { MODKEY | ShiftMask, 44, slankdev_movestack, Arg::set_i(+1) },
  { MODKEY | ShiftMask, 45, slankdev_movestack, Arg::set_i(-1) },
  TAGKEYS(10, 0)
      TAGKEYS(11, 1)
          TAGKEYS(12, 2)
              TAGKEYS(13, 3)
                  TAGKEYS(14, 4)
                      TAGKEYS(15, 5)
                          TAGKEYS(16, 6)
                              TAGKEYS(17, 7)
                                  TAGKEYS(18, 8) { MODKEY, 23, scratchpad_show, { 0 } },
  { MODKEY | ShiftMask, 23, scratchpad_hide, { 0 } },
  { MODKEY, 66, togglescratch, Arg::set_v(st_scratched_cmd) },
  { MODKEY, 21, scratchpad_remove, { 0 } },
  { 0, 233, spawn, Arg::set_v(incbacklight) },
  { 0, 232, spawn, Arg::set_v(decbacklight) },
  { 0, 123, spawn, Arg::set_v(incvolume) },
  { 0, 122, spawn, Arg::set_v(decvolume) },
  { 0, 121, mutevolume, { 0 } },
  { 0, 107, spawn, Arg::set_v(screenshot_gui) },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol, 0, Button1, setlayout, { 0 } },
  { ClkLtSymbol, 0, Button3, setlayout, Arg::set_v(&layouts[2]) },
  { ClkWinTitle, 0, Button2, zoom, { 0 } },
  { ClkStatusText, 0, Button2, spawn, Arg::set_v(termcmd) },
  { ClkClientWin, MODKEY, Button1, movemouse, { 0 } },
  { ClkClientWin, MODKEY, Button2, togglefloating, { 0 } },
  //{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkClientWin, MODKEY, Button3, resizemouse_any, { 0 } },
  { ClkTagBar, 0, Button1, view, { 0 } },
  { ClkTagBar, 0, Button3, toggleview, { 0 } },
  { ClkTagBar, MODKEY, Button1, tag, { 0 } },
  { ClkTagBar, MODKEY, Button3, toggletag, { 0 } },
};

static const char* ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(view, 1, { ARG_TYPE_UINT }),
  IPCCOMMAND(toggleview, 1, { ARG_TYPE_UINT }),
  IPCCOMMAND(tag, 1, { ARG_TYPE_UINT }),
  IPCCOMMAND(toggletag, 1, { ARG_TYPE_UINT }),
  IPCCOMMAND(tagmon, 1, { ARG_TYPE_UINT }),
  IPCCOMMAND(focusmon, 1, { ARG_TYPE_SINT }),
  IPCCOMMAND(focusstack, 1, { ARG_TYPE_SINT }),
  IPCCOMMAND(zoom, 1, { ARG_TYPE_NONE }),
  IPCCOMMAND(spawn, 1, { ARG_TYPE_PTR }),
  //IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(killclient, 1, { ARG_TYPE_SINT }),
  IPCCOMMAND(togglefloating, 1, { ARG_TYPE_NONE }),
  IPCCOMMAND(setmfact, 1, { ARG_TYPE_FLOAT }),
  IPCCOMMAND(setlayoutsafe, 1, { ARG_TYPE_PTR }),
  IPCCOMMAND(quit, 1, { ARG_TYPE_NONE })
};
