#ifndef PIHM_STRUCT_HEADER
#define PIHM_STRUCT_HEADER

/* Time structure */
typedef struct PihmTime
{
    int t;             /* time since the epoch (s) */
    int year;          /* current year */
    int month;         /* current month */
    int day;           /* current day of month */
    int hour;          /* current hour */
    int minute;        /* current minute */
    char str[17];      /* time string (yyyy-mm-dd HH:MM) */
    char strshort[13]; /* time string (yyyymmddHHMM) */
} PihmTime;

/* Site information structure */
typedef struct SiteInfo
{
    double longitude; /* (degree) */
    double latitude;  /* (degree) */
    double zmax;      /* average surface elevation (m) */
    double zmin;      /* average soil bottom elevation (m)
                       */
    double area;      /* total area (m2) */
    double tavg;      /* annual average air temperature
                       * (K) */
} SiteInfo;

#if defined(_BGC_)
/* A structure to hold information on the annual co2 concentration */
typedef struct co2control_struct
{
    int varco2;    /* 0 = const 1 = use file */
    double co2ppm; /* constant CO2 concentration (ppm)
                    */
} co2control_struct;

/* A structure to hold annual nitrogen deposition data */
typedef struct ndepcontrol_struct
{
    int varndep; /* 0 = const 1 = use file */
    double ndep; /* wet + dry atmospheric deposition
                  * of N (kgN m-2 yr-1) */
    double nfix; /* symbiotic + asymbiotic fixation
                  * of N (kgN m-2 yr-1) */
} ndepcontrol_struct;

/* Carbon and nitrogen state initialization structure */
typedef struct cninit_struct
{
    double max_leafc; /* first-year displayed + stored
                       * leafc (kgC m-2) */
    double max_stemc; /* first-year total stem carbon
                       * (kgC m-2) */
    double cwdc;      /* coarse woody debris C (kgC m-2)*/
    double litr1c;    /* litter labile C (kgC m-2) */
    double litr2c;    /* litter unshielded cellulose C
                       * (kgC m-2) */
    double litr3c;    /* litter shielded cellulose C
                       * (kgC m-2) */
    double litr4c;    /* litter lignin C (kgC m-2) */
    double soil1c;    /* microbial recycling pool C (fast)
                       * (kgC m-2) */
    double soil2c;    /* microbial recycling pool C
                       * (medium) (kgC m-2) */
    double soil3c;    /* microbial recycling pool C (slow)
                       * (kgC m-2) */
    double soil4c;    /* recalcitrant SOM C (humus,
                       * slowest) (kgC m-2) */
    double litr1n;    /* litter labile N (kgN m-2) */
    double sminn;     /* soil mineral N (kgN m-2) */
} cninit_struct;
#endif

/* Global calibration coefficients */
typedef struct CalibrationParameters
{
    double ksath; // horizontal saturated hydraulic conductivity
    double ksatv; // vertical saturated hydraulic conductivity
    double kinfv; // infiltration hydralic conductivity
    double kmach;
    double kmacv;
    double dinf;
    double rzd;
    double dmac;
    double porosity; // Porosity of the soil
    double alpha;
    double beta;
    double areafv;
    double areafh;
    double vegfrac;
    double albedo;
    double rough;
    double ec;
    double ett;
    double edir;
    double rivrough;
    double rivksath;
    double rivksatv;
    double rivbedthick;
    double rivdepth;
    double rivshpcoeff;
    double prcp;   /* multiplier of precipitation (-)*/
    double sfctmp; /* offset of surface air temperature
                    * (K) */
#if defined(_BGC_)
    double mortality;
    double sla;
#endif
#if defined(_NOAH_)
    double smcref;
    double smcwlt;
    double rsmin;
    double drip;
    double cmcmax;
    double czil;
    double fxexp;
    double cfactr;
    double rgl;
    double hs;
#endif
#if defined(_RT_)
    double rate;      /* rate constant */
    double ssa;       /* specific surface area */
    double gwinflux;  /* GW influx (M yr-1) */
    double prcpconc;  /* precip conc */
    double initconc;  /* initial conc */
    double Xsorption; /* DOC sorption */
#endif
} CalibrationParameters;

