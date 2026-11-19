---
name: beamdown
description: |
  Make and edit slide presentations with Beamdown, which turns one Markdown file into
  slides, PDF, and PowerPoint. Use for ANY request to create, change, review, or
  export a presentation, deck, slides, talk, or keynote, and for any .md file
  that is a Beamdown presentation.
---

# Beamdown

A Beamdown presentation is one Markdown file with `images/` and `videos/` beside it.
You write the file with your ordinary editing tools; the `beamdown` command starts,
checks, renders, and exports it. No command needs a display.

Run `beamdown help format` first. It prints the whole slide format, including front
matter, slide separators, and image and video options, for this version of Beamdown.

You write the first draft; the person finishes it in Beamdown's visual editor. So
keep the Markdown plain and easy to change, and follow their brand from the start.

## Brand guidelines

Before writing, look for the person's brand guidelines: in their request, or in a
`BRAND.md` (any case) beside the presentation or in a folder above it. Apply them:

- Colors, fonts and the running header go in the front matter: `color_background`,
  `color_foreground`, `color_accent` and the other `color_*` values, `font`,
  `heading_font`, `heading_weight`, `text_size`, `heading_size` and `header`.
  Use their exact hex values; never invent brand colors.
- Content rules (tone, bullets per slide, a logo's position, sections) apply to
  every slide you write.
- With no guidelines, use a bundled theme (`beamdown themes`) and say which.

## Workflow

1. Start: `beamdown new talk/presentation.md --title "My talk"` (`beamdown themes` lists
   themes for `--theme`). For an existing presentation, `beamdown slides <file>`
   prints an outline with each slide's number and lines.
2. Edit the Markdown file directly. Put media in `images/` or `videos/` and
   reference it by filename only.
3. Check: `beamdown check <file> --json` reports every problem with its slide and
   line. Fix errors, and treat a cramped-text warning as a cue to say less or
   split the slide.
4. Look: `beamdown render <file> --slide N -o /tmp/slide.png`, then view the PNG.
   Do this for slides whose layout matters: images, code, long text.
5. Hand it over: say where the file is and that `beamdown open <file>` opens it in
   the editor, where they can reorder, retype and restyle it.
6. Export when asked: `beamdown export <file> talk.pdf` or `talk.pptx`.

## Working with the person

- If they have the presentation open in the Beamdown editor, your saved edits appear
  there at once and the editor stays on the slide they are viewing. `beamdown open
  <file>` opens the editor for them; it needs their desktop, so do not wait on it.
- Slides are for an audience: a headline, a few bullets, or one image each. Prefer
  more slides over fuller ones.
- Every command takes `--json`, exits 0 on success and 1 on failure, and writes
  errors to stderr. `beamdown help <command>` lists a command's options.
