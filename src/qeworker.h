#ifndef QEWORKER_H
#define QEWORKER_H

#include <QObject>

class QEWorker : public QObject {
    Q_OBJECT
public:
    QEWorker() : QObject() {}
    virtual ~QEWorker() {};
signals:
    void requestWork();
    void workDone(QEWorker*);
};

#endif // QEWORKER_H
