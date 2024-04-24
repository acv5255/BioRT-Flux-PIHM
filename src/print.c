#include "pihm.h"

#define TEC_HEADER "VARIABLES = \"X\" \"Y\" \"Zmin\" \"Zmax\" \"h\""
#define WB_HEADER "VARIABLES = \"TIME (s)\" \"SRC (m)\" \"SNK (m)\" \"STRG (m)\""
#define RIVER_TEC_HEADER2 "ZONE T = \"Water Depth River\""
#define RIVER_TEC_HEADER3 "StrandID=1, SolutionTime="
#define ELEM_TEC_HEADER3 "VARSHARELIST = ([1, 2, 3, 4]=1), CONNECTIVITYSHAREZONE = 1"

void StartupScreen(void)
{
    PIHMprintf(VL_NORMAL, "\n");
    PIHMprintf(VL_NORMAL, "    ########    ####   ##     ##   ##     ##\n");
    PIHMprintf(VL_NORMAL, "    ##     ##    ##    ##     ##   ###   ###\n");
    PIHMprintf(VL_NORMAL, "    ##     ##    ##    ##     ##   #### ####\n");
    PIHMprintf(VL_NORMAL, "    ########     ##    #########   ## ### ##\n");
    PIHMprintf(VL_NORMAL, "    ##           ##    ##     ##   ##     ##\n");
    PIHMprintf(VL_NORMAL, "    ##           ##    ##     ##   ##     ##\n");
    PIHMprintf(VL_NORMAL, "    ##          ####   ##     ##   ##     ##\n");

    PIHMprintf(VL_BRIEF, "\n    The Penn State Integrated Hydrologic Model\n\n");
#if defined(_NOAH_)
    PIHMprintf(VL_BRIEF, "    * Land surface module turned on.\n");
#endif
#if defined(_RT_)
    PIHMprintf(VL_BRIEF, "    * Reactive transport module turned on.\n");
#endif
#if defined(_BGC_)
    PIHMprintf(VL_BRIEF, "    * Biogeochemistry module turned on.\n");
#endif
#if defined(_CYCLES_)
    PIHMprintf(VL_BRIEF, "    * Crop module turned on.\n");
#endif
#if defined(_FBR_)
    PIHMprintf(VL_BRIEF, "    * Fractured bedrock module turned on.\n");
#endif
#if defined(_OPENMP)
    PIHMprintf(VL_BRIEF, "    * OpenMP (# of threads = %d).\n", nthreads);
#endif
    PIHMprintf(VL_BRIEF, "\n");

    if (1 == corr_mode)
    {
        PIHMprintf(VL_NORMAL,
                   "    Surface elevation correction mode turned on.\n");
    }
    if (1 == debug_mode)
    {
        PIHMprintf(VL_NORMAL,
                   "    Debug mode turned on.\n");
    }
    if (1 == tecplot)
    {
        PIHMprintf(VL_NORMAL,
                   "    Tecplot output turned on.\n");
    }
    if (VL_BRIEF == verbose_mode)
    {
        PIHMprintf(VL_NORMAL,
                   "    Brief mode turned on.\n");
    }
    if (VL_VERBOSE == verbose_mode)
    {
        PIHMprintf(VL_NORMAL,
                   "    Verbose mode turned on.\n");
    }
    if (1 == append_mode)
    {
        PIHMprintf(VL_NORMAL,
                   "    Append mode turned on.\n");
    }
}

