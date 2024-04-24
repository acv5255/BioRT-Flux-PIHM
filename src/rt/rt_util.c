#include "pihm.h"

int FindChem(const char chemn[MAXSTRING], const ChemicalEntry chemtbl[],
             int nsps)
{
    int ind = -1;

    for (int i = 0; i < nsps; i++)
    {
        if (strcmp(chemn, chemtbl[i].ChemName) == 0)
        {
            ind = i;
            break;
        }
    }

    return ind;
}
