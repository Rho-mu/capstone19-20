///
/// \file misc_growth_funcs.c
/// \brief Contains functions initialize(), trunkradii(), trunkvolume(), LAIcalc(),
/// acruparms() and pitaparms().
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 04-21-2011
///
///  Updated numerical checks.
///

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "head_files/misc_growth_funcs.h"


// Only define M_PI if it is not defined already
// Added by MKF for compilers that don't define this
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

// Would use the following syntax to call initialize inside another function
// initialize(&sparms, &tparms, &gparms, &tstates);

/// Initialize function for initializing tree states.  sparms are specificed in
/// main call.  So this function initializes the state variables
///
/// \param p            Species parameters (sparms)
/// \param gp           gparms
/// \param tp           tree specific parameters (tparms)
/// \param st           tree state parameters (tstates)
///
/// Returns update st (state variables).  Calls on functions trunkradii() and
/// trunkvolume().
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-11-2010
///
void initialize(sparms *p, gparms *gp, tstates *st, double *r0){

  height hin;
  radius rin;
  volume vin;
    vin.vt = 0; // initialize values to stop compilation error
    vin.vts = 0;
    vin.vth = 0;

  // Initial radius (rinit), radial increment (drinit), and excess labile carbon
  if (*r0 > 0){
    st->r=*r0;
  }
  else {
    //printf("error in initialize, line 48 \n");
    getchar();
  }

  st->status=1;  // Tree starts out living
  //dr=p->drinit;
  //*excess=0.001;
  // initial height, function of initial radius
  if (p->hmax > 0){  // should never happen
    st->h=p->hmax*(1-exp(-p->phih*st->r/p->hmax));
  }
  else {
    //printf("hmax is 0 in initialize \n");
    st->status=0;   // tree dies
  }

  st->hh=p->eta*st->h;    /// 0<eta<1

  if(st->r < p->swmax){
    st->sw = st->r;
  }
  else{
    st->sw = p->swmax;
  }

  if (st->h <= 0){
    st->h = 1e-300;
    st->status=0;
    //printf("error in initialize, line 75 \n");
    //getchar();
  }

  // Trunk volume calculations based on neiloid, paraboloid, cone taper
  // trunkradii returns (or computes) trunk radii at different positions
  // along the trunk and updates r, rB, rC, rBH in tree states (st)
  // TODO: get rid of these
  hin.hB=p->etaB*st->h;   // 0<etaB<1
  hin.hC=st->hh;
  hin.H=st->h;
  hin.hBH=gp->BH;

  trunkradii(st->r, &hin, &rin, st);

  trunkvolume(&rin, &hin, st->sw, &vin, st);

  st->vts=vin.vts;
  st->vt=vin.vt;
  st->vth=vin.vth;

  //printf("r=%g, rB=%g, rC=%g, rBH=%g \n", st->r, st->rB, st->rC, st->rBH);
  // trunkvolume needs the updated radii from trunkradii and returns
  // volume of different trunk compartments vt, vth, vts in st

  //printf("vt=%g, vth=%g, vts=%g \n", st->vt, st->vth, st->vts);
  // compute other state variables
  st->sa=M_PI*st->sw*(2*st->r-st->sw);
  st->la=p->f2*st->sa;
  st->ra=p->f1*st->la;

  if (p->sla > 0){
    st->bl=st->la/p->sla;
  }
  else {
    //printf("problem in initialize 2");
    st->status=0; // tree dies
  }
  st->br=p->rr*p->rhor*st->ra/2;
  st->bt=(p->rhomin+p->rhomax)*st->vt/2;
  st->bts=(p->rhomin+p->rhomax)*st->vts/2;
  st->bth=st->bt-st->bts;
  st->bos=p->lamdas*st->bts;
  st->boh=p->lamdah*st->bth;
  st->bo=st->bos+st->boh;
  st->bs=st->bos+st->bts;

  /* Below, if wood density is very close to upper limit (given by deltaw=0),
   * set carbon storage to zero to avoid rounding and computational errors. */
  // TODO: neet an error check that p->gammaw > 0
  if ((p->gammaw > 0) && (st->bts > 0)){
    if ((p->rhomin+p->rhomax)/2 >
	((1-p->gammax)/p->gammaw)*exp(10)/(1+exp(10))){
      st->cs=0;
    }
    else {
      st->cs=p->gammac*st->bs*((1-p->gammax)*(st->vts/st->bts)-
  		       p->gammaw);
    }
  }
  else {
    // printf("problem in initialize 1 \n");
    st->cs=0;
    // printf("st->r=%g, st->h=%g, r0=%g \n",st->r,st->h, *r0);
    st->status=0;  //tree dies
  }

  st->clr=p->deltal*st->bl+p->deltar*st->br;
  //st->status=1; // living = 1; dead = 0;

  // Other state variables not yet defined; will be defined after initialize
  st->ex=0;
  st->fl=0;
  st->fo=0;
  st->fr=0;
  st->ft=0;
  //  st->light=0;
  st->nut=0;
  st->rfl=0;
  st->rfr=0;
  st->rfs=0;
  st->rtrans=0;
  //st->t=0;

  // Not sure what is different about Jstatus and status.
  //st->Jstatus=st->status;
  st->rBH=st->r;

} // end initialize

