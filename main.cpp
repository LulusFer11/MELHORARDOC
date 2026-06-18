#include <opencv2/opencv.hpp>
#include <windows.h>
#include <commdlg.h>

#include <iostream>
#include <string>

#include "ProcessadorImagem.h"

using namespace cv;
using namespace std;


// =====================
// VARIÁVEIS GLOBAIS
// =====================

string mensagemStatus = "";

Scalar corMensagem =
        Scalar(0,255,0);


// =====================
// DEFINIR MENSAGEM
// =====================

void definirMensagem(
        const string& texto,
        Scalar cor)
{
        mensagemStatus =
                texto;

        corMensagem =
                cor;
}


// =====================
// ABRIR IMAGEM
// =====================

string abrirImagem()
{
        OPENFILENAME ofn;

        char arquivo[260] = "";

        ZeroMemory(
                &ofn,
                sizeof(ofn));

        ofn.lStructSize =
                sizeof(ofn);

        ofn.hwndOwner =
                NULL;

        ofn.lpstrFile =
                arquivo;

        ofn.nMaxFile =
                sizeof(arquivo);

        ofn.lpstrFilter =
                "Imagens\0*.png;*.jpg;*.jpeg;*.bmp\0";

        ofn.nFilterIndex =
                1;

        ofn.Flags =
                OFN_PATHMUSTEXIST |
                OFN_FILEMUSTEXIST;

        if(GetOpenFileName(&ofn))
        {
                return string(
                        arquivo);
        }
        else
        {
                MessageBoxA(
                        NULL,
                        "A janela de selecao falhou.",
                        "DEBUG",
                        MB_OK);
        }

        return "";
}


// =====================
// ESCOLHER ONDE SALVAR
// =====================

string escolherSalvar()
{
        OPENFILENAME ofn;

        char arquivo[260] = "";

        ZeroMemory(
                &ofn,
                sizeof(ofn));

        ofn.lStructSize =
                sizeof(ofn);

        ofn.hwndOwner =
                NULL;

        ofn.lpstrFile =
                arquivo;

        ofn.nMaxFile =
                sizeof(arquivo);

        ofn.lpstrFilter =
                "PNG (*.png)\0*.png\0"
                "JPEG (*.jpg)\0*.jpg\0"
                "BMP (*.bmp)\0*.bmp\0";

        ofn.lpstrDefExt =
                "png";

        ofn.Flags =
                OFN_OVERWRITEPROMPT;

        if(GetSaveFileName(&ofn))
        {
                return string(
                        arquivo);
        }

        return "";
}
// =====================
// LEGENDA DOS COMANDOS
// =====================

void desenharLegenda(Mat& tela)
{
    int y = tela.rows - 210;

    putText(
            tela,
            "COMANDOS:",
            Point(30, y),
            FONT_HERSHEY_DUPLEX,
            0.9,
            Scalar(0,255,255),
            2,
            LINE_AA);

    y += 40;

    putText(
            tela,
            "[A] Abrir Imagem",
            Point(30, y),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[C] Escala de Cinza",
            Point(30, y + 40),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[B] Melhorar Contraste",
            Point(30, y + 80),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[T] Destacar Texto",
            Point(30, y + 120),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[N] Aplicar Nitidez",
            Point(450, y),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[E] Escanear Documento",
            Point(450, y + 40),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[Z] Desfazer",
            Point(450, y + 80),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[R] Restaurar Original",
            Point(450, y + 120),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[S] Salvar Imagem",
            Point(900, y),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(255,255,255),
            1,
            LINE_AA);

    putText(
            tela,
            "[ESC] Fechar Programa",
            Point(900, y + 40),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(0,255,255),
            1,
            LINE_AA);
}



// =====================
// TELA INICIAL
// =====================

