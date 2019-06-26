#ifndef DIALOGESCULTOR_H
#define DIALOGESCULTOR_H

#include <QDialog>

namespace Ui {
class DialogEscultor;
}

/**
 * @brief The DialogEscultor class
 * representa uma caixa de dialogo na qual o usuario escolhe as dimensões do escultor
 */
class DialogEscultor : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DialogEscultor: Construtor da classe DialogEscultor
     */
    explicit DialogEscultor(QWidget *parent = nullptr);
    /**
      @brief ~DialogEscultor: Destrutor da classe DialogEscultor
     */
    ~DialogEscultor();
    /**
     * @brief getNumLinhas : funcao que retorna a dimensao X do escultor, que refere-se ao numero de linhas da matriz 3D.
     * @return numero de linhas do escultor (matriz 3D)
     */
    int getNumLinhas();
    /**
     * @brief getNumColunas : funcao que retorna a dimensao Y do escultor, que refere-se ao numero de colunas da matriz 3D.
     * @return numero de colunas do escultor (matriz 3D)
     */
    int getNumColunas();
    /**
     * @brief getNumPlanos : funcao que retorna a dimensao Z do escultor, que refere-se ao numero de planos da matriz 3D.
     * @return numero de planos do escultor (matriz 3D)
     */
    int getNumPlanos();

private:
    Ui::DialogEscultor *ui;
};

#endif // DIALOGESCULTOR_H