/// Calculates radii of the trunk
///
/// \param r0          initial radius
/// \param h[in]           height structure
/// \param r[out]           radius structure
///
/// Inputs are various heights as described in the matlab comments below.
/// Output are various radii described below.
///
/// This function is called by initialize(), excessgrowingon() and
/// putonallometry(), since it is used to recalculate radii for growing
/// trees.  If the tree is not growing, it is not needed.
///
/// Below are the original matlab comments:
///
/// Computes trunk radii (r) at the transition from neiloid to paraboloid
/// (r.rB), from paraboloid to cone (r.rC) and at breast height (BH); also
/// returns radius at base (r.r0). The inputs are trunk radius at the base
/// (r0) and heights (h) at the transition from neiloid to paraboloid (h.hB),
/// at the transition from paraboloid to cone (h.hC), total tree height
/// (h.H), and breast height (h.BH).
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \todo remove height and radius structures and just pass overall
///       parameter structure.
///
/// \date 04-21-2011
///
/// Updated the error checks.
///

void trunkradii(double r0, height *h, radius *r, tstates *st){

  //NOTE: only need p.etaB, so should simplify later
  // Also, h.BH (hBH) always equals 1.37 m
  //st->hB=p->etaB*st->h;
  //st->hC=st->hh;  //which =st->h*p->eta
  //st->hBH=gp->BH;


  // Initial check that H is greater than hB, hBH, and hC
  if ((h->H > 0) && (h->H > h->hB) && (h->H > h->hBH) &&
      (h->H > h->hC) && (h->hB < h->hC) && (r0>0) &&
      (isnan(r0)==0) && (isinf(r0)==0)){

    r->rB = r0*sqrt(pow(((h->H-h->hB)/h->H),3));
    r->rC = r->rB*sqrt((h->H-h->hC)/(h->H-h->hB));

    //printf("in trunkradii: st.r=%g, st.rB=%g, st.rC=%g \n", r->r0, r->rB, r->rC);
    //printf("in trunkradii: hB=%g, st.hC=%g, st.h=%g, st.hBH=%g \n", h->hB, h->hC, h->H,h->hBH);
    // Below calculates radius at breast height.
    if(h->hBH < h->hB){
      //printf("here 1 \n");
      r->rBH = r0*sqrt(pow(((h->H-h->hBH)/h->H),3));
    }
    else if((h->hB < h->hBH) && (h->hBH < h->hC)){
      //printf("here 2 \n");
      r->rBH = r->rB*sqrt((h->H-h->hBH)/(h->H-h->hB));
    }
    else if((h->hC < h->hBH) && (h->hBH < h->H)){  // this also checks that H>hC
      //printf("here 3 \n");
      r->rBH = r->rC*(h->H-h->hBH)/(h->H-h->hC);
    }
    else{
      //printf("here 4 \n");
      r->rBH = 0;
    }

    r->r0=r0;  // don't need this
  }
  else if ((r0 > 0) && (h->H > 0)){
    // printf("problem in trunkradii, line 237 \n");
    r->r0=r0;
    r->rB = r0;
    r->rC = r0;
    r->rBH = r0;
     st->status=0;
  }
  else {
    // printf("problem in trunkradii, line 241 \n");
    r->r0=1e-300;
    r->rB = 1e-300;
    r->rC = 1e-300;
    r->rBH = 1e-300;
    h->H=1e-300;
     st->status=0;
  }

} // end trunkradii()

