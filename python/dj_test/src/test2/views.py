#coding:utf-8
from django.http import HttpResponse
from django.shortcuts import render
# Create your views here.
def home(request):
    s = u"你觉得可不可以"
    l = ["html", "css", "jquery", "python", "django"]
    dict1 = {'a': u'试试', 'b': u'看看', 'c': u'好吧'}
    return render(request, 'home.html',  {"dict": dict1})