void InitOutputFile(PrintStructure *print, const char *outputdir, int watbal,
                    int ascii)
{
    char ascii_fn[2 * MAXSTRING];
    char dat_fn[2 * MAXSTRING];
    char watbal_fn[2 * MAXSTRING];
    char perf_fn[2 * MAXSTRING];
    int i;
    char mode[2];
    char bin_mode[3];

    if (append_mode)
    {
        strcpy(mode, "a");
        strcpy(bin_mode, "ab");
    }
    else
    {
        strcpy(mode, "w");
        strcpy(bin_mode, "wb");
    }

    /* Initialize water balance file*/
    if (watbal)
    {
        sprintf(watbal_fn, "%s%s.watbal.plt", outputdir, project);
        print->watbal_file = fopen(watbal_fn, mode);
        CheckFile(print->watbal_file, watbal_fn);
    }

    /* Initialize cvode output files */
    if (debug_mode)
    {
        sprintf(perf_fn, "%s%s.cvode.log", outputdir, project);
        print->cvodeperf_file = fopen(perf_fn, mode);
        CheckFile(print->cvodeperf_file, perf_fn);
        /* Print header lines */
        fprintf(print->cvodeperf_file,
                "%-8s%-8s%-16s%-8s%-8s%-8s%-8s%-8s%-8s\n",
                "step", "cpu_dt", "cputime", "maxstep",
                "nsteps", "niters", "nevals", "nefails", "ncfails");
    }

    /*
     * Initialize model variable output files
     */
    for (i = 0; i < print->nprint; i++)
    {
        sprintf(dat_fn, "%s.dat", print->varctrl[i].name);
        print->varctrl[i].datfile = fopen(dat_fn, bin_mode);
        CheckFile(print->varctrl[i].datfile, dat_fn);

        if (ascii)
        {
            sprintf(ascii_fn, "%s.txt", print->varctrl[i].name);
            print->varctrl[i].txtfile = fopen(ascii_fn, mode);
            CheckFile(print->varctrl[i].txtfile, ascii_fn);
        }
    }

    /* Tecplot files */
    if (tecplot)
    {
        for (i = 0; i < print->ntpprint; i++)
        {
            int j;

            sprintf(dat_fn, "%s.plt", print->tp_varctrl[i].name);
            print->tp_varctrl[i].datfile = fopen(dat_fn, mode);
            CheckFile(print->tp_varctrl[i].datfile, dat_fn);

            if (print->tp_varctrl[i].intr == 0)
            {
                fprintf(print->tp_varctrl[i].datfile, "%s \n", TEC_HEADER);
                fprintf(print->tp_varctrl[i].datfile,
                        "ZONE T=\"%s\", N=%d, E=%d, DATAPACKING=%s, "
                        "SOLUTIONTIME=%lf, ZONETYPE=%s\n",
                        print->tp_varctrl[i].name, print->tp_varctrl[i].nnodes,
                        print->tp_varctrl[i].nvar, "POINT", 0.0000, "FETRIANGLE");

                for (j = 0; j < print->tp_varctrl[i].nnodes; j++)
                {
                    fprintf(print->tp_varctrl[i].datfile,
                            "%lf %lf %lf %lf %lf\n",
                            print->tp_varctrl[i].x[j], print->tp_varctrl[i].y[j],
                            print->tp_varctrl[i].zmin[j],
                            print->tp_varctrl[i].zmax[j],
                            0.000001);
                }
                for (j = 0; j < print->tp_varctrl[i].nvar; j++)
                {
                    fprintf(print->tp_varctrl[i].datfile, "%d %d %d\n",
                            print->tp_varctrl[i].node0[j],
                            print->tp_varctrl[i].node1[j],
                            print->tp_varctrl[i].node2[j]);
                }
            }
        }
    }
}

void UpdPrintVar(PrintVariables *varctrl, int nprint, int module_step)
{
    int i;
#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (i = 0; i < nprint; i++)
    {
        int j;

        if (varctrl[i].upd_intvl == module_step)
        {
            for (j = 0; j < varctrl[i].nvar; j++)
            {
                varctrl[i].buffer[j] += *varctrl[i].var[j];
            }

            varctrl[i].counter++;
        }
    }
}

void PrintData(PrintVariables *varctrl, int nprint, int t, int lapse, int ascii)
{
    int i;
    PihmTime pihm_time;

    pihm_time = PIHMTime(t);

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (i = 0; i < nprint; i++)
    {
        int j;
        double outval;
        double outtime;

        if (PrintNow(varctrl[i].intvl, lapse, &pihm_time))
        {
            if (ascii)
            {
                fprintf(varctrl[i].txtfile, "\"%s\"", pihm_time.str);
                for (j = 0; j < varctrl[i].nvar; j++)
                {
                    outval = (varctrl[i].counter > 0) ? varctrl[i].buffer[j] / (double)varctrl[i].counter : varctrl[i].buffer[j];

                    fprintf(varctrl[i].txtfile,
                            (outval == 0.0 || fabs(outval) > 1.0E-3) ? "\t%lf" : "\t%lE", outval);
                }
                fprintf(varctrl[i].txtfile, "\n");
                fflush(varctrl[i].txtfile);
            }

            outtime = (double)t;
            fwrite(&outtime, sizeof(double), 1, varctrl[i].datfile);
            for (j = 0; j < varctrl[i].nvar; j++)
            {
                outval = (varctrl[i].counter > 0) ? varctrl[i].buffer[j] / (double)varctrl[i].counter : varctrl[i].buffer[j];

                fwrite(&outval, sizeof(double), 1, varctrl[i].datfile);

                varctrl[i].buffer[j] = 0.0;
            }
            varctrl[i].counter = 0;
            fflush(varctrl[i].datfile);
        }
    }
}

