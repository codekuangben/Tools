# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'D:\file\opensource\unity-game-git\unitygame\Tools\FileDirDiff\FileDirDiff\src\FileDirDiff\UI\LoggerWin.ui'
#
# Created: Fri Apr 24 22:39:35 2015
#      by: PyQt5 UI code generator 5.4
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_LoggerWin(object):
    def setupUi(self, LoggerWin):
        LoggerWin.setObjectName("LoggerWin")
        LoggerWin.resize(471, 300)
        self.verticalLayoutWidget = QtWidgets.QWidget()
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(10, 0, 451, 271))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.textEdit = QtWidgets.QPlainTextEdit(self.verticalLayoutWidget)
        self.textEdit.setObjectName("textEdit")
        self.verticalLayout.addWidget(self.textEdit)
        LoggerWin.setWidget(self.verticalLayoutWidget)

        self.retranslateUi(LoggerWin)
        QtCore.QMetaObject.connectSlotsByName(LoggerWin)

    def retranslateUi(self, LoggerWin):
        _translate = QtCore.QCoreApplication.translate
        LoggerWin.setWindowTitle(_translate("LoggerWin", "logger"))

