#include "conversion_image_matrice.hpp"

#include <opencv2/opencv.hpp>

// IL faut convertir notre image en matrice

// l'intermédiaire c'est le csv

/*
Matrice image_to_matrice(string nom_fichier)
{

    ifstream image(nom_fichier.c_str(), ios::in);

    int n = 0;
    int m = 0;
    string line;
    char virgule;
    if (image.is_open())
    {
        image >> n >> virgule >> m;
        // image>>m;
        Matrice Image(n, m);
        printf("n = %d, m = %d\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {   
                if(j<m){
                image >> Image(i, j) >> virgule;
                }
                else{
                    image>>Image(i,j);
                }
            }
        }
        image.close();
        return Image;
    }

    else
    {
        cout << "Unable to open file";
        exit(0);
    }
}
*/

Matrice image_to_matrice(string nom_fichier)
{
    //auto image = cv::imread(nom_fichier, cv::IMREAD_GRAYSCALE);

    cv::Mat img = cv::imread(nom_fichier);// , cv::IMREAD_GRAYSCALE);


    std::vector<cv::Mat> bgr;
    split(img, bgr);

    for (int i = 1; i < bgr.size(); ++i)
        cv::max(bgr[0], bgr[i], bgr[0]);

    cv::Mat image = bgr[0];

    Matrice Image(image.rows, image.cols);
    for (int y = 0; y < image.rows; ++y)
        for (int x = 0; x < image.cols; ++x)
        {
            Image(y + 1, x + 1) = image.at<uchar>(y, x);
        }

    return Image;
}
