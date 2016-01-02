#include "include/Producer.h"
#include "include/Worker.h"

#include <QThreadPool>

using namespace basicQt;

Producer::Producer(QObject *parent) : QObject(parent) {
    this->setParent(parent);
}

unsigned Producer::workerCount() {
    return this->m_workers.activeThreadCount();
}

void Producer::slot_spawnProducers() {
    ProducerWorker *producer;
    if (qrand() % 2) {
        producer = new StringProducer;
    } else {
        producer = new NumberProducer;
    }
    QObject::connect(producer, SIGNAL(signal_deliverData(QVariant)), this, SIGNAL(signal_dataProduced(QVariant)));
    QObject::connect(producer, SIGNAL(signal_retire()), this, SIGNAL(signal_workDone()));
    this->m_workers.start(producer);
}
