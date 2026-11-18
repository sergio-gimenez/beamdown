#pragma once
#include <QColor>
#include <QDBusVariant>
#include <QFileSystemWatcher>
#include <QPointer>
#include <QQuickTextDocument>
#include <QObject>
#include <QTimer>
#include <QVariantMap>

class MarkdownHighlighter;

class AppTheme : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap colors READ colors NOTIFY changed)
    Q_PROPERTY(int rounding READ rounding NOTIFY changed)
    Q_PROPERTY(int controlRounding READ controlRounding NOTIFY changed)
    Q_PROPERTY(bool adwaita READ adwaita NOTIFY changed)
  public:
    explicit AppTheme(QObject *parent = nullptr);
    explicit AppTheme(const QString &currentDirectory, QObject *parent = nullptr);
    QVariantMap colors() const { return m_colors; }
    int rounding() const { return m_rounding; }
    // Buttons and fields round less than cards and popups.
    int controlRounding() const { return m_adwaita ? 6 : qMin(4, m_rounding); }
    // Without an Omarchy theme the app looks like a GNOME (libadwaita) app.
    bool adwaita() const { return m_adwaita; }
    // GNOME's palette for a color scheme and accent; public for tests.
    static QVariantMap adwaitaColors(bool dark, const QColor &accent);
    // Colors an editor's Markdown, in this theme's syntax colors as they change.
    Q_INVOKABLE void highlight(QQuickTextDocument *document);
  signals:
    void changed();

  private slots:
    void portalSettingChanged(const QString &group, const QString &key, const QDBusVariant &value);

  private:
    void reload();
    void followPortal();
    void readPortal(const QString &key, const QVariant &value);
    bool m_dark = false;
    bool m_adwaita = false;
    QColor m_accent{"#3584e4"};
    QVariantMap syntaxColors() const;
    QList<QPointer<MarkdownHighlighter>> m_highlighters;
    QString m_currentDirectory;
    QVariantMap m_colors;
    int m_rounding = 0;
    QFileSystemWatcher m_watcher;
    QTimer m_reload;
};
