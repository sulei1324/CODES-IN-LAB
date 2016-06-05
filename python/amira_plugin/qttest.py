from PyQt4 import QtCore
from PyQt4 import QtGui
import sys


def f1():
    global label1
    label1.setText(line_edit1.text())
#     QtGui.QInputDialog.getText(main_window, "1", "eeee")
    
global label1
app = QtGui.QApplication(sys.argv)
main_window = QtGui.QMainWindow()
main_window.setGeometry(300, 300, 500, 500)
button1 = QtGui.QPushButton(main_window)
button1.setGeometry(100, 200, 100, 50)
line_edit1 = QtGui.QLineEdit(main_window)
line_edit1.setGeometry(100, 100, 200, 50)
line_edit1.setText("eeeeeeeeee")
label1 = QtGui.QLabel(main_window)
label1.setText(line_edit1.text())
# main_window.connect(button1, QtCore.SIGNAL("clicked()"), f1)
main_window.connect(line_edit1, QtCore.SIGNAL("textChanged(QString)"), f1)
# line_edit1.textChanged.connect(f1)
main_window.connect(button1, QtCore.SIGNAL("clicked()"), f1)
main_window.show()
sys.exit(app.exec_())



