#ifndef VIDEO_H
#define VIDEO_H
#include "revue.h"

class Video : public Objet
{
public:

  Video();
  Video(int duree, QString auteur, QString maison, QString nom, int id);
  virtual ~Video();
  void ajoutervideo(int duree, QString auteur, QString maison, QString nom, int id);
  static int nb_Video();
  virtual void affichage();
  virtual int iswhat();
  virtual QString informations();

protected:

  int m_duree;  
  QString m_maisonProduction;
  QString m_nom_video;
  static int compteur_Video;

};
#endif
