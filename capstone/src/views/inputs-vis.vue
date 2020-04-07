<template>
  <div>
    <div class="inputField">
      <div class="mention-text">
      Mention:
      <br>
              <b>Every box</b> in this form <br>
               needs to be filled with <br>
              a <b>positive</b> number<br>
              <br>
              With the <b>* mark</b> on the <br>
              right of the input box,<br>
              it means that it needs <br>
              to be not only larger <br>
              than 0 but also <b>smaller</b><br>
              <b>than 1</b><br>
             <br>
              0 and 1 are valid<br>
      </div>
    
    <div class="collapsible-menu">
      <input type="checkbox" id="menu">
      <label for="menu">Group 1</label>
      <div class="menu-content">
        <ul>
          <input type="text" v-model="postBody.hmax" placeholder="hmax"><br>
          <input type="text" v-model="postBody.phih" placeholder="phih" ><br>
          <input type="text" v-model="postBody.eta" placeholder="eta" >*<br>
          <input type="text" v-model="postBody.swmax" placeholder="swmax" ><br>
          <input type="text" v-model="postBody.lamda" placeholder="lamda"><br>
          <input type="text" v-model="postBody.rhomax" placeholder="rhomax" ><br>
          <input type="text" v-model="postBody.f2" placeholder="f2" ><br>
          <input type="text" v-model="postBody.f1" placeholder="f1" ><br>
        </ul>
      </div>
    </div>
    <div class="collapsible-menu">
      <input type="checkbox" id="menu-1">
      <label for="menu-1">Group 2</label>
      <div class="menu-content-1">
        <ul>
          <input type="text" v-model="postBody.gammac" placeholder="gammac" ><br>
          <input type="text" v-model="postBody.gammaw" placeholder="gammaw" ><br>
          <input type="text" v-model="postBody.gammax" placeholder="gammax" >*<br>
          <input type="text" v-model="postBody.cgl" placeholder="cgl" ><br>
          <input type="text" v-model="postBody.cgr" placeholder="cgr" ><br>
          <input type="text" v-model="postBody.cgw" placeholder="cgw" ><br>
        </ul>
      </div>
    </div>
    <div class="collapsible-menu">
      <input type="checkbox" id="menu-2">
      <label for="menu-2">Group 3</label>
      <div class="menu-content-2">
        <ul>
          <input type="text" v-model="postBody.deltal" placeholder="deltal" ><br>
          <input type="text" v-model="postBody.deltar" placeholder="deltar" ><br>
          <input type="text" v-model="postBody.sl" placeholder="sl" ><br>
          <input type="text" v-model="postBody.sla" placeholder="sla" ><br>
          <input type="text" v-model="postBody.so" placeholder="so" ><br>
          <input type="text" v-model="postBody.sr" placeholder="sr" ><br>
          <input type="text" v-model="postBody.rr" placeholder="rr" ><br>
        </ul>
      </div>
    </div>
    <div class="collapsible-menu">
      <input type="checkbox" id="menu-3">
      <label for="menu-3">Group 4</label>
      <div class="menu-content-3">
        <ul>
          <input type="text" v-model="postBody.rhor" placeholder="rhor" ><br>
          <input type="text" v-model="postBody.rml" placeholder="rml" ><br>
          <input type="text" v-model="postBody.rms" placeholder="rms" ><br>
          <input type="text" v-model="postBody.rmr" placeholder="rmr" ><br>
          <input type="text" v-model="postBody.etaB" placeholder="etaB" >*<br>
          <input type="text" v-model="postBody.k" placeholder="k"><br>
        </ul>
      </div>
    </div>
    <div class="collapsible-menu">
      <input type="checkbox" id="menu-4">
      <label for="menu-4">Group 5</label>
      <div class="menu-content-4">
        <ul>
          <input type="text" v-model="postBody.epsg" placeholder="epsg" ><br>
          <input type="text" v-model="postBody.m" placeholder="m" >*<br>
          <input type="text" v-model="postBody.alpha" placeholder="alpha" ><br>
          <input type="text" v-model="postBody.r0" placeholder="r0" ><br>
          <input type="text" v-model="postBody.r40" placeholder="r40"><br>
        </ul>
      </div>
    </div>
    <button :disabled='isDisabled()' @click="postData()" name="button">PostData</button>
    <button @click="getData()" name="button">GetData</button>
    </div>
    <div class="outputDisplayContainer">
      <button @click="run()">RUN</Button><br>
      <button @click="setDefault('Red Maple')">Red Maple</button>
      <button @click="setDefault('Loblolly Pine')">Loblolly Pine</button><br>
      <button @click="loadTextures()">Load Textures</Button>
      <button @click="initialize()">Init</Button>
      <button @click="animate()">Animate</Button>
      <div class="setSceneContainer">
        <button @click="setScene('ringScene')" class="ringSceneButton" id="ringSceneButton">RINGS</button>
        <button @click="setScene('treeScene')" class="treeSceneButton" id="treeSceneButton">TREE</button>
        <button @click="setScene('rawDataScene')" class="rawDataSceneButton" id="rawDataSceneButton">DATA</button>
      </div>
      <div class="crownShapeContainer">
        <button @click="setCrownShape('cone')" class="coneButton" id="coneButton">CONE</button>
        <button @click="setCrownShape('sphere')" class="sphereButton" id="sphereButton">SPHERE</button>
        <button @click="setCrownShape('cylinder')" class="cylinderButton" id="cylinderButton">CYLINDER</button>
      </div>
      <input type="range" min="0" v-model="dataIndex" @input="drawTree()" id="timeStepSlider" class="timeStepSlider">
      <div class="treeCanvasport" id="treeCanvasport"></div>
      <div class="rawDataList" id="rawDataList">
        <br>
        <!--<label>height: {{ treeData[dataIndex].h }}           </label><br>
        <label>heightToCrown: {{ treeData[dataIndex].hh2 }}      </label><br>
        <label>radius: {{ treeData[dataIndex].r }}               </label><br>
        <label>radiusBase: {{ treeData[dataIndex].rB2 }}         </label><br>
        <label>radiusBreast: {{ treeData[dataIndex].rBH }}       </label><br>
        <label>radiusCrownBase: {{ treeData[dataIndex].rC2 }}    </label><br>
        <label>leafArea: {{ treeData[dataIndex].la2 }}           </label><br>
        <label>growthState: {{ treeData[dataIndex].growth_st }}  </label><br>-->

        <label>APARout: {{ this.resultJson.APARout }}               </label><br>
        <label>h: {{ this.resultJson.h }}               </label><br>
        <label>hh2: {{ this.resultJson.hh2 }}               </label><br>
        <label>hC2: {{ this.resultJson.hC2 }}               </label><br>
        <label>hB2: {{ this.resultJson.hB2 }}               </label><br>
        <label>hBH2: {{ this.resultJson.hBH2 }}               </label><br>
        <label>r: {{ this.resultJson.r }}               </label><br>
        <label>rB2: {{ this.resultJson.rB2 }}               </label><br>
        <label>rC2: {{ this.resultJson.rC2 }}               </label><br>
        <label>rBH: {{ this.resultJson.rBH }}               </label><br>
        <label>sw2: {{ this.resultJson.sw2 }}               </label><br>
        <label>vts2: {{ this.resultJson.vts2 }}               </label><br>
        <label>vt2: {{ this.resultJson.vt2 }}               </label><br>
        <label>vth2: {{ this.resultJson.vth2 }}               </label><br>
        <label>sa2: {{ this.resultJson.sa2 }}               </label><br>
        <label>la2: {{ this.resultJson.la2 }}               </label><br>
        <label>ra2: {{ this.resultJson.ra2 }}               </label><br>
        <label>dr2: {{ this.resultJson.dr2 }}               </label><br>
        <label>xa2: {{ this.resultJson.xa2 }}               </label><br>
        <label>bl2: {{ this.resultJson.bl2 }}               </label><br>
        <label>br2: {{ this.resultJson.br2 }}               </label><br>
        <label>bt2: {{ this.resultJson.bt2 }}               </label><br>
        <label>bts2: {{ this.resultJson.bts2 }}               </label><br>
        <label>bth2: {{ this.resultJson.bth2 }}               </label><br>
        <label>boh2: {{ this.resultJson.boh2 }}               </label><br>
        <label>bos2: {{ this.resultJson.bos2 }}               </label><br>
        <label>bo2: {{ this.resultJson.bo2 }}               </label><br>
        <label>bs2: {{ this.resultJson.bs2 }}               </label><br>
        <label>cs2: {{ this.resultJson.cs2 }}               </label><br>
        <label>clr2: {{ this.resultJson.clr2 }}               </label><br>
        <label>fl2: {{ this.resultJson.fl2 }}               </label><br>
        <label>fr2: {{ this.resultJson.fr2 }}               </label><br>
        <label>ft2: {{ this.resultJson.ft2 }}               </label><br>
        <label>fo2: {{ this.resultJson.fo2 }}               </label><br>
        <label>rfl2: {{ this.resultJson.rfl2 }}               </label><br>
        <label>rfr2: {{ this.resultJson.rfr2 }}               </label><br>
        <label>rfs2: {{ this.resultJson.rfs2 }}               </label><br>
        <label>egrow2: {{ this.resultJson.egrow2 }}               </label><br>
        <label>ex2: {{ this.resultJson.ex2 }}               </label><br>
        <label>rtrans2: {{ this.resultJson.rtrans2 }}               </label><br>
        <label>light2: {{ this.resultJson.light2 }}               </label><br>
        <label>nut2: {{ this.resultJson.nut2 }}               </label><br>
        <label>deltas2: {{ this.resultJson.deltas2 }}               </label><br>
        <label>LAI2: {{ this.resultJson.LAI2 }}               </label><br>
        <label>status2: {{ this.resultJson.status2 }}               </label><br>
        <label>errorind: {{ this.resultJson.errorind }}               </label><br>
        <label>growth_st: {{ this.resultJson.growth_st }}               </label><br>
      </div>
    </div>

