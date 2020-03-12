///
/// \file excessgrowing.c
/// \brief Contains functions excessgrowingon(), and excessgrowingoff()
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
/// \date 11-23-2010
///
/// No growthmodel-type errors in this file.  Only numerical.
/// TODO: still need to set status=0 for failures of numerical
/// checks in this file.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <R.h>
#include "head_files/misc_growth_funcs.h"
#include "head_files/excessgrowing.h"

/// excessgrowingon is used to grow a tree (that is currently on the target allometry)
/// along the target allometry.
///
/// \param p            Species parameters (sparms)
/// \param gp           Misc. growth parameters (gparms)
/// \param st           tree state variables (tstates)
/// \param i            iteration value from growth model loop
/// \param growthflag   0 if tree is currently off allometry, = 1 if tree is on allometry
/// \param r            array of tree radii
///
///
/// Returns updated st (state variables), r and h.  Calls on functions trunkradii() and
/// trunkvolume().  This has been mostly tested with Matlab code.  Should be checked
/// again.
///
/// \todo remove the hin, rin temp structures
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 11-23-2010
///

void excessgrowingon(sparms *p, gparms *gp, tstates *st,
	int i, int growthflag, double r[], int *errorind2, int *growth_st){
	//, double *tolout, double *errorout, double *drout, double *demandout,
	//double *odemandout, double *odrout){
  //Rprintf("The growthloop iteration is: %i \n", i);
	height hin; radius rin; volume v;

	//local temp variables.
	double dr=0; // incremental increase in radius
	double odr=0; // old incremental increase
	double efl=0,efr=0,efo=0,eft=0; // used to find demand
	double demand=0,odemand=0; // demand and old demand
	double denom=0,slope=0,intercept=0; // temp variables for root finding routine
	double nuo=0, rhow=0,la_new=0,ra_new=0;

	double r_new=0;  // new radius
	double oslope=0; // old slope (at t - 1) MKF 2/13/19 slope problem
	double obts=0; // starting bts (not negative)

	int j=1;
	int numerrors=0;

	double deltaw=0; // Is this a local (temp) variable? need to check on this.

	int eflag=0;                  // initialize while loop index

	// Matlab used 2*abs(excess*tolerance)+1;
	double error = fabs(st->ex*gp->tolerance)+10;         // initialize error w/ high value

	// Determine new value of r such that "demand" and excess are approx. equal.
	obts = st->bts;
	while ((error > fmaxmacro(fabs(st->ex*gp->tolerance),1e-5)) && (j<1000) && (st->status!=0)){
	  //Rprintf("slope=%g, error=%g, j=%i \n", slope, error, j);
		if (j>999){ // Was 998 not sure why
			st->status=0;
			*growth_st = 20;
		}
		eflag=0; // eflag=1 when dr=0

		if (j==1){  // j=1 is the first iteration in while loop

			if ((i<2) || (growthflag==0) || (r[i-1]==r[i-2])){// error check, if the tree is currenlty off allometry:
				odr=p->drinit;  // initial default radius increment
				dr=odr;         // new dr updated as old dr (odr)
			}
			else{
				odemand=st->egrow;        // egrow is excess labile carbon available for growth
				odr = r[i-1]-r[i-2];      // old dr.  should not =0 based on first if statement
				if ((odr > 0) && (odemand != 0)){
					slope=odemand/odr;
					dr=st->ex/slope;
				}
				else{
					//printf("problem in excessgrowingon, line 87 \n");
					*errorind2 = *errorind2 | 4;
					st->status=0;
					*growth_st = 21;
					break;
				}  // end else
			} // end outer else
		} //end if j==1

		else if ((j==2) && ((i<3) || (growthflag==0) || (r[i-1]==r[i-2]))){
			odemand=demand;   // demand saved to old demand
			odr = dr;         // dr saved to old dr
			if ((odr > 0) && (odemand != 0)){
				slope=odemand/odr;
				dr=st->ex/slope;
			}
			else{
				//printf("problem in excessgrowingon, line 102 \n");
				*errorind2 = *errorind2 | 8;
				st->status=0;
				*growth_st = 22;
				break;
			}  // end else
		} // end else if

		else{  // else if none of those conditions are met
			if (dr != odr){
			slope=(demand-odemand)/(dr-odr);
			}
			else{
				//printf("problem in excessgrowingon, line 111 \n");
				//getchar();
				st->status=0;
				*growth_st = 23;
				break;
			}
			intercept=demand-slope*dr;
			odemand=demand;
			odr=dr;
			if (slope == 0){
			  if(numerrors <=10){
			    //Rprintf("Restarting ROOT FINDING algorithm.");
			    slope = oslope;
			    error = fabs(st->ex*gp->tolerance)+(10*numerrors);
			    odr=p->drinit;  // initial default radius increment
			    dr=odr;         // new dr updated as old dr (odr)

		      odemand=st->egrow;        // egrow is excess labile carbon available for growth
		      odr = r[i-1]-r[i-2];      // old dr.  should not =0 based on first if statement
		      if ((odr > 0) && (odemand != 0)){
		        slope=odemand/odr;
		        dr=st->ex/slope;
		      }
		      else{
		        //printf("problem in excessgrowingon, line 87 \n");
		        *errorind2 = *errorind2 | 4;
		        st->status=0;
		        *growth_st = 200;
		        break;
		      }  // end else

			    // Rprintf("SLOPE = 0 error RESTART NOW! \n");
			  }
			  numerrors++;
			}
			if (slope != 0){
				dr=st->ex/slope;
			}
			else{
        //Rprintf("Slope 0 slope=%g, error=%g, j=%i \n", slope, error, j);
				//printf("problem in excessgrowingon, line 120 \n");
				*errorind2 = *errorind2 | 16;
				//getchar();  // keep
				st->status=0;
				*growth_st = 24;
				break;
			}
			// TODO: ASK ABOUT THIS.  THIS IS ALWAYS TRUE
			// ASK: changed this.  make sure it is ok.
			if ((slope>0.0000001) || (error>fabs(st->ex*gp->tolerance))){
				if( slope !=0){
					dr=(st->ex-intercept)/slope;
					if (dr<0.0){
						dr=0.0;
						eflag=1;
					}
				}
				else{
					st->status=0;
					*growth_st = 25;
					dr=0;
				}
			}
			else {
				demand=st->ex;
				error=0.0;
				//printf("set demand = excess in excessgrowingon \n");
			}
		} //end else

		// ***** end block of if, else if, else  *****

		// Calculate demand and error based on r and dr:
		// Begin if error ...
		if (error >= fabs(st->ex*gp->tolerance)){

			r_new=st->r+dr;  // new radius calc. from new dr

			if (r_new < 0){
				//printf("error in excessgrowingon, line 162 \n");
				//printf("dr=%g, slope=%g, odemand=%g, demand=%g, intercept=%g, j=%d \n",
				//       dr, slope, odemand,demand,intercept,j);
				//printf("sla=%g, hmax=%g, phih=%g, st->r=%g, st->ex=%g, rhomax=%g \n",p->sla,
				//       p->hmax, p->phih, st->r, st->ex, p->rhomax);
				r_new=st->r;
				st->h=p->hmax*(1.0-exp(-p->phih*r_new/p->hmax));
				st->status=0;
				*growth_st = 26;
				//getchar();
				break;
			}
			//printf("r_new=%g \n",r_new);
			if (p->hmax > 0){
				st->h=p->hmax*(1.0-exp(-p->phih*r_new/p->hmax));
			}
			else{
				//printf("problem in excessgrowingon, line 161 \n");
				*errorind2 = *errorind2 | 32;
			}
			st->hh=p->eta*st->h;

			if (r_new < p->swmax){
				st->sw=r_new;
			}
			else {
				st->sw=p->swmax;
			}

			// maybe should eliminate the need for these temp variables (i.e. the radius
			// and height structures)
			hin.hB=p->etaB*st->h;
			hin.hC=st->hh;
			hin.H=st->h;
			hin.hBH=gp->BH;


			trunkradii(r_new, &hin, &rin, st);

			trunkvolume(&rin, &hin, st->sw, &v, st);

			// end new radii and volume calculations.


			if((st->vts*gp->deltat != 0) && ((1.0+st->deltas)*st->bos != 0)){
				st->nut=(v.vth-st->vth)/(st->vts*gp->deltat);
			  //Rprintf("v.vth=%g, st->vth=%g, st->vts=%g \n", v.vth, st->vth, st->vts);
				nuo=(p->so*st->boh+(1.0+st->deltas)*p->lamdah*st->nut*st->bts)/((1.0+st->deltas)*st->bos);
			}
			else{
				//printf("problem in excessgrowingon, line 195 \n");
				*errorind2 = *errorind2 | 64;
				st->status=0;
				*growth_st = 27;
			}

			if (dr<(p->drcrit*gp->deltat)){
				rhow=p->rhomax-((p->rhomax-p->rhomin)/p->drcrit)*dr/gp->deltat;
			}
			else {
				rhow=p->rhomin;
			}
			if (rhow > ((1-p->gammax)/p->gammaw)*exp(10)/(1+exp(10))){
				// if wood density is very close to upper limit (given by deltaw=0), set
				// carbon storage capacity to zero to avoid rounding and computational errors.
				deltaw=0;
			}
			else if (rhow != 0) {
				deltaw=p->gammac*(1.0-p->gammax-p->gammaw*rhow)/rhow;
			}
			else{
				//printf("problem in excessgrowingon, line 214 \n");
				st->status=0;
				*growth_st = 28;
				*errorind2 = *errorind2 | 128;
			}

			st->sa=M_PI*st->sw*(2.0*r_new-st->sw);
			// need la_new and ra_new since we find the difference between new and old
			// below
			la_new=p->f2*st->sa;
			ra_new=p->f1*la_new;

			if (p->sla != 0){
				efl=(p->cgl+p->deltal)*(la_new-st->la+p->sl*p->sla*st->bl*gp->deltat)/(p->sla*gp->deltat);
				efr=(p->cgr+p->deltar)*(p->rr*p->rhor*(ra_new-st->ra)+2*p->sr*st->br*gp->deltat)/(2.0*gp->deltat);
				eft=(p->cgw+deltaw)*((v.vt-st->vt)*rhow-st->deltas*st->nut*st->bts*gp->deltat)/gp->deltat;
			}
			else{
				//printf("problem in excessgrowingon, line 232 \n");
				st->status=0;
				*growth_st = 29;
				*errorind2 = *errorind2 | 256;
			}
			if ((1+st->deltas) != 0){
				efo=(p->cgw+deltaw)*(p->so*gp->deltat*st->boh+(1+st->deltas)*
					((v.vt-st->vt)*p->lamdas*rhow+p->so*st->bos*gp->deltat+
					(p->lamdah-(1+st->deltas)*p->lamdas)*st->nut*st->bts*
					gp->deltat))/((1+st->deltas)*gp->deltat);
			}
			else{
				//printf("problem in excessgrowingon, line244 \n");
				st->status=0;
				*growth_st = 30;
				*errorind2 = *errorind2 | 512;
			}
			// update demand
			if (eflag==0) {
				demand=efl+efr+eft+efo;
			}
			else {
				demand=st->ex;
			}

			error=fabs(demand-st->ex);  // update the error

      //tolout[(i-1)*1000+j] = fmaxmacro(fabs(st->ex*gp->tolerance),1e-5);
      //errorout[(i-1)*1000+j] = error;
      //odrout[(i-1)*1000+j]=odr;
      //drout[(i-1)*1000+j]=dr;
      //odemandout[(i-1)*1000+j]=odemand;
      //demandout[(i-1)*1000+j]=demand;
      //printf("tolout, iter=%d, tolout=%f \n",i,tolout[(i-1)*1000+j]);
      //printf("errorout, iter=%d, errorout=%f \n",i,errorout[(i-1)*1000+j]);
      //printf("error, iter=%d, error=%f \n",i,error);


			j=j+1;   // change this to ++j
			oslope = slope;

		} //end "if (error..."
		//Rprintf("While loop calc, st->bts=%g, rhow=%g, v.vt=%g, st->vt=%g, st->nut=%g, gp->deltat=%g, i=%i \n", st->bts, rhow, v.vt, st->vt, st->nut, gp->deltat, i);
	} //end while loop



	// allocation fractions
	denom=efl+efr+eft+efo;
	st->fl=fmaxmacro(0,efl/denom);
	st->fr=fmaxmacro(0,efr/denom);
	st->ft=fmaxmacro(0,eft/denom);
	st->fo=fmaxmacro(0,efo/denom);

	denom=st->fl+st->fr+st->ft+st->fo;

	if (denom != 0) {
		st->fl=st->fl/denom;
		st->fr=st->fr/denom;
		st->ft=st->ft/denom;
		st->fo=st->fo/denom;
	}
	else{
		//printf("problem with allocation fractions in excessgrowingon or putonallometry \n");
		st->status=0;
		*growth_st = 31;
		*errorind2 = *errorind2 | 1024;
	}


	// Now that we have the new trunk radius, calculate new state variables:
	if ((p->cgw+deltaw) != 0){
		st->cs=st->cs+gp->deltat*(st->ft+st->fo)*st->ex*deltaw/(p->cgw+deltaw)
			-gp->deltat*st->deltas*(st->nut*st->bts+(nuo+p->so)*st->bos);
	}
	else{
		//printf("problem in excessgrowingon, line 302 \n");
		st->status=0;
		*growth_st = 32;
		*errorind2 = *errorind2 | 2048;
	}

	// Retranslocation fractions, only due to retranslocation during senescence.
	st->rfl=p->deltal*p->sl*st->bl;
	st->rfr=p->deltar*p->sr*st->br;
	st->rfs=st->deltas*p->so*st->bos;  //use old bos
	st->rtrans=st->rfl+st->rfr+st->rfs;
	if (st->rtrans != 0){
		st->rfl=st->rfl/st->rtrans;
		st->rfr=st->rfr/st->rtrans;
		st->rfs=st->rfs/st->rtrans;
	}
	else {
		//printf("problem in excessgrowingoff or on, translocation \n");
		st->status=0;
		*growth_st = 33;
		*errorind2 = *errorind2 | 4096;
	}

	// update state variables that have been modified

	st->bth=st->bth+(1.0+st->deltas)*st->nut*st->bts*gp->deltat;

	//Rprintf("prior to calc, st->bts=%g, rhow=%g, v.vt=%g, st->vt=%g, st->nut=%g, gp->deltat=%g, i=%i \n", st->bts, rhow, v.vt, st->vt, st->nut, gp->deltat, i);
	st->bts=st->bts+rhow*(v.vt-st->vt)-st->nut*st->bts*gp->deltat;
	if(st->bts < 0){ // Added 3/6/19
	  //Rprintf("BTS BTS BTS Restarting ROOT FINDING algorithm dut to ST->BTS.");
	  st->bts = obts;
	  slope = 0; // Force algorithem reset.
	  error = fmaxmacro(fabs(st->ex*gp->tolerance),1e-5) + 1; // Make sure while continues 3/6/2019
	}
	//Rprintf("st->bts=%g, i=%i \n", st->bts, i);

	if ((isnan(st->cs) !=0) || (isnan(st->deltas) !=0) ||
		(isnan(st->bos) !=0) || (isnan(st->bl) !=0)  || (isnan(st->ex) !=0)){
		//printf("inside excess growing on \n");
		//printf("st.r=%g, st.bos=%g, st.bts=%g \n", st->r,st->bos,st->bts);
		//printf("f2=%g, st.sa=%g, st.bl=%g, p->sla=%g \n",log(p->f2), st->sa, st->bl, p->sla);
		//printf("st->br=%g, st->bl=%g, p->sl=%g, p->sr=%g \n", st->br, st->bl, p->sl, p->sr);
		//printf("st->bts=%g,st->boh=%g,p->lamdah=%g,st->bth=%g, st->bos=%g \n",
		  //st->bts,st->boh,p->lamdah,st->bth,st->bos);

		//printf("dr=%g, slope=%g, odr=%g \n",dr,slope,odr);
		//printf("st->cs=%g, gp->deltat=%g, excess=%g, st->deltas=%g, p->so=%g, st->bos=%g \n",
		  //st->cs, gp->deltat, st->ex, st->deltas, p->so, st->bos);

		*errorind2 = *errorind2 | 8192;

	}

	st->bl=la_new/p->sla;
	st->br=p->rhor*p->rr*ra_new/2;
	st->bt=st->bts+st->bth;
	st->bos=p->lamdas*st->bts;
	st->boh=p->lamdah*st->bth;
	st->bo=st->bos+st->boh;
	st->bs=st->bos+st->bts;
	st->clr=p->deltal*st->bl+p->deltar*st->br;
	st->dr=r_new-st->r;
	st->r  = r_new;
	// st->dr=dr;
	st->rB = rin.rB;
	st->rC = rin.rC;
	st->rBH= rin.rBH;
	st->vts= v.vts;
	st->vt = v.vt;
	st->vth= v.vth;
	st->la = la_new;
	st->ra = ra_new;
	st->egrow=st->ex;
} //end excessgrowingon



