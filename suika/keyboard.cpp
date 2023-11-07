#include "../include/suika/keyboard.h"
#include "d3d/dinput.hpp"

namespace suika {
	namespace keyboard {
#pragma region key_define
		detail::_key Key1;

		detail::_key Key2;

		detail::_key Key3;

		detail::_key Key4;

		detail::_key Key5;

		detail::_key Key6;

		detail::_key Key7;

		detail::_key Key8;

		detail::_key Key9;

		detail::_key Key0;


		detail::_key Numlock;

		detail::_key Num1;

		detail::_key Num2;

		detail::_key Num3;

		detail::_key Num4;

		detail::_key Num5;

		detail::_key Num6;

		detail::_key Num7;

		detail::_key Num8;

		detail::_key Num9;

		detail::_key Num0;

		detail::_key NumAsterisk;

		detail::_key NumPlus;

		detail::_key NumMinus;

		detail::_key NumPeriod;

		detail::_key NumSlash;

		detail::_key NumEnter;


		detail::_key Minus;

		detail::_key Yen;

		detail::_key Caret;

		detail::_key Period;

		detail::_key Slash;

		detail::_key LAlt;

		detail::_key RAlt;

		detail::_key ScrollLock;

		detail::_key Semicolon;

		detail::_key Colon;

		detail::_key LBracket;

		detail::_key RBracket;

		detail::_key At;

		detail::_key Backslash;

		detail::_key Comma;

		detail::_key Kanji;

		detail::_key Convert;

		detail::_key NoConvert;

		detail::_key Kana;

		detail::_key Menu;

		detail::_key Capaslock;

		detail::_key Printscreen;

		detail::_key PauseBreak;

		detail::_key LWindows;

		detail::_key RWindows;


		detail::_key Tab;

		detail::_key Back;

		detail::_key Return;

		detail::_key LShift;

		detail::_key RShift;

		detail::_key LControl;

		detail::_key RControl;

		detail::_key Escape;

		detail::_key Space;

		detail::_key PageUp;

		detail::_key PageDown;

		detail::_key End;

		detail::_key Home;

		detail::_key Left;

		detail::_key Up;

		detail::_key Right;

		detail::_key Down;

		detail::_key Insert;

		detail::_key Delete;


		detail::_key F1;

		detail::_key F2;

		detail::_key F3;

		detail::_key F4;

		detail::_key F5;

		detail::_key F6;

		detail::_key F7;

		detail::_key F8;

		detail::_key F9;

		detail::_key F10;

		detail::_key F11;

		detail::_key F12;


		detail::_key A;

		detail::_key B;

		detail::_key C;

		detail::_key D;

		detail::_key E;

		detail::_key F;

		detail::_key G;

		detail::_key H;

		detail::_key I;

		detail::_key J;

		detail::_key K;

		detail::_key L;

		detail::_key M;

		detail::_key N;

		detail::_key O;

		detail::_key P;

		detail::_key Q;

		detail::_key R;

		detail::_key S;

		detail::_key T;

		detail::_key U;

		detail::_key V;

		detail::_key W;

		detail::_key X;

		detail::_key Y;

