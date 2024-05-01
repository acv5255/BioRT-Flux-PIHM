#include "pihm.h"

void Summary(MeshElement *elem, river_struct *river, N_Vector CV_Y,
             double stepsize)
{
    double *y;
    int i;

    y = NV_DATA(CV_Y);

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (i = 0; i < num_elements; i++)
    {
        double subrunoff;

        elem[i].ws.surf = y[SURF(i)];
        elem[i].ws.unsat = y[UNSAT(i)];
        elem[i].ws.gw = y[GW(i)];

#if defined(_FBR_)
        elem[i].ws.fbr_unsat = y[FBRUNSAT(i)];
        elem[i].ws.fbr_gw = y[FBRGW(i)];
#endif

#if defined(_FBR_)
        mass_balance(&elem[i].ws, &elem[i].ws0, &elem[i].wf, &subrunoff,
                     &elem[i].soil, &elem[i].geol, elem[i].topo.area, stepsize);
#else
        mass_balance(&elem[i].ws, &elem[i].ws0, &elem[i].wf, &subrunoff,
                     &elem[i].soil, elem[i].topo.area, stepsize);
#endif

#if defined(_NOAH_)
        elem[i].wf.runoff2 = subrunoff;
#if defined(_FBR_)
        elem[i].wf.runoff2 += elem[i].wf.fbr_infil;
#endif

        elem[i].ps.nwtbl = FindWaterTable(elem[i].ps.sldpth, elem[i].ps.nsoil,
                                          elem[i].ws.gw, elem[i].ps.satdpth);

        CalcLatFlx(&elem[i].ps, &elem[i].wf);
#endif

        elem[i].ws0 = elem[i].ws;

#if defined(_BGC_) && !defined(_LUMPED_)
        elem[i].ns.surfn = (y[SURFN(i)] > 0.0) ? y[SURFN(i)] : 0.0;
        elem[i].ns.sminn = (y[SMINN(i)] > 0.0) ? y[SMINN(i)] : 0.0;

        elem[i].ns.nleached_snk += (elem[i].nt.surfn0 + elem[i].nt.sminn0) -
                                   (elem[i].ns.surfn + elem[i].ns.sminn) +
                                   elem[i].nf.ndep_to_sminn / DAYINSEC * stepsize +
                                   elem[i].nf.nfix_to_sminn / DAYINSEC * stepsize +
                                   elem[i].nsol.snksrc * stepsize;

        elem[i].nt.surfn0 = elem[i].ns.surfn;
        elem[i].nt.sminn0 = elem[i].ns.sminn;
#endif

#if defined(_CYCLES_)
        elem[i].np.no3 = (y[NO3(i)] >= 0.0) ? y[NO3(i)] : 0.0;
        elem[i].np.nh4 = (y[NH4(i)] >= 0.0) ? y[NH4(i)] : 0.0;

        UpdNProf(stepsize, &elem[i].soil, &elem[i].ws, &elem[i].ns0,
                 &elem[i].nf, &elem[i].np, &elem[i].ps, &elem[i].ns);

        elem[i].ns0 = elem[i].ns;
#endif

#if defined(_RT_)
        int k;
        double vol_gw;
        double vol_unsat;

        vol_gw = MAX(get_groundwater_storage(elem[i].soil.depth, elem[i].soil.smcmax,
                                             elem[i].soil.smcmin, elem[i].ws.gw),
                     DEPTHR) *
                 elem[i].topo.area;
        vol_unsat = MAX(get_unsat_water_storage(elem[i].soil.depth, elem[i].soil.smcmax,
                                                elem[i].soil.smcmin, elem[i].ws.gw, elem[i].ws.unsat),
                        DEPTHR) *
                    elem[i].topo.area;

        for (k = 0; k < NumSpc; k++)
        {
            elem[i].chms_unsat.t_mole[k] = (y[UNSAT_MOLE(i, k)] > 0.0) ? y[UNSAT_MOLE(i, k)] : 0.0;
            elem[i].chms_gw.t_mole[k] = (y[GW_MOLE(i, k)] > 0.0) ? y[GW_MOLE(i, k)] : 0.0;

            /* Calculate concentrations */
            elem[i].chms_unsat.t_conc[k] = (vol_unsat > 0.0) ? elem[i].chms_unsat.t_mole[k] / vol_unsat : 0.0;
            elem[i].chms_unsat.t_conc[k] =
                (elem[i].chms_unsat.t_conc[k] > ZERO_CONC) ? elem[i].chms_unsat.t_conc[k] : ZERO_CONC;

            elem[i].chms_gw.t_conc[k] = (vol_gw > 0.0) ? elem[i].chms_gw.t_mole[k] / vol_gw : 0.0;
            elem[i].chms_gw.t_conc[k] =
                (elem[i].chms_gw.t_conc[k] > ZERO_CONC) ? elem[i].chms_gw.t_conc[k] : ZERO_CONC;
        }

#if defined(_FBR_)
        vol_gw = MAX(get_groundwater_storage(elem[i].geol.depth, elem[i].geol.smcmax,
                                             elem[i].geol.smcmin, elem[i].ws.fbr_gw),
                     DEPTHR) *
                 elem[i].topo.area;
        vol_unsat = MAX(get_unsat_water_storage(elem[i].geol.depth, elem[i].geol.smcmax,
                                                elem[i].geol.smcmin, elem[i].ws.fbr_gw, elem[i].ws.fbr_unsat),
                        DEPTHR) *
                    elem[i].topo.area;

        for (k = 0; k < NumSpc; k++)
        {
            elem[i].chms_fbrunsat.t_mole[k] = MAX(y[FBRUNSAT_MOLE(i, k)], 0.0);
            elem[i].chms_fbrgw.t_mole[k] = MAX(y[FBRGW_MOLE(i, k)], 0.0);

            /* Calculate concentrations */
            elem[i].chms_fbrunsat.t_conc[k] = (vol_unsat > 0.0) ? elem[i].chms_fbrunsat.t_mole[k] / vol_unsat : 0.0;
            elem[i].chms_fbrunsat.t_conc[k] =
                MAX(elem[i].chms_fbrunsat.t_conc[k], ZERO_CONC);

            elem[i].chms_fbrgw.t_conc[k] = (vol_gw > 0.0) ? elem[i].chms_fbrgw.t_mole[k] / vol_gw : 0.0;
            elem[i].chms_fbrgw.t_conc[k] =
                MAX(elem[i].chms_fbrgw.t_conc[k], ZERO_CONC);
        }
#endif
#endif
    }

#if defined(_BGC_) && defined(_LUMPED_)
    elem[LUMPED].ns.sminn = (y[LUMPED_SMINN] > 0.0) ? y[LUMPED_SMINN] : 0.0;

    elem[LUMPED].ns.nleached_snk += (elem[LUMPED].nt.sminn0 -
                                     elem[LUMPED].ns.sminn) +
                                    elem[LUMPED].nf.ndep_to_sminn / DAYINSEC * stepsize +
                                    elem[LUMPED].nf.nfix_to_sminn / DAYINSEC * stepsize +
                                    elem[LUMPED].nsol.snksrc * stepsize;

    elem[LUMPED].nt.sminn0 = elem[LUMPED].ns.sminn;
#endif

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (i = 0; i < num_river; i++)
    {
        river[i].ws.stage = y[RIVSTG(i)];
        river[i].ws.gw = y[RIVGW(i)];

        river[i].ws0 = river[i].ws;

#if defined(_CYCLES_)
        river[i].ns.streamno3 = y[STREAMNO3(i)];
        river[i].ns.streamnh4 = y[STREAMNH4(i)];
#endif

#if defined(_RT_)
        int k;
        double vol_rivbed;
        double vol_stream;

        vol_rivbed = MAX(RivBedStrg(&river[i].matl, &river[i].ws), DEPTHR) * elem[i].topo.area;
        vol_stream = river[i].topo.area * MAX(river[i].ws.stage, DEPTHR);

        for (k = 0; k < NumSpc; k++)
        {
            river[i].chms_stream.t_mole[k] = (y[STREAM_MOLE(i, k)] > 0.0) ? y[STREAM_MOLE(i, k)] : 0.0;
            river[i].chms_rivbed.t_mole[k] = (y[RIVBED_MOLE(i, k)] > 0.0) ? y[RIVBED_MOLE(i, k)] : 0.0;

            /* Calculate concentrations */
            river[i].chms_stream.t_conc[k] = (vol_stream > 0.0) ? river[i].chms_stream.t_mole[k] / vol_stream : 0.0;
            river[i].chms_stream.t_conc[k] =
                (river[i].chms_stream.t_conc[k] > ZERO_CONC) ? river[i].chms_stream.t_conc[k] : ZERO_CONC;

            river[i].chms_rivbed.t_conc[k] = (vol_rivbed > 0.0) ? river[i].chms_rivbed.t_mole[k] / vol_rivbed : 0.0;
            river[i].chms_rivbed.t_conc[k] =
                (river[i].chms_rivbed.t_conc[k] > ZERO_CONC) ? river[i].chms_rivbed.t_conc[k] : ZERO_CONC;
        }
#endif
    }
}

