/********************************************************************************
** Form generated from reading UI file 'cancellationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANCELLATIONWINDOW_H
#define UI_CANCELLATIONWINDOW_H

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

class Ui_CancellationWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *TitleClient;
    QLabel *SymbolClient;
    QGridLayout *gridLayout;
    QLineEdit *PasswordEdit;
    QLineEdit *UsernameEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *BackButton;
    QPushButton *CancelButton;
    QFrame *line;

    void setupUi(QDialog *CancellationWindow)
    {
        if (CancellationWindow->objectName().isEmpty())
            CancellationWindow->setObjectName(QString::fromUtf8("CancellationWindow"));
        CancellationWindow->resize(309, 367);
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        CancellationWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        CancellationWindow->setWindowIcon(icon);
        CancellationWindow->setStyleSheet(QString::fromUtf8("QDialog#CancellationWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(CancellationWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        TitleClient = new QLabel(CancellationWindow);
        TitleClient->setObjectName(QString::fromUtf8("TitleClient"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TitleClient->sizePolicy().hasHeightForWidth());
        TitleClient->setSizePolicy(sizePolicy);
        TitleClient->setMinimumSize(QSize(0, 60));
        TitleClient->setMaximumSize(QSize(16777215, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Manjari"));
        font1.setPointSize(36);
        font1.setBold(true);
        font1.setWeight(75);
        TitleClient->setFont(font1);
        TitleClient->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(TitleClient);

        SymbolClient = new QLabel(CancellationWindow);
        SymbolClient->setObjectName(QString::fromUtf8("SymbolClient"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SymbolClient->sizePolicy().hasHeightForWidth());
        SymbolClient->setSizePolicy(sizePolicy1);
        SymbolClient->setMinimumSize(QSize(150, 150));
        SymbolClient->setMaximumSize(QSize(150, 150));
        SymbolClient->setPixmap(QPixmap(QString::fromUtf8(":/IconsClient/myicons-pencil.png")));
        SymbolClient->setScaledContents(true);

        verticalLayout->addWidget(SymbolClient, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        PasswordEdit = new QLineEdit(CancellationWindow);
        PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
        PasswordEdit->setMinimumSize(QSize(0, 30));
        PasswordEdit->setMaximumSize(QSize(16777215, 30));
        PasswordEdit->setFont(font);
        PasswordEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));
        PasswordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(PasswordEdit, 1, 0, 1, 1);

        UsernameEdit = new QLineEdit(CancellationWindow);
        UsernameEdit->setObjectName(QString::fromUtf8("UsernameEdit"));
        UsernameEdit->setMinimumSize(QSize(0, 30));
        UsernameEdit->setMaximumSize(QSize(16777215, 30));
        UsernameEdit->setFont(font);
        UsernameEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px"));

        gridLayout->addWidget(UsernameEdit, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(165);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BackButton = new QPushButton(CancellationWindow);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));
        BackButton->setMaximumSize(QSize(36, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-back.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon1);
        BackButton->setIconSize(QSize(36, 36));
        BackButton->setFlat(true);

        horizontalLayout->addWidget(BackButton);

        CancelButton = new QPushButton(CancellationWindow);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
        CancelButton->setEnabled(false);
        CancelButton->setMaximumSize(QSize(100, 30));
        CancelButton->setFont(font);
        CancelButton->setMouseTracking(false);
        CancelButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/IconsClient/myicons-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        CancelButton->setIcon(icon2);
        CancelButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(CancelButton);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(CancellationWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        QWidget::setTabOrder(UsernameEdit, PasswordEdit);
        QWidget::setTabOrder(PasswordEdit, CancelButton);
        QWidget::setTabOrder(CancelButton, BackButton);

        retranslateUi(CancellationWindow);

        CancelButton->setDefault(true);


        QMetaObject::connectSlotsByName(CancellationWindow);
    } // setupUi

    void retranslateUi(QDialog *CancellationWindow)
    {
        CancellationWindow->setWindowTitle(QCoreApplication::translate("CancellationWindow", "Cancellation", nullptr));
        TitleClient->setText(QCoreApplication::translate("CancellationWindow", "PDS Client", nullptr));
        SymbolClient->setText(QString());
        PasswordEdit->setText(QString());
        PasswordEdit->setPlaceholderText(QCoreApplication::translate("CancellationWindow", "Password", nullptr));
        UsernameEdit->setPlaceholderText(QCoreApplication::translate("CancellationWindow", "Username", nullptr));
#if QT_CONFIG(tooltip)
        BackButton->setToolTip(QCoreApplication::translate("CancellationWindow", "<html><head/><body><p>Go back to the login window</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        BackButton->setText(QString());
        CancelButton->setText(QCoreApplication::translate("CancellationWindow", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CancellationWindow: public Ui_CancellationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANCELLATIONWINDOW_H
