#ifndef FRUITLISTMODEL_H
#define FRUITLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

struct Fruit {
    QString name;
    double price;
};

class FruitListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    FruitListModel(QObject *parent = nullptr);

    enum {
        nameRole = Qt::DisplayRole,
        priceRole = Qt::UserRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QVariantMap get(int i) const;
    Q_INVOKABLE void setName(int i, QString name);
    Q_INVOKABLE void setPrice(int i, double price);
    Q_INVOKABLE void addItem();
    Q_INVOKABLE void removeItem(int i);

    void inflatePrices();

private:
    QList<Fruit> fruitList_;

    bool inBounds(int i) const;
};
#endif // FRUITLISTMODEL_H
