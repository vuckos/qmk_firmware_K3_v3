/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

// 1. Define Tap Dance keys
enum {
    TD_LCTL_LPRN,  // Left Ctrl: Tap = '(', Hold = LCTL
    TD_RCTL_RPRN,  // Right Ctrl: Tap = ')', Hold = RCTL
    TD_RSFT_UNDER,  // Right Shift: Tap = '_', Hold = RSFT
};

// 2. Left Ctrl: '(' on tap, LCTL on hold
void td_lctl_lprn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) tap_code16(KC_LPRN);  // Tap: '('
        else register_code(KC_LCTL);  // Hold: Left Ctrl
    }
}

void td_lctl_lprn_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) unregister_code(KC_LCTL);
}

// 3. Right Ctrl: ')' on tap, RCTL on hold
void td_rctl_rprn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) tap_code16(KC_RPRN);  // Tap: ')'
        else register_code(KC_RCTL);  // Hold: Right Ctrl
    }
}

void td_rctl_rprn_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) unregister_code(KC_RCTL);
}


void td_rsft_under(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) tap_code16(KC_UNDERSCORE);  // Tap: '_'
        else register_code(KC_RSFT);  // Hold: Right Shift
    }
}

// 3. Reset function (release Shift if held)
void td_rsft_under_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) unregister_code(KC_RSFT);
}

// 4. Register Tap Dance actions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTL_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lctl_lprn, td_lctl_lprn_reset),
    [TD_RCTL_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rctl_rprn, td_rctl_rprn_reset),
    [TD_RSFT_UNDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rsft_under, td_rsft_under_reset),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_iso_85(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_HOME,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_iso_85(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_iso_85(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_APP,  KC_INS,   KC_DEL,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_HOME,
        LSFT_T(KC_PAST),  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,   TD(TD_RSFT_UNDER),  KC_UP,    KC_END,
        TD(TD_LCTL_LPRN),  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),TD(TD_RCTL_RPRN),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_iso_85(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            MS_WHLU,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      MS_WHLD,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            MS_BTN1,  MS_UP,  MS_BTN2,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  MS_LEFT,  MS_DOWN,  MS_RGHT)
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    
    return true;
}
