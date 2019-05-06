#ifndef DVD_H
#define DVD_H
#include "video.h"


class DVD : public Video
{
public:

  DVD();
  DVD(int duree, QString auteur, QString maison, QString nom, int piste, int flag, int id);
  virtual ~DVD();
  void ajouterdvd(int duree, QString auteur, QString maison, QString nom, int piste, int flag, int id);
  static int nb_DVD();
  virtual void affichage();
  virtual int iswhat();
  virtual int CD_DVD();
  virtual QString informations();

protected:

  int m_flag; // si flag vaut 0 c'est un cd si flag vaut 1 c'est un dvd
  int m_nbPiste;
  static int compteur_DVD;

};
#endif
