#include "include/Consumer.h"
#include "include/Worker.h"

#include <iostream>

using namespace basicQt;

Consumer::Consumer(QObject *parent) : QObject(parent) {
    this->setParent(parent);
}

void Consumer::slot_spawnConsumer(QVariant data) {
    ConsumerWorker *consumer;
    switch (data.type()) {
    case QMetaType::UInt: consumer = new IterativeConsumer(data); break;
    default: consumer = new BasicConsumer(data);
    }
    this->m_workers.start(consumer);
}
