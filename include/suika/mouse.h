#pragma once
#include "point.h"
#include "window.h"
#include "input_base.h"

namespace suika {
	namespace detail {
		class _mouse : public input_base {
		public:
			_mouse(unsigned int code, string name);
			_mouse() {}
			void update();
		};
	}
	/// <summary>
	/// キー入力の定義及び関数
	/// </summary>
	namespace mouse {
		/// <summary>
		/// 左ボタン
		/// </summary>
		extern detail::_mouse Left;

		/// <summary>
		/// 中ボタン
		/// </summary>
		extern detail::_mouse Middle;

		/// <summary>
		/// 右ボタン
		/// </summary>
		extern detail::_mouse Right;

		extern detail::_mouse Button4;
		extern detail::_mouse Button5;
		extern detail::_mouse Button6;
		extern detail::_mouse Button7;
		extern detail::_mouse Button8;

		/// <summary>
		/// マウスカーソルの位置を取得
		/// </summary>
		/// <returns>カーソルの位置</returns>
		point<int> position(window::id id = window::default_id);

		/// <summary>
		/// マウスカーソルの位置を設定
		/// </summary>
		/// <param name="p">カーソルの位置</param>
		void position(const point<int>& p);

		point<int> delta_position(window::id id = window::default_id);

		int wheel();
	}
}