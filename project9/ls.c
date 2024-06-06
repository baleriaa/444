#include "dir.h"
#include <stdio.h>

void ls(void)
{
    struct directory *dir;
    struct directory_entry ent;

    dir = directory_open(0);

    while (directory_get(dir, &ent) != -1)

    directory_close(dir);
}