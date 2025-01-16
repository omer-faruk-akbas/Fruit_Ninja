#ifndef DIALOG_H
#define DIALOG_H

#include "qobjectdefs.h"
#include <QDialog>
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void Karpuzdusur();
    void KarpuzHaraket();
    void konum_bul();
    void KarpuzSil();
    void BombaSil();
    void HediyeSil();
    void Skorlar();
    void kaydet();
    void Bombadusur();
    void BombaHaraket();
    void Ulti();
    void Tiklandi(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Dialog *ui;


};
#endif // DIALOG_H