/// Computes total trunk volume (v.vt), volume of trunk heartwood (v.vth),
/// and volume of trunk sapwood (v.vts). The inputs are trunk radius (r) and
/// heights (h) at the base of the tree (r.r0), at the transition from
/// neiloid to paraboloid (r.rB, h.hB), at the transition from paraboloid to
/// cone (r.rC, h.hC), total tree height (h.H), and sapwood width (SW).
///
/// \param r           radius structure
/// \param h           height structure
/// \param sw          sapwood width
/// \param v           volume structure
///
/// Returns volume structure v
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-11-2010
///

void trunkvolume(radius *r, height *h, double sw, volume *v, tstates *st){

  // intermediate calculations/quantities local to this function:
  double neiloidV=0, parabloidV=0, coneV=0;

  /* compute total trunk volume (vt). First, compute the volume of each of the
   * trunk segments:   */
   //st->hB=p->etaB*st->h;
  //st->hC=st->hh;

  // Compute total trunk volume (vt). First, compute the volume of each of the
  // trunk segments.  Check that hB<hC<H.  Uses current r->r0,r->rB and r->rC
  if ((h->H > 0) && (h->H > h->hC) && (h->hB < h->hC) && (st->status!=0)){
    neiloidV = (M_PI/4)*(pow(r->r0,2))*(pow(h->H,4) -
					pow((h->H-h->hB),4))/(pow(h->H,3));

    parabloidV = (M_PI/2)*(pow(r->rB,2))*(pow(h->hB,2) -
					  pow(h->hC,2) + 2*h->H*(h->hC-h->hB))/(h->H-h->hB);

    coneV = (M_PI/3)*(pow(r->rC,2))*(h->H-h->hC);

    // Compute total trunk volume.
    if ((neiloidV>=0) && (parabloidV>=0) && (coneV>=0)){
      v->vt = neiloidV + parabloidV + coneV;
    }
    else {
      //printf("problems in trunkvolume 1a \n");
      //getchar();
      st->status=0;  // tree dies
    }
    //printf("neilV=%g, paraV=%g, coneV=%g, vt=%g \n",neiloidV, parabloidV,coneV,v->vt);
    // Now compute volume of trunk heartwood (vth).

    // Potential radii of heartwood section:
    double r0 = r->r0 - sw;
    double rB = r->rB - sw;
    double rC = r->rC - sw;
    v->vth=0;

    if(r0 < 0){
      // no heartwood, entire trunk is sapwood
      v->vth = 0;
    }
    else if(rB < 0){
      // heartwood terminates in basal neiloid section.
      // Height if heartwood ends in neiloid:
      v->vth = (M_PI/4)*(h->H - h->H*(pow((sw/r->r0),(2/3))))*pow(r0,2);
    }
    else if(rC < 0){
      // heartwood terminates in middle paraboloid section.
      // Height if heartwood ends in paraboloid:
      double temp;
      temp = h->H - (h->H-h->hB)*pow((sw/r->rB),2);
      //H = Hp;
      // TODO: check that Volumes are > 0
      if (temp != 0){
	neiloidV = (M_PI/4)*pow(r0,2)*(pow(temp,4) -
				       pow((temp-h->hB),4))/(pow(temp,3));
	parabloidV = (M_PI/2)*(temp-h->hB)*(pow(rB,2));
	v->vth = neiloidV + parabloidV;
      }
      else {
	//printf("problems in trunkvolume 2 \n");
	//getchar();
	st->status=0;  // tree dies
      }
    } // end if rC <0
    else{
      // heartwood terminates in top cone section.
      // Height if heartwood reaches cone
      double temp;
      temp=fminmacro((h->H-sw),(h->H*rC+h->hC*sw)/r->rC);
      if((temp != 0) && (temp != h->hB)){
	neiloidV = (M_PI/4)*pow(r0,2)*(pow(temp,4) -
				       pow((temp-h->hB),4))/(pow(temp,3));
	parabloidV = (M_PI/2)*(pow(rB,2))*(pow(h->hB,2) -
					   pow(h->hC,2) + 2*temp*(h->hC-h->hB))/(temp-h->hB);
	coneV = (M_PI/3)*(pow(rC,2))*(temp-h->hC);
	v->vth = neiloidV + parabloidV + coneV;
      }
      else {
	//printf("problems in trunkvolume 3 \n");
	//getchar();
	st->status=0; // tree dies
      }
    } // end outer else statement


    // update volume of trunk sapwood
    if (v->vt >= v->vth){
      v->vts =v->vt - v->vth;
    }
    else {
      //printf("error in trunkvolume: vt<vth \n");
      st->status=0; // tree dies
    }

  }
  else {
    v->vt=0;
    v->vts=0;
    v->vth=0;
    //printf("error in trunkvolume 1 \n");
    st->status=0;  // tree dies
  }

} // end trunkvolume()



