<template>
  <div>
    <div class="instructionsContainer">
      <div class="instructionsButtons">
        <h2>
          Instructions!
          <button id="hideInstructionsButton" @click="showHideInstructions('hide')">HIDE</button>
          <button id="showInstructionsButton" @click="showHideInstructions('show')" style="display: none;">SHOW</button>
        </h2>
      </div>

      <div id="instructionsText">
        <p>1. Enter input values for the ACGCA model in the control panel on the left. You can also use the provided default values to autofill the fields.</p>
        <p>2. Once the input fields are are filled, press the "RUN" button to run the ACGCA model.</p>
        <p>3. Wait for the ACGCA model to finish running. When the output data has been retrieved, use the output box to see your simulated tree.</p>
        <br>
        <h3>Output Tools</h3>
        <p><b>Rings:</b> Shows the tree rings at each year.</p>
        <p><b>Tree:</b> Shows the tree at each year.
        <p><b>Cone:</b> Changes the tree crown to a cone.</P>
        <p><b>Cylinder:</b> Changes the tree crown to a Cylinder.</P>
        </p>
        <p><b>Data:</b> Shows the raw data from the ACGCA model at each year.</p>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'instructionsContainer',

  data() {
    return {

    } // END: return
  }, // END: data()

  methods: {
    showHideInstructions(type) {
      // Shows ot hides the instructions absed on which button was pressed.
      if( type == "hide" )
      {
        document.getElementById("instructionsText").style.display = "none"
        document.getElementById("hideInstructionsButton").style.display = "none"
        document.getElementById("showInstructionsButton").style.display = "inline"
      }
      else
      {
        document.getElementById("instructionsText").style.display = "inline"
        document.getElementById("showInstructionsButton").style.display = "none"
        document.getElementById("hideInstructionsButton").style.display = "inline"
      }
    } // END: showHideInstructions()
  } // END: methods
} // END: export default
</script>

<style>
  .instructionsContainer {
    display: block;
    width: 95.4%;
    margin: auto;
    margin-left: 0.5%;
    margin-bottom: 5px;
    padding: 1.5%;
    float: left;
    background-color: #b9b9b9;
    border-radius: 10px;
    float: left;
    position: relative;
    text-align: left;
    /*background-image: url("../assets/minimalist-forest.jpg");*/
  }

  .instructionsContainer button{
    display: inline-block;
    width: 70px;
    height: 35px;
    padding: 10px 10px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 14px;
    color: green;
    background-color: #FFF;
  }

  .instructionsContainer button:hover {
    background-color: #EEE;
  }
</style>
