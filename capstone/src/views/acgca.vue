<template>
  <div>
    <instructionsContainer></instructionsContainer>
    <inputContainer></inputContainer>
    <br><inputsvis></inputsvis><!--Going to delete once all the component are split-->
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
