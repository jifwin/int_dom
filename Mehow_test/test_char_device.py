#!/usr/bin/python2
filename='pseudo_char_device'
def FRDM_RESPONSE():
    value=[]
<<<<<<< HEAD
    file_object = open(filename, 'r')
=======
    file_object = open('/dev/rfcomm0', 'r')
>>>>>>> 1d5133316cdeb933b4c1c4b2a2c227943ca51570
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
<<<<<<< HEAD
    file_object = open(filename, 'w')
    value=value+"\n"                            #adding EOL
    file_object.write(value)
    file_object.close()
def REFRESH():
    file_object = open(filename, 'w')
    file_object.write(chr(128)+'\n')              #0b10000000 as refresh Question
    file_object.close()
=======
    file_object = open('/dev/rfcomm0', 'w')
>>>>>>> 1d5133316cdeb933b4c1c4b2a2c227943ca51570


#TESTS:


<<<<<<< HEAD
#FRDM_SEND("AA")
REFRESH()
=======
#TESTS:
FRDM_SEND("A")
>>>>>>> 1d5133316cdeb933b4c1c4b2a2c227943ca51570
print FRDM_RESPONSE()
