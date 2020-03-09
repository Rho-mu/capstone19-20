<template>
  <div>
    <div class="inputField">
      <form>
        <input type="text" v-model="postBody.hmax" placeholder="hmax"><br>
        <input type="text" v-model="postBody.phih" placeholder="phih"><br>
        <input type="text" v-model="postBody.eta" placeholder="eta"><br>
        <input type="text" v-model="postBody.swmax" placeholder="swmax"><br>
        <input type="text" v-model="postBody.lamda" placeholder="lamda"><br>
        <input type="text" v-model="postBody.rhomax" placeholder="rhomax"><br>
        <input type="text" v-model="postBody.f2" placeholder="f2"><br>
        <input type="text" v-model="postBody.f1" placeholder="f1"><br>
        <input type="text" v-model="postBody.gammac" placeholder="gammac"><br>
        <input type="text" v-model="postBody.gammaw" placeholder="gammaw"><br>
        <input type="text" v-model="postBody.gammax" placeholder="gammax"><br>
        <input type="text" v-model="postBody.cgl" placeholder="cgl"><br>
        <input type="text" v-model="postBody.cgr" placeholder="cgr"><br>
        <input type="text" v-model="postBody.cgw" placeholder="cgw"><br>
        <input type="text" v-model="postBody.deltal" placeholder="deltal"><br>
        <input type="text" v-model="postBody.deltar" placeholder="deltar"><br>
        <input type="text" v-model="postBody.sl" placeholder="sl"><br>
        <input type="text" v-model="postBody.sla" placeholder="sla"><br>
        <input type="text" v-model="postBody.so" placeholder="so"><br>
        <input type="text" v-model="postBody.sr" placeholder="sr"><br>
        <input type="text" v-model="postBody.rr" placeholder="rr"><br>
        <input type="text" v-model="postBody.rhor" placeholder="rhor"><br>
        <input type="text" v-model="postBody.rml" placeholder="rml"><br>
        <input type="text" v-model="postBody.rms" placeholder="rms"><br>
        <input type="text" v-model="postBody.rmr" placeholder="rmr"><br>
        <input type="text" v-model="postBody.etaB" placeholder="etaB"><br>
        <input type="text" v-model="postBody.k" placeholder="k"><br>
        <input type="text" v-model="postBody.epsg" placeholder="epsg"><br>
        <input type="text" v-model="postBody.m" placeholder="m"><br>
        <input type="text" v-model="postBody.alpha" placeholder="alpha"><br>
        <input type="text" v-model="postBody.r0" placeholder="r0"><br>
        <input type="text" v-model="postBody.r40" placeholder="r40"><br>
      </form>
      <button @click="postData()" name="button">PostData</button>
      <button @click="getData()" name="button"></button>
    </div>

    <div class="outputDisplayContainer">
      <button @click="addBox()">add box</button>
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
        <!--<label>height: {{ treeData[dataIndex].h }}               </label><br>
        <label>heightToCrown: {{ treeData[dataIndex].hh2 }}      </label><br>
        <label>radius: {{ treeData[dataIndex].r }}               </label><br>
        <label>radiusBase: {{ treeData[dataIndex].rB2 }}         </label><br>
        <label>radiusBreast: {{ treeData[dataIndex].rBH }}       </label><br>
        <label>radiusCrownBase: {{ treeData[dataIndex].rC2 }}    </label><br>
        <label>leafArea: {{ treeData[dataIndex].la2 }}           </label><br>
        <label>growthState: {{ treeData[dataIndex].growth_st }}  </label><br>-->

        <label>APARout: {{ treeData[dataIndex].APARout }}               </label><br>
        <label>h: {{ treeData[dataIndex].h }}               </label><br>
        <label>hh2: {{ treeData[dataIndex].hh2 }}               </label><br>
        <label>hC2: {{ treeData[dataIndex].hC2 }}               </label><br>
        <label>hB2: {{ treeData[dataIndex].hB2 }}               </label><br>
        <label>hBH2: {{ treeData[dataIndex].hBH2 }}               </label><br>
        <label>r: {{ treeData[dataIndex].r }}               </label><br>
        <label>rB2: {{ treeData[dataIndex].rB2 }}               </label><br>
        <label>rC2: {{ treeData[dataIndex].rC2 }}               </label><br>
        <label>rBH: {{ treeData[dataIndex].rBH }}               </label><br>
        <label>sw2: {{ treeData[dataIndex].sw2 }}               </label><br>
        <label>vts2: {{ treeData[dataIndex].vts2 }}               </label><br>
        <label>vt2: {{ treeData[dataIndex].vt2 }}               </label><br>
        <label>vth2: {{ treeData[dataIndex].vth2 }}               </label><br>
        <label>sa2: {{ treeData[dataIndex].sa2 }}               </label><br>
        <label>la2: {{ treeData[dataIndex].la2 }}               </label><br>
        <label>ra2: {{ treeData[dataIndex].ra2 }}               </label><br>
        <label>dr2: {{ treeData[dataIndex].dr2 }}               </label><br>
        <label>xa2: {{ treeData[dataIndex].xa2 }}               </label><br>
        <label>bl2: {{ treeData[dataIndex].bl2 }}               </label><br>
        <label>br2: {{ treeData[dataIndex].br2 }}               </label><br>
        <label>bt2: {{ treeData[dataIndex].bt2 }}               </label><br>
        <label>bts2: {{ treeData[dataIndex].bts2 }}               </label><br>
        <label>bth2: {{ treeData[dataIndex].bth2 }}               </label><br>
        <label>boh2: {{ treeData[dataIndex].boh2 }}               </label><br>
        <label>bos2: {{ treeData[dataIndex].bos2 }}               </label><br>
        <label>bo2: {{ treeData[dataIndex].bo2 }}               </label><br>
        <label>bs2: {{ treeData[dataIndex].bs2 }}               </label><br>
        <label>cs2: {{ treeData[dataIndex].cs2 }}               </label><br>
        <label>clr2: {{ treeData[dataIndex].clr2 }}               </label><br>
        <label>fl2: {{ treeData[dataIndex].fl2 }}               </label><br>
        <label>fr2: {{ treeData[dataIndex].fr2 }}               </label><br>
        <label>ft2: {{ treeData[dataIndex].ft2 }}               </label><br>
        <label>fo2: {{ treeData[dataIndex].fo2 }}               </label><br>
        <label>rfl2: {{ treeData[dataIndex].rfl2 }}               </label><br>
        <label>rfr2: {{ treeData[dataIndex].rfr2 }}               </label><br>
        <label>rfs2: {{ treeData[dataIndex].rfs2 }}               </label><br>
        <label>egrow2: {{ treeData[dataIndex].egrow2 }}               </label><br>
        <label>ex2: {{ treeData[dataIndex].ex2 }}               </label><br>
        <label>rtrans2: {{ treeData[dataIndex].rtrans2 }}               </label><br>
        <label>light2: {{ treeData[dataIndex].light2 }}               </label><br>
        <label>nut2: {{ treeData[dataIndex].nut2 }}               </label><br>
        <label>deltas2: {{ treeData[dataIndex].deltas2 }}               </label><br>
        <label>LAI2: {{ treeData[dataIndex].LAI2 }}               </label><br>
        <label>status2: {{ treeData[dataIndex].status2 }}               </label><br>
        <label>errorind: {{ treeData[dataIndex].errorind }}               </label><br>
        <label>growth_st: {{ treeData[dataIndex].growth_st }}               </label><br>
      </div>
    </div>
  </div>
