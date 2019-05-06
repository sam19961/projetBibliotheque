#ifndef LIVRE_H
#define LIVRE_H
#include <QApplication>
#include <QtDebug>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class Objet
{
public:

  Objet();
  Objet(QString auteur, int id);
  virtual ~Objet();
  virtual void affichage();
  virtual int iswhat();
  virtual QString informations();
  virtual int CD_DVD();
  int get_id();
  QString get_auteur();

protected:
  QString m_auteur;
  int m_id;
  static int compteur_Objet;

};


class Livre : public Objet
{
public:

  Livre();
  Livre(QString auteur, int annee, int page, QString collection, QString titre, QString resume, int id);
  virtual ~Livre();
  void ajouterlivre(QString auteur, int annee, int page, QString collection, QString titre, QString resume, int id);
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
