/********************************************************************************
** Form generated from reading UI file 'openfilewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENFILEWINDOW_H
#define UI_OPENFILEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OpenFileWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *OpenMenu;
    QPushButton *RefreshButton;
    QPushButton *OpenButton;
    QPushButton *URIButton;

    void setupUi(QDialog *OpenFileWindow)
    {
        if (OpenFileWindow->objectName().isEmpty())
            OpenFileWindow->setObjectName(QString::fromUtf8("OpenFileWindow"));
        OpenFileWindow->resize(302, 140);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenFileWindow->setWindowIcon(icon);
        OpenFileWindow->setStyleSheet(QString::fromUtf8("QDialog#OpenFileWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(OpenFileWindow);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        OpenMenu = new QComboBox(OpenFileWindow);
        OpenMenu->setObjectName(QString::fromUtf8("OpenMenu"));
        OpenMenu->setMinimumSize(QSize(0, 30));
        OpenMenu->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        OpenMenu->setFont(font);
        OpenMenu->setAutoFillBackground(true);
        OpenMenu->setEditable(true);
        OpenMenu->setInsertPolicy(QComboBox::NoInsert);
        OpenMenu->setFrame(false);

        horizontalLayout->addWidget(OpenMenu);

        RefreshButton = new QPushButton(OpenFileWindow);
        RefreshButton->setObjectName(QString::fromUtf8("RefreshButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RefreshButton->sizePolicy().hasHeightForWidth());
        RefreshButton->setSizePolicy(sizePolicy);
        RefreshButton->setMinimumSize(QSize(30, 30));
        RefreshButton->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        RefreshButton->setIcon(icon1);
        RefreshButton->setIconSize(QSize(16, 16));
        RefreshButton->setAutoDefault(false);

        horizontalLayout->addWidget(RefreshButton);


        verticalLayout->addLayout(horizontalLayout);

        OpenButton = new QPushButton(OpenFileWindow);
        OpenButton->setObjectName(QString::fromUtf8("OpenButton"));
        OpenButton->setMinimumSize(QSize(0, 30));
        OpenButton->setMaximumSize(QSize(100, 30));
        OpenButton->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/IconsClient/myicons-open-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenButton->setIcon(icon2);
        OpenButton->setIconSize(QSize(20, 20));
        OpenButton->setAutoDefault(false);

        verticalLayout->addWidget(OpenButton, 0, Qt::AlignRight);


        verticalLayout_2->addLayout(verticalLayout);

        URIButton = new QPushButton(OpenFileWindow);
        URIButton->setObjectName(QString::fromUtf8("URIButton"));
        URIButton->setMinimumSize(QSize(0, 30));
        URIButton->setMaximumSize(QSize(16777215, 30));
        URIButton->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/IconsClient/myicons-uri.png"), QSize(), QIcon::Normal, QIcon::Off);
        URIButton->setIcon(icon3);
        URIButton->setIconSize(QSize(20, 20));
        URIButton->setAutoDefault(false);

        verticalLayout_2->addWidget(URIButton);


        retranslateUi(OpenFileWindow);

        OpenButton->setDefault(true);


        QMetaObject::connectSlotsByName(OpenFileWindow);
    } // setupUi

    void retranslateUi(QDialog *OpenFileWindow)
    {
        OpenFileWindow->setWindowTitle(QCoreApplication::translate("OpenFileWindow", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        RefreshButton->setToolTip(QCoreApplication::translate("OpenFileWindow", "<html><head/><body><p>Refresh file list</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        RefreshButton->setText(QString());
        OpenButton->setText(QCoreApplication::translate("OpenFileWindow", "Open", nullptr));
        URIButton->setText(QCoreApplication::translate("OpenFileWindow", "Insert URI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenFileWindow: public Ui_OpenFileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENFILEWINDOW_H