///
/// NOTE all MKF comments added in 2018 by Michael Fell
///
/// Need to find comments on this function in Matlab code
/// \param LAI         LAindex structure
/// \param LA          Larea structure
/// \param LAtot       total leaf area of target tree
/// \param rBH         trunk radius at breast height
/// \param r0          trunk radius at base of tree (also referred to as 'r')
/// \param H           tree height
/// \param p           structure with growth model parameters
/// \param Hc          height of forest canopy
///
/// Returns LAI and LA
///
/// Note: need to allow for scalar or vector values of LA
/// I don't think this is necessary MKF
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-11-2010
///
/// Furthur modified by Michael Fell to address leftover comments and allow
/// use of the gap dynamics code.
///
/// date March 14, 2018
///

void LAIcalc(LAindex *LAI, Larea *LA, double LAtot, double r0,
	     double H, double rBH, sparms *p, gparms *gp, double Hc,
	     tstates *st){

  /******* Matlab comments
	   % function [LAI LA] = LAIcalc(LAtot, rBH, r0, H, p, Hc);
	   %
	   % Modified 5/19/08
	   %
	   % INPUTS:
	   %   LAtot = total leaf area of target tree
	   %   rBH = trunk radius at breast height
	   %   r0 = trunk radius at base of tree (also referred to as 'r')
	   %   H = tree height
	   %   p = structure with growth model parameters
	   %   Hc = height of forest canopy
	   %
	   % OUTPUTS:
	   %   LAI = tree's leaf area index (if Hc is missing, scalar with total LAI)
	   %   LAI(1) = total LAI of target tree;
	   %	 LAI(2) = LAI of target tree above the forest canopy (LAItop);
	   %	 LAI(3) =  LAI of target tree below the forest canopy (LAIbot);
	   %   LA = tree's leaf area (if Hc is missing, scalar with total LA)
	   %   LA(1) = total leaf area (LA) of target tree;
	   %	 LA(2) = LA of target tree above the forest canopy (LAtop);
	   %	 LA(3) = LA of target tree below the forest canopy (LAbot);

	   % Compute maximum radius of tree's crown (Rmax) based on: trunk diamter
	   % (diam) in cm; canopy maximum potential radius (Rmax) in m; canopy area
	   % (CanArea) at base of canopy in m^2. Model modified from Purves et al.
	   % PLOS
  ***************/
  double diam, Rmax, r0star=0, CAtot, Vtot, LAItot, z, CAz, Vz;
  //printf("in LAIcalc: rBH=%g, p->R0=%g, p->R40=%g, r0=%g \n",rBH,p->R0,p->R40,r0);
  //printf("p->hmax=%g, p->phih=%g, gp->BH=%g \n",p->hmax,p->phih,gp->BH);
  if (rBH > 0){
    diam = 2*rBH*100;
    Rmax = p->R0 + (p->R40 - p->R0)*(diam/40);
  }
  else{
    diam = 2*r0*100;
    // FIX THIS LATER
    if (p->hmax <= gp->BH){
      Rmax=0;
      st->status=0;  // tree dies
    }
    else {
      r0star = -(p->hmax/p->phih)*log((p->hmax-gp->BH)/p->hmax);
      Rmax = (p->R0/r0star)*r0;
    }
  }
  //printf("Rmax=%g, p->eta=%g, p->M=%g, p->alpha=%g \n",Rmax,p->eta,p->M,p->alpha);
  // Total projected crown area of tree at base of crown
  CAtot = M_PI*pow(Rmax,2)*pow((1-p->eta)/p->M,(2*p->alpha));
  // Total volume of tree's crown:
  Vtot = CAtot*(((1-p->eta)*H)/(1+2*p->alpha));
  //printf("CAtot=%g, Vtot=%g \n",CAtot,Vtot);
  // Total leaf area index of tree's crown
  if (CAtot > 0){
    LAItot = LAtot/CAtot;
  }
  else {
    // TODO: fix this
    LAItot = LAtot/1e-200;
    //printf("CAtot=%g, LAItot=%g \n",CAtot,LAtot);
  }
  //hack for now.  Need to make LAIcalc work on variable length arguements
  if (Hc == -99){
    // Forest canopy hght not given, so just return tree's LAI and LA:
    LAI->tot = LAItot;
    LA->tot = LAtot;
    LA->top = 0;
    LA->bot = 0;
    LAI->top = 0;
    LAI->bot = 0;
  }
  else{
    //If given forest canopy height, compute tree's LAI and LA above (top) and
    // below (bot) the height of the forest canopy

    // If tree's crown is taller than forest canopy:
    if (H > Hc){
      z = H-Hc;

      // If bottom of tree's crown is below forest canopy:
      //printf("z=%g, H=%g, Hc=%g. \n");
      if (z < (1-p->eta)*H){
      	CAz= M_PI*pow(Rmax,2)*pow(z/(H*p->M),(2*p->alpha));
      	Vz = CAz*(z/(1+2*p->alpha));
      	//printf("CAz=%g, Vz=%g. \n");
      	LA->top = LAtot*Vz/Vtot;
      	LA->bot = LAtot - LA->top;
      	//LAI->top = LAtop/CAz;
      	LAI->top = LA->top/CAtot;
      	LAI->bot = LA->bot/CAtot;
      	
//      	Rprintf("LAIcalc H > Hc LAI->top=%g \n", CAtot);
      }
      // Below, if forest canopy is below tree's crown:
      else{
      	LA->top = LAtot;
      	LA->bot = 0;
      	LAI->top = LAItot;
      	LAI->bot = 0;
//      	Rprintf("Inner else in LAIcalc \n");
      }
    }
    // Below, if forest canopy it taller than tree:
    else{
      LAI->top = 0;
      LAI->bot = LAItot;
      LA->top = 0;
      LA->bot = LAtot;
//      Rprintf("Outer ouse in LAIcalc \n");
    }
  } // End of else above
  LA->tot=LAtot;
  LAI->tot=LAItot;

  if (isnan(LAItot)!=0){
    //printf("error in LAI_calc: LAItot is nan \n");
  }
//  Rprintf("LAIcalc LAI->top=%g \n", LAI->top);
//  Rprintf("LAIcalc LAI->bot=%g \n", LAI->bot);
//  Rprintf("LAIcalc LAI->tot=%g \n", LAI->tot);
} // end LAIcalc()



