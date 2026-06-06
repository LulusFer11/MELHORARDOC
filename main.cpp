#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void mostrarMenu() {
    cout << "\n===== MELHORADOR DE DOCUMENTOS =====\n";
    cout << "1 - Converter para escala de cinza\n";
    cout << "2 - Melhorar contraste\n";
    cout << "3 - Destacar texto\n";
    cout << "4 - Aplicar nitidez\n";
    cout << "5 - Salvar imagem\n";
    cout << "0 - Sair\n";
    cout << "Escolha: ";
}

int main() {

    // Carrega imagem
    Mat imagem = imread("C:/Users/Luiz Fernandes/Desktop/opencv/imagens/atividade.jpg");

    // Verifica se carregou
    if (imagem.empty()) {
        cout << "Erro ao carregar imagem!" << endl;
        return 1;
    }

    Mat resultado = imagem.clone();

    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;

        switch(opcao) {

            case 1:
                cvtColor(resultado, resultado, COLOR_BGR2GRAY);

                imshow("Resultado", resultado);
                waitKey(0);
                break;

            case 2:
                resultado.convertTo(resultado, -1, 1.5, 20);

                imshow("Resultado", resultado);
                waitKey(0);
                break;

            case 3: {
                Mat cinza;

                cvtColor(resultado, cinza, COLOR_BGR2GRAY);

                threshold(cinza, resultado,
                          120, 255,
                          THRESH_BINARY);

                imshow("Resultado", resultado);
                waitKey(0);
                break;
            }

            case 4: {
                Mat kernel = (Mat_<float>(3,3) <<
                        0, -1, 0,
                        -1, 5, -1,
                        0, -1, 0);

                filter2D(resultado,
                         resultado,
                         resultado.depth(),
                         kernel);

                imshow("Resultado", resultado);
                waitKey(0);
                break;
            }

            case 5:
                imwrite(
                        "C:/Users/Luiz Fernandes/Desktop/opencv/saidas/documento_melhorado.jpg",
                        resultado
                );

                cout << "Imagem salva com sucesso!\n";
                break;

            case 0:
                cout << "Encerrando programa...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while(opcao != 0);

    return 0;
}