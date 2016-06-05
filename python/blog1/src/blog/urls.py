from django.conf.urls import patterns, url
from blog.views import archive

urlpattens = patterns('', 
    url(r'^$', archive), 
    url(r'^a/',  archive),
)