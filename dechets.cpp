#include "dechets.h"

Dechets::Dechets()
{
    nom = "";
    type= "";
    matiere="";
    destinataire="";
    etat="";
    poids=0;
    volume =0;

}
Dechets::Dechets(QString a,QString b ,float c,float d,QString e,QString f,QString g,QDate h)
{
    this->nom=a;
    this->type=b;
    this->poids=c;
    this->volume=d;
    this->etat=e;
    this->destinataire=f;
    this->matiere=g;
    this->Date=h;
}

bool Dechets::ajouter ()
{
    QSqlQuery q ; //me permet dajouter
    QString poids_string=QString::number(poids); // convertir poids en string
    QString volume_string=QString::number(volume);
    q.prepare("insert into Dechets (NOM,TYPE,POIDS,VOLUME,MATIERE,DATEARRIVE,ETAT,DESTINATAIRE,ID_C,ID_COL)""values(:nom,:type,:poids,:volume,:matiere,:date,:etat,:destinataire,1,1)");
    q.bindValue(0,nom); // bindValue : relier les variables (attributs ) ajoutés a les attributs principales dans tableau déchets elli houwa f BD
    q.bindValue(1,type);
    q.bindValue(2,poids_string);
    q.bindValue(3,volume_string);
    q.bindValue(4,matiere);
    q.bindValue(5,Date);
    q.bindValue(6,etat);
    q.bindValue(7,destinataire);
    return q.exec (); // verifer execution
}

bool Dechets::supprimer (int id )
{
    QSqlQuery q ;
    q.prepare("delete from dechets where ID =:id");  //ID = clé primaire elli fel tableau dechets f BD
    q.bindValue(0,id);
    return q.exec ();
}

QSqlQueryModel * Dechets:: afficher () //QSqlQueryModel : afficher tableau dechets f BD
{
    QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM Dechets"); // SELECT * FROM Dechet : afficher des attribus selon tabelau dechets // setQuery --> definir une nouvelle requette
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Poids"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Volume"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Matiere"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("Destinataire"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("Date"));
        return model;
}
QSqlQueryModel * Dechets:: afficher_historique () //QSqlQueryModel : afficher tableau historique f BD
{
    QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM historique"); // SELECT * FROM historique : afficher des attribus selon tabelau historique // setQuery --> definir une nouvelle requette
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATEARRIVE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEVENDUE"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("POIDS"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("MATIERE"));
        return model;
}

/*bool Dechets::modifier(int id)
{
QSqlQuery q ;
QString poids_string=QString::number (poids); // convertir poids en string
QString volume_string=QString::number (volume);
q.prepare("update dechets set nom=:nom,type=:type,matiere=:matiere,destinataire=:destinataire,etat=:etat,volume:=volume,date=:date where id (dechets)=:id (paramétre)"); //dechets :nom tableua BD
q.bindValue(":ID",id);
q.bindValue(":NOM",nom); // bindValue : relier les variables (attributs ) ajoutés a les attributs principales dans tableau déchets
q.bindValue(":TYPE",type);
q.bindValue(":MATIERE",matiere);
q.bindValue(":DESTINATAIRE",destinataire);
q.bindValue(":ETAT",etat);
q.bindValue(":POIDS",poids);
q.bindValue(":VOLUME",volume);
q.bindValue(":DATEARRIVE",Date);
return q.exec (); // verifer execution
}
*/

bool Dechets::modifier(int id, const Dechets& newDechets) {
    QSqlQuery q;
    QString poids_string = QString::number(newDechets.poids);
    QString volume_string = QString::number(newDechets.volume);
    q.prepare("UPDATE dechets SET nom=:nom, type=:type,poids=:poids,volume=:volume, matiere=:matiere, destinataire=:destinataire, etat=:etat , datearrive=:date WHERE id=:id");
    q.bindValue(":id", id);
    q.bindValue(":nom", newDechets.nom);
    q.bindValue(":type", newDechets.type);
    q.bindValue(":poids", poids_string);
    q.bindValue(":volume", volume_string);
    q.bindValue(":matiere", newDechets.matiere);
    q.bindValue(":destinataire", newDechets.destinataire);
    q.bindValue(":etat", newDechets.etat);
    q.bindValue(":date", newDechets.Date);
    return q.exec();
}



