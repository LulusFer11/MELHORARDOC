#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace cv;
using namespace std;

void mostrarMenu() {
    cout << "\n===== MELHORADOR DE DOCUMENTOS =====\n";
    cout << "1 - Converter para escala de cinza\n";
    cout << "2 - Melhorar contraste\n";
    cout << "3 - Destacar texto\n";
    cout << "4 - Aplicar nitidez\n";
    cout << "5 - Desfazer ultima acao\n";
    cout << "6 - Salvar imagem\n";
    cout << "0 - Sair\n";
    cout << "Escolha: ";
}

void atualizarTela(const Mat& original,
                   const Mat& resultado)
{
    Mat esquerda;
    Mat direita;

    if (original.channels() == 1)
        cvtColor(original, esquerda, COLOR_GRAY2BGR);
    else
        esquerda = original.clone();

    if (resultado.channels() == 1)
        cvtColor(resultado, direita, COLOR_GRAY2BGR);
    else
        direita = resultado.clone();

    resize(
            esquerda,
            esquerda,
            Size(),
            0.5,
            0.5
    );

    resize(
            direita,
            direita,
            Size(),
            0.5,
            0.5
    );

    copyMakeBorder(
            esquerda,
            esquerda,
            60, 0, 0, 0,
            BORDER_CONSTANT,
            Scalar(0,0,0)
    );

    copyMakeBorder(
            direita,
            direita,
            60, 0, 0, 0,
            BORDER_CONSTANT,
            Scalar(0,0,0)
    );

    putText(
            esquerda,
            "IMAGEM ORIGINAL",
            Point(20,40),
            FONT_HERSHEY_SIMPLEX,
            0.9,
            Scalar(0,255,0),
            2
    );

    putText(
            direita,
            "IMAGEM MODIFICADA",
            Point(20,40),
            FONT_HERSHEY_SIMPLEX,
            0.9,
            Scalar(0,255,0),
            2
    );

    Mat comparacao;

    hconcat(
            esquerda,
            direita,
            comparacao
    );

    imshow(
            "Melhorador de Documentos",
            comparacao
    );

    waitKey(1);
}

string gerarNomeArquivo()
{
    auto agora = time(nullptr);

    tm tempoLocal{};

#ifdef _WIN32
    localtime_s(&tempoLocal, &agora);
#else
    localtime_r(&agora, &tempoLocal);
#endif

    stringstream ss;

    ss << "C:/Users/Luiz Fernandes/Pictures/PROVA/Saidas/";

    ss << "resultado_"
       << put_time(
               &tempoLocal,
               "%Y-%m-%d_%H-%M-%S"
       )
       << ".png";

    return ss.str();
}

int main()
{
    Mat original = imread(
            "C:/Users/Luiz Fernandes/Pictures/PROVA/TESTE.png"
    );

    if(original.empty())
    {
        cout << "Erro ao carregar imagem!" << endl;
        return 1;
    }

    cout << "\n==================================\n";
    cout << "Documento carregado com sucesso!\n";
    cout << "Largura: " << original.cols << " px\n";
    cout << "Altura: " << original.rows << " px\n";
    cout << "==================================\n";

    Mat resultado = original.clone();
    Mat ultimoEstado = resultado.clone();

    namedWindow(
        "Melhorador de Documentos",
        WINDOW_NORMAL
);

    resizeWindow(
            "Melhorador de Documentos",
            1400,
            800
    );
    atualizarTela(
            original,
            resultado
    );

    int opcao;

    do
    {
        mostrarMenu();
        cin >> opcao;

        switch(opcao)
        {
            case 1:
            {
                ultimoEstado = resultado.clone();

                if(resultado.channels() == 3)
                {
                    cvtColor(
                            resultado,
                            resultado,
                            COLOR_BGR2GRAY
                    );
                }

                cout << "\nEscala de cinza aplicada!\n";

                atualizarTela(
                        original,
                        resultado
                );

                break;
            }

            case 2:
            {
                ultimoEstado = resultado.clone();

                resultado.convertTo(
                        resultado,
                        -1,
                        1.2,
                        0
                );

                cout << "\nContraste melhorado!\n";

                atualizarTela(
                        original,
                        resultado
                );

                break;
            }

            case 3:
            {
                ultimoEstado = resultado.clone();

                Mat cinza;

                if(resultado.channels() == 3)
                {
                    cvtColor(
                            resultado,
                            cinza,
                            COLOR_BGR2GRAY
                    );
                }
                else
                {
                    cinza = resultado.clone();
                }

                adaptiveThreshold(
                        cinza,
                        resultado,
                        255,
                        ADAPTIVE_THRESH_GAUSSIAN_C,
                        THRESH_BINARY,
                        11,
                        2
                );

                cout << "\nTexto destacado!\n";

                atualizarTela(
                        original,
                        resultado
                );

                break;
            }

            case 4:
            {
                ultimoEstado = resultado.clone();

                Mat kernel =
                        (Mat_<float>(3,3) <<
                         0,-1,0,
                         -1,5,-1,
                         0,-1,0);

                filter2D(
                        resultado,
                        resultado,
                        resultado.depth(),
                        kernel
                );

                cout << "\nNitidez aplicada!\n";

                atualizarTela(
                        original,
                        resultado
                );

                break;
            }

            case 5:
            {
                resultado = ultimoEstado.clone();

                cout << "\nUltima acao desfeita!\n";

                atualizarTela(
                        original,
                        resultado
                );

                break;
            }

            case 6:
            {
                filesystem::create_directories(
                        "C:/Users/Luiz Fernandes/Pictures/PROVA/Saidas"
                );

                string caminho =
                        gerarNomeArquivo();

                if(imwrite(
                        caminho,
                        resultado
                ))
                {
                    cout << "\n==================================\n";
                    cout << "Imagem salva com sucesso!\n\n";
                    cout << "Arquivo salvo em:\n";
                    cout << caminho << endl;
                    cout << "==================================\n";
                }
                else
                {
                    cout << "\nErro ao salvar imagem!\n";
                }

                break;
            }

            case 0:
            {
                cout << "\nEncerrando programa...\n";
                break;
            }

            default:
            {
                cout << "\nOpcao invalida!\n";
            }
        }

    } while(opcao != 0);

    destroyAllWindows();

    return 0;
}