#include "markdownhighlighter.h"
#include <QColor>
#include <QFont>
#include <QRegularExpression>
#include <QTextDocument>

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *document) : QSyntaxHighlighter(document) {}

void MarkdownHighlighter::setColors(const QVariantMap &colors) {
    if (colors == m_colors)
        return;
    m_colors = colors;
    rehighlight();
}

QTextCharFormat MarkdownHighlighter::role(const QString &name) const {
    QTextCharFormat format;
    const QColor color = m_colors.value(name).value<QColor>();
    if (color.isValid())
        format.setForeground(color);
    if (name == "comment")
        format.setFontItalic(true);
    return format;
}

void MarkdownHighlighter::add(int start, int length, const QTextCharFormat &format) {
    for (int i = qMax(0, start); i < start + length; ++i) {
        QTextCharFormat merged = this->format(i);
        merged.merge(format);
        setFormat(i, 1, merged);
    }
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    static const QRegularExpression fence(R"(^ {0,3}(`{3,}|~{3,})\s*([\w+#.-]*))");
    const int previous = qMax(0, previousBlockState());
    const QTextCharFormat marker = role("marker");
    setCurrentBlockState(Normal);
    // Front matter opens on the document's first line and closes at the next ---.
    if (currentBlock().blockNumber() == 0 && text == "---") {
        add(0, text.size(), marker);
        setCurrentBlockState(FrontMatter);
        return;
    }
    if (previous == FrontMatter) {
        static const QRegularExpression key(R"(^\s*([A-Za-z_][\w-]*)\s*:)");
        if (text == "---" || text == "...") {
            add(0, text.size(), marker);
            return;
        }
        if (const auto match = key.match(text); match.hasMatch())
            add(match.capturedStart(1), match.capturedLength(1), role("key"));
        setCurrentBlockState(FrontMatter);
        return;
    }
    if (previous == Fence) {
        if (const auto match = fence.match(text); match.hasMatch() && match.capturedLength(2) == 0) {
            add(0, text.size(), marker);
            return;
        }
        add(0, text.size(), role("code"));
        setCurrentBlockState(Fence);
        return;
    }
    if (const auto match = fence.match(text); match.hasMatch()) {
        add(0, text.size(), marker);
        add(match.capturedStart(2), match.capturedLength(2), role("key"));
        setCurrentBlockState(Fence);
        return;
    }
    if (previous == Math) {
        add(0, text.size(), role("math"));
        if (!text.contains("$$"))
            setCurrentBlockState(Math);
        return;
    }
    int from = 0;
    if (previous == Comment) {
        const int end = text.indexOf("-->");
        if (end < 0) {
            add(0, text.size(), role("comment"));
            setCurrentBlockState(Comment);
            return;
        }
        add(0, end + 3, role("comment"));
        from = end + 3;
    }
    const QString line = text.trimmed();
    if (from == 0) {
        // The lines that shape the deck: slide breaks, pauses, and fenced lists.
        if (line == "---" || line == ". . ." || line.startsWith(":::")) {
            QTextCharFormat structure = marker;
            structure.setFontWeight(QFont::Bold);
            add(0, text.size(), structure);
            return;
        }
        if (line.startsWith("$$")) {
            add(0, text.size(), role("math"));
            if (line == "$$" || !line.mid(2).contains("$$"))
                setCurrentBlockState(Math);
            return;
        }
        static const QRegularExpression delimiter(R"(^\s*\|?\s*:?-{3,}:?\s*(\|\s*:?-{3,}:?\s*)*\|?\s*$)");
        if (text.contains('|') && delimiter.match(text).hasMatch()) {
            add(0, text.size(), marker);
            return;
        }
        static const QRegularExpression heading(R"(^(#{1,6})\s)");
        static const QRegularExpression bullet(R"(^\s*([-*+]|\d+[.)])\s)");
        static const QRegularExpression quote(R"(^\s*(>+))");
        if (const auto match = heading.match(text); match.hasMatch()) {
            QTextCharFormat title = role("heading");
            title.setFontWeight(QFont::Bold);
            add(0, text.size(), title);
            add(0, match.capturedLength(1), marker);
        } else if (const auto match = bullet.match(text); match.hasMatch()) {
            add(match.capturedStart(1), match.capturedLength(1), role("heading"));
        } else if (const auto match = quote.match(text); match.hasMatch()) {
            add(match.capturedStart(1), match.capturedLength(1), marker);
        }
    }
    inlineSpans(text, from);
}

