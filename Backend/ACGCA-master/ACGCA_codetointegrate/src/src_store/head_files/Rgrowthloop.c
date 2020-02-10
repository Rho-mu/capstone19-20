#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
#include <C:/Program Files/R/local323/include/gsl/gsl_math.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_vector.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_blas.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_matrix.h>
*/ 

#include "head_files/misc_growth_funcs.h"
#include "head_files/misc_func.h"
#include "head_files/excessgrowing.h"
#include "head_files/rebuildstaticstate.h"
#include "head_files/putonallometry.h"
#include "head_files/shrinkingsize.h"
#include "head_files/growthloop.h"

/*
#ifdef DATA
#include <C:/Program Files/R/local323/include/gsl/gsl_randist.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_rng.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_vector.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_statistics.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_math.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_blas.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_matrix.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_linalg.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_sf.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_cdf.h>
#endif 
*/
//////////////////////////////////////////////////////////////////////////////////
// This code is to create a call to the growthloop from R
// I am hoping to avoid the structure problem that is causing problems.
// I need to create the structures needed by the growth loop but they need to be
// pointers so I need to send the variables to the loop indirectly.  The goal
// of the below function is to do this.  MKF 03/26/2013
//////////////////////////////////////////////////////////////////////////////////


void Rgrowthloop( double *p2, double *gp2, double *r0, int *t,
	double *h,
	double *hh,
	double *hC,
	double *hB,		
	double *hBH,		
	double *r,
	double *rB,
	double *rC,
	double *rBH,
	double *sw,
	double *vts,
	double *vt,
	double *vth,
	double *sa,
	double *la,
	double *ra,
	double *dr,
	double *xa,
	double *bl,
	double *br,
	double *bt,
	double *bts,
	double *bth,
	double *boh,
	double *bos,
	double *bo,
	double *bs,

	double *cs,
	double *clr,
	double *fl,
	double *fr,
	double *ft,
	double *fo,
	double *rfl,
	double *rfr,
	double *rfs, 
	
	double *egrow, 
	double *ex, 
	double *rtrans,
	double *light,
	double *nut,
	double *deltas,
	double *LAI, 
	int *status,
	//int *dim,
	int *lenvars,
	
	int *errorind,
        int *growth_st
){
	int i;
	int k;
	//int t = 1;
	//time = ceil(gp->T/gp->deltat)+1;
 	//double r[8000]={0},h[8000]={0}, rBH[8000]={0};
	//double r0;	
	
	//*t2 = t;	
	

	sparms p;
  	gparms gp;

	//for(i=0; i<(dim[0]); ++i){	
			// NOTE: all indicies -1 because C starts at 0 while R starts at 1
			// Define p(plant) parameters based on R array
			p.hmax = p2[0];
			p.phih = p2[1];
			p.eta = p2[2];
			p.swmax = p2[3]; //exp(-3.054);
			p.lamdas = p2[4];
			p.lamdah = p2[5];
			p.rhomax = p2[6]; //exp(13.2);
			p.rhomin = p2[7]; //exp(13.2);
		 	p.rhomin = p.rhomax;
			// p->rhomin=p->rhomax; // I don't know why this line is needed?
			p.f2 = p2[8]; //exp(8.456);//   //f2=gammax*NEWf2
			p.f1 = p2[9];
			p.gammac = p2[10];
			p.gammaw = p2[11];
			p.gammax = p2[12]; //inv_logit(-0.709);//
			p.cgl = p2[13]; //exp(0.3229);//
			p.cgr = p2[14]; //exp(0.192);//
			p.cgw = p2[15]; //exp(0.3361);// 
			p.deltal = p2[16];//inv_logit(-2.276);//  
			p.deltar = p2[17]; //inv_logit(-2.832);//   
			p.sl = p2[18]; //exp(0.8133);//
			p.sla = p2[19]; //exp(-4.119);//
			p.sr = p2[20]; //exp(0.2493);//
			p.so = p2[21]; //exp(0.6336); //
			p.rr = p2[22]; //exp(-8.103); //
			p.rhor = p2[23]; // new value: exp(-1.724); 
			p.rml = p2[24]; //exp(2.544);// 
			p.rms = p2[25]; //exp(0.5499); //
			p.rmr = p2[26]; //exp(3.252);//
			p.etaB = p2[27];
			p.K = p2[28];
			p.epsg = p2[29]; //exp(-3.304); //6.75;
			p.M = p2[30];
			p.alpha = p2[31];
			p.R0 = p2[32];
			p.R40 = p2[33];
			p.drinit = p2[34];
			p.drcrit = p2[35];

			/*
			printf("hmax=%g \n",p.hmax);
			printf("phih=%g \n",p.phih);
			printf("eta=%g \n",p.eta);
			printf("swmax=%g \n",p.swmax);
			printf("lamdas=%g \n",p.lamdas);
			printf("lamdah=%g \n",p.lamdah);
			printf("rhomax=%g \n",p.rhomax);
			printf("rhomin=%g \n",p.rhomin);
			printf("f2=%g \n",p.f2);	
			printf("f1=%g \n",p.f1);
			printf("gammac=%g \n",p.gammac);
			printf("gammaw=%g \n",p.gammaw);
			printf("gammax=%g \n",p.gammax);
			printf("cgl=%g \n",p.cgl);
			printf("cgr=%g \n",p.cgr);
			printf("cgw=%g \n",p.cgw);
			printf("deltal=%g \n",p.deltal);
			printf("deltar=%g \n",p.deltar);
			printf("sl=%g \n",p.sl);
			printf("sla=%g \n",p.sla);
			printf("sr=%g \n",p.sr);
			printf("so=%g \n",p.so);
			printf("rr=%g \n",p.rr);
			printf("rhor=%g \n",p.rhor);
			printf("rml=%g \n",p.rml);
			printf("rms=%g \n",p.rms);
			printf("rmr=%g \n",p.rmr);
			printf("etaB=%g \n",p.etaB);
			printf("K=%g \n",p.K);
			printf("epsg=%g \n",p.epsg);
			printf("M=%g \n",p.M);
			printf("alpha=%g \n",p.alpha);
			printf("R0=%g \n",p.R0);
			printf("R40=%g \n",p.R40);
			printf("drinit=%g \n",p.drinit);
			printf("drcrit=%g \n",p.drcrit);
			*/

			// define gp values based on input from R
			gp.deltat=gp2[0];
			gp.T=gp2[1]; 	
			gp.tolerance=gp2[2]; 
			gp.BH=gp2[3];
			gp.Io=gp2[4];  // make sure =9500*0.3 for real data 

				//R Code//
				//gparm[1] <- 0.0625 # gp.deltat
				//gparm[2] <- 10 # gp.T length of run in years
				//gparm[3] <- 0.00001 # gp.tolerance
				//gparm[4] <- 1.37 # gp.BH
				//#gparm[5] <- 9500*0.13 # gp.Io from MCMC part for Acer
				//gparm[5] <- 9500*0.3

			/*
			printf("Rgrowthloop \n");
			printf("gp out \n");
			printf("gp->deltat=%g,gp->tollerance=%g,gp->T=%g,gp.BH%g, gp.Io%g \n\n\n",gp.deltat,gp.tolerance,gp.T,gp.BH,gp.Io);
			*/

			//printf("Testvar %g, i %d, k %d \n", testvar[(i-1)+(k-1)*dim[1]],i,k);


			// This all comes from the main loop
			//r0=0.1;


			/*
			The code in the following section is to facilitate transfer of 
			parameter values to R.  It could be done more efficiently by
			updating the values in the above code but I decided not to modify 
			the original code (MKF 4/7/2013).
			*/
			/*
			I modified the code to make it work better.  p and gp are structures
			passed to the growthloop function.  However; the rest are pointers.  
			The pointers do not need to be dereferenced at this point since they
			already carry the addresses of what they point to.  This is the reason
			I also do not use & to send an address it is not necessary to send the
			address of something carrying an address.  At least that is how I think
			this is working (MKF 7/21/2014).
			*/

		 	growthloop(&p,&gp, r0, t,
				h,
				hh,
				hC,
				hB,		
				hBH,		
				r,
				rB,
				rC,
				rBH,
				sw,
				vts,
				vt,
				vth,
				sa,
				la,
				ra,
				dr,
				xa,
				bl,
				br,
				bt,
				bts,
				bth,
				boh,
				bos,
				bo,
				bs,

				cs,
				clr,
				fl,
				fr,
				ft,
				fo,
				rfl,
				rfr,
				rfs, 
	
				egrow, 
				ex, 
				rtrans,
				light,
				nut,
				deltas,
				LAI, 
				status,
				//i,
				//lenvars,
				errorind,
				growth_st
			);
	//} // End the for loop for acgca parms
} // End of Rgrowthloop






