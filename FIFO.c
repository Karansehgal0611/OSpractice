#include <stdio.h>

void FIFO(int pages[], int n, int frames) {
    int frame[frames];
    int index = 0, hit = 0, miss = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("Page\tFrames\t\tStatus\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                hit++;
                break;
            }
        }

        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            miss++;
        }

        printf("%d\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf(found ? "\tHit\n" : "\tMiss\n");
    }

    printf("\nTotal Hits: %d\nTotal Misses: %d\n", hit, miss);
    printf("Hit Ratio: %.2f%%\nMiss Ratio: %.2f%%\n", (float)hit / n * 100, (float)miss / n * 100);
}

int main() {
    int n, frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page references:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    FIFO(pages, n, frames);

    return 0;
}
