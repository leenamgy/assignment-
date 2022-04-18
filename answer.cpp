#include <stdio.h>

typedef struct point {
	int x;
	int y;
}POINT;

POINT swap(POINT q);
POINT point_move(POINT p, POINT delta);
int area(POINT *left_bottom, POINT *right_top);

int main() {
	POINT p = { 10, 20 };
	p = swap(p);
	printf("swap(p) = { %d,  %d }\n", p.x, p.y);

	POINT q = { 2,2 }, delta = { 1,1 };
	POINT result;
	POINT *ptr = &result;

	result = point_move(q, delta);
	printf("result = { %d, %d }\n", result.x, result.y);
	printf("x = %d, y = %d \n", ptr->x, ptr->y);

	POINT Left = { 3, 5 }, Right = { 1, 3 };
	int Area = 0;
	Area = area(&Left, &Right);
	printf("Area = %d\n", Area);
}

POINT swap(POINT q) {
	POINT T;
	T.x = q.y;
	T.y = q.x;
	return T;
}
POINT point_move(POINT p, POINT delta) {
	POINT result;
	result.x = p.x + delta.x;
	result.y = p.y + delta.y;
	return result;
}
int area(POINT *left_bottom, POINT *right_top)
{
	return (right_top->x - left_bottom->x) * (right_top->y - left_bottom->y);
}