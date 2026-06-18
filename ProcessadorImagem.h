#ifndef PROCESSADORIMAGEM_H
#define PROCESSADORIMAGEM_H

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class ProcessadorImagem
{
private:

    vector<Mat> historico;

public:

    ProcessadorImagem();

    void aplicarCinza(Mat& imagem);

    void aplicarContraste(Mat& imagem);

    void destacarTexto(Mat& imagem);

    void aplicarNitidez(Mat& imagem);

    void escanearDocumento(Mat& imagem);

    void desfazer(Mat& imagem);

    void salvarHistorico(const Mat& imagem);
};

#endif