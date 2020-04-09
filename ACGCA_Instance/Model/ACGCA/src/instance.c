#include "head_files/Rgrowthloop.h"
#include "head_files/misc_growth_funcs.h"
#include "head_files/growthloop.h"



typedef struct
{
    double BH;
    double deltat;
    double T;
    double tolerance;
} gparm;


void run_model(double *input, double *gp2, double *output,
    double *APARout,
    double *h,
    double* hh2,
    double* hC2,
    double* hB2,
    double* hBH2,
    double* r,
    double* rB2,
    double* rC2,
    double* rBH,
    double* sw2,
    double* vts2,
    double* vt2,
    double* vth2,
    double* sa2,
    double* la2,
    double* ra2,
    double* dr2,
    double* xa2,
    double* bl2,
    double* br2,
    double* bt2,
    double* bts2,
    double* bth2,
    double* boh2,
    double* bos2,
    double* bo2,
    double* bs2,
    double* cs2,
    double* clr2,
    double* fl2,
    double* fr2,
    double* ft2,
    double* fo2,
    double* rfl2,
    double* rfr2,
    double* rfs2,
    double* egrow2,
    double* ex2,
    double* rtrans2,
    double* light2,
    double* nut2,
    double* deltas2,
    double* LAI2,
    int* status2,
    // int* lenvars,
    int* errorind,
    int* growth_st
  )
{
  // this is test stuff



    printf("HELLO FROM THE INSTANCE.C CODE");
    // struct Output *str_ptr = &output;
    // modelInputs == p2

    //double *gp2; //do we need to create a struct for this

    //double *gp2 = {0.00625, 10, 0.00001,1.37};

    double I = 2060.0;
    // this is a questionable variable
    double *Io = &I;

    // there are two r0's
    double r1 = 0.05;
    double *r0 = &r1;
    int t0 = 1; // NEED TO CHECK THIS VARIABLE
    int *t = &t0;
    // need to check the variables here

    // number

    double Hc1[] = {-99.0, -99.0, -99.0, -99.0, -99.0, -99.0, -99.0, -99.0, -99.0, -99.0};
    double *Hc = Hc1;
    double LAIF1[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double *LAIF = LAIF1;
    // double k = 0.6;
    // double *kF = &k;
    // double HFmax = 40;
    // double inF = 3.4;
    // double *intF = &inF;
    // double slopF = -5.5;
    // double *slopeF = &slopF;

    sparms p;
    gparms gp;

    p.hmax = input[0];
    p.phih = input[1];
    p.eta = input[2];
    p.etaB = input[3];
    p.swmax = input[4]; //exp(-3.054);
    p.lamdas = input[5];
    p.lamdah = input[6];
    p.rhomax = input[7]; //exp(13.2);
    p.rhomin = input[8]; //exp(13.2);
    // p.rhomin = p.rhomax; // this could be changed if rhomin != rhomax.
    p.f2 = input[9]; //exp(8.456);//   //f2=gammax*NEWf2
    p.f1 = input[10];
    p.gammac = input[11];
    p.gammaw = input[12];
    p.gammax = input[13]; //inv_logit(-0.709);//
    p.cgl = input[14]; //exp(0.3229);//
    p.cgr = input[15]; //exp(0.192);//
    p.cgw = input[16]; //exp(0.3361);//
    p.deltal = input[17];//inv_logit(-2.276);//
    p.deltar = input[18]; //inv_logit(-2.832);//
    p.sl = input[19]; //exp(0.8133);//
    p.sla = input[20]; //exp(-4.119);//
    p.sr = input[21]; //exp(0.2493);//
    p.so = input[22]; //exp(0.6336); //
    p.rr = input[23]; //exp(-8.103); //
    p.rhor = input[24]; // new value: exp(-1.724);
    p.rml = input[25]; //exp(2.544);//
    p.rms = input[26]; //exp(0.5499); //
    p.rmr = input[27]; //exp(3.252);//
    p.drcrit = input[28];
    p.drinit = input[29];
    p.K = input[30];
    p.epsg = input[31]; //exp(-3.304); //6.75;

    p.M = input[32];
    p.alpha = input[33];
    p.R0 = input[34];
    p.R40 = input[35];


    gp.BH = gp2[0];
    gp.deltat=gp2[1];
    gp.T=gp2[2];
    gp.tolerance=gp2[3];
    //gparms gp2;
    //gp2.BH = 1.37;
    //gp2.deltat = 0.00625;
    //gp2.T = 10;
    //gp2.tolerance = 0.00001;
    // pointer to the input structure
    // create

    Forestparms ForParms;
  	ForParms.kF = 0.6;
  	ForParms.intF = 3.4;
  	ForParms.slopeF = -5.5;





    // call Rgrowthloop
      // is t that same as gp->T
    growthloop(&p,&gp, Io, r0, t,
  		Hc, LAIF, &ForParms,
      APARout,
  		h,
  		hh2,
  		hC2,
  		hB2,
  		hBH2,
  		r,
  		rB2,
  		rC2,
  		rBH,
  		sw2,
  		vts2,
  		vt2,
  		vth2,
  		sa2,
  		la2,
  		ra2,
  		dr2,
  		xa2,
  		bl2,
  		br2,
  		bt2,
  		bts2,
  		bth2,
  		boh2,
  		bos2,
  		bo2,
  		bs2,

  		cs2,
  		clr2,
  		fl2,
  		fr2,
  		ft2,
  		fo2,
  		rfl2,
  		rfr2,
  		rfs2,

  		egrow2,
  		ex2,
  		rtrans2,
  		light2,
  		nut2,
  		deltas2,
  		LAI2,
  		status2,
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







}
