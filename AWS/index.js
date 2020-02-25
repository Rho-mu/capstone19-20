async function postData(url = '', data = {}) {
    // Default options are marked with *
    const response = fetch(url,{
        method: "POST",
        body: data,
        mode: 'no-cors',
        headers: {
            'x-api-key': 'AZlzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW',
            'Content-Type': 'application/json'
        }
    })
    
    return (await response).headers.keys().next();
}

postData("https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/user", "Daniel")
  .then((data) => {
    console.log(data); // JSON data parsed by `response.json()` call
  });