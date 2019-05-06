#include "bibliotheque.h"

int Bibliotheque::compteur_bibliotheque = 0;


Bibliotheque::Bibliotheque()
{
  ++compteur_bibliotheque;
}
Bibliotheque::~Bibliotheque()
{
  --compteur_bibliotheque;
    armoire.erase(armoire.begin(), armoire.end()); //question de destruction ???

}

void Bibliotheque::ajouter(Objet& obj)
{
  armoire.push_back(&obj);
  BaseDeDonnee.push_back(&obj);
}

void Bibliotheque::egale(Bibliotheque biblio1)
{    
  for(QList<Objet*>::iterator it = biblio1.armoire.begin(); it != biblio1.armoire.end(); ++it){
      armoire.push_back(*it);
      BaseDeDonnee.push_back(*it);      
  }

}

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

QFile* Bibliotheque::sauvegarde(QFile* filename)
{
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

            out << (*it)->informations();
            out << "\n\n";
        }
    }
    filename->close();
    return filename;
}

void Bibliotheque::sauvegarde_base_de_donnee(QFile* filename)
{
    int cptLivre(1), cptVideo(1), cptDvd(1), cptRessource(1), cptRevue(1), cptCD(1);
    QList<Objet*>::iterator it;
    if (filename->open(QFile::WriteOnly)) {
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
             out << (*it)->informations();
             out << "\n\n";
             BufferList->push_back((*it));
            }
        }
    }
    else {
        qCritical() << "erreur ouverture de fichier fct recherche" << endl;
    }

    if(!BufferList->empty()){
        BaseDeDonnee.swap(*BufferList);
    }

    filename->close();
}



void Bibliotheque::load(QFile *filename)
{
    QTextStream in(filename);
    if(!filename->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",filename->errorString());
    }

    QList<Livre*> listLivre;
    QList<Video*> listVideo;
    QList<DVD*> listDVD;
    QList<RessourceNum*> listRessource;
    QList<Revue*> listRevue;

    QList<QString>::iterator it;
    QList<QString>::iterator it2;

    QString collection, titre, resume, auteur, maison, nom, chemin, editeur, type1;
    int annee, page, duree, piste, taille, articles, id, i(0);


    if(!armoire.empty()){
        armoire.erase(armoire.begin(), armoire.end());
    }

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
                }
                ++i;
            }
            Livre *livreBuffer = new Livre;
            livreBuffer->ajouterlivre(auteur, annee, page, collection, titre, resume, id);
            //listLivre.push_back(livreBuffer);
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
                }
                ++i;
            }
            Video *videoBuffer = new Video;
            videoBuffer->ajoutervideo(duree, auteur, maison, nom, id);
            //listVideo.push_back(videoBuffer);
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
                }
                ++i;
            }
            DVD *dvdBuffer = new DVD;            
            dvdBuffer->ajouterdvd(duree, auteur, maison, nom, piste, 1, id);
           // listDVD.push_back(dvdBuffer);
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
                }
                ++i;
            }
            DVD *dvdBuffer = new DVD;
            dvdBuffer->ajouterdvd(duree, auteur, maison, nom, piste, 0, id);
            //listDVD.push_back(dvdBuffer);
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
                }
                ++i;
            }
            RessourceNum *ressourceBuffer = new RessourceNum;
            ressourceBuffer->ajouterressource(taille, auteur, type1, nom, chemin, id);
            ressourceBuffer->set_format(type1);
            //listRessource.push_back(ressourceBuffer);
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
                }
                ++i;
            }
            Revue *revueBuffer = new Revue;            
            revueBuffer->ajouterrevue(auteur, annee, page, collection, titre, resume, editeur, articles, id);
            //listRevue.push_back(revueBuffer);
            armoire.push_back(revueBuffer);
            i = 0;
         }
        else {
            qCritical() << "erreur dans le fichier .txt (fct load)" << endl;
        }
        QString line = in.readLine();
    }


    //int cpt(0);
   /* if(!armoire.empty()){
        armoire.erase(armoire.begin(), armoire.end());
    }

    for(QList<Livre*>::iterator it3 = listLivre.begin(); it3 != listLivre.end(); ++it3){
        armoire.push_back(listLivre.value(cpt));        
        cpt++;
    }
    cpt=0;
    for(QList<Video*>::iterator it3 = listVideo.begin(); it3 != listVideo.end(); ++it3){
        armoire.push_back(listVideo.value(cpt));
        cpt++;
    }
    cpt=0;
    for(QList<DVD*>::iterator it3 = listDVD.begin(); it3 != listDVD.end(); ++it3){
        armoire.push_back(listDVD.value(cpt));
        cpt++;
    }
    cpt=0;
    for(QList<Revue*>::iterator it3 = listRevue.begin(); it3 != listRevue.end(); ++it3){
        armoire.push_back(listRevue.value(cpt));
        cpt++;
    }
    cpt=0;
    for(QList<RessourceNum*>::iterator it3 = listRessource.begin(); it3 != listRessource.end(); ++it3){
        armoire.push_back(listRessource.value(cpt));
        cpt++;
    }*/

    filename->close(); //non necessaire

}

void Bibliotheque::tri_donnee(tri choix) ///tri de l'armoire et de la base de donnee livre->revue->video->dvd/cd->ressource
{
    //tri a bulle
    //complexiter ameliorable
    //refaire tri rapide avec auteur et id
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




void Bibliotheque::Clear() /// met base de donnee = armoire et l'affiche dans le fichier
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

void Bibliotheque::deleteId(int numero_objet) //numero objet commence a 1 (utilisateur entre 1 ou plus)
{//recoder pour avoir en fonction de l'id
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
    //complexite ameliorable
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
                buffer += "erreur fct sauvegarde";
            }

            buffer += (*it)->informations();
            buffer += "\n\n";
        }

    return buffer;

}


