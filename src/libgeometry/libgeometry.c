#include <libgeometry.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int figure_num;
Figure fig_obj[4];

int init(int numberOf)
{
    figure_num = numberOf;
    char circleEx[7] = {"circle"};
    char triangleEx[9] = {"triangle"};
    char input[50] = {'0'};
    int len = 0;
    int countStart = 0;
    printf("Enter %d figure\nexample: triangle(x1 y1, x2 y2, x3 y3, x4 y4), "
           "circle(x1 y2, radius)\n",
           numberOf);
    while ((input[len] = getchar()) != '\n') {
        if (input[len] == '(') {
            countStart = len;
        }
        len++;
    }
    input[len] = '\0';

    if ((input[0] == circleEx[0]) || (input[0] == circleEx[0] - ' ')) {
        if (figure_check(input, circleEx) == 0) {
            fig_obj[numberOf].type = 0;
            if (converter(input, len, countStart, 1) == 0)
                return 100;
        }

    } else if (
            (input[0] == triangleEx[0]) || (input[0] == triangleEx[0] - ' ')) {
        if (figure_check(input, triangleEx) == 0) {
            fig_obj[numberOf].type = 1;
            if (converter(input, len, countStart, 2) == 0)
                return 100;
        }
    } else {
        printf("Please, enter the correct figure! Expected: 'circle' or "
               "'triangle'.\n");
        return 0;
    }
    return 0;
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

int converter(char input[], int len, int countStart, int answer_point)
{
    for (int j = countStart + 1; j < len - 1; j++) {
        if ((input[j] == ',') || (input[j] == '.') || (input[j] == ' ')
            || ((input[j] >= '0') && (input[j] <= '9')))
            continue;
        else {
            printf("Incorrect input!\n");
            return 0;
        }
    }

    if (input[len - 1] != ')') {
        printf("Expected )");
        return 0;
    }
    char converter[20];
    int answer = 0;

    if (answer_point == 1) {
        while (input[countStart] != '\0') {
            int k = 0;
            for (countStart += 1; countStart < len; countStart++) {
                if (input[countStart] == ' ' || input[countStart] == ','
                    || input[countStart] == ')') {
                    continue;
                } else {
                    if (input[countStart + 1] == ' '
                        || input[countStart + 1] == ','
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
    }
    answer = 0;
    if (answer_point == 2) {
        while (input[countStart] != '\0') {
            int k = 0;
            for (countStart += 1; countStart < len; countStart++) {
                if (input[countStart] == ' ' || input[countStart] == ','
                    || input[countStart] == ')') {
                    continue;
                } else {
                    if (input[countStart + 1] == ' '
                        || input[countStart + 1] == ','
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

    if (answer_point == 1) {
        printf("Circle's x = %.2lf, y = %.2lf\n",
               fig_obj[figure_num].center.x,
               fig_obj[figure_num].center.y);
        printf("Circle's radius = %.2lf\n", fig_obj[figure_num].radius);
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
    }
    return 0;
}