void mostrarTelaInicial()
{
    Mat tela(
            850,
            1400,
            CV_8UC3,
            Scalar(40,40,40));

    putText(
            tela,
            "BETTERDOCS",
            Point(500,120),
            FONT_HERSHEY_DUPLEX,
            1.8,
            Scalar(255,255,255),
            3,
            LINE_AA);

    rectangle(
            tela,
            Point(120,180),
            Point(1280,420),
            Scalar(80,80,80),
            2);

    putText(
            tela,
            "PRESSIONE A PARA ABRIR UMA IMAGEM",
            Point(220,260),
            FONT_HERSHEY_DUPLEX,
            1.0,
            Scalar(0,255,0),
            2,
            LINE_AA);

    putText(
            tela,
            "Selecione a imagem desejada usando o Explorador de Arquivos do Windows",
            Point(140,330),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(220,220,220),
            1,
            LINE_AA);

    putText(
            tela,
            "Depois utilize os filtros para melhorar a qualidade do documento.",
            Point(180,380),
            FONT_HERSHEY_DUPLEX,
            0.8,
            Scalar(220,220,220),
            1,
            LINE_AA);

    desenharLegenda(tela);

    imshow(
            "BetterDocs",
            tela);
}
// =====================
// ATUALIZAR TELA
// =====================

void atualizarTela(
        const Mat& original,
        const Mat& resultado)
{
    Mat esquerda;
    Mat direita;

    // Converte para colorido caso esteja em cinza
    if(original.channels() == 1)
    {
        cvtColor(
                original,
                esquerda,
                COLOR_GRAY2BGR);
    }
    else
    {
        esquerda =
                original.clone();
    }

    if(resultado.channels() == 1)
    {
        cvtColor(
                resultado,
                direita,
                COLOR_GRAY2BGR);
    }
    else
    {
        direita =
                resultado.clone();
    }

    resize(
            esquerda,
            esquerda,
            Size(),
            0.45,
            0.45);

    resize(
            direita,
            direita,
            Size(),
            0.45,
            0.45);

    copyMakeBorder(
            esquerda,
            esquerda,
            60,
            0,
            0,
            0,
            BORDER_CONSTANT,
            Scalar(0,0,0));

    copyMakeBorder(
            direita,
            direita,
            60,
            0,
            0,
            0,
            BORDER_CONSTANT,
            Scalar(0,0,0));

    putText(
            esquerda,
            "IMAGEM ORIGINAL",
            Point(20,40),
            FONT_HERSHEY_DUPLEX,
            0.9,
            Scalar(0,255,0),
            2,
            LINE_AA);

    putText(
            direita,
            "IMAGEM MODIFICADA",
            Point(20,40),
            FONT_HERSHEY_DUPLEX,
            0.9,
            Scalar(0,255,0),
            2,
            LINE_AA);

    Mat comparacao;

    hconcat(
            esquerda,
            direita,
            comparacao);

    copyMakeBorder(
            comparacao,
            comparacao,
            0,
            240,
            0,
            0,
            BORDER_CONSTANT,
            Scalar(35,35,35));

    desenharLegenda(
            comparacao);

    if(!mensagemStatus.empty())
    {
        putText(
                comparacao,
                mensagemStatus,
                Point(
                        20,
                        comparacao.rows - 20),
                FONT_HERSHEY_DUPLEX,
                0.8,
                corMensagem,
                2,
                LINE_AA);
    }

    imshow(
            "BetterDocs",
            comparacao);
}



// =====================
// SALVAR IMAGEM
// =====================

void salvarImagem(
        const Mat& resultado)
{
    string caminho =
            escolherSalvar();

    if(caminho.empty())
    {
        definirMensagem(
                "Salvamento cancelado!",
                Scalar(0,255,255));

        return;
    }

    bool sucesso =
            imwrite(
                    caminho,
                    resultado);

    if(sucesso)
    {
        definirMensagem(
                "Imagem salva com sucesso!",
                Scalar(0,255,0));

        cout << "\n=================================\n";
        cout << "ARQUIVO SALVO COM SUCESSO\n";
        cout << caminho << endl;
        cout << "=================================\n";
    }
    else
    {
        definirMensagem(
                "Erro ao salvar imagem!",
                Scalar(0,0,255));
    }
}
// =====================
// MAIN
// =====================

