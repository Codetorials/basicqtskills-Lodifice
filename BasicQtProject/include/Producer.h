#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QVariant>
#include <QThreadPool>

namespace basicQt {

class Producer :
        public QObject {
    Q_OBJECT
public:
    explicit Producer(QObject *parent = 0);

    /**
     * @brief workerCount returns the current number of active producers.
     * @return the number of active workers int the QThreadPool m_workers.
     */
    unsigned workerCount();

private:
    QThreadPool m_workers;

signals:
    /**
     * @brief signal_workDone will be emitted when a producer has stopped producing data.
     */
    void signal_workDone();

    /**
     * @brief signal_dataProduced will be emitted when a producer worker has produced new data.
     * @param data the data that are handed to the main application.
     */
    void signal_dataProduced(QVariant data);

public slots:
    /**
     * @brief slot_spawnProducers will be called by the main application when there are not enough
     * producer workers running and create new ones.
     */
    void slot_spawnProducers();
};
}

#endif // PRODUCER_H
