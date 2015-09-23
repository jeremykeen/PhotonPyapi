# Install the Python Requests library:
# pip install requests


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
                "led": "red"
            })
        )
        print('Response HTTP Status Code: {status_code}'.format(
            status_code=response.status_code))
        print('Response HTTP Response Body: {content}'.format(
            content=response.content))
    except requests.exceptions.RequestException:
        print('HTTP Request failed')

send_request ()