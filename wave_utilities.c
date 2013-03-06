#include <stdio.h>
#include <stdbool.h>

enum wave_type {SINE, TRIANGLE, SQUARE};

// The allowed deviation in number of samples between each period of a waveform.
#define PERIOD_TOLERANCE 5

// The minimum period we expect (in number of samples).
#define MIN_PERIOD 5

int abs(int x) {
    return x > 0 ? x : -x;
}

// Detects whether a waveform is periodic and returns the frequency if it is.
// Otherwise, returns 0.
int waveFrequency(int* wave, int start_index, int n_samples) {
    // Compute the DC offset (the average amplitude of the wave).
    long long dc_offset = 0;
    for (int i = 0; i < n_samples; i++) {
            dc_offset += wave[(start_index + i) % n_samples];
    }
    dc_offset /= n_samples;

    // Computes the points when the sign of the sum of the magnitude changes. These
    // points should occur at equally placed positions along the waveform.
    long long sum = 0;
    int previous_zero = 0;
    int previous_period_length = -1;
    for (int i = 0; i < n_samples; i++) {
        long long prev_sum = sum;
        sum += wave[(start_index + i) % n_samples] - dc_offset;
        printf("mag is %d, adding %lld\n", wave[(start_index + i) % n_samples], wave[(start_index + i) % n_samples] - dc_offset);
        printf("sum is %lld at pos %d\n", sum, i);
        bool different_sign = (prev_sum < 0) != (sum < 0);
        if (different_sign && i - previous_zero > MIN_PERIOD) {
            // Sign has changed. Update the period length and check that it
            // isn't too different from the previous value.
            int this_period_length = i - previous_zero;
            printf("found period of length %d at pos %d\n", this_period_length, i);
            previous_zero = i;
            if (previous_period_length == -1) {
                previous_period_length = this_period_length;
            }
            if (abs(this_period_length - previous_period_length) >
                PERIOD_TOLERANCE) {
                return -1;
            }
            previous_period_length = this_period_length;
        }
    }

    return previous_period_length;
}

/*wave_type waveType(int* wave, int n_samples) {
}

int waveFrequency(int* wave, int n_samples) {
}

double waveMeanSquareError(int* wave1, int* wave2, int n_samples) {
}*/
