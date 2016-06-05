#coding:utf-8
import treelib as tb

t = tb.Tree()
print t.size()
a = tb.Node([1])
b = tb.Node([2])
c = tb.Node([3])
d = tb.Node([4])
e = tb.Node([5])
t.add_node(a, parent=None)
t.add_node(b, parent=a.identifier)
t.add_node(c, parent=b.identifier)
t.add_node(d, parent=a.identifier)
t.add_node(e, parent=d.identifier)
sub_t1 = t.subtree(b.identifier)
print sub_t1.size()
tb.Tree.WIDTH
for node_id in t.expand_tree(t.root, mode=t.WIDTH):
    print type(t.get_node(node_id).tag)
t.show()
sub_t1.show()
print t.is_branch(e.identifier)

print t




