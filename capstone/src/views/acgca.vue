<template>
  <div>
    <instructionsContainer></instructionsContainer>
    <inputContainer></inputContainer>
    <br>
    <inputsvis></inputsvis>
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
