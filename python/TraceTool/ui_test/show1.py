from PyQt4 import QtCore
from PyQt4 import QtGui
import sys

def changeText():
    global label1, stack1
    stack1.setCurrentIndex(0)

def changeText2():
    global label1
    stack1.setCurrentIndex(1)


class MyMainWindow(QtGui.QMainWindow):
    def __init__(self):
        super(MyMainWindow, self).__init__()
        self.tb = QtGui.QToolButton(self)
        self.tb.setToolTip("sdfsfs")
        self.tb.setAcceptDrops(True)
        self.tb.setIcon(QtGui.QIcon(r"G:\sulei\workplace\TraceTool\Resource\monkey_off_32x32.png"))
        self.tb.setIconSize(QtCore.QSize(32, 32))
        self.tb.setGeometry(50, 50, 32, 32)
        self.setAcceptDrops(True)
    
    def mousePressEvent(self, event1):
        if self.tb.geometry().contains(event1.pos()):
            drag1 = QtGui.QDrag(self)
            mime1 = QtCore.QMimeData()
            mime1.setText("ddddd")
            pixmap1 = QtGui.QPixmap(r"G:\sulei\workplace\TraceTool\Resource\monkey_off_32x32.png")
            drag1.setPixmap(pixmap1)
            drag1.setMimeData(mime1)
            drag1.exec_(QtCore.Qt.CopyAction | QtCore.Qt.MoveAction)
            print "dddd"
            
    def dragEnterEvent(self, event2):
        event2.setDropAction(QtCore.Qt.MoveAction)
        event2.accept()
        
    dragMoveEvent = dragEnterEvent
    
    def dropEvent(self, event3):
        self.tb.move(event3.pos())
        
        
    
    
    def event(self, event1):
#         print event1
        return super(MyMainWindow, self).event(event1)
    
    def contextMenuEvent(self, event):
        menu3 = QtGui.QMenu(self)
        action2 = QtGui.QAction("&sdfsdf", None)
        menu3.addAction(action2)
        menu3.exec_(event.globalPos())
        print event.globalPos()
        print event.pos()
        print event


app = QtGui.QApplication(sys.argv)
manWin = MyMainWindow()
size1 = QtCore.QSize(400, 400)
manWin.setGeometry(500, 100, 200, 200)
manWin.setFixedSize(size1)
widget1 = QtGui.QWidget()
menu2 = manWin.menuBar().addMenu("&ttttt")

manWin.setCentralWidget(widget1)
vbox = QtGui.QVBoxLayout()
rect0 = QtCore.QRect(900, 200, 200, 200)
widget1.setGeometry(rect0)
vbox.setMargin(20)
rect1 = QtCore.QRect(20, 20, 160, 60)
rect2 = QtCore.QRect(20, 100, 160, 60)
stack1 = QtGui.QStackedWidget()
vbox.addWidget(stack1)
widget1.setLayout(vbox)
label1 = QtGui.QLabel()
label2 = QtGui.QLabel()
button1 = QtGui.QPushButton()
button2 = QtGui.QPushButton()
button1.setText("butttttttttt")
button2.setText("butteeeeeee")
action1 = QtGui.QAction("&sssss", manWin)
menu1 = QtGui.QMenu()
menu1.addAction(action1)
button1.setMenu(menu1)
button1.setSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Fixed)
button1.clicked.connect(changeText)
button2.connect(button2, QtCore.SIGNAL("clicked()"), changeText2)
stack1.addWidget(label1)
stack1.addWidget(label2)
vbox.addWidget(button1)
vbox.addWidget(button2)
label1.setText("1111111111111")
label2.setText("2222222222222")
label1.setAlignment(QtCore.Qt.AlignCenter)
label1.setGeometry(rect1)
label2.setGeometry(rect2)
stack1.setCurrentIndex(0)
manWin.show()
sys.exit(app.exec_())
