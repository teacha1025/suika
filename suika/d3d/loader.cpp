#include "info.hpp"
#include "xaudio.hpp"

namespace suika{
    namespace d3d{
        namespace xaudio{
            bool load_wav(const string& path, std::unique_ptr<uint8_t[]>& data){
                if(is_init){
                    auto er = DirectX::LoadWAVAudioFromFileEx(path.to_wstring().c_str(), data, wav_data[path]);
                    if (FAILED(er)){
						log_d3d.error("Failed to load wav:" + path.to_string());
						log_d3d.result(er);
                        return false;
                    }
                    return true;
                }
                return false;
            }

			struct PCM_WAVE_FORMAT {
				char riff[4];
				unsigned int riffSize;
				char wave[4];
				char fmt[4];
				unsigned int fmtSize;
				unsigned short formatID;
				unsigned short channel;
				unsigned int samplingRate;
				unsigned int dataSizePerSec;
				unsigned short blockSize;
				unsigned short bitPerSample;
				char data[4];
				unsigned int PCMSize;

				PCM_WAVE_FORMAT(unsigned short inChannel, unsigned int inSamplingRate, unsigned int inPCMDataSize) {
					memcpy(riff, "RIFF", 4);
					memcpy(wave, "WAVE", 4);
					memcpy(fmt, "fmt ", 4);
					fmtSize = 16;
					bitPerSample = 16; 
					formatID = 1;

					channel = inChannel;
					samplingRate = inSamplingRate;
					dataSizePerSec = samplingRate * bitPerSample / 8 * channel;
					blockSize = bitPerSample / 8 * channel;
					memcpy(data, "data", 4);

					PCMSize = inPCMDataSize;
					riffSize = sizeof(PCM_WAVE_FORMAT) - 8 + PCMSize;
				}
			};
			static uint8_t* createPCMWAVEFileImage(unsigned short channel, unsigned int samplingRate, uint8_t* PCMData, unsigned int PCMDataSize) {
				PCM_WAVE_FORMAT format(channel, samplingRate, PCMDataSize);
				unsigned int PCMImageSize = sizeof(PCM_WAVE_FORMAT) + PCMDataSize;
				uint8_t* PCMImage = new uint8_t[PCMImageSize];
				memcpy(PCMImage, &format, sizeof(PCM_WAVE_FORMAT));
				memcpy(PCMImage + sizeof(PCM_WAVE_FORMAT), PCMData, PCMDataSize);

				return PCMImage;
			}

			define PCMSize = (size_t)(10 * suffix::MEGA * 1.024);

            bool load_ogg(string path, std::unique_ptr<uint8_t[]>& data){
                if (is_init){
					OggVorbis_File vf;
					if (ov_fopen(path.to_string().c_str(), &vf) != 0) {
						log_d3d.error("Failed to open ogg: " + path.to_string());
						return false;
					}
					vorbis_info* ogg_info = ov_info(&vf, -1);
					if (ogg_info == nullptr) {
						log_d3d.error("Failed to get ogg info.");
						return false;
					}
					std::unique_ptr<uint8_t> buffer(new uint8_t[PCMSize]);
					memset(buffer.get(), 0, PCMSize);
					std::unique_ptr<uint8_t> tmpBuffer(new uint8_t[PCMSize]);
					int bitstream = 0;
					int readSize = 0;
					int comSize = 0;
					while (1) {
						readSize = ov_read(&vf, (char*)tmpBuffer.get(), 4096, 0, 2, 1, &bitstream);
						if (comSize + readSize >= PCMSize || readSize <= 0)
							break;
						memcpy(buffer.get() + comSize, tmpBuffer.get(), readSize);
						comSize += readSize;
					}

					data.reset(createPCMWAVEFileImage(ogg_info->channels, ogg_info->rate, buffer.get(), comSize));
					DirectX::LoadWAVAudioInMemoryEx(data.get(), PCMSize, wav_data[path]);
					ov_clear(&vf);
                    return true;
                }
                return false;
            }

            
            bool load_audio(string path, std::unique_ptr<uint8_t[]>& data) {
                auto ext = path.substr(path.find_last_of(".") + 1);
                if (ext == "wav") {
                    return load_wav(path, data);
                }
                else if (ext == "ogg") {
                    return load_ogg(path, data);
                }
                return false;
            }
        }
    }
}