<template>
  <div>
    <button @click="getData()" name="button">GetData</button>
    <!--<button @click="getData2()" name="button">GetData2</button>
    <button @click="getData3()" name="button">GetData3</button>
    <button @click="getData4()" name="button">GetData4</button>-->
  </div>
</template>

<script>
export default {
  name: 'outputs',
  methods: {
      getData() {
        fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user", {
          method: "GET",
          // mode: "no-cors",
          headers: {
            "Access-Control-Max-Age": "600",
            "Content-Type": "application/json",
            "X-Run-ID": "test",
            "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
          }
        })
        .then((data) => {
          console.log(data["body"])
        })
      },
    /*getData2() {
      // Alias the component instance as `vm`, so that we
      // can access it inside the promise function
      var vm = this;
      // Fetch our array of posts from an API
      fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/")
        .then(function(response) {
          return response.json()
        })
        .then(function(data) {
          vm.posts = data
          console.log(data)
        });
    },*/
    /*getData3() {
      fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/", {
        body: JSON.stringify(data),
        method: "GET",
        headers: {
          "Content-Type": "application/json",
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        },
      })
      .then((data) => {
        console.log(data)
      })
    }*/
    /*getData4() {
      fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/", {
        method: "GET",
        mode: "no-cors",
        headers: {
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        }
      })
      //.then(response => response.json())
      .then((data) => {
        console.log(data)
      })
    }*/ //getData4
  },
  mounted() {
    fetch("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user", {
      method: "GET",
      mode: "no-cors",
      headers: {
        "X-Run-ID": this.runID,
        "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
      }
    })
    .then((data) => {
      console.log(runID)
    })
  }
}
</script>

<style lang="css" scoped>
</style>
