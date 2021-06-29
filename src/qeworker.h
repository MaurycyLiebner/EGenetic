#ifndef QEWORKER_H
#define QEWORKER_H

#include <QObject>

#include "egenetic_global.h"

class EGENETIC_EXPORT QEWorker : public QObject {
    Q_OBJECT
public:
    QEWorker() : QObject() {}
    virtual ~QEWorker() {};
signals:
    void requestWork();
    void workDone(QEWorker*);
};

#endif // QEWORKER_H
