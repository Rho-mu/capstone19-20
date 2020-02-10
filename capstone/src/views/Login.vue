<template>
  <div class="login">
    <h3>Sign In</h3>
    <input type="text" v-model="email" placeholder="Email"><br>
    <input type="password" v-model="password" placeholder="Password"><br>
    <button @click="login">Connection</button>
    <p>
      or Sign In with Google <br>
      <button @click="socialLogin" class="social-button">
        <img src="../assets/google-logo.png" alt="Google Logo">
      </button>
    </p>
    <p>You don't have an account ? You can <router-link to="/sign-up">create one</router-link></p>
  </div>
</template>

<script>
import firebase from 'firebase';

export default {
  name: 'login',
  data() {
    return {
      email: '',
      password: ''
    }
  },
  methods: {
    login: function() {
      firebase.auth().signInWithEmailAndPassword(this.email, this.password).then(
        (user) => {
          this.$router.replace('home')
        },
        (err) => {
          alert('Oops. ' + err.message)
        }
      );
    },
    socialLogin() {
      const provider = new firebase.auth.GoogleAuthProvider();

      firebase.auth().signInWithPopup(provider).then((result) => {
        this.$router.replace('home');
      }).catch((err) => {
        alert('Oops. ' + err.message)
      });
    },


    }
}
</script>

<style lang="css" scoped>
  .social-button {
    width: 75px;
    background: white;
    padding: 10px;
    border-radius: 100%;
    box-shadow: 0 2px 4px 0 rgba(0,0,0,0,2);
    outline: 0;
    border: 0;
  }
  .social-button:active {
    box-shadow: 0 2px 4px 0 rgba(0,0,0,0,1);
  }
  .social-button img {
    width: 100%;
  }
</style>
