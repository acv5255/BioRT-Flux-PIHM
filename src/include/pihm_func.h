#ifndef PIHM_FUNC_HEADER
#define PIHM_FUNC_HEADER

#define _ARITH_

/* State variables */
#define SURF(i) (i)
#define UNSAT(i) (i + nelem)
#define GW(i) (i + 2 * nelem)
#define RIVSTG(i) (i + 3 * nelem)
#define RIVGW(i) (i + 3 * nelem + nriver)

#if defined(_FBR_)
#define FBRUNSAT(i) (i + 3 * nelem + 2 * nriver)
#define FBRGW(i) (i + 4 * nelem + 2 * nriver)
#endif

#if defined(_RT_)
#if defined(_FBR_)
#define UNSAT_MOLE(i, j) ((i) * NumSpc + j + 5 * nelem + 2 * nriver)
#define GW_MOLE(i, j) ((i) * NumSpc + j + (5 + NumSpc) * nelem + 2 * nriver)
#define STREAM_MOLE(i, j) ((i) * NumSpc + j + (5 + 2 * NumSpc) * nelem + 2 * nriver)
#define RIVBED_MOLE(i, j) ((i) * NumSpc + j + (5 + 2 * NumSpc) * nelem + (2 + NumSpc) * nriver)
#define FBRUNSAT_MOLE(i, j) ((i) * NumSpc + j + (5 + 2 * NumSpc) * nelem + (2 + 2 * NumSpc) * nriver)
#define FBRGW_MOLE(i, j) ((i) * NumSpc + j + (5 + 3 * NumSpc) * nelem + (2 + 2 * NumSpc) * nriver)
#else
#define UNSAT_MOLE(i, j) ((i) * NumSpc + j + 3 * nelem + 2 * nriver)
#define GW_MOLE(i, j) ((i) * NumSpc + j + (3 + NumSpc) * nelem + 2 * nriver)
#define STREAM_MOLE(i, j) ((i) * NumSpc + j + (3 + 2 * NumSpc) * nelem + 2 * nriver)
#define RIVBED_MOLE(i, j) ((i) * NumSpc + j + (3 + 2 * NumSpc) * nelem + (2 + NumSpc) * nriver)
#endif
#endif

#if defined(_BGC_) && !defined(_LUMPED_)
#define SURFN(i) (i + 3 * nelem + 2 * nriver)
#define SMINN(i) (i + 4 * nelem + 2 * nriver)
#define STREAMN(i) (i + 5 * nelem + 2 * nriver)
#define RIVBEDN(i) (i + 5 * nelem + 3 * nriver)
#else
#define LUMPED_SMINN (3 * nelem + 2 * nriver)
#endif

#if defined(_CYCLES_)
#define NO3(i) (i + 3 * nelem + 2 * nriver)
#define NH4(i) (i + 4 * nelem + 2 * nriver)
#define STREAMNO3(i) (i + 5 * nelem + 2 * nriver)
#define RIVBEDNO3(i) (i + 5 * nelem + 3 * nriver)
#define STREAMNH4(i) (i + 5 * nelem + 4 * nriver)
#define RIVBEDNH4(i) (i + 5 * nelem + 5 * nriver)
#endif

#define AvgElev(...) _WsAreaElev(WS_ZMAX, __VA_ARGS__)
#define AvgZmin(...) _WsAreaElev(WS_ZMIN, __VA_ARGS__)
#define TotalArea(...) _WsAreaElev(WS_AREA, __VA_ARGS__)

/* CVode functions */
#if defined(_CVODE_OMP)
#define N_VNew(N) N_VNew_OpenMP(N, nthreads)
#define NV_DATA NV_DATA_OMP
#define NV_Ith NV_Ith_OMP
#else
#define N_VNew(N) N_VNew_Serial(N)
#define NV_DATA NV_DATA_S
#define NV_Ith NV_Ith_S
#endif

/* PIHM system function */
#define PIHMexit(...) _custom_exit(__FILE__, __LINE__, __FUNCTION__, debug_mode, __VA_ARGS__)
#define PIHMprintf(...) _custom_printf(__FILE__, __LINE__, __FUNCTION__, debug_mode, verbose_mode, __VA_ARGS__)
#if defined(_WIN32) || defined(_WIN64)
#define PIHMmkdir(path) _mkdir((path))
#define PIHMaccess(path, amode) _access((path), (amode))
#else
#define PIHMmkdir(path) mkdir(path, 0755)
#define PIHMaccess(path, amode) access((path), (amode))
#endif
#if defined(_MSC_VER)
#define timegm _mkgmtime
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

#define Cycles_exit PIHMexit
#define Cycles_printf PIHMprintf

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/*
 * Function Declarations
 */
void _InitLc(elem_struct *, const LandCoverEntry *,
             const CalibrationParameters *);
