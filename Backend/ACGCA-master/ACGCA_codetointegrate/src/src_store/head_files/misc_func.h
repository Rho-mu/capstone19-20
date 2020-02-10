///
/// \file   misc_func.h
/// \brief Contains misc. MCMC functions and all the structure variable definitions.    
/// 
/// 
///
///
/// \author Darren Gemoets
///
/// \date   06-03-2010
///

#ifndef MISC_FUNC_H
#define MISC_FUNC_H
/*
#include <C:/Program Files/R/local323/include/gsl/gsl_rng.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_randist.h>
*/
#include <string.h>
/*
#include <C:/Program Files/R/local323/include/gsl/gsl_math.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_blas.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_sf_gamma.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_linalg.h>
#include <C:/Program Files/R/local323/include/gsl/gsl_cdf.h>
*/

/* This function generates a random double value from a left-truncated normal.  mu and sigma are the mean  
 * and standard devation before truncation, and trunc is the left truncation point. r is the randnom 
 * seed required for the GSL random pdf. */

//extern double ran_truncnorm(const gsl_rng * r, double mu, double sig, double trunc);


/* This function generates a random double value from a normal pdf times a left-truncated pdf.  norm_mu and 
 * norm_sigma are the mean and standard deviation for the normal, and trunc_mu and trunc_sigma for the 
 * truncated normal before truncation. trunc is the left-truncation point, and r is the random seed
 * needed for the GSL functions */

//extern double ran_norm_truncnorm(const gsl_rng * r, double norm_mu, double norm_sigma, 
//	double trunc_mu, double trunc_sigma, double trunc);


//extern double ran_truncnorm_pdf(double u, double mu, double sig, double trunc);
/* This function is the pdf of a normal times a truncated normal.  u is the arguement of this pdf. See 
 * ran_norm_truncnorm for the other values */
	
//extern double ran_norm_truncnorm_pdf(double u, double norm_mu, double norm_sigma, 
//	double trunc_mu, double trunc_sigma, double trunc);

/* This function below returns the array value[], and nothing else.  It does need to copy
 * the matrix covar to a temp matrix before it is modified so the original value
 * of covar is preserved.  This function also needs the positive integer n so the 
 * size of the array can be determined.                                       
 */	

//extern void new_param(const gsl_rng * r, double value[], gsl_matrix *covar);

extern double acceptprob(double prior_mean[], double prior_sd[], double param_new[], 
	double param_old[], double numdenom, size_t n);

//extern void read_in_data_vec(const char *path, const char *file, gsl_vector *vec);

//extern void read_in_data_matrix(const char *file, gsl_matrix *mat);

/*! \brief Structure for each (vector) tree growth parameter.
 * 
 *
 */
 /*
typedef struct{
  double value[2];           ///<current value
  double pri_mean[2];        ///<prior mean  (normal prior)
  double pri_sd[2];          ///<prior std. dev. 
  gsl_matrix * prop_covar;   ///<covariance matrix for normal proposal
  int accept;                ///<number accepted
  int specID;                ///<species ID
  int paramID;               ///<parameter ID
} param;
*/
/*! /brief Structure for scalar growth model parameters. 
 */
typedef struct{
  double value;      //parameter value
  double pri_mean;   //prior mean  (normal prior)
  double pri_sd;     //prior std. dev. 
  double prop_sd;    //proposal std. dev. Needed for tuning
  int accept;        //number accepted
  int specID;          //species id
  int paramID;       ///<parameter ID
} param_1;

/*! \brief Structure for each tree.
*/
typedef struct{
  double y_r[1];       ///<current radius value at second measurement ("y^{\theta}" or "y^p")
  double y_h[1];       ///<current height value at second measurement
  double obs_r[2];    ///<observed radii measurements (in meters)
  double obs_h[2];    ///<observed height measurements (in meters)
  double obs_h0;      ///< observed initial height (if present)
  double y_h0;        ///< computed initial height
  double yp_r[1];     ///<"yp" for radius for the non-rj case
  double yp_h[1];      ///<"yp" for height for non-rj case
  double last_alive_r;       ///<last (alive) radius value from growthmodel (call this ytheta_r)
  double last_alive_h;       ///<last (alive) height value from growthmodel (call this ytheta_h)
  double r_rep;       ///< replicated radius
  double h_rep;       ///< replicated height
  double r_rep_thet;  ///< replicated y^theta in norj model
  double h_rep_thet;  ///< replicated y^theta in norj model
  int meas_iter[1];        ///<number of iterations ceil(time of second measurement/deltat)) 
  int iter_last_alive;   ///<iteration number tree was last alive  
   double meas_year;        ///<year of second measurement.  
  int specID;           ///<1 for loblolly, 2 for red maple
  double obs_meas_year; ///< observed year of second measurement
  int dead;       ///< flag for dead (=1 for dead, =0 for alive)
  int rBHcd;      ///< =1 for rBH, =0 for radius measured at base
} tree_struct;

/*! \brief This structure is for the proposed "tree" in the MCMC routine.
 *
 *
 * Different from tree_struct in that it only includes items from 
 * tree_struct that change from iteration to iteration.  See tree_struct
 * for details
 */
typedef struct{
  double y_r[1];
  double y_h[1];
  double y_h0;
  double last_alive_r;
  double last_alive_h;
  int iter_last_alive;
  double meas_year;
  int meas_iter[1];
  int dead;
} prop_tree; 

/*! \brief Structure for variance components.
 *
 */
typedef struct{
  double thetar;     ///< sqrt(thetaro^2+thetar1^2)
  double thetah;    ///< observation std. dev. for height
  double thetar_old;
  double thetah_old;
  double pr;        ///< process std. dev. for radius
  double ph;        ///< process std. dev. for height
  double primeanr;  ///< prior mean for the additional comp. radius
  double primeanh;  ///< prior mean for height
  double prisdr;    ///< prior std. dev. for initial radius 
  double prisdh;    ///< prior std. dev. for height
  double propsdr;   ///< std. dev. for normal proposal for initial radius
  double propsdh;   ///< std. dev. for normal proposal for height 
  int acceptr;      ///< number accepted (for thetaro)
  int accepth;      ///< number of height accepted
  int dead[3];      ///< number of dead for total, spec 1 and spec 2 rj model
  int swtch;        ///< number of alive/dead "switches"
  int accept;       ///< was the move accepted?
  int dead_attmpt;  ///< # dead trees in proposed move
  int flag;         ///< =1 if dead to all alive, =2 if all alive to dead
} sigma;

/*!
 * \brief Contains the begining/ending indices for different species.  
 * 
 * The textfile containing the data is sorted by species.  This allows each loop 
 *  be run in parallel.
 */  
typedef struct{
  int spec[2];  ///< observation std. dev. for radius
  int status[2];  ///< observation std. dev. for height
} indexx;


#endif
