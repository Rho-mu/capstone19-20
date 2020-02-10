###############################################################################
# The following code runs the growth loop after setting up a 
# function.
# 
# The main goal of this code is to coordinate between the R and
# C components of the program.
#
# Major additions made while fixing errors 7/4/2013 by MFK.  
# I simplified the C code so only one parameter set runs at a 
# time.
#
###############################################################################

dyn.load("Rgrowthloop.so") ## see help (dyn.load)
#dyn.load("excessgrowing.so")
#dyn.load("growthloop.so")
#dyn.load("misc_func.so")
#dyn.load("misc_growth_funcs.so")
#dyn.load("putonallometry.so")
#dyn.load("rebuildstaticstate.so")
#dyn.load("shrinkingsize.so")

## Check dyn.load result to see that our C function symbol exists and
## presumably is ready to use in R:
print(paste("growthloop loaded: ",is.loaded("Rgrowthloop"), sep=""))

###############################################################################
# This version of the growth loop is a modification for incorporating it in a
# metropolis type algorithem that will run the model until it generates
# output that is similar to values used to generate a probability array.
#
# In this version of the code the inputs are interpreted as follows
# gparms2 - input model parameters (dt, r0 etc.).
# sparms2 - input initial parameters for the model to start mcmc with
# r0 - inital radius
# dim - ?
# lenvars2 - gan get rid of this it was the length of the file
# 
# VARIABLES TO ADD
# initial sigmas
# nits (iterations for comparison (acceptance rate)
# 
#
# This was written by MKF 4/16/2014 as a modification of the batch version of
# the code.
###############################################################################

## This code creates the function that runs the growth loop once it is loaded
growthloopR <- function(sparms2, gparms2, r0, dim,lenvars2){
  #t<- numeric(0)	

  # Set up the variables needed for lengths of output
  #lenvars2 <- (gparms2[2,1]/gparms2[1,1])*dim[1]+dim[1]
  lenvars <- (gparms2[2,1]/gparms2[1,1])+1
  output2 <- list(h=numeric(0), r=numeric(0), rBH=numeric(0), status=numeric(0), errorind=as.integer(numeric(0)),cs=numeric(0), clr=numeric(0), growth_st=as.integer(numeric(0)))
	
  # Loop through each set of variables and then check the output against
  # a probability array and apply the metropolis criteria where the acceptance
  # rate should be near 0.24-0.40.  This is accomplished by modifying adjusting
  # sigma until the acceptance is 0.24-0.40 for the last 100 iterations.
  for(j in 1:lenvars2){

    # Create a vector of variables for each run
    sparms <- sparms2[,j]
    gparms <- gparms2[,j]
    r02 <- r0[j]

    output1<- .C("Rgrowthloop",p=as.double(sparms), gp=as.double(gparms), r0=as.double
      (r02), t=integer(1),
      #la=double(gparm[2]/gparm[1]+1), #// double
      #LAI=double(gparm[2]/gparm[1]+1), #//double
      #egrow=double(gparm[2]/gparm[1]+1), #//double
      #ex=double(gparm[2]/gparm[1]+1), #//double
      #status=integer(gparm[2]/gparm[1]+1) #//int
      h=double(lenvars), 
      hh=double(lenvars), 
      hC=double(lenvars), 
      hB=double(lenvars), 
      hBH=double(lenvars), 
      r=double(lenvars), 
      rB=double(lenvars), 
      rC=double(lenvars), 
      rBH=double(lenvars), 
      sw=double(lenvars), 
      vts=double(lenvars), 
      vt=double(lenvars), 
      vth=double(lenvars), 
      sa=double(lenvars), 
      la=double(lenvars), 
      ra=double(lenvars), 
      dr=double(lenvars), 
      xa=double(lenvars), 
      bl=double(lenvars), 
      br=double(lenvars), 
      bt=double(lenvars), 
      bts=double(lenvars), 
      bth=double(lenvars), 
      boh=double(lenvars), 
      bos=double(lenvars), 
      bo=double(lenvars), 
      bs=double(lenvars), 

      cs=double(lenvars), 
      clr=double(lenvars), 
      fl=double(lenvars), 
      fr=double(lenvars), 
      ft=double(lenvars), 
      fo=double(lenvars), 
      rfl=double(lenvars), 
      rfr=double(lenvars), 
      rfs=double(lenvars), 
	
      egrow=double(lenvars), 
      ex=double(lenvars), 
      rtrans=double(lenvars), 
      light=double(lenvars), 
      nut=double(lenvars), 
      deltas=double(lenvars), 
      LAI=double(lenvars), 
      status=integer(lenvars), 
      #dim=as.integer(dim),
      lenvars=as.integer(lenvars),

      errorind=integer(lenvars),
      growth_st=integer(lenvars)
    )# End growthloop call
		
    # Output to be saved this can be added to as desired
    output2$h <- c(output2$h, output1$h)
    output2$r <- c(output2$r, output1$r)
    output2$rBH <-c(output2$rBH, output1$rBH)
    output2$status <-c(output2$status, output1$status)
    output2$errorind <- c(output2$errorind, output1$errorind)

    output2$cs <- c(output2$cs, output1$cs) # Added 7/21/2014
    output2$clr <- c(output2$clr, output1$clr) # Added 7/21/2014
    output2$growth_st <-c(output2$growth_st, output1$growth_st) # Added 9/22/2014
  }#growth loop

  return(output2)

} #end of growthloop function

# I have no idea why I did this it just sends the values to another function 
# without doing anything.
growthloopR2 <- function(sparms2, gparms2, r0, dim,lenvars2){
  growthloopR(sparms2, gparms2, r0, dim,lenvars2)
}


