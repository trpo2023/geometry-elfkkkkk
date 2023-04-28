#include <ctest.h>
#include <libgeometry.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SQR(x) (x) * (x)

CTEST(geometry_suite, check_triangle_perimeter)
{
    Figure fig_obj_test;
    fig_obj_test.type = 1;
    fig_obj_test.p[0].x = 0;
    fig_obj_test.p[0].y = 0;
    fig_obj_test.p[1].x = 5;
    fig_obj_test.p[1].y = 5;
    fig_obj_test.p[2].x = 10;
    fig_obj_test.p[2].y = 0;
    fig_obj_test.p[3].x = 0;
    fig_obj_test.p[3].y = 0;
    const double expect = 24.14;
    double res = format_figure(&fig_obj_test).perimetr;
    ASSERT_EQUAL(expect, res);
}
CTEST(geometry_suite, check_triangle_squre)
{
    Figure fig_obj_test;
    fig_obj_test.type = 1;
    fig_obj_test.p[0].x = 0;
    fig_obj_test.p[0].y = 0;
    fig_obj_test.p[1].x = 5;
    fig_obj_test.p[1].y = 5;
    fig_obj_test.p[2].x = 10;
    fig_obj_test.p[2].y = 0;
    fig_obj_test.p[3].x = 0;
    fig_obj_test.p[3].y = 0;
    const double expect = 25.00;
    double res = format_figure(&fig_obj_test).squre;
    ASSERT_EQUAL(expect, res);
}
CTEST(geometry_suite, check_triangle_intersection)
{
    Figure fig_obj_test, fig_obj_test2;
    fig_obj_test.type = 1;
    fig_obj_test2.type = 1;
    fig_obj_test.p[0].x = 0;
    fig_obj_test.p[0].y = 0;
    fig_obj_test.p[1].x = 5;
    fig_obj_test.p[1].y = 5;
    fig_obj_test.p[2].x = 10;
    fig_obj_test.p[2].y = 0;
    fig_obj_test.p[3].x = 0;
    fig_obj_test.p[3].y = 0;
    fig_obj_test2.p[0].x = 0;
    fig_obj_test2.p[0].y = 0;
    fig_obj_test2.p[1].x = 5;
    fig_obj_test2.p[1].y = 5;
    fig_obj_test2.p[2].x = 10;
    fig_obj_test2.p[2].y = 0;
    fig_obj_test2.p[3].x = 0;
    fig_obj_test2.p[3].y = 0;

    const double expect = 1;
    double res = figure_intersection(&fig_obj_test, &fig_obj_test2);
    ASSERT_EQUAL(expect, res);
}
CTEST(geometry_suite, check_non_degenerate_triangle)
{
    Figure fig_obj_test;
    fig_obj_test.type = 1;
    fig_obj_test.p[0].x = 0;
    fig_obj_test.p[0].y = 0;
    fig_obj_test.p[1].x = 1;
    fig_obj_test.p[1].y = 1;
    fig_obj_test.p[2].x = 2;
    fig_obj_test.p[2].y = 2;
    fig_obj_test.p[3].x = 0;
    fig_obj_test.p[3].y = 0;
    const double expect = 0;
    double res = format_figure(&fig_obj_test).squre;
    ASSERT_EQUAL(expect, res);
}
CTEST(geometry_suite, check_circle_intersection)
{
    Figure fig_obj_test, fig_obj_test2;
    fig_obj_test.type = 0;
    fig_obj_test2.type = 0;
    fig_obj_test.center.x = 0;
    fig_obj_test.center.y = 0;
    fig_obj_test2.center.x = 0;
    fig_obj_test2.center.y = 0;
    fig_obj_test.radius = 5;
    fig_obj_test2.radius = 5;

    const double expect = 1;
    double res = figure_intersection(&fig_obj_test, &fig_obj_test2);
    ASSERT_EQUAL(expect, res);
}