#include "head_files/Rgrowthloop.h"
#include "head_files/misc_growth_funcs.h" 
#include "head_files/growthloop.h"

typedef struct 
{
    double hmax; 
    double phih; 
    double eta; 
    double swmax;
    double lamdas; 
    double lamdah;
    double rhomax;
    double rhomin;  
    double f2; 
    double f1; 
    double gammac;
    double gammaw;
    double gammax; 
    double cgl;  
    double cgr;
    double cgw;
    double deltal;
    double deltar;
    double sl;
    double sla;
    double sr;
    double so;
    double rr;
    double rhor;
    double rml;
    double rms;
    double rmr;
    double drcrit;
    double drinit;  
    double k;
    double epsg;
    double M;
    double alpha;
    double R0;
    double R40;

}Inputs;

typedef struct 
{
    double* APARout;
    double* h;
    double* hh2;
    double* hC2;
    double* hB2;
    double* hBH2;
    double* r;
    double* rB2;
    double* rC2;
    double* rBH;
    double* sw2;
    double* vts2;
    double* vt2;
    double* vth2;
    double* sa2;
    double* la2;
    double* ra2;
    double* dr2;
    double* xa2;
    double* bl2;
    double* br2;
    double* bt2;
    double* bts2;
    double* bth2;
    double* boh2;
    double* bos2;
    double* bo2;
    double* bs2;
    double* cs2;
    double* clr2;
    double* fl2;
    double* fr2;
    double* ft2;
    double* fo2;
    double* rfl2;
    double* rfr2;
    double* rfs2;
    double* egrow2;
    double* ex2;
    double* rtrans2;
    double* light2;
    double* nut2;
    double* deltas2;
    double* LAI2;
    int* status2;
    int* lenvars;
    int* errorind;
    int* growth_st;
}Outputs;

typedef struct 
{
    double BH;
    double deltat;
    double T;
    double tolerance;
}gparm;


void main(double *input, double *gp2, Outputs *output) 
{
    printf("%lf\n",input[0]);
    printf("%lf\n",gp2[0]);
    // struct Output *str_ptr = &output;
    // modelInputs == p2
    
    //double *gp2; //do we need to create a struct for this 
    
    //double *gp2 = {0.00625, 10, 0.00001,1.37};
    double I = 2060.0;
    double *Io = &I;
    double r1 = 0.05;
    double *r0 = &r1;
    int t0 = 1;
    int *t = &t0; 
    double Hc[] = {-99, -99, -99, -99, -99, -99, -99, -99, -99, -99};
    double LAIF[] = {0,0,0,0,0,0,0,0,0,0};
    double k = 0.6;
    double *kF = &k;
    double HFmax = 40;
    double inF = 3.4;
    double *intF = &inF;
    double slopF = -5.5;
    double *slopeF = &slopF;

    //gparms gp2;
    //gp2.BH = 1.37;
    //gp2.deltat = 0.00625;
    //gp2.T = 10;
    //gp2.tolerance = 0.00001;
    // pointer to the input structure
    // create
    double* APARout = output->APARout;
    double* h = output->h;
    double* hh = output->hh2;
    double* hC = output->hC2;
    double* hB = output->hB2;
    double* hBH = output->hBH2;
    double* r = output->r;
    double* rB = output->rB2;
    double* rC = output->rC2;
    double* rBH = output->rBH;
    double* sw = output->sw2;
    double* vts = output->vts2;
    double* vt = output->vt2;
    double* vth = output->vth2;
    double* sa = output->sa2;
    double* la = output->la2;
    double* ra = output->ra2;
    double* dr = output->dr2;
    double* xa = output->xa2;
    double* bl = output->bl2;
    double* br = output->br2;
    double* bt = output->bt2;
    double* bts = output->bts2;
    double* bth = output->bth2;
    double* boh = output->boh2;
    double* bos = output->bos2;
    double* bo = output->bo2;
    double* bs = output->bs2;

    double* cs = output->cs2;
    double* clr = output->clr2;
    double* fl = output->fl2;
    double* fr = output->fr2;
    double* ft = output->ft2;
    double* fo = output->fo2;
    double* rfl = output->rfl2;
    double* rfr = output->rfr2;
    double* rfs = output->rfs2;

    double* egrow = output->egrow2;
    double* ex = output->ex2;
    double* rtrans = output->rtrans2;
    double* light = output->light2;
    double* nut = output->nut2;
    double* deltas = output->deltas2;
    double* LAI = output->LAI2;
    int* status = output->status2;
    int* lenvars = output->lenvars;
    int* errorind = output->errorind;
    int* growth_st = output->growth_st;

    // call Rgrowthloop
    Rgrowthloop(
        input, 
        gp2, 
        Io, 
        r0, 
        t, 
        Hc,
        LAIF,
        kF,
        intF,
        slopeF,
        APARout,

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
		lenvars,
		errorind,
		growth_st
    );

}