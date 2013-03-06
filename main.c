#include <stdio.h>
#include <math.h>
#include "wave_utilities.h"

#define WAVE_SIZE 70
#define NOISE_MAGNITUDE 5
#define ADC_MAX (1 << 10)

int sine[WAVE_SIZE];

int main() {
    for (int i = 0; i < WAVE_SIZE; i++) {
        sine[i] = (ADC_MAX / 2) + (ADC_MAX / 2) * sin(i);
        printf("%d\n", sine[i]);
    }
    printf("wave freq: %d\n", waveFrequency(sine, 0, WAVE_SIZE));
}
