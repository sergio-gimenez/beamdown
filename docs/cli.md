# Command line and agents

Beamdown's commands need no display, so a script or an AI agent can build a presentation from start to finish. A presentation is just a Markdown file: write it with any tool, then check, preview, and export it with `beamdown`.

```sh
beamdown new talk/presentation.md --title "My talk" --theme metropolis
beamdown check talk/presentation.md                   # every problem, with its slide and line
beamdown slides talk/presentation.md                  # an outline: number, lines, headline, media
beamdown render talk/presentation.md --slide 3 -o slide.png
beamdown render talk/presentation.md -o slides/       # every slide, plus slides.json
beamdown export talk/presentation.md talk.pdf         # or talk.pptx
beamdown themes
```

`check` reports all problems at once, such as missing media, invalid layout options, and unfinished code fences, and warns when a slide holds so much text that it shrinks below a readable size. `render --slide` writes a PNG even for a slide with problems, showing them on a banner, so you can look at what went wrong. Add `--json` to any command for structured output, and `--width` to `render` for another size. Commands exit 0 on success and 1 on failure, with errors on stderr.

`beamdown` alone lists the commands, and `beamdown open` starts the editor. `beamdown help format` prints the whole slide format, from front matter to media options, in a form an agent can read once and work from. `beamdown help <command>` lists a command's options.

To teach your coding agents about Beamdown, run `beamdown skill install`. It copies a short skill to `~/.agents/skills/beamdown/`, where Codex finds it, and links it into `~/.claude/skills/` for Claude Code. The skill points the agent at `beamdown help format`, so it stays current as Beamdown is upgraded. `beamdown skill` prints it instead.

If the presentation is open in the editor, changes written to the file appear there right away, and the editor stays on the slide you were viewing, even when slides are added or removed before it. **Ctrl+Z** undoes such a change. The editor never replaces unsaved changes of its own.
