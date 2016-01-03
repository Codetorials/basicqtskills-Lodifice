#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRunnable>
#include <QVariant>
#include <QMutex>

namespace basicQt {

class Worker :
        public QObject,
        public QRunnable {
    Q_OBJECT

public:
    explicit Worker();
    virtual void run();
};

class ProducerWorker :
        public Worker {
    Q_OBJECT

public:
    explicit ProducerWorker();
    virtual void run() = 0;

signals:
    /**
     * @brief signal_deliverData will be emitted each time the ProducerWorker has created new data.
     * @param data the data that will be handed to the main producer object.
     */
    void signal_deliverData(QVariant data);

    /**
     * @brief signal_retire will be emitted once the ProducerWorker has no more data to produce.
     */
    void signal_retire();
};

/**
 * @brief The StringProducer class is a ProducerWorker creating the two strings 'foo' and 'bar'.
 */
class StringProducer :
        public ProducerWorker {
    Q_OBJECT

public:
    explicit StringProducer();
    void run();
};

/**
 * @brief The NumberProducer class is a ProducerWorker that generates a random number and counts
 * up to it, this number corresponds to the data created.
 */
class NumberProducer :
        public ProducerWorker {
    Q_OBJECT

public:
    explicit NumberProducer();
    void run();
};

class ConsumerWorker :
        public Worker {
    Q_OBJECT

public:
    explicit ConsumerWorker(QVariant data);
    virtual void run() = 0;

protected:
    QVariant m_data;
    static QMutex outputLock;
};

/**
 * @brief The BasicConsumer class is a ConsumerWorker that prints the consumed data as a string
 * to stderr.
 */
class BasicConsumer :
        public ConsumerWorker {
    Q_OBJECT

public:
    explicit BasicConsumer(QVariant data);
    void run();
};

/**
 * @brief The IterativeConsumer class models a ConsumerWorker that consumes a number and adds it
 * to a cumulated value which is then printed to the stderr.
 */
class IterativeConsumer :
        public ConsumerWorker {
    Q_OBJECT

public:
    explicit IterativeConsumer(QVariant data);
    void run();

private:
    static QMutex sumLock;
    static long unsigned sum;
};

}
#endif // WORKER_H
