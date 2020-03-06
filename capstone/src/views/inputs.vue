<template>
  <div>
    <form>
      <input type="text" v-model="postBody.hmax"><br>
      <input type="text" v-model="postBody.phih"><br>
      <input type="text" v-model="postBody.eta"><br>
      <input type="text" v-model="postBody.swmax"><br>
      <input type="text" v-model="postBody.lamda"><br>
      <input type="text" v-model="postBody.rhomax"><br>
      <input type="text" v-model="postBody.f2"><br>
      <input type="text" v-model="postBody.f1"><br>
      <input type="text" v-model="postBody.gammac"><br>
      <input type="text" v-model="postBody.gammaw"><br>
      <input type="text" v-model="postBody.gammax"><br>
      <input type="text" v-model="postBody.cgl"><br>
      <input type="text" v-model="postBody.cgr"><br>
      <input type="text" v-model="postBody.cgw"><br>
      <input type="text" v-model="postBody.deltal"><br>
      <input type="text" v-model="postBody.deltar"><br>
      <input type="text" v-model="postBody.sl"><br>
      <input type="text" v-model="postBody.sla"><br>
      <input type="text" v-model="postBody.so"><br>
      <input type="text" v-model="postBody.sr"><br>
      <input type="text" v-model="postBody.rr"><br>
      <input type="text" v-model="postBody.rhor"><br>
      <input type="text" v-model="postBody.rml"><br>
      <input type="text" v-model="postBody.rms"><br>
      <input type="text" v-model="postBody.rmr"><br>
      <input type="text" v-model="postBody.etaB"><br>
      <input type="text" v-model="postBody.k"><br>
      <input type="text" v-model="postBody.epsg"><br>
      <input type="text" v-model="postBody.m"><br>
      <input type="text" v-model="postBody.alpha"><br>
      <input type="text" v-model="postBody.r0"><br>
      <input type="text" v-model="postBody.r40"><br>
    </form>
    <button @click="getData()" name="button">PostData</button>
  </div>
</template>

<script>
export default {
  data() {
    return {
      postBody: [
        {
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
        }
      ]
    }
  },
methods: {
    getData() {
      fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user", {
        body: this.postBody,
        method: "POST",
        mode: "no-cors",
        headers: {
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        }
      })
      .then((data) => {
        console.log(data["body"])
        console.log(this.postBody) // test stuff
      })
    },
  }
}
</script>

<style lang="css" scoped>
</style>
