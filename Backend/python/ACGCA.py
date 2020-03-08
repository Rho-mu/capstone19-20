import json
import ctypes
from ctypes import cdll, c_double, c_int
# read json -- complete
with open('input.json', encoding='utf-8') as f:
    line = f.readline()
    d = json.loads(line)
    hmax = d['hmax']
    f.close()

# read dll 
mydll = ctypes.CDLL(r'G:\ACGCA-master\ACGCA\src\ACGCA.dll')
output = mydll.growthloop
print(type(output))

# make C structure into python
class tparms(ctypes.Structure):
  _fields_=[('rinit', ctypes.c_double)]

class gparms(ctypes.Structure):
  _fields_=[('BH', ctypes.c_double), ('deltat', ctypes.c_double),
    ('T',ctypes.c_double), ('tolerance', ctypes.c_double)]

gp = gparms()
gp.BH = 1.37
gp.deltat = 0.0625
gp.T = 10
gp.tolerance = 0.00001

class sparms(ctypes.Structure):
  _fields_=[
    ('hmax', ctypes.c_double), 
    ('phih',ctypes.c_double), 
    ('eta',ctypes.c_double), 
    ('etaB',ctypes.c_double),
    ('swmax',ctypes.c_double),
    ('lamdas',ctypes.c_double), 
    ('lamdah',ctypes.c_double),
    ('rhomax',ctypes.c_double),
    ('rhomin',ctypes.c_double),  
    ('f2',ctypes.c_double), 
    ('f1',ctypes.c_double), 
    ('gammac',ctypes.c_double),
    ('gammaw',ctypes.c_double),
    ('gammax',ctypes.c_double), 
    ('cgl',ctypes.c_double),  
    ('cgr',ctypes.c_double),
    ('cgw',ctypes.c_double),
    ('deltal',ctypes.c_double),
    ('deltar',ctypes.c_double),
    ('sl',ctypes.c_double),
    ('sla',ctypes.c_double),
    ('sr',ctypes.c_double),
    ('so',ctypes.c_double),
    ('rr',ctypes.c_double),
    ('rhor',ctypes.c_double),
    ('rml',ctypes.c_double),
    ('rms',ctypes.c_double),
    ('rmr',ctypes.c_double),
    ('drcrit',ctypes.c_double),
    ('drinit',ctypes.c_double),  
    ('k',ctypes.c_double),
    ('epsg',ctypes.c_double),
    ('M',ctypes.c_double),
    ('alpha',ctypes.c_double),
    ('R0',ctypes.c_double),
    ('R40',ctypes.c_double)]

# suppose the default value just for current testing
p = sparms()
p.hmax = 27.5
p.phih = 263
p.eta = 0.64
p.swmax = 0.1
p.lamdas = 0.95  
p.lamdah = 0.95
p.rhomax = 525000
p.rhomin=525000 
p.f2=7000
p.f1=4
p.gammac = 131000
p.gammaw = 0.000000667
p.gammax=0.12
p.cgl=1.45
p.cgr=1.25
p.cgw=1.37  
p.deltal=0.095  
p.deltar = 0.15
p.sl=1
p.sla=0.0141
p.sr=1
p.so=0.05
p.rr=0.00015
p.rhor=160000
p.rml=2.5
p.rms = 0.05
p.rmr=1.5
p.etaB=0.045
p.k=0.7
p.epsg=6.75
p.M=0.95
p.alpha=0.365
p.R0=1.909
p.R40=5.592

class Forestparms(ctypes.Structure):
  _fields_=[
    ('kf',ctypes.c_double),
    ('intF',ctypes.c_double),
    ('slopeF',ctypes.c_double)]

ForParms = Forestparms()
ForParms.kf = 0.6
ForParms.intF = 3.4 
ForParms.slopeF = -5.5

# years * steps +1
# suppose it is 4
N = 4

# declare the pointers to the structure
Io = (c_double*N)()
r0 = (c_double*N)()
t = c_int
Io = 2060
r0 = (c_double)(0.05)
t = 1
Hc = (ctypes.c_double)(-99)
LAIF = (ctypes.c_double)(0)


# give the size of the double array
APARout = (c_double*N)()
h = (c_double*N)()
hh2 = (c_double*N)()
hC2 = (c_double*N)()
hB2 = (c_double*N)()
hBH2 = (c_double*N)()
r = (c_double*N)()
rB2 = (c_double*N)()
rC2 = (c_double*N)()
rBH = (c_double*N)()
sw2 = (c_double*N)()
vts2 = (c_double*N)()
vt2 = (c_double*N)()
vth2 = (c_double*N)()
sa2 = (c_double*N)()
la2 = (c_double*N)()
ra2 = (c_double*N)()
dr2 = (c_double*N)()
xa2 = (c_double*N)()
bl2 = (c_double*N)()
br2 = (c_double*N)()
bt2 = (c_double*N)()
bts2 = (c_double*N)()
bth2 = (c_double*N)()
boh2 = (c_double*N)()
bos2 = (c_double*N)()
bo2 = (c_double*N)()
bs2 = (c_double*N)()
cs2 = (c_double*N)()
clr2 = (c_double*N)()
fl2 = (c_double*N)()
fr2 = (c_double*N)()
ft2 = (c_double*N)()
fo2 = (c_double*N)()
rfl2 = (c_double*N)()
rfr2 = (c_double*N)()
rfs2 = (c_double*N)()
egrow2 = (c_double*N)()
ex2 = (c_double*N)()
rtrans2 = (c_double*N)()
light2 = (c_double*N)()
nut2 = (c_double*N)()
deltas2 = (c_double*N)()
LAI2 = (c_double*N)()
status2 = (c_int*N)()
errorind = (c_int*N)()
growth_st = (c_int*N)()

output(p, 
    gp,
    Io,
    r0, 
    t,
	  Hc,   
    LAIF, 
    ForParms, 
    APARout, 
    h,
    hh2,
	  hC2,
	  hB2,
	  hBH2,
	  r,
	  rB2,
	  rC2,
	  rBH,
	  sw2,
	  vts2,
	  vt2,
	  vth2,
	  sa2,
	  la2,
	  ra2,
	  dr2,
	  xa2,
	  bl2,
	  br2,
	  bt2,
	  bts2,
	  bth2,
	  boh2,
	  bos2,
	  bo2,
	  bs2 ,

	  cs2,
	  clr2,
	  fl2,
	  fr2,
	  ft2,
	  fo2,
	  rfl2,
	  rfr2,
	  rfs2,

	  egrow2,
	  ex2,
	  rtrans2,
	  light2,
	  nut2,
	  deltas2,
	  LAI2,
	  status2,
	  errorind,
	  growth_st                
)

