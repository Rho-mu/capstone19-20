#! python3
import ctypes
import requests
import json

# get the dll needs to be fixed
mydll = ctypes.WinDLL('C:\Users\user、\Desktop\model')
# call the growthloop function
runModel = mydll.growthloop
# location of json file read json
with open('path_to_file/person.json', 'r') as f:
  data = json.load(f)



inputs_filter = {
    # "": lambda data: data == "",
    # sparms *p, 
    # gparms *gp, 
    # double *Io, 
    # double *r0, 
    # int *t,
	# double *Hc, 
    # double *LAIF, 
    # Forestparms *ForParms, 
    # double APARout[],
	# double h[],
	# double hh2[],
	# double hC2[],
	# double hB2[],
	# double hBH2[],
	# double r[],
	# double rB2[],
	# double rC2[],
	# double rBH[],
	# double sw2[],
	# double vts2[],
	# double vt2[],
	# double vth2[],
	# double sa2[],
	# double la2[],
	# double ra2[],
	# double dr2[],
	# double xa2[],
	# double bl2[],
	# double br2[],
	# double bt2[],
	# double bts2[],
	# double bth2[],
	# double boh2[],
	# double bos2[],
	# double bo2[],
	# double bs2[],

	# double cs2[],
	# double clr2[],
	# double fl2[],
	# double fr2[],
	# double ft2[],
	# double fo2[],
	# double rfl2[],
	# double rfr2[],
	# double rfs2[],

	# double egrow2[],
	# double ex2[],
	# double rtrans2[],
	# double light2[],
	# double nut2[],
	# double deltas2[],
	# double LAI2[],
	# int status2[],
	# int errorind[],
	# int growth_st[]

    "p": lambda data: data == "data.p", 
    "gp": lambda data: data == "data.gp", 
    "Io": lambda data: data == "data.Io", 
    "r0": lambda data: data == "data.r0", 
    "t": lambda data: data == "data.t",
	"Hc": lambda data: data == "data.Hc", 
    "LAIF": lambda data: data == "data.LAIF", 
    "ForParms": lambda data: data == "data.ForParms", 
    "APARout": lambda data: data == "data.APARout",
	"h": lambda data: data == "data.h",
	"hh2": lambda data: data == "data.hh2",
	"hC2": lambda data: data == "data.hC2",
	"hB2": lambda data: data == "data.hB2",
	"hBH2": lambda data: data == "data.hBH2",
	"r": lambda data: data == "data.r",
	"rB2": lambda data: data == "data.rB2",
	"rC2": lambda data: data == "data.rC2",
	"rBH": lambda data: data == "data.rBH",
	"sw2": lambda data: data == "data.sw2",
	"vts2": lambda data: data == "data.vts2",
	"vt2": lambda data: data == "data.vt2",
	"vth2": lambda data: data == "data.vth2",
	"sa2": lambda data: data == "data.sa2",
	"la2": lambda data: data == "data.la2",
	"ra2": lambda data: data == "data.ra2",
	"dr2": lambda data: data == "data.dr2",
	"xa2": lambda data: data == "data.xa2",
	"bl2": lambda data: data == "data.bl2",
	"br2": lambda data: data == "data.br2",
	"bt2": lambda data: data == "data.bt2",
	"bts2": lambda data: data == "data.bts2",
	"bth2": lambda data: data == "data.bth2",
	"boh2": lambda data: data == "data.boh2",
	"bos2": lambda data: data == "",
	"bo2": lambda data: data == "",
	"bs2": lambda data: data == "",

	"cs2": lambda data: data == "",
	"clr2": lambda data: data == "",
	"fl2": lambda data: data == "",
	"fr2": lambda data: data == "",
	"ft2": lambda data: data == "",
	"fo2": lambda data: data == "",
	"rfl2": lambda data: data == "",
	"rfr2": lambda data: data == "",
	"rfs2": lambda data: data == "",

	"egrow2": lambda data: data == "",
	"ex2": lambda data: data == "",
	"rtrans2": lambda data: data == "",
	"light2": lambda data: data == "",
	"nut2": lambda data: data == "",
	"deltas2": lambda data: data == "",
	"LAI2": lambda data: data == "",
	"status2": lambda data: data == "",
	"errorind": lambda data: data == "",
	"growth_st": lambda data: data == ""
}





def main():
	get_url = ""
	post_url = ""

	data = requests.get(get_url)
    
	inputs = data.json()["body"]
	ouputs = []
	for key, value in inputs.items():
		if inputs_filter[key](value):
			pass
		else:
			continue
	
	requests.post(post_url, ouputs)

if __name__ == "__main__":
    main()
