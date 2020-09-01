#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    ui_->list->setModel(&model_);

    // ListView selection to detail update connection and initialization
    connect(ui_->list, &QListView::activated,
            this, &MainWindow::updateDetail);
    connect(ui_->list, &QListView::clicked,
            this, &MainWindow::updateDetail);
    ui_->list->setCurrentIndex(model_.index(0));
    emit ui_->list->clicked(ui_->list->currentIndex());

    // Data change to detail update connection
    connect(&model_, &FruitListModel::dataChanged,
            this, &MainWindow::dataChanged);

    // Inflation timer
    connect(&inflationTimer_, &QTimer::timeout,
            &model_, &FruitListModel::inflatePrices);
    inflationTimer_.start(1000);

    // Buttons
    connect(ui_->addButton, &QPushButton::clicked,
            &model_, &FruitListModel::addItem);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::dataChanged(const QModelIndex &top, const QModelIndex &bottom)
{
    QModelIndex current = ui_->list->currentIndex();
    int currentRow = current.row();
    if (top.row() <= currentRow && currentRow <= bottom.row())
        updateDetail(current);
}

void MainWindow::updateDetail(const QModelIndex &index)
{
    qDebug() << "Clicked" << index.row();

    if (!ui_->nameLineEdit->hasFocus())
    {
        QString name = model_.data(index, FruitListModel::nameRole).toString();
        ui_->nameLineEdit->setText(name);
    }

    if (!ui_->priceSpinBox->hasFocus())
    {
        double price = model_.data(index, FruitListModel::priceRole).toDouble();
        ui_->priceSpinBox->setValue(price);
    }
}
