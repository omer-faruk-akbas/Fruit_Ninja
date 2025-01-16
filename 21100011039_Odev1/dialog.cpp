#include "dialog.h"
#include "qlabel.h"
#include "ui_dialog.h"
#include <qtimer.h>
#include <qfile.h>
#include <stdlib.h>
#include <qmessagebox.h>
QTimer *zaman=new QTimer();
QTimer *zaman1=new QTimer();
QTimer *zaman2=new QTimer();
QTimer *zaman3=new QTimer();
QTimer *zaman4=new QTimer();
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    ui->setupUi(this);
    //Ekranın boyutunu bilgisayar ekranı kadar yaptım.
    QLabel *arka_plan=new QLabel(this);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->setGeometry(screenGeometry);

    //arka plan boyutunu ayarladım.
    //arka_plan->setGeometry(0,200,this->width(),this->height());
    arka_plan->setGeometry(0,200,screenGeometry.width(),screenGeometry.height());
    QPixmap resim(":/new/prefix1/images/back.jpg");
    arka_plan->setPixmap(resim);
    arka_plan->show();

    //Dosyadaki konumları okuma işlemi yapılıyor.
    konum_bul();
    //Dosyadaki skorları okuma işlemi yapılıyor. Ve en yüksek skor tespit ediliyor.
    Skorlar();

    //Karpuzlar konumlarda oluşturuluyor.
    connect(zaman, &QTimer::timeout, this, &Dialog::Karpuzdusur);
    zaman->setInterval(500);
    zaman->start();

    //Karpuzların aşağı doğru inmesi için kullandığımız zamanlayıcı
    connect(zaman1, &QTimer::timeout, this, &Dialog::KarpuzHaraket);
    zaman1->setInterval(5);
    zaman1->start();

    //Silinecek karpuzlar için zamanlayıcı ayarı.
    connect(zaman2, &QTimer::timeout, this, &Dialog::KarpuzSil);
    zaman2->setInterval(750);
    zaman2->start();

    //Ekrana tıklanma sinyali oluştuğu zaman Tiklandi fonksiyonunu çalıştırıyor.
    connect(this,&Dialog::mousePressEvent, this, &Dialog::Tiklandi);

    //Bomba düşürme zamanlayıcısı.
    connect(zaman3, &QTimer::timeout, this, &Dialog::Bombadusur);
    zaman3->setInterval(4000);
    zaman3->start();

    //Bomba Haraket zamanlayıcısı.Ekranda patlamayan her bomba haraket ediyor.
    //Silinecek bombalar için zamanlayıcı ayarı.
    connect(zaman4, &QTimer::timeout, this, &Dialog::BombaSil);
    connect(zaman4, &QTimer::timeout, this, &Dialog::HediyeSil);
    connect(zaman4, &QTimer::timeout, this, &Dialog::BombaHaraket);
    zaman4->setInterval(2600);
    zaman4->start();



}
QList<QString> konumlar;
QList<QLabel *> karpuzlar;
QList<QLabel *> bombalar;
QList<QLabel *> hediye_kutu;
QList<QLabel *> Silinecek_hediye_kutu;
QList<QLabel *> Silinecek_karpuzlar;
QList<QLabel *> Silinecek_bombalar;
float kalan_zaman=30.0;
int kacan_karpuz=0;
int kesilen_karpuz=0;
int saniye=0;
int hediye=0;
int hak=1;
int en_yukek_skor=0;
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::KarpuzHaraket()
{
      foreach (QLabel *karpuz ,karpuzlar) {
            karpuz->setGeometry(karpuz->x(),karpuz->y()+1,karpuz->width(),karpuz->height());

          if(karpuz->y() > this->height())
            {
                kacan_karpuz++;
                ui->kacan_karpuz->setText(QString("Kaçırılan Karpuz Sayısı: <font color=red>%1</font>").arg(kacan_karpuz));
                karpuz->clear();
                karpuzlar.remove(karpuzlar.indexOf(karpuz));
            }
        }

}

void Dialog::KarpuzSil()
{
    //Eğer silinecek karpular listesi boş değilse her 600 milisaniyede bir ilk elemanı siliyor ve ekrandan temizliyor.
     if(!Silinecek_karpuzlar.isEmpty())
     {
            Silinecek_karpuzlar.first()->clear();
            Silinecek_karpuzlar.removeFirst();

     }
}


