library("devtools")
options(devtools.install.args = "--no-multiarch")
library("roxygen2")

setwd("./ACGCA")
document()
devtools::build(vignettes = FALSE)

setwd("..")
install("ACGCA", build_vignettes = FALSE)

library(ACGCA)
help(package="ACGCA")
#browseVignettes("ACGCA")