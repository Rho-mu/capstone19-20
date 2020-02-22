<template>
  <div id="hello">

    <br>
    <div id="content">
      <img src="@/assets/logo.png" id="logo">


    </div>
    <div id="center">Lorem ipsum dolor sit amet, consetetur sadipscing elitr,
      sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam
      erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et
      ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem
      ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr,
      sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat,
      sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum.
      Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
      <p id="return">
        <button @click="moveToLogin"id="returnButton">Returning?</button>
      </p>
      <p id="survey">
        <button @click="moveToSignUp" id="surveyButton">New?</button>
      </p>
    </div>
    <div id="topLeft">
      ACGCA Model

    </div>
  </div>


</template>

<script>
import firebase from 'firebase'
export default {
  name: 'landing',
  methods: {
    moveToSignUp: function() {
      this.$router.replace('sign-up')
    },
    moveToLogin: function() {
      this.$router.replace('login')
    }
  }

}


</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>


#hello {
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

#center {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;

}
#return {
  position: absolute;
  top:100%;
  left: 15%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;
}
#survey {
  position: absolute;
  top:100%;
  right: 10%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;
}

#logo {
  top: 0;
  right: 0;
  position: absolute;
  display: block;
  height: 100px;
  width: 100px;
}


#content {
  position: relative;
}

#topLeft {
  position: absolute;
  top: 55px;
  left: 16px;
  font-size: 28px;
  color: white;
}
</style>
