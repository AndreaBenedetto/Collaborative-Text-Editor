/********************************************************************************
** Form generated from reading UI file 'filechoicewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECHOICEWINDOW_H
#define UI_FILECHOICEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FileChoiceWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *ProfilePicture;
    QLabel *WelcomeLabel;
    QPushButton *NewButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *OpenMenu;
    QPushButton *RefreshButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *OpenButton;
    QPushButton *ShareButton;
    QPushButton *DeleteButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *URIButton;
    QPushButton *SettingsButton;
    QPushButton *LogoutButton;

    void setupUi(QDialog *FileChoiceWindow)
    {
        if (FileChoiceWindow->objectName().isEmpty())
            FileChoiceWindow->setObjectName(QString::fromUtf8("FileChoiceWindow"));
        FileChoiceWindow->resize(384, 509);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FileChoiceWindow->sizePolicy().hasHeightForWidth());
        FileChoiceWindow->setSizePolicy(sizePolicy);
        FileChoiceWindow->setMinimumSize(QSize(324, 424));
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        FileChoiceWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        FileChoiceWindow->setWindowIcon(icon);
        FileChoiceWindow->setStyleSheet(QString::fromUtf8("QDialog#FileChoiceWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(FileChoiceWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        ProfilePicture = new QLabel(FileChoiceWindow);
        ProfilePicture->setObjectName(QString::fromUtf8("ProfilePicture"));
        sizePolicy.setHeightForWidth(ProfilePicture->sizePolicy().hasHeightForWidth());
        ProfilePicture->setSizePolicy(sizePolicy);
        ProfilePicture->setMinimumSize(QSize(96, 96));
        ProfilePicture->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(ProfilePicture, 0, Qt::AlignHCenter);

        WelcomeLabel = new QLabel(FileChoiceWindow);
        WelcomeLabel->setObjectName(QString::fromUtf8("WelcomeLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Manjari"));
        font1.setPointSize(32);
        font1.setBold(true);
        font1.setWeight(75);
        WelcomeLabel->setFont(font1);
        WelcomeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(WelcomeLabel);

        NewButton = new QPushButton(FileChoiceWindow);
        NewButton->setObjectName(QString::fromUtf8("NewButton"));
        NewButton->setMinimumSize(QSize(0, 30));
        NewButton->setMaximumSize(QSize(500, 30));
        NewButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-new-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewButton->setIcon(icon1);
        NewButton->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(NewButton);

        horizontalSpacer_2 = new QSpacerItem(357, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        OpenMenu = new QComboBox(FileChoiceWindow);
        OpenMenu->setObjectName(QString::fromUtf8("OpenMenu"));
        OpenMenu->setMinimumSize(QSize(122, 32));
        OpenMenu->setMaximumSize(QSize(500, 30));
        OpenMenu->setFont(font);
        OpenMenu->setAutoFillBackground(true);
        OpenMenu->setEditable(true);
        OpenMenu->setInsertPolicy(QComboBox::NoInsert);
        OpenMenu->setFrame(false);

        horizontalLayout_2->addWidget(OpenMenu);

        RefreshButton = new QPushButton(FileChoiceWindow);
        RefreshButton->setObjectName(QString::fromUtf8("RefreshButton"));
        sizePolicy.setHeightForWidth(RefreshButton->sizePolicy().hasHeightForWidth());
        RefreshButton->setSizePolicy(sizePolicy);
        RefreshButton->setMinimumSize(QSize(30, 30));
        RefreshButton->setMaximumSize(QSize(32, 32));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans"));
        font2.setPointSize(12);
        RefreshButton->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/IconsClient/myicons-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        RefreshButton->setIcon(icon2);
        RefreshButton->setIconSize(QSize(16, 16));
        RefreshButton->setAutoDefault(false);

        horizontalLayout_2->addWidget(RefreshButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(32);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        OpenButton = new QPushButton(FileChoiceWindow);
        OpenButton->setObjectName(QString::fromUtf8("OpenButton"));
        OpenButton->setMinimumSize(QSize(0, 30));
        OpenButton->setMaximumSize(QSize(100, 30));
        OpenButton->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/IconsClient/myicons-open-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenButton->setIcon(icon3);
        OpenButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(OpenButton);

        ShareButton = new QPushButton(FileChoiceWindow);
        ShareButton->setObjectName(QString::fromUtf8("ShareButton"));
        ShareButton->setMinimumSize(QSize(0, 30));
        ShareButton->setMaximumSize(QSize(100, 30));
        ShareButton->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/IconsClient/myicons-share.png"), QSize(), QIcon::Normal, QIcon::Off);
        ShareButton->setIcon(icon4);
        ShareButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(ShareButton);

        DeleteButton = new QPushButton(FileChoiceWindow);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        DeleteButton->setMinimumSize(QSize(0, 30));
        DeleteButton->setMaximumSize(QSize(100, 30));
        DeleteButton->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/IconsClient/myicons-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        DeleteButton->setIcon(icon5);
        DeleteButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(DeleteButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        URIButton = new QPushButton(FileChoiceWindow);
        URIButton->setObjectName(QString::fromUtf8("URIButton"));
        URIButton->setMinimumSize(QSize(0, 30));
        URIButton->setMaximumSize(QSize(16777215, 30));
        URIButton->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/IconsClient/myicons-uri.png"), QSize(), QIcon::Normal, QIcon::Off);
        URIButton->setIcon(icon6);
        URIButton->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(URIButton);

        SettingsButton = new QPushButton(FileChoiceWindow);
        SettingsButton->setObjectName(QString::fromUtf8("SettingsButton"));
        SettingsButton->setMinimumSize(QSize(0, 30));
        SettingsButton->setMaximumSize(QSize(16777215, 30));
        SettingsButton->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/IconsClient/myicons-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsButton->setIcon(icon7);
        SettingsButton->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(SettingsButton);

        LogoutButton = new QPushButton(FileChoiceWindow);
        LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));
        sizePolicy.setHeightForWidth(LogoutButton->sizePolicy().hasHeightForWidth());
        LogoutButton->setSizePolicy(sizePolicy);
        LogoutButton->setMinimumSize(QSize(0, 30));
        LogoutButton->setMaximumSize(QSize(100, 30));
        LogoutButton->setFont(font);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/IconsClient/myicons-logout.png"), QSize(), QIcon::Normal, QIcon::Off);
        LogoutButton->setIcon(icon8);
        LogoutButton->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(LogoutButton, 0, Qt::AlignRight);


        retranslateUi(FileChoiceWindow);

        QMetaObject::connectSlotsByName(FileChoiceWindow);
    } // setupUi

    void retranslateUi(QDialog *FileChoiceWindow)
    {
        FileChoiceWindow->setWindowTitle(QCoreApplication::translate("FileChoiceWindow", "File choice", nullptr));
        ProfilePicture->setText(QString());
        WelcomeLabel->setText(QCoreApplication::translate("FileChoiceWindow", "Welcome back!", nullptr));
        NewButton->setText(QCoreApplication::translate("FileChoiceWindow", "New file", nullptr));
#if QT_CONFIG(tooltip)
        RefreshButton->setToolTip(QCoreApplication::translate("FileChoiceWindow", "<html><head/><body><p>Refresh file list</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        RefreshButton->setText(QString());
        OpenButton->setText(QCoreApplication::translate("FileChoiceWindow", "Open", nullptr));
#if QT_CONFIG(tooltip)
        ShareButton->setToolTip(QCoreApplication::translate("FileChoiceWindow", "<html><head/><body><p>Get shareable URI</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        ShareButton->setText(QCoreApplication::translate("FileChoiceWindow", "Share", nullptr));
        DeleteButton->setText(QCoreApplication::translate("FileChoiceWindow", "Delete", nullptr));
        URIButton->setText(QCoreApplication::translate("FileChoiceWindow", "Insert URI", nullptr));
        SettingsButton->setText(QCoreApplication::translate("FileChoiceWindow", "Settings", nullptr));
        LogoutButton->setText(QCoreApplication::translate("FileChoiceWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileChoiceWindow: public Ui_FileChoiceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECHOICEWINDOW_H
