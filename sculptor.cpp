#include "sculptor.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;


// Construtor da classe Sculptor
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;
    // Verifica se as quantidades de linhas, colunas e planos sao positivas
    if (nx <= 0 || ny <= 0|| nz <= 0){
        nx = ny = nz = 0;
    }
    // Solicita um bloco de memoria com a quantidade de planos
    v = new Voxel**[nz];
    // Verifica se o bloco foi armazenado
    if(v == nullptr){
        exit(0);
    }
    // Solicita um bloco que armazena o indice as linhas dos planos
    v[0] = new Voxel*[nz*nx];
    // Verifica se o bloco foi armazenado
    if(v[0] == nullptr){
        exit(0);
    }

    // Distribui os planos
    for (int k=1;k<nz;k++){
        v[k] = v[k-1] + nx;
    }
    // Solicita um bloco de memoria que armazena todos os voxels na matriz 3D
    v[0][0] = new Voxel[nz*nx*ny];
    // Verifica se o bloco foi armazenado
    if(v[0][0] == nullptr){
        exit(0);
    }
    //Distribui as colunas entre as linhas e os planos
    int n = 0;
    for (int k=0; k<nz;k++){
        for(int i=0; i<nx;i++){
            v[k][i] = v[0][0] + n*ny;
            n++;
        }
    }
    inicializaMatriz3D();

}

// Destrutor da classe Sculptor
Sculptor::~Sculptor(){
    if (nx == 0 || ny == 0|| nz == 0){
        return;
    }
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

// Define a cor atual do desenho
void Sculptor::setColor(float _r, float _g, float _b, float alpha){
    r = _r;
    g = _g;
    b = _b;
    a = alpha;
}

// Ativa o voxel na posição (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor atual de desenho
void Sculptor::putVoxel(int x, int y, int z){
    if(dentroDosLimites(x, y, z) == true){ // verificando se o usuário não está acessando algum elemento da matriz que não existe
        v[z][x][y].isOn = true;
        v[z][x][y].r = r;
        v[z][x][y].g = g;
        v[z][x][y].b = b;
        v[z][x][y].a = a;
    }

}

//Desativa o voxel na posição (x,y,z) (fazendo isOn = false)
void Sculptor::cutVoxel(int x, int y, int z){
    if(dentroDosLimites(x, y, z) == true){ // verificando se o usuário não está acessando algum elemento da matriz que não existe
        v[z][x][y].isOn = false;
    }
}

// Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int k=z0; k<=z1; k++){
        for (int i=x0; i<=x1; i++) {
            for (int j=y0; j<=y1; j++) {
                putVoxel(i,j,k);
            }
        }
    }
}

// Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int k=z0; k<=z1; k++){
        for (int i=x0; i<=x1; i++) {
            for (int j=y0; j<=y1; j++) {
                cutVoxel(i,j,k);
            }
        }
    }
}

//Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    double dist;
    for(int k=0; k<nz; k++){
        for (int i=0; i<nx; i++) {
            for (int j=0; j<ny; j++){
               dist = pow(i-xcenter,2) + pow(j-ycenter,2) + pow(k-zcenter,2);
               if (dist <= pow(radius,2)){
                   putVoxel(i,j,k);
               }
            }

        }
    }
}

//Desativa todos os voxels que satisfazem à equação da esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    double dist;
    for(int k=0; k<nz; k++){
        for (int i=0; i<nx; i++) {
            for (int j=0; j<ny; j++){
               dist = pow(i-xcenter,2) + pow(j-ycenter,2) + pow(k-zcenter,2);
               if (dist <= pow(radius,2)){
                   cutVoxel(i,j,k);
               }
            }

        }
    }
}

//Ativa todos os voxels que satisfazem à equação do elipsóide e atribui aos mesmos a cor atual de desenho
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    double dist;

    if (rx ==0){
        for (int k=0;k<nz;k++) {
            for (int j=0;j<ny;j++) {
                dist =  pow(j-ycenter,2)/pow(ry,2) + pow(k-zcenter,2)/pow(rz,2);
                if(dist<=1){
                    putVoxel(xcenter,j,k);
              }
            }
        }
    }
    else if(ry==0){
        for (int k=0;k<nz;k++) {
            for (int i=0;i<nx;i++) {
                dist =  pow(i-xcenter,2)/pow(rx,2) + pow(k-zcenter,2)/pow(rz,2);
                if(dist<=1){
                    putVoxel(i,ycenter,k);
              }
            }
        }
    }
    else if (rz==0) {
        for (int i=0;i<nx;i++) {
            for (int j=0;j<ny;j++) {
                dist =  pow(i-xcenter,2)/pow(rx,2) + pow(j-ycenter,2)/pow(ry,2);
                if(dist<=1){
                    putVoxel(i,j,zcenter);
              }
            }
        }
    }
    else{
    for (int k=0;k<nz;k++) {
        for (int i=0;i<nx;i++) {
            for (int j=0;j<ny;j++) {
                  dist = pow(i-xcenter,2)/pow(rx,2) + pow(j-ycenter,2)/pow(ry,2) + pow(k-zcenter,2)/pow(rz,2);
                if(dist<=1){
                    putVoxel(i,j,k);
                }

            }

        }
      }
    }
}