void PrintInit(const elem_struct *elem, const river_struct *river,
               const char *outputdir, int t, int starttime, int endtime, int intvl)
{
    PihmTime pihm_time;

    pihm_time = PIHMTime(t);

    if (PrintNow(intvl, t - starttime, &pihm_time) || t == endtime)
    {
        FILE *init_file;
        char file_name[2 * MAXSTRING];
        int i;

        sprintf(file_name, "%s/restart/%s.%s.ic", outputdir, project,
                pihm_time.strshort);

        init_file = fopen(file_name, "wb");
        CheckFile(init_file, file_name);

        for (i = 0; i < nelem; i++)
        {
#if defined(_CYCLES_)
            fwrite(&elem[i].ws.flatResidueWater, sizeof(double), 1, init_file);
#else
            fwrite(&elem[i].ws.cmc, sizeof(double), 1, init_file);
#endif
            fwrite(&elem[i].ws.sneqv, sizeof(double), 1, init_file);
            fwrite(&elem[i].ws.surf, sizeof(double), 1, init_file);
            fwrite(&elem[i].ws.unsat, sizeof(double), 1, init_file);
            fwrite(&elem[i].ws.gw, sizeof(double), 1, init_file);
#if defined(_FBR_)
            fwrite(&elem[i].ws.fbr_unsat, sizeof(double), 1, init_file);
            fwrite(&elem[i].ws.fbr_gw, sizeof(double), 1, init_file);
#endif
#if defined(_NOAH_)
            fwrite(&elem[i].es.t1, sizeof(double), 1, init_file);
            fwrite(&elem[i].ps.snowh, sizeof(double), 1, init_file);

            int j;

            for (j = 0; j < MAXLYR; j++)
            {
                fwrite(&elem[i].es.stc[j], sizeof(double), 1, init_file);
            }
            for (j = 0; j < MAXLYR; j++)
            {
                fwrite(&elem[i].ws.smc[j], sizeof(double), 1, init_file);
            }
            for (j = 0; j < MAXLYR; j++)
            {
                fwrite(&elem[i].ws.sh2o[j], sizeof(double), 1, init_file);
            }
#endif
        }

        for (i = 0; i < nriver; i++)
        {
            fwrite(&river[i].ws.stage, sizeof(double), 1, init_file);
            fwrite(&river[i].ws.gw, sizeof(double), 1, init_file);
        }

        fflush(init_file);
        fclose(init_file);
    }
}

