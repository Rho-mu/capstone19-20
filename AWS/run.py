import requests, time, json

def model():
    acgca_input = requests.get(
        "https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/model",
        headers = {'x-api-key': 'AZlzU9ni0x5vG6Rsub9qLaDxH6z26Zrz9bwvteiW'}
    )

    data = acgca_input.json()

    if data == {}:
        print("Skipped")
        time.sleep(10)
        return

    print(acgca_input.text)

    payload = {"run_id": data["run_id"], "output": "Hello %s!" % json.loads(data["input"])}

    requests.post(
        "https://0q0oam4bxl.execute-api.us-east-2.amazonaws.com/Testing/model",
        data = payload,
        headers = {'x-api-key': data["run_id"]}
    )

if __name__ == "__main__":
    while True:
        model()