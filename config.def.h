/* See LICENSE file for copyright and license details. */

static unsigned int borderpx				= 3;    /* border pixel of windows */
static unsigned int snap					= 20;   /* snap pixel */

/* bar */
static int showbar							= 1;	/* 0 means no bar */
static int topbar							= 1;	/* 0 means bottom bar */
static const int user_bh					= 25;   /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad					= 15;   /* vertical padding of bar */
static const int sidepad					= 20;   /* horizontal padding of bar */
static int bb								= 5;	/* bar border */

/* gaps */
static const unsigned int gappih			= 15;   /* horiz inner gap between windows */
static const unsigned int gappiv			= 15;   /* vert inner gap between windows */
static const unsigned int gappoh			= 20;   /* horiz outer gap between windows and screen edge */
static const unsigned int gappov			= 15;   /* vert outer gap between windows and screen edge */
static const int smartgaps					= 0;    /* 1 means no outer gap when there is only one window */

/* systray */
static const unsigned int systraypinning	= 0;	/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing	= 0;	/* systray spacing */
static const int systraypinningfailfirst	= 1;	/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray				= 1;	/* 0 means no systray */

static char dmenu_lnm[]						= "10"; /* dmenu line number */

static const int swallowfloating			= 0;    /* 1 means swallow floating windows by default */

static char *fonts[]						= {
											"Font Awesome 5 Free Solid:size=13:antialias=true:autohint=true",
											"Font Awesome 5 Brands:size=13:antialias=true:autohint=true",
											"Fira Code:size=9:antialias=true:autohint=true:style=Regular",
											};
/* colors */
static char normbgcolor[]					= "#000000";
static char normbordercolor[]				= "#000000";
static char normfgcolor[]					= "#ffffff";

static char selfgcolor[]					= "#000000";
static char selbordercolor[]				= "#ffffff";
static char selbgcolor[]					= "#ffffff";

static char statfg[]						= "#000000";
static char statbg[]						= "#ffffff";
static char statborder[]					= "#ffffff";

static char tagnormfg[]						= "#000000";
static char tagnormbg[]						= "#ffffff";
static char tagnormborder[]					= "#ffffff";

static char tagselfg[]						= "#000000";
static char tagselbg[]						= "#ffffff";
static char tagselborder[]					= "#ffffff";

static char infonormfg[]					= "#000000";
static char infonormbg[]					= "#ffffff";
static char infonormborder[]				= "#ffffff";

static char infoselfg[]						= "#000000";
static char infoselbg[]						= "#ffffff";
static char infoselborder[]					= "#ffffff";

static char taggridfg[]						= "#f8faaa";
static char taggridbg[]						= "#005577";
static char taggridborder[]					= "#ffffff";

static char *colors[][3]					= {
											[SchemeNorm]		= { normfgcolor, normbgcolor, normbordercolor	},
											[SchemeSel]			= { selfgcolor,  selbgcolor,  selbordercolor	},
											[SchemeStatus]		= { statfg,		 statbg,	  statborder		}, // Statusbar right {text,background,not used but cannot be empty}
											[SchemeTagsNorm]	= { tagnormfg,   tagnormbg,   tagnormborder		}, // Tagbar left unselected {text,background,not used but cannot be empty}
											[SchemeTagsSel]		= { tagselfg,	 tagselbg,	  tagselborder		}, // Tagbar left selected {text,background,not used but cannot be empty}
											[SchemeInfoNorm]	= { infonormfg,  infonormbg,  infonormborder	}, // infobar middle  unselected {text,background,not used but cannot be empty}
											[SchemeInfoSel]		= { infoselfg,	 infoselbg,	  infoselborder		}, // infobar middle  selected {text,background,not used but cannot be empty}
											[SchemeTagGrid]		= { taggridfg,	 taggridbg,	  taggridborder		},
											};
/* alphas */
static const unsigned int baralpha			= 0x64; /* bar alpha */
static const unsigned int borderalpha		= 0x64; /* border alpha */
static const unsigned int fgalpha			= 0x64; /* foreground alpha */

static const unsigned int alphas[][3]		= {
											/*               fg      bg        border     */
											[SchemeNorm]		= { fgalpha, baralpha, borderalpha	},
											[SchemeSel]			= { fgalpha, baralpha, borderalpha	},
											[SchemeStatus]		= { fgalpha, baralpha, borderalpha	}, // Statusbar right {text,background,not used but cannot be empty}
											[SchemeTagsNorm]	= { fgalpha, baralpha, borderalpha	}, // Tagbar left unselected {text,background,not used but cannot be empty}
											[SchemeTagsSel]		= { fgalpha, baralpha, borderalpha	}, // Tagbar left selected {text,background,not used but cannot be empty}
											[SchemeInfoNorm]	= { fgalpha, baralpha, borderalpha	}, // infobar middle  unselected {text,background,not used but cannot be empty}
											[SchemeInfoSel]		= { fgalpha, baralpha, borderalpha	}, // infobar middle  selected {text,background,not used but cannot be empty}
											[SchemeTagGrid]		= { fgalpha, baralpha, borderalpha	},
											};

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *sp1[] = {"st", "-n", "sp1", "-g", "120x34", NULL };
const char *sp2[] = {"st", "-n", "sp2", "-g", "120x34", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"sp1",      sp1},
	{"sp2",      sp2},
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

/* grid of tags */
#define DRAWCLASSICTAGS             1 << 0
#define DRAWTAGGRID                 1 << 1

#define SWITCHTAG_UP                1 << 0
#define SWITCHTAG_DOWN              1 << 1
#define SWITCHTAG_LEFT              1 << 2
#define SWITCHTAG_RIGHT             1 << 3
#define SWITCHTAG_TOGGLETAG         1 << 4
#define SWITCHTAG_TAG               1 << 5
#define SWITCHTAG_VIEW              1 << 6
#define SWITCHTAG_TOGGLEVIEW        1 << 7

