<template>
  <div>
    <div class="treeCanvasport" id="treeCanvasport"></div>
    <div class = "slidecontainer">
      <h3>ONE</h3>
      <input type="range" min="0" max="3" value="2" class="slider"
              id="timeStampSlider" name="timeStampSlider" onchange="generateTrees()">
      <br><span>Tree: {{ data[document.getElementById("timeStampSlider").value] }}</span>
      <br><span>Tree: {{ data[0].height }}</span>
    </div>

    <div id="slideVal">a</div>
    <!--<div>
      <h3>TWO</h3>
      <input type="checkbox" id="jack" value="Jack" v-model="checkedNames">
      <label for="jack">Jack</label>
      <input type="checkbox" id="john" value="John" v-model="checkedNames">
      <label for="john">John</label>
      <input type="checkbox" id="mike" value="Mike" v-model="checkedNames">
      <label for="mike">Mike</label>
      <span>Checked names: {{ checkedNames }}</span>
      <br>

      <h3>THREE</h3>
      <select v-model="selected">
        <option v-for="tree in data" v-bind:height="tree.height" v-bind:year="tree.year">
          {{ tree.height }}
          {{ tree.year }}
        </option>
      </select>
      <span>Selected: {{ selected }}</span>
      <br>

      <input type="range" list="options">
      <br><span>Tree: {{ options }}</span>
    </div>


    <h3>FOUR</h3>
    <div v-for="tree in data">
      <label>{{ tree.year }}</label>
    </div>-->

    <div class="crossSecCanvas" id="crossSecCanvas"></div>
    <!--TESTING ONLY--><div class="testCanvas" id="testCanvas"></div>

  </div>
</template>