///
/// Function APARcalc()
///
/// author Kiona Ogle (translated into C by Michael Fell)
///
/// date early 2018
///
///
///

//(LAindex *LAI, Larea *LA, double LAtot, double r0,
 //double H, double rBH, sparms *p, gparms *gp, double Hc,
 //tstates *st)

 // Hc and FLAI can just pass the double values with minimal issue
void APARcalc(double *APARout, LAindex *LAI, Larea *LA, double eta, double k, double H,
                double Hc, double FLAI, double Io, Forestparms *ForParms)
{
  // Define internal variables
  double APAR;
  double Ioint = 0; //Io internal to this function
  // First block
  double logitLAImin;
  double pLAImin;
  double logitLAImax;
  double pLAImax;
  // First if
  double logitLAIc1;
  double pLAIc1;
  double LAIc1;
  double logitLAIc2;
  double pLAIc2;
  double LAIc2;
  double LAIc;
  double Kboth;
  double LAIboth;
  double fabs_both;
  double fabs_tree;
  double fabs_can;
  double fabs;
  // Third if
  double LogitLAIc;
  double pLAIc;
  double fabs_top;
  double APAR_top;
  double APAR_bot;
  // My vars
  //double APARout[2] = {-2, -2};

  // Predicted, unscaled forest canopy LAI at top of canopy:
  logitLAImin = ForParms->intF + ForParms->slopeF;
  pLAImin = exp(logitLAImin) / (1 + exp(logitLAImin));
  // Predicted, unscaled forest canopy LAI at ground level:
  logitLAImax = ForParms->intF;
  pLAImax = exp(logitLAImax) / (1 + exp(logitLAImax));
  
//  Rprintf("APAR_top=%g \n", LAI->top);
//  Rprintf("APAR_bot=%g \n", LAI->bot);
//  Rprintf("APAR_tot=%g \n", LAI->tot);

  if(H < Hc){
    // Calculate forest canopy LAI from top of forest canopy (height H meters)
    // to top of target tree (height H):
    assert(Hc > 0); // Make sure Hc > 0 or print an error and stop execution
    logitLAIc1 = ForParms->intF + ForParms->slopeF * (H/Hc);
    pLAIc1 = exp(logitLAIc1) / (1 + exp(logitLAIc1));
    // Rescale distribution of forest canopy LAI so that LAI = 0 at top of
    // canopy and LAI maximum LAI at ground level:
    assert((pLAImax - pLAImin) > 0); // Prevent divide by 0 this should be
                                     // positive.
    pLAIc1 = (pLAIc1 - pLAImin) / (pLAImax - pLAImin);
    LAIc1 = FLAI * pLAIc1;
    // Io is light level incedent at top of target tree's canopy, after having
    // accounted for the light absorbed by the forest canopy above the tree.
    Ioint = Io * exp(-ForParms->kF * LAIc1);

    // Now calculate the amount of light absorbed within a cylinder containing
    // the target tree's canopy and partitioning the abount absorbed by the
    // tree's canopy according to its potential fraction absorbed.

    // Calculate forest canopy LAI between the top and bottom of the target
    // tree's canopy:
    logitLAIc2 = ForParms->intF + ForParms->slopeF * (eta * H / Hc);
    // Rescale distribution of forest canopy LAI:
    pLAIc2 = exp(logitLAIc2) / (1 + exp(logitLAIc2));
    pLAIc2 = (pLAIc2 - pLAImin) / (pLAImax - pLAImin);
    LAIc2 = FLAI * pLAIc2;
    LAIc = LAIc2 - LAIc1;
    // Total LAI (forest + tree's canopies) within a cylinder containing the
    // target tree's canopy:
    LAIboth = LAIc + LAI->tot;
    // Combined light ext coef of forest and tree's canopies:
    assert(LAIboth > 0);
    Kboth = (ForParms->kF * LAIc + k * LAI->tot) / LAIboth;
    // Fraction of light absorbed by both canopies:
    fabs_both = 1 - exp(-Kboth * LAIboth);
    // Fraction of light that would have been absorbed by the tree's canopy if
    // not competing with the forest canopy:
    fabs_tree = 1 - exp(-k * LAI->tot);
    // Fraction of light that would have been absorbed by the forest's canopy
    // if not competing with the tree's canopy:
    fabs_can = 1 - exp(-ForParms->kF * LAIc);
    // "Correction" fraction of light absorbed by the tree's canopy, and total
    // amount of light absorbed by the tree:
    assert((fabs_tree + fabs_can) > 0);
    fabs = fminmacro(fabs_tree, fabs_both * fabs_tree / (fabs_tree + fabs_can));
    APAR = Ioint * fabs * LA->tot / LAI->tot;
  }
  else if((eta * H) > Hc){
    // Fraction and total amount of light absorbed by the target tree's canopy
    // when not competing for light with the forest canopy.
    fabs = 1 - exp(-k * LAI->tot);
    assert(LAI->tot > 0);
    APAR = Io * fabs * LA->tot / LAI->tot;
  }
  else if((eta * H) < Hc){
    // For the portion of the target tree's canopy that is above the forest
    // canopy, compute the fractionand total amount of light absorbed by the
    // top part of the tree's crown, and compute light penetrating to the
    // lower part of the crown (Io):
    fabs_top = 1 - exp(-k * LAI->top);
    assert(LAI->top > 0);
    APAR_top = Io * fabs_top * LA->top / LAI->top;
    Ioint = Io * (1 - fabs_top);

//    Rprintf("LAI->top=%g, APAR_top=%g, Ioint=%g \n", LAI->top, APAR_top, Ioint);
    // Now, compute the amount of light absorbed by the bottom part of the
    // tree's crown that is competing with the forest canopy for light.

    // Compute the LAI of the forest canopy to the bottom of the tree's crown:
    LogitLAIc = ForParms->intF + ForParms->slopeF * (eta * H / Hc);
    // Rescale distribution of forest canopy LAI:
    pLAIc = exp(LogitLAIc) / (1 + exp(LogitLAIc));
    pLAIc = (pLAIc-pLAImin) / (pLAImax - pLAImin);
    LAIc = FLAI * pLAIc;
    
//    Rprintf("LogitLAIc=%g, pLAIc=%g, LAIc=%g \n", LogitLAIc, pLAIc, LAIc);
    // Total LAI (forest + tree's canopies) within a cylinder containing the
    // target tree's bottom crown portion
    LAIboth = LAIc + LAI->bot;
//    Rprintf("LAIboth=%g \n", LAIboth);
    // Combined light ext coeff of forest and tree's canopies:
    Kboth = (ForParms->kF * LAIc + k * LAIboth);
//    Rprintf("Kboth=%g \n", Kboth);
    // Fraction of light absorbed by both canopies:
    fabs_both = 1 - exp(-Kboth * LAIboth);
//    Rprintf("fabs_both=%g \n", fabs_both);
    // Fraction of light that would have been absorbed by the forest's canopy
    // if not competing with the tree's canopy:
    fabs_tree = 1 - exp(-k * LAIboth);
//    Rprintf("fabs_tree=%g \n", fabs_tree);
    // Fraction of light that would have been absorbed by the forest's canopy
    // if not competing with the tree's canopy:
    fabs_can = 1 - exp(-ForParms->kF * LAIc);
//    Rprintf("fabs_can=%g \n", fabs_can);
    // Fraction of light absorbed by the tree's canopy, and total amount of light absorbed by the tree:
    fabs = fminmacro(fabs_tree, fabs_both * fabs_tree / (fabs_tree + fabs_can));
//    Rprintf("fabs=%g \n", fabs);
//    Rprintf("LAI->bot=%g \n", LAI->bot);
    assert(LAI->bot > 0);
    APAR_bot = Ioint * fabs * LA->bot / LAI->bot;
//    Rprintf("APAR_bot=%g \n", APAR_bot);
    APAR = APAR_top + APAR_bot;
//    Rprintf("APAR=%g \n", APAR);
  }
  else{
    printf("APAR not determined for gap sim.");
    exit(1);
  }
  // APAR out and save value Ioint to APARout
  APARout[0] = APAR;
  APARout[1] = Ioint;
//  Rprintf("Ioint=%g \n", Ioint);
  //return APARout;
}

