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
  virtual ~Objet();
  virtual void affichage();
  virtual int iswhat();
  virtual QString informations() = 0;
  virtual int CD_DVD();

protected:

  static int compteur_Objet;

};


class Livre : public Objet
{
public:

  Livre();
  Livre(QString auteur, int annee, int page, QString collection, QString titre, QString resume);
  virtual ~Livre();
  void ajouterlivre(QString auteur, int annee, int page, QString collection, QString titre, QString resume);
  static int nb_Livre();
  virtual void affichage();
  virtual int iswhat();
  virtual QString informations();


protected:

  QString m_auteur;
  int m_annee;
  int m_nbPage;
  QString m_collection;
  QString m_titre;
  QString m_resume;
  static int compteur_Livre;

};
