QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = ma_trick

CONFIG += c++11
INCLUDEPATH += ./hdr/
INCLUDEPATH += /usr/include/eigen3

DESTDIR=bin #Target file directory
OBJECTS_DIR=gen_bin #Intermediate object files directory
MOC_DIR=gen_bin #Intermediate moc files directory

# Input
HEADERS += hdr/main_win.h \
           hdr/field.h \
           hdr/set_dim.h \
           hdr/helper.h
           
FORMS += forms/main_view.ui \
         forms/set_dim.ui

SOURCES += src/main.cpp \
           src/main_win.cpp \
           src/field.cpp \
           src/set_dim.cpp 