</div>
</template>

<script>
import axios from 'axios'
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
  name: 'inputs-vis',
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
          r40: ''
        },
        runID: '',
        getJson: [],
        resultJson: {},

        dataIndex: "0",
        maxTimeStep: "3",
        treeData: json.trees,
        crownShape: "cone",
        currentScene: this.treeScene,
        currentCam: this.treeCam,
        barkTexture: "",

        isDisable: false,
      }
    }, // END: data()

methods: {

    run() {
      console.log("run")
      this.isDisable = true // Disable run button
      console.log("disable run button")

      // user clicks run
      console.log("Starting postData()")
      this.postData() // Send inputs to AWS and model wrapper

      console.log("Starting getData()")
      setTimeout( this.getData, 2000)
      console.log("Retreived output")

      // Once the output data is retrieved from the model, animate the scene
      this.initialize()
      this.animate()
      console.log("animate")

      this.isDisable = false // Re-enable run button
      console.log("enable run button")
    }, // END: run()

    /*reset() {
      // If the user wants to run the model again, they need to hit the reset button.
      
      // Reset animate()
      isDisable = false // Re-enable run button

    }*/

    postData() {
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
        console.log(this.runID)
      })
      console.log("posted")
    }, // END: postData()

    getData() {
      alert("Hello")
      axios.get('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        headers: {
          'Content-Type': 'application/json',
          'x-run-id': this.runID
        }
      })
      .then((response) => {

        console.log(this.runID)
        this.getJson = response.data

        let newStr = this.getJson.replace(/=/g, "\":")
        let newStr2 = newStr.replace(/&/g, ",\"")
        let newStr3 = "{\"" + newStr2 + "}"
        this.resultJson = JSON.parse(newStr3)
        console.log(this.resultJson)
      },
          (error) => { console.log(error.request)}
      )
    }, // END: getData()

    setDefault(defaultType) {
      // Sets default values in the input fields based on the button that user clicks
      
      if(defaultType == "Red Maple") // Red Maple button
      {
        this.postBody.hmax=27.5;
        this.postBody.phih=263;
        this.postBody.eta=0.64;
        this.postBody.swmax=0.1;
        this.postBody.lamda=0.95;
        this.postBody.rhomax=525000;
        this.postBody.f2=7000;
        this.postBody.f1=4;
        this.postBody.gammac=131000;
        this.postBody.gammaw=6.67e-7;
        this.postBody.gammax=0.12;
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
        this.postBody.rml=2.5
        this.postBody.rms=0.05
        this.postBody.rmr=1.5
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

    initialize() {
      // Change the slider to have as many steps as timeSteps from the ACGCA model.
      document.getElementById("timeStepSlider").setAttribute("max", this.maxTimeStep)

      /////////////// Tree Scene ///////////////
      this.treeCanvas = document.getElementById( "treeCanvasport" )
      this.outputDisplayContainer = document.getElementById("outputDisplayContainer")

      console.log("window:",window.innerWidth,window.innerHeight)
      console.log("this.treeCanvas:",this.treeCanvas.innerWidth,this.treeCanvas.innerHeight)
      //console.log("outputCanvas:", this.outputDisplayContainer.innerWidth  , this.outputDisplayContainer.innerHeight  )
      var canvasWidth = window.innerWidth * 0.7
      var canvasHeight = window.innerHeight * 0.7

      ///// Tree Scene /////
      // Create scene for trees
      this.treeScene = new THREE.Scene()
      this.treeScene.background = new THREE.Color( 0xcfffff );
      // Create camera for tree scene
      this.treeCam = new THREE.PerspectiveCamera( 90, canvasWidth / canvasHeight, 0.1, 1000 )
      this.treeCam.position.z = 7
      this.treeScene.add( this.treeCam )
      ///// Tree Scene /////

      ///// Ring Scene /////
      // Create scene for rings
      this.ringScene = new THREE.Scene()
      this.ringScene.background = new THREE.Color( 0xdfffcf  );
      // Create camera for ring scene
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
    }, // END: initialize()

    loadTextures() {
      //this.barkTexture = new THREE.TextureLoader().load( '../assets/bark.png' )
      console.log("starting texture load")

      var myMaterial2
      // instantiate a loader
      var loader = new THREE.TextureLoader()
      loader.crossOrigin = ""

      // load a resource
      loader.load(
        // resource URL
        //'../assets/bark.png',
        'https://i.imgur.com/XxwCL1S.jpg',

        // onLoad callback
        function ( texture ) {
          // in this example we create the material when the texture is loaded
          myMaterial2 = new THREE.MeshBasicMaterial( {
            map: texture
          } )
          console.log("texture loaded")
        },

        // onProgress callback currently not supported
        undefined,

        // onError callback
        function ( err ) {
          console.error( 'An error happened.' )
        }
      )

      console.log("creating box")
      var boxGeometry2 = new THREE.BoxGeometry( 1, 1, 1 );
      var box2 = new THREE.Mesh( boxGeometry2, myMaterial2 )
      box2.position.x = -5
      box2.position.y = -2.5
      this.treeScene.add( box2 )

    }, // END: loadTextures()

    addBox() {
      //var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )

      var myMaterial = new THREE.MeshLambertMaterial( { map: this.barkTexture } )
      //var myMaterial = new THREE.MeshLambertMaterial( { color: 0xFFFF00 } )

      var boxGeometry = new THREE.BoxGeometry( 1, 1, 1 );
      var box = new THREE.Mesh( boxGeometry, myMaterial )
      box.position.x = 5
      box.position.y = -2.5
      this.treeScene.add( box )
    }, // END: addBox()

    drawTree() {
      var index = document.getElementById("timeStepSlider").value // Get index from the slider

      while(this.treeScene.children.length > 0){                  // Clear scene of old tree
        this.treeScene.remove(this.treeScene.children[0])
      }
      this.newScene = new THREE.Scene()                           // Create new scene for new tree
      this.treeScene.add( this.newScene )                         // Add new scene to root scene

      this.addBox()
      this.addLight()
      /*
      // ACGCA output
      var h = this.treeData[index].h                  // Height of tree (total)
      var hh = this.treeData[index].hh2               // Height of transition from parabaloid to cone (also base of crown)
      var r = this.treeData[index].r                  // Radius
      var rB = this.treeData[index].rB2               // Radius at base of tree
      var rBH = this.treeData[index].rBH              // Radius at breast height (3.37m)
      var rC  = this.treeData[index].rC2              // Radius of crown base
      var la = this.treeData[index].la2               // Total one-sided leaf area
      var growth_st = this.treeData[index].growth_st  // State of tree (alive, dead, etc.)
      //console.log("h:",h,"\nhh:",hh,"\nr:",r,"\nrB:",rB,"\nrBH:",rBH,"\nrC:",rC,"\nla:",la,"\ngrowth_st:",growth_st)
      */


      // ACGCA output
      var h = this.resultJson.h                  // Height of tree (total)
      var hh = this.resultJson.hh2               // Height of transition from parabaloid to cone (also base of crown)
      var r = this.resultJson.r                  // Radius
      var rB = this.resultJson.rB2               // Radius at base of tree
      var rBH = this.resultJson.rBH              // Radius at breast height (3.37m)
      var rC  = this.resultJson.rC2              // Radius of crown base
      var la = this.resultJson.la2               // Total one-sided leaf area
      var growth_st = this.resultJson.growth_st  // State of tree (alive, dead, etc.)
      console.log("h:",h,"\nhh:",hh,"\nr:",r,"\nrB:",rB,"\nrBH:",rBH,"\nrC:",rC,"\nla:",la,"\ngrowth_st:",growth_st)
      
      // Supplemental parameters
      var geoSegments = 16
      var trunkPos = hh/2 - 2.8
      var crownPos = h - (h - hh)/2 - 2.8

      ///// Trunk /////
      // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
      var trunkGeo = new THREE.CylinderGeometry( r, rB, hh, geoSegments )
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
        crownGeo = new THREE.ConeGeometry( rC, h-hh, geoSegments )
      }
      else if( this.crownShape == "sphere")
      {
        // SphereGeometry(radius : Float, widthSegments : Integer, heightSegments : Integer)
        crownGeo = new THREE.SphereGeometry( rC, geoSegments*1.5, geoSegments*1.5 )
      }
      else if( this.crownShape == "cylinder" )
      {
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.CylinderGeometry( rC, rC, h-hh, geoSegments );
      }
      else if( this.crownShape == "Lathe" )
      {
        // LatheGeometry(points : Array, segments : Integer, phiStart : Float, phiLength : Float)
        var lathePoints = []
        for ( var i = 0; i < 10; i ++ ) {
           lathePoints.push( new THREE.Vector2( Math.sin( i * 0.2 ) * 10 + 5, ( i - 5 ) * 2 ) )
        }
        crownGeo = new THREE.LatheGeometry( lathePoints )
      }
      else // Default to cone shaped crown
      {
        // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.ConeGeometry( rC, h-hh, geoSegments )
      }
      var crownMat = new THREE.MeshLambertMaterial( {color: 0x00FF00} )
      this.crown = new THREE.Mesh( crownGeo, crownMat )
      this.crown.position.y = crownPos
      this.crown.position.x = 0
      ///// Crown /////

      // Add trunk and crown to scene
      this.newScene.add( this.crown )
      this.newScene.add( this.trunk )
    }, // END: drawTree()

    drawRings() {
      var geoSegments = 16

      // CircleGeometry(radius : Float, segments : Integer, thetaStart : Float, thetaLength : Float)
      for( var i = 0; i <= this.maxTimeStep; i++ )
      {
        // ACGCA parameters
        var r = this.treeData[i].r  // Radius

        var ringGeo = new THREE.CircleGeometry( r, geoSegments )
        var ringColor = new THREE.Color();
        ringColor.r = 0.3*i
        ringColor.g = 0.2*i
        ringColor.b = 0.1*i
        var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
        var ring = new THREE.Mesh( ringGeo, ringMat )
        ring.position.z = -0.1*i
        this.ringScene.add( ring )
      } // END: i for-loop
    }, // END: drawRings()

    loadRawData() {
      var index = document.getElementById("timeStepSlider").value // Get index from the slider
      var rawDataList = document.getElementById("rawDataList")

      if (rawDataList.style.display === "none") {
        rawDataList.style.display = "block"
      } else {
        rawDataList.style.display = "none"
      }



      /*for(var rawData in this.treeData[index]) {
        var para = document.createElement("p")
        var node = createTextNode("HI")
        //var newNode = createTextNode(rawData + ": " + this.treeData[index][rawData] + "<br>")
        para.appendChild(node)
      }
      rawDataList.appendChild(para)*/

      //var dataList = document.getElementById("rawDataList")       // Get rawDataList element from html

      // Iterate through the data at the current timestep and print its raw data.
      /*for(var rawData in this.treeData[index]) {
        var textNode = document.createTextNode(rawData)
        dataList.appendChild(textNode)
        //dataList.innerHTML += rawData + ": " + this.treeData[index][rawData]
        //console.log(rawData,": ",this.treeData[index][rawData])
      }*/

      /*var i
      for(var rawData in this.treeData[index]) {
        var textNode = document.createTextNode(rawData)
        var existingNode = dataList.childNodes[i]
        console.log(dataList.childNodes[i])
        existingNode.replaceChild(textnode, existingNode.childNodes[i])
        i++
      }*/

      /*
      for(var rawData in this.treeData[index]) {
        var newNode = dataList.childNodes[rawData]
        newNode.replaceChild(rawData + ": " + this.treeData[index][rawData] + "<br>", newNode.childNodes[rawData])
      }*/

    }, // END: loadRawData()

    addLight() {
      // Ambient light for all objects.
      var light = new THREE.AmbientLight( 0x404040 )
      this.treeScene.add( light )

      // Point light for casting shadows.
      var pointLight = new THREE.PointLight( 0xffffff, 1, 100 )
      pointLight.position.set( 10, 10, 10 )
      this.treeScene.add( pointLight )
    }, // END: addLight

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
        document.getElementById("sphereButton").style.display = "inline-block"
        document.getElementById("cylinderButton").style.display = "inline-block"

        this.currentScene = this.treeScene
        this.currentCam = this.treeCam
        this.drawTree()
      }
      else if(scene == "ringScene") {
        document.getElementById("treeCanvasport").style.display = "block"
        document.getElementById("rawDataList").style.display = "none"

        document.getElementById("coneButton").style.display = "none"
        document.getElementById("sphereButton").style.display = "none"
        document.getElementById("cylinderButton").style.display = "none"

        this.currentScene = this.ringScene
        this.currentCam = this.ringCam
        this.drawRings()
      }
      else if(scene == "rawDataScene") {
        document.getElementById("treeCanvasport").style.display = "none"
        document.getElementById("rawDataList").style.display = "block"

        document.getElementById("coneButton").style.display = "none"
        document.getElementById("sphereButton").style.display = "none"
        document.getElementById("cylinderButton").style.display = "none"
      }
    }, // END: setScene()

    update() {
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
      requestAnimationFrame(this.animate)
      this.update()
      this.treeRenderer.render(this.currentScene, this.currentCam)
    }, // END: animate()

    checkValidity(){
      var temporaryIsDisable=false
  
      //start checking null
      temporaryIsDisable=temporaryIsDisable || (this.postBody.hmax==="");
      temporaryIsDisable=temporaryIsDisable || (this.postBody.phip==="");
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
      //finish checking null
    
      //start check the lower limit for all of the inputs
      temporaryIsDisable=temporaryIsDisable || (this.postBody.hmax < 0);
      temporaryIsDisable=temporaryIsDisable || (this.postBody.phip < 0);
      temporaryIsDisable=temporaryIsDisable || (this.postBody.eta < 0);
      temporaryIsDisable=temporaryIsDisable || (this.postBody.swmax < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.lamda < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rhomax < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.f2 < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.f1 < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammac < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammaw < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammax < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.cgl < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.cgr < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.cgw < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.deltal < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.deltar < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.sl < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.sla < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.so < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.sr < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rr < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rhor < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rml < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rms < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rmr < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.etaB < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.k < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.epsg < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.m < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.alpha < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.r0 < 0) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.r40 < 0) ;
      //finish checking for the lower limits
    
      //start checking for the higher limits(if any)
      temporaryIsDisable=temporaryIsDisable || (this.postBody.eta > 1) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammax > 1) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.etaB > 1) ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.m > 1) ;
      //finish checking for the higher limits
    
    
      this.isDisable=temporaryIsDisable;
    }, // END: checkValidity()
      
    isDisabled() {
      this.checkValidity();
      return this.isDisable;
    }, // END: isDisabled()

  }, // END: Methods

  mounted() {
    //this.initialize()
    //this.animate()
  } // END: mounted
} // END: export default
</script>

