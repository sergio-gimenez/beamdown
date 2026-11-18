#include "apptheme.h"
#include <QColor>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <cmath>

static QColor mix(const QColor &base, const QColor &ink, double amount) {
    return QColor::fromRgbF(base.redF() + (ink.redF() - base.redF()) * amount,
                            base.greenF() + (ink.greenF() - base.greenF()) * amount,
                            base.blueF() + (ink.blueF() - base.blueF()) * amount);
}
static QColor contrastInk(const QColor &color) {
    auto linear = [](double value) {
        return value <= .04045 ? value / 12.92 : std::pow((value + .055) / 1.055, 2.4);
    };
    const double luminance = .2126 * linear(color.redF()) + .7152 * linear(color.greenF()) +
                             .0722 * linear(color.blueF());
    return luminance > .179 ? QColor("#111111") : QColor("#ffffff");
}
AppTheme::AppTheme(QObject *parent)
    : AppTheme(qEnvironmentVariable("XDG_STATE_HOME", QDir::homePath() + "/.local/state") +
                   "/omarchy/current",
               parent) {}
AppTheme::AppTheme(const QString &currentDirectory, QObject *parent)
    : QObject(parent), m_currentDirectory(currentDirectory) {
    m_reload.setSingleShot(true);
    m_reload.setInterval(100);
    connect(&m_reload, &QTimer::timeout, this, &AppTheme::reload);
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, [this] { m_reload.start(); });
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, [this] { m_reload.start(); });
    followPortal();
    reload();
}
static const char *portalService = "org.freedesktop.portal.Desktop";
static const char *portalPath = "/org/freedesktop/portal/desktop";
static const char *portalSettings = "org.freedesktop.portal.Settings";
static const char *appearance = "org.freedesktop.appearance";
// GNOME's dark style and accent color, read once up front so the window opens in the
// right colors, then followed as they change. HYPE_COLOR_SCHEME=light|dark pins the style.
void AppTheme::followPortal() {
    const QString pinned = qEnvironmentVariable("HYPE_COLOR_SCHEME");
    if (pinned == "light" || pinned == "dark") {
        m_dark = pinned == "dark";
        return;
    }
    auto bus = QDBusConnection::sessionBus();
    if (!bus.isConnected())
        return;
    for (const QString key : {"color-scheme", "accent-color"}) {
        auto call = QDBusMessage::createMethodCall(portalService, portalPath, portalSettings, "ReadOne");
        call.setArguments({appearance, key});
        const auto reply = bus.call(call, QDBus::Block, 300);
        if (reply.type() == QDBusMessage::ReplyMessage && !reply.arguments().isEmpty())
            readPortal(key, reply.arguments().first().value<QDBusVariant>().variant());
    }
    bus.connect(portalService, portalPath, portalSettings, "SettingChanged", this,
                SLOT(portalSettingChanged(QString, QString, QDBusVariant)));
}
void AppTheme::readPortal(const QString &key, const QVariant &value) {
    if (key == "color-scheme") {
        m_dark = value.toUInt() == 1; // 0 no preference, 1 dark, 2 light
    } else if (key == "accent-color" && value.canConvert<QDBusArgument>()) {
        const auto argument = value.value<QDBusArgument>();
        double red = -1, green = -1, blue = -1;
        argument.beginStructure();
        argument >> red >> green >> blue;
        argument.endStructure();
        // Out of range means the desktop has no accent color.
        if (red >= 0 && red <= 1 && green >= 0 && green <= 1 && blue >= 0 && blue <= 1)
            m_accent = QColor::fromRgbF(red, green, blue);
    }
}
void AppTheme::portalSettingChanged(const QString &group, const QString &key, const QDBusVariant &value) {
    if (group != appearance)
        return;
    readPortal(key, value.variant());
    m_reload.start();
}
// libadwaita's named colors, flattened onto their backgrounds.
QVariantMap AppTheme::adwaitaColors(bool dark, const QColor &accent) {
    const QColor white("#ffffff");
    const QColor window = dark ? QColor("#222226") : QColor("#fafafb");
    const QColor view = dark ? QColor("#1d1d20") : white;
    const QColor fg = dark ? white : mix(window, QColor("#000006"), .8);
    const QColor border = mix(window, fg, .15);
    const QColor selection = mix(view, accent, .3);
    const QColor inactiveSelection = mix(border, accent, .5);
    return {{"background", view},
            {"foreground", fg},
            {"accent", accent},
            {"panel", window},
            {"headerbar", dark ? QColor("#2e2e32") : white},
            {"sidebar", dark ? QColor("#2e2e32") : QColor("#ebebed")},
            {"popover", dark ? QColor("#36363a") : white},
            {"button", mix(window, fg, .1)},
            {"hover", mix(window, fg, .08)},
            {"border", border},
            {"muted", mix(window, fg, .55)},
            {"selection", selection},
            {"selectionText", contrastInk(selection)},
            {"inactiveSelection", inactiveSelection},
            {"inactiveSelectionText", contrastInk(inactiveSelection)},
            // Suggested actions keep white text on every GNOME accent.
            {"accentText", white},
            {"accentHover", mix(accent, white, .12)},
            {"windowBorder", accent},
            {"error", dark ? QColor("#ff7b63") : QColor("#c01c28")}};
}
void AppTheme::reload() {
    const QString theme = m_currentDirectory + "/theme", path = theme + "/colors.toml";
    QMap<QString, QColor> values;
    QFile file(path);
    const bool omarchy = file.open(QIODevice::ReadOnly);
    if (omarchy) {
        // Quoted or bare hex with an optional note. Quotes must pair; comments need no gap.
        const QRegularExpression entry(
            R"re(^\s*([a-z_]+)\s*=\s*(["']?)(#[0-9a-fA-F]{6})\2\s*(?:#.*)?\s*$)re");
        while (!file.atEnd()) {
            const auto match = entry.match(QString::fromUtf8(file.readLine()));
            if (match.hasMatch())
                values[match.captured(1)] = QColor(match.captured(3));
        }
    }
    const QColor bg = values.value("background", QColor("#1a1b26"));
    const QColor fg = values.value("foreground", QColor("#c0caf5"));
    const QColor accent = values.value("accent", QColor("#7aa2f7"));
    const QColor selection = values.value("selection", mix(bg, accent, .3));
    const QColor border = mix(bg, fg, .22);
    const QColor inactiveSelection = mix(border, accent, .7);
    QVariantMap colors{{"background", bg},
                             {"foreground", fg},
                             {"accent", accent},
                             {"panel", mix(bg, fg, .025)},
                             {"button", values.value("lighter_background", mix(bg, fg, .08))},
                             {"hover", mix(bg, accent, .22)},
                             {"border", border},
                             {"muted", mix(bg, fg, .62)},
                             {"selection", selection},
                             {"selectionText", contrastInk(selection)},
                             {"inactiveSelection", inactiveSelection},
                             {"inactiveSelectionText", contrastInk(inactiveSelection)},
                             {"accentText", contrastInk(accent)},
                             {"accentHover", mix(accent, fg, .15)},
                             {"windowBorder", values.value("active_border_color", accent)},
                             {"error", values.value("red", QColor("#d94b4b"))}};
    colors["headerbar"] = colors["sidebar"] = colors["popover"] = colors["panel"];
    // Popups take the desktop's window corners: square unless the theme rounds them.
    int rounding = 0;
    QStringList windowFiles;
    for (const auto &name : {"/hyprland.lua", "/hyprland.conf"}) {
        QFile window(theme + name);
        if (!window.open(QIODevice::ReadOnly))
            continue;
        windowFiles.append(theme + name);
        const QRegularExpression entry(R"re(^\s*rounding\s*=\s*(\d+))re");
        while (!window.atEnd()) {
            const auto match = entry.match(QString::fromUtf8(window.readLine()));
            if (match.hasMatch())
                rounding = match.captured(1).toInt();
        }
    }
    if (!omarchy) {
        colors = adwaitaColors(m_dark, m_accent);
        rounding = 12;
    }
    if (colors != m_colors || rounding != m_rounding || omarchy == m_adwaita) {
        m_colors = colors;
        m_rounding = rounding;
        m_adwaita = !omarchy;
        emit changed();
    }
    // Theme switching replaces symlinks; atomic saves replace file inodes.
    // Watch their parents as well, and re-arm after every change.
    const QStringList watched = m_watcher.files() + m_watcher.directories();
    if (!watched.isEmpty())
        m_watcher.removePaths(watched);
    QStringList paths{m_currentDirectory, theme, path};
    paths.append(windowFiles);
    QString ancestor = QFileInfo(m_currentDirectory).absolutePath();
    while (!QFileInfo::exists(ancestor) && ancestor != "/")
        ancestor = QFileInfo(ancestor).absolutePath();
    paths.append(ancestor);
    paths.removeDuplicates();
    for (const auto &entry : paths)
        if (QFileInfo::exists(entry))
            m_watcher.addPath(entry);
}
