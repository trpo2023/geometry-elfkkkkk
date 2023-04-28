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

int converter(
        char input[],
        int len,
        int countStart,
        int answer_point,
        int figure_num,
        Figure* fig_obj)
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

int output(
        char input[],
        int len,
        int countStart,
        int answer_point,
        int figure_num,
        Figure* fig_obj)
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

        } else {
            printf("Non-degenerate triangle!\n");
        }
    }
    if (fig->type == 0) {
        fig->squre = M_PI * SQR(fig->radius);
        fig->perimetr = 2 * M_PI * fig->radius;
        return *fig;
    }
    return *fig;
}