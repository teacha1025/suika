#include "info.hpp"
#include "xaudio.hpp"

namespace suika {
	namespace d3d {
		namespace xaudio {
			bgm::bgm(bgm&& s) noexcept {
				if (is_init) {
					if (is_init) {
						s.stop();
						_source_voice = std::move(s._source_voice);
						_volume = s._volume;
						_pan = s._pan;
					}
				}
			}

			bgm::~bgm() {
				if (is_init) {
					destroy();
				}
			}

			void bgm::load(string path) {
				_path = path;
				if (is_init) {
					_is_load = load_audio(path, _data);
					if (!_is_load) {
						log.error(std::format("音声:{}の読み込みに失敗", path));
					}
					if (_is_load) {
						if (_source_voice) {
							_source_voice->DestroyVoice();
							_source_voice = nullptr;
						}
						_source_voice = nullptr;
						auto er = p_xaudio->CreateSourceVoice(&_source_voice, wav_data[_path].wfx);
						if (FAILED(er)) {
							_source_voice = nullptr;
							log_d3d.error("Failed to create source voice.");
							log_d3d.result(er);
							log.error(std::format("音声:{}の読み込みに失敗", path));
							return;
						}
						if (_source_voice) {
							_source_voice->GetVoiceDetails(&_details);
						}
					}
				}
			}

			void bgm::mixer(submix_voice* mixer) {
				if(is_init && _is_load && _source_voice) {
					XAUDIO2_SEND_DESCRIPTOR send_descriptor = { .Flags = 0, .pOutputVoice = mixer->_submix_voice };
					XAUDIO2_VOICE_SENDS send_list = { .SendCount = 1, .pSends = &send_descriptor };
					_source_voice->SetOutputVoices(&send_list);
				}
			}

			void bgm::volume(float volume) {
				if(is_init && _is_load && _source_voice && _volume != volume) {
					_volume = volume;
					_source_voice->SetVolume(volume);
				}
			}

			void bgm::pan(float pan) {
				if (is_init && _is_load && _source_voice && _pan != pan) {
					_pan = pan;
					pan = (pan + 1.0f) / 4.0f * (float)M_PI;
					panning(pan, _source_voice, _details.InputChannels, mastering_detail.InputChannels);
				}
			}

			void bgm::play() {
				if (is_init && _is_load && _source_voice) {
					play_source(_source_voice, _path, _volume, _pan, _play_sample, _loop_data, _details);
				}
			}

			bool bgm::is_playing() {
				if (is_init && _is_load && _source_voice) {
					XAUDIO2_VOICE_STATE state;
					_source_voice->GetState(&state);
					if (state.BuffersQueued > 0) {
						return true;
					}
				}
				return false;
			}

			void bgm::stop() {
				if (is_init && _is_load && _source_voice) {
					_source_voice->Stop();
				}
			}

			void bgm::destroy() {
				if (is_init && _is_load) {
					stop();
					if (_source_voice) {
						_source_voice->DestroyVoice();
						_source_voice = nullptr;
					}
					_path.clear();
					_data.reset();
					_is_load = false;
				}
			}
		}
	}
}