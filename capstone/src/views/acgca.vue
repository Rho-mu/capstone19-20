<template>
  <div class="acgca">
    <instructionsContainer></instructionsContainer>


    <inputContainer
      v-on:resultJsonToParent="setResultJsonData"
      v-on:postBodyToParent="setPostBodyData"
      v-on:postFlagToParent="setLoadingData">
    </inputContainer>


    <outputContainer
      :resultJson="resultJson"
      :postBody="postBody"
      :loadingFlag="loadingFlag">
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
      postBody: '',
      loadingFlag: 0
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
    },

    setLoadingData(data) {
      this.loadingFlag = data
    }
  },
  mounted: function() {
    console.log(this.loadingFlag)
  }
}
</script>

<style scoped>


</style>
