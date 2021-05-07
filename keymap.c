#include QMK_KEYBOARD_H

#include "custom_defines.h"
#include "whitefox.h"

enum custom_keycodes {
    // FN1 macros
    MCR_SSH = SAFE_RANGE,
    MCR_EUR,

    // CapsLock single tap macros
    MCR_ARR,  // ->
    MCR_ARR2, // =>

    // CapsLock single tap macros for Mac
    MACRO_N,  // ñ (Mac OS)
    MACRO_A,  // á (Mac OS)
    MACRO_E,  // é (Mac OS)
    MACRO_I,  // í (Mac OS)
    MACRO_O,  // ó (Mac OS)
    MACRO_U,  // ú (Mac OS)
    MCR_COL,  // Cmd + right, ;

    // CapsLock single tap macros for Windows
    MACRO_NW, // ñ (Win)
    MACRO_AW, // á (Win)
    MACRO_EW, // é (Win)
    MACRO_IW, // í (Win)
    MACRO_OW, // ó (Win)
    MACRO_UW, // ú (Win)

    // Tab key macros
    MCR_EMA, // personal email
    MCR_WEM, // work email
    MCR_WUS, // work username
    MCR_PHO, // phone
    MCRO_UP, // up
    MCR_DOW, // down
    MCR_RIG, // right
    MCR_LEF, // left
    MCR_END, // Cmd + right
    MCR_STA, // Cmd + left

    // DYNAMIC MACROS (must be the last item)
    DYNAMIC_MACRO_RANGE
};

// Define shorter constants

#define _______ KC_TRNS

#define DYN_REC DYN_REC_START1
#define DYN_STO DYN_REC_STOP
#define DYN_PLA DYN_MACRO_PLAY1

// Define layers

#define LAYER_MAC  0
#define LAYER_WIN  1
#define LAYER_FN1  2
#define LAYER_FN2  3
#define LAYER_CAP  4
#define LAYER_CAPW 5
#define LAYER_TAB  6

#define KC_FN1 MO(LAYER_FN1)
#define KC_FN2 MO(LAYER_FN2)
#define DF_WIN DF(LAYER_WIN)
#define DF_MAC DF(LAYER_MAC)

// enable the numpad on start-up to make windows macros (alt keycodes) work
void led_set_keymap(uint8_t usb_led) {
    if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
}

void keymap_led_blink(void)
{
#ifdef BACKLIGHT_ENABLE
    backlight_toggle();
    wait_ms(100);
    backlight_toggle();
#endif
}

void keyboard_post_init_user(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_level(3);
    backlight_enable();
#endif
}