///
/// Initializes species parameters (p) for growthoop for red maple (species 2)
/// \param p            Species parameters (sparms)
/// \param gp           gparms
/// \param tp           tree specific parameters (tparms)
///
/// Returns p, gp, and tp
///
/// Note: This should maybe be a part of the initialize function?
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-11-2010
///
/*
void acruparms(sparms *p){
  p->hmax=27.5;
  p->phih=263.0;
  p->eta=0.64;
  p->swmax=0.10; //exp(-3.054);
  p->lamdas=0.95;
  p->lamdah=0.95;
  p->rhomax=502000.0;//exp(13.2);
  p->rhomin=502000.0;//exp(13.2);
  p->rhomin=p->rhomax;
  p->f2= 840.0;//exp(8.456);//   //f2=gammax*NEWf2
  p->f1=4.0;
  p->gammac=131000.0;
  p->gammaw=0.000000667;
  p->gammax=0.12;//inv_logit(-0.709);//
  p->cgl=1.45;//exp(0.3229);//
  p->cgr=1.25;//exp(0.192);//
  p->cgw=1.37;//exp(0.3361);//
  p->deltal=0.095;//inv_logit(-2.276);//
  p->deltar=0.15; //inv_logit(-2.832);//
  p->sl=1.0;//exp(0.8133);//
  p->sla=0.0121;//exp(-4.119);//
  p->sr=1.0;//exp(0.2493);//
  p->so=0.05;//exp(0.6336); //
  p->rr=0.00015;//exp(-8.103); //
  p->rhor=160000.0; // new value: exp(-1.724);
  p->rml=1.25;//exp(2.544);//
  p->rms=0.025;//exp(0.5499); //
  p->rmr=0.75;//exp(3.252);//
  p->etaB=0.045;
  p->K=0.70;
  p->epsg=6.75;//exp(-3.304); //6.75;
  p->M=0.95;
  p->alpha=0.365;
  p->R0=1.909;
  p->R40=5.592;
  p->drinit=0.000010;
  p->drcrit=0.00750;
} // end acruparms()
*/

