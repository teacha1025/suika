// -----------------------------------------------------------
// 
// vertex
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
	/// トポロジー
	/// </summary>
	enum primitive_topology {
		//! 未定義
		PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
		//! 点のリスト
		PRIMITIVE_TOPOLOGY_POINTLIST = 1,
		//! 線のリスト
		PRIMITIVE_TOPOLOGY_LINELIST = 2,
		//! ラインストリップ
		PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
		//! 三角形リスト
		PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
		//! 三角形ストリップ
		PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
		//! 隣接関係を持つラインリスト
		PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
		//! 隣接関係を持つラインストリップ
		PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
		//! 隣接関係を持つ三角形リスト
		PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
		//! 隣接関係を持つ三角形ストリップ
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
		/// 頂点の作成
		/// </summary>
		/// <param name="pos">頂点座標</param>
		/// <param name="col">色</param>
		/// <param name="uv">UV値</param>
		/// <returns>頂点</returns>
		vertex_2d create_2d(const float4& pos, const color_f& col, const float2& uv);

		/// <summary>
		/// 頂点の作成
		/// </summary>
		/// <param name="pos">頂点座標</param>
		/// <param name="col">色</param>
		/// <param name="uv">UV値</param>
		/// <returns>頂点</returns>
		vertex_2d create_2d(const float2& pos, const color_f& col, const float2& uv);

		/// <summary>
		/// 頂点の作成
		/// </summary>
		/// <param name="pos">頂点座標</param>
		/// <param name="col">色</param>
		/// <param name="uv">UV値</param>
		/// <returns>頂点</returns>
		vertex_2d create_2d(const float3& pos, const color_f& col, const float2& uv);
		
		/// <summary>
		/// ポリゴンの描画
		/// </summary>
		/// <param name="vertices">描画するポリゴンの頂点データ</param>
		/// <param name="index">ポリゴンのインデックス</param>
		/// <param name="topology">描画のトポロジー</param>
		void draw(const std::vector<vertex_2d>& vertices, const std::vector<uint16>& index, primitive_topology topology);
	}
}
