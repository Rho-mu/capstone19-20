#ifndef GROWTHLOOP_H
#define GROWTHLOOP_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "head_files/misc_growth_funcs.h"



extern void growthloop(sparms *p, gparms *gp, double *Io, double *r0, int *t,
  double *Hc, double *LAIF, Forestparms *ForParms, double *APARout,
	double h2[],
	double hh2[],
	double hC2[],
	double hB2[],		
	double hBH2[],		
	double r2[],
	double rB2[],
	double rC2[],
	double rBH2[],
	double sw2[],
	double vts2[],
	double vt2[],
	double vth2[],
	double sa2[],
	double la2[],
	double ra2[],
	double dr2[],
	double xa2[],
	double bl2[],
	double br2[],
	double bt2[],
	double bts2[],
	double bth2[],
	double boh2[],
	double bos2[],
	double bo2[],
	double bs2[],

	double cs2[],
	double clr2[],
	double fl2[],
	double fr2[],
	double ft2[],
	double fo2[],
	double rfl2[],
	double rfr2[],
	double rfs2[], 
	
	double egrow2[], 
	double ex2[], 
	double rtrans2[],
	double light2[],
	double nut2[],
	double deltas2[],
	double LAI2[], 
	int status2[],
	int errorind[],
	int growth_st[]
  //double *tolout,
  //double *errorout,
  //double *drout,
  //double *demandout,
  //double *odemandout,
  //double *odrout    
);

//extern void growthloop_MCMC(double *initr, double r[], double h[], 
//			    model_parms mod, int * t, double T, int flag, int rBHflag);

//extern void growthloop_light_MCMC(double *initr, double r[], double h[], model_parms mod[],
//				  int *t, double T, int flag, int rBHflag);
#endif
