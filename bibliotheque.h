#include "ressource.h"

class Bibliotheque
{
public:
  Bibliotheque();
  virtual ~Bibliotheque();
  void ajouter(Objet& obj);
  void egale(Bibliotheque biblio);
  void affichage();
  void afficher_BaseDeDonnee();
  void effacer();   //efface l'objet Bibliotheque
  QFile* sauvegarde(QFile* filename);
  void recherche(QString mot, QFile* filename);
  void load(QFile *filename);
  void tri_donnee();
  void Clear(QFile *filename);
  void deleteId(int numero_objet);

protected:
  QList<Objet*> armoire;
  QList<Objet*> BaseDeDonnee;
  static int compteur_bibliotheque;


};
