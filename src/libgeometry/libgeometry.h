#ifndef GEOMETRY
#define GEOMETRY

int init();

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p[4];
    Point center;
    double radius;
    double squre;
    double perimetr;
    int type;
    int intersect[4];
} Figure;

int init(int numberOf);
int figure_check(char a[], char b[]);
int converter(char input[], int len, int countStart, int answer_point);
Figure format_figure(Figure* fig);

#endif