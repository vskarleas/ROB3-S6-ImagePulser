// #############################################################################
// # File image_capture.c
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file image_capture.cpp
 * @brief le programme fait la capture de l'image et utilise les touches du clavier pour controler la camera
 *
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h>  // UNIX standard function definitions
#include <cstring>

cv::Mat capturedFrame;
bool imageCaptured = false;
bool programShouldFinish = false; // Indicateur pour terminer le programme
int time_id = 0;

// Constantes pour les étapes de mouvement et positions initiales
const int STEP_SIZE = 5;
int posX = 120; // Position initiale en X
int posY = 120; // Position initiale en Y

/**
 * @brief Configure le port série
 *
 * Cette fonction ouvre et configure le port série spécifié.
 *
 * @param device Le chemin du périphérique série (ex. : /dev/ttyACM0)
 * @return int Le descripteur de file_input du port série, ou -1 en cas d'erreur
 */
int open_serial(const char *device)
{
    int fd = open(device, O_RDWR | O_NOCTTY | O_SYNC); // Ouvre le périphérique série

    if (fd < 0)
    {
        std::cerr << "Error opening " << device << ": " << strerror(errno) << std::endl;
        return -1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0)
    {
        std::cerr << "Error from tcgetattr: " << strerror(errno) << std::endl;
        return -1;
    }

    cfsetospeed(&tty, B9600); // Configure la vitesse de transmission à 9600 baud
    cfsetispeed(&tty, B9600); // Configure la vitesse de réception à 9600 baud

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    tty.c_iflag &= ~IGNBRK; // Désactive le traitement des interruptions
    tty.c_lflag = 0;        // Désactive le mode canonique, les échos, etc.
    tty.c_oflag = 0;        // Désactive les retards et les remappages
    tty.c_cc[VMIN] = 0;     // Lecture non bloquante
    tty.c_cc[VTIME] = 5;    // Timeout de 0.5 secondes

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Désactive le contrôle de flux logiciel

    tty.c_cflag |= (CLOCAL | CREAD);   // Active la lecture et ignore les contrôles de modem
    tty.c_cflag &= ~(PARENB | PARODD); // Désactive la parité
    tty.c_cflag &= ~CSTOPB;            // Utilise un bit d'arrêt
    tty.c_cflag &= ~CRTSCTS;           // Désactive le contrôle de flux matériel

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        std::cerr << "Error from tcsetattr: " << strerror(errno) << std::endl;
        return -1;
    }
    return fd;
}

/**
 * @brief Envoie les coordonnées au port série
 *
 * @param x La coordonnée X à envoyer
 * @param y La coordonnée Y à envoyer
 */
void send_coordinates(int x, int y)
{
    static int fd = open_serial("/dev/ttyACM0"); // Ajustez selon votre système
    if (fd < 0)
        return;

    char buffer[50];
    int n = snprintf(buffer, sizeof(buffer), "%d %d\n", x, y);
    int w = write(fd, buffer, n);
    if (w != n)
    {
        std::cerr << "Error writing to serial port: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Coordinates X = " << x << ", Y = " << y << " sent." << std::endl;
    }
}

/**
 * @brief Gère les événements de la souris dans la fenêtre "Decision"
 *
 * @param event L'événement de la souris
 * @param x La position X de la souris
 * @param y La position Y de la souris
 * @param userdata Données utilisateur
 */
void on_decision_mouse(int event, int x, int y, int, void *)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        // Ouverture du file_input du decision utilisé par UI pour savoir si l'image a été gardée ou non
        std::ofstream decisionFile("tmp3209803-ext34V3");

        if (x >= 50 && x <= 150 && y >= 25 && y <= 75) // Bouton "Keep"
        {
            // Vérification si le dossier "images" existe
            std::string folder = "images";
#if defined(_WIN32)
            _mkdir(folder.c_str());
#else
            mkdir(folder.c_str(), 0777);
#endif

            // Sauvegarde de l'image dans le dossier "images"
            std::string filename = folder + "/codec-V1.jpeg";
            if (cv::imwrite(filename, capturedFrame))
            {
                std::cout << "Image captured and saved as '" << filename << "'" << std::endl;
                decisionFile << "1";
            }
            else
            {
                std::cerr << "Error: Could not save the image" << std::endl;
                decisionFile << "0";
            }
        }
        else if (x >= 160 && x <= 260 && y >= 25 && y <= 75) // Bouton "Discard"
        {
            std::cout << "Image discarded" << std::endl;
            decisionFile << "0";
        }

        decisionFile.close();
        cv::destroyWindow("Captured Image");
        cv::destroyWindow("Decision");
        imageCaptured = false; // Réinitialise le drapeau pour capturer de nouvelles images

        programShouldFinish = true; // Définit le drapeau pour terminer le programme
    }
}

/**
 * @brief Capture l'image si la souris est dans la zone désignée
 *
 * @param event L'événement de la souris
 * @param x La position X de la souris
 * @param y La position Y de la souris
 * @param userdata Données utilisateur
 */
