#include <QCoreApplication>
#include "file.h"
#include "DataFile.h"
#include "sub.h"
#include <QTextStream>
#include <QFileInfo>
struct Sub{
    QVector<Subscriber*>	subscribers;
    void  add_subscriber();
    void  size();
    void delete_subscriber();
void connect();
void resign();
};

void Sub:: add_subscriber()
{

    QTextStream cin(stdin), cout(stdout);
    QString name;
    bool isAdd = false;//флаг сдежит за разрешением на добавление

    // Блок добавление подписчика
    while (!isAdd)
    {
        cout << '\t' << "Input subscriber: " << flush;
        name = cin.readLine();
        isAdd = true;

        // цикл по всем существующим подписчикам
        for (const auto& it : subscribers)
        {
            // Если такой подписчик уже существует, то нужно ввести другое имя
            if (it->getName() == name)
            {
                cout << "\t" << name << " no!" << endl;
                isAdd = false;
                break;
            }
        }

        // можем добавить
        if (isAdd)
             {
            if(name!="")
            {
                if (!name.isEmpty())
                {
                    subscribers.push_back(new Subscriber(name));
                    QTextStream(stdout) << "\t\tSubscriber " << name << " was added!" << endl;
                }
                else
                {
                    QTextStream(stdout) << "\t\tSubscriber was not added!" << endl;
                }
            }

        }
    }

    // выход

}
void  Sub::size()
{
    bool isSize = false;
QTextStream cin(stdin), cout(stdout);
    // Если подписчики есть
    if (!subscribers.isEmpty())
    {
       ///вывод подписчиков
            QTextStream(stdout) << "\tSUBSCRIBERS" << endl;
            qint32 i = 0;

            for (const auto& subscriber : subscribers)
                QTextStream(stdout) << "\t" << i++ << "      " << subscriber->getName() << endl;

       ///

        // Блок вывода размера журнала, на который подписан подписчик
        while (!isSize)
        {
            cout << "\tEnter the id of the subscriber from whom you want to find out the size of DataFile: " << flush;

            qint32 idSubscriber = cin.readLine().toInt();

            // Если ввели верный ID, то выполняем
            if (idSubscriber >= 0 && idSubscriber < subscribers.size())
            {
                // Если подписчик подписан на журнал, то выводим размер журнала, на который он подписан
                if (subscribers[idSubscriber]->subscribe())
                {
                    cout << "\t\tSize is " << QFileInfo(subscribers[idSubscriber]->getDataFile()).size() << " byte" << endl;
                    isSize = true;
                }
                else
                {
                    cout << "\t\tSubscriber has not DataFile!" << endl;
                    break;
                }
            }
            else
            {
                cout << "\t\tWrong id!" << endl;
            }
        }
    }
    else
    {
        cout << "\tNO SUBSCRIBES!" << endl;
    }
}
void Sub::delete_subscriber()
{
    QTextStream cin(stdin), cout(stdout);
    if (subscribers.isEmpty())
    {
        cout << "\tNO SUBSCRIBES!" << endl;
        return;
    }

    ///вывод подписчиков
         QTextStream(stdout) << "\tSUBSCRIBERS" << endl;
         qint32 i = 0;

         for (const auto& subscriber : subscribers)
             QTextStream(stdout) << "\t" << i++ << "      " << subscriber->getName() << endl;

    ///

    cout << "\t\tInput number of subcriber which you want to delete: " << flush;

    bool isDelete = false;

    // Блок удаления подписчика
    while (!isDelete)
    {
        qint32 idSubscriber = cin.readLine().toInt();

        // Если ID существует, то выполняем
        if (idSubscriber >= 0 && idSubscriber < subscribers.size())
        {
            // Вызываем сигнал удаления подписчика
          //  deleteSubscriber(idSubscriber);
///
            for (qint32 i = 0; i < subscribers.size(); ++i)
            {
                // Ищем индекс нужного подписчика, которого надо удалить
                if (i == idSubscriber)
                {
                    QTextStream(stdout) << "\t\t" << subscribers[i]->getName() << " was deleted!" << endl;

                    // Проходим по списку журналов
                    for (qint32 iMag = 0; iMag < FileCheck::instance().DataFiles.size(); ++iMag)
                    {
                        // Ищем у каждого журнала нашего подписчика
                        for (qint32 iSub = 0; iSub < FileCheck::instance().DataFiles[iMag]->getSubscribers().size(); ++iSub)
                        {
                            // Если мы нашли нашего подписчика у журнала, то выполняем
                            if (subscribers[idSubscriber]->getName() == FileCheck::instance().DataFiles[iMag]->getSubscribers()[iSub]->getName())
                            {
                                // Удаляем у журнала этого подписчика
                                FileCheck::instance().DataFiles[iMag]->getSubscribers().remove(iSub);
                                FileCheck::instance().DataFiles[iMag]->getCounter()--;
                            }
                        }
                    }

                    // Удаляем подписчика из вектора ( массива )
                    subscribers.remove(i);

                    break;
                }
            }
            ///
            isDelete = true;
        }
    }
}
void Sub::connect()
{
    bool isConnect = false;
 QTextStream cin(stdin), cout(stdout);
    // Функции, которые выводят подписчиков и журналы
  //  this->printshop();
   // this->printSubscribers();
    // Если список журналов пуст, то переходим на новую итерацию
     if (FileCheck::instance().DataFiles.isEmpty())
     {
         cout << "\tNO shopS!" << endl;
         return;
     }

     if (subscribers.isEmpty())
     {
         cout << "\tNO SUBSCRIBERS!" << endl;
         return;
     }

    // Блок связывания журнала и подписчика
     while (!isConnect)
       {
        qint32 idshop, idSubscriber;

        cout << "\tInput ID magazine which you want to connect: " << flush;

        idshop = cin.readLine().toInt();

        cout << "\tInput ID subscriber which you want to connect: " << flush;

        idSubscriber = cin.readLine().toInt();

        // Если ввели правильные IDs, то выполняем
        if ((idshop >= 0 && idshop < FileCheck::instance().DataFiles.size()) && (idSubscriber >= 0 && idSubscriber < subscribers.size()))
        {
            // Если подписчик не подписан, то подписываем его на журнал ( чтобы подписчик был подписан только на один журнал )
            if (!subscribers[idSubscriber]->subscribe())
            {
                // Вызываем сигнал связывания
               // connect(idshop, idSubscriber);
                ///
                if(idSubscriber!=0)
                    {
                        // Если выбранный подписчик не подписан, то выполняем
                        if (!subscribers[idSubscriber]->subscribe())
                        {
                            // Обращаемся к журналу, на который хотим подписаться и добавляем ему подписчика
                            FileCheck::instance().DataFiles[idshop]->addSubscriber(subscribers[idSubscriber]);
                            // Добавляем подписчику журнал
                            subscribers[idSubscriber]->getDataFile() = FileCheck::instance().DataFiles[idshop]->getName();

                            // Выставляем подписчику флаг, что он был подписан
                            subscribers[idSubscriber]->subscribe() = true;

                            QTextStream(stdout) << "\t\t" << FileCheck::instance().DataFiles[idshop]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
                        }
                        else
                        {
                            QTextStream(stdout) << "\t\tConnection error!" << endl;
                        }
                    }
                ///
                isConnect = true;
            }
            // Если подписчик уже подписан, то говорим об этом
            else
                cout << "\tSubscriber " << subscribers[idSubscriber]->getName() << " already a subscriber! " << subscribers[idSubscriber]->getDataFile() << endl;
        }
        else
        {
            cout << "\t" << "Error connect!" << endl;
        }
    }
}
void Sub::resign()
{
    QTextStream cin(stdin), cout(stdout);
    if (subscribers.isEmpty())
    {
        cout << "\tNO SUBSCRIBERS!" << endl;
        return;
    }

    if (FileCheck::instance().DataFiles.isEmpty())
    {
        cout << "\tNO shopS!" << endl;
        return;
    }

  //  this->printshop();
   // this->printSubscribers();

    cout << "\t\tInput number subscriber which you want to re-sign: " << flush;

    bool isResign = false;

    // Блок переподписки
    while(!isResign)
    {
        qint32 idSubscriber = cin.readLine().toInt();

        if (idSubscriber >= 0 && idSubscriber < subscribers.size())
        {
            cout << "\t\tInput the idshop which you want to subscribe to: " << flush;

            qint32 idshop = cin.readLine().toInt();

            if (idshop >= 0 && idshop < FileCheck::instance().DataFiles.size())
            {
                // Вызываем сигнал переподписки
              //  resign(idSubscriber, idshop);
                ///
                for (qint32 i = 0; i < subscribers.size(); ++i)
                {
                    // Находим ID подписчика, которого надо переподписать
                    if (i == idSubscriber)
                    {
                        // Если подписчик ещё не подписан, то выполняем
                        if (!subscribers[idSubscriber]->subscribe())
                        {
                            QTextStream(stdout) << "\t\tThe subscriber is not subscribed yet!" << endl;
                        }
                        else
                        {
                            // Проходим по всем журналам
                            for (qint32 mag = 0; mag < FileCheck::instance().DataFiles.size(); ++mag)
                            {
                                // Если нашли нужный журнал, то удаляем из подписки этого подписчика
                                if (FileCheck::instance().DataFiles[mag]->getName() == subscribers[idSubscriber]->getDataFile())
                                {
                                    for (qint32 sub = 0; sub < FileCheck::instance().DataFiles[mag]->getSubscribers().size(); ++sub)
                                    {
                                        if (FileCheck::instance().DataFiles[mag]->getSubscribers()[sub]->getName() == subscribers[idSubscriber]->getName())
                                        {
                                            FileCheck::instance().DataFiles[mag]->getSubscribers().remove(sub);
                                           FileCheck::instance().DataFiles[mag]->getCounter()--;
                                        }
                                    }
                                }
                            }

                            // Здесь подписываем на новый журнал
                            FileCheck::instance().DataFiles[idshop]->addSubscriber(subscribers[idSubscriber]);
                            subscribers[idSubscriber]->getDataFile() = FileCheck::instance().DataFiles[idshop]->getName();
                            subscribers[idSubscriber]->subscribe() = true;

                            QTextStream(stdout) << "\t\t" << FileCheck::instance().DataFiles[idshop]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
                        }
                    }
                }
                ///

                isResign = true;
            }
        }
    }
}
int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    Sub t;
QVector<Subscriber*>	subscribers;
    QTextStream cin(stdin), cout(stdout);
    cout<<"press the ENTER to see all the commands"<<endl;
    // Благодаря одиночке мы можем работать только с единственным экемпляром класса FileCheck
      // FileCheck::instance().TERMINAL();
   QVector<QString> com({
        "add subscriber",
        "add shop",
        "connect",
        "list",
        "size",
        "delete shop",
        "delete subscriber",
        "get counter",
        "resign",
        });
 FileCheck::instance();

    int s=0;
        while(s==0)
        {
           QString command;
           bool isCommand = false;

            // Блок отвечающий за ввод команд
            while (!isCommand)
            {
                // Выводим пользователю приглашение ввести команду ( flush - позволяет очистить буфер, чтобы вывести текст )
                // Считываем строкУ
               // command="add subscriber";
                cout << "Go to command: " << flush;

                command = cin.readLine();
                // Ищем в векторе команд введёную с консоли команду, если нашли флаг в true
                if(std::find(com.begin(), com.end(), command) != com.end())
                {
                    isCommand = true;
                }
                else
                {
                    isCommand = false;
                }

                // Если мы не нашли команду , то выходим и заново в цикл ожидать команду
                if (!isCommand && command.isEmpty())
                {
                    break;
                }
            }

            // add subscriber добавление подписчика в мэин

            if (command == com[0])
            {
//следим за 1 файлои мз фм, сделать проверку и обход по фм если такого нет то ошибочка
           t.add_subscriber();
            //QObject::connect(&com[0], SIGNAL(salaryChanged(int)), SLOT(add_subscriber));
                // выход
                continue;
            }

            // добавление файла add shop
            if (command == com[1])
            {
                QString path;
              FileCheck::instance().add_DataFile();


                continue;
            }

            // connect
            if (command == com[2])
            {

   t.connect();
                continue;
            }

            // список файлов
            if (command == com[3])
            {
FileCheck::instance().list();
   // list();
                continue;
            }

            // список подписчиков
            if (command == com[4])
            {

   t.size();
                continue;
            }

            // удаление файлов
            if (command == com[5])
            {
FileCheck::instance().delete_DataFile();
   // delete_shop();
                continue;
            }

            // delete subscriber
            if (command == com[6])
            {

    t.delete_subscriber();
                continue;
            }

            // get counter
            if (command == com[7])
            {
                //get_counter();

                continue;
            }

            // resign ( переподписка )
            if (command == com[8])
            {

    t.resign();
                continue;
            }

        }

        QCoreApplication::exec();

}
