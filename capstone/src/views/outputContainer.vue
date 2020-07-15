<template>
  <div>
    <div class="outputContainer" id="outputContainer">
      <!--<button @click="addText()">temp: add text</button>
      <button @click="temp_sd()">temp: start draw</button>-->
      <div class="setSceneContainer">
        <button @click="setScene('ringScene')" class="ringSceneButton" id="ringSceneButton">RINGS</button>
        <button @click="setScene('treeScene')" class="treeSceneButton" id="treeSceneButton">TREE</button>
        <button @click="setScene('rawDataScene')" class="rawDataSceneButton" id="rawDataSceneButton">DATA</button>
      </div>
      <div class="crownShapeContainer">
        <button @click="setCrownShape('cone')" class="coneButton" id="coneButton">CONE</button>
        <button @click="setCrownShape('cylinder')" class="cylinderButton" id="cylinderButton">CYLINDER</button>
      </div>

      <h4> Move the slider to see the growth of the tree!</h4>
      <h5>Year: {{this.dataIndex}}</h5>


      <input type="range" min="1" v-model="dataIndex" @input="draw()" id="timeStepSlider" class="timeStepSlider"><br><br>
      <div id="treeCanvasport">
        <div id="treeScaleBarMaxHeight" class="UILabel"></div>
        <div id="treeScaleBarMaxRootDepth" class="UILabel"></div>
        <div id="treeLegendZero" class="UILabel"></div>

        <div id="ringScaleBarRadiusTop" class="UILabel"></div>
        <div id="ringScaleBarRadiusMid" class="UILabel"></div>
        <div id="ringScaleBarRadiusBot" class="UILabel"></div>
        <div id="ringLegendHW" class="UILabel"></div>
        <div id="ringLegendSW" class="UILabel"></div>
        <div id="ringLegendInitR" class="UILabel"></div>
        <div id="ringLegendCurR" class="UILabel"></div>
      </div>
      <div class="rawDataList" id="rawDataList">
        <br>
        <div class="rawData" id="rawData">
          <label >h: {{ this.localResultJson.h[this.dataIndex] }}              </label><br>
          <label >hh: {{ this.localResultJson.hh2[this.dataIndex] }}           </label><br>
          <label >hC: {{ this.localResultJson.hC2[this.dataIndex] }}           </label><br>
          <label >hB: {{ this.localResultJson.hB2[this.dataIndex] }}           </label><br>
          <label >hBH: {{ this.localResultJson.hBH2[this.dataIndex] }}         </label><br>
          <label >r: {{ this.localResultJson.r[this.dataIndex] }}              </label><br>
          <label >rB: {{ this.localResultJson.rB2[this.dataIndex] }}           </label><br>
          <label >rC: {{ this.localResultJson.rC2[this.dataIndex] }}           </label><br>
          <label >rBH: {{ this.localResultJson.rBH[this.dataIndex] }}          </label><br>
          <label >sw: {{ this.localResultJson.sw2[this.dataIndex] }}           </label><br>
          <label >vts: {{ this.localResultJson.vts2[this.dataIndex] }}         </label><br>
          <label >vt: {{ this.localResultJson.vt2[this.dataIndex] }}           </label><br>
          <label >vth: {{ this.localResultJson.vth2[this.dataIndex] }}         </label><br>
          <label >sa: {{ this.localResultJson.sa2[this.dataIndex] }}           </label><br>
          <label >la: {{ this.localResultJson.la2[this.dataIndex] }}           </label><br>
          <label >ra: {{ this.localResultJson.ra2[this.dataIndex] }}           </label><br>
          <label >dr: {{ this.localResultJson.dr2[this.dataIndex] }}           </label><br>
          <label >xa: {{ this.localResultJson.xa2[this.dataIndex] }}           </label><br>
          <label >bl: {{ this.localResultJson.bl2[this.dataIndex] }}           </label><br>
          <label >br: {{ this.localResultJson.br2[this.dataIndex] }}           </label><br>
          <label >bt: {{ this.localResultJson.bt2[this.dataIndex] }}           </label><br>
          <label >bts: {{ this.localResultJson.bts2[this.dataIndex] }}         </label><br>
          <label >bth: {{ this.localResultJson.bth2[this.dataIndex] }}         </label><br>
          <label >boh: {{ this.localResultJson.boh2[this.dataIndex] }}         </label><br>
          <label >bos: {{ this.localResultJson.bos2[this.dataIndex] }}         </label><br>
          <label >bo: {{ this.localResultJson.bo2[this.dataIndex] }}           </label><br>
          <label >bs: {{ this.localResultJson.bs2[this.dataIndex] }}           </label><br>
          <label >clr: {{ this.localResultJson.clr2[this.dataIndex] }}         </label><br>
          <label >fl: {{ this.localResultJson.fl2[this.dataIndex] }}           </label><br>
          <label >fr: {{ this.localResultJson.fr2[this.dataIndex] }}           </label><br>
          <label >ft: {{ this.localResultJson.ft2[this.dataIndex] }}           </label><br>
          <label >fo: {{ this.localResultJson.fo2[this.dataIndex] }}           </label><br>
          <label >rfl: {{ this.localResultJson.rfl2[this.dataIndex] }}         </label><br>
          <label >rfr: {{ this.localResultJson.rfr2[this.dataIndex] }}         </label><br>
          <label >rfs: {{ this.localResultJson.rfs2[this.dataIndex] }}         </label><br>
          <label >rtrans: {{ this.localResultJson.rtrans2[this.dataIndex] }}   </label><br>
          <label >light: {{ this.localResultJson.light2[this.dataIndex] }}     </label><br>
          <label >nut: {{ this.localResultJson.nut2[this.dataIndex] }}         </label><br>
          <label >deltas: {{ this.localResultJson.deltas2[this.dataIndex] }}   </label><br>
          <label >LAI: {{ this.localResultJson.LAI2[this.dataIndex] }}         </label><br>
          <!--<label>APARout: {{ this.localResultJson.APARout[this.dataIndex] }}   </label><br>-->
          <!--<label>cs2: {{ this.localResultJson.cs2[this.dataIndex] }}       </label><br>-->
          <!--<label >egrow: {{ this.localResultJson.egrow2[this.dataIndex] }}     </label><br>-->
          <!--<label >ex: {{ this.localResultJson.ex2[this.dataIndex] }}           </label><br>-->
          <!-- <label>status2: {{ this.localResultJson.status2[this.dataIndex] }}   </label><br> -->
          <!--<label>errorind: {{ this.localResultJson.errorind[this.dataIndex] }}   </label><br>-->
          <!--<label>growth_st: {{ this.localResultJson.growth_st[this.dataIndex] }} </label><br>-->
        </div>
        <br><br>
        <div>
          <download-csv class="downloadbutton" :data="this.array" name = "treeData.csv">
            <button @click="downloadRawData()">Download data</button>
          </download-csv>
          <div class="tooltip">
            <span class="tooltiptext">
              <b>h: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bl: </b>Slope at H versus r curve at r = 0<br>
              <b>hh: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>br: </b>Slope at H versus r curve at r = 0<br>
              <b>hC: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bt: </b>Slope at H versus r curve at r = 0<br>
              <b>hB: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bts: </b>Slope at H versus r curve at r = 0<br>
              <b>hBH: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bth: </b>Slope at H versus r curve at r = 0<br>
              <b>r: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>boh: </b>Slope at H versus r curve at r = 0<br>
              <b>rB: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bos: </b>Slope at H versus r curve at r = 0<br>
              <b>rC: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bo: </b>Slope at H versus r curve at r = 0<br>
              <b>rBH: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>bs: </b>Slope at H versus r curve at r = 0<br>
              <b>sw: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>clr: </b>Slope at H versus r curve at r = 0<br>
              <b>vts: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>fl: </b>Slope at H versus r curve at r = 0<br>
              <b>vt: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>fr: </b>Slope at H versus r curve at r = 0<br>
              <b>vth: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>ft: </b>Slope at H versus r curve at r = 0<br>
              <b>sa: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>rfl: </b>Slope at H versus r curve at r = 0<br>
              <b>la: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>rfr: </b>Slope at H versus r curve at r = 0<br>
              <b>ra: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>rfs: </b>Slope at H versus r curve at r = 0<br>
              <b>dr: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>rtrans: </b>Slope at H versus r curve at r = 0<br>
              <b>xa: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>light: </b>Slope at H versus r curve at r = 0<br>
              <b>nut: </b>Slope at H versus r curve at r = 0 &nbsp;&nbsp; <b>deltas: </b>Slope at H versus r curve at r = 0<br>
              <b>LAI: </b>Slope at H versus r curve at r = 0<br>
            </span>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import * as THREE from 'three'
  import JsonCSV from 'vue-json-csv'
  import font_helvetiker_regular from '../assets/fonts/helvetiker_regular.typeface.json'
  import loblolly9 from '../json/loblolly9.json'

  export default {
    name: 'outputContainer',

    components: {'download-csv': JsonCSV},

    props: ['resultJson', 'postBody', 'startDraw', 'loadingFlag', 'resetFlag'],

    data() {
      return {
        dataIndex: "1",
        canvasWidth: window.innerWidth*0.75,
        canvasHeight: window.innerHeight*0.75,
        currentScene: this.treeScene,
        currentCam: this.treeCam,
        maxRootDepth: 0,
        maxHeight: 0,
        maxTrunkRadius: 0,
        maxLAI2: 0,
        maxBr: 0,
        crownShape: "cone",
        ringScale: 10,
        array : [],
        ringArray: [],
        numberOfRings: 0,
        loopFlag: 0,
        localResultJson: {
          "APARout":'',
          "h":'',
          "hh2":'',
          "hC2":'',
          "hB2":'',
          "hBH2":'',
          "r":'',
          "rB2":'',
          "rC2":'',
          "rBH":'',
          "sw2":'',
          "vts2":'',
          "vt2":'',
          "vth2":'',
          "sa2":'',
          "la2":'',
          "ra2":'',
          "dr2":'',
          "xa2":'',
          "bl2":'',
          "br2":'',
          "bt2":'',
          "bts2":'',
          "bth2":'',
          "boh2":'',
          "bos2":'',
          "bo2":'',
          "bs2":'',
          "cs2":'',
          "clr2":'',
          "fl2":'',
          "fr2":'',
          "ft2":'',
          "fo2":'',
          "rfl2":'',
          "rfr2":'',
          "rfs2":'',
          "egrow2":'',
          "ex2":'',
          "rtrans2":'',
          "light2":'',
          "nut2":'',
          "deltas2":'',
          "LAI2":'',
          "status2":'',
          "errorind":'',
        },
        localLoadingFlag: ''
      } // END: return
    }, // END: data()

    methods: {
      initializeVisualization() {
        this.visCanvas = document.getElementById('treeCanvasport')

        ///// Tree Scene /////
        // Create scene for trees
        this.treeScene = new THREE.Scene()
        var bgColor = new THREE.Color()
        bgColor.r = 0.5
        bgColor.g = 0.9
        bgColor.b = 1
        this.treeScene.background = bgColor
        // Create camera for tree scene
        // PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )
        this.treeCam = new THREE.PerspectiveCamera( 90, this.canvasWidth / this.canvasHeight, 0.1, 1000 )
        this.treeCam.position.z = 10
        this.treeScene.add( this.treeCam )
        ///// Tree Scene /////

        ///// Ring Scene /////
        // Create scene for rings
        this.ringScene = new THREE.Scene()
        this.ringScene.background = new THREE.Color( 0xdfffcf  )
        // Create camera for ring scene
        // PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )
        this.ringCam = new THREE.PerspectiveCamera( 90, this.canvasWidth / this.canvasHeight, 0.1, 1000 )
        this.ringCam.position.z = 10
        this.ringScene.add( this.ringCam )
        ///// Ring Scene /////

        // Create renderer
        this.renderer = new THREE.WebGLRenderer( {antialias: true} )
        this.renderer.setSize( this.canvasWidth, this.canvasHeight )
        this.visCanvas.appendChild( this.renderer.domElement )

        // Choose default scene
        this.currentScene = this.treeScene
        this.currentCam = this.treeCam

        // Attempt at making a ground plane.
        // PlaneGeometry(width : Float, height : Float, widthSegments : Integer, heightSegments : Integer)
        /*var groundGEO = new THREE.PlaneGeometry(3, 3, 1)
        var groundMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
        var ground = new THREE.Mesh( groundGEO, groundMat )
        this.currentScene.add(ground)
        ground.position.z = 2
        ground.rotation.x = 89
        ground.rotation.y = 0*/

        // Show the tree view as default and hide the raw data view.
        document.getElementById("treeCanvasport").style.display = "block"
        document.getElementById("rawDataList").style.display = "none"
        // Also hide labels for ring scene scale
        document.getElementById('ringScaleBarRadiusTop').style.display = "none" // Hide top radius text
        document.getElementById('ringScaleBarRadiusMid').style.display = "none" // Hide middle text
        document.getElementById('ringScaleBarRadiusBot').style.display = "none" // Hide bottom radius text

        // Allow canvas to resize with window.
        window.addEventListener( 'resize', this.onWindowResize, false )



        console.log("initializeVisualization - Complete")
      }, // END: initializeVisualization()

      afterGetSetup() {
        // Does some setup once getData() is done and data has been retrieved.

        // For running locally if model stops working.
        //this.localResultJson = loblolly9
        //console.log("localResultJson", this.localResultJson)

        this.localResultJson = this.resultJson
        this.localLoadingFlag = this.loadingFlag

        // Change the background color of the tree scene based on the light level.
        var bgColor = new THREE.Color()
        if(this.postBody.io == null)
        {
          bgColor.r = 0.5
          bgColor.g = 0.9
          bgColor.b = 1
        }
        else
        {
          bgColor.r = this.postBody.io/2060
          bgColor.g = this.postBody.io/2060+0.4
          bgColor.b = 1
        }
        this.treeScene.background = bgColor

        // Find max height and radius of tree over its life to scale the scene to.
        // Find max LAI2 to normalize it for opacity.
        for( var i = 1; i <= this.postBody.t; i++ )
        {
          // Find max height
          if( this.maxHeight < this.localResultJson.h[i] )
          {
            this.maxHeight = this.localResultJson.h[i]
          }

          // Find max root depth
          var h = this.localResultJson.h[i]     // Total tree height
          var hC = this.localResultJson.hC2[i]  // Height that trunk transitions from paraboloid to cone (trunk to crown)
          hC = this.postBody.eta * h

          // Root depth = sqrt(f1/2)*(H-hc)
          var rootDepth = Math.sqrt(this.postBody.f1 / 2) * (h - hC) // Get root depth

          if( this.maxRootDepth < rootDepth )
          {
            this.maxRootDepth = rootDepth
          }

          // Find max LAI2.
          if( this.maxLAI2 < this.localResultJson.LAI2[i] )
          {
            this.maxLAI2 = this.localResultJson.LAI2[i]
          }

          // Find max root biomass.
          if( this.maxBr < this.localResultJson.br2[i] )
          {
            this.maxBr = this.localResultJson.br2[i]
          }

          // Check for larger trunk radius.
          if( this.maxTrunkRadius < this.localResultJson.r[i] )
          {
            this.maxTrunkRadius = this.localResultJson.r[i]
          }
        } // END: for i to t

        // Resize camera based on total tree height (from -maxRootdepth to maxHeight since 0 is the base of the tree).
        this.treeCam.position.y = (this.maxHeight - this.maxRootDepth) / 2
        this.treeCam.position.z = (this.maxHeight + this.maxRootDepth) * 0.6 // 0.6 just makes it fit on the screen better.
        this.treeCam.lookAt(0, (this.maxHeight - this.maxRootDepth)/2, 0)

        this.ringCam.position.z = this.maxTrunkRadius * this.ringScale * 1.1   // Scale scene to max radius of the trunk so that no rings are off-screen.
        this.ringCam.lookAt(0, 0, 0)

        this.setUpLabels()
        this.setScene("treeScene")

        console.log("afterGetSetup - Complete")
      }, // END: afterGetSetup()

      setUpLabels() {
        /// Set up labels for scale ///
        var treeScaleBarMaxHeight = document.getElementById('treeScaleBarMaxHeight')
        treeScaleBarMaxHeight.innerHTML = this.maxHeight.toFixed(2) + " m"
        var treeScaleBarMaxRootDepth = document.getElementById('treeScaleBarMaxRootDepth')
        treeScaleBarMaxRootDepth.innerHTML = "-" + this.maxRootDepth.toFixed(2) + " m"

        var ringScaleBarRadiusTop = document.getElementById('ringScaleBarRadiusTop')
        ringScaleBarRadiusTop.innerHTML = this.maxTrunkRadius.toFixed(2) + " m"
        var ringScaleBarRadiusMid = document.getElementById('ringScaleBarRadiusMid')
        ringScaleBarRadiusMid.innerHTML = "0 m"
        var ringScaleBarRadiusBot = document.getElementById('ringScaleBarRadiusBot')
        ringScaleBarRadiusBot.innerHTML = this.maxTrunkRadius.toFixed(2) + " m"


        // Sets position of scale labels
        treeScaleBarMaxHeight.style.left = ((0.73 + 1)/2 * this.canvasWidth) + 'px'
        treeScaleBarMaxHeight.style.top = ((-0.86 + 1)/2 * this.canvasHeight) + 'px'
        treeScaleBarMaxRootDepth.style.left = ((0.72 + 1)/2 * this.canvasWidth) + 'px'
        treeScaleBarMaxRootDepth.style.top = ((0.81 + 1)/2 * this.canvasHeight) + 'px'

        ringScaleBarRadiusTop.style.left = ((0.74 + 1)/2 * this.canvasWidth) + 'px'
        ringScaleBarRadiusTop.style.top = ((-0.93 + 1)/2 * this.canvasHeight) + 'px'
        ringScaleBarRadiusMid.style.left = ((0.78 + 1)/2 * this.canvasWidth) + 'px'
        ringScaleBarRadiusMid.style.top = ((-0.02 + 1)/2 * this.canvasHeight) + 'px'
        ringScaleBarRadiusBot.style.left = ((0.74 + 1)/2 * this.canvasWidth) + 'px'
        ringScaleBarRadiusBot.style.top = ((0.88 + 1)/2 * this.canvasHeight) + 'px'

        /// Set up lables for tree legend ///
        var treeLegendZeroText = document.getElementById('treeLegendZero')
        treeLegendZeroText.innerHTML = "0 m"
        treeLegendZeroText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        treeLegendZeroText.style.top = ((-0.86 + 1)/2 * this.canvasHeight) + 'px'

        /// Set up labels for ring legend ///
        var ringLegendHWText = document.getElementById('ringLegendHW')
        ringLegendHWText.innerHTML = "Heartwood"
        var ringLegendSWText = document.getElementById('ringLegendSW')
        ringLegendSWText.innerHTML = "Sapwood"

        var ringLegendInitRText = document.getElementById('ringLegendInitR')
        ringLegendInitRText.innerHTML = "Initial Radius"
        var ringLegendCurRText = document.getElementById('ringLegendCurR')
        ringLegendCurRText.innerHTML = "Current Radius"

        ringLegendHWText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendHWText.style.top = ((-0.93 + 1)/2 * this.canvasHeight) + 'px'
        ringLegendSWText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendSWText.style.top = ((-0.86 + 1)/2 * this.canvasHeight) + 'px'

        ringLegendInitRText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendInitRText.style.top = ((-0.79 + 1)/2 * this.canvasHeight) + 'px'
        ringLegendCurRText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendCurRText.style.top = ((-0.72 + 1)/2 * this.canvasHeight) + 'px'

      }, // END: setUpLabels()

      draw() {
        if(this.currentScene == this.treeScene)
        {
          if( this.localResultJson.h[1] != undefined) // Prevents drawing when there is no data yet.
          {
            this.drawTree()
          }
        }
        else if(this.currentScene == this.ringScene)
        {
          if( this.localResultJson.r[1] != undefined) // Prevents drawing when there is no data yet.
          {
            this.drawRings()
          }
        }
      }, // END: draw()

      drawTree() {
        var year = this.dataIndex // The current timestep on the slider. Named "year" to make it easier to read.

        // Clear scene of old drawings
        while(this.treeScene.children.length > 0){   // Clear scene of old tree
          this.treeScene.remove(this.treeScene.children[0])
        }
        this.newScene = new THREE.Scene()            // Create new scene for new tree
        this.treeScene.add( this.newScene )          // Add new scene to root scene

        this.addLight()

        /// Trunk variables
        var h = this.localResultJson.h[year]      // Total tree height
        var hB = this.localResultJson.hB2[year]   // Height that trunk transitions from neiloid to paraboloid (base to trunk)
        hB = this.postBody.etaB * h
        var hC = this.localResultJson.hC2[year]   // Height that trunk transitions from paraboloid to cone (trunk to crown)
        hC = this.postBody.eta * h
        var r = this.localResultJson.r[year]      // Radius of trunk at base
        var rB = this.localResultJson.rB2[year]   // Radius of trunk when transitioning from neilooid to paraboloid (base to trunk)
        var rC = this.localResultJson.rC2[year]   // Radius of trunk when transitioning from parapoloid to cone (trunk to crown)

        /// Crown variables (overlaid on "cone" part of trunk)
        var hmax = this.postBody.hmax        // Input.
        var phih = this.postBody.phih        // Input.
        var eta = this.postBody.eta          // Input.
        var m = this.postBody.m              // Input.
        var alpha = this.postBody.alpha      // Input.
        var r0 = this.postBody.r0            // Input.
        var r40 = this.postBody.r40          // Input.
        var rBH = this.localResultJson.rBH[year]  // Output.
        // var h = this.treeData[year].h     // Output. Delcared above
        const BH = 1.37                      // Breast height. Contsant 1.37 meters

        //if( h > 0 )
        //{
        // if h > BH --> rcmax = r0 + ((r40 - r0) * (2 * rBH * 100) / 40)
        // if h < BH --> rcmax = (r0 * r) / ((hmax / phih) * ln(hmax/(hmax - BH)))
        var rcmax // Maximum potential radius at a crown ratio of m
        if( h > BH )
        {
          rcmax = r0 + ((r40 - r0) * (2 * rBH * 100) / 40)
        }
        else if( h < BH )
        {
          rcmax = (r0 * r) / ((hmax / phih) * Math.log(hmax/(hmax - BH)))
        }
        //console.log("rcmax",rcmax)

        var eta = this.postBody.eta     // Input.
        var alpha = this.postBody.alpha // Input. Curvature of the crown.

        // if m > (1 - eta) --> rcbase = rcmax * ((1 - eta) / m)^alpha
        // otherwise --> rcbase = 1 - eta
        var rcbase // Radius at the base of the crown.
        if( m > (1 - eta))
        {
          rcbase = rcmax * Math.pow(((1 - eta) / m), alpha)
        }
        else
        {
          rcbase = rcmax
        }

        //console.log("year:",year,"\nLAI2:",this.localResultJson.LAI2[year],"\nh:",h,"\nhC:",hC,"\nhB:",hB,"\nr:",r,"\nrB:",rB,"\nrC:",rC,"\nrBH:",rBH,"\nrcmax:",rcmax,"\nrcbase:",rcbase)

        // Supplemental parameters
        var geoSegments = 20              // Segments of geometry
        var crownPos = hC + (h-hC)/2      // Moves the crown so that it's bottom plane is at the top of the middle segment.
        var trunkBasePos = hB/2           // Moves the trunk's base segment so that it's bottom plane is at (0,0).
        var trunkMidPos = hB + (hC-hB)/2  // Moves the trunk's middle segment so that it's bottom plane is at the top of the base segment.
        var trunkTopPos = hC + (h-hC)/2   // Moves the trunk's top segment so that it's bottom plane is at the top of the middle segment.

        ///// Trunk /////
        // Trunk Top
        // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
        var trunkTopGeo = new THREE.ConeGeometry( rC, h-hC, geoSegments )
        var trunkTopMat = new THREE.MeshLambertMaterial( {color: 0xb5651d} )
        this.trunkTop = new THREE.Mesh( trunkTopGeo, trunkTopMat )
        this.trunkTop.position.y = trunkTopPos

        // Trunk Middle
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        var trunkMidGeo = new THREE.CylinderGeometry( rC, rB, hC-hB, geoSegments )
        var trunkMidMat = new THREE.MeshLambertMaterial( {color: 0xb5651d} )
        this.trunkMid = new THREE.Mesh( trunkMidGeo, trunkMidMat )
        this.trunkMid.position.y = trunkMidPos

        // Trunk Base
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        var trunkBaseGeo = new THREE.CylinderGeometry( rB, r, hB, geoSegments )
        var trunkBaseMat = new THREE.MeshLambertMaterial( {color: 0xb5651d} )
        this.trunkBase = new THREE.Mesh( trunkBaseGeo, trunkBaseMat )
        this.trunkBase.position.y = trunkBasePos
        ///// END: Trunk /////

        ///// Crown /////
        var crownGeo
        if( this.crownShape == "cone" )
        {
          // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
          crownGeo = new THREE.ConeGeometry( rcbase, h-hC, geoSegments )
        }
        else if( this.crownShape == "sphere") // Currently looks weird. Needs tuning.
        {
          // SphereGeometry(radius : Float, widthSegments : Integer, heightSegments : Integer)
          crownGeo = new THREE.SphereGeometry( rcbase, geoSegments*1.5, geoSegments*1.5 )
        }
        else if( this.crownShape == "cylinder" )
        {
          // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
          crownGeo = new THREE.CylinderGeometry( rcbase, rcbase, h-hC, geoSegments );
        }
        else // Default to cone shaped crown
        {
          // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
          crownGeo = new THREE.ConeGeometry( rcbase, h-hC, geoSegments )
        }
        //console.log("crownShape:", this.crownShape)

        var crownMat = new THREE.MeshLambertMaterial( {color: 0x00FF00} )
        crownMat.transparent = true
        crownMat.opacity = this.localResultJson.LAI2[year]/this.maxLAI2
        this.crown = new THREE.Mesh( crownGeo, crownMat )
        this.crown.position.y = crownPos
        //console.log("Crown -", "\nradius:", rcbase, "\nheight:", h-hC,)
        ///// END: Crown /////

        ///// Roots /////
        var rootDepth
        var rootWidth

        // Root depth = sqrt(f1/2)*(H-hc)
        rootDepth = Math.sqrt(this.postBody.f1 / 2) * (h - hC)
        // Root width = sqrt(2*f1)*Rcbase
        rootWidth = Math.sqrt(2 * this.postBody.f1) * rcbase

        var rootGeo = new THREE.BoxGeometry( rootWidth, rootDepth, 1 )
        var rootMat = new THREE.MeshLambertMaterial( { color: 0x402000 } )
        rootMat.transparent = true
        rootMat.opacity = this.localResultJson.br2[year]/this.maxBr
        this.roots = new THREE.Mesh( rootGeo, rootMat )
        this.roots.position.y = -rootDepth/2
        ///// END: Roots /////

        // Add trunk, crown, and roots to scene
        this.newScene.add( this.crown )
        this.newScene.add( this.trunkTop )
        this.newScene.add( this.trunkMid )
        this.newScene.add( this.trunkBase )
        this.newScene.add( this.roots )

        // Draw the scale based on the current tree
        this.drawTreeScale(h, hC, rootDepth)
        this.drawTreeLegend()
      }, // END: drawTree()

      drawTreeLegend() {
        var leftEdgeOfScreen = -1 * (this.treeCam.position.z * (this.canvasWidth/this.canvasHeight))
        var x = leftEdgeOfScreen * 0.98
        var y = this.maxHeight

        var zeroMarkPoints = []

        zeroMarkPoints.push( new THREE.Vector3( x, y, 0 ) )
        zeroMarkPoints.push( new THREE.Vector3( x+1, y, 0 ) )

        var zeroMarkLineGeo = new THREE.BufferGeometry().setFromPoints( zeroMarkPoints )
        var zeroMarkLineMat = new THREE.LineBasicMaterial( {color: 0xff0000} )
        var zeroMarkLegend = new THREE.Line( zeroMarkLineGeo, zeroMarkLineMat )

        this.treeScene.add( zeroMarkLegend )
      }, // END: drawTreeLegend()

      drawTreeScale(h, hC, rootDepth) {
        var rightEdgeOfScreen = this.treeCam.position.z * (this.canvasWidth/this.canvasHeight)
        var points = []
        var zeroPoints = []

        //points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.maxHeight, 0 ) ) // max height
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, this.maxHeight, 0 ) ) // max height
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.maxHeight, 0 ) ) // max height

        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, h, 0 ) ) // current height
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, h, 0 ) ) // current height
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, h, 0 ) ) // current height

        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, hC, 0 ) ) // trunk top
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, hC, 0 ) ) // trunk top
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, hC, 0 ) ) // trunk top

        zeroPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, 0, 0 ) ) // trunk base
        zeroPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, 0, 0 ) ) // trunk base
        //zeroPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, 0, 0 ) ) // trunk base

        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -rootDepth, 0 ) ) // current root depth
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, -rootDepth, 0 ) ) // current root depth
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -rootDepth, 0 ) ) // current root depth

        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.maxRootDepth, 0 ) ) // max root depth
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, -this.maxRootDepth, 0 ) ) // max root depth
        //points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.maxRootDepth, 0 ) ) // max root depth

        var lineGeo = new THREE.BufferGeometry().setFromPoints( points )
        var lineMat = new THREE.LineBasicMaterial( {color: 0x008509, linewidth: 30} )
        var scale = new THREE.Line( lineGeo, lineMat )

        var zeroLineGeo = new THREE.BufferGeometry().setFromPoints( zeroPoints )
        var zeroLineMat = new THREE.LineBasicMaterial( {color: 0xff0000, linewidth: 30} )
        var zeroScale = new THREE.Line( zeroLineGeo, zeroLineMat )

        this.treeScene.add( scale )
        this.treeScene.add( zeroScale )
      }, // END: drawTreeScale()

      drawRings() {
        var geoSegments = 16

        // Clear scene of previous drawings
        while(this.ringScene.children.length > 0){           // Clear scene of old rings
          this.ringScene.remove(this.ringScene.children[0])
        }
        this.newScene = new THREE.Scene()                    // Create new scene for new rings
        this.ringScene.add( this.newScene )                  // Add new scene to root scene

        var heartwoodRadius = this.localResultJson.r[this.dataIndex] - this.localResultJson.sw2[this.dataIndex] // Gets the heart wood radius at the current year on the slider
        //console.log("sw:", this.localResultJson.sw2[this.dataIndex], "\nr:", this.localResultJson.r[this.dataIndex], "\nhw:", heartwoodRadius)



        for( var i = 1; i <= this.dataIndex; i++ )
        {
          // color
          var ringColor = new THREE.Color()
          if( this.localResultJson.r[i] < heartwoodRadius ) // If the current ring is part of the heart wood..
          {
            // Alternate between lighter colors
            if(i % 2 == 0) { ringColor = 0xad593b }
            else { ringColor = 0x521700 }
          }
          else                                              // If the current ring is part of the sap wood..
          {
            // Alternate between darker colors
            if(i % 2 == 0) { ringColor = 0x997354 }
            else { ringColor = 0x331700 }
          }

          var ringGeo
          if(i == 1)
          {
            // Sets the initial ring to a circle. Otherwise, there would be a hole of r0 raidus in the center.
            ringGeo = new THREE.CircleGeometry(this.localResultJson.r[i]*this.ringScale, geoSegments)
            var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
            ringMat.transparent = true
            ringMat.opacity = 0.6
            var ring = new THREE.Mesh( ringGeo, ringMat )
            this.newScene.add( ring )
          }
          else
          {
            // RingGeometry(innerRadius : Float, outerRadius : Float, thetaSegments : Integer, phiSegments : Integer, thetaStart : Float, thetaLength : Float)
            ringGeo = new THREE.RingGeometry( this.localResultJson.r[i-1]*this.ringScale, this.localResultJson.r[i]*this.ringScale, geoSegments, 1 )
            var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
            var ring = new THREE.Mesh( ringGeo, ringMat )
            this.newScene.add( ring )
          }
        } // END: for i

        this.drawRingLegend()
        this.drawRingScale()
      }, // END: drawRings()

      drawRingLegend() {
        var leftEdgeOfScreen = -1 * (this.ringCam.position.z * (this.canvasWidth/this.canvasHeight))
        var x = leftEdgeOfScreen * 0.98
        var y = this.maxTrunkRadius*this.ringScale
        var squareSize = 0.01*(this.ringScale*0.35)

        var squareShape = new THREE.Shape()
        squareShape.moveTo( 0, 0 )
        squareShape.lineTo( squareSize, 0 )
        squareShape.lineTo( squareSize, squareSize )
        squareShape.lineTo( 0, squareSize )
        squareShape.lineTo( 0, 0 )
        var squareGeo = new THREE.ShapeGeometry( squareShape )

        // Heartwood color 1
        var hwColor1Mat = new THREE.MeshBasicMaterial( { color: 0xad593b } )
        var hwColor1 = new THREE.Mesh( squareGeo, hwColor1Mat )
        hwColor1.position.x = x
        hwColor1.position.y = y - squareSize*0.5
        this.ringScene.add( hwColor1 )

        // Heartwood color 2
        var hwColor2Mat = new THREE.MeshBasicMaterial( { color: 0x521700 } )
        var hwColor2 = new THREE.Mesh( squareGeo, hwColor2Mat )
        hwColor2.position.x = x + squareSize
        hwColor2.position.y = y - squareSize*0.5
        this.ringScene.add( hwColor2 )

        // Sapwood color 1
        var swColor1Mat = new THREE.MeshBasicMaterial( { color: 0x997354 } )
        var swColor1 = new THREE.Mesh( squareGeo, swColor1Mat )
        swColor1.position.x = x
        swColor1.position.y = y - squareSize*2.5
        this.ringScene.add( swColor1 )

        // Sapwood color 2
        var swColor2Mat = new THREE.MeshBasicMaterial( { color: 0x331700 } )
        var swColor2 = new THREE.Mesh( squareGeo, swColor2Mat )
        swColor2.position.x = x + squareSize
        swColor2.position.y = y - squareSize*2.5
        this.ringScene.add( swColor2 )

        // Scale Bar legend
        var initRadPoints = []
        var curRadPoints = []

        initRadPoints.push( new THREE.Vector3( x, y - squareSize*4, 0 ) )
        initRadPoints.push( new THREE.Vector3( x + squareSize*2, y - squareSize*4, 0 ) )

        curRadPoints.push( new THREE.Vector3( x, y - squareSize*6, 0 ) )
        curRadPoints.push( new THREE.Vector3( x + squareSize*2, y - squareSize*6, 0 ) )

        var initRadLineGeo = new THREE.BufferGeometry().setFromPoints( initRadPoints )
        var initRadLineMat = new THREE.LineBasicMaterial( {color: 0xff0000} )
        var initRadScale = new THREE.Line( initRadLineGeo, initRadLineMat )

        var curRadLineGeo = new THREE.BufferGeometry().setFromPoints( curRadPoints )
        var CurRadLineMat = new THREE.LineBasicMaterial( {color: 0x0000ff} )
        var curRadScale = new THREE.Line( curRadLineGeo, CurRadLineMat )

        this.ringScene.add( initRadScale )
        this.ringScene.add( curRadScale )
      }, // END: drawRingLegend()

      drawRingScale() {
        //this.ringScene.remove(scale)
        var rightEdgeOfScreen = this.ringCam.position.z * (this.canvasWidth/this.canvasHeight)
        var points = []
        var curRadTopPoints = []
        var initRadTopPoints = []
        var initRadBotPoints = []
        var curRadBotPoints = []

        //points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.maxTrunkRadius*this.ringScale, 0 ) ) // Top of scale
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, this.maxTrunkRadius*this.ringScale, 0 ) ) // Top of scale
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.maxTrunkRadius*this.ringScale, 0 ) ) // Top of scale

        curRadTopPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.localResultJson.r[this.dataIndex]*this.ringScale, 0 ) ) // Current radius top
        curRadTopPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, this.localResultJson.r[this.dataIndex]*this.ringScale, 0 ) ) // Current radius top
        //curRadTopPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.localResultJson.r[this.dataIndex], 0 ) ) // Current radius top

        initRadTopPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.localResultJson.r[1]*this.ringScale, 0 ) ) // Top of initial radius
        initRadTopPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, this.localResultJson.r[1]*this.ringScale, 0 ) ) // Top of initial radius
        //initRadTopPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, this.localResultJson.r[1], 0 ) ) // Top of initial radius

        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, 0, 0 ) ) // Center
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, 0, 0 ) ) // Center
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, 0, 0 ) ) // Center

        initRadBotPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.localResultJson.r[1]*this.ringScale, 0 ) ) // Bottom of initial radius
        initRadBotPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, -this.localResultJson.r[1]*this.ringScale, 0 ) ) // Bottom of initial radius
        //initRadBotPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.localResultJson.r[1], 0 ) ) // Bottom of initial radius

        curRadBotPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.localResultJson.r[this.dataIndex]*this.ringScale, 0 ) ) // Current radius botttom
        curRadBotPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, -this.localResultJson.r[this.dataIndex]*this.ringScale, 0 ) ) // Current radius bottom
        //curRadBotPoints.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.localResultJson.r[this.dataIndex], 0 ) ) // Current radius bottom

        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.maxTrunkRadius*this.ringScale, 0 ) ) // Bottom of scale
        points.push( new THREE.Vector3( rightEdgeOfScreen * 0.85, -this.maxTrunkRadius*this.ringScale, 0 ) ) // Bottom of scale
        //points.push( new THREE.Vector3( rightEdgeOfScreen * 0.95, -this.maxTrunkRadius*this.ringScale, 0 ) ) // Bottom of scale

        var lineGeo = new THREE.BufferGeometry().setFromPoints( points )
        var curRadTopLineGeo = new THREE.BufferGeometry().setFromPoints( curRadTopPoints )
        var initRadTopLineGeo = new THREE.BufferGeometry().setFromPoints( initRadTopPoints )
        var initRadBotLineGeo = new THREE.BufferGeometry().setFromPoints( initRadBotPoints )
        var curRadBotLineGeo = new THREE.BufferGeometry().setFromPoints( curRadBotPoints )

        var lineMat = new THREE.LineBasicMaterial( {color: 0x008509, linewidth: 5} )
        var curRadTopLineMat = new THREE.LineBasicMaterial( {color: 0x0000ff} )
        var initRadTopLineMat = new THREE.LineBasicMaterial( {color: 0xff0000} )
        var initRadBotLineMat = new THREE.LineBasicMaterial( {color: 0xff0000} )
        var CurRadBotLineMat = new THREE.LineBasicMaterial( {color: 0x0000ff} )

        var scale = new THREE.Line( lineGeo, lineMat )
        var curRadTopScale = new THREE.Line( curRadTopLineGeo, curRadTopLineMat )
        var initRadTopScale = new THREE.Line( initRadTopLineGeo, initRadTopLineMat )
        var initRadBotScale = new THREE.Line( initRadBotLineGeo, initRadBotLineMat )
        var curRadBotScale = new THREE.Line( curRadBotLineGeo, CurRadBotLineMat )

        this.ringScene.add( scale )
        this.ringScene.add( curRadTopScale )
        this.ringScene.add( initRadTopScale )
        this.ringScene.add( initRadBotScale )
        this.ringScene.add( curRadBotScale )
      }, // END: drawRingScale()

      addLight() {
        // Ambient light for all objects.
        // AmbientLight( color : Integer, intensity : Float )
        var light = new THREE.AmbientLight( 0x404040 )
        this.treeScene.add( light )

        // Point light for casting shadows.
        // PointLight( color : Integer, intensity : Float, distance : Number, decay : Float )
        var pointLight = new THREE.PointLight( 0xffffff, 1, 100 )
        pointLight.position.set( 10, 10, 10 )
        this.treeScene.add( pointLight )
      }, // END: addLight

      setCrownShape(shape) {
        this.crownShape = shape
        console.log("Crown Shape Change -", shape)
        this.drawTree()
      }, // END: setCrownShape()

      setScene(scene) {
        if(scene == "treeScene") {
          document.getElementById("treeCanvasport").style.display = "block" // Show canvas that has the renderer attached to it
          document.getElementById("rawDataList").style.display = "none" // Hide raw data list

          document.getElementById("coneButton").style.display = "inline-block" // Show cone button
          //document.getElementById("sphereButton").style.display = "inline-block" // Show sphere button
          document.getElementById("cylinderButton").style.display = "inline-block" // Show cylinder button

          document.getElementById('treeScaleBarMaxHeight').style.display = "inline-block" // Show max height text
          document.getElementById('treeScaleBarMaxRootDepth').style.display = "inline-block" // Show base height text
          document.getElementById('treeLegendZero').style.display = "inline-block" // Show zero legend text

          document.getElementById('ringScaleBarRadiusTop').style.display = "none" // Hide top radius text
          document.getElementById('ringScaleBarRadiusMid').style.display = "none" // Hide middle text
          document.getElementById('ringScaleBarRadiusBot').style.display = "none" // Hide bottom radius text
          document.getElementById('ringLegendHW').style.display = "none" // Hide heartwood legend text
          document.getElementById('ringLegendSW').style.display = "none" // Hide sapwood legend text
          document.getElementById('ringLegendInitR').style.display = "none" // Hide ring initial radius text
          document.getElementById('ringLegendCurR').style.display = "none" // Hide ring current radius text

          this.currentScene = this.treeScene
          this.currentCam = this.treeCam
          this.onWindowResize()
          this.draw()
          console.log("Scene Change - Tree")
        }
        else if(scene == "ringScene") {
          document.getElementById("treeCanvasport").style.display = "block" // Show canvas that has the renderer attached to it
          document.getElementById("rawDataList").style.display = "none" // Hide raw data list

          document.getElementById("coneButton").style.display = "none" // Hide cone button
          //document.getElementById("sphereButton").style.display = "none" // Hide sphere button
          document.getElementById("cylinderButton").style.display = "none" // Hide cylinder button

          document.getElementById('treeScaleBarMaxHeight').style.display = "none" // Hide max height text
          document.getElementById('treeScaleBarMaxRootDepth').style.display = "none" // Hide base height text
          document.getElementById('treeLegendZero').style.display = "none" // Hide zero legend text

          document.getElementById('ringScaleBarRadiusTop').style.display = "block" // Show top radius text
          document.getElementById('ringScaleBarRadiusMid').style.display = "block" // Show middle text
          document.getElementById('ringScaleBarRadiusBot').style.display = "block" // Show bottom radius text
          document.getElementById('ringLegendHW').style.display = "block" // Show heartwood legend text
          document.getElementById('ringLegendSW').style.display = "block" // Show sapwood legend text
          document.getElementById('ringLegendInitR').style.display = "block" // Show ring initial radius text
          document.getElementById('ringLegendCurR').style.display = "block" // Show ring current radius text

          this.currentScene = this.ringScene
          this.currentCam = this.ringCam
          this.onWindowResize()
          this.draw()
          console.log("Scene Change - Rings")
        }
        else if(scene == "rawDataScene") {
          document.getElementById("treeCanvasport").style.display = "none" // Hide canvas that has the renderer attached to it
          document.getElementById("rawDataList").style.display = "block" // Show raw data list

          document.getElementById("coneButton").style.display = "none" // Hide cone button
          //document.getElementById("sphereButton").style.display = "none" // Hide sphere button
          document.getElementById("cylinderButton").style.display = "none" // Hide cylinder button
          console.log("Scene Change - Raw Data")
        }
      }, // END: setScene()

      onWindowResize() {
        // Adjusts the renderer size when the window is resized.
        this.canvasWidth = window.innerWidth * 0.75
        this.canvasHeight = window.innerHeight * 0.75

        this.currentCam.aspect = this.canvasWidth / this.canvasHeight
        this.currentCam.updateProjectionMatrix()

        // Repositions the scale labels
        var treeScaleBarMaxHeight = document.getElementById('treeScaleBarMaxHeight')
        var treeScaleBarMaxRootDepth = document.getElementById('treeScaleBarMaxRootDepth')
        treeScaleBarMaxHeight.style.left = ((0.73 + 1)/2 * this.canvasWidth) + 'px'
        treeScaleBarMaxHeight.style.top = ((-0.86 + 1)/2 * this.canvasHeight) + 'px'
        treeScaleBarMaxRootDepth.style.left = ((0.72 + 1)/2 * this.canvasWidth) + 'px'
        treeScaleBarMaxRootDepth.style.top = ((0.81 + 1)/2 * this.canvasHeight) + 'px'

        var treeLegendZeroText = document.getElementById('treeLegendZero')
        treeLegendZeroText.innerHTML = "0 m"
        treeLegendZeroText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        treeLegendZeroText.style.top = ((-0.86 + 1)/2 * this.canvasHeight) + 'px'

        var ringScaleBarRadiusTop = document.getElementById('ringScaleBarRadiusTop')
        var ringScaleBarRadiusMid = document.getElementById('ringScaleBarRadiusMid')
        var ringScaleBarRadiusBot = document.getElementById('ringScaleBarRadiusBot')
        ringScaleBarRadiusTop.style.left = ((0.74 + 1)/2 * this.canvasWidth) + 'px'
        ringScaleBarRadiusTop.style.top = ((-0.93 + 1)/2 * this.canvasHeight) + 'px'
        ringScaleBarRadiusMid.style.left = ((0.78 + 1)/2 * this.canvasWidth) + 'px'
        ringScaleBarRadiusMid.style.top = ((-0.02 + 1)/2 * this.canvasHeight) + 'px'
        ringScaleBarRadiusBot.style.left = ((0.74 + 1)/2 * this.canvasWidth) + 'px'
        ringScaleBarRadiusBot.style.top = ((0.88 + 1)/2 * this.canvasHeight) + 'px'

        var ringLegendHWText = document.getElementById('ringLegendHW')
        var ringLegendSWText = document.getElementById('ringLegendSW')
        ringLegendHWText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendHWText.style.top = ((-0.93 + 1)/2 * this.canvasHeight) + 'px'
        ringLegendSWText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendSWText.style.top = ((-0.86 + 1)/2 * this.canvasHeight) + 'px'

        var ringLegendInitRText = document.getElementById('ringLegendInitR')
        var ringLegendCurRText = document.getElementById('ringLegendCurR')
        ringLegendInitRText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendInitRText.style.top = ((-0.79 + 1)/2 * this.canvasHeight) + 'px'
        ringLegendCurRText.style.left = ((-0.92 + 1)/2 * this.canvasWidth) + 'px'
        ringLegendCurRText.style.top = ((-0.72 + 1)/2 * this.canvasHeight) + 'px'

        this.renderer.setSize( this.canvasWidth, this.canvasHeight)
        this.draw()
      }, // END: onWindowResize()

      animate() {
        // THREE.js function

        //this.update()
        this.renderer.render(this.currentScene, this.currentCam)
        //this.renderer.render(this.ringZoomScene, this.ringZoomCam)

        requestAnimationFrame(this.animate)
      }, // END: animate()

      update() {
        // THREE.js function used to move objects in the scene.
        //this.trunk.rotation.y += 0.01
        //this.crown.rotation.y += 0.01
        /*this.hudBitmap.clearRect(0, 0, this.canvasWidth, this.canvasHeight)
        this.hudBitmap.fillText("year: "+this.dataIndex, this.canvasWidth/2, this.canvasHeight/2)
  	    this.hudTexture.needsUpdate = true*/
        //this.vector.x = ( this.canvasWidth / 2 ) - ( this.textureSize / 2 );
				//this.vector.y = ( this.canvasHeight / 2 ) - ( this.textureSize / 2 );

				//this.renderer.copyFramebufferToTexture( this.vector, this.texture );
      }, // END: update()

      downloadRawData() {
        // Downloads the raw data output from localResultJson to a .csv file
        for(let i in this.localResultJson){
          let o = {name : i, v : this.localResultJson[i]};
          this.array.push(this.localResultJson[i])
        }
        console.log(this.array);
        console.log("object is transferred to array");
      }, // END: downloadRawData()

      setTempDefaultlocalResultJson() {
        this.localResultJson = {
          "APARout":'',
          "h":'',
          "hh2":'',
          "hC2":'',
          "hB2":'',
          "hBH2":'',
          "r":'',
          "rB2":'',
          "rC2":'',
          "rBH":'',
          "sw2":'',
          "vts2":'',
          "vt2":'',
          "vth2":'',
          "sa2":'',
          "la2":'',
          "ra2":'',
          "dr2":'',
          "xa2":'',
          "bl2":'',
          "br2":'',
          "bt2":'',
          "bts2":'',
          "bth2":'',
          "boh2":'',
          "bos2":'',
          "bo2":'',
          "bs2":'',
          "cs2":'',
          "clr2":'',
          "fl2":'',
          "fr2":'',
          "ft2":'',
          "fo2":'',
          "rfl2":'',
          "rfr2":'',
          "rfs2":'',
          "egrow2":'',
          "ex2":'',
          "rtrans2":'',
          "light2":'',
          "nut2":'',
          "deltas2":'',
          "LAI2":'',
          "status2":'',
          "errorind":'',
          //"growth_st":''
        }
      }, // END: setTempDefaultlocalResultJson()

      checkForStartDraw() {
        // Keeps checking for startDraw (from the input container)
        // to draw once getData() is complete.
        if( this.startDraw == true )
        {
          console.log("startDraw - True")
          this.afterGetSetup()
          this.draw()
        }
        else
        {
          setTimeout(this.checkForStartDraw, 200)
        }
      }, // END: checkForStartDraw()

      checkForReset() {
        // Keeps checking for resetFlag (from the input container)
        // to reset the visualization when the suer clicks the reset button.
        if( this.resetFlag == 1 )
        {
          console.log("resetFlag - 1")
          this.resetVisualization()
        }
        else
        {
          setTimeout(this.checkForReset, 200)
        }
      }, // END: checkForReset()

      resetVisualization() {
        // Resets the visualization so that it's easier for the user to rerun the simulation.

        // Set output data max's to 0.
        this.maxRootDepth = 0
        this.maxHeight = 0
        this.maxTrunkRadius = 0
        this.maxLAI2 = 0

        // Set result json to be all empty.
        this.setTempDefaultlocalResultJson()

        // Clear tree scene of all drawings.
        while(this.treeScene.children.length > 0){
          this.treeScene.remove(this.treeScene.children[0])
        }

        // Clear ring scene of all drawings.
        while(this.ringScene.children.length > 0){
          this.ringScene.remove(this.ringScene.children[0])
        }

        // Hide labels
        document.getElementById("treeScaleBarMaxHeight").style.display = "none"
        document.getElementById("treeScaleBarMaxRootDepth").style.display = "none"
        document.getElementById('treeLegendZero').style.display = "none"
        document.getElementById("ringScaleBarRadiusTop").style.display = "none"
        document.getElementById("ringScaleBarRadiusMid").style.display = "none"
        document.getElementById("ringScaleBarRadiusBot").style.display = "none"
        document.getElementById("ringLegendHW").style.display = "none"
        document.getElementById("ringLegendSW").style.display = "none"
        document.getElementById('ringLegendInitR').style.display = "none"
        document.getElementById('ringLegendCurR').style.display = "none"

        // Set startDraw to false and re-call it to check when getData is done again.
        this.startDraw = false
        this.checkForStartDraw()

        // Set resetFlag to 0 and re-call it to check when the reset button is clicked again.
        this.resetFlag = 0
        this.checkForReset()

        console.log("Reset - Visualization")
      }, // END: resetVisualization()

      addBox(x, y, z, theColor) {
        console.log("adding box:", x, y, z, theColor)
        //var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
        //var r = this.localResultJson.r[this.dataIndex]      // Radius of trunk at base
        //r = r * 7 // Temporary use to negate weird data

        var boxGeo = new THREE.BoxGeometry( 1, 1, 1 )

        //var myMaterial = new THREE.MeshLambertMaterial( { map: this.barkTexture } )
        var boxMat = new THREE.MeshLambertMaterial( { color: theColor } )
        /*var sideMats =
        [
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } )
        ]*/

        //var boxMat = new THREE.MeshFaceMaterial( sideMats )
        this.box = new THREE.Mesh( boxGeo, boxMat )
        this.box.position.x = x
        this.box.position.y = y
        this.box.position.z = z
        this.treeScene.add( this.box )
      }, // END: addBox()

      addText() {
        /*
        var loader = new THREE.FontLoader()

        loader.load( 'fonts/optimer_regular.typeface.json', function ( font ) {

          var text

          var color = 0x006699

          var material = new THREE.MeshBasicMaterial( { color: color } )

          var geometry = new THREE.TextGeometry( 'Hello three.js!', {
        		font: font,
        		size: 80,
        		height: 5,
        		curveSegments: 12,
        		bevelEnabled: true,
        		bevelThickness: 10,
        		bevelSize: 8,
        		bevelOffset: 0,
        		bevelSegments: 5
        	} )

          text = new THREE.Mesh( geometry, material )
          this.treeScene.add( text )
        } ) //end load function
        */

        console.log("adding text")

        //var loader = new THREE.FontLoader()

        /*var font = loader.load(
        	// resource URL
        	'../assets/fonts/helvetiker_regular.typeface.json',

        	// onLoad callback
        	function ( font ) {
            console.log("trying to add")
            console.log("font:", font)


            var geometry = new THREE.TextGeometry( 'Hello three.js!', {
          		font: parsedFont
          	} )

            var matLite = new THREE.MeshBasicMaterial( {
  						color: red
  					} )

            text = new THREE.Mesh( geometry, material )

        		// do something with the font
        		this.treeScene.add( text )
            console.log("text added")
        	},

        	// onProgress callback
        	function ( xhr ) {
        		console.log( (xhr.loaded / xhr.total * 100) + '% loaded' )
        	},

        	// onError callback
        	function ( err ) {
        		console.log( 'An error happened' )
        	}
        )*/


        /*var loader = new THREE.FileLoader()
        loader.setResponseType('json')

        var myfont = loader.load(
          '../assets/fonts/helvetiker_regular.typeface.json'
        )
        console.log("font:", myfont)*/

        //var parsedFont = loader.parse(myfont)
        console.log("parsedFont:", this.font_helvetiker_regular)

        var geometry = new THREE.TextGeometry( 'Hello three.js!', {})

        var material = new THREE.MeshBasicMaterial( {
          color: red
        } )

        text = new THREE.Mesh( geometry, material )

        // do something with the font
        this.treeScene.add( text )
        console.log("text added")

        //var parsedFont = loader.parse(font)

        console.log("addText - Complete")
      }, // END: addText()

      temp_sd() {
        this.startDraw = true
      },

      drawRingsTemp() {
        var geoSegments = 16

        console.log("dataIndex", this.dataIndex, "\nnumRings", this.numberOfRings)

        if(this.dataIndex > this.numberOfRings)
        {
          console.log("adding rings")
          var i = this.numberOfRings + 1 // Index that goes between numberOfRings and dataIndex.
          var heartwoodRadius = this.localResultJson.r[this.dataIndex] - this.localResultJson.sw2[this.dataIndex] // Gets the heart wood radius at the current year on the slider

          while(this.dataIndex > this.numberOfRings)
          {
            // color
            var ringColor = new THREE.Color()
            if( this.localResultJson.r[i] < heartwoodRadius ) // If the current ring is part of the heart wood..
            {
              // Alternate between lighter colors
              if(i % 2 == 0) { ringColor = 0xad593b }
              else { ringColor = 0x521700 }
            }
            else                                              // If the current ring is part of the sap wood..
            {
              // Alternate between darker colors
              if(i % 2 == 0) { ringColor = 0x997354 }
              else { ringColor = 0x331700 }
            }

            var ringGeo
            if(i == 1)
            {
              // Sets the initial ring to a circle. Otherwise, there would be a hole of r0 raidus in the center.
              ringGeo = new THREE.CircleGeometry(this.localResultJson.r[i], geoSegments)
              var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
              ringMat.transparent = true
              ringMat.opacity = 0.6
              var ring = new THREE.Mesh( ringGeo, ringMat )
              this.ringScene.add( ring )
              this.ringArray[this.numberOfRings] = ring
            }
            else
            {
              // RingGeometry(innerRadius : Float, outerRadius : Float, thetaSegments : Integer, phiSegments : Integer, thetaStart : Float, thetaLength : Float)
              ringGeo = new THREE.RingGeometry( this.localResultJson.r[i-1], this.localResultJson.r[i], geoSegments, 1 )
              var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
              var ring = new THREE.Mesh( ringGeo, ringMat )
              this.ringScene.add( ring )
              this.ringArray[this.numberOfRings] = ring
            }

            i++
            this.numberOfRings++
          } // END: while-loop
        } // END: if(dataIndex > numberOfRings)

        if(this.dataIndex < this.numberOfRings) // If the user moves the slider down (ie, younger tree, less rings)
        {
          console.log("removing rings")
          while(this.dataIndex < this.numberOfRings) // Remove all rings that come after the current index of the slider.
          {
            this.ringScene.remove(this.ringArray[this.numberOfRings])
            this.numberOfRings--
          }
        }

        this.drawRingLegend()
        this.drawRingScale()
      }, // END: drawRingsTemp()

      tempview() {
        this.visCanvas = document.getElementById('treeCanvasport')

        var treeBoundBotLeft = new THREE.Vector3(-5, 0, 0)
        var treeBoundBotRight = new THREE.Vector3(5, 0, 0)
        var treeBoundTopRight = new THREE.Vector3(5, this.maxHeight, 0)
        var treeBoundTopLeft = new THREE.Vector3(-5, this.maxHeight, 0)

        var mypoints = []
        mypoints.push( treeBoundBotLeft )
        mypoints.push( treeBoundBotRight )
        mypoints.push( treeBoundTopRight )
        mypoints.push( treeBoundTopLeft )
        mypoints.push( treeBoundBotLeft )

        var mylineGeo = new THREE.BufferGeometry().setFromPoints( mypoints )
        var mylineMat = new THREE.LineBasicMaterial( {color: 0x008509, linewidth: 30} )
        var myscale = new THREE.Line( mylineGeo, mylineMat )
        //this.treeScene.add( myscale )

        this.treeCam.position.y = this.maxHeight / 2
        this.treeCam.position.z = this.maxHeight * 0.6
        this.treeCam.lookAt(0, this.maxHeight/2, 0)
      },

      ringZoom() {
        this.ringZoomCam = new THREE.OrthographicCamera( -this.canvasWidth/2, this.canvasWidth/2, this.canvasHeight/2, -this.canvasHeight/2, 1, 10 )
        this.ringZoomCam.position.z = 10
        this.ringZoomScene = new THREE.Scene()

        this.vector = new THREE.Vector2()
        this.textureSize = 3

        var data = new Uint8Array( this.textureSize * this.textureSize * 3 )

				this.texture = new THREE.DataTexture( data, this.textureSize, this.textureSize, THREE.RGBFormat )
				this.texture.minFilter = THREE.NearestFilter
				this.texture.magFilter = THREE.NearestFilter

				//

				var spriteMaterial = new THREE.SpriteMaterial( { map: this.texture } )
				this.sprite = new THREE.Sprite( spriteMaterial )
				this.sprite.scale.set( this.textureSize, this.textureSize, 1 )
				this.ringZoomScene.add( this.sprite )

				this.updateSpritePosition()
      },

      updateSpritePosition() {

        var halfWidth = this.canvasWidth / 2
				var halfHeight = this.canvasHeight / 2

				var halfImageWidth = this.textureSize / 2
				var halfImageHeight = this.textureSize / 2

				this.sprite.position.set( - halfWidth + halfImageWidth, halfHeight - halfImageHeight, 1 );
      },
    }, // END: methods

    mounted() {
      this.setTempDefaultlocalResultJson()
      this.checkForStartDraw()
      this.checkForReset()
    },

    updated() {
      while(this.loopFlag == 0)
      {
        if(this.localLoadingFlag = 1)
        {
          this.loopFlag = 1

          this.initializeVisualization()
          this.animate()
        }
      }
    } // END: mounted
  } // END: export default
