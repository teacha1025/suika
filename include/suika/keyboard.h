#pragma once
#include "input_base.h"

namespace suika {
	namespace detail {
		class _key : public input_base {
		public:
			_key(unsigned int code, string name);
			_key() {}
			void update();
		};
	}
	/// <summary>
	/// キー入力の定義及び関数
	/// </summary>
	namespace keyboard {
		/// <summary>
		/// 1キー
		/// </summary>
		extern detail::_key Key1;

		/// <summary>
		/// 2キー
		/// </summary>
		extern detail::_key Key2;

		/// <summary>
		/// 3キー
		/// </summary>
		extern detail::_key Key3;

		/// <summary>
		/// 4キー
		/// </summary>
		extern detail::_key Key4;

		/// <summary>
		/// 5キー
		/// </summary>
		extern detail::_key Key5;

		/// <summary>
		/// 6キー
		/// </summary>
		extern detail::_key Key6;

		/// <summary>
		/// 7キー
		/// </summary>
		extern detail::_key Key7;

		/// <summary>
		/// 8キー
		/// </summary>
		extern detail::_key Key8;

		/// <summary>
		/// 9キー
		/// </summary>
		extern detail::_key Key9;

		/// <summary>
		/// 0キー
		/// </summary>
		extern detail::_key Key0;



		/// <summary>
		/// NumLockキー
		/// </summary>
		extern detail::_key Numlock;

		/// <summary>
		/// テンキー1キー
		/// </summary>
		extern detail::_key Num1;

		/// <summary>
		/// テンキー2キー
		/// </summary>
		extern detail::_key Num2;

		/// <summary>
		/// テンキー3キー
		/// </summary>
		extern detail::_key Num3;

		/// <summary>
		/// テンキー4キー
		/// </summary>
		extern detail::_key Num4;

		/// <summary>
		/// テンキー5キー
		/// </summary>
		extern detail::_key Num5;

		/// <summary>
		/// テンキー6キー
		/// </summary>
		extern detail::_key Num6;

		/// <summary>
		/// テンキー7キー
		/// </summary>
		extern detail::_key Num7;

		/// <summary>
		/// テンキー8キー
		/// </summary>
		extern detail::_key Num8;

		/// <summary>
		/// テンキー9キー
		/// </summary>
		extern detail::_key Num9;

		/// <summary>
		/// テンキー0キー
		/// </summary>
		extern detail::_key Num0;

		/// <summary>
		/// テンキー*キー
		/// </summary>
		extern detail::_key NumAsterisk;

		/// <summary>
		/// テンキー+キー
		/// </summary>
		extern detail::_key NumPlus;

		/// <summary>
		/// テンキー-キー
		/// </summary>
		extern detail::_key NumMinus;

		/// <summary>
		/// テンキー.キー
		/// </summary>
		extern detail::_key NumPeriod;

		/// <summary>
		/// テンキー/キー
		/// </summary>
		extern detail::_key NumSlash;

		/// <summary>
		/// テンキーのエンターキー
		/// </summary>
		extern detail::_key NumEnter;



		/// <summary>
		/// -キー
		/// </summary>
		extern detail::_key Minus;

		/// <summary>
		/// \キー
		/// </summary>
		extern detail::_key Yen;

		/// <summary>
		/// ^キー
		/// </summary>
		extern detail::_key Caret;
		/// <summary>
		/// .キー
		/// </summary>
		extern detail::_key Period;

		/// <summary>
		/// ／キー
		/// </summary>
		extern detail::_key Slash;

		/// <summary>
		/// 左Altキー
		/// </summary>
		extern detail::_key LAlt;

		/// <summary>
		/// 右Altキー
		/// </summary>
		extern detail::_key RAlt;

		/// <summary>
		/// ScrollLockキー
		/// </summary>
		extern detail::_key ScrollLock;

		/// <summary>
		/// ;キー
		/// </summary>
		extern detail::_key Semicolon;

		/// <summary>
		/// :キー
		/// </summary>
		extern detail::_key Colon;

		/// <summary>
		/// [キー
		/// </summary>
		extern detail::_key LBracket;

		/// <summary>
		/// ]キー
		/// </summary>
		extern detail::_key RBracket;

		/// <summary>
		/// @キー
		/// </summary>
		extern detail::_key At;

		/// <summary>
		/// ＼キー
		/// </summary>
		extern detail::_key Backslash;

		/// <summary>
		/// ,キー
		/// </summary>
		extern detail::_key Comma;

		/// <summary>
		/// 漢字キー
		/// </summary>
		extern detail::_key Kanji;

		/// <summary>
		/// 変換キー
		/// </summary>
		extern detail::_key Convert;

		/// <summary>
		/// 無変換キー
		/// </summary>
		extern detail::_key NoConvert;

		/// <summary>
		/// かなキー
		/// </summary>
		extern detail::_key Kana;

		/// <summary>
		/// アプリケーションメニューキー
		/// </summary>
		extern detail::_key Menu;

		/// <summary>
		/// CapsLockキー
		/// </summary>
		extern detail::_key Capaslock;

		/// <summary>
		/// PrintScreenキー
		/// </summary>
		extern detail::_key Printscreen;

		/// <summary>
		/// PauseBreakキー
		/// </summary>
		extern detail::_key PauseBreak;

		/// <summary>
		/// 左Windowsキー
		/// </summary>
		extern detail::_key LWindows;

		/// <summary>
		/// 右Windowsキー
		/// </summary>
		extern detail::_key RWindows;



