###############################################################################
# Calculate average par for sims
###############################################################################

#PARmax <- 2061.5; k <- 0.625; LAIf <- 6.0; gt <- 4; ct <- 5; tbg <- 20; simtime <- 200; del.t <- 16; Hmax<-40;

#test<-(paravg(PARmax=2061.5, k=0.625, LAIf=6.0, Hmax=40, gt=4, ct=5, tbg=20, simtime=200, del.t=16))


#jpeg(file=paste("Gap_demo_plot_2016_04_27.jpeg", sep=""), units ="in",
# width=6,height=5, res=300)
#plot((1:3200)/16,(paravg(PARmax=2061.5, k=0.625, LAIf=6.0, Hmax=40, gt=4, ct=45,
# tbg=100, simtime=200, del.t=16))[[1]], type="l", xlab="years", ylab="PARunder", col="darkblue")
# abline(h=0, lty=3)
#dev.off()

paravg <- function(PARmax, k, LAIf, Hmax, gt, ct, tbg, simtime, del.t){
  gap.phase <- numeric(simtime*del.t)

  ud <- 3.4-5.5*(Hmax/Hmax)
  LAIF=exp(ud)/(1+exp(ud))
  
  closed <- tbg-(gt+ct)
  if(closed < 0){
    stop("The colosed period is negative")
  }
  
  phase <- rep(c(rep(1, gt*del.t), rep(2, ct*del.t), rep(3,closed*del.t)), ceiling(simtime/tbg))
  phase <- phase[1:(simtime*del.t)]
  
  PARtime <- numeric(length(phase))
  cty=1
  
  # par at the forest floor
  # PARfloor <- PARmax*(exp(k*LAIF)/(1+exp(k*LAIF)))
  PARfloor <- PARmax*exp(-k*LAIf)
  
  for(i in 1:length(phase)){
    if(phase[i]==1){
      PARtime[i] <- PARmax
    }else if(phase[i]==2){
      if(cty < ct*del.t){
        Hmax2 <- (Hmax/(del.t*ct))*cty
        ud <- 3.4-5.5 #*(Hmax2/Hmax)
        #LAIF2=exp(ud)/(1+exp(ud))
        LAIF2<-(LAIf/(del.t*ct))*cty
        
        #PARtime[i] <- PARmax*(exp(k*((LAIF2/(del.t*ct))*cty))/(1+exp(k*((LAIF2/(del.t*ct))*cty))))
        PARtime[i] <- PARmax*exp(-k*LAIF2)
        cty <- cty+1
      }else if(cty == ct*del.t){
        Hmax2 <- (Hmax/(del.t*ct))*cty
        ud <- 3.4-5.5 #*(Hmax2/Hmax)
        #LAIF2=exp(ud)/(1+exp(ud))
        LAIF2<-(LAIf/(del.t*ct))*cty
      
        #PARtime[i] <- PARmax*(exp(k*((LAIF2/(del.t*ct))*cty))/(1+exp(k*((LAIF2/(del.t*ct))*cty))))
        PARtime[i] <- PARmax*exp(-k*LAIF2)
        cty <- 1
      }else{
        stop("cty is not < ct or == to ct")
      }
    }else if(phase[i]==3){
      PARtime[i] <- PARfloor
    }else{
      stop("phase is not equal to 1, 2, or 3.")
    }
  }
  
  phase <- rep(c(rep(1, gt), rep(2, ct), rep(3,closed)), ceiling(simtime/tbg))
  phase <- phase[1:(simtime)]
    
  simchar <- list()
  simchar[[1]] <- PARtime
  simchar[[2]] <- phase
  
  return(simchar)
}