/// excessgrowingoff is used to grow a tree (that is currently OFF the target allometry)c
/// along the reduced allometry (i.e., not enough labile C to bring-up to target allom.)
///
/// \param p            Species parameters (sparms)
/// \param gp           Misc. growth parameters (gparms)
/// \param st           tree state parameters (tstates)
/// \param i            iteration value from growth model loop
/// \param deltaw       storage capicity of newly-built "other" sapwood, calc'd in 'growthloop'
///
/// Returns update st (state variables).    THIS NEEDS TO BE TESTED against the Matlab code.
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 12-07-2010
///

void excessgrowingoff(sparms *p, gparms *gp, tstates *st, int i, double deltaw,
	int *errorind2, int *growth_st){

	//temp local variables for intermediate calculations
	double nuo=0,bos_new=0;

	// Grow tree along reduced allometry
	double prt1=2.0*st->bts*p->sla*p->lamdas;
	double prt2=(p->cgl+p->deltal)*(1.0+st->deltas)*(1.0-p->sl*gp->deltat)*st->bl;
	double prt3=(1.0-p->so*gp->deltat)*(p->cgw+deltaw)*st->boh;
	double prt4=(st->ex)*gp->deltat+(1.0-p->so*gp->deltat)*(p->cgw+deltaw)*
		st->bos+(p->cgr+p->deltar)*(1.0-p->sr*p->deltar)*st->br;
	double prt5=2.0*p->sla*(p->cgw+deltaw)*(st->bth*p->lamdah+st->bts*(1.0+st->deltas)*p->lamdas);
	double prt6=2.0*p->deltal+p->f1*p->rr*p->sla*(p->cgr+p->deltar)*p->rhor;
	double num=prt1*(prt2+prt3+(1.0+st->deltas)*prt4);
	double den=2.0*p->cgl*p->f2*st->sa*(1.0+st->deltas)+prt5+p->f2*st->sa*(1.0+st->deltas)*prt6;
	// only bos is updated here
	if (den != 0){
		bos_new=num/den;
	}
	else {
		//printf("problem in excessgrowingoff, line 419 \n");
		st->status=0;
		*growth_st = 34;
		*errorind2 = *errorind2 | 16384;
	}
	// first bos is new, second occurance is old
	den=st->bts*(1.0+st->deltas)*gp->deltat*p->lamdas*st->bos;
	if (den != 0){
		nuo= (bos_new*st->bth*p->lamdah+st->bts*(p->so*gp->deltat-1.0)*p->lamdas*st->boh)/
			den;
	}
	else {
		//printf("problem in excessgrowingoff, line 429 \n");
		st->status=0;
		*growth_st = 35;
		*errorind2 = *errorind2 | 32768;
	}

	if (nuo<=0.0){
		//prt1=2.0*st->bts*p->sla*p->lamdas;
		prt2=(p->cgl+p->deltal)*(1.0-p->sl*gp->deltat)*st->bl;
		prt3=(1.0-p->so*gp->deltat)*(p->cgw+deltaw)*st->bos;
		prt4=(p->cgr+p->deltar)*(1.0-p->sr*gp->deltat)*st->br;
		prt5=2.0*st->bts*p->sla*(p->cgw+deltaw)*p->lamdas;
		prt6=p->f1*p->f2*p->rr*st->sa*p->sla*(p->cgr+p->deltar)*p->rhor;
		num=prt1*(st->ex*gp->deltat+prt2+prt3+prt4);
		den=2.0*p->f2*st->sa*(p->cgl+p->deltal)+prt5+prt6;
		if (den != 0){
			bos_new=num/den;
		}
		else {
			//printf("problem in excessgrowingoff, line 448 \n");
			st->status=0;
			*growth_st = 36;
		}
		nuo=0.0;
	}

	// Allocation fractions.  Use bos_new
	// just reusing den and num.  they are not denominator and
	// numerator
	den=st->bts*st->ex*p->sla*p->lamdas*gp->deltat;
	num=2.0*st->bts*st->ex*p->lamdas*gp->deltat;
	if ((den !=0) && (num != 0)){
		st->fl=(p->cgl+p->deltal)*(bos_new*p->f2*st->sa+st->bts*p->sla*(p->sl*gp->deltat-1.0)*
							   p->lamdas*st->bl)/den;
		st->fr=(p->cgr+p->deltar)*(bos_new*p->f1*p->f2*p->rr*p->rhor*st->sa+2.0*st->bts*(p->sr*gp->deltat-1.0)*
							   p->lamdas*st->br)/num;
	}
	else {
		//printf("problem in excessgrowingoff, line 467 \n");
		st->status=0;
		*growth_st = 37;
		*errorind2 = *errorind2 | 65536;
	}
	st->fo=1.0-st->fl-st->fr;
	st->ft=0.0;

	// Retranslocation fractions, only due to retranslocation during senescence.
	st->rfl=p->deltal*p->sl*st->bl;
	st->rfr=p->deltar*p->sr*st->br;
	st->rfs=st->deltas*p->so*st->bos;  //use old bos
	st->rtrans=st->rfl+st->rfr+st->rfs;
	if (st->rtrans != 0){
		st->rfl=st->rfl/st->rtrans;
		st->rfr=st->rfr/st->rtrans;
		st->rfs=st->rfs/st->rtrans;
	}
	else {
		//printf("problem in excessgrowingoff or on, translocation \n");
		st->status=0;
		*growth_st = 38;
		*errorind2 = *errorind2 | 131072;
	}

	//update state variables
	if ((p->lamdas*st->bts) > 0){
		st->la=p->f2*st->sa*bos_new/(p->lamdas*st->bts);  // use bos_new
	}
	else {
		//printf("error in excessgrowingoff, line 495 \n");
		st->status=0;
		*growth_st = 39;
		*errorind2 = *errorind2 | 262144;
	}
	st->ra=p->f1*st->la;
	st->bl=st->la/p->sla;
	st->br=p->rhor*p->rr*st->ra/2.0;
	if ((p->cgw+deltaw) != 0){
		st->cs=st->cs+gp->deltat*(st->fo*deltaw*st->ex/(p->cgw+deltaw)-st->deltas*(nuo+p->so)*st->bos);
		// use old bos
	}
	else {
		//printf("problem in excessgrowingoff, line 490 \n");
		st->status=0;
		*growth_st = 40;
	}

	st->bos=bos_new;
	if ((p->lamdas*st->bts) > 0){
		st->boh=p->lamdah*st->bth*st->bos/(p->lamdas*st->bts);
	}
	else {
	  //Rprintf("p->lamdas=%g, st->bts=%g, i=%i \n", p->lamdas, st->bts, i);
		//printf("error in excessgrowingoff, line 516 \n");
		st->status=0;
		*growth_st = 41;
		*errorind2 = *errorind2 | 524288;
	}

	st->bo=st->bos+st->boh;
	st->bs=st->bos+st->bts;

	st->clr=p->deltal*st->bl+p->deltar*st->br;
	st->egrow=0.0;
	//st->status=1;

}

/// All error code added to this file by mkf was done between 5/19 and 5/21 2013
/// to capture errors for the end user.  These errors are interpreted by the
/// part of the code implemented in R.  The R code interprets the sequence of
/// bits from the integer values to return the error messages that are printed
/// out by this code.  All of the line numbers in this code are wrong unless the
/// getchar(); line is removed from the code.
///
/// I removed the getchar() lines from this code where I added error indicators
/// so that the code is the same length as it was when Darren wrote it.
///
