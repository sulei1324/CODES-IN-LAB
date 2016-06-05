import PyQt4 as qt
from PyQt4 import QtGui, QtCore
import sys



def on_trigger():
    print '33333'

def on_label():
    print 'eeeee'

class widget1(QtGui.QLabel):
    clicked = QtCore.pyqtSignal()
    def __init__(self, p):
        super(widget1, self).__init__(p)
    
    def mouseReleaseEvent(self, ev):
        print ev
        self.clicked.emit()




app = QtGui.QApplication(sys.argv)
main_win = QtGui.QMainWindow()
main_win.setFixedSize(QtCore.QSize(800, 400))
menu_bar = QtGui.QMenuBar()
load_menu = QtGui.QMenu('Load', menu_bar)
save_menu = QtGui.QMenu('Save', menu_bar)
action1 = QtGui.QAction('Load Swc', load_menu)
action2 = QtGui.QAction('Load Mostd', load_menu)
action1.triggered.connect(on_trigger)
menu_bar.addMenu(load_menu)
menu_bar.addMenu(save_menu)
load_menu.addAction(action1)
load_menu.addAction(action2)
main_win.setMenuBar(menu_bar)
cen_widg = QtGui.QWidget(main_win)
cen_layout = QtGui.QHBoxLayout(cen_widg)
image_label1 = QtGui.QLabel(cen_widg)
image_label2 = widget1(cen_widg)
image_label2.clicked.connect(on_label)
cen_widg.setLayout(cen_layout)
cen_layout.addWidget(image_label1)
cen_layout.addWidget(image_label2)
main_win.setCentralWidget(cen_widg) 
image_label1.setText("7777")
image_label2.setText('33111')
main_win.show()
sys.exit(app.exec_())