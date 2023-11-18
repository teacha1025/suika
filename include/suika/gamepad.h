#pragma once
#include <vector>
#include <array>
#include "point.h"
#include "def.h"
#include "type.h"
#include "range.h"
#include "input_base.h"

namespace suika {
	/// <summary>
	/// �Q�[���p�b�h�̏��
	/// </summary>
	enum class pad_states {
		//! XInput�œ��͏���
		XInput,
		//! DirectInput�œ��͏���
		DirectInput,
		//! �Q�[���p�b�h�͖��ڑ��A���邢�͎g�p�s��
		Disable
	};
	/// <summary>
	/// �Q�[���p�b�h���͂Ɋւ����`�y�ъ֐�
	/// </summary>
	namespace gamepad {
		/// <summary>
		/// �Q�[���p�b�h�Ɋւ�����
		/// </summary>
		struct info {
			/// <summary>
			/// �Q�[���p�b�h��ID
			/// </summary>
			ubyte		index = 255;

			/// <summary>
			/// �ڑ��̎��
			/// </summary>
			pad_states	states = pad_states::Disable;

			/// <summary>
			/// �f�o�C�X��
			/// </summary>
			string		name;

			/// <summary>
			/// PID
			/// </summary>
			string		pid;

			/// <summary>
			/// VID
			/// </summary>
			string		vid;
		};
	}
	/// <summary>
	/// �����I�Ȏ���
	/// </summary>
	namespace detail {
		class gamepad;
		class gamepad_trigger;
		class gamepad_stick;

		/// <summary>
		/// �Q�[���p�b�h�̃{�^��
		/// </summary>
		class gamepad_button : public input_base {
			ubyte _id = 0;
			ulong _xcode = 0;
			ulong _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

			friend gamepad;
			friend gamepad_trigger;
			friend gamepad_stick;
			void update_trigger(double value);
		public:
			gamepad_button(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id);
			gamepad_button() {}
			void update();
			/// <summary>
			/// ���O���擾
			/// </summary>
			/// <returns>�{�^���̖��O</returns>
			virtual string to_string() const override;
		};
		/// <summary>
		/// �Q�[���p�b�h�̃X�e�B�b�N
		/// </summary>
		class gamepad_stick : public input_base {
		private:
			point<double>   _value;
			gamepad_button button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ulong _xcode = 0;
			ulong _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

			friend gamepad;
			friend gamepad_trigger;
			friend gamepad_button;
		public:
			gamepad_stick(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id);
			gamepad_stick() {}
			void update();

			/// <summary>
			/// �X�e�B�b�N�̓��͒l�̎擾
			/// </summary>
			/// <returns>��:x[-1~1] �c:y[-1~1]</returns>
			point<double> value() const {
				return _value;
			}

			/// <summary>
			/// �����ꂽ���Ԃ̎擾
			/// </summary>
			/// <returns>�X�e�B�b�N���������܂ꂽ�t���[����</returns>
			unsigned int count() const override {
				return button.count();
			}

			/// <summary>
			/// ������Ă��邩�ǂ����̎擾
			/// </summary>
			/// <returns>������Ă��邩�ǂ���</returns>
			bool press() const override {
				return button.press();
			}

			/// <summary>
			/// ������Ă���̂��ǂ����̎擾
			/// </summary>
			/// <returns>������Ă��邩�ǂ���</returns>
			bool release() const override {
				return button.release();
			}

			/// <summary>
			/// �����ꂽ���ǂ����̎擾
			/// </summary>
			/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
			bool up() const override {
				return button.up();
			}

			/// <summary>
			/// �����ꂽ���ǂ����̎擾
			/// </summary>
			/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
			bool down() const override {
				return button.down();
			}

			/// <summary>
			/// 臒l��ݒ肷��
			/// </summary>
			/// <param name="value">�V����臒l</param>
			void threshold(range<0.0, 1.0> value) {
				_deadzone = value;
			}

			/// <summary>
			/// ���݂�臒l���擾
			/// </summary>
			/// <returns></returns>
			double threshold() const {
				return _deadzone;
			}

			/// <summary>
			/// ���O���擾
			/// </summary>
			/// <returns>�X�e�B�b�N�̖��O</returns>
			virtual string to_string() const override;
		};
		/// <summary>
		/// �Q�[���p�b�h�̃g���K�[
		/// </summary>
		class gamepad_trigger : public input_base {
		private:
			double		  _value = 0;
			gamepad_button _button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ulong _xcode = 0;
			ulong _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

			friend gamepad;
			friend gamepad_button;
			friend gamepad_stick;
		public:
			gamepad_trigger(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id);
			gamepad_trigger() {}
			void update();

			/// <summary>
			/// �g���K�[�̓��͒l�̎擾
			/// </summary>
			/// <returns>���:0 ����:1</returns>
			double value() const {
				return _value;
			}

			/// <summary>
			/// �����ꂽ���Ԃ̎擾
			/// </summary>
			/// <returns>�L�[��{�^���������ꂽ�t���[����</returns>
			unsigned int count() const override {
				return _button.count();
			}

			/// <summary>
			/// ������Ă��邩�ǂ����̎擾
			/// </summary>
			/// <returns>������Ă��邩�ǂ���</returns>
			bool press() const override {
				return _button.press();
			}

			/// <summary>
			/// ������Ă���̂��ǂ����̎擾
			/// </summary>
			/// <returns>������Ă��邩�ǂ���</returns>
			bool release() const override {
				return _button.release();
			}

