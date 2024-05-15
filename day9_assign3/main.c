#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main()
{
	printf("Area of circle: %d\n",carea(5));

	printf("perimeter of circle: %d\n",cperi(5));

	printf("Area of Square: %d\n",sarea(4));

	printf("Perimeter of Square: %d\n",speri(4));

	printf("Area of Rectangle: %d\n",rarea(3,2));

	printf("Perimeter of Rectangle: %d\n",rperi(3,2));
}

