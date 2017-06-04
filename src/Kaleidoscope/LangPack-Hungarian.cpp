/* -*- mode: c++ -*-
 * Kaleidoscope-LangPack-Hungarian -- Hungarian language support
 * Copyright (C) 2016, 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include <Kaleidoscope-LangPack-Hungarian.h>
#include <Kaleidoscope-OneShot.h>

typedef enum {
  AA,
  OA,
  OU,
  ODA,
  EA,
  UA,
  UU,
  UDA,
  IA,
} HungarianSymbol;

namespace KaleidoscopePlugins {
namespace LangPack {

static void tapKey(uint8_t keyCode) {
  Keyboard.press(keyCode);
  Keyboard.sendReport();
  Keyboard.release(keyCode);
  Keyboard.sendReport();
}

Key
Hungarian_::eventHandlerHook(Key mappedKey, byte row, byte col, uint8_t keyState) {
  if (mappedKey.raw < HUNGARIAN_FIRST || mappedKey.raw > HUNGARIAN_LAST)
    return mappedKey;

  if (!key_toggled_on(keyState))
    return Key_NoKey;

  bool needShift = Keyboard.isModifierActive(Key_LeftShift.keyCode) ||
                   ::OneShot.isModifierActive(Key_LeftShift);

  tapKey(Key_RightAlt.keyCode);

  HungarianSymbol symbol = (HungarianSymbol)(mappedKey.raw - HUNGARIAN_FIRST);
  Key accent;
  uint8_t kc = 0;

  accent.flags = KEY_FLAGS;
  accent.keyCode = Key_Quote.raw;

  switch (symbol) {
  case AA:
    kc = Key_A.keyCode;
    break;
  case OA:
    kc = Key_O.keyCode;
    break;
  case OU:
    kc = Key_O.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case ODA:
    kc = Key_O.keyCode;
    accent.raw = Key_Equals.raw;
    break;
  case EA:
    kc = Key_E.keyCode;
    break;
  case UA:
    kc = Key_U.keyCode;
    break;
  case UU:
    kc = Key_U.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case UDA:
    kc = Key_U.keyCode;
    accent.raw = Key_Equals.raw;
    break;
  case IA:
    kc = Key_I.keyCode;
    break;
  }

  if (accent.flags & SHIFT_HELD)
    Keyboard.press(Key_LeftShift.keyCode);
  else
    Keyboard.release(Key_LeftShift.keyCode);
  Keyboard.sendReport();

  tapKey(accent.keyCode);

  if (needShift)
    Keyboard.press(Key_LeftShift.keyCode);
  else
    Keyboard.release(Key_LeftShift.keyCode);

  tapKey(kc);

  return Key_NoKey;
}

Hungarian_::Hungarian_(void) {
}

void
Hungarian_::begin(void) {
  event_handler_hook_use(eventHandlerHook);
}
}
}

KaleidoscopePlugins::LangPack::Hungarian_ Hungarian;
