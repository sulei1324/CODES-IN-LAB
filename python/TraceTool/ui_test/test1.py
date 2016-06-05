from PyQt4 import QtCore, QtGui
import os, sys
 
app = QtGui.QApplication(sys.argv)
a = QtGui.QTextEdit()
a.setText("exddd")
print a.toPlainText()
sys.exit(app.exec_())









# class SortedDict(dict):
#     class Iterator(object):
#         def __init__(self, sorted_dict):
#             self._dict = sorted_dict
#             self._keys = sorted(self._dict.keys())
#             self._nr_items = len(self._keys)
#             self._idx = 0
# 
#         def __iter__(self):
#             return self
# 
#         def next(self):
#             if self._idx >= self._nr_items:
#                 raise StopIteration
# 
#             key = self._keys[self._idx]
#             value = self._dict[key]
#             self._idx += 1
# 
#             return key, value
# 
#         __next__ = next
# 
#     def __iter__(self):
#         return SortedDict.Iterator(self)
# 
#     iterkeys = __iter__
# 
# a = SortedDict({"a": 1, "e": 4})
# print iter(a).next()
# 
# 
# print map(lambda x, y: x + y, range(4), range(3, 7))


# class BlogBook(QtGui.QWidget):
#     def __init__(self, parent=None):
#         super(BlogBook, self).__init__()
#         nameLabel = QtGui.QLabel("Name: ")
#         self.nameLine = QtGui.QLineEdit()
#         contextLabel = QtGui.QLabel("Context: ")
#         self.contextLines = QtGui.QTextEdit()
#         mainLayout = QtGui.QGridLayout()
#         mainLayout.addWidget(nameLabel, 0, 0)
#         mainLayout.addWidget(self.nameLine, 0, 1)
#         mainLayout.addWidget(contextLabel, 1, 0, QtCore.Qt.AlignTop)
#         mainLayout.addWidget(self.contextLines, 1, 1)
#         self.setLayout(mainLayout)
#         self.setWindowTitle("Blogs")
#      
#  
# if __name__ == "__main__":
#     import sys
#     app = QtGui.QApplication(sys.argv)
#     blogBook = BlogBook()
#     blogBook.show()
#     sys.exit(app.exec_())
#            
         
         
     
     
         
