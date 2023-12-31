#include "info.hpp"
#include "xaudio.hpp"

namespace suika {
	namespace d3d {
		namespace xaudio {
			void play_source(IXAudio2SourceVoice* source_voice, string path, float volume, float pan, sample_data play_sample, loop_data loop, XAUDIO2_VOICE_DETAILS detail) {
				source_voice->SetVolume(volume);
				panning(pan, source_voice, detail.InputChannels, mastering_detail.InputChannels);
				XAUDIO2_BUFFER buffer = {};
				buffer.AudioBytes = (UINT32)wav_data[path].audioBytes;
				buffer.pAudioData = wav_data[path].startAudio;
				buffer.PlayBegin = play_sample.begin;
				buffer.PlayLength = play_sample.length;
				if (loop.type != loop_type::none) {
					buffer.LoopBegin = loop.sample.begin;
					buffer.LoopLength = loop.sample.length;
					buffer.LoopCount = loop.type == loop_type::infinite ? XAUDIO2_LOOP_INFINITE : loop.count;
				}
				buffer.Flags = XAUDIO2_END_OF_STREAM;
				auto er = source_voice->SubmitSourceBuffer(&buffer);
				if (FAILED(er)) {
					log_d3d.error("Failed to SubmitSourceBuffer.");
					log_d3d.result(er);
					log.error(std::format("音声:{}の再生に失敗", path));
					return;
				}
				er = source_voice->Start();
				if (FAILED(er)) {
					log_d3d.error("Failed to audio start.");
					log_d3d.result(er);
					log.error(std::format("音声:{}の再生に失敗", path));
					return;
				}
			}

            sound_effect::sound_effect(sound_effect&& s) noexcept{
                if (is_init) {
					if (is_init) {
						s.stop();
						_source_voice = std::move(s._source_voice);
						_volume = s._volume;
						_pan = s._pan;
					}
                }
            }

			sound_effect::~sound_effect() {
				if (is_init) {
					destroy();
				}
			}

			void sound_effect::attach_mixer(IXAudio2SourceVoice* source_voice) {
				if (is_init && _is_load && _mixer != nullptr && source_voice != nullptr) {
					XAUDIO2_SEND_DESCRIPTOR send_descriptor = { .Flags = 0, .pOutputVoice = _mixer->_submix_voice };
					XAUDIO2_VOICE_SENDS send_list = { .SendCount = 1, .pSends = &send_descriptor };
					auto er = source_voice->SetOutputVoices(&send_list);
					if (FAILED(er)) {
						log_d3d.error("Failed to SetOutputVoices.");
						log_d3d.result(er);
						log.error(std::format("音声:{}のミキサー割り当てに失敗", _path));
						return;
					}
				}
			}

			void sound_effect::load(string path) {
				_path = path;
				if (is_init) {
					_is_load = load_audio(path, _data);
					if(!_is_load) {
						log.error(std::format("音声:{}の読み込みに失敗", path));
					}
				}
			}

			void sound_effect::mixer(submix_voice* mixer) {
				_mixer = mixer;
			}

			void sound_effect::volume(float volume) {
				_volume = volume;
			}

			void sound_effect::pan(float pan) {
				_pan = (pan + 1.0f) / 4.0f * (float)M_PI;
			}

			void sound_effect::play() {
				if (is_init && _is_load) {
					for (auto& v : _source_voice) {
						if (v != nullptr) {
							XAUDIO2_VOICE_STATE state;
							v->GetState(&state);
							if (state.BuffersQueued > 0) {
								continue;
							}
							v->DestroyVoice();
							v = nullptr;
						}
					}

					std::erase_if(_source_voice, [](auto& v) { return v == nullptr; });

					_source_voice.push_back(nullptr);
					auto& source_voice = this->_source_voice.back();
					
					auto er = p_xaudio->CreateSourceVoice(&source_voice, wav_data[_path].wfx);
					if (FAILED(er)) {
						log_d3d.error("Failed to CreateSourceVoice.");
						log_d3d.result(er);
						return;
					}
					source_voice->GetVoiceDetails(&_details);
					attach_mixer(source_voice);
					
					play_source(source_voice, _path, _volume, _pan, _play_sample, _loop_data, _details);
				}
			}

			bool sound_effect::is_playing() {
				if (is_init && _is_load) {
					for (auto& v : _source_voice) {
						if (v != nullptr) {
							XAUDIO2_VOICE_STATE state;
							v->GetState(&state);
							if (state.BuffersQueued > 0) {
								return true;
							}
						}
					}
				}
				return false;
			}

			void sound_effect::stop() {
				if (is_init) {
					for (auto& v : _source_voice) {
						if (v != nullptr) {
							v->Stop();
							v->DestroyVoice();
							v = nullptr;
						}
					}
					_source_voice.resize(0);
				}
			}

			void sound_effect::destroy() {
				if (is_init) {
					stop();
					_path.clear();
					_data.reset();
					_is_load = false;
				}
			}
		}
	}
}