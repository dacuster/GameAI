using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Utility Functions.
public static class Utils
{
    // Fractal Brownian Motion Calculation.
    public static float fBM(float x, float y, int octave, float persistence)
    {
        // Total height value calculated.
        float total = 0.0f;
        // How close the waves are together.
        float frequency = 1.0f;
        // How high/low the waves are.
        float amplitude = 1.0f;
        // Addition of each amplitude for each octave.
        float maxValue = 0.0f;

        // Loop through each octave.
        for (int counter = 0; counter < octave; counter++)
        {
            total += Mathf.PerlinNoise(x * frequency, y * frequency) * amplitude;

            maxValue += amplitude;

            amplitude *= persistence;

            frequency *= 2.0f;
        }

        return total / maxValue;
    }
}
