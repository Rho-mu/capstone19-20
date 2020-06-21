<template>
  <div class="inputContainer">
    <form @submit.prevent="postData">
      <div class="containerTitle">Inputs Specification</div>
      <button type="button" class="accordion">Default values</button>
        <div class="panel">
          <br>
          <button type="button" @click="setDefault('Red Maple')">Red maple</button>
          <br><br>
          <button type="button" @click="setDefault('Loblolly Pine')">Loblolly pine</button>
          <br><br>
        </div>

      <button type="button" class="accordion">Allometries and biomass partitioning</button>
        <div class="panel">
          <br>
          <label> phip:</label><br>
          <input type="number" v-model="postBody.phih" step="any" placeholder="phih > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> eta:</label><br>
          <input type="number" v-model="postBody.eta" step="any" placeholder="0 < eta < 1" min="0" max="1" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> lamda:</label><br>
          <input type="number" v-model="postBody.lamda" step="any" placeholder="0 < lamda < 1" min="0" max="1" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> f2 (RA:LA):</label><br>
          <input type="number" v-model="postBody.f2" step="any" placeholder="f2 (RA:LA) > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> f1 (LA:XA):</label><br>
          <input type="number" v-model="postBody.f1" step="any" placeholder="f1 (LA:XA) > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> gammaX (XA:SA):</label><br>
          <input type="number" v-model="postBody.gammax" step="any" placeholder="0 <gammaX (XA:SA)< 1" min="0" max="1" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> etaB:</label><br>
          <input type="number" v-model="postBody.etaB" step="any" placeholder="0 < etaB < eta" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> M:</label><br>
          <input type="number" v-model="postBody.m" step="any" placeholder="0 < m < 1" min="0" max="1" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> R0:</label><br>
          <input type="number" v-model="postBody.r0" step="any" placeholder="R0 > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> R40:</label><br>
          <input type="number" v-model="postBody.r40" step="any" placeholder="R40 > R0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> alpha:</label><br>
          <input type="number" v-model="postBody.alpha" step="any" placeholder="alpha > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br><br>
        </div>

      <button type="button" class="accordion">Tree and organ size traits</button>
        <div class="panel">
          <br>
          <label> Hmax (m):</label><br>
          <input type="number" v-model="postBody.hmax" step="any" placeholder="0 < Hmax < 127" min="0" max="127" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> SWmax (m):</label><br>
          <input type="number" v-model="postBody.swmax" step="any" placeholder="SWmax > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> rr (m):</label><br>
          <input type="number" v-model="postBody.rr" step="any" placeholder="rr > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br><br>

        </div>

      <button type="button" class="accordion">Structural traits</button>
        <div class="panel">
          <br>
          <label> WD (g dw m<sup>-3</sup>):</label><br>
          <input type="number" v-model="postBody.rhomax" step="any" placeholder="WD > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> gammaW (m3g dw<sup>-1</sup>):</label><br>
          <input type="number" v-model="postBody.gammaw" placeholder="gammaW" step="any" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> sla (m2g dw<sup>-1</sup>):</label><br>
          <input type="number" v-model="postBody.sla" step="any" placeholder="sla > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br><br>
        </div>

      <button type="button" class="accordion">Turn-over and senescence traits</button>
        <div class="panel">
          <br>
          <label> sL (year<sup>-1</sup>):</label><br>
          <input type="number" v-model="postBody.sl" step="any" placeholder="sL > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> sR (year<sup>-1</sup>):</label><br>
          <input type="number" v-model="postBody.sr" step="any" placeholder="sR > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

          <label> sO (year<sup>-1</sup>):</label><br>
          <input type="number" v-model="postBody.so" step="any" placeholder="sO > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>

        </div><br><br>

      <div class="slidecontainer">
        <div>
          <label> Initial radius (m): </label><br>
          <input type="number" v-model="postBody.radius" step="any" placeholder="radius > 0" min="0" required>
          <div class="tooltip">
            <span class="tooltiptext">Tooltip text</span>
          </div><br>
        </div><br>


        <div class="slider">
          <label> Light level: {{ (postBody.io / 20.6).toFixed(0)}}%</label><br>
          <p>0<input type="range" class="inputSlider"  min="0" max="2060" v-model="postBody.io"> 100%</p><!--@input="draw()" Used for testing, but don't have it connected yet.-->
        </div>

        <div class="slider">
          <label for="t">Total time (years): {{postBody.t}} </label><br>
          <p>0 <input type="range" class="inputSlider" min="1" max="450" v-model="postBody.t"> 450</p>
        </div>
      </div>

      <button class="runButton" id="runButton" >RUN</button>
      <button class="resetButton" @click="resetData()">Reset</button>
      <br>
    </form>

  </div>
