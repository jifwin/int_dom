__author__ = 'mehow'
#!/usr/bin/python2
import os
import signal
filename='/dev/rfcomm0'
def handler(signum, frame):
    print "Signal handler Error", signum
    raise IOError('Timeout')
def frdm_response():
    #value=[]
    file_object = open(filename, 'r')

    signal.signal(signal.SIGALRM, handler)
    signal.alarm(1)
    try:
        response = file_object.readline()
    except IOError:
        pass
    signal.alarm(0)
    file_object.close()
    print response
    os.remove('/tmp/django.lck')
    #rm /tmp/django.lck
    if response == 'X\n':       #if response is ACK
        return "ACK"
    else:
        return "ERROR"
def frdm_send(value):
    print "frdm send"
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
    resp=""
    for item in response:
        resp+=str(bin(ord(item)))
    ##maybe add algoritm in future.
    #print resp
    return resp

def refresh():
    if os.path.isfile('/tmp/django.lck'):
        os.remove('/tmp/django.lck')
    file_object = open(filename, 'w')
    file_object.write(chr(128)+'\n')              #0b10000000 as refresh Question
    file_object.close()
    return refresh_response()

def light_response():
    file_object=open(filename, 'r')
    signal.signal(signal.SIGALRM, handler)
    signal.alarm(1)
    try:
        response=file_object.readline()
    except IOError:
        pass
    signal.alarm(0)


    file_object.close()

   # print "DUPA"

#    print response[0]
#    print response[1]
#
#    print "DUPA"

#    print bin(ord(response[0]))
#    print bin(ord(response[1]))
    
#    print type(response)

    resp=ord(response[1])*256+ord(response[0])
#    print resp #response from lighten detectoren
    os.remove('/tmp/django.lck')
    return resp
def send_light():
    print "send light"
    if not os.path.isfile('/tmp/django.lck'):
        open('/tmp/django.lck', 'w').close()
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
