#include <stdio.h>

int findOptimal(int pages[], int frame[], int n, int frames, int current) {
    int farthest = current, pos = -1;

    for (int i = 0; i < frames; i++) {
        int j;
        for (j = current; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        if (j == n) {
            return i;
        }
    }
    return (pos == -1) ? 0 : pos;
}

void Optimal(int pages[], int n, int frames) {
    int frame[frames];
    int hit = 0, miss = 0;

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
            int pos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = findOptimal(pages, frame, n, frames, i + 1);
            }

            frame[pos] = pages[i];
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

    Optimal(pages, n, frames);

    return 0;
}
