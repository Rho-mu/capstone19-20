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


void run_model(double *input, double *gp2,
    double *APARout2,
    double *h2,
    double* hh2,
    double* hC2,
    double* hB2,
    double* hBH2,
    double* r2,
    double* rB2,
    double* rC2,
    double* rBH2,
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
    int* errorind2,
    int* growth_st2
  )
{

    double I = input[38];
    double *Io = &I;

    double r1 = input[37];
    double *r0 = &r1;
    int t0 = 10;
    int *t = &t0;


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
    gp.T=input[36];
    gp.tolerance=gp2[3];
    //gparms gp2;
    //gp2.BH = 1.37;
    //gp2.deltat = 0.00625;
    //gp2.T = 10;
    //gp2.tolerance = 0.00001;
    // pointer to the input structure

    Forestparms ForParms;
  	ForParms.kF = 0.6;
  	ForParms.intF = 3.4;
  	ForParms.slopeF = -5.5;


    // need to fix the year problem there
      // establish the secondary data structures
      // double pointers to pass into the growth loop function

    double APARout3[(int)(ceil(gp.T/gp.deltat)+1)];
    double h3[(int)(ceil(gp.T/gp.deltat)+1)];
    double hh3[(int)(ceil(gp.T/gp.deltat)+1)];
    double hC3[(int)(ceil(gp.T/gp.deltat)+1)];
    double hB3[(int)(ceil(gp.T/gp.deltat)+1)];
    double hBH3[(int)(ceil(gp.T/gp.deltat)+1)];
    double r3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rB3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rC3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rBH3[(int)(ceil(gp.T/gp.deltat)+1)];
    double sw3[(int)(ceil(gp.T/gp.deltat)+1)];
    double vts3[(int)(ceil(gp.T/gp.deltat)+1)];
    double vt3[(int)(ceil(gp.T/gp.deltat)+1)];
    double vth3[(int)(ceil(gp.T/gp.deltat)+1)];
    double sa3[(int)(ceil(gp.T/gp.deltat)+1)];
    double la3[(int)(ceil(gp.T/gp.deltat)+1)];
    double ra3[(int)(ceil(gp.T/gp.deltat)+1)];
    double dr3[(int)(ceil(gp.T/gp.deltat)+1)];
    double xa3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bl3[(int)(ceil(gp.T/gp.deltat)+1)];
    double br3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bt3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bts3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bth3[(int)(ceil(gp.T/gp.deltat)+1)];
    double boh3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bos3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bo3[(int)(ceil(gp.T/gp.deltat)+1)];
    double bs3[(int)(ceil(gp.T/gp.deltat)+1)];
    double cs3[(int)(ceil(gp.T/gp.deltat)+1)];
    double clr3[(int)(ceil(gp.T/gp.deltat)+1)];
    double fl3[(int)(ceil(gp.T/gp.deltat)+1)];
    double fr3[(int)(ceil(gp.T/gp.deltat)+1)];
    double ft3[(int)(ceil(gp.T/gp.deltat)+1)];
    double fo3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rfl3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rfr3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rfs3[(int)(ceil(gp.T/gp.deltat)+1)];
    double egrow3[(int)(ceil(gp.T/gp.deltat)+1)];
    double ex3[(int)(ceil(gp.T/gp.deltat)+1)];
    double rtrans3[(int)(ceil(gp.T/gp.deltat)+1)];
    double light3[(int)(ceil(gp.T/gp.deltat)+1)];
    double nut3[(int)(ceil(gp.T/gp.deltat)+1)];
    double deltas3[(int)(ceil(gp.T/gp.deltat)+1)];
    double LAI3[(int)(ceil(gp.T/gp.deltat)+1)];
    int status3[(int)(ceil(gp.T/gp.deltat)+1)];
    // int* lenvars,
    int errorind3[(int)(ceil(gp.T/gp.deltat)+1)];
    int growth_st3[(int)(ceil(gp.T/gp.deltat)+1)];


    // call Rgrowthloop
      // is t that same as gp->T
    growthloop(&p,&gp, Io, r0, t,
  		Hc, LAIF, &ForParms,
      APARout3,
  		h3,
  		hh3,
  		hC3,
  		hB3,
  		hBH3,
  		r3,
  		rB3,
  		rC3,
  		rBH3,
  		sw3,
  		vts3,
  		vt3,
  		vth3,
  		sa3,
  		la3,
  		ra3,
  		dr3,
  		xa3,
  		bl3,
  		br3,
  		bt3,
  		bts3,
  		bth3,
  		boh3,
  		bos3,
  		bo3,
  		bs3,

  		cs3,
  		clr3,
  		fl3,
  		fr3,
  		ft3,
  		fo3,
  		rfl3,
  		rfr3,
  		rfs3,

  		egrow3,
  		ex3,
  		rtrans3,
  		light3,
  		nut3,
  		deltas3,
  		LAI3,
  		status3,
  		//i,
  		//lenvars,
  		errorind3,
  		growth_st3
  		//tolout,
  		//errorout,
      //drout,
      //demandout,
      //odemandout,
      //odrout
  	);




    int outputIter = 0;
    for(int iter = 0; iter < (ceil(gp.T/gp.deltat) + 1); iter+=16)
    {
      APARout2[outputIter] = APARout3[iter];
      h2[outputIter] = h3[iter];
      hh2[outputIter] = hh3[iter];
      hC2[outputIter] = hC3[iter];
      hB2[outputIter] = hB3[iter];
      hBH2[outputIter] = hBH3[iter];
      r2[outputIter] = r3[iter];
      rB2[outputIter] = rB3[iter];
      rC2[outputIter] = rC3[iter];
      rBH2[outputIter] = rBH3[iter];
      sw2[outputIter] = sw3[iter];
      vts2[outputIter] = vts3[iter];
      vt2[outputIter] = vts3[iter];
      vth2[outputIter] = vth3[iter];
      sa2[outputIter] = sa3[iter];
      la2[outputIter] = la3[iter];
      ra2[outputIter] = ra3[iter];
      dr2[outputIter] = dr3[iter];
      xa2[outputIter] = xa3[iter];
      bl2[outputIter] = bl3[iter];
      br2[outputIter] = br3[iter];
      bt2[outputIter] = bt3[iter];
      bts2[outputIter] = bts3[iter];
      bth2[outputIter] = bth3[iter];
      boh2[outputIter] = boh3[iter];
      bos2[outputIter] = bos3[iter];
      bo2[outputIter] = bo3[iter];
      bs2[outputIter] = bs3[iter];
      cs2[outputIter] = cs3[iter];
      clr2[outputIter] = clr3[iter];
      fl2[outputIter] = fl3[iter];
      fr2[outputIter] = fr3[iter];
      ft2[outputIter] = ft3[iter];
      fo2[outputIter] = fo3[iter];
      rfl2[outputIter] = rfl3[iter];
      rfr2[outputIter] = rfr3[iter];
      rfs2[outputIter] = rfs3[iter];
      egrow2[outputIter] = egrow3[iter];
      ex2[outputIter] = ex3[iter];
      rtrans2[outputIter] = rtrans3[iter];
      light2[outputIter] = light3[iter];
      nut2[outputIter] = nut3[iter];
      deltas2[outputIter] = deltas3[iter];
      LAI2[outputIter] = LAI3[iter];
      status2[outputIter] = status3[iter];
      errorind2[outputIter] = errorind3[iter];
      growth_st2[outputIter] = growth_st3[iter];
      outputIter++;
    }
    outputIter = 0;



}
