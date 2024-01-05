QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    articulacion.cpp \
    dialog1.cpp \
    dialog2.cpp \
    main.cpp \
    mainwindow.cpp \
    paciente.cpp \
    test.cpp

HEADERS += \
    MiExcepcion.h \
    articulacion.h \
    dialog1.h \
    dialog2.h \
    mainwindow.h \
    paciente.h \
    test.h

FORMS += \
    dialog1.ui \
    dialog2.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# OPENCV
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opencv/build/x64/vc15/lib/ -lopencv_world455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opencv/build/x64/vc15/lib/ -lopencv_world455d
else:unix: LIBS += -L$$PWD/../../../../opencv/build/x64/vc15/lib/ -lopencv_world455

INCLUDEPATH += $$PWD/../../../../opencv/build/include
DEPENDPATH += $$PWD/../../../../opencv/build/include

# KINECT SDK 2.0
#win32:CONFIG(debug, debug|release): LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x86/Kinect20.lib"
#else:win32:CONFIG(debug, debug|release): LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x86/Kinect20d.lib"
#else:unix: LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x86/lKinect20.lib"

INCLUDEPATH += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/inc"
DEPENDPATH += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/inc"

# KINECT SDK 2.0
win32:CONFIG(release, debug|release): LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x64/Kinect20.lib"
else:win32:CONFIG(debug, debug|release): LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x64/Kinect20d.lib"
else:unix: LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x64/lKinect20.lib"

DISTFILES +=
