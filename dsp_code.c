/**
 * ==============================================================================
 * DSP & IMAGE PROCESSING LAB CODE COLLECTION
 * Complete C Program Implementations transcribed from Lab Sheets & Handwritten Logs
 * Department of Electronics and Communication Engineering (ECE), NIT Warangal
 * ==============================================================================
 * 
 * NOTE ON STRUCTURE:
 * As requested, all 21 laboratory programs are consolidated into this single file.
 * Each program is completely standalone with its own #include directives, global
 * variables/macros, and main() entry point, preceded by a prominent section header.
 * 
 * TABLE OF CONTENTS:
 * ------------------------------------------------------------------------------
 * PART 1: IMAGE PROCESSING OPERATIONS
 *   1.1 Image Brightness and Darkness
 *   1.2 Simple Image Subtraction
 *   1.3 Image Contrast Adjustment
 *   1.4 Quantization and Thresholding
 * 
 * PART 2: FIR FILTER DESIGN USING WINDOWING TECHNIQUES
 *   2.1 FIR Low Pass Filter (Hamming Window)
 *   2.2 FIR High Pass Filter (Hamming Window)
 *   2.3 FIR Band Pass Filter (Hamming Window)
 *   2.4 FIR Band Stop Filter (Hamming Window)
 * 
 * PART 3: IIR FILTER DESIGN TECHNIQUES
 *   3.1 Impulse Invariant IIR Filter
 *   3.2 Bilinear Transformation (BLT) IIR Filter
 *   3.3 Matched Z-Transformation (MZT) IIR Filter
 * 
 * PART 4: FAST FOURIER TRANSFORM (FFT) ALGORITHMS
 *   4.1 Split-Radix IFFT and FFT
 *   4.2 Decimation-in-Time (DIT) Radix-2 FFT
 *   4.3 Decimation-in-Frequency (DIF) Radix-2 FFT
 * 
 * PART 5: BLOCK CONVOLUTION METHODS
 *   5.1 Overlap-Save Linear Convolution
 *   5.2 Overlap-Add Linear Convolution
 * 
 * PART 6: DIRECT DFT, IDFT & MATRIX MULTIPLICATION
 *   6.1 Direct DFT and IDFT
 *   6.2 DFT via Twiddle Factor Recurrence
 *   6.3 Matrix Multiplication Method for DFT
 * 
 * PART 7: LINEAR AND CIRCULAR CONVOLUTION
 *   7.1 Direct Linear Convolution
 *   7.2 Circular Convolution
 * ==============================================================================
 */


