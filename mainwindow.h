#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

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
    void on_actionNew_Book_triggered();

    void on_actionOpen_triggered();

    void on_actionErase_Bookcase_triggered();

    void on_actionDrop_triggered();

    void on_actionShow_triggered();

    void on_actionExecute_triggered();

    void on_actionDelete_Book_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidget* bookTable;

};
#endif // MAINWINDOW_H
