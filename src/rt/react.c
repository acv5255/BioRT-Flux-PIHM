#include "pihm.h"

#define TOL 1E-7
#define SKIP_JACOB 1

void Reaction(double stepsize, const chemtbl_struct chemtbl[],
              const kintbl_struct kintbl[], const rttbl_struct *rttbl, elem_struct elem[])
{

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (int i = 0; i < nelem; i++)
    {
        double vol_gw;
        double vol_unsat;
        double satn;

        vol_gw = MAX(GWStrg(elem[i].soil.depth, elem[i].soil.smcmax,
                            elem[i].soil.smcmin, elem[i].ws.gw),
                     DEPTHR) *
                 elem[i].topo.area;
        vol_unsat = MAX(UnsatWaterStrg(elem[i].soil.depth, elem[i].soil.smcmax,
                                       elem[i].soil.smcmin, elem[i].ws.gw, elem[i].ws.unsat),
                        DEPTHR) *
                    elem[i].topo.area;

        satn =
            UnsatSatRatio(elem[i].soil.depth, elem[i].ws.unsat, elem[i].ws.gw);

        for (int k = 0; k < NumSpc; k++)
        {
            elem[i].chmf.react_unsat[k] = 0.0;
            elem[i].chmf.react_gw[k] = 0.0;
        }

        /*
         * Unsaturated zone
         */
        if (elem[i].ws.unsat > 1.0E-3 && satn > 1.0E-2)
        {
            ReactControl(chemtbl, kintbl, rttbl, stepsize, vol_unsat, satn,
                         &elem[i].chms_unsat, elem[i].chmf.react_unsat);
        }

        /*
         * Groundwater
         */
        if (elem[i].ws.gw > 1.0E-3)
        {
            ReactControl(chemtbl, kintbl, rttbl, stepsize, vol_gw, 1.0,
                         &elem[i].chms_gw, elem[i].chmf.react_gw);
        }

        /* Averaging mineral concentration to ensure mass conservation */
        for (int k = 0; k < rttbl->NumStc; k++)
        {
            if (chemtbl[k].itype == MINERAL)
            {
                elem[i].chms_gw.t_conc[k] =
                    (elem[i].chms_gw.t_conc[k] * vol_gw +
                     elem[i].chms_unsat.t_conc[k] * vol_unsat) /
                    (vol_gw + vol_unsat);
                elem[i].chms_unsat.t_conc[k] = elem[i].chms_gw.t_conc[k];
                elem[i].chms_gw.p_conc[k] = elem[i].chms_gw.t_conc[k];
                elem[i].chms_unsat.p_conc[k] = elem[i].chms_gw.t_conc[k];
            }
        }

#if defined(_FBR_)
        vol_gw = MAX(GWStrg(elem[i].geol.depth, elem[i].geol.smcmax,
                            elem[i].geol.smcmin, elem[i].ws.fbr_gw),
                     DEPTHR) *
                 elem[i].topo.area;
        vol_unsat = MAX(UnsatWaterStrg(elem[i].geol.depth, elem[i].geol.smcmax,
                                       elem[i].geol.smcmin, elem[i].ws.fbr_gw, elem[i].ws.fbr_unsat),
                        DEPTHR) *
                    elem[i].topo.area;

        satn = UnsatSatRatio(elem[i].geol.depth, elem[i].ws.fbr_unsat,
                             elem[i].ws.fbr_gw);

        for (k = 0; k < NumSpc; k++)
        {
            elem[i].chmf.react_fbrunsat[k] = 0.0;
            elem[i].chmf.react_fbrgw[k] = 0.0;
        }

        /*
         * Fractured bedrock unsaturated zone
         */
        if (elem[i].ws.fbr_unsat > 1.0E-3 && satn > 1.0E-2)
        {
            ReactControl(chemtbl, kintbl, rttbl, stepsize, vol_unsat, satn,
                         &elem[i].chms_fbrunsat, elem[i].chmf.react_fbrunsat);
        }

        /*
         * Bedrock groundwater
         */
        if (elem[i].ws.fbr_gw > 1.0E-3)
        {
            ReactControl(chemtbl, kintbl, rttbl, stepsize, vol_gw, 1.0,
                         &elem[i].chms_fbrgw, elem[i].chmf.react_fbrgw);
        }

        /* Averaging mineral concentration to ensure mass conservation */
        for (k = 0; k < rttbl->NumStc; k++)
        {
            if (chemtbl[k].itype == MINERAL)
            {
                elem[i].chms_fbrgw.t_conc[k] =
                    (elem[i].chms_fbrgw.t_conc[k] * vol_gw +
                     elem[i].chms_fbrunsat.t_conc[k] * vol_unsat) /
                    (vol_gw + vol_unsat);
                elem[i].chms_fbrunsat.t_conc[k] = elem[i].chms_fbrgw.t_conc[k];
                elem[i].chms_fbrgw.p_conc[k] = elem[i].chms_fbrgw.t_conc[k];
                elem[i].chms_fbrunsat.p_conc[k] = elem[i].chms_fbrgw.t_conc[k];
            }
        }
#endif
    }
}

