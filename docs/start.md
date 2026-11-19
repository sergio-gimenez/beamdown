# Get started

## Install

Beamdown builds from source. You need a C++17 compiler, make, Qt 6.9 or newer, FFmpeg and GNU source-highlight. Math also needs `latex` and `dvisvgm` from TeX Live, and diagrams need the Mermaid CLI (`mmdc`) and `pdftocairo`.

```sh
git clone https://github.com/sergio-gimenez/beamdown.git
cd beamdown
./bin/build
./build/beamdown open examples/welcome.md
```

`./bin/install-dev` adds **Beamdown (Development)** to your app launcher, which rebuilds the checkout each time it opens. On Arch, `./bin/install` builds and installs a package with makepkg.

!!! tip "Coming from Hype?"
    The first time it opens, Beamdown copies Hype's settings and moves Hype's recovery drafts over. Presentations keep Hype's file format, so they open in either app.

## Your first presentation

1. Open Beamdown and press **Ctrl+N** for a new presentation, or **Ctrl+O** to open a Markdown file.
2. Write the first slide in the editor under the preview. Changes appear as you type.
3. Press **Ctrl+Enter** to add a slide, and drag slides in the sidebar to reorder them.
4. Press **Ctrl+S** to choose where to save. After that Beamdown saves on its own.
5. Press **F5** to present, and **Ctrl+E** to export a PDF.

Or start from the command line:

```sh
beamdown new talk/presentation.md --title "My talk" --theme metropolis
beamdown open talk/presentation.md
```

## The shape of a presentation

```text
my-talk/
  presentation.md   the slides, separated by ---
  images/           pictures, found by name
  videos/           clips, found by name
```

Next, [write your slides](write.md), pick a [theme](themes.md), and try the [Beamer features](beamer.md).
