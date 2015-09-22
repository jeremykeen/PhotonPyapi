#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Simple example command line usage:

Usage: ./check_disk_space.py <percentage free space>

e.g:

$ ./check_disk_space.py 30
Running low on disk space. 20.0% remaining (Warning Threshold: 30%)
Total: 115.13GB
Used:  92.35GB
Avail: 22.77GB

The idea would be to put this in a Cron Job and have it email you when
the free disk space is lower than "n" percent.

"""

import sys
import requests
import json

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
                "led": "yellow"
            })
        )
        print('Response HTTP Status Code: {status_code}'.format(
            status_code=response.status_code))
        print('Response HTTP Response Body: {content}'.format(
            content=response.content))
    except requests.exceptions.RequestException:
        print('HTTP Request failed')
send_request ()