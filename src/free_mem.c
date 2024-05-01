#include "pihm.h"

void free_pihm_data(PihmData pihm)
{
    int i;

    free_river_table(&pihm->rivtbl);

    free_river_shape_table(&pihm->shptbl);

    free_material_table(&pihm->matltbl);

    free_mesh_table(&pihm->meshtbl);

    free_element_attribute(&pihm->atttbl);

    free_soil_entry_table(&pihm->soiltbl);

#if defined(_FBR_)
    FreeGeoltbl(&pihm->geoltbl);
#endif

    free_land_cover_table(&pihm->lctbl);

    free_forcing(&pihm->forc);

#if defined(_BGC_)
    FreeEpctbl(&pihm->epctbl);
#endif

    free_control(&pihm->ctrl);

    /*
     * Close files
     */
    if (pihm->ctrl.waterbal)
    {
        fclose(pihm->print.watbal_file);
    }
    if (debug_mode)
    {
        fclose(pihm->print.cvodeperf_file);
    }
    for (i = 0; i < pihm->print.nprint; i++)
    {
        free(pihm->print.varctrl[i].var);
        free(pihm->print.varctrl[i].buffer);
        fclose(pihm->print.varctrl[i].datfile);
        if (pihm->ctrl.ascii)
        {
            fclose(pihm->print.varctrl[i].txtfile);
        }
    }
    if (tecplot)
    {
        for (i = 0; i < pihm->print.ntpprint; i++)
        {
            fclose(pihm->print.tp_varctrl[i].datfile);
        }
    }
    free(pihm->elem);
    free(pihm->river);
}

void free_river_table(RiverTile *rivtbl)
{
    free(rivtbl->fromnode);
    free(rivtbl->tonode);
    free(rivtbl->down);
    free(rivtbl->leftele);
    free(rivtbl->rightele);
    free(rivtbl->shp);
    free(rivtbl->matl);
    free(rivtbl->bc);
    free(rivtbl->rsvr);
}

void free_river_shape_table(RiverShape *shptbl)
{
    free(shptbl->depth);
    free(shptbl->intrpl_ord);
    free(shptbl->coeff);
}

void free_material_table(RiverMaterial *matltbl)
{
    free(matltbl->rough);
    free(matltbl->cwr);
    free(matltbl->ksath);
    free(matltbl->ksatv);
    free(matltbl->bedthick);
}

void free_mesh_table(MeshEntry *meshtbl)
{
    int i;

    for (i = 0; i < num_elements; i++)
    {
        free(meshtbl->node[i]);
        free(meshtbl->nabr[i]);
    }
    free(meshtbl->node);
    free(meshtbl->nabr);
    free(meshtbl->x);
    free(meshtbl->y);
    free(meshtbl->zmin);
    free(meshtbl->zmax);
#if defined(_FBR_)
    free(meshtbl->zbed);
#endif
}

void free_element_attribute(ElementAttribute *atttbl)
{
    int i;

    /* Free attribute input structure */
    for (i = 0; i < num_elements; i++)
    {
        free(atttbl->bc[i]);
#if defined(_FBR_)
        free(atttbl->fbr_bc[i]);
#endif
    }
    free(atttbl->bc);
#if defined(_FBR_)
    free(atttbl->fbr_bc);
#endif
    free(atttbl->soil);
    free(atttbl->geol);
    free(atttbl->lc);
    free(atttbl->meteo);
    free(atttbl->lai);
    free(atttbl->source);
}

void free_soil_entry_table(SoilEntry *soiltbl)
{
    free(soiltbl->silt);
    free(soiltbl->clay);
    free(soiltbl->om);
    free(soiltbl->bd);
    free(soiltbl->kinfv);
    free(soiltbl->ksatv);
    free(soiltbl->ksath);
    free(soiltbl->smcmax);
    free(soiltbl->smcmin);
    free(soiltbl->qtz);
    free(soiltbl->alpha);
    free(soiltbl->beta);
    free(soiltbl->areafh);
    free(soiltbl->areafv);
    free(soiltbl->dmac);
    free(soiltbl->smcref);
    free(soiltbl->smcwlt);
}

#if defined(_FBR_)
void FreeGeoltbl(GeologyEntry *geoltbl)
{
    free(geoltbl->ksatv);
    free(geoltbl->ksath);
    free(geoltbl->smcmax);
    free(geoltbl->smcmin);
    free(geoltbl->alpha);
    free(geoltbl->beta);
}
#endif

void free_land_cover_table(LandCoverEntry *lctbl)
{
    /* Free landcover input structure */
    free(lctbl->laimax);
    free(lctbl->laimin);
    free(lctbl->vegfrac);
    free(lctbl->albedomin);
    free(lctbl->albedomax);
    free(lctbl->emissmin);
    free(lctbl->emissmax);
    free(lctbl->z0min);
    free(lctbl->z0max);
    free(lctbl->hs);
    free(lctbl->snup);
    free(lctbl->rgl);
    free(lctbl->rsmin);
    free(lctbl->rough);
    free(lctbl->rzd);
}

