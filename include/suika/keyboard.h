#pragma once
#include "input_base.h"

namespace suika {
	namespace detail {
		class key : public input_base {
		public:
			/// <summary>
			/// �L�[�̍쐬
			/// </summary>
			/// <param name="code">�L�[�R�[�h</param>
			/// <param name="name">�L�[�̖��O</param>
			key(unsigned int code, string name);
			/// <summary>
			/// �f�t�H���g�L�[
			/// </summary>
			key() {}
			/// <summary>
			/// �L�[�̍X�V
			/// </summary>
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
		extern detail::key Key1;

		/// <summary>
		/// 2�L�[
		/// </summary>
		extern detail::key Key2;

		/// <summary>
		/// 3�L�[
		/// </summary>
		extern detail::key Key3;

		/// <summary>
		/// 4�L�[
		/// </summary>
		extern detail::key Key4;

		/// <summary>
		/// 5�L�[
		/// </summary>
		extern detail::key Key5;

		/// <summary>
		/// 6�L�[
		/// </summary>
		extern detail::key Key6;

		/// <summary>
		/// 7�L�[
		/// </summary>
		extern detail::key Key7;

		/// <summary>
		/// 8�L�[
		/// </summary>
		extern detail::key Key8;

		/// <summary>
		/// 9�L�[
		/// </summary>
		extern detail::key Key9;

		/// <summary>
		/// 0�L�[
		/// </summary>
		extern detail::key Key0;



		/// <summary>
		/// NumLock�L�[
		/// </summary>
		extern detail::key Numlock;

		/// <summary>
		/// �e���L�[1�L�[
		/// </summary>
		extern detail::key Num1;

		/// <summary>
		/// �e���L�[2�L�[
		/// </summary>
		extern detail::key Num2;

		/// <summary>
		/// �e���L�[3�L�[
		/// </summary>
		extern detail::key Num3;

		/// <summary>
		/// �e���L�[4�L�[
		/// </summary>
		extern detail::key Num4;

		/// <summary>
		/// �e���L�[5�L�[
		/// </summary>
		extern detail::key Num5;

		/// <summary>
		/// �e���L�[6�L�[
		/// </summary>
		extern detail::key Num6;

		/// <summary>
		/// �e���L�[7�L�[
		/// </summary>
		extern detail::key Num7;

		/// <summary>
		/// �e���L�[8�L�[
		/// </summary>
		extern detail::key Num8;

		/// <summary>
		/// �e���L�[9�L�[
		/// </summary>
		extern detail::key Num9;

		/// <summary>
		/// �e���L�[0�L�[
		/// </summary>
		extern detail::key Num0;

		/// <summary>
		/// �e���L�[*�L�[
		/// </summary>
		extern detail::key NumAsterisk;

		/// <summary>
		/// �e���L�[+�L�[
		/// </summary>
		extern detail::key NumPlus;

		/// <summary>
		/// �e���L�[-�L�[
		/// </summary>
		extern detail::key NumMinus;

		/// <summary>
		/// �e���L�[.�L�[
		/// </summary>
		extern detail::key NumPeriod;

		/// <summary>
		/// �e���L�[/�L�[
		/// </summary>
		extern detail::key NumSlash;

		/// <summary>
		/// �e���L�[�̃G���^�[�L�[
		/// </summary>
		extern detail::key NumEnter;



		/// <summary>
		/// -�L�[
		/// </summary>
		extern detail::key Minus;

		/// <summary>
		/// \�L�[
		/// </summary>
		extern detail::key Yen;

		/// <summary>
		/// ^�L�[
		/// </summary>
		extern detail::key Caret;
		/// <summary>
		/// .�L�[
		/// </summary>
		extern detail::key Period;

		/// <summary>
		/// �^�L�[
		/// </summary>
		extern detail::key Slash;

		/// <summary>
		/// ��Alt�L�[
		/// </summary>
		extern detail::key LAlt;

		/// <summary>
		/// �EAlt�L�[
		/// </summary>
		extern detail::key RAlt;

		/// <summary>
		/// ScrollLock�L�[
		/// </summary>
		extern detail::key ScrollLock;

		/// <summary>
		/// ;�L�[
		/// </summary>
		extern detail::key Semicolon;

		/// <summary>
		/// :�L�[
		/// </summary>
		extern detail::key Colon;

		/// <summary>
		/// [�L�[
		/// </summary>
		extern detail::key LBracket;

		/// <summary>
		/// ]�L�[
		/// </summary>
		extern detail::key RBracket;

		/// <summary>
		/// @�L�[
		/// </summary>
		extern detail::key At;

		/// <summary>
		/// �_�L�[
		/// </summary>
		extern detail::key Backslash;

		/// <summary>
		/// ,�L�[
		/// </summary>
		extern detail::key Comma;

		/// <summary>
		/// �����L�[
		/// </summary>
		extern detail::key Kanji;

		/// <summary>
		/// �ϊ��L�[
		/// </summary>
		extern detail::key Convert;

		/// <summary>
		/// ���ϊ��L�[
		/// </summary>
		extern detail::key NoConvert;

		/// <summary>
		/// ���ȃL�[
		/// </summary>
		extern detail::key Kana;

		/// <summary>
		/// �A�v���P�[�V�������j���[�L�[
		/// </summary>
		extern detail::key Menu;

		/// <summary>
		/// CapsLock�L�[
		/// </summary>
		extern detail::key Capaslock;

		/// <summary>
		/// PrintScreen�L�[
		/// </summary>
		extern detail::key Printscreen;

		/// <summary>
		/// PauseBreak�L�[
		/// </summary>
		extern detail::key PauseBreak;