int _React(double stepsize, const chemtbl_struct chemtbl[],
           const kintbl_struct kintbl[], const rttbl_struct *rttbl, double satn,
           chmstate_struct *chms)
{
    int i, j, k;
    int control;
    int num_spe = rttbl->NumStc + rttbl->NumSsc;
    int min_pos;
    int pivot_flg;
    int mn, in;
    double monodterm = 1.0, inhibterm = 1.0;
    double residue[MAXSPS];
    double residue_t[MAXSPS];
    double tmpconc[MAXSPS];
    double totconc[MAXSPS];
    double area[MAXSPS];
    double error[MAXSPS];
    double gamma[MAXSPS];
    double Keq[MAXSPS];
    double Rate_pre[MAXSPS];
    double IAP[MAXSPS];
    double dependency[MAXSPS];
    double Rate_spe[MAXSPS];
    double Rate_spet[MAXSPS];
    const int SUFEFF = 1;
    double tmpval;
    double tmpprb;
    double inv_sat;
    double I;
    double Iroot;
    double tmpKeq;
    double adh;
    double bdh;
    double bdt;
    double maxerror = 1.0;
    double surf_ratio;
    double tot_cec;
    double tmpprb_inv;
    realtype **jcb;
    sunindextype p[MAXSPS];
    realtype x_[MAXSPS];

    control = 0;
    tmpprb = 1.0E-2;
    tmpprb_inv = 1.0 / tmpprb;
    inv_sat = 1.0 / satn;

    for (i = 0; i < rttbl->NumMin; i++)
    {
        area[i] = chms->ssa[i + rttbl->NumStc - rttbl->NumMin] *
                  chms->p_conc[i + rttbl->NumStc - rttbl->NumMin] *
                  chemtbl[i + rttbl->NumStc - rttbl->NumMin].MolarMass;
    }

    if (SUFEFF)
    {
        if (satn < 1.0)
        {
            // surf_ratio = 1.0;  /* # 1 function */
            surf_ratio = exp(satn) - 1.0; /* # 3 function */
            // surf_ratio = 1.0 - pow(exp(-1.0/satn), 0.6); /* # 4 function */
            for (i = 0; i < rttbl->NumMin; i++)
            {
                area[i] *= surf_ratio;
            }
        }
    } /* Lichtner's 2 third law if SUF_EFF is turned on. */

    for (j = 0; j < rttbl->NumStc; j++)
    {
        Rate_spe[j] = 0.0;
    }

    for (i = 0; i < rttbl->NumMkr + rttbl->NumAkr; i++)
    {
        min_pos = kintbl[i].position - rttbl->NumStc + rttbl->NumMin;

        if (kintbl[i].type == TST)
        {
            IAP[i] = 0.0;
            for (j = 0; j < rttbl->NumStc; j++)
            {
                IAP[i] += log10(chms->p_actv[j]) *
                          rttbl->Dep_kinetic[min_pos][j];
            }
            IAP[i] = pow(10, IAP[i]);
            tmpKeq = pow(10, rttbl->KeqKinect[min_pos]);
            dependency[i] = 1.0;
            for (k = 0; k < kintbl[i].num_dep; k++)
                dependency[i] *=
                    pow(chms->p_actv[kintbl[i].dep_position[k]],
                        kintbl[i].dep_power[k]);
            /* Calculate the predicted rate depending on the type of rate law */
            Rate_pre[i] = area[min_pos] * (pow(10, kintbl[i].rate)) *
                          dependency[i] * (1 - (IAP[i] / tmpKeq));
            /* Rate_pre: rate per reaction (mol L-1 water s-1)
             * area: m2 L-1 water
             * rate: mol m-2 s-1
             * dependency: dimensionless */
        }
        else if (kintbl[i].type == MONOD)
        {
            monodterm = 1.0; /* re-set for new species */
            inhibterm = 1.0; /*re-set for new species */

            /* Calculate rate */
            for (mn = 0; mn < kintbl[i].num_monod; mn++)
            {
                monodterm *= chms->p_conc[kintbl[i].monod_position[mn]] /
                             (chms->p_conc[kintbl[i].monod_position[mn]] +
                              kintbl[i].monod_para[mn]);
            }

            for (in = 0; in < kintbl[i].num_inhib; in++)
            {
                inhibterm *= kintbl[i].inhib_para[in] /
                             (kintbl[i].inhib_para[in] +
                              chms->p_conc[kintbl[i].inhib_position[in]]);
            }

            /* Based on CrunchTope */
            Rate_pre[i] = area[min_pos] * pow(10, kintbl[i].rate) * monodterm;
        }

        for (j = 0; j < rttbl->NumStc; j++)
        {
            Rate_spe[j] += Rate_pre[i] * rttbl->Dep_kinetic[min_pos][j];
        }
    }

    for (i = 0; i < rttbl->NumMkr + rttbl->NumAkr; i++)
    {
        min_pos = kintbl[i].position - rttbl->NumStc + rttbl->NumMin;
        if (Rate_pre[i] < 0.0)
        {
            /* Mineral cutoff when mineral is disappearing */
            if (chms->p_conc[min_pos + rttbl->NumStc - rttbl->NumMin] < 1.0E-8)
            {
                area[min_pos] = 0.0;
            }
        }
    }

    for (i = 0; i < NumSpc; i++)
    {
        if (chemtbl[i].itype == AQUEOUS)
        {
            /* Aqueous species, saturation term for aqueous volume */
            Rate_spe[i] *= inv_sat;
        }
    }

    jcb = newDenseMat(rttbl->NumStc - rttbl->NumMin,
                      rttbl->NumStc - rttbl->NumMin);

    if (rttbl->TEMcpl == 0)
    {
        for (i = 0; i < rttbl->NumSsc; i++)
        {
            Keq[i] = rttbl->Keq[i];
        }
    }

    adh = rttbl->adh;
    bdh = rttbl->bdh;
    bdt = rttbl->bdt;

    for (i = 0; i < rttbl->NumStc; i++)
    {
        tmpconc[i] = log10(chms->p_conc[i]);
    }
    for (i = 0; i < rttbl->NumSsc; i++)
    {
        tmpconc[i + rttbl->NumStc] = log10(chms->s_conc[i]);
    }
    tot_cec = 0.0;
    for (i = 0; i < num_spe; i++)
    {
        tot_cec += (chemtbl[i].itype == CATION_ECHG) ? pow(10, tmpconc[i]) : 0.0;
    }

    I = 0;
    for (i = 0; i < num_spe; i++)
    {
        I += 0.5 * pow(10, tmpconc[i]) * chemtbl[i].Charge * chemtbl[i].Charge;
    }
    Iroot = sqrt(I);
    for (i = 0; i < num_spe; i++)
    {
        switch (chemtbl[i].itype)
        {
        case AQUEOUS:
            gamma[i] =
                (-adh * chemtbl[i].Charge * chemtbl[i].Charge * Iroot) /
                    (1.0 + bdh * chemtbl[i].SizeF * Iroot) +
                bdt * I;
            break;
        case ADSORPTION:
            gamma[i] = log10(satn);
            break;
        case CATION_ECHG:
            gamma[i] = -log10(tot_cec);
            break;
        case MINERAL:
            gamma[i] = -tmpconc[i];
            break;
        }
    }

    while (maxerror > TOL)
    {
        for (i = 0; i < rttbl->NumSsc; i++)
        {
            tmpval = 0.0;
            for (j = 0; j < rttbl->NumSdc; j++)
            {
                tmpval += (tmpconc[j] + gamma[j]) * rttbl->Dependency[i][j];
            }
            tmpval -= Keq[i] + gamma[i + rttbl->NumStc];
            tmpconc[i + rttbl->NumStc] = tmpval;
        }

        for (j = 0; j < rttbl->NumStc; j++)
        {
            Rate_spet[j] = 0.0;
        }

        for (i = 0; i < rttbl->NumMkr + rttbl->NumAkr; i++)
        {
            min_pos = kintbl[i].position - rttbl->NumStc + rttbl->NumMin;

            if (kintbl[i].type == TST)
            {
                IAP[i] = 0.0;
                for (j = 0; j < rttbl->NumStc; j++)
                {
                    if (chemtbl[j].itype != MINERAL)
                    {
                        IAP[i] += (tmpconc[j] + gamma[j]) *
                                  rttbl->Dep_kinetic[min_pos][j];
                    }
                }
                IAP[i] = pow(10, IAP[i]);
                tmpKeq = pow(10, rttbl->KeqKinect[min_pos]);
                /*
                 * if ( IAP[i] < tmpKeq)
                 * rct_drct[i] = 1.0;
                 * if ( IAP[i] > tmpKeq)
                 * rct_drct[i] = -1.0;
                 * if ( IAP[i] == tmpKeq)
                 * rct_drct[i] = 0.0;
                 */
                dependency[i] = 0.0;
                for (k = 0; k < kintbl[i].num_dep; k++)
                {
                    dependency[i] += (tmpconc[kintbl[i].dep_position[k]] +
                                      gamma[kintbl[i].dep_position[k]]) *
                                     kintbl[i].dep_power[k];
                }
                dependency[i] = pow(10, dependency[i]);
                /* Calculate predicted rate depending on type of rate law */
                Rate_pre[i] = area[min_pos] * (pow(10, kintbl[i].rate)) *
                              dependency[i] * (1.0 - (IAP[i] / tmpKeq));
                /* Rate_pre: in mol / L water / s
                 * area: m2/L water
                 * rate: mol/m2/s
                 * dependency: dimensionless; */
            }
            else if (kintbl[i].type == MONOD)
            {
                monodterm = 1.0;
                inhibterm = 1.0;

                /* Calculate rate */
                for (mn = 0; mn < kintbl[i].num_monod; mn++)
                {
                    monodterm *= chms->p_conc[kintbl[i].monod_position[mn]] /
                                 (chms->p_conc[kintbl[i].monod_position[mn]] +
                                  kintbl[i].monod_para[mn]);
                }

                for (in = 0; in < kintbl[i].num_inhib; in++)
                {
                    inhibterm *= kintbl[i].inhib_para[in] /
                                 (kintbl[i].inhib_para[in] +
                                  chms->p_conc[kintbl[i].inhib_position[in]]);
                }

                /* Based on CrunchTope */
                Rate_pre[i] =
                    area[min_pos] * pow(10, kintbl[i].rate) * monodterm;
            }

            for (j = 0; j < rttbl->NumStc; j++)
            {
                Rate_spet[j] += Rate_pre[i] * rttbl->Dep_kinetic[min_pos][j];
            }
            /* Adjust the unit of the calcuated rate. Note that for mineral, the
             * unit of rate and the unit of concentration are mol/L porous media
             * For the aqueous species, the unit of the rate and the unit of the
             * concentration are mol/L pm and mol/L water respectively. */
        }

        for (i = 0; i < NumSpc; i++)
        {
            Rate_spet[i] *= (chemtbl[i].itype == AQUEOUS) ? inv_sat : 1.0;
        }

        for (i = 0; i < rttbl->NumStc - rttbl->NumMin; i++)
        {
            tmpval = 0.0;
            for (j = 0; j < rttbl->NumStc + rttbl->NumSsc; j++)
            {
                tmpval += rttbl->Totalconc[i][j] * pow(10, tmpconc[j]);
            }
            totconc[i] = tmpval;
            residue[i] = tmpval - (chms->t_conc[i] +
                                   (Rate_spe[i] + Rate_spet[i]) * stepsize * 0.5);
        }
        if (control % SKIP_JACOB == 0)
        {
            for (k = 0; k < rttbl->NumStc - rttbl->NumMin; k++)
            {
                tmpconc[k] += tmpprb;
                for (i = 0; i < rttbl->NumSsc; i++)
                {
                    tmpval = 0.0;
                    for (j = 0; j < rttbl->NumSdc; j++)
                    {
                        tmpval +=
                            (tmpconc[j] + gamma[j]) * rttbl->Dependency[i][j];
                    }
                    tmpval -= Keq[i] + gamma[i + rttbl->NumStc];
                    tmpconc[i + rttbl->NumStc] = tmpval;
                }
                for (i = 0; i < rttbl->NumStc - rttbl->NumMin; i++)
                {
                    tmpval = 0.0;
                    for (j = 0; j < rttbl->NumStc + rttbl->NumSsc; j++)
                    {
                        tmpval += rttbl->Totalconc[i][j] * pow(10, tmpconc[j]);
                    }
                    residue_t[i] = tmpval - (chms->t_conc[i] +
                                             (Rate_spe[i] + Rate_spet[i]) * stepsize * 0.5);
                    jcb[k][i] = (residue_t[i] - residue[i]) * tmpprb_inv;
                }
                tmpconc[k] -= tmpprb;
            }
        }
        for (i = 0; i < rttbl->NumStc - rttbl->NumMin; i++)
        {
            x_[i] = -residue[i];
        }

        pivot_flg = denseGETRF(jcb, rttbl->NumStc - rttbl->NumMin,
                               rttbl->NumStc - rttbl->NumMin, p);
        if (pivot_flg != 0)
        {
            return 1;
        }

        denseGETRS(jcb, rttbl->NumStc - rttbl->NumMin, p, x_);

        for (i = 0; i < rttbl->NumStc - rttbl->NumMin; i++)
        {
            if (fabs(x_[i]) < 0.3)
            {
                tmpconc[i] += x_[i];
            }
            else
            {
                tmpconc[i] += (x_[i] < 0) ? -0.3 : 0.3;
            }
            error[i] = residue[i] / totconc[i];
        }
        maxerror = fabs(error[0]);
        for (i = 1; i < rttbl->NumStc - rttbl->NumMin; i++)
        {
            maxerror = MAX(fabs(error[i]), maxerror);
        }
        control++;
        if (control > 10)
        {
            return 1;
        }
    }

    destroyMat(jcb);

    for (i = 0; i < rttbl->NumSsc; i++)
    {
        tmpval = 0.0;
        for (j = 0; j < rttbl->NumSdc; j++)
        {
            tmpval += (tmpconc[j] + gamma[j]) * rttbl->Dependency[i][j];
        }
        tmpval -= Keq[i] + gamma[i + rttbl->NumStc];
        tmpconc[i + rttbl->NumStc] = tmpval;
    }

    for (i = 0; i < rttbl->NumStc - rttbl->NumMin; i++)
    {
        tmpval = 0.0;
        for (j = 0; j < rttbl->NumStc + rttbl->NumSsc; j++)
        {
            tmpval += rttbl->Totalconc[i][j] * pow(10, tmpconc[j]);
        }
        totconc[i] = tmpval;
        residue[i] = tmpval - chms->t_conc[i];
        error[i] = residue[i] / totconc[i];
    }
    for (i = 0; i < rttbl->NumStc + rttbl->NumSsc; i++)
    {
        if (i < rttbl->NumStc)
        {
            if (chemtbl[i].itype == MINERAL)
            {
                chms->t_conc[i] +=
                    (Rate_spe[i] + Rate_spet[i]) * stepsize * 0.5;
                chms->p_actv[i] = 1.0;
                chms->p_conc[i] = chms->t_conc[i];
            }
            else
            {
                chms->p_conc[i] = pow(10, tmpconc[i]);
                chms->p_actv[i] = pow(10, (tmpconc[i] + gamma[i]));
                chms->t_conc[i] = totconc[i];
            }
        }
        else
        {
            chms->s_conc[i - rttbl->NumStc] = pow(10, tmpconc[i]);
#if TEMP_DISABLED
            chms->s_actv[i - rttbl->NumStc] = pow(10, (tmpconc[i] + gamma[i]));
#endif
        }
    }

    return 0;
}

