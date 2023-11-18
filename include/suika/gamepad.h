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
		XInput,
		//! DirectInputで入力処理
		DirectInput,
		//! ゲームパッドは未接続、あるいは使用不可
		Disable
	};
	/// <summary>
	/// ゲームパッド入力に関する定義及び関数
	/// </summary>
	namespace gamepad {
		/// <summary>
		/// ゲームパッドに関する情報
		/// </summary>
		struct info {
			/// <summary>
			/// ゲームパッドのID
			/// </summary>
			ubyte		index = 255;

			/// <summary>
			/// 接続の種類
			/// </summary>
			pad_states	states = pad_states::Disable;

			/// <summary>
			/// デバイス名
			/// </summary>
			string		name;

			/// <summary>
			/// PID
			/// </summary>
			string		pid;

			/// <summary>
			/// VID
			/// </summary>
			string		vid;
		};
	}
	/// <summary>
	/// 内部的な実装
	/// </summary>
	namespace detail {
		class gamepad;
		class gamepad_trigger;
		class gamepad_stick;

		/// <summary>
		/// ゲームパッドのボタン
		/// </summary>
		class gamepad_button : public input_base {
			ubyte _id = 0;
			ulong _xcode = 0;
			ulong _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

			friend gamepad;
			friend gamepad_trigger;
			friend gamepad_stick;
			void update_trigger(double value);
		public:
			gamepad_button(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id);
			gamepad_button() {}
			void update();
			/// <summary>
			/// 名前を取得
			/// </summary>
			/// <returns>ボタンの名前</returns>
			virtual string to_string() const override;
		};
		/// <summary>
		/// ゲームパッドのスティック
		/// </summary>
		class gamepad_stick : public input_base {
		private:
			point<double>   _value;
			gamepad_button button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ulong _xcode = 0;
			ulong _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

			friend gamepad;
			friend gamepad_trigger;
			friend gamepad_button;
		public:
			gamepad_stick(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id);
			gamepad_stick() {}
			void update();

			/// <summary>
			/// スティックの入力値の取得
			/// </summary>
			/// <returns>横:x[-1~1] 縦:y[-1~1]</returns>
			point<double> value() const {
				return _value;
			}

			/// <summary>
			/// 押された時間の取得
			/// </summary>
			/// <returns>スティックが押し込まれたフレーム数</returns>
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

			/// <summary>
			/// 名前を取得
			/// </summary>
			/// <returns>スティックの名前</returns>
			virtual string to_string() const override;
		};
		/// <summary>
		/// ゲームパッドのトリガー
		/// </summary>
		class gamepad_trigger : public input_base {
		private:
			double		  _value = 0;
			gamepad_button _button;
			ubyte		   _id = 0;
			range<0.0, 1.0> _deadzone = 0.05;
			ulong _xcode = 0;
			ulong _dcode = 0;
			string _dname = "";
			bool _is_use_xinput = true;

			friend gamepad;
			friend gamepad_button;
			friend gamepad_stick;
		public:
			gamepad_trigger(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id);
			gamepad_trigger() {}
			void update();

			/// <summary>
			/// トリガーの入力値の取得
			/// </summary>
			/// <returns>解放:0 押下:1</returns>
			double value() const {
				return _value;
			}

			/// <summary>
			/// 押された時間の取得
			/// </summary>
			/// <returns>キーやボタンが押されたフレーム数</returns>
			unsigned int count() const override {
				return _button.count();
			}

			/// <summary>
			/// 押されているかどうかの取得
			/// </summary>
			/// <returns>押されているかどうか</returns>
			bool press() const override {
				return _button.press();
			}

			/// <summary>
			/// 離されているのかどうかの取得
			/// </summary>
			/// <returns>離されているかどうか</returns>
			bool release() const override {
				return _button.release();
			}

			/// <summary>
			/// 離されたかどうかの取得
			/// </summary>
			/// <returns>離された瞬間かどうか</returns>
			bool up() const override {
				return _button.up();
			}

			/// <summary>
			/// 押されたかどうかの取得
			/// </summary>
			/// <returns>押された瞬間かどうか</returns>
			bool down() const override {
				return _button.down();
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
			/// <returns>入力を検知するまでの閾値(デッドゾーン)</returns>
			double threshold() const {
				return _deadzone;
			}

			/// <summary>
			/// 名前を取得
			/// </summary>
			/// <returns>トリガーの名前</returns>
			virtual string to_string() const override;
		};
		/// <summary>
		/// ゲームパッド
		/// </summary>
		class gamepad {
		private:
			ubyte	  _id = 255;
			//pad_states _states = pad_states::Disable;
			//string _name;

			friend void init(gamepad& gp, ubyte id, suika::gamepad::info info);
			friend void update(gamepad& gp);
			suika::gamepad::info _info;
			bool _is_use_xinput = true;
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
				return _info.states;
			}

			/// <summary>
			/// 現在押されているボタンを取得
			/// </summary>
			/// <returns>ボタンへの参照を返す</returns>
			std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

			/// <summary>
			/// 現在の情報を取得する
			/// </summary>
			/// <returns>ゲームパッドの情報</returns>
			suika::gamepad::info info() const{
				return _info;
			}

			/// <summary>
			/// xinputに対応している場合、入力処理にxinputを使用するか設定
			/// </summary>
			/// <param name="flag">xinputを使用するか</param>
			void enable_xinput(bool flag) {
				_is_use_xinput = flag;
				A._is_use_xinput = flag;
				B._is_use_xinput = flag;
				X._is_use_xinput = flag;
				Y._is_use_xinput = flag;

				Up._is_use_xinput = flag;
				Down._is_use_xinput = flag;
				Left._is_use_xinput = flag;
				Right._is_use_xinput = flag;

				Start._is_use_xinput = flag;
				Back._is_use_xinput = flag;

				LShoulder._is_use_xinput = flag;
				RShoulder._is_use_xinput = flag;

				LStick._is_use_xinput = flag;
				RStick._is_use_xinput = flag;

				LStick.button._is_use_xinput = flag;
				RStick.button._is_use_xinput = flag;

				LTrigger._is_use_xinput = flag;
				RTrigger._is_use_xinput = flag;
			}

			/// <summary>
			/// ゲームパッドの名前を取得
			/// </summary>
			/// <returns>デバイス名+製品名</returns>
			string to_string() const{
				return _info.name;
			}
		};
	} // namespace detail

	/// <summary>
	/// ゲームパッド入力に関する定義及び関数
	/// </summary>
	namespace gamepad {
		define MAX_JOYPAD_NUM = 16;
		

		/// <summary>
		/// 接続されているゲームパッドを再更新する
		/// </summary>
		void load_gamepads();

		/// <summary>
		/// ゲームパッド(0~15)
		/// </summary>
		extern std::array<detail::gamepad, MAX_JOYPAD_NUM> pad;
		/// <summary>
		/// 現在押されているボタンを取得
		/// </summary>
		/// <returns>ボタンへの参照を返す</returns>
		//std::vector<std::reference_wrapper<detail::gamepad_button>> pressed_button();

	} // namespace gamepad
}