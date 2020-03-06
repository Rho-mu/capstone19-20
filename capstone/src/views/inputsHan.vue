<template>
  <div id="inputField">
    <form>
      <h1>Input parameters (default value is red maple)</h1>
      <div class="formBox">
        <label for="hmax">Maximum Tree Height (meters)</label>
        <br>
        <input type="text" id="hmax" placeholder="Enter" value="27.5"> m
      </div>

      <div class="formBox">
        <label for="phih">Slope at H versus r curve at r = 0 m</label>
        <br>
        <input type="text" id="phih" placeholder="Enter" value="263">
      </div>

      <div class="formBox">
        <label for="eta">Relative height at which trunk transitions from a paraboloid to a cone</label>
        <br>
        <input type="text" id="eta" placeholder="Enter" value="0.64">
      </div>

      <div class="formBox">
        <label for="swmax">Maximum sapwood width</label>
        <br>
        <input type="text" id="swmax" placeholder="Enter" value="0.1"> m
      </div>

      <div class="formBox">
        <label for="lamda">Proportionality between BT and BO</label>
        <br>
        <input type="text" id="lamda" placeholder="Enter" value="0.95">
      </div>

      <div class="formBox">
        <label for="rhomax">Wood density at maximum radial growth （g dw m-3）</label>
        <br>
        <input type="text" id="rhomax" placeholder="Enter" value="525000"> g*dw*m-3
      </div>

      <div class="formBox">
        <label for="f2">Fine root area to leaf area ratio</label>
        <br>
        <input type="text" id="f2" placeholder="Enter" value="7000">
      </div>

      <div class="formBox">
        <label for="f1">Leaf area to xylem conducting area ratio</label>
        <br>
        <input type="text" id="f1" placeholder="Enter" value="4">
      </div>

      <div class="formBox">
        <label for="gammac">Maximum storage capacity of living sapwood cells(g gluc m-3)</label>
        <br>
        <input type="text" id="gammac" placeholder="Enter" value="131000"> g gluc m-3
      </div>

      <div class="formBox">
        <label for="gammaw">(Inverse) density of sapwood structural tissue(m3g dw-1)</label>
        <br>
        <input type="text" id="gammaw" placeholder="Enter" value="0.000000667"> m3g dw-1
      </div>

      <div class="formBox">
        <label for="gammax">Xylem conducting area to sapwood area ratio</label>
        <br>
        <input type="text" id="gammax" placeholder="Enter" value="0.12">
      </div>

      <div class="formBox">
        <label for="cgl">Construction costs of producing leaves (g gluc g dw-1)</label>
        <br>
        <input type="text" id="cgl" placeholder="Enter" value="1.45"> g gluc g dw-1
      </div>

      <div class="formBox">
        <label for="cgr">Construction costs of producing fine roots (g gluc g dw-1)</label>
        <br>
        <input type="text" id="cgr" placeholder="Enter" value="1.25"> g gluc g dw-1
      </div>

      <div class="formBox">
        <label for="cgw">Construction costs of producing sapwood (g gluc g dw-1)</label>
        <br>
        <input type="text" id="cgw" placeholder="Enter" value="1.37"> g gluc g dw-1
      </div>

      <div class="formBox">
        <label for="deltal">Labile carbon storage capacity of leaves (g gluc g dw-1)</label>
        <br>
        <input type="text" id="deltal" placeholder="Enter" value="0.095"> g gluc g dw-1
      </div>

      <div class="formBox">
        <label for="deltar">Labile carbon storage capacity of fine roots (g gluc g dw-1)</label>
        <br>
        <input type="text" id="deltar" placeholder="Enter" value="0.15"> g gluc g dw-1
      </div>

      <div class="formBox">
        <label for="sl">Senescence rate of leaves (year-1)</label>
        <br>
        <input type="text" id="sl" placeholder="Enter" value="1"> year-1
      </div>

      <div class="formBox">
        <label for="sla">Specific leaf area(m2g dw-1)</label>
        <br>
        <input type="text" id="sla" placeholder="Enter" value="0.0141"> m2g dw-1
      </div>

      <div class="formBox">
        <label for="so">Senescence rate of fine roots(year-1)</label>
        <br>
        <input type="text" id="so" placeholder="Enter" value="0.05"> year-1
      </div>

      <div class="formBox">
        <label for="sr">Senescence rate of or coarse roots and branches(year-1)</label>
        <br>
        <input type="text" id="sr" placeholder="Enter" value="1"> year-1
      </div>

      <div class="formBox">
        <label for="rr">Average fine root radius(m)</label>
        <br>
        <input type="text" id="rr" placeholder="Enter" value="0.00015"> m
      </div>

      <div class="formBox">
        <label for="rhor">Tissue density of fine roots(g dw m-3)</label>
        <br>
        <input type="text" id="rhor" placeholder="Enter" value="160000"> g dw m-3
      </div>

      <div class="formBox">
        <label for="rml">Maintenance respiration rate of leaves(g gluc g dw-1year-1)</label>
        <br>
        <input type="text" id="rml" placeholder="Enter" value="2.5"> g gluc g dw-1year-1
      </div>

      <div class="formBox">
        <label for="rms">Maintenance respiration rate of sapwood(g gluc g dw-1year-1)</label>
        <br>
        <input type="text" id="rms" placeholder="Enter" value="0.05"> g gluc g dw-1year-1
      </div>

      <div class="formBox">
        <label for="rmr">Maintenance respiration rate of fine root(g gluc g dw-1year-1)</label>
        <br>
        <input type="text" id="rmr" placeholder="Enter" value="1.5"> g gluc g dw-1year-1
      </div>

      <div class="formBox">
        <label for="etaB">Relative height at which trunk transitions from a neiloid to a paraboloid</label>
        <br>
        <input type="text" id="etaB" placeholder="Enter" value="0.045">
      </div>

      <div class="formBox">
        <label for="k">Light extinction coefficient</label>
        <br>
        <input type="text" id="k" placeholder="Enter" value="0.7">
      </div>

      <div class="formBox">
        <label for="epsg">Radiation-use efficiency(g gluc MJ-1)</label>
        <br>
        <input type="text" id="epsg" placeholder="Enter" value="6.75"> g gluc MJ-1
      </div>

      <div class="formBox">
        <label for="M">Maximum relative crown depth</label>
        <br>
        <input type="text" id="M" placeholder="Enter" value="0.95">
      </div>

      <div class="formBox">
        <label for="alpha">Crown curvature parameter</label>
        <br>
        <input type="text" id="alpha" placeholder="Enter" value="0.365">
      </div>

      <div class="formBox">
        <label
          for="R0"
        >Maximum potential crown radius of a tree with diameter at breast height of 0 cm (i.e., for a tree that is exactly 1.37 m tall)</label>
        <br>
        <input type="text" id="R0" placeholder="Enter" value="1.909">
      </div>

      <div class="formBox">
        <label
          for="R40"
        >Maximum potential crown radius of a tree with diameter at breast height of 40 cm</label>
        <br>
        <input type="text" id="R40" placeholder="Enter" value="5.592">
      </div>

      <div class="formBox">
        <button v-on:click="generateJson" id="submit" type="submit">Click to run</button>
        <button id="clear">clear</button>
      </div>

      <div id="msg">
          Json output for testing
        <pre></pre>
      </div>
    </form>
  </div>
