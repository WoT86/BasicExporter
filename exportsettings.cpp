#include "exportsettings.h"
#include "ui_exportsettings.h"

ExportSettings::ExportSettings(const QString &path, int quality, float gamma, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportSettings),
    Quality(quality),
    Gamma(gamma),
    PreviewItem(0)
{
    ui->setupUi(this);

    this->ui->graphicsViewPreview->setScene(&(this->Scene));

    this->setPath(path);
    this->setGamma(gamma);
    this->setQuality(quality);
}

ExportSettings::~ExportSettings()
{
    delete ui;
}

void ExportSettings::setFilters(const QStringList& filters)
{
    this->Filters = filters;

    foreach(QString type,filters)
    {
        this->Filter += QString("*.") + type + QString(";; ");
    }

    this->Filter.truncate(this->Filter.count()-3);

    this->ui->comboBoxTypes->addItems(filters);
}

void ExportSettings::setPath(const QString &path)
{
    QFileInfo fi(path);

    this->FileName = fi.fileName();

    if(this->FileName.isEmpty())
    {
        this->FileName = QString("array_export_") + QDateTime::currentDateTime().toString("hhmmss_ddMMyyyy.") + this->ui->comboBoxTypes->currentText();
        fi.setFile(fi.filePath() + this->FileName);
    }

    this->Path = fi.filePath();
    this->ui->lineEditFilename->setText(this->FileName);
}

void ExportSettings::setQuality(int quality)
{
    this->Quality = quality;
    this->ui->hSliderQuality->setValue((this->Quality > 1) ? this->Quality-1 : 1);
    this->ui->labelQuality->setText(QString::number(this->Quality));
}

void ExportSettings::setGamma(float gamma)
{
    this->Gamma = gamma;
    this->ui->hSliderGamma->setValue((qRound(100*this->Gamma) > 0) ? (qRound(100*this->Gamma)-1) : 0);
    this->ui->labelGamma->setText(QString::number(this->Gamma,'f',2));
}

void ExportSettings::setType(const QString &type)
{
    this->ui->comboBoxTypes->setCurrentText(type);
}

void ExportSettings::setPreview(const QImage &pre)
{
    this->Preview = QPixmap::fromImage(pre);
    this->OriginalImage = QPixmap::fromImage(pre);
    this->on_ButtonApply_clicked();
}

QString ExportSettings::getType() const
{
    return this->ui->comboBoxTypes->currentText();
}

QString ExportSettings::getPath() const
{
    return this->Path;
}

int ExportSettings::getQuality() const
{
    return this->Quality;
}

float ExportSettings::getGamma() const
{
    return this->Gamma;
}

void ExportSettings::on_hSliderGamma_valueChanged(int value)
{
    this->Gamma = (value > 0) ? (((float) (value+1))/100) : 0.0f;
    this->ui->labelGamma->setText(QString::number(this->Gamma,'f',2));
}

void ExportSettings::on_hSliderQuality_valueChanged(int value)
{
    this->Quality = value + 1;
    this->ui->labelQuality->setText(QString::number(this->Quality));
}

void ExportSettings::on_ButtonBrowse_clicked()
{
    QString path;
    QString sPath = this->Path;
    sPath.truncate(sPath.count()-(this->ui->comboBoxTypes->currentText().count()+1));

    QFileDialog dialog(0,tr("Export array to..."),sPath,this->Filter);

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.selectNameFilter(QString("*.")+this->ui->comboBoxTypes->currentText());

    if(dialog.exec() == QDialog::Accepted)
    {
        QString suffix = QString(".") + this->ui->comboBoxTypes->currentText();
        path = dialog.selectedFiles().first();
        if(path.lastIndexOf(suffix) !=  path.count()-suffix.count())
            path += suffix;
    }

    if(!(path.isEmpty()))
    {
        this->setPath(path);
    }
}

void ExportSettings::on_ButtonApply_clicked()
{
    QByteArray ba;
    QBuffer buf(&ba);

    buf.open(QBuffer::ReadWrite);

    QImageWriter writer(&buf,this->ui->comboBoxTypes->currentText().toUtf8());

    writer.setQuality(this->Quality);
    writer.setGamma(this->Gamma);

    if(writer.write(this->OriginalImage.toImage()))
    {
        this->Preview.loadFromData(ba,this->ui->comboBoxTypes->currentText().toUtf8());
    }

    this->Scene.clear();
    this->Scene.setSceneRect(this->Preview.rect());
    this->PreviewItem = this->Scene.addPixmap(this->Preview);

    this->ui->graphicsViewPreview->fitInView(this->Scene.itemsBoundingRect(),Qt::KeepAspectRatio);
}

void ExportSettings::on_comboBoxTypes_currentIndexChanged(const QString &arg1)
{
    QFileInfo fi(this->Path);

    this->Path.truncate(this->Path.count()-fi.suffix().count());
    this->Path += arg1;

    this->setPath(this->Path);
}
