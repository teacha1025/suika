#pragma once
#include "palette.h"
#include "def.h"
#include "blend.h"
#include "base.h"
#include "rect.h"

namespace suika {
	class font : public detail::ibase {
	public:
		enum class alignment {
			leading = 0,
			trailing = 1,
			center = 2,
			justified = 3
		};

		enum class stretch {
			undefined = 0,
			ultra_condensed = 1,
			extra_condensed = 2,
			condensed = 3,
			semi_condensed = 4,
			normal = 5,
			semi_expanded = 6,
			expanded = 7,
			extra_expanded = 8,
			ultra_expanded = 9
		};

		enum class style {
			normal = 0,
			oblique = 1,
			italic = 2
		};

		enum class weight {
			thin = 100,
			extra_light = 200,
			light = 300,
			semi_light = 350,
			normal = 400,
			semi_bold = 600,
			bold = 700,
			extra_bold = 800,
			black = 900,
			extra_black = 950
		};
	private:
		color_f _color;
		std::string _font;
		float _size;
		alignment _alignment;
		std::string _locale;
		stretch _stretch;
		style _style;
		weight _weight;

		using position_type = float;
		//���_����̈ړ���
		vector3<position_type> _transition;

		//�I�u�W�F�N�g�̕`��A��]�̒��S
		vector3<position_type> _center;

		//��]��
		vector3<position_type> _rotation;

		//�g�嗦
		vector3<double> _extend;

		//�u�����h
		blend _blend;

		string _text;

		void set(canvas::canvas_id id) const;

		canvas::canvas_id _cid;
	public:
		font() {
			_color = palette::black;
			_size = 16;
			_alignment = alignment::leading;
			_font = "���C���I";
			_locale = "";
			_stretch = stretch::normal;
			_style = style::normal;
			_weight = weight::normal;
			_text = "";
			_cid = window::canvas()->id;
		}

