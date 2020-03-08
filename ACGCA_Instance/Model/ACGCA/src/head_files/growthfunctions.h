/* #ifndef GROWTHFUNCTIONS_H */
/* #define GROWTHFUNCTIONS_H */
/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <math.h> */

/* #include "growthfunctions.h" */

/* typedef struct{ */
/*     /\* Parameters used in the tree growth model. Should probably treat as global */
/*      * since passed between different functions and used with the MCMC routine. */
/*      * That is, these parameters should be inputs to all of the growth model */
/*      * functions, but the functions do not modify the parameters.  */
/*      * These parameters are same across species                                *\/ */
/*     double hmax, phih, eta, etaB, swmax, lamdas, lamdah, rhomax, rhomin, drcrit, */
/*             f2, f1, gammac, gammaw, gammax, cgl, cgr, cgw, deltal, deltar, sl, */
/*             sla, sr, so, rr, rhor, rml, rms, rmr, drinit, K, epsg, M, alpha, */
/*       R0, R40; */
/*     /\* NOTE: f2 = gammax*NEWf2, where NEWf2 is actually the value reported for */
/*      * f2 in the tree growth manuscript (Ogle and Pacala 2009). *\/ */
/* } sparms;   */


/* /\*Tree specific vs. species specific will be handled outside of the growthloop  */
/*   function call.   *\/ */
/* typedef struct{ */
/*     double rinit, drinit, drcrit; */
/* } tparms; */

/* /\*Below is included in sparms for now.  *\/ */
/* typedef struct{ */
/*    double BH; */
/* } gparms; */

/* /\*Leaf area structures*\/ */
/* typedef struct{ */
/*   double tot, top,bot; */
/* } LAindex; */

/* typedef struct{ */
/*   double tot, top,bot; */
/* } Larea; */

/* typedef struct{ */
/*   double hB,hC,H,hBH; */
/* } height; */

/* typedef struct{ */
/*   double r0,rB,rC,rBH; */
/* } radius; */

/* typedef struct{ */
/*   double vt,vts,vth; */
/* } volume; */


/* /\* These are scalar.  New values will be printed to a file, and any values needed */
/*  * For MCMC will be returned as needed. *\/ */
/* typedef struct{ */
/* double h, hh, hC, hB, hBH, r, rB, rC, rBH, sw, vts, vt, vth, sa, la, ra, xa,  */
/*            bl, br, bt, bts, bth, boh, bos, bo, bs, cs, clr, fl, fr, ft, fo, */
/*            rfl, rfr, rfs, egrow, ex, rtrans, light, t, nut, */
/*   deltas, cstar,LAI; */
/*     int status, Jstatus, yr; */
   
/*     // Note: status/Jstatus = 1 if living, 0 if dead. */
/* } tstates; */

/* //Intermediate structure.  Needed in ?? functions. */
/* typedef struct{ */
/*   double bosmax,bosmid,bosmin,bosst,bohst,blst,brst,bosl,bosr,boso; */
/* } bioms; */

/* //This will just be fixed for now. */
/* typedef struct{ */
/*     double Io; */
/* } dvars; */


/* extern void initialize(sparms *p, tparms *tp, gparms *gp, tstates *st); */

/* extern void trunkradii(double r0, height *h, radius *r); */

/* extern void trunkvolume(radius *r, height *h, double sw, volume *v); */


/* extern void LAIcalc(LAindex *LAI, Larea *LA, double LAtot, double r0,  */
/* 		    double H, double rBH, sparms *p, gparms *gp, double Hc); */


/* extern void shrinkingsize(sparms *p, tstates *st, int i, double excess, double deltas,   */
/* 			  double deltaw, double deltat, double pnet); */

/* extern void excessgrowingoff(sparms *p, tstates *st, int i,double deltaw,  */
/* 		      double deltas, double *excess, double deltat); */

/* extern void excessgrowingon(sparms *p, gparms *gp,  tparms *tp, tstates *st, int i,  */
/* 		     double deltas, double *excess, double deltat, double tolerance,  */
/* 			    int growthflag, double r[], double h[]); */

/* extern void rebuildstaticstate(sparms *p, tstates *st, int i, double excess, double deltas, */
/* 			double deltaw, double nuoerb, double erb, double eoerb, */
/* 			       double elerb, double ererb, double deltat); */

/* extern void shrinkingsizeA(sparms *p, tstates *st, int i, double excess, double deltas,   */
/* 		    double deltaw, double deltat, bioms *biomass, double csst,  */
/* 			   double pnet); */


/* extern void shrinkingsizeB(sparms *p, tstates *st, int i, double excess, double deltas,   */
/* 		    double deltaw, double deltat, bioms *biomass, double csst,  */
/* 			   double pnet); */

/* extern void putonallometry(sparms *p, tstates *st, gparms *gp, tparms *tp, int i, double excess, double ea, */
/* 		    double eo, double el, double er, double nuoa, double deltaw,  */
/* 			   double deltas, double deltat, double tolerance,double r[],double h[]);  */

/* extern void testparms(sparms *p, tparms *tp, gparms *gp); */

/* #endif */
