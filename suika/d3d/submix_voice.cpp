#include "info.hpp"
#include "xaudio.hpp"

namespace suika{
	namespace d3d{
		namespace xaudio{
			submix_voice::submix_voice(){
				if(is_init){
					HRESULT hr;
					if (FAILED(hr = p_xaudio->CreateSubmixVoice(&_submix_voice, 1, 44100, 0, 0, nullptr, nullptr))) {
						log_d3d.error("Failed to create submix voice.");
						log_d3d.result(hr);
						_submix_voice = nullptr;
						return;
					}
				}
				_submix_voice = nullptr;
			}

			submix_voice::submix_voice(submix_voice&& s) noexcept{
				if(is_init){
					_submix_voice = std::move(s._submix_voice);
					_volume = s._volume;
					_pan = s._pan;
					s._submix_voice = nullptr;
				}
				_submix_voice = nullptr;
			}
			submix_voice::~submix_voice() {
				destroy();
			}

			void submix_voice::destroy() {
				if (is_init) {
					if (_submix_voice) {
						_submix_voice->DestroyVoice();
						_submix_voice = nullptr;
					}
				}
			}

			void submix_voice::volume(float volume) {
				if (is_init && _volume != volume) {
					_volume = volume;
					if (_submix_voice) {
						_submix_voice->SetVolume(volume);
					}
				}
			}

			void submix_voice::pan(float pan) {
				if (is_init && _pan != pan) {
					_pan = pan;
					pan = (pan + 1.0f) / 4.0f * (float)M_PI;
					panning(pan, _submix_voice, mastering_detail.InputChannels, mastering_detail.InputChannels);
				}
			}
		}
	}
}