#!/usr/bin/python2
def FRDM_RESPONSE():
    value=[]
    file_object = open('pseudo_char_device', 'r')
    response = file_object.readline()
    #print response
    if len(response) ==1:       #if response is ACK
        return "OK"
    else:
        for i in response:
            value.append(i)
    return value
def FRDM_SEND(value):
    file_object = open('pseudo_char_device', 'w')

    if len(value)==1:
        file_object.write(value)
    else:
        file_object.write(value)



#TESTS:
#FRDM_SEND("A")
print FRDM_RESPONSE()
