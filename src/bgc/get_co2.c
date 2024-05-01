#include "pihm.h"

double GetCO2(TimeSeriesData *co2_ts, int t)
{
    double co2;

    interpolate_forcing(co2_ts, t, 1, INTRPL);

    co2 = co2_ts->value[0];

    return co2;
}
