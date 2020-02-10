<template>
  <div>
    <div class="canvasport" id="canvasport"></div>
    <div class="canvasport2" id="canvasport2"></div>
  </div>
</template>

<script>
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
  name: 'treeVisual',
  data() {
    return {
      data: json,
    }
  },
  methods: {
    init: function() {
      var width = 40
      var height = 40

      // Create scene
      this.scene = new THREE.Scene()
      this.scene.background = new THREE.Color( 0xadd8e6 );

      // Create camera
      //this.camera = new THREE.OrthographicCamera( width / - 2, width / 2, height / 2, height / - 2, 1, 1000 )
      this.camera = new THREE.PerspectiveCamera( 90, window.innerWidth / window.innerHeight, 0.1, 1000 )
      this.camera.position.z = 7
      this.scene.add( this.camera )

      // Create renderer
      this.canvasport = document.getElementById( "canvasport" );
      this.renderer = new THREE.WebGLRenderer( {antialias: true} )
      this.renderer.setSize( window.innerWidth, window.innerHeight )
      this.canvasport.appendChild( this.renderer.domElement )

      /*this.light = new THREE.HemisphereLight( 0xffffff, 0x080808, 1.5 );
			this.light.position.set( - 1.25, 1, 1.25 );
			scene.add( this.light );*/

      // Create orthographic scene
      this.scene2 = new THREE.Scene()
      this.scene2.background = new THREE.Color( 0xDDDDDD );

      // Create orthographic camera
      //this.camera2 = new THREE.OrthographicCamera( width / - 2, width / 2, height / 2, height / - 2, 1, 1000 )
      this.camera2 = new THREE.OrthographicCamera( width / - 5, width / 5, height / 8, height / - 8, 1, 1000 )
      this.camera2.position.z = 10
      this.scene2.add( this.camera2 )

      // Create orthographic renderer
      this.canvasport2 = document.getElementById( "canvasport2" );
      this.renderer2 = new THREE.WebGLRenderer( {antialias: true} )
      this.renderer2.setSize( window.innerWidth, window.innerHeight )
      this.canvasport2.appendChild( this.renderer2.domElement )

      var ringGroup = new THREE.Group()

      for( var i = 0; i < 3; i++ )
      {
        // ACGCA output
        var height = this.data.trees[i].height
        var heightToCrown = this.data.trees[i].heightToCrown
        var radius = this.data.trees[i].radius
        var radiusBase = this.data.trees[i].radiusBase
        var radiusBreast = this.data.trees[i].radiusBreast
        var leafArea = this.data.trees[i].leafArea
        var growthState = this.data.trees[i].growthState

        // Suplimental parameters
        var geoSegments = 20
        var crownRadius = radius + 0.5
        var trunkPos = heightToCrown/2 - 2.8
        var crownPos = height - (height - heightToCrown)/2 - 2.8

        // Crown
        // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
        var crownGeo = new THREE.ConeGeometry( crownRadius, height-heightToCrown, geoSegments )
        var crownMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
        var crown = new THREE.Mesh( crownGeo, crownMat )
        crown.position.y = crownPos
        crown.position.x = i*4-5
        this.scene.add( crown )

        // Trunk
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        var trunkGeo = new THREE.CylinderGeometry( radius, radiusBase, heightToCrown, geoSegments )
        var trunkMat = new THREE.MeshBasicMaterial( {color: 0xb5651d} )
        var trunk = new THREE.Mesh( trunkGeo, trunkMat )
        trunk.position.y = trunkPos
        trunk.position.x = i*4-5
        this.scene.add( trunk )

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
      this.scene2.add( ringGroup )
    },

    update: function() {
      //crown.rotation.y += 0.01
      //trunk.rotation.y += 0.01
      //ring.rotation.z -= 0.01
    },

    animate: function() {
      requestAnimationFrame(this.animate)
      this.update()
      this.renderer.render(this.scene, this.camera)
      this.renderer2.render(this.scene2, this.camera2)
    }
  },
  mounted() {
    this.init()
    this.animate()
    // http://www.codekayak.net/load-json-data-component-vue/
    /*$.getJSON('endpoint', json => {
      this.products = json.data
      console.log(json.data)
    })*/
  }
}

</script>
<style>
  .canvasport { display: block; width: 50%; height: 30%; border: 2px solid red;}
  .canvasport2 { display: block; width: 50%; height: 30%; border: 2px solid blue;}
</style>