double _WsAreaElev(int, const elem_struct *);
void AdjCVodeMaxStep(void *, RunParameters *);
#if defined(_RT_)
void ApplyBc(const ReactionNetwork *, Forcing *, elem_struct *,
             river_struct *, int);
#else
void ApplyBc(Forcing *, elem_struct *, river_struct *, int);
#endif
#if defined(_RT_)
void ApplyElemBc(const ReactionNetwork *, Forcing *, elem_struct *,
                 int);
#else
void ApplyElemBc(Forcing *, elem_struct *, int);
#endif
#if defined(_RT_)
void ApplyForc(Forcing *, ReactionNetwork *, elem_struct *, int,
               int, const SiteInfo *);
#elif defined(_NOAH_)
void ApplyForc(Forcing *, elem_struct *, int, int,
               const siteinfo_struct *);
#else
void ApplyForc(Forcing *, elem_struct *, int);
#endif
#if defined(_BGC_) || defined(_CYCLES_)
void ApplyLai(elem_struct *);
#else
void ApplyLai(Forcing *, elem_struct *, int);
#endif
#if defined(_NOAH_)
void ApplyMeteoForc(Forcing *, elem_struct *, int, int,
                    const SiteInfo *);
#else
void ApplyMeteoForc(Forcing *, elem_struct *, int);
#endif
void ApplyRiverBc(Forcing *, river_struct *, int);
double AvgKv(const soil_struct *, double, double, double);
double AvgH(double, double, double);
double AvgHsurf(double, double, double);
void BackupInput(const char *, const OutputFilenames *);
void BoundFluxElem(int, int, const bc_struct *,
                   const wstate_struct *, const topo_struct *, const soil_struct *,
                   wflux_struct *);
double BoundFluxRiver(int, const river_wstate_struct *,
                      const river_topo_struct *, const shp_struct *, const matl_struct *,
                      const river_bc_struct *bc);
void CalcModelStep(RunParameters *);
double ChanFlowElemToRiver(const elem_struct *, double,
                           const river_struct *, double);
double ChanFlowRiverToRiver(const river_struct *, const river_struct *,
                            int);
double ChanLeak(const river_wstate_struct *, const river_topo_struct *,
                const shp_struct *, const matl_struct *);
void CheckCVodeFlag(int);
void CheckDy(double, const char *, const char *, int, double);
#if defined(_BGC_)
int CheckSteadyState(const elem_struct *, double, int, int, int);
#else
int CheckSteadyState(const elem_struct *, double, int, int);
#endif
void CorrElev(elem_struct *, river_struct *);
void CreateOutputDir(char *);
double DhByDl(const double *, const double *, const double *);
double EffKh(const soil_struct *, double);
double EffKinf(const soil_struct *, double, double, double, double,
               double);
double EffKv(const soil_struct *, double, int);
void EtExtract(elem_struct *);
double FieldCapacity(double, double, double, double);
void FreeAtttbl(ElementAttribute *);
void FreeCtrl(RunParameters *);
void FreeForc(Forcing *);
void FreeLctbl(LandCoverEntry *);
void FreeMatltbl(RiverMaterial *);
void FreeMeshtbl(MeshEntry *);
void FreeMem(PihmData);
void FreeRivtbl(RiverTile *);
void FreeShptbl(RiverShape *);
void FreeSoiltbl(SoilEntry *);
void FrictSlope(const elem_struct *, const river_struct *, int,
                double *, double *);
void Hydrol(elem_struct *, river_struct *, const RunParameters *);
double Infil(const wstate_struct *, const wstate_struct *,
             const wflux_struct *, const topo_struct *, const soil_struct *, double);
void InitEFlux(eflux_struct *);
void InitEState(estate_struct *);
#if defined(_RT_)
void InitForc(elem_struct *, Forcing *, const CalibrationParameters *,
              const ReactionNetwork *);
#else
void InitForc(elem_struct *, Forcing *, const CalibrationParameters *);
#endif
void Initialize(PihmData, N_Vector, void **);
void InitLc(elem_struct *, const LandCoverEntry *,
            const CalibrationParameters *);
void InitMesh(elem_struct *, const MeshEntry *);
void InitOutputFile(PrintStructure *, const char *, int, int);
void InitPrtVarCtrl(const char *, const char *, int, int, int,
                    PrintVariables *);
void InitRiver(river_struct *, elem_struct *, const RiverTile *,
               const RiverShape *, const RiverMaterial *, const MeshEntry *,
               const CalibrationParameters *);
void InitRiverWFlux(river_wflux_struct *);
void InitRiverWState(river_wstate_struct *);
#if defined(_NOAH_)
void InitSoil(elem_struct *, const SoilEntry *,
              const NoahLandSurfaceEntry *, const CalibrationParameters *);
#else
void InitSoil(elem_struct *, const SoilEntry *,
              const CalibrationParameters *);
#endif
void InitSurfL(elem_struct *, const MeshEntry *);
void InitTecPrtVarCtrl(const char *, const char *, int, int, int,
                       int, int, PrintVariables *);
