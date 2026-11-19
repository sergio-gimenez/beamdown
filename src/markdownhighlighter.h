#pragma once
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVariantMap>

// Colors the editors' Markdown the way the slides read it: headings, emphasis, code,
// media and links, comments and hype directives, front matter, math, and the lines
// that split slides, pause them or fence a list. The text itself never changes.
class MarkdownHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
  public:
    explicit MarkdownHighlighter(QTextDocument *document);
    // Colors by role: heading, marker, code, link, key, math, comment.
    void setColors(const QVariantMap &colors);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    enum State { Normal = 0, Fence, Comment, FrontMatter, Math };
    QTextCharFormat role(const QString &name) const;
    // Adds a format to what a span already has, so bold keeps a heading's color.
    void add(int start, int length, const QTextCharFormat &format);
    void inlineSpans(const QString &text, int from);
    QVariantMap m_colors;
};
