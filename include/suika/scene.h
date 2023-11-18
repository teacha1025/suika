#pragma once
#include <functional>
#include <stack>
#include "def.h"
#include "base.h"
#include "font.h"

namespace suika {
	class scene_manager;
	class iscene {
	private:
		friend scene_manager;
	protected:
		scene_manager* _p_manager;
	public:
		/// <summary>
		/// シーン切り替えの時に実行
		/// </summary>
		virtual void init() {};
		/// <summary>
		/// 毎フレーム実行される更新関数
		/// </summary>
		virtual void update() {}
		/// <summary>
		/// 毎フレーム実行される描画関数
		/// </summary>
		virtual void draw() {};
		/// <summary>
		/// フェードイン時に実行される描画関数
		/// </summary>
		/// <param name="time">経過時間</param>
		virtual void fadein(double time) {};
		/// <summary>
		/// フェードアウト時に実行される描画関数
		/// </summary>
		/// <param name="time">経過時間</param>
		virtual void fadeout(double time) {};
		/// <summary>
		/// シーン終了の時に呼び出される関数
		/// </summary>
		virtual void fin() {};
		virtual ~iscene() = default;
	};

	class scene_manager {
	private:
		struct scene_data {
			std::function<void(double)> fadein;
			double fadein_time;
			std::function<void(double)> fadeout;
			double fadeout_time;
		} _data;

		std::stack<std::unique_ptr<iscene>> _scenes;
		std::unique_ptr<iscene> _next_scene, _now_scene;

		enum class change_state {
			none,
			change,
			back,
		} _change_state;

		enum class fade_state {
			none,//フェードしていない
			fadein,//フェードイン中
			fadeout,//フェードアウト中
			fade,//フェードインとフェードアウトを同時に行う
		} _fade_state = fade_state::none;

		double _fade_time = 0;

		bool _is_fade_sametime = false;
		bool _is_scene_pushed = false;
	public:
		/// <summary>
		/// 新しいシーンを登録する
		/// </summary>
		/// <typeparam name="Scene">isceneを継承したシーンクラス</typeparam>
		/// <typeparam name="...Args">シーンクラスのコンストラクタの引数</typeparam>
		/// <param name="fadeout_time">フェードアウトする時間</param>
		/// <param name="fadein_time">フェードインする時間</param>
		/// <param name="is_fade_sametime">フェードインとフェードアウトを同時に行うか</param>
		/// <param name="...arg">シーンクラスのコンストラクタの引数</param>
		/// <remarks>フェードを同時に行う場合、フェード時間はfadeout_timeを採用する</remarks>
		template<class Scene, class... Args>
		void change(double fadeout_time, double fadein_time, bool is_fade_sametime, Args... arg) {
			_next_scene.reset((iscene*)(new Scene(arg...)));
			_next_scene->_p_manager = this;
			_change_state = change_state::change;
			_fade_state = fade_state::none;
			if (_now_scene != nullptr) {
				_data = scene_data{ std::bind(&iscene::fadein, *_next_scene, std::placeholders::_1), fadein_time, std::bind(&iscene::fadeout, *_now_scene, std::placeholders::_1)  , fadeout_time };
			}
			else {
				_data = scene_data{ std::bind(&iscene::fadein, *_next_scene, std::placeholders::_1), fadein_time, [](double) {} , fadeout_time };
			}
			_fade_time = 0;
			_is_fade_sametime = is_fade_sametime;
		}

		/// <summary>
		/// 前のシーンに戻る
		/// </summary>
		/// <param name="fadeout_time">フェードアウトする時間</param>
		/// <param name="fadein_time">フェードインする時間</param>
		/// <param name="is_fade_sametime">フェードインとフェードアウトを同時に行うか</param>
		/// <remarks>フェードを同時に行う場合、フェード時間はfadeout_timeを採用する</remarks>
		void back(double fadeout_time, double fadein_time, bool is_fade_sametime);

		/// <summary>
		/// シーンの更新
		/// </summary>
		void update();

		/// <summary>
		/// シーンの描画
		/// </summary>
		void draw();
	};
}