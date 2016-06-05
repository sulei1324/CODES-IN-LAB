from xml.dom import minidom
import os
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET
    
def prettify(elem): 
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = ET.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")
    
src = r"G:\sulei\workplace\atlas\dst\svgs"
dst = r"G:\sulei\workplace\atlas\dst\svgs0"
svgs = os.listdir(src)

for a_svg in svgs:
    print a_svg
    svg_tree = ET.ElementTree(file=src+"\\"+a_svg)
    root = svg_tree.getroot()
    for elem in svg_tree.iter():
        if elem.tag == "{http://www.w3.org/2000/svg}path":
            elem.attrib['style'] = "stroke:black;fill:#ffffff;stroke-width:10"
    
    new_svg_file = open(dst+"\\"+a_svg, 'w')
    new_svg_file.writelines(prettify(root))
    new_svg_file.close()