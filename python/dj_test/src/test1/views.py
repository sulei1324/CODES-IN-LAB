#coding:utf-8
from django.http import HttpResponse
from django.shortcuts import render

# Create your views here.
def index(request):
    return HttpResponse(u'你好，师姐')

