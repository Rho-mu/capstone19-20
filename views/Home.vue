<template>
  <div class="home">

    <button @click="logout">Logout</button>
  </div>
</template>

<script>
import firebase from 'firebase';
// @ is an alias to /src


export default {
  name: 'Home',
  methods: {
    logout: function() {
      firebase.auth().signOut().then(() => {
        this.$router.replace('login')
      });
    }
  }

}
</script>
