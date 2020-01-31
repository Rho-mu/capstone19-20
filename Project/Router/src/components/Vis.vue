<template>
    <div id="container"></div>
</template>

<script>
import * as THREE from 'three'

export default {
  name: 'ThreeTest',
  data() {
    return {
      cube: null,
      renderer: null,
      scene: null,
      camera: null,
      crown: null,
      trunk: null
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
      this.crownGeo = new THREE.ConeGeometry( 2, 2, 10 )
      this.crownMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
      this.crown = new THREE.Mesh( this.crownGeo, this.crownMat )
      this.crown.position.y = 2
      this.scene.add( this.crown )

      // Trunk
      this.trunkGeo = new THREE.CylinderGeometry( 1, 1, 3, 10 )
      this.trunkMat = new THREE.MeshBasicMaterial( {color: 0xb5651d} )
      this.trunk = new THREE.Mesh( this.trunkGeo, this.trunkMat )
      this.scene.add( this.trunk )

      // Example geometry
      /*const geometry = new THREE.BoxGeometry(1, 1, 1)
      const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 })
      this.cube = new THREE.Mesh(geometry, material)
      this.scene.add(this.cube)*/

      this.camera.position.z = 5

      const animate = function() {}
    },
    update: function() {
      /*this.cube.rotation.x += 0.01
      this.cube.rotation.y += 0.01*/
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
  }
}
</script>
<style scoped>
  canvas { width: 100%; height: 100% }
  #container { height: 200px; }
</style>
