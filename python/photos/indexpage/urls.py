from django.conf.urls import url, patterns
import views as index_views


urlpatterns = patterns('',
                       url(r'^$', index_views.f1, name='index1'),                 
                       )