#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FruitListModel.h"

#include <QMainWindow>
#include <QTimer>

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
    void dataChanged(const QModelIndex &top, const QModelIndex &bottom);
    void updateDetail(const QModelIndex &index);

private:
    Ui::MainWindow *ui_;
    FruitListModel model_;
    QTimer inflationTimer_;
};
#endif // MAINWINDOW_H
