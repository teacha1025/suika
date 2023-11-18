#pragma once
#include "def.h"
#include "base.h"

namespace suika {
	enum class input_state {
		press,
		release,
		up,
		down
	};

	/// <summary>
	/// �f�o�C�X����
	/// </summary>
	class input_base : public detail::ibase {
	protected:
		unsigned int _code = 0;
		unsigned int _press_count = 0;
		input_state _state = input_state::release;

		string _device_name;
	public:
		/// <summary>
		/// �����ꂽ���Ԃ̎擾
		/// </summary>
		/// <returns>�L�[��{�^���������ꂽ�t���[����</returns>
		virtual unsigned int count() const {
			return _press_count;
		}

		/// <summary>
		/// ������Ă��邩�ǂ����̎擾
		/// </summary>
		/// <returns>������Ă��邩�ǂ���</returns>
		virtual bool press() const {
			return _state == input_state::press || _state == input_state::down;
		}

		/// <summary>
		/// ������Ă���̂��ǂ����̎擾
		/// </summary>
		/// <returns>������Ă��邩�ǂ���</returns>
		virtual bool release() const {
			return _state == input_state::release;
		}

		/// <summary>
		/// �����ꂽ���ǂ����̎擾
		/// </summary>
		/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
		virtual bool up() const {
			return _state == input_state::up;
		}

		/// <summary>
		/// �����ꂽ���ǂ����̎擾
		/// </summary>
		/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
		virtual bool down() const {
			return _state == input_state::down;
		}

		/// <summary>
		/// ���O���擾
		/// </summary>
		/// <returns>�L�[�̖��O��}�E�X�̃{�^���̖��O</returns>
		virtual string to_string() const {
			return _device_name;
		}

		virtual void update() = 0;
	};
}