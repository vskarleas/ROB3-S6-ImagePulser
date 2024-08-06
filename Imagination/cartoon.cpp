// #############################################################################
// # file_input cartoon.cpp
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file cartoon.cpp
 * @brief Filtre de cartoon
 *
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

/**
 * @brief Il applique un effet cartoon à une image capturé par le workflow automatique grâce au filtre bilateral de OpenCv
 * 
 * @param input_file le file_input de l'image (image à modifier inclus)
 * @param output_file la destination de l'image (image modifié inclus)
 */
void cartoon_effect(const std::string &input_file, const std::string &output_file)
{
    Mat img = imread(input_file);
    if (img.empty())
    {
        std::cerr << "Erreur de chargement de l'image : " << input_file << std::endl;
        return;
    }

    // Appication du filtre bilatéral selon OpenCV
    Mat img_bilateral;
    bilateralFilter(img, img_bilateral, 9, 75, 75);

    // Convertir en espace de couleur gris
    Mat gray, gray_blurred;
    cvtColor(img_bilateral, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray_blurred, 7); //filter pour diminuer la clarite

    // Detection des contours tout en les mettant en couleur
    Mat edges, edges_colored;
    adaptiveThreshold(gray_blurred, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 2);
    cvtColor(edges, edges_colored, COLOR_GRAY2BGR);

    // Combiner les contours avec l'image originale
    Mat cartoon;
    bitwise_and(img_bilateral, edges_colored, cartoon);

    // Enregistrer le résultat
    imwrite(output_file, cartoon);
}

int main(int argc, char **argv)
{
    std::string input_file = "images/codec-V1.jpeg";
    std::string output_file = "images/codec-V1.jpeg"; //choix explicit pour re-erire l'image pris par l'utilisateur avec un effet cartoon.
    cartoon_effect(input_file, output_file);
    return 0;
}
