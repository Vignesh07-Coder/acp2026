#include <stdio.h>

typedef struct {
    float length;
    float width;
    float area;
} Rectangle;

// Function prototypes
void input(int n, Rectangle rects[n]);
void calculate_area(int n, Rectangle rects[n]);
int findLargestArea(int n, Rectangle rects[n]);
void output(int largestIndex, Rectangle rects[]);

int main() {
    int n;

    printf("Enter the number of rectangles: ");
    scanf("%d", &n);

    Rectangle rects[n];

    input(n, rects);
    calculate_area(n, rects);
    
    int largestIndex = findLargestArea(n, rects);
    
    output(largestIndex, rects);

    return 0;
}

void input(int n, Rectangle rects[n]) {
    for (int i = 0; i < n; i++) {
        printf("\nRectangle %d:\n", i + 1);
        printf("Enter length: ");
        scanf("%f", &rects[i].length);
        printf("Enter width: ");
        scanf("%f", &rects[i].width);
    }
}

void calculate_area(int n, Rectangle rects[n]) {
    for (int i = 0; i < n; i++) {
        rects[i].area = rects[i].length * rects[i].width;
        printf("Area of Rectangle %d: %.2f\n", i + 1, rects[i].area);
    }
}

int findLargestArea(int n, Rectangle rects[n]) {
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (rects[i].area > rects[maxIdx].area) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

void output(int largestIndex, Rectangle rects[]) {
    printf("\n--- Result ---\n");
    printf("The rectangle with the largest area is Rectangle %d\n", largestIndex + 1);
    printf("Dimensions: %.2f x %.2f\n", rects[largestIndex].length, rects[largestIndex].width);
    printf("Area: %.2f\n", rects[largestIndex].area);
}
