// -----------------------------------------------------------
// 
// keyboard.
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#include "../include/suika/keyboard.h"
#include "d3d/dinput.hpp"

namespace suika {
	namespace keyboard {
#pragma region key_define
		detail::key Key1;

		detail::key Key2;

		detail::key Key3;

		detail::key Key4;

		detail::key Key5;

		detail::key Key6;

		detail::key Key7;

		detail::key Key8;

		detail::key Key9;

		detail::key Key0;


		detail::key Numlock;

		detail::key Num1;

		detail::key Num2;

		detail::key Num3;

		detail::key Num4;

		detail::key Num5;

		detail::key Num6;

		detail::key Num7;

		detail::key Num8;

		detail::key Num9;

		detail::key Num0;

		detail::key NumAsterisk;

		detail::key NumPlus;

		detail::key NumMinus;

		detail::key NumPeriod;

		detail::key NumSlash;

		detail::key NumEnter;


		detail::key Minus;

		detail::key Yen;

		detail::key Caret;

		detail::key Period;

		detail::key Slash;

		detail::key LAlt;

		detail::key RAlt;

		detail::key ScrollLock;

		detail::key Semicolon;

		detail::key Colon;

		detail::key LBracket;

		detail::key RBracket;

		detail::key At;

		detail::key Backslash;

		detail::key Comma;

		detail::key Kanji;

		detail::key Convert;

		detail::key NoConvert;

		detail::key Kana;

		detail::key Menu;

		detail::key Capaslock;

		detail::key Printscreen;

		detail::key PauseBreak;

		detail::key LWindows;

		detail::key RWindows;


		detail::key Tab;

		detail::key Back;

		detail::key Return;

		detail::key LShift;

		detail::key RShift;

		detail::key LControl;

		detail::key RControl;

		detail::key Escape;

		detail::key Space;

		detail::key PageUp;

		detail::key PageDown;

		detail::key End;

		detail::key Home;

		detail::key Left;

		detail::key Up;

		detail::key Right;

		detail::key Down;

		detail::key Insert;

		detail::key Delete;


		detail::key F1;

		detail::key F2;

		detail::key F3;

		detail::key F4;

		detail::key F5;

		detail::key F6;

		detail::key F7;

		detail::key F8;

		detail::key F9;

		detail::key F10;

		detail::key F11;

		detail::key F12;


		detail::key A;

		detail::key B;

		detail::key C;

		detail::key D;

		detail::key E;

		detail::key F;

		detail::key G;

		detail::key H;

		detail::key I;

		detail::key J;

		detail::key K;

		detail::key L;

		detail::key M;

		detail::key N;

		detail::key O;

		detail::key P;

		detail::key Q;

		detail::key R;

		detail::key S;

		detail::key T;

		detail::key U;

		detail::key V;

		detail::key W;

		detail::key X;

		detail::key Y;

