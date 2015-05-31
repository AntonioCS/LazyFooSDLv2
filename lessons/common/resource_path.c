
#include "resource_path.h"

char *resource_path(char *path) {

    char *full_path = calloc(MAX_PATH, sizeof (char));

    if (full_path != NULL) {
        strcat(full_path, RESOURCES_FULLPATH);
        strcat(full_path, path);
    }

    return full_path;
}
