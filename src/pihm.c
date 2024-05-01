#include "pihm.h"

void PIHM(PihmData pihm, void *cvode_mem, N_Vector CV_Y, double cputime)
{
    int t;
#if defined(_RT_)
    const int SPECIATION_STEP = 3600;
#endif

    t = pihm->ctrl.tout[pihm->ctrl.cstep];

    /* Apply boundary conditions */
#if defined(_RT_)
    ApplyBc(&pihm->rttbl, &pihm->forc, pihm->elem, pihm->river, t);
#else
    ApplyBc(&pihm->forc, pihm->elem, pihm->river, t);
#endif

    /*
     * Apply forcing and simulate land surface processes
     */
    if ((t - pihm->ctrl.starttime) % pihm->ctrl.etstep == 0)
    {
        /* Apply forcing */
#if defined(_RT_)
        apply_forcing(&pihm->forc, &pihm->rttbl, pihm->elem, t,
                  pihm->ctrl.rad_mode, &pihm->siteinfo);
#elif defined(_NOAH_)
        apply_forcing(&pihm->forc, pihm->elem, t, pihm->ctrl.rad_mode,
                  &pihm->siteinfo);
#else
        apply_forcing(&pihm->forc, pihm->elem, t);
#endif

#if defined(_NOAH_)
        /* Calculate surface energy balance */
        Noah(pihm->elem, &pihm->lctbl, &pihm->cal, (double)pihm->ctrl.etstep);
#else
        /* Calculate Interception storage and ET */
        interception_snow_et(t, (double)pihm->ctrl.etstep, pihm->elem, &pihm->cal);
#endif

        /* Update print variables for land surface step variables */
        UpdPrintVar(pihm->print.varctrl, pihm->print.nprint, LS_STEP);
        UpdPrintVar(pihm->print.tp_varctrl, pihm->print.ntpprint, LS_STEP);
    }

    /*
     * Solve PIHM hydrology ODE using CVode
     */
    SolveCVode(&pihm->ctrl, cputime, &t, cvode_mem, CV_Y);

    /* Use mass balance to calculate model fluxes or variables */
    Summary(pihm->elem, pihm->river, CV_Y, (double)pihm->ctrl.stepsize);

#if defined(_NOAH_)
    NoahHydrol(pihm->elem, (double)pihm->ctrl.stepsize);
#endif

    /* Update print variables for hydrology step variables */
    UpdPrintVar(pihm->print.varctrl, pihm->print.nprint, HYDROL_STEP);
    UpdPrintVar(pihm->print.tp_varctrl, pihm->print.ntpprint, HYDROL_STEP);

#if defined(_RT_)
    if (pihm->rttbl.RecFlg == KIN_REACTION)
    {
        if (t - pihm->ctrl.starttime >= pihm->ctrl.RT_delay &&
            (t - pihm->ctrl.starttime) % pihm->ctrl.AvgScl == 0)
        {
            /* Reaction */
            do_reaction((double)pihm->ctrl.AvgScl, pihm->chemtbl, pihm->kintbl,
                        &pihm->rttbl, pihm->elem);
        }

        if ((t - pihm->ctrl.starttime) % SPECIATION_STEP == 0)
        {
            /* Speciation */
            Speciation(pihm->chemtbl, &pihm->rttbl, pihm->river);
        }
    }
    else
    {
        UpdatePConc(pihm->elem, pihm->river);
    }

    UpdPrintVar(pihm->print.varctrl, pihm->print.nprint, RT_STEP);
    UpdPrintVar(pihm->print.tp_varctrl, pihm->print.ntpprint, RT_STEP);
#endif

#if defined(_DAILY_)
    DailyVar(t, pihm->ctrl.starttime, pihm->elem);

    /*
     * Daily timestep modules
     */
    if ((t - pihm->ctrl.starttime) % DAYINSEC == 0)
    {
#if defined(_BGC_)
        /* Daily BGC processes */
        DailyBgc(pihm, t - DAYINSEC);
#endif

#if defined(_CYCLES_)
        DailyCycles(t - DAYINSEC, pihm);
#endif

        /* Update print variables for CN (daily) step variables */
        UpdPrintVar(pihm->print.varctrl, pihm->print.nprint, CN_STEP);
        UpdPrintVar(pihm->print.tp_varctrl, pihm->print.ntpprint, CN_STEP);

        /* initialize_data daily structures */
        InitDailyStruct(pihm->elem);
    }
#endif

    /*
     * Print outputs
     */
    /* Print water balance */
    if (pihm->ctrl.waterbal)
    {
        PrintWaterBal(pihm->print.watbal_file, t, pihm->ctrl.starttime,
                      pihm->ctrl.stepsize, pihm->elem, pihm->river);
    }

    /* Print binary and txt output files */
    print_data(pihm->print.varctrl, pihm->print.nprint, t,
               t - pihm->ctrl.starttime, pihm->ctrl.ascii);

    /* Print tecplot output files */
    if (tecplot)
    {
        print_data_tecplot(pihm->print.tp_varctrl, pihm->print.ntpprint, t,
                           t - pihm->ctrl.starttime);
    }
}
