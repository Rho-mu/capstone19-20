#ifndef SHRINKINGSIZE_H
#define SHRINKINGSIZE_H

#include "misc_growth_funcs.h"

extern void shrinkingsize(sparms *p, gparms *gp, tstates *st, int i, double *deltaw, double *pnet);


extern void shrinkingsizeA(sparms *p, tstates *st, gparms *gp, int i,
			   double *deltaw, bioms *bio, double *csst,
			   double *pnet);


extern void shrinkingsizeB(sparms *p, tstates *st, gparms *gp, int i,  
			   double *deltaw, bioms *bio, double *csst, 
			   double *pnet);

#endif
