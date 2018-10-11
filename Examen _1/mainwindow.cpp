#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(intToQString(getPresicion()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getPresicion(){
    return presicion;
}
int MainWindow::setPresicion(int pPresicion){
    presicion=pPresicion;
}
void MainWindow::on_disPres_clicked()
{
    if(getPresicion()>0){
        setPresicion(getPresicion()-1);
        ui->lineEdit->setText(intToQString(getPresicion()));
    }

}

void MainWindow::on_aumPres_clicked()
{
    setPresicion(getPresicion()+1);
    ui->lineEdit->setText(intToQString(getPresicion()));

}

void MainWindow::on_convBin_clicked()
{
    QString numero_str=ui->lineDec->text();
    ListaCircular<char>  lista= construirListaDec(numero_str);
    QString numeroResultado=obtenerParteEnteraStr(obtenerParteEntera(lista));
    if(getPresicion()>0){
        numeroResultado+='.'+ obtenerMantisaStr(obtenerMantisa(lista),getPresicion());
    }
    ui->lineBin->setText(numeroResultado);


}

void MainWindow::on_convDec_clicked()

{
    if(ui->lineBin->text()!=""){
    ListaCircular<char> hola=construirListaDec(ui->lineBin->text());
    QString num_str;
    if(getPresicion()!=0){
       num_str=QString(obtenerParteEnteraDec(hola)+'.'+obtenerParteDecimalDec(hola));
       ui->lineDec->setText(ajustarPresicion(num_str,getPresicion()));
    }else{
        num_str=QString(obtenerParteEnteraDec(hola));
        ui->lineDec->setText(num_str);
    }



    }
}
ListaCircular<char> MainWindow::construirListaDec(QString numeroDecimal){
    char hola=0;
    ListaCircular<char> lista(0);
    bool aparecePunto=false;
    for(int n=0;n<numeroDecimal.length();n++){
        if (numeroDecimal.at(n)=='.'){
            aparecePunto=true;
        }
    }
    if(!aparecePunto){
        numeroDecimal+='.';
        numeroDecimal+='0';
    }

    for(int n=0; n<numeroDecimal.length();n++){
        hola= (numeroDecimal.at(n).toLatin1()-'0');
        lista.agregarSiguiente(hola);
        lista.avanzarEnLista();
    }


    return lista;
}
//Lo siguiente son funciones para operar con String y con numeros
QString obtenerParteEnteraDec(ListaCircular<char> lista){// esta funcion se encarga de obtener la parte entera de un numero en base 10
    long long parteEntera=0;
    int valorHastaElPunto=contarHastaElPunto(lista);
    lista.irNodoInicio();
    lista.avanzarEnLista();
    while (valorHastaElPunto>-1){
        parteEntera+=lista.getDatoNodoActual()*pow(2,valorHastaElPunto);
        lista.avanzarEnLista();
        valorHastaElPunto--;
    }
    QString parteEntera_str="";
    if (parteEntera==0){
        parteEntera_str=QChar('0');
    }
    char caracter=0;
    while (parteEntera>0){
        caracter=(parteEntera%10 +'0');
        parteEntera_str=QChar(caracter)+parteEntera_str;
        parteEntera=parteEntera/10;
    }
     return parteEntera_str;

}

QString obtenerParteDecimalDec(ListaCircular<char> lista){// esto optiene la mantisa de una numero en base 10
    long double parteDecimal=0;
    int valorDespuesDelPunto=contarDespuesdelPunto(lista);
    lista.irNodoInicio();
    do{
    lista.avanzarEnLista();
    } while(lista.getDatoNodoActual()!=('.'-'0'));
    lista.avanzarEnLista();
    int cont=1;
    while (valorDespuesDelPunto-cont>=0){
        parteDecimal+=lista.getDatoNodoActual()*pow(0.5,cont);
        lista.avanzarEnLista();
        cont++;
    }
    long double diez= 10.0000;
    char caracter;
    QString parteDecimal_str="";
    while (parteDecimal!=0){
        caracter=lround(floor(fmod((parteDecimal*diez),diez))+'0');
        parteDecimal_str=parteDecimal_str+QChar(caracter);
        parteDecimal=(parteDecimal*diez)-lround(floor(fmod((parteDecimal*diez),diez)));

    }
    if (parteDecimal_str==""){
        parteDecimal_str+='0';
    }
     return parteDecimal_str;

}

