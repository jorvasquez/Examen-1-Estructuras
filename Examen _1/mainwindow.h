#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listacircular.h"
#include <QDebug>
#include <math.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ListaCircular<char> construirListaDec(QString numeroDecimal);
    int getPresicion();
    int setPresicion(int presicion);
    ~MainWindow();

private slots:


    void on_disPres_clicked();

    void on_aumPres_clicked();

    void on_convBin_clicked();

    void on_convDec_clicked();



private:
    Ui::MainWindow *ui;
    int presicion=0;
};
int contarHastaElPunto(ListaCircular<char> lista);
int contarDespuesdelPunto(ListaCircular<char> lista);
QString obtenerParteEnteraDec(ListaCircular<char> lista);
QString obtenerParteDecimalDec(ListaCircular<char> lista);
QString ajustarPresicion(QString numero,int pPresicion);
QString intToQString(int numero);
double long obtenerMantisa(ListaCircular<char> lista);
long long obtenerParteEntera(ListaCircular<char> lista);
QString obtenerParteEnteraStr(long long numero);
QString obtenerMantisaStr(double long numero, int presicion);





#endif // MAINWINDOW_H
