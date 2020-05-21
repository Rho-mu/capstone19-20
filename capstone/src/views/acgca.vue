<template>
  <div>
    <inputContainer></inputContainer>
    <br>
    <inputsvis></inputsvis>
  </div>
</template>

<script>
import inputsvis from './inputs-vis.vue'
import inputContainer from './inputContainer.vue'
//import outputContainer from './outputContainer.vue'

export default {
  name: 'acgca',

  components: {
    inputsvis,
    inputContainer
  },

  data() {

  }
}
</script>

<style>

</style>
