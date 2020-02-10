///
/// \file   misc_growth_funcs.h
/// \brief Contains misc. functions for the tree growth model
///        and all the structure variable definitions.
///
///
///
///
/// \author Darren Gemoets
///
/// \date   09-07-2010
///


#ifndef MISC_GROWTH_FUNCS_H
#define MISC_GROWTH_FUNCS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define fminmacro(X, Y) ((X) < (Y) ? (X) : (Y))
#define fmaxmacro(X, Y) ((X) > (Y) ? (X) : (Y))

/// \brief Species level parameters for the tree growth model
///
/// These parameters vary by species.
/// Need to add comments to all variables.  Just a few are noted for
/// now.
///
///
typedef struct{
  double hmax; ///< Max. tree height
  double phih; ///< Slope at H vs. r curve at r=0
  double eta; ///< Relative crown height
  double etaB; ///< Relative height at which trunc transitions from a 
			   ///neiloid to parabolid
  double swmax; ///< Maximum sapwood width
  double lamdas; ///< Proportionality between BT and BO for sapwood
  double lamdah; ///< Proportionality between BT and BO for heart
  double rhomax; ///< Wood density
  double rhomin; ///< Wood density
  double f2; ///< Leaf area to xylem conducting area ratio
  double f1; ///< Fine root area to leaf area ratio
  double gammac; ///< Max. storage capacity of sapwood cellsx
  double gammaw; ///< (Inverse) density of sapwood structural tissue
  double gammax; ///< Xylem conducting area to sapwood area ratio
  double cgl; ///< Construction costs of producing leaves
  double cgr; ///< Construction costs of producing fine roots
  double cgw; ///< Construction costs of producing sapwood
  double deltal; ///< Labile carbon storage capacity of leaves
  double deltar; ///< Labile carbon storage capacity of fine roots
  double sl; ///< Senescence rate of leaves
  double sla; ///< Specific leaf area
  double sr; ///< Senescence rate of fine roots
  double so; ///< Senescence rate of course roots and branches
  double rr; ///< Average fine root radius
  double rhor; ///< Tissue density of fine roots
  double rml; ///< Maintenance respiration rate of leaves
  double rms; ///< Maintenance respiration rate of sapwood
  double rmr; ///< Maintenance respiration rate of fine roots
  double drcrit; ///< ???
  double drinit; ///< radial increment (may vary by tree??)
  double K; ///< Crown light extinction coefficient
  double epsg; ///< Radiation-use-efficiency 
  double M; ///< Maximum relative crown depth
  double alpha; ///< Crown Curvature parameter
  double R0; ///< Maximum potential crown radius of a tree with diameter at breast height of 0 m.
  double R40; ///< Maximum potential crown radius of a tree with diameter at breast height of 0.4 m.
  /* NOTE: f2 = gammax*NEWf2, where NEWf2 is actually the value reported for
   * f2 in the tree growth manuscript (Ogle and Pacala 2009). */
} sparms;


/// \brief Tree specific parameters
///
typedef struct{
  double rinit; ///< Initial radius
  //double drinit; ///< radial increment
  //double drcrit; ///< ???
} tparms;


/// \brief General growthmodel parameters.  Fixed for now, but may change in the future.
///
typedef struct{
  double BH; ///< breast hight.  Fixed at 1.37m
  //double Io; ///< light intensity
  double deltat; ///< timestep in growthmodel.  Fixed at 1/16
  double T; ///< maximum year for growthmodel.  Should be allowed to vary at some point.
  double tolerance; ///< tolerance for numerical solver
} gparms;

/// \brief Leaf area (index??) structures
///
///
typedef struct{
  double tot; ///< ???
  double top; ///< ???
  double bot; ///< ???
} LAindex;

/// \brief Leaf area (index??) structures
///
///
typedef struct{
  double tot; ///< ???
  double top; ///< ???
  double bot; ///< ???
} Larea;


/// structure for forest parameters added by MKF
/// for use in APARcalc
typedef struct{
  double kF;   /// Light extinction coefficient of Forest canopy
  double intF; /// intercept in the equation for logit (relative LAI) vs
               /// relative height.
  double slopeF;   /// Slope in the eqn. for logit (relative LAI) vs
               /// parms = parameter structure
} Forestparms;


/// \brief Height structure for LAIcalc()
/// don't need
///
typedef struct{
  double hB; ///< ???
  double hC; ///< ???
  double H; ///< ???
  double hBH; ///< ???
} height;

/// \brief Radius structure for LAIcalc()
/// don't need
///
typedef struct{
  double r0; ///< ???
  double rB; ///< ???
  double rC; ///< ???,
  double rBH; ///< ???
} radius;

