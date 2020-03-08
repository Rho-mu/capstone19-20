###############################################################################
# parameters for acer
###############################################################################

parameter.names <- c("p.hmax","p.phih","p.eta","p.swmax","lamdas","lamdah","rhomax","rhomin_notinuse","p.f2","p.f1","p.gammac","p.gammaw","p.gammax","p.cgl","p.cgr","p.cgw","p.deltal","p.deltar","p.sl","p.sla","p.sr","p.so","p.rr","p.rhor","p.rml","p.rms","p.rmr","p.etaB","p.k","p.epsg","p.M","p.alpha","p.R0","p.R40","drinit","drcrit","PAR","deviance")
parameter.values <- c(16.0183184165118,280.16572056794,0.652990182221256,0.0555915685718514,2.44910056520544,0.533260371924704,928016.564320175,535444.466257044,5207.96968647829,1.70033582587291,526305.358303859,6.67e-07,0.424306683650843,1.39142601439415,1.12672311629253,1.39295089424243,0.0922032781717314,0.0676723454071751,1.69141013863837,0.0134855441429331,1.34824699309595,0.269589293753742,0.000389462649404076,71807.2432405614,7.79032300830437,1.1869636574623,16.1538118486095,0.0445501644484093,0.53000849561364,68.3345065014988,0.871823417740634,0.29564309930226,0.897090645006579,6.15481807673639,1e-05,0.0075,206,10.8841758890596)

#c("p.hmax",
#"p.phih",
#"p.eta",
#"p.swmax",
#"lamdas",
#"lamdah",
#"rhomax",
#"rhomin_notinuse",
#"p.f2",
#"p.f1",
#"p.gammac",
#"p.gammaw",
#"p.gammax",
#"p.cgl",
#"p.cgr",
#"p.cgw",
#"p.deltal",
#"p.deltar",
#"p.sl",
#"p.sla",
#"p.sr",
#"p.so",
#"p.rr",
#"p.rhor",
#"p.rml",
#"p.rms",
#"p.rmr",
#"p.etaB",
#"p.k",
#"p.epsg",
#"p.M",
#"p.alpha",
#"p.R0",
#"p.R40"
#)


acru <- c(27.5, # 1 Hmax
  263, # 2 phih
  0.64, # 3 eta
  0.10, # 4 swmax
  0.95, # 5 "lamdas", #
  0.95, # 6 "lamdah", #
  525000, # 7 rhomax
  525000, # 8 rhomin not used
  7000, #9 "p.f2",
  4.0, #" 10 p.f1",
  131000, # 11 "p.gammac",
  0.000000667, # 12 "p.gammaw",
  0.12, # 13 "p.gammax",
  1.45, # 14 "p.cgl",
  1.25, # 15 "p.cgr",
  1.37, # 16 "p.cgw",
  0.095, # 17 "p.deltal",
  0.15, # 18 "p.deltar",
  1.0, # 19 "p.sl",
  0.0141, # 20 "p.sla",
  1.0, # 21 "p.sr",
  0.05, # 22 "p.so",
  0.00015, # 23 "p.rr",
  160000, # 24 "p.rhor",
  1.25, # 25 "p.rml",
  0.025, # 26 "p.rms",
  0.75, # 27 "p.rmr",
  0.045, # 28 "p.etaB",
  0.7, # 29 "p.k",
  6.75, # 30 "p.epsg",
  0.95, # 31 "p.M",
  0.365, # 32 "p.alpha",
  1.909, # 33 I am not sure about this value "p.R0",
  5.592, # 34 I am not sure about this value "p.R40"
  0.00005, # 35 drinit
  0.0075 # 36 drcrit
)

years <- 50
gparm <- numeric(5)
gparm[1] <- 0.0625 # gp.deltat
gparm[2] <- years # gp.T length of run in years
gparm[3] <- 0.00001 # gp.tolerance
gparm[4] <- 1.37 # gp.BH
gparm[5] <- 2060 # Value not really used but is changed below
gparm<-as.matrix(gparm)

cbind(parameter.names[1:34], acru[1:34], parameter.values[1:34])