</template>

<script>
export default {
  name: "App",
  methods: {
    generateJson: function(event) {
      var uniqueTrees = [];
      event.preventDefault();  //to stop the form submitting
      let uniqueTree = {
        hmax: document.getElementById("hmax").value,
        phih: document.getElementById("phih").value,
        eta: document.getElementById("eta").value,
        swmax: document.getElementById("swmax").value,
        lamdas: document.getElementById("lamda").value,
        lamdah: document.getElementById("lamda").value,
        // (lambdas = lambdah = lambda).
        rhomax: document.getElementById("rhomax").value,
        //See detailed notes in picture below table;
        // Kiona or Mike need to translate this to a quantitative rule.
        rhomin: document.getElementById("rhomax").value,
        //Don't allow user to adjust, leave out from the parameter table.
        f2: document.getElementById("f2").value,
        f1: document.getElementById("f1").value,
        gammac: document.getElementById("gammac").value,
        gammaw: document.getElementById("gammaw").value,
        gammax: document.getElementById("gammax").value,
        cgl: document.getElementById("cgl").value,
        cgr: document.getElementById("cgr").value,
        cgw: document.getElementById("cgw").value,
        deltal: document.getElementById("deltal").value,
        deltar: document.getElementById("deltar").value,
        sl: document.getElementById("sl").value,
        sla: document.getElementById("sla").value,
        sr: document.getElementById("sr").value,
        so: document.getElementById("so").value,
        rr: document.getElementById("rr").value,
        rhor: document.getElementById("rhor").value,
        rml: document.getElementById("rml").value,
        rms: document.getElementById("rms").value,
        rmr: document.getElementById("rmr").value,
        etaB: document.getElementById("etaB").value,
        k: document.getElementById("k").value,
        epsg: document.getElementById("epsg").value,
        M: document.getElementById("M").value,
        alpha: document.getElementById("alpha").value,
        R0: document.getElementById("R0").value,
        R40: document.getElementById("R40").value
      };

      uniqueTrees.push(uniqueTree);
      document.forms[0].reset(); // to clear the form for the next entries

      //for display purposes only
      console.warn("added", { uniqueTrees });
      let pre = document.querySelector("#msg pre");
      pre.textContent = "\n" + JSON.stringify(uniqueTrees, "\t", 2);

      //saving to localStorage
      localStorage.setItem("TreeInput", JSON.stringify(uniqueTrees));
    }
  }
};
</script>

<style>
.formBox{
            padding: 0.5rem 2rem;
        }
#inputField {
    text-align: left;

}
</style>


