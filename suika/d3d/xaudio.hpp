// -----------------------------------------------------------
// 
// xaudio
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

#define XAUDIO2_HELPER_FUNCTIONS

#include <windows.h>
#include <xaudio2.h>
#include <wrl/client.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "therd_party/xaudio/WAVFileReader.h"
#include "therd_party/ogg/ogg.h"
#include "therd_party/ogg/os_types.h"
#include "therd_party/vorbis/codec.h"
#include "therd_party/vorbis/vorbisfile.h"
#include "therd_party/vorbis/vorbisenc.h"

#include "../../include/suika/string.h"
#include "../../include/suika/def.h"


#ifdef _DEBUG
#pragma comment(lib, "third_party/ogg/libogg_d.lib")
#pragma comment(lib, "third_party/vorbis/libvorbis_static_d.lib")
#pragma comment(lib, "third_party/vorbis/libvorbisfile_static_d.lib")
#else
#pragma comment(lib, "third_party/ogg/libogg.lib")
#pragma comment(lib, "third_party/vorbis/libvorbis_static.lib")
#pragma comment(lib, "third_party/vorbis/libvorbisfile_static.lib")
#endif

namespace suika{
	namespace d3d{
		namespace xaudio{
			class submix_voice;
			class sound_effect;
			class bgm;

			extern Microsoft::WRL::ComPtr<IXAudio2> p_xaudio;
			extern IXAudio2MasteringVoice* p_master_voice;
			extern std::unordered_map<string, DirectX::WAVData> wav_data;
			extern std::unordered_map<string, sound_effect> se_list;
			extern std::unordered_map<string, bgm> bgm_list;
			extern XAUDIO2_VOICE_DETAILS mastering_detail;
			extern bool is_init;           

			class isound{
			protected:
				float _volume = 1.0f;
				float _pan = 0.25f * PI_F;
			};

			class ivoice : public isound{
			protected:

			public:
				virtual void volume(float volume) = 0;
				virtual void decibel(float volume){
					this->volume(powf(10.0f, volume / 20.0f));
				}
				virtual void pan(float pan) = 0;
				virtual void destroy() = 0;
			};
			
			enum class loop_type {
				none,
				count,
				infinite
			};

			struct sample_data {
				uint begin = 0;
				uint length = 0;
			};

			struct loop_data {
				loop_type type = loop_type::none;
				sample_data sample;
				int count = -1;
			};

			class isouce : public ivoice{
			protected:
				string _path;
				std::unique_ptr<uint8_t[]> _data;
				XAUDIO2_VOICE_DETAILS _details = {};

				sample_data _play_sample;

				loop_data _loop_data;

				bool _is_load = false;
			public:
				virtual void mixer(submix_voice* mixer) = 0;
				virtual void play() = 0;
				virtual void stop() = 0;
				virtual bool is_playing() = 0;

				virtual void load(string path) = 0;

				virtual void play_sample(uint begin, uint length) {
					_play_sample.begin = begin;
					_play_sample.length = length;
				}

				virtual void loop(loop_type type, uint begin = 0, uint length = 0, int count = -1) {
					_loop_data.type = type;
					_loop_data.sample.begin = begin;
					_loop_data.sample.length = length;
					_loop_data.count = count;
				}
			};

			class submix_voice : public ivoice{
			private:
				IXAudio2SubmixVoice* _submix_voice;
				friend sound_effect;
				friend bgm;
			public:
				submix_voice();
				submix_voice(const submix_voice& s) = delete;
				submix_voice(submix_voice&& s) noexcept;
				virtual ~submix_voice();
				virtual void volume(float volume) override;
				virtual void pan(float pan) override;
				virtual void destroy() override;

			};

			void play_source(IXAudio2SourceVoice* source_voice, string path, float volume, float pan, sample_data play_sample, loop_data loop, XAUDIO2_VOICE_DETAILS detail);

			class sound_effect : public isouce{
			private:
				std::vector<IXAudio2SourceVoice*> _source_voice;
				submix_voice* _mixer = nullptr;
				virtual void attach_mixer(IXAudio2SourceVoice* v);
			public:
				sound_effect(){};
				sound_effect(const sound_effect& s) = delete;
				sound_effect(sound_effect&& s) noexcept;
				~sound_effect();
				virtual void load(string path) override;
				virtual void mixer(submix_voice* mixer) override;
				virtual void volume(float volume) override;
				virtual void pan(float pan) override;
				virtual void play() override;
				virtual void stop() override;
				virtual bool is_playing() override;
				virtual void destroy() override;
			};

			class bgm : public isouce{
			private:
				IXAudio2SourceVoice* _source_voice = nullptr;
			public:
				bgm(){};
				bgm(const bgm& s) = delete;
				bgm(bgm&& s) noexcept;
				~bgm();
				virtual void load(string path) override;
				virtual void mixer(submix_voice* mixer) override;
				virtual void volume(float volume) override;
				virtual void pan(float pan) override;
				virtual void play() override;
				virtual void stop() override;
				virtual bool is_playing() override;
				virtual void destroy() override;
			};

			void init();

			void fin();

			void panning(float pan, IXAudio2SourceVoice* source_voice, UINT32 in, UINT32 out);

			void panning(float pan, IXAudio2SubmixVoice* source_voice, UINT32 in, UINT32 out);

			bool load_audio(string path, std::unique_ptr<uint8_t[]>& data);
		}
	}
}