</template>

<script>
  import axios from 'axios'

  export default {
    name: 'inputContainer',

    data() {
      return {
        postBody: {
          hmax: '',
          phih: '',
          eta: '',
          swmax: '',
          lamda: '',
          rhomax: '',
          f2: '',
          f1: '',
          gammac: '',
          gammaw: '',
          gammax: '',
          cgl: '',
          cgr: '',
          cgw: '',
          deltal: '',
          deltar: '',
          sl: '',
          sla: '',
          so: '',
          sr: '',
          rr: '',
          rhor: '',
          rml: '',
          rms: '',
          rmr: '',
          etaB: '',
          k: '',
          epsg: '',
          m: '',
          alpha: '',
          r0: '',
          r40: '',
          t: '',
          radius: '',
          io: ''
        }, // END: postBody
        isDisable: false,
        errorMessage: "",
        runID: '',
        getJson: [],
        loadingFlag: 0,
        resetFlag: 0,
        resultJson: {
            "APARout":' ',
            "h":' ',
            "hh2":' ',
            "hC2":' ',
            "hB2":' ',
            "hBH2":' ',
            "r":' ',
            "rB2":' ',
            "rC2":' ',
            "rBH":' ',
            "sw2":' ',
            "vts2":' ',
            "vt2":' ',
            "vth2":' ',
            "sa2":' ',
            "la2":' ',
            "ra2":' ',
            "dr2":' ',
            "xa2":' ',
            "bl2":' ',
            "br2":' ',
            "bt2":' ',
            "bts2":' ',
            "bth2":' ',
            "boh2":' ',
            "bos2":' ',
            "bo2":' ',
            "bs2":' ',
            "cs2":' ',
            "clr2":' ',
            "fl2":' ',
            "fr2":' ',
            "ft2":' ',
            "fo2":' ',
            "rfl2":' ',
            "rfr2":' ',
            "rfs2":' ',
            "egrow2":' ',
            "ex2":' ',
            "rtrans2":' ',
            "light2":' ',
            "nut2":' ',
            "deltas2":' ',
            "LAI2":' ',
            "status2":' ',
            "errorind":' ',
            //"growth_st":''
        } // END: resultJson
      } // END: return
    }, // END: data()

    methods: {
      resetData() {
        this.postBody.hmax=''
        this.postBody.phih=''
        this.postBody.eta=''
        this.postBody.swmax=''
        this.postBody.lamda=''
        this.postBody.rhomax=''
        this.postBody.f2=''
        this.postBody.f1=''
        this.postBody.gammac=''
        this.postBody.gammaw=''
        this.postBody.gammax=''
        this.postBody.cgl=''
        this.postBody.cgr=''
        this.postBody.cgw=''
        this.postBody.deltal=''
        this.postBody.deltar=''
        this.postBody.sl=''
        this.postBody.sla=''
        this.postBody.sr=''
        this.postBody.so=''
        this.postBody.rr=''
        this.postBody.rhor=''
        this.postBody.rml=''
        this.postBody.rms=''
        this.postBody.rmr=''
        this.postBody.etaB=''
        this.postBody.k=''
        this.postBody.epsg=''
        this.postBody.m=''
        this.postBody.alpha=''
        this.postBody.r0=''
        this.postBody.r40=''
        this.resetFlag = 1
        this.loadingFlag = 0
        this.$emit('postResetFlagToParent', this.resetFlag)
        this.$emit('postFlagToParent', this.loadingFlag)
      },

      initializeWebpage() {
        this.postBody.io = 1030 // Set light level to 1000.
        this.postBody.t = 100   // Set time to 100.

        /////////////// collapsible Menus ///////////////
        var acc = document.getElementsByClassName("accordion");
        var i;

        for (i = 0; i < acc.length; i++) {
          acc[i].addEventListener("click", function() {
            /* Toggle between adding and removing the "active" class,
            to highlight the button that controls the panel */
            this.classList.toggle("active");

            /* Toggle between hiding and showing the active panel */
            var panel = this.nextElementSibling;
            if (panel.style.display === "block") {
              panel.style.display = "none";
            } else {
              panel.style.display = "block";
            }
          });
        }
      }, // END: initializeWebpage()

      setDefault(defaultType) {
        // Set default time, light level, and initial radius
        this.postBody.t=100
        this.postBody.radius=0.05
        this.postBody.io=1030

        // Sets default values in the input fields based on the button that user clicks
        if(defaultType == "Red Maple") // Red Maple button
        {
          this.postBody.hmax=27.5
          this.postBody.phih=263
          this.postBody.eta=0.64
          this.postBody.swmax=0.1
          this.postBody.lamda=0.95
          this.postBody.rhomax=525000
          this.postBody.f2=7000
          this.postBody.f1=4
          this.postBody.gammac=131000
          this.postBody.gammaw=6.67e-7
          this.postBody.gammax=0.12
          this.postBody.cgl=1.45;
          this.postBody.cgr=1.25
          this.postBody.cgw=1.37
          this.postBody.deltal=0.095
          this.postBody.deltar=0.15
          this.postBody.sl=1
          this.postBody.sla=0.0141
          this.postBody.sr=1
          this.postBody.so=0.05
          this.postBody.rr=0.00015
          this.postBody.rhor=160000
          this.postBody.rml=1.25
          this.postBody.rms=0.025
          this.postBody.rmr=0.75
          this.postBody.etaB=0.045
          this.postBody.k=0.7
          this.postBody.epsg=6.75
          this.postBody.m=0.95
          this.postBody.alpha=0.365
          this.postBody.r0=1.909
          this.postBody.r40=5.592
        } // END: if Red Maple

        else if(defaultType == "Loblolly Pine")  // Loblolly Pine button
        {
          this.postBody.hmax=42
          this.postBody.phih=220
          this.postBody.eta=0.71
          this.postBody.swmax=0.06
          this.postBody.lamda=0.95
          this.postBody.rhomax=380000
          this.postBody.f2=2100
          this.postBody.f1=4
          this.postBody.gammac=265000
          this.postBody.gammaw=6.67e-7
          this.postBody.gammax=0.62
          this.postBody.cgl=1.51
          this.postBody.cgr=1.3
          this.postBody.cgw=1.47
          this.postBody.deltal=0.11
          this.postBody.deltar=0.08
          this.postBody.sl=0.33
          this.postBody.sla=0.00602
          this.postBody.sr=0.5
          this.postBody.so=0.05
          this.postBody.rr=0.00027
          this.postBody.rhor=200000
          this.postBody.rml=1.9
          this.postBody.rms=0.05
          this.postBody.rmr=1.5
          this.postBody.etaB=0.045
          this.postBody.k=0.55
          this.postBody.epsg=4.5
          this.postBody.m=0.95
          this.postBody.alpha=0.308
          this.postBody.r0=1.434
          this.postBody.r40=3.873
        } // END: if Loblolly Pine
      }, // END: set_default()

      postData() {
        console.log("Posting inputs..")
        axios.post('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
          headers: {
            'Content-Type': 'application/json',
            'x-api-key': 'AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
            'Access-Control-Allow-Origin': '*'
          },
          body: this.postBody
        })
        .then(response => {
          this.runID = response.headers['x-run-id'],
          //console.log("from post -- runID: ", this.runID)
          console.log("Posted inputs!")

          document.getElementById("timeStepSlider").setAttribute("max", this.postBody.t) // Sets max value for timestep slider.
          this.getData() // Call getData() to start looking for model outputs.
        })
      }, // END: postData()

      getData() {
        axios.get('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
          headers: {
            'Content-Type': 'application/json',
            'x-run-id': this.runID
          }
        })
        .then((response) => {
          this.loadingFlag = 1
          this.resetFlag = 0;


          //console.log("runID:", this.runID)
          this.getJson = response.data

          //console.log("json:", this.getJson)

          // If the JSON is not found quit out and try again in 2 seconds.
          if(this.getJson == "Not Found")
          {
            console.log("Polling for output data..")
            // Shows loading dots to let the user know that the program is running.
            var runButton = document.getElementById("runButton")
            setTimeout(function() {runButton.innerHTML = "." }, 500)
            setTimeout(function() {runButton.innerHTML = ". ."}, 1000)
            setTimeout(function() {runButton.innerHTML = ". . ."}, 1500)
            setTimeout(this.getData, 2000)
            return
          }

          var parsedobj = JSON.parse(JSON.stringify(this.resultJson))

          let newStr = this.getJson.replace(/=/g, "\":")
          let newStr2 = newStr.replace(/&/g, ",\"")
          let newStr3 = newStr2.split(",")
          let VarName = ""
          let Values = []
          let Result = {}
          for(let iter = 0; iter < newStr3.length; iter++)
          {
            let item = newStr3[iter]
            let index_array = item.split(":")
            let varName = index_array[0].substring(1, index_array[0].length-1)
            let value = parseFloat(index_array[1])
            if (varName != VarName)
            {
              Result[VarName] = Values
              Values = []
              VarName = varName
            }
            Values.push(value)
          }

          this.resultJson = Result
          // let newStr3 = "{\"" + newStr2 + "}"
          // this.resultJson = JSON.parse(newStr3)
          console.log("Output data retrieved!")
          console.log("ResultJson: \n", this.resultJson)

          document.getElementById("runButton").innerHTML = "RUN"

          //this.afterGet() // Sets up some stuff for the visualization now that the output data has been retrieved.
          this.$emit('resultJsonToParent', this.resultJson) // Sends the result json to acgca.vue to be used in outputContainer.
          this.$emit('postBodyToParent', this.postBody) // Sends the postBody to acgca.vue to be used in outputContainer.
          this.$emit('postFlagToParent', this.loadingFlag)
          this.$emit('startDrawToParent', true)
          this.$emit('postResetFlagToParent', this.resetFlag)

        },
            (error) => { console.log(error.request)}
        )
      }
    }, // END: getData()

    mounted() {
      this.initializeWebpage()
    } // END: mounted
  } // END: export default
