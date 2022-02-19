/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int user_bh = 16; /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int swallowfloating = 0; /* 1 means swallow floating windows by default */
static const int focusonwheel = 0;
static const char *fonts[] = {
    "Fira Code:pixelsize=14:antialias=true:autohint=true",
    "SauceCodePro Nerd Font:size=12",
    "Mono:weight=bold:size=16:antialias=true:hinting=true"
};
static const char dmenufont[] = "Fira Code:pixelsize=14:antialias=true:autohint=true";
static const char col_black[] = "#000000";
static const char col_grey[]  = "#444444";
static const char col_white[] = "#FFFFFF";
static const char col_red[]   = "#FF0000";
static const char *colors[][3] = {
    /*                  fg         bg         border   */
    [SchemeNorm]     = {col_white, col_black, col_grey},
    [SchemeSel]      = {col_white, col_grey,  col_white},
    [SchemeUrg]      = {col_white, col_black, col_red},
	[SchemeStatus]   = {col_white, col_black, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = {col_white, col_black, "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = {col_white, col_black, "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = {col_white, col_black, "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = {col_white, col_black, "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
const char *sp1[] = {"st", "-c", "stscratchpad", NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"st", sp1},
};

/* swallow emacs */
static const char emacsclient[] = "emacsclient";
static const char emacsname[] = "emacs@";

/* tagging */
static const char *tags[] = {"", "", "3", "4", "5"};

static const unsigned int ulinepad = 0; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke = 1; /* thickness / height of the underline */
static const unsigned int ulinevoffset = 0; /* how far above the bottom of the bar the line should appear */
static const int ulineall = 0; /* 1 to show underline on all tags, 0 for just the active ones */

static const char ptagf[] = "%s %s";	/* format of a tag label */
static const char etagf[] = "%s";	/* format of an empty tag */
static const int lcaselbl = 1;		/* 1 means make tag label lowercase */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
/*   class               instance            title tagmask   iscentered isfloating isfakefullscreen isterminal noswallow mon*/
    {"Gimp",             NULL,               NULL, 0,        0,         0,         0,               0,         0,        -1},
    {"gimp",             NULL,               NULL, 0,        0,         0,         0,               0,         0,        -1},
    {"Firefox",          NULL,               NULL, 1 << 1,   0,         0,         1,               0,         0,        -1},
    {"ncmpcpp",          NULL,               NULL, 0,        1,         1,         0,               0,         1,        -1},
    {"pulsemixer",       NULL,               NULL, 0,        1,         1,         0,               0,         1,        -1},
    {"st",               NULL,               NULL, 1 << 0,   1,         0,         0,               1,         0,        -1},
    {"stscratchpad",     NULL,               NULL, SPTAG(0), 1,         0,         0,               1,         0,        -1},
    {"Emacs",            "emacs",            NULL, 1 << 0,   0,         0,         0,               0,         0,        -1},
    {"firefox",          "Places",           NULL, 1 << 1,   1,         1,         0,               0,         0,        -1},
    {"firefox",          "Devtools",         NULL, 1 << 1,   1,         1,         0,               0,         0,        -1},
    {"firefox",          "Navigator",        NULL, 1 << 1,   0,         0,         0,               0,         0,        -1},
    {"MEGAsync",         "megasync",         NULL, 1 << 8,   1,         1,         0,               0,         0,        -1},
    {"Galculator",       "galculator",       NULL, 1 << 8,   1,         1,         0,               0,         0,        -1},
    {"qutebrowser",      "qutebrowser",      NULL, 1 << 1,   0,         0,         0,               0,         0,        -1},
    {"Transmission-gtk", "transmission-gtk", NULL, 0,        1,         1,         0,               0,         0,        -1},
    /* Notificações, popups, etc. */
    {NULL, NULL, "Event Tester", 0, 1, 1, 0, 0, 1, -1},
    {"confirm", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"dialog", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"download", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"error", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"MPlayer", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"splash", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"toolbar", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"notification", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"pinentry-gtk-2", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"file_progress", NULL, NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
    {"Gcr-prompter", "gcr-prompter", NULL, 1 << 8, 1, 1, 0, 0, 0, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    {"  ", monocle},
    {"┬┬┬", bstack},
    {" ├─", tile},
    {"─┼─", gaplessgrid},
};

/* key definitions */
/* #define TAGKEYS(KEY,TAG) */
/* { Mod4Mask,                       KEY,      view,           {.ui = 1 << TAG}}, */
/* { Mod4Mask|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG}}, */
/* { Mod4Mask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG}}, */
/* { Mod4Mask|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG}}, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }}

/* aplicações */
/* static const char *st[] = { "st", NULL }; */

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
/* { MODKEY,               XK_Right,       viewnext,         {0} }, */
/* { MODKEY,               XK_Left,        viewprev,         {0} }, */
/* { MODKEY|ShiftMask,     XK_Right,       tagtonext,        {0} }, */
/* { MODKEY|ShiftMask,     XK_Left,        tagtoprev,        {0} }, */
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
/*   click         eventmask button   function     argument */
    {ClkTagBar,    Mod4Mask, Button1, tag,         {0}},
    {ClkTagBar,    Mod4Mask, Button3, toggletag,   {0}},
    {ClkClientWin, Mod4Mask, Button1, movemouse,   {0}},
    {ClkClientWin, Mod4Mask, Button3, resizemouse, {0}},
    {ClkTagBar,    0,        Button1, view,        {0}},
    {ClkTagBar,    0,        Button3, toggleview,  {0}},
    {ClkTagBar,    Mod4Mask, Button1, tag,         {0}},
    {ClkTagBar,    Mod4Mask, Button3, toggletag,   {0}},
};

void setlayoutex(const Arg *arg) { setlayout(&((Arg){.v = &layouts[arg->i]})); }

void viewex(const Arg *arg) { view(&((Arg){.ui = 1 << arg->ui})); }

void viewall(const Arg *arg) { view(&((Arg){.ui = ~0})); }

void toggleviewex(const Arg *arg) { toggleview(&((Arg){.ui = 1 << arg->ui})); }

void tagex(const Arg *arg) { tag(&((Arg){.ui = 1 << arg->ui})); }

void toggletagex(const Arg *arg) { toggletag(&((Arg){.ui = 1 << arg->ui})); }

void tagall(const Arg *arg) { tag(&((Arg){.ui = ~0})); }

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum           function */
    {"focusstack",     focusstack},
    {"setmfact",       setmfact},
    {"setcfact",       setcfact},
    {"togglefloating", togglefloating},
    {"zoom",           zoom},
    {"view",           view},
    {"viewall",        viewall},
    {"viewex",         viewex},
    {"toggleview",     view},
    {"toggleviewex",   toggleviewex},
    {"tag",            tag},
    {"tagall",         tagall},
    {"tagex",          tagex},
    {"toggletag",      tag},
    {"toggletagex",    toggletagex},
    {"togglescratch",  togglescratch},
    {"killclient",     killclient},
    {"setlayout",      setlayout},
    {"setlayoutex",    setlayoutex},
    {"layoutscroll",   layoutscroll},
    {"quit",           quit},
    {"togglebar",      togglebar},
    {"viewnext",       viewnext},
    {"viewprev",       viewprev},
    {"tagtonext",      tagtonext},
    {"tagtoprev",      tagtoprev},
};