static const unsigned int drawtagmask = DRAWTAGGRID; /* | DRAWCLASSICTAGS to show classic row of tags */
static const int tagrows = 3;

/* Bartabgroups properties */
#define BARTAB_BORDERS 1       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 0  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 2 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 5        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 3      // # rows in tag grid (9 tags, e.g. 3x3)
//static void (*bartabmonfns[])(Monitor *) = { monocle [> , customlayoutfn <] };
//static void (*bartabfloatfns[])(Monitor *) = { NULL [> , customlayoutfn <] };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance		title				tags mask	isfloating	noswallow   isterminal  iscentered monitor */
	{ "St",			NULL,			NULL,				0,			0,			0,			1,			1,			-1 },
	{ "tabbed",		NULL,			NULL,				0,			0,			0,			1,			1,			-1 },
	{ NULL,			NULL,			"Event Tester",			0,			1,			1,			0,			1,			-1 }, /* xev */
	{ NULL,			"sp1",			NULL,				SPTAG(0),		1,			0,			-1,			1,			-1 },
	{ NULL,			"sp2",			NULL,				SPTAG(1),		1,			0,			-1,			1,			-1 },
	{ NULL,			"translate",		NULL,				0,			1,			1,			-1,			1,			-1 },

};

/* layout(s) */
static float mfact					= 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster					= 1;    /* number of clients in master area */
static const int attachdirection	= 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static int resizehints				= 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints			= 1;    /* 1 means respect decoration hints */

static const char *layoutmenu_cmd = "dwm_setlayoutmenu";

#include "layouts.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",			tile },    /* first entry is default */
	{ "",			NULL },    /* no layout function means floating behavior */
 	{ " (s)",      spiral },
 	{ " (d)",      dwindle },
	{ "|M|",		centeredmaster },
	{ "D",			deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ Mod1Mask|ShiftMask,           KEY,      swaptags,       {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-F", "-m", dmenumon, "-c", "-l", dmenu_lnm, "-b", NULL };
static const char *termcmd[]  = { "tabbedst", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "statfg",				STRING,  &statfg },
		{ "statbg",				STRING,  &statbg },
		{ "statborder",			STRING,  &statborder },
		{ "tagnormfg",			STRING,  &tagnormfg },
		{ "tagnormbg",			STRING,  &tagnormbg },
		{ "tagnormborder",		STRING,  &tagnormborder },
		{ "tagselfg",			STRING,  &tagselfg },
		{ "tagselbg",			STRING,  &tagselbg },
		{ "tagselborder",		STRING,  &tagselborder },
		{ "infonormfg",			STRING,  &infonormfg },
		{ "infonormbg",			STRING,  &infonormbg },
		{ "infonormborder",		STRING,  &infonormborder },
		{ "infoselfg",			STRING,  &infoselfg },
		{ "infoselbg",			STRING,  &infoselbg },
		{ "infoselborder",		STRING,  &infoselborder },
		{ "taggridfg",			STRING,  &taggridfg },
		{ "taggridbg",			STRING,  &taggridbg },
		{ "taggridborder",		STRING,  &taggridborder },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "topbar",				INTEGER, &topbar },
		{ "showbar",          	INTEGER, &showbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
		{ "barborder",			INTEGER, &bb },
};

#include "shiftview.c"

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
	/* GAP CONTROL */
	/*
	 *{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	 *{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	 *{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	 *{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	 *{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	 *{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	 *{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	 *{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	 *{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	 *{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	 *{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	 *{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	 *{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	 *{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	 *{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	 *{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	 */
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	//{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },

	{ MODKEY|ShiftMask|ControlMask, XK_j,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask|ControlMask, XK_k,	moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask|ControlMask, XK_l,	moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask|ControlMask, XK_h,	moveresize,     {.v = "-25x 0y 0w 0h" } },

	{ MODKEY|Mod1Mask,				XK_j,	moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask,				XK_k,	moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask,				XK_l,	moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask,				XK_h,	moveresize,     {.v = "0x 0y -25w 0h" } },

	//{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	//{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	//{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	//{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },

	//{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,            			XK_u,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_y,  	   togglescratch,  {.ui = 1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ShiftMask,           XK_k,	   switchtag,      { .ui = SWITCHTAG_UP     | SWITCHTAG_VIEW } },
    { MODKEY|ShiftMask,           XK_j,	   switchtag,      { .ui = SWITCHTAG_DOWN   | SWITCHTAG_VIEW } },
    { MODKEY|ShiftMask,           XK_l,	   switchtag,      { .ui = SWITCHTAG_RIGHT  | SWITCHTAG_VIEW } },
    { MODKEY|ShiftMask,           XK_h,	   switchtag,      { .ui = SWITCHTAG_LEFT   | SWITCHTAG_VIEW } },
    { MODKEY|Mod4Mask|ControlMask,              XK_k,     switchtag,      { .ui = SWITCHTAG_UP     | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY|Mod4Mask|ControlMask,              XK_j,   switchtag,      { .ui = SWITCHTAG_DOWN   | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY|Mod4Mask|ControlMask,              XK_l,  switchtag,      { .ui = SWITCHTAG_RIGHT  | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY|Mod4Mask|ControlMask,              XK_h,   switchtag,      { .ui = SWITCHTAG_LEFT   | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
	{ MODKEY,			XK_z,		shiftview,	{ .i = -1 } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayoutmenu,  {0} },
	//{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* dwmc */

#include "dwmc.c"

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "reload",	        livereloadxres },
};
