# -*- coding: utf-8 -*-
"""
Created on Tue Feb 23 10:39:29 2016

@author: zhouhang
"""
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import lxml.etree as etree
import lxml.html.soupparser as soupparser
import urllib2,os

brainArea = dict()

def SpanTreeList(treeList):
    print treeList
    for ele in treeList:
        print ele.text," id:",ele.get_attribute("id")
        brainArea[ele.text]=ele.get_attribute("id")
        clickList=ele.find_elements_by_xpath(u"./ins")
        for item in clickList:
            item.click()
        newList=ele.find_elements_by_xpath(u"./ul/li")
        SpanTreeList(newList)


browser = webdriver.Firefox()
browser.get(u"http://atlas.brain-map.org/atlas?atlas=1&plate=100960520")
#ele=browser.find_element_by_id("180606756")
browser.implicitly_wait(10)
tree=browser.find_elements_by_xpath(u".//*[@id='page_container_left_pane_inner_container']/ul/li")
SpanTreeList(tree)
with open('./brainAre.txt','r') as f:
    for i in brainArea:
        f.write([i,"\t",brainAre[i],"\n"])

