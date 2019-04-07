#include "ressource.h"

class Bibliotheque
{
public:
  Bibliotheque();
  virtual ~Bibliotheque();
  void ajouter(Objet& obj);
  void egale(Bibliotheque biblio1);
  int taille_biblio();
  void affichage();
  void afficher_BaseDeDonnee();
  QString information_biblio(QFile *filename);
  void effacer();   //efface l'objet Bibliotheque
  QFile* sauvegarde(QFile* filename);
  void sauvegarde_biblio(QFile* filename);
  void recherche(QString mot, QFile* filename);
  void load(QFile *filename);
  void tri_donnee(); //ajouter un bouton pour ranger les donnees
  void Clear();
  void deleteId(int numero_objet);

protected:
  QList<Objet*> armoire;
  QList<Objet*> BaseDeDonnee;
  static int compteur_bibliotheque;


};
