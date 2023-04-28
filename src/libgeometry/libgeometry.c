#include <libgeometry.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SQR(x) (x) * (x)

int init(int numberOf)
{
    Figure fig_obj[4];
    char circleExpect[7] = {"circle"};
    char triangleExpect[9] = {"triangle"};
    char input[50] = {'0'};
    int len = 0;
    int countStart = 0;
    printf("Enter %d figure\nexample: triangle((x1 y1, x2 y2, x3 y3, x4 y4)), "
           "circle(x1 y2, radius)\n",
           numberOf);
    while ((input[len] = getchar()) != '\n') {
        if (input[len] == '(') {
            countStart = len;
        }
        len++;
    }
    input[len] = '\0';

    if ((input[0] == circleExpect[0]) || (input[0] == circleExpect[0] - ' ')) {
        if (figure_check(input, circleExpect) == 0) {
            fig_obj[numberOf].type = 0;
            if (check_brackets(input, len, countStart, 1) == 100)
                return 0;
            if (converter(input, len, countStart, 1, numberOf, fig_obj) == 100)
                return 0;
            if (output(input, len, countStart, 1, numberOf, fig_obj) == -1)
                return 0;
        }

    } else if (
            (input[0] == triangleExpect[0])
            || (input[0] == triangleExpect[0] - ' ')) {
        if (figure_check(input, triangleExpect) == 0) {
            fig_obj[numberOf].type = 1;
            if (check_brackets(input, len, countStart, 2) == 100)
                return 0;
            if (converter(input, len, countStart, 2, numberOf, fig_obj) == 100)
                return 0;
            if (output(input, len, countStart, 2, numberOf, fig_obj) == -1)
                return 0;
        }
    } else {
        printf("Please, enter the correct figure! Expected: 'circle' or "
               "'triangle'.\n");
        return 0;
    }
    return 100;
}

int figure_check(char a[], char b[])
{
    for (int i = 1; a[i] != '('; i++) {
        if ((a[i] == b[i]) || (a[i] == b[i] - ' ')) {
            continue;
        } else {
            printf("Undefined figure. Maybe you put something between command "
                   "and '(', check it.\n");
            return 0;
        }
    }
    return 0;
}

int check_brackets(char input[], int len, int countStart, int answer_point)
{
    if (answer_point == 1) {
        for (int j = countStart + 1; j < len - 1; j++) {
            if ((input[j] == ',') || (input[j] == '.') || (input[j] == ' ')
                || ((input[j] >= '0') && (input[j] <= '9')))
                continue;
            else {
                return 100;
            }
        }
    }
    if (answer_point == 2) {
        if (input[9] != '(') {
            return 100;
        }
        for (int j = countStart + 2; j < len - 2; j++) {
            if ((input[j] == ',') || (input[j] == '.') || (input[j] == ' ')
                || ((input[j] >= '0') && (input[j] <= '9')))
                continue;
            else {
                return 100;
            }
        }
    }
    if (input[len - 1] != ')') {
        return 100;
    }
    return 0;
}

int converter(char input[], int len, int countStart, int answer_point, int figure_num, Figure *fig_obj)
{
    char converter[20];
    int answer = 0;

    while (input[countStart] != '\0') {
        int k = 0;
        for (countStart += 1; countStart < len; countStart++) {
            if (input[countStart] == ' ' || input[countStart] == ','
                || input[countStart] == ')') {
                continue;
            } else {
                if ((input[countStart + 1] == ',') && (answer == 0)
                    && (answer_point == 1)) {
                    return 100;
                }
                if (input[countStart + 1] == ' ' || input[countStart + 1] == ','
                    || input[countStart + 1] == ')') {
                    converter[k] = input[countStart];
                    converter[k + 1] = '\0';
                    countStart++;
                    answer++;
                    break;
                }
                converter[k] = input[countStart];
                k++;
            }
        }
        if (answer_point == 1) {
            if (answer == 1) {
                fig_obj[figure_num].center.x = atof(converter);
            }
            if (answer == 2) {
                fig_obj[figure_num].center.y = atof(converter);
            }
            if (answer == 3) {
                fig_obj[figure_num].radius = atof(converter);
            }
        }
        if (answer_point == 2) {
            switch (answer) {
            case 1:
                fig_obj[figure_num].p[0].x = atof(converter);
                break;

            case 2:
                fig_obj[figure_num].p[0].y = atof(converter);
                break;

            case 3:
                fig_obj[figure_num].p[1].x = atof(converter);
                break;

            case 4:
                fig_obj[figure_num].p[1].y = atof(converter);
                break;

            case 5:
                fig_obj[figure_num].p[2].x = atof(converter);
                break;

            case 6:
                fig_obj[figure_num].p[2].y = atof(converter);
                break;

            case 7:
                fig_obj[figure_num].p[3].x = atof(converter);
                break;

            case 8:
                fig_obj[figure_num].p[3].y = atof(converter);
                break;
            }
        }
    }
    return 0;
}

