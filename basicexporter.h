#ifndef BASICEXPORTER_H
#define BASICEXPORTER_H

#include "basicexporter_global.h"
#include "../FastArray/exporterplugininterface.h"
#include "../FastArray/plugininterface.h"
#include "exportsettings.h"

#include <QStandardPaths>
#include <QImage>
#include <QImageWriter>
#include <QPixmap>
#include <QObject>

class BASICEXPORTERSHARED_EXPORT BasicExporter : public QObject, public ExporterPluginInterface, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "WoT.FastArray.BasicExporterPlugin/0.1")
    Q_INTERFACES(ExporterPluginInterface PluginInterface)

public:
    BasicExporter();

    virtual bool hasFailed() const;
    virtual unsigned int getErrorCode() const;
    virtual QString getErrorDescription() const;

    virtual QString getPluginName() const;
    virtual QString getPluginType() const;
    virtual QString getPluginVersion() const;

    virtual void registerLogger(LoggerInterface *logger);

    virtual QStringList getValidFileExtensions() const;
    virtual bool writeImage(const QImage& image, const QString& type);

private:
    //bunch of private convenient functions
    void logError(const QString& msg);
    void logWarning(const QString& msg);
    void logInfo(const QString& msg);

protected:
    unsigned int ErrorCode;

    bool Error;

    QString ErrorDescription;
    QString Version;
    QString Type;
    QString Name;

    QStringList FileExtensions;
    QStringList ExtensionFilter;

    LoggerInterface* Logger;

    ExportSettings dialog;
};

#endif // BASICEXPORTER_H
