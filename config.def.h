/* See LICENSE file for copyright and license details. */

/* appearance */
#include <X11/X.h>
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Symbols Nerd Font Mono:size=10","Cantarell:size=16" };
static const char teal0[]       = "#030808";
static const char teal1[]       = "#081616";
static const char teal2[]       = "#0d2525";
static const char teal3[]       = "#123333";
static const char teal4[]       = "#174141";
static const char teal5[]       = "#1c5050";
static const char teal6[]       = "#215e5e";
static const char teal7[]       = "#266d6d";
static const char teal8[]       = "#2c7b7b";
static const char teal9[]      = "#318a8a";
static const char teal10[]      = "#369898";
static const char teal11[]      = "#3ba7a7";
static const char teal12[]      = "#40b5b5";
static const char teal13[]      = "#4abfbf";
static const char teal14[]      = "#59c4c4";
static const char teal15[]      = "#67c9c9";
static const char teal16[]      = "#76cece";
static const char teal17[]      = "#84d4d4";
static const char teal18[]      = "#93d9d9";
static const char teal19[]      = "#a1dede";
static const char teal20[]      = "#b0e3e3";
static const char teal21[]      = "#bee8e8";
static const char teal22[]      = "#cdeded";
static const char teal23[]      = "#dbf2f2";
static const char teal24[]      = "#eaf7f7";
static const char teal25[]      = "#f8fdfd";
static const char border_sel[]  = "#123323";
static const char border_norm[] = "#122333";
static const char *colors[][3]      = {
	/*                      forground   background  border   */
	[SchemeIconBoxNorm] = { teal4,  NULL,  NULL },
	[SchemeIconBoxSel]  = { teal6,  NULL,  NULL },
	[SchemeIconBoxUrg]  = { teal4,  NULL,  NULL },

	[SchemeIconNorm] = { teal20, NULL, NULL },
	[SchemeIconSel]  = { teal22, NULL, NULL },
	[SchemeIconUrg]  = { teal18,  NULL, NULL },

	[SchemeLayoutNorm] = { teal20, NULL, NULL },
	[SchemeLayoutSel]  = { teal22, NULL, NULL },

	[SchemeClientNorm] = { teal20, NULL, border_norm },
	[SchemeClientSel]  = { teal22, NULL, border_sel },

	[SchemeStatusNorm] = { teal20, NULL, NULL },
	[SchemeStatusSel]  = { teal22, NULL, NULL },

	[SchemeBarNorm]  = { teal2, NULL, NULL },
	[SchemeBarSel]  =  { teal3, NULL, NULL },
};

/* tagging */
static const char *tags[] = {
	"", // terminal
	"󰖟", // browser
	"", // general
	"", // code
	"󰝚", // spotify
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance  title      tags mask       isfloating   monitor */
	{ "Terminator",   NULL,     NULL,           1,         0,           -1 },
	{ "firefox",      NULL,     NULL,      1 << 1,         0,           -1 },
	{ "Thunar",       NULL,     NULL,      1 << 2,         0,           -1 },
	{ "code-oss",     NULL,     NULL,      1 << 3,         0,           -1 },
	{ "Spotify",      NULL,     NULL,      1 << 4,         0,            0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tiling",   tile },    /* first entry is default */
	{ "floating", NULL },    /* no layout function means floating behavior */
	{ "monocle",  monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "terminator", NULL };
static const char *spotifycmd[]= { "spotify-launcher", NULL };
static const char *codecmd[]= { "code", NULL };
static const char *autostart[]= { "./dwm/autostart.sh", NULL };
static const Arg autostartarg= {.v = autostart };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = spotifycmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = codecmd } },
	{ MODKEY,                       XK_b,      spawn,          SHCMD ("firefox")},
	{ MODKEY,                       XK_z,      spawn,          SHCMD ("blueberry")},
	{ MODKEY,                       XK_e,      spawn,          SHCMD ("thunar")},
	{ MODKEY,                       XK_p,      spawn,          SHCMD ("shotgun -s")},
	{ MODKEY,                       XK_x,      spawn,          SHCMD ("./dwm/monitor.sh")},
	{ 0,                            0x1008ff02, spawn,         SHCMD ("brightnessctl set +2%")},
	{ 0,                            0x1008ff03, spawn,         SHCMD ("brightnessctl set 2%-")},
	{ 0,                            0x1008ff11, spawn,         SHCMD ("pactl set-sink-volume 0 -2%")},
	{ 0,                            0x1008ff12, spawn,         SHCMD ("pactl set-sink-mute 0 toggle")},
	{ 0,                            0x1008ff13, spawn,         SHCMD ("pactl set-sink-volume 0 +2%")},
	{ 0,                            0x1008FF14, spawn,         SHCMD ("playerctl play-pause")},
	{ 0,                            0x1008FF16, spawn,         SHCMD ("playerctl previous")},
	{ 0,                            0x1008FF17, spawn,         SHCMD ("playerctl next")},
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

