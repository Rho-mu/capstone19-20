///
/// \file growthloop.c
/// \brief Main tree growth model call growthloop().  Also contains growthloop_MCMC() wrapper.
///
/// 
/// \param p            Species parameters (sparms)
/// \param gp           gparms
/// \param tp           tree specific parameters (tparms)
/// \param st           tree state parameters (tstates)
/// \param i            iteration value from growth model loop
/// \param deltas       actual labile C stored in sapwood, calc'd in 'growthloop'
/// \param deltaw       max. labile C storage capacity of current sapwood. 
/// \param excess       excess labile carbon, calc'd in 'growthloop'
/// \param deltat       time step
/// \param pnet         total net photosynthesis
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-13-2010
///
///
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
///#include <C:/Program Files/R/local323/include/gsl/gsl_math.h>
///#include <C:/Program Files/R/local323/include/gsl/gsl_vector.h>
///#include <C:/Program Files/R/local323/include/gsl/gsl_blas.h>
///#include <C:/Program Files/R/local323/include/gsl/gsl_matrix.h>

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

/// growthloop() calls: excessgrowingon/off() in excessgrowing.c, putonallometry() 
/// in putonallometry.c, 
/// rebuildingstaticstate() in rebuildingstaticstate.c, and shrinkingsize() in 
/// shrinkingsize.c, initialize() and  LAIcalc() in misc_growth_funcs.c.
///
/// \param p        species specific parameters (sparms)
/// \param gp       Misc. growthmodel parameters
/// \param r0       initial radiusiteration value from growth model loop
/// \param r        array of tree radii (at base, indexed by iteration, not by year)
/// \param h        array of tree heights
/// \param *t       last alive iteration
///
/// Returns update st (state variables).  Calls on functions trunkradii() and 
/// trunkvolume().
///   
/// \todo need rBH array along with r array
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 01-13-2010
/// TODO: need numerical checks here
/// 
void growthloop(sparms *p, gparms *gp, double *r0, int *t, 
	double h[],
	double hh2[],
	double hC2[],
	double hB2[],		
	double hBH2[],		
	double r[],
	double rB2[],
	double rC2[],
	double rBH[],
	double sw2[],
	double vts2[],
	double vt2[],
	double vth2[],
	double sa2[],
	double la2[],
	double ra2[],
	double dr2[],
	double xa2[],
	double bl2[],
	double br2[],
	double bt2[],
	double bts2[],
	double bth2[],
	double boh2[],
	double bos2[],
	double bo2[],
	double bs2[],

	double cs2[],
	double clr2[],
	double fl2[],
	double fr2[],
	double ft2[],
	double fo2[],
	double rfl2[],
	double rfr2[],
	double rfs2[], 
	
	double egrow2[], 
	double ex2[], 
	double rtrans2[],
	double light2[],
	double nut2[],
	double deltas2[],
	double LAI2[], 
	int status2[],
	int errorind[],
	int growth_st[]
){

//, double la[],double LAI[], double egrow[], double ex[], int status[]

    // state variables
    tstates st;
    
    // structure for rebuildstaticstate()
    rebuild rebld;

    // structure for putonallometry()
    puton pton;

    // Below are local variables for growthloop(). 
    double rm,bsstar,pg,rhow,deltaw,f_abs; 
    
    // growthflag is used to select which function call is used. growthflag=1 when 
    // tree is currently on target allometry (so excessgrowingon() is called below)
    // growthflag =0 when tree is off target allometry (other functions are called).
    // i is the index for the growthloop
    int i,growthflag=1;  // tree starts on target 

    // Leaf area index and leaf area.  Only used in LAIcalc().
    LAindex LAI;
    Larea LA; 
   
	//printf(" Initialize start=%d \n",i);  
    //Initialze the state variables.  Returns the state structure st.
    initialize(p,gp,&st,r0); 
	//printf(" Initialize complete=%d \n",i);   

    //Initialize the radius and height arrays to be returned (needed in the MCMC)
    //The if statement was added by MKF for multiple parameter sets on 5/5/2013
	//if(*iout < 1){
		r[0]=r[1]=st.r;  //same as initial radius
    		h[0]=h[1]=st.h;
    		rBH[0]=rBH[1]=st.rBH;
	//}
	//if(*iout > 0){
	//	r[(*lenvars * *iout) + *iout]=r[(*lenvars * *iout) + *iout + 1]=st.r;  //same as initial radius
   	//	h[(*lenvars * *iout) + *iout]=h[(*lenvars * *iout) + *iout + 1]=st.h;
    	//	rBH[(*lenvars * *iout) + *iout]=rBH[(*lenvars * *iout) + *iout + 1]=st.rBH;
	//}
    
    //Compute the LAI of the tree canopy (initially)
    LAIcalc(&LAI,&LA, st.la,  st.r, st.h, st.rBH, p, gp, 0, &st);  //0 is Hc=0

  
  /****************** Start growthloop *****************************************/

  // gp->T number of years, gp->deltat is increment (=1/16)
  for (i = 1; i < (ceil(gp->T/gp->deltat)+1); i++){  //DG: added in plus one  
 
       // If tree died last iteration, then exit program.
       if (st.status==0){
            growth_st[i]=6; 
            //printf(" loop broke at iteration=%d \n",i);
            //printf("p->sla=%g,p->hmax=%g,p->phih=%g \n",p->sla,p->hmax,p->phih);
	    //printf("p->rhomax=%g,p->gammac=%g,p->epsg=%g \n",p->rhomax,p->gammac,p->epsg);
            //printf("p->alpha=%g,p->K=%g \n",p->alpha,p->K);
            //printf("r=%g, init r=%g \n",st.r,r[0]);
         //getchar(); // REMOVE
         break;
        }
      
       // Check for possible division by zero, negative areas, etc.
       if ((st.vts <= 0) || (st.bts == 0) || (p->gammax == 1) || (p->gammaw == 0) || 
           (LAI.tot == 0) || ((1.0+st.deltas)*st.bos*gp->deltat == 0) || ((p->f2*st.sa) <= 0) || 
           (p->sla <= 0) || (st.bs == 0)){
            st.status=0;
            growth_st[i]=6; 
         break;
        }
       // If miniscule amount of labile C and tissues (i.e., less than 0.01 cm2 of
       // leaf area and equivalent bos), tree dies. Use this for "established" trees
       // with r > 0.1 m.
       if ((st.r>=0.1) && (st.bos<(p->lamdas*st.bts/(1000000*p->f2*st.sa))) &&
           (st.bl<(1/(p->sla*1000000))) && (st.cs<=0)){
         st.status=0;
         growth_st[i]=6; 
         //    printf("exit loop due to miniscule amount of labile, iter=%d \n",i); 
         //printf("TreeDies \n");
         break;
        }
    
    // Define light as the total annual amount of absorbed radiation (i.e.,
    // APAR). Compute total PAR absorbed by canopy as incident PAR above
    // canopy (Io) * fraction of PAR absorbed (f_abs) * Canopy area

    f_abs = GSL_MIN(1,GSL_MAX(0,(1-exp(-p->K*LAI.tot))));
      
    // update light value
    st.light = gp->Io*f_abs*(st.la/LAI.tot);
        
    // Determine labile carbon needed to bring all tissues in-line with target allometry (ea),
    // and labile carbon needed to rebuild all senescesed tissues (erb):
    st.deltas=GSL_MAX(0,st.cs/st.bs);
       
    // BELOW: revised version, accounts for relative amounts or woody vs. "living" tissue.
    // First, respiring sapwood due to base-line "structural" biomass of living cells:
            
    bsstar = (1-p->gammaw*st.bts/((1-p->gammax)*st.vts))*st.bs;
    if ((p->gammac > 0) && (st.cs > 0)){
      // respiring sapwood also due to cells with labile carbon:
      bsstar = bsstar + (1-p->gammaw*st.bts/((1-p->gammax)*st.vts))*((st.cs/p->gammac)*(st.bts/st.vts));
     }

    rm=p->rml*st.bl+p->rmr*st.br+p->rms*bsstar;   
             
    // Revised photosynthesis model based on radiation-use efficiency model:
    pg=p->epsg*st.light;   //pg is intermediate variable
    //update excess carbon (st.ex).  
    st.ex=pg-rm+p->deltal*p->sl*st.bl+p->deltar*p->sr*st.br+st.deltas*p->so*st.bos;
     
    rhow=st.bts/st.vts;   //intermediate variable
          if (rhow > ((1-p->gammax)/p->gammaw)*exp(10)/(1+exp(10))){
            // if wood density is very close to upper limit (given by deltaw=0), set
            // carbon storage capacity to zero to avoid rounding and computational errors.
            deltaw=0;
          }
          else{
            deltaw=p->gammac*(1.0-p->gammax-p->gammaw*rhow)/rhow;
          }
        
    //used in putonallometry()
    pton.nuoa=((p->so*gp->deltat-1.0)*st.boh+p->lamdah*st.bth)/((1.0+st.deltas)*st.bos*gp->deltat);
    if (pton.nuoa<0.0){ 
      pton.nuoa=0.0;
     }
       
    //These are used in putonallometry()
    pton.eo=((p->cgw+deltaw)*(((p->so+pton.nuoa)*gp->deltat-1.0)*st.bos+p->lamdas*st.bts))/gp->deltat;
    pton.el=((p->cgl+p->deltal)*(p->sla*(p->sl*gp->deltat-1.0)*st.bl+p->f2*st.sa))/(p->sla*gp->deltat);
    pton.er=((p->cgr+p->deltar)*(2.0*(p->sr*gp->deltat-1.0)*st.br+p->f1*p->f2*p->rr*p->rhor*st.sa))/(2.0*gp->deltat);
    pton.ea=pton.eo+pton.el+pton.er;
       
    //These are used in rebuildstaticstate()
    rebld.nuoerb=p->so*st.boh/((1.0+st.deltas)*st.bos);
    rebld.elerb=(p->cgl+p->deltal)*p->sl*st.bl;
    rebld.ererb=(p->cgr+p->deltar)*p->sr*st.br;gp->T;
    rebld.eoerb=(p->cgw+deltaw)*(p->so+rebld.nuoerb)*st.bos;
    rebld.erb=rebld.elerb+rebld.ererb+rebld.eoerb;
    
        if ((pton.ea<st.ex) && (pton.ea>0.0)){      // enough labile C to grow tree along target allometry.
          if (growthflag==0){       // tree currently off target allometry.
            //printf("PutOnAllometry \n");
            putonallometry(&st,p,gp,&pton,i,deltaw);  //make deltaw *deltaw
            growthflag=1;
            growth_st[i]=3; 
          }
          else{ // growthflag==1.  tree growing along target allometry.
            //printf("ExcessGrowingOn \n");
	    //MKF 04/20/2013 I added errorind to excessgrowing on to catch errors
            excessgrowingon(p,gp,&st,i,growthflag,r, &errorind[i]);
            growthflag=1;
            growth_st[i]=1;
            if (st.nut > 1){
              //printf("Sapwood conversion rate > 1 flag disabled. \n");
              //st.status=0;
              //getchar();
            }
          } //end else
        } // end if ((pton.ea<st.ex) && ...
        else{       // not enough labile C to grow tree on target allometry.
          // TODO: put rebld updates here since they are only used here. 
          //
          growthflag=0;
          if (rebld.erb<st.ex){     // enough labile C to growth tree along reduced allometry.
            //printf("ExcessGrowingOff \n");
            excessgrowingoff(p,gp,&st,i,deltaw,&errorind[i]);
            growth_st[i]=2; 
          }
          else{
            if ((rebld.erb-st.ex) < (st.cs/gp->deltat - st.deltas*(rebld.nuoerb+p->so)*st.bos)){    // enough labile C to rebuild non-trunk tissues. 
              //printf("RebuildStaticState \n");
              rebuildstaticstate(p,&st,gp,&rebld,i,deltaw);
              growth_st[i]=4;
            }
            else{           // Not enough labile C to rebuild tissues, non-trunk compartments shrinking in size.
              //printf("ShrinkingSize \n");
              double pnet=pg-rm;  //used in shrinking size
              shrinkingsize(p,gp,&st,i,&deltaw,&pnet);
              growth_st[i]=5; 
            }
          } 
        } // end outer else   
                
    /* update radius, height, and rBH arrays  */
    r[i]=st.r;
    h[i]=st.h; 

    rBH[i]=st.rBH;
    //deltar[i]=st.dr;
    /* Recalculate st.light */
    LAIcalc(&LAI,&LA, st.la, st.r, st.h, st.rBH, p, gp, 0, &st);
    if (isnan(st.ex) !=0){
      //printf("st.r=%g, st.bos=%g, st.bts=%g \n", st.r,st.bos,st.bts);
      //printf("f2=%g, st.sa=%g, st.bl=%g, sla=%g \n",log(p->f2), st.sa, st.bl, log(p->sla));
      //printf("st->br=%g, st->bl=%g, p->sl=%g, p->sr=%g \n", st.br, st.bl, p->sl, p->sr); 
      //printf("st->bts=%g,st->boh=%g,p->lamdah=%g,st->bth=%g, st->bos=%g \n",
      //       st.bts,st.boh,p->lamdah,st.bth,st.bos);
      //printf("st->cs=%g, gp->deltat=%g, st.deltas=%g, p->so=%g, st->bos=%g \n",
      //       st.cs, gp->deltat, st.deltas, p->so, st.bos);
      errorind[i] = errorind[i] | 1;
      //getchar(); // keep
     }
    if ((r[i]<=0) || ( h[i]<=0) || (rBH[i]<=0) || (isnan(r[i]) !=0) || (isnan(h[i]) !=0)){
      printf("error in growthloop: r or h is negative or nan \n");
      //getchar(); // keep 
      errorind[i] = errorind[i] | 2;
     }

	//la2[i]=st.la;// double
	//LAI2[i]=st.LAI; //double
	//egrow2[i]=st.egrow; //double
	//ex2[i]=st.ex; //double
	//status2[i]=st.status; //int


	hh2[i]=st.hh; //double
	hC2[i]=st.hC; //double
	hB2[i]=st.hB; //double	
	hBH2[i]=st.hBH; //double		
	rB2[i]=st.rB; //double
	rC2[i]=st.rC; //double
	sw2[i]=st.sw; //double
	vts2[i]=st.vts; //double
	vt2[i]=st.vt; //double
	vth2[i]=st.vth; //double
	sa2[i]=st.sa; //double
	la2[i]=st.la; //double
	ra2[i]=st.ra; //double
	dr2[i]=st.dr; //double
	xa2[i]=st.xa; //double
	bl2[i]=st.bl; //double
	br2[i]=st.br; //double
	bt2[i]=st.bt; //double
	bts2[i]=st.bts; //double
	bth2[i]=st.bth; //double
	boh2[i]=st.boh; //double
	bos2[i]=st.bos; //double
	bo2[i]=st.bo; //double
	bs2[i]=st.bs; //double

	cs2[i]=st.cs; //double
	clr2[i]=st.clr; //double
	fl2[i]=st.fl; //double
	fr2[i]=st.fr; //double
	ft2[i]=st.ft; //double
	fo2[i]=st.fo; //double
	rfl2[i]=st.rfl; //double
	rfr2[i]=st.rfr; //double
	rfs2[i]=st.rfs;  //double
	
	egrow2[i]=st.egrow;  //double
	ex2[i]=st.ex;  //double
	rtrans2[i]=st.rtrans; //double
	light2[i]=st.light; //double
	nut2[i]=st.nut; //double
	deltas2[i]=st.deltas; //double
	//LAI2[i]=st.LAI; //double
	LAI2[i]=LAI.tot;
        status2[i]=st.status; //int
	
	//printf("index number in loop: %d \n", (i+(*lenvars * *iout)+ *iout));
	
  } //end the for loop
 
	//printf("This is lenvars * iout %d \nlenvars %d \niout %d\n\n", *lenvars * *iout, *lenvars, *iout);
 
  //*t=(i-1);  // return iteration  
  
} //end growthloop function

