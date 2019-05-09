#include "bibliotheque.h"

int Bibliotheque::compteur_bibliotheque = 0;


Bibliotheque::Bibliotheque()
{
  ++compteur_bibliotheque;
}
Bibliotheque::~Bibliotheque()
{
  --compteur_bibliotheque;
    armoire.erase(armoire.begin(), armoire.end());

}

//ajoute un objet dans l'armoire et dans la base de donnée
void Bibliotheque::ajouter(Objet& obj)
{
  armoire.push_back(&obj);
  BaseDeDonnee.push_back(&obj);
}

//on aurait pu surcharger l'opérateur "=" de la bibliothèque pour cette fonction
void Bibliotheque::egale(Bibliotheque biblio1)
{    
  for(QList<Objet*>::iterator it = biblio1.armoire.begin(); it != biblio1.armoire.end(); ++it){
      armoire.push_back(*it);
      BaseDeDonnee.push_back(*it);      
  }

}

//affiche l'ensemble de la bibliothèque (uniquement l'armoire)
void Bibliotheque::affichage()
{    
  if(armoire.empty()){
    qDebug() << "la bibliotheque est vide\n";
  }
  else{
    QList<Objet*>::iterator it;
    for(it = armoire.begin(); it != armoire.end(); ++(it)){
      (*it)->affichage();      
    }
  }
}

//idem pour la base de donées
void Bibliotheque::afficher_BaseDeDonnee()
{
    if(BaseDeDonnee.empty()){
      qDebug() << "la base de données est vide\n";
    }
    else{
      QList<Objet*>::iterator it;
      for(it = BaseDeDonnee.begin(); it != BaseDeDonnee.end(); ++(it)){
        (*it)->affichage();
      }
    }
}

//sauvegarde de l'armoire dans un fichier
QFile* Bibliotheque::sauvegarde(QFile* filename)
{
    //on créer des compteurs pour savoir le nombre d'objet du même type présent dans la bibliothèque
    int cptLivre(1), cptVideo(1), cptDvd(1), cptRessource(1), cptRevue(1), cptCD(1);
    QList<Objet*>::iterator it;
    if (filename->open(QFile::WriteOnly)) {
        QTextStream out(filename);
        for(it = armoire.begin(); it!=armoire.end(); ++it){
            if((*it)->iswhat() == 1){
                out << cptLivre;
                ++cptLivre;
            }
            else if((*it)->iswhat() == 2){
                out << cptRevue;
                ++cptRevue;
            }
            else if((*it)->iswhat() == 3){
                out << cptVideo;
                ++cptVideo;
            }
            else if((*it)->iswhat() == 4){
                if(!(*it)->CD_DVD()){
                    out << cptCD;
                    ++cptCD;
                }
                else{
                    out << cptDvd;
                    ++cptDvd;
                }

            }
            else if((*it)->iswhat() == 5){
                out << cptRessource;
                ++cptRessource;
            }
            else {
                out << "erreur fct sauvegarde";
            }

            //une fois qu'on a le numéro de l'objet on prend un QString renvoyé par la fonction "information"
            //afin de le mettre dans le fichier txt
            out << (*it)->informations();
            out << "\n\n";
        }
    }
    filename->close(); //on ferme le fichier manuellement pour éviter toute erreur
    return filename;
}

//idem pour la base de données
void Bibliotheque::sauvegarde_base_de_donnee(QFile* filename)
{
    int cptLivre(1), cptVideo(1), cptDvd(1), cptRessource(1), cptRevue(1), cptCD(1);
    QList<Objet*>::iterator it;
    if (filename->open(QFile::WriteOnly)) { //ouverture du fichier en écriture seule
        QTextStream out(filename);
        for(it = BaseDeDonnee.begin(); it!=BaseDeDonnee.end(); ++it){
            if((*it)->iswhat() == 1){
                out << cptLivre;
                ++cptLivre;
            }
            else if((*it)->iswhat() == 2){
                out << cptRevue;
                ++cptRevue;
            }
            else if((*it)->iswhat() == 3){
                out << cptVideo;
                ++cptVideo;
            }
            else if((*it)->iswhat() == 4){
                if(!(*it)->CD_DVD()){
                    out << cptCD;
                    ++cptCD;
                }
                else{
                    out << cptDvd;
                    ++cptDvd;
                }

            }
            else if((*it)->iswhat() == 5){
                out << cptRessource;
                ++cptRessource;
            }
            else {
                out << "erreur fct sauvegarde";
            }

            out << (*it)->informations();
            out << "\n\n";
        }
    }
    filename->close();

}


