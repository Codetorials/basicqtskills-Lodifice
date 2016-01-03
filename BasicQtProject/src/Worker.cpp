#include "include/Worker.h"

#include <iostream>

using namespace basicQt;

Worker::Worker():
    QObject(),
    QRunnable() {

    this->setObjectName("Basic Worker");
}

void Worker::run() {
    std::cerr << "Basic worker implementation does not do anything." << std::endl;
}

ProducerWorker::ProducerWorker():
    Worker() {
}

StringProducer::StringProducer():
    ProducerWorker() {

    this->setObjectName("String Producer");
}

void StringProducer::run() {
    emit this->signal_deliverData(QVariant("foo"));
    emit this->signal_deliverData(QVariant("bar"));
    emit this->signal_retire();
}

NumberProducer::NumberProducer():
    ProducerWorker() {

    this->setObjectName("Number Producer");
}

void NumberProducer::run() {
    unsigned count = qrand() % NumberProducer::maxNumber;
    for (unsigned i = 0; i < count; ++i) {
    }
    emit this->signal_deliverData(QVariant(count));
    emit this->signal_retire();
}

ConsumerWorker::ConsumerWorker(QVariant data):
    Worker(),
    m_data(data) {
}

QMutex ConsumerWorker::outputLock;

BasicConsumer::BasicConsumer(QVariant data):
    ConsumerWorker(data) {

    this->setObjectName("Basic Consumer");
}

void BasicConsumer::run() {
    ConsumerWorker::outputLock.lock();
    std::cerr << "Consumed string \"" << this->m_data.toString().toStdString() << "\"" << std::endl;
    ConsumerWorker::outputLock.unlock();
}

IterativeConsumer::IterativeConsumer(QVariant data):
    ConsumerWorker(data) {

    this->setObjectName("Iterative Consumer");
}

void IterativeConsumer::run() {
    IterativeConsumer::sumLock.lock();
    IterativeConsumer::sum += this->m_data.toUInt();
    ConsumerWorker::outputLock.lock();
    std::cerr << "Cumulated number to " << IterativeConsumer::sum << std::endl;
    ConsumerWorker::outputLock.unlock();
    IterativeConsumer::sumLock.unlock();
}

unsigned long IterativeConsumer::sum = 0;
QMutex IterativeConsumer::sumLock;
