#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    ui_->list->setModel(&model_);

    // ListView selection changed
    connect(ui_->list, &QListView::activated,
            this, &MainWindow::selectionChanged);
    connect(ui_->list, &QListView::clicked,
            this, &MainWindow::selectionChanged);

    // Initial selection handling
    if (model_.rowCount() > 0)
    {
        QModelIndex newIndex = model_.index(0);
        ui_->list->setCurrentIndex(newIndex);
        selectionChanged(newIndex);
    }

    // Data changed from external source
    connect(&model_, &FruitListModel::dataChanged,
            this, &MainWindow::dataChanged);

    // Inflation timer
    connect(&inflationTimer_, &QTimer::timeout,
            &model_, &FruitListModel::inflatePrices);
    inflationTimer_.start(1000);

    // Buttons
    connect(ui_->addButton, &QPushButton::clicked,
            &model_, &FruitListModel::addItem);
    connect(ui_->deleteButton, &QPushButton::clicked,
            this, &MainWindow::itemRemovalRequested);

    // Rows removed
    connect(&model_, &FruitListModel::rowsRemoved,
            this, &MainWindow::rowsRemoved);

    // Field edits
    connect(ui_->nameLineEdit, &QLineEdit::editingFinished, [this]() {
        model_.setName(currentRow_, ui_->nameLineEdit->text());
    });

    // There are two signals of name QDoubleSpinBox::valueChanged, we need to tell which one. See:
    // https://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5
    // https://en.cppreference.com/w/cpp/language/overloaded_address
    void (QDoubleSpinBox::*pointerToOverloadedSignal)(double) = &QDoubleSpinBox::valueChanged;
    connect(ui_->priceSpinBox, pointerToOverloadedSignal, [this](double value) {
        model_.setPrice(currentRow_, value);
    });
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::selectionChanged(const QModelIndex &index)
{
    currentIndex_ = index;
    int newRow = currentIndex_.row();
    if (newRow != currentRow_)
    {
        currentRow_ = newRow;
        updateDetail();
    }
}

void MainWindow::dataChanged(const QModelIndex &top, const QModelIndex &bottom)
{
    if (top.row() <= currentRow_ && currentRow_ <= bottom.row())
        updateDetail();
}

void MainWindow::updateDetail()
{
    bool onValid = indexOnValiditem();

    if (onValid)
    {
        if (!ui_->nameLineEdit->hasFocus())
        {
            QString name = model_.data(currentIndex_, FruitListModel::nameRole).toString();
            ui_->nameLineEdit->setText(name);
        }

        if (!ui_->priceSpinBox->hasFocus())
        {
            double price = model_.data(currentIndex_, FruitListModel::priceRole).toDouble();
            ui_->priceSpinBox->setValue(price);
        }
    }
    else
    {
        ui_->nameLineEdit->setText("");
        ui_->priceSpinBox->setValue(0);
    }

    ui_->nameLineEdit->setEnabled(onValid);
    ui_->priceSpinBox->setEnabled(onValid);

    // Update Detail is also updating delete button state
    ui_->deleteButton->setEnabled(onValid);
}

void MainWindow::itemRemovalRequested()
{
    if (indexOnValiditem())
        model_.removeItem(currentRow_);
}

void MainWindow::rowsRemoved()
{
    int newModelRowCount = model_.rowCount();

    if (currentRow_ < newModelRowCount) // Current index was not on the last item,
        return;                         // the dataChanged signal will care about

    selectionChanged(model_.index(newModelRowCount - 1));
}

bool MainWindow::indexOnValiditem()
{
    if (currentRow_ < 0) return false;
    if (currentRow_ >= model_.rowCount()) return false;
    return true;
}
