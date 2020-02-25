import json
import boto3

def lambda_handler(event, context):
    client = boto3.resource('dynamodb')
    table = client.Table("Outputs")
    try:
        run_id = event["run_id"]
        item = table.get_item(Key={'runid': run_id})["Item"]
        table.delete_item(Key={'runid': run_id})
        return {
            'statusCode': 200,
            'body': json.dumps(item)
        }
    except:
        return {
            'statusCode': 400,
            'body': json.dumps({})
        }
    
    