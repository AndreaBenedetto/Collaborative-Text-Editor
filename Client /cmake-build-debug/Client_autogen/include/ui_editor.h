/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../../MyTextEdit.h"

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionPrint;
    QAction *actionPrintPreview;
    QAction *actionExportPDF;
    QAction *actionQuit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionBold;
    QAction *actionItalic;
    QAction *actionUnderline;
    QAction *actionLeft;
    QAction *actionCenter;
    QAction *actionRight;
    QAction *actionJustify;
    QAction *actionColor;
    QAction *actionOnlineUsers;
    QAction *actionSettings;
    QAction *actionShare;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QPushButton *OnlineUsersButton;
    MyTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuFormat;
    QToolBar *toolBarFile;
    QToolBar *toolBarEdit;
    QToolBar *toolBarFormat;
    QToolBar *toolBarOnlineUsers;
    QToolBar *toolBarStyle;

    void setupUi(QMainWindow *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(1000, 1000);
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        Editor->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        Editor->setWindowIcon(icon);
        Editor->setStyleSheet(QString::fromUtf8("QMainWindow#Editor{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        Editor->setUnifiedTitleAndToolBarOnMac(true);
        actionNew = new QAction(Editor);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-new-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionNew->setFont(font);
        actionOpen = new QAction(Editor);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/IconsClient/myicons-open-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionOpen->setFont(font);
        actionPrint = new QAction(Editor);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/IconsClient/myicons-print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        actionPrint->setFont(font);
        actionPrintPreview = new QAction(Editor);
        actionPrintPreview->setObjectName(QString::fromUtf8("actionPrintPreview"));
        actionPrintPreview->setIcon(icon3);
        actionPrintPreview->setFont(font);
        actionExportPDF = new QAction(Editor);
        actionExportPDF->setObjectName(QString::fromUtf8("actionExportPDF"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/IconsClient/myicons-export-pdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportPDF->setIcon(icon4);
        actionExportPDF->setFont(font);
        actionQuit = new QAction(Editor);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/IconsClient/myicons-quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon5);
        actionQuit->setFont(font);
        actionCut = new QAction(Editor);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/IconsClient/myicons-cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon6);
        actionCut->setFont(font);
        actionCopy = new QAction(Editor);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/IconsClient/myicons-copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon7);
        actionCopy->setFont(font);
        actionPaste = new QAction(Editor);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/IconsClient/myicons-paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon8);
        actionPaste->setFont(font);
        actionBold = new QAction(Editor);
        actionBold->setObjectName(QString::fromUtf8("actionBold"));
        actionBold->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/IconsClient/myicons-bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBold->setIcon(icon9);
        actionBold->setFont(font);
        actionItalic = new QAction(Editor);
        actionItalic->setObjectName(QString::fromUtf8("actionItalic"));
        actionItalic->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/IconsClient/myicons-italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionItalic->setIcon(icon10);
        actionItalic->setFont(font);
        actionUnderline = new QAction(Editor);
        actionUnderline->setObjectName(QString::fromUtf8("actionUnderline"));
        actionUnderline->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/IconsClient/myicons-underline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUnderline->setIcon(icon11);
        actionUnderline->setFont(font);
        actionLeft = new QAction(Editor);
        actionLeft->setObjectName(QString::fromUtf8("actionLeft"));
        actionLeft->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/IconsClient/myicons-align-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLeft->setIcon(icon12);
        actionLeft->setFont(font);
        actionCenter = new QAction(Editor);
        actionCenter->setObjectName(QString::fromUtf8("actionCenter"));
        actionCenter->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/IconsClient/myicons-align-center.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCenter->setIcon(icon13);
        actionCenter->setFont(font);
        actionRight = new QAction(Editor);
        actionRight->setObjectName(QString::fromUtf8("actionRight"));
        actionRight->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/IconsClient/myicons-align-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRight->setIcon(icon14);
        actionRight->setFont(font);
        actionJustify = new QAction(Editor);
        actionJustify->setObjectName(QString::fromUtf8("actionJustify"));
        actionJustify->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/IconsClient/myicons-align-justify.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJustify->setIcon(icon15);
        actionColor = new QAction(Editor);
        actionColor->setObjectName(QString::fromUtf8("actionColor"));
        actionColor->setFont(font);
        actionOnlineUsers = new QAction(Editor);
        actionOnlineUsers->setObjectName(QString::fromUtf8("actionOnlineUsers"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/IconsClient/myicons-default-user-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOnlineUsers->setIcon(icon16);
        actionSettings = new QAction(Editor);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/IconsClient/myicons-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon17);
        actionShare = new QAction(Editor);
        actionShare->setObjectName(QString::fromUtf8("actionShare"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/IconsClient/myicons-share.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShare->setIcon(icon18);
        centralWidget = new QWidget(Editor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setFont(font);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboFont = new QFontComboBox(centralWidget);
        comboFont->setObjectName(QString::fromUtf8("comboFont"));
        comboFont->setFont(font);
        comboFont->setCurrentFont(font);

        horizontalLayout->addWidget(comboFont);

        comboSize = new QComboBox(centralWidget);
        comboSize->setObjectName(QString::fromUtf8("comboSize"));
        comboSize->setFont(font);
        comboSize->setEditable(true);
        comboSize->setMaxCount(100);
        comboSize->setInsertPolicy(QComboBox::InsertAtBottom);

        horizontalLayout->addWidget(comboSize);


        verticalLayout->addLayout(horizontalLayout);

        OnlineUsersButton = new QPushButton(centralWidget);
        OnlineUsersButton->setObjectName(QString::fromUtf8("OnlineUsersButton"));
        OnlineUsersButton->setMaximumSize(QSize(32, 32));
        OnlineUsersButton->setFont(font);
        OnlineUsersButton->setIcon(icon16);
        OnlineUsersButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(OnlineUsersButton);

        textEdit = new MyTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setFont(font);

        verticalLayout->addWidget(textEdit);

        Editor->setCentralWidget(centralWidget);
        menubar = new QMenuBar(Editor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 26));
        menubar->setFont(font);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setFont(font);
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuEdit->setFont(font);
        menuFormat = new QMenu(menubar);
        menuFormat->setObjectName(QString::fromUtf8("menuFormat"));
        menuFormat->setFont(font);
        Editor->setMenuBar(menubar);
        toolBarFile = new QToolBar(Editor);
        toolBarFile->setObjectName(QString::fromUtf8("toolBarFile"));
        toolBarFile->setFont(font);
        toolBarFile->setMovable(false);
        Editor->addToolBar(Qt::TopToolBarArea, toolBarFile);
        toolBarEdit = new QToolBar(Editor);
        toolBarEdit->setObjectName(QString::fromUtf8("toolBarEdit"));
        toolBarEdit->setFont(font);
        toolBarEdit->setMovable(false);
        Editor->addToolBar(Qt::TopToolBarArea, toolBarEdit);
        toolBarFormat = new QToolBar(Editor);
        toolBarFormat->setObjectName(QString::fromUtf8("toolBarFormat"));
        toolBarFormat->setFont(font);
        toolBarFormat->setMovable(false);
        Editor->addToolBar(Qt::TopToolBarArea, toolBarFormat);
        toolBarOnlineUsers = new QToolBar(Editor);
        toolBarOnlineUsers->setObjectName(QString::fromUtf8("toolBarOnlineUsers"));
        toolBarOnlineUsers->setFont(font);
        toolBarOnlineUsers->setLayoutDirection(Qt::RightToLeft);
        toolBarOnlineUsers->setMovable(false);
        toolBarOnlineUsers->setFloatable(false);
        Editor->addToolBar(Qt::TopToolBarArea, toolBarOnlineUsers);
        toolBarStyle = new QToolBar(Editor);
        toolBarStyle->setObjectName(QString::fromUtf8("toolBarStyle"));
        toolBarStyle->setFont(font);
        toolBarStyle->setAllowedAreas(Qt::BottomToolBarArea|Qt::TopToolBarArea);
        Editor->addToolBar(Qt::TopToolBarArea, toolBarStyle);
        Editor->insertToolBarBreak(toolBarStyle);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuFormat->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionPrintPreview);
        menuFile->addAction(actionExportPDF);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuFormat->addAction(actionBold);
        menuFormat->addAction(actionItalic);
        menuFormat->addAction(actionUnderline);
        menuFormat->addSeparator();
        menuFormat->addAction(actionLeft);
        menuFormat->addAction(actionCenter);
        menuFormat->addAction(actionRight);
        menuFormat->addSeparator();
        menuFormat->addAction(actionColor);
        toolBarFile->addAction(actionNew);
        toolBarFile->addAction(actionOpen);
        toolBarFile->addAction(actionPrint);
        toolBarFile->addAction(actionExportPDF);
        toolBarEdit->addAction(actionCut);
        toolBarEdit->addAction(actionCopy);
        toolBarEdit->addAction(actionPaste);
        toolBarFormat->addAction(actionBold);
        toolBarFormat->addAction(actionItalic);
        toolBarFormat->addAction(actionUnderline);
        toolBarFormat->addAction(actionLeft);
        toolBarFormat->addAction(actionCenter);
        toolBarFormat->addAction(actionRight);
        toolBarFormat->addAction(actionColor);

        retranslateUi(Editor);

        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Editor)
    {
        Editor->setWindowTitle(QCoreApplication::translate("Editor", "Editor", nullptr));
        actionNew->setText(QCoreApplication::translate("Editor", "&New", nullptr));
        actionOpen->setText(QCoreApplication::translate("Editor", "&Open...", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("Editor", "Open...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPrint->setText(QCoreApplication::translate("Editor", "&Print...", nullptr));
#if QT_CONFIG(tooltip)
        actionPrint->setToolTip(QCoreApplication::translate("Editor", "Print...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPrintPreview->setText(QCoreApplication::translate("Editor", "Print Preview...", nullptr));
#if QT_CONFIG(tooltip)
        actionPrintPreview->setToolTip(QCoreApplication::translate("Editor", "Print Preview...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExportPDF->setText(QCoreApplication::translate("Editor", "&Export PDF...", nullptr));
#if QT_CONFIG(tooltip)
        actionExportPDF->setToolTip(QCoreApplication::translate("Editor", "Export PDF...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionQuit->setText(QCoreApplication::translate("Editor", "&Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("Editor", "Quit", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCut->setText(QCoreApplication::translate("Editor", "Cu&t", nullptr));
#if QT_CONFIG(tooltip)
        actionCut->setToolTip(QCoreApplication::translate("Editor", "Cut", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCopy->setText(QCoreApplication::translate("Editor", "&Copy", nullptr));
#if QT_CONFIG(tooltip)
        actionCopy->setToolTip(QCoreApplication::translate("Editor", "Copy", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPaste->setText(QCoreApplication::translate("Editor", "&Paste", nullptr));
#if QT_CONFIG(tooltip)
        actionPaste->setToolTip(QCoreApplication::translate("Editor", "Paste", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBold->setText(QCoreApplication::translate("Editor", "&Bold", nullptr));
#if QT_CONFIG(tooltip)
        actionBold->setToolTip(QCoreApplication::translate("Editor", "<html><head/><body><p><span style=\" font-weight:600;\">Bold</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionItalic->setText(QCoreApplication::translate("Editor", "&Italic", nullptr));
#if QT_CONFIG(tooltip)
        actionItalic->setToolTip(QCoreApplication::translate("Editor", "<html><head/><body><p><span style=\" font-style:italic;\">Italic</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionUnderline->setText(QCoreApplication::translate("Editor", "&Underline", nullptr));
#if QT_CONFIG(tooltip)
        actionUnderline->setToolTip(QCoreApplication::translate("Editor", "<html><head/><body><p><span style=\" text-decoration: underline;\">Underline</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLeft->setText(QCoreApplication::translate("Editor", "&Left", nullptr));
#if QT_CONFIG(tooltip)
        actionLeft->setToolTip(QCoreApplication::translate("Editor", "Align Left", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCenter->setText(QCoreApplication::translate("Editor", "C&enter", nullptr));
#if QT_CONFIG(tooltip)
        actionCenter->setToolTip(QCoreApplication::translate("Editor", "Align Center", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRight->setText(QCoreApplication::translate("Editor", "&Right", nullptr));
#if QT_CONFIG(tooltip)
        actionRight->setToolTip(QCoreApplication::translate("Editor", "Align Right", nullptr));
#endif // QT_CONFIG(tooltip)
        actionJustify->setText(QCoreApplication::translate("Editor", "&Justify", nullptr));
#if QT_CONFIG(tooltip)
        actionJustify->setToolTip(QCoreApplication::translate("Editor", "Justify", nullptr));
#endif // QT_CONFIG(tooltip)
        actionColor->setText(QCoreApplication::translate("Editor", "&Color", nullptr));
#if QT_CONFIG(tooltip)
        actionColor->setToolTip(QCoreApplication::translate("Editor", "Color", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOnlineUsers->setText(QCoreApplication::translate("Editor", "OnlineUsers", nullptr));
#if QT_CONFIG(tooltip)
        actionOnlineUsers->setToolTip(QCoreApplication::translate("Editor", "<html><head/><body><p>Online users</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSettings->setText(QCoreApplication::translate("Editor", "Settings", nullptr));
#if QT_CONFIG(tooltip)
        actionSettings->setToolTip(QCoreApplication::translate("Editor", "User settings...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShare->setText(QCoreApplication::translate("Editor", "Share", nullptr));
#if QT_CONFIG(tooltip)
        actionShare->setToolTip(QCoreApplication::translate("Editor", "Get URI to share this file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        OnlineUsersButton->setToolTip(QCoreApplication::translate("Editor", "Online users...", nullptr));
#endif // QT_CONFIG(tooltip)
        OnlineUsersButton->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("Editor", "&File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("Editor", "&Edit", nullptr));
        menuFormat->setTitle(QCoreApplication::translate("Editor", "F&ormat", nullptr));
        toolBarFile->setWindowTitle(QCoreApplication::translate("Editor", "File Actions", nullptr));
        toolBarEdit->setWindowTitle(QCoreApplication::translate("Editor", "Edit Actions", nullptr));
        toolBarFormat->setWindowTitle(QCoreApplication::translate("Editor", "Format Actions", nullptr));
        toolBarOnlineUsers->setWindowTitle(QCoreApplication::translate("Editor", "toolBar", nullptr));
        toolBarStyle->setWindowTitle(QCoreApplication::translate("Editor", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
