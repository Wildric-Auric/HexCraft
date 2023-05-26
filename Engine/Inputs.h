#pragma once



typedef int InputKey;

enum class KeyBoardMode {
	INPUT_QWERTY,
	INPUT_AZERTY
};

enum class DirectionalKey {
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_LEFT,
	INPUT_DOWN
};


class Inputs {
public:
	static KeyBoardMode keyBoardMode;
	static int KeyPressed(InputKey key);
	static int DirectionalKeyPressed(DirectionalKey key);
};



























//Copied from glfw3.h -------------------------------------------------------------------------------
#define HEX_INPUT_KEY_UNKNOWN            -1

/* Printable keys */
#define HEX_INPUT_KEY_SPACE              32
#define HEX_INPUT_KEY_APOSTROPHE         39  /* ' */
#define HEX_INPUT_KEY_COMMA              44  /* , */
#define HEX_INPUT_KEY_MINUS              45  /* - */
#define HEX_INPUT_KEY_PERIOD             46  /* . */
#define HEX_INPUT_KEY_SLASH              47  /* / */
#define HEX_INPUT_KEY_0                  48
#define HEX_INPUT_KEY_1                  49
#define HEX_INPUT_KEY_2                  50
#define HEX_INPUT_KEY_3                  51
#define HEX_INPUT_KEY_4                  52
#define HEX_INPUT_KEY_5                  53
#define HEX_INPUT_KEY_6                  54
#define HEX_INPUT_KEY_7                  55
#define HEX_INPUT_KEY_8                  56
#define HEX_INPUT_KEY_9                  57
#define HEX_INPUT_KEY_SEMICOLON          59  /* ; */
#define HEX_INPUT_KEY_EQUAL              61  /* = */
#define HEX_INPUT_KEY_A                  65
#define HEX_INPUT_KEY_B                  66
#define HEX_INPUT_KEY_C                  67
#define HEX_INPUT_KEY_D                  68
#define HEX_INPUT_KEY_E                  69
#define HEX_INPUT_KEY_F                  70
#define HEX_INPUT_KEY_G                  71
#define HEX_INPUT_KEY_H                  72
#define HEX_INPUT_KEY_I                  73
#define HEX_INPUT_KEY_J                  74
#define HEX_INPUT_KEY_K                  75
#define HEX_INPUT_KEY_L                  76
#define HEX_INPUT_KEY_M                  77
#define HEX_INPUT_KEY_N                  78
#define HEX_INPUT_KEY_O                  79
#define HEX_INPUT_KEY_P                  80
#define HEX_INPUT_KEY_Q                  81
#define HEX_INPUT_KEY_R                  82
#define HEX_INPUT_KEY_S                  83
#define HEX_INPUT_KEY_T                  84
#define HEX_INPUT_KEY_U                  85
#define HEX_INPUT_KEY_V                  86
#define HEX_INPUT_KEY_W                  87
#define HEX_INPUT_KEY_X                  88
#define HEX_INPUT_KEY_Y                  89
#define HEX_INPUT_KEY_Z                  90
#define HEX_INPUT_KEY_LEFT_BRACKET       91  /* [ */
#define HEX_INPUT_KEY_BACKSLASH          92  /* \ */
#define HEX_INPUT_KEY_RIGHT_BRACKET      93  /* ] */
#define HEX_INPUT_KEY_GRAVE_ACCENT       96  /* ` */
#define HEX_INPUT_KEY_WORLD_1            161 /* non-US
#define HEX_INPUT_KEY_WORLD_2            162 /* non-US

/* Function keys */
#define HEX_INPUT_KEY_ESCAPE             256
#define HEX_INPUT_KEY_ENTER              257
#define HEX_INPUT_KEY_TAB                258
#define HEX_INPUT_KEY_BACKSPACE          259
#define HEX_INPUT_KEY_INSERT             260
#define HEX_INPUT_KEY_DELETE             261
#define HEX_INPUT_KEY_RIGHT              262
#define HEX_INPUT_KEY_LEFT               263
#define HEX_INPUT_KEY_DOWN               264
#define HEX_INPUT_KEY_UP                 265
#define HEX_INPUT_KEY_PAGE_UP            266
#define HEX_INPUT_KEY_PAGE_DOWN          267
#define HEX_INPUT_KEY_HOME               268
#define HEX_INPUT_KEY_END                269
#define HEX_INPUT_KEY_CAPS_LOCK          280
#define HEX_INPUT_KEY_SCROLL_LOCK        281
#define HEX_INPUT_KEY_NUM_LOCK           282
#define HEX_INPUT_KEY_PRINT_SCREEN       283
#define HEX_INPUT_KEY_PAUSE              284
#define HEX_INPUT_KEY_F1                 290
#define HEX_INPUT_KEY_F2                 291
#define HEX_INPUT_KEY_F3                 292
#define HEX_INPUT_KEY_F4                 293
#define HEX_INPUT_KEY_F5                 294
#define HEX_INPUT_KEY_F6                 295
#define HEX_INPUT_KEY_F7                 296
#define HEX_INPUT_KEY_F8                 297
#define HEX_INPUT_KEY_F9                 298
#define HEX_INPUT_KEY_F10                299
#define HEX_INPUT_KEY_F11                300
#define HEX_INPUT_KEY_F12                301
#define HEX_INPUT_KEY_F13                302
#define HEX_INPUT_KEY_F14                303
#define HEX_INPUT_KEY_F15                304
#define HEX_INPUT_KEY_F16                305
#define HEX_INPUT_KEY_F17                306
#define HEX_INPUT_KEY_F18                307
#define HEX_INPUT_KEY_F19                308
#define HEX_INPUT_KEY_F20                309
#define HEX_INPUT_KEY_F21                310
#define HEX_INPUT_KEY_F22                311
#define HEX_INPUT_KEY_F23                312
#define HEX_INPUT_KEY_F24                313
#define HEX_INPUT_KEY_F25                314
#define HEX_INPUT_KEY_KP_0               320
#define HEX_INPUT_KEY_KP_1               321
#define HEX_INPUT_KEY_KP_2               322
#define HEX_INPUT_KEY_KP_3               323
#define HEX_INPUT_KEY_KP_4               324
#define HEX_INPUT_KEY_KP_5               325
#define HEX_INPUT_KEY_KP_6               326
#define HEX_INPUT_KEY_KP_7               327
#define HEX_INPUT_KEY_KP_8               328
#define HEX_INPUT_KEY_KP_9               329
#define HEX_INPUT_KEY_KP_DECIMAL         330
#define HEX_INPUT_KEY_KP_DIVIDE          331
#define HEX_INPUT_KEY_KP_MULTIPLY        332
#define HEX_INPUT_KEY_KP_SUBTRACT        333
#define HEX_INPUT_KEY_KP_ADD             334
#define HEX_INPUT_KEY_KP_ENTER           335
#define HEX_INPUT_KEY_KP_EQUAL           336
#define HEX_INPUT_KEY_LEFT_SHIFT         340
#define HEX_INPUT_KEY_LEFT_CONTROL       341
#define HEX_INPUT_KEY_LEFT_ALT           342
#define HEX_INPUT_KEY_LEFT_SUPER         343
#define HEX_INPUT_KEY_RIGHT_SHIFT        344
#define HEX_INPUT_KEY_RIGHT_CONTROL      345
#define HEX_INPUT_KEY_RIGHT_ALT          346
#define HEX_INPUT_KEY_RIGHT_SUPER        347
#define HEX_INPUT_KEY_MENU               348

#define HEX_INPUT_KEY_LAST               HEX_INPUT_KEY_MENU