int output(char input[], int len, int countStart, int answer_point, int figure_num, Figure *fig_obj)
{
    if (answer_point == 1) {
        printf("Circle's x = %.2lf, y = %.2lf\n",
               fig_obj[figure_num].center.x,
               fig_obj[figure_num].center.y);
        printf("Circle's radius = %.2lf\n", fig_obj[figure_num].radius);
        fig_obj[figure_num] = format_figure(&fig_obj[figure_num]);
        printf("Perimeter of circle = %lf\n", fig_obj[figure_num].perimetr);
        printf("Square of circle = %lf\n", fig_obj[figure_num].squre);
    }
    if (answer_point == 2) {
        if ((fig_obj[figure_num].p[0].x != fig_obj[figure_num].p[3].x)
            && (fig_obj[figure_num].p[0].y != fig_obj[figure_num].p[3].y)) {
            printf("First and last coordinate can't be different!\n");
            return -1;
        }

        for (int k = 0; k < 4; k++) {
            printf("Triangle's x%d = %.2lf, y%d = %.2lf\n",
                   k + 1,
                   fig_obj[figure_num].p[k].x,
                   k + 1,
                   fig_obj[figure_num].p[k].y);
        }
        fig_obj[figure_num] = format_figure(&fig_obj[figure_num]);
        if (fig_obj[figure_num].perimetr && fig_obj[figure_num].squre) {
            printf("Perimeter of triangle = %.2lf\n",
                   fig_obj[figure_num].perimetr);
            printf("Square of triangle = %lf\n", fig_obj[figure_num].squre);
        }
    }
    return 0;
}

Figure format_figure(Figure* fig)
{
    if (fig->type == 1) {
        double first_side
                = sqrt(SQR((fig->p[1].x - fig->p[0].x))
                       + SQR((fig->p[1].y - fig->p[0].y)));
        double second_side
                = sqrt(SQR((fig->p[2].x - fig->p[1].x))
                       + SQR((fig->p[2].y - fig->p[1].y)));
        double third_side
                = sqrt(SQR((fig->p[3].x - fig->p[2].x))
                       + SQR((fig->p[3].y - fig->p[2].y)));
        if ((first_side < second_side + third_side)
            && (second_side < first_side + third_side)
            && (third_side < second_side + first_side)) {
            fig->perimetr = first_side + second_side + third_side;
            double halfp = fig->perimetr / 2;
            fig->squre
                    = sqrt(halfp * (halfp - first_side) * (halfp - second_side)
                           * (halfp - third_side));
            return *fig;

        } 
        // else {
        //     printf("Non-degenerate triangle!\n");
        // }
    }
    if (fig->type == 0) {
        fig->squre = M_PI * SQR(fig->radius);
        fig->perimetr = 2 * M_PI * fig->radius;
        return *fig;
    }
    return *fig;
}

void intersection_output(int figure_num, Figure *fig_obj)
{
    if (((fig_obj[1].squre > 0) && fig_obj[2].squre > 0)
        && (fig_obj[3].squre > 0)) {
        if ((fig_obj[1].squre > 0) && fig_obj[2].squre > 0) {
            if (figure_intersection(&fig_obj[1], &fig_obj[2]) == 1) {
                fig_obj[1].intersect[2] = 1;
                fig_obj[2].intersect[1] = 1;
            }
        }

        if ((fig_obj[2].squre > 0) && fig_obj[3].squre > 0) {
            if (figure_intersection(&fig_obj[2], &fig_obj[3]) == 1) {
                fig_obj[2].intersect[3] = 1;
                fig_obj[3].intersect[2] = 1;
            }
        }

        if ((fig_obj[1].squre > 0) && fig_obj[3].squre > 0)
            if (figure_intersection(&fig_obj[1], &fig_obj[3]) == 1) {
                {
                    fig_obj[1].intersect[3] = 1;
                    fig_obj[3].intersect[1] = 1;
                }
            }
        printf("\n");
        for (int i = 1; i < 4; i++) {
            printf("Figure №%d intersections:\n", i);
            for (int j = 0; j < 4; j++) {
                if (fig_obj[i].intersect[j] == 1) {
                    printf("figure №%d\n", j);
                }
            }
            printf("\n");
        }
    }
}