#if defined(_FBR_)
void mass_balance(const wstate_struct *ws, const wstate_struct *ws0,
                  wflux_struct *wf, double *subrunoff, const SoilData *soil,
                  const geol_struct *geol, double area, double stepsize)
#else
void mass_balance(const wstate_struct *ws, const wstate_struct *ws0,
                  wflux_struct *wf, double *subrunoff, const SoilData *soil,
                  double area, double stepsize)
#endif
{
    int j;
    double soilw0, soilw1;
#if defined(_FBR_)
    double fbrw0, fbrw1;
    double fbrrunoff;
#endif

    /*
     * The mass_balance subroutine adjusts model infiltration rate and recharge
     * rate based on mass balance in the soil column. This subroutine also
     * calculates an equivalent infiltration rate, which is used as the boundary
     * condition in the Noah soil moisture calculation. Unlike the infiltration
     * rate, the equivalent infiltration rate is calculated without considering
     * oversturation, and is based on the mass balance of the whole soil column,
     * instead of just the unsaturated zone.
     */

    /* Adjust recharge */
    soilw0 = ws0->gw;
    soilw1 = ws->gw;

    *subrunoff = 0.0;
    for (j = 0; j < NUM_EDGE; j++)
    {
        *subrunoff += wf->subsurf[j] / area;
    }

    wf->rechg = (soilw1 - soilw0) * soil->porosity / stepsize + *subrunoff +
                wf->edir_gw + wf->ett_gw;

    /* Adjust infiltration */
    soilw0 = ws0->unsat;
    soilw1 = ws->unsat;

    wf->infil = (soilw1 - soilw0) * soil->porosity / stepsize + wf->rechg +
                wf->edir_unsat + wf->ett_unsat;

#if defined(_FBR_)
    /* Adjust bedrock recharge */
    fbrw0 = ws0->fbr_gw;
    fbrw1 = ws->fbr_gw;

    fbrrunoff = 0.0;
    for (j = 0; j < NUM_EDGE; j++)
    {
        fbrrunoff += wf->fbrflow[j] / area;
    }

    wf->fbr_rechg = (fbrw1 - fbrw0) * geol->porosity / stepsize + fbrrunoff;

    /* Adjust bedrock infiltration */
    fbrw0 = ws0->fbr_unsat;
    fbrw1 = ws->fbr_unsat;

    wf->fbr_infil = (fbrw1 - fbrw0) * geol->porosity / stepsize + wf->fbr_rechg;

    /* Further adjust soil infiltration and recharge rate to take into account
     * bedrock leakage */
    wf->rechg += wf->fbr_infil;
    wf->infil += wf->fbr_infil;
#endif

    /*
     * Calculate equivalent infiltration based on mass conservation
     */
    soilw0 = ws0->gw + ws0->unsat;
    soilw0 = (soilw0 > soil->depth) ? soil->depth : soilw0;
    soilw0 = (soilw0 < 0.0) ? 0.0 : soilw0;

    soilw1 = ws->gw + ws->unsat;
    soilw1 = (soilw1 > soil->depth) ? soil->depth : soilw1;
    soilw1 = (soilw1 < 0.0) ? 0.0 : soilw1;

    /* Subsurface runoff rate */
    *subrunoff = 0.0;
    for (j = 0; j < NUM_EDGE; j++)
    {
        *subrunoff += wf->subsurf[j] / area;
    }

    wf->eqv_infil = (soilw1 - soilw0) * soil->porosity / stepsize + *subrunoff +
                    wf->edir_unsat + wf->edir_gw + wf->ett_unsat + wf->ett_gw;

#if defined(_FBR_)
    fbrw0 = ws0->fbr_gw + ws0->fbr_unsat;
    fbrw1 = ws->fbr_gw + ws->fbr_unsat;

    fbrrunoff = 0.0;
    for (j = 0; j < NUM_EDGE; j++)
    {
        fbrrunoff += wf->fbrflow[j] / area;
    }

    wf->fbr_infil = (fbrw1 - fbrw0) * geol->porosity / stepsize + fbrrunoff;

    wf->eqv_infil += wf->fbr_infil;
#endif

    if (wf->eqv_infil < 0.0)
    {
        *subrunoff -= wf->eqv_infil;
        wf->eqv_infil = 0.0;
    }
}
