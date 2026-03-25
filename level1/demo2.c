#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

typedef struct {
    float length;
    float width;
    float area;
} Rectangle;

int safe_input(Rectangle *rect, int n);
float calculate_area(Rectangle rect);
void compare_areas(Rectangle r1, Rectangle r2, Rectangle r3);
int is_equal(float a, float b);

int main() {
    Rectangle r1, r2, r3;

    if (!safe_input(&r1, 1)) return 1;
    r1.area = calculate_area(r1);

    if (!safe_input(&r2, 2)) return 1;
    r2.area = calculate_area(r2);

    if (!safe_input(&r3, 3)) return 1;
    r3.area = calculate_area(r3);

    printf("\nResult:\n");
    compare_areas(r1, r2, r3);

    return 0;
}

int safe_input(Rectangle *rect, int n) {
    printf("Enter details of Rectangle %d\n", n);

    printf("Enter length: ");
    if (scanf("%f", &rect->length) != 1 || isnan(rect->length) || rect->length <= 0) {
        printf("Invalid input\n");
        return 0;
    }

    printf("Enter width: ");
    if (scanf("%f", &rect->width) != 1 || isnan(rect->width) || rect->width <= 0) {
        printf("Invalid input\n");
        return 0;
    }

    printf("\n");
    return 1;
}

float calculate_area(Rectangle rect) {
    return rect.length * rect.width;
}

int is_equal(float a, float b) {
    return fabs(a - b) < EPSILON;
}

void compare_areas(Rectangle r1, Rectangle r2, Rectangle r3) {

    if (r1.area > r2.area && r1.area > r3.area) {
        printf("Rectangle 1 has the largest area = %.0f", r1.area);
    }
    else if (r2.area > r1.area && r2.area > r3.area) {
        printf("Rectangle 2 has the largest area = %.0f", r2.area);
    }
    else if (r3.area > r1.area && r3.area > r2.area) {
        printf("Rectangle 3 has the largest area = %.0f", r3.area);
    }

    else if (is_equal(r1.area, r2.area) && r1.area > r3.area) {
        printf("Rectangle 1 and Rectangle 2 have the largest equal area = %.0f", r1.area);
    }
    else if (is_equal(r1.area, r3.area) && r1.area > r2.area) {
        printf("Rectangle 1 and Rectangle 3 have the largest equal area = %.0f", r1.area);
    }
    else if (is_equal(r2.area, r3.area) && r2.area > r1.area) {
        printf("Rectangle 2 and Rectangle 3 have the largest equal area = %.0f", r2.area);
    }

    else if (is_equal(r1.area, r2.area) && is_equal(r2.area, r3.area)) {
        printf("All three rectangles have the same area = %.0f", r1.area);
    }

    else {
        printf("Unexpected case\n"); 
    }
}