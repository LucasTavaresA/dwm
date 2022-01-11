/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int focusonwheel  = 0;
static const char *fonts[]     = {
    "Inconsolata Regular:size=11",
    "SauceCodePro Nerd Font Mono:weight=bold:size=16:antialias=true:hinting=true"
};
static const char dmenufont[]  = "Inconsolata Regular:size=11";
static const char col_black[]  = "#000000";
static const char col_white[]  = "#FFFFFF";
static const char col_red[]    = "#FF0000";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_black },
	[SchemeSel]  = { col_white, col_black, col_white },
	[SchemeUrg]  = { col_white, col_black, col_red },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *sp1[] = {"st", "-c", "stscratchpad", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"st",      sp1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isfakefullscreen monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,               -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           1,               -1 },
	/*class               instance            title            tags mask iscentered isfloating isfakefullscreen isterminal noswallow monitor */
	{ "Gimp",             NULL,               NULL,            0,        0,         0,         0,               0,         0,        -1 },
	{ "gimp",             NULL,               NULL,            0,        0,         0,         0,               0,         0,        -1 },
	{ "Firefox",          NULL,               NULL,            1 << 8,   0,         0,         1,               0,         0,       -1 },
	{ "qutebrowser",      "qutebrowser",      NULL,            1 << 8,   0,         0,         1,               0,         0,       -1 },
	{ "confirm",          NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "file_progress",    NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "dialog",           NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "download",         NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "error",            NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "MPlayer",          NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "notification",     NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "pinentry-gtk-2",   NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "splash",           NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "toolbar",          NULL,               NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "Galculator",       "galculator",       NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "firefox",          "Devtools",         NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "MEGAsync",         "megasync",         NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "firefox",          "Places",           NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "Transmission-gtk", "transmission-gtk", NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "Gcr-prompter",     "gcr-prompter",     NULL,            1 << 8,   1,         1,         0,               0,         0,        -1 },
	{ "ncmpcpp",          NULL,               NULL,            1 << 8 ,  1,         1,         0,               0,         1,        -1 },
	{ "pulsemixer",       NULL,               NULL,            1 << 8 ,  1,         1,         0,               0,         1,        -1 },
    { NULL,               NULL,               "Event Tester",  0,        0,         0,         0,               0,         1,        -1 }, /* xev */
	{ "stscratchpad",	  NULL,	              NULL,		       SPTAG(0), 1,         0,		   0,               1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout Monocle[] = {
	{ "  ",      monocle },
};

static const Layout Grid[] = {
    { "─┼─",      gaplessgrid },
};

static const Layout layouts[] = {
	{ "┬┬┬",      bstack },
    { " ├─",      tile },
};

/* key definitions */
/* #define TAGKEYS(KEY,TAG) \ */
	/* { Mod4Mask,                       KEY,      view,           {.ui = 1 << TAG} }, \ */
	/* { Mod4Mask|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \ */
	/* { Mod4Mask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \ */
	/* { Mod4Mask|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* aplicações */
/* static const char *st[]              = { "st",                                    NULL }; */

/* Atalhos configurados usando sxhkd */
/* static Key keys[] = { */
	/* modifier           key             function          argument */
    /* { Mod4Mask|ShiftMask,   XK_Return,      spawn,            {.v = st } }, */
	/* { Mod4Mask,             XK_backslash,   togglescratch,    {.ui = 0 } }, */
	/* { Mod4Mask,             XK_t,           togglefloating,   {0} }, */
	/* { Mod4Mask|ShiftMask,   XK_space,       togglebar,        {0} }, */
    /* { Mod4Mask,             XK_Tab,         focusstack,       {.i = +1 } }, */
    /* { Mod4Mask,             XK_Right,       focusstack,       {.i = +1 } }, */
    /* { Mod4Mask,             XK_Left,        focusstack,       {.i = -1 } }, */
	/* { Mod1Mask,             XK_Down,        setcfact,         {.f = +0.25} }, */
	/* { Mod1Mask,             XK_Up,          setcfact,         {.f = -0.25} }, */
	/* { Mod1Mask,             XK_Left,        setmfact,         {.f = -0.05} }, */
	/* { Mod1Mask,             XK_Right,       setmfact,         {.f = +0.05} }, */
    /* { Mod4Mask,             XK_Return,      zoom,             {0} }, */
	/* { ShiftMask,            XK_Menu,        killclient,       {0} }, */
	/* { Mod4Mask,             XK_Escape,      layoutscroll,     {.i = +1 } }, */
	/* { Mod4Mask,             XK_0,           view,             {.ui = ~0 } }, */
	/* { Mod4Mask|ShiftMask,   XK_0,           tag,              {.ui = ~0 } }, */
	/* TAGKEYS(                XK_1,                             0) */
	/* TAGKEYS(                XK_2,                             1) */
	/* TAGKEYS(                XK_3,                             2) */
/* }; */

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         Mod4Mask,       Button1,        movemouse,      {0} },
	{ ClkClientWin,         Mod4Mask,       Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            Mod4Mask,       Button1,        tag,            {0} },
	{ ClkTagBar,            Mod4Mask,       Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
setmonocle(const Arg *arg)
{
	setlayout(&((Arg) { .v = &Monocle[arg->i] }));
}

void
setgrid(const Arg *arg)
{
	setlayout(&((Arg) { .v = &Grid[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "setcfact",       setcfact },
	{ "togglefloating", togglefloating },
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
	{ "togglescratch",  togglescratch },
	{ "killclient",     killclient },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "setgrid",        setgrid },
	{ "setmonocle",     setmonocle },
    { "layoutscroll",   layoutscroll },
	{ "quit",           quit },
    { "togglebar",      togglebar },
};

