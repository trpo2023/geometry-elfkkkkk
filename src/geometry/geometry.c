#include <libgeometry.h>

int main()
{
    for (int i = 1; i <= 3; i++) {
        if (init(i) == 0)
            return 1;
    }
    return 0;
}