/********************************************************************************
** Form generated from reading UI file 'uriwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_URIWINDOW_H
#define UI_URIWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_URIWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *DescriptionLabel;
    QLineEdit *URIEdit;
    QPushButton *OkButton;

    void setupUi(QDialog *URIWindow)
    {
        if (URIWindow->objectName().isEmpty())
            URIWindow->setObjectName(QString::fromUtf8("URIWindow"));
        URIWindow->resize(362, 160);
        URIWindow->setStyleSheet(QString::fromUtf8("QDialog#URIWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(URIWindow);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        DescriptionLabel = new QLabel(URIWindow);
        DescriptionLabel->setObjectName(QString::fromUtf8("DescriptionLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        DescriptionLabel->setFont(font);

        verticalLayout->addWidget(DescriptionLabel);

        URIEdit = new QLineEdit(URIWindow);
        URIEdit->setObjectName(QString::fromUtf8("URIEdit"));
        URIEdit->setMinimumSize(QSize(0, 30));
        URIEdit->setFont(font);
        URIEdit->setStyleSheet(QString::fromUtf8("border-radius: 5px"));
        URIEdit->setReadOnly(true);

        verticalLayout->addWidget(URIEdit);

        OkButton = new QPushButton(URIWindow);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OkButton->sizePolicy().hasHeightForWidth());
        OkButton->setSizePolicy(sizePolicy);
        OkButton->setMinimumSize(QSize(100, 30));
        OkButton->setMaximumSize(QSize(16777215, 30));
        OkButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        OkButton->setIcon(icon);
        OkButton->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(OkButton, 0, Qt::AlignRight);


        retranslateUi(URIWindow);

        QMetaObject::connectSlotsByName(URIWindow);
    } // setupUi

    void retranslateUi(QDialog *URIWindow)
    {
        URIWindow->setWindowTitle(QCoreApplication::translate("URIWindow", "Dialog", nullptr));
        DescriptionLabel->setText(QCoreApplication::translate("URIWindow", "You can share this URI with anybody\n"
"so that they could use it to open this file", nullptr));
        OkButton->setText(QCoreApplication::translate("URIWindow", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class URIWindow: public Ui_URIWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URIWINDOW_H
