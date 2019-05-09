#ifndef BIBLIOTHEK_H //évite les inclusions multiples
#define BIBLIOTHEK_H

#include "ressource.h"

enum tri{auteur, id};

class Bibliotheque
{
public:
  Bibliotheque();
  virtual ~Bibliotheque(); //tous les destructeurs sont virtualisés pour appelé celui de la fille en cas d'héritage (pas nécessaire ici)
  void ajouter(Objet& obj);
  void egale(Bibliotheque biblio1); //égalise les armoires et les base de données de 2 bibliothèques
  int taille_biblio(); //renvoi la taille de l'armoire
  void affichage(); //affiche les élements présents dans l'armoire
  void afficher_BaseDeDonnee(); //affiche les éléments présents dans la base de données
  QString information_armoire(); //renvoie un QString avec les éléments de l'armoire
  QString information_biblio(QFile *filename); //renvoie un QString avec les élements d'une bibliothèque présents dans un fichier
  QFile* sauvegarde(QFile* filename);
  void sauvegarde_base_de_donnee(QFile* filename); //sauvegarde la base de donnée
  void recherche(QString mot, QFile* filename);
  void load(QFile *filename);
  void tri_donnee(tri choix); //trier en fonction de: auteur ou id
  void Clear(); //armoire = BaseDedonnee
  void deleteId(int numero_objet);
  int doublon(); //efface les éventuels doublons dans la bibliothèque
  void emprunter_objet(int numero_objet);
  void rendre_objet(int numero_objet);

protected:
  QList<Objet*> armoire;
  QList<Objet*> BaseDeDonnee; //utile pour la partie "recherche"
  static int compteur_bibliotheque;


};
#endif
