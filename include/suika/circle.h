// -----------------------------------------------------------
// 
// circle
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#pragma once

#include "draw.h"
#include "vertex.h"
#include "palette.h"

namespace suika {
	/// <summary>
	/// �~�`�N���X
	/// </summary>
	class circle : public detail::ishape<circle> {
	protected:
		float _radius = 64;
		uint16 _resolution = 64;
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// �~�̍쐬
		/// </summary>
		/// <param name="r">�~�̔��a</param>
		circle(float r) : _radius(r) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
			_resolution = (uint16)r;
		}

		/// <summary>
		/// �~��`�悷��
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		virtual circle colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�h��Ԃ��̐F</param>
		virtual circle& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// ���a��ς���
		/// </summary>
		/// <param name="r">�ύX��̔��a</param>
		virtual circle resized(float r)&& {
			this->_radius = r;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// ���a��ς���
		/// </summary>
		/// <param name="r">�ύX��̑傫��</param>
		virtual circle& resized(float r)& {
			this->_radius = r;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// �`��̕���\��ݒ�
		/// </summary>
		/// <param name="r">������</param>
		virtual circle resolution(uint16 r)&& {
			this->_resolution = r;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// �`��̕���\��ݒ�
		/// </summary>
		/// <param name="r">������</param>
		virtual circle& resolution(uint16 r)& {
			this->_resolution = r;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// �~�̔��a���擾
		/// </summary>
		/// <returns>���a</returns>
		virtual float radius() const {
			return this->_radius;
		}

		/// <summary>
		/// �~�̐F���擾
		/// </summary>
		/// <returns>�~�̐F</returns>
		virtual color_f color() const {
			return this->_color;
		}

		virtual point<position_type> offset() const;
		virtual vector3<position_type> offset_xyz() const;

		/// <summary>
		/// �`��̕���\���擾
		/// </summary>
		/// <returns>����\</returns>
		virtual uint16 resolution() const {
			return this->_resolution;
		}
	};
}