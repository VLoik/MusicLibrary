#include "artistdialog.h"
#include "ui_artistdialog.h"

ArtistDialog::ArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtistDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Artist Dialog"));
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

}

ArtistDialog::~ArtistDialog()
{
    delete ui;
}

void ArtistDialog::on_brouse_button_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("/home/vladimir"), tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty()) return;
    else
    {
        if (!image.load(fileName))
        {
            QMessageBox::warning(this, tr("Open Image"), tr("The image file could not be loaded."),  QMessageBox::Close);
            return;
        }
        ui->img_label->setPixmap(image.scaled(180,180));
    }
}

void ArtistDialog::setModel(MusicModel *model)
{
    m_mapper.setModel(model);
}

void ArtistDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    m_mapper.addMapping(ui->n_line_edit,0);
    m_mapper.addMapping(ui->c_line_edit,1);
    m_mapper.addMapping(ui->comment,2);
    m_mapper.addMapping(ui->img_label,3, "pixmap");
    m_mapper.setCurrentIndex(index.row());
}

void ArtistDialog::accept()
{
    m_mapper.submit();
    QDialog::accept();
}

bool ArtistDialog::addArtist(MusicModel *model, const QModelIndex &parent)
{
    setModel(model);
    int row = model->rowCount(parent);
    if(!model->insertRow(row, parent))        return false;
    QModelIndex index = model->index(row, 0, parent);
    setModelIndex(index);
    if(!exec()){
        model->removeRow(row, parent);
        return false;
    }
    return true;

}
