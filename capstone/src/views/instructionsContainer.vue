<template>
  <div>
    <div class="instructionsContainer">
      <div class="instructionsButtons">
        <h1>
          ACGCA Simulation and Visualization of Tree Growth
          <br>
          <button id="hideInstructionsButton" @click="showHideInstructions('hide')">Hide</button>
          <button id="showInstructionsButton" @click="showHideInstructions('show')" style="display: none;">Instructions +</button>
        </h1>
      </div>

      <div id="instructionsText">
        <p>1. Enter input values for the ACGCA model in the control panel on the left. You can also use the provided default values to autofill the fields.</p>
        <p>2. Press the "RUN" button to run the simulation. You can tell that the model is running by the dots animation on the run button.</p>
        <p>3. Wait for the ACGCA model to finish running. When the output data has been retrieved, it will be displayed in the box on the right.</p>
        <p>4. To run the simulation again, simply enter in your desired inputs and click run again. The previous tree data will be erased from the output box.</p>
        <br>
        <p>If the visualization is producing unrealistic graphics or not displaying graphical output, this could be due to unreasonable input values. Even if the input values are within the constraints provided, input values may be incompatible with each other. Try different inputs values.</p>
        <br>
        <h4>Output Tools</h4>
        <p><b>Rings:</b> Shows the tree rings and their widths at each year, and distinguishes between heartwood and sapwood.</p>
        <p><b>Tree:</b> Visualizes the tree each year, in terms of its simulated height, trunk radius, crown dimensions, and status (living vs dead).</p>
          <p class="subTool"><b>Cone:</b> Changes the tree crown to a cone.</P>
          <p class="subTool"><b>Cylinder:</b> Changes the tree crown to a cylinder.</P>
        <p><b>Data:</b> Shows the numerical (simulated) values for a subset of output variables produced by the ACGCA simulation at each year. These output data can also be downloaded (saved) as a csv file.</p>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'instructionsContainer',

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
  h1 {
    font-family: Avant Garde,Avantgarde,Century Gothic,CenturyGothic,AppleGothic,sans-serif;
    text-align: center;
    color: white;
  }
  .instructionsContainer {
    display: block;
    width: 98%;
    margin-bottom: 2px;
    padding: 1%;
    float: left;
    background-color: #11ffee00;
    border-radius: 10px;
    float: left;
    position: relative;
    text-align: left;
    background-image: url('../assets/Background.png');
  }

  .subTool {
    text-indent: 20px;
    font-size: 14px;
  }
</style>
