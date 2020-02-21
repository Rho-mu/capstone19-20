<template>
  <div id="app">
    <div>
      <img src="../assets/Logo-Black.png"><br>
      <input type="text" v-model="newUser.first_Name" placeholder="First Name" required><br>
      <input type="text" v-model="newUser.last_Name" placeholder="Last Name" required><br>
      <input type="text" v-model="newUser.occupation" placeholder="Affiliation"required><br>
      <input type="text" v-model="newUser.locale" placeholder="Locale"required><br>
      <input type="text" v-model="newUser.role" placeholder="Affiliation Role" required><br>
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
import { userRef } from '../main';

export default {
  data () {
    return {
      newUser: {
        first_Name: '',
        last_Name: '',
        occupation: '',
        local: '',
        role: ''
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
      this.$router.replace('visualization');
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
  margin-top: 20px;
  width: 10%;
  cursor: pointer;
}
input {
  margin: 10px 0;
  width: 20%;
  padding: 15px;
}
</style>
