#include "info.hpp"
#include "xaudio.hpp"

namespace suika{
    namespace d3d{
        namespace xaudio{
            Microsoft::WRL::ComPtr<IXAudio2> p_xaudio;
            IXAudio2MasteringVoice* p_master_voice;
            std::unordered_map<string, DirectX::WAVData> wav_data;
            std::unordered_map<string, sound_effect> se_list;
            std::unordered_map<string, bgm> bgm_list;
            bool is_init = false;
            XAUDIO2_VOICE_DETAILS mastering_detail;

            void init(){
                HRESULT hr;

                UINT32 flags = 0;
            #if _WIN32_WINNT < _WIN32_WINNT_WIN8 
            #ifdef _DEBUG
                flags |= XAUDIO2_DEBUG_ENGINE;
            #endif
            #endif

                if (FAILED(hr = XAudio2Create(&p_xaudio, flags))) {
                    is_init = false;
					log_d3d.error("Failed to create XAudio instance.");
					log_d3d.result(hr);
					log.error("XAudio2の初期化に失敗");
                    return;
                }
            #ifdef _DEBUG
                XAUDIO2_DEBUG_CONFIGURATION debug{ 0 };
                debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
                debug.BreakMask = XAUDIO2_LOG_ERRORS;
                p_xaudio->SetDebugConfiguration(&debug, 0);
            #endif
                if (FAILED(hr = p_xaudio->CreateMasteringVoice(&p_master_voice))) {
                    is_init = false;
					log_d3d.error("Failed to create mastering voice.");
					log_d3d.result(hr);
					log.error("XAudio2の初期化に失敗");
                    return;
                }
                p_master_voice->GetVoiceDetails(&mastering_detail);

                is_init = true;

				d3d::log_d3d.info("XAudio2 initialized.");
            }

            void fin(){
                if (is_init){
                    for(auto& v : se_list) {
                        v.second.stop();
                    }  
                    se_list.clear();
                    for (auto& v : bgm_list) {
                        v.second.destroy();
                    }
                    bgm_list.clear();
                    if (p_master_voice != nullptr) {
                        p_master_voice->DestroyVoice();
                        p_master_voice = nullptr;
                    }
                    
					is_init = false;

					d3d::log_d3d.info("XAudio2 finalized.");
                }
            }

#ifndef SPEAKER_STEREO
#define SUIKA_DEF_SPEAKER
#define SPEAKER_MONO             (SPEAKER_FRONT_CENTER)
#define SPEAKER_STEREO           (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT)
#define SPEAKER_2POINT1          (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_LOW_FREQUENCY)
#define SPEAKER_SURROUND         (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_BACK_CENTER)
#define SPEAKER_QUAD             (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)
#define SPEAKER_4POINT1          (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)
#define SPEAKER_5POINT1          (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)
#define SPEAKER_7POINT1          (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_LEFT_OF_CENTER | SPEAKER_FRONT_RIGHT_OF_CENTER)
#define SPEAKER_5POINT1_SURROUND (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_SIDE_LEFT | SPEAKER_SIDE_RIGHT)
#define SPEAKER_7POINT1_SURROUND (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_SIDE_LEFT  | SPEAKER_SIDE_RIGHT)
#endif

			void panning(float pan, IXAudio2SourceVoice* source_voice, UINT32 in, UINT32 out) {
				if (is_init && source_voice) {
					std::vector<float> v(in * out);
					float left = cosf(pan);
					float right = sinf(pan);
					DWORD mask;
					auto er = p_master_voice->GetChannelMask(&mask);

					if (FAILED(er)) {
						log_d3d.error("Failed to SetOutputVoices.");
						log_d3d.result(er);
						return;
					}

					switch (mask) {
						case SPEAKER_MONO:
							v[0] = 1.0;
							break;
						case SPEAKER_STEREO:
						case SPEAKER_2POINT1:
						case SPEAKER_SURROUND:
							v[0ull * in] = left;
							v[1ull * in] = right;
							break;
						case SPEAKER_QUAD:
							v[0ull * in] = v[2ull * in] = left;
							v[0ull * in + 1] = v[2ull * in + 1] = right;
							break;
						case SPEAKER_4POINT1:
							v[0ull * in] = v[3ull * in] = left;
							v[0ull * in + 1] = v[3ull * in + 1] = right;
							break;
						case SPEAKER_5POINT1:
						case SPEAKER_7POINT1:
						case SPEAKER_5POINT1_SURROUND:
							v[0ull * in] = v[4ull * in] = left;
							v[0ull * in + 1] = v[4ull * in + 1] = right;
							break;
						case SPEAKER_7POINT1_SURROUND:
							v[0ull * in] = v[4ull * in] = v[6ull * in] = left;
							v[0ull * in + 1] = v[4ull * in + 1] = v[6ull * in + 1] = right;
							break;
					}
					er = source_voice->SetOutputMatrix(nullptr, in, out, v.data());
					if (FAILED(er)) {
						log_d3d.error("Failed to SetOutputVoices.");
						log_d3d.result(er);
						log.error("音声のパン設定に失敗");
						return;
					}
				}
			}

			void panning(float pan, IXAudio2SubmixVoice* source_voice, UINT32 in, UINT32 out) {
				if (is_init && source_voice) {
					std::vector<float> v(in * out);
					float left = cosf(pan);
					float right = sinf(pan);
					DWORD mask;
					auto er = p_master_voice->GetChannelMask(&mask);
					if (FAILED(er)) {
						log_d3d.error("Failed to GetChannelMask.");
						log_d3d.result(er);
						return;
					}
					switch (mask) {
						case SPEAKER_MONO:
							v[0] = 1.0;
							break;
						case SPEAKER_STEREO:
						case SPEAKER_2POINT1:
						case SPEAKER_SURROUND:
							v[0ull * in] = left;
							v[1ull * in] = right;
							break;
						case SPEAKER_QUAD:
							v[0ull * in] = v[2ull * in] = left;
							v[0ull * in + 1] = v[2ull * in + 1] = right;
							break;
						case SPEAKER_4POINT1:
							v[0ull * in] = v[3ull * in] = left;
							v[0ull * in + 1] = v[3ull * in + 1] = right;
							break;
						case SPEAKER_5POINT1:
						case SPEAKER_7POINT1:
						case SPEAKER_5POINT1_SURROUND:
							v[0ull * in] = v[4ull * in] = left;
							v[0ull * in + 1] = v[4ull * in + 1] = right;
							break;
						case SPEAKER_7POINT1_SURROUND:
							v[0ull * in] = v[4ull * in] = v[6ull * in] = left;
							v[0ull * in + 1] = v[4ull * in + 1] = v[6ull * in + 1] = right;
							break;
					}
					er = source_voice->SetOutputMatrix(nullptr, in, out, v.data());
					if (FAILED(er)) {
						log_d3d.error("Failed to SetOutputVoices.");
						log_d3d.result(er);
						log.error("音声のパン設定に失敗");
						return;
					}
				}
			}
#ifdef SUIKA_DEF_SPEAKER
#undef SUIKA_DEF_SPEAKER
#undef SPEAKER_MONO            
#undef SPEAKER_STEREO          
#undef SPEAKER_2POINT1         
#undef SPEAKER_SURROUND        
#undef SPEAKER_QUAD            
#undef SPEAKER_4POINT1         
#undef SPEAKER_5POINT1         
#undef SPEAKER_7POINT1         
#undef SPEAKER_5POINT1_SURROUND
#undef SPEAKER_7POINT1_SURROUND
#endif
        }
    }
}