<style lang="css" scoped>
  .inputField {
    position: absolute;
    left: -50px;
    float:left;
  }

  .outputDisplayContainer {
    width: 80%;
    height: 80%;
    margin: auto;
    padding: 2%;
    float: left;
    background-color: #b9b9b9;
    border-color: green;
    border-radius: 10px;
    float: right;
    position: relative;
  }

  .outputDisplayContainer button {
    display: inline-block;
    width: 100px;
    height: 50px;
    padding: 5px 5px;
    margin: 2px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 16px;
    color: green;
    font-family: "Lucida Console", Monaco, monospace;
    background-color: #FFF;
  }

  .outputDisplayContainer button:hover {
    background-color: #EEE;
  }

  .rawDataList {
    width: 100%;
    text-align: center;
  }

  .timeStepSlider {
    -webkit-appearance: none;
    width: 100%;
    height: 25px;
    background: #d3d3d3;
    outline: none;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
  }

  .timeStepSlider:hover {
    opacity: 1;
  }

  .timeStepSlider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
  }

  .timeStepSlider::-moz-range-thumb {
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
  }

  .menu-content {
    max-height: 0;
    overflow: hidden;
    font-family: 'Oswald', sans-serif;
    padding: 0 0 0 50px;
  }

  /* Toggle Effect */

  input:checked ~ .menu-content {
    max-height: 100%;
  }

  .collapsible-menu {
    background-color: rgb(255, 255, 255);
    padding: 0px 30px;
    border-bottom: 3px solid #CDE700;
    box-shadow: 1px 2px 3px rgba(0,0,0,0.2);
  }

  .collapsible-menu ul {
    list-style-type: none;
    padding: 0;
  }

  .collapsible-menu a {
      display:block;
      padding: 10px;
      text-decoration: none;
  }

  .collapsible-menu label {
    font-family: Arial, Helvetica, sans-serif;
    font-size: 56px;
    display: block;
    cursor: pointer;
    padding: 10px 0 10px 50px;
  }input#menu {
    display: none;
  }

  .menu-content-1 {
    max-height: 0;
    overflow: hidden;
    font-family: 'Oswald', sans-serif;
    padding: 0 0 0 50px;
  }

  .menu-content-2 {
    max-height: 0;
    overflow: hidden;
    font-family: 'Oswald', sans-serif;
    padding: 0 0 0 50px;
  }

  .menu-content-3 {
    max-height: 0;
    overflow: hidden;
    font-family: 'Oswald', sans-serif;
    padding: 0 0 0 50px;
  }

  .menu-content-4 {
    max-height: 0;
    overflow: hidden;
    font-family: 'Oswald', sans-serif;
    padding: 0 0 0 50px;
  }


  /* Toggle Effect */

  input:checked ~ .menu-content-1 {
    max-height: 100%;
  }

  input:checked ~ .menu-content-2 {
    max-height: 100%;
  }

  input:checked ~ .menu-content-3 {
    max-height: 100%;
  }

  input:checked ~ .menu-content-4 {
    max-height: 100%;
  }

  .collapsible-menu label {
    font-family: Arial, Helvetica, sans-serif;
    font-size: 30px;
    display: inline-block;
    cursor: pointer;
    padding: 10px 0 10px 50px;

  }

  input#menu-1 {
    display: none;
  }

  input#menu-2 {
    display: none;
  }

  input#menu-3 {
    display: none;
  }

  input#menu-4 {
    display: none;
  }

  .buttons {
    float: left;
  }



</style>
