__author__ = 'mehow'
#!/usr/bin/python2
import os
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
    open('/tmp/django.lck', 'w').close()
    #touch /tmp/django.lck
    value=int_to_char(value)
    file_object = open(filename, 'w')
    value=value+"\n"                            #adding EOL
    file_object.write(value)
    file_object.close()
    return frdm_response()
def refresh_response():
    file_object = open(filename, 'r')
    response = file_object.readline()
    file_object.close()
    resp=""
    for item in response:
        resp+=str(bin(ord(item)))
    ##maybe add algoritm in future.
    #print resp
    return resp

def refresh():
    os.remove('/tmp/django.lck')
    file_object = open(filename, 'w')
    file_object.write(chr(128)+'\n')              #0b10000000 as refresh Question
    file_object.close()
    return refresh_response()

def light_response():
    file_object=open(filename, 'r')
    response=file_object.readline()
    file_object.close()

    print "DUPA"

    print response[0]
    print response[1]

    print "DUPA"

    print bin(ord(response[0]))
    print bin(ord(response[1]))
    
    print type(response)

    resp=ord(response[1])*256+ord(response[0])
    print resp #response from lighten detectoren
    return resp
def send_light():
    if not os.path.isfile('/tmp/django.lck'):
        file_object=open(filename,'w')
        file_object.write('Z'+'\n')
        file_object.close()
        return light_response()
    else:
        print "Ha, nakladajo sie."
        return 0
def int_to_char(value):
    if isinstance( value, int ):
        response=chr(value+65)
    else:
        response=[]

        for [i, item] in enumerate(value):
            response.append(chr(item+65))

    return response