void InitTopo(elem_struct *, const MeshEntry *);
void InitVar(elem_struct *, river_struct *, N_Vector);
void InitWbFile(char *, char *, FILE *);
void InitWFlux(wflux_struct *);
void InitWState(wstate_struct *);
void IntcpSnowEt(int, double, elem_struct *, const CalibrationParameters *);
void IntrplForc(TimeSeriesData *, int, int, int);
double KrFunc(double, double);
void LateralFlow(elem_struct *, const river_struct *, int);
#if defined(_CYCLES_)
void MapOutput(const int *, const int *, const epconst_struct[],
               const elem_struct *, const river_struct *, const MeshEntry *,
               const char *, PrintStructure *);
#elif defined(_RT_)
void MapOutput(const int *, const int *, const ChemicalEntry[],
               const ReactionNetwork *, const elem_struct *, const river_struct *,
               const MeshEntry *, const char *, PrintStructure *);
#else
void MapOutput(const int *, const int *, const elem_struct *,
               const river_struct *, const MeshEntry *, const char *, print_struct *);
#endif
#if defined(_FBR_)
void MassBalance(const wstate_struct *, const wstate_struct *,
                 wflux_struct *, double *, const soil_struct *, const geol_struct *, double,
                 double);
#else
void MassBalance(const wstate_struct *, const wstate_struct *,
                 wflux_struct *, double *, const soil_struct *, double, double);
#endif
double MonthlyLai(int, int);
double MonthlyMf(int);
double MonthlyRl(int, int);
int NumStateVar(void);
int Ode(realtype, N_Vector, N_Vector, void *);
double OutletFlux(int, const river_wstate_struct *,
                  const river_topo_struct *, const shp_struct *, const matl_struct *,
                  const river_bc_struct *);
double OverLandFlow(double, double, double, double, double);
double OvlFlowElemToElem(const elem_struct *, const elem_struct *, int,
                         double, int);
double OvlFlowElemToRiver(const elem_struct *, const river_struct *);
void ParseCmdLineParam(int, char *[], char *);
void PIHM(PihmData, void *, N_Vector, double);
PihmTime PIHMTime(int);
void PrintCVodeFinalStats(void *);
void PrintData(PrintVariables *, int, int, int, int);
void PrintDataTecplot(PrintVariables *, int, int, int);
void PrintInit(const elem_struct *, const river_struct *,
               const char *, int, int, int, int);
int PrintNow(int, int, const PihmTime *);
void PrintPerf(void *, int, int, double, double, double, FILE *);
void PrintWaterBal(FILE *, int, int, int, const elem_struct *,
                   const river_struct *);
void ProgressBar(int);
double Psi(double, double, double);
double PtfAlpha(double, double, double, double, int);
double PtfBeta(double, double, double, double, int);
double PtfKv(double, double, double, double, int);
double PtfThetar(double, double);
double PtfThetas(double, double, double, double, int);
double Qtz(int);
void ReadAlloc(PihmData);
void ReadAtt(const char *, ElementAttribute *);
#if defined(_RT_)
void ReadBc(const char *, Forcing *, const ElementAttribute *,
            const ReactionNetwork *, const ChemicalEntry[]);
#else
void ReadBc(const char *, Forcing *, const ElementAttribute *);
#endif
void ReadCalib(const char *, CalibrationParameters *);
void ReadForc(const char *, Forcing *);
void ReadIc(const char *, elem_struct *, river_struct *);
int ReadKeyword(const char *, const char *, void *, char,
                const char *, int);
void ReadLai(const char *, Forcing *, const ElementAttribute *);
void ReadLc(const char *, LandCoverEntry *);
void ReadMesh(const char *, MeshEntry *);
void ReadPara(const char *, RunParameters *);
int ReadPrtCtrl(const char *, const char *, const char *, int);
void ReadRiver(const char *, RiverTile *, RiverShape *,
               RiverMaterial *, Forcing *);
void ReadSoil(const char *, SoilEntry *);
void ReadTecplot(const char *, RunParameters *);
int ReadTS(const char *, int *, double *, int);
double Recharge(const wstate_struct *, const wflux_struct *,
                const soil_struct *);
double RiverCroSectArea(int, double, double);
double RiverEqWid(int, double, double);
void RiverFlow(elem_struct *, river_struct *, int);
double RiverPerim(int, double, double);
void RiverToElem(river_struct *, elem_struct *, elem_struct *);
int roundi(double);
#if defined(_OPENMP)
void RunTime(double, double *, double *);
#else
void RunTime(clock_t, double *, double *);
#endif
void RelaxIc(elem_struct *, river_struct *);
void SetCVodeParam(PihmData, void *, SUNLinearSolver *, N_Vector);
int SoilTex(double, double);
void SolveCVode(const RunParameters *, double, int *, void *,
                N_Vector);
