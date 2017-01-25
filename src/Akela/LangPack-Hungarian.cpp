/* -*- mode: c++ -*-
 * Akela -- Animated Keyboardio Extension Library for Anything
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

#include <Akela-LangPack-Hungarian.h>
#include <Akela-OneShot.h>

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

namespace Akela {
  namespace LangPack {

    Key
    Hungarian_::eventHandlerHook (Key mappedKey, byte row, byte col, uint8_t keyState) {
      if (mappedKey.raw < HUNGARIAN_FIRST || mappedKey.raw > HUNGARIAN_LAST)
        return mappedKey;

      if (!key_toggled_on (keyState))
        return Key_NoKey;

      bool needShift = Keyboard.isModifierActive (Key_LShift.keyCode) ||
        ::OneShot.isModifierActive (Key_LShift);

      Keyboard.press (Key_RAlt.keyCode);
      Keyboard.sendReport ();
      delay (10);
      Keyboard.release (Key_RAlt.keyCode);
      Keyboard.sendReport ();
      delay (10);

      HungarianSymbol symbol = (HungarianSymbol) (mappedKey.raw - HUNGARIAN_FIRST);
      Key accent;
      uint8_t kc = 0;

      accent.flags = KEY_FLAGS;

      switch (symbol) {
      case AA:
        kc = Key_A.keyCode;
        accent.raw = Key_Quote.raw;
        break;
      case OA:
        kc = Key_O.keyCode;
        accent.raw = Key_Quote.raw;
        break;
      case OU:
        kc = Key_O.keyCode;
        accent.raw = Key_Quote.raw;
        accent.flags |= SHIFT_HELD;
        break;
      case ODA:
        kc = Key_O.keyCode;
        accent.raw = Key_Equals.raw;
        break;
      case EA:
        kc = Key_E.keyCode;
        accent.raw = Key_Quote.raw;
        break;
      case UA:
        kc = Key_U.keyCode;
        accent.raw = Key_Quote.raw;
        break;
      case UU:
        kc = Key_U.keyCode;
        accent.raw = Key_Quote.raw;
        accent.flags |= SHIFT_HELD;
        break;
      case UDA:
        kc = Key_U.keyCode;
        accent.raw = Key_Equals.raw;
        break;
      case IA:
        kc = Key_I.keyCode;
        accent.raw = Key_Quote.raw;
        break;
      }

      if (accent.flags & SHIFT_HELD)
        Keyboard.press (Key_LShift.keyCode);
      else
        Keyboard.release (Key_LShift.keyCode);
      Keyboard.sendReport ();
      delay(10);

      Keyboard.press (accent.keyCode);
      Keyboard.sendReport ();
      Keyboard.release (accent.keyCode);
      Keyboard.sendReport ();

      if (needShift)
        Keyboard.press (Key_LShift.keyCode);
      else
        Keyboard.release (Key_LShift.keyCode);

      delay (10);
      Keyboard.press (kc);
      Keyboard.sendReport ();
      delay(10);
      Keyboard.release (kc);
      Keyboard.sendReport ();
      delay (10);

      return Key_NoKey;
    }

    Hungarian_::Hungarian_ (void) {
    }

    void
    Hungarian_::begin (void) {
      event_handler_hook_add (eventHandlerHook);
    }
  }
}

Akela::LangPack::Hungarian_ Hungarian;
