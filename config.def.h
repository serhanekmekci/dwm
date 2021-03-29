/* See LICENSE file for copyright and license details. */

static unsigned int borderpx				= 3;    /* border pixel of windows */
static unsigned int snap					= 20;   /* snap pixel */

/* bar */
static int showbar							= 1;	/* 0 means no bar */
static int topbar							= 1;	/* 0 means bottom bar */
static const int user_bh					= 28;   /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
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

/* window swallowing */
static const int swaldecay					= 3;
static const int swalretroactive			= 1;
static const char swalsymbol[]				= "";


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

/* Bartabgroups properties */
#define BARTAB_BORDERS 0       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 0  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 1 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 6        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 3      // # rows in tag grid (9 tags, e.g. 3x3)

static const unsigned int drawtagmask = DRAWTAGGRID; /* | DRAWCLASSICTAGS to show classic row of tags */
static const int tagrows = 3;


static Key keys[0];

#define MODKEY Mod4Mask
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance		title				tags mask	isfloating	iscentered monitor */
	{ "St",			NULL,			NULL,				0,			0,			1,			-1 },
	{ "tabbed",		NULL,			NULL,				0,			0,			1,			-1 },
	{ NULL,			NULL,			"Event Tester",		0,			1,			1,			-1 }, /* xev */
	{ NULL,			"sp1",			NULL,				SPTAG(0),	1,			1,			-1 },
	{ NULL,			"sp2",			NULL,				SPTAG(1),	1,			1,			-1 },
	{ NULL,			"translate",	NULL,				0,			1,			1,			-1 },
	{ "Steam",		"Steam",		NULL,				0,			0,			0,			-1 },
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

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayoutmenu,  {0} },
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
#include "shiftview.c"

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
	{ "togglefullscr",  togglefullscr},
	{ "swaptags",       swaptags},
	{ "togglesticky",   togglesticky},
	{ "togglescratch",  togglescratch},
	{ "switchtag",		switchtag},
	{ "shiftview",      shiftview},
	{ "moveresize",		moveresize},
	{ "swalstopsel",	swalstopsel},
	{ "swalmouse",		swalmouse},
};
