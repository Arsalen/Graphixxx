QT += widgets
QT += core
QT += gui

HEADERS += \
    graphwidget.h \
    node.h \
    edge.h

SOURCES += \
    graphwidget.cpp \
    node.cpp \
    edge.cpp \
    main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target
