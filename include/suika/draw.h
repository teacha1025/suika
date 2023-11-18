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
	/// 内部的な実装
	/// </summary>
	namespace detail {
		/// <summary>
		/// 描画系クラス
		/// </summary>
		template<class T>
		class ishape : public ibase {
		protected:
			using position_type = float;
			//原点からの移動量
			vector3<position_type> _transition;

			//オブジェクトの描画、回転の中心
			vector3<position_type> _center;

			//回転量
			vector3<position_type> _rotation;

			//拡大率
			vector3<double> _extend;
			
			//ブレンド
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

			//設定系

			/// <summary>
			/// 座標を設定
			/// </summary>
			/// <param name="position">設定する座標</param>
			virtual T at(const vector3<position_type>& position)&& {
				_transition = position;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 座標を設定
			/// </summary>
			/// <param name="position">設定する座標</param>
			virtual T& at(const vector3<position_type>& position)& {
				_transition = position;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// 座標を設定
			/// </summary>
			/// <param name="position">設定する座標</param>
			virtual T at(const point<position_type>& position)&& {
				_transition = vector3<position_type>{ position.x, position.y, 0.0 };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 座標を設定
			/// </summary>
			/// <param name="position">設定する座標</param>
			virtual T& at(const point<position_type>& position)& {
				_transition = vector3<position_type>{ position.x, position.y, 0.0 };
				return static_cast<T&>(*this);
			}

			/// <summary>
			/// オブジェクトの中心を設定
			/// </summary>
			/// <param name="center">設定する中心座標</param>
			virtual T centered(const vector3<position_type>& center)&& {
				_center = center;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// オブジェクトの中心を設定
			/// </summary>
			/// <param name="center">設定する中心座標</param>
			virtual T& centered(const vector3<position_type>& center)& {
				_center = center;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// オブジェクトの中心を設定
			/// </summary>
			/// <param name="center">設定する中心座標</param>
			virtual T centered(const point<position_type>& center)&& {
				_center = vector3<position_type>{ center.x, center.y, 0.0 };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// オブジェクトの中心を設定
			/// </summary>
			/// <param name="center">設定する中心座標</param>
			virtual T& centered(const point<position_type>& center)& {
				_center = vector3<position_type>{ center.x, center.y, 0.0 };
				return dynamic_cast<T&>(*this);
			}

			/// <summary>
			/// 回転量の設定
			/// </summary>
			/// <param name="center">設定する各軸の回転量</param>
			virtual T rotated(const vector3<position_type>& rotation)&& {
				_rotation = rotation;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 回転量の設定
			/// </summary>
			/// <param name="center">設定する各軸の回転量</param>
			virtual T& rotated(const vector3<position_type>& rotation)& {
				_rotation = rotation;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// 回転量の設定
			/// </summary>
			/// <param name="center">設定する回転量</param>
			virtual T rotated(const position_type& rotation)&& {
				_rotation.z = rotation;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 回転量の設定
			/// </summary>
			/// <param name="center">設定する回転量</param>
			virtual T& rotated(const position_type& rotation)& {
				_rotation.z = rotation;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// 拡大率の設定
			/// </summary>
			/// <param name="rate">拡大率</param>
			virtual T extended(const vector3<double>& rate)&& {
				_extend = rate;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 拡大率の設定
			/// </summary>
			/// <param name="rate">拡大率</param>
			virtual T& extended(const vector3<double>& rate)& {
				_extend = rate;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// 拡大率の設定
			/// </summary>
			/// <param name="rate">拡大率</param>
			virtual T extended(const point<double>& rate)&& {
				_extend = { rate.x, rate.y, 1 };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 拡大率の設定
			/// </summary>
			/// <param name="rate">拡大率</param>
			virtual T& extended(const point<double>& rate)& {
				_extend = { rate.x, rate.y, 1 };
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// 拡大率の設定
			/// </summary>
			/// <param name="rate">拡大率</param>
			virtual T extended(double rate)&& {
				_extend = { rate, rate, rate };
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 拡大率の設定
			/// </summary>
			/// <param name="rate">拡大率</param>
			virtual T& extended(double rate)& {
				_extend = { rate, rate, rate };
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// ブレンドの設定
			/// </summary>
			/// <param name="type">ブレンドの種類</param>
			virtual T blended(blend type)&& {
				_blend = type;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ブレンドの設定
			/// </summary>
			/// <param name="type">ブレンドの種類</param>
			virtual T& blended(blend type)& {
				_blend = type;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// 頂点シェーダーの設定
			/// </summary>
			/// <param name="shader">シェーダーの名前</param>
			virtual T vs(const string& shader)&& {
				_shaders.vs = shader;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// 頂点シェーダーの設定
			/// </summary>
			/// <param name="shader">シェーダーの名前</param>
			virtual T& vs(const string& shader)& {
				_shaders.vs = shader;
				return static_cast<T&>(*this);
			}
			/// <summary>
			/// ピクセルシェーダーの設定
			/// </summary>
			/// <param name="shader">シェーダーの名前</param>
			virtual T ps(const string& shader)&& {
				_shaders.ps = shader;
				return static_cast<T&&>(std::move(*this));
			}
			/// <summary>
			/// ピクセルシェーダーの設定
			/// </summary>
			/// <param name="shader">シェーダーの名前</param>
			virtual T& ps(const string& shader)& {
				_shaders.ps = shader;
				return static_cast<T&>(*this);
			}

			//取得系

			/// <summary>
			/// オブジェクトの原点からの移動量を取得
			/// </summary>
			/// <returns>xyz空間の移動量</returns>
			virtual vector3<position_type> position_xyz() const {
				return _transition;
			}
			/// <summary>
			/// オブジェクトの原点からの移動量を取得
			/// </summary>
			/// <returns>xy平面の移動量</returns>
			virtual point<position_type> position() const {
				return point<position_type> {
					static_cast<position_type>(_transition.x),
						static_cast<position_type>(_transition.y)
				};
			}

			/// <summary>
			/// 拡大率の取得
			/// </summary>
			/// <returns>xyz方向の拡大率</returns>
			virtual vector3<position_type> extend_xyz() const {
				return _extend;
			}

			/// <summary>
			/// 拡大率の取得
			/// </summary>
			/// <returns>xy方向への拡大率</returns>
			virtual point<position_type> extend() const {
				return point<position_type> {
					static_cast<position_type>(_extend.x),
						static_cast<position_type>(_extend.y)
				};
			}

			/// <summary>
			/// 回転量の取得
			/// </summary>
			/// <returns>xyz軸の回転量</returns>
			virtual vector3<position_type> rotate_xyz() const {
				return _rotation;
			}

			/// <summary>
			/// 回転量の取得
			/// </summary>
			/// <returns>xy軸の回転量</returns>
			virtual point<position_type> rotate() const {
				return point<position_type> {
					static_cast<position_type>(_rotation.x),
						static_cast<position_type>(_rotation.y)
				};
			}

			/// <summary>
			/// 中心座標の取得
			/// </summary>
			/// <returns>xyz空間の中心座標</returns>
			virtual vector3<position_type> center_xyz() const {
				return _center;
			}

			/// <summary>
			/// 中心座標の取得
			/// </summary>
			/// <returns>xy空間の中心座標</returns>
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