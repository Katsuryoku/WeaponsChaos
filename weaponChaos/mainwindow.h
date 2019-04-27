
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <cstdio>
#include <iostream>
#include <queue>
#include <QWidget>


using namespace cv;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow // classe pour la fenêtre principale
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); //constructeur, Auteur Samy
    ~MainWindow(); //destructeur
    void keyPressEvent(QKeyEvent* event); //fonction qui gère les appuis sur les touches haut, bas, droite, gauche, Auteur Maxime


private:
    Ui::MainWindow *ui;
    VideoCapture * webCam_; // objet pour gérer l'acquisition webcam
    CascadeClassifier* cascadeClass; // objet pour la détection

    /*
     * objets utilisés pour mettre en tampon les frames et les rectanges de détections des poings.
    */
    std::queue<cv::Mat> fileFrame;
    std::queue<QPixmap> fileQPix;
    std::vector<cv::Rect> faces;

    Rect rightFist; // enregistre la dernière position du poing droit
    Rect leftFist; // enregistre la dernière position du poing gauche
    bool fistsDetected=false; // les deux poings sont détectés (et seulement deux)
    bool lat=false; // latence entre deux commandes

signals:
    void right(); // signal de mouvement lateral vers la droite, Auteur Samy
    void left(); // signal de mouvement lateral vers la gauche, Auteur Samy
    void rotation(); // signal de rotation, Auteur Samy

private slots :
    void affiche(); // slot activé pour l'affichage dans la fenêtre, Auteur Samy
    void capture(); // slot activé pour la capture, Auteur Samy
    void process(); // slot activé pour la conversion pour l'affichage de la frame, Auteur Samy
    void report(QString s); // déprécié, slot activé pour le debogage, Auteur Samy
    void latence(); // slot activé pour la latence entre deux commandes, Auteur Samy




    void quit(); // slot activé pour quitter l'application, Auteur Maxime

    void reprise(); // slot activé pour finir la latence
};

#endif // MAINWINDOW_H
