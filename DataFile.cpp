#include "DataFile.h"
#include "sub.h"
#include<QTextStream>
DataFile::DataFile(const QString& name) :
    name(name), counter(0)
{
}

QString DataFile::getName() const
{
    return name;
}

void DataFile::addSubscriber(Subscriber* subscriber)
{
    subscribers.push_back(subscriber);
    ++counter;
}

QVector<Subscriber*>& DataFile::getSubscribers()
{
    return subscribers;
}

qint32& DataFile::getCounter()//кол во
{
    return counter;
}


