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
    void selectionChanged(const QModelIndex &index);
    void updateDetail();
    void dataChanged(const QModelIndex &top, const QModelIndex &bottom);
    void itemRemovalRequested();
    void rowsRemoved();

private:
    Ui::MainWindow *ui_;
    FruitListModel model_ {this};
    QTimer inflationTimer_;

    QModelIndex currentIndex_;
    int currentRow_ = -1;

    bool indexOnValiditem();
};
#endif // MAINWINDOW_H
