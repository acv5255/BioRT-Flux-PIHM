#include "pihm.h"

void init_mesh(MeshElement *elem, const MeshEntry *meshtbl)
{
    int i;

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (i = 0; i < num_elements; i++)
    {
        int j;

        elem[i].ind = i + 1;

        for (j = 0; j < NUM_EDGE; j++)
        {
            elem[i].node_ids[j] = meshtbl->node[i][j];
            elem[i].nabr[j] = meshtbl->nabr[i][j];
            elem[i].nabr_river[j] = 0; /* initialize to 0 */
        }
    }
}
