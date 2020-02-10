# ACGCA
## Table of contents
* [Overview](#overview)
  * [Using the ACGCA model](#using-the-acgca-model)
    * [Installing the ACGCA Package](#installation)
    * [Quick Test](#quicktest)
* [Versioning and Licence](#versioning-and-licence)
* [References](#references)

## Overview
The Allometrically Constrained Growth and Carbon Allocation (ACGCA) model is an individually based model of tree growth and mortality originally developed by Ogle and Pacala (2009). As the name implies the ACGCA model makes use of functional traits and allometries between tissue types (i.e. leaves, roots, and stems) to determine carbon allocation in a tree.

Carbon dynamics within the tree are essential to this model. Carbon is allocated between a structural and two storage pools in a way that satisfies the aforementioned allometric relationships (Ogle and Pacala (2009). One storage pool is associated with leaf and fine root tissue. Labile carbon in this pool is retranslocated when the tissue senesceses (Ogle and Pacala 2009). The other storage pool is in the sapwood and is used in times of stress (high labile carbon demand relative to carbon inputs). Finally there is a transient labile carbon pool representative of recent photosynthate and retranslocated carbon. It is not associated with a specific tissue and is immediately redistributed within the tree to accommodate biomass production, respiration, and allocation to storage. If the labile carbon available to the tree is depleted the tree dies (Ogle and Pacala 2009).

There are six possible physiological states in the ACGCA model: healthy, static, shrinking, recovering, recovered, or dead (Ogle and Pacala 2009). Each state is described by a set of difference equations satisfying mass-balance relationshipts between structural and labile carbon pools. The only environmental driver included in the model is parmax (annual radiation for a site).

For a full description of the model see Ogle and Pacala (2009) and the accompanying supplemental material. The model has also been used in several other studies (Fell et al. 2018 and Gemoets et al 2013).

## Using the ACGCA model
### Installing the ACGCA Package
To install the ACGCA package run the following commands.
```{R}
.libPaths()
install.packages("devtools")  
library(devtools)  
devtools::install_github("fellmk/ACGCA/ACGCA", lib="LIBRARYPATH")
library(ACGCA)
```
The first command `.libPaths()` is not necessarily needed but will list available R libraries on your system. The second line installs the devtools package which is required for installing the ACGCA package. The third line loads devtools. The final two lines install and load the ACGCA package. Where `lib="LIBRARYPATH"` insert the R library where you would like the package to install. The default will be used if this is not specified.

### Quick Test
Run a quick test to make sure the ACGCA model is working
```{R}
test <- runacgca(sparms = acru, parmax = 1000, years = 50, steps = 16) # acru contains a set of parameters
plot(x=1:800/16, y = test$h, type="l", xlab = "time (years)", ylab = "height (m)")
```

## Versioning and Licence
The ACGCA package uses the MIT license.

## References

Fell, M., J. Barber, J. W. Lichstein, and K. Ogle. 2018. Multidimensional trait space informed by a mechanistic model of tree growth and carbon allocation. Ecosphere 9. DOI:10.1002/ecs2.2060

Gemoets, D., J. Barber, and K. Ogle. 2013. Reversible jump MCMC for inference in a deterministic individual-based model of tree growth for studying forest dynamics. Environmetrics 24:433–448.

Ogle, K., and S. W. Pacala. 2009. A modeling framework for inferring tree growth and allocation from physiological, morphological and allometric traits. Tree Physiology 29:587–605.
