From https://academic.oup.com/treephys/article/29/4/587/1642683#supplementary-data supplementary data
r = radius at bottom
H = total tree height
Hc = height from base of trunk to base of crown
rc = height at top of trunk (where it transitions to crown)
Rc = radius of crown (might not need)
Rcbase = radius at base of crown


From R documentation
h = A time series of tree height from the simulation for each time step. The length is steps*years+1 due to the initialization (time 0) (m).
hh = Height at which trunc transitions from a paraaboloid to a cone. Also the height to the base of the crown (m).
r = A time series of tree radius (m) from the simulation for each time step. The length is steps*years+1 (time 0).
rB = Radius at the tree's base (m).
status = The status of the tree (i.e. living=1 or dead=0) at each iteration. Always 0 for the first iteration (initialization).
growth_st = Growth status of the tree: 1=healthy, 2=reduced, 3=recovery, 4=static, 5=shrinking, 6=dead, other=Error.