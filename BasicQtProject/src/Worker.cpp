#include "include/Worker.h"

#include <iostream>
#include <QTextStream>

using namespace basicQt;

Worker::Worker():
    QObject(),
    QRunnable() {

    this->setObjectName("Basic Worker");
}

void Worker::run() {
    QTextStream(stdout) << "Basic worker implementation does not do anything." << endl;
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
    QTextStream(stdout) << "Consumed string \"" << this->m_data.toString() << "\"" << endl;
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
    QTextStream(stdout) << "Cumulated number to " << IterativeConsumer::sum << endl;
    ConsumerWorker::outputLock.unlock();
    IterativeConsumer::sumLock.unlock();
}

unsigned long IterativeConsumer::sum = 0;
QMutex IterativeConsumer::sumLock;
