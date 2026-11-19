# Write your slides

Separate slides with `---`, with a blank line on either side:

````markdown
# A big idea

---

# Keep it simple

- Write in Markdown
- Put your slides in order
- Tell your story

---

> Make something wonderful.

— Your closing thought

---

# Show the code

```ruby
class Presentation
  def next_slide
    slides.next
  end
end
```
````

Headlines are big by default. Quotes, lists, tables, and inline `code` work too. Ordinary line breaks stay visible on the slide. Code blocks fit the slide and use syntax highlighting when you specify a language, such as `ruby`, `rust`, `javascript`, `bash`, or `json`.

Tables use GitHub's pipe syntax. Colons in the line under the header align a column: `:---` left, `:---:` center, `---:` right. Extra spaces around a cell's text pad it, so `|  100,000 |` keeps its leading space.

```markdown
| Plan | Price | Seats |
| --- | :---: | ---: |
| Basic | $9 | 1 |
| Team | $29 | 10 |
```

The single-slide editor hides the blank lines around slide separators, leaving just your content to edit.