void on_mouse(int event, int x, int y, int, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN && !imageCaptured)
    {
        if (x >= 10 && x <= 110 && y >= 10 && y <= 60)
        {
            cv::Mat *frame = static_cast<cv::Mat *>(userdata);
            cv::Size targetSize(640, 480); // Résolution 480p

            // Retirer la zone du bouton de l'image
            cv::Mat frameWithoutButton = frame->clone();
            cv::rectangle(frameWithoutButton, cv::Point(10, 10), cv::Point(110, 60), cv::Scalar(0, 0, 0), cv::FILLED);

            // Calculer le ratio d'aspect
            double aspectRatio = static_cast<double>(frameWithoutButton.cols) / frameWithoutButton.rows;
            int targetWidth, targetHeight;

            if (frameWithoutButton.cols > frameWithoutButton.rows)
            {
                targetHeight = targetSize.height;
                targetWidth = static_cast<int>(targetSize.height * aspectRatio);
            }
            else
            {
                targetWidth = targetSize.width;
                targetHeight = static_cast<int>(targetSize.width / aspectRatio);
            }

            // Redimensionner l'image
            cv::Mat resizedFrame;
            cv::resize(frameWithoutButton, resizedFrame, cv::Size(targetWidth, targetHeight));

            // Recadrer au centre
            int xOffset = (targetWidth - targetSize.width) / 2;
            int yOffset = (targetHeight - targetSize.height) / 2;
            cv::Rect cropRegion(xOffset, yOffset, targetSize.width, targetSize.height);
            capturedFrame = resizedFrame(cropRegion);

            // Afficher l'image capturée à l'utilisateur
            cv::imshow("Captured Image", capturedFrame);

            // Créer des boutons pour la décision de l'utilisateur
            cv::namedWindow("Decision");
            cv::Mat decisionMat(100, 300, CV_8UC3, cv::Scalar(255, 255, 255));
            cv::rectangle(decisionMat, cv::Point(50, 25), cv::Point(150, 75), cv::Scalar(0, 255, 0), cv::FILLED);
            cv::putText(decisionMat, "Keep", cv::Point(70, 55), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
            cv::rectangle(decisionMat, cv::Point(160, 25), cv::Point(260, 75), cv::Scalar(0, 0, 255), cv::FILLED);
            cv::putText(decisionMat, "Discard", cv::Point(170, 55), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
            cv::imshow("Decision", decisionMat);

            cv::setMouseCallback("Decision", on_decision_mouse);

            imageCaptured =

 true; // Définit le drapeau pour empêcher les captures multiples
        }
    }
}


int main(int argc, char **argv)
{
    // Ouvre la caméra par défaut (généralement la première détectée par le système)
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open video capture" << std::endl;
        return -9;
    }

    // Définit la résolution de la caméra à une valeur plus élevée si elle est prise en charge par la caméra
    // Ne fonctionne pas sur tous les ordinateurs
    // Désactivez les deux lignes suivantes pour les caméras avec une résolution inférieure
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // Crée une fenêtre pour afficher le flux vidéo
    cv::namedWindow("Video Feed");

    cv::Mat frame;
    cv::setMouseCallback("Video Feed", on_mouse, &frame);

    while (true)
    {
        if (cap.read(frame))
        {
            // Dessine le bouton sur l'image
            cv::rectangle(frame, cv::Point(10, 10), cv::Point(110, 60), cv::Scalar(0, 255, 0), cv::FILLED);
            cv::putText(frame, "Capture", cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);

            // Affiche l'image
            cv::imshow("Video Feed", frame);

            int key = cv::waitKey(30); // Attend un événement clé pendant un "délai" (30 millisecondes)
            if (key == 'q' || key == 27)
            { // 'q' ou ESC pour quitter
                break;
            }
            else if (key == 'a')
            {                                           // Flèche gauche
                posX = std::min(640, posX + STEP_SIZE); // Supposant 640 comme largeur maximale
                if (posX > 180)
                {
                    posX = 180;
                }
            }
            else if (key == 'd')
            { // Flèche droite
                posX = std::max(0, posX - STEP_SIZE);
            }
            else if (key == 'w')
            { // Flèche haut
                posY = std::max(0, posY - STEP_SIZE);
            }
            else if (key == 's')
            {                                           // Flèche bas
                posY = std::min(480, posY + STEP_SIZE); // Supposant 480 comme hauteur maximale
                if (posY > 130)
                {
                    posY = 130;
                }
            }

            // Envoie les coordonnées mises à jour à l'Arduino
            send_coordinates(posX, posY);
        }
        else
        {
            std::cerr << "Error: Could not read frame from video capture" << std::endl;
        }

        // Quitte la boucle si l'utilisateur appuie sur la touche 'q' ou si le programme doit se terminer
        if (cv::waitKey(30) == 'q' || programShouldFinish)
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
