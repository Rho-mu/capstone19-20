<template>
  <div>
    <button @click="getData2()" name="button">Button</button>
  </div>
</template>

<script>
export default {
  methods: {
    // Test 1 - Change the function in the button to switch between tests.
    getData() {
      fetch("https://ak04d09oj9.execute-api.us-east-2.amazonaws.com/Testing/user", {
        params: JSON.stringify({"runid": "yeah"}),
        method: "GET",
        mode: "no-cors",
        headers: {

          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        }
      })
      .then((data) => {
        console.log(data)
      })
    },
    // Test 2 - Change the function in the button to switch between tests.
    getData2() {
          // Alias the component instance as `vm`, so that we
          // can access it inside the promise function
          var vm = this;
          // Fetch our array of posts from an API
          fetch("https://ak04d09oj9.execute-api.us-east-2.amazonaws.com/Testing/user")
            .then(function(response) {
              return response.json();
            })
            .then(function(data) {
              vm.posts = data;
            });
        }
  }
}
</script>

<style lang="css" scoped>
</style>