void free_forcing(Forcing *forc)
{
    int i, j;

    if (forc->nriverbc > 0)
    {
        for (i = 0; i < forc->nriverbc; i++)
        {
            for (j = 0; j < forc->riverbc[i].length; j++)
            {
                free(forc->riverbc[i].data[j]);
            }
            free(forc->riverbc[i].ftime);
            free(forc->riverbc[i].data);
        }
        free(forc->riverbc);
    }

    if (forc->nmeteo > 0)
    {
        for (i = 0; i < forc->nmeteo; i++)
        {
            for (j = 0; j < forc->meteo[i].length; j++)
            {
                free(forc->meteo[i].data[j]);
            }
            free(forc->meteo[i].ftime);
            free(forc->meteo[i].data);
            free(forc->meteo[i].value);
        }
        free(forc->meteo);
    }

    if (forc->nlai > 0)
    {
        for (i = 0; i < forc->nlai; i++)
        {
            for (j = 0; j < forc->lai[i].length; j++)
            {
                free(forc->lai[i].data[j]);
            }
            free(forc->lai[i].ftime);
            free(forc->lai[i].data);
            free(forc->lai[i].value);
        }
        free(forc->lai);
    }

    if (forc->nbc > 0)
    {
        for (i = 0; i < forc->nbc; i++)
        {
            for (j = 0; j < forc->bc[i].length; j++)
            {
                free(forc->bc[i].data[j]);
            }
            free(forc->bc[i].ftime);
            free(forc->bc[i].data);
            free(forc->bc[i].value);
        }
        free(forc->bc);
    }

#if defined(_NOAH_)
    if (forc->nrad > 0)
    {
        for (i = 0; i < forc->nrad; i++)
        {
            for (j = 0; j < forc->rad[i].length; j++)
            {
                free(forc->rad[i].data[j]);
            }
            free(forc->rad[i].ftime);
            free(forc->rad[i].data);
            free(forc->rad[i].value);
        }
        free(forc->rad);
    }
#endif

#if defined(_BGC_)
    if (forc->nco2 > 0)
    {
        for (j = 0; j < forc->co2[0].length; j++)
        {
            free(forc->co2[0].data[j]);
        }
        free(forc->co2[0].ftime);
        free(forc->co2[0].data);
        free(forc->co2[0].value);
    }
    free(forc->co2);

    if (forc->nndep > 0)
    {
        for (j = 0; j < forc->ndep[0].length; j++)
        {
            free(forc->ndep[0].data[j]);
        }
        free(forc->ndep[0].ftime);
        free(forc->ndep[0].data);
        free(forc->ndep[0].value);
    }
    free(forc->ndep);
#endif

#if defined(_RT_)
    if (forc->PrpFlg == 2)
    {
        for (i = 0; i < forc->nprcpc; i++)
        {
            for (j = 0; j < forc->prcpc[i].length; j++)
            {
                free(forc->prcpc[i].data[j]);
            }
            free(forc->prcpc[i].ftime);
            free(forc->prcpc[i].data);
            free(forc->prcpc[i].value);
        }
    }
#endif
}

#if defined(_BGC_)
void FreeEpctbl(epctbl_struct *epctbl)
{
    free(epctbl->woody);
    free(epctbl->evergreen);
    free(epctbl->c3_flag);
    free(epctbl->phenology_flag);
    free(epctbl->onday);
    free(epctbl->offday);
    free(epctbl->transfer_days);
    free(epctbl->litfall_days);
    free(epctbl->leaf_turnover);
    free(epctbl->froot_turnover);
    free(epctbl->livewood_turnover);
    free(epctbl->daily_mortality_turnover);
    free(epctbl->daily_fire_turnover);
    free(epctbl->alloc_frootc_leafc);
    free(epctbl->alloc_newstemc_newleafc);
    free(epctbl->alloc_newlivewoodc_newwoodc);
    free(epctbl->alloc_crootc_stemc);
    free(epctbl->alloc_prop_curgrowth);
    free(epctbl->avg_proj_sla);
    free(epctbl->sla_ratio);
    free(epctbl->lai_ratio);
    free(epctbl->ext_coef);
    free(epctbl->flnr);
    free(epctbl->psi_open);
    free(epctbl->psi_close);
    free(epctbl->vpd_open);
    free(epctbl->vpd_close);
    free(epctbl->froot_cn);
    free(epctbl->leaf_cn);
    free(epctbl->livewood_cn);
    free(epctbl->deadwood_cn);
    free(epctbl->leaflitr_cn);
    free(epctbl->leaflitr_flab);
    free(epctbl->leaflitr_fucel);
    free(epctbl->leaflitr_fscel);
    free(epctbl->leaflitr_flig);
    free(epctbl->frootlitr_flab);
    free(epctbl->frootlitr_fucel);
    free(epctbl->frootlitr_fscel);
    free(epctbl->frootlitr_flig);
    free(epctbl->deadwood_fucel);
    free(epctbl->deadwood_fscel);
    free(epctbl->deadwood_flig);
}
#endif

void free_control(RunParameters *ctrl)
{
    free(ctrl->tout);
}
