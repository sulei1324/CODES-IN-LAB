from django.shortcuts import render
from django.http import HttpRequest, HttpResponse

def f1(request):
    return HttpResponse('<html>2222222</html>')
# Create your views here.
