#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import requests
import json

sys.path.insert(0, '../')

from diskspace import DiskSpace

ds = DiskSpace()
free = (ds.percent_free())
print free
def send_request():
# call function
# POST https://api.particle.io/v1/devices/330048000547343233323032/led
	
    try:
        response = requests.post(
            url="https://api.particle.io/v1/devices/330048000547343233323032/led",
            headers={
                "Authorization": "Bearer ad84d0f05262309428b7fa8595c360a33609537b",
                "Content-Type": "application/json",
            },
            data=json.dumps({
                "led": free
            })
        )
        print('Response HTTP Status Code: {status_code}'.format(
            status_code=response.status_code))
        print('Response HTTP Response Body: {content}'.format(
            content=response.content))
    except requests.exceptions.RequestException:
        print('HTTP Request failed')
send_request ()

    