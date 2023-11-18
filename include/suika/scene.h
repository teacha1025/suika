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
		/// �V�[���؂�ւ��̎��Ɏ��s
		/// </summary>
		virtual void init() {};
		/// <summary>
		/// ���t���[�����s�����X�V�֐�
		/// </summary>
		virtual void update() {}
		/// <summary>
		/// ���t���[�����s�����`��֐�
		/// </summary>
		virtual void draw() {};
		/// <summary>
		/// �t�F�[�h�C�����Ɏ��s�����`��֐�
		/// </summary>
		/// <param name="time">�o�ߎ���</param>
		virtual void fadein(double time) {};
		/// <summary>
		/// �t�F�[�h�A�E�g���Ɏ��s�����`��֐�
		/// </summary>
		/// <param name="time">�o�ߎ���</param>
		virtual void fadeout(double time) {};
		/// <summary>
		/// �V�[���I���̎��ɌĂяo�����֐�
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
			none,//�t�F�[�h���Ă��Ȃ�
			fadein,//�t�F�[�h�C����
			fadeout,//�t�F�[�h�A�E�g��
			fade,//�t�F�[�h�C���ƃt�F�[�h�A�E�g�𓯎��ɍs��
		} _fade_state = fade_state::none;

		double _fade_time = 0;

		bool _is_fade_sametime = false;
		bool _is_scene_pushed = false;
	public:
		/// <summary>
		/// �V�����V�[����o�^����
		/// </summary>
		/// <typeparam name="Scene">iscene���p�������V�[���N���X</typeparam>
		/// <typeparam name="...Args">�V�[���N���X�̃R���X�g���N�^�̈���</typeparam>
		/// <param name="fadeout_time">�t�F�[�h�A�E�g���鎞��</param>
		/// <param name="fadein_time">�t�F�[�h�C�����鎞��</param>
		/// <param name="is_fade_sametime">�t�F�[�h�C���ƃt�F�[�h�A�E�g�𓯎��ɍs����</param>
		/// <param name="...arg">�V�[���N���X�̃R���X�g���N�^�̈���</param>
		/// <remarks>�t�F�[�h�𓯎��ɍs���ꍇ�A�t�F�[�h���Ԃ�fadeout_time���̗p����</remarks>
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
		/// �O�̃V�[���ɖ߂�
		/// </summary>
		/// <param name="fadeout_time">�t�F�[�h�A�E�g���鎞��</param>
		/// <param name="fadein_time">�t�F�[�h�C�����鎞��</param>
		/// <param name="is_fade_sametime">�t�F�[�h�C���ƃt�F�[�h�A�E�g�𓯎��ɍs����</param>
		/// <remarks>�t�F�[�h�𓯎��ɍs���ꍇ�A�t�F�[�h���Ԃ�fadeout_time���̗p����</remarks>
		void back(double fadeout_time, double fadein_time, bool is_fade_sametime);

		/// <summary>
		/// �V�[���̍X�V
		/// </summary>
		void update();

		/// <summary>
		/// �V�[���̕`��
		/// </summary>
		void draw();
	};
}