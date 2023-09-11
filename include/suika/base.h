#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_BASE
#define _SK_BASE
#include <string>
#include "def.h"
#include "string.h"

namespace suika {
	namespace detail {
		class ibase {
		public:
			constexpr ibase() {}
			string to_string() const;
			//virtual ~ibase() {};
		};
	} // namespace detail
} // namespace suika
#endif