uint32_t default_layer_state_set_user(uint32_t state) {
    keymap_led_blink();
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {

            // FN1 key macros
            case MCR_SSH:
                keymap_led_blink();
                SEND_STRING(SS_TAP(X_ENTER)"~."); // Disconnect SSH session
                return false;
            case MCR_EUR:
                SEND_STRING(SS_LALT(SS_LSFT("2"))); // €
                return false;


            // CapsLock single tap macros
            case MCR_ARR:
                SEND_STRING("->");
                layer_off(LAYER_CAP);
                return false;
            case MCR_ARR2:
                SEND_STRING("=>");
                layer_off(LAYER_CAP);
                return false;


            // CapsLock single tap macros for Mac
            case MACRO_N:
                SEND_STRING(SS_LALT("n")"n"); // ñ
                layer_off(LAYER_CAP);
                return false;
            case MACRO_A:
                SEND_STRING(SS_LALT("e")"a"); // á
                layer_off(LAYER_CAP);
                return false;
            case MACRO_E:
                SEND_STRING(SS_LALT("e")"e"); // é
                layer_off(LAYER_CAP);
                return false;
            case MACRO_I:
                SEND_STRING(SS_LALT("e")"i"); // í
                layer_off(LAYER_CAP);
                return false;
            case MACRO_O:
                SEND_STRING(SS_LALT("e")"o"); // ó
                layer_off(LAYER_CAP);
                return false;
            case MACRO_U:
                SEND_STRING(SS_LALT("e")"u"); // ú
                layer_off(LAYER_CAP);
                return false;
            case MCR_COL:
                SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT))";"); // Cmd + right, ;
                layer_off(LAYER_CAP);
                return false;


            // CapsLock single tap macros for Windows
            case MACRO_NW:
                SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_6)SS_TAP(X_KP_4))); // ñ
                layer_off(LAYER_CAPW);
                return false;
            case MACRO_AW:
                SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_6)SS_TAP(X_KP_0))); // á
                layer_off(LAYER_CAPW);
                return false;
            case MACRO_EW:
                SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_0))); // é
                layer_off(LAYER_CAPW);
                return false;
            case MACRO_IW:
                SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_6)SS_TAP(X_KP_1))); // í
                layer_off(LAYER_CAPW);
                return false;
            case MACRO_OW:
                SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_6)SS_TAP(X_KP_2))); // ó
                layer_off(LAYER_CAPW);
                return false;
            case MACRO_UW:
                SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_6)SS_TAP(X_KP_3))); // ú
                layer_off(LAYER_CAPW);
                return false;


            // Tab key macros
            case MCR_EMA:
                SEND_STRING(MY_EMAIL);
                return false;
            case MCR_WEM:
                SEND_STRING(MY_WORK_EMAIL);
                return false;
            case MCR_WUS:
                SEND_STRING(MY_WORK_USERNAME);
                return false;
            case MCR_PHO:
                SEND_STRING(MY_PHONE_NUMBER);
                return false;
            case MCRO_UP:
                SEND_STRING(SS_TAP(X_UP));
                return false;
            case MCR_DOW:
                SEND_STRING(SS_TAP(X_DOWN));
                return false;
            case MCR_RIG:
                SEND_STRING(SS_TAP(X_RIGHT));
                return false;
            case MCR_LEF:
                SEND_STRING(SS_TAP(X_LEFT));
                return false;
            case MCR_END:
                SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT))); // Cmd + right
                return false;
            case MCR_STA:
                SEND_STRING(SS_LGUI(SS_TAP(X_LEFT))); // Cmd + left
                return false;
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0
     * ,----------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|F12 |
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|Pla |
     * |----------------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |vol+|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |vol-|
     * |----------------------------------------------------------------|
     * |Ctrl|Alt |Gui |         Space    |Fn1 |Fn2 |       |Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    // Base layout MAC
    [LAYER_MAC] = LAYOUT_truefox( \
        KC_ESC,                  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, KC_F12, \
        LT(LAYER_TAB, KC_TAB),   KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_MPLY,\
        OSL(LAYER_CAP),          KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_VOLU,\
        KC_LSPO,                 KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_VOLD,\
        KC_LCTL,        KC_LALT, KC_LGUI,               KC_SPC,           KC_FN1, KC_FN2,                            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    // Base layout WIN
    [LAYER_WIN] = LAYOUT_truefox( \
        KC_ESC,                  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, KC_F12, \
        KC_TAB,                  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_MPLY,\
        OSL(LAYER_CAPW),         KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_VOLU,\
        KC_LSFT,                 KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_VOLD,\
        KC_LGUI,        KC_LALT, KC_LCTL,               KC_SPC,           KC_FN1, KC_FN2,                            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    // Activated holding FN1
    [LAYER_FN1] = LAYOUT_truefox( \
        MCR_SSH,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11,  KC_F12,  KC_F13,  KC_F14, KC_F15, \
        _______, _______,  DF_WIN, MCR_EUR, DYN_REC, DYN_STO, _______, _______, _______, _______, KC_MPLY, _______, _______,  KC_DEL, _______,\
        KC_CAPS,   KC_F1,   KC_F2, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_MFFD,\
        _______,          _______, _______, _______, _______, _______, _______,  DF_MAC, _______, _______, _______, _______, KC_PGUP, KC_MRWD,\
        _______, _______, _______,               _______,          _______, _______,                                KC_HOME, KC_PGDN, KC_END  \
    ),
    // Activated holding FN2
    [LAYER_FN2] = LAYOUT_truefox( \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          BL_TOGG, _______,\
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_INC, _______,\
        _______, _______, _______,               _______,          _______, _______,                       BL_BRTG, BL_DEC, BL_STEP  \
    ),
    // Activated with one tap on CapsLock from MAC layout
    [LAYER_CAP] = LAYOUT_truefox( \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MCR_ARR, MCR_ARR2, _______, _______, _______,\
        _______, _______, _______, MACRO_E, _______, _______, _______, MACRO_U, MACRO_I, MACRO_O, _______, _______, _______,  _______, _______,\
        _______, MACRO_A, _______, _______, _______, _______, _______, _______, _______, _______, MACRO_N, _______,           MCR_COL, _______,\
        _______,          _______, _______, _______, _______, _______, MACRO_N, _______, _______, _______, _______, _______,  _______, _______,\
        _______, _______, _______,               _______,           _______, _______,                               _______,  _______, _______ \
    ),
    // Activated with one tap on CapsLock from WIN layout
    [LAYER_CAPW] = LAYOUT_truefox( \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, MACRO_EW, _______, _______, _______, MACRO_UW, MACRO_IW, MACRO_OW, _______, _______, _______,  _______, _______,\
        _______, MACRO_AW, _______, _______, _______, _______, _______, _______, _______, _______, MACRO_NW, _______,           _______, _______,\
        _______,          _______, _______, _______, _______, _______, MACRO_NW, _______, _______, _______, _______, _______,  _______, _______,\
        _______, _______, _______,               _______,           _______, _______,                               _______,  _______, _______ \
    ),
    // Activated holding TAB
    [LAYER_TAB] = LAYOUT_truefox( \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
        _______, DYN_PLA, MCR_WEM, MCR_EMA, _______, _______, _______, MCR_STA, MCRO_UP, MCR_END, MCR_PHO, _______, _______, _______, _______,\
        _______, _______, MCR_WUS, _______, _______, _______, _______, MCR_LEF, MCR_DOW, MCR_RIG, _______, _______,          _______, _______,\
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
        _______, _______, _______,               _______,           _______, _______,                               _______, _______, _______ \
    ),
};

const uint16_t fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2),
    [2] = ACTION_LAYER_MOMENTARY(3),
    [3] = ACTION_LAYER_MOMENTARY(4),
    [4] = ACTION_LAYER_MOMENTARY(5),
    [5] = ACTION_LAYER_MOMENTARY(6),
};
