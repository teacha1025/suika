#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_INCLUDE
#define _SK_INCLUDE
#include "../include/suika/logger.h"
#include "../include/suika/window.h"

#include "../include/suika/shader.h"
#include "../include/suika/vertex.h"
#include "../include/suika/cbuffer.h"
#include "../include/suika/blend.h"

#include "../include/suika/color.h"
#include "../include/suika/pallet.h"
#include "../include/suika/string.h"
#include "../include/suika/string_function.h"

#include "../include/suika/texture.h"

#ifdef _DEBUG
#pragma comment(lib, "suika_d.lib")
#else
#pragma comment(lib, "suika.lib")
#endif
#endif