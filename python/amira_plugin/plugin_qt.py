#coding:utf-8
from PyQt4 import QtCore as qtcore
from PyQt4 import QtGui as qtgui

import sys
import my_module as mymo

def get_txt_name():
    global ref1, file_dialog1, txt_area1, label1
    ref1.txt_name = file_dialog1.getOpenFileName() 
     
def capture():
    global ref1
    ref1.capture_raw()
    label1.setText("Cordinate: \n" + ref1.cord + "\n" + "Note: \n" + ref1.note)
  
def get_note():
    global ref1, file_dialog1, txt_area1, label1
    ref1.note = txt_area1.text()
    label1.setText(ref1.note)

global ref1, file_dialog1, txt_area1, label1
ref1 = mymo.Ref_used()
print ref1.txt_name
app = qtgui.QApplication(sys.argv)
main_window = qtgui.QMainWindow()
main_window.setGeometry(300, 300, 400, 400)
palette1 = qtgui.QPalette()
palette2 = qtgui.QPalette()
color_white = qtgui.QColor(255, 255, 255)
color_gray = qtgui.QColor(240, 240, 240)
palette1.setColor(qtgui.QPalette.Window, color_white)
palette2.setColor(qtgui.QPalette.Window, color_gray)
main_window.setAutoFillBackground(True)
main_window.setPalette(palette2)
txt_area1 = qtgui.QLineEdit(main_window)
txt_area1.setGeometry(160, 100, 80, 30)
label1 = qtgui.QLabel(main_window)
label1.setAutoFillBackground(True)
label1.setGeometry(50, 140, 300, 80)
label1.setPalette(palette1)
button1 = qtgui.QPushButton(main_window)
button2 = qtgui.QPushButton(main_window)
button1.setGeometry(160, 20, 80, 30)
button2.setGeometry(160, 60, 80, 30)
button1.setText("Screenshot")
button2.setText("Load txt")
button1.connect(button1, qtcore.SIGNAL("clicked()"), capture)
file_dialog1 = qtgui.QFileDialog(main_window)
button2.connect(button2, qtcore.SIGNAL("clicked()"), get_txt_name)
txt_area1.connect(txt_area1, qtcore.SIGNAL("textChanged(QString)"), get_note)
main_window.show()


sys.exit(app.exec_())