/* finding the area of a circle */

#include <stdio.h>
#define PI 3.14159

int main()
{
    double area;
    double radius;

    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);

    area = PI * radius * radius;

    printf("The area of the circle is: %.2lf\n", area);
    return 0;

}

