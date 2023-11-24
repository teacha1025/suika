#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_CONCEPT
#define _SK_CONCEPT
#include <concepts>
#include "magic_enum.hpp"
#include "def.h"
#include "base.h"

namespace suika {
	namespace concepts {
		/// <summary>
		/// ベースクラスを継承しているか
		/// </summary>
		template<class T>
		concept is_based =
			requires(T t) {
				// requires(typeid(&t).before(typeid(detail::ibase*)) == true); // not constexpr
				t.to_string();
			};

		/// <summary>
		/// 数値型
		/// </summary>
		template<typename T>
		concept numbers = std::is_arithmetic_v<T>;

		/// <summary>
		/// 文字列型
		/// </summary>
		template<class T>
		concept string = std::is_convertible_v<T, std::string_view>;

		template <class Type>
		concept trivially = std::is_trivially_copyable_v<Type>;

		/// <summary>
		/// 列挙型
		/// </summary>
		template<class T>
		concept enum_elements = std::is_enum_v<T>;
	} // namespace concepts
} // namespace suika
#endif