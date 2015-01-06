#!/usr/bin/python2
import sys
filename='/dev/rfcomm0'
def frdm_response():
    #value=[]
    file_object = open(filename, 'r')
    response = file_object.readline()
    file_object.close()
    #print response
    #if response == 'X\n':       #if response is ACK
     #   return "ACK"
    #else:
     #   return "ERROR"
    return response
def frdm_send(value):
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
    ##maybe add algoritm in future.
    return response

def refresh():
    file_object = open(filename, 'w')
    file_object.write(chr(128)+'\n')              #0b10000000 as refresh Question
    file_object.close()



def int_to_char(value):
    if isinstance( value, int ):
        response=chr(value+65)
    else:
        response=[]

        for [i, item] in enumerate(value):
            response.append(chr(item+65))

    return response

#TESTS:


#print frdm_send(23)
#refresh()
for i in frdm_response():
    print bin(ord(i))
#print refresh_response()
