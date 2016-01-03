#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QVariant>
#include <QThreadPool>

namespace basicQt {

class Consumer :
        public QObject {
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = 0);

private:
    QThreadPool m_workers;

signals:

public slots:
    /**
     * @brief slot_spawnConsumer will be called by the main application whenever there is data
     * to be consumed and create a consumer worker for that task.
     * @param data the data that will be handed to the new consumer.
     */
    void slot_spawnConsumer(QVariant data);
};
}

#endif // CONSUMER_H
