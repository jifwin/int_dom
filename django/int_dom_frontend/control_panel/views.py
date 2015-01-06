from django.shortcuts import render
import sys
from django.http import HttpResponse
from django.template import RequestContext, loader
from django.contrib.auth import authenticate, login
from django.contrib.auth import logout
sys.path.append('/home/mehow/git/communication/uart/') #do rozkminienia!!!!!!!!!!
from frdm_connect import *

# Create your views here.
def control(request,device,action):

    if request.user.is_authenticated():
        #device_table={"1":1,"2":2,"0":0}
        action_table={"blink":0,"on":1,"off":2,"toggle":3}
        #for i in device_table:
        #    if i==device:
        #for j in action_table:              #FIND!!!!
         #   if j==action:

        device = int(device)

        response=device*4+action_table[action]
        frdm_send(response)


    else:
        body_text = "Not Logged in!"

    template = loader.get_template('control_panel/control.html')
    context = RequestContext(request,
        {

            'msg':'dupa'

        })
    return HttpResponse(template.render(context))


def index(request):

    if request.user.is_authenticated():
        body_text = "Blabla!"
    else:
        body_text = "Hello World!"





    template = loader.get_template('control_panel/index.html')
    context = RequestContext(request,
        {

            'body_text': body_text

        })
    return HttpResponse(template.render(context))


def login_page(request):



    if not request.user.is_authenticated():
        username = request.POST['username']
        password = request.POST['password']

        user = authenticate(username=username, password=password)

        if user is not None:
            login(request, user)
            context = RequestContext(request,
            {
            'status': "Login Success!"
            })
            #redirect to success page

        else:
            context = RequestContext(request,
            {
            'status': "Login Failed!"
            })

        template = loader.get_template('control_panel/login.html')

        return HttpResponse(template.render(context))

    else:
        #todo: already logged in
        template = loader.get_template('control_panel/login.html')


        context = RequestContext(request,
        {
        'status': "Already logged in!"
        })


        return HttpResponse(template.render(context))

def logout_page(request):
    logout(request)
    template = loader.get_template('control_panel/logout.html')
    context = RequestContext(request,{})
    return HttpResponse(template.render(context))
