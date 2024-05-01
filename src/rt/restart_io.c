#include "pihm.h"

void WriteRtIc(const char *outputdir, const ChemicalEntry chemtbl[],
               const ReactionNetwork *rttbl, MeshElement elem[])
{
    FILE *file_pointer;
    char restart_fn[2 * MAXSTRING];

    sprintf(restart_fn, "%s/restart/%s.rtic", outputdir, project);

    file_pointer = fopen(restart_fn, "wb");
    check_file(file_pointer, restart_fn);
    PIHMprintf(VL_VERBOSE, "Writing RT initial conditions.\n");

    for (int i = 0; i < num_elements; i++)
    {

        for (int k = 0; k < MAXSPS; k++)
        {
            if (k < rttbl->NumStc && chemtbl[k].itype == MINERAL)
            {
                elem[i].chms_unsat.t_conc[k] /= (rttbl->RelMin == 0) ? 1000.0 / chemtbl[k].MolarVolume / elem[i].soil.smcmax : (1.0 - elem[i].soil.smcmax) * 1000.0 / chemtbl[k].MolarVolume / elem[i].soil.smcmax;
                elem[i].chms_gw.t_conc[k] /= (rttbl->RelMin == 0) ? 1000.0 / chemtbl[k].MolarVolume / elem[i].soil.smcmax : (1.0 - elem[i].soil.smcmax) * 1000.0 / chemtbl[k].MolarVolume / elem[i].soil.smcmax;
#if defined(_FBR_)
                elem[i].chms_fbrunsat.t_conc[k] /= (rttbl->RelMin == 0) ? 1000.0 / chemtbl[k].MolarVolume / elem[i].geol.smcmax : (1.0 - elem[i].geol.smcmax) * 1000.0 / chemtbl[k].MolarVolume / elem[i].geol.smcmax;
                elem[i].chms_fbrgw.t_conc[k] /= (rttbl->RelMin == 0) ? 1000.0 / chemtbl[k].MolarVolume / elem[i].geol.smcmax : (1.0 - elem[i].geol.smcmax) * 1000.0 / chemtbl[k].MolarVolume / elem[i].geol.smcmax;
#endif
            }
            else if (k < rttbl->NumStc && (chemtbl[k].itype == CATION_ECHG ||
                                           chemtbl[k].itype == ADSORPTION))
            {
                elem[i].chms_unsat.t_conc[k] /=
                    (1.0 - elem[i].soil.smcmax) * 2650.0;
                elem[i].chms_gw.t_conc[k] /=
                    (1.0 - elem[i].soil.smcmax) * 2650.0;
#if defined(_FBR_)
                elem[i].chms_fbrunsat.t_conc[k] /=
                    (1.0 - elem[i].geol.smcmax) * 2650.0;
                elem[i].chms_fbrgw.t_conc[k] /=
                    (1.0 - elem[i].geol.smcmax) * 2650.0;
#endif
            }

            elem[i].restart_output[UNSAT_CHMVOL].t_conc[k] =
                elem[i].chms_unsat.t_conc[k];
            elem[i].restart_output[UNSAT_CHMVOL].ssa[k] =
                elem[i].chms_unsat.ssa[k];

            elem[i].restart_output[GW_CHMVOL].t_conc[k] =
                elem[i].chms_gw.t_conc[k];
            elem[i].restart_output[GW_CHMVOL].ssa[k] =
                elem[i].chms_gw.ssa[k];
#if defined(_FBR_)
            elem[i].restart_output[FBRUNSAT_CHMVOL].t_conc[k] =
                elem[i].chms_fbrunsat.t_conc[k];
            elem[i].restart_output[FBRUNSAT_CHMVOL].ssa[k] =
                elem[i].chms_fbrunsat.ssa[k];

            elem[i].restart_output[FBRGW_CHMVOL].t_conc[k] =
                elem[i].chms_fbrgw.t_conc[k];
            elem[i].restart_output[FBRGW_CHMVOL].ssa[k] =
                elem[i].chms_fbrgw.ssa[k];
#endif
        }

        for (int j = 0; j < NCHMVOL; j++)
        {
            fwrite(&(elem[i].restart_output[j]), sizeof(ConcSSA), 1, file_pointer);
        }
    }

    fclose(file_pointer);
}

void ReadRtIc(const char *fn, MeshElement elem[])
{
    FILE *file_pointer;
    int i;

    file_pointer = fopen(fn, "rb");
    check_file(file_pointer, fn);
    PIHMprintf(VL_VERBOSE, " Reading %s\n", fn);

    for (i = 0; i < num_elements; i++)
    {
        int j;

        for (j = 0; j < NCHMVOL; j++)
        {
            fread(&elem[i].restart_input[j], sizeof(ConcSSA), 1, file_pointer);
        }
    }

    fclose(file_pointer);
}
