/*!
* \file misc_func.c
* \brief Contains misc. densities and other functions for MCMC
* 
* \author Darren Gemoets
* \date 11-12-2009
*
*/

#include "head_files/misc_func.h"

/*!
 * Generates a left-truncated normal rv.
 *
 * \f[
 * p(x) = \frac{1}{N(trunc;\sigma) \sqrt{2 \pi \sigma^2}} \exp (- (x-\mu)^2/(2 \sigma^2))
 * \f]
 *
 * \param mu      Location parameter
 * \param r       gsl_rng 
 * \param sig     Scale parameter
 * \param trunc   Truncation point
 */ 
double ran_truncnorm(const gsl_rng * r, double mu, double sig, double trunc){
        
  double x=0,rand;
 
  rand=gsl_ran_flat(r,0,1);  // generate U(0,1)
  printf("rand=%g \n",rand);
  if (trunc >= mu){
    x=gsl_ran_gaussian_tail(r,(trunc-mu),sig)+mu;
  }
  else {
    // invert the CDF
    if (rand == 0){ // make sure > 0
      printf ("warning in ran_truncnorm: uniform is zero=%g \n",rand); 
      printf("mu=%g, sig=%g, trunc=%g \n",mu,sig,trunc);
      getchar();
      rand=1e-10; 
      }
    double c=gsl_cdf_gaussian_Q ((trunc-mu), sig)*(1-rand);  
    if (c==0){  // check for numerical zero  
      c=1e-300;
    }
    x=gsl_cdf_gaussian_Qinv (c, sig)+mu;
  }

  if(isinf(-x)!=0){ // check if infinite value
    printf("warning in ran_truncnorm: returned -infty \n");
    printf("mu=%g, sig=%g, trunc=%g \n",mu,sig,trunc);
    printf("x=%g \n",x);
    x=-1e100;  // return large finite negative value
    //getchar();        
  }

return x;
}  


/*!
* The left-truncated normal pdf.
*
* \f[N()\f] is the normalizing constant.
*
* \f[
* p(x|\mu,\sigma,trunc) = \frac{1}{N(trunc;\sigma) 
*             \sqrt{2 \pi \sigma^2}} \exp (- (x-\mu)^2/(2 \sigma^2)) 
* \f]
*
* \param mu
* \param \sigma^2
* \param trunc
*
*  TODO: test the code below.  make sure shift is correct.
*/
double ran_truncnorm_pdf(double u, double mu, double sig, double trunc){
        
  double x=0;
  double a=gsl_ran_gaussian_pdf((u-mu),sig);
  double b=gsl_cdf_gaussian_Q ((trunc-mu), sig);
    
  if (trunc >= mu){
            x=gsl_ran_gaussian_tail_pdf((u-mu),(trunc-mu),sig);
        if((isnan(x)!=0) || (isinf(x)!=0)){
        printf("warning, gsl_ran_gaussian_tail_pdf is nan \n"); 
        printf("u=%g, mu=%g, sig=%g, trunc=%g, x=%g, a=%g, b=%g \n",
               u, mu, sig, trunc, x, a, b);
        x=1e-150;
        //getchar();
        }
    
  }
  else {  // mu>trunc
    
    if (u >= trunc){  // check that value is larger than truncation point
      
           if ((a==0) && (b==0)){
             printf("error in ran_truncnorm_pdf, line 120 \n");
             //getchar();
             //x=1;
	     x=1e-150;
           }
           else if ((a==0) && (b>0)){
             printf("warning in ran_truncnorm_pdf, pdf is zero \n");
             x=1e-150;
             //getchar();
           }
           else if ((a>0) && (b==0)){
             printf("error in ran_truncnorm_pdf, b=0 \n");
             x=-999;
             getchar();
           }
           else {
             x=a/b;
           }
      
  }
  else{  // u<trunc. serious error
    printf("error in ran_truncnorm_pdf: u<trunc \n"); 
    printf("u=%g, mu=%g, sig=%g, trunc=%g, x=%g, a=%g, b=%g \n",
           u, mu, sig, trunc, x, a, b);
    getchar();
  }
  } // end outermost else
  if(x==0){ // replace x=0 with small value
    x=1e-150;
  }
  if((isnan(x)!=0) || (isinf(x)!=0)){ // check for nan and inf
    printf("errir in ran_truncnorm_pdf \n"); 
    printf("u=%g, mu=%g, sig=%g, trunc=%g, x=%g, a=%g, b=%g \n",
           u, mu, sig, trunc, x, a, b);
    getchar();
  } 

  return x;
}

