#pragma once
#include "input_base.h"

namespace suika {
	namespace detail {
		class key : public input_base {
		public:
			/// <summary>
			/// キーの作成
			/// </summary>
			/// <param name="code">キーコード</param>
			/// <param name="name">キーの名前</param>
			key(unsigned int code, string name);
			/// <summary>
			/// デフォルトキー
			/// </summary>
			key() {}
			/// <summary>
			/// キーの更新
			/// </summary>
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
		extern detail::key Key1;

		/// <summary>
		/// 2キー
		/// </summary>
		extern detail::key Key2;

		/// <summary>
		/// 3キー
		/// </summary>
		extern detail::key Key3;

		/// <summary>
		/// 4キー
		/// </summary>
		extern detail::key Key4;

		/// <summary>
		/// 5キー
		/// </summary>
		extern detail::key Key5;

		/// <summary>
		/// 6キー
		/// </summary>
		extern detail::key Key6;

		/// <summary>
		/// 7キー
		/// </summary>
		extern detail::key Key7;

		/// <summary>
		/// 8キー
		/// </summary>
		extern detail::key Key8;

		/// <summary>
		/// 9キー
		/// </summary>
		extern detail::key Key9;

		/// <summary>
		/// 0キー
		/// </summary>
		extern detail::key Key0;



		/// <summary>
		/// NumLockキー
		/// </summary>
		extern detail::key Numlock;

		/// <summary>
		/// テンキー1キー
		/// </summary>
		extern detail::key Num1;

		/// <summary>
		/// テンキー2キー
		/// </summary>
		extern detail::key Num2;

		/// <summary>
		/// テンキー3キー
		/// </summary>
		extern detail::key Num3;

		/// <summary>
		/// テンキー4キー
		/// </summary>
		extern detail::key Num4;

		/// <summary>
		/// テンキー5キー
		/// </summary>
		extern detail::key Num5;

		/// <summary>
		/// テンキー6キー
		/// </summary>
		extern detail::key Num6;

		/// <summary>
		/// テンキー7キー
		/// </summary>
		extern detail::key Num7;

		/// <summary>
		/// テンキー8キー
		/// </summary>
		extern detail::key Num8;

		/// <summary>
		/// テンキー9キー
		/// </summary>
		extern detail::key Num9;

		/// <summary>
		/// テンキー0キー
		/// </summary>
		extern detail::key Num0;

		/// <summary>
		/// テンキー*キー
		/// </summary>
		extern detail::key NumAsterisk;

		/// <summary>
		/// テンキー+キー
		/// </summary>
		extern detail::key NumPlus;

		/// <summary>
		/// テンキー-キー
		/// </summary>
		extern detail::key NumMinus;

		/// <summary>
		/// テンキー.キー
		/// </summary>
		extern detail::key NumPeriod;

		/// <summary>
		/// テンキー/キー
		/// </summary>
		extern detail::key NumSlash;

		/// <summary>
		/// テンキーのエンターキー
		/// </summary>
		extern detail::key NumEnter;



		/// <summary>
		/// -キー
		/// </summary>
		extern detail::key Minus;

		/// <summary>
		/// \キー
		/// </summary>
		extern detail::key Yen;

		/// <summary>
		/// ^キー
		/// </summary>
		extern detail::key Caret;
		/// <summary>
		/// .キー
		/// </summary>
		extern detail::key Period;

		/// <summary>
		/// ／キー
		/// </summary>
		extern detail::key Slash;

		/// <summary>
		/// 左Altキー
		/// </summary>
		extern detail::key LAlt;

		/// <summary>
		/// 右Altキー
		/// </summary>
		extern detail::key RAlt;

		/// <summary>
		/// ScrollLockキー
		/// </summary>
		extern detail::key ScrollLock;

		/// <summary>
		/// ;キー
		/// </summary>
		extern detail::key Semicolon;

		/// <summary>
		/// :キー
		/// </summary>
		extern detail::key Colon;

		/// <summary>
		/// [キー
		/// </summary>
		extern detail::key LBracket;

		/// <summary>
		/// ]キー
		/// </summary>
		extern detail::key RBracket;

		/// <summary>
		/// @キー
		/// </summary>
		extern detail::key At;

		/// <summary>
		/// ＼キー
		/// </summary>
		extern detail::key Backslash;

		/// <summary>
		/// ,キー
		/// </summary>
		extern detail::key Comma;

		/// <summary>
		/// 漢字キー
		/// </summary>
		extern detail::key Kanji;

		/// <summary>
		/// 変換キー
		/// </summary>
		extern detail::key Convert;

		/// <summary>
		/// 無変換キー
		/// </summary>
		extern detail::key NoConvert;

		/// <summary>
		/// かなキー
		/// </summary>
		extern detail::key Kana;

		/// <summary>
		/// アプリケーションメニューキー
		/// </summary>
		extern detail::key Menu;

		/// <summary>
		/// CapsLockキー
		/// </summary>
		extern detail::key Capaslock;

		/// <summary>
		/// PrintScreenキー
		/// </summary>
		extern detail::key Printscreen;

		/// <summary>
		/// PauseBreakキー
		/// </summary>
		extern detail::key PauseBreak;

		/// <summary>
		/// 左Windowsキー
		/// </summary>
		extern detail::key LWindows;

		/// <summary>
		/// 右Windowsキー
		/// </summary>
		extern detail::key RWindows;