</template>

<script>
import axios from 'axios'
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
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
        dataIndex: "0",
        maxTimeStep: "3",
        treeData: json.trees,
        crownShape: "cone",
        currentScene: this.treeScene,
        currentCam: this.treeCam
      }
    }, // END: data()
methods: {
    // postData() {
    //   fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user", {
    //
    //     headers: {
    //       'Content-Type': 'application/json',
    //       'x-api-key': 'AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
    //       'Access-Control-Allow-Origin': '*'
    //     },
    //     method: 'post',
    //     // mode: "no-cors",
    //   })
    //
    //   .then((response) => {
    //     console.log(response)
    //     /// test stuff
    //     // this.$router.replace('outputs') // routes to the output page
    //   })
    //   .catch(e => {
    //     console.log(e)
    //   })
    // },
    postData() {
      axios.post('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        // headers: {
        //   'Content-Type': 'application/json',
        //   'x-api-key': 'AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
        //   'Access-Control-Allow-Origin': '*'
        // },
        body: this.postBody
      })
      .then(response => {
        this.runID = response.headers['x-run-id'],
        console.log(this.runID)
      });
    }, // END: postData()

    getData() {
      axios.get('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        headers: {
          "X-Run-ID": this.runID,
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        }
      })
      .then((response) => {
        console.log(runID)
        this.getJson = response.data
      })
    }, // END: getData()

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

    addBox() {
      var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )

      var myMaterial = new THREE.MeshBasicMaterial( { map: myTexture } )
      //var myMaterial = new THREE.MeshBasicMaterial( { color: 0xFFFF00 } )

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

      // ACGCA output
      var h = this.treeData[index].h                  // Height of tree (total)
      var hh = this.treeData[index].hh2               // Height of transition from parabaloid to cone (also base of crown)
      var r = this.treeData[index].r                  // Radius
      var rB = this.treeData[index].rB2               // Radius at base of tree
      var rBH = this.treeData[index].rBH              // Radius at breast height (3.37m)
      var rC  = this.treeData[index].rC2              // Radius of crown base
      var la = this.treeData[index].la2               // Total one-sided leaf area
      var growth_st = this.treeData[index].growth_st  // Growth state of tree
      console.log("h:",h,"\nhh:",hh,"\nr:",r,"\nrB:",rB,"\nrBH:",rBH,"\nrC:",rC,"\nla:",la,"\ngrowth_st:",growth_st)

      // Supplemental parameters
      var geoSegments = 16
      var trunkPos = hh/2 - 2.8
      var crownPos = h - (h - hh)/2 - 2.8

      ///// Trunk /////
      // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
      var trunkGeo = new THREE.CylinderGeometry( r, rB, hh, geoSegments )
      var trunkMat = new THREE.MeshBasicMaterial( {color: 0xb5651d} )
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
      var crownMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
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
    } // END: animate()
  }, // END: Methods

  mounted() {
    this.initialize()
    this.animate()
  } // END: mounted
} // END: export default
</script>

<style lang="css" scoped>
  .inputField {
    float: left;
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
</style>
