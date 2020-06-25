<template>
  <div>
    <div class="outputContainer" id="outputContainer">
      <button @click="addText()">TEMP: add text</button>
      <button @click="temp_sd()">TEMP: start draw</button>
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
        <p class="scaleBar" id="maxHeightText">{{this.dataIndex/*this.maxHeight*/}}</p>
        <p class="scaleBar" id="curHeightText">{{this.dataIndex/*this.localResultJson.h[this.dataIndex]*/}}</p>
        <p class="scaleBar" id="trunkTopText">{{this.dataIndex/*this.localResultJson.hC[this.dataIndex]*/}}</p>
        <p class="scaleBar" id="trunkMidText">{{this.dataIndex/*this.localResultJson.hB[this.dataIndex]*/}}</p>
        <p class="scaleBar" id="trunkBaseText">0</p>

        <p class="scaleBar" id="topleft">top left</p>
        <p class="scaleBar" id="topright">top right</p>
        <p class="scaleBar" id="botleft">bot left</p>
        <p class="scaleBar" id="botright">bot right</p>
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
        maxHeight: 0,
        maxRadius: 0,
        maxLAI2: 0,
        crownShape: "cone",
        array : [],
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

        // Allow canvas to resize with window.
        window.addEventListener( 'resize', this.onWindowResize, false )

        this.tempview()

        console.log("initializeVisualization - Complete")
      }, // END: initializeVisualization()

      tempview() {
        this.visCanvas = document.getElementById('treeCanvasport')

        var treeBoundBotLeft = new THREE.Vector3(-5, 0, 0)
        var treeBoundBotRight = new THREE.Vector3(5, 0, 0)
        var treeBoundTopRight = new THREE.Vector3(5, this.maxHeight, 0)
        var treeBoundTopLeft = new THREE.Vector3(-5, this.maxHeight, 0)


        this.text2 = document.createElement('div')
        this.text2.style.position = 'absolute'
        this.text2.style.height = 100
        this.text2.style.backgroundColor = "blue"
        this.text2.innerHTML = "text 2"
        this.visCanvas.appendChild(this.text2)

        this.text2.style.top = 0 + 'px'
        this.text2.style.left = this.canvasWidth/2 + 'px'



        this.text3 = document.createElement('div')
        this.text3.style.position = 'absolute'
        this.text3.style.backgroundColor = "blue"
        this.text3.innerHTML = "text 3"
        this.visCanvas.appendChild(this.text3)


        var vector = new THREE.Vector3(0, 0, 0)

        vector.x = (vector.x + 1)/2 * this.canvasWidth
        vector.y = -(vector.y - 1)/2 * this.canvasHeight
        this.text3.style.top = vector.y + 'px'
        this.text3.style.left = vector.x + 'px'



        var mypoints = []
        mypoints.push( treeBoundBotLeft )
        mypoints.push( treeBoundBotRight )
        mypoints.push( treeBoundTopRight )
        mypoints.push( treeBoundTopLeft )
        mypoints.push( treeBoundBotLeft )

        var mylineGeo = new THREE.BufferGeometry().setFromPoints( mypoints )
        var mylineMat = new THREE.LineBasicMaterial( {color: 0x008509, linewidth: 30} )
        var myscale = new THREE.Line( mylineGeo, mylineMat )
        this.treeScene.add( myscale )

        this.treeCam.position.y = this.maxHeight / 2
        this.treeCam.position.z = this.maxHeight * 0.6
        this.treeCam.lookAt(0, this.maxHeight/2, 0)
      },

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
          // Find max height.
          if( this.maxHeight < this.localResultJson.h[i] )
          {
            this.maxHeight = this.localResultJson.h[i]
          }

          // Find max LAI2.
          if( this.maxLAI2 < this.localResultJson.LAI2[i] )
          {
            this.maxLAI2 = this.localResultJson.LAI2[i]
          }

          // Find max Radius. The larger value between rcmax (max r of crown) and max r (max r of base of trunk).
          var h = this.localResultJson.h[i]     // Total tree height
          const BH = 1.37                       // Breast height. Contsant 1.37 meters
          var r0 = this.postBody.r0             // Input.
          var r40 = this.postBody.r40           // Input.
          var rBH = this.localResultJson.rBH[i] // Output.
          var r = this.localResultJson.r[i]     // Radius of trunk at base
          var hmax = this.postBody.hmax         // Input.
          var phih = this.postBody.phih         // Input.

          var rcmax // Maximum potential radius at a crown ratio of m
          if( h > BH )
          {
            // if h > BH --> rcmax = r0 + ((r40 - r0) * (2 * rBH * 100) / 40)
            rcmax = r0 + ((r40 - r0) * (2 * rBH * 100) / 40)
          }
          else if( h < BH )
          {
            // if h < BH --> rcmax = (r0 * r) / ((hmax / phih) * ln(hmax/(hmax - BH)))
            rcmax = (r0 * r) / ((hmax / phih) * Math.log(hmax/(hmax - BH)))
          }

          // Check for larger rcmax.
          if( this.maxRadius < rcmax )
          {
            this.maxRadius = rcmax
          }

          // Check for larger base radius.
          if( this.maxRadius < this.localResultJson.r[i] )
          {
            this.maxRadius = this.localResultJson.r[i]
          }
        } // END: for i to t

        // Resize camera based on max tree height or radius
        var scale = this.maxHeight
        if( this.maxHeight > this.maxRadius )
        {
          scale = this.maxHeight * 0.6
        }
        else
        {
          scale = this.maxRadius * 0.9
        }
        this.treeCam.position.y = this.maxHeight / 2
        this.treeCam.position.z = scale
        this.treeCam.lookAt(0, this.maxHeight/2, 0)

        //console.log("maxHeight", this.maxHeight)
        //console.log("maxRadius", this.maxRadius)
        //console.log("maxLAI2", this.maxLAI2)
        console.log("afterGetSetup - Complete")
      }, // END: afterGetSetup()

      draw() {
        if(this.currentScene == this.treeScene)
        {
          this.drawTree()
        }
        else if(this.currentScene == this.ringScene)
        {
          this.drawRings()
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
        ///// Trunk /////



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
        //console.log("crown opacity:", crownMat.opacity)

        this.crown = new THREE.Mesh( crownGeo, crownMat )
        this.crown.position.y = crownPos
        //console.log("Crown -", "\nradius:", rcbase, "\nheight:", h-hC,)
        ///// Crown /////


        // Add trunk and crown to scene
        this.newScene.add( this.crown )
        this.newScene.add( this.trunkTop )
        this.newScene.add( this.trunkMid )
        this.newScene.add( this.trunkBase )


        ///// Scale /////
        var  rightEdgeOfScreen = this.treeCam.position.z * (this.canvasWidth/this.canvasHeight)
        var points = []

        // YELLOW //
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, this.maxHeight, 0 ) ) // Max height
        points.push( new THREE.Vector3( rightEdgeOfScreen - 5, this.maxHeight, 0 ) ) // Max height
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, this.maxHeight, 0 ) ) // Max height
        var maxHeightText = document.getElementById("maxHeightText")
        var maxHeightpx = String(this.canvasHeight) + "px"
        maxHeightText.style.top = maxHeightpx
        //console.log("pos-maxHeightText", maxHeightText.style.top)

        // GREEN //
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, h, 0 ) ) // current height
        points.push( new THREE.Vector3( rightEdgeOfScreen - 5, h, 0 ) ) // current height
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, h, 0 ) ) // current height
        var curHeightText = document.getElementById("curHeightText")
        var curHeightpx = String(this.canvasHeight - h) + "px"
        curHeightText.style.top = curHeightpx
        //console.log("pos-curHeightText", curHeightText.style.top)

        // BLUE //
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, hC, 0 ) ) // trunk top
        points.push( new THREE.Vector3( rightEdgeOfScreen - 5, hC, 0 ) ) // trunk top
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, hC, 0 ) ) // trunk top
        var trunkTopText = document.getElementById("trunkTopText")
        var trunkToppx = String(this.canvasHeight - hC) + "px"
        trunkTopText.style.top = trunkToppx
        //console.log("pos-trunkTopText", trunkTopText.style.top)

        // PURPLE //
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, hB, 0 ) ) // trunk mid
        points.push( new THREE.Vector3( rightEdgeOfScreen - 5, hB, 0 ) ) // trunk mid
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, hB, 0 ) ) // trunk mid
        var trunkMidText = document.getElementById("trunkMidText")
        var trunkMidpx = String(this.canvasHeight - hB) + "px"
        trunkMidText.style.top = trunkMidpx
        //console.log("pos-trunkMidText", trunkMidText.style.top)

        // BLACK //
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, 0, 0 ) ) // trunk base
        points.push( new THREE.Vector3( rightEdgeOfScreen - 5, 0, 0 ) ) // trunk base
        points.push( new THREE.Vector3( rightEdgeOfScreen - 1, 0, 0 ) ) // trunk base
        var trunkBaseText = document.getElementById("trunkBaseText")
        var trunkBasepx = "0px"
        trunkBaseText.style.top = trunkBasepx
        //console.log("pos-trunkBaseText", trunkBaseText.style.top)

        var lineGeo = new THREE.BufferGeometry().setFromPoints( points )
        var lineMat = new THREE.LineBasicMaterial( {color: 0x008509, linewidth: 30} )
        var scale = new THREE.Line( lineGeo, lineMat )
        this.newScene.add( scale )
        ///// Scale /////
      }, // END: drawTree()

      drawRings() {
        var geoSegments = 16

        // Clear scene of previous drawings
        while(this.ringScene.children.length > 0){           // Clear scene of old rings
          this.ringScene.remove(this.ringScene.children[0])
        }
        this.newScene = new THREE.Scene()                    // Create new scene for new rings
        this.ringScene.add( this.newScene )                  // Add new scene to root scene

        this.ringCam.position.z = this.localResultJson.r[this.postBody.t] * 1.1   // Scale scene to final radius of the trunk so that no rings are off-screne.
        this.ringCam.lookAt(0, 0, 0)

        var heartwoodRadius = this.localResultJson.r[this.dataIndex] - this.localResultJson.sw2[this.dataIndex] // Gets the heart wood radius at the current year on the slider
        //console.log("sw:", this.localResultJson.sw2[this.dataIndex], "\nr:", this.localResultJson.r[this.dataIndex], "\nhw:", heartwoodRadius)

        for( var i = 1; i <= this.dataIndex; i++ )
        {
          var ringGeo

          // RingGeometry(innerRadius : Float, outerRadius : Float, thetaSegments : Integer, phiSegments : Integer, thetaStart : Float, thetaLength : Float)
          if(i == 1)
          {
            // Sets the initial ring to a circle. Otherwise, there would be a hole of r0 raidus in the center.
            ringGeo = new THREE.CircleGeometry(this.localResultJson.r[i], geoSegments)
          }
          else
          {
            ringGeo = new THREE.RingGeometry( this.localResultJson.r[i-1], this.localResultJson.r[i], geoSegments, 1 )
          }

          // color
          var ringColor = new THREE.Color()
          if( this.localResultJson.r[i] < heartwoodRadius ) // If the current ring is part of the heart wood..
          {
            // Alternate between lighter colors
            if(i % 2 == 0) { ringColor = 0xad593b }
            else { ringColor = 0x521700 }
          }
          else                                         // If the current ring is part of the sap wood..
          {
            // Alternate between darker colors
            if(i % 2 == 0) { ringColor = 0x997354 }
            else { ringColor = 0x331700 }
          }

          var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
          var ring = new THREE.Mesh( ringGeo, ringMat )
          this.newScene.add( ring )
        } // END: for i
      }, // END: drawRings()

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

      addBox() {
        //var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
        //var r = this.localResultJson.r[this.dataIndex]      // Radius of trunk at base
        //r = r * 7 // Temporary use to negate weird data

        var boxGeo = new THREE.BoxGeometry( 1, 1, 1 )

        //var myMaterial = new THREE.MeshLambertMaterial( { map: this.barkTexture } )
        //var boxMat = new THREE.MeshLambertMaterial( { color: 0xFFFF00 } )
        var sideMats =
        [
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } ),
          new THREE.MeshBasicMaterial( { map: new THREE.TextureLoader().load('../json/bark.png'), side: THREE.DoubleSide } )
        ]

        //var boxMat = new THREE.MeshFaceMaterial( sideMats )
        var box = new THREE.Mesh( boxGeo, sideMats )
        //box.position.x = r * 1.1
        this.treeScene.add( box )
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

      setCrownShape(shape) {
        this.crownShape = shape
        console.log("Crown Shape Change -", shape)
        this.drawTree()
      }, // END: setCrownShape()

      setScene(scene) {
        if(scene == "treeScene") {
          document.getElementById("treeCanvasport").style.display = "block"
          document.getElementById("rawDataList").style.display = "none"

          document.getElementById("coneButton").style.display = "inline-block"
          //document.getElementById("sphereButton").style.display = "inline-block"
          document.getElementById("cylinderButton").style.display = "inline-block"

          this.currentScene = this.treeScene
          this.currentCam = this.treeCam
          this.drawTree()
          console.log("Scene Change - Tree")
        }
        else if(scene == "ringScene") {
          document.getElementById("treeCanvasport").style.display = "block"
          document.getElementById("rawDataList").style.display = "none"

          document.getElementById("coneButton").style.display = "none"
          //document.getElementById("sphereButton").style.display = "none"
          document.getElementById("cylinderButton").style.display = "none"

          this.currentScene = this.ringScene
          this.currentCam = this.ringCam
          this.drawRings()
          console.log("Scene Change - Rings")
        }
        else if(scene == "rawDataScene") {
          document.getElementById("treeCanvasport").style.display = "none"
          document.getElementById("rawDataList").style.display = "block"

          document.getElementById("coneButton").style.display = "none"
          //document.getElementById("sphereButton").style.display = "none"
          document.getElementById("cylinderButton").style.display = "none"
          console.log("Scene Change - Raw Data")
        }
      }, // END: setScene()

      update() {
        // THREE.js function used to move objects in the scene.
        //this.trunk.rotation.y += 0.01
        //this.crown.rotation.y += 0.01
        /*this.hudBitmap.clearRect(0, 0, this.canvasWidth, this.canvasHeight)
        this.hudBitmap.fillText("year: "+this.dataIndex, this.canvasWidth/2, this.canvasHeight/2)
  	    this.hudTexture.needsUpdate = true*/
      }, // END: update()

      onWindowResize() {
        // Adjusts the renderer size when the window is resized.
        this.canvasWidth = window.innerWidth * 0.75
        this.canvasHeight = window.innerHeight * 0.75

        this.currentCam.aspect = this.canvasWidth / this.canvasHeight
        this.currentCam.updateProjectionMatrix()

        this.renderer.setSize( this.canvasWidth, this.canvasHeight)
        this.draw()
      }, // END: onWindowResize()

      animate() {
        // THREE.js function

        //this.update()
        this.renderer.render(this.currentScene, this.currentCam)

        requestAnimationFrame(this.animate)
      }, // END: animate()

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
        this.maxHeight = 0
        this.maxRadius = 0
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

        // Set startDraw to false and re-call it to check when getData is done again.
        this.startDraw = false
        this.checkForStartDraw()

        // Set resetFlag to 0 and re-call it to check when the reset button is clicked again.
        this.resetFlag = 0
        this.checkForReset()

        console.log("Reset - Visualization")
      }, // END: resetVisualization()

      temp_sd() {
        this.startDraw = true
      },
    }, // END: methods

    mounted() {
      this.setTempDefaultlocalResultJson()
      this.checkForStartDraw()
      this.checkForReset()
      // setTimeout(this.initializeVisualization, 1)
      // setTimeout(this.animate, 2)
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

  /* .timeStepSlider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
    border-radius: 50%;
  } */

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

  #maxHeightText {
    color: yellow;
    top: 0px;
    right: 150px;
  }

  #curHeightText {
    color: green;
    top: 30px;
    right: 150px;
  }

  #trunkTopText {
    color: blue;
    top: 60px;
    right: 150px;
  }

  #trunkMidText {
    color: purple;
    top: 90px;
    right: 150px;
  }

  #trunkBaseText {
    color: black;
    top: 120px;
    right: 150px;
  }

  #topleft {
    top: 0px;
    left: 0px;
  }

  #topright {
    top: 0px;
    right: 0px;
  }

  #botleft {
    bottom: 0px;
    left: 0px;
  }

  #botright {
    bottom: 0px;
    right: 0px;
  }

  #treeCanvasport {
    position: relative;
    text-align: center;
    width: 100%;
    height: auto;
  }
</style>
