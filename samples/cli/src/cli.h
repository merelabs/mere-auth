#ifndef CLI_H
#define CLI_H

#include <QObject>

class Cli : public QObject
{
    Q_OBJECT
public:
    explicit Cli(QObject *parent = nullptr);

public slots:
    void run();

signals:
    void done();
};

#endif // CLI_H
