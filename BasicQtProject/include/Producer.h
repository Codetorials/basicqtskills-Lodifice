
/*
 * TODO:
 * Oh, dear.
 * This has been auto-generated and looks terrible.
 * (Don't forget the implementation file, press [F4] to get there)
 *
 * 1) Properly format the code
 * 2) Add the namespace "basic_qt"
 * 3) Add a QThreadPool in which to run your workers
 * 4) Implement the method below to get the number of currently active producer workers
 * 5) Make sure that the application is the producers parent.
 * 6) Add a slot which will listen for the applications signal_producersRequired and launches a new producer worker
 *      If you have multiple implementations of the producer worker, launch a random one.
 * 7) If a producer worker finishes, emit a signal which connects to the applications slot_producerFinished
 * 8) If a producer worker has created some data, pass it on to the applications signal_dataAvailable
 * 9) Make sure, all producer workers get shut down upon destruction. Disconnect relevant signals first.
 *
 * Note:
 * A producer worker may produce multipe data items.
 * You can connect signals to other signals
 */


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

    // TODO implement this
    unsigned workerCount();

private:
    QThreadPool m_workers;

signals:
    void signal_workDone();
    void signal_dataProduced(QVariant data);

public slots:
    void slot_spawnProducers();
};
}

#endif // PRODUCER_H
