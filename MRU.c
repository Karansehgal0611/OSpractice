#include <stdio.h>

int findMRU(int time[], int frames) {
    int max_time = time[0], pos = 0;
    for (int i = 1; i < frames; i++) {
        if (time[i] > max_time) {
            max_time = time[i];
            pos = i;
        }
    }
    return pos;
}

void MRU(int pages[], int n, int frames) {
    int frame[frames];
    int time[frames];
    int hit = 0, miss = 0, counter = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("Page\tFrames\t\tStatus\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                hit++;
                counter++;
                time[j] = counter;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = findMRU(time, frames);
            }

            frame[pos] = pages[i];
            counter++;
            time[pos] = counter;
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

    MRU(pages, n, frames);

    return 0;
}
