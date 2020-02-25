import json
import boto3

def post_output(body):
    client = boto3.resource('dynamodb')

    table = client.Table("Outputs")
    output = True
    try:
        run_id = body["run_id"]
        try:
            table.get_item(Key={'runid': run_id})["Item"]
            output = False
        except:
            table.put_item(Item= {'runid': run_id, 'output': body["output"]})
    except:
        output = False

    return output
