import requests, time, json
from ctypes import *

def model():
    acgca_input = requests.get(
        "https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/model",
        headers = {'x-api-key': 'AZlzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW'}
    )


    # json
    data = acgca_input.json()
    print(data)

    if data == {}:
        print("Skipped")
        time.sleep(10)
        return


    model_input = data["input"]
    test_input = model_input.encode('ascii', 'igonre')

    body_inputs = json.loads(test_input)
    print("USER INPUT RECEIVED")
    model_inputs = body_inputs['body']
    print(model_inputs)
    print('\n')

    # wrapper run
    model_outputs = run_alg(model_inputs)

    print("OUTPUTS FROM MODEL")
    print(model_outputs)


    payload = {"run_id": data["run_id"], "output": model_outputs}


    requests.post(
        "https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/model",
        data = model_outputs,
        headers = {'x-api-key': 'AZlzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
        'X-Run-ID': data["run_id"] }
    )


def run_alg(input):
    import json
    import ctypes

    import os.path

    # lower casex
    mydll = ctypes.CDLL("/Users/alexbentley/Documents/GitHub/capstone19-20/ACGCA_Instance/Model/ACGCA/src/ACGCA.so")
    model = mydll.run_model


    # Need to include t variable for time
    class Inputs(ctypes.Structure):
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
            ('K',ctypes.c_double),
            ('epsg',ctypes.c_double),
            ('M',ctypes.c_double),
            ('alpha',ctypes.c_double),
            ('R0',ctypes.c_double),
            ('R40',ctypes.c_double),
            ('t',ctypes.c_double),
            ('r0',ctypes.c_double),
            ('io',ctypes.c_double),
            ]

    N = (int(input['t'])) + 1

    class Outputs(ctypes.Structure):
        _fields_ = [
            ('APARout',(ctypes.c_double*N)),
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
    g.deltat =(ctypes.c_double)(0.0625)
    g.T = (ctypes.c_double)(10)
    g.tolerance = (ctypes.c_double)(0.00001)
    # suppose the default value just for current testing
    try:
        p = Inputs()

        # these arent linking with input file. input cant grab .hmax
        p.hmax = (ctypes.c_double)(float(input['hmax']))#(27.5)
        p.phih = (ctypes.c_double)(float(input['phih']))#(263)
        p.eta = (ctypes.c_double)(float(input['eta']))#(0.64)
        p.etaB = (ctypes.c_double)(float(input['etaB']))#(0.045)
        p.swmax = (ctypes.c_double)(float(input['swmax']))#(0.1) # wrong
        p.lamdas = (ctypes.c_double)(float(input['lamda']))#(0.95)
        p.lamdah = (ctypes.c_double)(float(input['lamda']))#(0.95)
        p.rhomax = (ctypes.c_double)(float(input['rhomax']))#(525000)
        p.rhomin= (ctypes.c_double)(float(input['rhomax']))#(525000)
        p.f2= (ctypes.c_double)(float(input['f2']))#(7000)
        p.f1= (ctypes.c_double)(float(input['f1']))#(4)
        p.gammac = (ctypes.c_double)(float(input['gammac']))#(131000)
        p.gammaw = (ctypes.c_double)(float(input['gammaw']))#(0.000000667)
        p.gammax= (ctypes.c_double)(float(input['gammax']))#(0.12)
        p.cgl= (ctypes.c_double)(float(input['cgl']))#(1.45)
        p.cgr= (ctypes.c_double)(float(input['cgr']))#(1.25)
        p.cgw= (ctypes.c_double)(float(input['cgw']))#(1.37)
        p.deltal= (ctypes.c_double)(float(input['deltal']))#(0.095)
        p.deltar = (ctypes.c_double)(float(input['deltar']))#(0.15)
        p.sl= (ctypes.c_double)(float(input['sl']))#(1)
        p.sla= (ctypes.c_double)(float(input['sla']))#(0.0141)
        p.sr= (ctypes.c_double)(1)#(float(input['sr']))(1)
        p.so= (ctypes.c_double)(0.05)#(float(input['so']))#(0.05)
        p.rr= (ctypes.c_double)(float(input['rr']))#(0.00015)
        p.rhor= (ctypes.c_double)(float(input['rhor']))#(160000)
        p.rml= (ctypes.c_double)(float(input['rml']))#(2.5)
        p.rms = (ctypes.c_double)(float(input['rms']))#(0.05)
        p.rmr= (ctypes.c_double)(float(input['rmr']))#(1.5)

        p.drcrit= (ctypes.c_double)(1)
        p.drinit= (ctypes.c_double)(1)

        p.K= (ctypes.c_double)(float(input['k']))#(0.7)
        p.epsg= (ctypes.c_double)(float(input['epsg']))#(6.75)
        p.M= (ctypes.c_double)(float(input['m']))#(0.95)
        p.alpha= (ctypes.c_double)(float(input['alpha']))#(0.365)
        p.R0= (ctypes.c_double)(float(input['r0']))#(1.909)
        p.R40= (ctypes.c_double)(float(input['r40']))#(5.592)
        p.t= (ctypes.c_double)(float(input['t']))#(5.592)
        p.r0= (ctypes.c_double)(float(input['radius']))#(5.592)
        p.io= (ctypes.c_double)(float(input['io']))#(5.592)

    except:
        pass

    o = Outputs()


    model.argtypes = [
    ctypes.POINTER(Inputs),
    ctypes.POINTER(gparm),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_int),
    ctypes.POINTER(ctypes.c_int),
    ctypes.POINTER(ctypes.c_int),
    ]


    model(p,g,o.APARout,o.h,o.hh2,o.hC2,o.hB2,o.hBH2,o.r,o.rB2,o.rC2,o.rBH,
        o.sw2,o.vts2,o.vt2,o.vth2,o.sa2,o.la2,o.ra2,o.dr2,o.xa2,o.bl2,o.br2,
        o.bt2,o.bts2,o.bth2,o.boh2,o.bos2,o.bo2,o.bs2,o.cs2,o.clr2,o.fl2,o.fr2,
        o.ft2,o.fo2,o.rfl2,o.rfr2,o.rfs2,o.egrow2,o.ex2,o.rtrans2,o.light2,
        o.nut2,o.deltas2,o.LAI2,o.status2,o.errorind,o.growth_st)


    output = {
        'APARout':o.APARout,
        'h':o.h,
        'hh2':o.hh2,
        'hC2':o.hC2,
        'hB2':o.hB2,
        'hBH2':o.hBH2,
        'r':o.r,
        'rB2':o.rB2,
        'rC2':o.rC2,
        'rBH':o.rBH,
        'sw2':o.sw2,
        'vts2':o.vts2,
        'vt2':o.vt2,
        'vth2':o.vth2,
        'sa2':o.sa2,
        'la2':o.la2,
        'ra2':o.ra2,
        'dr2':o.dr2,
        'xa2':o.xa2,
        'bl2':o.bl2,
        'br2':o.br2,
        'bt2':o.bt2,
        'bts2':o.bts2,
        'bth2':o.bth2,
        'boh2':o.boh2,
        'bos2':o.bos2,
        'bo2':o.bo2,
        'bs2':o.bs2,
        'cs2':o.cs2,
        'clr2':o.clr2,
        'fl2':o.fl2,
        'fr2':o.fr2,
        'ft2':o.ft2,
        'fo2':o.fo2,
        'rfl2':o.rfl2,
        'rfr2':o.rfr2,
        'rfs2':o.rfs2,
        'egrow2':o.egrow2,
        'ex2':o.ex2,
        'rtrans2':o.rtrans2,
        'light2':o.light2,
        'nut2':o.nut2,
        'deltas2':o.deltas2,
        'LAI2':o.LAI2,
        'status2':o.status2,
        'errorind':o.errorind,
        'growth_st':o.growth_st
    }


    print(o.fl2[9])
    return output


if __name__ == "__main__":
    while True:
        model()
        # try:
        #     model()
        # except:
        #     print("Errored")
