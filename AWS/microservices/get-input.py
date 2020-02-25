import json
import boto3

sqs = boto3.client('sqs')

queue_url = 'https://sqs.us-east-2.amazonaws.com/342443493806/model-input.fifo'

def get_input():
    try:
        response = sqs.receive_message(
            QueueUrl=queue_url,
            AttributeNames=[
                'SentTimestamp'
            ],
            MaxNumberOfMessages=1,
            MessageAttributeNames=[
                'All'
            ],
            VisibilityTimeout=10,
            WaitTimeSeconds=0
        )
        
        message = response['Messages'][0]
        receipt_handle = message['ReceiptHandle']

        sqs.delete_message(
            QueueUrl=queue_url,
            ReceiptHandle=receipt_handle
        )
        
        return message["Body"]
    except:
        return {}