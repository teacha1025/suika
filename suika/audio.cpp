#include "d3d/xaudio.hpp"

#include "../include/suika/audio.h"

namespace xaudio = suika::d3d::xaudio;

namespace suika {
	namespace audio {
		sound_effect::sound_effect(const string& path):detail::iaudio(path) {
			if (xaudio::is_init) {
				xaudio::se_list[path].load(path);
			}
		}

		void sound_effect::play() {
			if (xaudio::is_init) {
				xaudio::se_list[_path].play();
			}
		}

		void sound_effect::stop() {
			if (xaudio::is_init) {
				xaudio::se_list[_path].stop();
			}
		}

		void sound_effect::volume(float volume) {
			if (xaudio::is_init) {
				_volume = volume;
				_decibel = powf(10.0f, volume / 20.0f);
				xaudio::se_list[_path].volume(volume);
			}
		}

		void sound_effect::decibel(float decibel) {
			if (xaudio::is_init) {
				_decibel = decibel;
				_volume = 20.0f * log10f(decibel);
				xaudio::se_list[_path].decibel(decibel);
			}
		}

		void sound_effect::pan(float pan) {
			if (xaudio::is_init) {
				_pan = pan;
				xaudio::se_list[_path].pan(pan);
			}
		}

		bool sound_effect::is_playing() {
			if (xaudio::is_init) {
				return xaudio::se_list[_path].is_playing();
			}
			return false;
		}

		bgm::bgm(const string& path) :detail::iaudio(path) {
			if (xaudio::is_init) {
				xaudio::bgm_list[path].load(path);
			}
		}

		void bgm::play() {
			if (xaudio::is_init) {
				xaudio::bgm_list[_path].play();
			}
		}

		void bgm::stop() {
			if (xaudio::is_init) {
				xaudio::bgm_list[_path].stop();
			}
		}

		void bgm::volume(float volume) {
			if (xaudio::is_init) {
				_volume = volume;
				_decibel = powf(10.0f, volume / 20.0f);
				xaudio::bgm_list[_path].volume(volume);
			}
		}

		void bgm::decibel(float decibel) {
			if (xaudio::is_init) {
				_decibel = decibel;
				_volume = 20.0f * log10f(decibel);
				xaudio::bgm_list[_path].decibel(decibel);
			}
		}

		void bgm::pan(float pan) {
			if (xaudio::is_init) {
				_pan = pan;
				xaudio::bgm_list[_path].pan(pan);
			}
		}

		bool bgm::is_playing() {
			if (xaudio::is_init) {
				return xaudio::bgm_list[_path].is_playing();
			}
			return false;
		}
	}
}