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
	/// �L�[���͂̒�`�y�ъ֐�
	/// </summary>
	namespace keyboard {
		/// <summary>
		/// 1�L�[
		/// </summary>
		extern detail::_key Key1;

		/// <summary>
		/// 2�L�[
		/// </summary>
		extern detail::_key Key2;

		/// <summary>
		/// 3�L�[
		/// </summary>
		extern detail::_key Key3;

		/// <summary>
		/// 4�L�[
		/// </summary>
		extern detail::_key Key4;

		/// <summary>
		/// 5�L�[
		/// </summary>
		extern detail::_key Key5;

		/// <summary>
		/// 6�L�[
		/// </summary>
		extern detail::_key Key6;

		/// <summary>
		/// 7�L�[
		/// </summary>
		extern detail::_key Key7;

		/// <summary>
		/// 8�L�[
		/// </summary>
		extern detail::_key Key8;

		/// <summary>
		/// 9�L�[
		/// </summary>
		extern detail::_key Key9;

		/// <summary>
		/// 0�L�[
		/// </summary>
		extern detail::_key Key0;



		/// <summary>
		/// NumLock�L�[
		/// </summary>
		extern detail::_key Numlock;

		/// <summary>
		/// �e���L�[1�L�[
		/// </summary>
		extern detail::_key Num1;

		/// <summary>
		/// �e���L�[2�L�[
		/// </summary>
		extern detail::_key Num2;

		/// <summary>
		/// �e���L�[3�L�[
		/// </summary>
		extern detail::_key Num3;

		/// <summary>
		/// �e���L�[4�L�[
		/// </summary>
		extern detail::_key Num4;

		/// <summary>
		/// �e���L�[5�L�[
		/// </summary>
		extern detail::_key Num5;

		/// <summary>
		/// �e���L�[6�L�[
		/// </summary>
		extern detail::_key Num6;

		/// <summary>
		/// �e���L�[7�L�[
		/// </summary>
		extern detail::_key Num7;

		/// <summary>
		/// �e���L�[8�L�[
		/// </summary>
		extern detail::_key Num8;

		/// <summary>
		/// �e���L�[9�L�[
		/// </summary>
		extern detail::_key Num9;

		/// <summary>
		/// �e���L�[0�L�[
		/// </summary>
		extern detail::_key Num0;

		/// <summary>
		/// �e���L�[*�L�[
		/// </summary>
		extern detail::_key NumAsterisk;

		/// <summary>
		/// �e���L�[+�L�[
		/// </summary>
		extern detail::_key NumPlus;

		/// <summary>
		/// �e���L�[-�L�[
		/// </summary>
		extern detail::_key NumMinus;

		/// <summary>
		/// �e���L�[.�L�[
		/// </summary>
		extern detail::_key NumPeriod;

		/// <summary>
		/// �e���L�[/�L�[
		/// </summary>
		extern detail::_key NumSlash;

		/// <summary>
		/// �e���L�[�̃G���^�[�L�[
		/// </summary>
		extern detail::_key NumEnter;



		/// <summary>
		/// -�L�[
		/// </summary>
		extern detail::_key Minus;

		/// <summary>
		/// \�L�[
		/// </summary>
		extern detail::_key Yen;

		/// <summary>
		/// ^�L�[
		/// </summary>
		extern detail::_key Caret;
		/// <summary>
		/// .�L�[
		/// </summary>
		extern detail::_key Period;

		/// <summary>
		/// �^�L�[
		/// </summary>
		extern detail::_key Slash;

		/// <summary>
		/// ��Alt�L�[
		/// </summary>
		extern detail::_key LAlt;

		/// <summary>
		/// �EAlt�L�[
		/// </summary>
		extern detail::_key RAlt;

		/// <summary>
		/// ScrollLock�L�[
		/// </summary>
		extern detail::_key ScrollLock;

		/// <summary>
		/// ;�L�[
		/// </summary>
		extern detail::_key Semicolon;

		/// <summary>
		/// :�L�[
		/// </summary>
		extern detail::_key Colon;

		/// <summary>
		/// [�L�[
		/// </summary>
		extern detail::_key LBracket;

		/// <summary>
		/// ]�L�[
		/// </summary>
		extern detail::_key RBracket;

		/// <summary>
		/// @�L�[
		/// </summary>
		extern detail::_key At;

		/// <summary>
		/// �_�L�[
		/// </summary>
		extern detail::_key Backslash;

		/// <summary>
		/// ,�L�[
		/// </summary>
		extern detail::_key Comma;

		/// <summary>
		/// �����L�[
		/// </summary>
		extern detail::_key Kanji;

		/// <summary>
		/// �ϊ��L�[
		/// </summary>
		extern detail::_key Convert;

		/// <summary>
		/// ���ϊ��L�[
		/// </summary>
		extern detail::_key NoConvert;

		/// <summary>
		/// ���ȃL�[
		/// </summary>
		extern detail::_key Kana;

		/// <summary>
		/// �A�v���P�[�V�������j���[�L�[
		/// </summary>
		extern detail::_key Menu;

		/// <summary>
		/// CapsLock�L�[
		/// </summary>
		extern detail::_key Capaslock;

		/// <summary>
		/// PrintScreen�L�[
		/// </summary>
		extern detail::_key Printscreen;

		/// <summary>
		/// PauseBreak�L�[
		/// </summary>
		extern detail::_key PauseBreak;

		/// <summary>
		/// ��Windows�L�[
		/// </summary>
		extern detail::_key LWindows;

		/// <summary>
		/// �EWindows�L�[
		/// </summary>
		extern detail::_key RWindows;



		/// <summary>
		/// �^�u�L�[
		/// </summary>
		extern detail::_key Tab;

		/// <summary>
		/// �o�b�N�X�y�[�X�L�[
		/// </summary>
		extern detail::_key Back;

		/// <summary>
		/// �G���^�[�L�[
		/// </summary>
		extern detail::_key Return;

		/// <summary>
		/// ���V�t�g�L�[
		/// </summary>
		extern detail::_key LShift;

		/// <summary>
		/// �E�V�t�g�L�[
		/// </summary>
		extern detail::_key RShift;

		/// <summary>
		/// ���R���g���[���L�[
		/// </summary>
		extern detail::_key LControl;

		/// <summary>
		/// �E�R���g���[���L�[
		/// </summary>
		extern detail::_key RControl;

		/// <summary>
		/// �G�X�P�[�v�L�[
		/// </summary>
		extern detail::_key Escape;

		/// <summary>
		/// �X�y�[�X�L�[
		/// </summary>
		extern detail::_key Space;

		/// <summary>
		/// PageUp�L�[
		/// </summary>
		extern detail::_key PageUp;

		/// <summary>
		///�ς�Down �L�[
		/// </summary>
		extern detail::_key PageDown;

		/// <summary>
		/// End�L�[
		/// </summary>
		extern detail::_key End;

		/// <summary>
		/// Home�L�[
		/// </summary>
		extern detail::_key Home;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::_key Left;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::_key Up;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::_key Right;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::_key Down;

		/// <summary>
		/// Insert�L�[
		/// </summary>
		extern detail::_key Insert;

		/// <summary>
		/// Delete�L�[
		/// </summary>
		extern detail::_key Delete;



		/// <summary>
		/// F1�L�[
		/// </summary>
		extern detail::_key F1;

		/// <summary>
		/// F2�L�[
		/// </summary>
		extern detail::_key F2;

		/// <summary>
		/// F3�L�[
		/// </summary>
		extern detail::_key F3;

		/// <summary>
		/// F4�L�[
		/// </summary>
		extern detail::_key F4;

		/// <summary>
		/// F5�L�[
		/// </summary>
		extern detail::_key F5;

		/// <summary>
		/// F6�L�[
		/// </summary>
		extern detail::_key F6;

		/// <summary>
		/// F7�L�[
		/// </summary>
		extern detail::_key F7;

		/// <summary>
		/// F8�L�[
		/// </summary>
		extern detail::_key F8;

		/// <summary>
		/// F9�L�[
		/// </summary>
		extern detail::_key F9;

		/// <summary>
		/// !0�L�[
		/// </summary>
		extern detail::_key F10;

		/// <summary>
		/// F11�L�[
		/// </summary>
		extern detail::_key F11;

		/// <summary>
		/// F12�L�[
		/// </summary>
		extern detail::_key F12;



		/// <summary>
		/// A�L�[
		/// </summary>
		extern detail::_key A;

		/// <summary>
		/// B�L�[
		/// </summary>
		extern detail::_key B;

		/// <summary>
		/// C�L�[
		/// </summary>
		extern detail::_key C;

		/// <summary>
		/// D�L�[
		/// </summary>
		extern detail::_key D;

		/// <summary>
		/// E�L�[
		/// </summary>
		extern detail::_key E;

		/// <summary>
		/// F�L�[
		/// </summary>
		extern detail::_key F;

		/// <summary>
		/// G�L�[
		/// </summary>
		extern detail::_key G;

		/// <summary>
		/// H�L�[
		/// </summary>
		extern detail::_key H;

		/// <summary>
		/// I�L�[
		/// </summary>
		extern detail::_key I;

		/// <summary>
		/// J�L�[
		/// </summary>
		extern detail::_key J;

		/// <summary>
		/// K�L�[
		/// </summary>
		extern detail::_key K;

		/// <summary>
		/// L�L�[
		/// </summary>
		extern detail::_key L;

		/// <summary>
		/// M�L�[
		/// </summary>
		extern detail::_key M;

		/// <summary>
		/// N�L�[
		/// </summary>
		extern detail::_key N;

		/// <summary>
		/// O�L�[
		/// </summary>
		extern detail::_key O;

		/// <summary>
		/// P�L�[
		/// </summary>
		extern detail::_key P;

		/// <summary>
		/// Q�L�[
		/// </summary>
		extern detail::_key Q;

		/// <summary>
		/// R�L�[
		/// </summary>
		extern detail::_key R;

		/// <summary>
		/// S�L�[
		/// </summary>
		extern detail::_key S;

		/// <summary>
		/// T�L�[
		/// </summary>
		extern detail::_key T;

		/// <summary>
		/// U�L�[
		/// </summary>
		extern detail::_key U;

		/// <summary>
		/// V�L�[
		/// </summary>
		extern detail::_key V;

		/// <summary>
		/// W�L�[
		/// </summary>
		extern detail::_key W;

		/// <summary>
		/// X�L�[
		/// </summary>
		extern detail::_key X;

		/// <summary>
		/// Y�L�[
		/// </summary>
		extern detail::_key Y;

		/// <summary>
		/// Z�L�[
		/// </summary>
		extern detail::_key Z;

		/// <summary>
		/// �����ꂽ�L�[�����ׂĎ擾
		/// </summary>
		/// <returns>���݉�����Ă���L�[�̔z��</returns>
		std::vector<std::reference_wrapper<detail::_key>> pressed_key();
	}; // namespace keyboard
}