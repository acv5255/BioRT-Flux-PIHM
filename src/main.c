#include "pihm.h"

/* Global variables */
int verbose_mode;
int debug_mode;
int append_mode;
int corr_mode;
int spinup_mode;
int fixed_length;
int tecplot;
char project[MAXSTRING];
int num_elements;
int num_river;
#if defined(_OPENMP)
int nthreads = 1; /* Default value */
#endif
#if defined(_BGC_)
int first_balance;
#endif
#if defined(_RT_)
int NumSpc;
#endif

int main(int argc, char *argv[])
{
    char outputdir[MAXSTRING];
    PihmData pihm;
    RunParameters *ctrl;
    N_Vector CV_Y;
    void *cvode_mem;
    SUNLinearSolver sun_ls;
#if defined(_OPENMP)
    double start_omp;
#else
    clock_t start;
#endif
    double cputime, cputime_dt; /* Time cpu duration */

#if defined(_OPENMP)
    /* Set the number of threads to use */
    nthreads = omp_get_max_threads();
#endif

    memset(outputdir, 0, MAXSTRING);

    /* Read command line arguments */
    parse_cmd_line_param(argc, argv, outputdir);

    /* Print AscII art */
    StartupScreen();

    /* Allocate memory for model data structure */
    pihm = (PihmData)malloc(sizeof(*pihm));

    /* Read PIHM input files */
    ReadAlloc(pihm);

    /* Initialize CVode state variables */
    CV_Y = N_VNew(num_state_variables());
    if (CV_Y == NULL)
    {
        PIHMprintf(VL_ERROR, "Error creating CVODE state variable vector.\n");
        PIHMexit(EXIT_FAILURE);
    }

    /* Initialize PIHM structure */
    initialize_data(pihm, CV_Y, &cvode_mem);

    /* Create output directory */
    create_output_dir(outputdir);

    /* Create output structures */
#if defined(_CYCLES_)
    map_output(pihm->ctrl.prtvrbl, pihm->ctrl.tpprtvrbl, pihm->epctbl,
               pihm->elem, pihm->river, &pihm->meshtbl, outputdir, &pihm->print);
#elif defined(_RT_)
    map_output(pihm->ctrl.prtvrbl, pihm->ctrl.tpprtvrbl, pihm->chemtbl,
               &pihm->rttbl, pihm->elem, pihm->river, &pihm->meshtbl, outputdir,
               &pihm->print);
#else
    map_output(pihm->ctrl.prtvrbl, pihm->ctrl.tpprtvrbl, pihm->elem, pihm->river,
               &pihm->meshtbl, outputdir, &pihm->print);
#endif

    /* Backup input files */
#if !defined(_MSC_VER)
    if (!append_mode)
    {
        backup_input(outputdir, &pihm->filename);
    }
#endif

    init_output_files(&pihm->print, outputdir, pihm->ctrl.waterbal,
                      pihm->ctrl.ascii);

    PIHMprintf(VL_VERBOSE, "\n\nSolving ODE system ... \n\n");

    /* Set solver parameters */
    SetCVodeParam(pihm, cvode_mem, &sun_ls, CV_Y);

#if defined(_BGC_)
    first_balance = 1;
#endif

    /*
     * Run PIHM
     */
#if defined(_OPENMP)
    start_omp = omp_get_wtime();
#else
    start = clock();
#endif

    ctrl = &pihm->ctrl;

    /* Hide cursor */
    PIHMprintf(VL_NORMAL, "\e[?25l");

    if (spinup_mode)
    {
        Spinup(pihm, CV_Y, cvode_mem, &sun_ls);

        /* In spin-up mode, initial conditions are always printed */
        print_init(pihm->elem, pihm->river, outputdir,
                   ctrl->endtime, ctrl->starttime,
                   ctrl->endtime, ctrl->prtvrbl[IC_CTRL]);
#if defined(_BGC_)
        WriteBgcIc(outputdir, pihm->elem, pihm->river);
#endif

#if defined(_RT_)
        WriteRtIc(outputdir, pihm->chemtbl, &pihm->rttbl, pihm->elem);
#endif
    }
    else
    {
        for (ctrl->cstep = 0; ctrl->cstep < ctrl->nstep; ctrl->cstep++)
        {
#if defined(_OPENMP)
            RunTime(start_omp, &cputime, &cputime_dt);
#else
            RunTime(start, &cputime, &cputime_dt);
#endif

            PIHM(pihm, cvode_mem, CV_Y, cputime);

            /* Adjust CVODE max step to reduce oscillation */
            AdjCVodeMaxStep(cvode_mem, &pihm->ctrl);

            /* Print CVODE performance and statistics */
            if (debug_mode)
            {
                print_perf(cvode_mem, ctrl->tout[ctrl->cstep + 1],
                           ctrl->starttime, cputime_dt, cputime,
                           ctrl->maxstep, pihm->print.cvodeperf_file);
            }

            /* Write init files */
            if (ctrl->write_ic)
            {
                print_init(pihm->elem, pihm->river, outputdir,
                           ctrl->tout[ctrl->cstep + 1], ctrl->starttime,
                           ctrl->endtime, ctrl->prtvrbl[IC_CTRL]);
            }
        }

#if defined(_BGC_)
        if (ctrl->write_bgc_restart)
        {
            WriteBgcIc(outputdir, pihm->elem, pihm->river);
        }
#endif

#if defined(_RT_)
        if (ctrl->write_rt_restart)
        {
            WriteRtIc(outputdir, pihm->chemtbl, &pihm->rttbl, pihm->elem);
        }
#endif

#if TEMP_DISABLED
#if defined(_CYCLES_)
        if (ctrl->write_cycles_restart)
        {
            WriteCyclesIC(pihm->filename.cyclesic, pihm->elem, pihm->river);
        }
#endif
#endif
    }

    if (debug_mode)
    {
        print_cvode_final_stats(cvode_mem);
    }

    /* Free memory */
    N_VDestroy(CV_Y);

    /* Free integrator memory */
    CVodeFree(&cvode_mem);
    SUNLinSolFree(sun_ls);
    free_pihm_data(pihm);
    free(pihm);

    PIHMprintf(VL_BRIEF, "Simulation completed.\n");

    /* Re-enable cursor */
    printf("\e[?25h");

    return EXIT_SUCCESS;
}
