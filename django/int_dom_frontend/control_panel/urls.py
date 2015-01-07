__author__ = 'gpietrusza'

from django.conf.urls import patterns, url
from control_panel import views

urlpatterns = patterns('',
    url(r'^$', views.index, name='index'),
    url(r'^login$', views.login_page, name='login'),
    url(r'^logout$', views.logout_page, name='logout'),
    #url(r'^control/(?P<device>)/(?P<action>)$', views.control, name='control'))
    url(r'^control/(?P<device>\d{2})/(?P<action>[a-z]+)/$', views.control, name='control'),
    url(r'^light_sensor$', views.light_sensor, name='light_sensor'),
    )
