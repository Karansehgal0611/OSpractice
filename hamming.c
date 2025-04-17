#include <stdio.h>
#include <math.h>

int calculateParityBits(int m) {
    int r = 0;
    while ((1 << r) < (m + r + 1)) {
        r++;
    }
    return r;
}

void generateHammingCode(int data[], int m, int code[]) {
    int r = calculateParityBits(m);
    int n = m + r;
    int j = 0, k = 0;

    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) {
            code[i - 1] = 0; // Initialize parity bits to 0
        } else {
            code[i - 1] = data[j++];
        }
    }

    for (int i = 0; i < r; i++) {
        int parityPos = (1 << i);
        int parity = 0;
        for (int j = 1; j <= n; j++) {
            if (j & parityPos) {
                parity ^= code[j - 1];
            }
        }
        code[parityPos - 1] = parity;
    }
}

int detectError(int code[], int n) {
    int r = 0;
    while ((1 << r) < (n + 1)) {
        r++;
    }

    int errorPos = 0;
    for (int i = 0; i < r; i++) {
        int parityPos = (1 << i);
        int parity = 0;
        for (int j = 1; j <= n; j++) {
            if (j & parityPos) {
                parity ^= code[j - 1];
            }
        }
        if (parity) {
            errorPos += parityPos;
        }
    }
    return errorPos;
}

int main() {
    int data[] = {1, 0, 1, 1}; // Example data bits
    int m = sizeof(data) / sizeof(data[0]);
    int r = calculateParityBits(m);
    int n = m + r;
    int code[n];

    generateHammingCode(data, m, code);

    printf("Generated Hamming code: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", code[i]);
    }
    printf("\n");

    // Introduce an error for testing
    code[4] ^= 1;

    int errorPos = detectError(code, n);
    if (errorPos) {
        printf("Error detected at position: %d\n", errorPos);
    } else {
        printf("No error detected.\n");
    }

    return 0;
}