void Spinup(PihmData, N_Vector, void *, SUNLinearSolver *);
void StartupScreen(void);
int StrTime(const char *);
double SubFlowElemToElem(const elem_struct *, const elem_struct *,
                         int);
double SubFlowElemToRiver(const elem_struct *, double,
                          const river_struct *, double, double);
double SubFlowRiverToRiver(const river_struct *, double,
                           const river_struct *, double);
void Summary(elem_struct *, river_struct *, N_Vector, double);
double SurfH(double);
void UpdPrintVar(PrintVariables *, int, int);
void UpdPrintVarT(PrintVariables *, int);
void VerticalFlow(elem_struct *, double);
double WiltingPoint(double, double, double, double);

/*
 * Fractured bedrock functions
 */
#if defined(_FBR_)
double FbrBoundFluxElem(int, int, const bc_struct *,
                        const wstate_struct *, const topo_struct *, const geol_struct *);
double FbrFlowElemToElem(const elem_struct *, const elem_struct *,
                         double, double);
double FbrInfil(const wstate_struct *, const soil_struct *,
                const geol_struct *, const topo_struct *);
double FbrRecharge(const wstate_struct *, const wflux_struct *,
                   const geol_struct *);
void FreeGeoltbl(GeologyEntry *);
void InitGeol(elem_struct *, const GeologyEntry *,
              const CalibrationParameters *);
void ReadBedrock(const char *, ElementAttribute *, MeshEntry *,
                 RunParameters *);
void ReadGeol(const char *, GeologyEntry *);
#endif

/*
 * Noah functions
 */
#if defined(_NOAH_)
void AdjSmProf(const soil_struct *, const pstate_struct *,
               const double *, double, wflux_struct *, wstate_struct *);
void AlCalc(pstate_struct *, double, int);
void CalcLatFlx(const pstate_struct *, wflux_struct *);
void CalcSlopeAspect(elem_struct *, const MeshEntry *);
void CalHum(pstate_struct *, estate_struct *);
#if defined(_CYCLES_)
void CanRes(const estate_struct *, pstate_struct *);
#else
void CanRes(const wstate_struct *, const estate_struct *,
            const eflux_struct *, pstate_struct *, const soil_struct *,
            const epconst_struct *);
#endif
double CSnow(double);
void DefSldpth(double *, int *, double *, double, const double *,
               int);
void DEvap(const wstate_struct *, wflux_struct *,
           const pstate_struct *, const lc_struct *, const soil_struct *);
#if defined(_CYCLES_)
void Evapo(const soil_struct *, const lc_struct *,
           const pstate_struct *, const estate_struct *es,
           const cstate_struct *, double, crop_struct[], wstate_struct *,
           wflux_struct *);
#else
void Evapo(const wstate_struct *, wflux_struct *,
           const pstate_struct *, const lc_struct *, const soil_struct *, double);
#endif
int FindLayer(const double *, int, double);
int FindWaterTable(const double *, int, double, double *);
double FrozRain(double, double);
double GwTransp(double, const double *, int, int);
void HRT(wstate_struct *, const estate_struct *,
         const pstate_struct *, const lc_struct *, const soil_struct *, double *,
         double, double, double, double, double *, double *, double *);
void IcePac(wstate_struct *, wflux_struct *, estate_struct *,
            eflux_struct *, pstate_struct *, const lc_struct *, const soil_struct *,
            int, double, double, double, double);
void InitLsm(elem_struct *, const char[], const RunParameters *,
             const NoahLandSurfaceEntry *, const CalibrationParameters *);
double Mod(double, double);
void Noah(elem_struct *, const LandCoverEntry *, const CalibrationParameters *,
          double);
void NoahHydrol(elem_struct *, double);
#if defined(_CYCLES_)
void NoPac(const soil_struct *, const lc_struct *,
           const cstate_struct *, double, double, crop_struct[], pstate_struct *,
           wstate_struct *, wflux_struct *, estate_struct *, eflux_struct *);
#else
void NoPac(wstate_struct *, wflux_struct *, estate_struct *,
           eflux_struct *, pstate_struct *, const lc_struct *, const soil_struct *,
           double, double);
#endif
void PcpDrp(wstate_struct *, wflux_struct *, const lc_struct *,
            double, double);
void Penman(wflux_struct *, const estate_struct *, eflux_struct *,
            pstate_struct *, double *, double, int, int);
void PenmanGlacial(wflux_struct *, const estate_struct *,
                   eflux_struct *, pstate_struct *, double *, double, int, int);
double Pslhs(double);
double Pslhu(double);
double Pslms(double);
double Pslmu(double);
double Psphs(double);
double Psphu(double);
double Pspms(double);
double Pspmu(double);
void ReadGlacierIce(const char[], double[]);
void ReadLsm(const char *, SiteInfo *, RunParameters *,
             NoahLandSurfaceEntry *);
void ReadRad(const char *, Forcing *);
void RootDist(const double *, int, int, double *);
void Rosr12(double *, const double *, const double *, double *,
            const double *, double *, int);
