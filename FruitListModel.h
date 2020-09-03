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

    enum ItemDataRoles {
        nameRole = Qt::DisplayRole,
        priceRole = Qt::UserRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    QVariantMap get(int i) const;
    void setName(int i, QString name);
    void setPrice(int i, double price);
    void addItem();
    void removeItem(int i);

    void inflatePrices();

private:
    QList<Fruit> fruitList_;

    bool inBounds(int i) const;
};
#endif // FRUITLISTMODEL_H
