#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Only define M_PI if it is not defined already
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

///////////////////////////////////////////////////////////////////////////////
// Translated from Kiona Ogle's Matlab code to C by Michael Fell March 13, 2018
// 
// INPUTS:
//   LAtot = total leaf area of target tree
//   rBH = trunk radius at breast height
//   r0 = trunk radius at base pf tree (also referred to as 'r')
//   H = tree height
//   p = structure with growth model parameters
//   Hc = height of forest canopy
//
// OUTPUTS:
//   lai->tot = tree's leaf area index (if Hc is missing, scalar with total LAI)
//   lai->top
//   lai->bot
//
///////////////////////////////////////////////////////////////////////////////

// NOTE: once done this can be moved to the header file
typedef struct{
	double LAI;    // tree's leaf area index (if Hc is missing, scalar with 
			       //total LAI
	double LAItot; // total LAI of target tree;
	double LAItop; // LAI of target tree above the forest canopy (LAItop)
	double LAIbot; // LAI of target tree below the forest canopy (LAIbot)
	
	double LA;     // tree's leaf area (if Hc is missing, scalar with total LA)
	double LAtot;  // total leaf area (LA) of target tree (LAtot)
	double LAtop;  // LA of target tree above the forest canopy (LAtop) 
	double LAbot;  // LA of target tree below the forest canopy (LAbot)
} gap;

// this is temporary and will be removed in the final version
typedef struct{
	double R0;
	double R40;
	double phih;
	double hmax;
	double eta;
	double M;
	double alpha;
} sparms;
// END OF STRUCTURE TO REMOVE

int main(int argc, char **argv){
	// If the Forest canopy is 0m then this function will stop and return the
	// values of LAI and LA used when calling the function.
	
	// This section can be removed once complete
	printf("test %i\n", argc);
	for(int i=1; i < argc; i++){
		printf("argv %s\n", argv[i]);
	}
	
	double LAItot;
	double rBH;
	double r0;
	double H;
	double Hc;
	double BH = 1.37;
	
	sparms p;
	p.R0 = 1.909;
	p.R40 = 5.592;
	p.phih = 263;
	p.hmax = 27.5;
	p.eta = 0.64;
	p.M = 0.95;
	p.alpha = 0.365;
	
	gap tree;
	
	
	// END OF SECTION TO REMOVE
	
	// Compute maximum radius of tree's crown (Rmax) based on: trunk diameter
	// (diam) in cm; canopy maximum potential radius (Rmax) in m; canopy area
	// (CanArea) at base of canopy in m^2. Model modified from Purves et al.
	// PLOS.
	
	
	// Declare gap function variables
	double diam;
	double Rmax;
	double r0star;
	double CAtot; // Total projected crown area of tree at base of crown
	double Vtot; // Total volume of tree's crown
	double LAItot; // Total leaf area index of tree at base of crown
	
	if(rBH > 0){
		diam = 2*rBH*100; // convert rBH to cm
		Rmax = p.R0 + (p.R40 - p.R0)*(diam/40);
	}else{
		diam = 2*r0*100;
		r0star = -(p.hmax/p.phih)*log((p.hmax-BH)/p.hmax);
		Rmax = (p.R0/r0star)*r0;
	}
	
	// Total projected crown area of tree at base of crown
	CAtot = M_PI*(pow(Rmax, 2))*(pow(((1-p.eta)/p.M),(2*p.alpha));
	// Total volume of tree's crown
	Vtot = CAtot*(((1-p.eta)*H)/(1+2*p.alpha));
	// Total leaf area index of tree's crown
	LAItot = LAtot/CAtot;
	
	// The Matlab version checked the number in inputs
	if(Hc == 0){
		// Forest canopy height is 0m, so return tree's LAI and LA
		tree.LAI = tree.LAItot;
		tree.LA = tree.LAtot;
	}else{
		// If given forest canopy height, compute tree's LAI and LA above (top)
		// and below (bot) the height of the forest canopy
		
		// If tree's crown is taller than forest canopy
		if(){
		}
	}
	
} // End of main
