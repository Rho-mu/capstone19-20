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
    font-family: Arial, Helvetica, sans-serif;    
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: white;
  }

  img {
    height: 80px;
    width: 80px;
  }

  button {
    margin-top: 10px;
    background-color: #44c767;
    border-radius: 15px;
    border: none;
    padding: 10px 30px;
    color:#ffffff;
    font-family:Arial;
    font-size: 12px;
    outline: none;
    vertical-align: middle;
  }

  button:hover {
    background-color: #EEE;
    color: black;
  }

  input {
    border-radius: 5px;
    border: thin;
    outline: none;
  }


</style>
