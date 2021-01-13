/********************************************************************************
** Form generated from reading UI file 'registrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_H
#define UI_REGISTRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegistrationWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *TitleLabel;
    QLabel *SymbolLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ProfilePicture;
    QVBoxLayout *verticalLayout_2;
    QPushButton *ProfilePictureButton;
    QPushButton *DeletePictureButton;
    QGridLayout *gridLayout;
    QLineEdit *NameEdit;
    QLineEdit *SurnameEdit;
    QPushButton *InfoUsername;
    QLineEdit *UsernameEdit;
    QPushButton *CorrectUsername;
    QPushButton *InfoPassword;
    QLineEdit *PasswordEdit;
    QPushButton *CorrectPassword;
    QLineEdit *RepeatPasswordEdit;
    QPushButton *CorrectRepeatPassword;
    QHBoxLayout *horizontalLayout;
    QPushButton *BackButton;
    QPushButton *RegisterButton;
    QFrame *line;

    void setupUi(QDialog *RegistrationWindow)
    {
        if (RegistrationWindow->objectName().isEmpty())
            RegistrationWindow->setObjectName(QString::fromUtf8("RegistrationWindow"));
        RegistrationWindow->resize(335, 579);
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        RegistrationWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        RegistrationWindow->setWindowIcon(icon);
        RegistrationWindow->setStyleSheet(QString::fromUtf8("QDialog#RegistrationWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(RegistrationWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        TitleLabel = new QLabel(RegistrationWindow);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TitleLabel->sizePolicy().hasHeightForWidth());
        TitleLabel->setSizePolicy(sizePolicy);
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

        SymbolLabel = new QLabel(RegistrationWindow);
        SymbolLabel->setObjectName(QString::fromUtf8("SymbolLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SymbolLabel->sizePolicy().hasHeightForWidth());
        SymbolLabel->setSizePolicy(sizePolicy1);
        SymbolLabel->setMinimumSize(QSize(150, 150));
        SymbolLabel->setMaximumSize(QSize(150, 150));
        SymbolLabel->setPixmap(QPixmap(QString::fromUtf8(":/IconsClient/myicons-pencil.png")));
        SymbolLabel->setScaledContents(true);

        verticalLayout->addWidget(SymbolLabel, 0, Qt::AlignHCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ProfilePicture = new QLabel(RegistrationWindow);
        ProfilePicture->setObjectName(QString::fromUtf8("ProfilePicture"));
        sizePolicy1.setHeightForWidth(ProfilePicture->sizePolicy().hasHeightForWidth());
        ProfilePicture->setSizePolicy(sizePolicy1);
        ProfilePicture->setMinimumSize(QSize(96, 96));
        ProfilePicture->setMaximumSize(QSize(96, 96));
        ProfilePicture->setFrameShape(QFrame::NoFrame);
        ProfilePicture->setPixmap(QPixmap(QString::fromUtf8(":/IconsClient/myicons-default-user-image.png")));
        ProfilePicture->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ProfilePicture);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ProfilePictureButton = new QPushButton(RegistrationWindow);
        ProfilePictureButton->setObjectName(QString::fromUtf8("ProfilePictureButton"));
        ProfilePictureButton->setMinimumSize(QSize(0, 30));
        ProfilePictureButton->setMaximumSize(QSize(16777215, 30));
        ProfilePictureButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-add-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        ProfilePictureButton->setIcon(icon1);
        ProfilePictureButton->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(ProfilePictureButton);

        DeletePictureButton = new QPushButton(RegistrationWindow);
        DeletePictureButton->setObjectName(QString::fromUtf8("DeletePictureButton"));
        DeletePictureButton->setEnabled(false);
        DeletePictureButton->setMinimumSize(QSize(0, 30));
        DeletePictureButton->setMaximumSize(QSize(16777215, 30));
        DeletePictureButton->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/IconsClient/myicons-remove-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        DeletePictureButton->setIcon(icon2);
        DeletePictureButton->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(DeletePictureButton);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NameEdit = new QLineEdit(RegistrationWindow);
        NameEdit->setObjectName(QString::fromUtf8("NameEdit"));
        NameEdit->setMinimumSize(QSize(0, 30));
        NameEdit->setMaximumSize(QSize(16777215, 30));
        NameEdit->setFont(font);
        NameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));

        gridLayout->addWidget(NameEdit, 0, 1, 1, 1);

        SurnameEdit = new QLineEdit(RegistrationWindow);
        SurnameEdit->setObjectName(QString::fromUtf8("SurnameEdit"));
        SurnameEdit->setMinimumSize(QSize(0, 30));
        SurnameEdit->setMaximumSize(QSize(16777215, 30));
        SurnameEdit->setFont(font);
        SurnameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));

        gridLayout->addWidget(SurnameEdit, 1, 1, 1, 1);

        InfoUsername = new QPushButton(RegistrationWindow);
        InfoUsername->setObjectName(QString::fromUtf8("InfoUsername"));
        InfoUsername->setMaximumSize(QSize(24, 16777215));
        InfoUsername->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/IconsClient/myicons-help.png"), QSize(), QIcon::Normal, QIcon::Off);
        InfoUsername->setIcon(icon3);
        InfoUsername->setIconSize(QSize(24, 24));
        InfoUsername->setFlat(true);

        gridLayout->addWidget(InfoUsername, 2, 0, 1, 1);

        UsernameEdit = new QLineEdit(RegistrationWindow);
        UsernameEdit->setObjectName(QString::fromUtf8("UsernameEdit"));
        UsernameEdit->setMinimumSize(QSize(0, 30));
        UsernameEdit->setMaximumSize(QSize(16777215, 30));
        UsernameEdit->setFont(font);
        UsernameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));

        gridLayout->addWidget(UsernameEdit, 2, 1, 1, 1);

        CorrectUsername = new QPushButton(RegistrationWindow);
        CorrectUsername->setObjectName(QString::fromUtf8("CorrectUsername"));
        CorrectUsername->setMaximumSize(QSize(24, 16777215));
        CorrectUsername->setIconSize(QSize(24, 24));
        CorrectUsername->setFlat(true);

        gridLayout->addWidget(CorrectUsername, 2, 2, 1, 1);

        InfoPassword = new QPushButton(RegistrationWindow);
        InfoPassword->setObjectName(QString::fromUtf8("InfoPassword"));
        InfoPassword->setMaximumSize(QSize(24, 16777215));
        InfoPassword->setCursor(QCursor(Qt::PointingHandCursor));
        InfoPassword->setIcon(icon3);
        InfoPassword->setIconSize(QSize(24, 24));
        InfoPassword->setFlat(true);

        gridLayout->addWidget(InfoPassword, 3, 0, 1, 1);

        PasswordEdit = new QLineEdit(RegistrationWindow);
        PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
        PasswordEdit->setMinimumSize(QSize(0, 30));
        PasswordEdit->setMaximumSize(QSize(16777215, 30));
        PasswordEdit->setFont(font);
        PasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        PasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(PasswordEdit, 3, 1, 1, 1);

        CorrectPassword = new QPushButton(RegistrationWindow);
        CorrectPassword->setObjectName(QString::fromUtf8("CorrectPassword"));
        CorrectPassword->setMaximumSize(QSize(24, 16777215));
        CorrectPassword->setIconSize(QSize(24, 24));
        CorrectPassword->setFlat(true);

        gridLayout->addWidget(CorrectPassword, 3, 2, 1, 1);

        RepeatPasswordEdit = new QLineEdit(RegistrationWindow);
        RepeatPasswordEdit->setObjectName(QString::fromUtf8("RepeatPasswordEdit"));
        RepeatPasswordEdit->setMinimumSize(QSize(0, 30));
        RepeatPasswordEdit->setMaximumSize(QSize(16777215, 30));
        RepeatPasswordEdit->setFont(font);
        RepeatPasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        RepeatPasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(RepeatPasswordEdit, 4, 1, 1, 1);

        CorrectRepeatPassword = new QPushButton(RegistrationWindow);
        CorrectRepeatPassword->setObjectName(QString::fromUtf8("CorrectRepeatPassword"));
        CorrectRepeatPassword->setMaximumSize(QSize(24, 16777215));
        CorrectRepeatPassword->setIconSize(QSize(24, 24));
        CorrectRepeatPassword->setFlat(true);

        gridLayout->addWidget(CorrectRepeatPassword, 4, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(165);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        BackButton = new QPushButton(RegistrationWindow);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));
        BackButton->setMaximumSize(QSize(48, 16777215));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/IconsClient/myicons-back.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon4);
        BackButton->setIconSize(QSize(36, 36));
        BackButton->setFlat(true);

        horizontalLayout->addWidget(BackButton, 0, Qt::AlignLeft);

        RegisterButton = new QPushButton(RegistrationWindow);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));
        RegisterButton->setEnabled(false);
        RegisterButton->setMaximumSize(QSize(100, 30));
        RegisterButton->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/IconsClient/myicons-login.png"), QSize(), QIcon::Normal, QIcon::Off);
        RegisterButton->setIcon(icon5);
        RegisterButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(RegisterButton, 0, Qt::AlignRight);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(RegistrationWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        QWidget::setTabOrder(NameEdit, SurnameEdit);
        QWidget::setTabOrder(SurnameEdit, UsernameEdit);
        QWidget::setTabOrder(UsernameEdit, PasswordEdit);
        QWidget::setTabOrder(PasswordEdit, RepeatPasswordEdit);
        QWidget::setTabOrder(RepeatPasswordEdit, RegisterButton);

        retranslateUi(RegistrationWindow);

        RegisterButton->setDefault(true);


        QMetaObject::connectSlotsByName(RegistrationWindow);
    } // setupUi

    void retranslateUi(QDialog *RegistrationWindow)
    {
        RegistrationWindow->setWindowTitle(QCoreApplication::translate("RegistrationWindow", "Registration", nullptr));
        TitleLabel->setText(QCoreApplication::translate("RegistrationWindow", "PDS Client", nullptr));
        SymbolLabel->setText(QString());
#if QT_CONFIG(tooltip)
        ProfilePicture->setToolTip(QCoreApplication::translate("RegistrationWindow", "Your profile picture", nullptr));
#endif // QT_CONFIG(tooltip)
        ProfilePicture->setText(QString());
        ProfilePictureButton->setText(QCoreApplication::translate("RegistrationWindow", "Profile picture...", nullptr));
        DeletePictureButton->setText(QCoreApplication::translate("RegistrationWindow", "Delete picture", nullptr));
        NameEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "First name", nullptr));
        SurnameEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Last name", nullptr));
        InfoUsername->setText(QString());
        UsernameEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Username", nullptr));
        CorrectUsername->setText(QString());
        InfoPassword->setText(QString());
        PasswordEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Password", nullptr));
        CorrectPassword->setText(QString());
        RepeatPasswordEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Repeat password", nullptr));
        CorrectRepeatPassword->setText(QString());
#if QT_CONFIG(tooltip)
        BackButton->setToolTip(QCoreApplication::translate("RegistrationWindow", "<html><head/><body><p>Go back to the login window</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        BackButton->setText(QString());
        RegisterButton->setText(QCoreApplication::translate("RegistrationWindow", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrationWindow: public Ui_RegistrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_H