void Bibliotheque::recherche(QString mot, QFile* filename) //fenetre differente pas le numero des objets
{   //cherche un mot dans BaseDeDonnee et affiche l'objet en entier dans filename
    QList<Objet*> *BufferList = new QList<Objet*>;
    QTextStream out(filename);
    QList<Objet*>::iterator it;
    if(filename->open(QFile::WriteOnly)){
        for(it=BaseDeDonnee.begin(); it!=BaseDeDonnee.end(); ++it){
         if((*it)->informations().contains(mot, Qt::CaseInsensitive)){
             //on utilise a fonction contains de QString qui est déja codé sur Qt
             out << (*it)->informations();
             out << "\n\n";
             BufferList->push_back((*it));
            }
        }
    }
    else {
        qCritical() << "erreur ouverture de fichier fct recherche" << endl;
    }

    //on utilise un buffer qu'on met dans la base de données à la fin
    if(!BufferList->empty()){
        BaseDeDonnee.swap(*BufferList);
    }

    filename->close();
}



void Bibliotheque::load(QFile *filename)
{
    //on test l'ouverture du fichier
    QTextStream in(filename);
    if(!filename->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",filename->errorString());
    }

    QList<QString>::iterator it, it2;

    //buffer pour récuperer les différents attributs dans le fichier
    QString collection, titre, resume, auteur, maison, nom, chemin, editeur, type1, emprunt;
    int annee, page, duree, piste, taille, articles, id, i(0);

    //on efface l'armoire avant de le remplir avec les nouveaux éléments
    if(!armoire.empty()){
        armoire.erase(armoire.begin(), armoire.end());
    }

    //exemple d'une ligne dans le fichier txt
    //1LIVRE: [titre]:Relativity; [auteur]:Albert Einstein; [annee]:1916
    //les lignes suivantes sont un ensemple de procédés ne s'appliquant qu'à ce type de fichier pour extraire les attributs
    while(!in.atEnd()){
        QString word = in.read(4);
        if(word.contains("LIV")){
            QString line = in.readLine();
            QStringList  fields = line.split(":");
            for(it=fields.begin() + 2; it!=fields.end();++it){
                QStringList fields1 = (*it).split(";");
                switch(i){
                    case 0: titre = fields1.value(0); break;
                    case 1: auteur = fields1.value(0); break;
                    case 2: annee = fields1.value(0).toInt(); break;
                    case 3: page = fields1.value(0).toInt(); break;
                    case 4: collection = fields1.value(0); break;
                    case 5: resume = fields1.value(0); break;
                    case 6: id = fields1.value(0).toInt(); break;
                    case 7: emprunt = fields1.value(0); break;
                }
                ++i;
            }
            Livre *livreBuffer = new Livre;
            livreBuffer->ajouterlivre(auteur, annee, page, collection, titre, resume, id, emprunt);            
            armoire.push_back(livreBuffer);
            i = 0;
         }
        else if(word.contains("VID")){
            QString line = in.readLine();
            QStringList  fields = line.split(":");
            for(it=fields.begin() + 2; it!=fields.end();++it){
                QStringList fields1 = (*it).split(";");
                switch(i){
                    case 0: nom = fields1.value(0); break;
                    case 1: duree = fields1.value(0).toInt(); break;
                    case 2: auteur = fields1.value(0); break;
                    case 3: maison = fields1.value(0); break;
                    case 4: id= fields1.value(0).toInt(); break;
                    case 5: emprunt = fields1.value(0); break;
                }
                ++i;
            }
            Video *videoBuffer = new Video;
            videoBuffer->ajoutervideo(duree, auteur, maison, nom, id, emprunt);            
            armoire.push_back(videoBuffer);
            i = 0;
         }
        else if(word.contains("DVD")){
            QString line = in.readLine();
            QStringList  fields = line.split(":");
            for(it=fields.begin() + 2; it!=fields.end();++it){
                QStringList fields1 = (*it).split(";");
                switch(i){
                    case 0: nom = fields1.value(0);break;
                    case 1: duree = fields1.value(0).toInt(); break;
                    case 2: auteur = fields1.value(0); break;
                    case 3: maison = fields1.value(0); break;
                    case 4: piste = fields1.value(0).toInt(); break;
                    case 5: id= fields1.value(0).toInt(); break;
                    case 6: emprunt = fields1.value(0); break;
                }
                ++i;
            }
            DVD *dvdBuffer = new DVD;            
            dvdBuffer->ajouterdvd(duree, auteur, maison, nom, piste, 1, id, emprunt);           
            armoire.push_back(dvdBuffer);
            i = 0;
         }
        else if(word.contains("CD")){
            QString line = in.readLine();
            QStringList  fields = line.split(":");
            for(it=fields.begin() + 1; it!=fields.end();++it){
                QStringList fields1 = (*it).split(";");
                switch(i){
                    case 0: nom = fields1.value(0);break;
                    case 1: duree = fields1.value(0).toInt(); break;
                    case 2: auteur = fields1.value(0); break;
                    case 3: maison = fields1.value(0); break;
                    case 4: piste = fields1.value(0).toInt(); break;
                    case 5: id = fields1.value(0).toInt(); break;
                    case 6: emprunt = fields1.value(0); break;
                }
                ++i;
            }
            DVD *dvdBuffer = new DVD;
            dvdBuffer->ajouterdvd(duree, auteur, maison, nom, piste, 0, id, emprunt);            
            armoire.push_back(dvdBuffer);
            i = 0;
         }
        else if(word.contains("Res")){
            QString line = in.readLine();
            QStringList  fields = line.split(":");
            for(it=fields.begin() + 2; it!=fields.end();++it){
                QStringList fields1 = (*it).split(";");
                switch(i){
                    case 0: nom = fields1.value(0); break;
                    case 1: auteur = fields1.value(0); break;
                    case 2: taille = fields1.value(0).toInt(); break;
                    case 3: chemin = fields1.value(0); break;
                    case 4: type1 = fields1.value(0); break;
                    case 5: id = fields1.value(0).toInt(); break;
                    case 6: emprunt = fields1.value(0); break;
                }
                ++i;
            }
            RessourceNum *ressourceBuffer = new RessourceNum;
            ressourceBuffer->ajouterressource(taille, auteur, type1, nom, chemin, id, emprunt);
            ressourceBuffer->set_format(type1);            
            armoire.push_back(ressourceBuffer);
            i = 0;
         }
        else if(word.contains("REV")){
            QString line = in.readLine();
            QStringList  fields = line.split(":");
            for(it=fields.begin() + 2; it!=fields.end();++it){
                QStringList fields1 = (*it).split(";");
                switch(i){
                    case 0: titre = fields1.value(0); break;
                    case 1: auteur = fields1.value(0); break;
                    case 2: annee = fields1.value(0).toInt(); break;
                    case 3: page = fields1.value(0).toInt(); break;
                    case 4: collection = fields1.value(0); break;
                    case 5: resume = fields1.value(0); break;
                    case 6: editeur = fields1.value(0); break;
                    case 7: articles = fields1.value(0).toInt(); break;
                    case 8: id = fields1.value(0).toInt(); break;
                    case 9: emprunt = fields1.value(0); break;
                }
                ++i;
            }
            Revue *revueBuffer = new Revue;            
            revueBuffer->ajouterrevue(auteur, annee, page, collection, titre, resume, editeur, articles, id, emprunt);            
            armoire.push_back(revueBuffer);
            i = 0;
         }
        //on gère le cas ou le mot n'est pas contenu dans le fichier
        else {
            qCritical() << "erreur dans le fichier .txt (fct load)" << endl;
        }
        QString line = in.readLine();
    }


    filename->close();

}

