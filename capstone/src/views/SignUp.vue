<template>
  <div class="sign-up">
    <p>Let's create a new account !</p>
    <input type="text" v-model="email" placeholder="Email"><br>
    <input type="password" v-model="password" placeholder="Password"><br>
    <button @click="signUp">Sign Up</button><br>
    <button @click="move">Home</button>
    <span>or go back to <router-link to="/login">login</router-link>.</span>
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
          function (user) {
            alert('Your account has been created !')
          },
          function (err) {
            alert('Oops. ' + err.message)
          }
        );
      },
      move: function() {
        this.$router.replace('/')
      },
    }
  }
</script>

<style lang="css" scoped>
</style>
