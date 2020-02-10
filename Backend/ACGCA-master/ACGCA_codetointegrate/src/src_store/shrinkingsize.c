/*!
 * \file shrinkingsize.c
 * \brief Contains functions shrinkingsize(), shrinkA() and shrinkB()
 * 
 * \author Kiona Ogle (translated into C by Darren Gemoets)
 * \date 01-13-2010
 *
 */

#include "head_files/shrinkingsize.h"

/*! 
 * shrinkingsize is used to drop extra tissues (other, leaves, fine roots) from the
 * tree to bring the tree in balance with the reduced allometry and/or to free-up
 * enough labile carbon to satisfy a carbon deficit.  It consists of a short series
 * of if-else statements that determine if shrinkingsizeA() or shrinkingsizeB() should
 * be called, or if the tree dies.  
 *
 * \todo Use a sort algorithm from the GSl to find bosmax,bosmid,bosmin.
 * \todo Make biomass struct global to avoid creating/destroying that memory
 *
 * \param p[in]            Species parameters (sparms)
 * \param gp[in]           gparms
 * \param st[out]           tree state parameters (tstates)
 * \param i            iteration value from growth model loop
 * \param deltaw       max. labile C storage capacity of current sapwood. 
 * \param pnet         total net photosynthesis
 *
 * Returns update st (state variables).  
 *   
 * \author Kiona Ogle (translated into C by Darren Gemoets)
 *
 * \date 12-06-2010
 */
void shrinkingsize(sparms *p, gparms *gp, tstates *st, int i, double *deltaw, double *pnet){

    bioms bio;
    
    // Before dropping extra tissues have:
    double nuost=GSL_MAX(0,(p->so*gp->deltat-1.0)*(p->lamdas*st->bts*st->boh-p->lamdah*st->bth*st->bos)/ 
                  (st->bos*(p->lamdah*st->bth+p->lamdas*(1.0+st->deltas)*st->bts)*gp->deltat)); 
    bio.blst =st->bl-p->sl*st->bl*gp->deltat;
    bio.brst =st->br-p->sr*st->br*gp->deltat;
    bio.bohst=st->boh+gp->deltat*(nuost*(1.0+st->deltas)*st->bos-p->so*st->boh);
    bio.bosst=st->bos-(p->so+nuost)*st->bos*gp->deltat;
    double csst =st->cs+gp->deltat*(st->ex-st->deltas*(nuost+p->so)*st->bos);
    
    // Determine BOS equivalents:
    bio.bosl=bio.blst*p->sla*p->lamdas*st->bts/(p->f2*st->sa);
    bio.bosr=bio.brst*2.0*p->lamdas*st->bts/(p->rhor*p->rr*p->f1*p->f2*st->sa);
    bio.boso=bio.bosst;
      
  // Now determine if tree is in a non-deficit (4A) or deficit (4B) condition:
  if (csst>0.0){
      // COULD DO THIS USING GSL_RANK FUNCTIONS
      bio.bosmax=GSL_MAX(GSL_MAX(bio.bosl,bio.bosr),bio.boso);  
      bio.bosmin=GSL_MIN(GSL_MIN(bio.bosl,bio.bosr),bio.boso); 
      
      if ((bio.bosmin < bio.boso) && (bio.bosmax > bio.boso)){
        bio.bosmid=bio.boso;
      }
      else if ((bio.bosmin < bio.bosl) && (bio.bosmax > bio.bosl)){
        bio.bosmid=bio.bosl;
      }
      else{
        bio.bosmid=bio.bosr;
      }
    shrinkingsizeA(p,st,gp,i,deltaw,&bio,&csst,pnet);
    //printf("ShrinkingSizeA \n");
  }
  else if ((csst+p->deltal*bio.blst+p->deltar*bio.brst)>0.0){
    shrinkingsizeB(p,st,gp,i,deltaw,&bio,&csst,pnet);
    //printf("ShrinkingSizeB \n");
  }
  else { // tree dies   
    st->status=0;
  }
  
}  //End shrinkingsize() function


