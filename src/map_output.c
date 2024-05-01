#include "pihm.h"

#if defined(_CYCLES_)
void map_output(const int *prtvrbl, const int *tpprtvrbl,
                const epconst_struct epctbl[], const elem_struct *elem,
                const river_struct *river, const MeshEntry *meshtbl,
                const char *outputdir, PrintStructure *print)
#elif defined(_RT_)
void map_output(const int *prtvrbl, const int *tpprtvrbl,
                const ChemicalEntry chemtbl[], const ReactionNetwork *rttbl,
                const MeshElement *elem, const river_struct *river,
                const MeshEntry *meshtbl, const char *outputdir, PrintStructure *print)
#else
void map_output(const int *prtvrbl, const int *tpprtvrbl,
                const elem_struct *elem, const river_struct *river,
                const MeshEntry *meshtbl, const char *outputdir, PrintStructure *print)
#endif
{
    int n;
    char ext[MAXSTRING];

    PIHMprintf(VL_VERBOSE, "\nInitializing PIHM output files\n");

    n = 0;

    for (int i = 0; i < MAXPRINT; i++)
    {
        if (prtvrbl[i] != 0)
        {
            switch (i)
            {
            case SURF_CTRL:
                init_print_var_control(outputdir, "surf", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.surf;
                }
                n++;
                break;
            case UNSAT_CTRL:
                init_print_var_control(outputdir, "unsat", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.unsat;
                }
                n++;
                break;
            case GW_CTRL:
                init_print_var_control(outputdir, "gw", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.gw;
                }
                n++;
                break;
            case RIVSTG_CTRL:
                init_print_var_control(outputdir, "stage", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].ws.stage;
                }
                n++;
                break;
            case RIVGW_CTRL:
                init_print_var_control(outputdir, "rivgw", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].ws.gw;
                }
                n++;
                break;
            case SNOW_CTRL:
                init_print_var_control(outputdir, "snow", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.sneqv;
                }
                n++;
                break;
            case CMC_CTRL:
#if defined(_CYCLES_)
                init_print_var_control(outputdir, "stanresw", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.stanResidueWater;
                }
                n++;

                init_print_var_control(outputdir, "flatresw", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.flatResidueWater;
                }
                n++;
#else
                init_print_var_control(outputdir, "is", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.cmc;
                }
                n++;
#endif
                break;
            case INFIL_CTRL:
                init_print_var_control(outputdir, "infil", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.infil;
                }
                n++;
                break;
            case RECHARGE_CTRL:
                init_print_var_control(outputdir, "recharge", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.rechg;
                }
                n++;
                break;
            case EC_CTRL:
                init_print_var_control(outputdir, "ec", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.ec;
                }
                n++;
                break;
            case ETT_CTRL:
                init_print_var_control(outputdir, "ett", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.ett;
                }
                n++;
                break;
            case EDIR_CTRL:
                init_print_var_control(outputdir, "edir", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.edir;
                }
                n++;
                break;
            case RIVFLX0_CTRL:
                init_print_var_control(outputdir, "rivflx0", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[0];
                }
                n++;
                break;
            case RIVFLX1_CTRL:
                init_print_var_control(outputdir, "rivflx1", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[1];
                }
                n++;
#if defined(_FBR_) && defined(_TGM_)
                init_print_var_control(outputdir, "rivflx11", prtvrbl[i],
                                       HYDROL_STEP, nriver, &print->varctrl[n]);
                for (j = 0; j < nriver; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[11];
                }
                n++;
                init_print_var_control(outputdir, "rivflx12", prtvrbl[i],
                                       HYDROL_STEP, nriver, &print->varctrl[n]);
                for (j = 0; j < nriver; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[12];
                }
                n++;
#endif
                break;
            case RIVFLX2_CTRL:
                init_print_var_control(outputdir, "rivflx2", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[2];
                }
                n++;
                break;
            case RIVFLX3_CTRL:
                init_print_var_control(outputdir, "rivflx3", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[3];
                }
                n++;
                break;
            case RIVFLX4_CTRL:
                init_print_var_control(outputdir, "rivflx4", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[4];
                }
                n++;
                break;
            case RIVFLX5_CTRL:
                init_print_var_control(outputdir, "rivflx5", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[5];
                }
                n++;
                break;
            case RIVFLX6_CTRL:
                init_print_var_control(outputdir, "rivflx6", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[6];
                }
                n++;
                break;
            case RIVFLX7_CTRL:
                init_print_var_control(outputdir, "rivflx7", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[7];
                }
                n++;
                break;
            case RIVFLX8_CTRL:
                init_print_var_control(outputdir, "rivflx8", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[8];
                }
                n++;
                break;
            case RIVFLX9_CTRL:
                init_print_var_control(outputdir, "rivflx9", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[9];
                }
                n++;
                break;
            case RIVFLX10_CTRL:
                init_print_var_control(outputdir, "rivflx10", prtvrbl[i],
                                       HYDROL_STEP, num_river, &print->varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->varctrl[n].var[j] = &river[j].wf.rivflow[10];
                }
                n++;
                break;
            case SUBFLX_CTRL:
                for (int k = 0; k < NUM_EDGE; k++)
                {
                    sprintf(ext, "subflx%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] = &elem[j].wf.subsurf[k];
                    }
                    n++;
                }
                break;
            case SURFFLX_CTRL:
                for (int k = 0; k < NUM_EDGE; k++)
                {
                    sprintf(ext, "surfflx%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] = &elem[j].wf.ovlflow[k];
                    }
                    n++;
                }
                break;
#if defined(_NOAH_)
            case T1_CTRL:
                init_print_var_control(outputdir, "t1", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].es.t1;
                }
                n++;
                break;
            case STC_CTRL:
                for (int k = 0; k < MAXLYR; k++)
                {
                    sprintf(ext, "stc%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           LS_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] = &elem[j].es.stc[k];
                    }
                    n++;
                }
                break;
            case SMC_CTRL:
                for (int k = 0; k < MAXLYR; k++)
                {
                    sprintf(ext, "smc%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] = &elem[j].ws.smc[k];
                    }
                    n++;
                }
                break;
            case SH2O_CTRL:
                for (int k = 0; k < MAXLYR; k++)
                {
                    sprintf(ext, "swc%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] = &elem[j].ws.sh2o[k];
                    }
                    n++;
                }
                break;
            case SNOWH_CTRL:
                init_print_var_control(outputdir, "snowh", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.snowh;
                }
                n++;

                init_print_var_control(outputdir, "iceh", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.iceh;
                }
                n++;
                break;
            case ALBEDO_CTRL:
                init_print_var_control(outputdir, "albedo", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.albedo;
                }
                n++;
                break;
            case LE_CTRL:
                init_print_var_control(outputdir, "le", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ef.eta;
                }
                n++;
                break;
            case SH_CTRL:
                init_print_var_control(outputdir, "sh", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ef.sheat;
                }
                n++;
                break;
            case G_CTRL:
                init_print_var_control(outputdir, "g", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ef.ssoil;
                }
                n++;
                break;
            case ETP_CTRL:
                init_print_var_control(outputdir, "etp", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ef.etp;
                }
                n++;
                break;
            case ESNOW_CTRL:
                init_print_var_control(outputdir, "esnow", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ef.esnow;
                }
                n++;
                break;
            case ROOTW_CTRL:
                init_print_var_control(outputdir, "rootw", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.soilw;
                }
                n++;
                break;
            case SOILM_CTRL:
                init_print_var_control(outputdir, "soilm", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.soilm;
                }
                n++;
                break;
            case SOLAR_CTRL:
                init_print_var_control(outputdir, "solar", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ef.soldn;
                }
                n++;
                break;
            case CH_CTRL:
                init_print_var_control(outputdir, "ch", prtvrbl[i],
                                       LS_STEP, num_elements, &print->varctrl[n]);
                for (int j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.ch;
                }
                n++;
                break;
#endif
#if defined(_BGC_)
#if defined(_LUMPED_)
            case LAI_CTRL:
                init_print_var_control(outputdir, "lai", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].ps.proj_lai;
                n++;
                break;
            case NPP_CTRL:
                init_print_var_control(outputdir, "npp", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_npp;
                n++;
                break;
            case NEP_CTRL:
                init_print_var_control(outputdir, "nep", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_nep;
                n++;
                break;
            case NEE_CTRL:
                init_print_var_control(outputdir, "nee", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_nee;
                n++;
                break;
            case GPP_CTRL:
                init_print_var_control(outputdir, "gpp", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_gpp;
                n++;
                break;
            case MR_CTRL:
                init_print_var_control(outputdir, "mr", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_mr;
                n++;
                break;
            case GR_CTRL:
                init_print_var_control(outputdir, "gr", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_gr;
                n++;
                break;
            case HR_CTRL:
                init_print_var_control(outputdir, "hr", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_hr;
                n++;
                break;
            case FIRE_CTRL:
                init_print_var_control(outputdir, "fire", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.daily_fire;
                n++;
                break;
            case LITFALLC_CTRL:
                init_print_var_control(outputdir, "litfallc", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] =
                    &elem[LUMPED].summary.daily_litfallc;
                n++;
                break;
            case VEGC_CTRL:
                init_print_var_control(outputdir, "vegc", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.vegc;
                n++;
                break;
            case AGC_CTRL:
                init_print_var_control(outputdir, "agc", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.agc;
                n++;
                break;
            case LITRC_CTRL:
                init_print_var_control(outputdir, "litrc", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.litrc;
                n++;
                break;
            case SOILC_CTRL:
                init_print_var_control(outputdir, "soilc", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.soilc;
                n++;
                break;
            case TOTALC_CTRL:
                init_print_var_control(outputdir, "totalc", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].summary.totalc;
                n++;
                break;
            case SMINN_CTRL:
                init_print_var_control(outputdir, "sminn", prtvrbl[i],
                                       CN_STEP, 1, &print->varctrl[n]);
                print->varctrl[n].var[0] = &elem[LUMPED].ns.sminn;
                n++;
                break;
#else
            case LAI_CTRL:
                init_print_var_control(outputdir, "lai", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.proj_lai;
                }
                n++;
                break;
            case NPP_CTRL:
                init_print_var_control(outputdir, "npp", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_npp;
                }
                n++;
                break;
            case NEP_CTRL:
                init_print_var_control(outputdir, "nep", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_nep;
                }
                n++;
                break;
            case NEE_CTRL:
                init_print_var_control(outputdir, "nee", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_nee;
                }
                n++;
                break;
            case GPP_CTRL:
                init_print_var_control(outputdir, "gpp", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_gpp;
                }
                n++;
                break;
            case MR_CTRL:
                init_print_var_control(outputdir, "mr", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_mr;
                }
                n++;
                break;
            case GR_CTRL:
                init_print_var_control(outputdir, "gr", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_gr;
                }
                n++;
                break;
            case HR_CTRL:
                init_print_var_control(outputdir, "hr", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_hr;
                }
                n++;
                break;
            case FIRE_CTRL:
                init_print_var_control(outputdir, "fire", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.daily_fire;
                }
                n++;
                break;
            case LITFALLC_CTRL:
                init_print_var_control(outputdir, "litfallc", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] =
                        &elem[j].summary.daily_litfallc;
                }
                n++;
                break;
            case VEGC_CTRL:
                init_print_var_control(outputdir, "vegc", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.vegc;
                }
                n++;
                break;
            case AGC_CTRL:
                init_print_var_control(outputdir, "agc", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.agc;
                }
                n++;
                break;
            case LITRC_CTRL:
                init_print_var_control(outputdir, "litrc", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.litrc;
                }
                n++;
                break;
            case SOILC_CTRL:
                init_print_var_control(outputdir, "soilc", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.soilc;
                }
                n++;
                break;
            case TOTALC_CTRL:
                init_print_var_control(outputdir, "totalc", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].summary.totalc;
                }
                n++;
                break;
            case SMINN_CTRL:
                init_print_var_control(outputdir, "sminn", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ns.sminn;
                }
                n++;
                break;
#endif
#endif
#if defined(_CYCLES_)
            case BIOMASS_CTRL:
                for (k = 0; k < MAXCROP && '\0' != epctbl[k].cropn[0]; k++)
                {
                    sprintf(ext, "%s.shoot", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].ccs.shoot;
                    }
                    n++;

                    sprintf(ext, "%s.root", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].ccs.root;
                    }
                    n++;
                }
                break;
            case RADNINTCP_CTRL:
                for (k = 0; k < MAXCROP && '\0' != epctbl[k].cropn[0]; k++)
                {
                    sprintf(ext, "%s.radintcp", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].epv.rad_intcp;
                    }
                    n++;
                }
                break;
            case WATER_STS_CTRL:
                for (k = 0; k < MAXCROP && '\0' != epctbl[k].cropn[0]; k++)
                {
                    sprintf(ext, "%s.waterstress", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].epv.h2o_stress;
                    }
                    n++;
                }
                break;
            case N_STS_CTRL:
                for (k = 0; k < MAXCROP && '\0' != epctbl[k].cropn[0]; k++)
                {
                    sprintf(ext, "%s.nstress", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].epv.n_stress;
                    }
                    n++;
                }
                break;
            case CROP_TR_CTRL:
                for (k = 0; k < MAXCROP && '\0' != epctbl[k].cropn[0]; k++)
                {
                    sprintf(ext, "%s.transp", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].cwf.transp;
                    }
                    n++;
                }
                break;
            case CROP_POTTR_CTRL:
                for (k = 0; k < MAXCROP && '\0' != epctbl[k].cropn[0]; k++)
                {
                    sprintf(ext, "%s.pottransp", epctbl[k].cropn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           CN_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].crop[k].cwf.transp_pot;
                    }
                    n++;
                }
                break;
            case RES_EVAP_CTRL:
                break;
            case NO3_PROF_CTRL:
                init_print_var_control(outputdir, "NO3", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].np.no3;
                }
                n++;
                break;
            case NO3_RIVER_CTRL:
                init_print_var_control(outputdir, "rivNO3", prtvrbl[i],
                                       HYDROL_STEP, nriver, &print->varctrl[n]);
                for (j = 0; j < nriver; j++)
                {
                    print->varctrl[n].var[j] = &river[j].ns.streamno3;
                }
                n++;
                break;
            case NH4_PROF_CTRL:
                init_print_var_control(outputdir, "NH4", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].np.nh4;
                }
                n++;
                break;
            case NH4_RIVER_CTRL:
                init_print_var_control(outputdir, "rivNH4", prtvrbl[i],
                                       HYDROL_STEP, nriver, &print->varctrl[n]);
                for (j = 0; j < nriver; j++)
                {
                    print->varctrl[n].var[j] = &river[j].ns.streamnh4;
                }
                n++;
                break;
            case NO3_DENIT_CTRL:
                init_print_var_control(outputdir, "NO3denitrif",
                                       prtvrbl[i], CN_STEP, num_elements,
                                       &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] =
                        &elem[j].nf.no3denitrif;
                }
                n++;
                break;
            case NO3_LEACH_CTRL:
                for (k = 0; k < NUM_EDGE; k++)
                {
                    sprintf(ext, "NO3leach%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].no3sol.flux[k];
                    }
                    n++;
                }
                break;
            case NH4_LEACH_CTRL:
                for (k = 0; k < NUM_EDGE; k++)
                {
                    sprintf(ext, "NH4leach%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].nh4sol.flux[k];
                    }
                    n++;
                }
                break;
            case NO3_LEACH_RIVER_CTRL:
                init_print_var_control(outputdir, "rivNO3leach", prtvrbl[i],
                                       HYDROL_STEP, nriver, &print->varctrl[n]);
                for (j = 0; j < nriver; j++)
                {
                    print->varctrl[n].var[j] =
                        &river[j].no3sol.flux[DOWN_CHANL2CHANL];
                }
                n++;
                break;
            case NH4_LEACH_RIVER_CTRL:
                init_print_var_control(outputdir, "rivNH4leach", prtvrbl[i],
                                       HYDROL_STEP, nriver, &print->varctrl[n]);
                for (j = 0; j < nriver; j++)
                {
                    print->varctrl[n].var[j] =
                        &river[j].nh4sol.flux[DOWN_CHANL2CHANL];
                }
                n++;
                break;
            case LAI_CTRL:
                init_print_var_control(outputdir, "lai", prtvrbl[i],
                                       CN_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ps.proj_lai;
                }
                n++;
                break;
#endif
#if defined(_FBR_)
            case FBRUNSAT_CTRL:
                init_print_var_control(outputdir, "fbrunsat", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.fbr_unsat;
                }
                n++;
                break;
            case FBRGW_CTRL:
                init_print_var_control(outputdir, "fbrgw", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].ws.fbr_gw;
                }
                n++;
                break;
            case FBRINFIL_CTRL:
                init_print_var_control(outputdir, "fbrinfil", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.fbr_infil;
                }
                n++;
                break;
            case FBRRECHG_CTRL:
                init_print_var_control(outputdir, "fbrrechg", prtvrbl[i],
                                       HYDROL_STEP, num_elements, &print->varctrl[n]);
                for (j = 0; j < num_elements; j++)
                {
                    print->varctrl[n].var[j] = &elem[j].wf.fbr_rechg;
                }
                n++;
                break;
            case FBRFLOW_CTRL:
                for (k = 0; k < NUM_EDGE; k++)
                {
                    sprintf(ext, "fbrflow%d", k);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           HYDROL_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] = &elem[j].wf.fbrflow[k];
                    }
                    n++;
                }
                break;
