#include <iostream>
#include "matrice.hpp"
#include "conversion_image_matrice.hpp"
#include "vecteur.hpp"
#include "lbfgs.hpp"
#include "maillage.hpp"

#include <opencv2/opencv.hpp>

#include <queue>

auto FindThresholdIIntensity(const cv::Mat& dst, double coeff) {
    std::priority_queue<double> heap;
    const auto HEAP_SIZE = dst.rows * dst.cols * coeff;
    for (int y = 0; y < dst.rows; ++y)
        for (int x = 0; x < dst.cols; ++x) {
            auto v = dst.at<double>(y, x);
            if (heap.size() >= HEAP_SIZE) {
                if (heap.top() <= v) continue;
                heap.pop();
            }
            heap.push(v);
        }

    return heap.top();
}

//  g++ -o main.exe -Iinclude -Isrc src/main.cpp src/matrice.cpp src/conversion_image_matrice.cpp src/vecteur.cpp src/lbfgs.cpp src/maillage.cpp

int main(int argc, char *argv[])
{
    //_controlfp(_MCW_EM, _MCW_EM);
    _controlfp_s(0, _EM_INEXACT, _MCW_EM); /* throw all floating point exceptions */

	// On charge une image, et converti en fichier .csv et on crée une matrice image
	// On la remplit avec les niveaux de gris de l'image initiale.
	// Done by achraf

	Matrice Image = image_to_matrice(argv[1]);
	// Image.print();

	// Appel de la Méthode L-BFGS
	// Définition de x=(p,q) initiale
	Vecteur<double> x0(2 * Image.n * Image.m, 0.5);

	cout << " BFGS Algorithme " << endl;
	// Appel de la Méthode L-BFGS
	Vecteur<double> x = BFGS(Image, x0);

	// Définition de la hauteur initiale
	Vecteur<double> h0(Image.n * Image.m, 0);
	h0.init(Image.n, Image.m);

	// Définition de (p*,q*) sortant du BFGS

	Matrice etoile_pq = x.toMatrice(2 * Image.n, Image.m);
	// Matrice etoile_pq(2*Image.n,Image.m,5);
	cout << " BFGS Hauteur Algorithme " << endl;

	Vecteur<double> h_final = BFGS_hauteur(etoile_pq, h0);

    cv::Mat Xat2(Image.n, Image.m, CV_64FC1, h_final.val);

    cv::Mat copy;

    GaussianBlur(Xat2, copy, cv::Size(3, 3), 0, 0);

    cv::Mat permanent;

    GaussianBlur(Xat2, permanent, cv::Size((Xat2.cols / 2) | 1, (Xat2.rows / 2) | 1), 0, 0);

    copy -= permanent;

    copy = cv::max(copy, FindThresholdIIntensity(copy, 0.05));

    normalize(copy, copy, 0, 1, cv::NORM_MINMAX);

    cv::imshow("result", copy);

    cv::Mat img;
    copy.convertTo(img, CV_8U, 255);

    // this is great. It converts your grayscale image into a tone-mapped one, 
    // much more pleasing for the eye
    // function is found in contrib module, so include contrib.hpp 
    // and link accordingly
    cv::Mat falseColorsMap;
    applyColorMap(img, falseColorsMap, cv::COLORMAP_JET);

    cv::imshow("Out", falseColorsMap);

    cv::waitKey();

    if (argc > 2)
    {
        cv::imwrite(argv[2], img);
    }

    /*
	Matrice result = h_final.toMatrice(Image.n, Image.m);

	cout << "Fini" << endl;
	cout << "Génération du maillage... " << endl;
	generate_mesh(result, argv[2]); // Génération du maillage
    */

	return 0;
}