void SfcDifOff(pstate_struct *, const lc_struct *, double, double,
               int);
#if defined(_CYCLES_)
void SFlx(const cstate_struct *, double, soil_struct *, lc_struct *,
          crop_struct[], pstate_struct *, wstate_struct *, wflux_struct *,
          estate_struct *, eflux_struct *);
#else
void SFlx(wstate_struct *, wflux_struct *, estate_struct *,
          eflux_struct *, pstate_struct *, lc_struct *, epconst_struct *,
          soil_struct *, double);
#endif
void SFlxGlacial(wstate_struct *, wflux_struct *, estate_struct *,
                 eflux_struct *, pstate_struct *, lc_struct *, soil_struct *, double);
void ShFlx(wstate_struct *, estate_struct *, const pstate_struct *,
           const lc_struct *, const soil_struct *, double, double, double, double);
#if defined(_CYCLES_)
void SmFlx(const soil_struct *, const cstate_struct *, double, pstate_struct *,
           wstate_struct *, wflux_struct *);
#else
void SmFlx(wstate_struct *, wflux_struct *, pstate_struct *,
           const soil_struct *, double);
#endif
double SnFrac(double, double, double);
void SnkSrc(double *, double, double, double *,
            const soil_struct *, const double *, double, int, double);
#if defined(_CYCLES_)
void SnoPac(const soil_struct *, const lc_struct *,
            const cstate_struct *, int, double, double, double, double, crop_struct[],
            pstate_struct *, wstate_struct *, wflux_struct *, estate_struct *,
            eflux_struct *);
#else
void SnoPac(wstate_struct *, wflux_struct *, estate_struct *,
            eflux_struct *, pstate_struct *, const lc_struct *, const soil_struct *,
            int, double, double, double, double);
#endif
void SnowNew(const estate_struct *, double, pstate_struct *);
void SnowPack(double, double, double *, double *, double, double);
double Snowz0(double, double, double);
#if defined(_CYCLES_)
void SRT(const soil_struct *, const cstate_struct *, double,
         pstate_struct *, wstate_struct *, wflux_struct *, double *, double *,
         double *, double *, double *);
#else
void SRT(wstate_struct *, wflux_struct *, pstate_struct *,
         const soil_struct *, double *, double *, double *, double *, double *);
#endif
void SStep(wstate_struct *, wflux_struct *, pstate_struct *,
           const soil_struct *, double *, double *, double *, double *, double *,
           double);
void SunPos(const SiteInfo *, int, spa_data *);
double TBnd(double, double, const double *, double, int, int);
double TDfCnd(double, double, double, double, double);
double TmpAvg(double, double, double, const double *, int);
double TopoRadn(const topo_struct *, double, double, double, double);
void Transp(const wstate_struct *, wflux_struct *,
            const pstate_struct *, const lc_struct *, const soil_struct *);
void WDfCnd(double *, double *, double, double, const soil_struct *);
#endif

#if defined(_DAILY_)
void DailyVar(int, int, elem_struct *);
void InitDailyStruct(elem_struct *);
#endif

#if defined(_BGC_) || defined(_CYCLES_)
void SetAbsTol(double, double, N_Vector);
#endif

#if defined(_BGC_)
void BackgroundLitterfall(const epconst_struct *, epvar_struct *,
                          const cstate_struct *, cflux_struct *, nflux_struct *);
void CanopyCond(const epconst_struct *, epvar_struct *,
                const eflux_struct *, const pstate_struct *, const soil_struct *,
                const daily_struct *);
void CheckCarbonBalance(const cstate_struct *, double *);
void CheckNitrogenBalance(const nstate_struct *, double *);
void CSummary(const cflux_struct *, const cstate_struct *,
              summary_struct *);
void DailyAllocation(cflux_struct *, const cstate_struct *,
                     nflux_struct *, const nstate_struct *, const epconst_struct *,
                     epvar_struct *, ntemp_struct *);
void DailyBgc(PihmData, int);
void DailyCarbonStateUpdate(cflux_struct *, cstate_struct *, int,
                            int, int);
void DailyNitrogenStateUpdate(nflux_struct *, nstate_struct *,
                              solute_struct *, int, int, int);
void Decomp(double, const epconst_struct *, epvar_struct *,
            const cstate_struct *, cflux_struct *, const nstate_struct *,
            nflux_struct *, ntemp_struct *);
void EvergreenPhenology(const epconst_struct *, epvar_struct *,
                        const cstate_struct *);
void FirstDay(elem_struct *, river_struct *, const cninit_struct *);
void FRootLitFall(const epconst_struct *, double, cflux_struct *,
                  nflux_struct *);
void FreeEpctbl(epctbl_struct *);
double GetCO2(TimeSeriesData *, int);
double GetNdep(TimeSeriesData *, int);
void GrowthResp(const epconst_struct *, cflux_struct *);
void InitBgc(elem_struct *, const epctbl_struct *,
             const CalibrationParameters *);
