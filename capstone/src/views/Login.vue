<template>
  <div class="login">
    <div class="content">
      <img src="../assets/logo.png"><br>
      <h4>Sign In</h4>
      <input type="text" v-model="email" placeholder="Email"><br>
      <input type="password" v-model="password" placeholder="Password"><br>
      <button @click="login">Submit</button>
      <span>Don't have an account? You can <router-link class="link" to="/sign-up">create one</router-link></span>
    </div>
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
            this.$router.replace('acgca')
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
    background-image: url('../assets/Background.png');
    min-height: 100%;
    min-width: 1024px;
    width: 100%;
    height: auto;
    position: fixed;
    top: 0;
    left: 0;
    z-index: -1;
  }

  .content {
    margin-top: 160px;
    color: white;
  }

  input {
    margin: 10px 0;
    width: 20%;
    padding: 15px;
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
    color: white;
  }
</style>
