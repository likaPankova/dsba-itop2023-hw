#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include "about.h"
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), tableModel(new TableModel), proxyModel(new ProxyModel), slideText("Max Result: "), lang("ENG")
//    , _translator(new QTranslator(this))

{
    ui->setupUi(this);
    proxyModel->setSourceModel(tableModel);
    ui->tableView->setModel(proxyModel);
    ui->comboBox->insertItem(0,"All groups");
    ui->comboBox->insertItem(1,"group A");
    ui->comboBox->insertItem(2,"group B");
    ui->comboBox->insertItem(3,"group C");
    ui->comboBox->insertItem(4,"group D");
    ui->comboBox->insertItem(5,"group E");

    helpMenu = menuBar() -> addMenu("File");
    help = new QAction("Info");
    connect(help, &QAction::triggered, this, &MainWindow::aboutFunction);

    save = new QAction("Save as");
    connect(save, &QAction::triggered, this, &MainWindow::saveFunction);

    load = new QAction("Open");
    connect(load, &QAction::triggered, this, &MainWindow::openFunction);

    transRu = new QAction("Russian");
    connect(transRu, &QAction::triggered, this, &MainWindow::translateRussian);
    transEn = new QAction("English");
    connect(transEn, &QAction::triggered, this, &MainWindow::translateEnglish);

    helpMenu->addAction(load);
    helpMenu->addAction(save);
    languageMenu = helpMenu -> addMenu("Change Language");
    helpMenu->addAction(help);
    languageMenu->addAction(transRu);
    languageMenu->addAction(transEn);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableModel;
}

void MainWindow::translateEnglish()
{
    helpMenu->setTitle("File");
    languageMenu->setTitle("Change language");
    save->setText("Save as");
    load->setText("Open");
    help->setText("Info");
    transRu->setText("Russian");
    transEn->setText("English");
    ui->comboBox->setItemText(0, "All groups");
    ui->comboBox->setItemText(1, "group A");
    ui->comboBox->setItemText(2, "group B");
    ui->comboBox->setItemText(3, "group C");
    ui->comboBox->setItemText(4, "group D");
    ui->comboBox->setItemText(5, "group E");
    ui->mathScoreLabel->setText("mathScore");
    ui->readingScoreLabel->setText("readingScore");
    ui->writingScoreLabel->setText("writingScore");
    ui->maleRadioButton->setText("male");
    ui->femaleRadioButton->setText("female");
    ui->deleteButton->setText("delete an item");
    ui->addRowButton->setText("add new");
    slideText = "Max Result: ";
    ui->label->setText(slideText + QString::number(ui->slide_lb->value()));
    tableModel->changeLan("ENG");
    lang = "ENG";
}

void MainWindow::translateRussian()
{
    helpMenu->setTitle("Файл");
    languageMenu->setTitle("Сменить язык");
    save->setText("Сохранить");
    load->setText("Открыть");
    help->setText("Информация");
    transRu->setText("Русский");
    transEn->setText("Английский");
    ui->comboBox->setItemText(0, "Все группы");
    ui->comboBox->setItemText(1, "группа A");
    ui->comboBox->setItemText(2, "группа B");
    ui->comboBox->setItemText(3, "группа C");
    ui->comboBox->setItemText(4, "группа D");
    ui->comboBox->setItemText(5, "группа E");
    ui->mathScoreLabel->setText("Результат математики");
    ui->readingScoreLabel->setText("Результат чтения");
    ui->writingScoreLabel->setText("Результат письма");
    ui->maleRadioButton->setText("Мужчина");
    ui->femaleRadioButton->setText("Женщина");
    ui->deleteButton->setText("Удалить");
    ui->addRowButton->setText("Добавить");
    slideText = "Максимальный результат: ";
    ui->label->setText(slideText + QString::number(ui->slide_lb->value()));
    lang = "RUS";
    tableModel->changeLan("RUS");
}

void MainWindow::openFunction()
{
    QString dir = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
    if (!dir.size())
        return;
    tableModel->openData(dir);
}

void MainWindow::saveFunction()
{
    QString dir = QFileDialog::getSaveFileName(this, "Save File As", QDir::currentPath());
    if (!dir.size())
        return;
    tableModel->saveData(dir);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QList<QString> row = tableModel->getRow(proxyModel->mapToSource(index).row());
    ui->mathLine->setText(row.at(5));
    ui->readingLine->setText(row.at(6));
    ui->writingLine->setText(row.at(7));

    if (row.at(0) == "male")
        ui->maleRadioButton->setChecked(true);
    else
        ui->femaleRadioButton->setChecked(true);
}

void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    ui->tableView->setRowHidden(0, true);
}

void MainWindow::on_addRowButton_clicked()
{
    AddRowDialog addDialog(nullptr, lang);
    if (addDialog.exec())
    {
        QList<QVariant> list = addDialog.addPerson();
        QList<QString> row;
        for(int i = 0; i < tableModel->getSize().first; ++i)
        {
            row.push_back("no data");
        }
        row[0] = list[0].toString();
        row[1] = list[1].toString();
        row[5] = list[2].toString();
        row[6] = list[3].toString();
        row[7] = list[4].toString();
        row[8] = QString::number(row[5].toInt() + row[6].toInt() + row[7].toInt());
        tableModel->appendRow(row);
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    proxyModel->setCategory(arg1);
}

void MainWindow::aboutFunction()
{
    about ab;
    ab.exec();
}

void MainWindow::on_slide_lb_valueChanged(int position)
{
    ui->label->setText(slideText + QString::number(position));
    proxyModel->setScore(position);
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndex removeIndex = ui->tableView->currentIndex();
    QList<QString> row = tableModel->getRow(proxyModel->mapToSource(removeIndex).row());
    tableModel->deleteOne(row);
    ui->mathLine->setText("");
    ui->readingLine->setText("");
    ui->writingLine->setText("");
    ui->maleRadioButton->setAutoExclusive(false);
    ui->femaleRadioButton->setAutoExclusive(false);
    ui->maleRadioButton->setChecked(false);
    ui->femaleRadioButton->setChecked(false);
    ui->maleRadioButton->setAutoExclusive(true);
    ui->femaleRadioButton->setAutoExclusive(true);
}

