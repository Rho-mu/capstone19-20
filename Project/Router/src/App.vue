<template>
  <div id="app">
    <img src="./assets/logo.png">
    <br>
    <router-link to="identification">Identification</router-link>
    <router-link to="survey">Survey</router-link>
    <router-link to="contact">Contact</router-link>
    <router-link to="warning">Warning</router-link>
    <router-link to="login">Login</router-link>
    <router-link to="upload">Upload</router-link>
    <router-link to="admin">Admin</router-link>
    <router-link to="threejs">Visualization</router-link>
    <router-view/>
  </div>
</template>

<script>
export default {
  name: 'App'
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