/*! shrinkingsizeA is used to drop extra tissues (other, leaves, fine roots) from the
 * tree to bring the tree in balance with the reduced allometry (not enough labile
 * C available to grow new tissues).  It consists of a series of conditional statements.
 * The first set determines of only ``bosmax is used".  Then if that is not true, it
 * determines of ``bosmid is used".  If not, then only bosmin is used.
 *
 *
 * \param p[in]            Species parameters (sparms)
 * \param st[out]           tree state parameters (tstates)
 * \param gp[in]           gparms
 * \param i[in]            iteration value from growth model loop
 * \param deltaw       max. labile C storage capacity of current sapwood. 
 * \param bio      structure of temporary biomass calculations
 * \param csst         temporary labile C in sapwood, to be used for growth and satisfying deficit
 * \param pnet         total net photosynthesis
 *
 * Returns update st (state variables).  Called by shrinkingsize()
 *   
 * \todo division by zero checks
 * 
 * \author Kiona Ogle (translated into C by Darren Gemoets)
 *
 * \date 12-07-2010
 */
void shrinkingsizeA(sparms *p, tstates *st, gparms *gp, int i,
                    double *deltaw, bioms *bio, double *csst,
                    double *pnet){

  //local variables
  double eo=0,el=0,er=0,sigo=0,sigr=0,sigl=0,nuoht=0,denom;

  // Determine if able to bring all tissues up to "largest" tissue (i.e., BOSmax):
  // Initial calculation.  Only one is non true since bosmax is one of either boso, 
  // bosl or bosr.  

    if (bio->boso < bio->bosmax){
      eo=(p->cgw+(*deltaw))*(bio->bosmax*(p->lamdah*st->bth+p->lamdas*st->bts)-p->lamdas*st->bts*(bio->bosst+bio->bohst))/
        (p->lamdas*st->bts*gp->deltat);
    } 
    
    if (bio->bosl < bio->bosmax){
      el=(p->cgl+p->deltal)*(bio->bosmax*p->f2*st->sa-p->lamdas*p->sla*st->bts*bio->blst)/
        (p->lamdas*p->sla*st->bts*gp->deltat);
    } 

    if (bio->bosr < bio->bosmax){
      er=(p->cgr+p->deltar)*(bio->bosmax*p->f1*p->f2*st->sa*p->rr*p->rhor-2.0*p->lamdas*st->bts*bio->brst)/
        (2.0*p->lamdas*st->bts*gp->deltat);
    } 
   
  
  
  // end this series of if statements
  // begin if-else. If first if is true, this is all that is done.  st->bos, st->rfl, st->rfr are
  // that are updated 
      
        if(*csst > ((eo+el+er)*gp->deltat)){ // enough stored C to bring all tissues in-line with BOSmax. 
          st->bos=(2.0*st->bts*p->sla*p->lamdas)*
            (*csst+(p->cgl+p->deltal)*bio->blst+(p->cgw+*deltaw)*(bio->bosst+bio->bohst)+(p->cgr+p->deltar)*bio->brst)/
            (2.0*p->sla*(p->cgw+*deltaw)*(st->bth*p->lamdah+st->bts*p->lamdas)+
             p->f2*st->sa*(2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->sla*p->rhor*(p->cgr+p->deltar)));
          
          // Recalculate labile C allocated to growth of each tissue.
          er=(p->cgr+p->deltar)*(st->bos*p->f1*p->f2*p->rr*p->rhor*st->sa-2.0*st->bts*p->lamdas*bio->brst)/
            (2.0*st->bts*p->lamdas*gp->deltat);
          el=(p->cgl+p->deltal)*(st->bos*p->f2*st->sa-st->bts*p->sla*p->lamdas*bio->blst)/(st->bts*p->sla*p->lamdas*gp->deltat);
          eo=(*csst/gp->deltat)-el-er;
          
          // Parts of retranslocation fractions:
          st->rfl=p->deltal*p->sl*st->bl*gp->deltat;  //need to be carefull here.  old stored as new
          st->rfr=p->deltar*p->sr*st->br*gp->deltat;  //
        }  //end if. 
                      
      else{   // grow BOSmid & BOSmin OR grow only BOSmin.
        // set all "required excess C" and "excess" senescence at zero.
        eo=0.0;
        el=0.0;
        er=0.0;
        sigo=0.0;
        sigr=0.0;
        sigl=0.0;
        nuoht=0.0;
        
        // being series of three if statements.  Either boso, bosl, or bosr equals bosmid.  So only one of 
        // first set ifs is true
        if (bio->boso < bio->bosmid){
          eo=(p->cgw+*deltaw)*(bio->bosmid*(p->lamdah*st->bth+p->lamdas*st->bts)-
                               st->bts*p->lamdas*(bio->bosst+bio->bohst))/(st->bts*p->lamdas*gp->deltat);
          nuoht=(bio->bosmid*st->bth*p->lamdah-st->bts*p->lamdas*bio->bohst)/(p->lamdas*st->bts*bio->bosst*gp->deltat);
        }
       
        if (bio->bosl < bio->bosmid){
          el=(p->cgl+p->deltal)*(bio->bosmid*p->f2*st->sa-st->bts*p->sla*p->lamdas*bio->blst)/
            (st->bts*p->sla*p->lamdas*gp->deltat);
        }
       
        if (bio->bosr < bio->bosmid){
          er=(p->cgr+p->deltar)*(bio->bosmid*p->f1*p->f2*p->rr*p->rhor*st->sa-
                                 2.0*st->bts*p->lamdas*bio->brst)/(2.0*st->bts*p->lamdas*gp->deltat);
        }
        // end series of ifs
        // begin next series of three if statements.  Again, only one is true. 
        if (bio->boso > bio->bosmid){
          sigo=(1.0-bio->bosmid*(st->bth*p->lamdah+st->bts*p->lamdas)/
                (p->lamdas*st->bts*(bio->bosst+bio->bohst)))/gp->deltat;
          nuoht=bio->bosmid*(st->bth*p->lamdah*bio->bosst-st->bts*p->lamdas*bio->bohst)/
            (p->lamdas*st->bts*bio->bosst*(bio->bosst+bio->bohst)*gp->deltat);
        }
        
        if (bio->bosl > bio->bosmid){
          sigl=(1.0-bio->bosmid*p->f2*st->sa/(p->lamdas*p->sla*st->bts*bio->blst))/gp->deltat;
        }
        
        if (bio->bosr > bio->bosmid){
          sigr=(1.0-bio->bosmid*p->f1*p->f2*p->rhor*p->rr*st->sa/(2.0*p->lamdas*st->bts*bio->brst))/gp->deltat;
        }
        // end series of three if statements

    if (*csst+(p->deltal*sigl*bio->blst+p->deltar*sigr*bio->brst)*gp->deltat > 
            (eo+el+er)*gp->deltat){  // able to bring tissues in-line with BOSmid.

          // begin series of three if statements.  Agian, only one is true
          if (bio->bosl > bio->bosmid){  // too many leaves, drop leaves, growth other & roots.
            st->bos=2.0*st->bts*p->sla*p->lamdas*
              (*csst+p->deltal*bio->blst+(p->cgw+*deltaw)*(bio->bohst+bio->bosst)+(p->cgr+p->deltar)*bio->brst)/
              (2.0*p->sla*(p->cgw+*deltaw)*(st->bth*p->lamdah+st->bts*p->lamdas)+
               p->f2*st->sa*(2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar)));
            sigl=(st->bts*p->sla*p->lamdas*bio->blst-st->bos*p->f2*st->sa)/(st->bts*p->sla*p->lamdas*bio->blst*gp->deltat);
            er=(p->cgr+p->deltar)*(st->bos*p->f1*p->f2*p->rr*p->rhor*st->sa-2.0*st->bts*p->lamdas*bio->brst)/
              (2.0*st->bts*p->lamdas*gp->deltat);
            eo=(*csst/gp->deltat)-er+p->deltal*sigl*bio->blst;
             
            // Part of retranslocation fractions.
            st->rfl=p->deltal*(p->sl*st->bl+sigl*bio->blst)*gp->deltat;  
            st->rfr=p->deltar*p->sr*st->br*gp->deltat;
             
          }
          
          if (bio->bosr > bio->bosmid){  // too many roots, drop roots, grow other & leaves.
            st->bos=2.0*st->bts*p->sla*p->lamdas*
              (*csst+p->deltar*bio->brst+(p->cgw+*deltaw)*(bio->bohst+bio->bosst)+(p->cgl+p->deltal)*bio->blst)/
              (2.0*p->sla*(p->cgw+*deltaw)*(st->bth*p->lamdah+st->bts*p->lamdas)+
               p->f2*st->sa*(2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->rhor*p->sla*p->deltar));
            sigr=(2.0-(st->bos*p->f1*p->f2*p->rr*p->rhor*st->sa)/(st->bts*p->lamdas*bio->brst))/(2.0*gp->deltat);
            el=(p->cgl+p->deltal)*(st->bos*p->f2*st->sa-st->bts*p->sla*p->lamdas*bio->blst)/(st->bts*p->sla*p->lamdas*gp->deltat);
            eo=(*csst/gp->deltat)-el+p->deltar*sigr*bio->brst;
           
            // Part of retranslocation fractions. need to look at this too
            st->rfl=p->deltal*p->sl*st->bl*gp->deltat;  //careful here too
            st->rfr=p->deltar*(p->sr*st->br+sigr*bio->brst)*gp->deltat;
          }
          
          if (bio->boso > bio->bosmid){  // too much BOS, drop "other", grow roots & leaves.
            st->bos=2.0*st->bts*p->sla*p->lamdas*
              (*csst+(p->cgr+p->deltar)*bio->brst+(p->cgl+p->deltal)*bio->blst)/
              (p->f2*st->sa*(2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->sla*p->rhor*(p->cgr+p->deltar)));
            //    Below, don't think nuoht & sigo are needed, and the denominator in 
            // sigo is equal to zero.  This is from matlab version
            //   
            //   nuoht=(2.0*sla*(bth(i-1)*lamdah*bosst-st->bts(i-1)*p->lamdas*bohst)*...
            //      (csst+(cgl+deltal)*blst+(cgr+deltar)*brst))/...
            //      (f2*sa(i-1)*gp->deltat*(2.0*(cgl+deltal)+...
            //      f1*p->rr*rhor*sla*(cgr+deltar))*bosst*(bosst+bohst));
            //   sigo=(bts(i-1)*lamdas*bohst+bosst*(nuoht*(bth(i-1)*lamdah+bts(i-1)*lamdas)*...
            //      deltat-bth(i-1)*lamdah))/...
            //      ((bts(i-1)*lamdas*bohst-bth(i-1)*lamdah*bosst)*deltat);
            el=(p->cgl+p->deltal)*(st->bos*p->f2*st->sa-st->bts*p->sla*p->lamdas*bio->blst)/
              (st->bts*p->sla*p->lamdas*gp->deltat);
            eo=(*csst/gp->deltat)-el;
             
            // Part of retranslocation fractions.
            st->rfl=p->deltal*p->sl*st->bl*gp->deltat;  //carefull here 
            st->rfr=p->deltar*p->sr*st->br*gp->deltat;
          }
              // end series of three if statements
    }  
         
      else{  // can only grow BOSmin tissues, drop others.
        
        // set all "excess labile C" and "excess" senescence to zero.
        eo=0.0;
        el=0.0;
        er=0.0;
        sigo=0.0;
        sigr=0.0;
        sigl=0.0;
        nuoht=0.0;
        
        // Begin series of three if statements.  Only one is true
        if (bio->bosr < bio->bosmid){ // grow roots, drop leaves and other.
          st->bos=(2.0*st->bts*p->sla*p->lamdas*(*csst+p->deltal*bio->blst+(p->cgr+p->deltar)*bio->brst))/
            (p->f2*st->sa*(2.0*p->deltal+p->f1*p->rr*p->sla*p->rhor*(p->cgr+p->deltar)));
          nuoht=(2.0*p->sla*(st->bth*p->lamdah*bio->bosst-st->bts*p->lamdas*bio->bohst)*
                 (*csst+p->deltal*bio->blst+(p->cgr+p->deltar)*bio->brst))/
            (p->f2*st->sa*gp->deltat*(2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar))*bio->bosst*(bio->bosst+bio->bohst));
          sigo=(st->bts*p->lamdas*(bio->bohst+nuoht*bio->bosst*gp->deltat)-st->bos*st->bth*p->lamdah)/
            (st->bts*p->lamdas*bio->bohst*gp->deltat);
          sigl=(p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar)*bio->blst-2.0*(*csst+(p->cgr+p->deltar)*bio->brst))/
            ((2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar))*bio->blst*gp->deltat);
          er=((p->cgr+p->deltar)*(p->f1*p->rr*p->rhor*p->sla*(*csst+p->deltal*bio->blst)-2.0*p->deltal*bio->brst))/
            ((2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar))*gp->deltat);
          
          // Part of retranslocation fractions.
          st->rfl=p->deltal*(p->sl*st->bl+sigl*bio->blst)*gp->deltat;  //need to fix this
          st->rfr=p->deltar*p->sr*st->br*gp->deltat;
        }
        
        if (bio->bosl < bio->bosmid){ // grow leaves, drop roots and other.
          st->bos=(2.0*st->bts*p->sla*p->lamdas*(*csst+p->deltar*bio->brst+(p->cgl+p->deltal)*bio->blst))/
            (p->f2*st->sa*(2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->sla*p->rhor*p->deltar));
          nuoht=(2.0*p->sla*(st->bth*p->lamdah*bio->bosst-st->bts*p->lamdas*bio->bohst)*
                 (*csst+p->deltar*bio->brst+(p->cgl+p->deltal)*bio->blst))/
            (p->f2*st->sa*gp->deltat*(2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->rhor*p->sla*p->deltar)*bio->bosst*(bio->bosst+bio->bohst)); 
          sigo=(st->bts*p->lamdas*(bio->bohst+bio->bosst*nuoht*gp->deltat)-st->bos*st->bth*p->lamdah)/
            (st->bts*p->lamdas*bio->bohst*gp->deltat);
          el=((p->cgl+p->deltal)*(2.0*(*csst+p->deltar*bio->brst)-p->f1*p->rr*p->rhor*p->sla*p->deltar*bio->blst))/
            ((2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->rhor*p->sla*p->deltar)*gp->deltat);
          sigr=(el*gp->deltat-*csst)/(p->deltar*bio->brst*gp->deltat);
          
          // Part of retranslocation fractions.
          st->rfl=p->deltal*p->sl*st->bl*gp->deltat;  //carefull here
          st->rfr=p->deltar*(p->sr*st->br+sigr*bio->brst)*gp->deltat;
        }
        
        if (bio->boso < bio->bosmid){ // grow other, drop roots and leaves.
          st->bos=(2.0*st->bts*p->sla*p->lamdas*
                   (*csst+p->deltar*bio->brst+p->deltal*bio->blst+(p->cgw+*deltaw)*(bio->bohst+bio->bosst)))/
            (2.0*p->sla*(p->cgw+*deltaw)*(st->bth*p->lamdah+st->bts*p->lamdas)+
             p->f2*st->sa*(2.0*p->deltal+p->f1*p->rr*p->sla*p->rhor*p->deltar));
          nuoht=(st->bos*st->bth*p->lamdah-st->bts*p->lamdas*bio->bohst)/(st->bts*p->lamdas*bio->bosst*gp->deltat);
          sigl=(st->bts*p->sla*p->lamdas*bio->blst-st->bos*p->f2*st->sa)/(st->bts*p->sla*p->lamdas*bio->blst*gp->deltat);
          sigr=(2.0*st->bts*p->lamdas*bio->brst-st->bos*p->f1*p->f2*p->rr*p->rhor*st->sa)/
            (2.0*st->bts*p->lamdas*bio->brst*gp->deltat);
          eo=(*csst/gp->deltat)+p->deltal*sigl*bio->blst+p->deltar*sigr*bio->brst;
          
          // Part of retranslocation fractions.
          st->rfl=p->deltal*(p->sl*st->bl+sigl*bio->blst)*gp->deltat;  //need to fix this
          st->rfr=p->deltar*(p->sr*st->br+sigr*bio->brst)*gp->deltat;
        }
      } //end else
    } //end outermost else   
   
    // Allocation fractions:
    denom=er+el+eo;
    st->ft=0.0;
    st->fr=er/denom;
    st->fl=el/denom;
    st->fo=eo/denom;
    

  
  st->rfs = GSL_MIN(st->cs,denom*gp->deltat - st->rfl - st->rfr - *pnet*gp->deltat);
 
  st->bl=p->f2*st->sa*st->bos/(p->sla*p->lamdas*st->bts);
  st->br=p->f1*p->f2*p->rhor*p->rr*st->sa*st->bos/(p->lamdas*2.0*st->bts);
    //Update new states
    st->rtrans=st->rfl+st->rfr+st->rfs;
    st->rfl=st->rfl/st->rtrans;
    st->rfr=st->rfr/st->rtrans;
    st->rfs=st->rfs/st->rtrans;
    st->rtrans = st->rtrans/gp->deltat;

    //st->bos=nbos;
    st->boh=p->lamdah*st->bth*st->bos/(p->lamdas*st->bts);
    
    st->la=p->sla*st->bl;
    st->ra=p->f1*st->la;
    st->bo=st->bos+st->boh;
    st->bs=st->bos+st->bts;
    st->cs=eo*(*deltaw)*gp->deltat/(p->cgw+(*deltaw));
    st->clr=p->deltal*st->bl+p->deltar*st->br;
    st->egrow=0.0;
    //st->ex=excess;
    st->status=1;
  
   
} 