		detail::key Z;
#pragma endregion
		void init() {
			A =		detail::key(DIK_A, "A");
			B =		detail::key(DIK_B, "B");
			C =		detail::key(DIK_C, "C");
			D =		detail::key(DIK_D, "D");
			E =		detail::key(DIK_E, "E");
			F =		detail::key(DIK_F, "F");
			G =		detail::key(DIK_G, "G");
			H =		detail::key(DIK_H, "H");
			I =		detail::key(DIK_I, "I");
			J =		detail::key(DIK_J, "J");
			K =		detail::key(DIK_K, "K");
			L =		detail::key(DIK_L, "L");
			N =		detail::key(DIK_N, "N");
			M =		detail::key(DIK_M, "M");
			O =		detail::key(DIK_O, "O");
			P =		detail::key(DIK_P, "P");
			Q =		detail::key(DIK_Q, "Q");
			R =		detail::key(DIK_R, "R");
			S =		detail::key(DIK_S, "S");
			T =		detail::key(DIK_T, "T");
			U =		detail::key(DIK_U, "U");
			V =		detail::key(DIK_V, "V");
			W =		detail::key(DIK_W, "W");
			X =		detail::key(DIK_X, "X");
			Y =		detail::key(DIK_Y, "Y");
			Z =		detail::key(DIK_Z, "Z");
			Key1 =	detail::key(DIK_1, "1");
			Key2 =	detail::key(DIK_2, "2");
			Key3 =	detail::key(DIK_3, "3");
			Key4 =	detail::key(DIK_4, "4");
			Key5 =	detail::key(DIK_5, "5");
			Key6 =	detail::key(DIK_6, "6");
			Key7 =	detail::key(DIK_7, "7");
			Key8 =	detail::key(DIK_8, "8");
			Key9 =	detail::key(DIK_9, "9");
			Key0 =	detail::key(DIK_0, "0");
			F1 =	detail::key(DIK_F1, "F1");
			F2 =	detail::key(DIK_F2, "F2");
			F3 =	detail::key(DIK_F3, "F3");
			F4 =	detail::key(DIK_F4, "F4");
			F5 =	detail::key(DIK_F5, "F5");
			F6 =	detail::key(DIK_F6, "F6");
			F7 =	detail::key(DIK_F7, "F7");
			F8 =	detail::key(DIK_F8, "F8");
			F9 =	detail::key(DIK_F9, "F9");
			F10 =	detail::key(DIK_F10, "F10");
			F11 =	detail::key(DIK_F11, "F11");
			F12 =	detail::key(DIK_F12, "F12");
			Numlock = detail::key(DIK_NUMLOCK, "NumLock");
			Num1 =	detail::key(DIK_NUMPAD1, "Num1");
			Num2 =	detail::key(DIK_NUMPAD2, "Num2");
			Num3 =	detail::key(DIK_NUMPAD3, "Num3");
			Num4 =	detail::key(DIK_NUMPAD4, "Num4");
			Num5 =	detail::key(DIK_NUMPAD5, "Num5");
			Num6 =	detail::key(DIK_NUMPAD6, "Num6");
			Num7 =	detail::key(DIK_NUMPAD7, "Num7");
			Num8 =	detail::key(DIK_NUMPAD8, "Num8");
			Num9 =	detail::key(DIK_NUMPAD9, "Num9");
			Num0 =	detail::key(DIK_NUMPAD0, "Num0");
			NumAsterisk = detail::key(DIK_MULTIPLY, "Num*");
			NumPlus = detail::key(DIK_ADD, "Num+");
			NumMinus = detail::key(DIK_SUBTRACT, "Num-");
			NumPeriod = detail::key(DIK_DECIMAL, "Num.");
			NumSlash = detail::key(DIK_DIVIDE, "Num/");
			NumEnter = detail::key(DIK_NUMPADENTER, "NumEnter");
			Minus = detail::key(DIK_MINUS, "-");
			Yen = detail::key(DIK_YEN, "Åè");
			Caret = detail::key(DIK_PREVTRACK, "^");
			Period = detail::key(DIK_PERIOD, ".");
			Slash = detail::key(DIK_SLASH, "/");
			LAlt = detail::key(DIK_LALT, "Left Alt");
			RAlt = detail::key(DIK_RALT, "Right Alt");
			ScrollLock = detail::key(DIK_SCROLL, "ScrollLock");
			Semicolon = detail::key(DIK_SEMICOLON, ";");
			Colon = detail::key(DIK_COLON, ":");
			LBracket = detail::key(DIK_LBRACKET, "[");
			RBracket = detail::key(DIK_RBRACKET, "]");
			At = detail::key(DIK_AT, "@");
			Backslash = detail::key(DIK_BACKSLASH, "Å_");
			Comma = detail::key(DIK_COMMA, ",");
			Kanji = detail::key(DIK_KANJI, "Kanji");
			Convert = detail::key(DIK_CONVERT, "Convert");
			NoConvert = detail::key(DIK_NOCONVERT, "NoConvert");
			Kana = detail::key(DIK_KANA, "Kana");
			Menu = detail::key(DIK_APPS, "Menu");
			Capaslock = detail::key(DIK_CAPSLOCK, "CapsLock");
			Printscreen = detail::key(DIK_SYSRQ, "PrintScreen");
			PauseBreak = detail::key(DIK_PAUSE, "Pause/Break");
			LWindows = detail::key(DIK_LWIN, "Left Windows");
			RWindows = detail::key(DIK_RWIN, "Right Windows");
			Tab = detail::key(DIK_TAB, "Tab");
			Back = detail::key(DIK_BACK, "Back");
			Return = detail::key(DIK_RETURN, "Enter");
			LShift = detail::key(DIK_LSHIFT, "Left Shift");
			RShift = detail::key(DIK_RSHIFT, "Right Shift");
			LControl = detail::key(DIK_LCONTROL, "Left Controll");
			RControl = detail::key(DIK_RCONTROL, "Right Controll");
			Escape = detail::key(DIK_ESCAPE, "Escape");
			Space = detail::key(DIK_SPACE, "Space");
			PageUp = detail::key(DIK_PGUP, "PageUp");
			PageDown = detail::key(DIK_PGDN, "PageDown");
			End = detail::key(DIK_END, "End");
			Home = detail::key(DIK_HOME, "Home");
			Left = detail::key(DIK_LEFT, "Left");
			Up = detail::key(DIK_UP, "Up");
			Right = detail::key(DIK_RIGHT, "Right");
			Down = detail::key(DIK_DOWN, "Down");
			Insert = detail::key(DIK_INSERT, "Insert");
			Delete = detail::key(DIK_DELETE, "Delete");
		}

