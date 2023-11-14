#pragma once
#include <vector>
#include <array>
#include "point.h"
#include "def.h"
#include "type.h"
#include "range.h"
#include "input_base.h"

namespace suika {
	/// <summary>
	/// ゲームパッドの状態
	/// </summary>
	enum class pad_states {
		//! XInputで入力処理
		xinput,
		//! DirectInputで入力処理
		direct_input,
		//! ゲームパッドは未接続、あるいは使用不可
		disable
	};
	namespace detail {
		class gamepad_button : public input_base {
			ubyte _id = 0;
			ubyte _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;
		public:
			gamepad_button(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id);
			gamepad_button() {}
			void update();
		};
		class gamepad_stick : public input_base {
		private:
			point<double>   _value;
			gamepad_button button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ubyte _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;
		public:
			gamepad_stick(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id);
			gamepad_stick() {}
			void update();

			/// <summary>
			/// スティックの入力値の取得
			/// </summary>
			/// <returns>横:x[-1~1] 縦:y[-1~1]</returns>
			point<double> value() const;

			/// <summary>
			/// 押された時間の取得
			/// </summary>
			/// <returns>キーやボタンが押されたフレーム数</returns>
			unsigned int count() const override {
				return button.count();
			}

			/// <summary>
			/// 押されているかどうかの取得
			/// </summary>
			/// <returns>押されているかどうか</returns>
			bool press() const override {
				return button.press();
			}

			/// <summary>
			/// 離されているのかどうかの取得
			/// </summary>
			/// <returns>離されているかどうか</returns>
			bool release() const override {
				return button.release();
			}

			/// <summary>
			/// 離されたかどうかの取得
			/// </summary>
			/// <returns>離された瞬間かどうか</returns>
			bool up() const override {
				return button.up();
			}

			/// <summary>
			/// 押されたかどうかの取得
			/// </summary>
			/// <returns>押された瞬間かどうか</returns>
			bool down() const override {
				return button.down();
			}

			/// <summary>
			/// 閾値を設定する
			/// </summary>
			/// <param name="value">新しい閾値</param>
			void threshold(range<0.0, 1.0> value) {
				_deadzone = value;
			}

			/// <summary>
			/// 現在の閾値を取得
			/// </summary>
			/// <returns></returns>
			double threshold() const {
				return _deadzone;
			}
		};
		class gamepad_trigger : public input_base {
		private:
			double		  _value = 0;
			gamepad_button _button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ubyte _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

		public:
			gamepad_trigger(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id);
			gamepad_trigger() {}
			void update();

			/// <summary>
			/// トリガーの入力値の取得
			/// </summary>
			/// <returns>解放:0 押下:1</returns>
			double value() const;

			/// <summary>
			/// 押された時間の取得
			/// </summary>
			/// <returns>キーやボタンが押されたフレーム数</returns>
			unsigned int count() const override {
				return button.count();
			}

			/// <summary>
			/// 押されているかどうかの取得
			/// </summary>
			/// <returns>押されているかどうか</returns>
			bool press() const override {
				return button.press();
			}

			/// <summary>
			/// 離されているのかどうかの取得
			/// </summary>
			/// <returns>離されているかどうか</returns>
			bool release() const override {
				return button.release();
			}

			/// <summary>
			/// 離されたかどうかの取得
			/// </summary>
			/// <returns>離された瞬間かどうか</returns>
			bool up() const override {
				return button.up();
			}

			/// <summary>
			/// 押されたかどうかの取得
			/// </summary>
			/// <returns>押された瞬間かどうか</returns>
			bool down() const override {
				return button.down();
			}

			/// <summary>
			/// 閾値を設定する
			/// </summary>
			/// <param name="value">新しい閾値</param>
			void threshold(range<0.0, 1.0> value) {
				_deadzone = value;
			}

			/// <summary>
			/// 現在の閾値を取得
			/// </summary>
			/// <returns></returns>
			double threshold() const {
				return _deadzone;
			}
		};

		class gamepad {
		private:
			ubyte	  ID = 255;
			pad_states states = pad_states::disable;

			friend void init(gamepad& gp, ubyte id);
			friend void update(gamepad& gp);

		public:
			/// <summary>
			/// 十字上
			/// </summary>
			gamepad_button Up;

			/// <summary>
			/// 十字下
			/// </summary>
			gamepad_button Down;

			/// <summary>
			/// 十字左
			/// </summary>
			gamepad_button Left;

			/// <summary>
			/// 十字右
			/// </summary>
			gamepad_button Right;

			/// <summary>
			/// スタートボタン
			/// </summary>
			gamepad_button Start;

			/// <summary>
			/// バックボタン
			/// </summary>
			gamepad_button Back;

			/// <summary>
			/// LBボタン
			/// </summary>
			gamepad_button LShoulder;

			/// <summary>
			/// RBボタン
			/// </summary>
			gamepad_button RShoulder;

			/// <summary>
			/// 左スティック
			/// </summary>
			gamepad_stick LStick;

			/// <summary>
			/// 右スティック
			/// </summary>
			gamepad_stick RStick;

			/// <summary>
			/// 左トリガー
			/// </summary>
			gamepad_trigger LTrigger;

			/// <summary>
			/// 右トリガー
			/// </summary>
			gamepad_trigger RTrigger;

			/// <summary>
			/// Aボタン
			/// </summary>
			gamepad_button A;

			/// <summary>
			/// Bボタン
			/// </summary>
			gamepad_button B;

			/// <summary>
			/// Xボタン
			/// </summary>
			gamepad_button X;

			/// <summary>
			/// Yボタン
			/// </summary>
			gamepad_button Y;

			/// <summary>
			/// ゲームパッドの状態
			/// </summary>
			/// <returns>現在の処理状態</returns>
			pad_states states() const {
				return states;
			}

			/// <summary>
			/// 現在押されているボタンを取得
			/// </summary>
			/// <returns>ボタンへの参照を返す</returns>
			std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

			/// <summary>
			/// ゲームパッドの名前を取得
			/// </summary>
			/// <returns>デバイス名+製品名</returns>
			string to_string();
		};
	} // namespace detail
	namespace gamepad {
		define MAX_JOYPAD_NUM = 16;
		struct info {
			ubyte		index = 255;
			pad_states	states = pad_states::disable;
			string		name;
			string		pid;
			string		vid;
		};


		void load_gamepads();

		/// <summary>
		/// ゲームパッド(0~15)
		/// </summary>
		//extern std::array<detail::gamepad, MAX_JOYPAD_NUM> pad;
		/// <summary>
		/// 現在押されているボタンを取得
		/// </summary>
		/// <returns>ボタンへの参照を返す</returns>
		//std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

	} // namespace gamepad
}