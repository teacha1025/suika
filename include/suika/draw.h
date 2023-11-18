#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_DRAW
#define _SK_DRAW
#include "point.h"
#include "def.h"
#include "string.h"
#include "blend.h"
#include "vertex.h"

namespace suika {
	/// <summary>
	/// �����I�Ȏ���
	/// </summary>
	namespace detail {
		/// <summary>
		/// �`��n�N���X
		/// </summary>
		template<class T>
		class ishape : public ibase {
		protected:
			using position_type = float;
			//���_����̈ړ���
			vector3<position_type> _transition;

			//�I�u�W�F�N�g�̕`��A��]�̒��S
			vector3<position_type> _center;

			//��]��
			vector3<position_type> _rotation;

			//�g�嗦
			vector3<double> _extend;
			
			//�u�����h
			blend _blend;

			struct shaders {
				string vs;
				string ps;
			} _shaders;

			virtual std::vector<suika::vertex::vertex_2d> create_vertex() = 0;
		public:
			constexpr ishape() :
				_transition({ 0, 0, 0 }),
				_center({ 0, 0, 0 }),
				_rotation({ 0, 0, 0 }),
				_extend({ 1.0, 1.0, 1.0 }),
				_blend(blend::none){}

			//virtual string to_string() const = 0;

			//�ݒ�n