void InitBgcVar(elem_struct *, river_struct *, N_Vector);
void LeafLitFall(const epconst_struct *, double, cflux_struct *,
                 nflux_struct *);
void LivewoodTurnover(const epconst_struct *, epvar_struct *,
                      const cstate_struct *, cflux_struct *, const nstate_struct *,
                      nflux_struct *);
void MaintResp(const epconst_struct *, epvar_struct *,
               const cstate_struct *, cflux_struct *, const nstate_struct *,
               const daily_struct *);
void MakeZeroFluxStruct(cflux_struct *, nflux_struct *);
void Mortality(const epconst_struct *, cstate_struct *,
               cflux_struct *, nstate_struct *, nflux_struct *);
#if defined(_LEACHING_)
void NLeaching(elem_struct *);
#elif defined(_LUMPED_)
void NLeachingLumped(elem_struct *, river_struct *);
#else
void NTransport(elem_struct *, river_struct *);
#endif
void OffsetLitterfall(const epconst_struct *, epvar_struct *,
                      const cstate_struct *, cflux_struct *, nflux_struct *);
void OnsetGrowth(const epconst_struct *, const epvar_struct *,
                 const cstate_struct *, cflux_struct *, const nstate_struct *,
                 nflux_struct *);
void Phenology(const epconst_struct *, epvar_struct *,
               const cstate_struct *, cflux_struct *, const nstate_struct *,
               nflux_struct *, const daily_struct *);
void Photosynthesis(psn_struct *);
void PrecisionControl(cstate_struct *cs, nstate_struct *ns);
void RadTrans(const cstate_struct *, eflux_struct *,
              pstate_struct *, const epconst_struct *, epvar_struct *,
              const daily_struct *);
void ReadAnnFile(TimeSeriesData *, const char *);
void ReadBgc(const char *, RunParameters *, co2control_struct *,
             ndepcontrol_struct *, cninit_struct *, char *, char *);
void ReadBgcIc(const char *, elem_struct *, river_struct *);
void ReadEpc(epctbl_struct *);
void ResetSpinupStat(elem_struct *);
void RestartInput(cstate_struct *, nstate_struct *,
                  epvar_struct *, const bgcic_struct *);
void RestartOutput(const cstate_struct *, const nstate_struct *,
                   const epvar_struct *, bgcic_struct *);
void SeasonDecidPhenology(const epconst_struct *, epvar_struct *,
                          const daily_struct *);
void SoilPsi(const soil_struct *, double, double *);
void TotalPhotosynthesis(const epconst_struct *, epvar_struct *,
                         const pstate_struct *, cflux_struct *, psn_struct *, psn_struct *,
                         const daily_struct *);
void WriteBgcIc(const char *, elem_struct *, river_struct *);
void ZeroSrcSnk(cstate_struct *, nstate_struct *, summary_struct *,
                solute_struct *);
#endif

#if defined(_CYCLES_)
void AddCrop(crop_struct *);
double Aeration(double);
double AirMolarDensity(double, double);
void ApplyFertilizer(const fixfert_struct *, cstate_struct *,
                     nstate_struct *, nflux_struct *);
double AvgSolConc(int, double, const double[],
                  const double[], const double[], double, const double[]);
double CNdestiny(double, double);
void CalcLatNFlux(double, int, const double[], const double[],
                  const double[], const double[], const double[], double, double[]);
void CalSnkSrc(const nflux_struct *, int, solute_struct *,
               solute_struct *);
void CalcRootFraction(const crop_struct *, const pstate_struct *,
                      double *);
double ColdDamage(double, double, double);
double CommRadIntcp(const crop_struct[]);
double CommTotRadIntcp(const crop_struct[]);
void ComputeColdDamage(const daily_struct *, crop_struct *,
                       wstate_struct *, cstate_struct *, nstate_struct *);
void ComputeFactorComposite(const soil_struct *,
                            const daily_struct *, pstate_struct *);
double ComputeHarvestIndex(double, double, double, double, double);
void ComputeResidueCover(const cstate_struct *, pstate_struct *);
void ComputeSoilCarbonBalanceMB(const double[], const soil_struct *,
                                pstate_struct *, wstate_struct *, cstate_struct *, cflux_struct *,
                                nstate_struct *, nflux_struct *);
double ComputeTextureFactor(double);
void ComputeTillageFactor(const tillage_struct *, const double[],
                          double, const soil_struct *, const pstate_struct *, double[]);
void CropGrowth(double, const daily_struct *, double *,
                crop_struct *);
void CropNitrogenConcentration(double, const crop_struct *,
                               double *, double *, double *, double *, double *, double *, double *);
void CropStage(int, crop_struct[]);
void CropNitrogenDemand(double, double, const crop_struct *,
                        double *, double *, double *, double *);