int main()
{
    ProcessadorImagem processador;

    Mat original;
    Mat resultado;

    namedWindow(
            "BetterDocs",
            WINDOW_NORMAL);

    resizeWindow(
            "BetterDocs",
            1400,
            850);

    mostrarTelaInicial();

    while(true)
    {
        int tecla =
                waitKey(30);

        // ESC
        if(tecla == 27)
        {
            break;
        }

        // A = Abrir imagem
        else if(
                tecla == 'a' ||
                tecla == 'A')
        {
            string caminho =
                    abrirImagem();

            if(!caminho.empty())
            {
                original =
                        imread(caminho);

                if(!original.empty())
                {
                    resultado =
                            original.clone();

                    definirMensagem(
                            "Imagem carregada com sucesso!",
                            Scalar(0,255,0));

                    atualizarTela(
                            original,
                            resultado);
                }
                else
                {
                    definirMensagem(
                            "Erro ao carregar imagem!",
                            Scalar(0,0,255));

                    mostrarTelaInicial();
                }
            }
        }

        // Executa apenas se existir imagem carregada
        if(!original.empty())
        {
            // C = Cinza
            if(
                    tecla == 'c' ||
                    tecla == 'C')
            {
                processador.aplicarCinza(
                        resultado);

                definirMensagem(
                        "Escala de cinza aplicada!",
                        Scalar(0,255,0));

                atualizarTela(
                        original,
                        resultado);
            }

            // B = Contraste
            else if(
                    tecla == 'b' ||
                    tecla == 'B')
            {
                processador.aplicarContraste(
                        resultado);

                definirMensagem(
                        "Contraste melhorado!",
                        Scalar(0,255,0));

                atualizarTela(
                        original,
                        resultado);
            }

            // T = Texto
            else if(
                    tecla == 't' ||
                    tecla == 'T')
            {
                processador.destacarTexto(
                        resultado);

                definirMensagem(
                        "Texto destacado!",
                        Scalar(0,255,0));

                atualizarTela(
                        original,
                        resultado);
            }

            // N = Nitidez
            else if(
                    tecla == 'n' ||
                    tecla == 'N')
            {
                processador.aplicarNitidez(
                        resultado);

                definirMensagem(
                        "Nitidez aplicada!",
                        Scalar(0,255,0));

                atualizarTela(
                        original,
                        resultado);
            }

            // E = Escanear Documento
            else if(
                    tecla == 'e' ||
                    tecla == 'E')
            {
                processador.escanearDocumento(
                        resultado);

                definirMensagem(
                        "Documento escaneado!",
                        Scalar(0,255,0));

                atualizarTela(
                        original,
                        resultado);
            }

            // Z = Desfazer
            else if(
                    tecla == 'z' ||
                    tecla == 'Z')
            {
                processador.desfazer(
                        resultado);

                definirMensagem(
                        "Ultima acao desfeita!",
                        Scalar(0,255,255));

                atualizarTela(
                        original,
                        resultado);
            }

            // R = Restaurar Original
            else if(
                    tecla == 'r' ||
                    tecla == 'R')
            {
                resultado =
                        original.clone();

                definirMensagem(
                        "Imagem restaurada!",
                        Scalar(255,255,0));

                atualizarTela(
                        original,
                        resultado);
            }

            // S = Salvar
            else if(
                    tecla == 's' ||
                    tecla == 'S')
            {
                salvarImagem(
                        resultado);

                atualizarTela(
                        original,
                        resultado);
            }
        }
    }

    destroyAllWindows();

    return 0;
}
