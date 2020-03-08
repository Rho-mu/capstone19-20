/*!
 * \file rebuildstaticstate.c
 *
 * \brief Contains only rebuildstaticstate() function, that is called by
 *        the growthloop().
 *
 * This function should be combined with others for simplicity.
 *  
 * \author Kiona Ogle (translated into C by Darren Gemoets)
 * 
 * \date 1/18/2010
 *
 */

#include "head_files/rebuildstaticstate.h"

///  rebuildstaticstate is used to regrow all senesced tissues.
///
/// \param p            Species parameters (sparms)
/// \param st           tree state parameters (tstates)
/// \param gp           Misc. growthmodel parameters
/// \param rebld        structure containing nuoerb,elerb,ererb,eoerb,erb
/// \param i            iteration value from growth model loop
/// \param deltaw       max storage capacity of newly built "other" sapwood
///
/// rebld structure contains:
///  nuoerb       sapwood conversion rate of "other"
///  erb          labile C needed to rebuild all senesced tissues
///  eoerb        labile C needed to rebuild "other" senesced tissues
///  elerb        labile C needed to rebuild leaf senesced tissues
///  ererb        labile C needed to rebuild fine root senesced tissues
///
/// Returns update st (state variables).
///   
/// \author Kiona Ogle (translated into C by Darren Gemoets)
///
/// \date 12-07-2010
///
void rebuildstaticstate(sparms *p, tstates *st, gparms *gp, rebuild *rebld, int i, double deltaw){

  // Calculate new state variables:
  //nut=0.0;  //ask about this
  
  st->cs=st->cs+gp->deltat*(st->ex-rebld->erb+(rebld->eoerb*deltaw/(p->cgw+deltaw))-
			    st->deltas*(p->so+rebld->nuoerb)*st->bos); 

  // Allocation fractions.
  st->fl=rebld->elerb/rebld->erb;
  st->fr=rebld->ererb/rebld->erb;
  st->fo=rebld->eoerb/rebld->erb;
  st->ft=0.0;

  // Retranslocation fractions due to senescences and draw-down of sapwood stores.
  st->rfl=p->deltal*p->sl*st->bl;
  st->rfr=p->deltar*p->sr*st->br;
  st->rfs=(rebld->erb-st->ex+st->deltas*p->so*st->bos);

  st->rtrans=st->rfl+st->rfr+st->rfs;
  if (st->rtrans != 0){
    st->rfl=st->rfl/st->rtrans;
    st->rfr=st->rfr/st->rtrans;
    st->rfs=st->rfs/st->rtrans;
  }
  else {
    printf("problem in rebuildstaticstate 1 \n");
  }
  
  st->egrow=0.0;
  st->status=1;
}


