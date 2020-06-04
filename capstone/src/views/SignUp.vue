<template>
  <div class="sign-up">
    <div class="content">
      <img src="../assets/logo.png"><br>
      <h4>Let's create a new account !</h4>
      <input type="text" v-model="email" placeholder="Email"><br>
      <input type="password" v-model="password" placeholder="Password"><br>
      <button @click="signUp">Sign Up</button>
      <span>Go back to <router-link class="link" to="/login">login</router-link></span>
    </div>
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
    background-image: url('../assets/Background.png');
    min-height: 100%;
    min-width: 1024px;

    /* Set up proportionate scaling */
    width: 100%;
    height: auto;

    /* Set up positioning */
    position: fixed;
    top: 0;
    left: 0;
    z-index: -1;
  }

  img {
    height: 80px;
    width: 80px;
  }

  .content {
    margin-top: 160px;
    color: white;
  }

  input {
    margin: 10px 0;
    width: 20%;
    padding: 15px;
    border-radius: 10px;
    border-width: thin;
  }

  span {
    margin-top: 20px;
    display: block;
    font-size: 14px;
  }

  .link {
    color: #ffb901;
  }
  .link:hover {
    color: red;
  }
</style>
