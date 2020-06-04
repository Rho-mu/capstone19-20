<template>
  <div>
    <div class="inputContainer">
      <div class="containerTitle">Inputs Specification</div>
      <button class="collapsible">Default values</button>
        <div class="content">
          <br>
          <button @click="setDefault('Red Maple')">Red maple</button>
          <br><br>
          <button @click="setDefault('Loblolly Pine')">Loblolly pine</button>
          <br><br>
        </div>

      <button class="collapsible">Allometries and biomass partitioning</button>
        <div class="content">
          <br>
          <label for="phih"> phip:</label><br>
          <input id="phih" type="text" v-model="postBody.phih" placeholder="phih > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSlope of height vs trunk radius (r) curve at r = 0 m<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="eta"> eta:</label><br>
          <input id="eta" type="text" v-model="postBody.eta" placeholder="0 < eta < 1" min="0" max="1">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspRelative height that trunk transitions from paraboloid to cone<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="lamda"> lamda:</label><br>
          <input id="lamda" type="text" v-model="postBody.lamda" placeholder="0 < lamda < 1" min="0" max="1" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspProportionality between trunk and non-trunk biomass<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="f2"> f2 (RA:LA):</label><br>
          <input id="f2" type="text" v-model="postBody.f2" placeholder="f2 (RA:LA) > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspFine root area to leaf area ratio<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="f1"> f1 (LA:XA):</label><br>
          <input id="f1" type="text" v-model="postBody.f1" placeholder="f1 (LA:XA) > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspLeaf area to xylem conducting area ratio<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="gammax"> gammaX (XA:SA):</label><br>
          <input id="gammax" type="text" v-model="postBody.gammax" placeholder="0 <gammaX (XA:SA)< 1" min="0" max="1">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspXylem conducting area to sapwood area ratio<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="etaB"> etaB:</label><br>
          <input id="etaB" type="text" v-model="postBody.etaB" placeholder="0 < etaB < eta" min="0" :disabled='postBody.eta==""'>
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspRelative height at which trunk transitions from a neiloid to a paraboloid<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,eta)
            </p></span><br>

          <label for="m"> M:</label><br>
          <input id="m" type="text" v-model="postBody.m" placeholder="0 < m < 1" min="0" max="1">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum relative crown depth<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="r0"> R0:</label><br>
          <input id="r0" type="text" v-model="postBody.r0" placeholder="R0 > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum potential crown radius of a tree with diameter at breast height of 0 cm (i.e., for a tree that is exactly 1.37 m tall)<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="r40"> R40:</label><br>
          <input id="r40" type="text" v-model="postBody.r40" placeholder="R40 > R0" min="0" :disabled='postBody.r0==""'>
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum potential crown radius of a tree with diameter at breast height of 40 cm<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (R0,+&#8734)
            </p></span><br>

          <label for="alpha"> alpha:</label><br>
          <input id="alpha" type="text" v-model="postBody.alpha" placeholder="alpha > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspCrown curvature parameter<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>
          <!-- <div class="paddingForHelptip"></div>
          <br><br> -->
        </div>

      <button class="collapsible">Tree and organ size traits</button>
        <div class="content">
          <br>
          <label for="hmax"> Hmax (m):</label><br>
          <input id="hmax" type="text" v-model="postBody.hmax" placeholder="0 < Hmax < 127" min="0" max="127">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum tree height<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (R0,127)
            </p></span><br>

          <label for="swmax"> SWmax (m):</label><br>
          <input id="swmax" type="text" v-model="postBody.swmax" placeholder="SWmax > 0" min="0"  >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum sapwood width<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="rr"> rr (m):</label><br>
          <input id="rr" type="text" v-model="postBody.rr" placeholder="rr > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspAverage fine root radius<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>
          <div class="paddingForHelptip"></div>
          <br><br>
        </div>

      <button class="collapsible">Structural traits</button>
        <div class="content">
          <br>
          <label for="rhomax"> WD (g dw m-3):</label><br>
          <input id="rhomax" type="text" v-model="postBody.rhomax" placeholder="WD > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspWood density<br>
              <span class="separator"></span>
              Unit: g dw m-3<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="gammaw"> gammaW (m3g dw-1):</label><br>
          <input id="gammaw" type="text" v-model="postBody.gammaw" placeholder="gammaW">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbsp(Inverse) density of sapwood structural tissue<br>
              <span class="separator"></span>
              Unit: m3g dw-1<br>
              <span class="separator"></span>
              Constraint: none
            </p></span><br>

          <label for="sla"> sla (m2g dw-1):</label><br>
          <input id="sla" type="text" v-model="postBody.sla" placeholder="sla > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSpecific leaf area<br>
              <span class="separator"></span>
              Unit: m2g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>
          <div class="paddingForHelptip"></div>
          <br>
        </div>

      <button class="collapsible">Turn-over and senescence traits</button>
        <div class="content">
          <br>
          <label for="sl"> sL (year-1):</label><br>
          <input id="sl" type="text" v-model="postBody.sl" placeholder="sL > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSenescence rate of leaves<br>
              <span class="separator"></span>
              Unit: year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="sr"> sR (year-1):</label><br>
          <input id="sr" type="text" v-model="postBody.sr" placeholder="sR > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSenescence rate of fine roots<br>
              <span class="separator"></span>
              Unit: year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="so"> sO (year-1):</label><br>
          <input id="so" type="text" v-model="postBody.so" placeholder="sO > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSenescence rate of or coarse roots and branches<br>
              <span class="separator"></span>
              Unit: year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>
          <div class="paddingForHelptip"></div>
          <br><br><br>
        </div><br>

      <div class="slidecontainer">
        <div>
          <label> Initial radius (m): </label><br>
              <input type="text" v-model="postBody.radius" placeholder="radius > 0" min="0" >
              <span class="help-tip">
                <p>
                  &nbspInformation Box<br>
                  <span class="separator"></span>
                  Name:&nbspInitial radius<br>
                  <span class="separator"></span>
                  Unit: m<br>
                  <span class="separator"></span>
                  Constraint: (0,+&#8734)
              </p></span>
        </div><br>

        <div class="lightSlider">
          <label> Light level: {{ (postBody.io / 20.6).toFixed(0)}}%</label>
          <p>0 <input type="range" class="inputSlider"  min="0" max="2060" v-model="postBody.io"> 100%</p><!--@input="draw()" Used for testing, but don't have it connected yet.-->
        </div>

        <div class="timeSlider">
          <label for="t">Total time: {{postBody.t}} </label>
          <p>0 <input type="range" class="inputSlider" min="1" max="450" v-model="postBody.t"> 450</p>
        </div>
      </div>

      <div id="error-message"><br>
          {{this.errorMessage}}
      </div>
      <button class="runButton" id="runButton" :disabled='isDisabled()' @click="postData()">RUN</button>
      <button class="resetButton" @click="resetData()">Reset</button>
      <br>
    </div>
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
        this.$emit('postResetFlagToParent', this.resetFlag)
      },

      initializeWebpage() {
        this.postBody.io = 1030 // Set light level to 1000.
        this.postBody.t = 100   // Set time to 100.

        /////////////// collapsible Menus ///////////////
        var coll = document.getElementsByClassName("collapsible")
        var i

        for (i = 0; i < coll.length; i++) {
          coll[i].addEventListener("click",
          function() {
            this.classList.toggle("active")
            var content = this.nextElementSibling
            if (content.style.maxHeight)
            {
              content.style.maxHeight = null
            }
            else
            {
              content.style.maxHeight = content.scrollHeight + "px"
            }
          })
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


          //document.getElementById("timeStepSlider").setAttribute("max", this.postBody.t) // Sets max value for timestep slider.
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

        },
            (error) => { console.log(error.request)}
        )
      }, // END: getData()

      checkForNull(){
        var temporaryIsDisable=false

        //start checking null
        temporaryIsDisable=temporaryIsDisable || (this.postBody.hmax==="");
        temporaryIsDisable=temporaryIsDisable || (this.postBody.phih==="");
        temporaryIsDisable=temporaryIsDisable || (this.postBody.eta==="");
        temporaryIsDisable=temporaryIsDisable || (this.postBody.swmax==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.lamda==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.rhomax==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.f2==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.f1==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.gammac==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.gammaw==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.gammax==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.cgl==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.cgr==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.cgw==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.deltal==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.deltar==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.sl==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.sla==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.so==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.sr==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.rr==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.rhor==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.rml==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.rms==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.rmr==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.etaB==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.k==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.epsg==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.m==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.alpha==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.r0==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.r40==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.radius==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.io==="") ;
        temporaryIsDisable=temporaryIsDisable || (this.postBody.t==="") ;
        this.isDisable=temporaryIsDisable;

        if(this.isDisable){
           this.errorMessage="ERROR: Please fill out all of the fields";
        }
        else{
          this.errorMessage=""
        }

      }, // END: checkForNull()

      hardLimit(){
        if (this.postBody.phih < 0) this.postBody.phih= 0;

        if (this.postBody.eta < 0) this.postBody.eta = 0;
        if (this.postBody.eta > 1) this.postBody.eta= 1;

        if (this.postBody.lamda < 0) this.postBody.lamda = 0;
        if (this.postBody.lamda > 1) this.postBody.lamda= 1;

        if (this.postBody.f2 < 0) this.postBody.f2 = 0;

        if (this.postBody.f1 < 0) this.postBody.f1 = 0;

        if (this.postBody.gammax < 0) this.postBody.gammax = 0;
        if (this.postBody.gammax > 1) this.postBody.gammax= 1;

        if (this.postBody.etaB < 0) this.postBody.etaB = 0;
        if(this.postBody.eta!=""){
        if (this.postBody.etaB > eta) this.postBody.etaB= eta;
        }

        if (this.postBody.m < 0) this.postBody.m = 0;
        if (this.postBody.m > 1) this.postBody.m= 1;

        if (this.postBody.alpha < 0) this.postBody.alpha = 0;

        if (this.postBody.r0 < 0) this.postBody.r0 = 0;

        if(this.postBody.r0!=""){
        if (this.postBody.r40 < r0) this.postBody.r40 = r0;
        }

        //Group A end

        if (this.postBody.hmax < 0) this.postBody.hmax= 0;
        if (this.postBody.hmax> 127) this.postBody.hmax= 127;

        if (this.postBody.swmax < 0) this.postBody.swmax= 0;

        if (this.postBody.rr < 0) this.postBody.rr= 0;

        //Group B end

        if (this.postBody.rhomax < 0) this.postBody.rhomax= 0;

        if (this.postBody.gammaw < 0) this.postBody.gammaw= 0;

        if (this.postBody.sla < 0) this.postBody.sla= 0;

        //Group C end

        if (this.postBody.gammac < 0) this.postBody.gammac= 0;

        if (this.postBody.cgl < 0) this.postBody.cgl= 0;

        if (this.postBody.cgr < 0) this.postBody.cgr= 0;

        if (this.postBody.cgw < 0) this.postBody.cgw= 0;

        if (this.postBody.deltal < 0) this.postBody.deltal= 0;

        if (this.postBody.deltar < 0) this.postBody.deltar= 0;

        if (this.postBody.rhor < 0) this.postBody.rhor= 0;

        if (this.postBody.rml < 0) this.postBody.rml= 0;

        if (this.postBody.rms < 0) this.postBody.rms= 0;

        if (this.postBody.rmr < 0) this.postBody.rmr= 0;

        if (this.postBody.k < 0) this.postBody.k= 0;

        if (this.postBody.epsg < 0) this.postBody.epsg= 0;
        if (this.postBody.epsg> 15.73) this.postBody.epsg= 15.73;

        //Group D end

        if (this.postBody.sl < 0) this.postBody.sl= 0;

        if (this.postBody.sr < 0) this.postBody.sr= 0;

        if (this.postBody.so < 0) this.postBody.so= 0;

        if (this.postBody.radius < 0) this.postBody.gammac= 0;

        if (this.postBody.io < 0) this.postBody.io = 0;
        if (this.postBody.io > 2060) this.postBody.io= 2060;

        if (this.postBody.t < 0) this.postBody.cgr= 0;

        //Group E end


      }, // END: hardLimit()

      isDisabled() {
        this.checkForNull();
        this.hardLimit();
        return this.isDisable;
      }, // END: isDisabled()
    }, // END: methods

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
    display: inline-block;
    float:left;
    padding: 20px 10px 20px 10px;
    margin: auto;
    border: none;
    border-radius: 10px;
    font-size: 16px;
    color:black;
    width:17%;
    background-color: #b9b9b9;
    background-image: url("../assets/InputBack.png");
    background-repeat: repeat-x;
    color: white;
  }


  .inputContainer button {
    color: black;
    display: inline-block;
    height: 40px;
    padding: 10px 10px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 13px;
    background-color: #FFF;
    width: 100%;
  }

  .inputContainer button:hover {
    background-color: #EEE;
  }


  .slidecontainer {
    text-align: left;
  }

  .slidecontainer input {
    width: 78%;
    height: 15px;
    border-radius: 10px;
    border-width: thin;

  }


  .runButton {
    background-color: #44c767 !important;
    padding: 10px 30px;
    color:#ffffff !important;
  }

  .runButton:hover {
    background-color: #EEE !important;
    color: black !important;
  }

  .runButton:disabled {
    cursor: auto;
    color: white;
    background-color: lightgray !important;
  }


  #error-message{
    color: white;
    font-weight: bold;
  }


  .collapsible {
    color: black;
    border: none;
    text-align: left;
  }

  .collapsible:after {
    content: '\02795';
    font-size: 10px !important;
    color: white;
    float: right;
  }

  .active:after {
    content: "\2796";
  }

  .content {
    padding: 0px 10px;
    max-height: 0;
    overflow: hidden;
    transition: max-height 0.2s ease-out;
    background-color: #999999;
    border-radius: 15px;
  }

  .content button {
    margin-top: 10px;
    background-color: #44c767;
    border-radius: 20px;
    border: none;
    padding: 10px 30px;
    color:#ffffff;
    font-family:Arial;
    font-size: 13px;
    display: inline-block;
  }

  .content button:hover {
    background-color: #EEE;
    color: black;
  }

  input[type=text] {
    border-radius:5px;
    padding-left: 5px;
  }

  .inputSlider {
    -webkit-appearance: none;
    width: 075%;
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

  .inputSlider::-moz-range-thumb {
    width: 25px;
    height: 25px;
    background: #44c767;
    cursor: pointer;
    border-radius: 50%;
  }

  .help-tip{
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

  .help-tip:before{
    content:'?';
    font-weight: bold;
    color:#fff;
  }

  .help-tip:hover p{
    display: inline-block;
    transform-origin: 100% 0%;

    -webkit-animation: fadeIn 0.3s ease-in-out;
    animation: fadeIn 0.3s ease-in-out;
  }

  .help-tip p{
    display:none;
    text-align: left;
    background-color: green;
    padding: 20px;
    width: 700%;
    position: absolute;
    border-radius: 3px;
    box-shadow: 1px 1px 1px rgba(0, 0, 0, 0.2);
    right: -4px;
    color: #fff;
    font-size: 13px;
    line-height: 1.4;
    border-radius: 25px;
    z-index: 100;
  }

  .help-tip p:after{ //Prevents the tooltip from being hidden
      width:100%;
      height:40px;
      content:'';
      position: relative;
      top:-40px;
      left:0;
  }

  .separator {
      border-top: 1px solid #333;
      border-radius:1px;
      width: 100%;
      height: 3px;
      display: block;
      border-color: white;
  }

  .paddingForHelptip {
    height:120px;
  }


  @-webkit-keyframes fadeIn {
      0% { opacity:0; transform: scale(0.6); }
      100% { opacity:100%; transform: scale(1); }
  }

  @keyframes fadeIn {
      0% { opacity:0; }
      100% { opacity:100%; }
  }


  label {
    font-size: 15px;
  }

  .collapsible button {
    font-size: 10px;
    color: black;
    z-index: 0;
  }

  .lightSlider p {
    font-size: 13px;
  }

  .timeSlider p {
    font-size: 13px;
  }

  .setSceneContainer button {
    font-size: 13px;
  }
</style>