///
/// Initializes species parameters (p) for growthoop for loblolly pine (sp 1)
/// \param p            Species parameters (sparms)
/// \param gp           gparms
/// \param tp           tree specific parameters (tparms)
///
/// Returns p, gp, and tp
///
/// Note: This should maybe be a part of the initialize function?
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-11-2010
///
/*
  void pitaparms(sparms *p){
  p->hmax=42;
  p->phih=220;
  p->eta=0.71;
  p->swmax=0.06;//exp(-2.946); //
  p->lamdas=0.95;
  p->lamdah=0.95;
  p->rhomax=296000.0;//exp(12.92); //
  p->rhomin=296000.0;//exp(12.92); //380000.0;
  p->rhomin=p->rhomax;
  p->f2=1302.0;//exp(7.981);//1302.0;
  p->f1=4.0;
  p->gammac=265000.0;
  p->gammax=0.62;//inv_logit(-0.3071); //0.62;
  p->gammaw=0.000000667;
  p->cgl=1.51;//exp(0.3964);//1.51;
  p->cgr=1.3;//exp(0.1655);//1.3;
  p->cgw=1.47;//exp(0.3753);//1.47;
  p->deltal=0.11;//inv_logit(-2.528);//0.11;
  p->deltar=0.08;//inv_logit(-2.633);//0.08;
  p->sl=.33;//exp(-1.392);//.33;
  p->sla=0.00497;//exp(-5.34); //0.00497
  p->sr=0.5;//exp(0.4873);//0.5;
  p->so=0.05;//exp(0.5704);//0.05;
  p->rr=0.00027;//exp(-7.874);//0.00027;
  p->rhor=200000.0;  // new value:exp(-2.489);
  p->rml=0.95;//exp(2.077);//0.95;
  p->rms=0.025;//exp(-0.04416);//0.025;
  p->rmr=0.75;//exp(3.129);// 0.75;
  p->etaB = 0.045;
  p->K=0.55;
  p->epsg=4.5;//exp(-3.29);//4.5;
  p->M=0.95;
  p->alpha=0.308;  // very old: 0.72
  p->R0=1.434;
  p->R40=3.873;
  p->drinit=0.00001;
  p->drcrit=0.01;
}
*/

