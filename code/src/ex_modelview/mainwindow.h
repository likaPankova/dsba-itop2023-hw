#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tablemodel.h"
#include <QMainWindow>
#include "proxymodel.h"
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_textActivated(const QString &arg1);

    void on_addRowButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_slide_lb_valueChanged(int position);

    void aboutFunction();

    void openFunction();

    void saveFunction();

    void on_deleteButton_clicked();

    void translateEnglish();

    void translateRussian();


private:
    Ui::MainWindow *ui;
    TableModel *tableModel;
    ProxyModel *proxyModel;

    QMenu *helpMenu;
    QMenu *languageMenu;

    QAction *aboutAction;
    QAction *languageChoice;
    QAction* save;
    QAction* help;
    QAction* load;
    QAction* transRu;
    QAction* transEn;

    QString slideText;
    QString lang;

    void createMenus();
    void createActions();
    QList<QString> collectData();

    QTranslator* _translator;

};
#endif // MAINWINDOW_H