			/// <summary>
			/// �����ꂽ���ǂ����̎擾
			/// </summary>
			/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
			bool up() const override {
				return _button.up();
			}

			/// <summary>
			/// �����ꂽ���ǂ����̎擾
			/// </summary>
			/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
			bool down() const override {
				return _button.down();
			}

			/// <summary>
			/// 臒l��ݒ肷��
			/// </summary>
			/// <param name="value">�V����臒l</param>
			void threshold(range<0.0, 1.0> value) {
				_deadzone = value;
			}

			/// <summary>
			/// ���݂�臒l���擾
			/// </summary>
			/// <returns>���͂����m����܂ł�臒l(�f�b�h�]�[��)</returns>
			double threshold() const {
				return _deadzone;
			}

			/// <summary>
			/// ���O���擾
			/// </summary>
			/// <returns>�g���K�[�̖��O</returns>
			virtual string to_string() const override;
		};
		/// <summary>
		/// �Q�[���p�b�h
		/// </summary>
		class gamepad {
		private:
			ubyte	  _id = 255;
			//pad_states _states = pad_states::Disable;
			//string _name;

			friend void init(gamepad& gp, ubyte id, suika::gamepad::info info);
			friend void update(gamepad& gp);
			suika::gamepad::info _info;
			bool _is_use_xinput = true;
		public:
			/// <summary>
			/// �\����
			/// </summary>
			gamepad_button Up;

			/// <summary>
			/// �\����
			/// </summary>
			gamepad_button Down;

			/// <summary>
			/// �\����
			/// </summary>
			gamepad_button Left;

			/// <summary>
			/// �\���E
			/// </summary>
			gamepad_button Right;

			/// <summary>
			/// �X�^�[�g�{�^��
			/// </summary>
			gamepad_button Start;

			/// <summary>
			/// �o�b�N�{�^��
			/// </summary>
			gamepad_button Back;

			/// <summary>
			/// LB�{�^��
			/// </summary>
			gamepad_button LShoulder;

			/// <summary>
			/// RB�{�^��
			/// </summary>
			gamepad_button RShoulder;

			/// <summary>
			/// ���X�e�B�b�N
			/// </summary>
			gamepad_stick LStick;

			/// <summary>
			/// �E�X�e�B�b�N
			/// </summary>
			gamepad_stick RStick;

			/// <summary>
			/// ���g���K�[
			/// </summary>
			gamepad_trigger LTrigger;

			/// <summary>
			/// �E�g���K�[
			/// </summary>
			gamepad_trigger RTrigger;

			/// <summary>
			/// A�{�^��
			/// </summary>
			gamepad_button A;

			/// <summary>
			/// B�{�^��
			/// </summary>
			gamepad_button B;

			/// <summary>
			/// X�{�^��
			/// </summary>
			gamepad_button X;

			/// <summary>
			/// Y�{�^��
			/// </summary>
			gamepad_button Y;

			/// <summary>
			/// �Q�[���p�b�h�̏��
			/// </summary>
			/// <returns>���݂̏������</returns>
			pad_states states() const {
				return _info.states;
			}

			/// <summary>
			/// ���݉�����Ă���{�^�����擾
			/// </summary>
			/// <returns>�{�^���ւ̎Q�Ƃ�Ԃ�</returns>
			std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

			/// <summary>
			/// ���݂̏����擾����
			/// </summary>
			/// <returns>�Q�[���p�b�h�̏��</returns>
			suika::gamepad::info info() const{
				return _info;
			}

			/// <summary>
			/// xinput�ɑΉ����Ă���ꍇ�A���͏�����xinput���g�p���邩�ݒ�
			/// </summary>
			/// <param name="flag">xinput���g�p���邩</param>
			void enable_xinput(bool flag) {
				_is_use_xinput = flag;
				A._is_use_xinput = flag;
				B._is_use_xinput = flag;
				X._is_use_xinput = flag;
				Y._is_use_xinput = flag;

				Up._is_use_xinput = flag;
				Down._is_use_xinput = flag;
				Left._is_use_xinput = flag;
				Right._is_use_xinput = flag;

				Start._is_use_xinput = flag;
				Back._is_use_xinput = flag;

				LShoulder._is_use_xinput = flag;
				RShoulder._is_use_xinput = flag;

				LStick._is_use_xinput = flag;
				RStick._is_use_xinput = flag;

				LStick.button._is_use_xinput = flag;
				RStick.button._is_use_xinput = flag;

				LTrigger._is_use_xinput = flag;
				RTrigger._is_use_xinput = flag;
			}

			/// <summary>
			/// �Q�[���p�b�h�̖��O���擾
			/// </summary>
			/// <returns>�f�o�C�X��+���i��</returns>
			string to_string() const{
				return _info.name;
			}
		};
	} // namespace detail

	/// <summary>
	/// �Q�[���p�b�h���͂Ɋւ����`�y�ъ֐�
	/// </summary>
	namespace gamepad {
		define MAX_JOYPAD_NUM = 16;
		

		/// <summary>
		/// �ڑ�����Ă���Q�[���p�b�h���čX�V����
		/// </summary>
		void load_gamepads();

		/// <summary>
		/// �Q�[���p�b�h(0~15)
		/// </summary>
		extern std::array<detail::gamepad, MAX_JOYPAD_NUM> pad;
		/// <summary>
		/// ���݉�����Ă���{�^�����擾
		/// </summary>
		/// <returns>�{�^���ւ̎Q�Ƃ�Ԃ�</returns>
		//std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

	} // namespace gamepad
}