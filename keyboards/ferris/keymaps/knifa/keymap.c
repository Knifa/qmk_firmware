#include QMK_KEYBOARD_H

// =================================================================================================

enum ferris_keycodes {
    FR_WSWC = SAFE_RANGE,  // Window switch
};

enum ferris_layers {
    _ALPHA,
    _ALPHA_SHIFT,
    _MOD,
    _MOD_SHIFT,
    _SYMBOL,
    _SYMBOL_SHIFT,
    _NAV,
    _NAV_SHIFT,
    _GAMING,
    _GAMING_SHIFT,
};

// =================================================================================================

#define MO_ALS MO(_ALPHA_SHIFT)
#define MO_MOD MO(_MOD)
#define MO_MOS MO(_MOD_SHIFT)
#define MO_SYM MO(_SYMBOL)
#define MO_SYS MO(_SYMBOL_SHIFT)
#define MO_NAV MO(_NAV)
#define MO_NAS MO(_NAV_SHIFT)

#define TG_GAME TG(_GAMING)
#define MO_GASH MO(_GAMING_SHIFT)

#define WIN_CPY LCTL(KC_C)
#define WIN_CUT LCTL(KC_X)
#define WIN_PST LCTL(KC_V)
#define WIN_UND LCTL(KC_Z)

#define LS_A LSFT(KC_A)
#define LS_B LSFT(KC_B)
#define LS_C LSFT(KC_C)
#define LS_D LSFT(KC_D)
#define LS_E LSFT(KC_E)
#define LS_F LSFT(KC_F)
#define LS_G LSFT(KC_G)
#define LS_H LSFT(KC_H)
#define LS_I LSFT(KC_I)
#define LS_J LSFT(KC_J)
#define LS_K LSFT(KC_K)
#define LS_L LSFT(KC_L)
#define LS_M LSFT(KC_M)
#define LS_N LSFT(KC_N)
#define LS_O LSFT(KC_O)
#define LS_P LSFT(KC_P)
#define LS_Q LSFT(KC_Q)
#define LS_R LSFT(KC_R)
#define LS_S LSFT(KC_S)
#define LS_T LSFT(KC_T)
#define LS_U LSFT(KC_U)
#define LS_V LSFT(KC_V)
#define LS_W LSFT(KC_W)
#define LS_X LSFT(KC_X)
#define LS_Y LSFT(KC_Y)
#define LS_Z LSFT(KC_Z)

#define WIN_SWITCH_TAPPING_TERM 300

// =================================================================================================

static bool is_win_switch_active = false;
static uint16_t win_switch_timer = 0;

// =================================================================================================

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FR_WSWC:
            if (record->event.pressed) {
                if (!is_win_switch_active) {
                    is_win_switch_active = true;
                    register_code(KC_LALT);
                }

                win_switch_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }

            return false;
            break;
        default:
            return true;
            break;
    }
}

void matrix_scan_user(void) {
    if (is_win_switch_active) {
        if (timer_elapsed(win_switch_timer) > WIN_SWITCH_TAPPING_TERM) {
            unregister_code(KC_LALT);
            is_win_switch_active = false;
        }
    }
}

// =================================================================================================

