#ifndef EXPORTSETTINGS_H
#define EXPORTSETTINGS_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>

#include <QGraphicsScene>
#include <QImageWriter>
#include <QBuffer>

#include <QImage>
#include <QPixmap>

#include <QDateTime>

namespace Ui {
class ExportSettings;
}

class ExportSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ExportSettings(const QString& path = QString(),int quality = 100, float gamma = 1.0f, QWidget *parent = 0);
    ~ExportSettings();

    void setFilters(const QStringList& filters);

    void setPath(const QString& path);
    void setQuality(int quality);
    void setGamma(float gamma);
    void setType(const QString& type);
    void setPreview(const QImage& pre);

    QString getType() const;
    QString getPath() const;
    int getQuality() const;
    float getGamma() const;

private slots:
    void on_hSliderGamma_valueChanged(int value);

    void on_hSliderQuality_valueChanged(int value);

    void on_ButtonBrowse_clicked();

    void on_ButtonApply_clicked();

    void on_comboBoxTypes_currentIndexChanged(const QString &arg1);

private:
    Ui::ExportSettings *ui;

    int Quality;
    float Gamma;

    QString Path;
    QString FileName;
    QString Filter;
    QStringList Filters;

    QGraphicsScene Scene;

    QPixmap Preview;
    QPixmap OriginalImage;
    QGraphicsPixmapItem* PreviewItem;
};

#endif // EXPORTSETTINGS_H
