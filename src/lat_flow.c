#include "pihm.h"

void lateral_flow(MeshElement *elem, const river_struct *river, int surf_mode)
{
    double *dhbydx;
    double *dhbydy;

    dhbydx = (double *)malloc(num_elements * sizeof(double));
    dhbydy = (double *)malloc(num_elements * sizeof(double));

    friction_slope(elem, river, surf_mode, dhbydx, dhbydy);

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (int i = 0; i < num_elements; i++)
    {
        double avg_sf;
        MeshElement *nabr;

        for (int j = 0; j < NUM_EDGE; j++)
        {
            if (elem[i].nabr[j] == 0) /* Boundary condition flux */
            {
                bound_flux_elem(elem[i].attrib.bc_type[j], j, &elem[i].bc,
                                &elem[i].ws, &elem[i].topo, &elem[i].soil, &elem[i].wf);
            }
            else if (elem[i].nabr_river[j] == 0)
            {
                nabr = &elem[elem[i].nabr[j] - 1];

                /* Subsurface flow between triangular elements */
                elem[i].wf.subsurf[j] = SubFlowElemToElem(&elem[i], nabr, j);

                /* Surface flux between triangular elements */
                avg_sf = 0.5 *
                         (sqrt(dhbydx[i] * dhbydx[i] + dhbydy[i] * dhbydy[i]) +
                          sqrt(dhbydx[nabr->ind - 1] * dhbydx[nabr->ind - 1] +
                               dhbydy[nabr->ind - 1] * dhbydy[nabr->ind - 1]));
                elem[i].wf.ovlflow[j] =
                    overland_flow_to_elem(&elem[i], nabr, j, avg_sf, surf_mode);
            }
            else
            {
                /* Do nothing. River-element interactions are calculated
                 * in river_flow.c */
            }
        } /* End of neighbor loop */
    }     /* End of element loop */

    free(dhbydx);
    free(dhbydy);

#if defined(_FBR_)
    /*
     * Lateral fractured bedrock flow
     */
#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (i = 0; i < num_elements; i++)
    {
        int j;
        elem_struct *nabr;

        for (j = 0; j < NUM_EDGE; j++)
        {
            if (elem[i].nabr[j] == 0)
            {
                elem[i].wf.fbrflow[j] =
                    FbrBoundFluxElem(elem[i].attrib.fbrbc_type[j], j,
                                     &elem[i].fbr_bc, &elem[i].ws, &elem[i].topo, &elem[i].geol);
            }
            else
            {
                nabr = &elem[elem[i].nabr[j] - 1];

                /* Groundwater flow modeled by Darcy's Law */
                elem[i].wf.fbrflow[j] = FbrFlowElemToElem(&elem[i], nabr,
                                                          elem[i].topo.nabrdist[j], elem[i].topo.edge[j]);
            }
        }
    }
#endif
}

void friction_slope(const MeshElement *elem, const river_struct *river,
                    int surf_mode, double *dhbydx, double *dhbydy)
{
#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (int i = 0; i < num_elements; i++)
    {
        double surfh[NUM_EDGE];
        double x[NUM_EDGE];
        double y[NUM_EDGE];
        const MeshElement *nabr;
        const river_struct *rivnabr;

        if (surf_mode == DIFF_WAVE)
        {
            for (int j = 0; j < NUM_EDGE; j++)
            {
                if (elem[i].nabr[j] == 0)
                {
                    surfh[j] = elem[i].topo.zmax + elem[i].ws.surfh;
                    x[j] = elem[i].topo.nabr_x[j];
                    y[j] = elem[i].topo.nabr_y[j];
                }
                else if (elem[i].nabr_river[j] == 0)
                {
                    nabr = &elem[elem[i].nabr[j] - 1];
                    surfh[j] = nabr->topo.zmax + nabr->ws.surfh;
                    x[j] = elem[i].topo.nabr_x[j];
                    y[j] = elem[i].topo.nabr_y[j];
                }
                else
                {
                    rivnabr = &river[elem[i].nabr_river[j] - 1];

                    surfh[j] = (rivnabr->ws.stage > rivnabr->shp.depth) ? rivnabr->topo.zbed + rivnabr->ws.stage : rivnabr->topo.zmax;
                    x[j] = river[elem[i].nabr_river[j] - 1].topo.x;
                    y[j] = river[elem[i].nabr_river[j] - 1].topo.y;
                }
            }

            dhbydx[i] = dh_by_dl(y, x, surfh);
            dhbydy[i] = dh_by_dl(x, y, surfh);
        }
    }
}

