// -----------------------------------------------------------
// 
// suika engine include file
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

#include <format>

#include "../include/suika/vector.h"
#include "../include/suika/matrix.h"
#include "../include/suika/system.h"
#include "../include/suika/logger.h"
#include "../include/suika/window.h"

#include "../include/suika/shader.h"
#include "../include/suika/vertex.h"
#include "../include/suika/cbuffer.h"
#include "../include/suika/blend.h"

#include "../include/suika/filesystem.h"
#include "../include/suika/text_reader.h"
#include "../include/suika/text_writer.h"
#include "../include/suika/binary_writer.h"
#include "../include/suika/binary_reader.h"

#include "../include/suika/color.h"
#include "../include/suika/palette.h"
#include "../include/suika/string.h"
#include "../include/suika/string_function.h"

#include "../include/suika/texture.h"
#include "../include/suika/animation.h"
#include "../include/suika/animator.h"

#include "../include/suika/font.h"
#include "../include/suika/rect.h"
#include "../include/suika/circle.h"
#include "../include/suika/line.h"

#include "../include/suika/keyboard.h"
#include "../include/suika/mouse.h"
#include "../include/suika/gamepad.h"

#include "../include/suika/scene.h"

#include "../include/suika/easing.h"

#include "../include/suika/audio.h"

#include "../include/suika/task.h"
#include "../include/suika/collision.h"

#include "../include/suika/magic_enum.hpp"

#ifdef _DEBUG
#pragma comment(lib, "suika_d.lib")
#else
#pragma comment(lib, "suika.lib")
#endif
