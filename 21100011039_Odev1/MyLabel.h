#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>

class MyLabel : public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:
    void clicked(); // Label tıklandığında emit edilecek sinyal
};
#endif // MYLABEL_H
