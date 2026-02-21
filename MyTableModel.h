#include <qqml.h>

#include <QAbstractTableModel>

class MyTableModel : public QAbstractTableModel {
    Q_OBJECT
    QML_ELEMENT
    
private:
    std::vector<int> elements;
    
public:
    explicit MyTableModel(QObject *parent = nullptr) {
        elements = { 5, 10, 15, 20, 25 };
    }

public:

    int rowCount(const QModelIndex &index = QModelIndex()) const override {
        return (int)elements.size();
    }
    
    int columnCount(const QModelIndex &index = QModelIndex()) const override {
        return 1;
    }
    
    QVariant data(const QModelIndex &index, int role) const override {
        switch (role) {
            case Qt::DisplayRole:
            return QString("%1 = %2").arg(index.row()).arg(elements[index.row()]);
            default:
            break;
        }
        
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            { Qt::DisplayRole, "display" },
        };
    }
};
