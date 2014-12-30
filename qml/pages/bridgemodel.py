#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pyotherside
import urllib.request
import json

# Example how to fill a list model with data from Python.
def fetch_bridges():
    print("fetch_bridges()")
    response = urllib.request.urlopen("https://www.meethue.com/api/nupnp")
    content = response.read().decode('utf8')
    data = json.loads(content)
    pyotherside.send('bridges-fetched', data)