/* Model control parameters */
typedef struct RunParameters
{
    int ascii;               /* flag to turn on ascii output */
    int waterbal;            /* flag to turn on water balance
                              * diagnostic output */
    int write_ic;            /* flag to write model output as
                              * initial conditions */
    int nstep;               /* number of external time steps
                              * (when results can be printed) for
                              * the whole simulation */
    int cstep;               /* current model step (from 0) */
    int prtvrbl[MAXPRINT];   /* number of output */
    int tpprtvrbl[MAXPRINT]; /* time interval to tecplot output
                              * average values of variables;
                              * 0 = turn off output */
    int init_type;           /* initialization mode:
                              * 0 = relaxed mode,
                              * 1 = use .ic file */
    int unsat_mode;          /* unsaturation formulation:
                              * 1 = kinematic, 2 = diffusion */
    int surf_mode;           /* surface overland flow formulation
                              * 1 = kinematic, 2 = diffusion */
    int riv_mode;            /* river routing formulation:
                              * 1 = kinematic, 2 = diffusion */
    int etstep;              /* land surface (ET) time step (s)*/
    int starttime;           /* start time of simulation (ctime)
                              */
    int endtime;             /* end time of simulation (ctime) */
    int stepsize;            /* model step size (s) */
    int *tout;               /* model output times (ctime) */
    double abstol;           /* absolute solver tolerance (m) */
    double reltol;           /* relative solver tolerance (-) */
    double initstep;         /* initial step size (s) */
    double maxstep;          /* CVode maximum step size (s) */
    double stmin;            /* minimum allowed CVode max step
                              * size (s) */
    double nncfn;            /* number of non-convergence
                              * failures tolerance */
    double nnimax;           /* maximum number of non-linear
                              * iterations */
    double nnimin;           /* minimum number of non-linear
                              * iterations */
    double decr;             /* decrease factor (-) */
    double incr;             /* increase factor (-) */
    int maxspinyears;        /* maximum number of years for
                              * spinup run */
#if defined(_BGC_)
    int read_bgc_restart;  /* flag to read BGC restart file */
    int write_bgc_restart; /* flag to write BGC restart file */
#endif
#if defined(_CYCLES_)
    int read_cycles_restart;
    int write_cycles_restart;
#endif
#if defined(_NOAH_)
    int nsoil;             /* number of standard soil layers */
    double sldpth[MAXLYR]; /* thickness of soil layer (m) */
    int rad_mode;          /* radiation forcing mode:
                            * 0 = uniform, 1 = topographic */
#endif
#if defined(_RT_)
    int read_rt_restart;  /* flag to read chemistry restart
                           * file */
    int write_rt_restart; /* flag to write chemistry restart
                           * file */
    int RT_delay;         /* RT start after PIHM running for a
                           * period of time (s) */
    int AvgScl;           /* reaction time step (s) */
#endif
} RunParameters;

/* Print variable control structure */
typedef struct PrintVariables
{
    char name[MAXSTRING]; /* name of output file */
    int intvl;            /* output interval (s) */
    int intr;             /* output type flag */
    int upd_intvl;        /* 0: hydrology step
                           * 1: land surface step
                           * 2: CN step */
    int nvar;             /* number of variables for print */
    const double **var;   /* pointers to model variables */
    double *buffer;       /* buffer for averaging variables */
    int counter;          /* counter for averaging variables*/
    FILE *txtfile;        /* pointer to txt file */
    FILE *datfile;        /* pointer to binary file */
    /* tecplot coordinate variables */
    double *x;
    double *y;
    double *zmax;
    double *zmin;
    int nnodes;
    int *node0;
    int *node1;
    int *node2;
} PrintVariables;

/* Print structure */
typedef struct PrintStructure
{
    PrintVariables varctrl[MAXPRINT];
    PrintVariables tp_varctrl[MAXPRINT];
    int nprint;           /* number of output variables */
    int ntpprint;         /* number of tecplot output
                           * variables */
    FILE *watbal_file;    /* pointer to water balance file */
    FILE *cvodeperf_file; /* pointer to CVode performance file
                           */
} PrintStructure;

typedef struct PihmData
{
    SiteInfo siteinfo;
    OutputFilenames filename;
    MeshEntry meshtbl;
    ElementAttribute atttbl;
    SoilEntry soiltbl;
    GeologyEntry geoltbl;
    LandCoverEntry lctbl;
    RiverTile rivtbl;
    RiverShape shptbl;
    RiverMaterial matltbl;
#if defined(_NOAH_)
    NoahLandSurfaceEntry noahtbl;
#endif
#if defined(_CYCLES_)
    agtbl_struct agtbl;
    epconst_struct epctbl[MAXCROP];
    opertbl_struct opertbl[MAXOP];
#endif
#if defined(_BGC_)
    co2control_struct co2;
    ndepcontrol_struct ndepctrl;
    epctbl_struct epctbl;
    cninit_struct cninit;
#endif
    Forcing forc;
    MeshElement *elem;
    river_struct *river;
    CalibrationParameters cal;
    RunParameters ctrl;
    PrintStructure print;
#if defined(_RT_)
    ChemicalEntry chemtbl[MAXSPS];
    KineticEntry kintbl[MAXSPS];
    ReactionNetwork rttbl;
    chmictbl_struct chmictbl;
#endif
} *PihmData;

#endif
