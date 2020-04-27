<template>
  <div id="hello">

    <br>
    <div id="content">
      <img src="@/assets/logo.png" id="logo">


    </div>
    <div id="center">
      ACGCA Introduction

      The Allometrically Constrained Growth and Carbon Allocation (ACGCA) model is an individually based model of tree growth and mortality originally developed by Ogle and Pacala (2009). As the name implies the ACGCA model makes use of functional traits and allometries between tissue types (i.e. leaves, roots, and stems) to determine carbon allocation in a tree.
      <br><br>
      Carbon dynamics within the tree are essential to this model. Carbon is allocated between a structural and two storage pools in a way that satisfies the aforementioned allometric relationships (Ogle and Pacala (2009). One storage pool is associated with leaf and fine root tissue. Labile carbon in this pool is retranslocated when the tissue senesceses (Ogle and Pacala 2009). The other storage pool is in the sapwood and is used in times of stress (high labile carbon demand relative to carbon inputs). Finally there is a transient labile carbon pool representative of recent photosynthate and retranslocated carbon. It is not associated with a specific tissue and is immediately redistributed within the tree to accommodate biomass production, respiration, and allocation to storage. If the labile carbon available to the tree is depleted the tree dies (Ogle and Pacala 2009).
      <br><br>
      There are six possible physiological states in the ACGCA model: healthy, static, shrinking, recovering, recovered, or dead (Ogle and Pacala 2009). Each state is described by a set of difference equations satisfying mass-balance relationshipts between structural and labile carbon pools. The only environmental driver included in the model is parmax (annual radiation for a site).
      <br><br>
      For a full description of the model see Ogle and Pacala (2009) and the accompanying supplemental material. The model has also been used in several other studies (Fell et al. 2018 and Gemoets et al 2013).
      <br><br><br>
      <p class="return">
        <button class="testButton" @click="moveToLogin"id="returnButton">Returning?</button>
      </p>
      <p class="survey">
        <button class="testButton" @click="moveToSignUp" id="surveyButton">New?</button>
      </p>
    </div>
    <br>
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
  font-size: 14px;
  color: white;

}
.return {
  position: absolute;
  top:100%;
  left: 15%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;
}
.survey {
  position: absolute;
  top:100%;
  right: 5%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;
}

#logo {
  top: 0;
  right: 0;
  position: absolute;
  display: block;

  height: 80px;
  width: 80px;
}


#content {
  position: relative;
}

#topLeft {
  position: absolute;
  top: 55px;
  left: 16px;
  font-size: 24px;
  color: white;
}

.testButton {
  background-color: #44c767;
  border-radius: 28px;
  border: 1px solid #18ab29;
  padding: 15px 32px;
  color:#ffffff;
  font-family:Arial;
  font-size: 17px;
  display: inline-block;
}

.survey button:hover {
  background-color: #EEE;
  color: black;
}
.return button:hover {
  background-color: #EEE;
  color: black;
}

</style>
