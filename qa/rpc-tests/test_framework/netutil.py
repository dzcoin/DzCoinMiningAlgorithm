﻿#!/usr/bin/env python2
# copyright (c) 2014 the dzcoin core developers
# distributed under the mit software license, see the accompanying
# file copying or http://www.opensource.org/licenses/mit-license.php.

# linux network utilities
import sys
import socket
import fcntl
import struct
import array
import os
import binascii

# roughly based on http://voorloopnul.com/blog/a-python-netstat-in-less-than-100-lines-of-code/ by ricardo pascal
state_established = '01'
state_syn_sent  = '02'
state_syn_recv = '03'
state_fin_wait1 = '04'
state_fin_wait2 = '05'
state_time_wait = '06'
state_close = '07'
state_close_wait = '08'
state_last_ack = '09'
state_listen = '0a'
state_closing = '0b'

def get_socket_inodes(pid):
    '''
    get list of socket inodes for process pid.
    '''
    base = '/proc/%i/fd' % pid
    inodes = []
    for item in os.listdir(base):
        target = os.readlink(os.path.join(base, item))
        if target.startswith('socket:'):
            inodes.append(int(target[8:-1]))
    return inodes

def _remove_empty(array):
    return [x for x in array if x !='']

def _convert_ip_port(array):
    host,port = array.split(':')
    # convert host from mangled-per-four-bytes form as used by kernel
    host = binascii.unhexlify(host)
    host_out = ''
    for x in range(0, len(host)/4):
        (val,) = struct.unpack('=i', host[x*4:(x+1)*4])
        host_out += '%08x' % val

    return host_out,int(port,16)

def netstat(typ='tcp'):
    '''
    function to return a list with status of tcp connections at linux systems
    to get pid of all network process running on system, you must run this script
    as superuser
    '''
    with open('/proc/net/'+typ,'r') as f:
        content = f.readlines()
        content.pop(0)
    result = []
    for line in content:
        line_array = _remove_empty(line.split(' '))     # split lines and remove empty spaces.
        tcp_id = line_array[0]
        l_addr = _convert_ip_port(line_array[1])
        r_addr = _convert_ip_port(line_array[2])
        state = line_array[3]
        inode = int(line_array[9])                      # need the inode to match with process pid.
        nline = [tcp_id, l_addr, r_addr, state, inode]
        result.append(nline)
    return result

def get_bind_addrs(pid):
    '''
    get bind addresses as (host,port) tuples for process pid.
    '''
    inodes = get_socket_inodes(pid)
    bind_addrs = []
    for conn in netstat('tcp') + netstat('tcp6'):
        if conn[3] == state_listen and conn[4] in inodes:
            bind_addrs.append(conn[1])
    return bind_addrs

# from: http://code.activestate.com/recipes/439093/
def all_interfaces():
    '''
    return all interfaces that are up
    '''
    is_64bits = sys.maxsize > 2**32
    struct_size = 40 if is_64bits else 32
    s = socket.socket(socket.af_inet, socket.sock_dgram)
    max_possible = 8 # initial value
    while true:
        bytes = max_possible * struct_size
        names = array.array('b', '\0' * bytes)
        outbytes = struct.unpack('il', fcntl.ioctl(
            s.fileno(),
            0x8912,  # siocgifconf
            struct.pack('il', bytes, names.buffer_info()[0])
        ))[0]
        if outbytes == bytes:
            max_possible *= 2
        else:
            break
    namestr = names.tostring()
    return [(namestr[i:i+16].split('\0', 1)[0],
             socket.inet_ntoa(namestr[i+20:i+24]))
            for i in range(0, outbytes, struct_size)]

def addr_to_hex(addr):
    '''
    convert string ipv4 or ipv6 address to binary address as returned by
    get_bind_addrs.
    very naive implementation that certainly doesn't work for all ipv6 variants.
    '''
    if '.' in addr: # ipv4
        addr = [int(x) for x in addr.split('.')]
    elif ':' in addr: # ipv6
        sub = [[], []] # prefix, suffix
        x = 0
        addr = addr.split(':')
        for i,comp in enumerate(addr):
            if comp == '':
                if i == 0 or i == (len(addr)-1): # skip empty component at beginning or end
                    continue
                x += 1 # :: skips to suffix
                assert(x < 2)
            else: # two bytes per component
                val = int(comp, 16)
                sub[x].append(val >> 8)
                sub[x].append(val & 0xff)
        nullbytes = 16 - len(sub[0]) - len(sub[1])
        assert((x == 0 and nullbytes == 0) or (x == 1 and nullbytes > 0))
        addr = sub[0] + ([0] * nullbytes) + sub[1]
    else:
        raise valueerror('could not parse address %s' % addr)
    return binascii.hexlify(bytearray(addr))


