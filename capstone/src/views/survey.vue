<template>
  <div id="app">
    <form @submit="submitName">
      <div>
        <img src="../assets/Logo-Black.png"><br>
        <input type="text" v-model="newUser.first_Name" placeholder="First Name" required>
          <span class="help-tip">
            <p>helllo</p>
          </span><br>
        <input type="text" v-model="newUser.last_Name" placeholder="Last Name" required>
          <span class="help-tip">
            <p>helllo</p>
          </span><br>
        <input type="text" v-model="newUser.occupation" placeholder="Affiliation"required>
          <span class="help-tip">
            <p>helllo</p>
          </span><br>
        <input type="text" v-model="newUser.locale" placeholder="Locale"required>
          <span class="help-tip">
            <p>helllo</p>
          </span><br>
        <input type="text" v-model="newUser.role" placeholder="Affiliation Role" required>
          <span class="help-tip">
            <p>helllo</p>
          </span><br>
        <button type="submit" value="Submit">Add</button>
      </div>
      <div>
        <ul>
          <li v-for="user of users"
            v-bind:key="user['.key']">
          </li>
        </ul>
      </div>
  </form>
  </div>
</template>

<script>
import { userRef } from '../main';

export default {
  name: 'survey',
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
      this.$router.replace('inputs-vis');
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

.help-tip{
  position: relative;
  display: inline-block;
  text-align: center;
  background-color: #BCDBEA;
  border-radius: 50%;
  width: 24px;
  height: 24px;
  font-size: 14px;
  line-height: 26px;
  cursor: default;
}
.help-tip:before{
  content:'?';
  font-weight: bold;
  color:#fff;
}
.help-tip:hover p{
  display: inline;
  transform-origin: 100% 0%;

  -webkit-animation: fadeIn 0.3s ease-in-out;
  animation: fadeIn 0.3s ease-in-out;
}
.help-tip p{
  display: none;
  text-align: left;
  background-color: #1E2021;
  padding: 20px;
  width: 300px;
  postion: absolute;
  border-radius: 3px;
  box-shadow: 1px 1px 1px rgba(0, 0, 0, 0.2);
  right: -4px;
  color: #fff;
  font-size: 13px;
  line-height: 1.4;
}
.help-tip p:before{ /* The pointer of the tooltip */
    position: relative;
    content: '';
    width:0;
    height: 0;
    border:6px solid transparent;
    border-bottom-color:#1E2021;
    right:10px;
    top:-12px;
}
.help-tip p:after{ /* Prevents the tooltip from being hidden */
    width:100%;
    height:40px;
    content:'';
    position: relative;
    top:-40px;
    left:0;
}
@-webkit-keyframes fadeIn {
    0% {
        opacity:0;
        transform: scale(0.6);
    }

    100% {
        opacity:100%;
        transform: scale(1);
    }
}

@keyframes fadeIn {
    0% { opacity:0; }
    100% { opacity:100%; }
}
</style>
