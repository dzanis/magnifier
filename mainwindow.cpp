#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>

#include <QSettings>
#include <QDebug>



// 25.04.2016

// Magnifier работает через менеджер xfwm4 по комбинации "Alt_L + mouse scroll"
// т.к я не нашол как симулировать нажатие клавиш средствами Qt
// потребуется xdotool,который симулирует нажатие этой комбинации
// через функу system  т.е system("xdotool keydown Alt_L  mousedown 4 ...
// костыль тот ешё o_O
// установка xdotool через терминал sudo apt-get install xdotool



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     int result = system("xdotool -version");
     if(result){
     QMessageBox::critical(0,"Error",
                           " <html>"
                           "xdotool: not found <br> "
                           "install xdotoo :<br>"
                           "<b>sudo apt-get install xdotool</b>"
                           "</html>"
                           );
     }

    zoom = 0;
    /* открываем файл с настройками для считывания */
      QSettings settings ("magnifier");
       zoom = settings.value("zoom",0).toInt();  //читаем настройки из файла, если файла ешё нет - то 0
       qDebug() << settings.fileName();
       for(int i = zoom;i > 0;i--){
           zoom_in();
       }
       updateTitle();
}



MainWindow::~MainWindow()
{
        QSettings settings ("magnifier");
        settings.setValue("zoom",zoom);  //записываем настройки

    for(;zoom > 0;zoom--){
        zoom_out();
    }

    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{

    QWidget::showEvent(event);

    QPoint p = QCursor::pos();
    int x = p.x();
    int y = p.y();
    QDesktopWidget *d = QApplication::desktop();

        x -= this->width()/2;

    if(y > d->height()/2)
        y -= this->height()*2;
    else
        y += this->height();

    this->move(x,y);

    //QString text = QString("x:%1 y: %2").arg(p.x() ).arg(p.y());
   // QMessageBox::information(0,"showEvent",text);
}


void MainWindow::on_zoom_in_clicked()
{
    if(!zoom_in() )// если нет ошибки (т.е result == 0) то обновляю переменные
    {
     zoom++;
     if(zoom > 16)
         zoom = 16;
     updateTitle();
    }
}

void MainWindow::on_zoom_out_clicked()
{
    if(!zoom_out())
    {
    zoom--;
    if(zoom < 0)
        zoom = 0;
    updateTitle();
    }
}




int MainWindow::zoom_in()
{
    // xdotool --clearmodifiers keydown Alt click 4 keyup Alt
    return system("xdotool keydown Alt_L  mousedown 4  sleep 0,1  keyup Alt_L   mouseup 4 ");
}


int MainWindow::zoom_out()
{
    return system("xdotool  keydown Alt_L  mousedown 5  sleep 0,1  keyup Alt_L   mouseup 5 ");
}



void MainWindow::updateTitle()
{
    QString text = QString("%1% zoom").arg(100 + (zoom * 10) );
    if(zoom == 0)
        text = "Magnifier";
    setWindowTitle(text);
}




