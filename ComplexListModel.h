#include <QAbstractListModel>

struct Vector2f {
    Q_GADGET

public:
    Q_PROPERTY(float x MEMBER x)
    Q_PROPERTY(float y MEMBER y)

public:
    float x;
    float y;
};

class ComplexListModel : public QAbstractListModel {
    Q_OBJECT

private:
    std::vector<Vector2f> points;

    enum Role {
        DataRole = Qt::UserRole,
    };

public:
    explicit ComplexListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {
        points.emplace_back(Vector2f { 0.5f, 1.0f });
        points.emplace_back(Vector2f { 2.5f, 2.0f });
        points.emplace_back(Vector2f { 4.5f, 3.0f });
        points.emplace_back(Vector2f { 5.5f, 4.0f });
        points.emplace_back(Vector2f { 6.5f, 5.0f });
    }

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return (int)points.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        switch(role) {
            case Qt::DisplayRole:
                break;
    
            case DataRole:
                return QVariant::fromValue(points.at(index.row()));

            default: break;
        }

        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            { DataRole, "data" },
        };
    }

public:
    Q_INVOKABLE void addPoint(float x, float y) {
        int idx = rowCount();
        beginInsertRows(QModelIndex(), idx, idx);
        points.emplace_back(Vector2f { x, y });
        endInsertRows();
    }
};

