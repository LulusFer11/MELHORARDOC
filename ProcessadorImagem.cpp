#include "ProcessadorImagem.h"



// =====================
// CONSTRUTOR
// =====================

ProcessadorImagem::ProcessadorImagem()
{
}



// =====================
// SALVAR HISTÓRICO
// =====================

void ProcessadorImagem::salvarHistorico(
        const Mat& imagem)
{
    historico.push_back(
            imagem.clone());
}



// =====================
// ESCALA DE CINZA
// =====================

void ProcessadorImagem::aplicarCinza(
        Mat& imagem)
{
    salvarHistorico(imagem);

    if(imagem.channels() == 3)
    {
        cvtColor(
                imagem,
                imagem,
                COLOR_BGR2GRAY);
    }
}



// =====================
// CONTRASTE
// =====================

void ProcessadorImagem::aplicarContraste(
        Mat& imagem)
{
    salvarHistorico(imagem);

    imagem.convertTo(
            imagem,
            -1,
            1.4,
            10);
}
// =====================
// DESTACAR TEXTO
// =====================

void ProcessadorImagem::destacarTexto(
        Mat& imagem)
{
        salvarHistorico(imagem);

        Mat cinza;
        Mat borrada;

        if(imagem.channels() == 3)
        {
                cvtColor(
                        imagem,
                        cinza,
                        COLOR_BGR2GRAY);
        }
        else
        {
                cinza =
                        imagem.clone();
        }

        GaussianBlur(
                cinza,
                borrada,
                Size(5,5),
                0);

        adaptiveThreshold(
                borrada,
                imagem,
                255,
                ADAPTIVE_THRESH_GAUSSIAN_C,
                THRESH_BINARY,
                21,
                10);
}



// =====================
// NITIDEZ
// =====================

void ProcessadorImagem::aplicarNitidez(
        Mat& imagem)
{
        salvarHistorico(imagem);

        Mat kernel =
                (Mat_<float>(3,3) <<
                 0,-1,0,
                 -1,5,-1,
                 0,-1,0);

        filter2D(
                imagem,
                imagem,
                imagem.depth(),
                kernel);
}



// =====================
// ESCANEAR DOCUMENTO
// =====================

void ProcessadorImagem::escanearDocumento(
        Mat& imagem)
{
        salvarHistorico(imagem);

        Mat cinza;
        Mat blur;
        Mat finalImg;

        if(imagem.channels() == 3)
        {
                cvtColor(
                        imagem,
                        cinza,
                        COLOR_BGR2GRAY);
        }
        else
        {
                cinza =
                        imagem.clone();
        }

        GaussianBlur(
                cinza,
                blur,
                Size(5,5),
                0);

        adaptiveThreshold(
                blur,
                finalImg,
                255,
                ADAPTIVE_THRESH_GAUSSIAN_C,
                THRESH_BINARY,
                25,
                15);

        imagem =
                finalImg;
}
// =====================
// DESFAZER
// =====================

void ProcessadorImagem::desfazer(
        Mat& imagem)
{
        if(!historico.empty())
        {
                imagem =
                        historico.back().clone();

                historico.pop_back();
        }
}