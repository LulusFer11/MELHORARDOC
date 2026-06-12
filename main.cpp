#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace cv;
using namespace std;

// Mensagem exibida na tela
string mensagemStatus = "Documento carregado com sucesso!";

// Instante em que a mensagem foi atualizada
time_t tempoMensagem = time(nullptr);

// Atualiza a mensagem exibida na janela
void definirMensagem(const string& mensagem)
{
    mensagemStatus = mensagem;
    tempoMensagem = time(nullptr);
}

// Gera automaticamente o nome do arquivo com data e hora
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
              "%Y-%m-%d_%H-%M-%S")
       << ".png";

    return ss.str();
}
void atualizarTela(const Mat& original,
                   const Mat& resultado)
{
    Mat esquerda;
    Mat direita;

    // Converte para BGR se estiver em escala de cinza
    if(original.channels() == 1)
        cvtColor(original, esquerda, COLOR_GRAY2BGR);
    else
        esquerda = original.clone();

    if(resultado.channels() == 1)
        cvtColor(resultado, direita, COLOR_GRAY2BGR);
    else
        direita = resultado.clone();

    // Reduz tamanho das imagens
    resize(
            esquerda,
            esquerda,
            Size(),
            0.5,
            0.5);

    resize(
            direita,
            direita,
            Size(),
            0.5,
            0.5);

    // Espaço superior para os títulos
    copyMakeBorder(
            esquerda,
            esquerda,
            60,0,0,0,
            BORDER_CONSTANT,
            Scalar(0,0,0));

    copyMakeBorder(
            direita,
            direita,
            60,0,0,0,
            BORDER_CONSTANT,
            Scalar(0,0,0));

    // Títulos
    putText(
            esquerda,
            "IMAGEM ORIGINAL",
            Point(20,40),
            FONT_HERSHEY_SIMPLEX,
            0.9,
            Scalar(0,255,0),
            2);

    putText(
            direita,
            "IMAGEM MODIFICADA",
            Point(20,40),
            FONT_HERSHEY_SIMPLEX,
            0.9,
            Scalar(0,255,0),
            2);

    // Junta as duas imagens
    Mat comparacao;

    hconcat(
            esquerda,
            direita,
            comparacao);

    // Barra inferior
    copyMakeBorder(
            comparacao,
            comparacao,
            0,
            120,
            0,
            0,
            BORDER_CONSTANT,
            Scalar(20,20,20));

    // Mensagem de status
    putText(
            comparacao,
            mensagemStatus,
            Point(20, comparacao.rows - 80),
            FONT_HERSHEY_SIMPLEX,
            0.8,
            Scalar(0,255,255),
            2);

    // Primeira linha dos atalhos
    putText(
            comparacao,
            "[C] Cinza   [K] Contraste   [T] Texto   [N] Nitidez",
            Point(20, comparacao.rows - 45),
            FONT_HERSHEY_SIMPLEX,
            0.7,
            Scalar(255,255,255),
            2);

    // Segunda linha dos atalhos
    putText(
            comparacao,
            "[Z] Desfazer   [R] Restaurar   [S] Salvar   [ESC] Sair",
            Point(20, comparacao.rows - 15),
            FONT_HERSHEY_SIMPLEX,
            0.7,
            Scalar(255,255,255),
            2);

    imshow(
            "Melhorador de Documentos",
            comparacao);
}
int main()
{
    Mat original = imread(
            "C:/Users/Luiz Fernandes/Pictures/PROVA/TESTE.png");

    if(original.empty())
    {
        cout << "Erro ao carregar imagem!" << endl;
        return 1;
    }

    Mat resultado = original.clone();
    Mat ultimoEstado = resultado.clone();

    namedWindow(
            "Melhorador de Documentos",
            WINDOW_NORMAL);

    resizeWindow(
            "Melhorador de Documentos",
            1400,
            800);

    atualizarTela(
            original,
            resultado);

    while(true)
    {
        int tecla = waitKey(30);

        // ESC = sair
        if(tecla == 27)
        {
            break;
        }

        // C = Escala de cinza
        else if(tecla == 'c' || tecla == 'C')
        {
            ultimoEstado = resultado.clone();

            if(resultado.channels() == 3)
            {
                cvtColor(
                        resultado,
                        resultado,
                        COLOR_BGR2GRAY);
            }

            definirMensagem("Escala de cinza aplicada!");

            atualizarTela(
                    original,
                    resultado);
        }

        // K = Contraste
        else if(tecla == 'k' || tecla == 'K')
        {
            ultimoEstado = resultado.clone();

            resultado.convertTo(
                    resultado,
                    -1,
                    1.2,
                    0);

            definirMensagem("Contraste aplicado!");

            atualizarTela(
                    original,
                    resultado);
        }

        // T = Destacar texto
        else if(tecla == 't' || tecla == 'T')
        {
            ultimoEstado = resultado.clone();

            Mat cinza;

            if(resultado.channels() == 3)
            {
                cvtColor(
                        resultado,
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
                    2);

            definirMensagem("Texto destacado!");

            atualizarTela(
                    original,
                    resultado);
        }

        // N = Nitidez
        else if(tecla == 'n' || tecla == 'N')
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
                    kernel);

            definirMensagem("Nitidez aplicada!");

            atualizarTela(
                    original,
                    resultado);
        }

        // Z = Desfazer
        else if(tecla == 'z' || tecla == 'Z')
        {
            resultado = ultimoEstado.clone();

            definirMensagem("Ultima acao desfeita!");

            atualizarTela(
                    original,
                    resultado);
        }

        // R = Restaurar original
        else if(tecla == 'r' || tecla == 'R')
        {
            resultado = original.clone();

            definirMensagem("Imagem restaurada!");

            atualizarTela(
                    original,
                    resultado);
        }

        // S = Salvar
        else if(tecla == 's' || tecla == 'S')
        {
            filesystem::create_directories(
                    "C:/Users/Luiz Fernandes/Pictures/PROVA/Saidas");

            string caminho =
                    gerarNomeArquivo();

            if(imwrite(
                    caminho,
                    resultado))
            {
                definirMensagem("Imagem salva com sucesso!");
            }
            else
            {
                definirMensagem("Erro ao salvar imagem!");
            }

            atualizarTela(
                    original,
                    resultado);
        }
    }

    destroyAllWindows();

    return 0;
}