DINER_APP_VERSION = 0.1

QT       += core gui quick quickwidgets qml network xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES  += QT_NO_SSL
INCLUDEPATH += /Users/edm/workspace/install/include/maia
INCLUDEPATH += /Users/edm/workspace/install/include/quazip

macx-clang {
    message( It was generated the makefile to the (MACOS) project version! )
    LIBS += ~/workspace/install/lib/macos/libmaia.a
    LIBS += /opt/local/lib/libz.a
    LIBS += ~/workspace/install/lib/macos/libquazip.a
}

ios {
    message( It was generated the makefile to the (IOS) project version! )
    QMAKE_INFO_PLIST = ios/iosInfo.plist
    LIBS += /Users/edm/workspace/install/lib/ios/arm7/libmaia.a
    LIBS += /Users/edm/workspace/install/lib/ios/arm7/libquazip.a
}

android {
    message( It was generated the makefile to the (ANDROID) project version! )
    LIBS += ~/workspace/install/lib/android/libmaia.a
    LIBS += ~/workspace/install/lib/android/libquazip.a
}

TARGET = DinerTablet
TEMPLATE = app

CONFIG(debug, debug|release) {
    message( Diner app build DEBUG mode. )
    DEFINES += DINER_APP_DEBUG
}
CONFIG(release, debug|release) {
    message( Diner app build RELEASE mode. )
    DEFINES += DINER_APP_RELEASE
}

SOURCES += src/thirdpartycodes/pictureflow.cpp \
        src/main.cpp \
        src/loader.cpp \
        src/dinerapplication.cpp \
        src/getdeviceinfo.cpp \
        src/picturebrowser.cpp \
        src/wigglytext.cpp \
        src/xmlrpcclient.cpp \
        src/overlaydialogbox.cpp \
        src/filedownloader.cpp \
        src/configdialog.cpp \
        src/configdialogconn.cpp \
        src/login.cpp \
        src/mainwidget.cpp \
        src/menuchoice.cpp \
        src/menufoods.cpp \
        src/menudrinks.cpp \
        src/menuwine.cpp \
        src/menuwinefilter.cpp \
        src/menuwidget.cpp \
        src/clientnamelist.cpp \
        src/listorder.cpp \
        src/listitemdetails.cpp \
        src/listitemwinedetails.cpp \
        src/advertisingnews.cpp \
        src/bill.cpp \
        src/printout.cpp \
        src/loading.cpp

HEADERS  += src/thirdpartycodes/pictureflow.h \
         src/thirdpartycodes/imgzoom.h \
         src/loader.h \
         src/filedownloader.h \
         src/dinerapplication.h \
         src/getdeviceinfo.h \
         src/picturebrowser.h \
         src/wigglytext.h \
         src/xmlrpcclient.h \
         src/overlaydialogbox.h \
         src/configdialog.h \
         src/configdialogconn.h \
         src/login.h \
         src/mainwidget.h \
         src/menuchoice.h \
         src/menufoods.h \
         src/menuwine.h \
         src/menudrinks.h \
         src/menuwidget.h \
         src/menuwinefilter.h \
         src/clientnamelist.h \
         src/listorder.h \
         src/listitemdetails.h \
         src/listitemwinedetails.h \
         src/advertisingnews.h \
         src/bill.h \
         src/printout.h \
         src/loading.h

FORMS    += ui/mainwidget.ui \
         ui/menuwidget.ui \
         ui/menuchoice.ui \
         ui/menufoods.ui \
         ui/menuwine.ui \
         ui/menuwinefilter.ui \
         ui/menudrinks.ui \
         ui/login.ui \
         ui/clientnamelist.ui \
         ui/listorder.ui \
         ui/listitemdetails.ui \
         ui/listitemwinedetails.ui \
         ui/advertisingnews.ui \
         ui/bill.ui \
         ui/overlaydialogbox.ui \
         ui/loading.ui

RESOURCES += \
    qml.qrc \
    others.qrc \
    images.qrc

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

# Supported languages
LANGUAGES = pt_BR es

# Available translations
TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/translations/DinerTablet_, .ts)

# Used to embed the qm files in resources
TRANSLATIONS_FILES =

# run LRELEASE to generate the qm files
qtPrepareTool(LRELEASE, lrelease)
for(tsfile, TRANSLATIONS) {
    qmfile = $$shadowed($$tsfile)
    qmfile ~= s,\\.ts$,.qm,
    qmdir = $$dirname(qmfile)
    !exists($$qmdir) {
        mkpath($$qmdir)|error("Aborting.")
    }
    command = $$LRELEASE -removeidentical $$tsfile -qm  $$qmfile
    system($$command)|error("Failed to run: $$command")
    TRANSLATIONS_FILES += $$qmfile
}
