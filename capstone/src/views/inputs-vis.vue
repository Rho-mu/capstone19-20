<template>
  <div>

    <div class="divider">
      </div>

    <div class="inputField">

      <div class="title-wrapper" id="input-title">
      Control Pannel
      </div>

      <span class="help-tip" id="mention">
      <p>
      <span id="mention-text">Mention</span>
      <br><br>

       </p>
       </span>

      <div class="divider">
      </div>
      <div class="divider">
      </div>
      <div class="divider">
      </div>
      <div class="divider">
      </div>
    <div class="collapsible-menu">
      <input type="checkbox" id="menu-0">
      <label for="menu-0">Default Data Sets</label>
      <div class="menu-content">
      <br>
        <button @click="setDefault('Red Maple')">Red Maple</button>
        <button @click="setDefault('Loblolly Pine')">Loblolly Pine</button>
      </div>
    </div>

      <div class="divider">
      </div>

    <div class="collapsible-menu">
      <input type="checkbox" id="menu">
      <label id="gourp1" for="menu">Allometries and <br>biomass partitioning</label>
      <div class="menu-content">
        <ul>
          <label for="phih"> phip:</label><br>
          <input id="phih" type="text" v-model="postBody.phih" placeholder="phih > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSlope of height vs trunk radius (r) curve at r = 0 m<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="eta"> eta:</label><br>
          <input id="eta" type="text" v-model="postBody.eta" placeholder="0 < eta < 1" min="0" max="1">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspRelative height that trunk transitions from paraboloid to cone<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="lamda"> lamda:</label><br>
          <input id="lamda" type="text" v-model="postBody.lamda" placeholder="0 < lamda < 1" min="0" max="1" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspProportionality between trunk and non-trunk biomass<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="f2"> f2 (RA:LA):</label><br>
          <input id="f2" type="text" v-model="postBody.f2" placeholder="f2 (RA:LA) > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspFine root area to leaf area ratio<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="f1"> f1 (LA:XA):</label><br>
          <input id="f1" type="text" v-model="postBody.f1" placeholder="f1 (LA:XA) > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspLeaf area to xylem conducting area ratio<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="gammax"> gammaX (XA:SA):</label><br>
          <input id="gammax" type="text" v-model="postBody.gammax" placeholder="0 <gammaX (XA:SA)< 1" min="0" max="1">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspXylem conducting area to sapwood area ratio<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="etaB"> etaB:</label><br>
          <input id="etaB" type="text" v-model="postBody.etaB" placeholder="0 < etaB < eta" min="0" :disabled='postBody.eta==""'>
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspRelative height at which trunk transitions from a neiloid to a paraboloid<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,eta)
            </p></span><br>

          <label for="m"> M:</label><br>
          <input id="m" type="text" v-model="postBody.m" placeholder="0 < m < 1" min="0" max="1">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum relative crown depth<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,1)
            </p></span><br>

          <label for="r0"> R0:</label><br>
          <input id="r0" type="text" v-model="postBody.r0" placeholder="R0 > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum potential crown radius of a tree with diameter at breast height of 0 cm (i.e., for a tree that is exactly 1.37 m tall)<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="r40"> R40:</label><br>
          <input id="r40" type="text" v-model="postBody.r40" placeholder="R40 > R0" min="0" :disabled='postBody.r0==""'>
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum potential crown radius of a tree with diameter at breast height of 40 cm<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (R0,+&#8734)
            </p></span><br>

          <label for="alpha"> alpha:</label><br>
          <input id="alpha" type="text" v-model="postBody.alpha" placeholder="alpha > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspCrown curvature parameter<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

      <div class="groupDivider">
     </div>

        </ul>
      </div>
    </div>

    <div class="divider">
      </div>

    <div class="collapsible-menu">
      <input type="checkbox" id="menu-1">
      <label for="menu-1">Tree and organ<br> size traits</label>
      <div class="menu-content">
        <ul>
          <label for="hmax"> Hmax:(m)</label><br>
          <input id="hmax" type="text" v-model="postBody.hmax" placeholder="0 < Hmax < 127" min="0" max="127">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum tree height<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (R0,127)
            </p></span><br>

          <label for="swmax"> SWmax:(m)</label><br>
          <input id="swmax" type="text" v-model="postBody.swmax" placeholder="SWmax > 0" min="0"  >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum sapwood width<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="rr"> rr: (m)</label><br>
          <input id="rr" type="text" v-model="postBody.rr" placeholder="rr > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspAverage fine root radius<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

      <div class="groupDivider">
     </div>

        </ul>
      </div>
    </div>

    <div class="divider">
      </div>

    <div class="collapsible-menu">
      <input type="checkbox" id="menu-2">
      <label for="menu-2">Structural traits</label>
      <div class="menu-content">
        <ul>
          <label for="rhomax"> WD: (g dw m-3)</label><br>
          <input id="rhomax" type="text" v-model="postBody.rhomax" placeholder="WD > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspWood density<br>
              <span class="separator"></span>
              Unit: g dw m-3<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

          <label for="gammaw"> gammaW: (m3g dw-1)</label><br>
          <input id="gammaw" type="text" v-model="postBody.gammaw" placeholder="gammaW">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbsp(Inverse) density of sapwood structural tissue<br>
              <span class="separator"></span>
              Unit: m3g dw-1<br>
              <span class="separator"></span>
              Constraint: none
            </p></span><br>

          <label for="sla"> sla: (m2g dw-1)</label><br>
          <input id="sla" type="text" v-model="postBody.sla" placeholder="sla > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSpecific leaf area<br>
              <span class="separator"></span>
              Unit: m2g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
            </p></span><br>

      <div class="groupDivider">
     </div>

        </ul>
      </div>
    </div>


    <div class="divider">
      </div>

    <div class="collapsible-menu">
      <input type="checkbox" id="menu-3">
      <label for="menu-3">Physiological traits</label>
      <div class="menu-content">
        <ul>
          <label for="gammac"> gammaC: (g gluc m-3)</label><br>
          <input id="gammac" type="text" v-model="postBody.gammac" placeholder="gammac > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaximum labile carbon storage capacity of living sapwood cells<br>
              <span class="separator"></span>
              Unit: g dw m-3<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="cgl"> cgL: (g gluc g dw-1)</label><br>
          <input id="cgl" type="text" v-model="postBody.cgl" placeholder="cgL > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspConstruction costs of producing leaves<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="cgr"> cgR: (g gluc g dw-1)</label><br>
          <input id="cgr" type="text" v-model="postBody.cgr" placeholder="cgr > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspConstruction costs of producing fine roots<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="cgw"> cgW: (g gluc g dw-1)</label><br>
          <input id="cgw" type="text" v-model="postBody.cgw" placeholder="cgw > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspConstruction costs of producing sapwood<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="deltal"> deltaL: (g gluc g dw-1)</label><br>
          <input id="deltal" type="text" v-model="postBody.deltal" placeholder="deltal > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspLabile carbon storage capacity of leaves<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="deltar"> deltaR: (g gluc g dw-1)</label><br>
          <input id="deltar" type="text" v-model="postBody.deltar" placeholder="deltar > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspLabile carbon storage capacity of fine roots<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="rhor"> rhor: (g dw m-3)</label><br>
          <input id="rhor" type="text" v-model="postBody.rhor" placeholder="rhor > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspTissue density of fine roots<br>
              <span class="separator"></span>
              Unit: g dw m-3<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="rml"> rmL: (g gluc g dw-1year-1)</label><br>
          <input id="rml" type="text" v-model="postBody.rml" placeholder="rmL > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaintenance respiration rate of leaves<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="rms"> rmS: (g gluc g dw-1year-1)</label><br>
          <input id="rms" type="text" v-model="postBody.rms" placeholder="rmS > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaintenance respiration rate of sapwood<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="rmr"> rmR: (g gluc g dw-1year-1)</label><br>
          <input id="rmr" type="text" v-model="postBody.rmr" placeholder="rmR > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspMaintenance respiration rate of fine roots<br>
              <span class="separator"></span>
              Unit: g gluc g dw-1year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="k"> k: (g gluc g dw-1year-1)</label><br>
          <input id="k" type="text" v-model="postBody.k" placeholder="k > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspLight extinction coefficient<br>
              <span class="separator"></span>
              Unit: none<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="epsg"> epsg (RUE): (g gluc MJ-1)</label><br>
          <input id="epsg" type="text" v-model="postBody.epsg" placeholder="0 < epsg < 15.73" min="0" max="15.73">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspRadiation-use efficiency<br>
              <span class="separator"></span>
              Unit: g gluc MJ-1<br>
              <span class="separator"></span>
              Constraint: (0,15.73)
          </p></span><br>

      <div class="groupDivider">
     </div>

        </ul>
      </div>
    </div>

    <div class="divider">
      </div>

    <div class="collapsible-menu">
      <input type="checkbox" id="menu-4">
      <label for="menu-4">Turn-over and <br>senescence traits</label>
      <div class="menu-content">
        <ul>
          <label for="sl"> sL: (year-1)</label><br>
          <input id="sl" type="text" v-model="postBody.sl" placeholder="sL > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSenescence rate of leaves<br>
              <span class="separator"></span>
              Unit: year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="sr"> sR: (year-1)</label><br>
          <input id="sr" type="text" v-model="postBody.sr" placeholder="sR > 0" min="0">
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSenescence rate of fine roots<br>
              <span class="separator"></span>
              Unit: year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="so"> sO: (year-1)</label><br>
          <input id="so" type="text" v-model="postBody.so" placeholder="sO > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspSenescence rate of or coarse roots and branches<br>
              <span class="separator"></span>
              Unit: year-1<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

          <label for="initialRadius"> Initial radius: (m)</label><br>
          <input id="initialRadius" type="text" v-model="postBody.radius" placeholder="radius > 0" min="0" >
          <span class="help-tip">
            <p>
              &nbspInformation Box<br>
              <span class="separator"></span>
              Name:&nbspInitial radius<br>
              <span class="separator"></span>
              Unit: m<br>
              <span class="separator"></span>
              Constraint: (0,+&#8734)
          </p></span><br>

      <div class="groupDivider">
     </div>

        </ul>
      </div>
    </div>
    <div id="sliderdiv" class="slidecontainer">

      <div class="divider">
      </div>
      <div class="divider">
      </div>

      <label for="io"> Light Level:</label>
      <input id="iodisplay" type="text" v-model="postBody.io" >
      <div class="divider">
      </div>
       <div class="divider">
      </div>
      0<input id="io"type="range" min="0" max="2060" v-model="postBody.io" class="timeStepSlider">2060


      <div class="divider">
      </div>
      <div class="divider">
      </div>

      <label for="t">Total Time: (year)</label><br>
      <input id="t" type="text" v-model="postBody.t" placeholder="Time in Years" class="time" min="0" max="100">


    </div>

    <div class="divider">
      </div>

    <div id="error-message"><br>
         {{this.errorMessage}}
    </div>

    <div class="divider">
      </div>

    <button id="postDataBtn" :disabled='isDisabled()' @click="postData()" name="button">PostData</button>
    <button @click="getData()" name="button">GetData</button>
    <button @click="run()">RUN</Button><br>
      <br>
    </div>

    <div class="outputDisplayContainer">
      <button @click="loadTextures()">Load Textures</Button>
      <div class="setSceneContainer">
        <button @click="setScene('ringScene')" class="ringSceneButton" id="ringSceneButton">RINGS</button>
        <button @click="setScene('treeScene')" class="treeSceneButton" id="treeSceneButton">TREE</button>
        <button @click="setScene('rawDataScene')" class="rawDataSceneButton" id="rawDataSceneButton">DATA</button>
      </div>
      <div class="crownShapeContainer">
        <button @click="setCrownShape('cone')" class="coneButton" id="coneButton">CONE</button>
        <button @click="setCrownShape('cylinder')" class="cylinderButton" id="cylinderButton">CYLINDER</button>
        <!--<button @click="setCrownShape('sphere')" class="sphereButton" id="sphereButton">SPHERE</button> Hidden for demo-->
      </div>

      <div class="divider">
      </div>

      <h3> Move the slider to see the growth of the tree!</h3>

      <input type="range" min="1" v-model="dataIndex" @input="draw()" id="timeStepSlider" class="timeStepSlider"><br><br>
      <div class="treeCanvasport" id="treeCanvasport"></div>
      <div class="rawDataList" id="rawDataList">
        <br>
        <button @click="downloadRawData()" class="dlRawDataButton" id="dlRawDataButton">Download to CSV</button><br><br>
        <label>Year: {{ this.dataIndex }}               </label><br>
        <label>APARout: {{ this.resultJson.APARout[this.dataIndex] }}               </label><br>
        <label>h: {{ this.resultJson.h[this.dataIndex] }}               </label><br>
        <label>hh2: {{ this.resultJson.hh2[this.dataIndex] }}               </label><br>
        <label>hC2: {{ this.resultJson.hC2[this.dataIndex] }}               </label><br>
        <label>hB2: {{ this.resultJson.hB2[this.dataIndex] }}               </label><br>
        <label>hBH2: {{ this.resultJson.hBH2[this.dataIndex] }}               </label><br>
        <label>r: {{ this.resultJson.r[this.dataIndex] }}               </label><br>
        <label>rB2: {{ this.resultJson.rB2[this.dataIndex] }}               </label><br>
        <label>rC2: {{ this.resultJson.rC2[this.dataIndex] }}               </label><br>
        <label>rBH: {{ this.resultJson.rBH[this.dataIndex] }}               </label><br>
        <label>sw2: {{ this.resultJson.sw2[this.dataIndex] }}               </label><br>
        <label>vts2: {{ this.resultJson.vts2[this.dataIndex] }}               </label><br>
        <label>vt2: {{ this.resultJson.vt2[this.dataIndex] }}               </label><br>
        <label>vth2: {{ this.resultJson.vth2[this.dataIndex] }}               </label><br>
        <label>sa2: {{ this.resultJson.sa2[this.dataIndex] }}               </label><br>
        <label>la2: {{ this.resultJson.la2[this.dataIndex] }}               </label><br>
        <label>ra2: {{ this.resultJson.ra2[this.dataIndex] }}               </label><br>
        <label>dr2: {{ this.resultJson.dr2[this.dataIndex] }}               </label><br>
        <label>xa2: {{ this.resultJson.xa2[this.dataIndex] }}               </label><br>
        <label>bl2: {{ this.resultJson.bl2[this.dataIndex] }}               </label><br>
        <label>br2: {{ this.resultJson.br2[this.dataIndex] }}               </label><br>
        <label>bt2: {{ this.resultJson.bt2[this.dataIndex] }}               </label><br>
        <label>bts2: {{ this.resultJson.bts2[this.dataIndex] }}               </label><br>
        <label>bth2: {{ this.resultJson.bth2[this.dataIndex] }}               </label><br>
        <label>boh2: {{ this.resultJson.boh2[this.dataIndex] }}               </label><br>
        <label>bos2: {{ this.resultJson.bos2[this.dataIndex] }}               </label><br>
        <label>bo2: {{ this.resultJson.bo2[this.dataIndex] }}               </label><br>
        <label>bs2: {{ this.resultJson.bs2[this.dataIndex] }}               </label><br>
        <!--<label>cs2: {{ this.resultJson.cs2[this.dataIndex] }}               </label><br>-->
        <label>clr2: {{ this.resultJson.clr2[this.dataIndex] }}               </label><br>
        <label>fl2: {{ this.resultJson.fl2[this.dataIndex] }}               </label><br>
        <label>fr2: {{ this.resultJson.fr2[this.dataIndex] }}               </label><br>
        <label>ft2: {{ this.resultJson.ft2[this.dataIndex] }}               </label><br>
        <label>fo2: {{ this.resultJson.fo2[this.dataIndex] }}               </label><br>
        <label>rfl2: {{ this.resultJson.rfl2[this.dataIndex] }}               </label><br>
        <label>rfr2: {{ this.resultJson.rfr2[this.dataIndex] }}               </label><br>
        <label>rfs2: {{ this.resultJson.rfs2[this.dataIndex] }}               </label><br>
        <label>egrow2: {{ this.resultJson.egrow2[this.dataIndex] }}               </label><br>
        <label>ex2: {{ this.resultJson.ex2[this.dataIndex] }}               </label><br>
        <label>rtrans2: {{ this.resultJson.rtrans2[this.dataIndex] }}               </label><br>
        <label>light2: {{ this.resultJson.light2[this.dataIndex] }}               </label><br>
        <label>nut2: {{ this.resultJson.nut2[this.dataIndex] }}               </label><br>
        <label>deltas2: {{ this.resultJson.deltas2[this.dataIndex] }}               </label><br>
        <label>LAI2: {{ this.resultJson.LAI2[this.dataIndex] }}               </label><br>
        <label>status2: {{ this.resultJson.status2[this.dataIndex] }}               </label><br>
        <!--<label>errorind: {{ this.resultJson.errorind[this.dataIndex] }}               </label><br>-->
        <!--<label>growth_st: {{ this.resultJson.growth_st[this.dataIndex] }}               </label><br>-->
      </div>
    </div>

</div>
</template>

<script>
import axios from 'axios'
import * as THREE from 'three'
import json from '../json/treeData.json'

export default {
  name: 'inputs-vis',
  data() {
    return {
    postBody: {
          hmax: '',
          phih: '',
          eta: '',
          swmax: '',
          lamda: '',
          rhomax: '',
          f2: '',
          f1: '',
          gammac: '',
          gammaw: '',
          gammax: '',
          cgl: '',
          cgr: '',
          cgw: '',
          deltal: '',
          deltar: '',
          sl: '',
          sla: '',
          so: '',
          sr: '',
          rr: '',
          rhor: '',
          rml: '',
          rms: '',
          rmr: '',
          etaB: '',
          k: '',
          epsg: '',
          m: '',
          alpha: '',
          r0: '',
          r40: '',
          t: '',
          radius: '',
          io: ''
        },
        runID: '',
        getJson: [],
        resultJson: {
            "APARout":'',
            "h":'',
            "hh2":'',
            "hC2":'',
            "hB2":'',
            "hBH2":'',
            "r":'',
            "rB2":'',
            "rC2":'',
            "rBH":'',
            "sw2":'',
            "vts2":'',
            "vt2":'',
            "vth2":'',
            "sa2":'',
            "la2":'',
            "ra2":'',
            "dr2":'',
            "xa2":'',
            "bl2":'',
            "br2":'',
            "bt2":'',
            "bts2":'',
            "bth2":'',
            "boh2":'',
            "bos2":'',
            "bo2":'',
            "bs2":'',
            "cs2":'',
            "clr2":'',
            "fl2":'',
            "fr2":'',
            "ft2":'',
            "fo2":'',
            "rfl2":'',
            "rfr2":'',
            "rfs2":'',
            "egrow2":'',
            "ex2":'',
            "rtrans2":'',
            "light2":'',
            "nut2":'',
            "deltas2":'',
            "LAI2":'',
            "status2":'',
            "errorind":'',
            //"growth_st":''
        },

        dataIndex: "1",
        timeStep: "16",
        treeData: json.trees,
        crownShape: "cone",
        currentScene: this.treeScene,
        currentCam: this.treeCam,
        barkTexture: "",

        isDisable: false,
        etaBDisable:true,
        errorMessage:"",
        tempc: 0
      }
    }, // END: data()

methods: {

    run() {
      // postData
      // done posting
      // loop getData until result json is retrieved
      // done getting
    }, // END: run()

    postData() {
      console.log("posting")
      axios.post('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        headers: {
          'Content-Type': 'application/json',
          'x-api-key': 'AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
          'Access-Control-Allow-Origin': '*'
        },
        body: this.postBody
      })
      .then(response => {
        this.runID = response.headers['x-run-id'],
        console.log("from post -- runID: ", this.runID)
      })
      console.log("posted")
    }, // END: postData()

    getData() {
      console.log("getData")
      axios.get('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        headers: {
          'Content-Type': 'application/json',
          'x-run-id': this.runID
        }
      })
      .then((response) => {

        console.log(this.runID)
        this.getJson = response.data

        if (this.getJson == undefined)
        {
          return;
        }
        var parsedobj = JSON.parse(JSON.stringify(this.resultJson))

        let newStr = this.getJson.replace(/=/g, "\":")
        let newStr2 = newStr.replace(/&/g, ",\"")
        let newStr3 = newStr2.split(",")
        let VarName = ""
        let Values = []
        let Result = {}
        for(let iter = 0; iter < newStr3.length; iter++)
        {
          let item = newStr3[iter]
          let index_array = item.split(":")
          let varName = index_array[0].substring(1, index_array[0].length-1)
          let value = parseFloat(index_array[1])
          if (varName != VarName)
          {
            Result[VarName] = Values
            Values = []
            VarName = varName
          }
          Values.push(value)
        }

        this.resultJson = Result
        // let newStr3 = "{\"" + newStr2 + "}"
        // this.resultJson = JSON.parse(newStr3)
        console.log("ResultJson: \n", this.resultJson)

      },
          (error) => { console.log(error.request)}
      )
      console.log("data retrieved")
    }, // END: getData()

    setDefault(defaultType) {

      // Set default time, light level, and initial radius
      this.postBody.t=29
      this.postBody.radius=0.05
      this.postBody.io=1000

      // Sets default values in the input fields based on the button that user clicks
      if(defaultType == "Red Maple") // Red Maple button
      {
        this.postBody.hmax=27.5;
        this.postBody.phih=263;
        this.postBody.eta=0.64;
        this.postBody.swmax=0.1;
        this.postBody.lamda=0.95;
        this.postBody.rhomax=525000;
        this.postBody.f2=7000;
        this.postBody.f1=4;
        this.postBody.gammac=131000;
        this.postBody.gammaw=6.67e-7;
        this.postBody.gammax=0.12;
        this.postBody.cgl=1.45;
        this.postBody.cgr=1.25
        this.postBody.cgw=1.37
        this.postBody.deltal=0.095
        this.postBody.deltar=0.15
        this.postBody.sl=1
        this.postBody.sla=0.0141
        this.postBody.sr=1
        this.postBody.so=0.05
        this.postBody.rr=0.00015
        this.postBody.rhor=160000
        this.postBody.rml=1.25
        this.postBody.rms=0.025
        this.postBody.rmr=0.75
        this.postBody.etaB=0.045
        this.postBody.k=0.7
        this.postBody.epsg=6.75
        this.postBody.m=0.95
        this.postBody.alpha=0.365
        this.postBody.r0=1.909
        this.postBody.r40=5.592
      } // END: if Red Maple

      else if(defaultType == "Loblolly Pine")  // Loblolly Pine button
      {
        this.postBody.hmax=42
        this.postBody.phih=220
        this.postBody.eta=0.71
        this.postBody.swmax=0.06
        this.postBody.lamda=0.95
        this.postBody.rhomax=380000
        this.postBody.f2=2100
        this.postBody.f1=4
        this.postBody.gammac=265000
        this.postBody.gammaw=6.67e-7
        this.postBody.gammax=0.62
        this.postBody.cgl=1.51
        this.postBody.cgr=1.3
        this.postBody.cgw=1.47
        this.postBody.deltal=0.11
        this.postBody.deltar=0.08
        this.postBody.sl=0.33
        this.postBody.sla=0.00602
        this.postBody.sr=0.5
        this.postBody.so=0.05
        this.postBody.rr=0.00027
        this.postBody.rhor=200000
        this.postBody.rml=1.9
        this.postBody.rms=0.05
        this.postBody.rmr=1.5
        this.postBody.etaB=0.045
        this.postBody.k=0.55
        this.postBody.epsg=4.5
        this.postBody.m=0.95
        this.postBody.alpha=0.308
        this.postBody.r0=1.434
        this.postBody.r40=3.873
      } // END: if Loblolly Pine
    }, // END: set_default()

    initialize() {
      // Change the slider to have as many steps as timeSteps from the ACGCA model.
      document.getElementById("timeStepSlider").setAttribute("max", 10)

      /////////////// Tree Scene ///////////////
      this.treeCanvas = document.getElementById( "treeCanvasport" )
      this.outputDisplayContainer = document.getElementById("outputDisplayContainer")

      console.log("window:",window.innerWidth,window.innerHeight)
      console.log("this.treeCanvas:",this.treeCanvas.innerWidth,this.treeCanvas.innerHeight)
      //console.log("outputCanvas:", this.outputDisplayContainer.innerWidth  , this.outputDisplayContainer.innerHeight  )
      var canvasWidth = window.innerWidth * 0.7
      var canvasHeight = window.innerHeight * 0.7

      ///// Tree Scene /////
      // Create scene for trees
      this.treeScene = new THREE.Scene()
      this.treeScene.background = new THREE.Color( 0xcfffff );
      // Create camera for tree scene
      // PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )
      this.treeCam = new THREE.PerspectiveCamera( 90, canvasWidth / canvasHeight, 0.1, 1000 )
      this.treeCam.position.z = 7
      this.treeScene.add( this.treeCam )
      ///// Tree Scene /////

      ///// Ring Scene /////
      // Create scene for rings
      this.ringScene = new THREE.Scene()
      this.ringScene.background = new THREE.Color( 0xdfffcf  );
      // Create camera for ring scene
      // PerspectiveCamera( fov : Number, aspect : Number, near : Number, far : Number )
      this.ringCam = new THREE.PerspectiveCamera( 90, canvasWidth / canvasHeight, 0.1, 1000 )
      this.ringCam.position.z = 7
      this.ringScene.add( this.ringCam )
      ///// Ring Scene /////

      // Create renderer
      this.treeRenderer = new THREE.WebGLRenderer( {antialias: true} )
      this.treeRenderer.setSize( canvasWidth, canvasHeight )
      this.treeCanvas.appendChild( this.treeRenderer.domElement )

      // Create stand-in tree, but don't add it to the scene.
      this.trunk = new THREE.Mesh( new THREE.CylinderGeometry( 1, 1, 1, 1 ), new THREE.MeshBasicMaterial( {color: 0xb5651d} ) )
      this.crown = new THREE.Mesh( new THREE.CylinderGeometry( 1, 1, 1, 1 ), new THREE.MeshBasicMaterial( {color: 0xb5651d} ) )

      // Choose default scene
      this.currentScene = this.treeScene
      this.currentCam = this.treeCam

      // Attempt at making a ground plane.
      // PlaneGeometry(width : Float, height : Float, widthSegments : Integer, heightSegments : Integer)
      /*var groundGEO = new THREE.PlaneGeometry(3, 3, 1)
      var groundMat = new THREE.MeshBasicMaterial( {color: 0x00FF00} )
      var ground = new THREE.Mesh( groundGEO, groundMat )
      this.currentScene.add(ground)
      ground.position.z = 2
      ground.rotation.x = 89
      ground.rotation.y = 0*/

      // Show the tree view as default and hide the raw data view.
      document.getElementById("treeCanvasport").style.display = "block"
      document.getElementById("rawDataList").style.display = "none"

      window.addEventListener( 'resize', this.onWindowResize, false )
    }, // END: initialize()

    loadTextures() {
      //this.barkTexture = new THREE.TextureLoader().load( '../assets/bark.png' )
      console.log("starting texture load")

      var myMaterial2
      // instantiate a loader
      var loader = new THREE.TextureLoader()
      loader.crossOrigin = ""

      // load a resource
      loader.load(
        // resource URL
        //'../assets/bark.png',
        'https://i.imgur.com/XxwCL1S.jpg',

        // onLoad callback
        function ( texture ) {
          // in this example we create the material when the texture is loaded
          myMaterial2 = new THREE.MeshBasicMaterial( {
            map: texture
          } )
          console.log("texture loaded")
        },

        // onProgress callback currently not supported
        undefined,

        // onError callback
        function ( err ) {
          console.error( 'An error happened.' )
        }
      )

      console.log("creating box")
      var boxGeometry2 = new THREE.BoxGeometry( 1, 1, 1 );
      var box2 = new THREE.Mesh( boxGeometry2, myMaterial2 )
      box2.position.x = -5
      box2.position.y = -2.5
      this.treeScene.add( box2 )

    }, // END: loadTextures()

    addBox() {
      //var myTexture = new THREE.TextureLoader().load( '../json/bark.png' )
      var r = this.resultJson.r[this.dataIndex]      // Radius of trunk at base
      r = r * 7 // Temporary use to negate weird data

      var myMaterial = new THREE.MeshLambertMaterial( { map: this.barkTexture } )
      //var myMaterial = new THREE.MeshLambertMaterial( { color: 0xFFFF00 } )

      var boxGeometry = new THREE.BoxGeometry( 1, 1, 1 );
      var box = new THREE.Mesh( boxGeometry, myMaterial )
      box.position.x = r + 2
      this.treeScene.add( box )
    }, // END: addBox()

    draw(scene) {
      document.getElementById("timeStepSlider").setAttribute("max", this.postBody.t) // Should be moved to end of getData().
      if(this.currentScene == this.treeScene)
      {
        this.drawTree()
      }
      else if(this.currentScene == this.ringScene)
      {
        this.drawRings()
      }
    }, // END: draw()

    drawTree() {
      // Find max height of tree over its life to scale the scene to.
      var maxHeight = 0
      for( var i = 1; i < this.postBody.t; i++ )
      {
        if( maxHeight < this.resultJson.h[i*this.timeStep] )
        {
          maxHeight = this.resultJson.h[i*this.timeStep]
        }
      }

      // Clear scene of old drawings
      while(this.treeScene.children.length > 0){                  // Clear scene of old tree
        this.treeScene.remove(this.treeScene.children[0])
      }
      this.newScene = new THREE.Scene()                           // Create new scene for new tree
      this.treeScene.add( this.newScene )                         // Add new scene to root scene

      this.addBox()
      this.addLight()

      var year = this.dataIndex
      var timestep = year * 16 - 1

      /// Trunk variables
      var h = this.resultJson.h[timestep]      // Total tree height
      var hB = this.resultJson.hB2[timestep]   // Height that trunk transitions from neiloid to paraboloid (base to trunk)
      hB = this.postBody.etaB * h
      var hC = this.resultJson.hC2[timestep]   // Height that trunk transitions from paraboloid to cone (trunk to crown)
      hC = this.postBody.eta * h
      var r = this.resultJson.r[timestep]      // Radius of trunk at base
      //r = r * 7 // Temporary use to negate weird data
      var rB = this.resultJson.rB2[timestep]   // Radius of trunk when transitioning from neilooid to paraboloid (base to trunk)
      var rC = this.resultJson.rC2[timestep]   // Radius of trunk when transitioning from parapoloid to cone (trunk to crown)
      //rC = rC * 7 // Temporary use to negate weird data

      /// Crown variables (overlaid on "cone" part of trunk)
      var hmax = this.postBody.hmax                 // Input.
      var phih = this.postBody.phih                 // Input.
      var eta = this.postBody.eta                   // Input.
      var m = this.postBody.m                       // Input.
      var alpha = this.postBody.alpha               // Input.
      var r0 = this.postBody.r0                     // Input.
      var r40 = this.postBody.r40                   // Input.
      var rBH = this.resultJson.rBH[timestep]           // Output.
      // var h = this.treeData[timestep].h              // Output. Delcared above
      const BH = 1.37                               // Breast height. Contsant 1.37 meters

      // if h > BH --> rcmax = r0 + ((r40 - r0) * (2 * rBH * 100) / 40)
      // if h < BH --> rcmax = (r0 * r) / ((hmax / phih) * ln(hmax/(hmax - BH)))
      var rcmax // Maximum potential radius at a crown ratio of m
      if( h > BH )
      {
        rcmax = r0 + ((r40 - r0) * (2 * rBH * 100) / 40)
      }
      else if( h < BH )
      {
        rcmax = (r0 * r) / ((hmax / phih) * ln(hmax/(hmax - BH)))
      }

      var eta = this.postBody.eta     // Input.
      var alpha = this.postBody.alpha // Input. Curvature of the crown.

      // if m > (1 - eta) --> rcbase = rcmax * ((1 - eta) / m)^alpha
      // otherwise --> rcbase = 1 - eta
      var rcbase // Radius at the base of the crown.
      if( m > (1 - eta))
      {
        rcbase = rcmax * Math.pow(((1 - eta) / m), alpha)
      }
      else
      {
        rcbase = rcmax
      }

      console.log("year:",year,"timestep:",timestep,"\nh:",h,"\nhC:",hC,"\nhB:",hB,"\nr:",r,"\nrB:",rB,"\nrC:",rC,
      "\nrBH:",rBH,"\nrcmax:",rcmax,"\nrcbase:",rcbase)

      // Supplemental parameters
      var geoSegments = 20                  // Segments of geometry
      var trunkPos = hC/2             // Trunk position on the screen. Needs to be based on max height.
      var crownPos = h - (h - hC)/2   // Crown position on the screen. Bottom of crown needs to be on the same x plan as top of trunk.

      ///// Trunk /////
      // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
      var trunkGeo = new THREE.CylinderGeometry( rC, r, hC, geoSegments )
      var trunkMat = new THREE.MeshLambertMaterial( {color: 0xb5651d} )
      this.trunk = new THREE.Mesh( trunkGeo, trunkMat )
      this.trunk.position.y = trunkPos
      this.trunk.position.x = 0
      ///// Trunk /////

      ///// Crown /////
      var crownGeo
      if( this.crownShape == "cone" )
      {
        // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.ConeGeometry( rcbase, h-hC, geoSegments )
      }
      else if( this.crownShape == "sphere") // Currently doesn't work very well. Needs tuning.
      {
        // SphereGeometry(radius : Float, widthSegments : Integer, heightSegments : Integer)
        crownGeo = new THREE.SphereGeometry( rcbase, geoSegments*1.5, geoSegments*1.5 )
      }
      else if( this.crownShape == "cylinder" )
      {
        // CylinderGeometry(radiusTop : Float, radiusBottom : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.CylinderGeometry( rcbase, rcbase, h-hC, geoSegments );
      }
      else // Default to cone shaped crown
      {
        // ConeGeometry(radius : Float, height : Float, radialSegments : Integer)
        crownGeo = new THREE.ConeGeometry( rcbase, h-hC, geoSegments )
      }
      var crownColor = new THREE.Color()
      crownColor.setRGB(0, this.resultJson.LAI2[year] * 0.1, 0)
      var crownMat = new THREE.MeshLambertMaterial( {color: crownColor} )
      console.log("crown color:",crownColor)
      //var crownMat = new THREE.MeshLambertMaterial( {color: 0x00FF00} )
      this.crown = new THREE.Mesh( crownGeo, crownMat )
      this.crown.position.y = crownPos
      this.crown.position.x = 0
      ///// Crown /////

      // Resize camera based on max tree height
      this.currentCam.position.y = maxHeight / 2
      this.currentCam.position.z = maxHeight
      this.currentCam.lookAt(0, maxHeight/2, 0)
      // Add trunk and crown to scene
      this.newScene.add( this.crown )
      this.newScene.add( this.trunk )
    }, // END: drawTree()

    drawRings() {
      var geoSegments = 16

      // Clear scene of previous drawings
      while(this.ringScene.children.length > 0){                  // Clear scene of old tree
        this.ringScene.remove(this.ringScene.children[0])
      }
      this.newScene = new THREE.Scene()                           // Create new scene for new tree
      this.ringScene.add( this.newScene )                         // Add new scene to root scene

      // Find max radius and scale scene to that size
      var maxRadius = this.resultJson.r[this.postBody.t]
      this.ringCam.position.z = maxRadius*2
      this.ringCam.lookAt(0, 0, 0)

      var heartwoodRadius = this.resultJson.r[this.dataIndex] - this.resultJson.sw2[this.dataIndex] // Gets the heart wood radius at the current year on the slider
      console.log("sw:", this.resultJson.sw2[this.dataIndex], "\nr:", this.resultJson.r[this.dataIndex], "\nhw:", heartwoodRadius)

      for( var i = 1; i <= this.dataIndex; i++ )
      {
        // RingGeometry(innerRadius : Float, outerRadius : Float, thetaSegments : Integer, phiSegments : Integer, thetaStart : Float, thetaLength : Float)
        var ringGeo = new THREE.RingGeometry( this.resultJson.r[i-1], this.resultJson.r[i], 32 )

        // color
        var ringColor = new THREE.Color()
        if( this.resultJson.r[i] < heartwoodRadius ) // If the current ring is part of the heart wood..
        {
          // Alternate between lighter colors
          if(i % 2 == 0) { ringColor = 0x925A40 }
          else { ringColor = 0x642C11 }
        }
        else                                        // If the current ring is part of the sap wood..
        {
          // Alternate between darker colors
          if(i % 2 == 0) { ringColor = 0x7E572D }
          else { ringColor = 0x43280B }
        }

        var ringMat = new THREE.MeshBasicMaterial( {color: ringColor} )
        var ring = new THREE.Mesh( ringGeo, ringMat )
        this.newScene.add( ring )
      }
    }, // END: drawRings()

    addLight() {
      // Ambient light for all objects.
      var light = new THREE.AmbientLight( 0x404040 )
      this.treeScene.add( light )

      // Point light for casting shadows.
      var pointLight = new THREE.PointLight( 0xffffff, 1, 100 )
      pointLight.position.set( 10, 10, 10 )
      this.treeScene.add( pointLight )
    }, // END: addLight

    setCrownShape(shape) {
      this.crownShape = shape
      console.log("crownShape:", shape)
      this.drawTree()
    }, // END: setCrownShape()

    setScene(scene) {
      if(scene == "treeScene") {
        document.getElementById("treeCanvasport").style.display = "block"
        document.getElementById("rawDataList").style.display = "none"

        document.getElementById("coneButton").style.display = "inline-block"
        //document.getElementById("sphereButton").style.display = "inline-block"
        document.getElementById("cylinderButton").style.display = "inline-block"

        this.currentScene = this.treeScene
        this.currentCam = this.treeCam
        this.drawTree()
      }
      else if(scene == "ringScene") {
        document.getElementById("treeCanvasport").style.display = "block"
        document.getElementById("rawDataList").style.display = "none"

        document.getElementById("coneButton").style.display = "none"
        //document.getElementById("sphereButton").style.display = "none"
        document.getElementById("cylinderButton").style.display = "none"

        this.currentScene = this.ringScene
        this.currentCam = this.ringCam
        this.drawRings()
      }
      else if(scene == "rawDataScene") {
        document.getElementById("treeCanvasport").style.display = "none"
        document.getElementById("rawDataList").style.display = "block"

        document.getElementById("coneButton").style.display = "none"
        //document.getElementById("sphereButton").style.display = "none"
        document.getElementById("cylinderButton").style.display = "none"
      }
    }, // END: setScene()

    update() {
      // THREE.js function
      //this.trunk.rotation.y += 0.01
      //this.crown.rotation.y += 0.01
    }, // END: update()

    onWindowResize() {
      // Adjusts the renderer size when the window is resized.
			this.currentCam.aspect = window.innerWidth / window.innerHeight
			this.currentCam.updateProjectionMatrix()

			this.treeRenderer.setSize( window.innerWidth * 0.7, window.innerHeight * 0.7)
    }, // END: onWindowResize()

    animate() {
      // THREE.js function
      requestAnimationFrame(this.animate)
      this.update()
      this.treeRenderer.render(this.currentScene, this.currentCam)
    }, // END: animate()

    checkForNull(){
      var temporaryIsDisable=false


      //start checking null
      temporaryIsDisable=temporaryIsDisable || (this.postBody.hmax==="");
      temporaryIsDisable=temporaryIsDisable || (this.postBody.phih==="");
      temporaryIsDisable=temporaryIsDisable || (this.postBody.eta==="");
      temporaryIsDisable=temporaryIsDisable || (this.postBody.swmax==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.lamda==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rhomax==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.f2==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.f1==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammac==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammaw==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.gammax==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.cgl==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.cgr==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.cgw==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.deltal==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.deltar==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.sl==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.sla==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.so==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.sr==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rr==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rhor==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rml==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rms==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.rmr==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.etaB==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.k==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.epsg==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.m==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.alpha==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.r0==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.r40==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.radius==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.io==="") ;
      temporaryIsDisable=temporaryIsDisable || (this.postBody.t==="") ;
      this.isDisable=temporaryIsDisable;

      if(this.isDisable){
         this.errorMessage="ERROR: Please fill out all of the fields";
      }
      else{
        this.errorMessage=""
      }

    }, // END: checkForNull()
    
    hardLimit(){
      if (this.postBody.phih < 0) this.postBody.phih= 0;

      if (this.postBody.eta < 0) this.postBody.eta = 0;
      if (this.postBody.eta > 1) this.postBody.eta= 1;

      if (this.postBody.lamda < 0) this.postBody.lamda = 0;
      if (this.postBody.lamda > 1) this.postBody.lamda= 1;

      if (this.postBody.f2 < 0) this.postBody.f2 = 0;

      if (this.postBody.f1 < 0) this.postBody.f1 = 0;

      if (this.postBody.gammax < 0) this.postBody.gammax = 0;
      if (this.postBody.gammax > 1) this.postBody.gammax= 1;

      if (this.postBody.etaB < 0) this.postBody.etaB = 0;
      if(this.postBody.eta!=""){
      if (this.postBody.etaB > eta) this.postBody.etaB= eta;
      }

      if (this.postBody.m < 0) this.postBody.m = 0;
      if (this.postBody.m > 1) this.postBody.m= 1;

      if (this.postBody.alpha < 0) this.postBody.alpha = 0;

      if (this.postBody.r0 < 0) this.postBody.r0 = 0;

      if(this.postBody.r0!=""){
      if (this.postBody.r40 < r0) this.postBody.r40 = r0;
      }

      //Group A end 

      if (this.postBody.hmax < 0) this.postBody.hmax= 0;
      if (this.postBody.hmax> 127) this.postBody.hmax= 127;

      if (this.postBody.swmax < 0) this.postBody.swmax= 0;

      if (this.postBody.rr < 0) this.postBody.rr= 0;

      //Group B end

      if (this.postBody.rhomax < 0) this.postBody.rhomax= 0;

      if (this.postBody.gammaw < 0) this.postBody.gammaw= 0;

      if (this.postBody.sla < 0) this.postBody.sla= 0;

      //Group C end

      if (this.postBody.gammac < 0) this.postBody.gammac= 0;

      if (this.postBody.cgl < 0) this.postBody.cgl= 0;

      if (this.postBody.cgr < 0) this.postBody.cgr= 0;

      if (this.postBody.cgw < 0) this.postBody.cgw= 0;

      if (this.postBody.deltal < 0) this.postBody.deltal= 0;

      if (this.postBody.deltar < 0) this.postBody.deltar= 0;

      if (this.postBody.rhor < 0) this.postBody.rhor= 0;

      if (this.postBody.rml < 0) this.postBody.rml= 0;

      if (this.postBody.rms < 0) this.postBody.rms= 0;

      if (this.postBody.rmr < 0) this.postBody.rmr= 0;

      if (this.postBody.k < 0) this.postBody.k= 0;

      if (this.postBody.epsg < 0) this.postBody.epsg= 0;
      if (this.postBody.epsg> 15.73) this.postBody.epsg= 15.73;

      //Group D end

      if (this.postBody.sl < 0) this.postBody.sl= 0;

      if (this.postBody.sr < 0) this.postBody.sr= 0;

      if (this.postBody.so < 0) this.postBody.so= 0;

      if (this.postBody.radius < 0) this.postBody.gammac= 0;

      if (this.postBody.io < 0) this.postBody.io = 0;
      if (this.postBody.io > 2060) this.postBody.io= 2060;

      if (this.postBody.t < 0) this.postBody.cgr= 0;

      //Group E end


    }, // END: hardLimit()

    isDisabled() {
      this.checkForNull();
      this.hardLimit();
      return this.isDisable;
    }, // END: isDisabled()

    downloadRawData() {
      // Downloads the raw data output from resultJson to a .csv file


    }, // END: downloadRawData()

  }, // END: Methods

  mounted() {
    this.initialize()
    this.animate()
  } // END: mounted
} // END: export default
</script>

