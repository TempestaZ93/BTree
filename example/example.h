#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"

int cmp_data(void *d1, void *d2) {
    char *string1 = ((char *)d1);
    char *string2 = ((char *)d2);

    return strcmp(string1, string2);
}
