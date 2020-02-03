<template>
    <div id="container"></div>
</template>

<script>
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
  name: 'ThreeTest',
  data() {
    return {
      data: json,
    }
  },
  methods: {
    init: function() {
      // Create scene and camera.
      this.scene = new THREE.Scene()
      this.scene.background = new THREE.Color( 0xadd8e6 );
      this.camera = new THREE.PerspectiveCamera( 75,window.innerWidth / window.innerHeight, 0.1, 1000 )

      // Create renderer
      this.renderer = new THREE.WebGLRenderer( {antialias: true} )
      this.renderer.setSize(window.innerWidth, window.innerHeight)
      document.body.appendChild(this.renderer.domElement)

      // Crown
      // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
      this.crownGeo = new THREE.ConeGeometry( this.data.crownRadius, this.data.crownHeight, 10 )
      this.crownMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
      this.crown = new THREE.Mesh( this.crownGeo, this.crownMat )
      this.crown.position.y = 2
      this.scene.add( this.crown )

      // Trunk
      // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
      this.trunkGeo = new THREE.CylinderGeometry( this.data.trunkRadiusTop, this.data.trunkRadiusBot, this.data.trunkHeight, 10 )
      this.trunkMat = new THREE.MeshBasicMaterial( {color: 0xb5651d} )
      this.trunk = new THREE.Mesh( this.trunkGeo, this.trunkMat )
      this.scene.add( this.trunk )

      this.camera.position.z = 5

      const animate = function() {}
    },

    update: function() {
      this.crown.rotation.y += 0.01
      this.trunk.rotation.y += 0.01
    },

    animate: function() {
      requestAnimationFrame(this.animate)
      this.update()
      this.renderer.render(this.scene, this.camera)
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
<style scoped>
  canvas { width: 100%; height: 100% }
  #container { height: 200px; }
</style>
