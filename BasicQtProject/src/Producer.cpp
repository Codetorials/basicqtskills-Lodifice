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
    QObject::connect(producer, &ProducerWorker::signal_deliverData, this, &Producer::signal_dataProduced);
    QObject::connect(producer, &ProducerWorker::signal_retire, this, &Producer::signal_workDone);
    this->m_workers.start(producer);
}
