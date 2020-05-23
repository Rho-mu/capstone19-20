<template>
  <div class="sign-up">
    <img src="../assets/Logo-Black.png"><br>
    <h4>Let's create a new account !</h4>
    <input type="text" v-model="email" placeholder="Email"><br>
    <input type="password" v-model="password" placeholder="Password"><br>
    <button @click="signUp">Sign Up</button>
    <span>or go back to <router-link to="/login">login</router-link></span>
  </div>
</template>

<script>
import firebase from 'firebase';

export default {
  name: 'signUp',
  data() {
    return {
      email: '',
      password: ''
    }
  },
  methods: {
    signUp: function() {
      firebase.auth().createUserWithEmailAndPassword(this.email, this.password).then(
        (user) => {
          this.$router.replace('survey')
        },
        (err) => {
          alert('Oops. ' + err.message)
        }
      );
    }
  }
}
</script>

<style scoped>
  .sign-up {
    margin-top: 160px;
  }

  input {
    margin: 10px 0;
    width: 20%;
    padding: 15px;
    border-radius: 10px;
    border-width: thin;
  }

  button {
    margin-top: 10px;
    background-color: #44c767;
    border-radius: 20px;
    border: none;
    padding: 10px 30px;
    color:#ffffff;
  }

  button:hover {
    background-color: #EEE;
    color: black;
  }

  span {
    display: block;
    margin-top: 20px;
    font-size: 12px;
  }
</style>
