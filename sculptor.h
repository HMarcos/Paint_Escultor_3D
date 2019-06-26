#ifndef SCULPTOR_H
#define SCULPTOR_H

#include<iostream>
#include<cstring>

/**
 * @brief The Voxel struct:
     * Voxels (volume elements), algo equivalente aos Pixels que comumente são usados em imagens digitais.
     * Nos Voxels seria possível armazenar informações como cor e transparência, necessárias para idealizar os elementos de uma escultura.
     * @param r : intensidade da cor vermelha, varia entre [0,1]
     * @param g : intensidade da cor vermelha, varia entre [0,1]
     * @param b : intensidade da cor vermelha, varia entre [0,1]
     * @param a : opacidade do voxel, varia entre [0,1]
     * @param isOn : define se o voxel esta ativo ou nao, assume como valores 0 (desativado) ou 1 (ativado)
 */
struct Voxel{
    float r,g,b; // Cores
    float a; // Canal alpha
    bool isOn; // Inclue ou nao
};

/**
 * @brief A classe Sculptor
 * monta uma estrutura e fornece os metodos para manipular os pixels de uma matriz tridimensional
 */
class Sculptor
{

protected:
    /**
     * @brief v: matriz 3D alocada dinamicamente que armazena todos os voxels
     */
    Voxel ***v;
     /**
     * @brief nx: dimensao em x (numero de linhas)
     */
    int nx;
    /**
     * @brief ny: dimensao em y (numero de colunas)
     */
    int ny;
    /**
     * @brief nz: dimensao em z (numero de planos)
     */
    int nz;
    /**
     * @brief r: intensidade atual da cor vermelha, varia entre [0,1]
     */
    float r;
    /**
     * @brief g: intensidade atual da cor verde, varia entre [0,1]
     */
    float g;
    /**
     * @brief b: intensidade atual da cor azul, varia entre [0,1]
     */
    float b;
    /**
     * @brief a: intensidade atual da opacidade, varia entre [0,1]
     */
    float a;
public:

    /**
     * @brief Sculptor: Construtor da classe Sculptor
     * @param _nx : dimensao em x (numero de linhas)
     * @param _ny : dimensao em y (numer de colunas)
     * @param _nz : dimensao em z (numero de planos)
     */
    Sculptor(int _nx, int _ny, int _nz);

    /**
      * @brief ~Sculptor: Destrutor da classe Sculptor
    */
    ~Sculptor();

    /**
     * @brief setColor : Define a cor atual do desenho
     * @param r : intensidade da cor vermelha, varia entre [0,1]
     * @param g : intensidade da cor vermelha, varia entre [0,1]
     * @param b : intensidade da cor vermelha, varia entre [0,1]
     * @param alpha : opacidade do voxel, varia entre [0,1]
     */
    void setColor(float r, float g, float b, float alpha);

    /**
     * @brief putVoxel : Ativa o voxel na posição (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor atual de desenho
     * @param x : coordenada em relacao ao eixo x
     * @param y : coordenada em relacao ao eixo y
     * @param z : coordenada em relacao ao eixo z
     */
    void putVoxel(int x, int y, int z);

    /**
     * @brief cutVoxel : Desativa o voxel na posição (x,y,z) (fazendo isOn = false)
     * @param x : coordenada em relacao ao eixo x
     * @param y : coordenada em relacao ao eixo y
     * @param z : coordenada em relacao ao eixo z
     */
    void cutVoxel(int x, int y, int z);

    /**
     * @brief putBox : Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
     * @param x0 : coordenada do ponto inicial no eixo x
     * @param x1 : coordenada do ponto final no eixo x
     * @param y0 : coordenada do ponto inicial no eixo y
     * @param y1 : coordenada do ponto final no eixo y
     * @param z0 : coordenada do ponto inicial no eixo z
     * @param z1 : coordenada do ponto final no eixo z
     */
    void putBox(int x0, int x1,int y0, int y1,int z0, int z1);

    /**
     * @brief cutBox : Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
     * @param x0 : coordenada do ponto inicial no eixo x
     * @param x1 : coordenada do ponto final no eixo x
     * @param y0 : coordenada do ponto inicial no eixo y
     * @param y1 : coordenada do ponto final no eixo y
     * @param z0 : coordenada do ponto inicial no eixo z
     * @param z1 : coordenada do ponto final no eixo z
     */
    void cutBox(int x0, int x1,int y0, int y1,int z0, int z1);

    /**
     * @brief putSphere : Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho
     * @param xcenter : coordenada x do centro da esfera
     * @param ycenter : coordenada y do centro da esfera
     * @param zcenter : coordenada z do centro da esfera
     * @param radius : raio da esfera
     */
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);

    /**
     * @brief cutSphere : Desativa todos os voxels que satisfazem a equação da esfera
     * @param xcenter : coordenada x do centro da esfera
     * @param ycenter : coordenada y do centro da esfera
     * @param zcenter : coordenada z do centro da esfera
     * @param radius : raio da esfera
     */
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

    /**
     * @brief putEllipsoid : Ativa todos os voxels que satisfazem a equação do elipsoide e atribui aos mesmos a cor atual de desenho
     * @param xcenter : coordenada x do centro do elipsoide
     * @param ycenter : coordenada y do centro do elipsoide
     * @param zcenter : coordenada z do centro do elipsoide
     * @param rx : raio na direcao x
     * @param ry : raio na direcao y
     * @param rz : raio na direcao z
     */
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    /**
     * @brief cutEllipsoid : Desativa todos os voxels que satisfazem a equação do elipsoide
     * @param xcenter : coordenada x do centro do elipsoide
     * @param ycenter : coordenada y do centro do elipsoide
     * @param zcenter : coordenada z do centro do elipsoide
     * @param rx : raio na direcao x
     * @param ry : raio na direcao y
     * @param rz : raio na direcao z
     */
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    /**
     * @brief writeVECT : grava a escultura no formato VECT no arquivo filename
     * @param filename : caminho do arquivo .vect
     */
    void writeVECT(std::string filename);

    /**
     * @brief writeOFF : grava a escultura no formato OFF no arquivo filename
     * @param filename : caminho do arquivo .vect
     */
    void writeOFF(std::string filename);

    // Funções auxiliares

    /**
     * @brief verLimites: verifica se o voxel esta dentro dos limites do escultor
     * @param x : coordenada em relacao ao eixo x
     * @param y : coordenada em relacao ao eixo y
     * @param z : coordenada em relacao ao eixo z
     */
    bool dentroDosLimites(int x, int y, int z);

    /**
     * @brief inicializaMatriz3D : Inicializa a matriz 3D com voxels com todos os campos iguais a zero
     */
    void inicializaMatriz3D();

    /**
     * @brief print_sculptor : Imprime o campo isOn de cada Voxel no formato da matriz 3D
     */
    void print_sculptor();
    /**
     * @brief otimizar : Verifica quais voxels estão completamente rodeados por outros voxels e assinala isOn = false,
     * para otimizar a visualização e o desempenho
     */
    void otimizar();


};

#endif // SCULPTOR_H