double average_h_surf(double diff, double hsurf, double hnabr)
{
    double avg_h;

    if (diff > 0.0)
    {
        if (hsurf > DEPRSTG)
        {
            avg_h = 1.0 * (hsurf - DEPRSTG);
        }
        else
        {
            avg_h = 0.0;
        }
    }
    else
    {
        if (hnabr > DEPRSTG)
        {
            avg_h = 1.0 * (hnabr - DEPRSTG);
        }
        else
        {
            avg_h = 0.0;
        }
    }

    return avg_h;
}

double average_h(double diff, double hsub, double hnabr)
{
    double avg_h = 0.0;

    if (diff > 0.0)
    {
        if (hsub > 0.0)
        {
            avg_h = hsub;
        }
    }
    else
    {
        if (hnabr > 0.0)
        {
            avg_h = hnabr;
        }
    }

    return avg_h;
}

double dh_by_dl(const double *l1, const double *l2, const double *surfh)
{
    return -1.0 *
           (l1[2] * (surfh[1] - surfh[0]) + l1[1] * (surfh[0] - surfh[2]) +
            l1[0] * (surfh[2] - surfh[1])) /
           (l2[2] * (l1[1] - l1[0]) + l2[1] * (l1[0] - l1[2]) +
            l2[0] * (l1[2] - l1[1]));
}

double effective_kh(const SoilData *soil, double gw)
{
    double k1, k2;
    double d1, d2;

    gw = (gw > 0.0) ? gw : 0.0;

    if (gw > soil->depth - soil->dmac)
    {
        k1 = soil->kmach * soil->areafv + soil->ksath * (1.0 - soil->areafv);
        k2 = soil->ksath;

        if (gw > soil->depth)
        {
            d1 = soil->dmac;
            d2 = soil->depth - soil->dmac;
        }
        else
        {
            d1 = gw - (soil->depth - soil->dmac);
            d2 = soil->depth - soil->dmac;
        }

        return (k1 * d1 + k2 * d2) / (d1 + d2);
    }
    else
    {
        return soil->ksath;
    }
}

double overland_flow(double avg_h, double grad_h, double avg_sf, double crossa,
                     double avg_rough)
{
    return crossa * pow(avg_h, 0.6666667) * grad_h / (sqrt(avg_sf) * avg_rough);
}

double SubFlowElemToElem(const MeshElement *elem, const MeshElement *nabr,
                         int j)

{
    double diff_h;
    double avg_h;
    double grad_h;
    double effk, effk_nabr;
    double avg_ksat;

    /*
     * Subsurface lateral flux calculation between triangular
     * elements
     */
    diff_h = (elem->ws.gw + elem->topo.zmin) - (nabr->ws.gw + nabr->topo.zmin);
    avg_h = average_h(diff_h, elem->ws.gw, nabr->ws.gw);
    grad_h = diff_h / elem->topo.nabrdist[j];

    /* Take into account macropore effect */
    effk = effective_kh(&elem->soil, elem->ws.gw);
    effk_nabr = effective_kh(&nabr->soil, nabr->ws.gw);
    avg_ksat = 0.5 * (effk + effk_nabr);

    /* Groundwater flow modeled by Darcy's Law */
    return avg_ksat * grad_h * avg_h * elem->topo.edge[j];
}

