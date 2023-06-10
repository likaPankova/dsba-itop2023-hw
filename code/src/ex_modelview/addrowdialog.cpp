#include "addrowdialog.h"
#include "ui_addrowdialog.h"

AddRowDialog::AddRowDialog(QWidget *parent, const QString &lang) : QDialog(parent), ui(new Ui::AddRowDialog), lan(lang)
{
    translate.insert({"группа A","group A"});
    translate.insert({"группа B","group B"});
    translate.insert({"группа C","group C"});
    translate.insert({"группа D","group D"});
    translate.insert({"группа E","group E"});
    ui->setupUi(this);
    if (lan == "RUS")
    {
        ui->comboBoxRace->addItems({"группа A", "группа B", "группа C", "группа D", "группа E"});
        ui->maleRadioButton->setText("Мужчина");
        ui->femaleRadioButton->setText("Женщина");
        ui->raceLabel->setText("группа");
        ui->genderLabel->setText("пол");
        ui->resultsLabel->setText("результат");
        ui->mathLabel->setText("мат");
        ui->readingLabel->setText("чтен");
        ui->writingLabel->setText("письм");
    }
    else if (lan == "ENG")
    {
        ui->comboBoxRace->addItems({"group A", "group B", "group C", "group D", "group E"});
        ui->maleRadioButton->setText("male");
        ui->femaleRadioButton->setText("female");
        ui->raceLabel->setText("race");
        ui->genderLabel->setText("gender");
        ui->resultsLabel->setText("results");
        ui->mathLabel->setText("math");
        ui->readingLabel->setText("reading");
        ui->writingLabel->setText("writing");
    }
}

AddRowDialog::~AddRowDialog() // destructor
{
    delete ui;
}

QList<QVariant> AddRowDialog::addPerson()
{
    QString race = ui->comboBoxRace->currentText();
    if(translate.count(race))
        race = translate[race];
    QString gender = ui->femaleRadioButton->isChecked() ? "female" : "male";
    int math = ui->mathSpinBox->value();
    int reading = ui->readingSpinBox->value();
    int writing = ui->writingSpinBox->value();
    QList<QVariant> list = {gender,race, math, reading, writing};
    return list;
}


