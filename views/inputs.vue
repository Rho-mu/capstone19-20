<template>
  <form class="" action="index.html" method="post">
    <input type="text" name="inputTest" value="">input
    <button type="submit" name="button">Button</button>
  </form>
</template>

<script>
export default {
  methods: {
    updateFriend(friend) {
      fetch("https://ak04d09oj9.execute-api.us-east-2.amazonaws.com/Testing/user", {
        body: JSON.stringify(friend),
        method: "POST", //to create a new thing we use POST
        headers: {
          "Content-Type": "application/json",
          "x-api-key": "AZIzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW"
        },
      })
      .then((data) => {
        console.log(data)
      })
    }
  }
}
</script>

<style lang="css" scoped>
</style>
