#include "pihm.h"

void ReadAlloc(PihmData pihm)
{
    char proj[MAXSTRING / 4];
    char *token;

    PIHMprintf(VL_VERBOSE, "\nRead input files:\n");

    strncpy(proj, project, MAXSTRING / 4);
    if (strstr(proj, ".") != 0)
    {
        token = strtok(proj, ".");
        strcpy(proj, token);
    }
    else
    {
        strcpy(proj, project);
    }

    /* Set file names of the input files */
    sprintf(pihm->filename.riv, "input/%s/%s.riv", proj, proj);
    sprintf(pihm->filename.mesh, "input/%s/%s.mesh", proj, proj);
    sprintf(pihm->filename.att, "input/%s/%s.att", proj, proj);
    sprintf(pihm->filename.soil, "input/%s/%s.soil", proj, proj);
    sprintf(pihm->filename.lc, "input/vegprmt.tbl");
    sprintf(pihm->filename.meteo, "input/%s/%s.meteo", proj, proj);
    sprintf(pihm->filename.lai, "input/%s/%s.lai", proj, proj);
    sprintf(pihm->filename.bc, "input/%s/%s.bc", proj, proj);
    sprintf(pihm->filename.para, "input/%s/%s.para", proj, proj);
    sprintf(pihm->filename.calib, "input/%s/%s.calib", proj, proj);
    sprintf(pihm->filename.ic, "input/%s/%s.ic", proj, proj);
    sprintf(pihm->filename.tecplot, "input/%s/%s.tecplot", proj, proj);
#if defined(_FBR_)
    sprintf(pihm->filename.geol, "input/%s/%s.geol", proj, proj);
    sprintf(pihm->filename.bedrock, "input/%s/%s.bedrock", proj, proj);
#endif
#if defined(_NOAH_)
    sprintf(pihm->filename.lsm, "input/%s/%s.lsm", proj, proj);
    sprintf(pihm->filename.rad, "input/%s/%s.rad", proj, proj);
    sprintf(pihm->filename.ice, "input/%s/%s.ice", proj, proj);
#endif
#if defined(_CYCLES_)
    sprintf(pihm->filename.cycles, "input/%s/%s.cycles", proj, proj);
    sprintf(pihm->filename.soilinit, "input/%s/%s.soilinit", proj, proj);
    sprintf(pihm->filename.crop, "input/%s/%s.crop", proj, proj);
    sprintf(pihm->filename.cyclesic, "input/%s/%s.cyclesic", proj, proj);
#endif
#if defined(_BGC_)
    sprintf(pihm->filename.bgc, "input/%s/%s.bgc", proj, proj);
    sprintf(pihm->filename.bgcic, "input/%s/%s.bgcic", proj, proj);
#endif
#if defined(_RT_)
    sprintf(pihm->filename.chem, "input/%s/%s.chem", proj, proj);
    sprintf(pihm->filename.cini, "input/%s/%s.cini", proj, proj);
    sprintf(pihm->filename.cdbs, "input/%s/%s.cdbs", proj, proj);
    sprintf(pihm->filename.prep, "input/%s/%s.prep", proj, proj);
    sprintf(pihm->filename.rtic, "input/%s/%s.rtic", proj, proj);
#endif

    /* Read river input file */
    ReadRiver(pihm->filename.riv, &pihm->rivtbl, &pihm->shptbl, &pihm->matltbl,
              &pihm->forc);

    /* Read mesh structure input file */
    ReadMesh(pihm->filename.mesh, &pihm->meshtbl);

    /* Read attribute table input file */
    ReadAtt(pihm->filename.att, &pihm->atttbl);

    /* Read soil input file */
    ReadSoil(pihm->filename.soil, &pihm->soiltbl);

    /* Read land cover input file */
    ReadLc(pihm->filename.lc, &pihm->lctbl);

    /* Read meteorological forcing input file */
    ReadForc(pihm->filename.meteo, &pihm->forc);

    /* Read LAI input file */
    ReadLai(pihm->filename.lai, &pihm->forc, &pihm->atttbl);

    /* Read source and sink input file */
    pihm->forc.nsource = 0;
#if NOT_YET_IMPLEMENTED
    ReadSS();
#endif

    /* Read model control file */
    ReadPara(pihm->filename.para, &pihm->ctrl);

    /* Read calibration input file */
    ReadCalib(pihm->filename.calib, &pihm->cal);

    if (tecplot)
    {
        ReadTecplot(pihm->filename.tecplot, &pihm->ctrl);
    }

#if defined(_FBR_)
    /* Read geology input file */
    ReadGeol(pihm->filename.geol, &pihm->geoltbl);

    /* Read bedrock control file */
    ReadBedrock(pihm->filename.bedrock, &pihm->atttbl, &pihm->meshtbl,
                &pihm->ctrl);
#endif

#if defined(_NOAH_)
    /* Read LSM input file */
    ReadLsm(pihm->filename.lsm, &pihm->siteinfo, &pihm->ctrl, &pihm->noahtbl);

    if (pihm->ctrl.rad_mode == TOPO_SOL)
    {
        /* Read radiation input file */
        ReadRad(pihm->filename.rad, &pihm->forc);
    }
#endif

#if defined(_RT_)
    /* Read RT input file */
    ReadChem(pihm->filename.chem, pihm->filename.cdbs, pihm->chemtbl,
             pihm->kintbl, &pihm->rttbl, &pihm->forc, &pihm->ctrl);

    ReadCini(pihm->filename.cini, pihm->chemtbl, pihm->rttbl.NumStc,
             &pihm->atttbl, &pihm->chmictbl);

    if (pihm->forc.PrpFlg == 2)
    {
        ReadPrep(pihm->filename.prep, pihm->chemtbl, &pihm->rttbl, &pihm->forc);
    }
#endif

    /* Read boundary condition input file
     * Boundary conditions might be needed by FBR and RT thus should be read in
     * after reading bedrock and chemistry input */
#if defined(_RT_)
    ReadBc(pihm->filename.bc, &pihm->forc, &pihm->atttbl, &pihm->rttbl,
           pihm->chemtbl);
#else
    ReadBc(pihm->filename.bc, &pihm->forc, &pihm->atttbl);
#endif

#if defined(_CYCLES_)
    /* Read Cycles simulation control file */
    ReadCyclesCtrl(pihm->filename.cycles, &pihm->agtbl, &pihm->ctrl);

    /* Read soil initialization file */
    ReadSoilInit(pihm->filename.soilinit, &pihm->soiltbl);

    /* Read crop description file */
    ReadCrop(pihm->filename.crop, pihm->epctbl);

    /* Read operation file */
    ReadMultOper(&pihm->agtbl, pihm->epctbl, pihm->opertbl);
#endif

#if defined(_BGC_)
    ReadBgc(pihm->filename.bgc, &pihm->ctrl, &pihm->co2, &pihm->ndepctrl,
            &pihm->cninit, pihm->filename.co2, pihm->filename.ndep);

    /* Read Biome-BGC epc files */
    ReadEpc(&pihm->epctbl);

    /* Read CO2 and Ndep files */
    pihm->forc.co2 = (TimeSeriesData *)malloc(sizeof(TimeSeriesData));
    pihm->forc.ndep = (TimeSeriesData *)malloc(sizeof(TimeSeriesData));

    if (pihm->co2.varco2)
    {
        pihm->forc.nco2 = 1;
        ReadAnnFile(&pihm->forc.co2[0], pihm->filename.co2);
    }
    else
    {
        pihm->forc.nco2 = 0;
    }

    if (pihm->ndepctrl.varndep)
    {
        pihm->forc.nndep = 1;
        ReadAnnFile(&pihm->forc.ndep[0], pihm->filename.ndep);
    }
    else
    {
        pihm->forc.nndep = 0;
    }
#endif
}
