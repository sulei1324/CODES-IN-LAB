try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET

from xml.dom import minidom
import os

def prettify(elem): 
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = ET.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")


ET.register_namespace("", "http://www.w3.org/2000/svg")
svgs_file = "G:\\sulei\\workplace\\atlas\\dst\\svgs\\"
dst = "G:\\sulei\\workplace\\atlas\\dst\\single_svgs\\"

svg_names = os.listdir(svgs_file)
for svg_name in svg_names:
    svg_level = svg_name[0: len(svg_name) - 4]
    print svg_level
    if not os.path.exists(dst + svg_level):
        os.mkdir(dst + svg_level)
    svg_address = svgs_file + svg_name
    svg_tree = ET.ElementTree(file=svg_address)
    root = svg_tree.getroot()
    svg_kargs = dict()
    for svg_attrib in root.attrib:
        svg_kargs[svg_attrib] = root.attrib[svg_attrib]
    for elem in svg_tree.iter():
        if elem.tag == "{http://www.w3.org/2000/svg}path":
            structure_id_elem = elem.attrib['structure_id']
            structure_order = elem.attrib['order']
            structure_order = structure_order.zfill(5)
            # print structure_id_elem
            svg_file_name = structure_order + "_" + svg_level + "_" + structure_id_elem + ".svg"
            if not os.path.exists(svgs_file + svg_file_name):
                new_svg_root = ET.Element("svg", **svg_kargs)
                new_path_kargs = dict()
                for path_attr in elem.attrib:
                    # print path_attr, elem.attrib[path_attr]
                    new_path_kargs[path_attr] = elem.attrib[path_attr]
                new_svg_path = ET.SubElement(new_svg_root, "path", **new_path_kargs)
                new_svg_tree = ET.ElementTree(new_svg_root)
                new_svg_file = open(dst + svg_level + "\\" + svg_file_name, 'w')
                new_svg_file.writelines(prettify(new_svg_root))
                new_svg_file.close()
            else:
                print structure_id_elem
                tmp_svg = ET.ElementTree(file=(dst + svg_level + "\\" + svg_file_name))
                new_path_kargs = dict()
                for path_attr in elem.attrib:
                    # print path_attr, elem.attrib[path_attr]
                    new_path_kargs[path_attr] = elem.attrib[path_attr]
                new_svg_root = tmp_svg.getroot()
                new_svg_path = ET.SubElement(new_svg_root, "path", **new_path_kargs)
                new_svg_root.append(new_svg_path)
                new_svg_file = open(dst + svg_level + "\\" + svg_file_name, 'w')
                new_svg_file.writelines(prettify(new_svg_root))
                new_svg_file.close()