		/// <summary>
		/// タブキー
		/// </summary>
		extern detail::key Tab;

		/// <summary>
		/// バックスペースキー
		/// </summary>
		extern detail::key Back;

		/// <summary>
		/// エンターキー
		/// </summary>
		extern detail::key Return;

		/// <summary>
		/// 左シフトキー
		/// </summary>
		extern detail::key LShift;

		/// <summary>
		/// 右シフトキー
		/// </summary>
		extern detail::key RShift;

		/// <summary>
		/// 左コントロールキー
		/// </summary>
		extern detail::key LControl;

		/// <summary>
		/// 右コントロールキー
		/// </summary>
		extern detail::key RControl;

		/// <summary>
		/// エスケープキー
		/// </summary>
		extern detail::key Escape;

		/// <summary>
		/// スペースキー
		/// </summary>
		extern detail::key Space;

		/// <summary>
		/// PageUpキー
		/// </summary>
		extern detail::key PageUp;

		/// <summary>
		///ぱげDown キー
		/// </summary>
		extern detail::key PageDown;

		/// <summary>
		/// Endキー
		/// </summary>
		extern detail::key End;

		/// <summary>
		/// Homeキー
		/// </summary>
		extern detail::key Home;

		/// <summary>
		/// ←キー
		/// </summary>
		extern detail::key Left;

		/// <summary>
		/// ↑キー
		/// </summary>
		extern detail::key Up;

		/// <summary>
		/// →キー
		/// </summary>
		extern detail::key Right;

		/// <summary>
		/// ↓キー
		/// </summary>
		extern detail::key Down;

		/// <summary>
		/// Insertキー
		/// </summary>
		extern detail::key Insert;

		/// <summary>
		/// Deleteキー
		/// </summary>
		extern detail::key Delete;



		/// <summary>
		/// F1キー
		/// </summary>
		extern detail::key F1;

		/// <summary>
		/// F2キー
		/// </summary>
		extern detail::key F2;

		/// <summary>
		/// F3キー
		/// </summary>
		extern detail::key F3;

		/// <summary>
		/// F4キー
		/// </summary>
		extern detail::key F4;

		/// <summary>
		/// F5キー
		/// </summary>
		extern detail::key F5;

		/// <summary>
		/// F6キー
		/// </summary>
		extern detail::key F6;

		/// <summary>
		/// F7キー
		/// </summary>
		extern detail::key F7;

		/// <summary>
		/// F8キー
		/// </summary>
		extern detail::key F8;

		/// <summary>
		/// F9キー
		/// </summary>
		extern detail::key F9;

		/// <summary>
		/// !0キー
		/// </summary>
		extern detail::key F10;

		/// <summary>
		/// F11キー
		/// </summary>
		extern detail::key F11;

		/// <summary>
		/// F12キー
		/// </summary>
		extern detail::key F12;



		/// <summary>
		/// Aキー
		/// </summary>
		extern detail::key A;

		/// <summary>
		/// Bキー
		/// </summary>
		extern detail::key B;

		/// <summary>
		/// Cキー
		/// </summary>
		extern detail::key C;

		/// <summary>
		/// Dキー
		/// </summary>
		extern detail::key D;

		/// <summary>
		/// Eキー
		/// </summary>
		extern detail::key E;

		/// <summary>
		/// Fキー
		/// </summary>
		extern detail::key F;

		/// <summary>
		/// Gキー
		/// </summary>
		extern detail::key G;

		/// <summary>
		/// Hキー
		/// </summary>
		extern detail::key H;

		/// <summary>
		/// Iキー
		/// </summary>
		extern detail::key I;

		/// <summary>
		/// Jキー
		/// </summary>
		extern detail::key J;

		/// <summary>
		/// Kキー
		/// </summary>
		extern detail::key K;

		/// <summary>
		/// Lキー
		/// </summary>
		extern detail::key L;

		/// <summary>
		/// Mキー
		/// </summary>
		extern detail::key M;

		/// <summary>
		/// Nキー
		/// </summary>
		extern detail::key N;

		/// <summary>
		/// Oキー
		/// </summary>
		extern detail::key O;

		/// <summary>
		/// Pキー
		/// </summary>
		extern detail::key P;

		/// <summary>
		/// Qキー
		/// </summary>
		extern detail::key Q;

		/// <summary>
		/// Rキー
		/// </summary>
		extern detail::key R;

		/// <summary>
		/// Sキー
		/// </summary>
		extern detail::key S;

		/// <summary>
		/// Tキー
		/// </summary>
		extern detail::key T;

		/// <summary>
		/// Uキー
		/// </summary>
		extern detail::key U;

		/// <summary>
		/// Vキー
		/// </summary>
		extern detail::key V;

		/// <summary>
		/// Wキー
		/// </summary>
		extern detail::key W;

		/// <summary>
		/// Xキー
		/// </summary>
		extern detail::key X;

		/// <summary>
		/// Yキー
		/// </summary>
		extern detail::key Y;

		/// <summary>
		/// Zキー
		/// </summary>
		extern detail::key Z;

		/// <summary>
		/// 押されたキーをすべて取得
		/// </summary>
		/// <returns>現在押されているキーの配列</returns>
		std::vector<std::reference_wrapper<detail::key>> pressed_key();
	}; // namespace keyboard
}