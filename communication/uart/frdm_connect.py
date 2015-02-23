__author__ = 'mehow'
#!/usr/bin/python2
import os
from django.core import serializers
import simplejson

filename='/dev/rfcomm0'

def frdm_response():
    #value=[]
    file_object = open(filename, 'r')

    response = file_object.readline()

    file_object.close()
    #print response
    os.remove('/tmp/django.lck')
    #rm /tmp/django.lck
    if response == 'X\n':       #if response is ACK
        return "ACK"
    else:
        return "ERROR"
def frdm_send(value):
    #print "frdm send"
    if not os.path.isfile('/tmp/django.lck'):
        open('/tmp/django.lck', 'w').close()
        #touch /tmp/django.lck
        value=int_to_char(value)
        file_object = open(filename, 'w')
        value=value+"\n"                            #adding EOL
        file_object.write(value)
        file_object.close()
        return frdm_response()
    else:
        return None #i tak olewamy
def refresh_response():
    file_object = open(filename, 'r')
    response = file_object.readline()
    file_object.close()
    response = list(response)[1:-1]
    response = [ord(item) for item in response]

    resp=""

    #    resp+=str(bin(ord(item)))
    #    resp+="\n"

    resp = simplejson.dumps({"refresh": response})

    ##maybe add algoritm in future.
    #print resp
    return resp

def refresh():
    if os.path.isfile('/tmp/django.lck'):
        #print "removing djnaog.lck"
        os.remove('/tmp/django.lck')
    file_object = open(filename, 'w')
    file_object.write(chr(128)+'\n')              #0b10000000 as refresh Question
    file_object.close()
    return refresh_response()

def light_response():
    file_object=open(filename, 'r')
    response=file_object.readline()
    file_object.close()

    resp=ord(response[1])*256+ord(response[0])
#    print resp #response from lighten detectoren
    #print "kasownik"
    os.remove('/tmp/django.lck')
    return resp
def send_light():
    #print "send light"
    if not os.path.isfile('/tmp/django.lck'):
        open('/tmp/django.lck', 'w').close()
        file_object=open(filename,'w')
        file_object.write('Z'+'\n')
        file_object.close()
        return light_response()
    else:
        #print "Ha, nakladajo sie."
        return 0
def int_to_char(value):
    if isinstance( value, int ):
        response=chr(value+65)
    else:
        response=[]

        for [i, item] in enumerate(value):
            response.append(chr(item+65))

    return response
