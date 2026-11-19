# Present and export

Click **Present** or press **Ctrl+Space** (or **F5**) to toggle fullscreen presentation from the selected slide. Press **Shift+F5** to start from the first slide, or return to it while already presenting. Click the slide to go to the next one. Use the arrows to navigate, Space to play or pause video, and Escape to return to editing.

Finished videos hold their last frame. Press Space again to replay from the beginning.

## Presenter View

With more than one display, Beamdown sends the slides fullscreen to an external display
and opens Presenter View on the laptop display with the current slide, next slide,
and any speaker notes written as `<!-- comments -->`. If Beamdown is already on an
external display, that display remains the audience display. Navigate from either
display with the presentation shortcuts. Connecting or disconnecting a display ends
the show and returns to the editor on a connected display.

Choose **Export as PDF** or **Export as PowerPoint** from the file menu in the top bar, or press **Ctrl+E** for PDF and **Ctrl+Shift+E** for PowerPoint, to share your presentation. Both exports are built into Beamdown. PowerPoint renders slides and converted animations at 4K (3840 × 2160), storing slides as high-quality JPEG like the pictures in a PDF. Slides preserve the rendered appearance rather than exposing editable text and shapes; the receiving computer does not need your fonts installed. Videos are embedded, and animated WebP/GIF images are converted to MP4 automatically without changing the original files. PDF captures still slides.

## Export to PDF and PowerPoint

Export runs in the background. The top bar shows progress through rendering, video conversion, and packaging under the presentation name, with a **Cancel export** button. You can keep editing; the export uses the presentation as it was when you started. Failed or cancelled exports leave an existing file intact.

PDF keeps text as vectors and sizes embedded images for their visible area at 4K, omitting unused pixels outside spanning crops. Images are stored as high-quality JPEG, which keeps exports fast and small; at 4K the compression is not visible.

PowerPoint export automatically converts other video formats, including WebM, to H.264 MP4 with AAC audio, leaving your originals untouched. Compatible MP4s are embedded directly. Use `fit` for videos that aren’t 16:9. Video autoplay and looping may vary between presentation apps; playback in Microsoft PowerPoint has not yet been verified.
