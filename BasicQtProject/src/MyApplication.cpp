#include "MyApplication.h"

#include <iomanip>
#include <iostream>

#include <QStringList>
#include <QTime>

using namespace basicQt;

MyApplication::MyApplication(int argc, char** argv):
    QCoreApplication(argc, argv),
    m_consumer(this),
    m_producer(this) {

    this->setObjectName("My Application");
    this->setApplicationName("A basic Qt application");
    this->setApplicationVersion("v2015.12.18");
    this->setOrganizationName("GWT-TUD");

    QObject::connect(&this->m_producer, &Producer::signal_dataProduced, this, &MyApplication::signal_dataAvailable);
    QObject::connect(&this->m_producer, &Producer::signal_workDone, this, &MyApplication::slot_producerFinished);
    QObject::connect(this, &MyApplication::signal_producersRequired, &this->m_producer, &Producer::slot_spawnProducers);
    QObject::connect(this, &MyApplication::signal_dataAvailable, &this->m_consumer, &Consumer::slot_spawnConsumer);

    this->parseCommandLineArguments();
}

void MyApplication::parseCommandLineArguments() {
    std::cerr << "Here are your command line arguments:" << std::endl;

    unsigned counter = 0;
    for (auto argument : this->arguments()) {
        std::cerr << std::setw(3) << std::right << counter << " : " << argument.toStdString() << std::endl;
        counter++;
    }
}

void MyApplication::setup() {
    qsrand(QTime::currentTime().msec());

    for (unsigned i = 0; i < this->m_minProducerCount; ++i) {
        emit this->signal_producersRequired();
    }
}

void MyApplication::slot_producerFinished() {
    if (this->m_producer.workerCount() < this->m_minProducerCount) {
       emit this->signal_producersRequired();
    }
}
