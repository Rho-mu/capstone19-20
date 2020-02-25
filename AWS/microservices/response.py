import json

def response(status_code = 200, body = None, headers = {}):
    required_headers = {
        'Content-Type': 'application/json'
    }
    
    required_headers.update(headers)
    
    if type(status_code) != int:
        status_code = 500
    
    if type(body) != str:
        body = json.dumps(body)
    
    return {
        'statusCode': str(status_code),
        'body': body,
        'headers': required_headers,
    }