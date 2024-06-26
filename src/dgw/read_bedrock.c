#include "pihm.h"

void ReadBedrock(const char *filename, ElementAttribute *atttbl,
                 MeshEntry *meshtbl, RunParameters *ctrl)
{
    FILE *br_file;
    int i;
    char cmdstr[MAXSTRING];
    int match;
    int index;
    int lno = 0;

    br_file = fopen(filename, "r");
    check_file(br_file, filename);
    PIHMprintf(VL_VERBOSE, " Reading %s\n", filename);

    /* Start reading bedrock file */
    /* Read fbr boundary conditions */
    atttbl->fbr_bc = (int **)malloc(num_elements * sizeof(int *));
    for (i = 0; i < num_elements; i++)
    {
        atttbl->fbr_bc[i] = (int *)malloc(NUM_EDGE * sizeof(int));
    }

    /* Skip header line */
    NextLine(br_file, cmdstr, &lno);
    for (i = 0; i < num_elements; i++)
    {
        NextLine(br_file, cmdstr, &lno);
        match = sscanf(cmdstr, "%d %d %d %d",
                       &index,
                       &atttbl->fbr_bc[i][0], &atttbl->fbr_bc[i][1],
                       &atttbl->fbr_bc[i][2]);
        if (match != 4 || i != index - 1)
        {
            PIHMprintf(VL_ERROR,
                       "Error reading boundary condition type for fractured bedrock"
                       "layer of the %dth element.\n",
                       i + 1);
            PIHMprintf(VL_ERROR, "Error in %s near Line %d.\n", filename, lno);
            PIHMexit(EXIT_FAILURE);
        }
    }

    /* Read bedrock elevations */
    meshtbl->zbed = (double *)malloc(meshtbl->numnode * sizeof(double));

    /* Skip header line */
    NextLine(br_file, cmdstr, &lno);
    for (i = 0; i < meshtbl->numnode; i++)
    {
        NextLine(br_file, cmdstr, &lno);
        match = sscanf(cmdstr, "%d %lf", &index, &meshtbl->zbed[i]);
        if (match != 2 || i != index - 1)
        {
            PIHMprintf(VL_ERROR,
                       "Error reading bedrock description of the %dth node.\n", i + 1);
            PIHMprintf(VL_ERROR, "Error in %s near Line %d.\n", filename, lno);
            PIHMexit(EXIT_FAILURE);
        }
    }

    NextLine(br_file, cmdstr, &lno);
    ctrl->prtvrbl[FBRUNSAT_CTRL] =
        ReadPrtCtrl(cmdstr, "FBRUNSAT", filename, lno);

    NextLine(br_file, cmdstr, &lno);
    ctrl->prtvrbl[FBRGW_CTRL] = ReadPrtCtrl(cmdstr, "FBRGW", filename, lno);

    NextLine(br_file, cmdstr, &lno);
    ctrl->prtvrbl[FBRINFIL_CTRL] =
        ReadPrtCtrl(cmdstr, "FBRINFIL", filename, lno);

    NextLine(br_file, cmdstr, &lno);
    ctrl->prtvrbl[FBRRECHG_CTRL] =
        ReadPrtCtrl(cmdstr, "FBRRECHG", filename, lno);

    NextLine(br_file, cmdstr, &lno);
    ctrl->prtvrbl[FBRFLOW_CTRL] =
        ReadPrtCtrl(cmdstr, "FBRFLOW", filename, lno);

    fclose(br_file);
}
