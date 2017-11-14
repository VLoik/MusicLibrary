#ifndef ITEM_H
#define ITEM_H
#include <QList>
#include <QDataStream>
#include <QDebug>
#include <QPixmap>
#include <QTime>

class Artist;
class Album;
class Song;

class Item
{
public:
    Item();
    Item(QString name);
    ~Item();
    Item* parent() {return m_parent;}
    void setParent(Item* p);
    void insertChild(Item *c, int pos = -1);
    Item* childAt(int pos) const;
    int indexOf(Item* c) const {return m_children.indexOf(c,0);}
    int childCount() const {return m_children.count();}
    void setName(QString n) {m_name = n;}
    QString name() const {return m_name;}
    QString comment() const {return m_comment;}
    void setComment(QString c) {m_comment = c;}
    Item* takeChild(int pos);
    virtual Artist *toArtist(){return 0;}
    virtual Album *toAlbum(){return 0;}
    virtual Song *toSong(){return 0;}

private:
    Item* m_parent;
    QList<Item*> m_children;

    QString m_name;
    QString m_comment;
};

class Artist: public Item
{
    QPixmap m_photo;
    QString m_country;
public:
    Artist():Item(){}
    Artist(QString name):Item(name){}
    const QPixmap photo() const {return m_photo;}
    void setPhoto(QPixmap photo){m_photo = photo;}
    const QString country() const {return m_country;}
    void setCountry(QString c){m_country = c;}
    Artist *toArtist(){return this;}
    Album *toAlbum(){return 0;}
    Song *toSong(){return 0;}


};

class Album: public Item
{
    int m_year;
    QPixmap m_cover;
    QString m_genre;

public:
    Album():Item(){}
    Album(QString name):Item(name){}
    const QPixmap cover() const {return m_cover;}
    void setCover(QPixmap cov){m_cover = cov;}
    const QString genre() const {return m_genre;}
    void setGenre(QString c){m_genre = c;}
    const int year() const {return m_year;}
    void setYear(int y) {m_year = y;}
    Artist *toArtist(){return 0;}
    Album *toAlbum(){return this;}
    Song *toSong(){return 0;}

};

class Song: public Item
{
    QTime m_duration;


public:
    int m_rate;
    Song():Item(){}
    Song(QString name):Item(name){}
    const QTime duration() const {return m_duration;}
    void setDuration(QTime d){m_duration = d;}
    const int rate() const {return m_rate;}
    void setRate(int r) {m_rate = r;}
    Artist *toArtist(){return 0;}
    Album *toAlbum(){return 0;}
    Song *toSong(){return this;}
};

QDataStream& operator <<(QDataStream&stream, const Artist& artist);
QDataStream& operator <<(QDataStream&stream, const Album& album);
QDataStream& operator <<(QDataStream&stream, const Song& song);

QDataStream& operator >>(QDataStream &stream, Artist &artist);
QDataStream& operator >>(QDataStream &stream, Album &album);
QDataStream& operator >>(QDataStream &stream, Song &song);
#endif // ITEM_H