void ReactControl(const chemtbl_struct chemtbl[], const kintbl_struct kintbl[],
                  const rttbl_struct *rttbl, double stepsize, double vol, double satn,
                  chmstate_struct *chms, double react_flux[])
{
    double t_conc0[MAXSPS];
    double substep;
    double step_counter = 0.0;
    int flag;
    int k;

    for (k = 0; k < NumSpc; k++)
    {
        t_conc0[k] = chms->t_conc[k];
    }

    substep = stepsize;

    while (1.0 - step_counter / stepsize > 1.0E-10 && substep > 30.0)
    {
        flag = _React(substep, chemtbl, kintbl, rttbl, satn, chms);

        if (flag == 0)
        {
            /* Reaction passed with current step */
            step_counter += substep;
        }
        else
        {
            substep *= 0.5;
        }
    }

    if (roundi(step_counter) == roundi(stepsize))
    {
        if (roundi(substep) != roundi(stepsize))
        {
            PIHMprintf(VL_NORMAL,
                       " Reaction passed with minimum step of %f s.\n", substep);
        }
    }
    else
    {
        PIHMprintf(VL_NORMAL, " Reaction failed.\n");
    }

    for (k = 0; k < NumSpc; k++)
    {
        react_flux[k] =
            (chms->t_conc[k] - t_conc0[k]) * vol / stepsize;
    }
}