// Desativa todos os voxels que satisfazem à equação do elipsóide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    double dist;

    if (rx ==0){
        for (int k=0;k<nz;k++) {
            for (int j=0;j<ny;j++) {
                dist =  pow(j-ycenter,2)/pow(ry,2) + pow(k-zcenter,2)/pow(rz,2);
                if(dist<=1){
                    cutVoxel(xcenter,j,k);
              }
            }
        }
    }
    else if(ry==0){
        for (int k=0;k<nz;k++) {
            for (int i=0;i<nx;i++) {
                dist =  pow(i-xcenter,2)/pow(rx,2) + pow(k-zcenter,2)/pow(rz,2);
                if(dist<=1){
                    cutVoxel(i,ycenter,k);
              }
            }
        }
    }
    else if (rz==0) {
        for (int i=0;i<nx;i++) {
            for (int j=0;j<ny;j++) {
                dist =  pow(i-xcenter,2)/pow(rx,2) + pow(j-ycenter,2)/pow(ry,2);
                if(dist<=1){
                    cutVoxel(i,j,zcenter);
              }
            }
        }
    }
    else{
    for (int k=0;k<nz;k++) {
        for (int i=0;i<nx;i++) {
            for (int j=0;j<ny;j++) {
                  dist = pow(i-xcenter,2)/pow(rx,2) + pow(j-ycenter,2)/pow(ry,2) + pow(k-zcenter,2)/pow(rz,2);
                if(dist<=1){
                    cutVoxel(i,j,k);
                }

            }

        }
    }
    }
}
//grava a escultura no formato VECT no arquivo filename
void Sculptor::writeVECT(std::string filename){
    ofstream fout;
    string pontos, cores;
    int contador = 0;

    otimizar();
    // Abrindo o arquivo
    fout.open(filename);
    // Verificiando se o arquivo foi aberto corretamente
    if (fout.is_open()){
        cout << "Arquivo VECT aberto com sucesso" << endl;
    }
    else{
        cout << "Nao foi possivel abrir o arquivo VECT" << endl;
        exit(0);
    }
    // Criando as stings com os pontos e as cores
    pontos = "";
    cores = "";
    for (int k=0;k<nz;k++) {
        for(int i=0;i<nx;i++){
            for(int j=0;j<ny;j++){
                if(v[k][i][j].isOn == true){
                    stringstream ponto;
                    ponto << k << " " << i << " " << j << endl;
                    pontos = pontos + ponto.str();
                    stringstream cor;
                    cor << fixed << setprecision(1) << v[k][i][j].r << " " << v[k][i][j].g << " " << v[k][i][j].b << " " << v[k][i][j].a <<endl;
                    cores = cores + cor.str();
                    contador++;
                }
            }
        }
    }
    fout << "VECT"<<endl; // Linha 1
    fout << contador << " " << contador << " " << contador << endl; // Linha 2
    // Linhas 3 e 4
    for(int k=0; k<2; k++){
        for (int i=0;i<contador;i++) {
            fout << 1 <<" ";
        }
        fout<<endl;
    }

    // Os voxels que possuem isOn == true
    fout<<pontos;
    // As cores referentes aos voxels
    fout << cores;
    // Fecha o arquivo
    fout.close();
}

//grava a escultura no formato OFF no arquivo filename
void Sculptor::writeOFF(std::string filename){
    ofstream fout;
    string pontos, faces;
    int contador;

    otimizar();
    // Definindo os pesos para desenhar os cubos
    vector<vector<float> > pesos;
    vector<float> v1;
    v1 = {-0.5, 0.5, -0.5};
    pesos.push_back(v1);
    v1 = {-0.5, -0.5, -0.5};
    pesos.push_back(v1);
    v1 = {0.5,- 0.5, -0.5};
    pesos.push_back(v1);
    v1 = {0.5, 0.5, -0.5};
    pesos.push_back(v1);
    v1 = {-0.5, 0.5, 0.5};
    pesos.push_back(v1);
    v1 = {-0.5, -0.5, 0.5};
    pesos.push_back(v1);
    v1 = {0.5, -0.5, 0.5};
    pesos.push_back(v1);
    v1 = {0.5, 0.5, 0.5};
    pesos.push_back(v1);

    // Definindo a sequencia inicial para as faces
    vector<vector<int> > pontos_faces;
    vector<int> v2;
    v2 = {0, 3, 2, 1};
    pontos_faces.push_back(v2);
    v2 = {4, 5, 6, 7};
    pontos_faces.push_back(v2);
    v2 = {0, 1, 5, 4};
    pontos_faces.push_back(v2);
    v2 = {0, 4, 7, 3};
    pontos_faces.push_back(v2);
    v2 = {3, 7, 6, 2};
    pontos_faces.push_back(v2);
    v2 = {1, 2, 6, 5};
    pontos_faces.push_back(v2);


    //Abre o arquivo
    fout.open(filename);
    // Verifica se o arquivo foi aberto corretamente
    if(fout.is_open()){
        cout << "Arquivo OFF aberto com sucesso" << endl;
    }
    else{
        cout << "Nao foi possivel abrir o arquivo OFF"<< endl;
        exit(0);
    }
    // Inicializa as string
    pontos = "";
    faces = "";
    contador = 0;
    // Configurando para cada voxel ser representado como um cubo de aresta igual a 1
    for (int k=0;k<nz;k++) {
        for (int i=0;i<nx;i++) {
            for(int j=0;j<ny;j++){
                if(v[k][i][j].isOn == true){
                    vector<int> coord;
                    coord = {j,-i,-k};

                    for (unsigned int a=0;a<8;a++) {
                        stringstream ponto;
                        for(unsigned int t=0;t<3;t++){
                            ponto << fixed << setprecision(1) << coord[t] + pesos[a][t] << " ";
                        }
                        ponto << endl;
                        pontos = pontos + ponto.str();
                    }
                    for (unsigned int a=0;a<6;a++) {
                        stringstream face;
                        face << 4 << " ";
                        for(unsigned int t=0;t<4;t++){
                            face << contador*8 + pontos_faces[a][t] << " ";
                        }
                        face << fixed << setprecision(1) << v[k][i][j].r << " "<< v[k][i][j].g << " "<< v[k][i][j].b << " " << v[k][i][j].a <<endl;
                        faces = faces + face.str();
                    }

                    contador++;

                }
            }

        }

    }
    //Configurando o arquivo OFF
    fout << "OFF"<<endl;
    fout << contador*8 << " " << contador*6 << " " << 0 <<endl;
    fout << pontos;
    fout << faces;

    //Fecha o arquivo
    fout.close();
}