		/// <summary>
		/// タブキー
		/// </summary>
		extern detail::_key Tab;

		/// <summary>
		/// バックスペースキー
		/// </summary>
		extern detail::_key Back;

		/// <summary>
		/// エンターキー
		/// </summary>
		extern detail::_key Return;

		/// <summary>
		/// 左シフトキー
		/// </summary>
		extern detail::_key LShift;

		/// <summary>
		/// 右シフトキー
		/// </summary>
		extern detail::_key RShift;

		/// <summary>
		/// 左コントロールキー
		/// </summary>
		extern detail::_key LControl;

		/// <summary>
		/// 右コントロールキー
		/// </summary>
		extern detail::_key RControl;

		/// <summary>
		/// エスケープキー
		/// </summary>
		extern detail::_key Escape;

		/// <summary>
		/// スペースキー
		/// </summary>
		extern detail::_key Space;

		/// <summary>
		/// PageUpキー
		/// </summary>
		extern detail::_key PageUp;

		/// <summary>
		///ぱげDown キー
		/// </summary>
		extern detail::_key PageDown;

		/// <summary>
		/// Endキー
		/// </summary>
		extern detail::_key End;

		/// <summary>
		/// Homeキー
		/// </summary>
		extern detail::_key Home;

		/// <summary>
		/// ←キー
		/// </summary>
		extern detail::_key Left;

		/// <summary>
		/// ↑キー
		/// </summary>
		extern detail::_key Up;

		/// <summary>
		/// →キー
		/// </summary>
		extern detail::_key Right;

		/// <summary>
		/// ↓キー
		/// </summary>
		extern detail::_key Down;

		/// <summary>
		/// Insertキー
		/// </summary>
		extern detail::_key Insert;

		/// <summary>
		/// Deleteキー
		/// </summary>
		extern detail::_key Delete;



		/// <summary>
		/// F1キー
		/// </summary>
		extern detail::_key F1;

		/// <summary>
		/// F2キー
		/// </summary>
		extern detail::_key F2;

		/// <summary>
		/// F3キー
		/// </summary>
		extern detail::_key F3;

		/// <summary>
		/// F4キー
		/// </summary>
		extern detail::_key F4;

		/// <summary>
		/// F5キー
		/// </summary>
		extern detail::_key F5;

		/// <summary>
		/// F6キー
		/// </summary>
		extern detail::_key F6;

		/// <summary>
		/// F7キー
		/// </summary>
		extern detail::_key F7;

		/// <summary>
		/// F8キー
		/// </summary>
		extern detail::_key F8;

		/// <summary>
		/// F9キー
		/// </summary>
		extern detail::_key F9;

		/// <summary>
		/// !0キー
		/// </summary>
		extern detail::_key F10;

		/// <summary>
		/// F11キー
		/// </summary>
		extern detail::_key F11;

		/// <summary>
		/// F12キー
		/// </summary>
		extern detail::_key F12;



		/// <summary>
		/// Aキー
		/// </summary>
		extern detail::_key A;

		/// <summary>
		/// Bキー
		/// </summary>
		extern detail::_key B;

		/// <summary>
		/// Cキー
		/// </summary>
		extern detail::_key C;

		/// <summary>
		/// Dキー
		/// </summary>
		extern detail::_key D;

		/// <summary>
		/// Eキー
		/// </summary>
		extern detail::_key E;

		/// <summary>
		/// Fキー
		/// </summary>
		extern detail::_key F;

		/// <summary>
		/// Gキー
		/// </summary>
		extern detail::_key G;

		/// <summary>
		/// Hキー
		/// </summary>
		extern detail::_key H;

		/// <summary>
		/// Iキー
		/// </summary>
		extern detail::_key I;

		/// <summary>
		/// Jキー
		/// </summary>
		extern detail::_key J;

		/// <summary>
		/// Kキー
		/// </summary>
		extern detail::_key K;

		/// <summary>
		/// Lキー
		/// </summary>
		extern detail::_key L;

		/// <summary>
		/// Mキー
		/// </summary>
		extern detail::_key M;

		/// <summary>
		/// Nキー
		/// </summary>
		extern detail::_key N;

		/// <summary>
		/// Oキー
		/// </summary>
		extern detail::_key O;

		/// <summary>
		/// Pキー
		/// </summary>
		extern detail::_key P;

		/// <summary>
		/// Qキー
		/// </summary>
		extern detail::_key Q;

		/// <summary>
		/// Rキー
		/// </summary>
		extern detail::_key R;

		/// <summary>
		/// Sキー
		/// </summary>
		extern detail::_key S;

		/// <summary>
		/// Tキー
		/// </summary>
		extern detail::_key T;

		/// <summary>
		/// Uキー
		/// </summary>
		extern detail::_key U;

		/// <summary>
		/// Vキー
		/// </summary>
		extern detail::_key V;

		/// <summary>
		/// Wキー
		/// </summary>
		extern detail::_key W;

		/// <summary>
		/// Xキー
		/// </summary>
		extern detail::_key X;

		/// <summary>
		/// Yキー
		/// </summary>
		extern detail::_key Y;

		/// <summary>
		/// Zキー
		/// </summary>
		extern detail::_key Z;

		/// <summary>
		/// 押されたキーをすべて取得
		/// </summary>
		/// <returns>現在押されているキーの配列</returns>
		std::vector<std::reference_wrapper<detail::_key>> pressed_key();
	}; // namespace keyboard
}