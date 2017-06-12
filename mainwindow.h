#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
    /**
     * @brief id numero de IP ao qual o programa irá se conectar e capturar os dados
     */
    int id;
public:
    /**
   * @brief MainWindow inicialização da programação em qt
   * @param parent ponteiro da classe QWidget
   */
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    /**
     * @brief tcpConnect função que começa a capturar os dados
     * @param str
     */
    void tcpConnect(QString str);

public slots:
    /**
   * @brief putData slot que sortea dados
   */
  void putData();
  /**
   * @brief comeco slot que começa a capturar dados na tela
   * @param tempo slot que termina o processo de captura de dados
   */
  void comeco(int tempo);
  void fim();
  void timerEvent(QTimerEvent *e);
private slots:
  /**
   * @brief on_botaoConnect_clicked slot do botao que dá início a conexão de dados
   */
  void on_botaoConnect_clicked();
  /**
   * @brief on_botaoDisconnect_clicked slot do botao que finaliza a conexão de dados
   */
  void on_botaoDisconnect_clicked();
  /**
   * @brief on_botaocomeco_clicked slot do botão que começa a captura e exibição de dados
   */
  void on_botaocomeco_clicked();
  /**
   * @brief on_botaoFimDeTempo_clicked slot do botão que finaliza a captura e o processo de exibição de dados
   */
  void on_botaoFimDeTempo_clicked();

private:
  /**
   * @brief ui funçaõ privada para garantir a segurança do processo
   */
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