void Dialog::Karpuzdusur()
{

    QLabel *karpuz=new QLabel(this);
    QPixmap resim(":/new/prefix1/images/karpuz.png");
    //Karpuz resminin boyutunu oran olarak küçülttüm.
    QPixmap kücültülmüsResim = resim.scaled(80, 80, Qt::KeepAspectRatio);

    //Karpuzun oluşacak kordinatını rastgele olarak seçtim
    int random=rand()%konumlar.size();
    QString kordinat = konumlar[random];

    // Seçilen kordinatı x ve y eksenleri için ayırdım.
    QStringList x_y=kordinat.split(" ");
    karpuz->setPixmap(kücültülmüsResim);

    karpuz->setGeometry(x_y[0].toInt(),x_y[1].toInt()+100,kücültülmüsResim.width(),kücültülmüsResim.height());
    karpuz->show();
    //karpuzlar listesine karpuzu ekliyoruz.
    karpuzlar.append(karpuz);

    //zaman 500 milisaniyede bir azaldığı için ekranda sadece tam değerler basılcak şekilde ayarlandı.
    kalan_zaman-=0.5;
    saniye++;
    hediye++;
    if(saniye==2)
    {
        ui->sure->setText(QString("Süre: <font color=green>%1</font>").arg(kalan_zaman));
        saniye=0;
    }
    //Her 8 saniyede bir hediye kutu oluşturuyoruz.
    if(hediye==16)
    {
        QLabel *kutu=new QLabel(this);
        QPixmap resim(":/new/prefix1/images/hediye.png");
        QPixmap kücültülmüsResim = resim.scaled(90, 90, Qt::KeepAspectRatio);
        int random=rand()%konumlar.size();
        QString kordinat = konumlar[random];
        QStringList x_y=kordinat.split(" ");
        kutu->setPixmap(kücültülmüsResim);
        kutu->setGeometry(x_y[0].toInt(),x_y[1].toInt()+100,kücültülmüsResim.width(),kücültülmüsResim.height());
        kutu->show();
        hediye_kutu.append(kutu);
        hediye=0;
    }
    if (kalan_zaman <= 0) {
        zaman->stop();
        zaman1->stop();
        zaman2->stop();
        zaman3->stop();
        zaman4->stop();
        if(kesilen_karpuz>en_yukek_skor)
        {
            QMessageBox::information(this,"Bigi!",QString("OYUN BİTTİ\nTebrikler maksimum skor sizde!\nKesilen Karpuz Sayısı:%1\nKaçırılan Karpuz Sayısı:%2\nEn yüksek skor: %3").arg(kesilen_karpuz).arg(kacan_karpuz).arg(en_yukek_skor));
        }
        else
        {

            QMessageBox::information(this,"Bigi!",QString("OYUN BİTTİ\nMaksimum skoru geçemediniz!\nKesilen Karpuz Sayısı:%1"
                                                            "\nKaçırılan Karpuz Sayısı:%2"
                                                            "\nEn yüksek skor: %3").arg(kesilen_karpuz).arg(kacan_karpuz).arg(en_yukek_skor));
        }
        kaydet();
        this->close();
    }
}

void Dialog::konum_bul() {

    QFile dosya("konumlar.txt");

    if (!dosya.open(QIODevice::ReadOnly)) {
        qDebug()<<"Dosya açma hatası";
        return;
    }

    QTextStream stream(&dosya);
    while(!stream.atEnd()){
        QString satir=stream.readLine();
        konumlar.append(satir);
    }
    dosya.close();
}

void Dialog::Tiklandi(QMouseEvent *event) {
    // Tıklanan koordinatları alın
    int x = event->x();
    int y = event->y();

    foreach (QLabel *karpuz ,karpuzlar) {

       if (karpuz->geometry().contains(QPoint(x, y)))
        {
            kesilen_karpuz++;
            QPixmap resim(":/new/prefix1/images/dilim_karpuz.png");
            QPixmap kücültülmüsResim = resim.scaled(80, 80, Qt::KeepAspectRatio);
            karpuz->setPixmap(kücültülmüsResim);
            //Tıklanan karpuzu karpuzlar listesinden silip silineceklere ekledik.
            karpuzlar.remove(karpuzlar.indexOf(karpuz));
            Silinecek_karpuzlar.append(karpuz);
            ui->kesilen->setText(QString("Kesilen Karpuz Sayısı: <font color=blue>%1</font>").arg(kesilen_karpuz));
        }
    }

    foreach (QLabel *bomba ,bombalar) {

        if (bomba->geometry().contains(QPoint(x, y)))
        {
            kesilen_karpuz-=3;
            QPixmap resim(":/new/prefix1/images/duman.png");
            QPixmap kücültülmüsResim = resim.scaled(250, 250, Qt::KeepAspectRatio);
            bomba->setPixmap(kücültülmüsResim);
            bomba->setFixedWidth(250);
            bomba->setFixedHeight(250);
            //Tıklanan bombayı bombalar listesinden sildik ve silinenlere ekleyip duman efekti verdik.
            bombalar.remove(bombalar.indexOf(bomba));
            Silinecek_bombalar.append(bomba);
            ui->kesilen->setText(QString("Kesilen Karpuz Sayısı: <font color=blue>%1</font>").arg(kesilen_karpuz));
        }
    }

    foreach (QLabel *kutu ,hediye_kutu) {

        if (kutu->geometry().contains(QPoint(x, y)))
        {
            int random=rand()%3;
            if(random==0)
            {
                //Ekrandaki tüm karpuzları kesiyor.
                Ulti();
                kutu->hide();
                hediye_kutu.remove(hediye_kutu.indexOf(kutu));
                Silinecek_hediye_kutu.append(kutu);

            }
            else if(random==1)
            {
                // +5 saniye süre ekleniyor.
                QPixmap resim(":/new/prefix1/images/+5 time.png");
                QPixmap kücültülmüsResim = resim.scaled(100, 100, Qt::KeepAspectRatio);
                kutu->setPixmap(kücültülmüsResim);
                kutu->setFixedWidth(100);
                kutu->setFixedHeight(100);
                hediye_kutu.remove(hediye_kutu.indexOf(kutu));
                Silinecek_hediye_kutu.append(kutu);
                kalan_zaman+=5;

            }
            else if(random==2)
            {
                // 5 saniye süre azaliyor.
                QPixmap resim(":/new/prefix1/images/-5 time.png");
                QPixmap kücültülmüsResim = resim.scaled(100, 100, Qt::KeepAspectRatio);
                kutu->setPixmap(kücültülmüsResim);
                kutu->setFixedWidth(100);
                kutu->setFixedHeight(100);
                hediye_kutu.remove(hediye_kutu.indexOf(kutu));
                Silinecek_hediye_kutu.append(kutu);
                kalan_zaman-=5;

            }
        }
    }

}
void Dialog::mousePressEvent(QMouseEvent *event) {
    emit Tiklandi(event);
}