/*!
* Generates a normal times a left-truncated normal rv,
*
* NOT THE CORRECT DENSITY
* \f[
* p(x) = \frac{1}{N(trunc;\sigma) \sqrt{2 \pi \sigma^2}} \exp (- (x-\mu)^2/(2 \sigma^2))
* \f]
*
* \param norm_mu         Mean of normal
* \param norm_sigma      Std. dev. of normal
* \param trunc_mu        Location param of trunc normal
* \param trunc_sigma     Scale param of trunc normal
* \param trunc           Truncation location
*
*/
double ran_norm_truncnorm(const gsl_rng * r, double norm_mu, double norm_sigma, 
			  double trunc_mu, double trunc_sigma, double trunc){
  
  double sig=sqrt((norm_sigma*norm_sigma*trunc_sigma*trunc_sigma)/
		  (norm_sigma*norm_sigma + trunc_sigma*trunc_sigma));
  double mu=(norm_mu/(norm_sigma*norm_sigma)+trunc_mu/(trunc_sigma*trunc_sigma))/
    (1/(norm_sigma*norm_sigma)+1/(trunc_sigma*trunc_sigma));
    return ran_truncnorm(r, mu, sig, trunc);
}

/*!
 * Generates a normal times a left-truncated normal rv,
 *
 * Todo: have it call ran_trunknorm_pdf
 *
 * NOT THE CORRECT DENSITY
 * \f[
 * p(x) = \frac{1}{N(trunc;\sigma) \sqrt{2 \pi \sigma^2}} \exp (- (x-\mu)^2/(2 \sigma^2))
 * \f]
 *
 * \param u               Value
 * \param norm_mu         Mean of normal
 * \param norm_sigma      Std. dev. of normal
 * \param trunc_mu        Location param of trunc normal
 * \param trunc_sigma     Scale param of trunc normal
 * \param trunc           Truncation location
 *
 */
double ran_norm_truncnorm_pdf(double u, double norm_mu, double norm_sigma, 
                              double trunc_mu, double trunc_sigma, double trunc){
        
  double y;

  double sig=sqrt((norm_sigma*norm_sigma*trunc_sigma*trunc_sigma)/
           (norm_sigma*norm_sigma + trunc_sigma*trunc_sigma));
  double mu=(norm_mu/(norm_sigma*norm_sigma)+trunc_mu/(trunc_sigma*trunc_sigma))/
    (1/(norm_sigma*norm_sigma)+1/(trunc_sigma*trunc_sigma));
    
  double x=ran_truncnorm_pdf(u, mu, sig, trunc);
  
  if (x > 0){
    y=x;
  }
  else {
    printf("warning: density is zero in ran_norm_truncnorm_pdf \n");
    y=1e-150;
  }
  return y;
}

/*! Generates a vector from a multivariate normal proposal.
 *  
 * Add some details.
 * 
 *
 * \param r               gsl_rng
 * \param value           Current value for mvnormal proposal
 * \param covar           Covariance matrix for normal proposal
 *
 * Returns 
 * NOTE: Rename this function
 */
void new_param(const gsl_rng * r, double value[], gsl_matrix *covar){

  double x;
  size_t i;

  size_t length=covar->size1;
  size_t length2=covar->size2;
  if(length != length2){
    printf("Matrix needs to be square");
  }
  gsl_vector * z = gsl_vector_alloc (length); 
  gsl_matrix * A = gsl_matrix_alloc(length,length);
  gsl_matrix_memcpy (A,covar);
  gsl_linalg_cholesky_decomp (A);
     
  for (i =0; i < length; i++){     
    x = gsl_ran_gaussian_ziggurat(r,1);
    gsl_vector_set(z,i,x);
  }  
    
  gsl_blas_dtrmv (CblasLower, CblasNoTrans, CblasNonUnit, A, z);
  gsl_matrix_free(A);

  for (i=0; i<length ; i++){
    value[i] = value[i] + gsl_vector_get(z,i);
  }	
}

/*! Not sure what this does, or if it is used.
*  
* Add some details.
* 
*/
double acceptprob(double prior_mean[], double prior_sd[], double param_new[], 
		  double param_old[], double numdenom, size_t n){	
  
  double temp1=0, temp2=0, x;
  size_t i;

  for (i=0; i<n; i++){
    temp1=temp1 + ((1/(2*prior_sd[i]*prior_sd[i]))*(prior_mean[i]-param_new[i])*(prior_mean[i]-param_new[i]));
    temp2=temp2 + ((1/(2*prior_sd[i]*prior_sd[i]))*(prior_mean[i]-param_old[i])*(prior_mean[i]-param_old[i]));
  }
  //printf("temp1=%g, temp2=%g \n", temp1,temp2);
  
  x = numdenom + (temp2 - temp1);
  return x;
}


 /*! \brief Reads a text file into a gsl_vector
 * 
 * \date 04/21/2010
 *
 */

//Reads data from text file into gsl vector
void read_in_data_vec(const char *path, const char *file, gsl_vector *vec){

  FILE *fp;
  char temp[60];
  strcpy(temp,path);
  strcat(temp,file);
  fp=fopen(temp, "r");
  gsl_vector_fscanf (fp,vec);
  fclose(fp);
  // printf("file name is %s \n",temp);

}

/*! \brief Reads a text file into a gsl_matrix
 * 
 * \date 04/21/2010
 *
 */

//Reads data from textfile into gsl matrix
void read_in_data_matrix(const char *file, gsl_matrix *mat){

  FILE *fp;
  fp=fopen(file, "r");
  gsl_matrix_fscanf (fp,mat);
  fclose(fp);

}





