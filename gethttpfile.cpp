#include "gethttpfile.h"

getHttpFile::getHttpFile( QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &getHttpFile::onResult);

}

void getHttpFile::getData(){
    QUrl url("http://kappa.cs.petrsu.ru/~simagin/web/"+curFile);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void getHttpFile::onResult(QNetworkReply *reply){
    if(reply->error()){
        qDebug() << "Error";
        qDebug() << reply->errorString();
    } else {
        QByteArray data = reply->readAll();
        QFile file("E://qt_creator//projects//123//123//webFiles//"+curFile);
        if(file.open(QIODevice::WriteOnly)){
            file.write(data);
            file.close();
        }
        emit onReady();
    }

}
