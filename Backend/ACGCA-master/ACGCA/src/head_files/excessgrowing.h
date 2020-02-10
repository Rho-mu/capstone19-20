#ifndef EXCESSGROWING_H
#define EXCESSGROWING_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "growthfunctions.h"


//extern void trunkradii(double r0, height *h, radius *r);

//extern void trunkvolume(radius *r, height *h, double sw, volume *v);


extern void excessgrowingoff(sparms *p, gparms *gp, tstates *st, int i,double deltaw,
                             int *errorind2, int *growth_st);

extern void excessgrowingon(sparms *p, gparms *gp, tstates *st, int i,
                            int growthflag, double r[], int *errorind2,
                            int *growth_st);
                            //, double *tolout, double *errorout,
                            //double *drout, double *demandout,
                            //double *odemandout, double *odrout);

#endif
