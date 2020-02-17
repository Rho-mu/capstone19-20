<template>
  <div id="app">
    <div>
      <label>Name:</label>
      <input type="text" v-model="newUser.first_Name" />
      <input type="text" v-model="newUser.last_Name" />
      <input type="text" v-model="newUser.occupation" />
      <button @click="submitName()">Add</button>

    </div>
    <div>
      <ul>
        <li v-for="user of users"
          v-bind:key="user['.key']">
        </li>
      </ul>
    </div>
  </div>
</template>

<script>
import { userRef } from './firebase';

export default {
  data () {
    return {
      newUser: {
        first_Name: '',
        last_Name: '',
        occupation: ''
      }
    }
  },
  firebase: {
    users: userRef
  },
  methods: {
    submitName() {
      var keyRef = userRef.push( this.newUser );
      console.log(keyRef.key);
    }
  }
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

h1, h2 {
  font-weight: normal;
}

ul {
  list-style-type: none;
  padding: 0;
}

li {
  display: inline-block;
  margin: 0 10px;
}

a {
  color: #42b983;
}

button {
  background-color: transparent;
  border: 2px solid black;
}
</style>