#endif
#if defined(_RT_)
            case CHEM_CTRL:
                /* Primary species */
                for (int k = 0; k < rttbl->NumStc; k++)
                {
                    char chemn[MAXSTRING];
                    Unwrap(chemn, chemtbl[k].ChemName);

                    /* Unsaturated zone concentration */
                    snprintf(ext, MAXSTRING + 11, "unsat_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_unsat.p_conc[k];
                    }
                    n++;

                    /* Groundwater concentration */
                    snprintf(ext, MAXSTRING + 8, "gw_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_gw.p_conc[k];
                    }
                    n++;

#if defined(_FBR_)
                    /* Fractured unsaturated bedrock layer concentration */
                    sprintf(ext, "fbrunsat_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_fbrunsat.p_conc[k];
                    }
                    n++;

                    /* Deep groundwater concentration */
                    sprintf(ext, "fbrgw_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_fbrgw.p_conc[k];
                    }
                    n++;
#endif

                    /* River concentration */
                    snprintf(ext, MAXSTRING + 11, "river_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_river, &print->varctrl[n]);
                    for (int j = 0; j < num_river; j++)
                    {
                        print->varctrl[n].var[j] =
                            &river[j].chms_stream.p_conc[k];
                    }
                    n++;

                    /* River fluxes */
                    snprintf(ext, MAXSTRING + 20, "river_discharge.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_river, &print->varctrl[n]);
                    for (int j = 0; j < num_river; j++)
                    {
                        print->varctrl[n].var[j] =
                            &river[j].chmf.flux[DOWN_CHANL2CHANL][k];
                    }
                    n++;

#if defined(_FBR_) && defined(_TGM_)
                    sprintf(ext, "left_fbr_discharge.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, nriver, &print->varctrl[n]);
                    for (j = 0; j < nriver; j++)
                    {
                        print->varctrl[n].var[j] =
                            &river[j].chmf.flux[LEFT_FBR2CHANL][k];
                    }
                    n++;

                    sprintf(ext, "right_fbr_discharge.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, nriver, &print->varctrl[n]);
                    for (j = 0; j < nriver; j++)
                    {
                        print->varctrl[n].var[j] =
                            &river[j].chmf.flux[RIGHT_FBR2CHANL][k];
                    }
                    n++;
#endif
                }

                /* Secondary species */
                for (int k = 0; k < rttbl->NumSsc; k++)
                {
                    char chemn[MAXSTRING];
                    Unwrap(chemn, chemtbl[k + rttbl->NumStc].ChemName);

                    /* Unsaturated zone concentration */
                    snprintf(ext, MAXSTRING + 20, "unsat_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_unsat.s_conc[k];
                    }
                    n++;

                    /* Groundwater concentration */
                    snprintf(ext, MAXSTRING + 8, "gw_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (int j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_gw.s_conc[k];
                    }
                    n++;

#if defined(_FBR_)
                    /* Fractured unsaturated bedrock layer concentration */
                    sprintf(ext, "fbrunsat_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_fbrunsat.s_conc[k];
                    }
                    n++;

                    /* Deep groundwater concentration */
                    sprintf(ext, "fbrgw_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, num_elements, &print->varctrl[n]);
                    for (j = 0; j < num_elements; j++)
                    {
                        print->varctrl[n].var[j] =
                            &elem[j].chms_fbrgw.s_conc[k];
                    }
                    n++;
#endif
                }
#if OBSOLETE
                for (k = 0; k < rttbl->NumSsc; k++)
                {
                    char chemn[MAXSTRING];

                    Unwrap(chemn, chemtbl[k + rttbl->NumStc].ChemName);
                    sprintf(ext, "river_conc.%s", chemn);
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, nriver, &print->varctrl[n]);
                    for (j = 0; j < nriver; j++)
                    {
                        print->varctrl[n].var[j] =
                            &river[j].chms_stream.s_conc[k];
                    }
                    n++;
                }

                for (j = 0; j < rttbl->NumBTC; j++)
                {
                    if (rttbl->BTC_loc[j] < 0)
                    {
                        sprintf(ext, "riv%d.btcv", -rttbl->BTC_loc[j]);
                    }
                    else if (rttbl->BTC_loc[j] < num_elements)
                    {
                        sprintf(ext, "unsat%d.btcv", rttbl->BTC_loc[j]);
                    }
                    else
                    {
                        sprintf(ext, "gw%d.btcv", rttbl->BTC_loc[j] - num_elements);
                    }
                    init_print_var_control(outputdir, ext, prtvrbl[i],
                                           RT_STEP, rttbl->NumStc + rttbl->NumSsc,
                                           &print->varctrl[n]);
                    for (k = 0; k < rttbl->NumStc; k++)
                    {
                        if (rttbl->BTC_loc[j] < 0)
                        {
                            print->varctrl[n].var[k] = &river[-rttbl->BTC_loc[j] - 1].chms_stream.btcv_pconc[k];
                        }
                        else if (rttbl->BTC_loc[j] < num_elements)
                        {
                            print->varctrl[n].var[k] = &elem[rttbl->BTC_loc[j] - 1].chms_unsat.btcv_pconc[k];
                        }
                        else
                        {
                            print->varctrl[n].var[k] = &elem[rttbl->BTC_loc[j] - num_elements - 1].chms_gw.btcv_pconc[k];
                        }
                    }
                    for (k = rttbl->NumStc; k < rttbl->NumStc + rttbl->NumSsc; k++)
                    {
                        if (rttbl->BTC_loc[j] < 0)
                        {
                            print->varctrl[n].var[k] = &river[-rttbl->BTC_loc[j] - 1].chms_stream.s_conc[k - rttbl->NumStc];
                        }
                        else if (rttbl->BTC_loc[j] < num_elements)
                        {
                            print->varctrl[n].var[k] = &elem[rttbl->BTC_loc[j] - 1].chms_unsat.s_conc[k - rttbl->NumStc];
                        }
                        else
                        {
                            print->varctrl[n].var[k] = &elem[rttbl->BTC_loc[j] - num_elements - 1].chms_gw.s_conc[k - rttbl->NumStc];
                        }
                    }
                    n++;
                }
#endif
#endif
            default:
                break;
            }
        }
    }

    if (n > MAXPRINT)
    {
        PIHMprintf(VL_ERROR, "Error: Too many output files. ");
        PIHMprintf(VL_ERROR, "The maximum number of output files is %d.\n",
                   MAXPRINT);
        PIHMexit(EXIT_FAILURE);
    }

    print->nprint = n;

    /*
     * Tecplot output
     */
    n = 0;

    for (int i = 0; i < MAXPRINT; i++)
    {
        if (tpprtvrbl[i] != 0)
        {
            switch (i)
            {
            case SURF_CTRL:
                init_tec_print_var_control(outputdir, "surf", tpprtvrbl[i], ELEMVAR,
                                           HYDROL_STEP, num_elements, meshtbl->numnode,
                                           &print->tp_varctrl[n]);

                for (int j = 0; j < print->tp_varctrl[n].nnodes; j++)
                {
                    print->tp_varctrl[n].x[j] = meshtbl->x[j];
                    print->tp_varctrl[n].y[j] = meshtbl->y[j];
                    print->tp_varctrl[n].zmax[j] = meshtbl->zmax[j];
                    print->tp_varctrl[n].zmin[j] = meshtbl->zmin[j];
                }
                for (int j = 0; j < num_elements; j++)
                {
                    print->tp_varctrl[n].var[j] = &elem[j].ws.surf;
                    print->tp_varctrl[n].node0[j] = elem[j].node_ids[0];
                    print->tp_varctrl[n].node1[j] = elem[j].node_ids[1];
                    print->tp_varctrl[n].node2[j] = elem[j].node_ids[2];
                }
                n++;
                break;
            case UNSAT_CTRL:
                init_tec_print_var_control(outputdir, "unsat", tpprtvrbl[i], ELEMVAR,
                                           HYDROL_STEP, num_elements, meshtbl->numnode,
                                           &print->tp_varctrl[n]);
                for (int j = 0; j < print->tp_varctrl[n].nnodes; j++)
                {
                    print->tp_varctrl[n].x[j] = meshtbl->x[j];
                    print->tp_varctrl[n].y[j] = meshtbl->y[j];
                    print->tp_varctrl[n].zmax[j] = meshtbl->zmax[j];
                    print->tp_varctrl[n].zmin[j] = meshtbl->zmin[j];
                }
                for (int j = 0; j < num_elements; j++)
                {
                    print->tp_varctrl[n].var[j] = &elem[j].ws.unsat;
                    print->tp_varctrl[n].node0[j] = elem[j].node_ids[0];
                    print->tp_varctrl[n].node1[j] = elem[j].node_ids[1];
                    print->tp_varctrl[n].node2[j] = elem[j].node_ids[2];
                }
                n++;
                break;
            case GW_CTRL:
                init_tec_print_var_control(outputdir, "gw", tpprtvrbl[i], ELEMVAR,
                                           HYDROL_STEP, num_elements, meshtbl->numnode,
                                           &print->tp_varctrl[n]);
                for (int j = 0; j < print->tp_varctrl[n].nnodes; j++)
                {
                    print->tp_varctrl[n].x[j] = meshtbl->x[j];
                    print->tp_varctrl[n].y[j] = meshtbl->y[j];
                    print->tp_varctrl[n].zmax[j] = meshtbl->zmax[j];
                    print->tp_varctrl[n].zmin[j] = meshtbl->zmin[j];
                }
                for (int j = 0; j < num_elements; j++)
                {
                    print->tp_varctrl[n].var[j] = &elem[j].ws.gw;
                    print->tp_varctrl[n].node0[j] = elem[j].node_ids[0];
                    print->tp_varctrl[n].node1[j] = elem[j].node_ids[1];
                    print->tp_varctrl[n].node2[j] = elem[j].node_ids[2];
                }
                n++;
                break;
            case RIVSTG_CTRL:
                init_tec_print_var_control(outputdir, "stage", tpprtvrbl[i],
                                           RIVERVAR, HYDROL_STEP, num_river, num_river,
                                           &print->tp_varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->tp_varctrl[n].var[j] =
                        &river[j].ws.stage;
                    print->tp_varctrl[n].x[j] = river[j].topo.x;
                    print->tp_varctrl[n].y[j] = river[j].topo.y;
                    print->tp_varctrl[n].zmax[j] =
                        river[j].topo.zmax;
                    print->tp_varctrl[n].zmin[j] =
                        river[j].topo.zmin;
                }
                n++;
                break;
            case RIVGW_CTRL:
                init_tec_print_var_control(outputdir, "rivgw", tpprtvrbl[i],
                                           RIVERVAR, HYDROL_STEP, num_river, num_river,
                                           &print->tp_varctrl[n]);
                for (int j = 0; j < num_river; j++)
                {
                    print->tp_varctrl[n].var[j] = &river[j].ws.gw;
                    print->tp_varctrl[n].x[j] = river[j].topo.x;
                    print->tp_varctrl[n].y[j] = river[j].topo.y;
                    print->tp_varctrl[n].zmax[j] = river[j].topo.zmax;
                    print->tp_varctrl[n].zmin[j] = river[j].topo.zmin;
                }
                n++;
                break;
            default:
                break;
            }
        }
    }

    if (n > MAXPRINT)
    {
        PIHMprintf(VL_ERROR, "Error: Too many Tecplot output files. ");
        PIHMprintf(VL_ERROR,
                   "The maximum number of Tecplot output files is %d.\n", MAXPRINT);
        PIHMexit(EXIT_FAILURE);
    }

    print->ntpprint = n;
}