</script>

<style>
  .outputContainer {
    width: 77%;
    height: 80%;
    margin: auto;
    padding: 2%;
    float: right;
    background-color: #9f9b9b;
    border-radius: 10px;
    float: right;
    position: relative;
    background-image: url("../assets/OutputBackground.png");
  }

  .timeStepSlider {
    -webkit-appearance: none;
    width: 100%;
    height: 15px;
    border-radius: 5px;
    background: #d3d3d3;
    outline: none;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
  }

  .timeStepSlider:hover {
    opacity: 1;
  }

  /* Tooltip container */
  .tooltip {
    position: relative;
    display: inline-block;
    text-align: center;
    float: right;
    background-color: #44c767;
    border-radius: 50%;
    width: 24px;
    height: 24px;
    font-size: 14px;
    line-height: 26px;
  }

  .tooltip:before {
    content:'?';
    font-weight: bold;
    color:#fff;
  }

  /* Tooltip text */
  .tooltip .tooltiptext {
    visibility: hidden;
    width: 520px;
    background-color: #555;
    color: #fff;
    text-align: left;
    border-radius: 6px;
    padding: 10px;
    position: absolute;
    z-index: 1;
    bottom: 0%;
    right: 140%;
  }

  /* Tooltip arrow */
  .tooltip .tooltiptext::after {
    content: "";
    position: absolute;
    top: 97%;
    left: 100%;
    margin-top: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: transparent transparent transparent #555;
  }

  /* Show the tooltip text when you mouse over the tooltip container */
  .tooltip:hover .tooltiptext {
    visibility: visible;
    opacity: 1;
  }

  .timeStepSlider::-moz-range-thumb {
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
    border-radius: 50%;
  }

  .rawDataList {
    width: 100%;
    text-align: center;
  }

  .rawData {
    column-count: 3;
    column-rule: 3px solid green;
  }

  h4 {
    color: white;
  }

  h5 {
    color: white;
  }

  .scaleBar {
    color: red;
    font-size: 20px;
    position: absolute;
  }

  .UILabel {
    position: absolute;
    color: black;
  }

  #treeCanvasport {
    position: relative;
    text-align: center;
    width: 100%;
    height: auto;
  }
</style>