double overland_flow_to_elem(const MeshElement *elem, const MeshElement *nabr,
                             int j, double avg_sf, int surf_mode)
{
    double diff_h;
    double avg_h;
    double grad_h;
    double avg_rough;
    double crossa;

    diff_h = (surf_mode == KINEMATIC) ? elem->topo.zmax - nabr->topo.zmax : (elem->ws.surfh + elem->topo.zmax) - (nabr->ws.surfh + nabr->topo.zmax);
    avg_h = average_h_surf(diff_h, elem->ws.surfh, nabr->ws.surfh);
    grad_h = diff_h / elem->topo.nabrdist[j];
    if (surf_mode == KINEMATIC)
    {
        avg_sf = (grad_h > 0.0) ? grad_h : GRADMIN;
    }
    else
    {
        avg_sf = (avg_sf > GRADMIN) ? avg_sf : GRADMIN;
    }
    /* Weighting needed */
    avg_rough = 0.5 * (elem->lc.rough + nabr->lc.rough);
    crossa = avg_h * elem->topo.edge[j];

    return overland_flow(avg_h, grad_h, avg_sf, crossa, avg_rough);
}

void bound_flux_elem(int bc_type, int j, const bc_struct *bc,
                     const wstate_struct *ws, const Topology *topo, const SoilData *soil,
                     wflux_struct *wf)
{
    double diff_h;
    double avg_h;
    double effk;
    double avg_ksat;
    double grad_h;

    /* No flow (natural) boundary condition is default */
    if (bc_type == NO_FLOW)
    {
        wf->ovlflow[j] = 0.0;
        wf->subsurf[j] = 0.0;
    }
    /* Note: ideally different boundary conditions need to be
     * incorporated for surf and subsurf respectively */
    else if (bc_type > 0)
    {
        /* Note: the formulation assumes only Dirichlet TS right now */
        /* note the assumption here is no flow for surface */
        wf->ovlflow[j] = 0.0;

        diff_h = ws->gw + topo->zmin - bc->head[j];
        avg_h = average_h(diff_h, ws->gw, bc->head[j] - topo->zmin);
        /* Minimum distance from circumcenter to the edge of the triangle
         * on which boundary condition is defined */
        effk = effective_kh(soil, ws->gw);
        avg_ksat = effk;
        grad_h = diff_h / topo->nabrdist[j];
        wf->subsurf[j] = avg_ksat * grad_h * avg_h * topo->edge[j];
    }
    else
    {
        /* Neumann bc (note: md->ele[i].bc[j] value has to be
         * = 2+(index of Neumann boundary ts) */
        wf->ovlflow[j] = 0.0;
        /* Negative sign is added so the positive numbers in forcing time series
         * represents source */
        wf->subsurf[j] = -bc->flux[j];
    }
}

#if defined(_FBR_)
double FbrFlowElemToElem(const elem_struct *elem, const elem_struct *nabr,
                         double dist, double edge)
{
    double diff_h;
    double avg_h;
    double grad_h;
    double avg_ksat;

    diff_h = (elem->ws.fbr_gw + elem->topo.zbed) -
             (nabr->ws.fbr_gw + nabr->topo.zbed);
    avg_h = average_h(diff_h, elem->ws.fbr_gw, nabr->ws.fbr_gw);
    grad_h = diff_h / dist;

    avg_ksat = 0.5 * (elem->geol.ksath + nabr->geol.ksath);

    return avg_ksat * grad_h * avg_h * edge;
}

double FbrBoundFluxElem(int bc_type, int j, const bc_struct *bc,
                        const wstate_struct *ws, const Topology *topo, const geol_struct *geol)
{
    double diff_h;
    double avg_h;
    double effk;
    double grad_h;
    double flux;

    /* No flow (natural) boundary condition is default */
    if (bc_type == NO_FLOW)
    {
        flux = 0.0;
    }
    else if (bc_type > 0)
    {
        /* Dirichlet boundary conditions */
        diff_h = ws->fbr_gw + topo->zbed - bc->head[j];
        avg_h = average_h(diff_h, ws->fbr_gw, bc->head[j] - topo->zbed);
        /* Minimum distance from circumcenter to the edge of the triangle
         * on which boundary condition is defined */
        effk = geol->ksath;
        grad_h = diff_h / topo->nabrdist[j];
        flux = effk * grad_h * avg_h * topo->edge[j];
    }
    else
    {
        /* Neumann boundary conditions */
        flux = -bc->flux[j];
    }

    return flux;
}
#endif