			/// <summary>
			/// ���W��ݒ�
			/// </summary>
			/// <param name="position">�ݒ肷����W</param>
			virtual T at(const vector3<position_type>& position)&& {
				_transition = position;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ���W��ݒ�
			/// </summary>
			/// <param name="position">�ݒ肷����W</param>
			virtual T& at(const vector3<position_type>& position)& {
				_transition = position;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// ���W��ݒ�
			/// </summary>
			/// <param name="position">�ݒ肷����W</param>
			virtual T at(const point<position_type>& position)&& {
				_transition = vector3<position_type>{ position.x, position.y, 0.0 };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ���W��ݒ�
			/// </summary>
			/// <param name="position">�ݒ肷����W</param>
			virtual T& at(const point<position_type>& position)& {
				_transition = vector3<position_type>{ position.x, position.y, 0.0 };
				return static_cast<T&>(*this);
			}

			/// <summary>
			/// �I�u�W�F�N�g�̒��S��ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷�钆�S���W</param>
			virtual T centered(const vector3<position_type>& center)&& {
				_center = center;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �I�u�W�F�N�g�̒��S��ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷�钆�S���W</param>
			virtual T& centered(const vector3<position_type>& center)& {
				_center = center;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// �I�u�W�F�N�g�̒��S��ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷�钆�S���W</param>
			virtual T centered(const point<position_type>& center)&& {
				_center = vector3<position_type>{ center.x, center.y, 0.0 };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �I�u�W�F�N�g�̒��S��ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷�钆�S���W</param>
			virtual T& centered(const point<position_type>& center)& {
				_center = vector3<position_type>{ center.x, center.y, 0.0 };
				return dynamic_cast<T&>(*this);
			}

			/// <summary>
			/// ��]�ʂ̐ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷��e���̉�]��</param>
			virtual T rotated(const vector3<position_type>& rotation)&& {
				_rotation = rotation;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ��]�ʂ̐ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷��e���̉�]��</param>
			virtual T& rotated(const vector3<position_type>& rotation)& {
				_rotation = rotation;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// ��]�ʂ̐ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷���]��</param>
			virtual T rotated(const position_type& rotation)&& {
				_rotation.z = rotation;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ��]�ʂ̐ݒ�
			/// </summary>
			/// <param name="center">�ݒ肷���]��</param>
			virtual T& rotated(const position_type& rotation)& {
				_rotation.z = rotation;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// �g�嗦�̐ݒ�
			/// </summary>
			/// <param name="rate">�g�嗦</param>
			virtual T extended(const vector3<double>& rate)&& {
				_extend = rate;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �g�嗦�̐ݒ�
			/// </summary>
			/// <param name="rate">�g�嗦</param>
			virtual T& extended(const vector3<double>& rate)& {
				_extend = rate;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// �g�嗦�̐ݒ�
			/// </summary>
			/// <param name="rate">�g�嗦</param>
			virtual T extended(const point<double>& rate)&& {
				_extend = { rate.x, rate.y, 1 };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �g�嗦�̐ݒ�
			/// </summary>
			/// <param name="rate">�g�嗦</param>
			virtual T& extended(const point<double>& rate)& {
				_extend = { rate.x, rate.y, 1 };
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// �g�嗦�̐ݒ�
			/// </summary>
			/// <param name="rate">�g�嗦</param>
			virtual T extended(double rate)&& {
				_extend = { rate, rate, rate };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �g�嗦�̐ݒ�
			/// </summary>
			/// <param name="rate">�g�嗦</param>
			virtual T& extended(double rate)& {
				_extend = { rate, rate, rate };
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// �u�����h�̐ݒ�
			/// </summary>
			/// <param name="type">�u�����h�̎��</param>
			virtual T blended(blend type)&& {
				_blend = type;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �u�����h�̐ݒ�
			/// </summary>
			/// <param name="type">�u�����h�̎��</param>
			virtual T& blended(blend type)& {
				_blend = type;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// ���_�V�F�[�_�[�̐ݒ�
			/// </summary>
			/// <param name="shader">�V�F�[�_�[�̖��O</param>
			virtual T vs(const string& shader)&& {
				_shaders.vs = shader;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ���_�V�F�[�_�[�̐ݒ�
			/// </summary>
			/// <param name="shader">�V�F�[�_�[�̖��O</param>
			virtual T& vs(const string& shader)& {
				_shaders.vs = shader;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// �s�N�Z���V�F�[�_�[�̐ݒ�
			/// </summary>
			/// <param name="shader">�V�F�[�_�[�̖��O</param>
			virtual T ps(const string& shader)&& {
				_shaders.ps = shader;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// �s�N�Z���V�F�[�_�[�̐ݒ�
			/// </summary>
			/// <param name="shader">�V�F�[�_�[�̖��O</param>
			virtual T& ps(const string& shader)& {
				_shaders.ps = shader;
				return static_cast<T&>(*this);
			}

			//�擾�n

			/// <summary>
			/// �I�u�W�F�N�g�̌��_����̈ړ��ʂ��擾
			/// </summary>
			/// <returns>xyz��Ԃ̈ړ���</returns>
			virtual vector3<position_type> position_xyz() const {
				return _transition;
			}
			/// <summary>
			/// �I�u�W�F�N�g�̌��_����̈ړ��ʂ��擾
			/// </summary>
			/// <returns>xy���ʂ̈ړ���</returns>
			virtual point<position_type> position() const {
				return point<position_type> {
					static_cast<position_type>(_transition.x),
						static_cast<position_type>(_transition.y)
				};
			}

			/// <summary>
			/// �g�嗦�̎擾
			/// </summary>
			/// <returns>xyz�����̊g�嗦</returns>
			virtual vector3<position_type> extend_xyz() const {
				return _extend;
			}

			/// <summary>
			/// �g�嗦�̎擾
			/// </summary>
			/// <returns>xy�����ւ̊g�嗦</returns>
			virtual point<position_type> extend() const {
				return point<position_type> {
					static_cast<position_type>(_extend.x),
						static_cast<position_type>(_extend.y)
				};
			}

			/// <summary>
			/// ��]�ʂ̎擾
			/// </summary>
			/// <returns>xyz���̉�]��</returns>
			virtual vector3<position_type> rotate_xyz() const {
				return _rotation;
			}

			/// <summary>
			/// ��]�ʂ̎擾
			/// </summary>
			/// <returns>xy���̉�]��</returns>
			virtual point<position_type> rotate() const {
				return point<position_type> {
					static_cast<position_type>(_rotation.x),
						static_cast<position_type>(_rotation.y)
				};
			}

			/// <summary>
			/// ���S���W�̎擾
			/// </summary>
			/// <returns>xyz��Ԃ̒��S���W</returns>
			virtual vector3<position_type> center_xyz() const {
				return _center;
			}

			/// <summary>
			/// ���S���W�̎擾
			/// </summary>
			/// <returns>xy��Ԃ̒��S���W</returns>
			virtual point<position_type> center() const {
				return point<position_type> {
					static_cast<position_type>(_center.x),
						static_cast<position_type>(_center.y)
				};
			}

			virtual void draw() = 0;

			string to_string() const {
				return std::format("at:{}, rotation:{}, center:{}, extend:{}", _transition.to_string().to_string(), _rotation.to_string().to_string(), _center.to_string().to_string(), _extend.to_string().to_string());
			}
		};
	} // namespace detail
} // namespace suika
#endif