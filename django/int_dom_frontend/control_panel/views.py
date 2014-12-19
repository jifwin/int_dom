from django.shortcuts import render
from django.http import HttpResponse
from django.template import RequestContext, loader

# Create your views here.

def index(request):
    body_text = "Hello World!"
    template = loader.get_template('control_panel/index.html')
    context = RequestContext(request,
        {

            'body_text': body_text

        })
    return HttpResponse(template.render(context))