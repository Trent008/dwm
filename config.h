/* See LICENSE file for copyright and license details. */

/* appearance */
#include <X11/X.h>
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Symbols Nerd Font Mono:size=10","Cantarell:size=16" };
static const char dmenufont[]       = "Cantarell:size=16";
static const char col_grey1[]       = "#222d32";
static const char col_grey2[]       = "#35454d";
static const char col_grey3[]       = "#587482";
static const char col_cyan1[]       = "#14273d";
static const char col_cyan2[]       = "#397ccc";
static const char col_cyan3[]       = "#00bcd4";
static const char col_white[]       = "#b9c2c7";
static const char *colors[][3]      = {
	/*                     fg         bg         border   */
	[SchemeTagNorm]    = { col_white, col_grey1, col_grey1 },
	[SchemeTagSel]     = { col_white, col_grey2, col_grey1 },
	[SchemeTagUrgent]  = { col_cyan3, col_grey1, col_grey1 },

	[SchemeLayoutNorm] = { col_cyan2, col_grey1, col_grey1 },
	[SchemeLayoutSel]  = { col_cyan2, col_grey1, col_grey1 },

	[SchemeClientNorm] = { col_grey3, col_grey1, col_grey1 },
	[SchemeClientSel]  = { col_white, col_grey1, col_grey3 },

	[SchemeStatusNorm] = { col_grey3, col_grey1, col_grey1 },
	[SchemeStatusSel]  = { col_white, col_grey1, col_grey1 },
};

/* tagging */
static const char *tags[] = {
	"", // terminal
	"", // browser
	"", // general
	"", // code
	"󰝚", // spotify
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance  title      tags mask       isfloating   monitor */
	{ "kitty",           NULL,     NULL,           1,         0,           -1 },
	{ "Thorium-browser", NULL,     NULL,      1 << 1,         0,           -1 },
	{ "Spotify",         NULL,     NULL,      1 << 4,         0,            0 },
	{ "code-oss",        NULL,     NULL,      1 << 3,         0,           -1 },
	{ "Nemo",            NULL,     NULL,      1 << 2,         0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tiling",     tile },    /* first entry is default */
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
static char menumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *menucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *spotifycmd[]= { "spotify-launcher", NULL };
static const char *codecmd[]= { "code", NULL };
static const char *autostart[]= { "./dwm/scripts/autostart.sh", NULL };
static const Arg autostartarg= {.v = autostart };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = menucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = spotifycmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = codecmd } },
	{ MODKEY,                       XK_b,      spawn,          SHCMD ("thorium-browser")},
	{ MODKEY,                       XK_e,      spawn,          SHCMD ("nemo")},
	{ MODKEY,                       XK_z,      spawn,          SHCMD ("blueberry")},
	{ MODKEY,                       XK_p,      spawn,          SHCMD ("flameshot full -p ~/Downloads/")},
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD ("flameshot gui -p ~/Downloads/")},
	{ MODKEY|ControlMask,           XK_p,      spawn,          SHCMD ("flameshot gui --clipboard")},
	{ MODKEY,                       XK_x,      spawn,          SHCMD ("./dwm/configuration/monitor.sh")},
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
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
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

