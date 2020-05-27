<template>
  <div>
    <div class="outputContainer">
      <!--<button @click="loadTextures()">Load Textures</Button>-->
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
      <div id="treeCanvasport"></div>
      <div class="rawDataList" id="rawDataList">
        <br>
        <label>APARout: {{ this.resultJson.APARout[this.dataIndex] }}   </label><br>
        <label>h: {{ this.resultJson.h[this.dataIndex] }}               </label><br>
        <label>hh2: {{ this.resultJson.hh2[this.dataIndex] }}           </label><br>
        <label>hC2: {{ this.resultJson.hC2[this.dataIndex] }}           </label><br>
        <label>hB2: {{ this.resultJson.hB2[this.dataIndex] }}           </label><br>
        <label>hBH2: {{ this.resultJson.hBH2[this.dataIndex] }}         </label><br>
        <label>r: {{ this.resultJson.r[this.dataIndex] }}               </label><br>
        <label>rB2: {{ this.resultJson.rB2[this.dataIndex] }}           </label><br>
        <label>rC2: {{ this.resultJson.rC2[this.dataIndex] }}           </label><br>
        <label>rBH: {{ this.resultJson.rBH[this.dataIndex] }}           </label><br>
        <label>sw2: {{ this.resultJson.sw2[this.dataIndex] }}           </label><br>
        <label>vts2: {{ this.resultJson.vts2[this.dataIndex] }}         </label><br>
        <label>vt2: {{ this.resultJson.vt2[this.dataIndex] }}           </label><br>
        <label>vth2: {{ this.resultJson.vth2[this.dataIndex] }}         </label><br>
        <label>sa2: {{ this.resultJson.sa2[this.dataIndex] }}           </label><br>
        <label>la2: {{ this.resultJson.la2[this.dataIndex] }}           </label><br>
        <label>ra2: {{ this.resultJson.ra2[this.dataIndex] }}           </label><br>
        <label>dr2: {{ this.resultJson.dr2[this.dataIndex] }}           </label><br>
        <label>xa2: {{ this.resultJson.xa2[this.dataIndex] }}           </label><br>
        <label>bl2: {{ this.resultJson.bl2[this.dataIndex] }}           </label><br>
        <label>br2: {{ this.resultJson.br2[this.dataIndex] }}           </label><br>
        <label>bt2: {{ this.resultJson.bt2[this.dataIndex] }}           </label><br>
        <label>bts2: {{ this.resultJson.bts2[this.dataIndex] }}         </label><br>
        <label>bth2: {{ this.resultJson.bth2[this.dataIndex] }}         </label><br>
        <label>boh2: {{ this.resultJson.boh2[this.dataIndex] }}         </label><br>
        <label>bos2: {{ this.resultJson.bos2[this.dataIndex] }}         </label><br>
        <label>bo2: {{ this.resultJson.bo2[this.dataIndex] }}           </label><br>
        <label>bs2: {{ this.resultJson.bs2[this.dataIndex] }}           </label><br>
        <!--<label>cs2: {{ this.resultJson.cs2[this.dataIndex] }}       </label><br>-->
        <label>clr2: {{ this.resultJson.clr2[this.dataIndex] }}         </label><br>
        <label>fl2: {{ this.resultJson.fl2[this.dataIndex] }}           </label><br>
        <label>fr2: {{ this.resultJson.fr2[this.dataIndex] }}           </label><br>
        <label>ft2: {{ this.resultJson.ft2[this.dataIndex] }}           </label><br>
        <label>fo2: {{ this.resultJson.fo2[this.dataIndex] }}           </label><br>
        <label>rfl2: {{ this.resultJson.rfl2[this.dataIndex] }}         </label><br>
        <label>rfr2: {{ this.resultJson.rfr2[this.dataIndex] }}         </label><br>
        <label>rfs2: {{ this.resultJson.rfs2[this.dataIndex] }}         </label><br>
        <label>egrow2: {{ this.resultJson.egrow2[this.dataIndex] }}     </label><br>
        <label>ex2: {{ this.resultJson.ex2[this.dataIndex] }}           </label><br>
        <label>rtrans2: {{ this.resultJson.rtrans2[this.dataIndex] }}   </label><br>
        <label>light2: {{ this.resultJson.light2[this.dataIndex] }}     </label><br>
        <label>nut2: {{ this.resultJson.nut2[this.dataIndex] }}         </label><br>
        <label>deltas2: {{ this.resultJson.deltas2[this.dataIndex] }}   </label><br>
        <label>LAI2: {{ this.resultJson.LAI2[this.dataIndex] }}         </label><br>
        <!-- <label>status2: {{ this.resultJson.status2[this.dataIndex] }}   </label><br> -->
        <!--<label>errorind: {{ this.resultJson.errorind[this.dataIndex] }}   </label><br>-->
        <!--<label>growth_st: {{ this.resultJson.growth_st[this.dataIndex] }} </label><br>-->
        <br>
        <div>
          <download-csv class="downloadbutton" :data="this.array" name = "treeData.csv">
            <button @click="downloadRawData()">Download</button>
          </download-csv>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import * as THREE from 'three'
  import JsonCSV from 'vue-json-csv'

  export default {
    name: 'outputContainer',

    components: {'download-csv': JsonCSV},

    props: ['resultJsonProp', 'postBodyProp'],

    data() {
      return {
        resultJson: this.resultJsonProp,
        postBody: this.postBodyProp,
        dataIndex: "1",
        currentScene: this.treeScene,
        currentCam: this.treeCam,
        crownShape: "cone",
        array : []
      } // END: return
    }, // END: data()

    methods: {
      initializeVisualization() {
        /////////////// Tree Scene ///////////////
        this.treeCanvas = document.getElementById('treeCanvasport')
        console.log("treeCanvas:", this.treeCanvas)

        //console.log("outputCanvas:", this.outputContainer.innerWidth  , this.outputContainer.innerHeight  )
        var canvasWidth = window.innerWidth * 0.7
        var canvasHeight = window.innerHeight * 0.7

        ///// Tree Scene /////
        // Create scene for trees
        this.treeScene = new THREE.Scene()
        this.treeScene.background = new THREE.Color( 0xcfffff )
        // Create camera for tree scene
        // PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )
        this.treeCam = new THREE.PerspectiveCamera( 90, canvasWidth / canvasHeight, 0.1, 1000 )
        this.treeCam.position.z = 7
        this.treeScene.add( this.treeCam )
        ///// Tree Scene /////

        ///// Ring Scene /////
        // Create scene for rings
        this.ringScene = new THREE.Scene()
        this.ringScene.background = new THREE.Color( 0xdfffcf  )
        // Create camera for ring scene
        // PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )
        this.ringCam = new THREE.PerspectiveCamera( 90, canvasWidth / canvasHeight, 0.1, 1000 )
        this.ringCam.position.z = 7
        this.ringScene.add( this.ringCam )
        ///// Ring Scene /////

        // Create renderer
        this.treeRenderer = new THREE.WebGLRenderer( {antialias: true} )
        this.treeRenderer.setSize( canvasWidth, canvasHeight )
        this.treeCanvas.appendChild( this.treeRenderer.domElement )

        // Create stand-in tree, but don't add it to the scene.
        this.trunk = new THREE.Mesh( new THREE.CylinderGeometry( 1, 1, 1, 1 ), new THREE.MeshBasicMaterial( {color: 0xb5651d} ) )
        this.crown = new THREE.Mesh( new THREE.CylinderGeometry( 1, 1, 1, 1 ), new THREE.MeshBasicMaterial( {color: 0xb5651d} ) )

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

        window.addEventListener( 'resize', this.onWindowResize, false )
      }, // END: initializeVisualization()

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
        // Move to afterGet() once tuned.
        var bgColor = new THREE.Color()
        bgColor.r = this.postBody.io/2060
        bgColor.g = this.postBody.io/2060+0.4
        bgColor.b = 1
        this.treeScene.background = bgColor

        var year = this.dataIndex // The current timestep on the slider. Named "year" to make it easier to read.
        // This stuff should be calculated once after getData.
        // Find max radius and height of tree over its life to scale the scene to.
        // Find max LAI2 to normalize it for opacity.
        var maxHeight = 0
        var maxLAI2 = 0
        for( var i = 1; i <= this.postBody.t; i++ )
        {
          // Find max height.
          if( maxHeight < this.resultJson.h[i] )
          {
            maxHeight = this.resultJson.h[i]
          }
          // Find max radius.
          if( maxLAI2 < this.resultJson.r[i] )
          {
            maxLAI2 = this.resultJson.r[i]
          }
          // Find max LAI2.
          if( maxHeight < this.resultJson.LAI2[i] )
          {
            maxHeight = this.resultJson.LAI2[i]
          }
        }
        //console.log("Max LAI2:", maxLAI2)

        // Clear scene of old drawings
        while(this.treeScene.children.length > 0){   // Clear scene of old tree
          this.treeScene.remove(this.treeScene.children[0])
        }
        this.newScene = new THREE.Scene()            // Create new scene for new tree
        this.treeScene.add( this.newScene )          // Add new scene to root scene

        this.addBox()
        this.addLight()

        /// Trunk variables
        var h = this.resultJson.h[year]      // Total tree height
        var hB = this.resultJson.hB2[year]   // Height that trunk transitions from neiloid to paraboloid (base to trunk)
        hB = this.postBody.etaB * h
        var hC = this.resultJson.hC2[year]   // Height that trunk transitions from paraboloid to cone (trunk to crown)
        hC = this.postBody.eta * h
        var r = this.resultJson.r[year]      // Radius of trunk at base
        var rB = this.resultJson.rB2[year]   // Radius of trunk when transitioning from neilooid to paraboloid (base to trunk)
        var rC = this.resultJson.rC2[year]   // Radius of trunk when transitioning from parapoloid to cone (trunk to crown)

        /// Crown variables (overlaid on "cone" part of trunk)
        var hmax = this.postBody.hmax        // Input.
        var phih = this.postBody.phih        // Input.
        var eta = this.postBody.eta          // Input.
        var m = this.postBody.m              // Input.
        var alpha = this.postBody.alpha      // Input.
        var r0 = this.postBody.r0            // Input.
        var r40 = this.postBody.r40          // Input.
        var rBH = this.resultJson.rBH[year]  // Output.
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
        console.log("rcmax",rcmax)

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

        console.log("year:",year,"\nLAI2:",this.resultJson.LAI2[year],"\nh:",h,"\nhC:",hC,"\nhB:",hB,"\nr:",r,"\nrB:",rB,"\nrC:",rC,"\nrBH:",rBH,"\nrcmax:",rcmax,"\nrcbase:",rcbase)

        // Supplemental parameters
        var geoSegments = 20            // Segments of geometry
        var trunkPos = hC/2             // Trunk position on the screen. Needs to be based on max height.
        var crownPos = h - (h - hC)/2   // Crown position on the screen. Bottom of crown needs to be on the same x plan as top of trunk.

        ///// Trunk /////
        // Trunk Top

        // Trunk Middle

        // Trunk Base
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        var trunkGeo = new THREE.CylinderGeometry( rC, r, hC, geoSegments )
        var trunkMat = new THREE.MeshLambertMaterial( {color: 0xb5651d} )
        this.trunk = new THREE.Mesh( trunkGeo, trunkMat )
        this.trunk.position.y = trunkPos
        this.trunk.position.x = 0

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
        crownMat.opacity = this.resultJson.LAI2[year]/maxLAI2
        //console.log("crown opacity:", crownMat.opacity)

        this.crown = new THREE.Mesh( crownGeo, crownMat )
        this.crown.position.y = crownPos
        this.crown.position.x = 0
        //console.log("Crown -", "\nradius:", rcbase, "\nheight:", h-hC,)
        ///// Crown /////

        // Resize camera based on max tree height
        this.currentCam.position.y = maxHeight / 1.8
        this.currentCam.position.z = maxHeight * 0.6
        this.currentCam.lookAt(0, maxHeight/1.8, 0)
        // Add trunk and crown to scene
        this.newScene.add( this.crown )
        this.newScene.add( this.trunk )
      }, // END: drawTree()

      drawRings() {
        var geoSegments = 16

        // Clear scene of previous drawings
        while(this.ringScene.children.length > 0){                  // Clear scene of old rings
          this.ringScene.remove(this.ringScene.children[0])
        }
        this.newScene = new THREE.Scene()                           // Create new scene for new rings
        this.ringScene.add( this.newScene )                         // Add new scene to root scene

        // Find max radius and scale scene to that size
        var maxRadius = this.resultJson.r[this.postBody.t]
        this.ringCam.position.z = maxRadius * 1.1

        this.ringCam.lookAt(0, 0, 0)

        var heartwoodRadius = this.resultJson.r[this.dataIndex] - this.resultJson.sw2[this.dataIndex] // Gets the heart wood radius at the current year on the slider
        //console.log("sw:", this.resultJson.sw2[this.dataIndex], "\nr:", this.resultJson.r[this.dataIndex], "\nhw:", heartwoodRadius)


        for( var i = 1; i <= this.dataIndex; i++ )
        {
          var ringGeo

          // RingGeometry(innerRadius : Float, outerRadius : Float, thetaSegments : Integer, phiSegments : Integer, thetaStart : Float, thetaLength : Float)
          if(i == 1)
          {
            // Sets the initial ring to a circle. Otherwise, there would be a hole of r0 raidus in the center.
            ringGeo = new THREE.CircleGeometry(this.resultJson.r[i], geoSegments)
          }
          else
          {
            ringGeo = new THREE.RingGeometry( this.resultJson.r[i-1], this.resultJson.r[i], geoSegments, 1 )
          }

          // color
          var ringColor = new THREE.Color()
          if( this.resultJson.r[i] < heartwoodRadius ) // If the current ring is part of the heart wood..
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

      // adding ambient light to the render
      addLight() {
        // Ambient light for all objects.
        // AmbientLight( color : Integer, intensity : Float )
        var light = new THREE.AmbientLight( 0x404040 )
        this.treeScene.add( light )

        // Point light for casting shadows.
        // PointLight( color : Integer, intensity : Float, distance : Number, decay : Float )
        /*var pointLight = new THREE.PointLight( 0xffffff, this.postBody.io/2060*2.5, 100 )
        console.log("light:",this.postBody.io/2060*2.5)
        pointLight.position.set( 10, 10, 10 )
        this.treeScene.add( pointLight )*/
      }, // END: addLight

      // test code for adding photos to the threejs render
      addBox() {
        //var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
        var r = this.resultJson.r[this.dataIndex]      // Radius of trunk at base
        r = r * 7 // Temporary use to negate weird data

        var myMaterial = new THREE.MeshLambertMaterial( { map: this.barkTexture } )
        //var myMaterial = new THREE.MeshLambertMaterial( { color: 0xFFFF00 } )

        var boxGeometry = new THREE.BoxGeometry( 1, 1, 1 );
        var box = new THREE.Mesh( boxGeometry, myMaterial )
        box.position.x = r + 1.1
        this.treeScene.add( box )
      }, // END: addBox()

      setCrownShape(shape) {
        this.crownShape = shape
        console.log("crownShape:", shape)
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
        }
        else if(scene == "rawDataScene") {
          document.getElementById("treeCanvasport").style.display = "none"
          document.getElementById("rawDataList").style.display = "block"

          document.getElementById("coneButton").style.display = "none"
          //document.getElementById("sphereButton").style.display = "none"
          document.getElementById("cylinderButton").style.display = "none"
        }
      }, // END: setScene()

      update() {
        // THREE.js function
        //this.trunk.rotation.y += 0.01
        //this.crown.rotation.y += 0.01
      }, // END: update()

      onWindowResize() {
        // Adjusts the renderer size when the window is resized.
        this.currentCam.aspect = window.innerWidth / window.innerHeight
        this.currentCam.updateProjectionMatrix()

        this.treeRenderer.setSize( window.innerWidth * 0.7, window.innerHeight * 0.7)
      }, // END: onWindowResize()

      animate() {
        // THREE.js function
        requestAnimationFrame(this.animate)
        this.update()
        this.treeRenderer.render(this.currentScene, this.currentCam)
      }, // END: animate()

      downloadRawData() {
        // Downloads the raw data output from resultJson to a .csv file
        for(let i in this.resultJson){
          let o = {name : i, v : this.resultJson[i]};
          this.array.push(this.resultJson[i])
        }
        console.log(this.array);
        console.log("object is transferred to array");
      }, // END: downloadRawData()

      setTempDefaultResultJson() {
        this.resultJson = {
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
        }
      } // END: setTempDefaultResultJson()
    }, // END: methods

    mounted() {
      this.setTempDefaultResultJson()
      setTimeout(this.initializeVisualization, 1)
      setTimeout(this.animate, 2)
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
    background-color: #b9b9b9;
    border-radius: 10px;
    float: right;
    position: relative;
    /* background-image: linear-gradient(lightblue, lightgreen); */
  }

  .outputContainer button {
    margin-top: 5px;
    background-color: #44c767;
    border-radius: 20px;
    border: none;
    padding: 10px 35px;
    color:#ffffff;
    font-family:Arial;
    font-size: 18px;
    display: inline-block;
    font-size: 12px;
  }

  .outputContainer button:hover {
    background-color: #EEE;
    color: black;
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

</style>
