#include "file.h"
#include "DataFile.h"
#include "sub.h"

#include <QTextStream>
#include <QFileInfo>
#include <thread>
#include <QTimer>

FileCheck::~FileCheck()
{
//    for (const auto& it : subscribers)
//        delete it;

    for (const auto& it : DataFiles)
        delete it;
}

FileCheck& FileCheck::instance()
{
    static FileCheck obj;
    return obj;
}

void FileCheck::printDataFile()
{
    QTextStream(stdout) << "\tDataFileS" << endl;
    qint32 i = 0;

    for (const auto&DataFile : DataFiles)
        QTextStream(stdout) << "\t" << i++ << "      " << DataFile->getName() << endl;
}


 QTextStream cin(stdin), cout(stdout);

 void FileCheck:: add_DataFile()
{
    QString path;
    bool isAdd = false;

    // Блок добавления журнала
    while (!isAdd)
    {
        cout << '\t' << "Input DataFile: " << flush;
        path = cin.readLine();
        isAdd = true;

        for (const auto& it : DataFiles)
        {
           if (it->getName() == path)
            {
                cout << "\t" << path << " exists!" << endl;
                isAdd = false;
                break;
            }
        }

        // Если путь не пустой
        if (!path.isEmpty() && isAdd)
        {
             addDataFile(path);
            isAdd = true;
        }
    }
}

void FileCheck::list()//список файлов
{
    // Если список журналов не пуст, то выводим их
    if (!DataFiles.isEmpty())
    {
        this->printDataFile();
    }
    else
    {
        cout << "\tNO DataFileS!" << endl;
    }

//    // Если список подписчиков не пуст, то выводим их
//    if (!subscribers.isEmpty())
//    {
//        this->printSubscribers();
//    }
//    else
//    {
//        cout << "\tNO SUBSCRIBERS!" << endl;
//    }
}

void FileCheck::delete_DataFile()
{
    // Если список журналов пуст, то переходим на новую итерацию
    if (DataFiles.isEmpty())
    {
        cout << "\tNO DataFileS!" << endl;
        return;;
    }

    this->printDataFile();

    cout << "\t\tInput number DataFile which you want to delete: " << flush;

    bool isDelete = false;

    // Блок удаления журнала из вектора ( массива )
    while (!isDelete)
    {
        // toInt из QString делает Int
        qint32 idDataFile = cin.readLine().toInt();

        // Если введённый ID существует, то выполняем
        if (idDataFile >= 0 && idDataFile < DataFiles.size())
        {
            // Вызываем синал удаления журнала
             deleteDataFile(idDataFile);

            isDelete = true;
        }
    }
}

void FileCheck::get_counter()
{
    if (DataFiles.isEmpty())
    {
        cout << "\tNO DataFileS!" << endl;
        return;
    }

    this->printDataFile();

    cout << "\t\tInput number DataFile which you want to know counter: " << flush;

    bool isCounter = false;

    // Блок возврата количества подписчиков у журнала
    while (!isCounter)
    {
        qint32 idDataFile = cin.readLine().toInt();

        if (idDataFile >= 0 && idDataFile < DataFiles.size())
        {
            // Вызываем сигнал, который выведет число подписчиков у журнала
             getCounter(idDataFile);

            isCounter = true;
        }
    }
}



void FileCheck::addDataFile(const QString& path)
      {
    if(path!="")
    {
          // Если журнал(путь) существует и он файл
//          if (QFileInfo(path).exists() && QFileInfo(path).isFile())
//          {
              DataFiles.push_back(new DataFile(path));
              QTextStream(stdout) << "\t\tDataFile " << path << " was added!" << endl;
//          }
//          else
//          {
//              QTextStream(stdout) << "\t\tPath to DataFile was not added!" << endl;
//          }
      }
}


void FileCheck::deleteDataFile(const qint32& index)
    {
        for (qint32 i = 0; i < DataFiles.size(); ++i)
        {
            // Находим нужный индекс журнала, который надо удалить
            if (i == index)
            {
                QTextStream(stdout) << "\t\t" <<DataFiles[i]->getName() << " was deleted!" << endl;

                // Проходимся по всем подписчикам, и удаляем у этих подписчиков этот журнал
                for (const auto& subscriber : DataFiles[i]->getSubscribers())
                {
                    subscriber->getDataFile().clear();
                    subscriber->subscribe() = false;
                }

                // Удаляем журнал из вектора ( массива )
                DataFiles.remove(i);

                break;
            }
        }
    }

void FileCheck::getCounter(const qint32& index)
    {
        for (qint32 i = 0; i < DataFiles.size(); ++i)
        {
            // Находим нужный индекс магазина
            if (i == index)
            {
                QTextStream(stdout) << "\t\tCounter " << DataFiles[i]->getName() << " is equal " << DataFiles[i]->getCounter() << endl;
                break;
            }
        }
    }

FileCheck::FileCheck() :
    QObject(nullptr),
    com({
        "add subscriber",
        "add shop",
        "connect",
        "list",
        "size",
        "delete shop",
        "delete subscriber",
        "get counter",
        "resign",
        })
{

//    QString path;
//    addshop( path);

//const QString name;
////addSubscriber( name);

//const qint32& idshop=0;
//const qint32& idSubscriber=0;
//connect(idshop,idSubscriber);

//const qint32& inde=0;
//deleteshop( inde);

//const qint32& index=0;
////deleteSubscriber( index);

//const qint32& index1=0;
//getCounter(index1);

//const qint32& idSubscriber1=0;
//const qint32& idshop1=0;
//resign( idSubscriber1, idshop1);


}

