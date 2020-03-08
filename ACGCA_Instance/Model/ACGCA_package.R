###############################################################################
#
# The goal of this project is to develop an ACGCA package for R.
#
# Started by Michael Fell on January 18, 2018.
#
###############################################################################

install.packages("devtools")
devtools::install_github("klutometis/roxygen")

# Load the development library and roxygen which helps with documentation.
library("devtools")
options(devtools.install.args = "--no-multiarch")
library("roxygen2")

# A devtools function that produces a barebones folder for a package
create("ACGCA")

# I added documentation this moves into the ACGCA folder to create
# documentation.
setwd("./ACGCA")
use_rcpp()
document()
devtools::use_vignette("ACGCA_Vignette")
devtools::use_testthat()
# This will build the package and Vignetttes
devtools::build()
# Create data to be loaded
devtools::use_data(acru)
devtools::use_data(parms)

setwd("..")
install("ACGCA")
help(package="ACGCA")
library(ACGCA)
help("runacgca")

###############################################################################
#
# Beyond this point the code is for testing the function much if this may or
# may not work after modifying the file. MKF 4/5/18.
#
###############################################################################

load("inputs_chain1_r00.05_PAR206_parACGCA.Rdata")
load("names_thetaj.R")

theta.j <- theta.j[-c(8,12,35,36)]

# Run the growthloop 1000 times to check for bugs.
system.time(for(i in 1:1000){
test2 <- ACGCA::runacgca(sparms=theta.j, r0=0.05, fulloutput=TRUE, parmax=2060,  gapvars=list(gt=5, ct=5,
                                                                                                 tbg=20), gapsim=TRUE)
}
)

plot(test2$h, type="l")

theta.j[1] <- 30
test2 <- ACGCA::runacgca(sparms=theta.j, r0=0.05, fulloutput=TRUE, parmax=2060)
plot(test2$h, type="l")

test2 <- ACGCA::runacgca(sparms=theta.j, r0=0.05, fulloutput=TRUE, parmax=seq(2060, 200, length.out = 801))
plot(test2$h, type="l")


source("acruparms.R")
acru <- acru[-c(8,12,35,36)]
light.levels <- seq(1,.1,-.1)

# This tests the package code at multiple light levels
test <- list()
test.s <- list()

test <- ACGCA::runactca(sparms=acru, r0=0.0054, parmax=2060, 
                           fulloutput=FALSE, gapsim=FALSE)

test <- ACGCA::runactca(sparms=acru, r0=0.0054, parmax=2060, 
                           gapvars=list(gt=2, ct=5,
                                        tbg=20), fulloutput=TRUE, gapsim=TRUE)

for(i in 1:length(light.levels)){
  acru <- as.matrix(acru)
  # This uses the smallest radius I can get
  test <- ACGCA::runactca(sparms=acru, r0=0.0054, parmax=2060, 
                             gapvars=list(gt=2, ct=5,
                                          tbg=20), fulloutput=TRUE, gapsim=TRUE)
  test.s[[i]] <- test
  if(i == 1){
    plot((1:801)/16, test$r, type="l")
  }else{
    lines((1:801)/16, test$r, type="l")
  }
}

acru <- as.matrix(acru)
# This uses the smallest radius I can get
test <- ACGCA::runactca(sparms=acru, r0=0.0054, parmax=2060, fulloutput=TRUE, years=100)
test.s[[i]] <- test
plot(1:1601, test$r, type="l")

partest <- seq(from=2060, by=-1, length.out=1600)
test <- ACGCA::runactca(sparms=acru, r0=0.0054, parmax=partest, fulloutput=TRUE, years=100)
test.s[[i]] <- test
lines(1:1601, test$r, type="l")

partest <- seq(from=2060, by=-2, length.out=1600)
test <- ACGCA::runactca(sparms=acru, r0=0.0054, parmax=partest, fulloutput=TRUE, years=100)
test.s[[i]] <- test
lines(1:1601, test$r, type="l")

# Print out the values
cbind(theta=parameter.names[-c(8,12,35,36,37,38)], acru, theta.j)
# Test the scafold to make sure it runs. This call is for development and
# would in no way work with the full funciton. That should be tested using
# inputs from the origional paper by Ogle and Pacala (2009).

#ACGCArun(as.matrix(c(1, 1, 1)), as.matrix(c(1,1,1)), 1)
#dyn.load("ACGCA.dll")

#Make sure data is used correctly