void init_print_var_control(const char *outputdir, const char *ext, int intvl,
                            int upd_intvl, int nvar, PrintVariables *varctrl)
{
    // sprintf(varctrl->name, "%s%s.%s", outputdir, project, ext);
    snprintf(varctrl->name, MAXSTRING + 1, "%s%s.%s", outputdir, project, ext);
    if (spinup_mode)
    {
        /* When spinning-up, print interval is set to monthly */
        varctrl->intvl = MONTHLY_OUTPUT;
    }
    else
    {
        varctrl->intvl = intvl;
    }
    varctrl->upd_intvl = upd_intvl;
    varctrl->nvar = nvar;
    varctrl->var = (const double **)malloc(nvar * sizeof(double *));
    varctrl->buffer = (double *)calloc(nvar, sizeof(double));
    varctrl->counter = 0;
}

void init_tec_print_var_control(const char *outputdir, const char *ext, int intvl,
                                int intr, int upd_intvl, int nvar, int nnode, PrintVariables *varctrl)
{
    snprintf(varctrl->name, MAXSTRING + 1, "%s%s.%s", outputdir, project, ext);
    varctrl->intvl = intvl;
    varctrl->intr = intr;
    varctrl->upd_intvl = upd_intvl;
    varctrl->nvar = nvar;
    varctrl->nnodes = nnode;

    varctrl->x = (double *)malloc(nnode * sizeof(double));
    varctrl->y = (double *)malloc(nnode * sizeof(double));
    varctrl->zmin = (double *)malloc(nnode * sizeof(double));
    varctrl->zmax = (double *)malloc(nnode * sizeof(double));
    if (intr == ELEMVAR)
    {
        varctrl->node0 = (int *)malloc(nvar * sizeof(int));
        varctrl->node1 = (int *)malloc(nvar * sizeof(int));
        varctrl->node2 = (int *)malloc(nvar * sizeof(int));
    }
    varctrl->var = (const double **)malloc(nvar * sizeof(double *));
    varctrl->buffer = (double *)calloc(nvar, sizeof(double));
    varctrl->counter = 0;
}

#if defined(_RT_)
void Unwrap(char *str, const char *str0)
{
    int i, j = 0;

    for (i = 0; i < (int)strlen(str0); i++)
    {
        if (str0[i] != '\'')
        {
            str[j] = str0[i];
            j++;
        }
    }

    str[j] = '\0';
}
#endif
