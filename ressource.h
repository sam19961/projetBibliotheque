#include "dvd.h"

enum format{PDF, DOC, PPT, inconnu};

class RessourceNum: public Objet
{
public:

  RessourceNum();
  RessourceNum(int taille, QString auteur, format type, QString nom, QString chemin);
  ~RessourceNum();
  void ajouterressource(int taille, QString auteur, QString type, QString nom, QString chemin);
  static int nb_RessourceNum();
  void affiche_type();
  void affichage();
  virtual int iswhat();
  virtual QString informations();
  void set_format(QString mot);

protected:

  QString m_auteur;
  format m_type;
  int m_taille;
  QString m_nom;
  QString m_cheminAcces;
  static int compteur_RessourceNum;

};
