from PyQt4 import QtGui as qgui
from PyQt4 import QtCore as qcore
import sys

if __name__ == '__main__':
    app = qgui.QApplication(sys.argv)
    m = qgui.QSpinBox()
    m.setGeometry(100, 100, 200, 40)
    m.setWrapping(True)
    m.setRange(1, 100)
    m.setPrefix('aa: ')
    m.setSuffix('   bb')
    m.show()
    sys.exit(app.exec_())
    