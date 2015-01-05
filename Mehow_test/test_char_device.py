#!/usr/bin/python2
filename='pseudo_char_device'
def FRDM_RESPONSE():
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
def FRDM_SEND(value):
    file_object = open(filename, 'w')
    value=value+"\n"                            #adding EOL
    file_object.write(value)
    file_object.close()
def REFRESH():
    file_object = open(filename, 'w')
    file_object.write(chr(128)+'\n')              #0b10000000 as refresh Question
    file_object.close()


#TESTS:


#FRDM_SEND("AA")
REFRESH()
#FRDM_SEND("A")

print FRDM_RESPONSE()
