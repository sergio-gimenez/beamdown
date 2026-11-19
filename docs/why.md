# Why Beamdown

I like LaTeX Beamer. Sections, build steps and real math suit a technical talk. But Beamer is made for academic talks, and it is hard to use: every slide is a LaTeX frame that you compile to see. Pandoc made life easy here, since you write Markdown and pandoc turns it into Beamer slides.

Then I saw Hype, David Heinemeier Hansson's Markdown presentation app, in his 2026 Rails keynote. It had what the pandoc route lacks: a visual editor with a live preview, still on one Markdown file. I forked it and made it suit my needs, adding the Beamer features I missed and a look that fits GNOME.

Beamdown started as a fork of [Hype](https://github.com/omacom/hype), made for [Omarchy](https://omarchy.org). It has since diverged too much to follow upstream, so it is now its own app. It still reads and writes Hype's file format, so a presentation opens in either.

What Beamdown adds over Hype:

- **A GNOME look.** Adwaita colors and rounded corners that follow your dark style and accent color as you change them. On Omarchy it still follows the Omarchy theme.
- **Slide themes built in.** `adwaita` (the default), `adwaita-dark`, `beamer`, `metropolis`, `metropolis-dark` and `tokyo-night`, with no Omarchy needed. Installed Omarchy themes still appear in the list.
- **Beamer's toolbox.** Build steps with `. . .` and incremental lists, a PDF page per step, LaTeX math, Mermaid diagrams, hidden backup slides, fixed typography with a running header and slide numbers, and split layouts that put an image beside the text.
- **Editing comforts.** Markdown colored as you type, find with **Ctrl+F** in the slide and **Ctrl+Shift+F** in every slide, an editor you can make taller or shorter, and SVG labels you can retype on the slide.

Hype's history and MIT license come with the fork; see [LICENSE](https://github.com/sergio-gimenez/beamdown/blob/fork/LICENSE).