/// \brief Volume structure for LAIcalc() and trunkvolume()
/// don't need
///
typedef struct{
   double vt; ///< total trunk volume
   double vts; ///< volume of trunk sapwood
   double vth; /// volume of trunk heartwood
} volume;


/* These are scalar.  New values will be printed to a file, and any values needed
 * For MCMC will be returned as needed. */
typedef struct{
  double h; ///<  tree height, m
  double hh; ///< height to base of crown, m
  double hC; ///< same as hh
  double hB; ///<??
  double hBH; ///<
  double r; ///< basal trunk radius, m
  double rB; ///< trunk radius at neiloid to paraboloid transition, m
  double rC; ///< trunk radius at paraboloid to cone transition, m
  double rBH; ///< trunk radius at breast height, m
  double sw; ///< sapwood width at base, m
  double vts; ///< trunk sapwood volume, m3
  double vt; ///< total trunk volume, m3
  double vth; ///< trunk heartwood volume, m3
  double sa; ///< sapwood area at base, m2
  double la; ///< total leaf area, m2
  double ra; ///< total fineroot surface area, m2
  double dr; ///< radia increment
  double xa; ///<
  double bl; ///< leaf biomass, g dw
  double br; ///< root biomass, g dw
  double bt; ///< total trunk biomass, g dw
  double bts; ///< trunk sapwood biomass, g dw
  double bth; ///< trunk heartwood biomass, g dw
  double boh; ///< heartwood biomass of c. roots & branches, g dw
  double bos; ///< sapwood biomass of coarse roots & branches, g dw
  double bo; ///< total biomass of c. roots & branches, g dw
  double bs; ///< total sapwood biomass, bos+bts, g dw

  double cs; ///< labile carbon in sapwood, g glucose
  double clr; ///< labile carbin in leaves & fineroots, g gluc
  double fl; ///< relative allocation to leaves
  double fr; ///< relative allocation to fine roots
  double ft; ///< relative allocation to trunk
  double fo; ///< relative allocation to trunk
  double rfl; ///< relative retranslocation from leaves
  double rfr; ///< relative retranslocation from fineroots
  double rfs; ///< relative retranslocation from sapwood

  //%           st.LAtop = LA of target tree above the forest canopy (m2);
  //%           st.LAbot = LA of target tree below the forest canopy (m2);
  //%           st.LAI = total LAI of target tree (m2/m2);
  //%           st.LAItop = LAI of target tree above the forest canopy
  //%           st.LAIbot = LAI of target tree below the forest canopy

  double egrow; ///< excess labile carbon available for growth, g gluc
  double ex; ///< excess labile carbon after maintenance, g gluc
  double rtrans; ///< total labile carbon retranslocated, g gluc
  double light; ///< annual absorbed PAR, mol m2 year1) (UNITS CHANGE?)
  //double t; ///< time, fraction of year?
  double nut; ///< sapwood-to-heartwood conversion in trunk
  double deltas; ///<
  //double cstar; ///<
  double LAI; ///<
  int status; ///< dead or alive
  //int Jstatus;
  //int yr; ///< time, year

  // Note: status/Jstatus = 1 if living, 0 if dead.
} tstates;

//Intermediate structure.  Needed in shrinkingsize.c functions.
typedef struct{
  double bosmax,bosmid,bosmin,bosst,bohst,blst,brst,bosl,bosr,boso;
} bioms;

typedef struct{
  double nuoerb,elerb,ererb,eoerb,erb;
} rebuild;

typedef struct{
  double eo,el,er,ea,nuoa;
} puton;
/// \brief These parameters are a subset of the sparms that are updated via MCMC
///
/// Their meaning is the same as for sparms.
///
///
typedef struct{
  double hmax,phih,sla,rhomax;
} model_parms;

extern void initialize(sparms *p, gparms *gp, tstates *st, double *r0);

extern void trunkradii(double r0, height *h, radius *r, tstates *st);

extern void trunkvolume(radius *r, height *h, double sw, volume *v, tstates *st);


extern void LAIcalc(LAindex *LAI, Larea *LA, double LAtot, double r0,
		    double H, double rBH, sparms *p, gparms *gp, double Hc,
		    tstates *st);

extern void APARcalc(double *APARout, LAindex *LAI, Larea *LA, double eta, double k, double H,
                       double Hc, double FLAI, double Io,
                       Forestparms *ForParms);

extern void acruparms(sparms *p);

extern void pitaparms(sparms *p);

#endif
