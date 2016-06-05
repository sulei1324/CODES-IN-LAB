__author__ = 'Su Lei'

import xml
import xml.dom.minidom
from xml.dom.minidom import parse
import xml.etree.cElementTree as ET
import urllib2
import urllib

values = {"atlas": "1", "plate": "100960328", "structure": "236", "x": "5088", "y": "211", "zoom": "-4",
          "resolution": "16.75", "z": "5"}
data = urllib.urlencode(values)
url = "http://atlas.brain-map.org/"
geturl = url + "#" + data
request = urllib2.Request(geturl)
response = urllib2.urlopen(request)
print response.read()
# tree = ET.ElementTree(file='names.xhtml')
# print tree.getroot()
# root = tree.getroot()
# for child_of_root in root:
# print child_of_root.tag, child_of_root.attrib
#
# for elem in tree.iter():
#     print elem.tag, elem.attrib