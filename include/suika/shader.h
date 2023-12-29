// -----------------------------------------------------------
// 
// shader
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
#include "string.h"
namespace suika {
	const string SHAPE_VERTEX = "suika_shader_internal_shape";
	const string SHAPE_PIXEL  = "suika_shader_internal_shape";
	const string TEXTURE_VERTEX = "suika_shader_internal_texture";
	const string TEXTURE_PIXEL  = "suika_shader_internal_texture";

	/// <summary>
	/// HLSLファイルからバーテックスシェーダーを作成
	/// </summary>
	/// <param name="key_input">シェーダーファイルへのパス</param>
	/// <param name="name">シェーダーの登録名</param>
	void add_vs(const string& key_input, const string& name);

	/// <summary>
	/// シェーダー配列からバーテックスシェーダーを作成
	/// </summary>
	/// <param name="key_input">シェーダー配列</param>
	/// <param name="size">シェーダー配列の要素数</param>
	/// <param name="name">シェーダーの登録名</param>
	void add_vs(const void* key_input, size_t size, const string& name);

	/// <summary>
	/// HLSLファイルからピクセルシェーダーを作成
	/// </summary>
	/// <param name="key_input">シェーダーファイルへのパス</param>
	/// <param name="name">シェーダーの登録名</param>
	void add_ps(const string& key_input, const string& name);

	/// <summary>
	/// シェーダー配列からピクセルシェーダーを作成
	/// </summary>
	/// <param name="key_input">シェーダー配列</param>
	/// <param name="size">シェーダー配列の要素数</param>
	/// <param name="name">シェーダーの登録名</param>
	void add_ps(const void* key_input, size_t size, const string& name);

	/// <summary>
	/// バーテックスシェーダーを設定する
	/// </summary>
	/// <param name="name">シェーダーの登録名</param>
	void set_vs(const string& name);

	/// <summary>
	/// ピクセルシェーダーを設定する
	/// </summary>
	/// <param name="name">シェーダーの登録名</param>
	void set_ps(const string& name);

}