/*******************************************************************************
 * ============================================================================
 * PART 1: IMAGE PROCESSING OPERATIONS
 * PROGRAM 1.1: IMAGE BRIGHTNESS AND DARKNESS
 * ============================================================================
 * Source Page: 1
 * Description: Adjusts image brightness by adding and subtracting an offset 'b'
 *              with saturation clipping to [0, 255].
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include "image.h"

// IMAGE BRIGHTNESS AND DARKNESS
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
int I2[256][256];
int I3[256][256];
int b = 50;

int main(void) {
    int i, j;
    
    // Increase Brightness
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            I2[i][j] = I1[i][j] + b;
            if (I2[i][j] > 255)
                I2[i][j] = 255;
        }
    }
    
    // Decrease Brightness (Darkness)
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            I3[i][j] = I1[i][j] - b;
            if (I3[i][j] < 0)
                I3[i][j] = 0;
        }
    }
    
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 1: IMAGE PROCESSING OPERATIONS
 * PROGRAM 1.2: SIMPLE IMAGE SUBTRACTION
 * ============================================================================
 * Source Page: 2
 * Description: Computes absolute pixel-by-pixel difference between two images
 *              I2 and I1: I3[i][j] = |I2[i][j] - I1[i][j]|.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"

// SIMPLE IMAGE SUBTRACTION
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
int I3[256][256];

int main(void) {
    int i, j;
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            I3[i][j] = abs(I2[i][j] - I1[i][j]);
        }
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 1: IMAGE PROCESSING OPERATIONS
 * PROGRAM 1.3: IMAGE CONTRAST ADJUSTMENT
 * ============================================================================
 * Source Page: 3
 * Description: Linear contrast transformation I_out = m * I_in + b for both
 *              high contrast (m = 1.6) and low contrast (m = 0.8) with clamping.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include "image.h"

// IMAGE CONTRAST
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
int I2[256][256];
int I3[256][256];

int main(void) {
    int i, j;
    float m, b;
    
    // High contrast: m = 1.6
    m = 1.6f;
    b = (255.0f / 2.0f) * (1.0f - m);
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            I2[i][j] = (int)(m * I1[i][j] + b);
            if (I2[i][j] > 255)
                I2[i][j] = 255;
            if (I2[i][j] < 0)
                I2[i][j] = 0;
        }
    }
    
    // Low contrast: m = 0.8
    m = 0.8f;
    b = 0.0f;
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            I3[i][j] = (int)(m * I1[i][j] + b);
            if (I3[i][j] > 255)
                I3[i][j] = 255;
            if (I3[i][j] < 0)
                I3[i][j] = 0;
        }
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 1: IMAGE PROCESSING OPERATIONS
 * PROGRAM 1.4: QUANTIZATION AND THRESHOLDING
 * ============================================================================
 * Source Page: 4
 * Description: 5-level gray scale quantization into levels {25, 75, 125, 175, 225}
 *              and binary thresholding at intensity level 130 into {0, 255}.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include "image.h"

// QUANTIZE AND THRESHOLD
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
int I2[256][256];
int I3[256][256];

int main(void) {
    int i, j;
    
    // 5-level Quantization
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            if (I1[i][j] <= 255 && I1[i][j] > 200)
                I2[i][j] = 225;
            else if (I1[i][j] <= 200 && I1[i][j] > 150)
                I2[i][j] = 175;
            else if (I1[i][j] <= 150 && I1[i][j] > 100)
                I2[i][j] = 125;
            else if (I1[i][j] <= 100 && I1[i][j] > 50)
                I2[i][j] = 75;
            else if (I1[i][j] <= 50 && I1[i][j] >= 0)
                I2[i][j] = 25;
        }
    }
    
    // Thresholding at level 130
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            if (I1[i][j] > 130)
                I3[i][j] = 255;
            else
                I3[i][j] = 0;
        }
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 2: FIR FILTER DESIGN USING WINDOWING TECHNIQUES
 * PROGRAM 2.1: FIR LOW PASS FILTER (LPF)
 * ============================================================================
 * Source Page: 5
 * Description: Hamming window FIR Low Pass Filter (N=21, FS=1000 Hz, FC=200 Hz).
 *              Filters composite input (50 Hz + 350 Hz) by convolution.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// FIR FILTER using windowing techniques - LPF
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define N 21
#define L 128
#define PI 3.14159265358979323846
#define FS 1000.0
#define FC 200.0

float h[N];
float x[L];
float y[L];

int main(void) {
    int n, k;
    int M = (N - 1) / 2;
    float hd, w, sum = 0.0f;
    float wc = 2.0f * (float)PI * (float)FC / (float)FS;
    
    for (n = 0; n < N; n++) {
        int m = n - M;
        if (m == 0) {
            hd = (float)FC / ((float)FS / 2.0f);
        } else {
            hd = sinf(wc * (float)m) / ((float)PI * (float)m);
        }
        w = 0.54f - 0.46f * cosf(2.0f * (float)PI * (float)n / (float)(N - 1));
        h[n] = hd * w;
        sum += h[n];
    }
    
    // Normalize impulse response
    for (n = 0; n < N; n++) {
        h[n] = h[n] / sum;
    }
    
    // Generate test input signal (50 Hz + 350 Hz components)
    for (n = 0; n < L; n++) {
        x[n] = sinf(2.0f * (float)PI * 50.0f * (float)n / (float)FS) +
               sinf(2.0f * (float)PI * 350.0f * (float)n / (float)FS);
    }
    
    // Filtering by convolution
    for (n = 0; n < L; n++) {
        y[n] = 0.0f;
        for (k = 0; k < N; k++) {
            if ((n - k) >= 0) {
                y[n] += h[k] * x[n - k];
            }
        }
    }
    
    printf("FIR LOW PASS FILTER\n");
    printf("Hamming Window Method\n");
    for (n = 0; n < N; n++) {
        printf("h[%d] = %f\n", n, h[n]);
    }
    printf("\nfiltering completed.\n");
    
    // while (1); // Embedded target loop
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 2: FIR FILTER DESIGN USING WINDOWING TECHNIQUES
 * PROGRAM 2.2: FIR HIGH PASS FILTER (HPF)
 * ============================================================================
 * Source Page: 6
 * Description: Hamming window FIR High Pass Filter (N=21, FS=1000 Hz, FC=200 Hz).
 *              Attenuates 50 Hz component while passing 350 Hz component.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// FIR FILTER using windowing techniques - HPF
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define N 21
#define L 128
#define PI 3.14159265358979323846
#define FS 1000.0
#define FC 200.0

float h[N];
float x[L];
float y[L];

int main(void) {
    int n, k;
    int M = (N - 1) / 2;
    float hd, w, sum = 0.0f;
    float wc = 2.0f * (float)PI * (float)FC / (float)FS;
    
    for (n = 0; n < N; n++) {
        int m = n - M;
        if (m == 0) {
            hd = 1.0f - (2.0f * (float)FC / (float)FS);
        } else {
            hd = -sinf(wc * (float)m) / ((float)PI * (float)m);
        }
        w = 0.54f - 0.46f * cosf(2.0f * (float)PI * (float)n / (float)(N - 1));
        h[n] = hd * w;
        if (n % 2 == 0)
            sum += h[n];
        else
            sum -= h[n];
    }
    
    for (n = 0; n < N; n++) {
        h[n] = h[n] / sum;
    }
    
    for (n = 0; n < L; n++) {
        x[n] = sinf(2.0f * (float)PI * 50.0f * (float)n / (float)FS) +
               sinf(2.0f * (float)PI * 350.0f * (float)n / (float)FS);
    }
    
    for (n = 0; n < L; n++) {
        y[n] = 0.0f;
        for (k = 0; k < N; k++) {
            if ((n - k) >= 0) {
                y[n] += h[k] * x[n - k];
            }
        }
    }
    
    printf("FIR HIGH PASS FILTER\n");
    printf("Hamming Window Method\n");
    for (n = 0; n < N; n++) {
        printf("h[%d] = %f\n", n, h[n]);
    }
    printf("\nfiltering completed.\n");
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 2: FIR FILTER DESIGN USING WINDOWING TECHNIQUES
 * PROGRAM 2.3: FIR BAND PASS FILTER (BPF)
 * ============================================================================
 * Source Page: 7
 * Description: Hamming window FIR Band Pass Filter with passband [100 Hz, 300 Hz],
 *              sampling FS=1000 Hz, normalized using center frequency f0 gain.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// FIR FILTER using windowing techniques - BPF
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define N 21
#define L 128
#define PI 3.14159265358979323846
#define FS 1000.0
#define F1 100.0
#define F2 300.0

float h[N];
float x[L];
float y[L];

int main(void) {
    int n, k;
    int M = (N - 1) / 2;
    double hd, w;
    double sum_re = 0.0, sum_im = 0.0;
    double gain;
    double f0 = (F1 + F2) / 2.0;
    double wc1 = 2.0 * PI * F1 / FS;
    double wc2 = 2.0 * PI * F2 / FS;
    double w0 = 2.0 * PI * f0 / FS;
    
    for (n = 0; n < N; n++) {
        int m = n - M;
        if (m == 0) {
            hd = 2.0 * (F2 - F1) / FS;
        } else {
            hd = (sin(wc2 * m) - sin(wc1 * m)) / (PI * m);
        }
        w = 0.54 - 0.46 * cos(2.0 * PI * n / (N - 1));
        h[n] = (float)(hd * w);
    }
    
    for (n = 0; n < N; n++) {
        sum_re += h[n] * cos(w0 * n);
        sum_im -= h[n] * sin(w0 * n);
    }
    gain = sqrt(sum_re * sum_re + sum_im * sum_im);
    if (gain > 0.0) {
        for (n = 0; n < N; n++) {
            h[n] = (float)(h[n] / gain);
        }
    }
    
    // Input with 50 Hz, 150 Hz (passband), and 400 Hz
    for (n = 0; n < L; n++) {
        x[n] = (float)(sin(2.0 * PI * 50.0 * n / FS) +
                      sin(2.0 * PI * 150.0 * n / FS) +
                      sin(2.0 * PI * 400.0 * n / FS));
    }
    
    for (n = 0; n < L; n++) {
        y[n] = 0.0f;
        for (k = 0; k < N; k++) {
            if ((n - k) >= 0) {
                y[n] += h[k] * x[n - k];
            }
        }
    }
    
    printf("FIR BAND PASS FILTER\n");
    printf("Hamming Window Method\n");
    for (n = 0; n < N; n++) {
        printf("h[%d] = %f\n", n, h[n]);
    }
    printf("\nfiltering completed.\n");
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 2: FIR FILTER DESIGN USING WINDOWING TECHNIQUES
 * PROGRAM 2.4: FIR BAND STOP FILTER (BSF)
 * ============================================================================
 * Source Page: 8
 * Description: Hamming window FIR Band Stop Filter rejecting band [100 Hz, 300 Hz],
 *              sampling FS=1000 Hz, normalized at DC using sum of coefficients.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// FIR FILTER using windowing techniques - BSF
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define N 21
#define L 128
#define PI 3.14159265358979323846
#define FS 1000.0
#define F1 100.0
#define F2 300.0

float h[N];
float x[L];
float y[L];

int main(void) {
    int n, k;
    int M = (N - 1) / 2;
    double hd, w;
    double sum = 0.0;
    double wc1 = 2.0 * PI * F1 / FS;
    double wc2 = 2.0 * PI * F2 / FS;
    
    for (n = 0; n < N; n++) {
        int m = n - M;
        if (m == 0) {
            hd = 1.0 - (2.0 * (F2 - F1) / FS);
        } else {
            hd = (sin(wc1 * m) - sin(wc2 * m)) / (PI * m);
        }
        w = 0.54 - 0.46 * cos(2.0 * PI * n / (N - 1));
        h[n] = (float)(hd * w);
        sum += h[n];
    }
    
    if (fabs(sum) > 1e-12) {
        for (n = 0; n < N; n++) {
            h[n] = (float)(h[n] / sum);
        }
    }
    
    for (n = 0; n < L; n++) {
        x[n] = (float)(sin(2.0 * PI * 50.0 * n / FS) +
                      sin(2.0 * PI * 150.0 * n / FS) +
                      sin(2.0 * PI * 400.0 * n / FS));
    }
    
    for (n = 0; n < L; n++) {
        y[n] = 0.0f;
        for (k = 0; k < N; k++) {
            if ((n - k) >= 0) {
                y[n] += h[k] * x[n - k];
            }
        }
    }
    
    printf("FIR BAND STOP FILTER\n");
    printf("Hamming Window Method\n");
    for (n = 0; n < N; n++) {
        printf("h[%d] = %f\n", n, h[n]);
    }
    printf("\nfiltering completed.\n");
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 3: IIR FILTER DESIGN TECHNIQUES
 * PROGRAM 3.1: IMPULSE INVARIANT IIR FILTER
 * ============================================================================
 * Source Page: 9
 * Description: Direct Form II Second-Order Section (biquad) IIR filtering with
 *              direct summation input/output frequency spectrum calculations.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// IMPULSE INVARIANT IIR FILTER
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define NUM_SECTIONS 1
#define N 100
#define PI 3.14159265

float b[NUM_SECTIONS][3] = {
    {0.0f, 0.244920344f, 0.0f}
};
float a[NUM_SECTIONS][3] = {
    {1.0f, -1.158045900f, 0.411240700f}
};

float x[N];
float XR[N], XI[N];
float M1[N], M2[N];
float y[N];
float w[NUM_SECTIONS][2] = { {0} };

int main(void) {
    int i, j;
    int section;
    float input;
    float wn, yn;
    
    for (i = 0; i < N; i++) {
        x[i] = sinf(2.0f * (float)PI * 2.0f * (float)i / (float)N) +
               sinf(2.0f * (float)PI * 30.0f * (float)i / (float)N);
    }
    
    // Input spectrum magnitude M1
    for (j = 0; j < N; j++) {
        XR[j] = 0.0f;
        XI[j] = 0.0f;
        for (i = 0; i < N; i++) {
            XR[j] += x[i] * cosf(2.0f * (float)PI * (float)i * (float)j / (float)N);
            XI[j] -= x[i] * sinf(2.0f * (float)PI * (float)i * (float)j / (float)N);
        }
        M1[j] = sqrtf(XR[j] * XR[j] + XI[j] * XI[j]) / (float)N;
    }
    
    // Direct Form II Biquad Section Filtering
    for (i = 0; i < N; i++) {
        input = x[i];
        for (section = 0; section < NUM_SECTIONS; section++) {
            wn = input - a[section][1] * w[section][0] - a[section][2] * w[section][1];
            yn = b[section][0] * wn + b[section][1] * w[section][0] + b[section][2] * w[section][1];
            w[section][1] = w[section][0];
            w[section][0] = wn;
            input = yn;
        }
        y[i] = yn;
    }
    
    // Output spectrum magnitude M2
    for (j = 0; j < N; j++) {
        XR[j] = 0.0f;
        XI[j] = 0.0f;
        for (i = 0; i < N; i++) {
            XR[j] += y[i] * cosf(2.0f * (float)PI * (float)i * (float)j / (float)N);
            XI[j] -= y[i] * sinf(2.0f * (float)PI * (float)i * (float)j / (float)N);
        }
        M2[j] = sqrtf(XR[j] * XR[j] + XI[j] * XI[j]) / (float)N;
    }
    
    printf("\n");
    printf("Impulse Invariance IIR Filter\n");
    printf("===============================\n");
    printf("\nInput\t\tOutput\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%f\t%f\n", i, x[i], y[i]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 3: IIR FILTER DESIGN TECHNIQUES
 * PROGRAM 3.2: BILINEAR TRANSFORMATION (BLT) IIR FILTER
 * ============================================================================
 * Source Page: 10
 * Description: 4th-order difference equation implementation of Bilinear
 *              Transformation IIR filter with input/output spectrum analysis.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// BILINEAR TRANSFORMATION IIR FILTER
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define N 100
#define PI 3.14159265

float b[5] = { 0.028f, 0.053f, 0.071f, 0.053f, 0.028f };
float a[5] = { 1.000f, -2.026f, 2.148f, -1.159f, 0.279f };
float x[N], y[N];
float XR[N], XI[N];
float M1[N], M2[N];

int main(void) {
    int i, j;
    
    for (i = 0; i < N; i++) {
        x[i] = sinf(2.0f * (float)PI * 2.0f * (float)i / (float)N) +
               sinf(2.0f * (float)PI * 30.0f * (float)i / (float)N);
    }
    
    // Difference equation implementation
    for (i = 0; i < N; i++) {
        y[i] = b[0] * x[i];
        if (i >= 1)
            y[i] = y[i] + b[1] * x[i - 1] - a[1] * y[i - 1];
        if (i >= 2)
            y[i] = y[i] + b[2] * x[i - 2] - a[2] * y[i - 2];
        if (i >= 3)
            y[i] = y[i] + b[3] * x[i - 3] - a[3] * y[i - 3];
        if (i >= 4)
            y[i] = y[i] + b[4] * x[i - 4] - a[4] * y[i - 4];
    }
    
    // Input Spectrum
    for (j = 0; j < N; j++) {
        XR[j] = 0.0f;
        XI[j] = 0.0f;
        for (i = 0; i < N; i++) {
            XR[j] += x[i] * cosf(2.0f * (float)PI * (float)i * (float)j / (float)N);
            XI[j] -= x[i] * sinf(2.0f * (float)PI * (float)i * (float)j / (float)N);
        }
        M1[j] = sqrtf(XR[j] * XR[j] + XI[j] * XI[j]) / (float)N;
    }
    
    // Output Spectrum
    for (j = 0; j < N; j++) {
        XR[j] = 0.0f;
        XI[j] = 0.0f;
        for (i = 0; i < N; i++) {
            XR[j] += y[i] * cosf(2.0f * (float)PI * (float)i * (float)j / (float)N);
            XI[j] -= y[i] * sinf(2.0f * (float)PI * (float)i * (float)j / (float)N);
        }
        M2[j] = sqrtf(XR[j] * XR[j] + XI[j] * XI[j]) / (float)N;
    }
    
    printf("\n");
    printf("Bilinear Transformation IIR Filter\n");
    printf("===================================\n");
    printf("\nInput\t\tOutput\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%f\t%f\n", i, x[i], y[i]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 3: IIR FILTER DESIGN TECHNIQUES
 * PROGRAM 3.3: MATCHED Z-TRANSFORMATION (MZT) IIR FILTER
 * ============================================================================
 * Source Page: 11
 * Description: 1st order analog pole mapping s = -1 to discrete pole zp = exp(pole*T)
 *              via Matched Z-Transformation with frequency spectrum analysis.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// MATCHED Z TRANSFORMATION IIR FILTER
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define N 100
#define FS 100.0
#define PI 3.14159265

float x[N], y[N];
float XR[N], XI[N];
float YR[N], YI[N];
float M1[N], M2[N];

int main(void) {
    int i, j;
    float T, pole, zp, b0;
    
    T = 1.0f / (float)FS;
    pole = -1.0f;
    zp = expf(pole * T);
    b0 = 1.0f - zp;
    
    for (i = 0; i < N; i++) {
        x[i] = sinf(2.0f * (float)PI * 2.0f * (float)i / (float)N) +
               sinf(2.0f * (float)PI * 30.0f * (float)i / (float)N);
    }
    
    // Difference equation: y[n] = b0 * x[n] + zp * y[n-1]
    y[0] = b0 * x[0];
    for (i = 1; i < N; i++) {
        y[i] = b0 * x[i] + zp * y[i - 1];
    }
    
    // Input spectrum M1
    for (j = 0; j < N; j++) {
        XR[j] = 0.0f;
        XI[j] = 0.0f;
        for (i = 0; i < N; i++) {
            XR[j] += x[i] * cosf(2.0f * (float)PI * (float)i * (float)j / (float)N);
            XI[j] -= x[i] * sinf(2.0f * (float)PI * (float)i * (float)j / (float)N);
        }
        M1[j] = sqrtf(XR[j] * XR[j] + XI[j] * XI[j]) / (float)N;
    }
    
    // Output spectrum M2
    for (j = 0; j < N; j++) {
        YR[j] = 0.0f;
        YI[j] = 0.0f;
        for (i = 0; i < N; i++) {
            YR[j] += y[i] * cosf(2.0f * (float)PI * (float)i * (float)j / (float)N);
            YI[j] -= y[i] * sinf(2.0f * (float)PI * (float)i * (float)j / (float)N);
        }
        M2[j] = sqrtf(YR[j] * YR[j] + YI[j] * YI[j]) / (float)N;
    }
    
    printf("\n");
    printf("Matched Z Transformation IIR Filter\n");
    printf("===================================\n");
    printf("Sampling Frequency = %f Hz\n", (float)FS);
    printf("Sampling Time = %f sec\n", T);
    printf("Analog Pole = %f\n", pole);
    printf("Digital Pole = %f\n", zp);
    printf("\nInput\t\tOutput\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%f\t%f\n", i, x[i], y[i]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 4: FAST FOURIER TRANSFORM (FFT) PROGRAMS
 * PROGRAM 4.1: SPLIT-RADIX IFFT AND FFT
 * ============================================================================
 * Source Pages: 12 & 13
 * Description: Mixed-radix recursive butterfly engine (N=6, 9, or 12) with
 *              magnitude and phase computation.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// Split radix FFT
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define MAX_N 12
#define PI 3.14159265358979323846

float input[MAX_N], input_imag[MAX_N];
float real[MAX_N], imag[MAX_N];
float magnitude[MAX_N], phase[MAX_N];
int N;

void butterfly(float xr[], float xi[], float yr[], float yi[], int R) {
    int k, n;
    float a, c, s;
    for (k = 0; k < R; k++) {
        yr[k] = yi[k] = 0;
        for (n = 0; n < R; n++) {
            a = -2.0 * PI * k * n / R;
            c = cos(a);
            s = sin(a);
            yr[k] += xr[n] * c - xi[n] * s;
            yi[k] += xr[n] * s + xi[n] * c;
        }
    }
}

void FFT(float xr[], float xi[], int n) {
    int R, M, i, j, k;
    float ar[MAX_N], ai[MAX_N], br[MAX_N], bi[MAX_N];
    float cr[3], ci[3], a, c, s, tr, ti;
    
    if (n == 1) return;
    R = (n % 2 == 0) ? 2 : 3;
    M = n / R;
    
    for (j = 0; j < R; j++) {
        for (i = 0; i < M; i++) {
            ar[i] = xr[R * i + j];
            ai[i] = xi[R * i + j];
        }
        FFT(ar, ai, M);
        for (i = 0; i < M; i++) {
            br[j * M + i] = ar[i];
            bi[j * M + i] = ai[i];
        }
    }
    
    for (k = 0; k < M; k++) {
        for (j = 0; j < R; j++) {
            a = -2.0 * PI * j * k / n;
            c = cos(a);
            s = sin(a);
            tr = br[j * M + k] * c - bi[j * M + k] * s;
            ti = br[j * M + k] * s + bi[j * M + k] * c;
            ar[j] = tr;
            ai[j] = ti;
        }
        butterfly(ar, ai, cr, ci, R);
        for (j = 0; j < R; j++) {
            xr[k + j * M] = cr[j];
            xi[k + j * M] = ci[j];
        }
    }
}

int main(void) {
    int i;
    printf("Enter N (6, 9 or 12): ");
    scanf("%d", &N);
    if (N != 6 && N != 9 && N != 12) {
        printf("Invalid N\n");
        return 1;
    }
    
    printf("Enter input sequence:\n");
    for (i = 0; i < N; i++) {
        printf("x[%d] = ", i);
        scanf("%f", &input[i]);
        real[i] = input[i];
        imag[i] = 0;
    }
    
    FFT(real, imag, N);
    
    for (i = 0; i < N; i++) {
        magnitude[i] = sqrt(real[i] * real[i] + imag[i] * imag[i]);
        phase[i] = atan2(imag[i], real[i]) * 180.0 / PI;
    }
    
    printf("\nFFT OUTPUT\n");
    for (i = 0; i < N; i++) {
        printf("X[%d] = %f + j(%f)\n", i, real[i], imag[i]);
    }
    printf("\nMAGNITUDE\n");
    for (i = 0; i < N; i++) {
        printf("%f ", magnitude[i]);
    }
    printf("\nPHASE (degrees)\n");
    for (i = 0; i < N; i++) {
        printf("%f ", phase[i]);
    }
    printf("\n");
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 4: FAST FOURIER TRANSFORM (FFT) PROGRAMS
 * PROGRAM 4.2: DECIMATION-IN-TIME (DIT) RADIX-2 FFT
 * ============================================================================
 * Source Pages: 14 & 15
 * Description: Iterative Cooley-Tukey Radix-2 DIT-FFT with bit-reversal input
 *              shuffling, stage-by-stage butterfly computation, magnitude and phase.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// DIT FFT - Source Code
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define MAX_N 1024
#define PI 3.14159265358979323846

float input[MAX_N];
float real[MAX_N];
float imag[MAX_N];
float magnitude[MAX_N];
float phase[MAX_N];
int N;

int is_power_of_two(int n) {
    if (n < 2) return 0;
    return (n & (n - 1)) == 0;
}

void bit_reverse(float r[], float im[]) {
    int i, j, k;
    float temp;
    j = 0;
    for (i = 1; i < N; i++) {
        k = N >> 1;
        while (j >= k && k > 0) {
            j -= k;
            k >>= 1;
        }
        j += k;
        if (i < j) {
            temp = r[i]; r[i] = r[j]; r[j] = temp;
            temp = im[i]; im[i] = im[j]; im[j] = temp;
        }
    }
}

int main(void) {
    int i, j, k;
    int stage, stages;
    int step, half;
    float angle, wr, wi, tr, ti, ur, ui;
    
    printf("Enter N: ");
    scanf("%d", &N);
    if (!is_power_of_two(N) || N > MAX_N) {
        printf("\nInvalid N.");
        printf("\nN must be 2, 4, 8, 16, 32, ...\n");
        return 1;
    }
    
    printf("Enter %d input values:\n", N);
    for (i = 0; i < N; i++) {
        printf("x[%d] = ", i);
        scanf("%f", &input[i]);
        real[i] = input[i];
        imag[i] = 0.0f;
    }
    
    stages = 0;
    for (i = N; i > 1; i >>= 1) {
        stages++;
    }
    
    bit_reverse(real, imag);
    
    for (stage = 1; stage <= stages; stage++) {
        step = 1 << stage;
        half = step >> 1;
        for (j = 0; j < half; j++) {
            angle = -2.0f * (float)PI * (float)j / (float)step;
            wr = cosf(angle);
            wi = sinf(angle);
            for (i = j; i < N; i += step) {
                k = i + half;
                ur = real[i];
                ui = imag[i];
                tr = wr * real[k] - wi * imag[k];
                ti = wr * imag[k] + wi * real[k];
                real[i] = ur + tr;
                imag[i] = ui + ti;
                real[k] = ur - tr;
                imag[k] = ui - ti;
            }
        }
        printf("\nStage %d:\n", stage);
        for (i = 0; i < N; i++) {
            printf("%f ", real[i]);
        }
        printf("\n");
    }
    
    for (i = 0; i < N; i++) {
        magnitude[i] = sqrtf(real[i] * real[i] + imag[i] * imag[i]);
        phase[i] = atan2f(imag[i], real[i]) * 180.0f / (float)PI;
    }
    
    printf("\nFinal FFT:\n");
    for (i = 0; i < N; i++) {
        printf("%f + j(%f)\n", real[i], imag[i]);
    }
    printf("\nMagnitude:\n");
    for (i = 0; i < N; i++) {
        printf("%f ", magnitude[i]);
    }
    printf("\n\nPhase (degrees):\n");
    for (i = 0; i < N; i++) {
        printf("%f ", phase[i]);
    }
    printf("\n");
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 4: FAST FOURIER TRANSFORM (FFT) PROGRAMS
 * PROGRAM 4.3: DECIMATION-IN-FREQUENCY (DIF) RADIX-2 FFT
 * ============================================================================
 * Source Pages: 16 & 17
 * Description: Iterative Radix-2 DIF-FFT with natural order butterfly stages
 *              followed by bit-reversal sorting on the final output.
 * Roll Numbers: 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// DIF FFT - Source Code
// ROLL NUMBERS - 24ECB0A18, 24ECB0A31, 24ECB0A33, 24ECB0A34
#define MAX_N 1024
#define PI 3.14159265358979323846

float input[MAX_N];
float real[MAX_N];
float imag[MAX_N];
float magnitude[MAX_N];
float phase[MAX_N];
int N;

int is_power_of_two(int n) {
    if (n < 2) return 0;
    return (n & (n - 1)) == 0;
}

void bit_reverse(float r[], float im[]) {
    int i, j, k;
    float temp;
    j = 0;
    for (i = 1; i < N; i++) {
        k = N >> 1;
        while (j >= k && k > 0) {
            j -= k;
            k >>= 1;
        }
        j += k;
        if (i < j) {
            temp = r[i]; r[i] = r[j]; r[j] = temp;
            temp = im[i]; im[i] = im[j]; im[j] = temp;
        }
    }
}

int main(void) {
    int i, j, k;
    int stage, stages;
    int step, half;
    float angle, wr, wi, ar, ai, br, bi;
    
    printf("Enter N: ");
    scanf("%d", &N);
    if (!is_power_of_two(N) || N > MAX_N) {
        printf("\nInvalid N.");
        return 1;
    }
    
    printf("Enter %d input values:\n", N);
    for (i = 0; i < N; i++) {
        printf("x[%d] = ", i);
        scanf("%f", &input[i]);
        real[i] = input[i];
        imag[i] = 0.0f;
    }
    
    stages = 0;
    for (i = N; i > 1; i >>= 1) {
        stages++;
    }
    
    for (stage = stages; stage >= 1; stage--) {
        step = 1 << stage;
        half = step >> 1;
        for (i = 0; i < N; i += step) {
            for (j = 0; j < half; j++) {
                ar = real[i + j];
                ai = imag[i + j];
                br = real[i + j + half];
                bi = imag[i + j + half];
                
                real[i + j] = ar + br;
                imag[i + j] = ai + bi;
                
                ar = ar - br;
                ai = ai - bi;
                angle = -2.0f * (float)PI * (float)j / (float)step;
                wr = cosf(angle);
                wi = sinf(angle);
                
                real[i + j + half] = ar * wr - ai * wi;
                imag[i + j + half] = ar * wi + ai * wr;
            }
        }
        printf("\nStage %d:\n", stages - stage + 1);
        for (i = 0; i < N; i++) {
            printf("%f ", real[i]);
        }
        printf("\n");
    }
    
    bit_reverse(real, imag);
    
    for (i = 0; i < N; i++) {
        magnitude[i] = sqrtf(real[i] * real[i] + imag[i] * imag[i]);
        phase[i] = atan2f(imag[i], real[i]) * 180.0f / (float)PI;
    }
    
    printf("\nFinal FFT:\n");
    for (i = 0; i < N; i++) {
        printf("%f + j(%f)\n", real[i], imag[i]);
    }
    printf("\nMagnitude:\n");
    for (i = 0; i < N; i++) {
        printf("%f ", magnitude[i]);
    }
    printf("\n\nPhase (degrees):\n");
    for (i = 0; i < N; i++) {
        printf("%f ", phase[i]);
    }
    printf("\n");
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 5: BLOCK CONVOLUTION METHODS
 * PROGRAM 5.1: OVERLAP-SAVE LINEAR CONVOLUTION
 * ============================================================================
 * Source Pages: 18 & 19
 * Description: High-speed block convolution using Overlap-Save method with DFT/IDFT.
 *              Discards the first (M-1) contaminated samples per block.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// Linear Convolution using Overlap-Save Method
#define LX 9
#define M 3
#define N 6
#define L (N - M + 1)
#define PI 3.14159265358979

float x[LX] = {1, 3, 5, 8, 9, 2, 3, 9, 1};
float h[M] = {1, 3, 2};
float y[LX + M - 1];

void dft(float in_re[], float out_re[], float out_im[]) {
    int k, n;
    for (k = 0; k < N; k++) {
        out_re[k] = 0.0f;
        out_im[k] = 0.0f;
        for (n = 0; n < N; n++) {
            float angle = 2.0f * (float)PI * (float)k * (float)n / (float)N;
            out_re[k] += in_re[n] * cosf(angle);
            out_im[k] -= in_re[n] * sinf(angle);
        }
    }
}

void idft(float in_re[], float in_im[], float out_re[]) {
    int n, k;
    for (n = 0; n < N; n++) {
        float sum = 0.0f;
        for (k = 0; k < N; k++) {
            float angle = 2.0f * (float)PI * (float)k * (float)n / (float)N;
            sum += in_re[k] * cosf(angle) - in_im[k] * sinf(angle);
        }
        out_re[n] = sum / (float)N;
    }
}

int main(void) {
    float Hre[N], Him[N], hpad[N];
    float block[N], Xre[N], Xim[N];
    float Yre[N], Yim[N], out[N];
    int i, n, blk, outIdx = 0;
    int numblocks = (LX + L - 1) / L;
    
    for (i = 0; i < N; i++) {
        hpad[i] = (i < M) ? h[i] : 0.0f;
    }
    dft(hpad, Hre, Him);
    
    for (blk = 0; blk < numblocks; blk++) {
        int start = blk * L - (M - 1);
        for (i = 0; i < N; i++) {
            int idx = start + i;
            block[i] = (idx >= 0 && idx < LX) ? x[idx] : 0.0f;
        }
        
        dft(block, Xre, Xim);
        
        for (i = 0; i < N; i++) {
            Yre[i] = Xre[i] * Hre[i] - Xim[i] * Him[i];
            Yim[i] = Xre[i] * Him[i] + Xim[i] * Hre[i];
        }
        
        idft(Yre, Yim, out);
        
        // Discard first (M-1) samples, save remaining L
        for (i = M - 1; i < N; i++) {
            if (outIdx < (LX + M - 1)) {
                y[outIdx++] = out[i];
            }
        }
    }
    
    printf("Overlap-Save Linear Convolution Output y[n]:\n");
    for (n = 0; n < LX + M - 1; n++) {
        printf("y[%d] = %f\n", n, y[n]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 5: BLOCK CONVOLUTION METHODS
 * PROGRAM 5.2: OVERLAP-ADD LINEAR CONVOLUTION
 * ============================================================================
 * Source Pages: 20 & 21
 * Description: Fast linear block convolution using the Overlap-Add method with
 *              zero-padded block DFTs and addition of overlapping tails.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// Linear Convolution using Overlap-Add Method
#define LX 9
#define M 3
#define N 6
#define L (N - M + 1)
#define PI 3.14159265358979

float x[LX] = {1, 3, 5, 8, 9, 2, 3, 9, 1};
float h[M] = {1, 3, 2};
float y[LX + M - 1];

void dft(float in_re[], float out_re[], float out_im[]) {
    int k, n;
    for (k = 0; k < N; k++) {
        out_re[k] = 0.0f;
        out_im[k] = 0.0f;
        for (n = 0; n < N; n++) {
            float angle = 2.0f * (float)PI * (float)k * (float)n / (float)N;
            out_re[k] += in_re[n] * cosf(angle);
            out_im[k] -= in_re[n] * sinf(angle);
        }
    }
}

void idft(float in_re[], float in_im[], float out_re[]) {
    int n, k;
    for (n = 0; n < N; n++) {
        float sum = 0.0f;
        for (k = 0; k < N; k++) {
            float angle = 2.0f * (float)PI * (float)k * (float)n / (float)N;
            sum += in_re[k] * cosf(angle) - in_im[k] * sinf(angle);
        }
        out_re[n] = sum / (float)N;
    }
}

int main(void) {
    float Hre[N], Him[N], hpad[N];
    float block[N], Xre[N], Xim[N];
    float Yre[N], Yim[N], out[N];
    int i, n, blk;
    int numblocks = (LX + L - 1) / L;
    
    for (i = 0; i < LX + M - 1; i++) {
        y[i] = 0.0f;
    }
    
    for (i = 0; i < N; i++) {
        hpad[i] = (i < M) ? h[i] : 0.0f;
    }
    dft(hpad, Hre, Him);
    
    for (blk = 0; blk < numblocks; blk++) {
        int start = blk * L;
        for (i = 0; i < N; i++) {
            if (i < L && (start + i) < LX)
                block[i] = x[start + i];
            else
                block[i] = 0.0f;
        }
        
        dft(block, Xre, Xim);
        
        for (i = 0; i < N; i++) {
            Yre[i] = Xre[i] * Hre[i] - Xim[i] * Him[i];
            Yim[i] = Xre[i] * Him[i] + Xim[i] * Hre[i];
        }
        
        idft(Yre, Yim, out);
        
        // Add overlapped block segments
        for (i = 0; i < N; i++) {
            if (start + i < LX + M - 1) {
                y[start + i] += out[i];
            }
        }
    }
    
    printf("Overlap-Add Linear Convolution Output y[n]:\n");
    for (n = 0; n < LX + M - 1; n++) {
        printf("y[%d] = %f\n", n, y[n]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 6: DIRECT DFT, IDFT & MATRIX MULTIPLICATION
 * PROGRAM 6.1: DIRECT DFT AND IDFT
 * ============================================================================
 * Source Pages: 22–24
 * Description: Direct O(N^2) evaluation of Discrete Fourier Transform and
 *              Inverse Discrete Fourier Transform on 4-point real sequence {1, 2, 3, 4}.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// Direct DFT and IDFT
#define N 4
#define PI 3.14159265

int main(void) {
    float x[N] = {1, 2, 3, 4};
    float Xr[N], Xi[N];
    float xr[N], xi[N];
    int n, k;
    
    // Direct DFT
    for (k = 0; k < N; k++) {
        Xr[k] = 0.0f;
        Xi[k] = 0.0f;
        for (n = 0; n < N; n++) {
            Xr[k] += x[n] * cosf(2.0f * (float)PI * (float)k * (float)n / (float)N);
            Xi[k] -= x[n] * sinf(2.0f * (float)PI * (float)k * (float)n / (float)N);
        }
    }
    
    printf("DFT Output X[k]:\n");
    for (k = 0; k < N; k++) {
        printf("X[%d] = %.4f + j(%.4f)\n", k, Xr[k], Xi[k]);
    }
    
    // Direct IDFT
    for (n = 0; n < N; n++) {
        xr[n] = 0.0f;
        xi[n] = 0.0f;
        for (k = 0; k < N; k++) {
            xr[n] += Xr[k] * cosf(2.0f * (float)PI * (float)k * (float)n / (float)N) -
                     Xi[k] * sinf(2.0f * (float)PI * (float)k * (float)n / (float)N);
            xi[n] += Xr[k] * sinf(2.0f * (float)PI * (float)k * (float)n / (float)N) +
                     Xi[k] * cosf(2.0f * (float)PI * (float)k * (float)n / (float)N);
        }
        xr[n] /= (float)N;
        xi[n] /= (float)N;
    }
    
    printf("\nIDFT Output x[n]:\n");
    for (n = 0; n < N; n++) {
        printf("x[%d] = %.4f + j(%.4f)\n", n, xr[n], xi[n]);
    }
    
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 6: DIRECT DFT, IDFT & MATRIX MULTIPLICATION
 * PROGRAM 6.2: DFT VIA LINEAR TWIDDLE FACTOR RECURRENCE
 * ============================================================================
 * Source Pages: 24–25
 * Description: Computes DFT using successive complex multiplication by W_N^k
 *              to eliminate repeated trigonometric evaluations per outer loop.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// DFT using Linear Twiddle Factor Recurrence
#define N 4
#define PI 3.14159265

int main(void) {
    float x[N] = {1, 2, 3, 4};
    float Xr[N], Xi[N];
    float Wkr, Wki, Pr, Pi, tr, ti;
    int n, k;
    
    for (k = 0; k < N; k++) {
        Wkr = cosf(2.0f * (float)PI * (float)k / (float)N);
        Wki = -sinf(2.0f * (float)PI * (float)k / (float)N);
        
        Pr = 1.0f;
        Pi = 0.0f;
        Xr[k] = 0.0f;
        Xi[k] = 0.0f;
        
        for (n = 0; n < N; n++) {
            Xr[k] += Pr * x[n];
            Xi[k] += Pi * x[n];
            
            // Advance twiddle power (Pr + j*Pi) * (Wkr + j*Wki)
            tr = Pr * Wkr - Pi * Wki;
            ti = Pr * Wki + Pi * Wkr;
            Pr = tr;
            Pi = ti;
        }
    }
    
    printf("DFT Output X[k]:\n");
    for (k = 0; k < N; k++) {
        printf("X[%d] = %.4f + j(%.4f)\n", k, Xr[k], Xi[k]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 6: DIRECT DFT, IDFT & MATRIX MULTIPLICATION
 * PROGRAM 6.3: MATRIX MULTIPLICATION METHOD FOR DFT
 * ============================================================================
 * Source Pages: 26–28
 * Description: Precomputes the N x N complex twiddle factor matrix W_N and computes
 *              DFT via matrix-vector multiplication X = W * x.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

// Matrix Multiplication Method for DFT
#define N 4
#define PI 3.14159265

int main(void) {
    float x[N] = {1, 2, 3, 4};
    float Wr[N][N], Wi[N][N];
    float Xr[N], Xi[N];
    int n, k;
    
    // Construct Twiddle Matrix W[k][n] = e^(-j*2*PI*k*n/N)
    for (k = 0; k < N; k++) {
        for (n = 0; n < N; n++) {
            Wr[k][n] = cosf(2.0f * (float)PI * (float)k * (float)n / (float)N);
            Wi[k][n] = -sinf(2.0f * (float)PI * (float)k * (float)n / (float)N);
        }
    }
    
    // Matrix-vector product: X = W * x
    for (k = 0; k < N; k++) {
        Xr[k] = 0.0f;
        Xi[k] = 0.0f;
        for (n = 0; n < N; n++) {
            Xr[k] += Wr[k][n] * x[n];
            Xi[k] += Wi[k][n] * x[n];
        }
    }
    
    printf("Matrix DFT Output X[k]:\n");
    for (k = 0; k < N; k++) {
        printf("X[%d] = %.4f + j(%.4f)\n", k, Xr[k], Xi[k]);
    }
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 7: LINEAR AND CIRCULAR CONVOLUTION
 * PROGRAM 7.1: DIRECT LINEAR CONVOLUTION
 * ============================================================================
 * Source Page: 29
 * Description: Standard linear convolution of x[n1]={1, 2, 3} and h[n2]={4, 5}.
 *              Output length is n1 + n2 - 1 = 4. Expected: {4, 13, 22, 15}.
 ******************************************************************************/

