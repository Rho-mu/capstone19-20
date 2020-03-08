library(ACGCA)
test <- runacgca(sparms=acru, gapsim = TRUE, fulloutput = TRUE, years = 200, 
                 steps = 16, gapvars = list(gt = 4, ct = 10, tbg = 20), parmax = 2061.5, r0 = 0.009)

forest <- cbind(test$LAIF, test$Hc)

plot(test$h, type="l")
test$h[1:20]

# Test without gapsim
test <- runacgca(sparms=acru, gapsim = FALSE, fulloutput = TRUE, years = 200, 
                 steps = 16, gapvars = list(gt = 4, ct = 10, tbg = 20), parmax = 2061.5, r0 = 0.009)

plot(test$h, type="l")
test$h[1:20]

thatan <- names.thetaj[-c(8,12,35:36)]

# Test without gapsim fine resolution
test <- runacgca(sparms=acru, gapsim = FALSE, fulloutput = TRUE, years = 200, 
                 steps = 32, gapvars = list(gt = 4, ct = 10, tbg = 20), parmax = 2061.5, r0 = 0.009)

plot(test$h, type="l")
test$h[1:20]

thatan <- names.thetaj[-c(8,12,35:36)]


# Test without gapsim fine resolution
library(ACGCA)
out <- numeric(0)
for(i in 1:70){
  stepset <- i
  test <- runacgca(sparms=acru, gapsim = TRUE, fulloutput = TRUE, years = 200, 
                   steps = stepset, gapvars = list(gt = 4, ct = 10, tbg = 20), parmax = 2061.5, r0 = 0.009)
  print(paste0("steps: ", 200*stepset))
  print(paste0("radius: ", test$r[200*stepset]))
  out <- cbind(out, c(test$r[200*stepset], 200*stepset))
}

plot(out[2,], out[1,])
#plot(test$h, type="l")
#test$h[1:20]
#test$h[5447:5467]

thatan <- names.thetaj[-c(8,12,35:36)]








# Test without gapsim fine resolution without gaps 
library(ACGCA)
out <- numeric(0)
for(i in 1:70){
  stepset <- i
  test <- runacgca(sparms=acru, gapsim = FALSE, fulloutput = TRUE, years = 200, 
                   steps = stepset, gapvars = list(gt = 4, ct = 10, tbg = 20), parmax = 2061.5, r0 = 0.009)
  print(paste0("steps: ", 200*stepset))
  print(paste0("radius: ", test$r[200*stepset]))
  out <- cbind(out, c(test$r[200*stepset], 200*stepset))
}

plot(out[2,], out[1,])





stepset <- 16
test <- runacgca(sparms=acru, gapsim = FALSE, fulloutput = TRUE, years = 200, 
                 steps = stepset, gapvars = list(gt = 4, ct = 10, tbg = 20), parmax = 2061.5, r0 = 0.009)
print(paste0("steps: ", 200*stepset))
print(paste0("radius: ", test$r[200*stepset]))
out <- cbind(out, c(test$r[200*stepset], 200*stepset))