<style lang="css" scoped>

  input[type=text] {
    border-radius:5px;
  }

  input[type=text]::-webkit-input-placeholder {
    font-family: "Lucida Console", Monaco, monospace;
  }

  input[type=text]:-ms-input-placeholder {
    font-family: "Lucida Console", Monaco, monospace;
  }

  input[type=text]:-moz-placeholder {
    font-family: "Lucida Console", Monaco, monospace;
  }

  input[type=text]::-moz-placeholder {
    font-family: "Lucida Console", Monaco, monospace;
  }

  #iodisplay{
      border: none;
      background: transparent;
      border-bottom: 1px solid #fff;
      outline: none;
      width:40%;
  }

  #io{
    width:80%;
  }

  #io::-webkit-slider-thumb {
    background: url('../assets/Logo-Black.png');
    width:36px;
    height:36px;
  }

  #io::-moz-range-thumb{
    background: url('../assets/Logo-Black.png');
    width:36px;
    height:36px;
  }

  #sliderdiv{
    text-align:left;
  }

  .slidecontainer {
    width: 100%;

  }

  .slider {
    -webkit-appearance: none;
    appearance: none;
    width: 100%;
    height: 25px;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
  }
  /*title wrapper*/

  .title-wrapper {
    text-align: center;
    display:inline-block;
    font-size: 30px;
    width:98%;
    border-radius: 20px;
    background-color: #4CAF50;
    font-family: "Lucida Console", Monaco, monospace;
    padding:5px;
  }

  #input-title {
    font-size: 25px;
    width:80%;
    float:left;
    background-color: #b9b9b9;
    height:30px;
  }

  #mention p {
     width:200px;
  }

  #mention-text{
    font-size: 20px;
    font-weight: bold;
    color:coral
  }

  .divider {
    height:10px;
  }

  .groupDivider {
    height:120px;
  }

  .inputField {
    display: inline-block;
    padding: 20px 10px 20px 10px;
    margin: 2px;
    border: none;
    border-radius: 10px;
    font-size: 16px;
    color:black;
    font-family: "Lucida Console", Monaco, monospace;
    width:17%;
    background-color: #b9b9b9;
  }

    .inputField button {
    display: inline-block;
    width: 100px;
    height: 50px;
    padding: 5px 5px;
    margin: 2px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 16px;
    color: black;
    font-family: "Lucida Console", Monaco, monospace;
    background-color:green;
  }

  .inputField button:hover {
    background-color: #EEE;
  }

  .inputField button:disabled {
    background-color: red;
    cursor: auto;
  }

  #error-message{
    color: red;
  }

  .outputDisplayContainer {
    width: 77%;
    height: 80%;
    margin: auto;
    padding: 2%;
    float: right;
    background-color: #b9b9b9;
    border-color: green;
    border-radius: 10px;
    float: right;
    position: relative;
  }

  .outputDisplayContainer button {
    display: inline-block;
    width: 100px;
    height: 50px;
    padding: 5px 5px;
    margin: 2px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 16px;
    color: green;
    font-family: "Lucida Console", Monaco, monospace;
    background-color: #FFF;
  }

  .outputDisplayContainer button:hover {
    background-color: #EEE;
  }

  .rawDataList {
    width: 100%;
    text-align: center;
  }

  .timeStepSlider {
    -webkit-appearance: none;
    width: 100%;
    height: 15px;
    border-radius: 5px;
    background: #d3d3d3;
    outline: none;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
  }

  #timeStepSlider::-webkit-slider-thumb {
    background: url('../assets/Logo-Black.png');
    width:45px;
    height:45px;
  }

    #timeStepSlider::-moz-range-thumb{
    background: url('../assets/Logo-Black.png');
    width:45px;
    height:45px;
  }

  .timeStepSlider:hover {
    opacity: 1;
  }

  .timeStepSlider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
    border-radius: 50%;
  }

  .timeStepSlider::-moz-range-thumb {
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
    border-radius: 50%;
  }

  .menu-content {
    max-height: 0;
    overflow: hidden;
    font-family: "Lucida Console", Monaco, monospace;
    padding: 0 5px 5px 5px;
    text-align: left;
  }

  /* Toggle Effect */

  input:checked ~ .menu-content {
    max-height: 100%;
  }

  .collapsible-menu {
    background-color: rgb(255, 255, 255);
    padding: 0px 0px;
    border-bottom: 3px solid #CDE700;
    box-shadow: 1px 2px 3px rgba(0,0,0,0.2);
    border-radius: 20px;
  }

  .collapsible-menu ul {
    list-style-type: none;
    padding: 0;
  }

  .collapsible-menu a {
      display:block;
      padding: 10px;
      text-decoration: none;
  }

  .collapsible-menu label {
    font-family: "Lucida Console", Monaco, monospace;
    font-size: 20px;
    display: inline-block;
    cursor: pointer;
    padding: 10px 0px 5px 0px;

  }

  .collapsible-menu button {
    display: inline-block;
    width: 100px;
    height: 50px;
    padding: 5px 5px;
    margin: 2px;
    border: 2px solid green;
    border-radius: 15px;
    cursor: pointer;
    font-size: 16px;
    color: black;
    font-family: "Lucida Console", Monaco, monospace;
    background-color: #FFF;

  }

  .menu-content label {
    font-size:15px;
  }


  input#menu-0 {
    display: none;
  }

  input#menu {
    display: none;
  }

  input#menu0 {
    display: none;
  }



  /* Toggle Effect */

  input#menu-1 {
    display: none;
  }

  input#menu-2 {
    display: none;
  }

  input#menu-3 {
    display: none;
  }

  input#menu-4 {
    display: none;
  }

  .buttons {
    float: left;
  }

  /*help tip*/
  .help-tip{
    position: relative;
    display: inline-block;
    text-align: center;
    background-color: #BCDBEA;
    border-radius: 50%;
    width: 24px;
    height: 24px;
    font-size: 14px;
    line-height: 26px;
    cursor: default;
  }
  .help-tip:before{
    content:'?';
    font-weight: bold;
    color:#fff;
  }
  .help-tip:hover p{
    display: inline;
    transform-origin: 100% 0%;

    -webkit-animation: fadeIn 0.3s ease-in-out;
    animation: fadeIn 0.3s ease-in-out;
  }
  .help-tip p{
    display:none;
    text-align: left;
    background-color: green;
    padding: 20px;
    width: 700%;
    position: absolute;
    border-radius: 3px;
    box-shadow: 1px 1px 1px rgba(0, 0, 0, 0.2);
    right: -4px;
    color: #fff;
    font-size: 13px;
    line-height: 1.4;
    border-radius: 25px;
    z-index:9999;  /*this z index makes the help tip on top of every other things*/
  }
  .help-tip p:before{ /* The pointer of the tooltip */
      position: relative;
      content: '';
      width:0;
      height: 0;
      border:6px solid transparent;
      border-bottom-color:#1E2021;
      right:10px;
      top:-12px;
  }


  .help-tip p:after{ /*Prevents the tooltip from being hidden */
      width:100%;
      height:40px;
      content:'';
      position: relative;
      top:-40px;
      left:0;
  }

  @-webkit-keyframes fadeIn {
      0% {
          opacity:0;
          transform: scale(0.6);
      }

      100% {
          opacity:100%;
          transform: scale(1);
      }
  }

  @keyframes fadeIn {
      0% { opacity:0; }
      100% { opacity:100%; }
  }

  span .separator {
      border-top: 3px solid #333;
      border-radius:1px;
      width: 100%;
      height: 3px;
      display: block;
      border-color: white;
  }

  .help-tip p:after{ /*Prevents the tooltip from being hidden */
      width:100%;
      height:40px;
      content:'';
      position: relative;
      top:-40px;
      left:0;
  }

  @-webkit-keyframes fadeIn {
      0% {
          opacity:0;
          transform: scale(0.6);
      }

      100% {
          opacity:100%;
          transform: scale(1);
      }
  }

  @keyframes fadeIn {
      0% { opacity:0; }
      100% { opacity:100%; }
  }

  span .separator {
      border-top: 3px solid #333;
      border-radius:1px;
      width: 100%;
      height: 3px;
      display: block;
      border-color: white;
  }
  .time {
    width: 100%;
    height: 25px;
  }



</style>
