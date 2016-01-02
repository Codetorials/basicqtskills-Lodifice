/*
 * TODO TASK:
 * Properly subclass this into producer and consumer worker classes.
 * Each of these can have different strategies how to do stuff.
 *
 * All data passed between workers are by convention of the type QVariant.
 *
 * Producer worker examples:
 * - ConstantStringProducer (just produces --- you guessed it...)
 * - CounterProducer (counts up a number and issues it as data)
 * - JsonProducer (produces a QJsonObject)
 *
 * Consumer worker examples:
 * - PrintConsumer (Just prints, what it gets)
 * - FileConsumer (Appends everything it gets to a file)
 * - SumConsumer (Filters out the numbers and sums them up)
 *
 * General consideration:
 * How to set up signals and slots?
 * How to deal with different content types of QVariant?
 * How to keep information alive over multiple runs of the same consumer?
 * (Multiple solutions are possible)
 */

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

    /*
     * This method is inherited from QRunnable and will be executed in a seperate thread.
     * Override this to achieve some actual results.
     * Remember to use some proper locking if necessary.
     */
    virtual void run();
};

class ProducerWorker :
        public Worker {
    Q_OBJECT

public:
    explicit ProducerWorker();
    virtual void run() = 0;

signals:
    void signal_deliverData(QVariant data);
    void signal_retire();
};

class StringProducer :
        public ProducerWorker {
    Q_OBJECT

public:
    explicit StringProducer();
    void run();
};

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

class BasicConsumer :
        public ConsumerWorker {
    Q_OBJECT

public:
    explicit BasicConsumer(QVariant data);
    void run();
};

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
