/********************************************************************************
** Form generated from reading UI file 'userinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFO_H
#define UI_USERINFO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserInfo
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *ProfilePicture;
    QLabel *UsernameLabel;
    QLabel *NameLabel;

    void setupUi(QDialog *UserInfo)
    {
        if (UserInfo->objectName().isEmpty())
            UserInfo->setObjectName(QString::fromUtf8("UserInfo"));
        UserInfo->resize(239, 304);
        UserInfo->setMinimumSize(QSize(200, 150));
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        UserInfo->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        UserInfo->setWindowIcon(icon);
        UserInfo->setStyleSheet(QString::fromUtf8("QDialog#UserInfo{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(UserInfo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        ProfilePicture = new QLabel(UserInfo);
        ProfilePicture->setObjectName(QString::fromUtf8("ProfilePicture"));
        ProfilePicture->setMinimumSize(QSize(96, 96));
        ProfilePicture->setMaximumSize(QSize(96, 96));
        ProfilePicture->setPixmap(QPixmap(QString::fromUtf8(":/IconsClient/myicons-default-user-image.png")));

        verticalLayout->addWidget(ProfilePicture, 0, Qt::AlignHCenter);

        UsernameLabel = new QLabel(UserInfo);
        UsernameLabel->setObjectName(QString::fromUtf8("UsernameLabel"));
        UsernameLabel->setMinimumSize(QSize(50, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Manjari"));
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setWeight(75);
        UsernameLabel->setFont(font1);
        UsernameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(UsernameLabel);

        NameLabel = new QLabel(UserInfo);
        NameLabel->setObjectName(QString::fromUtf8("NameLabel"));
        NameLabel->setMinimumSize(QSize(0, 20));
        NameLabel->setFont(font);
        NameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(NameLabel);


        retranslateUi(UserInfo);

        QMetaObject::connectSlotsByName(UserInfo);
    } // setupUi

    void retranslateUi(QDialog *UserInfo)
    {
        UserInfo->setWindowTitle(QCoreApplication::translate("UserInfo", "User Info", nullptr));
        ProfilePicture->setText(QString());
        UsernameLabel->setText(QString());
        NameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserInfo: public Ui_UserInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFO_H
