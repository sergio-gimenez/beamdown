<div align="center">

<img src="pkgbuild/beamdown.svg" alt="Beamdown logo" width="112" height="112">

# Beamdown

**PowerPoint + LaTeX Beamer, but Markdown-driven.**

A presentation app for GNOME. Write one Markdown file, see every slide as you type,<br>
and export to PDF or PowerPoint. No LaTeX document to compile.

[**Documentation**](https://beamdown.sergiogimenez.com) ·
[Get started](https://beamdown.sergiogimenez.com/start/) ·
[Why Beamdown](https://beamdown.sergiogimenez.com/why/)

<br>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/assets/editor-dark.png">
  <img src="docs/assets/editor-light.png" alt="The Beamdown editor: slides on the left, the slide in the middle, its Markdown below">
</picture>

</div>

## Highlights

- **One Markdown file.** Slides are separated by `---`, with images and videos beside the file.
- **Beamer's toolbox.** Build steps with `. . .`, real LaTeX math, sections with a running header and slide numbers, and a PDF page per step.
- **A visual editor.** Live preview, drag-and-drop slides, an overview grid, find in every slide, and Markdown colored as you type.
- **At home on GNOME.** Follows your dark style and accent color, with six slide themes built in, from Adwaita to Metropolis and Beamer blue.
- **Diagrams and code.** Mermaid and SVG in the deck's colors and highlighted code, all kept as vectors in the PDF.
- **PDF and PowerPoint.** Present full screen with Presenter View, or export a file that looks the same anywhere.

## Write this, get slides

```markdown
---
title: "Why the radio dominates"
theme: metropolis
header: "Ops review · Q3"
---

<!-- hype: section="Context" -->

# Why the radio dominates

- Latency is **bound** by the air interface

. . .

- So the fix starts at the cell
```

<img src="docs/assets/example.png" alt="That slide, rendered with the metropolis theme" width="640">

## Install

Beamdown builds from source with Qt 6.9 or newer, FFmpeg and GNU source-highlight ([full list](https://beamdown.sergiogimenez.com/start/)):

```sh
git clone https://github.com/sergio-gimenez/beamdown.git
cd beamdown
./bin/build
./build/beamdown open examples/tour/presentation.md
```

## Credits

Beamdown is a fork of [Hype](https://github.com/omacom/hype) by David Heinemeier Hansson, and it keeps Hype's file format. It has since gone its own way, toward GNOME and toward everyday and technical talks; [Why Beamdown](https://beamdown.sergiogimenez.com/why/) tells the story. MIT licensed, see [LICENSE](LICENSE).