#include <stdio.h>

// Linear Convolution
int main(void) {
    int x[] = {1, 2, 3};
    int h[] = {4, 5};
    int y[4] = {0};
    int n1 = 3, n2 = 2;
    int i, j;
    
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            y[i + j] += x[i] * h[j];
        }
    }
    
    printf("Linear Convolution Output:\n");
    for (i = 0; i < n1 + n2 - 1; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");
    // Expected output: 4 13 22 15
    return 0;
}


/*******************************************************************************
 * ============================================================================
 * PART 7: LINEAR AND CIRCULAR CONVOLUTION
 * PROGRAM 7.2: CIRCULAR CONVOLUTION
 * ============================================================================
 * Source Page: 30
 * Description: N-point periodic circular convolution of x={1, 2, 3, 4} and h={1, 1, 1, 1}
 *              with modulo index wrapping: (i - j + N) % N. Expected: {10, 10, 10, 10}.
 ******************************************************************************/

#include <stdio.h>

// Circular Convolution
int main(void) {
    int x[] = {1, 2, 3, 4};
    int h[] = {1, 1, 1, 1};
    int y[4] = {0};
    int N = 4;
    int i, j;
    
    for (i = 0; i < N; i++) {
        y[i] = 0;
        for (j = 0; j < N; j++) {
            y[i] += x[j] * h[(i - j + N) % N];
        }
    }
    
    printf("Output:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");
    // Expected output: 10 10 10 10
    return 0;
}
