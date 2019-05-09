#ifndef RESSOURCE_H
#define RESSOURCE_H
#include "dvd.h"

enum format{PDF, DOC, PPT, inconnu};

class RessourceNum: public Objet
{
public:

  RessourceNum();
  RessourceNum(int taille, QString auteur, format type, QString nom, QString chemin, int id, QString emprunt);
  ~RessourceNum();
  void ajouterressource(int taille, QString auteur, QString type, QString nom, QString chemin, int id, QString emprunt);
  static int nb_RessourceNum();
  void affiche_type(); //affiche le type de la ressource numerique (PDF, DOC ...)
  void affichage();
  virtual int iswhat();
  virtual QString informations();
  void set_format(QString mot); //met a jour le type de la ressource avec le QString "mot"

protected:

  format m_type;
  int m_taille;
  QString m_nom;
  QString m_cheminAcces;
  static int compteur_RessourceNum;

};
#endif
