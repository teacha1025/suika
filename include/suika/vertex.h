#pragma once
#include "def.h"
#include "point.h"
#include "color.h"

namespace suika {
	using float2 = vector2<float>;
	using float3 = vector3<float>;
	using float4 = vector4<float>;
	using double2 = vector2<double>;
	using double3 = vector3<double>;
	using double4 = vector4<double>;
	struct color_v {
		float r, g, b, a;
	};
	/// <summary>
	/// �g�|���W�[
	/// </summary>
	enum primitive_topology {
		//! ����`
		PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
		//! �_�̃��X�g
		PRIMITIVE_TOPOLOGY_POINTLIST = 1,
		//! ���̃��X�g
		PRIMITIVE_TOPOLOGY_LINELIST = 2,
		//! ���C���X�g���b�v
		PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
		//! �O�p�`���X�g
		PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
		//! �O�p�`�X�g���b�v
		PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
		//! �אڊ֌W�������C�����X�g
		PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
		//! �אڊ֌W�������C���X�g���b�v
		PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
		//! �אڊ֌W�����O�p�`���X�g
		PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
		//! �אڊ֌W�����O�p�`�X�g���b�v
		PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
	};
	namespace vertex {
		
		struct vertex_2d {
			float4 position;
			color_v color;
			float2 uv;
			//float2 dummy;

			bool operator == (const vertex_2d& v) const {
				return this->position.x == v.position.x && this->position.y == v.position.y && this->position.z == v.position.z && this->position.w == v.position.w
					&& this->color.r == v.color.r && this->color.g == v.color.g && this->color.b == v.color.b && this->color.a == v.color.a
					&& this->uv.x == v.uv.x && this->uv.y == v.uv.y;
			}
		};
		/// <summary>
		/// ���_�̍쐬
		/// </summary>
		/// <param name="pos">���_���W</param>
		/// <param name="col">�F</param>
		/// <param name="uv">UV�l</param>
		/// <returns>���_</returns>
		vertex_2d create_2d(const float4& pos, const color_f& col, const float2& uv);
		/// <summary>
		/// ���_�̍쐬
		/// </summary>
		/// <param name="pos">���_���W</param>
		/// <param name="col">�F</param>
		/// <param name="uv">UV�l</param>
		/// <returns>���_</returns>
		vertex_2d create_2d(const float2& pos, const color_f& col, const float2& uv);
		/// <summary>
		/// ���_�̍쐬
		/// </summary>
		/// <param name="pos">���_���W</param>
		/// <param name="col">�F</param>
		/// <param name="uv">UV�l</param>
		/// <returns>���_</returns>
		vertex_2d create_2d(const float3& pos, const color_f& col, const float2& uv);
		
		/// <summary>
		/// �|���S���̕`��
		/// </summary>
		/// <param name="vertices">�`�悷��|���S���̒��_�f�[�^</param>
		/// <param name="index">�|���S���̃C���f�b�N�X</param>
		/// <param name="topology">�`��̃g�|���W�[</param>
		void draw(const std::vector<vertex_2d>& vertices, const std::vector<uint16>& index, primitive_topology topology);
	}
}