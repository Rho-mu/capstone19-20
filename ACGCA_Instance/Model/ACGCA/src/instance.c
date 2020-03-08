#include "Rgrowthloop.h"

typedef struct Input
{
    double data;
    double hmax; 
    double phih; 
    double eta; 
    double etaB;
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


    //Gparams
    double BH; 
    double deltat;
    double T; 
    double tolerance;
} Input;

typedef struct Output
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
    int* errorind;
    int* growth_st;
} Output;

void call_model(Input *input, Output *output) 
{
    double Io = 2060.0;
    double r0 = 0.05;
    double t = 1;
    double Hc[] = {-99, -99, -99, -99, -99, -99, -99, -99, -99, -99};
    double LAIF = 0;
}