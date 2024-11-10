#include QMK_KEYBOARD_H

enum custom {
  LS_LEFT = SAFE_RANGE,
  LS_RIGHT,
  LS_DOWN,
  LS_UP,
};

joystick_config_t joystick_axes[2] = {
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, /**/ KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
    MO(1), KC_Q, KC_W, KC_E, KC_R, KC_T, /**/ KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
    LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, /**/ KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, /**/ KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
    KC_LGUI, KC_LALT, KC_SPC, /**/ KC_TAB, KC_MINS, KC_EQL
  ),
  [1] = LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, /**/ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_DEL,
    KC_TRNS, KC_F11, KC_F12, KC_BTN1, KC_BTN3, KC_BTN2, /**/ KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS, TO(2),
    KC_TRNS, RGB_TOG, MEH(KC_U), KC_MPRV, KC_MPLY, KC_MNXT, /**/ KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_APP, KC_RCTL,
    KC_TRNS, LCTL(KC_PSCR), KC_PSCR, KC_MSTP, KC_F20, KC_MUTE, KC_VOLU, /**/ KC_BRIU, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_RALT, KC_RSFT,
    KC_TRNS, KC_TRNS, KC_VOLD, /**/ KC_BRID, RGB_RMOD, RGB_MOD
  ),
  [2] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, LS_UP, KC_NO, KC_NO, KC_NO, /**/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0),
    JS_0, LS_LEFT, LS_DOWN, LS_RIGHT, KC_NO, KC_NO, /**/ JS_1, JS_2, JS_3, JS_4, KC_NO, JS_5,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO, JS_6, JS_7, KC_NO, KC_NO, KC_NO, KC_NO,
    JS_8, JS_9, JS_10, /**/ JS_11, JS_12, KC_NO
  ),
};

static bool ls_left = false;
static bool ls_right = false;
static bool ls_up = false;
static bool ls_down = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LS_LEFT:
    if (record->event.pressed) {
      ls_left = true;
      joystick_set_axis(0, -127);
    } else {
      ls_left = false;
      if (ls_right) {
        joystick_set_axis(0, 127);
      } else {
        joystick_set_axis(0, 0);
      }
    }
    return false;

  case LS_RIGHT:
    if (record->event.pressed) {
      ls_right = true;
      joystick_set_axis(0, 127);
    } else {
      ls_right = false;
      if (ls_left) {
        joystick_set_axis(0, -127);
      } else {
        joystick_set_axis(0, 0);
      }
    }
    return false;

  case LS_UP:
    if (record->event.pressed) {
      ls_up = true;
      joystick_set_axis(1, -127);
    } else {
      ls_up = false;
      if (ls_down) {
        joystick_set_axis(1, 127);
      } else {
        joystick_set_axis(1, 0);
      }
    }
    return false;

  case LS_DOWN:
    if (record->event.pressed) {
      ls_down = true;
      joystick_set_axis(1, 127);
    } else {
      ls_down = false;
      if (ls_up) {
        joystick_set_axis(1, -127);
      } else {
        joystick_set_axis(1, 0);
      }
    }
    return false;

  default:
    return true;
  }
}
