#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TIMEOUT 5

typedef struct {
    int seq_num;
    char data[1024];
} Packet;

bool send_packet(Packet packet) {
    // Simulate packet sending with a random success/failure
    return rand() % 2 == 0;
}

bool receive_ack(int seq_num) {
    // Simulate ACK reception with a random success/failure
    return rand() % 2 == 0;
}

void stop_and_wait_protocol() {
    Packet packet;
    int seq_num = 0;
    bool ack_received = false;
    time_t start_time, current_time;

    while (true) {
        // Prepare the packet
        packet.seq_num = seq_num;
        snprintf(packet.data, sizeof(packet.data), "Data packet %d", seq_num);

        // Send the packet
        printf("Sending packet with sequence number %d\n", seq_num);
        if (!send_packet(packet)) {
            printf("Failed to send packet %d\n", seq_num);
            continue;
        }

        // Wait for ACK
        start_time = time(NULL);
        while (true) {
            current_time = time(NULL);
            if (difftime(current_time, start_time) > TIMEOUT) {
                printf("Timeout waiting for ACK %d\n", seq_num);
                break;
            }

            if (receive_ack(seq_num)) {
                printf("Received ACK for packet %d\n", seq_num);
                ack_received = true;
                break;
            }
        }

        if (ack_received) {
            seq_num = (seq_num + 1) % 2; // Toggle sequence number between 0 and 1
            ack_received = false;
        }
    }
}

int main() {
    srand(time(NULL));
    stop_and_wait_protocol();
    return 0;
}