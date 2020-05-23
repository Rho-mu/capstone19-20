<template>
  <div class="login">
    <img src="../assets/Logo-Black.png"><br>
    <h4>Sign In</h4>
    <input type="text" v-model="email" placeholder="Email"><br>
    <input type="password" v-model="password" placeholder="Password"><br>
    <button @click="login">Submit</button>
    <p>You don't have an account? You can <router-link to="/sign-up">create one</router-link></p>
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
      login() {
        firebase.auth().signInWithEmailAndPassword(this.email, this.password).then(
          (user) => {
            this.$router.replace('inputs-vis')
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
  .login {
    margin-top: 160px;
  }
  input {
    margin: 10px 0;
    width: 20%;
    padding: 15px;
  }

  button {
    margin-top: 10px;
    background-color: #44c767;
    border-radius: 20px;
    border: 1px solid #18ab29;
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

  p {
    font-size: 12px;
  }
  p a {
    text-decoration: underline;
    cursor: pointer;
  }
</style>
