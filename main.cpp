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

void mostrarComparacao(const Mat& original,
                       const Mat& resultado)
{
    Mat originalExibir;
    Mat resultadoExibir;

    if (original.channels() == 1)
        cvtColor(original, originalExibir, COLOR_GRAY2BGR);
    else
        originalExibir = original;

    if (resultado.channels() == 1)
        cvtColor(resultado, resultadoExibir, COLOR_GRAY2BGR);
    else
        resultadoExibir = resultado;

    resize(originalExibir,
           originalExibir,
           Size(),
           0.5,
           0.5);

    resize(resultadoExibir,
           resultadoExibir,
           Size(),
           0.5,
           0.5);

    Mat comparacao;

    hconcat(originalExibir,
            resultadoExibir,
            comparacao);

    namedWindow("Original | Resultado",
                WINDOW_NORMAL);

    imshow("Original | Resultado",
           comparacao);

    waitKey(0);

    destroyAllWindows();
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
       << put_time(&tempoLocal,
                   "%Y-%m-%d_%H-%M-%S")
       << ".png";

    return ss.str();
}

int main() {

    Mat original = imread(
        "C:/Users/Luiz Fernandes/Pictures/PROVA/TESTE.png"
    );

    if (original.empty()) {
        cout << "Erro ao carregar imagem!" << endl;
        return 1;
    }

    Mat resultado = original.clone();

    Mat ultimoEstado = resultado.clone();

    int opcao;

    do {

        mostrarMenu();
        cin >> opcao;

        switch(opcao) {

            case 1: {

                ultimoEstado = resultado.clone();

                if(resultado.channels() == 3)
                {
                    cvtColor(resultado,
                             resultado,
                             COLOR_BGR2GRAY);
                }

                cout << "\nEscala de cinza aplicada!\n";

                mostrarComparacao(original,
                                  resultado);

                break;
            }

            case 2: {

                ultimoEstado = resultado.clone();

                resultado.convertTo(
                    resultado,
                    -1,
                    1.2,
                    0
                );

                cout << "\nContraste melhorado!\n";

                mostrarComparacao(original,
                                  resultado);

                break;
            }

            case 3: {

                ultimoEstado = resultado.clone();

                Mat cinza;

                if(resultado.channels() == 3)
                {
                    cvtColor(resultado,
                             cinza,
                             COLOR_BGR2GRAY);
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

                mostrarComparacao(original,
                                  resultado);

                break;
            }

            case 4: {

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

                mostrarComparacao(original,
                                  resultado);

                break;
            }

            case 5: {

                resultado = ultimoEstado.clone();

                cout << "\nUltima acao desfeita!\n";

                mostrarComparacao(original,
                                  resultado);

                break;
            }

            case 6: {

                filesystem::create_directories(
                    "C:/Users/Luiz Fernandes/Pictures/PROVA/Saidas"
                );

                string caminho = gerarNomeArquivo();

                if(imwrite(caminho,
                           resultado))
                {
                    cout << "\n================================\n";
                    cout << "Imagem salva com sucesso!\n\n";
                    cout << "Arquivo:\n";
                    cout << caminho << endl;
                    cout << "================================\n";
                }
                else
                {
                    cout << "\nErro ao salvar imagem!\n";
                }

                break;
            }

            case 0:

                cout << "\nEncerrando programa...\n";
                break;

            default:

                cout << "\nOpcao invalida!\n";
        }

    } while(opcao != 0);

    return 0;
}