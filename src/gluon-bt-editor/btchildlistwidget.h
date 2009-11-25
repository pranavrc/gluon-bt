#ifndef BTCHILDLISTWIDGET_H
#define BTCHILDLISTWIDGET_H

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>

class btChildListWidget : public QWidget 
{
    Q_OBJECT
public:
    btChildListWidget(QWidget * parent = 0);
    ~btChildListWidget();
    
    void setChildProbabilites(QObject * object);
    
private:
    QVBoxLayout*        childLayout;    
};

#endif