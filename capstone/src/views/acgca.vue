<template>
  <div class="acgca">
    <instructionsContainer></instructionsContainer>


    <inputContainer
      v-on:resultJsonToParent="setResultJsonData"
      v-on:postBodyToParent="setPostBodyData">
    </inputContainer>


    <outputContainer
      :resultJson="resultJson"
      :postBody="postBody">
    </outputContainer>
  </div>
</template>

<script>
import inputsvis from './inputs-vis.vue'
import instructionsContainer from './instructionsContainer.vue'
import inputContainer from './inputContainer.vue'
import outputContainer from './outputContainer.vue'

export default {
  name: 'acgca',

  components: {
    inputsvis,
    instructionsContainer,
    inputContainer,
    outputContainer
  },

  data() {
    return {
      resultJson: '',
      postBody: ''
    }
  },

  methods: {
    setResultJsonData(data) {
      // When resultJsonToParent is triggered in the inputContainer tag, it calls this function.
      this.resultJson = data // Sets resultJson to the output sent from inputContainer.
    },

    setPostBodyData(data) {
      // When postBodyToParent is triggered in the inputContainer tag, it calls this function.
      this.postBody = data // Sets postBody to the output sent from inputContainer.
    }
  }
}
</script>

<style scoped>


</style>
