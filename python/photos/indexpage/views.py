from django.shortcuts import render
from django.http import HttpResponse
from django.template import Context, loader

def f1(request):
    temp = loader.get_template("404.html")
    return HttpResponse(temp.render())


# Create your views here.
