# -*- coding: utf-8 -*-
from PyQt4 import QtGui, QtCore
import sys


class MyFile(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.setGeometry(500, 500, 512, 512)
        self.setWindowTitle('test')
        self.button1 = QtGui.QPushButton('choose', self)
        self.button1.setGeometry(180, 480, 40, 20)
        self.button2 = QtGui.QPushButton('do average', self)
        self.button2.setGeometry(240, 480, 40, 20)
        self.label = QtGui.QLabel(self)
        self.label.setGeometry(10, 10, 450, 450)
        self.label.setText('ssssss')
        self.image = QtGui.QImage()
        self.image.load('1.jpg')
        b = self.image.bits()
        b.setsize(self.image.byteCount())
        print b, 'sss'
        self.image2 = QtGui.QImage()
        self.label.setAlignment(QtCore.Qt.AlignHCenter | QtCore.Qt.AlignVCenter)
        self.file_dialog = QtGui.QFileDialog()
        self.connect(self.button1, QtCore.SIGNAL('clicked()'), self.showDialog)
        self.connect(self.button2, QtCore.SIGNAL('clicked()'), self.doAverage)              
#        print self.file_dialog.getOpenFileName()
        
    def showDialog(self):
        image_src = self.file_dialog.getOpenFileName() 
        self.image.load(image_src)
        self.label.setPixmap(QtGui.QPixmap.fromImage(self.image))
    
    def doAverage(self):
        p = self.image.bits()
        print p       


app = QtGui.QApplication(sys.argv)
fileApp = MyFile()
fileApp.show()

sys.exit(app.exec_())