		detail::_key Z;
#pragma endregion
		void init() {
			A =		detail::_key(DIK_A, "A");
			B =		detail::_key(DIK_B, "B");
			C =		detail::_key(DIK_C, "C");
			D =		detail::_key(DIK_D, "D");
			E =		detail::_key(DIK_E, "E");
			F =		detail::_key(DIK_F, "F");
			G =		detail::_key(DIK_G, "G");
			H =		detail::_key(DIK_H, "H");
			I =		detail::_key(DIK_I, "I");
			J =		detail::_key(DIK_J, "J");
			K =		detail::_key(DIK_K, "K");
			L =		detail::_key(DIK_L, "L");
			N =		detail::_key(DIK_N, "N");
			M =		detail::_key(DIK_M, "M");
			O =		detail::_key(DIK_O, "O");
			P =		detail::_key(DIK_P, "P");
			Q =		detail::_key(DIK_Q, "Q");
			R =		detail::_key(DIK_R, "R");
			S =		detail::_key(DIK_S, "S");
			T =		detail::_key(DIK_T, "T");
			U =		detail::_key(DIK_U, "U");
			V =		detail::_key(DIK_V, "V");
			W =		detail::_key(DIK_W, "W");
			X =		detail::_key(DIK_X, "X");
			Y =		detail::_key(DIK_Y, "Y");
			Z =		detail::_key(DIK_Z, "Z");
			Key1 =	detail::_key(DIK_1, "1");
			Key2 =	detail::_key(DIK_2, "2");
			Key3 =	detail::_key(DIK_3, "3");
			Key4 =	detail::_key(DIK_4, "4");
			Key5 =	detail::_key(DIK_5, "5");
			Key6 =	detail::_key(DIK_6, "6");
			Key7 =	detail::_key(DIK_7, "7");
			Key8 =	detail::_key(DIK_8, "8");
			Key9 =	detail::_key(DIK_9, "9");
			Key0 =	detail::_key(DIK_0, "0");
			F1 =	detail::_key(DIK_F1, "F1");
			F2 =	detail::_key(DIK_F2, "F2");
			F3 =	detail::_key(DIK_F3, "F3");
			F4 =	detail::_key(DIK_F4, "F4");
			F5 =	detail::_key(DIK_F5, "F5");
			F6 =	detail::_key(DIK_F6, "F6");
			F7 =	detail::_key(DIK_F7, "F7");
			F8 =	detail::_key(DIK_F8, "F8");
			F9 =	detail::_key(DIK_F9, "F9");
			F10 =	detail::_key(DIK_F10, "F10");
			F11 =	detail::_key(DIK_F11, "F11");
			F12 =	detail::_key(DIK_F12, "F12");
			Numlock = detail::_key(DIK_NUMLOCK, "NumLock");
			Num1 =	detail::_key(DIK_NUMPAD1, "Num1");
			Num2 =	detail::_key(DIK_NUMPAD2, "Num2");
			Num3 =	detail::_key(DIK_NUMPAD3, "Num3");
			Num4 =	detail::_key(DIK_NUMPAD4, "Num4");
			Num5 =	detail::_key(DIK_NUMPAD5, "Num5");
			Num6 =	detail::_key(DIK_NUMPAD6, "Num6");
			Num7 =	detail::_key(DIK_NUMPAD7, "Num7");
			Num8 =	detail::_key(DIK_NUMPAD8, "Num8");
			Num9 =	detail::_key(DIK_NUMPAD9, "Num9");
			Num0 =	detail::_key(DIK_NUMPAD0, "Num0");
			NumAsterisk = detail::_key(DIK_MULTIPLY, "Num*");
			NumPlus = detail::_key(DIK_ADD, "Num+");
			NumMinus = detail::_key(DIK_SUBTRACT, "Num-");
			NumPeriod = detail::_key(DIK_DECIMAL, "Num.");
			NumSlash = detail::_key(DIK_DIVIDE, "Num/");
			NumEnter = detail::_key(DIK_NUMPADENTER, "NumEnter");
			Minus = detail::_key(DIK_MINUS, "-");
			Yen = detail::_key(DIK_YEN, "");
			Caret = detail::_key(DIK_PREVTRACK, "^");
			Period = detail::_key(DIK_PERIOD, ".");
			Slash = detail::_key(DIK_SLASH, "/");
			LAlt = detail::_key(DIK_LALT, "Left Alt");
			RAlt = detail::_key(DIK_RALT, "Right Alt");
			ScrollLock = detail::_key(DIK_SCROLL, "ScrollLock");
			Semicolon = detail::_key(DIK_SEMICOLON, ";");
			Colon = detail::_key(DIK_COLON, ":");
			LBracket = detail::_key(DIK_LBRACKET, "[");
			RBracket = detail::_key(DIK_RBRACKET, "]");
			At = detail::_key(DIK_AT, "@");
			Backslash = detail::_key(DIK_BACKSLASH, "_");
			Comma = detail::_key(DIK_COMMA, ",");
			Kanji = detail::_key(DIK_KANJI, "Kanji");
			Convert = detail::_key(DIK_CONVERT, "Convert");
			NoConvert = detail::_key(DIK_NOCONVERT, "NoConvert");
			Kana = detail::_key(DIK_KANA, "Kana");
			Menu = detail::_key(DIK_APPS, "Menu");
			Capaslock = detail::_key(DIK_CAPSLOCK, "CapsLock");
			Printscreen = detail::_key(DIK_SYSRQ, "PrintScreen");
			PauseBreak = detail::_key(DIK_PAUSE, "Pause/Break");
			LWindows = detail::_key(DIK_LWIN, "Left Windows");
			RWindows = detail::_key(DIK_RWIN, "Right Windows");
			Tab = detail::_key(DIK_TAB, "Tab");
			Back = detail::_key(DIK_BACK, "Back");
			Return = detail::_key(DIK_RETURN, "Enter");
			LShift = detail::_key(DIK_LSHIFT, "Left Shift");
			RShift = detail::_key(DIK_RSHIFT, "Right Shift");
			LControl = detail::_key(DIK_LCONTROL, "Left Controll");
			RControl = detail::_key(DIK_RCONTROL, "Right Controll");
			Escape = detail::_key(DIK_ESCAPE, "Escape");
			Space = detail::_key(DIK_SPACE, "Space");
			PageUp = detail::_key(DIK_PGUP, "PageUp");
			PageDown = detail::_key(DIK_PGDN, "PageDown");
			End = detail::_key(DIK_END, "End");
			Home = detail::_key(DIK_HOME, "Home");
			Left = detail::_key(DIK_LEFT, "Left");
			Up = detail::_key(DIK_UP, "Up");
			Right = detail::_key(DIK_RIGHT, "Right");
			Down = detail::_key(DIK_DOWN, "Down");
			Insert = detail::_key(DIK_INSERT, "Insert");
			Delete = detail::_key(DIK_DELETE, "Delete");
		}

		std::vector<std::reference_wrapper<detail::_key>> pushed_key;

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

		std::vector<std::reference_wrapper<detail::_key>> pressed_key() {
			return pushed_key;
		}
	}

	namespace detail {
		_key::_key(unsigned int code, string name) {
			_code = code;
			_device_name = name;
			_press_count = 0;
			_state = input_state::release;
		}
		void _key::update() {
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