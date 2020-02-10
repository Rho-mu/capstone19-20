#include "head_files/misc_growth_funcs.h"
#include "head_files/growthloop.h"

//////////////////////////////////////////////////////////////////////////////////
// This code is to create a call to the growthloop from R
// I am hoping to avoid the structure that is causing problems.
// I need to create the structures needed by the growth loop but they need to be
// pointers so I need to send the variables to the loop indirectly.  The goal
// of the below function is to do this.  MKF 03/26/2013
//////////////////////////////////////////////////////////////////////////////////
// changes added Hc, LAIf,
void Rgrowthloop( double *p2, double *gp2, double *Io, double *r0, int *t,
	double *Hc, double *LAIF, double *kF, double *intF, double *slopeF, 
	double *APARout,

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
  int *growth_st)
  //double *tolout,
  //double *errorout,
  //double *drout,
  //double *demandout,
  //double *odemandout,
  //double *odrout)
{

	///////////////////////////////////////////////////////////////////////////
	// Declare two structs and use them to store the simulation parameters
	// and the simulation control variables.
	///////////////////////////////////////////////////////////////////////////
	sparms p;
  	gparms gp;

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
	p.rhomin = p.rhomax; // this could be changed if rhomin != rhomax.
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

	// define gp values based on input from R
	gp.deltat=gp2[0]; // gparm[1] <- 0.0625 # gp.deltat
	gp.T=gp2[1]; // gparm[2] <- 10 # gp.T length of run in years
	gp.tolerance=gp2[2]; // gparm[3] <- 0.00001 # gp.tolerance
	gp.BH=gp2[3]; // gparm[4] <- 1.37 # gp.BH
	//gp.Io=gp2[4];  // annual par APAR

	// Define a structure of forest parameters.
	Forestparms ForParms;
	ForParms.kF = *kF;
	ForParms.intF = *intF;
	ForParms.slopeF = *slopeF;

	/*
	The code in the following section is to facilitate transfer of
	parameter values to R.  It could be done more efficiently by
	updating the values in the above code but I decided not to modify
	the original code (MKF 4/7/2013).

	I modified the code to make it work better.  p and gp are structures
	passed to the growthloop function.  However; the rest are pointers.
	The pointers do not need to be dereferenced at this point since they
	already carry the addresses of what they point to.  This is the reason
	I also do not use & to send an address it is not necessary to send the
	address of something carrying an address.  At least that is how I think
	this is working (MKF 7/21/2014).
	*/
  // Hc and LAIF were added on 3/16/2018 by MKF to allow gap dynamics
  // simulations.
	growthloop(&p,&gp, Io, r0, t,
		Hc, LAIF, &ForParms, APARout,
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
		//tolout,
		//errorout,
    //drout,
    //demandout,
    //odemandout,
    //odrout
	);
} // End of Rgrowthloop