void Bibliotheque::tri_donnee(tri choix) ///tri de l'armoire et de la base de donnee livre->revue->video->dvd/cd->ressource
{
    //tri a bulle soit en fonction de l'auteur soit en fonction de l'id
    QList<Objet*>::iterator it1, it2;
    int i(0), j(0);

    if(choix == auteur){
        for(it1 = armoire.begin(); it1 != armoire.end(); ++it1){
            for(it2 = it1; it2 != armoire.end(); ++it2){
                if((*it1)->get_auteur().front().toLower() > (*it2)->get_auteur().front().toLower()){
                    armoire.swap(i, j);
                }
                ++j;
            }
            ++i;
            j = i;
        }
    }
    else {
        for(it1 = armoire.begin(); it1 != armoire.end(); ++it1){
            for(it2 = it1; it2 != armoire.end(); ++it2){
                if((*it1)->get_id() > (*it2)->get_id()){
                    armoire.swap(i, j);
                }
                ++j;
            }
            ++i;
            j = i;
        }
    }
}




void Bibliotheque::Clear() /// met base de données = armoire
{    
    QList<Objet*>::iterator it;
    BaseDeDonnee.erase(BaseDeDonnee.begin(), BaseDeDonnee.end());
    if(!armoire.empty()){        
        for(it = armoire.begin(); it != armoire.end(); ++it){
            BaseDeDonnee.push_back(*it);
        }
    }
    else {
        qCritical() << "erreur, armoire vide fonction clear" << endl;
    }                
}

