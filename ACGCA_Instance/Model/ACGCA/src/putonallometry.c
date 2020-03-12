///
/// \file putonallometry.c
/// \brief Contains function putonallometry().
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 02-08-2010
///
///

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "head_files/misc_growth_funcs.h"
#include "head_files/putonallometry.h"

/// putonallometry is used to bring a tree back to the target allometry (was currently
/// off allometry) and then grow the tree along the target allometry.
///
/// \param p            Species parameters (sparms)
/// \param gp           gparms
/// \param st           tree state parameters (tstates)
/// \param i            iteration value from growth model loop
/// \param deltaw       max. labile C storage capacity of current sapwood.
/// \param pton         contains ea,eo,el,er
///
/// Returns update st (state variables).  Follows the same form as excessgrowingon()
///
/// the structure pton contains:
/// ea           excess C needed to bring-up to target allometry.
/// eo           excess needed for "other"
/// el           excess needed for leaves
/// er           excess needed for fine roots
/// nuoa         other sapwood conversion
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \todo put in error messages (i.e. division by zero)
///
/// \date 02-08-2010
///

void putonallometry(tstates *st, sparms *p, gparms *gp, puton *pton, int i, double deltaw){

  double r_new=0; // new radius

  double dr=0,demand=0,odemand=0,odr=0,slope=0,intercept=0,nut=0,nuo=0,rhow=0,efl=0,
    eft=0,efr=0,efo=0,denom=0,la_new=0,ra_new=0;

  int j,check;
  height hin;
  radius rin;
  volume v;

  //update subset of status variables
  //st->la=p->f2*st->sa;
  //st->bl=st->la/p->sla;
  //st->ra=p->f1*st->la;
  //st->br=p->rhor*p->rr*st->ra/2.0;
  double bos_new=p->lamdas*st->bts;
  st->boh=p->lamdah*st->bth;
  //  bts_new=st->bts;
  //st->bo=st->bos+st->boh;
  st->bs=st->bts+st->bos;
  st->cs=st->cs+gp->deltat*(pton->eo*deltaw/(p->cgw+deltaw)-
			    st->deltas*(pton->nuoa+p->so)*st->bos); // use old bos
  //st->bos=p->lamdas*st->bts;
  double deltasa=fmaxmacro(0,st->cs/st->bs);

  double excess=st->ex-pton->ea; // excess labile C available after bringing tissues in-line with target allometry.
  double error = 2*fabs(excess*gp->tolerance)+1;	 // initialize error w/ high value
  j = 1;					 	// initialize while loop index
  //printf("cs=%g,bos_new=%g,bs=%g,boh=%g,excess=%9.8f \n",st->cs,bos_new,st->bs,st->boh,excess);
  //printf("pton->eo=%g,pton->nuoa=%g \n", pton->eo,pton->nuoa);
  // Determine new value of r such that "demand" and "excess" are approx. equal.
  check=0;
  while ((error>fmaxmacro(fabs(excess*gp->tolerance), 1e-5)) && (j<1000) && (st->status!=0)){

    if (j==1){
      odr=p->drinit;
      dr=odr;
    }
    else if (j==2){
      odemand=demand;
      if ((odr != 0) && (odemand !=0)){
	slope=odemand/odr;
	odr=dr;
	dr=excess/slope;
      }
      else{
	printf("problem in putonallometry 1 \n");
      }
    } //end if (j==2)
    else{  // if j>2
      if (dr != odr){
	slope=(demand-odemand)/(dr-odr);
      }
      else{
	printf("problem in putonallometry, line 103 \n");
	st->status=0;
      }
      intercept=demand-slope*dr;
      odemand=demand;
      odr=dr;
      if ((slope>0.0000000001) || (error>fmaxmacro(fabs(excess*gp->tolerance),1e-5))){
	dr=(excess-intercept)/slope;
	if (dr<0.0){
	  dr=0.0;
	  check=1;
	}
      }
      else{
	dr=odr;
	check=1;
      }

    } // end else

    // end if, else if, block
    // printf("slope=%g, demand=%g, dr=%9.8f \n",slope,demand,dr);
    // Calculate demand and error based on r(i) and dr:
    if (error>fabs(excess*gp->tolerance)){
      //printf("dr=%g, excess=%g \n",dr,excess);
      r_new=st->r+dr;
        if (r_new < 0){
	//printf("error in putonallometry, line 129 \n");
	//printf("dr=%g, slope=%g, odemand=%g, demand=%g, intercept=%g, j=%d \n",
	//       dr, slope, odemand,demand,intercept,j);
	//printf("sla=%g, hmax=%g, phih=%g, st->r=%g, st->ex=%g, rhomax=%g \n",p->sla,
	//       p->hmax, p->phih, st->r, st->ex, p->rhomax);
	r_new=st->r;
	st->h=p->hmax*(1.0-exp(-p->phih*r_new/p->hmax));
	st->status=0;
	//getchar();
	break;
      }
      // update heights
      if (p->hmax > 0){
	st->h=p->hmax*(1.0-exp(-p->phih*r_new/p->hmax));
      }
      else {
	printf("problem in putonallometry 3 \n");
      }
      st->hh=p->eta*st->h;

      if (r_new < p->swmax){

	st->sw=r_new;
      }
      else{
	st->sw=p->swmax;
      }

      // New calculations based on neiloid, paraboloid, cone taper:
      hin.hB=p->etaB*st->h;
      hin.hC=st->hh;
      hin.H=st->h;
      hin.hBH=gp->BH;

      trunkradii(r_new, &hin, &rin, st);

      trunkvolume(&rin, &hin, st->sw, &v, st);


      // end new radii and volume calculations.
      // new vth minus old vth, divided by old vts
      nut=(v.vth-st->vth)/(st->vts*gp->deltat);
      //printf("nut=%g \n",nut);
      // old bth, old bts, new boh, new bos
      nuo=(p->lamdah*(st->bth+nut*(1.0+deltasa)*st->bts*gp->deltat)-st->boh)/((1.0+deltasa)*bos_new*gp->deltat);

      if (dr<(p->drcrit*gp->deltat)){
	rhow=p->rhomax-((p->rhomax-p->rhomin)/p->drcrit)*dr/gp->deltat;
      }
      else{
	rhow=p->rhomin;
      }

      if (rhow > ((1-p->gammax)/p->gammaw)*exp(10)/(1+exp(10))){
	// if wood density is very close to upper limit (given by deltaw=0), set
	// carbon storage capacity to zero to avoid rounding and computational errors.
	deltaw=0;
      }
      else{  // need to check that rhow != 0
	deltaw=p->gammac*(1.0-p->gammax-p->gammaw*rhow)/rhow;
      }

      st->sa=M_PI*st->sw*(2.0*r_new-st->sw);    //CHECK IF THIS IS REALLY PI
      la_new=p->f2*st->sa;
      ra_new=p->f1*la_new;
      //printf("cgl=%9.8f,deltal=%9.8f,la_new=%9.8f,la=%9.8f ,sla=%g,deltat=%g \n",
	//     p->cgl,p->deltal,la_new,st->la,p->sla,gp->deltat);
      //printf("rnew=%9.8f,sw=%9.8f,f2=%g,sa=%9.8f \n",r_new,st->sw,p->f2,st->sa);
      efl=(p->cgl+p->deltal)*(la_new-st->la)/(p->sla*gp->deltat);
      efr=(p->cgr+p->deltar)*p->rr*p->rhor*(ra_new-st->ra)/(2.0*gp->deltat);
      eft=(p->cgw+deltaw)*((v.vt-st->vt)*rhow-deltasa*nut*st->bts*gp->deltat)/gp->deltat;
      // bos and boh are new.  others are old values
      efo=(p->lamdah*st->bth-st->boh)/(1.0+deltasa) + nut*(p->lamdah-p->lamdas*(1.0+deltasa))*st->bts*gp->deltat +
	p->lamdas*((v.vt-st->vt)*rhow+st->bts)-bos_new;
      efo=efo*((p->cgw+deltaw)/gp->deltat);
      //printf("eft=%g, efo=%g, efr=%g, efl=%g \n",eft,efo,efr,efl);
      demand=efl+efr+eft+efo;
      if (check==1){
	demand=excess;
      }
      error=fabs(demand-excess);
      j=j+1;

    } // end if ((error>abs(excess*gp->tolerance)))
    //     if ((mod(j,50)==0 & j <= 200) | mod(j,500)==0),
    // disp(['PutOnAllometry: # interations in dr root-finding routine = ' int2str(j)]);
    //     end;
    //     if j > 100000,
    //         Jstatus=0;
    //         break;
    //     end;
    // printf("slope=%g, demand=%g,   la_new=%g \n",slope,demand,la_new);
  } //end while loop

  // Set other trunk radii (rB, rC, rBH) given solution for radius (r0):
  //rB(i) = rout.rB;
  //rC(i) = rout.rC;   DG: already updated
  //rBH(i) = rout.rBH;

  // Now that we have the new trunk radius, calculate new state variables:
  st->cs=st->cs+gp->deltat*(eft+efo)*deltaw/(p->cgw+deltaw) - gp->deltat*deltasa*(nut*st->bts+nuo*bos_new);
  // nuo(i)=(nuoa*bos(i-1)+nuo*bos(i))/(bos(i)+bos(i-1));

  // allocation fractions
  st->fl=fmaxmacro(0,(pton->el + efl)/(pton->ea+excess));
  st->fr=fmaxmacro(0,(pton->er + efr)/(pton->ea+excess));
  st->fo=fmaxmacro(0,(pton->eo + efo)/(pton->ea+excess));
  st->ft=fmaxmacro(0,eft/(pton->ea+excess));
  denom=st->fl+st->fr+st->ft+st->fo;  // use error here as temp variable
  st->fl=st->fl/denom;
  st->fr=st->fr/denom;
  st->ft=st->ft/denom;
  st->fo=st->fo/denom;

  // Retranslocation fractions, only due to retranslocation during senescence.
  st->rfl=p->deltal*p->sl*st->bl;
  st->rfr=p->deltar*p->sr*st->br;
  st->rfs=st->deltas*p->so*st->bos;  // old bos
  st->rtrans=st->rfl+st->rfr+st->rfs;    // remove this

  st->rfl=st->rfl/st->rtrans;
  st->rfr=st->rfr/st->rtrans;
  st->rfs=st->rfs/st->rtrans;

  st->bl=la_new/p->sla;            // using la_new
  st->br=p->rhor*p->rr*ra_new/2;   // using ra_new
  st->bth=st->bth+(1.0+deltasa)*nut*st->bts*gp->deltat;
  // v.vt is new value, st->vt is old value
  st->bts=st->bts+rhow*(v.vt-st->vt)-nut*st->bts*gp->deltat;
  st->bt=st->bts+st->bth;
  st->bos=p->lamdas*st->bts;
  st->boh=p->lamdah*st->bth;
  st->bo=st->bos+st->boh;
  st->bs=st->bos+st->bts;
  st->clr=p->deltal*st->bl+p->deltar*st->br;
  //egrow_new=excess;
  //ex_new=excess+ea;

  // updata other state variables
  st->r  = r_new;
  st->rB = rin.rB;
  st->rC = rin.rC;
  st->rBH= rin.rBH;
  st->ra=ra_new;
  st->la=la_new;
  st->vts= v.vts;
  st->vt = v.vt;
  st->vth= v.vth;
  st->egrow=excess;
  st->status=1;


}
