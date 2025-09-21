#pragma once


#include <iostream>
#include <vector>
#include <cmath>

#include <miniaudio.h>


class SoundPlayer final {

public:

    SoundPlayer (const std::string &pathToSound);

    SoundPlayer (const SoundPlayer&) = delete;
    SoundPlayer& operator= (const SoundPlayer&) = delete;

    ~SoundPlayer ();

    void start ();
    void stop ();
    void swith ();

    float getPitch () const;
    void setPitch (float pitch);
    void adjustPitch (float delta);

private:

    void initializeDecoder (const std::string &pathToSound);
    void loadSound ();
    void initializeDevice ();

    static void callbakcPlayer (ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

private:

    struct PlayerData {

        double advance = 0.0;
        float pitch = 1.0;

        std::vector <float> soundSamples = std::vector <float> ();
    };

    ma_decoder decoder_;
    ma_device device_;

    PlayerData playerData_;

    bool isPlaying_;
};