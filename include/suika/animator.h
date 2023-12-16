// -----------------------------------------------------------
// 
// animator
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

#include <unordered_map>
#include <functional>

#include "def.h"
#include "base.h"
#include "draw.h"
#include "vertex.h"
#include "point.h"
#include "animation.h"


namespace suika {
	/// <summary>
	/// �A�j���[�V�����Đ����Ǘ�����N���X
	/// </summary>
	class animator : public detail::ishape<animator> {
	private:
		struct hash_pair {
			template<class T1, class T2>
			size_t operator()(const std::pair<T1, T2>& p) const {
				auto hash1 = std::hash<T1>{}(p.first);
				auto hash2 = std::hash<T2>{}(p.second);
				size_t seed = 0;
				seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				return seed;
			}
		};

		animation _anm;
		struct pattern {
			std::vector<uint> pattern;
			double interval = 1;
			bool loop = true;
			uint next = 0;
			bool _smooth = false;
		};
		std::unordered_map<uint, pattern> _pattern;

		std::unordered_map<std::pair<uint, uint>, std::pair<std::function<bool()>, bool>, hash_pair> _condition;

		uint _key = 0;

		point<bool> _turn;

		virtual std::vector<vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// �V�����A�j���[�^�[���쐬����
		/// </summary>
		animator() = default;

		/// <summary>
		/// �V�����A�j���[�^�[���쐬����
		/// </summary>
		/// <param name="path">�e�N�X�`���̃p�X</param>
		/// <param name="div">�c���̕�����</param>
		animator(string path, const point<uint>& div);

		/// <summary>
		/// �V�����A�j���[�^�[���쐬����
		/// </summary>
		/// <param name="path">�e�N�X�`���̃p�X</param>
		/// <param name="div">�c���̕�����</param>
		/// <param name="region_lt">�e�N�X�`���̍����UV</param>
		/// <param name="region_rb">�e�N�X�`���̉E����UV</param>
		animator(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb);

		/// <summary>
		/// �A�j���[�V�����̃p�^�[����ǉ�����
		/// </summary>
		/// <param name="key">�p�^�[���̎��ʃL�[</param>
		/// <param name="pattern">�Đ��̏���(�摜�̍��ォ��Z�̏���1,2,...)</param>
		/// <param name="interval">���̉摜�ɑJ�ڂ���܂ł̃J�E���g</param>
		/// <param name="resume">�Đ����I������Ƃ��ɁA���ɍĐ������p�^�[���̃L�[</param>
		void add(uint key, std::vector<uint> pattern, double interval, uint next);

		/// <summary>
		/// �A�j���[�V�����̃p�^�[����ǉ�����
		/// </summary>
		/// <param name="key">�p�^�[���̎��ʃL�[</param>
		/// <param name="pattern">�Đ��̏���(�摜�̍��ォ��Z�̏���1,2,...)</param>
		/// <param name="interval">���̉摜�ɑJ�ڂ���܂ł̃J�E���g</param>
		void add(uint key, std::vector<uint> pattern, double interval);

		/// <summary>
		/// ��������ŃA�j���[�V������J�ڂ�����
		/// </summary>
		/// <param name="from">�J�ڑO�̃A�j���[�V�����̃L�[</param>
		/// <param name="to">�J�ڐ�̃A�j���[�V�����̃L�[</param>
		/// <param name="cond">��������̊֐�</param>
		/// <param name="smooth">�؂�ւ������炩�ɍs����</param>
		/// <remarks>cond�́A����������bool��Ԃ����֐�</remarks>
		/// <remarks>�X���[�Y�Ȑ؂�ւ��͊ȈՓI�Ȃ��̂ł���A���S�ɃX���[�Y�ɍs����킯�ł͂Ȃ��ł�</remarks>
		void condition(uint from, uint to, std::function<bool()> cond, bool smooth = true);

		/// <summary>
		/// �e�N�X�`�����]���擾
		/// </summary>
		/// <returns>�e�����̔��]</returns>
		animator& turned(const point<bool>& turn)&;

		/// <summary>
		/// �e�N�X�`�����]���擾
		/// </summary>
		/// <returns>�e�����̔��]</returns>
		animator turned(const point<bool>& turn)&&;

		/// <summary>
		/// �A�j���[�V�������X�V����
		/// </summary>
		/// <param name="t">�ω�����</param>
		virtual void updated(double t);

		/// <summary>
		/// �Đ�����A�j���[�V�����̃L�[��ݒ肷��
		/// </summary>
		/// <param name="key">�A�j���[�V�����̃L�[</param>
		void set(uint key);

		/// <summary>
		/// �e�N�X�`���̗̈��������`���擾����
		/// </summary>
		/// <returns>�e�N�X�`���̗̈��������`</returns>
		rect rect() const;

		/// <summary>
		/// �A�j���[�V������`�悷��
		/// </summary>
		virtual void draw() override;
	};
}