<script>
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
  name: 'treeVisual',
  data() {
    return {
      data: json.trees,
      crownShape: "sphere",
      checkedNames: [],
      selected: 'A',
      options: [
        { text: 'One', value: 'A' },
        { text: 'Two', value: 'B' },
        { text: 'Three', value: 'C' }
      ]
    }
  },
  methods: {
    getData: function() {
      /*fetch("https://ak04d09oj9.execute-api.us-east-2.amazonaws.com/Testing/user", {
        params: JSON.stringify({"runid": "yeah"}),
        method: "GET",
        headers: {
          "Content-Type": "application/json",
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        },
      })
      .then((data) => {
        console.log(data)
      })*/
    },

    updateSlider: function() {
      var val = document.getElementById("timeStampSlider").value
      var slideDiv = document.getElementById("slideVal")
      slideDiv.innerHTML = val
    },

    init: function() {
      /////////////// Tree Scene ///////////////
      this.treeCanvas = document.getElementById( "treeCanvasport" );
      var treeCanvasWidth = window.innerWidth * 0.9
      var treeCanvasHeight = window.innerHeight * 0.9

      // Create scene for trees
      this.treeScene = new THREE.Scene()
      this.treeScene.background = new THREE.Color( 0xadd8e6 );

      // Create camera for tree scene
      this.treeCam = new THREE.PerspectiveCamera( 90, treeCanvasWidth / treeCanvasHeight, 0.1, 1000 )
      this.treeCam.position.z = 7
      this.treeScene.add( this.treeCam )

      // Create renderer
      this.treeRenderer = new THREE.WebGLRenderer( {antialias: true} )
      this.treeRenderer.setSize( treeCanvasWidth, treeCanvasHeight )
      this.treeCanvas.appendChild( this.treeRenderer.domElement )

      /////////////// Cross-section Scene ///////////////
      // Create scene for cross-sections
      this.crossSecScene = new THREE.Scene()
      this.crossSecScene.background = new THREE.Color( 0xDDDDDD );

      // Create camera for cross-section scene
      var width = 50
      var height = 40
      this.crossSecCam = new THREE.OrthographicCamera( width / - 5, width / 5, height / 8, height / - 8, 1, 1000 )
      this.crossSecCam.position.z = 10
      this.crossSecScene.add( this.crossSecCam )

      // Create orthographic renderer
      this.crossSecCanvas = document.getElementById( "crossSecCanvas" );
      this.crossSecRenderer = new THREE.WebGLRenderer( {antialias: true} )
      this.crossSecRenderer.setSize( window.innerWidth, window.innerHeight )
      this.crossSecCanvas.appendChild( this.crossSecRenderer.domElement )

      /*for(var tree in this.data)
      {
        v-bind:year = "tree.year"
      }*/
    }, // End: init()

    generateTrees: function() {
      var ringGroup = new THREE.Group()

      /*var loader = new THREE.TextureLoader();

      // load a resource
      loader.load(
      	// resource URL
      	'../json/bark.png',

      	// onLoad callback
      	function ( texture ) {
      		// in this example we create the material when the texture is loaded
      		var material = new THREE.MeshBasicMaterial( {
      			map: texture
      		 } )
      	},

      	// onProgress callback currently not supported
      	undefined,

      	// onError callback
      	function ( err ) {
      		console.error( 'An error happened.' )
      	}
      )*/
  /*    new THREE.TextureLoader().load( '../json/bark.png', function ( texture ) {

					texture.wrapS = texture.wrapT = THREE.RepeatWrapping
					texture.anisotropy = renderer.capabilities.getMaxAnisotropy()

					//texture.matrixAutoUpdate = false; // default true; set to false to update texture.matrix manually

					var material = new THREE.MeshBasicMaterial( { map: texture } )

					mesh = new THREE.Mesh( geometry, material )
					scene.add( mesh )

					updateUvTransform()

					initGui()

					render()

				} )*/
      var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
      var myMaterial = new THREE.MeshBasicMaterial( { map: myTexture } )
      //var myMaterial = new THREE.MeshBasicMaterial( { color: 0xFFFF00 } )
      var boxGeometry = new THREE.BoxGeometry( 1, 1, 1 );
      var box = new THREE.Mesh( boxGeometry, myMaterial )
      box.position.x = 8
      box.position.y = 0
      this.treeScene.add( box )
      var j = document.getElementById("timeStampSlider").value
      //var j = key

      for( var i = 0; i < 3; i++ )
      {

        // ACGCA output
        var height = this.data[j].height
        var heightToCrown = this.data[j].heightToCrown
        var radiusCrownBase  = this.data[j].radiusCrownBase
        var radius = this.data[j].radius
        var radiusBase = this.data[j].radiusBase
        var radiusBreast = this.data[j].radiusBreast
        var leafArea = this.data[j].leafArea
        var growthState = this.data[j].growthState

        // Suplimental parameters
        var geoSegments = 10
        var crownRadius = radius
        var trunkPos = heightToCrown/2 - 2.8
        var crownPos = height - (height - heightToCrown)/2 - 2.8

        // Crown
        var crownShape = "cylinder"
        var crownGeo
        if( crownShape == "cone" )
        {
          // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
          crownGeo = new THREE.ConeGeometry( radiusCrownBase, height-heightToCrown, geoSegments )
        }
        else if( crownShape == "sphere")
        {
          // SphereGeometry(radius : Float, widthSegments : Integer, heightSegments : Integer)
          crownGeo = new THREE.SphereGeometry( radiusCrownBase, geoSegments*1.5, geoSegments*1.5 )
          crownPos = crownPos - 1
        }
        else if( crownShape == "cylinder" )
        {
          // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
          crownGeo = new THREE.CylinderGeometry( radiusCrownBase, radiusCrownBase, height-heightToCrown, geoSegments );
        }
        else if( crownShape == "Lathe" )
        {
          // LatheGeometry(points : Array, segments : Integer, phiStart : Float, phiLength : Float)
          var lathePoints = []
          for ( var i = 0; i < 10; i ++ ) {
	           lathePoints.push( new THREE.Vector2( Math.sin( i * 0.2 ) * 10 + 5, ( i - 5 ) * 2 ) )
          }
          crownGeo = new THREE.LatheGeometry( lathePoints )
        }
        var crownMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
        var crown = new THREE.Mesh( crownGeo, crownMat )
        crown.position.y = crownPos
        crown.position.x = i*4-5
        this.treeScene.add( crown )

        // Trunk
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        var trunkGeo = new THREE.CylinderGeometry( radius, radiusBase, heightToCrown, geoSegments )
        var trunkMat = new THREE.MeshBasicMaterial( {color: 0xb5651d} )
        var trunk = new THREE.Mesh( trunkGeo, trunkMat )
        trunk.position.y = trunkPos
        trunk.position.x = i*4-5
        this.treeScene.add( trunk )
        this.trunk = trunk

        // Trunk Cross-section
        // CircleGeometry(radius : Float, segments : Integer, thetaStart : Float, thetaLength : Float)
        var ringGeo = new THREE.CircleGeometry( radius, geoSegments )
        var ringColor = new THREE.Color();
        ringColor.r = 0.3*i
        ringColor.g = 0.2*i
        ringColor.b = 0.1*i
        var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
        var ring = new THREE.Mesh( ringGeo, ringMat )
        ring.position.z = -i
        ringGroup.add( ring );
        //this.scene.add( ring )
      }
      this.crossSecScene.add( ringGroup )
      this.render()
    }, // End: generateTrees()

    test: function() {
      /////////////// Tree Scene ///////////////
      // Create scene for trees
      this.testScene = new THREE.Scene()
      this.testScene.background = new THREE.Color( 0xadd8e6 );

      // Create camera for tree scene
      this.testCam = new THREE.PerspectiveCamera( 90, window.innerWidth / window.innerHeight, 0.1, 1000 )
      this.testCam.position.z = 7
      this.testScene.add( this.testCam )

      // Create renderer
      this.testCanvas = document.getElementById( "testCanvas" );
      this.testRenderer = new THREE.WebGLRenderer( {antialias: true} )
      this.testRenderer.setSize( window.innerWidth, window.innerHeight )
      this.testCanvas.appendChild( this.testRenderer.domElement )
    },

    update: function() {
      //crown.rotation.y += 0.01
      //trunk.rotation.y += 0.01
      //ring.rotation.z -= 0.01
    }, // End: update()

    render: function() {
      this.treeRenderer.render(this.treeScene, this.treeCam)
      this.crossSecRenderer.render(this.crossSecScene, this.crossSecCam)
      /*TESTING ONLY*/this.testRenderer.render(this.testScene, this.testCam)
    }, // End: render()

    animate: function() {
      requestAnimationFrame(this.animate)
      this.update()
      //this.render()

    }
  }, // End: methods

  created() {
    //this.myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
  },

  mounted() {
    //this.getData()
    this.init()
    this.generateTrees()
    //this.test()
    this.animate()

    // http://www.codekayak.net/load-json-data-component-vue/
    /*$.getJSON('endpoint', json => {
      this.products = json.data
      console.log(json.data)
    })*/
  }, // End: mounted()

  updated() {

  }
} // End: export

</script>
<style>
  .treeCanvasport { display: block; width: 90%; height: 30%; border: 2px solid red;}
  .crossSecCanvas { display: block; width: 50%; height: 30%; border: 2px solid blue;}
  .testCanvas { display: block; width: 50%; height: 30%; border: 2px solid green;}
  .slidecontainer {
    width: 90%;
  }

  .slider {
    -webkit-appearance: none;
    width: 100%;
    height: 0px;
    background: #d3d3d3;
    outline: none;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
  }

  .slider:hover {
    opacity: 1;
  }

  .slider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 25px;
    height: 30px;
    background: #4CAF50;
    cursor: pointer;
  }

  .slider::-moz-range-thumb {
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
  }
</style>
