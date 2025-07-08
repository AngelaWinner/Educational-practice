QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
HEADERS += ../littleWorkingProg/Calculator.h
SOURCES +=  tst_tst_calculator.cpp ../littleWorkingProg/Calculator.cpp