QSqlQueryModel * Dechets::trier(int test)
{
    QSqlQueryModel *model=new QSqlQueryModel() ;
    QSqlQuery query ;

    if(test==1)
    {
        query.prepare("SELECT *  FROM dechets ORDER BY type ASC ") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT *  FROM dechets ORDER BY nom  ASC ") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT *  FROM dechets ORDER BY volume ASC ") ;
    }

    if (query.exec()&&query.next())
    {
        model->setQuery(query) ;
    }

return model;

}


QSqlQueryModel * Dechets::recherche(QString id)/*cherche un dechets de meme id*/
{
    QSqlQueryModel * model= new QSqlQueryModel(); // afficher le tableau

    model->setQuery("SELECT * FROM dechets WHERE ID LIKE '"+id+"'  ");

    return model;
}



QChart * Dechets::statistique_chart()
{

    QSqlQuery query0,query1,query2,query3,query4,query5,query6,query8,query7;

    qreal c1_1=0,c1_2=0,c1_3=0,c1_4=0
                ,c2_1=0 ,c2_2=0;

    int totale=0;

        query0.prepare("SELECT * FROM DECHETS");
        query0.exec();

        //Les classes de type violation
        query1.prepare("SELECT * FROM DECHETS WHERE type='plastique' ");
        query1.exec();

        query2.prepare("SELECT * FROM DECHETS WHERE type='verre' ");
        query2.exec();

        query3.prepare("SELECT * FROM DECHETS WHERE poids > 30 ");
        query3.exec();

        query4.prepare("SELECT * FROM DECHETS WHERE poids < 30 ");
        query4.exec();






        while (query0.next()){totale++;}
        //total des classes par rapport au type violation
        while (query1.next()){c1_1++;}
        while (query2.next()){c1_2++;}
        while (query3.next()){c1_3++;}
        while (query4.next()){c1_4++;}
        while (query5.next()){c2_1++;}
        while (query6.next()){c2_2++;}


        totale=totale/2;


        // Assign names to the set of bars used
                QBarSet *set0 = new QBarSet(" type:plastique");
                QBarSet *set1 = new QBarSet("type:verre");
                QBarSet *set2 = new QBarSet("poids:>15");
                QBarSet *set3 = new QBarSet("poids:<15 ");

                // Assign values for each bar
                *set0 << c1_3;
                *set1 << c1_4;
                 *set2<< c2_1;
                 *set3<< c2_2;

                // Add all sets of data to the chart as a whole
                // 1. Bar Chart
                QBarSeries *series = new QBarSeries();

                // 2. Stacked bar chart
                series->append(set0);
                series->append(set1);
                series->append(set2);
                series->append(set3);

                // Used to define the bar chart to display, title
                // legend,
                QChart *chart = new QChart();

                // Add the chart
                chart->addSeries(series);
                chart->setTitle("statistique Dechets");
                chart->setAnimationOptions(QChart::SeriesAnimations);
                chart->setTheme( QChart::ChartThemeBlueCerulean);

                QStringList type;
                    type << "plastique" << "verre"  ;
                // Adds categories to the axes
                    QBarCategoryAxis *axisX = new QBarCategoryAxis();
                        axisX->append(type);
                        chart->addAxis(axisX, Qt::AlignBottom);
                        series->attachAxis(axisX);

                        QValueAxis *axisY = new QValueAxis();
                        axisY->setRange(0,totale);
                        chart->addAxis(axisY, Qt::AlignLeft);
                        series->attachAxis(axisY);


                // 1. Bar chart
               // chart->setAxisX(axis, series);

                // Used to change the palette
                QPalette pal = qApp->palette();

                // Change the color around the chart widget and text
                pal.setColor(QPalette::Window, QRgb(0xffffff));
                pal.setColor(QPalette::WindowText, QRgb(0x404044));

                // Apply palette changes to the application
                qApp->setPalette(pal);
return chart;
}























