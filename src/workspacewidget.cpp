/**
 * Oui
 */

#include "workspacewidget.h"

namespace ghostwriter
{
    /**
     * Constructor
     */
    WorkspaceWidget::WorkspaceWidget(QWidget *parent) : QFrame(parent)
    {
        // Get last opened folder
        appSettings = AppSettings::instance();
        QString lastWorkspace = appSettings->lastWorkspacePath();

        // Init file system model
        fsModel = new QFileSystemModel();
        fsModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::AllDirs);
        QModelIndex lastWorkspaceIndex = fsModel->setRootPath(lastWorkspace);

        // Create a tree view of the file system
        treeView = new QTreeView();
        treeView->setModel(fsModel);
        treeView->setRootIndex(lastWorkspaceIndex);
        treeView->setHeaderHidden(true);
        hideColumns();

        connect(treeView, &QTreeView::doubleClicked, this, &WorkspaceWidget::openFileFromTreeView);

        // Add a layout and children widget
        layout = new QVBoxLayout(this);
        layout->addWidget(treeView);
    }

    /**
     * Hide columns other than file name
     */
    void WorkspaceWidget::hideColumns()
    {
        for (int j = 1; j < fsModel->columnCount(); j++)
        {
            treeView->hideColumn(j);
        }
    }

    /**
     * Slot : Prompt user to select a root folder as a "workspace"
     */
    void WorkspaceWidget::openFolder()
    {
        QString folderName = QFileDialog::getExistingDirectory(this, tr("Open Workspace Folder"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        QModelIndex rootIndex = fsModel->setRootPath(folderName);

        treeView->setRootIndex(rootIndex);
        appSettings->setLastWorkspacePath(folderName);
    }

    /**
     * Set current index of tree view of a given filePath
     */
    void WorkspaceWidget::setCurrentFile(const QString &filePath)
    {
        QModelIndex fileIndex = fsModel->index(filePath);

        treeView->selectionModel()->setCurrentIndex(fileIndex, QItemSelectionModel::Current);
    }

    void WorkspaceWidget::openFileFromTreeView(const QModelIndex &index)
    {
        emit fileDoubleClicked(fsModel->filePath(index));
    }

    WorkspaceWidget::~WorkspaceWidget()
    {
        ;
    }
}