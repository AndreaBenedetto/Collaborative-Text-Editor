/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *TitleLabel;
    QLabel *SymbolLabel;
    QGridLayout *gridLayout;
    QLineEdit *UsernameEdit;
    QLineEdit *PasswordEdit;
    QPushButton *LoginButton;
    QLabel *RegistrationLink;
    QLabel *CancellationLink;
    QFrame *line;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(370, 407);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(12);
        LoginWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginWindow->setWindowIcon(icon);
        LoginWindow->setStyleSheet(QString::fromUtf8("QDialog#LoginWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        TitleLabel = new QLabel(LoginWindow);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TitleLabel->sizePolicy().hasHeightForWidth());
        TitleLabel->setSizePolicy(sizePolicy1);
        TitleLabel->setMinimumSize(QSize(0, 60));
        TitleLabel->setMaximumSize(QSize(16777215, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Manjari"));
        font1.setPointSize(36);
        font1.setBold(true);
        font1.setWeight(75);
        TitleLabel->setFont(font1);
        TitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(TitleLabel);

        SymbolLabel = new QLabel(LoginWindow);
        SymbolLabel->setObjectName(QString::fromUtf8("SymbolLabel"));
        sizePolicy.setHeightForWidth(SymbolLabel->sizePolicy().hasHeightForWidth());
        SymbolLabel->setSizePolicy(sizePolicy);
        SymbolLabel->setMinimumSize(QSize(150, 150));
        SymbolLabel->setMaximumSize(QSize(150, 150));
        SymbolLabel->setPixmap(QPixmap(QString::fromUtf8(":/IconsClient/myicons-pencil.png")));
        SymbolLabel->setScaledContents(true);

        verticalLayout->addWidget(SymbolLabel, 0, Qt::AlignHCenter);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        UsernameEdit = new QLineEdit(LoginWindow);
        UsernameEdit->setObjectName(QString::fromUtf8("UsernameEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(UsernameEdit->sizePolicy().hasHeightForWidth());
        UsernameEdit->setSizePolicy(sizePolicy2);
        UsernameEdit->setMinimumSize(QSize(200, 30));
        UsernameEdit->setMaximumSize(QSize(200, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Manjari"));
        font2.setPointSize(14);
        UsernameEdit->setFont(font2);
        UsernameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));

        gridLayout->addWidget(UsernameEdit, 0, 0, 1, 1);

        PasswordEdit = new QLineEdit(LoginWindow);
        PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
        sizePolicy2.setHeightForWidth(PasswordEdit->sizePolicy().hasHeightForWidth());
        PasswordEdit->setSizePolicy(sizePolicy2);
        PasswordEdit->setMinimumSize(QSize(200, 30));
        PasswordEdit->setMaximumSize(QSize(200, 16777215));
        PasswordEdit->setFont(font2);
        PasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        PasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(PasswordEdit, 1, 0, 1, 1);

        LoginButton = new QPushButton(LoginWindow);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setEnabled(false);
        LoginButton->setMinimumSize(QSize(0, 30));
        LoginButton->setMaximumSize(QSize(16777215, 30));
        LoginButton->setFont(font2);
        LoginButton->setMouseTracking(false);
        LoginButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-login.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginButton->setIcon(icon1);
        LoginButton->setIconSize(QSize(20, 20));

        gridLayout->addWidget(LoginButton, 2, 0, 1, 1, Qt::AlignRight);


        verticalLayout->addLayout(gridLayout);

        RegistrationLink = new QLabel(LoginWindow);
        RegistrationLink->setObjectName(QString::fromUtf8("RegistrationLink"));
        RegistrationLink->setFont(font2);
        RegistrationLink->setCursor(QCursor(Qt::PointingHandCursor));
        RegistrationLink->setAutoFillBackground(false);
        RegistrationLink->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        verticalLayout->addWidget(RegistrationLink);

        CancellationLink = new QLabel(LoginWindow);
        CancellationLink->setObjectName(QString::fromUtf8("CancellationLink"));
        CancellationLink->setFont(font2);

        verticalLayout->addWidget(CancellationLink);

        line = new QFrame(LoginWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        retranslateUi(LoginWindow);

        LoginButton->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        TitleLabel->setText(QCoreApplication::translate("LoginWindow", "PDS Client", nullptr));
        SymbolLabel->setText(QString());
        UsernameEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        PasswordEdit->setText(QString());
        PasswordEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        LoginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        RegistrationLink->setText(QCoreApplication::translate("LoginWindow", "<html><head/><body><p><span style=\" color:#000000;\">Register</span></p></body></html>", nullptr));
        CancellationLink->setText(QCoreApplication::translate("LoginWindow", "Cancel your account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