///* shrinkingsizeB is used to drop extra tissues (other, leaves, fine roots) from the
/// tree to bring the tree in balance with the reduced allometry AND to satisfy
/// carbon deficit.
///
/// \param p            Species parameters (sparms)
/// \param st           tree state parameters (tstates)
/// \param gp           Misc. growthmodel parameters
/// \param i            iteration value from growth model loop
/// \param *deltaw      max. labile C storage capacity of current sapwood. 
/// \param bio          structure of temporary biomass calculations
/// \param csst         temporary labile C in sapwood, to be used for growth and satisfying deficit
/// \param pnet         total net photosynthesis
///
/// Returns update st (state variables).  Called by shrinkingsize()
///   
/// 
///
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 12-07-2010
///
void shrinkingsizeB(sparms *p, tstates *st, gparms *gp, int i,  
                    double *deltaw, bioms *bio, double *csst, 
                    double *pnet){

  // set all "excess" senescence at zero.
  double eo=0,el=0,er=0,ce,sigr=0,sigl=0,Al,Ar,nuoht=0,denom, new_bl, new_br;
 
  // if-else block
  if (bio->bosr > bio->bosl){
    sigr=(2.0*bio->brst-p->f1*p->rr*p->rhor*p->sla*bio->blst)/(2.0*bio->brst*gp->deltat);
    ce=p->deltar*sigr*bio->brst*gp->deltat;
  }
  else{
    sigl=(p->f1*p->rr*p->rhor*p->sla*bio->blst-2.0*bio->brst)/(p->f1*p->rr*p->rhor*p->sla*bio->blst*gp->deltat);
    ce=p->deltal*sigl*bio->blst*gp->deltat;
  }
  // end if-else block

  if ((*csst+ce)>0.0){ // dropping leaves (roots) to meet target allometry satisfies deficit.
    //eo=0.0;
    if (bio->bosr > bio->bosl){ // drop roots, grow leaves.
      el=((p->cgl+p->deltal)*(2.0*(*csst+p->deltar*bio->brst)-p->f1*p->rr*p->rhor*p->sla*p->deltar*bio->blst))/
        (gp->deltat*(2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->rhor*p->sla*p->deltar));
      sigr=(2.0*(p->cgl+p->deltal)*bio->brst-p->f1*p->rr*p->rhor*p->sla*(*csst+(p->cgl+p->deltal)*bio->blst))/
        ((2.0*(p->cgl+p->deltal)+p->f1*p->rr*p->rhor*p->sla*p->deltar)*bio->brst*gp->deltat);
      //er=0.0;
      sigl=0.0;
    }
    else{   // drop leaves, grow roots.
      er=((p->cgr+p->deltar)*(p->f1*p->rr*p->rhor*p->sla*(*csst+p->deltal*bio->blst)-2.0*p->deltal*bio->brst))/
        (gp->deltat*(2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar)));
      sigl=(p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar)*bio->blst-2.0*(*csst+(p->cgr+p->deltar)*bio->brst))/
        ((2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*(p->cgr+p->deltar))*bio->blst*gp->deltat);
      sigr=0.0;
      //el=0.0;
    }
   
    // Calculate temp new BL and BR, before determining new BOS.
    new_bl=bio->blst+((el/(p->cgl+p->deltal))-sigl*bio->blst)*gp->deltat;
    new_br=bio->brst+((er/(p->cgr+p->deltar))-sigr*bio->brst)*gp->deltat;
  }  //end ((*csst+ce)>0.0)
  else{ // *csst+ce<0, must drop both leaves and roots to meet target allometry and satisfy deficit.
    //eo=0.0;
    //el=0.0;
    //er=0.0;
    sigl=(p->f1*p->rr*p->sla*p->deltar*p->rhor*bio->blst-2.0*(*csst+p->deltar*bio->brst))/
      ((2.0*p->deltal+p->f1*p->rr*p->sla*p->deltar*p->rhor)*bio->blst*gp->deltat);
    sigr=(2.0*p->deltal*bio->brst-p->f1*p->rr*p->rhor*p->sla*(*csst+p->deltal*bio->blst))/
      ((2.0*p->deltal+p->f1*p->rr*p->rhor*p->sla*p->deltar)*bio->brst*gp->deltat);
    new_bl=bio->blst-sigl*bio->blst*gp->deltat;
    new_br=bio->brst-sigr*bio->brst*gp->deltat;
  } // end if-else block

  // Now need to determine BOS.
  st->bos=new_bl*p->sla*p->lamdas*st->bts/(p->f2*st->sa);  // bos that matches new_bl; bos if need to drop bos.
 
  //eo=0.0;
  if(bio->bosst < st->bos){ // too little BOS, drop extra BL and BR & build BOS.
    st->bos=2*st->bts*p->sla*p->lamdas*(p->deltal*new_bl+p->deltar*new_br+(p->cgw+*deltaw)*(bio->bohst+bio->bosst))/
      (2*p->sla*(p->cgw+*deltaw)*(st->bth*p->lamdah+st->bts*p->lamdas)+
       p->f2*st->sa*(2*p->deltal+p->f1*p->rr*p->sla*p->deltar*p->rhor));
    nuoht=(st->bos*st->bth*p->lamdah-st->bts*p->lamdas*bio->bohst)/(st->bts*p->lamdas*bio->bosst*gp->deltat);
    sigl=(1-st->bos*p->f2*st->sa/(st->bts*p->sla*p->lamdas*new_bl))/gp->deltat;
    sigr=(1-st->bos*p->f1*p->f2*p->rr*st->sa*p->rhor/(2*st->bts*p->lamdas*new_br))/gp->deltat;
    new_bl=p->f2*st->sa*st->bos/(p->sla*p->lamdas*st->bts);
    new_br=p->f1*p->f2*p->rhor*p->rr*st->sa*st->bos/(p->lamdas*2.0*st->bts);
    eo=p->deltal*sigl*new_bl+p->deltar*sigr*new_br;
  }

  // Recalculate labile carbon associated with allocation and retranslocation
  // to/from leaves and fine roots:
  Al=new_bl-bio->blst;
  Ar=new_br-bio->brst;

  if (Al <= 0){
    el=0.0;
    st->rfl=p->deltal*(p->sl*st->bl*gp->deltat-Al);
  }
  else{
    el=Al*(p->cgl+p->deltal)/gp->deltat;
    st->rfl=p->deltal*p->sl*st->bl*gp->deltat;
  }
  if (Ar <= 0){
    er=0.0;
    st->rfr=p->deltar*(p->sr*st->br*gp->deltat-Ar);
  }
  else{
    er=Ar*(p->cgr+p->deltar)/gp->deltat;
    st->rfr=p->deltar*p->sr*st->br*gp->deltat;
  }

    // Allocation fractions.
    denom=er+el+eo;
    //printf("denom=%g \n",denom);
    st->ft=0.0;
    if(denom==0.0){
      st->fr=0.0;
      st->fl=0.0;
      st->fo=0.0;
    }
    else{
      st->fr=er/denom;
      st->fl=el/denom;
      st->fo=eo/denom;
    }

  
  // Retranslocation fractions, only due to retranslocation during senescence.
  // Correct rfs, accounts for fact that all sapwood labile C used-up. (But,
  // will give retrans > 0 even if Cs = 0!
  // rfs(i)=max(0,csst)+st->deltas*p->so*bos(i-1)*deltat;
  // revised: rfs = total demand - retranslocation from leaves and fine roots
  // - net photsynthetic input (Pg - Rm):
  st->rfs = GSL_MIN(st->cs,denom*gp->deltat - st->rfl - st->rfr - (*pnet)*gp->deltat);
  if (st->cs < (denom*gp->deltat - st->rfl - st->rfr - (*pnet)*gp->deltat)){
    //printf("retranslocation does not balance \n");
  }

  st->bl=new_bl;
  st->br=new_br;
    //Update new states
    st->rtrans=st->rfl+st->rfr+st->rfs;
    st->rfl=st->rfl/st->rtrans;
    st->rfr=st->rfr/st->rtrans;
    st->rfs=st->rfs/st->rtrans;
    st->rtrans = st->rtrans/gp->deltat;

    //st->bos=nbos;
    st->boh=p->lamdah*st->bth*st->bos/(p->lamdas*st->bts);

    
    st->la=p->sla*st->bl;
    st->ra=p->f1*st->la;
    st->bo=st->bos+st->boh;
    st->bs=st->bos+st->bts;
    st->cs=eo*(*deltaw)*gp->deltat/(p->cgw+(*deltaw));
    st->clr=p->deltal*st->bl+p->deltar*st->br;
    st->egrow=0.0;
    //st->ex=excess;
    st->status=1;
  


} // end shrinkingsizeB

