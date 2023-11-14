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
		xinput,
		//! DirectInput�œ��͏���
		direct_input,
		//! �Q�[���p�b�h�͖��ڑ��A���邢�͎g�p�s��
		disable
	};
	namespace detail {
		class gamepad_button : public input_base {
			ubyte _id = 0;
			ubyte _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;
		public:
			gamepad_button(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id);
			gamepad_button() {}
			void update();
		};
		class gamepad_stick : public input_base {
		private:
			point<double>   _value;
			gamepad_button button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ubyte _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;
		public:
			gamepad_stick(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id);
			gamepad_stick() {}
			void update();

			/// <summary>
			/// �X�e�B�b�N�̓��͒l�̎擾
			/// </summary>
			/// <returns>��:x[-1~1] �c:y[-1~1]</returns>
			point<double> value() const;

			/// <summary>
			/// �����ꂽ���Ԃ̎擾
			/// </summary>
			/// <returns>�L�[��{�^���������ꂽ�t���[����</returns>
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
		};
		class gamepad_trigger : public input_base {
		private:
			double		  _value = 0;
			gamepad_button _button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ubyte _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

		public:
			gamepad_trigger(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id);
			gamepad_trigger() {}
			void update();

			/// <summary>
			/// �g���K�[�̓��͒l�̎擾
			/// </summary>
			/// <returns>���:0 ����:1</returns>
			double value() const;

			/// <summary>
			/// �����ꂽ���Ԃ̎擾
			/// </summary>
			/// <returns>�L�[��{�^���������ꂽ�t���[����</returns>
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
		};

		class gamepad {
		private:
			ubyte	  ID = 255;
			pad_states states = pad_states::disable;

			friend void init(gamepad& gp, ubyte id);
			friend void update(gamepad& gp);

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
				return states;
			}

			/// <summary>
			/// ���݉�����Ă���{�^�����擾
			/// </summary>
			/// <returns>�{�^���ւ̎Q�Ƃ�Ԃ�</returns>
			std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

			/// <summary>
			/// �Q�[���p�b�h�̖��O���擾
			/// </summary>
			/// <returns>�f�o�C�X��+���i��</returns>
			string to_string();
		};
	} // namespace detail
	namespace gamepad {
		define MAX_JOYPAD_NUM = 16;
		struct info {
			ubyte		index = 255;
			pad_states	states = pad_states::disable;
			string		name;
			string		pid;
			string		vid;
		};


		void load_gamepads();

		/// <summary>
		/// �Q�[���p�b�h(0~15)
		/// </summary>
		//extern std::array<detail::gamepad, MAX_JOYPAD_NUM> pad;
		/// <summary>
		/// ���݉�����Ă���{�^�����擾
		/// </summary>
		/// <returns>�{�^���ւ̎Q�Ƃ�Ԃ�</returns>
		//std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

	} // namespace gamepad
}