//  esta funcion se encarga de contar la cantidad de digitos de la parte entera
int contarHastaElPunto(ListaCircular<char> lista){
    int cont=-2;
    lista.irNodoInicio();
    while(lista.getDatoNodoActual()!=('.'-'0')){
    lista.avanzarEnLista();
    cont++;//1001.
    }
    return cont;
}
// ajusta la presicion para que imprima unicamenta la cantidad de caracteres de presicion.
QString ajustarPresicion(QString numero,int pPresicion){
    if(pPresicion<0){
        pPresicion=0;
    }
    QString numeroResultado;
    int n=0;
    while(numero.at(n)!='.'&& n<=numero.length()){
        numeroResultado=numeroResultado+numero.at(n);
        n++;
    }
    numeroResultado=numeroResultado+numero.at(n);
    //Cambio
    if(pPresicion==0){
        return numeroResultado+'0';
    }
    n++;
    while(pPresicion>0 && n<numero.length()){
        numeroResultado=numeroResultado+numero.at(n);
        pPresicion--;
        n++;
    }
    return numeroResultado;
}

// pasa de un entero a un string
QString intToQString(int numero){
    char caracter;
    QString numeroStr="";
    bool negative=false;
    if (numero<0){
        numero=-numero;
        negative=true;
    }
    if (numero==0){
        caracter='0';
        numeroStr=numeroStr+caracter;
        return numeroStr;
    }

    while(numero>0){
       caracter= numero%10+'0';
       numeroStr=caracter+numeroStr;
       numero=numero/10;
    }
    qDebug()<< numeroStr;
    if(negative){
         numeroStr='-'+numeroStr;
    }
    return numeroStr;
}
// esta funcion se encarga de contar la cantidad de digitos que tiene la mantisa
int contarDespuesdelPunto(ListaCircular<char> lista){
    int cont=1;
    lista.irNodoInicio();
    while(lista.getDatoNodoActual()!=('.'-'0')){
    lista.avanzarEnLista();
    }
    lista.avanzarEnLista();
    while(lista.verSiguiente()){
    lista.avanzarEnLista();
    cont++;//1001.
    }
    return cont;
}
// obtiene el string de la mantisa
double long obtenerMantisa(ListaCircular<char> lista){
    lista.irNodoInicio();
    int n=0;
    while(lista.getDatoNodoActual()!='.'-'0'){
        lista.avanzarEnLista();
        n++;
    }
    lista.avanzarEnLista();
    double long valor=0;
    int j=1;
    while(lista.verSiguiente()){
         valor += lista.getDatoNodoActual()/pow(10,j);
         lista.avanzarEnLista();
         j++;
    }
    valor += lista.getDatoNodoActual()/pow(10,j);
    return valor;
}
// esto obtiene la parte entera
long long obtenerParteEntera(ListaCircular<char> lista){
    lista.irNodoInicio();
    long long valor=0;
    int n=0;
    while(lista.getDatoNodoActual()!='.'-'0'){
        lista.avanzarEnLista();
        n++;
    }
    lista.irNodoInicio();
    n--;
    while(lista.getDatoNodoActual()!='.'-'0'){
        valor+=lista.getDatoNodoActual()*pow(10,n);
        lista.avanzarEnLista();
        n--;
    }
    return valor;
}
// esto pasa de un numero de tipo long long a String
QString obtenerParteEnteraStr(long long numero){
    QString valorStr="";
    char caracter;
    if (numero==0){
        valorStr+='0';
        return valorStr;
    }
    while(numero>0){
        caracter=numero%2+'0';
        valorStr=QChar(caracter)+valorStr;
        numero=numero/2;
    }
    return valorStr;
}
// obtiene el String del numero double long numero, tomando en cuenta la presicion
QString obtenerMantisaStr(double long numero, int presicion){
    QString valorStr="";
    if (numero==0){
        valorStr+='0';
        return valorStr;
    }
    while(presicion>0){
        numero=numero*2;
        if(numero<1){
            valorStr+='0';
        }
        if (numero>=1){
            valorStr+='1';
            numero=numero-1;
        }

        presicion--;
    }
    return valorStr;

}
//long long obtenerParteEntera(QString numero);

