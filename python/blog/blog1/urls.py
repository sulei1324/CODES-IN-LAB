from django.conf.urls import url, patterns
from views import f1

urlpatterns = patterns('',
                       url(r'^$', f1),                  
                       )