void CropNitrogenStress(double, double, double, crop_struct *);
void CropNitrogenUptake(int, double, double, const double[],
                        const double[], const double[], const double[], const double[],
                        const pstate_struct *, double[], double[], const double[],
                        crop_struct[], nstate_struct *, nflux_struct *);
void DailyCycles(int, PihmData);
void DailyOperations(int, const opertbl_struct *,
                     const daily_struct *, soil_struct *, mgmt_struct *, crop_struct[],
                     pstate_struct *, wstate_struct *, wflux_struct *, cstate_struct *,
                     cflux_struct *, nstate_struct *, nflux_struct *);
void Denitrification(const soil_struct *, const daily_struct *,
                     const pstate_struct *, const cflux_struct *, nstate_struct *,
                     nflux_struct *);
void DistributeRootDetritus(double, double, double,
                            double, const crop_struct *, const pstate_struct *, cstate_struct *,
                            nstate_struct *);
int Doy(int, int, int);
void Doy2Date(int, int, int *, int *);
void ExecuteTillage(const tillage_struct *, const pstate_struct *,
                    double *, soil_struct *, wstate_struct *, cstate_struct *,
                    nstate_struct *, nflux_struct *);
void FieldOperation(int, const opertbl_struct *,
                    const daily_struct *, soil_struct *, mgmt_struct *,
                    crop_struct[], pstate_struct *, wstate_struct *, wflux_struct *,
                    cstate_struct *, nstate_struct *, nflux_struct *);
int FinalHarvestDate(int, double, double, double);
int FindCrop(const char[], const epconst_struct[]);
double FindIrrigationVolume(int, double, const soil_struct *,
                            const daily_struct *daily, const pstate_struct *, const wflux_struct *);
void FirstDay(const SoilEntry *, elem_struct[],
              river_struct[]);
void FirstDOY(int, int *);
void ForageAndSeedHarvest(int, crop_struct *,
                          pstate_struct *, wstate_struct *, cstate_struct *, nstate_struct *,
                          nflux_struct *);
int ForcedClipping(int, const crop_struct[]);
double Fraction(double, double, double, double, double);
void GrainHarvest(int, crop_struct *, pstate_struct *,
                  wstate_struct *, cstate_struct *, nstate_struct *);
void GrowingCrop(int, const soil_struct *, const daily_struct *,
                 mgmt_struct *, crop_struct[], pstate_struct *, wstate_struct *,
                 cstate_struct *, nstate_struct *, nflux_struct *);
void HarvestCrop(int, crop_struct *, pstate_struct *,
                 wstate_struct *, cstate_struct *, nstate_struct *);
void InitCropSV(crop_struct *);
void InitCycles(const agtbl_struct *, const SoilEntry *,
                epconst_struct[], elem_struct[], river_struct[]);
void InitCyclesVar(elem_struct[], river_struct[], N_Vector);
int IsLeapYear(int);
int IsOperationToday(int, int, const void *, int, int, int *);
void KillCrop(crop_struct *);
double LinearEquilibriumConcentration(double, double, double, double,
                                      double);
void MakeZeroFluxStruct(wflux_struct *, cflux_struct *,
                        nflux_struct *);
double MaximumAbgdHumificationFactor(double);
double MaximumManuHumificationFactor(double);
double MaximumRhizHumificationFactor(double);
double MaximumRootHumificationFactor(double);
double Moisture(double);
double N2OFractionNitrification(double);
void Nitrification(const soil_struct *, const daily_struct *,
                   const pstate_struct *, nstate_struct *, nflux_struct *);
double NitrogenMineralization(double, double, double, double);
void NitrogenTransformation(const soil_struct *,
                            const daily_struct *, const crop_struct[], const cstate_struct *,
                            const cflux_struct *, pstate_struct *, nstate_struct *, nflux_struct *);
void NTransport(double, elem_struct[], river_struct[]);
int NumActiveCrop(const crop_struct[]);
void Phenology(const daily_struct *, crop_struct[]);
void PlantingCrop(const plant_struct *, crop_struct *);
void PotentialSoluteUptake(double, int, const double[],
                           const double[], const double[], const double[], const double[], double *,
                           double[]);
void Processes(int, const soil_struct *, const daily_struct *,
               const pstate_struct *, crop_struct[], cstate_struct *, nstate_struct *,
               nflux_struct *);
void RadiationInterception(crop_struct[]);
void ReadCrop(const char[], epconst_struct[]);
void ReadCyclesCtrl(const char[], agtbl_struct *, RunParameters *);
void ReadMultOper(const agtbl_struct *, const epconst_struct[],
                  opertbl_struct[]);
void ReadOperation(const char[], int, const epconst_struct[],
                   opertbl_struct[]);
void ReadSoilInit(const char[], SoilEntry *);
void ResidueEvaporation(double, double, double, const crop_struct[],
                        const pstate_struct *, const cstate_struct *, wstate_struct *,
                        wflux_struct *);
