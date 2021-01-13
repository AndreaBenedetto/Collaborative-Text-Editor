/********************************************************************************
** Form generated from reading UI file 'choosefilenamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEFILENAMEWINDOW_H
#define UI_CHOOSEFILENAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChooseFileNameWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *QuestionLabel;
    QLineEdit *FileNameEdit;
    QPushButton *OkButton;
    QFrame *line;

    void setupUi(QDialog *ChooseFileNameWindow)
    {
        if (ChooseFileNameWindow->objectName().isEmpty())
            ChooseFileNameWindow->setObjectName(QString::fromUtf8("ChooseFileNameWindow"));
        ChooseFileNameWindow->resize(420, 162);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/IconsClient/myicons-pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        ChooseFileNameWindow->setWindowIcon(icon);
        ChooseFileNameWindow->setStyleSheet(QString::fromUtf8("QDialog#ChooseFileNameWindow{\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 133, 255, 255), stop:1 rgba(241, 255, 253, 255));\n"
"}"));
        verticalLayout = new QVBoxLayout(ChooseFileNameWindow);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        QuestionLabel = new QLabel(ChooseFileNameWindow);
        QuestionLabel->setObjectName(QString::fromUtf8("QuestionLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Manjari"));
        font.setPointSize(14);
        QuestionLabel->setFont(font);

        verticalLayout->addWidget(QuestionLabel);

        FileNameEdit = new QLineEdit(ChooseFileNameWindow);
        FileNameEdit->setObjectName(QString::fromUtf8("FileNameEdit"));
        FileNameEdit->setMinimumSize(QSize(0, 30));
        FileNameEdit->setFont(font);
        FileNameEdit->setStyleSheet(QString::fromUtf8("border-radius: 5px"));

        verticalLayout->addWidget(FileNameEdit);

        OkButton = new QPushButton(ChooseFileNameWindow);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));
        OkButton->setEnabled(false);
        OkButton->setMinimumSize(QSize(0, 30));
        OkButton->setMaximumSize(QSize(500, 30));
        OkButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/IconsClient/myicons-ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        OkButton->setIcon(icon1);
        OkButton->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(OkButton, 0, Qt::AlignRight);

        line = new QFrame(ChooseFileNameWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        retranslateUi(ChooseFileNameWindow);

        OkButton->setDefault(false);


        QMetaObject::connectSlotsByName(ChooseFileNameWindow);
    } // setupUi

    void retranslateUi(QDialog *ChooseFileNameWindow)
    {
        ChooseFileNameWindow->setWindowTitle(QCoreApplication::translate("ChooseFileNameWindow", "Choose file name", nullptr));
        QuestionLabel->setText(QCoreApplication::translate("ChooseFileNameWindow", "What name do you want to give to the new file?", nullptr));
        OkButton->setText(QCoreApplication::translate("ChooseFileNameWindow", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseFileNameWindow: public Ui_ChooseFileNameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEFILENAMEWINDOW_H
