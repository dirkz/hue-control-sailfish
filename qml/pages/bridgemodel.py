#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pyotherside
import urllib.request
import json
import uuid
import collections
import hashlib

fake_mac = 4000000

def mac_address():
    mac1 = uuid.getnode()
    mac2 = uuid.getnode()
    if mac1 != mac2:
        pyotherside.send('bridge-register-error', 'No valid mac address')
        return fake_mac
    else:
        return mac1

def unique_id():
    mac = mac_address()
    h = hashlib.new('ripemd160')
    h.update(str(mac).encode('utf-8'))
    return h.hexdigest()

def username():
    return "hue_control"

def extract_error(json):
    if isinstance(json, collections.Sequence) and len(json) == 1:
        return json[0]['error']['description']
    else:
        return None

def handle_error(json):
    error_msg = extract_error(json)
    if error_msg != None:
        pyotherside.send('bridge-register-error', error_msg)
    return error_msg

def fetch(url, post_data = None):
    response = urllib.request.urlopen(url, post_data)
    content = response.read().decode('utf8')
    data = json.loads(content)
    return data

def fetch_bridges():
    data = fetch("https://www.meethue.com/api/nupnp")
    pyotherside.send('bridges-fetched', data)

def is_bridge_registered(ip):
    url = "http://" + ip + "/api/" + username()
    data = fetch(url)
    error_msg = handle_error(data)
    return error_msg == None

def register_bridge(ip):
    url = "http://" + ip + "/api"
    payload = json.dumps({"devicetype": username(), "username": unique_id()}).encode('utf-8')
    data = fetch(url, payload)
    error_msg = handle_error(data)
    return error_msg == None
