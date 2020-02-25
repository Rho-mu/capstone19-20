import json
import boto3
import uuid

# Create SQS client
sqs = boto3.client('sqs')
queue_url = 'https://sqs.us-east-2.amazonaws.com/342443493806/model-input.fifo'

def post_input(body):
    while True:
        run_id = str(uuid.uuid1())
        try:
            table.get_item(Key={'runid': run_id})["Item"]
        except:
            sqs.send_message(
                QueueUrl=queue_url,
                MessageGroupId='input',
                MessageDeduplicationId = "dedupe",
                MessageBody=json.dumps({"run_id":run_id, "input": body})
            )
            break
    return run_id