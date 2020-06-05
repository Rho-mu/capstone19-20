<template>
  <div class="hello">

    <br>
    <div class="content">
      <img src="@/assets/logo.png" class="logo">
    </div>
    <div class="center">

      <h3>Brief overview of the ACGCA model</h3>
      <p>
      The Allometrically Constrained Growth and Carbon Allocation (ACGCA) model is an individual-based model of tree growth and mortality.
      The ACGCA model makes use of plant functional traits and allometric relationships between different tissue types or organs (i.e. leaves, roots, and stems)
      to determine how carbon is allocated within the tree to meet growth and maintenance demands.
      </p>
      <p>
      The carbon allocation scheme satisfies both allometric constraints and physiological processes, and is unique and essential to this model.
      Labile carbon is allocated among structural pools and two storage pools in a way that satisfies allometric relationships.
      The structural pools include biomass of leaves, fine roots, trunk sapwood, trunk heartwood, other (branches, coarse roots) sapwood, and other heartwood.
      One labile storage pool is associated with leaf and fine root tissue; when leaves or roots die, labile carbon in these senescing tissues can be drawn-up
      and used elsewhere within the tree. Labile carbon is also stored in the sapwood, which is used during times of stress (high labile carbon demand relative
      to carbon inputs). There is also a transient labile carbon pool that contains recent photosynthates and retranslocated carbon; this carbon is immediately
      translocated and used to meet growth and maintenance demands. If these labile carbon pools are depleted, the tree dies. There are six possible physiological
      states captured by the ACGCA model: healthy, static, shrinking, recovering, recovered, or dead. Each state is described by a set of difference equations
      satisfying mass-balance relationships between the structural and labile carbon pools.
      </p>
      <p>
      The ACGCA model requires numerical values for about 30 parameters (model inputs or “functional traits”). Currently, light is the only environmental
      driver included in the model. The model has been thoroughly tested with parameters representative of red maple (Acer rubrum) and loblolly
      ping (Pinus taeda).  The model produces time-series of simulation output related to tree height, trunk radius, canopy dimensions,
      structural biomass of different compartments (leaves, roots, trunk heartwood, trunk sapwood, etc.), physiological state, among many others.
      </p>
      <p>
      This web-based software was developed to provide a user-friendly means of exploring the ACGCA model predictions and learning about the
      processes and traits governing tree growth.
      </p>
      <h3>
      For a full description of the ACGCA model, see the following paper and its associated supplemental materials:
      </h3>
          <p>
          Ogle, K. and S.W. Pacala (2009) A modeling framework for inferring tree growth and allocation from physiological, morphological,
          and allometric traits. Tree Physiology, 29:587-605.
          </p>
      <h3>
      For additional information about the model, see:
      </h3>
          <p>
          Gemoets, D., J.J. Barber, andK. Ogle (2013). Reversible jump MCMC for inferencein a deterministic
          individual-based model of tree growth forstudying forest dynamics. Environmetrics, 24: 433-448.
          </p>
          <p>
          Fell M., J. Barber, J.W. Lichstein, and K. Ogle (2018). Multidimensional trait space informed by a
          mechanistic model of tree growth and carbon allocation. Ecosphere, 9(1):e02060. abstract
          </p>
          <p>
          Fell, M. and K. Ogle (2018). Refinement of a theoretical trait space for North American trees
          via environmental filtering. Ecological Monographs, 88:372-384.
          </p>
      <br><br><br>
      <p class="login">
        <button class="testButton" @click="moveToLogin">Returning?</button>
      </p>
      <p class="signup">
        <button class="testButton" @click="moveToSignUp">New?</button>
      </p>
    </div>
    <br>
    <div class="topLeft">
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


.hello {
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

.center {
  position: absolute;
  top: 50%;
  left: 50%;
  width: 80%;
  transform: translate(-50%, -50%);
  font-size: 13px;
  color: white;
}

.login {
  position: absolute;
  top:100%;
  left: 15%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;
}

.signup {
  position: absolute;
  top:100%;
  right: 5%;
  transform: translate(-50%, -50%);
  font-size: 18px;
  color: black;
}

.logo {
  top: 0;
  right: 20px;
  position: absolute;
  height: 80px;
  width: 80px;
}

.content {
  position: relative;
}

.topLeft {
  position: absolute;
  top: 55px;
  left: 16px;
  font-size: 24px;
  color: white;
}


</style>
