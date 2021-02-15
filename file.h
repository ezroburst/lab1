
#ifndef FILE__H
#define FILE__H

#include <QObject>

class Shop;
class Subscriber;

class FileCheck final : public QObject
{
    Q_OBJECT

public:
    ~FileCheck();

    // Функция "взывать". Она возвращает ссылку на единственный объекьт класса FileManager
    static FileCheck& instance();
void add_subscriber();
 void add_shop();
void connect();
void list();
void size();
void delete_shop();
void delete_subscriber();
void get_counter();
void resign();

    // Сигнал добавления журнала
    void addshop(const QString& path);

    // Сигнал добавления подписчика
     void addSubscriber(const QString& name);

    // Сигнал связывания журнала и подписчика
    void connect(const qint32& idshop, const qint32& idSubscriber);

    // Сигнал удаления журнала
     void deleteshop(const qint32& index);

    // Сигнал удаления подписчика
    void deleteSubscriber(const qint32& index);

    // Сигнал, который вызывает функцию у журнала ( счётчик подписчиков )
     void getCounter(const qint32& index);

    // Сигнал переподписки подписчика
     void resign(const qint32& idSubscriber, const qint32& idshop);

  //  void TERMINAL();
QVector<Shop*>		shops;
private:
    explicit FileCheck();
    void printshop();
    void printSubscribers();

    private:

    QVector<Subscriber*>	subscribers;
    QVector<QString>		com;
};

#endif // FILE__H