void MarkdownHighlighter::inlineSpans(const QString &text, int from) {
    const QTextCharFormat marker = role("marker");
    auto each = [&](const QRegularExpression &pattern, const auto &apply) {
        for (auto matches = pattern.globalMatch(text, from); matches.hasNext();)
            apply(matches.next());
    };
    if (text.trimmed().startsWith('|'))
        for (int i = from; i < text.size(); ++i)
            if (text[i] == '|')
                add(i, 1, marker);
    // Emphasis as the slides read it: **bold**, *italic*, and _underline_.
    auto emphasis = [&](const QRegularExpression &pattern, int width, const QTextCharFormat &format) {
        each(pattern, [&](const QRegularExpressionMatch &match) {
            add(match.capturedStart(), match.capturedLength(), format);
            add(match.capturedStart(), width, marker);
            add(match.capturedEnd() - width, width, marker);
        });
    };
    QTextCharFormat strong, italic, underline;
    strong.setFontWeight(QFont::Bold);
    italic.setFontItalic(true);
    underline.setFontUnderline(true);
    static const QRegularExpression bold(R"(\*\*(?=\S)(.+?)(?<=\S)\*\*)");
    static const QRegularExpression slanted(R"((?<![*\w])\*(?=[^\s*])(.+?)(?<=[^\s*])\*(?![*\w]))");
    static const QRegularExpression underscored(R"((?<![_\w])_(?=\S)(.+?)(?<=\S)_(?![_\w]))");
    static const QRegularExpression math(R"((?<![\\$])\$(?=[^\s$])(.+?)(?<=[^\s\\])\$(?!\d))");
    static const QRegularExpression link(R"((!?)\[([^\]\n]*)\]\(([^)\n]*)\))");
    static const QRegularExpression code(R"((`+)(.+?)\1)");
    emphasis(bold, 2, strong);
    emphasis(slanted, 1, italic);
    emphasis(underscored, 1, underline);
    // A $ needs a non-space inside it, so prices stay text.
    each(math,
         [&](const QRegularExpressionMatch &match) { add(match.capturedStart(), match.capturedLength(), role("math")); });
    // Media and links: the options of ![fit](photo.jpg) and the target of [text](url).
    each(link, [&](const QRegularExpressionMatch &match) {
        add(match.capturedStart(), match.capturedStart(2) - match.capturedStart(), marker);
        add(match.capturedEnd(2), 2, marker);
        add(match.capturedEnd() - 1, 1, marker);
        if (match.capturedLength(1))
            add(match.capturedStart(2), match.capturedLength(2), role("key"));
        add(match.capturedStart(3), match.capturedLength(3), role("link"));
    });
    // Code last, replacing what came before: nothing inside it is emphasis or math.
    each(code, [&](const QRegularExpressionMatch &match) {
        setFormat(match.capturedStart(), match.capturedLength(), role("code"));
    });
    // Comments hold speaker notes and hype directives, and may run on to later lines.
    static const QRegularExpression directive(R"(\G<!--\s*(hype:))");
    for (int start = text.indexOf("<!--", from); start >= 0; start = text.indexOf("<!--", start + 4)) {
        const int end = text.indexOf("-->", start + 4);
        setFormat(start, (end < 0 ? text.size() : end + 3) - start, role("comment"));
        if (const auto match = directive.match(text, start); match.hasMatch())
            add(match.capturedStart(1), match.capturedLength(1), role("key"));
        if (end < 0) {
            setCurrentBlockState(Comment);
            return;
        }
        start = end;
    }
}
