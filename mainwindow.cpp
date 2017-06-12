#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      socket = new QTcpSocket(this);

  /*connect(ui->pushButtonPut,
          SIGNAL(clicked(bool)),
          this,
          SLOT(putData()));
*/
}

void MainWindow::tcpConnect(QString str){ // bloco de conexão com o servidor
      socket->connectToHost(str,1234);
      if(socket->waitForConnected(3000)){
            qDebug() << "Connected"; //exibição do status de conexão - connected e disconnected
            ui->textEdit->insertPlainText("Connected\n");
  }
      else{
            ui->textEdit->insertPlainText("Disconnected\n");
            qDebug() << "Disconnected";
  }
}

void MainWindow::timerEvent(QTimerEvent *e){
        putData(); // captura do tempo real
}

void MainWindow::putData()
{
      QDateTime datetime;
      QString str;
      if(socket->state()== QAbstractSocket::ConnectedState){
        // quando conectado, em tempo real // exibição do número escolhido entre os mínimos e máximos definidos pelo usuário no programa
          datetime = QDateTime::currentDateTime();
          str = "set "+
              datetime.toString(Qt::ISODate)+
              " "+
              QString::number(ui->sliderMin->value() + qrand()%(ui->sliderMax->value()-ui->sliderMin->value()))+"\r\n";
          ui->textEdit->insertPlainText(str);
          qDebug() << str;
          qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
          if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
          }
      }
}
void MainWindow::fim(){
        killTimer(id); //mata o tempo - fim da exibição de dados capturados
}

void MainWindow::comeco(int tempo)
{
        //temporizador int id = startTimer(1000)
        id = startTimer(tempo*1000);
}
MainWindow::~MainWindow()
{
          delete socket;
          delete ui;
}

void MainWindow::on_botaoConnect_clicked()
{
    //captura o ID digitado pelo server e liga o clique à conexão
          tcpConnect(ui->lineEdit->text());
}

void MainWindow::on_botaoDisconnect_clicked()
{
        //atribui a desconexão
        socket->disconnectFromHost();
        ui->textEdit->insertPlainText("Disconnected\n");
}

void MainWindow::on_botaocomeco_clicked()
{
    //atribuição do clique no botão começo à captura e exibiçao dos valores limitados no intervalo designado
    comeco(ui->sliderTiming->value());
}

void MainWindow::on_botaoFimDeTempo_clicked()
{
        fim(); // fim de papo - encerra o processo
}
