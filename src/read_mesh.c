#include "pihm.h"

void ReadMesh(const char *filename, MeshEntry *meshtbl)
{
    FILE *mesh_file;
    int i;
    char cmdstr[MAXSTRING];
    int match;
    int index;
    int lno = 0;

    mesh_file = fopen(filename, "r");
    check_file(mesh_file, filename);
    PIHMprintf(VL_VERBOSE, " Reading %s\n", filename);

    /*
     * Read element mesh block
     */
    NextLine(mesh_file, cmdstr, &lno);
    ReadKeyword(cmdstr, "NUMELE", &num_elements, 'i', filename, lno);

#if defined(_TGM_)
    if (num_elements != 2)
    {
        PIHMprintf(VL_ERROR,
                   "Error: Number of elements should be 2 in two-grid model.\n");
        PIHMexit(EXIT_FAILURE);
    }
#endif

    meshtbl->node = (int **)malloc(num_elements * sizeof(int *));
    meshtbl->nabr = (int **)malloc(num_elements * sizeof(int *));

    /* Skip header line */
    NextLine(mesh_file, cmdstr, &lno);

    for (i = 0; i < num_elements; i++)
    {
        meshtbl->node[i] = (int *)malloc(NUM_EDGE * sizeof(int));
        meshtbl->nabr[i] = (int *)malloc(NUM_EDGE * sizeof(int));

        NextLine(mesh_file, cmdstr, &lno);
        match = sscanf(cmdstr, "%d %d %d %d %d %d %d",
                       &index,
                       &meshtbl->node[i][0], &meshtbl->node[i][1], &meshtbl->node[i][2],
                       &meshtbl->nabr[i][0], &meshtbl->nabr[i][1], &meshtbl->nabr[i][2]);
        if (match != 7 || i != index - 1)
        {
            PIHMprintf(VL_ERROR,
                       "Error reading mesh description of the %dth element.\n", i + 1);
            PIHMprintf(VL_ERROR, "Error in %s near Line %d.\n", filename, lno);
            PIHMexit(EXIT_FAILURE);
        }
    }

    /*
     * Read node_ids block
     */
    NextLine(mesh_file, cmdstr, &lno);
    ReadKeyword(cmdstr, "NUMNODE", &meshtbl->numnode, 'i', filename, lno);

    /* Skip header line */
    NextLine(mesh_file, cmdstr, &lno);

    meshtbl->x = (double *)malloc(meshtbl->numnode * sizeof(double));
    meshtbl->y = (double *)malloc(meshtbl->numnode * sizeof(double));
    meshtbl->zmin = (double *)malloc(meshtbl->numnode * sizeof(double));
    meshtbl->zmax = (double *)malloc(meshtbl->numnode * sizeof(double));

    for (i = 0; i < meshtbl->numnode; i++)
    {
        NextLine(mesh_file, cmdstr, &lno);
        match = sscanf(cmdstr, "%d %lf %lf %lf %lf",
                       &index,
                       &meshtbl->x[i], &meshtbl->y[i],
                       &meshtbl->zmin[i], &meshtbl->zmax[i]);
        if (match != 5 || i != index - 1)
        {
            PIHMprintf(VL_ERROR,
                       "Error reading description of the %dth node_ids!\n", i + 1);
            PIHMprintf(VL_ERROR, "Error in %s near Line %d.\n", filename, lno);
            PIHMexit(EXIT_FAILURE);
        }
    }

    fclose(mesh_file);
}
