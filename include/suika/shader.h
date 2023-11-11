#pragma once
#include "def.h"
#include "string.h"
namespace suika {
	const string SHAPE_VERTEX = "shape";
	const string SHAPE_PIXEL  = "shape";
	const string TEXTURE_VERTEX = "texture";
	const string TEXTURE_PIXEL  = "texture";

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