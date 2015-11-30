/* See LICENSE file for copyright and license details. */

static const char *fonts[] = {
    "Sans:pixelsize=10:style=Bold",
    "VL Gothic:size=10.5",
    "WenQuanYi Micro Hei:size=10.5"
};

static const char dmenufont[] = "monospace-10";

static const unsigned int borderpx  = 1;        	/* border pixel of windows */
static const unsigned int snap      = 32;       	/* snap pixel */
static const unsigned int systraypinning = 0;   	/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;   	/* systray spacing */
static const Bool systraypinningfailfirst = True;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = True;     	/* False means no systray */
static const Bool topbar            = True;     	/* False means bottom bar */
static const Bool resizehints 		= False; 		/* True means respect size hints in tiled resizals */

#define mfactor 	0.50
#define NUMCOLORS	7

static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  /* border  foreground background */
  { "#444444", "#dddddd", "#444444" },  /* norm */
  { "#ff0000", "#000000", "#dddddd" },  /* sel  */
  { "#000000", "#000000", "#ff9999" },
  { "#000000", "#000000", "#ffff99" },
  { "#000000", "#000000", "#add6ff" },
  { "#000000", "#000000", "#ebc2ff" },
  { "#000000", "#000000", "#ff99c2" },
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",            NULL,       NULL,       0,            	True,        -1 },
	{ "chromium-browser",NULL,       NULL,       1 << 1,       	False,       -1 },
	{ "Icedove",         NULL,       NULL,       1 << 2,       	True,        -1 },
	{ "Firefox",         NULL,       NULL,       1 << 3,       	False,       -1 },
	{ "Iceweasel",       NULL,       NULL,       1 << 3,       	False,       -1 },
	{ "XTerm",           NULL,       NULL,       1 << 8,       	False,       -1 },
	{ "Gedit",           NULL,       NULL,       1 << 7,       	False,       -1 },		
	{ "Spacefm",         NULL,       NULL,       1 << 9,       	True,        -1 },
	{ "Kodi", 	         NULL,       NULL,       1 << 10,       True,        -1 },
	{ "Vlc", 	         NULL,       NULL,       1 << 10,       True,        -1 },
	{ "Audacious", 	     NULL,       NULL,       1 << 10,       True,        -1 },	
	{ "Seamonkey",       NULL,       NULL,       1 << 11,       False,       -1 },
	{ "libreoffice",     NULL,       NULL,       1 << 12,      	False,       -1 },
	{ "Iceweasel",       NULL,       "Iceweasel Preferences", 1 << 13, True, -1 },
};

/* tagging */
static const Tag tags[] = { 
	/* Name	Layout	mfact      nmaster showbar*/
	{ "\uff5e",  0,      mfactor,   1,      True  },
	{ "\uff23",  2,      mfactor,   1,      False },
	{ "\uff20",  0,      mfactor,   1,      True  },
	{ "\uff37",  1,      0.50,      1,      True  },
	{ "\uff14",  1,      mfactor,   1,      True  },
	{ "\uff15",  1,      mfactor,   1,      False },
	{ "\uff16",  1,      mfactor,   1,      False },
	{ "\uff17",  0,      mfactor,   1,      True  },
	{ "\uff38",  1,      mfactor,   2,      True  },
	{ "\uff26",  0,      mfactor,   1,      True  },
	{ "\uff10",  0,      mfactor,   1,      True  },
	{ "\uff37",  1,      mfactor,   1,      True  },
	{ "\uff1d",  2,      mfactor,   1,      True  },
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[T]",      tile },
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", colors[0][1], "-nf", colors[0][0], "-sb", colors[0][0], "-sf", colors[0][1], NULL };

static const char *termcmd[]  = { "xterm", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoomcycle,      {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_BackSpace, view,        {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_BackSpace, tag,         {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_quoteleft,		       0)
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	TAGKEYS(                        XK_6,                      6)
	TAGKEYS(                        XK_7,                      7)
	TAGKEYS(                        XK_8,                      8)
	TAGKEYS(                        XK_9,                      9)
	TAGKEYS(                        XK_0,                      10)
	TAGKEYS(                        XK_minus,                  11)
	TAGKEYS(                        XK_equal,                  12)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
 	{ MODKEY,                       XK_Left,   xadjtag,    	   {.i = -1 } },
 	{ MODKEY,                       XK_Right,  xadjtag,		   {.i = +1 } },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,      pushup,         {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

struct Pertag 
{
	unsigned int curtag;
	int nmasters[LENGTH(tags) + 1];
	float mfacts[LENGTH(tags) + 1];
	unsigned int sellts[LENGTH(tags) + 1];
	const Layout *ltidxs[LENGTH(tags) + 1][2];
	Bool showbars[LENGTH(tags) + 1];
	Client *prevzooms[LENGTH(tags) + 1];
};

