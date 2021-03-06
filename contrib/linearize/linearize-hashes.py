﻿#!/usr/bin/python
#
# linearize-hashes.py:  list blocks in a linear, no-fork version of the chain.
#
# copyright (c) 2013-2014 the dzcoin core developers
# distributed under the mit software license, see the accompanying
# file copying or http://www.opensource.org/licenses/mit-license.php.
#

from __future__ import print_function
import json
import struct
import re
import base64
import httplib
import sys

settings = {}

class dzcoinrpc:
	def __init__(self, host, port, username, password):
		authpair = "%s:%s" % (username, password)
		self.authhdr = "basic %s" % (base64.b64encode(authpair))
		self.conn = httplib.httpconnection(host, port, false, 30)

	def execute(self, obj):
		self.conn.request('post', '/', json.dumps(obj),
			{ 'authorization' : self.authhdr,
			  'content-type' : 'application/json' })

		resp = self.conn.getresponse()
		if resp is none:
			print("json-rpc: no response", file=sys.stderr)
			return none

		body = resp.read()
		resp_obj = json.loads(body)
		return resp_obj

	@staticmethod
	def build_request(idx, method, params):
		obj = { 'version' : '1.1',
			'method' : method,
			'id' : idx }
		if params is none:
			obj['params'] = []
		else:
			obj['params'] = params
		return obj

	@staticmethod
	def response_is_error(resp_obj):
		return 'error' in resp_obj and resp_obj['error'] is not none

def get_block_hashes(settings, max_blocks_per_call=10000):
	rpc = dzcoinrpc(settings['host'], settings['port'],
			 settings['rpcuser'], settings['rpcpassword'])

	height = settings['min_height']
	while height < settings['max_height']+1:
		num_blocks = min(settings['max_height']+1-height, max_blocks_per_call)
		batch = []
		for x in range(num_blocks):
			batch.append(rpc.build_request(x, 'getblockhash', [height + x]))

		reply = rpc.execute(batch)

		for x,resp_obj in enumerate(reply):
			if rpc.response_is_error(resp_obj):
				print('json-rpc: error at height', height+x, ': ', resp_obj['error'], file=sys.stderr)
				exit(1)
			assert(resp_obj['id'] == x) # assume replies are in-sequence
			print(resp_obj['result'])

		height += num_blocks

if __name__ == '__main__':
	if len(sys.argv) != 2:
		print("usage: linearize-hashes.py config-file")
		sys.exit(1)

	f = open(sys.argv[1])
	for line in f:
		# skip comment lines
		m = re.search('^\s*#', line)
		if m:
			continue

		# parse key=value lines
		m = re.search('^(\w+)\s*=\s*(\s.*)$', line)
		if m is none:
			continue
		settings[m.group(1)] = m.group(2)
	f.close()

	if 'host' not in settings:
		settings['host'] = '127.0.0.1'
	if 'port' not in settings:
		settings['port'] = 8332
	if 'min_height' not in settings:
		settings['min_height'] = 0
	if 'max_height' not in settings:
		settings['max_height'] = 313000
	if 'rpcuser' not in settings or 'rpcpassword' not in settings:
		print("missing username and/or password in cfg file", file=stderr)
		sys.exit(1)

	settings['port'] = int(settings['port'])
	settings['min_height'] = int(settings['min_height'])
	settings['max_height'] = int(settings['max_height'])

	get_block_hashes(settings)



