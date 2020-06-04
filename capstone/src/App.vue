<template>
  <div id="app">
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
  color: white;
}

button {
  margin-top: 10px;
  background-color: #44c767;
  border-radius: 20px;
  border: none;
  padding: 10px 30px;
  color:#ffffff;
  font-family:Arial;
  font-size: 13px;
  display: inline-block;
}

button:hover {
  background-color: #EEE;
  color: black;
}
</style>
