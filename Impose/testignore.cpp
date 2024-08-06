// #############################################################################
// # File testignore.cpp
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <opencv2/opencv.hpp>
#include <iostream>

/**
 * @brief Programme principal pour tester les opérations de HSV et de caméra via OpenCV.
 *
 * Ce programme capture des images à partir d'une caméra, extrait le canal rouge de l'image, binarise ce canal,
 * et affiche à la fois l'image originale et l'image binarisée.
 *
 * @return int Retourne 0 si l'exécution est réussie, -1 en cas d'erreur d'ouverture du périphérique de capture vidéo.
 */
int main()
{
    // Charge l'image couleur originale depuis la caméra
    cv::VideoCapture capture(2);

    if (!capture.isOpened())
    {
        std::cerr << "Error opening video capture device!" << std::endl;
        return -1;
    }

    /* Création des images pour le flux de traitement */
    cv::Mat color_image;
    cv::Mat redChannel;
    cv::Mat redBinary;

    while (true)
    {
        /* Capture un cadre de la caméra */
        if (!capture.read(color_image))
        {
            std::cerr << "Error: Captured empty color_image" << std::endl;
            break;
        }

        // Divise l'image en ses canaux de couleur BGR individuels
        std::vector<cv::Mat> channels;
        cv::split(color_image, channels);

        // channels[2] contient le canal rouge
        redChannel = channels[2]; // contient le canal rouge (channels[0] -> bleu, channels[1] -> vert)

        // Binarise le canal rouge
        // Ici, vous pouvez ajuster la valeur du seuil (128 dans cet exemple)
        // et la valeur maximale (255, typique pour les images binaires)
        double thresh = 128; // Seuil en dessous duquel tout devient noir
        double maxval = 255; // Valeur à attribuer si la valeur du pixel est supérieure au seuil (blanc)
        cv::threshold(redChannel, redBinary, thresh, maxval, cv::THRESH_BINARY);

        // Affiche les images originale et binarisée
        cv::imshow("Original Image", color_image);
        cv::imshow("Binarized Red Channel", redBinary);
        cv::waitKey(0); // Attend une pression de touche pour fermer les fenêtres

        return 0;
    }
}
