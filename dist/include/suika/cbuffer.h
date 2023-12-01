// -----------------------------------------------------------
// 
// constant buffer
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

#include "def.h"
#include "point.h"
#include "type.h"
#include "matrix.h"

namespace suika {
	struct cbuffer_default {
		matrix4x4<float> mt;
	};

	cbuffer_default set_view(const point<int>& window_size);

	void set_cbuffer(uint constant_size, void* constant, uint index);
}