#ifndef GEOMETRY
#define GEOMETRY
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
int check_brackets(char input[], int len, int countStart, int answer_point);
int converter(char input[], int len, int countStart, int answer_point, int figure_num, Figure *fig_obj);
int output(char input[], int len, int countStart, int answer_point, int figure_num, Figure *fig_obj);
Figure format_figure(Figure* fig);

#endif