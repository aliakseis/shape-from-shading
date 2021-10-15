#include "matrice.hpp"
#include "vecteur.hpp"
#include <vector>
// Définition des facteurs de pénalisation

const double delta = 1;
const double lambda_int = 1;
const double lambda_csmo = 1;

// Définition des constantes de Wolfe

const double w1 = 1.0e-4;
const double w2 = 0.99;

// Définition des précisions

const double epsilon_1 = 100;
const double epsilon_2 = 10e-3;

// Définition des nombres d'itérations maximales

const int i_max = 10000;
const int i_max_Wolfe = 200;

// Définition des fonctions

Vecteur<double> BFGS(const Matrice &Image, Vecteur<double> &x);
Vecteur<double> BFGS_hauteur(const Matrice &Image, Vecteur<double> &x);
double Wolfe(const Matrice &Image, Vecteur<double> &x, Vecteur<double> &z, Vecteur<double> &gradient);
double Wolfe_hauteur(const Matrice &Image, Vecteur<double> &x, Vecteur<double> &z, Vecteur<double> &gradient);
Matrice grad_fonctionnelle(const Matrice &image, const Vecteur<double> &x);
double fonctionnelle_hauteur(const Matrice &h, const Matrice &p, const Matrice &q);
double fonctionnelle(const Matrice &image, const Vecteur<double> &x);
Vecteur<double> grad_fonctionnelle_hauteur(const Matrice &image, const Vecteur<double> &x);
