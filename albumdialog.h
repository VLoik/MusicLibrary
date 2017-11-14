#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataWidgetMapper>
#include <musicmodel.h>

namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *parent = 0);
    void setModel(MusicModel*model);
    void setModelIndex(const QModelIndex &model);
    void accept();
    bool addAlbum(MusicModel *model, const QModelIndex &parent);
    ~AlbumDialog();

private slots:
    void on_brouse_button_clicked();

private:
    Ui::AlbumDialog *ui;
    QDataWidgetMapper m_mapper;
    QPixmap image;
};

#endif // ALBUMDIALOG_H
