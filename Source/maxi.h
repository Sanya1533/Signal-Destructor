#pragma once
#define MAXIMILIAN_H

 //#define MAXIMILIAN_PORTAUDIO
#define MAXIMILIAN_RT_AUDIO

#include <iostream>
#include <fstream>
#include <string.h>
#include <cassert>
#include <cstdlib>
#include "math.h"
#include <cerrno>
#include <queue>
#include <vector>

#if !defined(_WIN32) && (defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#define OS_IS_UNIX true
#include <pthread.h>
#include <unistd.h>
#endif

#ifdef _WIN32 //|| _WIN64
#define OS_IS_WIN true
#include <algorithm>
#include <Windows.h>
#include <process.h>
#endif

using namespace std;
#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif
#define TWOPI 6.283185307179586476925286766559

class maxiSettings
{
public:
    static int sampleRate;
    static int channels;
    static int bufferSize;
    static void setup(int initSampleRate, int initChannels, int initBufferSize) {
        maxiSettings::sampleRate = initSampleRate;
        maxiSettings::channels = initChannels;
        maxiSettings::bufferSize = initBufferSize;
    }
};


class maxiOsc
{
private:
    double frequency;
    double phase;
    double startphase;
    double endphase;
    double output;
    double tri;


public:
    maxiOsc();
    double sinewave(double frequency);
    double coswave(double frequency);
    double phasor(double frequency);
    double phasor(double frequency, double startphase, double endphase);
    double saw(double frequency);
    double triangle(double frequency);
    double square(double frequency);
    double pulse(double frequency, double duty);
    double noise();
    double sinebuf(double frequency);
    double sinebuf4(double frequency);
    double sawn(double frequency);
    double rect(double frequency, double duty = 0.5);
    void phaseReset(double phaseIn);

};