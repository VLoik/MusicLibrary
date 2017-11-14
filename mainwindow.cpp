#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "albumdialog.h"
#include "artistdialog.h"
#include "ratingdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->treeView);

    model = new MusicModel();
    ui->treeView->setModel(model);

    RatingDelegate *delegate = new RatingDelegate();
    ui->treeView->setItemDelegateForColumn(2, delegate);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->edit_action->setEnabled(false);
    ui->delete_action->setEnabled(false);
    ui->add_album_action->setEnabled(false);
    ui->add_song_action->setEnabled(false);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setModified()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(update_active_actions(QModelIndex)));

    myappTranslator.load(QString("lab3_") + QLocale::system().name());
    qApp->installTranslator(&myappTranslator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_artist_action_triggered()
{
    ArtistDialog *dialog = new ArtistDialog();
    dialog->addArtist(model, QModelIndex());
    setModified();
}

void MainWindow::on_delete_action_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    model->removeRow(cur_index.row(), cur_index.parent());

    update_active_actions(ui->treeView->selectionModel()->currentIndex());
    setModified();
}

void MainWindow::on_edit_action_triggered()
{
    Item *cur_item=static_cast<Item*>(ui->treeView->selectionModel()->currentIndex().internalPointer());
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    QModelIndex parent = ui->treeView->selectionModel()->currentIndex().parent();

    if(cur_item->toAlbum())
    {
            AlbumDialog *album = new AlbumDialog();
            album->setModel(model);
            album->setModelIndex(cur_index);
            album->show();
    }
    else
    if(cur_item->toArtist())
    {
            ArtistDialog *artist = new ArtistDialog();
            artist->setModel(model);
            artist->setModelIndex(cur_index);
            artist->show();
    }
    else
    if(cur_item->toSong()) return;

}

void MainWindow::on_add_album_action_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    AlbumDialog *album= new AlbumDialog();
    album->addAlbum(model, cur_index);
    setModified();
}

void MainWindow::on_add_song_action_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();


    int row = model->rowCount(cur_index);
    model->insertRow(row, cur_index);

    setModified();
}

bool MainWindow::on_save_action_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save"), tr("/home/vladimir"), tr("*.db"));
    if (fileName.isEmpty()) return false;
    else
    {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            out << *(model->m_root);
            file.close();
            setWindowModified(false);
            return true;
        }

    }
    return false;

}
void MainWindow::setModified()
{
    setWindowModified(true);
}

void MainWindow::update_active_actions(QModelIndex index)
{
    Item *cur_item=static_cast<Item*>(index.internalPointer());
    if(!cur_item or !index.isValid())
    {
        ui->edit_action->setEnabled(false);
        ui->delete_action->setEnabled(false);
        ui->add_album_action->setEnabled(false);
        ui->add_song_action->setEnabled(false);
        return;
    }
    if(cur_item->toAlbum())
    {
        ui->edit_action->setEnabled(true);
        ui->delete_action->setEnabled(true);
        ui->add_album_action->setEnabled(false);
        ui->add_song_action->setEnabled(true);
    }
    if(cur_item->toSong())
    {
        ui->edit_action->setEnabled(true);
        ui->delete_action->setEnabled(true);
        ui->add_album_action->setEnabled(false);
        ui->add_song_action->setEnabled(false);
    }
    if(cur_item->toArtist())
    {
        ui->edit_action->setEnabled(true);
        ui->delete_action->setEnabled(true);
        ui->add_album_action->setEnabled(true);
        ui->add_song_action->setEnabled(false);
    }


}

void MainWindow::on_load_action_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open"), tr("/home/vladimir"), tr("*.db"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            delete model->m_root;
            setWindowModified(false);
            model->m_root = new Item();
            ui->treeView->reset();
            in >> *(model->m_root);
            file.close();
            ui->edit_action->setEnabled(false);
            ui->delete_action->setEnabled(false);
            ui->add_album_action->setEnabled(false);
            ui->add_song_action->setEnabled(false);
        }

    }
    ui->treeView->reset();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(isWindowModified())
    {
        QMessageBox::StandardButton choose = QMessageBox::warning(this, tr("Saving Document"), tr("Detected change. Do you want to save it?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Discard);
        switch (choose)
        {
          case QMessageBox::Save:
              if(!this->on_save_action_triggered())
              {
                  event->ignore();
                  return;
              }
              event->accept();
              return;
          case QMessageBox::Discard:
              event->accept();
              return;
          case QMessageBox::Cancel:
              event->ignore();
              return;
        }
    }
    event->accept();
}

void MainWindow::on_exit_action_triggered()
{
    this->close();
}

void MainWindow::on_actionRussian_triggered()
{
    myappTranslator.load(QString("lab3_") + QString("ru"));
    qApp->installTranslator(&myappTranslator);

    s_myappTranslator.load(QString("qt_") + QString("ru"),
                         QLibraryInfo::location(QLibraryInfo::TranslationsPath));
      qApp->installTranslator(&s_myappTranslator);

}

void MainWindow::on_actionEnglish_triggered()
{
    myappTranslator.load(QString("lab3_") + QString("en"));
    qApp->installTranslator(&myappTranslator);

    s_myappTranslator.load(QString("qt_") + QString("en"),
                         QLibraryInfo::location(QLibraryInfo::TranslationsPath));
       qApp->installTranslator(&s_myappTranslator);

}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

