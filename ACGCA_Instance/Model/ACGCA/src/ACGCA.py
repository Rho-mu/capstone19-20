import json
import ctypes


with open('input.json', encoding='utf-8') as f:
    line = f.readline()
    d = json.loads(line)
    hmax = d['hmax']
    f.close()

# read dll 
mydll = ctypes.CDLL(r'G:\capstone new\capstone19-20-master\ACGCA_Instance\Model\ACGCA\src\ACGCA.dll')
model = mydll.main

class Inputs(ctypes.Structure):
  _fields_=[
      ('hmax', ctypes.c_double), 
      ('phih',ctypes.c_double), 
      ('eta',ctypes.c_double), 
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
      ('R40',ctypes.c_double),

    ]

N = 10

class Outputs(ctypes.Structure):
  _fields_ = [
      ('APARout', (ctypes.c_double*N)),
      ('h', (ctypes.c_double*N)),
      ('hh2', (ctypes.c_double*N)),
      ('hC2', (ctypes.c_double*N)),
      ('hB2', (ctypes.c_double*N)),
      ('hBH2', (ctypes.c_double*N)),
      ('r', (ctypes.c_double*N)),
      ('rB2', (ctypes.c_double*N)),
      ('rC2', (ctypes.c_double*N)),
      ('rBH', (ctypes.c_double*N)),
      ('sw2', (ctypes.c_double*N)),
      ('vts2', (ctypes.c_double*N)),
      ('vt2', (ctypes.c_double*N)),
      ('vth2', (ctypes.c_double*N)),
      ('sa2', (ctypes.c_double*N)),
      ('la2', (ctypes.c_double*N)),
      ('ra2', (ctypes.c_double*N)),
      ('dr2', (ctypes.c_double*N)),
      ('xa2', (ctypes.c_double*N)),
      ('bl2', (ctypes.c_double*N)),
      ('br2', (ctypes.c_double*N)),
      ('bt2', (ctypes.c_double*N)),
      ('bts2', (ctypes.c_double*N)),
      ('bth2', (ctypes.c_double*N)),
      ('boh2', (ctypes.c_double*N)),
      ('bos2', (ctypes.c_double*N)),
      ('bo2', (ctypes.c_double*N)),
      ('bs2', (ctypes.c_double*N)),
      ('cs2', (ctypes.c_double*N)),
      ('clr2', (ctypes.c_double*N)),
      ('fl2', (ctypes.c_double*N)),
      ('fr2', (ctypes.c_double*N)),
      ('ft2', (ctypes.c_double*N)),
      ('fo2', (ctypes.c_double*N)),
      ('rfl2', (ctypes.c_double*N)),
      ('rfr2', (ctypes.c_double*N)),
      ('rfs2', (ctypes.c_double*N)),
      ('egrow2', (ctypes.c_double*N)),
      ('ex2', (ctypes.c_double*N)),
      ('rtrans2', (ctypes.c_double*N)),
      ('light2', (ctypes.c_double*N)),
      ('nut2', (ctypes.c_double*N)),
      ('deltas2', (ctypes.c_double*N)),
      ('LAI2', (ctypes.c_double*N)),
      ('status2', (ctypes.c_int*N)),
      ('errorind', (ctypes.c_int*N)),
      ('growth_st', (ctypes.c_int*N))
  ]

class gparm(ctypes.Structure):
  _fields_ = [
    ('BH',ctypes.c_double),
    ('deltat',ctypes.c_double),
    ('T',ctypes.c_double),
    ('tolerance',ctypes.c_double)
  ]

g = gparm()
g.BH = (ctypes.c_double)(1.37)
g.deltat =(ctypes.c_double)(0.00625)
g.T = (ctypes.c_double)(10)
g.tolerance = (ctypes.c_double)(0.00001)

# suppose the default value just for current testing
p = Inputs()
p.hmax = (ctypes.c_double)(27.5)
p.phih = (ctypes.c_double)(263)
p.eta = (ctypes.c_double)(0.64)
p.swmax = (ctypes.c_double)(0.1) # wrong
p.lamdas = (ctypes.c_double)(0.95)  
p.lamdah = (ctypes.c_double)(0.95)
p.rhomax = (ctypes.c_double)(525000)
p.rhomin= (ctypes.c_double)(525000) 
p.f2= (ctypes.c_double)(7000)
p.f1= (ctypes.c_double)(4)
p.gammac = (ctypes.c_double)(131000)
p.gammaw = (ctypes.c_double)(0.000000667)
p.gammax= (ctypes.c_double)(0.12)
p.cgl= (ctypes.c_double)(1.45)
p.cgr= (ctypes.c_double)(1.25)
p.cgw= (ctypes.c_double)(1.37)  
p.deltal= (ctypes.c_double)(0.095)  
p.deltar = (ctypes.c_double)(0.15)
p.sl= (ctypes.c_double)(1)
p.sla= (ctypes.c_double)(0.0141)
p.sr= (ctypes.c_double)(1)
p.so= (ctypes.c_double)(0.05)
p.rr= (ctypes.c_double)(0.00015)
p.rhor= (ctypes.c_double)(160000)
p.rml= (ctypes.c_double)(2.5)
p.rms = (ctypes.c_double)(0.05)
p.rmr= (ctypes.c_double)(1.5)
p.etaB= (ctypes.c_double)(0.045)
p.k= (ctypes.c_double)(0.7)
p.epsg= (ctypes.c_double)(6.75)
p.M= (ctypes.c_double)(0.95)
p.alpha= (ctypes.c_double)(0.365)
p.R0= (ctypes.c_double)(1.909)
p.R40= (ctypes.c_double)(5.592)



o = Outputs()


model.argtypes = [
  ctypes.POINTER(Inputs),
  ctypes.POINTER(gparm),
  ctypes.POINTER(Outputs),
]


model(p,g,o)
