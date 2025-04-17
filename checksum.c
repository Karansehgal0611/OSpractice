#include <stdio.h>
#include <stdint.h>

// Function to calculate checksum
uint16_t calculate_checksum(uint16_t *data, size_t length) {
    uint32_t sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += data[i];
        if (sum & 0xFFFF0000) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
    }
    return ~sum;
}

// Function to verify checksum
int verify_checksum(uint16_t *data, size_t length, uint16_t checksum) {
    uint32_t sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += data[i];
        if (sum & 0xFFFF0000) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
    }
    sum += checksum;
    return (sum == 0xFFFF);
}

int main() {
    uint16_t data[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    size_t length = sizeof(data) / sizeof(data[0]);

    uint16_t checksum = calculate_checksum(data, length);
    printf("Calculated checksum: 0x%04X\n", checksum);

    if (verify_checksum(data, length, checksum)) {
        printf("Checksum verification passed.\n");
    } else {
        printf("Checksum verification failed.\n");
    }

    return 0;
}