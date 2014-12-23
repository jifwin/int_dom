__author__ = 'gpietrusza'

from django.conf.urls import patterns, url
from control_panel import views

urlpatterns = patterns('',
    url(r'^$', views.index, name='index'),
    url(r'^login$', views.login_page, name='login'),
    url(r'^logout$', views.logout_page, name='logout'),

)
