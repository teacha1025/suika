#pragma once

namespace suika {
	/// <summary>
	/// ブレンドの種類
	/// </summary>
	enum class blend {
		//! ノーブレンド
		none = 0,
		//! αブレンド
		alpha = 1,
		//! 加算ブレンド
		add = 2,
		//! 減算ブレンド
		sub = 3,
		//! 乗算ブレンド
		mul = 4,
		//! カラーは更新されない
		dest = 5,
		//! 描画先の色の反転値を掛ける
		inv_dest = 6,
		//! 描画元の色を反転する
		inv_src = 7,
		//! アルファチャンネル考慮付き乗算ブレンド
		mul_alpha = 8,
		//! 乗算済みαブレンドモードのαブレンド
		pma_alpha = 9,
		//! 乗算済みαブレンドモードの加算ブレンド
		pma_add = 10,
		//! 乗算済みαブレンドモードの減算ブレンド
		pma_sub = 11,
		//! 乗算済みαブレンドモードの描画元の色を反転する
		pma_inv_src = 12,
	};
}