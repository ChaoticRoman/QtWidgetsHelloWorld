#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->list->setModel(&model_);

    connect(ui->list, &QListView::activated, this, &MainWindow::updateDetail);
    connect(ui->list, &QListView::clicked, this, &MainWindow::updateDetail);

    ui->list->setCurrentIndex(model_.index(0));
    emit ui->list->clicked(ui->list->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDetail(const QModelIndex &index)
{
    qDebug() << "Clicked" << index.row();
    QString name = model_.data(index, FruitListModel::nameRole).toString();
    double price = model_.data(index, FruitListModel::priceRole).toDouble();

    ui->nameLineEdit->setText(name);
    ui->priceSpinBox->setValue(price);
}