</script>

<style scoped>
  .containerTitle {
    text-align: center;
    display: inline-block;
    font-size: 20px;
    padding-bottom: 10px;
  }

  .inputContainer {
    float:left;
    padding: 20px 10px 20px 10px;
    border: none;
    border-radius: 10px;
    width:17.5%;
    background-color: #9e9a9a;
    background-image: url("../assets/InputBack.png");
    background-position: bottom;
    background-repeat: no-repeat;
  }

  .inputContainer button {
    color: black;
    display: inline-block;
    height: 40px;
    padding: 10px;
    border: none;
    border-radius: 15px;
    padding: 10px;
    font-size: 12px;
    background-color: #FFF;
    width: 100%;
  }

  .inputContainer button:hover {
    background-color: #EEE;
  }

  .slidecontainer {
    text-align: left;
  }

  .slidecontainer input{
    width: 75%;
  }

  .runButton:enabled {
    background-color: #44c767;
    padding: 10px 30px;
    color:#ffffff;
  }

  .runButton:hover {
    background-color: #EEE;
    color: black;
  }

  .runButton:disabled {
    cursor: auto;
    color: white;
    background-color: lightgray;
  }

  .error-message{
    color: white;
    font-weight: bold;
  }

  .accordion {
    background-color: #eee;
    color: #444;
    cursor: pointer;
    padding: 18px;
    width: 100%;
    text-align: left;
    border: none;
    outline: none;
    transition: 0.4s;
  }

  .active, .accordion:hover {
    background-color: #ccc;
  }

  .panel {
    padding: 0 18px;
    background-color: transparent;
    display: none;
    overflow: visible;
  }

  .panel input {
    float: left;
    width: 80%;
  }

  .panel button {
    margin-top: 10px;
    background-color: #44c767;
    border-radius: 20px;
    border: none;
    padding: 10px 30px;
    color:#ffffff;
    font-family:Arial;
    display: inline-block;
  }

  .inputSlider {
    -webkit-appearance: none;
    width: 70%;
    height: 10px;
    border-radius: 5px;
    background: #d3d3d3;
    outline: none;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
  }

  .inputSlider:hover {
    opacity: 1;
  }

  .accordion button {
    color: black;
    z-index: 0;
  }

  /* Tooltip container */
  .tooltip {
    position: relative;
    display: inline-block;
    text-align: center;
    background-color: #44c767;
    border-radius: 50%;
    width: 24px;
    height: 24px;
    font-size: 14px;
    line-height: 26px;
    cursor: default;
  }

  .tooltip:before {
    content:'?';
    font-weight: bold;
    color:#fff;
  }

  /* Tooltip text */
  .tooltip .tooltiptext {
    visibility: hidden;
    width: 160px;
    background-color: #555;
    color: #fff;
    text-align: center;
    padding: 5px 0;
    border-radius: 6px;

    /* Position the tooltip text */
    position: absolute;
    z-index: 1;
    bottom: 125%;
    left: 50%;
    margin-left: -80px;

    /* Fade in tooltip */
    opacity: 0;
    transition: opacity 0.3s;
  }

  /* Tooltip arrow */
  .tooltip .tooltiptext::after {
    content: "";
    position: absolute;
    top: 100%;
    left: 50%;
    margin-left: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: #555 transparent transparent transparent;
  }

  /* Show the tooltip text when you mouse over the tooltip container */
  .tooltip:hover .tooltiptext {
    visibility: visible;
    opacity: 1;
  }

  .accordion:after {
    content: '\02795'; /* Unicode character for "plus" sign (+) */
    font-size: 13px;
    color: #777;
    float: right;
    margin-left: 5px;
  }

  .active:after {
    content: "\2796"; /* Unicode character for "minus" sign (-) */
  }

  label {
    font-size: 15px;
    float: left;
  }
</style>