//Funcoes Auxiliares
// impõe o usuário de não ultrapassar os limites do voxel
bool Sculptor::dentroDosLimites(int x, int y, int z){
    if (x>=nx || y>=ny || z>=nz || x<0 || y<0 || z<0){
       cout << "o elemento (" << x << "," << y << "," << z << ") nao pode ser acessado" << endl;
       return false;
    }
    return true;
}


// Inicializa a matriz 3D com voxels com todos os campos iguais a zero
void Sculptor::inicializaMatriz3D(){
    Voxel x;
    // Voxel Genérico
    x.r = x.g = x.b =0;
    x.a = 0;
    x.isOn = false;

    for(int k=0; k<nz; k++){
        for(int i=0; i<nx; i++){
            for (int j=0; j<ny; j++) {
                    v[k][i][j] = x;
            }
        }
    }
}


// Imprime o conteuduo do Escultor
void Sculptor::print_sculptor(){

    for(int k=0; k<nz; k++){
        cout << "Plano " << k << endl;
        for(int i=0; i<nx; i++){
            for (int j=0; j<ny; j++) {
                    cout << v[k][i][j].isOn << " ";

            }
            cout << endl;
        }
        cout << "---------------------------" << endl;
    }

}

// Otmiza
void Sculptor::otimizar(){
    char ***voxels_isOn;
    voxels_isOn = new char**[nz];
    // Verifica se o bloco foi armazenado
    if(voxels_isOn == nullptr){
        exit(0);
    }
    // Solicita um bloco que armazena o indice as linhas dos planos
    voxels_isOn[0] = new char*[nz*nx];
    // Verifica se o bloco foi armazenado
    if(voxels_isOn[0] == nullptr){
        exit(0);
    }

    // Distribui os planos
    for (int k=1;k<nz;k++){
        voxels_isOn[k] = voxels_isOn[k-1] + nx;
    }
    // Solicita um bloco de memoria que armazena todos os voxels na matriz 3D
    voxels_isOn[0][0] = new char[nz*nx*ny];
    // Verifica se o bloco foi armazenado
    if(voxels_isOn[0][0] == nullptr){
        exit(0);
    }
    //Distribui as colunas entre as linhas e os planos
    int n = 0;
    for (int k=0; k<nz;k++){
        for(int i=0; i<nx;i++){
            voxels_isOn[k][i] = voxels_isOn[0][0] + n*ny;
            n++;
        }
    }

    for(int k=0; k<nz; k++){
        for(int i=0; i<nx; i++){
            for (int j=0; j<ny; j++) {
                     voxels_isOn[k][i][j]=v[k][i][j].isOn;

            }
        }
    }
    for(int k=1; k<nz-1; k++){
        for(int i=1; i<nx-1; i++){
            for (int j=1; j<ny-1; j++) {
                     char direita = voxels_isOn[k][i][j+1];
                     char esquerda = voxels_isOn[k][i][j-1];
                     char frente = voxels_isOn[k-1][i][j];
                     char atras = voxels_isOn[k+1][i][j];
                     char acima = voxels_isOn[k][i-1][j];
                     char abaixo = voxels_isOn[k][i+1][j];
                     if(direita == 1 && esquerda == 1 && frente == 1 && atras == 1 && acima == 1 && abaixo == 1 ){
                         v[k][i][j].isOn = 0;
                     }

            }
        }
    }

    delete [] voxels_isOn[0][0];
    delete [] voxels_isOn[0];
    delete [] voxels_isOn;


}