void swap(double* xp, double* yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int figure_intersection(Figure* fig, Figure* fig2)
{
    if ((fig->type == 0) && (fig2->type == 0)) {
        double d = (fig->center.x - fig2->center.x)
                        * (fig->center.x - fig2->center.x)
                + (fig->center.y - fig2->center.y)
                        * (fig->center.y - fig2->center.y);

        if (d <= (fig->radius + fig2->radius) * (fig->radius + fig2->radius)
            && d >= (fig->radius > fig2->radius ? fig->radius - fig2->radius
                                                : fig2->radius - fig->radius))
            return 1;
        else
            return 0;
        ;
    }

    if ((fig->type == 1) && (fig2->type == 1)) {
        int ff = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ff = cross_segment(
                        fig->p[i].x,
                        fig->p[i].y,
                        fig->p[i + 1].x,
                        fig->p[i + 1].y,
                        fig2->p[j].x,
                        fig2->p[j].y,
                        fig2->p[j + 1].x,
                        fig2->p[j + 1].y);
            }
        }
        if (ff) {
            return 1;
        }
        return 0;
    }

    if (((fig->type == 0) && (fig2->type == 1))
        || ((fig->type == 1) && (fig2->type == 0))) {
        if (fig->type == 0) {
            return tri_cir_intersection(fig, fig2);
        }
        if (fig->type == 1)
            return tri_cir_intersection(fig2, fig);
    }
    return 0;
}

double s_n(Figure* fig, int n)
{
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        double det = fig->p[i % n].x * fig->p[(i + 1) % n].y
                - fig->p[(i + 1) % n].x * fig->p[i % n].y;
        sum += det;
    }
    return fabs(sum / 2);
}

int tri_cir_intersection(Figure* fig, Figure* fig2)
{
    const double eps = 1e-10;
    double x0 = fig->center.x;
    double y0 = fig->center.y;
    double r = fig->radius;
    double x1, x2, y1, y2;
    int track = 0;
    for (int i = 0; i < 3; i++) {
        x1 = fig2->p[i].x;
        y1 = fig2->p[i].y;
        x2 = fig2->p[i + 1].x;
        y2 = fig2->p[i + 1].y;

        double dx01 = x1 - x0, dy01 = y1 - y0, dx12 = x2 - x1, dy12 = y2 - y1;
        double a = SQR(dx12) + SQR(dy12);
        if (fabs(a) < eps) {
            printf("Начало и конец отрезка совпадают!\n");
            return 0;
        }
        double k = dx01 * dx12 + dy01 * dy12;
        double c = SQR(dx01) + SQR(dy01) - SQR(r);
        double d1 = SQR(k) - a * c;
        if (d1 < 0)
            printf("Прямая не пересекается с окружностью - отрезок снаружи\n");
        else if (fabs(d1) < eps) {
            double t = -k / a;
            track++;
            printf("Прямая касается окружности в точке\n");
            if (t > 0 - eps && t < 1 + eps) {
                track++;
                printf("Отрезок снаружи, имеет общую точку с окружностью\n");
            } else {
                printf("Отрезок строго снаружи\n");
            }
        } else {
            double t1 = (-k + sqrt(d1)) / a, t2 = (-k - sqrt(d1)) / a;
            if (t1 > t2)
                swap(&t1, &t2);

            printf("Прямая пересекает окружность в двух точках\n");

            if (t1 >= 0 - eps && t2 <= 1 + eps) {
                if (t1 > 0 - eps && t2 < 1 + eps) {
                    track++;
                    printf("Отрезок строго внутри\n");
                } else {
                    printf("Отрезок внутри, имеет  как минимум одну общую "
                           "точку с окружностью\n");
                    track++;
                }
            }

            else if ((t2 <= 0 + eps) || (t1 >= 1 - eps)) {
                if (!(t2 < 0 + eps || t1 > 1 - eps)) {
                    track++;
                    printf("Отрезок строго снаружи\n");
                } else {
                    track++;
                    printf("Отрезок снаружи, имеет общую точку с "
                           "окружностью\n");
                }

            } else {
                track++;
                printf("Отрезок пересекает окружность в двух точках\n");
            }
        }
    }
    if (track > 0)
        return 1;
    return 0;
}

int cross_segment(
        double x1,
        double y1,
        double x2,
        double y2,
        double x3,
        double y3,
        double x4,
        double y4)
{
    double denum = (y4 - y3) * (x1 - x2) - (x4 - x3) * (y1 - y2);
    int ff = 0;
    if (denum == 0) {
        if ((x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1)
                    == 0
            && (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1)
                    == 0)
            ff = 1;
        else
            ff = 0;
    } else {
        double num_a = (x4 - x2) * (y4 - y3) - (x4 - x3) * (y4 - y2);
        double num_b = (x1 - x2) * (y4 - y2) - (x4 - x2) * (y1 - y2);
        double Ua = num_a / denum;
        double Ub = num_b / denum;

        ff = (Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1 ? 1 : 0);
    }
    return ff;
}