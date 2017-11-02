SOURCES += \
    main.cpp \
    mainwindow.cpp \
    selectdialog.cpp \
    finddialog.cpp \
    deletedialog.cpp \
    adddialog.cpp \
    tablemodel.cpp \
    proxymodel.cpp \
    uniqueproxymodel.cpp \
    parser.cpp

QT += core gui \
    xml \
    widgets

HEADERS += \
    mainwindow.h \
    selectdialog.h \
    adddialog.h \
    finddialog.h \
    deletedialog.h \
    tablemodel.h \
    proxymodel.h \
    uniqueproxymodel.h \
    record.h \
    parser.h

RESOURCES += \
    resource.qrc
