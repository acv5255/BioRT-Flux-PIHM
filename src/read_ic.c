#include "pihm.h"

void ReadIc(const char *filename, MeshElement *elem, river_struct *river)
{
    FILE *ic_file;
    int i;
    int size;

    ic_file = fopen(filename, "rb");
    check_file(ic_file, filename);
    PIHMprintf(VL_VERBOSE, " Reading %s\n", filename);

    fseek(ic_file, 0L, SEEK_END);
    size = ftell(ic_file);

    if (size !=
        (int)(sizeof(ic_struct) * num_elements + sizeof(river_ic_struct) * num_river))
    {
        PIHMprintf(VL_ERROR,
                   "Error in initial condition file %s.\n"
                   "The file size does not match requirement.\n",
                   filename);
        PIHMprintf(VL_ERROR, "Please use a correct initial condition file.\n");
        PIHMexit(EXIT_FAILURE);
    }

    fseek(ic_file, 0L, SEEK_SET);

    for (i = 0; i < num_elements; i++)
    {
        fread(&elem[i].ic, sizeof(ic_struct), 1, ic_file);
    }

    for (i = 0; i < num_river; i++)
    {
        fread(&river[i].ic, sizeof(river_ic_struct), 1, ic_file);
    }

    fclose(ic_file);
}