// [_LAYER] = LAYOUT(
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                _______, _______, _______, _______
// ),

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_ALPHA] = LAYOUT(
        KC_Q   , KC_W   , KC_F   , KC_P   ,  KC_B  , KC_J   , KC_L   , KC_U   , KC_Y   , KC_QUOT,
        KC_A   , KC_R   , KC_S   , KC_T   ,  KC_G  , KC_M   , KC_N   , KC_E   , KC_I   , KC_O   ,
        KC_Z   , KC_X   , KC_C   , KC_D   ,  KC_V  , KC_K   , KC_H   , KC_SPC , KC_DOT , KC_QUES,
                                   MO_NAV ,  MO_MOD, MO_ALS, MO_SYM
    ),

    [_ALPHA_SHIFT] = LAYOUT(
        LS_Q   , LS_W   , LS_F   , LS_P   ,  LS_B  , LS_J   , LS_L   , LS_U   , LS_Y   , KC_GRV,
        LS_A   , LS_R   , LS_S   , LS_T   ,  LS_G  , LS_M   , LS_N   , LS_E   , LS_I   , LS_O   ,
        LS_Z   , LS_X   , LS_C   , LS_D   ,  LS_V  , LS_K   , LS_H   , KC_ENT , KC_COMM, KC_EXLM,
                                   KC_DEL , KC_BSPC, XXXXXXX, XXXXXXX
    ),

    // =============================================================================================

    [_MOD] = LAYOUT(
        KC_ESC , _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB , KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, KC_LSFT, KC_LALT, KC_LGUI, KC_LCTL, _______,
        WIN_UND, WIN_CUT, WIN_CPY, WIN_PST, _______, _______, _______, _______, _______, _______,
                                   XXXXXXX, XXXXXXX, MO_MOS , XXXXXXX
    ),

    [_MOD_SHIFT] = LAYOUT(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, _______, _______, _______,
        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______, _______, _______, _______, _______,
        KC_F11 , KC_F12 , _______, _______, _______, _______, _______, _______, _______, _______,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    // =============================================================================================

  	[_SYMBOL] = LAYOUT(
        KC_ASTR, KC_PLUS, KC_MINS, KC_EQL , KC_CIRC, KC_0   , KC_1   , KC_2   , KC_3   , KC_4   ,
        KC_DLR , KC_SLSH, KC_DQUO, KC_LT  , KC_LBRC, KC_RBRC, KC_GT  , _______, _______, _______,
        KC_AT  , KC_PIPE, KC_COLN, KC_AMPR, KC_HASH, KC_5   , KC_6   , KC_7   , KC_8   , KC_9   ,
                                   XXXXXXX, MO_SYS,  XXXXXXX, XXXXXXX
    ),

    [_SYMBOL_SHIFT] = LAYOUT(
        KC_PERC, _______, KC_UNDS, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_BSLS, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______,
        _______, _______, KC_SCLN, KC_PERC, _______, _______, _______, _______, _______, _______,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    // =============================================================================================

    [_NAV] = LAYOUT(
        _______, _______, FR_WSWC, KC_BSPC, KC_DEL , KC_PSCR, _______, _______, _______, _______,
        _______, KC_LEFT, KC_UP  , KC_RGHT, _______, _______, _______, _______, _______, _______,
        _______, KC_TAB , KC_DOWN, KC_ENT , _______, _______, _______, _______, _______, _______,
                                   XXXXXXX, XXXXXXX, MO_NAS , XXXXXXX
    ),

    [_NAV_SHIFT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, TG_GAME,
        _______, KC_HOME, KC_PGUP, KC_END , _______, _______, _______, _______, _______, _______,
        _______, _______, KC_PGDN, _______, _______, _______, _______, _______, _______, _______,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    // =============================================================================================

    [_GAMING] = LAYOUT(
        KC_Q   , KC_1   , KC_2   , KC_3   , KC_4   , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,
        KC_LSFT, KC_A   , KC_W   , KC_D   , KC_R   , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
        KC_LCTL, KC_Z   , KC_S   , KC_E   , KC_F   , KC_F11 , KC_F12 , KC_F13 , KC_F14 , KC_F15 ,
                                   MO_GASH, KC_SPC , XXXXXXX, XXXXXXX
    ),

    [_GAMING_SHIFT] = LAYOUT(
        KC_TAB , KC_5   , KC_6   , KC_7   , KC_0   , _______, _______, _______, _______, TG_GAME,
        KC_N   , _______, _______, _______, KC_G   , _______, _______, _______, _______, _______,
        KC_M   , KC_X   , _______, KC_V   , KC_B   , _______, _______, _______, _______, _______,
                                   XXXXXXX, KC_ENT , XXXXXXX, XXXXXXX
    ),
};
