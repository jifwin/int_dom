#!/usr/bin/python2
import sys
filename=sys.argv[1]
def frdm_response():
    value=[]
    file_object = open(filename, 'r')
    response = file_object.readline()
    file_object.close()
    #print response
    if len(response) ==1:       #if response is ACK
        return "OK"
    else:
        for i in response:
            value.append(i)
    return value
def frdm_send(value):
    file_object = open(filename, 'w')
    value=value+"\n"                            #adding EOL
    file_object.write(value)
    file_object.close()
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


frdm_send(int_to_char(0))
#refresh()

print frdm_response()
