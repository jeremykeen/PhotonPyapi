#!/usr/bin/python
import json
from sseclient import SSEClient

deviceID = '<deviceid>'
accessToken = '<accesstoken>'
sparkURL = 'https://api.spark.io/v1/devices/' + deviceID + '/events/?access_token=' + accessToken

messages = SSEClient('https://api.particle.io/v1/devices/events?access_token=<deviceid>')

for msg in messages:
    print 'Processing Particle Event: ', msg
    outputMsg = msg.data
    if type(outputMsg) is not str:
        parsed_json = json.loads(outputMsg)
        FilterName = "data"
        print 'Parsed JSON data: '
        print(parsed_json[FilterName])
        
# to be added:
# if data = expand
# send ViPR API to expand volume
# publish event to particle cloud