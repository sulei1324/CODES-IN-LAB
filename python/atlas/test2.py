__author__ = 'Su Lei'
import json
mapword=dict()
def traverse(parent):
    print parent['id'],":",parent['name']
    mapword[parent['id']]=parent['name']
    if parent.has_key('children'):
        for i in parent['children']:
            traverse(i)

with open('1.json', 'r') as f:
    data = json.load(f)
traverse(data['msg'][0])
with open('mapword.txt', 'w') as f:
    for i in mapword:
        f.write("%s\t%s\n"%(i,mapword[i]))