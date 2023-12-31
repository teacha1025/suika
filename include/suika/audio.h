// -----------------------------------------------------------
// 
// audio
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
#include "string.h"

namespace suika{
    namespace detail {
        class iaudio {
        protected:
            string _path;
            float _volume = 1.0f, _pan = 0.0f, _decibel = 0.0f;
        public:
            iaudio(const string& path) :_path(path) {}
            virtual ~iaudio() {}

            virtual void play() = 0;
            virtual void stop() = 0;
            virtual void volume(float volume) = 0;
            virtual void decibel(float volume) = 0;
            virtual void pan(float pan) = 0;
            virtual bool is_playing() = 0;
        };
    }
    namespace audio{
        class sound_effect : public detail::iaudio{
        public:
            sound_effect() :detail::iaudio("") {}
            sound_effect(const string& path);
            void play() override;
            void stop() override;
            void volume(float volume) override;
            void decibel(float volume) override;
            void pan(float pan) override;
            bool is_playing() override;
        };

        class bgm : public detail::iaudio{
        public:
            bgm() :detail::iaudio("") {}
            bgm(const string& path);
            void play() override;
            void stop() override;
            void volume(float volume) override;
            void decibel(float volume) override;
            void pan(float pan) override;
            bool is_playing() override;
        };
    }
}