#include "basicexporter.h"


BasicExporter::BasicExporter():
    ErrorCode(0),
    Error(false),
    Version("0.1"),
    Type(EXPORTER_PLUGIN),
    Name("Basic Exporter Plugin")
{    
    foreach(QByteArray format,QImageWriter::supportedImageFormats())
    {
        this->FileExtensions.append(format);
        this->ExtensionFilter.append(QString("*.")+format);
    }
}

bool BasicExporter::hasFailed() const
{
    return this->Error;
}

unsigned int BasicExporter::getErrorCode() const
{
    return this->ErrorCode;
}

QString BasicExporter::getErrorDescription() const
{
    return this->ErrorDescription;
}

QString BasicExporter::getPluginName() const
{
    return this->Name;
}

QString BasicExporter::getPluginType() const
{
    return this->Type;
}

QString BasicExporter::getPluginVersion() const
{
    return this->Version;
}

void BasicExporter::registerLogger(LoggerInterface *logger)
{
    this->Logger = logger;
    this->logInfo(QObject::tr("logger registered."));
    this->logInfo(QObject::tr("valid file extensions: %1").arg(this->getValidFileExtensions().join(",")));
}

QStringList BasicExporter::getValidFileExtensions() const
{
    return this->FileExtensions;
}

bool BasicExporter::writeImage(const QImage &image, const QString &type)
{
    this->Error = false;

    dialog.setFilters(this->FileExtensions);
    dialog.setPath(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+QString("/"));
    dialog.setPreview(image);
    dialog.setType(type);

    if(dialog.exec() == QDialog::Accepted)
    {
        QImageWriter writer(dialog.getPath(),dialog.getType().toUtf8());

        writer.setQuality(dialog.getQuality());
        writer.setGamma(dialog.getGamma());

        if(writer.write(image))
        {
            this->logInfo(tr("array successfully exported to %1").arg(dialog.getPath()));
            return true;
        }
        else
        {
            this->Error = true;
            this->ErrorCode = writer.error();
            this->ErrorDescription = writer.errorString();
            this->logError(tr("unable to save array to %1 ERRORCODE %2 DESCRIPTION %3").arg(dialog.getPath(),QString::number(this->ErrorCode),this->ErrorDescription));
        }
    }

    return false;
}

void BasicExporter::logError(const QString &msg)
{
    this->Logger->log(this->getPluginName(),msg,ERROR);
}

void BasicExporter::logWarning(const QString &msg)
{
    this->Logger->log(this->getPluginName(),msg,WARNING);
}

void BasicExporter::logInfo(const QString &msg)
{
    this->Logger->log(this->getPluginName(),msg,INFO);
}
