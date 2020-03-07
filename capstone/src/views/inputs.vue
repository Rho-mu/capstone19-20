<template>
  <div>
    <div class="inputField">
      <form>
        <input type="text" v-model="postBody.hmax" placeholder="hmax"><br>
        <input type="text" v-model="postBody.phih" placeholder="phih"><br>
        <input type="text" v-model="postBody.eta" placeholder="eta"><br>
        <input type="text" v-model="postBody.swmax" placeholder="swmax"><br>
        <input type="text" v-model="postBody.lamda" placeholder="lamda"><br>
        <input type="text" v-model="postBody.rhomax" placeholder="rhomax"><br>
        <input type="text" v-model="postBody.f2" placeholder="f2"><br>
        <input type="text" v-model="postBody.f1" placeholder="f1"><br>
        <input type="text" v-model="postBody.gammac" placeholder="gammac"><br>
        <input type="text" v-model="postBody.gammaw" placeholder="gammaw"><br>
        <input type="text" v-model="postBody.gammax" placeholder="gammax"><br>
        <input type="text" v-model="postBody.cgl" placeholder="cgl"><br>
        <input type="text" v-model="postBody.cgr" placeholder="cgr"><br>
        <input type="text" v-model="postBody.cgw" placeholder="cgw"><br>
        <input type="text" v-model="postBody.deltal" placeholder="deltal"><br>
        <input type="text" v-model="postBody.deltar" placeholder="deltar"><br>
        <input type="text" v-model="postBody.sl" placeholder="sl"><br>
        <input type="text" v-model="postBody.sla" placeholder="sla"><br>
        <input type="text" v-model="postBody.so" placeholder="so"><br>
        <input type="text" v-model="postBody.sr" placeholder="sr"><br>
        <input type="text" v-model="postBody.rr" placeholder="rr"><br>
        <input type="text" v-model="postBody.rhor" placeholder="rhor"><br>
        <input type="text" v-model="postBody.rml" placeholder="rml"><br>
        <input type="text" v-model="postBody.rms" placeholder="rms"><br>
        <input type="text" v-model="postBody.rmr" placeholder="rmr"><br>
        <input type="text" v-model="postBody.etaB" placeholder="etaB"><br>
        <input type="text" v-model="postBody.k" placeholder="k"><br>
        <input type="text" v-model="postBody.epsg" placeholder="epsg"><br>
        <input type="text" v-model="postBody.m" placeholder="m"><br>
        <input type="text" v-model="postBody.alpha" placeholder="alpha"><br>
        <input type="text" v-model="postBody.r0" placeholder="r0"><br>
        <input type="text" v-model="postBody.r40" placeholder="r40"><br>
      </form>
      <button @click="postData()" name="button">PostData</button>
      <button @click="getData()" name="button"></button>
    </div>
  </div>
</template>

<script>
import axios from 'axios';
export default {
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
          r40: ''
        },
        runID: '',
        getJson: []
      }
    },
methods: {
    // postData() {
    //   fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user", {
    //
    //     headers: {
    //       'Content-Type': 'application/json',
    //       'x-api-key': 'AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
    //       'Access-Control-Allow-Origin': '*'
    //     },
    //     method: 'post',
    //     // mode: "no-cors",
    //   })
    //
    //   .then((response) => {
    //     console.log(response)
    //     /// test stuff
    //     // this.$router.replace('outputs') // routes to the output page
    //   })
    //   .catch(e => {
    //     console.log(e)
    //   })
    // },
    postData() {
      axios.post('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        // headers: {
        //   'Content-Type': 'application/json',
        //   'x-api-key': 'AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
        //   'Access-Control-Allow-Origin': '*'
        // },
        body: this.postBody
      })
      .then(response => {
        this.runID = response.headers['x-run-id'],
        console.log(this.runID)
      });
    },
    getData() {
      axios.get('https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user', {
        headers: {
          "X-Run-ID": this.runID,
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        }
      })
      .then((response) => {
        console.log(runID)
        this.getJson = response.data
      })
    }
  }
}
</script>

<style lang="css" scoped>
  .inputField {
    float: left;
  }
</style>
