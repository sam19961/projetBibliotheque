#ifndef LIVRE_H
#define LIVRE_H
#include <QApplication>
#include <QtDebug>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>

#include "../serveurside/fenserveur.h"
#include "../clientside/clientside.h"

class Objet
{
public:

  Objet();
  Objet(QString auteur, int id, QString emprunt);
  virtual ~Objet();
  virtual void affichage();
  virtual int iswhat(); //
  virtual QString informations(); //renvoie un QString contenant les informations sur les attributs de l'objet
  virtual int CD_DVD();
  int get_id();
  QString get_auteur();
  void prendre(int pris); //permet d'afficher "dispo" ou "pas dispo" pour l'attribut "emprunt"

protected:
  QString m_auteur;
  int m_id;
  QString m_emprunt; //permet d'évaluer si l'objet est disponible ou non
  static int compteur_Objet; // ces compteurs sont défnis au cas ou il est nécessaire de rajouter des fonctionalités
  //mais nous ne les utilisons pas pour l'application à l'état acutel.

};


class Livre : public Objet
{
public:

  Livre();
  Livre(QString auteur, int annee, int page, QString collection, QString titre, QString resume, int id, QString emprunt);
  virtual ~Livre();
  void ajouterlivre(QString auteur, int annee, int page, QString collection, QString titre, QString resume, int id, QString emprunt);
  //ajouterLivre permet de rajouter les pramaètres à un livre déja existant
  static int nb_Livre();
  virtual void affichage();
  virtual int iswhat();
  virtual QString informations();


protected:

  int m_annee;
  int m_nbPage;
  QString m_collection;
  QString m_titre;
  QString m_resume;
  static int compteur_Livre;

};
#endif