void PrintDataTecplot(PrintVariables *varctrl, int nprint, int t, int lapse)
{
    int i;
    PihmTime pihm_time;
    double *hnodes; /* h at nodes */
    int *inodes;

    pihm_time = PIHMTime(t);

    for (i = 0; i < nprint; i++)
    {
        int j;
        double outval;
        double outtime;

        if (PrintNow(varctrl[i].intvl, lapse, &pihm_time))
        {
            outtime = (double)t;

            if (varctrl[i].intr == RIVERVAR)
            {
                /*Print river files */
                fprintf(varctrl[i].datfile, "%s\n", TEC_HEADER);
                fprintf(varctrl[i].datfile, "%s\n", RIVER_TEC_HEADER2);
                fprintf(varctrl[i].datfile, "%s %d\n", RIVER_TEC_HEADER3, t);
                for (j = 0; j < varctrl[i].nvar; j++)
                {
                    if (varctrl[i].counter > 0)
                    {
                        outval = varctrl[i].buffer[j] /
                                 (double)varctrl[i].counter;
                    }
                    else
                    {
                        outval = varctrl[i].buffer[j];
                    }

                    fprintf(varctrl[i].datfile, "%lf %lf %lf %lf %lf\n",
                            varctrl[i].x[j], varctrl[i].y[j],
                            varctrl[i].zmin[j], varctrl[i].zmax[j], outval);
                    varctrl[i].buffer[j] = 0.0;
                }
            }
            else
            {
                /*Print element files */
                hnodes = (double *)calloc(varctrl[i].nnodes, sizeof(double));
                inodes = (int *)calloc(varctrl[i].nnodes, sizeof(int));
                for (j = 0; j < varctrl[i].nnodes; j++)
                {
                    hnodes[j] = 0.0;
                    inodes[j] = 0;
                }
                fprintf(varctrl[i].datfile,
                        "ZONE T=\"%s\", N=%d, E=%d, DATAPACKING=%s, "
                        "SOLUTIONTIME=%lf, ZONETYPE=%s\n",
                        varctrl[i].name, varctrl[i].nnodes, varctrl[i].nvar,
                        "POINT", outtime, "FETRIANGLE");
                fprintf(varctrl[i].datfile, "%s\n", ELEM_TEC_HEADER3);
                for (j = 0; j < varctrl[i].nvar; j++)
                {
                    if (varctrl[i].counter > 0)
                    {
                        outval = varctrl[i].buffer[j] /
                                 (double)varctrl[i].counter;
                    }
                    else
                    {
                        outval = varctrl[i].buffer[j];
                    }

                    hnodes[varctrl[i].node0[j] - 1] += outval;
                    hnodes[varctrl[i].node1[j] - 1] += outval;
                    hnodes[varctrl[i].node2[j] - 1] += outval;
                    inodes[varctrl[i].node0[j] - 1] += 1;
                    inodes[varctrl[i].node1[j] - 1] += 1;
                    inodes[varctrl[i].node2[j] - 1] += 1;
                    varctrl[i].buffer[j] = 0.0;
                }
                for (j = 0; j < varctrl[i].nnodes; j++)
                {
                    if (inodes[j] == 0)
                    {
                        fprintf(varctrl[i].datfile, "%8.6f\n", 0.0);
                    }
                    else
                    {
                        fprintf(varctrl[i].datfile, "%8.6f\n",
                                hnodes[j] / inodes[j]);
                    }
                }

                free(hnodes);
                free(inodes);
            }

            varctrl[i].counter = 0;
            fflush(varctrl[i].datfile);
        }
    }
}

void PrintPerf(void *cvode_mem, int t, int starttime, double cputime_dt,
               double cputime, double maxstep, FILE *perf_file)
{
    static double dt;
    static long int nst0, nfe0, nni0, ncfn0, netf0;
    long int nst, nfe, nni, ncfn, netf;
    int cv_flag;

    /* Gets the cumulative number of internal steps taken by the solver (total
     * so far) */
    cv_flag = CVodeGetNumSteps(cvode_mem, &nst);
    CheckCVodeFlag(cv_flag);

    /* Gets the number of calls to the user's right-hand side function */
    cv_flag = CVodeGetNumRhsEvals(cvode_mem, &nfe);
    CheckCVodeFlag(cv_flag);

    /* Gets the number of nonlinear iterations performed */
    cv_flag = CVodeGetNumNonlinSolvIters(cvode_mem, &nni);
    CheckCVodeFlag(cv_flag);

    /* Gets the number of nonlinear convergence failures that have occurred */
    cv_flag = CVodeGetNumNonlinSolvConvFails(cvode_mem, &ncfn);
    CheckCVodeFlag(cv_flag);

    /* Gets the number of local error test failures that have occurred */
    cv_flag = CVodeGetNumErrTestFails(cvode_mem, &netf);
    CheckCVodeFlag(cv_flag);

    fprintf(perf_file, "%-8d%-8.3f%-16.3f%-8.2f",
            t - starttime, cputime_dt, cputime, maxstep);
    fprintf(perf_file, "%-8ld%-8ld%-8ld%-8ld%-8ld\n",
            nst - nst0, nni - nni0, nfe - nfe0, netf - netf0, ncfn - ncfn0);
    fflush(perf_file);

    dt = 0.0;

    nst0 = nst;
    nni0 = nni;
    nfe0 = nfe;
    netf0 = netf;
    ncfn0 = ncfn;

    dt += cputime_dt;
}

