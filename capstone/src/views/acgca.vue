<template>
  <div>
    <h2>instructionsContainer.vue import</h2>
    <instructionsContainer></instructionsContainer>
    <br>

    <h2>inputContainer.vue import</h2>
    <inputContainer></inputContainer>
    <br>
    
    <h2>inputs-vis.vue import</h2>
    <inputsvis></inputsvis><!--Going to delete once all the component are split-->
  </div>
</template>

<script>
import inputsvis from './inputs-vis.vue'
import inputContainer from './inputContainer.vue'
import instructionsContainer from './instructionsContainer.vue'

export default {
  name: 'acgca',

  components: {
    inputsvis,
    inputContainer,
    instructionsContainer
  },

  data() {

  }
}
</script>

<style>

</style>
