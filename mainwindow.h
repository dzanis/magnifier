#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
      void showEvent(QShowEvent *ev);


private slots:

    void on_zoom_in_clicked();

    void on_zoom_out_clicked();

private:
    Ui::MainWindow *ui;
    int zoom;
    int zoom_in();
    int zoom_out();
    void updateTitle();
};

#endif // MAINWINDOW_H
