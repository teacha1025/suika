#pragma once
#pragma once
#include "draw.h"
#include "vertex.h"
#include "palette.h"

namespace suika {
	/// <summary>
	/// �����N���X
	/// </summary>
	class line : public detail::ishape<line> {
	protected:
		point<float> _A, _B;
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		line() {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
		}
		/// <summary>
		///�@2�_��������쐬
		/// </summary>
		/// <param name="A">�n�_</param>
		/// <param name="B">�I�_</param>
		line(point<float> A, point<float> B) : _A(A), _B(B) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
		}

		/// <summary>
		/// ����1�̐�����`�悷��
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// ����b�̐�����`�悷��
		/// </summary>
		/// <param name="b">����</param>
		/// <param name="rounded">��[���ۂ߂邩</param>
		virtual void draw(float b, bool rounded);

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		virtual line colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<line&&>(std::move(*this));
		}
		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		virtual line& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<line&>(*this);
		}
		/// <summary>
		/// �����̓_��ݒ�
		/// </summary>
		/// <param name="A">�n�_</param>
		virtual line& A(const point<float>& A)& {
			this->_A = A;
			return static_cast<line&>(*this);
		}
		/// <summary>
		/// �����̓_��ݒ�
		/// </summary>
		/// <param name="A">�n�_</param>
		virtual line A(point<float>&& A)&& {
			this->_A = A;
			return static_cast<line&&>(std::move(*this));
		}
		/// <summary>
		/// �����̓_��ݒ�
		/// </summary>
		/// <param name="A">�I�_</param>
		virtual line& B(const point<float>& B)& {
			this->_B = B;
			return static_cast<line&>(*this);
		}
		/// <summary>
		/// �����̓_��ݒ�
		/// </summary>
		/// <param name="A">�I�_</param>
		virtual line B(point<float>&& B)&& {
			this->_B = B;
			return static_cast<line&&>(std::move(*this));
		}

		/// <summary>
		/// �����̐F���擾
		/// </summary>
		/// <returns>�����̐F</returns>
		virtual color_f color() const {
			return this->_color;
		}

		/// <summary>
		/// �����̓_���擾
		/// </summary>
		/// <returns>�n�_</returns>
		virtual point<float> A() const {
			return this->_A;
		}

		/// <summary>
		/// �����̓_���擾
		/// </summary>
		/// <returns>�I�_</returns>
		virtual point<float> B() const {
			return this->_B;
		}
	};
}