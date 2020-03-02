import json
import ctypes
from ctypes import *

mydll = ctypes.WinDLL(r'C:\Users\user、\Desktop\model\ACGCA.dll')
growthloop = mydll.growthloop

# wrap function
def wrap_function(lib, funcname, restype, argtypes):
    # Simplify wrapping ctypes functions
    func = lib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

# make C structure into python
class tparms(ctypes.Structure)
  _fields_=[('rinit', ctypes.c_double)]

class sparms(ctypes.Structure)
  _fields_=[('hmax', ctypes.c_double), ('phih',ctypes.c_double), ('eta',ctypes.c_double), ('etaB',ctypes.c_double),
  ('swmax',ctypes.c_double),('lamdas',ctypes.c_double), ('lamdah',ctypes.c_double),('rhomax',ctypes.c_double),
  ('rhomin',ctypes.c_double),  ('f2',ctypes.c_double), ('f1',ctypes.c_double), ('gammac',ctypes.c_double),
  ('gammaw',ctypes.c_double),('gammax',ctypes.c_double), ('cgl',ctypes.c_double),  ('cgr',ctypes.c_double),
  ('cgw',ctypes.c_double),('deltal',ctypes.c_double),('deltar',ctypes.c_double),('sl',ctypes.c_double),('sla',ctypes.c_double),('sr',ctypes.c_double),
  ('so',ctypes.c_double),('rr',ctypes.c_double),('rhor',ctypes.c_double),('rml',ctypes.c_double),('rms',ctypes.c_double),('rmr',ctypes.c_double),
  ('drcrit',ctypes.c_double),('drinit',ctypes.c_double),  ('k',ctypes.c_double),('epsg',ctypes.c_double),('M',ctypes.c_double),('alpha',ctypes.c_double),
  ('R0',ctypes.c_double),('R40',ctypes.c_double)]

class Larea(ctypes.Structure)
  _fields_=[('tot',ctypes.c_double),('top',ctypes.c_double),('bot',ctypes.c_double)]

class Forestparms(ctypes.Structure)
  _fields_=[('hB',ctypes.c_double),('hC',ctypes.c_double),('H',ctypes.c_double),('hBH',ctypes.c_double)]

# read json
with open('test.json', encoding='utf-8') as f:
    line = f.readline()
    d = json.loads(line)
    p = d['p']
    gp = d['gp']
    Io = d['Io']
    r0 = d['r0']
    t = d['t']
    Hc = d['Hc']
    r0 = d['r0']
    LAIF = d['LAIF']
    ForParms = d['ForParms']
    APARout = d['APARout']
    h = d['h']
    hh2 = d['hh2']
    hC2 = d['hC2']
    hB2 = d['hB2']
    hBH2 = d['hBH2']
    r = d['r']
    rB2 = d['rB2']
    rC2 = d['rC2']
    rBH = d['rBH']
    sw2 = d['sw2']
    vts2 = d['vts2']
    vt2 = d['vt2']
    vth2 = d['vth2']
    sa2 = d['sa2']
    la2 = d['la2']
    ra2 = d['ra2']
    dr2 = d['dr2']
    xa2 = d['xa2']
    bl2 = d['bl2']
    br2 = d['br2']
    bt2 = d['bt2']
    bts2 = d['bts2']
    bth2 = d['bth2']
    boh2 = d['boh2']
    bos2 = d['bos2']
    bo2 = d['bo2']
    bs2 = d['bs2']

    cs2 = d['cs2']
    clr2 = d['clr2']
    fl2 = d['fl2']
    fr2 = d['fr2']
    ft2 = d['ft2']
    fo2 = d['fo2']
    rfl2 = d['rfl2']    
    rfr2 = d['rfr2']
    rfs2 = d['rfs2']

    egrow2 = d['egrow2']
    ex2 = d['ex2']
    rtrans2 = d['rtrans2']
    light2 = d['light2']
    nut2 = d['nut2']
    deltas2 = d['deltas2']
    LAI2 = d['LAI2']
    status2 = d['status2']
    errorind = d['errorind']
    growth_st = d['growth_st']



# growthloop.argtypes = (   ctypes.POINTER(ctypes.c_double), 
  #ctypes.POINTER(ctypes.c_double),ctypes.POINTER(ctypes.c_int),ctypes.POINTER(ctypes.c_double),
  # ctypes.POINTER(ctypes.c_double),)

growthloop = wrap_function(mydll, 'growthloop', None, ([sparms],[gparms],[Forestparms],c_int,c_double, ctypes.POINTER(ctypes.c_double),ctypes.POINTER(ctypes.c_int))

growthloop(sparms *p, gparms *gp,   *Io,   *r0, int *t,
	  *Hc,   *LAIF, Forestparms *ForParms,   APARout , h ,
	  hh2 ,
	  hC2 ,
	  hB2 ,
	  hBH2 ,
	  r ,
	  rB2 ,
	  rC2 ,
	  rBH ,
	  sw2 ,
	  vts2 ,
	  vt2 ,
	  vth2 ,
	  sa2 ,
	  la2 ,
	  ra2 ,
	  dr2 ,
	  xa2 ,
	  bl2 ,
	  br2 ,
	  bt2 ,
	  bts2 ,
	  bth2 ,
	  boh2 ,
	  bos2 ,
	  bo2 ,
	  bs2 ,

	  cs2 ,
	  clr2 ,
	  fl2 ,
	  fr2 ,
	  ft2 ,
	  fo2 ,
	  rfl2 ,
	  rfr2 ,
	  rfs2 ,

	  egrow2 ,
	  ex2 ,
	  rtrans2 ,
	  light2 ,
	  nut2 ,
	  deltas2 ,
	  LAI2 ,
	status2 ,
	errorind ,
	growth_st                
)

