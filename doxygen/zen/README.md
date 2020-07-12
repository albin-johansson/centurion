Zen Doxygen Theme
=================

This is a theme for Doxygen designed to be easy on the eyes and help you easily
find what you are looking for. Developers spend a lot of time looking at
documentation. The Zen theme hopes to make it a bit more pleasurable to sift
through large hunks of documentation.

<img src="https://raw.githubusercontent.com/ZenCPP/zen-doxygen-theme/master/screenshot.png" />

## Usage

1. Create a new `Doxyfile` in your project, if you haven't done so yet
2. Download a copy of this repository, either as a zip-file or a Git clone.
3. Edit your `Doxyfile` and update `HTML_HEADER`, `HTML_FOOTER` and
   `HTML_STYLEHSEET` to point to the respective files in this repository.

The generated documentation should now have the Zen theme by default.

The following is an example of how the configuration could look:

```
HTML_HEADER            = "doxygen-theme/header.html"
HTML_FOOTER            = "doxygen-theme/footer.html"
HTML_STYLESHEET        = "doxygen-theme/stylesheet.css"
```

## License

You are free to use this theme in your own creations. Giving a bit of credit to
the original authors is always appreciated but not required.