//kendi eklediğim fonksiyon.
//Her 4 saniyede bir bomba oluşturuyoruz bu bombalara tıklanırsa skor 3 puan azalıyor.
void Dialog::Bombadusur()
{
    QLabel *bomba=new QLabel(this);
    QPixmap resim(":/new/prefix1/images/bomba.png");
    //Bomba resminin boyutunu oran olarak küçülttüm.
    QPixmap kücültülmüsResim = resim.scaled(120, 120, Qt::KeepAspectRatio);
    //Bomba oluşacak kordinatını rastgele olarak seçtim
    int random=rand()%konumlar.size();
    QString kordinat = konumlar[random];
    // Seçilen kordinatı x ve y eksenleri için ayırdım.
    QStringList x_y=kordinat.split(" ");
    bomba->setPixmap(kücültülmüsResim);
    bomba->setGeometry(x_y[0].toInt(),x_y[1].toInt()+100,120,120);
    bomba->show();
    bombalar.append(bomba);
}
void Dialog::BombaHaraket()
{
    //Bombaları ekranda rastgele konumlara ışınlıyoruz.
    foreach (QLabel *bomba ,bombalar) {
        int random_x=rand()%this->width();
        int random_y=rand()%this->height();
        bomba->setGeometry(random_x,random_y+200,bomba->width(),bomba->height());

    }

}

void Dialog::BombaSil()
{
    //Eğer silinecek bombalar listesi boş değilse her 2600 milisaniyede bir ilk patlayan bombanın duman efektini elemanı siliyor ve ekrandan temizliyor.
    if(!Silinecek_bombalar.isEmpty())
    {
        Silinecek_bombalar.first()->clear();
        Silinecek_bombalar.removeFirst();

    }
}

//Ekranda konumu değişen bombalardan birine tıklayınca, ekrandaki tüm karpuzlar kesiliyor.
void Dialog::Ulti()
{
    foreach (QLabel *karpuz ,karpuzlar) {
        kesilen_karpuz++;
        QPixmap resim(":/new/prefix1/images/dilim_karpuz.png");
        QPixmap kücültülmüsResim = resim.scaled(80, 80, Qt::KeepAspectRatio);
        karpuz->setPixmap(kücültülmüsResim);
        //Tıklanan karpuzu karpuzlar listesinden silip silineceklere ekledik.
        karpuzlar.remove(karpuzlar.indexOf(karpuz));
        Silinecek_karpuzlar.append(karpuz);
        ui->kesilen->setText(QString("Kesilen Karpuz Sayısı: <font color=blue>%1</font>").arg(kesilen_karpuz));
    }

}
void Dialog::HediyeSil()
{
    //Eğer silinecek bombalar listesi boş değilse her 2600 milisaniyede bir ilk patlayan bombanın duman efektini elemanı siliyor ve ekrandan temizliyor.
    if(!Silinecek_hediye_kutu.isEmpty())
    {
       Silinecek_hediye_kutu.first()->clear();
        Silinecek_hediye_kutu.removeFirst();

    }
}

void Dialog::Skorlar()
{
    QFile dosya("skorlar.txt");

    if (!dosya.open(QIODevice::ReadOnly)) {
        qDebug()<<"Dosya açma hatası";
        return;
    }
    int kucuk=-100;
    QTextStream stream(&dosya);
    while(!stream.atEnd()){
        QString satir=stream.readLine();
        if(kucuk<satir.toInt())
            kucuk=satir.toInt();
    }
    dosya.close();
    en_yukek_skor=kucuk;
}

void Dialog::kaydet()
{
    QFile dosya("skorlar.txt");

    if (!dosya.open(QIODevice::Append)) {
        qDebug()<<"Dosya açma hatası";
        return;
    }
    QTextStream stream(&dosya);
    stream<<"\n"<<kesilen_karpuz;
}
