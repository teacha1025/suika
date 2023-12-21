/** @example{lineno} font.hpp
 * ������`��̃T���v��
*/

// -----------------------------------------------------------
// 
// font draw.
// IO
namespace suika {
	/// <summary>
	/// �t�H���g�̔z�u
	/// </summary>
	enum class font_alignment {
		//! ���[����
		left = 0,
		//! �E�[����
		right = 1,
		//! ��������
		center = 2,
		//! ���[����
		justified = 3
	};

	/// <summary>
	/// �t�H���g�̕�
	/// </summary>
	enum class font_stretch {
		//! ����`
		undefined = 0,
		//! ���ɍ�
		ultra_condensed = 1,
		//! �ɍ�
		extra_condensed = 2,
		//! ��
		condensed = 3,
		//! ����
		semi_condensed = 4,
		//! �W��
		normal = 5,
		//! ����
		semi_expanded = 6,
		//! ��
		expanded = 7,
		//! �ɑ�
		extra_expanded = 8,
		//! ���ɑ�
		ultra_expanded = 9,
	};

	/// <summary>
	/// �t�H���g�̎Α�
	/// </summary>
	enum class font_style {
		//! �W��
		normal = 0,
		//! �Α�
		oblique = 1,
		//! �t�H���g�W���̎Α�
		italic = 2
	};

	/// <summary>
	/// �t�H���g�̑���
	/// </summary>
	enum class font_weight {
		//! ���ɍ�
		thin = 100,
		//! �ɍ�
		extra_light = 200,
		//! ��
		light = 300,
		//! ����
		semi_light = 350,
		//! �W��
		normal = 400,
		//! ����
		semi_bold = 600,
		//! ��
		bold = 700,
		//! �ɑ�
		extra_bold = 800,
		//! ���ɑ�
		heavy = 900,
		//! �ő�
		extra_heavy = 950
	};

	/// <summary>
	/// �t�H���g�`��Ɋւ���N���X
	/// </summary>
	class font : public detail::ibase {
	public:
		
	private:
		color_f _color;
		string _font;
		float _size;
		font_alignment _alignment;
		string _locale;
		font_stretch _stretch;
		font_style _style;
		font_weight _weight;

		uint32 _edge_width;
		color_f _edge_color;
		bool _edge_enabled;

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

		string create_key() const;
	public:
		/// <summary>
		/// �f�t�H���g�̃t�H���g���쐬
		/// </summary>
		font() {
			_color = palette::black;
			_size = 16;
			_alignment = font_alignment::left;
			_font = "���C���I";
			_locale = "";
			_stretch = font_stretch::normal;
			_style = font_style::normal;
			_weight = font_weight::normal;
			_text = "";
			_cid = window::canvas()->id;
			_blend = blend::none;

			_edge_color = palette::black;
			_edge_width = 0;
			_edge_enabled = false;
		}

