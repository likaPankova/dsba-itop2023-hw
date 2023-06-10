#ifndef ADDROWDIALOG_H
#define ADDROWDIALOG_H

#include <QDialog>

namespace Ui {
class AddRowDialog;
}

class AddRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRowDialog(QWidget *parent = nullptr, const QString &lang = "ENG");
    ~AddRowDialog();
    QList<QVariant> addPerson();
private:
    QString lan;
    Ui::AddRowDialog *ui;
    std::map<QString, QString> translate;
};

#endif // ADDROWDIALOG_H
