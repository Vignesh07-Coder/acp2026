#include <stdio.h>

typedef struct {
    char name[50];
    float length;
    float width;
    float area;
} Rectangle;

Rectangle input(int n);
float calculate_area(Rectangle rect);
void compare_areas(Rectangle r1, Rectangle r2, Rectangle r3);

int main() {
    Rectangle r1, r2, r3;

    r1 = input(1);
    r1.area = calculate_area(r1);

    r2 = input(2);
    r2.area = calculate_area(r2);

    r3 = input(3); // Fixed the variable assignment here
    r3.area = calculate_area(r3);

    printf("\nResult:\n");
    compare_areas(r1, r2, r3);

    return 0;
}

Rectangle input(int n) {
    Rectangle rect;
    printf("Enter details of Rectangle %d\n", n);
    printf("Enter length: ");
    scanf("%f", &rect.length);
    printf("Enter width: ");
    scanf("%f", &rect.width);
    printf("\n");
    return rect;
}

float calculate_area(Rectangle rect) {
    return rect.length * rect.width;
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
    else if (r1.area == r2.area && r1.area > r3.area) {
        printf("Rectangle 1 and Rectangle 2 have the largest equal area = %.0f", r1.area);
    }
    else if (r1.area == r3.area && r1.area > r2.area) {
        printf("Rectangle 1 and Rectangle 3 have the largest equal area = %.0f", r1.area);
    }
    else if (r2.area == r3.area && r2.area > r1.area) {
        printf("Rectangle 2 and Rectangle 3 have the largest equal area = %.0f", r2.area);
    }
    else {
        printf("All three rectangles have the same area = %.0f", r1.area);
    }
}