		/// <summary>
		/// �t�H���g���쐬����
		/// </summary>
		/// <param name="font_name">�t�H���g��(e.g.���C���I)</param>
		/// <param name="size">�t�H���g�T�C�Y</param>
		/// <param name="edge">�t�H���g�̃G�b�W�ݒ�</param>
		/// <param name="edge_width">�t�H���g�̃G�b�W��(edge==false�Ȃ疳�������)</param>
		/// <param name="w">�t�H���g�̑���</param>
		/// <param name="s">�t�H���g�̎Α̐ݒ�</param>
		/// <param name="a">�t�H���g�̔z�u</param>
		/// <param name="st">�t�H���g�̕�</param>
		font(const string& font_name, float size = 16.0f, bool edge = false, int32 edge_width =1u, font_weight w = font_weight::normal, font_style s = font_style::normal, font_alignment a = font_alignment::left, font_stretch st = font_stretch::normal) {
			_color = palette::black;
			_size = size;
			_alignment = a;
			_font = font_name;
			_locale = "";
			_stretch = st;
			_style = s;
			_weight = w;
			_text = "";
			_cid = window::canvas()->id;
			_blend = blend::none;

			_edge_color = palette::black;
			_edge_width = edge_width;
			_edge_enabled = edge;

			if (edge) {
				if (edge_width <= 0) {
					_edge_enabled = false;
				}
				else if (edge_width > (_size / 3.0f)) {
					_edge_width = (uint32)(_size / 3.0f);
				}
				else {
					_edge_width = (uint32)edge_width;
				}
			}
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
		/// �t�H���g�̕ύX
		/// </summary>
		/// <param name="font_name">�t�H���g��</param>
		virtual font font_name(const string& font_name)&& {
			_font = font_name;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �t�H���g�̕ύX
		/// </summary>
		/// <param name="font_name">�t�H���g��</param>
		virtual font& font_name(const string& font_name)& {
			_font = font_name;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �t�H���g��
		/// </summary>
		/// <param name="stretch">��</param>
		virtual font stretch(font_stretch stretch)&& {
			_stretch = stretch;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �t�H���g��
		/// </summary>
		/// <param name="stretch">��</param>
		virtual font& stretch(font_stretch stretch)& {
			_stretch = stretch;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �t�H���g�̃X�^�C��
		/// </summary>
		/// <param name="style">�X�^�C��</param>
		virtual font style(font_style style)&& {
			_style = style;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �t�H���g�̃X�^�C��
		/// </summary>
		/// <param name="style">�X�^�C��</param>
		virtual font& style(font_style style)& {
			_style = style;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �t�H���g�̑���
		/// </summary>
		/// <param name="weight">����</param>				
		virtual font weight(font_weight weight)&& {
			_weight = weight;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �t�H���g�̑���
		/// </summary>
		/// <param name="weight">����</param>
		virtual font& weight(font_weight weight)& {
			_weight = weight;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �t�H���g�̔z�u
		/// </summary>
		/// <param name="alignment">�z�u</param>
		virtual font alignment(font_alignment alignment)&& {
			_alignment = alignment;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �t�H���g�̔z�u
		/// </summary>
		/// <param name="alignment">�z�u</param>
		virtual font& alignment(font_alignment alignment)& {
			_alignment = alignment;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �����̐ݒ�
		/// </summary>
		/// <param name="enabled">���������邩</param>
		/// <param name="width">���̑���</param>
		/// <remarks>width��0�ȉ��̏ꍇ�͉����͂���܂���</remarks>
		/// <remarks>���̑������t�H���g�̑�����1/3�ȉ��ƂȂ�܂��B</remarks>
		virtual font edged(bool enabled, int32 width = 0)&& {
			_edge_enabled = enabled;
			if (enabled) {
				if (width <= 0) {
					_edge_enabled = false;
				}
				else if (width > (_size / 3.0f)) {
					_edge_width = (uint32)(_size / 3.0f);
				}
				else {
					_edge_width = (uint32)width;
				}
			}
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �����̐ݒ�
		/// </summary>
		/// <param name="enabled">���������邩</param>
		/// <param name="width">���̑���</param>
		/// <remarks>width��0�ȉ��̏ꍇ�͉����͂���܂���</remarks>
		/// <remarks>���̑������t�H���g�̑�����1/3�ȉ��ƂȂ�܂��B</remarks>
		virtual font& edged(bool enabled, int32 width = 0)& {
			_edge_enabled = enabled;
			if (enabled) {
				if (width <= 0) {
					_edge_enabled = false;
				}
				else if (width > (_size / 3.0f)) {
					_edge_width = (uint32)(_size / 3.0f);
				}
				else {
					_edge_width = (uint32)width;
				}
			}
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="rotation">�ݒ肷��e���̉�]��</param>
		virtual font rotated(const vector3<position_type>& rotation)&& {
			_rotation = rotation;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="rotation">�ݒ肷��e���̉�]��</param>
		virtual font& rotated(const vector3<position_type>& rotation)& {
			_rotation = rotation;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="rotation">�ݒ肷���]��</param>
		virtual font rotated(const position_type& rotation)&& {
			_rotation.z = rotation;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// ��]�ʂ̐ݒ�
		/// </summary>
		/// <param name="rotation">�ݒ肷���]��</param>
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
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		/// <param name="a">�����x</param>
		virtual font colored(const color_f& color, float a)&& {
			this->_color = color_f(color, a);
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		/// <param name="a">�����x</param>
		virtual font& colored(const color_f& color, float a)& {
			this->_color = color_f(color, a);
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		/// <param name="edge">�G�b�W�̐F</param>
		virtual font colored(const color_f& color, const color_f& edge)&& {
			this->_color = color;
			this->_edge_color = edge;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		/// <param name="edge">�G�b�W�̐F</param>
		virtual font& colored(const color_f& color, const color_f& edge)& {
			this->_color = color;
			this->_edge_color = edge;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		/// <param name="edge">�G�b�W�̐F</param>
		/// <param name="a">�����x</param>
		virtual font colored(const color_f& color, const color_f& edge, float a)&& {
			this->_color = color_f(color, a);
			this->_edge_color = color_f(edge, a);
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		/// <param name="edge">�G�b�W�̐F</param>
		/// <param name="a">�����x</param>
		virtual font& colored(const color_f& color, const color_f& edge, float a)& {
			this->_color = color_f(color, a);
			this->_edge_color = color_f(edge, a);
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