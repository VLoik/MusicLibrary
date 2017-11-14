#ifndef ARTISTDIALOG_H
#define ARTISTDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataWidgetMapper>
#include <musicmodel.h>

namespace Ui {
class ArtistDialog;
}

class ArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistDialog(QWidget *parent = 0);
    void setModel(MusicModel*model);
    void setModelIndex(const QModelIndex &model);
    void accept();
    bool addArtist(MusicModel *model, const QModelIndex &parent);
    ~ArtistDialog();

private slots:
    void on_brouse_button_clicked();

private:
    Ui::ArtistDialog *ui;
    QDataWidgetMapper m_mapper;
    QPixmap image;
};

#endif // ARTISTDIALOG_H