void PrintWaterBal(FILE *watbal_file, int t, int tstart, int dt,
                   const elem_struct *elem, const river_struct *river)
{
    int i;
    double tot_src = 0.0, tot_snk = 0.0, tot_strg = 0.0;
    static double tot_strg_prev = 0.0;
    static double error = 0.0;

    if (t == tstart + dt)
    {
        fprintf(watbal_file, "%s\n", WB_HEADER);
    }

    for (i = 0; i < nelem; i++)
    {
        tot_src += elem[i].wf.prcp * elem[i].topo.area * dt;
#if defined(_NOAH_)
        tot_src += (elem[i].wf.dew + elem[i].wf.snomlt) *
                   elem[i].topo.area * dt;
#endif

        tot_snk += (elem[i].wf.edir + elem[i].wf.ett + elem[i].wf.ec) *
                   elem[i].topo.area * dt;
#if defined(_NOAH_)
        tot_snk += elem[i].wf.esnow * elem[i].topo.area * dt;
#endif

#if defined(_CYCLES_)
        tot_strg += (elem[i].ws.flatResidueWater + elem[i].ws.stanResidueWater +
                     elem[i].ws.sneqv + elem[i].ws.surf +
                     (elem[i].ws.unsat + elem[i].ws.gw) * elem[i].soil.porosity) *
                    elem[i].topo.area;
#else
        tot_strg += (elem[i].ws.cmc + elem[i].ws.sneqv + elem[i].ws.surf +
                     (elem[i].ws.unsat + elem[i].ws.gw) * elem[i].soil.porosity) *
                    elem[i].topo.area;
#endif
    }

    for (i = 0; i < nriver; i++)
    {
        tot_strg +=
            (river[i].ws.stage + river[i].ws.gw * river[i].matl.porosity) *
            river[i].topo.area;

        if (river[i].down < 0)
        {
            tot_snk += river[i].wf.rivflow[DOWN_CHANL2CHANL] * dt;
        }
    }

    if (tot_strg_prev != 0.0)
    {
        error += tot_src - tot_snk - (tot_strg - tot_strg_prev);

        fprintf(watbal_file, "%d %lg %lg %lg %lg %lg\n", t - tstart,
                tot_src, tot_snk, tot_strg - tot_strg_prev,
                tot_src - tot_snk - (tot_strg - tot_strg_prev), error);
        fflush(watbal_file);
    }

    tot_strg_prev = tot_strg;
}

void PrintCVodeFinalStats(void *cvode_mem)
{
    int cv_flag;
    long int nst;
    long int nfe;
    long int netf;
    long int nni;
    long int ncfn;

    cv_flag = CVodeGetNumSteps(cvode_mem, &nst);
    CheckCVodeFlag(cv_flag);

    cv_flag = CVodeGetNumRhsEvals(cvode_mem, &nfe);
    CheckCVodeFlag(cv_flag);

    cv_flag = CVodeGetNumErrTestFails(cvode_mem, &netf);
    CheckCVodeFlag(cv_flag);

    cv_flag = CVodeGetNumNonlinSolvConvFails(cvode_mem, &ncfn);
    CheckCVodeFlag(cv_flag);

    cv_flag = CVodeGetNumNonlinSolvIters(cvode_mem, &nni);
    CheckCVodeFlag(cv_flag);

    PIHMprintf(VL_NORMAL, "\n");
    PIHMprintf(VL_NORMAL,
               "num of steps = %-6ld num of rhs evals = %-6ld\n", nst, nfe);
    PIHMprintf(VL_NORMAL,
               "num of nonlin solv iters = %-6ld "
               "num of nonlin solv conv fails = %-6ld "
               "num of err test fails = %-6ld\n",
               nni, ncfn, netf);
}

int PrintNow(int intvl, int lapse, const PihmTime *pihm_time)
{
    int print = 0;

    if (intvl != 0)
    {
        switch (intvl)
        {
        case YEARLY_OUTPUT:
            if (pihm_time->month == 1 && pihm_time->day == 1 &&
                pihm_time->hour == 0 && pihm_time->minute == 0)
            {
                print = 1;
            }
            break;
        case MONTHLY_OUTPUT:
            if (pihm_time->day == 1 && pihm_time->hour == 0 &&
                pihm_time->minute == 0)
            {
                print = 1;
            }
            break;
        case DAILY_OUTPUT:
            if (pihm_time->hour == 0 && pihm_time->minute == 0)
            {
                print = 1;
            }
            break;
        case HOURLY_OUTPUT:
            if (pihm_time->minute == 0)
            {
                print = 1;
            }
            break;
        default:
            if (lapse % intvl == 0)
            {
                print = 1;
            }
        }
    }

    return print;
}

void ProgressBar(int progress)
{
    int i;

    PIHMprintf(VL_NORMAL, "  [");

    for (i = 0; i < progress; i++)
    {
        PIHMprintf(VL_NORMAL, "=");
    }
    for (i = progress; i < 100; i++)
    {
        PIHMprintf(VL_NORMAL, " ");
    }

    PIHMprintf(VL_NORMAL, "] %d%%", progress);

    if (progress == 100)
    {
        PIHMprintf(VL_NORMAL, "\n");
    }
}
