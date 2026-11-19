# Brand guidelines

Beamdown should look like what it is: a calm GNOME app that turns plain text into clear slides. These rules cover the name, the logo, colors, type and voice, for the app, this site, the README and anything else that talks about Beamdown.

## Name and tagline

**Beamdown** is one word with a capital B. Not BeamDown, Beam Down or beamdown in prose; `beamdown` is only the command.

The tagline is **PowerPoint + LaTeX Beamer, but Markdown-driven.** Use it whole, with the plus sign. When there is room for one more line, add: *A presentation app for GNOME.*

When a fuller credit is needed, say Beamdown is *a fork of Hype by David Heinemeier Hansson*, and link to [Hype](https://github.com/omacom/hype).

## Logo

<div class="bd-logo-row" markdown>
<img src="../assets/logo.svg" alt="The Beamdown logo" width="128" height="128">
<img src="../assets/logo.svg" alt="" width="64" height="64">
<img src="../assets/logo.svg" alt="" width="32" height="32">
<img src="../assets/logo.svg" alt="" width="16" height="16">
</div>

The logo is a slide in GNOME's icon style. A blue frame-title band, as Beamer draws one, sits over the Markdown mark (an M and a down arrow), and a grey slab underneath gives it depth.

- Use the SVG in [`pkgbuild/beamdown.svg`](https://github.com/sergio-gimenez/beamdown/blob/fork/pkgbuild/beamdown.svg). Don't redraw, recolor, rotate or add effects to it.
- Leave clear space around it of at least the band's height (a fifth of the logo).
- The smallest size is 16 px; below 32 px the white bar in the band can drop out.
- It works on light and dark backgrounds as it is, so there is no separate dark version.

## Colors

The palette is GNOME's, so Beamdown sits naturally beside other GNOME apps.

<div class="bd-swatches" markdown>

<div class="bd-swatch" style="--swatch:#3584e4"><strong>Beamdown Blue</strong><code>#3584e4</code><span>Primary: buttons, the band, selection</span></div>
<div class="bd-swatch" style="--swatch:#1c71d8"><strong>Deep Blue</strong><code>#1c71d8</code><span>Links and the arrow on light backgrounds</span></div>
<div class="bd-swatch" style="--swatch:#62a0ea"><strong>Sky</strong><code>#62a0ea</code><span>The band's highlight; links on dark</span></div>
<div class="bd-swatch" style="--swatch:#241f31"><strong>Ink</strong><code>#241f31</code><span>Text and the Markdown mark</span></div>
<div class="bd-swatch bd-swatch--light" style="--swatch:#fafafb"><strong>Paper</strong><code>#fafafb</code><span>Light backgrounds; slides use pure white</span></div>
<div class="bd-swatch" style="--swatch:#9a9996"><strong>Slab</strong><code>#9a9996</code><span>The logo's depth; quiet borders</span></div>
<div class="bd-swatch" style="--swatch:#222226"><strong>Night</strong><code>#222226</code><span>Dark backgrounds</span></div>
<div class="bd-swatch" style="--swatch:#2e2e32"><strong>Raised</strong><code>#2e2e32</code><span>Dark surfaces: header bar, sidebar, cards</span></div>

</div>

Blue is for one thing per view: the main action, the current item, or the link. Everything else is ink on paper, or white on night.

## Type

| Use | Typeface | Weight |
| --- | --- | --- |
| Headings | Inter Display (or Inter) | 800 |
| Text and interface | Inter | 400, 600 for emphasis |
| Markdown, code and commands | JetBrains Mono | 400 |

In the app the interface takes your desktop's font (Cantarell or Adwaita Sans on GNOME); Inter stands in for it on the web. Markdown is always shown in JetBrains Mono, because it's what the user writes.

## Voice

- Plain and short. Say what something does, then show it.
- Show the Markdown. A snippet beats a paragraph about it.
- Credit where things come from: Hype, Beamer, pandoc, Mermaid.
- No hype about Hype. Let the slides speak.

## Screenshots and slides

- Show real decks, such as [`examples/tour`](https://github.com/sergio-gimenez/beamdown/tree/fork/examples/tour), never mock-ups.
- Offer both GNOME styles where you can: dark and light.
- Round screenshot corners to 12 px with a soft shadow, as GNOME rounds its windows.
