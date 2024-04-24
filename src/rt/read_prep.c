#include "pihm.h"

void ReadPrep(const char filen[], const chemtbl_struct chemtbl[],
              const rttbl_struct *rttbl, forc_struct *forc)
{
    FILE *fp;
    int lno = 0;
    int match;
    int bytes_now;
    int bytes_consumed = 0;
    int index[MAXSPS];
    int tsind;
    int *nsps;
    double temp_conc[MAXSPS];
    char chemn[MAXSTRING];
    char cmdstr[MAXSTRING];

    fp = fopen(filen, "r");
    CheckFile(fp, filen);
    PIHMprintf(VL_VERBOSE, " Reading %s\n", filen);

    forc->nprcpc = CountOccurr(fp, "PRCP_CONC_TS");

    FindLine(fp, "BOF", &lno, filen);

    if (forc->nprcpc > 0)
    {
        forc->prcpc =
            (tsdata_struct *)malloc(forc->nprcpc * sizeof(tsdata_struct));
        nsps = (int *)malloc(forc->nprcpc * sizeof(int));

        NextLine(fp, cmdstr, &lno);
        for (int i = 0; i < forc->nprcpc; i++)
        {
            match = sscanf(cmdstr, "%*s %d %*s %d", &tsind, &nsps[i]);
            if (match != 2 || i != tsind - 1)
            {
                PIHMprintf(VL_ERROR,
                           "Error reading the %dth precipitation concentration"
                           " time series.\n",
                           i + 1);
                PIHMprintf(VL_ERROR, "Error in %s near Line %d.\n",
                           filen, lno);
                PIHMexit(EXIT_FAILURE);
            }
            /* Skip header lines */
            NextLine(fp, cmdstr, &lno);
            forc->prcpc[i].length =
                CountLine(fp, cmdstr, 1, "PRCP_CONC_TS");
        }

        /* Rewind and read */
        FindLine(fp, "BOF", &lno, filen);
        for (int i = 0; i < forc->nprcpc; i++)
        {
            /* Skip header lines */
            NextLine(fp, cmdstr, &lno);

            NextLine(fp, cmdstr, &lno);
            bytes_consumed = 0;
            for (int j = 0; j < nsps[i]; j++)
            {
                if (sscanf(cmdstr + bytes_consumed, "%s%n", chemn,
                           &bytes_now) != 1)
                {
                    PIHMprintf(VL_ERROR,
                               "Error reading precipitation conc. "
                               "in %s near Line %d.\n",
                               filen, lno);
                    PIHMexit(EXIT_FAILURE);
                }
                bytes_consumed += bytes_now;

                index[j] = FindChem(chemn, chemtbl, rttbl->NumStc);
                if (index[j] < NumSpc)
                {
                    PIHMprintf(VL_VERBOSE,
                               "  Precipitation concentration of '%s' "
                               "is a time series.\n",
                               chemn);
                }
                else
                {
                    PIHMprintf(VL_VERBOSE,
                               "Error: Precipitation species index is larger than "
                               "number of primary species.\n");
                    PIHMexit(EXIT_FAILURE);
                }
            }

            forc->prcpc[i].ftime =
                (int *)malloc((forc->prcpc[i].length) * sizeof(int));
            forc->prcpc[i].data =
                (double **)malloc((forc->prcpc[i].length) * sizeof(double *));
            forc->prcpc[i].value =
                (double *)malloc(NumSpc * sizeof(double));

            for (int j = 0; j < forc->prcpc[i].length; j++)
            {
                int k, kk;

                forc->prcpc[i].data[j] =
                    (double *)malloc(NumSpc * sizeof(double));

                NextLine(fp, cmdstr, &lno);
                ReadTS(cmdstr, &forc->prcpc[i].ftime[j], temp_conc, nsps[i]);

                for (k = 0; k < NumSpc; k++)
                {
                    /* Species not described in the forcing file will be filled
                     * with the concentrations in .chem file */
                    forc->prcpc[i].data[j][k] = rttbl->prcp_conc[k];

                    for (kk = 0; kk < nsps[i]; kk++)
                    {
                        if (index[kk] == k)
                        {
                            if (strcmp(chemtbl[k].ChemName, "pH") == 0)
                            {
                                /* Convert pH to H+ concentration */
                                forc->prcpc[i].data[j][k] =
                                    (temp_conc[kk] < 7.0) ? pow(10, -temp_conc[kk]) : -pow(10, -temp_conc[kk] - 14);
                            }
                            else
                            {
                                forc->prcpc[i].data[j][k] = temp_conc[kk];
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    fclose(fp);
}
