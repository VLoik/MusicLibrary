#include "albumdialog.h"
#include "ui_albumdialog.h"

AlbumDialog::AlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Album Dialog"));
    ui->a_line_edit->setReadOnly(true);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

}

AlbumDialog::~AlbumDialog()
{
    delete ui;
}

void AlbumDialog::on_brouse_button_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("/home/vladimir"), tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty()) return;
    else
    {
        if (!image.load(fileName))
        {
            QMessageBox::warning(this, tr("Open Image"), tr("The image file could not be loaded."), QMessageBox::Close);
            return;
        }
        ui->img_label->setPixmap(image.scaled(170,170));
    }

}

void AlbumDialog::setModel(MusicModel *model)
{
    m_mapper.setModel(model);
}

void AlbumDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    Item *parent_item = static_cast<Item*>(index.parent().internalPointer());
    ui->a_line_edit->setText(parent_item->name());

    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);

    m_mapper.addMapping(ui->n_line_edit,0);
    m_mapper.addMapping(ui->g_line_edit,1);
    m_mapper.addMapping(ui->y_spinBox,2);
    m_mapper.addMapping(ui->comment,3);
    m_mapper.addMapping(ui->img_label,4, "pixmap");
    m_mapper.setCurrentIndex(index.row());
}

void AlbumDialog::accept()
{
    m_mapper.submit();
    QDialog::accept();
}

bool AlbumDialog::addAlbum(MusicModel *model, const QModelIndex &parent)
{

    setModel(model);
    int row = model->rowCount(parent);
    if(!model->insertRow(row, parent)) return false;
    QModelIndex index = model->index(row, 0, parent);
    setModelIndex(index);
    if(!exec()){
        model->removeRow(row, parent);
        return false;
    }
    return true;

}
