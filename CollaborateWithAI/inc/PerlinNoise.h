#pragma once
#include <iostream>
#include <vector>
using namespace std;
static void Perlin1Df(int octaves, const vector<float>& OneD, vector<float>& OneDPerlin, float spiky)
{
    for (int i = 0; i < OneD.size(); i++)
    {
        float Noise = 0;
        float scale = 1.0;
        float ScaleAcc = 0;
        for (int j = 0; j < octaves; j++)
        {
            int Pitch = OneD.size() >> j;
            int Sample1 = (i / Pitch) * Pitch;
            int Sample2 = (Sample1 + Pitch) % OneD.size();
            float Blend = (float)(i - Sample1) / Pitch;
            float Sample = (1.0 - Blend) * OneD[Sample1] + Blend * OneD[Sample2];
            Noise += Sample * scale;
            ScaleAcc += scale;
            scale /= spiky;
        }
        OneDPerlin[i] = Noise / ScaleAcc;
    }
}
static void Perlin2Df(int octaves, const vector<float>& TwoD, vector<float>& TwoDPerlin, float spiky)
{
    for (int i = 0; i < sqrt(TwoD.size()); i++)
    {
        for (int j = 0; j < sqrt(TwoD.size()); j++)
        {
            float Noise = 0;
            float scale = 1.0;
            float ScaleAcc = 0;
            for (int k = 0; k < octaves; k++)
            {
                int Pitch = (int)sqrt(TwoD.size()) >> k;
                int SampleX1 = (i / Pitch) * Pitch;
                int SampleY1 = (j / Pitch) * Pitch;

                int SampleX2 = (SampleX1 + Pitch) % (int)sqrt(TwoD.size());
                int SampleY2 = (SampleY1 + Pitch) % (int)sqrt(TwoD.size());
                float BlendX = (float)(i - SampleX1) / Pitch;
                float BlendY = (float)(j - SampleY1) / Pitch;
                float SampleT = (1.0 - BlendX) * TwoD[SampleY1 * (int)sqrt(TwoD.size()) + SampleX1] + BlendX * TwoD[SampleY1 * (int)sqrt(TwoD.size()) + SampleX2];
                float SampleB = (1.0 - BlendX) * TwoD[SampleY2 * (int)sqrt(TwoD.size()) + SampleX1] + BlendX * TwoD[SampleY2 * (int)sqrt(TwoD.size()) + SampleX2];
                Noise += (BlendY * (SampleB - SampleT) + SampleT) * scale;
                ScaleAcc += scale;
                scale /= spiky;
            }
            TwoDPerlin[j * sqrt(TwoD.size()) + i] = Noise / ScaleAcc;
        }
    }
}
static void Perlin1Df(vector<float>& OneDPerlin, int octaves, int size, float spiky)
{
    vector<float> oneD;
    OneDPerlin.resize(size);
    oneD.resize(size);
    for (int i = 0; i < size; i++)
    {
        oneD[i] = (float)rand() / RAND_MAX;
    }
    Perlin1Df(octaves, oneD, OneDPerlin, spiky);
}
static void Perlin2Df(vector<float>& TwoDPerlin, int octaves, int size, float spiky)
{
    vector<float> twoD;
    twoD.resize(size * size);
    TwoDPerlin.resize(size * size);
    for (int i = 0; i < size * size; i++)
    {
        twoD[i] = (float)rand() / RAND_MAX;
    }
    Perlin2Df(octaves, twoD, TwoDPerlin, spiky);
}
static void OptimizeMap(vector<float>& map)
{
    float mini = 1.0;
    float maxi = 0.0;
    for (int i = 0; i < map.size(); i++)
    {
        if (map[i] > maxi)
            maxi = map[i];
        if (map[i] < mini)
            mini = map[i];
    }
    for (int i = 0; i < map.size(); i++)
    {
        map[i] = map[i] - mini;
        map[i] = map[i] / (maxi - mini);
    }
}