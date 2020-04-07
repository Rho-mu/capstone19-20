<template>
  <div>
    <button @click="initialize()">init</button>
    <button @click="animate()">animate</button>
    <button @click="addBox()">add box</button>
    <!--<button @click="drawTree()">draw tree</button>-->
    <br>
    <!--<h3>Index: {{ dataIndex }}</h3><br>-->
    <br>
    <button @click="setCrownShape('cone')">cone</button>
    <button @click="setCrownShape('sphere')">sphere</button>
    <button @click="setCrownShape('cylinder')">cylinder</button>

    <div class="treeCanvasport" id="treeCanvasport"></div>

    <input type="range" min="3" max="5" v-model="dataIndex" id="timeStepSlider" @click="drawTree()"><br>

    <label for="s2">height: {{ treeData[dataIndex].h }}               </label><br>
    <label for="s2">heightToCrown: {{ treeData[dataIndex].hh2 }}       </label><br>
    <label for="s2">radius: {{ treeData[dataIndex].r }}               </label><br>
    <label for="s2">radiusBase: {{ treeData[dataIndex].rB2 }}          </label><br>
    <label for="s2">radiusBreast: {{ treeData[dataIndex].rBH }}       </label><br>
    <label for="s2">radiusCrownBase: {{ treeData[dataIndex].rC2 }}     </label><br>
    <label for="s2">leafArea: {{ treeData[dataIndex].la2 }}            </label><br>
    <label for="s2">growthState: {{ treeData[dataIndex].growth_st }}  </label><br>
  </div>
</template>

<script>
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
  name: 'vistest',
  data() {
    return {
      dataIndex: "0",
      treeData: json.trees,
      crownShape: "cone",
    }
  },

  methods: {
    initialize() {
      /////////////// Tree Scene ///////////////
      this.treeCanvas = document.getElementById( "treeCanvasport" );
      var treeCanvasWidth = window.innerWidth * 0.7
      var treeCanvasHeight = window.innerHeight * 0.7

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

      this.trunk = new THREE.Mesh( new THREE.CylinderGeometry( 1, 1, 1, 1 ), new THREE.MeshBasicMaterial( {color: 0xb5651d} ) )
      this.crown = new THREE.Mesh( new THREE.CylinderGeometry( 1, 1, 1, 1 ), new THREE.MeshBasicMaterial( {color: 0xb5651d} ) )


    }, // END: initialize()

    addBox() {
      //var myTexture = barkTex
      var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
      var myMaterial = new THREE.MeshBasicMaterial( { map: myTexture } )
      //var myMaterial = new THREE.MeshBasicMaterial( { color: 0xFFFF00 } )
      var boxGeometry = new THREE.BoxGeometry( 1, 1, 1 );
      var box = new THREE.Mesh( boxGeometry, myMaterial )
      box.position.x = 8
      box.position.y = 0
      this.treeScene.add( box )
    }, // END: addBox()

    drawTree() {
      var index = document.getElementById("timeStepSlider").value // Get index from the slider

      while(this.treeScene.children.length > 0){                  // Clear scene of old tree
        this.treeScene.remove(this.treeScene.children[0]);
      }
      this.newScene = new THREE.Scene()                           // Create new scene for new tree
      this.treeScene.add( this.newScene )                         // Add new scene to root scene

      // ACGCA output
      var height = this.treeData[index].height
      var heightToCrown = this.treeData[index].heightToCrown
      var radiusCrownBase  = this.treeData[index].radiusCrownBase
      var radius = this.treeData[index].radius
      var radiusBase = this.treeData[index].radiusBase
      var radiusBreast = this.treeData[index].radiusBreast
      var leafArea = this.treeData[index].leafArea
      var growthState = this.treeData[index].growthState

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
      //console.log("h:",height,"\nHtC:",heightToCrown,"\nrcb:",radiusCrownBase,"\nr:",radius,"\nrb:",radiusBase,"\nrBr:",radiusBreast,"\nla:",leafArea,"\ngs:",growthState)

      // Suplimental parameters
      var geoSegments = 20
      var crownRadius = radius
      var trunkPos = heightToCrown/2 - 2.8
      var crownPos = height - (height - heightToCrown)/2 - 2.8

      /// Trunk ///
      // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
      var trunkGeo = new THREE.CylinderGeometry( radius, radiusBase, heightToCrown, geoSegments )
      var trunkMat = new THREE.MeshBasicMaterial( {color: 0xb5651d} )
      this.trunk = new THREE.Mesh( trunkGeo, trunkMat )
      this.trunk.position.y = trunkPos
      this.trunk.position.x = 0

      /// Crown ///
      var crownGeo
      if( this.crownShape == "cone" )
      {
        // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.ConeGeometry( radiusCrownBase, height-heightToCrown, geoSegments )
      }
      else if( this.crownShape == "sphere")
      {
        // SphereGeometry(radius : Float, widthSegments : Integer, heightSegments : Integer)
        crownGeo = new THREE.SphereGeometry( radiusCrownBase, geoSegments*1.5, geoSegments*1.5 )
      }
      else if( this.crownShape == "cylinder" )
      {
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.CylinderGeometry( radiusCrownBase, radiusCrownBase, height-heightToCrown, geoSegments );
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


      this.newScene.add( this.crown )
      this.newScene.add( this.trunk )
    }, // END: drawTree()

    setCrownShape(shape) {
      this.crownShape = shape
      console.log("crownShape:", shape)

      this.drawTree()
    }, // END: setCrownShape()

    update() {
      //this.trunk.rotation.y += 0.01
      //this.crown.rotation.y += 0.01
    }, // END: update()

    animate() {
      requestAnimationFrame(this.animate)
      this.update()
      this.treeRenderer.render(this.treeScene, this.treeCam)
    } // END: animate()
  }
}

</script>

<style>

</style>