		std::vector<std::reference_wrapper<detail::key>> pushed_key;

		void update() {
			pushed_key.clear();
			pushed_key.reserve(109);

			A.update();
			B.update();
			C.update();
			D.update();
			E.update();
			F.update();
			G.update();
			H.update();
			I.update();
			J.update();
			K.update();
			L.update();
			N.update();
			M.update();
			O.update();
			P.update();
			Q.update();
			R.update();
			S.update();
			T.update();
			U.update();
			V.update();
			W.update();
			X.update();
			Y.update();
			Z.update();
			Key1.update();
			Key2.update();
			Key3.update();
			Key4.update();
			Key5.update();
			Key6.update();
			Key7.update();
			Key8.update();
			Key9.update();
			Key0.update();
			F1.update();
			F2.update();
			F3.update();
			F4.update();
			F5.update();
			F6.update();
			F7.update();
			F8.update();
			F9.update();
			F10.update();
			F11.update();
			F12.update();
			Numlock.update();
			Num1.update();
			Num2.update();
			Num3.update();
			Num4.update();
			Num5.update();
			Num6.update();
			Num7.update();
			Num8.update();
			Num9.update();
			Num0.update();
			NumAsterisk.update();
			NumPlus.update();
			NumMinus.update();
			NumPeriod.update();
			NumSlash.update();
			NumEnter.update();

			Minus.update();
			Yen.update();
			Caret.update();
			Period.update();
			Slash.update();
			LAlt.update();
			RAlt.update();
			ScrollLock.update();
			Semicolon.update();
			Colon.update();
			LBracket.update();
			RBracket.update();
			At.update();
			Backslash.update();
			Comma.update();
			Kanji.update();
			Convert.update();
			NoConvert.update();
			Kana.update();
			Menu.update();
			Capaslock.update();
			Printscreen.update();
			PauseBreak.update();
			LWindows.update();
			RWindows.update();

			Tab.update();
			Back.update();
			Return.update();
			LShift.update();
			RShift.update();
			LControl.update();
			RControl.update();
			Escape.update();
			Space.update();
			PageUp.update();
			PageDown.update();
			End.update();
			Home.update();
			Left.update();
			Up.update();
			Right.update();
			Down.update();
			Insert.update();
			Delete.update();

			pushed_key.shrink_to_fit();
		}

		std::vector<std::reference_wrapper<detail::key>> pressed_key() {
			return pushed_key;
		}
	}

	namespace detail {
		key::key(unsigned int code, string name) {
			_code = code;
			_device_name = name;
			_press_count = 0;
			_state = input_state::release;
		}

		void key::update() {
			auto tmp = _press_count;

			if (d3d::dinput::key[_code] & 0x80) {
				_press_count++;
				_state = _press_count > 1 ? input_state::press : input_state::down;
				keyboard::pushed_key.emplace_back(*this);
			}
			else {
				if (tmp > 0) {
					_state = input_state::up;
				}
				else {
					_state = input_state::release;
				}
				_press_count = 0;
			}
		}
	}
}