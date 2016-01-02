/*
 * TODO:
 * More auto-generated code...
 *
 * 1) Fix formatting and namespacing
 * 2) Make sure the application is the consumers parent
 * 3) Listen for signal_dataAvailable
 * 4) If new data is available create a new consumer worker and let it handle the data
 *      Hint: QThreadPool
 *
 * Restictions:
 * Do not have just one worker idling around, waiting for data.
 * Once the workers are done, they shall perish.
 */

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
    void slot_spawnConsumer(QVariant data);
};
}

#endif // CONSUMER_H
