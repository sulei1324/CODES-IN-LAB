# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui as q

app = q.QApplication(sys.argv)
widget = q.QWidget()
widget.resize(250, 250)
widget.setWindowTitle('simple')
widget.show()
sys.exit(app.exec_())