		/// <summary>
		/// ��Windows�L�[
		/// </summary>
		extern detail::key LWindows;

		/// <summary>
		/// �EWindows�L�[
		/// </summary>
		extern detail::key RWindows;



		/// <summary>
		/// �^�u�L�[
		/// </summary>
		extern detail::key Tab;

		/// <summary>
		/// �o�b�N�X�y�[�X�L�[
		/// </summary>
		extern detail::key Back;

		/// <summary>
		/// �G���^�[�L�[
		/// </summary>
		extern detail::key Return;

		/// <summary>
		/// ���V�t�g�L�[
		/// </summary>
		extern detail::key LShift;

		/// <summary>
		/// �E�V�t�g�L�[
		/// </summary>
		extern detail::key RShift;

		/// <summary>
		/// ���R���g���[���L�[
		/// </summary>
		extern detail::key LControl;

		/// <summary>
		/// �E�R���g���[���L�[
		/// </summary>
		extern detail::key RControl;

		/// <summary>
		/// �G�X�P�[�v�L�[
		/// </summary>
		extern detail::key Escape;

		/// <summary>
		/// �X�y�[�X�L�[
		/// </summary>
		extern detail::key Space;

		/// <summary>
		/// PageUp�L�[
		/// </summary>
		extern detail::key PageUp;

		/// <summary>
		///�ς�Down �L�[
		/// </summary>
		extern detail::key PageDown;

		/// <summary>
		/// End�L�[
		/// </summary>
		extern detail::key End;

		/// <summary>
		/// Home�L�[
		/// </summary>
		extern detail::key Home;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::key Left;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::key Up;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::key Right;

		/// <summary>
		/// ���L�[
		/// </summary>
		extern detail::key Down;

		/// <summary>
		/// Insert�L�[
		/// </summary>
		extern detail::key Insert;

		/// <summary>
		/// Delete�L�[
		/// </summary>
		extern detail::key Delete;



		/// <summary>
		/// F1�L�[
		/// </summary>
		extern detail::key F1;

		/// <summary>
		/// F2�L�[
		/// </summary>
		extern detail::key F2;

		/// <summary>
		/// F3�L�[
		/// </summary>
		extern detail::key F3;

		/// <summary>
		/// F4�L�[
		/// </summary>
		extern detail::key F4;

		/// <summary>
		/// F5�L�[
		/// </summary>
		extern detail::key F5;

		/// <summary>
		/// F6�L�[
		/// </summary>
		extern detail::key F6;

		/// <summary>
		/// F7�L�[
		/// </summary>
		extern detail::key F7;

		/// <summary>
		/// F8�L�[
		/// </summary>
		extern detail::key F8;

		/// <summary>
		/// F9�L�[
		/// </summary>
		extern detail::key F9;

		/// <summary>
		/// !0�L�[
		/// </summary>
		extern detail::key F10;

		/// <summary>
		/// F11�L�[
		/// </summary>
		extern detail::key F11;

		/// <summary>
		/// F12�L�[
		/// </summary>
		extern detail::key F12;



		/// <summary>
		/// A�L�[
		/// </summary>
		extern detail::key A;

		/// <summary>
		/// B�L�[
		/// </summary>
		extern detail::key B;

		/// <summary>
		/// C�L�[
		/// </summary>
		extern detail::key C;

		/// <summary>
		/// D�L�[
		/// </summary>
		extern detail::key D;

		/// <summary>
		/// E�L�[
		/// </summary>
		extern detail::key E;

		/// <summary>
		/// F�L�[
		/// </summary>
		extern detail::key F;

		/// <summary>
		/// G�L�[
		/// </summary>
		extern detail::key G;

		/// <summary>
		/// H�L�[
		/// </summary>
		extern detail::key H;

		/// <summary>
		/// I�L�[
		/// </summary>
		extern detail::key I;

		/// <summary>
		/// J�L�[
		/// </summary>
		extern detail::key J;

		/// <summary>
		/// K�L�[
		/// </summary>
		extern detail::key K;

		/// <summary>
		/// L�L�[
		/// </summary>
		extern detail::key L;

		/// <summary>
		/// M�L�[
		/// </summary>
		extern detail::key M;

		/// <summary>
		/// N�L�[
		/// </summary>
		extern detail::key N;

		/// <summary>
		/// O�L�[
		/// </summary>
		extern detail::key O;

		/// <summary>
		/// P�L�[
		/// </summary>
		extern detail::key P;

		/// <summary>
		/// Q�L�[
		/// </summary>
		extern detail::key Q;

		/// <summary>
		/// R�L�[
		/// </summary>
		extern detail::key R;

		/// <summary>
		/// S�L�[
		/// </summary>
		extern detail::key S;

		/// <summary>
		/// T�L�[
		/// </summary>
		extern detail::key T;

		/// <summary>
		/// U�L�[
		/// </summary>
		extern detail::key U;

		/// <summary>
		/// V�L�[
		/// </summary>
		extern detail::key V;

		/// <summary>
		/// W�L�[
		/// </summary>
		extern detail::key W;

		/// <summary>
		/// X�L�[
		/// </summary>
		extern detail::key X;

		/// <summary>
		/// Y�L�[
		/// </summary>
		extern detail::key Y;

		/// <summary>
		/// Z�L�[
		/// </summary>
		extern detail::key Z;

		/// <summary>
		/// �����ꂽ�L�[�����ׂĎ擾
		/// </summary>
		/// <returns>���݉�����Ă���L�[�̔z��</returns>
		std::vector<std::reference_wrapper<detail::key>> pressed_key();
	}; // namespace keyboard
}