void Bibliotheque::deleteId(int numero_objet) //supprime de l'armoire de la base de données l'élement avec son numero
{
    int cpt(0);
    for(QList<Objet*>::iterator it = armoire.begin(); it != armoire.end(); ++it){
        if(cpt == (numero_objet-1)){
            armoire.removeAt(cpt);
            break;
        }
        ++cpt;
    }
    cpt = 0;
    for(QList<Objet*>::iterator it = BaseDeDonnee.begin(); it != BaseDeDonnee.end(); ++it){
        if(cpt == (numero_objet-1)){
            BaseDeDonnee.removeAt(cpt);
            break;
        }
        ++cpt;
    }
}

//met les attributs de chaque objet dans un fichier
QString Bibliotheque::information_biblio(QFile *filename)
{
    QString buffer;
    QTextStream in(filename);
    if(!filename->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",filename->errorString());
    }
    while(!in.atEnd()){
        QString line = in.readLine();
        buffer += line;
        buffer += "\n";
    }
    return buffer;
}

int Bibliotheque::taille_biblio()
{
    int i(0);
    for(QList<Objet*>::iterator it = armoire.begin(); it != armoire.end(); ++it){
        ++i;
    }
    return i;
}

int Bibliotheque::doublon()
{
    //complexite ameliorable, ici en O(n^2) dans le pire des cas
    int i(0), j(0), indice(-1), nb_fois(0);
    QList<Objet*>::iterator it, it2;
    for(it = armoire.begin(); it != armoire.end(); ++it){        
        for(it2 = it; it2 != armoire.end(); ++it2){
            if((it2 != it) && ((*it2)->get_id() == (*it)->get_id())){
                ++nb_fois;
                indice = j;                
            }
            ++j;            
        }
        ++i;
        j = i;        
    }

    if(indice != -1)
        armoire.removeAt(indice);

    return nb_fois;
}

//renvoie un QString contenant les informations des différents objets dans l'armoire
QString Bibliotheque::information_armoire()
{
    QString buffer;
    int cptLivre(1), cptVideo(1), cptDvd(1), cptRessource(1), cptRevue(1), cptCD(1);
    QList<Objet*>::iterator it;
        for(it = armoire.begin(); it!=armoire.end(); ++it){
            if((*it)->iswhat() == 1){
                buffer += QString::number(cptLivre);
                ++cptLivre;
            }
            else if((*it)->iswhat() == 2){
                buffer += QString::number(cptRevue);
                ++cptRevue;
            }
            else if((*it)->iswhat() == 3){
                buffer += QString::number(cptVideo);
                ++cptVideo;
            }
            else if((*it)->iswhat() == 4){
                if(!(*it)->CD_DVD()){
                    buffer += QString::number(cptCD);
                    ++cptCD;
                }
                else{
                    buffer += QString::number(cptDvd);
                    ++cptDvd;
                }

            }
            else if((*it)->iswhat() == 5){
                buffer += QString::number(cptRessource);
                ++cptRessource;
            }
            else {
                buffer += "erreur fct information_armoire";
            }

            buffer += (*it)->informations();
            buffer += "\n\n";
        }

    return buffer;

}

//fait passer l'attribut d'un objet de "disponible" à "non disponible"
void Bibliotheque::emprunter_objet(int numero_objet)
{
    int cpt(0);
    for(QList<Objet*>::iterator it = armoire.begin(); it != armoire.end(); ++it){
        if(cpt == (numero_objet-1)){
            (*it)->prendre(1);
            break;
        }
        ++cpt;
    }
    cpt = 0;
    for(QList<Objet*>::iterator it = BaseDeDonnee.begin(); it != BaseDeDonnee.end(); ++it){
        if(cpt == (numero_objet-1)){
            (*it)->prendre(1);
            break;
        }
        ++cpt;
    }
}

//fait passer l'attribut d'un objet de "non disponible" à "disponible"
void Bibliotheque::rendre_objet(int numero_objet)
{
    int cpt(0);
    for(QList<Objet*>::iterator it = armoire.begin(); it != armoire.end(); ++it){
        if(cpt == (numero_objet-1)){
            (*it)->prendre(0);
            break;
        }
        ++cpt;
    }
    cpt = 0;
    for(QList<Objet*>::iterator it = BaseDeDonnee.begin(); it != BaseDeDonnee.end(); ++it){
        if(cpt == (numero_objet-1)){
            (*it)->prendre(0);
            break;
        }
        ++cpt;
    }

}

