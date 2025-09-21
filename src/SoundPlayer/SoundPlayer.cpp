#include <SoundPlayer.hpp>


SoundPlayer::SoundPlayer (const std::string &pathToSound):
    decoder_(),
    device_(),
    playerData_(),
    isPlaying_(false) {

    initializeDecoder(pathToSound);
    loadSound();
    initializeDevice();
}

SoundPlayer::~SoundPlayer () {

    ma_device_uninit(&device_);
    ma_decoder_uninit(&decoder_);
}

void SoundPlayer::start () {

    ma_device_start(&device_);
    isPlaying_ = true;
}

void SoundPlayer::stop () {

    ma_device_stop(&device_);
    isPlaying_ = false;
}

void SoundPlayer::swith () {

    if (isPlaying_) {

        stop();
    }
    else {

        start();
    }
}

float SoundPlayer::getPitch () const {

    return playerData_.pitch;
}

void SoundPlayer::setPitch (float pitch) {

    playerData_.pitch = pitch;
}

void SoundPlayer::adjustPitch (float delta) {

    playerData_.pitch += delta;
}


void SoundPlayer::initializeDecoder (const std::string &pathToSound) {

    ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 1, 48000);

    if (ma_decoder_init_file(pathToSound.c_str(), &config, &decoder_) != MA_SUCCESS) {

        std::cerr << "An error occured during decoder initialization!\n";
        return;
    }
}

void SoundPlayer::loadSound () {

    ma_uint64 frameCount = 0;
    if (ma_decoder_get_length_in_pcm_frames(&decoder_, &frameCount)) {

        std::cerr << "An error occured during sound loading!\n";
        return;
    }

    playerData_.soundSamples.resize(frameCount);
    if (ma_decoder_read_pcm_frames(&decoder_, playerData_.soundSamples.data(), frameCount, nullptr) != MA_SUCCESS) {

        std::cerr << "An error occured during sound loading!\n";
        return;
    }
}

void SoundPlayer::initializeDevice () {

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = 1;
    config.sampleRate = decoder_.outputSampleRate;
    config.dataCallback = callbakcPlayer;
    config.pUserData = &playerData_;

    if (ma_device_init(NULL, &config, &device_) != MA_SUCCESS) {
        
        std::cerr << "An error occured during device initialization!\n";
        return;
    }
}

void SoundPlayer::callbakcPlayer (ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {

    PlayerData *playerData = static_cast<PlayerData*>(pDevice->pUserData);
    if (!playerData) {

        std::cerr << "Error! No data in callbackPlayer!\n";
        return;
    }

    for (ma_uint32 i = 0; i < frameCount; ++i) {

        double advanceFloored = std::floor(playerData->advance);
        long long id = static_cast<long long>(advanceFloored);

        if (id >= 0 && id + 1 < static_cast<long long>(playerData->soundSamples.size())) {  //more optimized realizations are possible

            float a = playerData->soundSamples[id];
            float b = playerData->soundSamples[id + 1];
            float t = static_cast<float>(playerData->advance - advanceFloored);

            *(static_cast<float*>(pOutput) + i) = std::lerp(a, b, t);
        }
        else {

            *(static_cast<float*>(pOutput) + i) = 0.f;
        }

        playerData->advance += playerData->pitch;
    }
}