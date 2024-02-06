/**
 * Oui
*/

#ifndef WORKSPACEWIDGET_H
#define WORKSPACEWIDGET_H

#include <QFrame>
#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QSettings>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QVBoxLayout>

#include "settings/appsettings.h"

namespace ghostwriter
{
/**
 * Workspace Widget
 * 
 * A "workspace" is simply a project root folder used to browse files
 * 
 * https://doc.qt.io/qt-5/qtreeview.html
 * https://doc.qt.io/qt-5/qfilesystemmodel.html
 * https://doc.qt.io/qt-5/qtwidgets-itemviews-dirview-example.html
*/
class WorkspaceWidget : public QFrame
{
    Q_OBJECT

public:
    /**
     * Constructor
    */
    WorkspaceWidget(QWidget *parent = nullptr);

    /**
     * Destructor
    */
    virtual ~WorkspaceWidget();

    void setCurrentFile(const QString &filePath);

signals:
    void fileDoubleClicked(const QString &filePath);

public slots:
    void openFolder();
    void openFileFromTreeView(const QModelIndex &index);

private:
    QVBoxLayout *layout;
    QFileSystemModel *fsModel;
    QTreeView *treeView;
    AppSettings *appSettings;

    void hideColumns();
};
} // namespace ghostwriter

#endif