void ResidueWetting(const pstate_struct *, const cstate_struct *,
                    double, double, wstate_struct *, wflux_struct *);
void RestartInput(const cyclesic_struct *, pstate_struct *,
                  wstate_struct *, cstate_struct *, nstate_struct *);
double ShootBiomassPartitioning(double, double, double, int);
double SoilBufferPower(double, double, double);
void SoluteTransport(int, double, double, const double[],
                     const double[], const double[], const double[], double[]);
double TemperatureFunction(double);
double TemperatureFunctionGrowth(double, double, double, double);
double TemperatureLimitation(double, double, double);
double ThermalTime(double, double, double, double);
void TillageFactorSettling(int, const double[], double, double[]);
void UpdNProf(double, const soil_struct *, const wstate_struct *,
              const nstate_struct *, const nflux_struct *, const nprof_struct *,
              pstate_struct *, nstate_struct *);
void Volatilization(const soil_struct *, const daily_struct *,
                    const crop_struct[], const pstate_struct *, const cstate_struct *,
                    nstate_struct *, nflux_struct *);
double VolatilizationDepthFunction(double);
void WaterUptake(const soil_struct *, const estate_struct *,
                 const pstate_struct *, double, crop_struct[], wstate_struct *,
                 wflux_struct *);
#endif

#if defined(_RT_)
void InitChem(const char[], const CalibrationParameters *, Forcing *forc,
              ChemicalEntry[], KineticEntry[], ReactionNetwork *, chmictbl_struct *,
              elem_struct[]);
void Reaction(double, const ChemicalEntry[], const KineticEntry[],
              const ReactionNetwork *, elem_struct[]);
int _React(double, const ChemicalEntry[], const KineticEntry[],
           const ReactionNetwork *, double, chmstate_struct *);
void ReactControl(const ChemicalEntry[], const KineticEntry[],
                  const ReactionNetwork *, double, double, double, chmstate_struct *, double[]);
void Lookup(FILE *, const CalibrationParameters *, ChemicalEntry[],
            KineticEntry[], ReactionNetwork *);
void Speciation(const ChemicalEntry[], const ReactionNetwork *,
                river_struct[]);
int _Speciation(const ChemicalEntry[], const ReactionNetwork *, int,
                chmstate_struct *);
int SpeciesType(FILE *, const char[]);
void Unwrap(char *, const char *);
double EqvUnsatH(double, double, double, double, double);
double UnsatSatRatio(double, double, double);
void SortChem(char[][MAXSTRING], const int[], int, ChemicalEntry[]);
int FindChem(const char[], const ChemicalEntry[], int);
void ReadChem(const char[], const char[], ChemicalEntry[],
              KineticEntry[], ReactionNetwork *, Forcing *, RunParameters *);
void ReadPrep(const char[], const ChemicalEntry[],
              const ReactionNetwork *, Forcing *forc);
void ReadCini(const char[], const ChemicalEntry *, int,
              ElementAttribute *, chmictbl_struct *);
int ParseLocation(const char[], const char[], int);
void ApplyPrcpConc(const ReactionNetwork *, Forcing *,
                   elem_struct[], int);
void wrap(char *);
double GWStrg(double, double, double, double);
double UnsatWaterStrg(double, double, double, double, double);
double RivBedStrg(const matl_struct *, const river_wstate_struct *);
void Transport(const ChemicalEntry[], const ReactionNetwork *,
               elem_struct[], river_struct[]);
double AdvDiffDisp(double, double, double, double, double, double,
                   double, double, double);
void RTUpdate(const ReactionNetwork *, elem_struct[], river_struct[]);
void InitRTVar(const ChemicalEntry[], const ReactionNetwork *,
               elem_struct[], river_struct[], N_Vector);
int MatchWrappedKey(const char[], const char[]);
void ReadTempPoints(const char[], double, int *, int *);
void ReadDHParam(const char[], int, double *);
void ReadPrimary(const char[], int, ChemicalEntry[]);
void ReadSecondary(const char[], int, int, ChemicalEntry[],
                   ReactionNetwork *);
void ReadMinerals(const char[], int, int, ChemicalEntry[],
                  ReactionNetwork *);
void ReadAdsorption(const char[], int, int, ChemicalEntry[],
                    ReactionNetwork *);
void ReadCationEchg(const char[], double, ChemicalEntry[],
                    ReactionNetwork *);
void ReadMinKin(FILE *, int, double, int *, char[], ChemicalEntry[],
                KineticEntry *);
void InitChemS(const ChemicalEntry[], const ReactionNetwork *,
               const rtic_struct *, double, double, chmstate_struct *);
void ReadChemAtt(const char *, ElementAttribute *);
void ReadRtIc(const char *, elem_struct[]);
void UpdatePConc(elem_struct[], river_struct[]);
void WriteRtIc(const char *, const ChemicalEntry[],
               const ReactionNetwork *, elem_struct[]);
#endif

#endif