		/// <summary>
		/// �e�L�X�g��`�悷��
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// �`�悷����e��ݒ�
		/// </summary>
		/// <param name="text">�e�L�X�g</param>
		virtual font text(const string& text)&& {
			_text = text;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �`�悷����e��ݒ�
		/// </summary>
		/// <param name="text">�e�L�X�g</param>
		virtual font& text(const string& text)& {
			_text = text;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position">�ݒ肷����W</param>
		virtual font at(const vector3<position_type>& position)&& {
			_transition = position;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position">�ݒ肷����W</param>
		virtual font& at(const vector3<position_type>& position)& {
			_transition = position;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position">�ݒ肷����W</param>
		virtual font at(const point<position_type>& position)&& {
			_transition = vector3<position_type>{ position.x, position.y, 0.0 };
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position">�ݒ肷����W</param>
		virtual font& at(const point<position_type>& position)& {
			_transition = vector3<position_type>{ position.x, position.y, 0.0 };
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �I�u�W�F�N�g�̒��S��ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷�钆�S���W</param>
		virtual font centered(const vector3<position_type>& center)&& {
			_center = center;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �I�u�W�F�N�g�̒��S��ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷�钆�S���W</param>
		virtual font& centered(const vector3<position_type>& center)& {
			_center = center;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// �I�u�W�F�N�g�̒��S��ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷�钆�S���W</param>
		virtual font centered(const point<position_type>& center)&& {
			_center = vector3<position_type>{ center.x, center.y, 0.0 };
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �I�u�W�F�N�g�̒��S��ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷�钆�S���W</param>
		virtual font& centered(const point<position_type>& center)& {
			_center = vector3<position_type>{ center.x, center.y, 0.0 };
			return dynamic_cast<font&>(*this);
		}

		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷��e���̉�]��</param>
		virtual font rotated(const vector3<position_type>& rotation)&& {
			_rotation = rotation;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷��e���̉�]��</param>
		virtual font& rotated(const vector3<position_type>& rotation)& {
			_rotation = rotation;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷���]��</param>
		virtual font rotated(const position_type& rotation)&& {
			_rotation.z = rotation;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="center">�ݒ肷���]��</param>
		virtual font& rotated(const position_type& rotation)& {
			_rotation.z = rotation;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="rate">�g�嗦</param>
		virtual font extended(const vector3<double>& rate)&& {
			_extend = rate;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="rate">�g�嗦</param>
		virtual font& extended(const vector3<double>& rate)& {
			_extend = rate;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="rate">�g�嗦</param>
		virtual font extended(const point<double>& rate)&& {
			_extend = { rate.x, rate.y, 1 };
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="rate">�g�嗦</param>
		virtual font& extended(const point<double>& rate)& {
			_extend = { rate.x, rate.y, 1 };
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="rate">�g�嗦</param>
		virtual font extended(double rate)&& {
			_extend = { rate, rate, rate };
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="rate">�g�嗦</param>
		virtual font& extended(double rate)& {
			_extend = { rate, rate, rate };
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// �u�����h�̐ݒ�
		/// </summary>
		/// <param name="type">�u�����h�̎��</param>
		virtual font blended(blend type)&& {
			_blend = type;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �u�����h�̐ݒ�
		/// </summary>
		/// <param name="type">�u�����h�̎��</param>
		virtual font& blended(blend type)& {
			_blend = type;
			return static_cast<font&>(*this);
		}

		//�擾�n

		/// <summary>
		/// �I�u�W�F�N�g�̌��_����̈ړ��ʂ��擾
		/// </summary>
		/// <returns>xyz��Ԃ̈ړ���</returns>
		virtual vector3<position_type> position_xyz() const {
			return _transition;
		}
		/// <summary>
		/// �I�u�W�F�N�g�̌��_����̈ړ��ʂ��擾
		/// </summary>
		/// <returns>xy���ʂ̈ړ���</returns>
		virtual point<position_type> position() const {
			return point<position_type> {
				static_cast<position_type>(_transition.x),
					static_cast<position_type>(_transition.y)
			};
		}

		/// <summary>
		/// �g�嗦�̎擾
		/// </summary>
		/// <returns>xyz�����̊g�嗦</returns>
		virtual vector3<position_type> extend_xyz() const {
			return _extend;
		}

		/// <summary>
		/// �g�嗦�̎擾
		/// </summary>
		/// <returns>xy�����ւ̊g�嗦</returns>
		virtual point<position_type> extend() const {
			return point<position_type> {
				static_cast<position_type>(_extend.x),
					static_cast<position_type>(_extend.y)
			};
		}

		/// <summary>
		/// ��]�ʂ̎擾
		/// </summary>
		/// <returns>xyz���̉�]��</returns>
		virtual vector3<position_type> rotate_xyz() const {
			return _rotation;
		}

		/// <summary>
		/// ��]�ʂ̎擾
		/// </summary>
		/// <returns>xy���̉�]��</returns>
		virtual point<position_type> rotate() const {
			return point<position_type> {
				static_cast<position_type>(_rotation.x),
					static_cast<position_type>(_rotation.y)
			};
		}

		/// <summary>
		/// ���S���W�̎擾
		/// </summary>
		/// <returns>xyz��Ԃ̒��S���W</returns>
		virtual vector3<position_type> center_xyz() const {
			return _center;
		}

		/// <summary>
		/// ���S���W�̎擾
		/// </summary>
		/// <returns>xy��Ԃ̒��S���W</returns>
		virtual point<position_type> center() const {
			return point<position_type> {
				static_cast<position_type>(_center.x),
					static_cast<position_type>(_center.y)
			};
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		virtual font colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		virtual font& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// �t�H���g�̑傫����ς���
		/// </summary>
		/// <param name="size">�ύX��̑傫��</param>
		virtual font resized(float size)&& {
			this->_size = size;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// �t�H���g�̑傫����ς���
		/// </summary>
		/// <param name="size">�ύX��̑傫��</param>
		virtual font& resized(float size)& {
			this->_size = size;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// ��`�̃T�C�Y���擾
		/// </summary>
		/// <returns>��`�̃T�C�Y</returns>
		virtual suika::rect rect() const;
		/// <summary>
		/// �t�H���g�̐F���擾
		/// </summary>
		/// <returns>�t�H���g�̐F</returns>
		virtual color_f color() const {
			return this->_color;
		}
	};
} // namespace suika