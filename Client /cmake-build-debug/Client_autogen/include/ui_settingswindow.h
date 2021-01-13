/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

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

class Ui_SettingsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ProfilePicture;
    QVBoxLayout *verticalLayout_2;
    QPushButton *ProfilePictureButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *DeletePictureButton;
    QPushButton *UndoButton;
    QGridLayout *gridLayout;
    QLineEdit *UsernameEdit;
    QLineEdit *SurnameEdit;
    QLineEdit *CurrentPasswordEdit;
    QPushButton *CorrectCurrentPassword;
    QPushButton *CorrectNewPassword;
    QLineEdit *NewPasswordEdit;
    QPushButton *InfoPassword;
    QLineEdit *NameEdit;
    QLineEdit *RepeatNewPasswordEdit;
    QPushButton *CorrectRepeatNewPassword;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BackButton;
    QPushButton *UpdatePictureButton;
    QPushButton *UpdatePasswordButton;
    QFrame *line;

    void setupUi(QDialog *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QString::fromUtf8("SettingsWindow"));
        SettingsWindow->resize(404, 491);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsWindow->setWindowIcon(icon);
        SettingsWindow->setStyleSheet(QString::fromUtf8("QDialog#SettingsWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(SettingsWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ProfilePicture = new QLabel(SettingsWindow);
        ProfilePicture->setObjectName(QString::fromUtf8("ProfilePicture"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProfilePicture->sizePolicy().hasHeightForWidth());
        ProfilePicture->setSizePolicy(sizePolicy);
        ProfilePicture->setMinimumSize(QSize(96, 96));
        ProfilePicture->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ProfilePicture);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ProfilePictureButton = new QPushButton(SettingsWindow);
        ProfilePictureButton->setObjectName(QString::fromUtf8("ProfilePictureButton"));
        ProfilePictureButton->setMinimumSize(QSize(0, 30));
        ProfilePictureButton->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        ProfilePictureButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-change-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        ProfilePictureButton->setIcon(icon1);
        ProfilePictureButton->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(ProfilePictureButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        DeletePictureButton = new QPushButton(SettingsWindow);
        DeletePictureButton->setObjectName(QString::fromUtf8("DeletePictureButton"));
        DeletePictureButton->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DeletePictureButton->sizePolicy().hasHeightForWidth());
        DeletePictureButton->setSizePolicy(sizePolicy1);
        DeletePictureButton->setMinimumSize(QSize(0, 30));
        DeletePictureButton->setMaximumSize(QSize(16777215, 30));
        DeletePictureButton->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/IconsClient/myicons-remove-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        DeletePictureButton->setIcon(icon2);
        DeletePictureButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(DeletePictureButton);

        UndoButton = new QPushButton(SettingsWindow);
        UndoButton->setObjectName(QString::fromUtf8("UndoButton"));
        UndoButton->setEnabled(false);
        UndoButton->setMinimumSize(QSize(30, 30));
        UndoButton->setMaximumSize(QSize(30, 30));
        UndoButton->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/IconsClient/myicons-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        UndoButton->setIcon(icon3);
        UndoButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(UndoButton);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        UsernameEdit = new QLineEdit(SettingsWindow);
        UsernameEdit->setObjectName(QString::fromUtf8("UsernameEdit"));
        UsernameEdit->setMinimumSize(QSize(0, 30));
        UsernameEdit->setMaximumSize(QSize(16777215, 30));
        UsernameEdit->setFont(font);
        UsernameEdit->setCursor(QCursor(Qt::ArrowCursor));
        UsernameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        UsernameEdit->setReadOnly(true);

        gridLayout->addWidget(UsernameEdit, 2, 1, 1, 1);

        SurnameEdit = new QLineEdit(SettingsWindow);
        SurnameEdit->setObjectName(QString::fromUtf8("SurnameEdit"));
        SurnameEdit->setMinimumSize(QSize(0, 30));
        SurnameEdit->setMaximumSize(QSize(16777215, 30));
        SurnameEdit->setFont(font);
        SurnameEdit->setCursor(QCursor(Qt::ArrowCursor));
        SurnameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        SurnameEdit->setReadOnly(true);

        gridLayout->addWidget(SurnameEdit, 1, 1, 1, 1);

        CurrentPasswordEdit = new QLineEdit(SettingsWindow);
        CurrentPasswordEdit->setObjectName(QString::fromUtf8("CurrentPasswordEdit"));
        CurrentPasswordEdit->setMinimumSize(QSize(0, 30));
        CurrentPasswordEdit->setMaximumSize(QSize(16777215, 30));
        CurrentPasswordEdit->setFont(font);
        CurrentPasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        CurrentPasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(CurrentPasswordEdit, 3, 1, 1, 1);

        CorrectCurrentPassword = new QPushButton(SettingsWindow);
        CorrectCurrentPassword->setObjectName(QString::fromUtf8("CorrectCurrentPassword"));
        CorrectCurrentPassword->setMaximumSize(QSize(24, 16777215));
        CorrectCurrentPassword->setIconSize(QSize(24, 24));
        CorrectCurrentPassword->setFlat(true);

        gridLayout->addWidget(CorrectCurrentPassword, 3, 2, 1, 1);

        CorrectNewPassword = new QPushButton(SettingsWindow);
        CorrectNewPassword->setObjectName(QString::fromUtf8("CorrectNewPassword"));
        CorrectNewPassword->setMaximumSize(QSize(24, 16777215));
        CorrectNewPassword->setIconSize(QSize(24, 24));
        CorrectNewPassword->setFlat(true);

        gridLayout->addWidget(CorrectNewPassword, 4, 2, 1, 1);

        NewPasswordEdit = new QLineEdit(SettingsWindow);
        NewPasswordEdit->setObjectName(QString::fromUtf8("NewPasswordEdit"));
        NewPasswordEdit->setMinimumSize(QSize(0, 30));
        NewPasswordEdit->setMaximumSize(QSize(16777215, 30));
        NewPasswordEdit->setFont(font);
        NewPasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        NewPasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(NewPasswordEdit, 4, 1, 1, 1);

        InfoPassword = new QPushButton(SettingsWindow);
        InfoPassword->setObjectName(QString::fromUtf8("InfoPassword"));
        InfoPassword->setMinimumSize(QSize(24, 24));
        InfoPassword->setMaximumSize(QSize(24, 24));
        InfoPassword->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/IconsClient/myicons-help.png"), QSize(), QIcon::Normal, QIcon::Off);
        InfoPassword->setIcon(icon4);
        InfoPassword->setIconSize(QSize(24, 24));
        InfoPassword->setFlat(true);

        gridLayout->addWidget(InfoPassword, 4, 0, 1, 1);

        NameEdit = new QLineEdit(SettingsWindow);
        NameEdit->setObjectName(QString::fromUtf8("NameEdit"));
        NameEdit->setMinimumSize(QSize(0, 30));
        NameEdit->setMaximumSize(QSize(16777215, 30));
        NameEdit->setFont(font);
        NameEdit->setCursor(QCursor(Qt::ArrowCursor));
        NameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        NameEdit->setReadOnly(true);

        gridLayout->addWidget(NameEdit, 0, 1, 1, 1);

        RepeatNewPasswordEdit = new QLineEdit(SettingsWindow);
        RepeatNewPasswordEdit->setObjectName(QString::fromUtf8("RepeatNewPasswordEdit"));
        RepeatNewPasswordEdit->setMinimumSize(QSize(0, 30));
        RepeatNewPasswordEdit->setMaximumSize(QSize(16777215, 30));
        RepeatNewPasswordEdit->setFont(font);
        RepeatNewPasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        RepeatNewPasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(RepeatNewPasswordEdit, 5, 1, 1, 1);

        CorrectRepeatNewPassword = new QPushButton(SettingsWindow);
        CorrectRepeatNewPassword->setObjectName(QString::fromUtf8("CorrectRepeatNewPassword"));
        CorrectRepeatNewPassword->setMaximumSize(QSize(24, 16777215));
        CorrectRepeatNewPassword->setIconSize(QSize(24, 24));
        CorrectRepeatNewPassword->setFlat(true);

        gridLayout->addWidget(CorrectRepeatNewPassword, 5, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        BackButton = new QPushButton(SettingsWindow);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));
        BackButton->setMaximumSize(QSize(36, 16777215));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/IconsClient/myicons-back.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon5);
        BackButton->setIconSize(QSize(36, 36));
        BackButton->setFlat(true);

        horizontalLayout_3->addWidget(BackButton);

        UpdatePictureButton = new QPushButton(SettingsWindow);
        UpdatePictureButton->setObjectName(QString::fromUtf8("UpdatePictureButton"));
        UpdatePictureButton->setEnabled(false);
        UpdatePictureButton->setMinimumSize(QSize(0, 30));
        UpdatePictureButton->setMaximumSize(QSize(250, 30));
        UpdatePictureButton->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/IconsClient/myicons-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        UpdatePictureButton->setIcon(icon6);
        UpdatePictureButton->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(UpdatePictureButton);

        UpdatePasswordButton = new QPushButton(SettingsWindow);
        UpdatePasswordButton->setObjectName(QString::fromUtf8("UpdatePasswordButton"));
        UpdatePasswordButton->setEnabled(false);
        UpdatePasswordButton->setMinimumSize(QSize(0, 30));
        UpdatePasswordButton->setMaximumSize(QSize(200, 30));
        UpdatePasswordButton->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/IconsClient/myicons-password.png"), QSize(), QIcon::Normal, QIcon::Off);
        UpdatePasswordButton->setIcon(icon7);
        UpdatePasswordButton->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(UpdatePasswordButton);


        verticalLayout->addLayout(horizontalLayout_3);

        line = new QFrame(SettingsWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        QWidget::setTabOrder(CurrentPasswordEdit, NewPasswordEdit);
        QWidget::setTabOrder(NewPasswordEdit, RepeatNewPasswordEdit);
        QWidget::setTabOrder(RepeatNewPasswordEdit, UpdatePictureButton);
        QWidget::setTabOrder(UpdatePictureButton, UpdatePasswordButton);
        QWidget::setTabOrder(UpdatePasswordButton, ProfilePictureButton);
        QWidget::setTabOrder(ProfilePictureButton, DeletePictureButton);
        QWidget::setTabOrder(DeletePictureButton, SurnameEdit);
        QWidget::setTabOrder(SurnameEdit, UsernameEdit);
        QWidget::setTabOrder(UsernameEdit, NameEdit);
        QWidget::setTabOrder(NameEdit, UndoButton);
        QWidget::setTabOrder(UndoButton, InfoPassword);
        QWidget::setTabOrder(InfoPassword, BackButton);
        QWidget::setTabOrder(BackButton, CorrectNewPassword);
        QWidget::setTabOrder(CorrectNewPassword, CorrectCurrentPassword);
        QWidget::setTabOrder(CorrectCurrentPassword, CorrectRepeatNewPassword);

        retranslateUi(SettingsWindow);

        UpdatePasswordButton->setDefault(true);


        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QCoreApplication::translate("SettingsWindow", "Settings", nullptr));
        ProfilePicture->setText(QString());
        ProfilePictureButton->setText(QCoreApplication::translate("SettingsWindow", "Profile picture...", nullptr));
        DeletePictureButton->setText(QCoreApplication::translate("SettingsWindow", "Delete picture", nullptr));
        UndoButton->setText(QString());
        UsernameEdit->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Username", nullptr));
        SurnameEdit->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Last name", nullptr));
        CurrentPasswordEdit->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Current password", nullptr));
        CorrectCurrentPassword->setText(QString());
        CorrectNewPassword->setText(QString());
        NewPasswordEdit->setText(QString());
        NewPasswordEdit->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "New password", nullptr));
        InfoPassword->setText(QString());
        NameEdit->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "First name", nullptr));
        RepeatNewPasswordEdit->setPlaceholderText(QCoreApplication::translate("SettingsWindow", "Repeat new password", nullptr));
        CorrectRepeatNewPassword->setText(QString());
#if QT_CONFIG(tooltip)
        BackButton->setToolTip(QCoreApplication::translate("SettingsWindow", "<html><head/><body><p>Go back to the file choice window</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        BackButton->setText(QString());
        UpdatePictureButton->setText(QCoreApplication::translate("SettingsWindow", "Update Picture", nullptr));
        UpdatePasswordButton->setText(QCoreApplication::translate("SettingsWindow", "Update Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
